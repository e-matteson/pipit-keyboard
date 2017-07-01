use time::*;
use std::path::Path;
use std::collections::BTreeMap;

use types::{Sequence, KeyPress, Maps, SeqType, KmapPath, CCode,
            ToC, Options, OpDef, OpType};
use format::{Format, CArray, Lookup, compress, make_compression_macros};



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
        // f.append_newline();
        // f.append(&self.format_modes());
        f
    }

    // fn format_modes (&self) -> Format {
    //     Format{
    //         h: make_enum(&self.get_modes(), "mode_enum"),
    //         c: String::new(),
    //     }
    // }
}


impl OpDef {
    // TODO use CCode here?
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
                CArray::new(name)
                    .fill_1d(self.get_val().unwrap_vec())
                    .format()
            }
            OpType::Array2D => {
                CArray::new(name)
                    .fill_2d(self.get_val().unwrap_vec2())
                    .format()
            }
            _ => panic!(format!("option cannot be formatted: {}", name)),
        }
    }

}

// TODO put in c_array.rs

// struct ModeStruct {
//     plains: String,
//     macros: String,
//     words: String,
//     commands: String,
//     // wordmod_capital_chord: Chord,
//     // wordmod_nospace_chord: Chord,
//     // anagram_chords: Vec<Chord>,
// }

// impl ModeStruct{
//     fn format(&self, name: &str) -> Format {
//         let mut dict = BTreeMap::new();
//         dict.insert("plains", self.plains);
//         dict.insert("macros", self.macros);
//         dict.insert("words", self.words);
//         dict.insert("commands", self.commands);
//         // TODO how to make strings from vecs?
//         // dict.push("wordmod_capital_chord", self.wordmod_capital_chord.to_ints().to_string());
//         // dict.push("wordmod_nospace_chord", self.wordmod_nospace_chord.to_ints().to_string());
//         // dict.push("anagram_chords", self.anagram_chords.to_ints().to_string());
//         format_c_struct(&"ModeStruct".to_c(), name, &dict)

//     }
// }

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
        // f.append(&self.format_anagrams());
        // f.append(&self.format_wordmods());
        // f.append(&self.format_commands());
        // f.append(&self.format_plains());
        // f.append(&self.format_macros());
        // f.append(&self.format_words());

        f.append(&self.format_modes());

        f.append(&format_outro());
        f
    }

    fn format_kmaps(&self,
                    struct_names: &mut BTreeMap<SeqType,
                                                BTreeMap<KmapPath, CCode>>)
                    -> Format
    {
        let mut f = Format::new();

        // Format all keymap structs, and return their names
        for seq_type in self.sequences.keys() {
            let l = Lookup::new(seq_type.clone(),
                                &self.sequences[seq_type],
                                &self.chords,
                                &self.kmap_ids);
            let mut tmp: BTreeMap<KmapPath, CCode> = BTreeMap::new();
            f.append(&l.format(&mut tmp));
            struct_names.insert(seq_type.clone(), tmp);
        }
        f.append_newline();
        f
    }

    fn format_modes (&self) -> Format {
        let mut f = Format::new();
        f.append(&self.format_command_enum());
        let mut struct_names = BTreeMap::new();
        f.append(&self.format_kmaps(&mut struct_names));

        // for (mode, kmap_infos) in self.modes {
        //     let fields = BTreeMap::new();
        //     for seq_type in self.sequences.keys() {
        //         fields.insert(seq_type, Vec::new())
        //         for info in kmap_infos {
        //             let struct_name =
        //                 if seq_type == SeqType::Word && !info.use_words {
        //                     "NULL"
        //                 } else {
        //                     fields.get_mut(se) struct_names.get(info.path)
        //                         .expect("kmap struct name not found")
        //                 };
        //         }
        //     }
        //     let m = ModeStruct {

        //     }
        // }
        // TODO anagrams and wordmods
        // TODO mod positions
        // TODO mode structs
        // TODO mode struct array, enum
        f
    }

    fn format_command_enum (&self) -> Format {
        let command_list: Vec<_> = self.sequences[&SeqType::Command].keys()
            .map(|x| x.to_uppercase().to_c())
            .collect();
        Format {
            h: make_enum(&command_list, &"command_enum".to_c()),
            c: CCode::new(),
        }
    }

    // fn format_wordmods(&self) -> Format {
    //     let mut f = Format::new();
    //     for name in &self.wordmods {
    //         let all_chord_bytes: Vec<Vec<i64>> =
    //             self.options.get_modes().iter()
    //             .map(|mode|
    //                  match self.chords[mode].get(name) {
    //                      Some(c) => c.to_ints(),
    //                      None => Chord::new().to_ints(),})
    //             .collect();

    //         let full_name = format!("{}_chord_bytes", name);
    //         f.append(&CArray::new(&full_name)
    //                  .fill_2d(&all_chord_bytes)
    //                  .format())
    //     }
    //     f.append_newline();
    //     f
    // }

    // pub fn format_anagrams(&self) -> Format {
    //     // TODO consistent naming
    //     let mut f = Format::new();
    //     let mut anagram_ints: Vec<Vec<Vec<i64>>> = Vec::new();
    //     for mode in self.options.get_modes() {
    //         let v: Vec<Vec<i64>> = self.anagrams.iter()
    //             .map(|name|
    //                  match self.chords[&mode].get(name){
    //                      Some(c) => c.clone(),
    //                      None => Chord::new(),
    //                      // If this mode doesn't have anagram mods, they'll all be zero.
    //                      // TODO make sure the firmware doesn't try to use them...
    //                  })
    //             .map(|chord|
    //                  chord.to_ints())
    //             .collect();
    //         anagram_ints.push(v);
    //     }
    //     f.append(&CArray::new("anagram_chord_bytes")
    //              .fill_3d(&anagram_ints)
    //              .format());
    //     f
    // }
}


pub fn format_intro(h_file_name: &str) -> Format{
    let mut f = format_autogen_message();

    let guard_name = make_guard_name(h_file_name);
    let start_namespace = "namespace conf{\n\n";

    f.h += format!("#ifndef {}\n#define {}\n\n", guard_name, guard_name);
    f.h += "#include <Arduino.h>\n";
    f.h += "#include \"keycodes.h\"\n\n";
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
