use types::{Chord, Sequence, KeyPress, SwitchPos};
use options::options::*;
use format::{Format, CArray, format_lookups, compress};

use maps::*;


impl KeyPress{
    pub fn as_bytes(&self, use_mods: bool) -> Vec<String> {
        let mut v: Vec<String> = Vec::new();
        v.push(format!("{}&0xff", self.key));
        if use_mods{
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
        f
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
                self.format_ifdef_value(name)
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

    fn format_ifdef_value(&self, name: &str) -> Format {
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


impl Maps{

    pub fn format_words (&self) -> Format {
        let chord_map = &self.chords;
        format_lookups(&self.words, chord_map, "word", true, false)
    }

    pub fn format_plains (&self) -> Format {
        let chord_map = &self.chords;
        format_lookups(&self.plains, chord_map, "plain", false, true)
    }

    pub fn format_macros (&self) -> Format {
        let chord_map = &self.chords;
        format_lookups(&self.macros, chord_map, "macro", false, true)
    }

    pub fn format_specials (&self) -> Format {
        let mut f = Format {
            h: self.specials.keys()
                .fold(String::new(),
                      |acc, name|
                      acc + &format!("#define {} {}\n",
                                     name,
                                     self.specials[name].get_only_value()))
                + "\n",
            c: String::new(),
        };
        let chord_map = &self.chords;
        f.append(&format_lookups(&self.specials, chord_map, "special", false, false));
        f
    }

    pub fn format_wordmods(&self) -> Format {
        let mut f = Format::new();
        for name in &self.wordmods {
            let full_name = format!("{}_chord_bytes", name);
            f.append(&CArray::new(&full_name)
                     .fill_1d(&self.chords[name].to_ints())
                     .format())
        }
        f
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
