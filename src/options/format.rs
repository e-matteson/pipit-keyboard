use options::options::*;
use itertools::Itertools;

#[derive(Debug)]
pub struct Format {
    h: String,   // for header file
    c: String,   // for cpp file
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
        format_c_array(
            name,
            self.get_val().unwrap_vec(),
            "uint8_t")
    }


    fn format_array2d(&self, name: &str) -> Format {
        format_c_array2(
            name,
            self.get_val().unwrap_vec2(),
            "uint8_t"
        )
    }

}


pub fn format_c_array(name: &str, v: &Vec<i64>, ctype: &str) -> Format {
    let contents = make_c_array(&v);
    Format {
        h: format!("extern const {} {}[];\n", ctype, name),
        c: format!("extern const {} {}[] = {};\n\n", ctype, name, contents),
    }
}

pub fn format_c_array2(name: &str, v: &Vec<Vec<i64>>, ctype: &str) -> Format {
    let contents = make_c_array2(&v);
    let len_2nd_dim = v[0].len();
    Format {
        h: format!("extern const {} {}[][{}];\n",
                   ctype, name, len_2nd_dim),
        c: format!("extern const {} {}[][{}] = {};\n\n",
                   ctype, name, len_2nd_dim, contents),
    }
}

pub fn make_c_array(v: &Vec<i64>) -> String {
    let lines = wrap_in_braces(&to_string_vec(v));
    // println!("{:?}", lines);
    lines.join("\n")
}

fn is_rectangular(v: &Vec<Vec<i64>>) -> bool {
    let len_2nd_dim = v[0].len();
    v.iter()
        .map(|v| v.len())
        .all(|x| x == len_2nd_dim)
}

pub fn make_c_array2(v: &Vec<Vec<i64>>) -> String {
    // TODO assert rectangular
    assert!(is_rectangular(v));

    let mut rows: Vec<String> = Vec::new();
    for row in v {
        rows.extend(wrap_in_braces(&to_string_vec(&row)));
    }
    println!("{:?}", rows);
    wrap_in_braces(&rows).join("\n")
}

fn wrap_in_braces(lines: &Vec<String>) -> Vec<String> {
    let mut new: Vec<_> = lines.iter().map(|s| format!(" {}", s)).collect();
    new.insert(0, "{".to_owned());
    new.push("}".to_owned());
    new
}

pub fn to_string_vec(v: &Vec<i64>) -> Vec<String> {
    let mut lines: Vec<String> = Vec::new();
    let chunks = &v.iter().map(|x| x.to_string()).chunks(5);
    for chunk in chunks {
        let tmp: Vec<_> = chunk.collect();
        lines.push(tmp.join(", ") + ", ");
    }
    lines
}

