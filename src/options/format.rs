use itertools::Itertools;
use std::path::Path;
use std::io::{Write};
use std::fs::OpenOptions;

use options::options::*;
use sequence::*;
use chord::*;
use c_array::*;

#[derive(Debug)]
pub struct Format {
    pub h: String,   // for header file
    pub c: String,   // for cpp file
}

impl Format {
    pub fn new() -> Format {
        Format {
            h: String::new(),
            c: String::new(),
        }
    }
    pub fn append(&mut self, other: &Format) {
        self.h += &other.h;
        self.c += &other.c;
    }

    pub fn append_newline(&mut self) {
        self.h += "\n";
        self.c += "\n";
    }

    pub fn save(&self, path_base: &str) {
        write_to_file(&format!("{}.h", path_base), &self.h);
        write_to_file(&format!("{}.cpp", path_base), &self.c);
    }


}

fn write_to_file(full_path: &str, s: &str) {
    let path = Path::new(full_path);
    let mut file = OpenOptions::new()
        .create(true)
        .write(true)
        .open(path)
        .expect("failed to open output file");
    file.set_len(0).expect("failed to clear output file");
    file.write_all(s.as_bytes()).expect("failed to write to output file");
}


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


