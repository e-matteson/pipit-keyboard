use time::*;
use std::path::Path;
use std::collections::BTreeMap;

use types::{Sequence, KeyPress, Maps, SeqType, KmapPath, CCode, ToC,
            Options, OpDef, OpType};
use format::{Format, CArray, KmapBuilder, ModeBuilder, compress,
             make_compression_macros};



impl KeyPress {
    pub fn as_bytes(&self, use_mods: bool) -> Vec<CCode> {
        let mut v: Vec<CCode> = Vec::new();
        v.push(CCode(format!("{}&0xff", self.key)));
        if use_mods {
            v.push(CCode(format!("({})&0xff", self.modifier)));
        }
        v
    }
}

impl Options {
    pub fn format(&self) -> Format {
        let mut f = Format::new();
        for (name, op) in self.get_non_internal() {
            f.append(&op.format(&name.to_c()));
        }
        f.append_newline();
        f
    }
}


impl OpDef {
    pub fn format(&self, name: &CCode) -> Format {
        match self.op_type {
            OpType::DefineInt => {
                format_define(name,
                              &self.get_val().unwrap_int().to_c())
            }
            OpType::DefineString => {
                format_define(name,
                              &self.get_val().unwrap_str().to_c())
            }
            OpType::IfdefValue => {
                format_define(&self.get_val().unwrap_str().to_c(),
                              &CCode::new())
            }
            OpType::IfdefKey => {
                let blank = "".to_c();
                let x = if self.get_val().unwrap_bool() {
                    name
                } else {
                    &blank
                };
                format_define(x, &blank)
            }
            OpType::Uint8 => {
                format_uint8(&name, self.get_val().unwrap_int())
            }
            OpType::Array1D => {
                CArray::new()
                    .name(name)
                    .fill_1d(self.get_val().unwrap_vec())
                    .format()
            }
            OpType::Array2D => {
                CArray::new()
                    .name(name)
                    .fill_2d(self.get_val().unwrap_vec2())
                    .format()
            }
            _ => panic!(format!("option cannot be formatted: {}", name)),
        }
    }
}

impl Sequence {

    pub fn to_bytes(&self, use_compression: bool, use_mods: bool) -> Vec<CCode>{
        // TODO different name for "bytes"?
        if use_compression{
            self.to_compressed_bytes(use_mods)
        }
        else {
            self.to_raw_bytes(use_mods)
        }
    }

    fn to_raw_bytes(&self, use_mods: bool) -> Vec<CCode> {
        let mut v: Vec<CCode> = Vec::new();
        for keypress in self.0.iter() {
            v.extend(keypress.as_bytes(use_mods));
        }
        v
    }

    fn to_compressed_bytes(&self, use_mods: bool) -> Vec<CCode> {
        compress(self, use_mods)
    }

}



impl Maps {

    pub fn format(&self, file_name_base: &str) -> Format {
        let mut f = Format::new();
        f.append(&format_intro(&format!("{}.h", file_name_base)));
        f.append(&self.options.format());
        f.append(&self.format_modes());
        f.append(&format_outro());
        f
    }

    fn format_modes (&self) -> Format {
        let mut f = Format::new();
        f.append(&self.format_command_enum());
        f.append(&self.format_seq_type_enum());
        f.append(&self.format_mode_enum());
        f.append(&self.format_modifiers());

        let mut struct_names = BTreeMap::new();
        f.append(&self.format_kmaps(&mut struct_names));

        let mut mode_struct_names = Vec::new();
        for (mode, kmap_infos) in self.modes.iter() {
            let m = ModeBuilder {
                infos: &kmap_infos,
                kmap_struct_names: &struct_names,
                seq_types: self.get_seq_types(),
                mode_name: &mode,
                mod_chords: self.get_mod_chords(mode),
                anagram_chords: self.get_anagrams(mode),
            };
            let mut tmp = CCode::new();
            f.append(&m.format(&mut tmp));
            mode_struct_names.push(CCode(format!("&{}", tmp)));
        }
        f.append_newline();
        f.append(&CArray::new()
                 .name(&"mode_structs".to_c())
                 .is_extern(true)
                 .c_type(&"ModeStruct*".to_c())
                 .fill_1d(&mode_struct_names)
                 .format());
        f.append_newline();
        f
    }

    fn format_kmaps(&self,
                    kmap_struct_names: &mut BTreeMap<SeqType,
                                                     BTreeMap<KmapPath, CCode>>)
                    -> Format
    {
        // Format all keymap structs, and return their names
        let mut f = Format::new();
        for seq_type in self.sequences.keys() {
            let l = KmapBuilder::new(seq_type.clone(),
                                     &self.sequences[seq_type],
                                     &self.chords,
                                     &self.kmap_ids);
            let mut tmp: BTreeMap<KmapPath, CCode> = BTreeMap::new();
            f.append(&l.format(&mut tmp));
            kmap_struct_names.insert(seq_type.to_owned(), tmp);
        }
        f.append_newline();
        f
    }

    fn format_mode_enum (&self) -> Format {
        let modes_list: Vec<_> = self.modes.keys()
            .map(|x| x.to_c().to_uppercase())
            .collect();
        Format {
            h: make_enum(&modes_list, &"mode_enum".to_c()),
            c: CCode::new(),
        }
    }

    fn format_modifiers (&self) -> Format {
        let mut mod_indices = BTreeMap::new();

        for name in self.get_mod_names().iter(){
            mod_indices.insert(name.to_owned(),
                               format!("{}_ENUM", name).to_c().to_uppercase());
        }
        let mut f = Format {
            h: make_enum(&mod_indices.values().map(|x| x.to_owned()).collect(),
                         &"mod_enum".to_c()),
            c: CCode::new(),
        };
        f.append(&format_define(&"NUM_MODIFIERS".to_c(),
                                &mod_indices.len().to_c()));
        f.append(&format_define(&"NUM_WORDMODS".to_c(),
                                &self.wordmods.len().to_c()));
        f.append(&format_define(&"NUM_MODIFIERKEYS".to_c(),
                                &self.modifierkeys.len().to_c()));
        f.append(&CArray::new()
                 .name(&"wordmod_indices".to_c())
                 .c_type(&"mod_enum".to_c())
                 .fill_1d(&self.wordmods.iter()
                          .map(|x| mod_indices[x].clone())
                          .collect())
                 .format());
        f.append(&CArray::new()
                 .name(&"modifierkey_indices".to_c())
                 .c_type(&"mod_enum".to_c())
                 .fill_1d(&self.modifierkeys.iter()
                          .map(|x| mod_indices[x].to_owned())
                          .collect())
                 .format());
        f.append(&CArray::new()
                 .name(&"modifierkey_keys".to_c())
                 .fill_1d(&self.modifierkeys.iter()
                          .map(|x| format!("({})&0xff", self.get_mod_key(x)))
                          .collect())
                 .format());
        f
    }

    fn format_command_enum (&self) -> Format {
        let command_list: Vec<_> = self.sequences[&SeqType::Command].keys()
            .map(|x| x.to_c().to_uppercase())
            .collect();
        Format {
            h: make_enum(&command_list, &"command_enum".to_c()),
            c: CCode::new(),
        }
    }

    fn format_seq_type_enum (&self) -> Format {
        let v: Vec<_> = self.get_seq_types().into_iter()
            .map(|s| s.to_c().to_uppercase())
            .collect();
        Format {
            h: make_enum(&v, &"seq_type_enum".to_c()),
            c: CCode::new(),
        }
    }
}


pub fn format_intro(h_file_name: &str) -> Format{
    let mut f = format_autogen_message();

    let guard_name = make_guard_name(h_file_name);
    let start_namespace = "namespace conf{\n\n";

    f.h += format!("#ifndef {}\n#define {}\n\n", guard_name, guard_name);
    f.h += "#include <Arduino.h>\n";
    f.h += "#include \"keycodes.h\"\n\n";
    f.h += "#include \"structs.h\"\n\n";
    f.h += "typedef void (*voidFuncPtr)(void);\n\n";
    f.h += make_compression_macros();
    f.h += start_namespace;

    f.c += format!("#include \"{}\"\n\n", h_file_name);
    f.c += start_namespace;
    f
}

pub fn format_outro() -> Format {
    let end_namespace = "\n} // end namespace\n";
    let mut f = Format::new();

    f.h += make_debug_macros();
    f.h += end_namespace;
    f.h += "\n#endif\n";

    f.c += end_namespace;
    f
}

fn format_autogen_message( ) -> Format {
    const AUTHOR: &str = "pipit-config";

    let mut s = format!("/**\n * Automatically generated by {} on:  {}\n",
                        AUTHOR,
                        now().strftime("%c").unwrap()
    );
    s += " * Do not make changes here, they will be overwritten.\n */\n\n";
    Format{
        h: s.to_c(),
        c: s.to_c(),
    }
}

fn make_guard_name(h_file_name: &str) -> CCode {
    // TODO remove unsafe characters, like the python version
    let error_message = format!("invalid header file name: {}", h_file_name);
    let p: String = Path::new(h_file_name)
        .file_name()
        .expect("failed to get file name")
        .to_str().unwrap().to_string()
        .to_uppercase()
        .chars()
        .map(|c| if c.is_alphanumeric() {c} else {'_'})
        .collect();
    let first = p.chars().nth(0)
        .expect(&error_message);
    if !first.is_alphabetic() && first != '_' {
        panic!(error_message);
    }
    CCode(p + "_")
}

fn make_debug_macros() -> CCode {
    // TODO clean up debug macros
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
    s += "#endif\n\n ";
    CCode(s)
}


fn make_enum(variants: &Vec<CCode>, name: &CCode) -> CCode {
    // TODO move somewhere?
    // TODO only assign first to 0
    let contents = variants
        .iter()
        .enumerate()
        .fold(String::new(),
              |acc, (index, field)|
              format!("{}  {} = {},\n", acc, field, index));

    CCode(format!("enum {}{{\n{}}};\n\n", name, contents))
}

fn format_define(name: &CCode, value: &CCode) -> Format {
    // Name will be written in all-caps.

    Format {
        h: CCode(format!("#define {} {}\n",
                         name.to_uppercase(),
                         value)),
        c: CCode::new(),
    }
}

fn format_uint8(name: &CCode, value: i64) -> Format {
    if value > 255 || value < 0 {
        panic!("8-bit value out of range 0-255");
    }
    Format {
        h: CCode(format!("extern const uint8_t {};\n",
                         name)),

        c: CCode(format!("extern const uint8_t {} = {};\n\n",
                         name,
                         value)),
    }
}
