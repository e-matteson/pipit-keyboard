use std::fmt::Display;
use std::clone::Clone;
use itertools::Itertools;

use format::c_files::CFiles;
use types::{CCode, ToC};

// TODO fix horrible 2d array formatting

pub struct CArray<T>
where
    T: Display + Clone,
{
    name: CCode,
    is_extern: bool,
    c_type: CCode,
    contents: Vec<T>,
}

impl<T> CArray<T>
where
    T: Display + Clone,
{
    pub fn new<U>(name: U, contents: &Vec<T>) -> CArray<T>
    where
        U: ToC,
    {
        CArray {
            name: name.to_c(),
            is_extern: true,
            c_type: "uint8_t".to_c(),
            contents: contents.to_owned(),
        }
    }

    pub fn c_extern(mut self, is_extern: bool) -> CArray<T> {
        self.is_extern = is_extern;
        self
    }
    pub fn c_type<U>(mut self, c_type: U) -> CArray<T>
    where
        U: ToC,
    {
        self.c_type = c_type.to_c();
        self
    }

    pub fn format(self) -> CFiles {
        let values = make_c_array(&self.contents);
        if self.is_extern {
            CFiles {
                h: CCode(
                    format!("extern const {} {}[];\n", self.c_type, self.name),
                ),
                c: CCode(format!(
                    "extern const {} {}[] = {};\n\n",
                    self.c_type,
                    self.name,
                    values
                )),
            }
        } else {
            CFiles {
                h: CCode::new(),
                c: CCode(format!(
                    "const {} {}[] = {};\n\n",
                    self.c_type,
                    self.name,
                    values
                )),
            }
        }
    }
}

// TODO refactor to recursively make arrays of arbitrary dimensions?
// Or at least re-use more code, and improve formatting

fn make_c_array<T>(v: &[T]) -> CCode
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
    let items_per_line = 4;
    let mut lines: Vec<String> = Vec::new();
    let chunks = &v.iter().map(|x| x.to_string()).chunks(items_per_line);
    for chunk in chunks {
        let tmp: Vec<_> = chunk.collect();
        lines.push(tmp.join(", ") + ", ");
    }
    let code_lines: Vec<_> = lines.into_iter().map(CCode).collect();
    code_lines
}
