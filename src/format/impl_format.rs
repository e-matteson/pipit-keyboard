use time::*;
use std::path::Path;
use std::collections::BTreeMap;
use std::fmt::Display;
use itertools::Itertools;

use types::{AllData, CCode, CTree, Field, KeyPress, KmapPath, Name, SeqType,
            Sequence, ToC};

use types::errors::*;

use format::{compress, make_compression_macros, CFiles, KmapBuilder,
             ModeBuilder};


impl KeyPress {
    fn truncate(contents: &CCode) -> CCode {
        CCode(format!("({})&0xff", contents))
    }

    pub fn format_key(&self) -> CCode {
        match self.key {
            Some(ref code) => KeyPress::truncate(code),
            None => KeyPress::empty_code(),
        }
    }

    fn format_mods(&self) -> CCode {
        match self.mods {
            Some(ref codes) => KeyPress::truncate(&CCode::join(codes, "|")),
            None => KeyPress::empty_code(),
        }
    }

    fn as_bytes(&self, use_mods: bool) -> Vec<CCode> {
        let mut v: Vec<CCode> = Vec::new();
        v.push(self.format_key());
        if use_mods {
            v.push(self.format_mods());
        }
        v
    }
}


impl CTree {
    pub fn format(&self) -> Result<CFiles> {
        Ok(match *self {
            CTree::Define {
                ref name,
                ref value,
            } => format_define(name, value),
            CTree::Ifdef { ref name, value } => if value {
                format_define(name, &CCode::new())
            } else {
                CFiles::new()
            },
            CTree::Var {
                ref name,
                ref value,
                ref c_type,
                is_extern,
            } => format_var(name, value, c_type, is_extern),
            CTree::Array {
                ref name,
                ref values,
                ref c_type,
                is_extern,
            } => format_array(name, values, c_type, is_extern),
            CTree::CompoundArray {
                ref name,
                ref values,
                ref subarray_type,
                is_extern,
            } => format_compound_array(name, values, subarray_type, is_extern)?,
            CTree::EnumDecl {
                ref name,
                ref variants,
            } => format_enum_decl(name, variants),
            CTree::StructInstance {
                ref name,
                ref c_type,
                ref fields,
                is_extern,
            } => format_struct_instance(name, c_type, fields, is_extern),
            CTree::Namespace {
                ref name,
                ref contents,
            } => format_namespace(name, contents)?,
            CTree::Include { ref path } => format_include(path),
            CTree::LiteralH(ref text) => CFiles::with_h(text),
            CTree::LiteralC(ref text) => CFiles::with_c(text),
            // CTree::CommentH(ref text) => CFiles::with_h(comment(text)),
            // CTree::CommentC(ref text) => CFiles::with_c(comment(text)),
            CTree::Group(ref vec) => format_group(vec)?,

            // CTree::LiteralH(ref literal) => CFiles::with_h(literal),
            CTree::IncludeGuard {
                ref header_name,
                ref contents,
            } => format_guard(header_name, contents)?,
        })
    }
}



impl Sequence {
    pub fn as_bytes(
        &self,
        use_compression: bool,
        use_mods: bool,
    ) -> Vec<CCode> {
        // TODO different name for "bytes"?
        if use_compression {
            self.as_compressed_bytes(use_mods)
        } else {
            self.as_raw_bytes(use_mods)
        }
    }

    fn as_raw_bytes(&self, use_mods: bool) -> Vec<CCode> {
        let mut v: Vec<CCode> = Vec::new();
        for keypress in &self.0 {
            v.extend(keypress.as_bytes(use_mods));
        }
        v
    }

    fn as_compressed_bytes(&self, use_mods: bool) -> Vec<CCode> {
        compress(self, use_mods)
    }
}


impl AllData {
    pub fn save_as(&self, file_name_base: &str) -> Result<()> {
        (|| {
            let c_tree = self.to_c_tree(file_name_base)?;
            let f = c_tree.format()?;
            // TODO as_ref?
            let dir = self.output_directory
                .as_ref()
                .ok_or_else(|| "output directory option not set")?;
            f.save(dir, file_name_base)
        })()
            .chain_err(|| "failure to save configuration")
    }

    pub fn to_c_tree(&self, file_name_base: &str) -> Result<CTree> {
        let h_file_name = format!("{}.h", file_name_base);

        let mut group = Vec::new();
        group.push(self.format_options());
        group.push(self.format_modifiers()?);
        group.push(self.format_command_enum());
        group.push(self.format_seq_type_enum());
        group.push(self.format_mode_enum());
        group.push(self.format_modes()?);
        wrap_intro(&h_file_name, CTree::Group(group))
    }

    fn format_modes(&self) -> Result<CTree> {
        let mut g = Vec::new();
        let mut kmap_struct_names = BTreeMap::new();
        g.push(self.format_kmaps(&mut kmap_struct_names)?);

        let mut mode_struct_names = Vec::new();
        for (mode, info) in &self.modes {
            let m = ModeBuilder {
                info: info,
                kmap_struct_names: &kmap_struct_names,
                seq_types: self.get_seq_types(),
                mode_name: mode,
                mod_chords: self.get_mod_chords(mode),
                anagram_chords: self.get_anagram_chords(mode),
            };
            let mut tmp = CCode::new();
            g.push(m.format(&mut tmp)?);
            mode_struct_names.push(CCode(format!("&{}", tmp)));
        }
        g.push(CTree::Array {
            name: "mode_structs".to_c(),
            values: mode_struct_names,
            c_type: "ModeStruct*".to_c(),
            is_extern: true,
        });
        Ok(CTree::Group(g))
    }

    fn format_kmaps(
        &self,
        kmap_struct_names: &mut BTreeMap<SeqType, BTreeMap<KmapPath, CCode>>,
    ) -> Result<CTree> {
        // Format all keymap structs, and return their names
        let mut g = Vec::new();
        for seq_type in self.sequences.keys() {
            let builder = KmapBuilder::new(
                *seq_type,
                &self.sequences[seq_type],
                &self.chords,
                &self.kmap_ids,
            );
            let mut tmp: BTreeMap<KmapPath, CCode> = BTreeMap::new();
            g.push(builder.format(&mut tmp)?);
            kmap_struct_names.insert(seq_type.to_owned(), tmp);
        }
        Ok(CTree::Group(g))
    }

    fn format_options(&self) -> CTree {
        CTree::Group(self.options.clone())
    }

    fn format_mode_enum(&self) -> CTree {
        let modes_list: Vec<_> =
            self.modes.keys().map(|x| x.to_c().to_uppercase()).collect();
        CTree::EnumDecl {
            name: "mode_enum".to_c(),
            variants: modes_list,
        }
    }

    fn make_mod_index_variants(&self) -> BTreeMap<Name, CCode> {
        // TODO rename?
        let mut all_index_variants = BTreeMap::new();
        for name in &self.get_mod_names() {
            all_index_variants.insert(
                name.to_owned(),
                format!("{}_ENUM", name).to_c().to_uppercase(),
            );
        }
        all_index_variants
    }

    fn get_variants(
        &self,
        mod_names: &[Name],
        all_mod_indices: &BTreeMap<Name, CCode>,
    ) -> Vec<CCode> {
        mod_names
            .iter()
            .map(|x| all_mod_indices[x].clone())
            .collect()
    }

    fn format_modifiers(&self) -> Result<CTree> {
        let all_index_variants = self.make_mod_index_variants();
        let mut group = Vec::new();
        group.push(CTree::EnumDecl {
            name: "mod_enum".to_c(),
            variants: all_index_variants.values().cloned().collect(),
        });

        group.push(CTree::Define {
            name: "NUM_MODIFIERS".to_c(),
            value: all_index_variants.len().to_c(),
        });


        group.push(CTree::Define {
            name: "NUM_WORD_MODS".to_c(),
            value: self.word_mods.len().to_c(),
        });

        group.push(CTree::Define {
            name: "NUM_ANAGRAM_MODS".to_c(),
            value: self.anagram_mods.len().to_c(),
        });

        group.push(CTree::Define {
            name: "NUM_ANAGRAMS".to_c(),
            value: self.get_num_anagrams().to_c(),
        });

        group.push(CTree::Define {
            name: "NUM_PLAIN_MODS".to_c(),
            value: self.plain_mods.len().to_c(),
        });

        group.push(CTree::Array {
            name: "word_mod_indices".to_c(),
            values: self.get_variants(&self.word_mods, &all_index_variants),
            c_type: "mod_enum".to_c(),
            is_extern: true,
        });

        group.push(CTree::Array {
            name: "plain_mod_indices".to_c(),
            values: self.get_variants(&self.plain_mods, &all_index_variants),
            c_type: "mod_enum".to_c(),
            is_extern: true,
        });

        group.push(CTree::Array {
            name: "anagram_mod_indices".to_c(),
            values: self.get_variants(&self.anagram_mods, &all_index_variants),
            c_type: "mod_enum".to_c(),
            is_extern: true,
        });

        group.push(CTree::Array {
            name: "plain_mod_keys".to_c(),
            values: self.get_plain_mod_codes()?,
            c_type: "uint8_t".to_c(),
            is_extern: true,
        });

        Ok(CTree::Group(group))
    }

    fn get_plain_mod_codes(&self) -> Result<Vec<CCode>> {
        self.plain_mods
            .iter()
            .map(|name| Ok(self.get_single_keypress(name)?.format_mods()))
            .collect()
    }

    fn format_command_enum(&self) -> CTree {
        let command_list: Vec<_> = self.sequences[&SeqType::Command]
            .keys()
            .map(|x: &Name| x.to_owned().to_c().to_uppercase())
            .collect();
        CTree::EnumDecl {
            name: "command_enum".to_c(),
            variants: command_list,
        }
    }

    fn format_seq_type_enum(&self) -> CTree {
        let v: Vec<_> = self.get_seq_types()
            .into_iter()
            .map(|s| s.to_c().to_uppercase())
            .collect();
        CTree::EnumDecl {
            name: "seq_type_enum".to_c(),
            variants: v,
        }
    }
}


pub fn wrap_intro(h_file_name: &str, namespace_tree: CTree) -> Result<CTree> {
    // format!("#ifndef {}\n#define {}\n\n", guard_name, guard_name);
    let mut guard_group = Vec::new();
    guard_group.push(CTree::Include {
        path: "<Arduino.h>".to_c(),
    });
    guard_group.push(CTree::Include {
        path: "\"keycodes.h\"".to_c(),
    });
    guard_group.push(CTree::Include {
        path: "\"structs.h\"".to_c(),
    });
    guard_group.push(CTree::LiteralH(
        "typedef void (*voidFuncPtr)(void);\n".to_c(),
    ));
    guard_group.push(make_compression_macros());
    guard_group.push(make_debug_macros());

    guard_group.push(CTree::Namespace {
        name: "conf".to_c(),
        contents: Box::new(namespace_tree),
    });

    let guard = CTree::IncludeGuard {
        header_name: h_file_name.to_owned(),
        contents: Box::new(CTree::Group(guard_group)),
    };

    let mut outer_group = Vec::new();
    let msg = autogen_message();
    outer_group.push(CTree::LiteralC(msg.clone()));
    outer_group.push(CTree::LiteralH(msg));
    outer_group.push(guard);

    Ok(CTree::Group(outer_group))
}


fn autogen_message() -> CCode {
    const AUTHOR: &str = "pipit-config";

    let mut s = format!(
        "/**\n * Automatically generated by {} on:  {}\n",
        AUTHOR,
        now().strftime("%c").unwrap()
    );
    s += " * Do not make changes here, they will be overwritten.\n */\n\n";
    s.to_c()
}

fn make_guard_id(h_file_name: &str) -> Result<CCode> {
    // TODO remove unsafe characters, like the python version
    let error_message = format!("invalid header file name: {}", h_file_name);
    let p: String = Path::new(h_file_name)
        .file_name()
        .ok_or_else(|| "failure to get file name")?
        .to_str()
        .unwrap()
        .to_string()
        .to_uppercase()
        .chars()
        .map(|c| if c.is_alphanumeric() { c } else { '_' })
        .collect();
    let first = p.chars().nth(0).ok_or_else(|| error_message.clone())?;

    if !first.is_alphabetic() && first != '_' {
        bail!(error_message);
    }
    Ok(CCode(p + "_"))
}

fn make_debug_macros() -> CTree {
    // TODO clean up debug macros
    // TODO use Define variant instead
    let mut s = String::new();
    s += "\n#if DEBUG_MESSAGES == 0\n";
    s += "#define DEBUG1(msg)\n";
    s += "#define DEBUG1_LN(msg)\n";
    s += "#define DEBUG2(msg)\n";
    s += "#define DEBUG2_LN(msg)\n";
    s += "#endif\n\n";
    s += "#if DEBUG_MESSAGES == 1\n";
    s += "#define DEBUG1(msg) Serial.print(msg)\n";
    s += "#define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "#define DEBUG2(msg)\n";
    s += "#define DEBUG2_LN(msg)\n";
    s += "#endif\n\n";
    s += "#if DEBUG_MESSAGES == 2\n";
    s += "#define DEBUG1(msg) Serial.print(msg)\n";
    s += "#define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "#define DEBUG2(msg) Serial.print(msg)\n";
    s += "#define DEBUG2_LN(msg) Serial.println(msg)\n";
    s += "#endif\n\n";
    CTree::LiteralH(CCode(s))
}


fn format_struct_instance(
    name: &CCode,
    c_type: &CCode,
    fields: &[Field],
    is_extern: bool,
) -> CFiles {
    // TODO only assign first to 0?
    let mut c = format!(
        "{}const {} {} = {{\n",
        format_extern(is_extern),
        c_type,
        name
    );
    for field in fields {
        c += &format!("  {}, // {}\n", field.value, field.name);
    }
    c += "};\n";
    CFiles {
        h: CCode::new(),
        c: CCode(c),
    }
}

fn format_enum_decl(name: &CCode, variants: &[CCode]) -> CFiles {
    // TODO only assign first to 0?
    let contents = variants
        .into_iter()
        .enumerate()
        .fold(String::new(), |acc, (index, field)| {
            format!("{}  {} = {},\n", acc, field, index)
        });
    CFiles {
        h: CCode(format!("enum {}{{\n{}}};\n\n", name, contents)),
        c: CCode::new(),
    }
}

fn format_define(name: &CCode, value: &CCode) -> CFiles {
    // Name will be written in all-caps.
    CFiles {
        h: CCode(format!("#define {} {}\n", name.to_uppercase(), value)),
        c: CCode::new(),
    }
}

fn format_var(
    name: &CCode,
    value: &CCode,
    c_type: &CCode,
    is_extern: bool,
) -> CFiles {
    CFiles {
        h: format!("{}const {} {};\n", format_extern(is_extern), c_type, name)
            .to_c(),
        c: CCode(format!("const {} {} = {};\n\n", c_type, name, value)),
    }
}

fn format_include(path: &CCode) -> CFiles {
    CFiles::with_h(&format!("#include {}\n", path).to_c())
}

fn format_guard(header_name: &str, contents: &Box<CTree>) -> Result<CFiles> {
    let id = make_guard_id(header_name)?;
    let mut f = CFiles {
        h: format!("#ifndef {}\n#define {}\n", id, id).to_c(),
        c: format!("#include \"{}\"\n", header_name).to_c(),
    };
    f += contents.format()?;
    f += CFiles::with_h(&format!("#endif // {}", id));
    Ok(f)
}

fn format_namespace(name: &CCode, contents: &CTree) -> Result<CFiles> {
    let open = format!("namespace {} {{\n", name).to_c();
    let close = format!("\n}} // end namespace {}\n", name).to_c();
    let mut f = CFiles::with(&open);
    f += contents.format()?;
    f += CFiles::with(&close);
    Ok(f)
}
fn format_group(v: &[CTree]) -> Result<CFiles> {
    let mut f = CFiles::new();
    for node in v {
        f += node.format()?
    }
    Ok(f)
}

fn format_compound_array(
    name: &CCode,
    values: &[Vec<CCode>],
    subarray_type: &CCode,
    is_extern: bool,
) -> Result<CFiles> {
    // TODO prepend underscore? special meaning?
    let mut subarray_names: Vec<_> = (0..values.len())
        .map(|x| CCode(format!("{}_{}", name, x)))
        .collect();
    let mut g = Vec::new();
    for (sub_name, sub_values) in subarray_names.iter().zip(values.into_iter())
    {
        g.push(CTree::Array {
            name: sub_name.to_owned(),
            values: sub_values.to_owned(),
            c_type: subarray_type.to_c(),
            is_extern: false,
        });
    }

    subarray_names.push("NULL".to_c());
    g.push(CTree::Array {
        name: name.to_owned(),
        values: subarray_names,
        c_type: format!("{}*", subarray_type).to_c(),
        is_extern: is_extern,
    });
    CTree::Group(g).format()
}

fn format_array(
    name: &CCode,
    values: &[CCode],
    c_type: &CCode,
    is_extern: bool,
) -> CFiles {
    let contents = make_c_array_contents(values);
    if is_extern {
        CFiles {
            h: CCode(format!("extern const {} {}[];\n", c_type, name)),
            c: CCode(format!(
                "extern const {} {}[] = {};\n\n",
                c_type,
                name,
                contents
            )),
        }
    } else {
        CFiles {
            h: CCode::new(),
            c: CCode(
                format!("const {} {}[] = {};\n\n", c_type, name, contents),
            ),
        }
    }
}

fn make_c_array_contents<T>(v: &[T]) -> CCode
where
    T: Display,
{
    let lines = wrap_in_braces(&to_code_vec(v));
    CCode::join(&lines, "\n")
}


fn wrap_in_braces(lines: &[CCode]) -> Vec<CCode> {
    let mut new: Vec<_> =
        lines.iter().map(|s| CCode(format!(" {}", s))).collect();
    new.insert(0, "{".to_c());
    new.push("}".to_c());
    new
}

fn to_code_vec<T>(v: &[T]) -> Vec<CCode>
where
    T: Display,
{
    // TODO rename
    let items_per_line = 4;
    let mut lines: Vec<String> = Vec::new();
    //  TODO use slice chunks instead of itertools?
    let chunks = &v.iter().map(|x| x.to_string()).chunks(items_per_line);
    for chunk in chunks {
        let tmp: Vec<_> = chunk.collect();
        lines.push(tmp.join(", ") + ", ");
    }
    let code_lines: Vec<_> = lines.into_iter().map(CCode).collect();
    code_lines
}


// fn comment(line: &CCode) -> CCode {
//     // only works for single lines.  must not contain \n.
//     format!("// {}", line).to_c()
// }

fn format_extern(is_extern: bool) -> CCode {
    let s = if is_extern { "extern " } else { "" };
    s.to_c()
}
