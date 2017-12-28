use time::*;
use std::collections::BTreeMap;

use types::{AllData, CCode, CTree, KeyPress, KmapPath, Name, SeqType,
            Sequence, ToC};

use types::errors::*;

use format::{compress, make_compression_macros, KmapBuilder, ModeBuilder};

impl AllData {
    pub fn save_as(&self, file_name_base: &str) -> Result<()> {
        (|| {
            let c_tree = self.render(file_name_base)?;
            let f = c_tree.format()?;
            // TODO as_ref?
            let dir = self.output_directory
                .as_ref()
                .ok_or_else(|| "output directory option not set")?;
            f.save(dir, file_name_base)
        })()
            .chain_err(|| "failure to save configuration")
    }

    pub fn render(&self, file_name_base: &str) -> Result<CTree> {
        let h_file_name = format!("{}.h", file_name_base);

        let mut group = Vec::new();
        group.push(self.render_options());
        group.push(self.render_modifiers()?);
        group.push(self.render_command_enum());
        group.push(self.render_seq_type_enum());
        group.push(self.render_mode_enum());
        group.push(self.render_modes()?);
        wrap_intro(&h_file_name, CTree::Group(group))
    }

    fn render_modes(&self) -> Result<CTree> {
        let mut g = Vec::new();
        let (tree, kmap_struct_names) = self.render_kmaps()?;
        g.push(tree);

        let mut mode_struct_pointers = Vec::new();
        for (mode, info) in &self.modes {
            let m = ModeBuilder {
                info: info,
                kmap_struct_names: &kmap_struct_names,
                seq_types: self.get_seq_types(),
                mode_name: mode,
                mod_chords: self.get_mod_chords(mode),
                anagram_chords: self.get_anagram_chords(mode),
            };
            let (tree, name) = m.render()?;
            g.push(tree);
            mode_struct_pointers.push(CCode(format!("&{}", name)));
        }
        g.push(CTree::Array {
            name: "mode_structs".to_c(),
            values: mode_struct_pointers,
            c_type: "ModeStruct*".to_c(),
            is_extern: true,
        });
        Ok(CTree::Group(g))
    }

    fn render_kmaps(
        &self,
    ) -> Result<(CTree, BTreeMap<SeqType, BTreeMap<KmapPath, CCode>>)> {
        // Render all keymap structs as CTrees, and return their names
        let mut kmap_struct_names = BTreeMap::new();
        let mut g = Vec::new();
        for seq_type in self.sequences.keys() {
            let builder = KmapBuilder::new(
                *seq_type,
                &self.sequences[seq_type],
                &self.chords,
            );
            let (tree, kmap_struct_names_for_seq_type) = builder.render()?;
            g.push(tree);
            kmap_struct_names
                .insert(seq_type.to_owned(), kmap_struct_names_for_seq_type);
        }
        Ok((CTree::Group(g), kmap_struct_names))
    }

    fn render_options(&self) -> CTree {
        CTree::Group(self.options.clone())
    }

    fn render_mode_enum(&self) -> CTree {
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

    fn render_modifiers(&self) -> Result<CTree> {
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

    fn render_command_enum(&self) -> CTree {
        let command_list: Vec<_> = self.sequences[&SeqType::Command]
            .keys()
            .map(|x: &Name| x.to_owned().to_c().to_uppercase())
            .collect();
        CTree::EnumDecl {
            name: "command_enum".to_c(),
            variants: command_list,
        }
    }

    fn render_seq_type_enum(&self) -> CTree {
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
