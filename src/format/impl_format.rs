use time::*;
use std::path::Path;

use types::{Sequence, KeyPress, Chord, Maps, Options, OpDef, OpType};
use format::{Format, CArray, Lookup, compress, make_compression_macros};



impl KeyPress {
    pub fn as_bytes(&self, use_mods: bool) -> Vec<String> {
        let mut v: Vec<String> = Vec::new();
        v.push(format!("{}&0xff", self.key));
        if use_mods {
            v.push(format!("({})&0xff", self.modifier));
        }
        v
    }
}

impl Options {
    pub fn format(&self) -> Format {
        let mut f = Format::new();
        for (name, op) in self.get_non_internal() {
            f.append(&op.format(&name));
        }
        f.append_newline();
        f.append(&self.format_modes());
        f
    }

    fn format_modes (&self) -> Format {
        Format{
            h: make_enum(&self.get_modes(), "mode_enum"),
            c: String::new(),
        }
    }
}


impl OpDef {
    pub fn format(&self, name: &str) -> Format {
        match self.op_type {
            OpType::DefineInt => {
                self.format_define_int(name)
            }
            OpType::DefineString => {
                self.format_define_string(name)
            }
            OpType::IfdefValue => {
                self.format_ifdef_value()
            }
            OpType::IfdefKey => {
                self.format_ifdef_key(name)
            }
            OpType::Uint8 => {
                self.format_uint8(name)
            }
            OpType::Array1D => {
                self.format_array1d(name)
            }
            OpType::Array2D => {
                self.format_array2d(name)
            }
            _ => panic!(format!("option cannot be formatted: {}", name)),
        }
    }

    fn format_define_int(&self, name: &str) -> Format {
        Format {
            h: format!("#define {} {}\n",
                       name.to_uppercase(),
                       self.get_val().unwrap_int()),
            c: String::new(),
        }
    }

    fn format_define_string(&self, name: &str) -> Format {
        Format {
            h: format!("#define {} {}\n",
                        name.to_uppercase(),
                        self.get_val().unwrap_str()),
            c: String::new(),
        }
    }

    fn format_ifdef_value(&self) -> Format {
        Format {
            h: format!("#define {}\n",
                       self.get_val().unwrap_str()),
            c: String::new(),
        }
    }

    fn format_ifdef_key(&self, name: &str) -> Format {
        Format {
            h: if self.get_val().unwrap_bool() {
                format!("#define {}\n",
                        name.to_uppercase())
            } else {
                String::new()
            },

            c: String::new(),
        }
    }

    fn format_uint8(&self, name: &str) -> Format {
        Format {
            h: format!("extern const uint8_t {};\n",
                       name),

            c: format!("extern const uint8_t {} = {};\n\n",
                       name,
                       self.get_val().unwrap_int()),
        }
    }

    fn format_array1d(&self, name: &str) -> Format {
        CArray::new(name)
            .fill_1d(self.get_val().unwrap_vec())
            .format()
    }


    fn format_array2d(&self, name: &str) -> Format {
            CArray::new(name)
            .fill_2d(self.get_val().unwrap_vec2())
            .format()
    }

}


impl Sequence {

    pub fn to_bytes(&self, use_compression: bool, use_mods: bool) -> Vec<String>{
        // TODO different name for "bytes"?
        if use_compression{
            self.to_compressed_bytes(use_mods)
        }
        else {
            self.to_raw_bytes(use_mods)
        }
    }

    fn to_raw_bytes(&self, use_mods: bool) -> Vec<String> {
        let mut v: Vec<String> = Vec::new();
        for keypress in self.0.iter() {
            v.extend(keypress.as_bytes(use_mods));
        }
        v
    }

    fn to_compressed_bytes(&self, use_mods: bool) -> Vec<String> {
        compress(self, use_mods)
    }

}


impl Maps {

    pub fn format(&self, file_name_base: &str) -> Format {
        let mut f = Format::new();
        f.append(&format_intro(&format!("{}.h", file_name_base)));
        f.append(&self.options.format());
        f.append(&self.format_anagrams());
        f.append(&self.format_wordmods());
        f.append(&self.format_commands());
        f.append(&self.format_plains());
        f.append(&self.format_macros());
        f.append(&self.format_words());
        f.append(&format_outro());
        f
    }


    fn format_words (&self) -> Format {
        // format_lookups(&self.words, &self.chords, "word", true, false)
        let l = Lookup::new(&self.words, &self.chords, &self.options, "word", true, false);
        l.format()
    }

    fn format_plains (&self) -> Format {
        // format_lookups(&self.plains, &self.chords, "plain", false, true)
        let l = Lookup::new(&self.plains, &self.chords, &self.options, "plain", false, true);
        l.format()
    }

    fn format_macros (&self) -> Format {
        // format_lookups(&self.macros, &self.chords, "macro", false, true)
        let l = Lookup::new(&self.macros, &self.chords, &self.options, "macro", false, true);
        l.format()
    }

    fn format_commands (&self) -> Format {
        let command_list: Vec<_> = self.commands.keys()
            .map(|s| s.to_owned())
            .collect();
        let mut f = Format {
            h: make_enum(&command_list, "command_enum"),
            c: String::new(),
        };
        let chord_map = &self.chords;
        // f.append(&format_lookups(&self.commands, chord_map, "command", false, false));
        let l = Lookup::new(&self.commands, chord_map, &self.options, "command", false, false);;
        f.append(&l.format());
        f
    }

    fn format_wordmods(&self) -> Format {
        let mut f = Format::new();
        for name in &self.wordmods {
            let all_chord_bytes: Vec<Vec<i64>> =
                self.options.get_modes().iter()
                .map(|mode|
                     match self.chords[mode].get(name) {
                         Some(c) => c.to_ints(),
                         None => Chord::new().to_ints(),})
                .collect();

            let full_name = format!("{}_chord_bytes", name);
            f.append(&CArray::new(&full_name)
                     .fill_2d(&all_chord_bytes)
                     .format())
        }
        f.append_newline();
        f
    }

    pub fn format_anagrams(&self) -> Format {
        let mut f = Format::new();
        f.append(&self.format_anagram_masks());
        f.append(&self.format_anagram_lookup());
        f
    }

    fn format_anagram_masks(&self) -> Format {
        // TODO consistent naming
        let mut f = Format::new();
        let anagram_masks: Vec<Chord> = self.make_anagram_bit_masks();
        let anagram_bytes: Vec<_> = anagram_masks.iter()
            .map(|c| c.to_ints())
            .collect();

        f.append(&CArray::new("anagram_mask_chord_bytes")
                 .fill_2d(&anagram_bytes)
                 .format());
        f.append_newline();
        f
    }

    fn format_anagram_lookup(&self) -> Format {
        // TODO consistent naming
        let mut f = Format::new();
        let mut anagram_ints: Vec<Vec<Vec<i64>>> = Vec::new();
        for mode in self.options.get_modes() {
            let v: Vec<Vec<i64>> = self.anagrams.iter()
                .map(|name|
                     match self.chords[&mode].get(name){
                         Some(c) => c.clone(),
                         None => Chord::new(),
                         // If this mode doesn't have anagram mods, they'll all be zero.
                         // TODO make sure the firmware doesn't try to use them...
                     })
                .map(|chord|
                     chord.to_ints())
                .collect();
            anagram_ints.push(v);
        }
        f.append(&CArray::new("anagram_chord_bytes")
                 .fill_3d(&anagram_ints)
                 .format());
        f
    }


}


pub fn format_intro(h_file_name: &str) -> Format{
    let autogen_message = make_autogen_message();
    let guard_name = make_guard_name(h_file_name);
    let mut f = Format::new();

    f.h += &autogen_message;
    f.h += &format!("#ifndef {}\n#define {}\n\n", guard_name, guard_name);
    f.h += "#include <Arduino.h>\n";
    f.h += "#include \"keycodes.h\"\n\n";
    f.h += "typedef void (*voidFuncPtr)(void);\n\n";
    f.h += &make_compression_macros();

    f.c += &autogen_message;
    f.c += &format!("#include \"{}\"\n\n", h_file_name);
    f
}

pub fn format_outro() -> Format {
    let mut f = Format::new();
    f.h += make_debug_macros().as_ref();
    f.h += "\n#endif\n";
    f
}

fn make_autogen_message( ) -> String {
    const AUTHOR: &str = "rusty-pipit";

    let s = format!("/**\n * Automatically generated by {} on:  {}\n",
                    AUTHOR,
                    now().strftime("%c").unwrap()
    );
    s + " * Do not make changes here, they will be overwritten.\n */\n\n"
}

fn make_guard_name(h_file_name: &str) -> String {
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
    p + "_"
}

fn make_debug_macros() -> String {
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
    s
}


fn make_enum(variants: &Vec<String>, name: &str) -> String {
    // TODO move somewhere?
    let contents = variants
        .iter()
        .enumerate()
        .fold(String::new(),
              |acc, (index, name)|
              format!("{}  {} = {},\n", acc, name.to_uppercase(), index));

    format!("enum {}{{\n{}}};\n\n", name, contents)
}
