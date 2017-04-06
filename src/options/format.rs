use options::options::*;
use compression::*;
use sequence::*;
use chord::*;
use c_array::*;
use itertools::Itertools;

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
            _ => panic!("option type cannot be formatted"),
        }
    }

    fn format_define_int(&self, name: &str) -> Format {
        Format {
            h: format!("#define {} {}",
                       name.to_uppercase(),
                       self.get_val().unwrap_int()),
            c: String::new(),
        }
    }

    fn format_define_string(&self, name: &str) -> Format {
        Format {
            h: format!("#define {} {}",
                        name.to_uppercase(),
                        self.get_val().unwrap_str()),
            c: String::new(),
        }
    }

    fn format_ifdef_value(&self, name: &str) -> Format {
        Format {
            h: format!("#define {}",
                       self.get_val().unwrap_str()),
            c: String::new(),
        }
    }

    fn format_ifdef_key(&self, name: &str) -> Format {
        Format {
            h: if self.get_val().unwrap_bool() {
                format!("#define {}",
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
                       name.to_uppercase()),

            c: format!("extern const uint8_t {} = {};\n\n",
                       name.to_uppercase(),
                       self.get_val().unwrap_int()),
        }
    }

    fn format_array1d(&self, name: &str) -> Format {
        // format_c_array(
        //     name,
        //     self.get_val().unwrap_vec(),
        //     "uint8_t")
        CArray::new(name)
            .fill_1d(self.get_val().unwrap_vec())
            .format()
    }


    fn format_array2d(&self, name: &str) -> Format {
        // format_c_array2(
        //     name,
        //     self.get_val().unwrap_vec2(),
        //     "uint8_t"
        // )
            CArray::new(name)
            .fill_2d(self.get_val().unwrap_vec2())
            .format()
    }

}


