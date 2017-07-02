use std::fmt::Display;
use std::clone::Clone;
use itertools::Itertools; // TODO unused?

use format::format::Format;
use types::{CCode, ToC};

// TODO fix horrible formatting in structs

enum Contents <T> where T: Display + Clone {
    D1(Vec<T>),
    D2(Vec<Vec<T>>),
}

pub struct CArray <T> where T: Display + Clone
{
    name: Option<CCode>,
    is_extern: bool,
    c_type: CCode,
    contents: Option<Contents<T>>,
}

impl <T> CArray<T> where T: Display + Clone
{
    pub fn new() -> CArray<T>  {
        CArray {
            name: None,
            is_extern: true,
            c_type: "uint8_t".to_c(),
            contents: None,
        }
    }
    pub fn name(mut self, name: &CCode) -> CArray<T>  {
        self.name = Some(name.to_owned());
        self
    }

    pub fn is_extern(mut self, is_extern: bool) -> CArray<T> {
        self.is_extern = is_extern;
        self
    }
    pub fn c_type(mut self, c_type: &CCode) -> CArray<T> {
        self.c_type = c_type.to_owned();
        self
    }
    pub fn fill_1d(mut self, contents: &Vec<T>) -> CArray<T> {
        self.assert_contents_none();
        self.contents = Some(Contents::D1(contents.to_vec()));
        self
    }
    pub fn fill_2d(mut self, contents: &Vec<Vec<T>>) -> CArray<T> {
        self.assert_contents_none();
        self.contents = Some(Contents::D2(contents.to_vec()));
        self
    }

    pub fn format_contents(self) -> CCode {
        // Use this if you only want the contents, like as the initializer for
        //  a struct field
        match self.contents {
            Some(Contents::D1(ref v)) => make_c_array1(&v),
            Some(Contents::D2(ref v)) => make_c_array2(&v),
            None => panic!("CArray was not filled")
        }
    }

    pub fn format(self) -> Format {
        let name = match self.name {
            Some(ref s) => s.to_owned(),
            None => panic!("CArray name must be provided"),
        };

        match self.contents {
            Some(Contents::D1(ref v)) => self.format_c_array1(&v, &name),
            Some(Contents::D2(ref v)) => self.format_c_array2(&v, &name),
            None => panic!("CArray was not filled")
        }
    }


    fn format_c_array1 (&self, v: &Vec<T>, name: &CCode) -> Format
        where T: Display + Clone
    {
        let contents = make_c_array1(&v);
        if self.is_extern {
            Format {
                h: CCode(format!("extern const {} {}[];\n", self.c_type, name)),
                c: CCode(format!("extern const {} {}[] = {};\n\n", self.c_type, name, contents)),
            }
        }
        else {
            Format {
                h: CCode::new(),
                c: CCode(format!("const {} {}[] = {};\n\n", self.c_type, name, contents)),
            }
        }
    }

    fn format_c_array2(&self, v: &Vec<Vec<T>>, name: &CCode) -> Format
        where T: Display
    {
        let contents = make_c_array2(&v);
        let len_2nd_dim = v[0].len();

        if self.is_extern {
            Format {
                h: CCode(format!("extern const {} {}[][{}];\n",
                                 self.c_type, name, len_2nd_dim)),
                c: CCode(format!("extern const {} {}[][{}] = {};\n\n",
                                 self.c_type, name, len_2nd_dim, contents)),
            }
        }
        else {
            Format {
                h: CCode::new(),
                c: CCode(format!("const {} {}[][{}] = {};\n\n",
                                 self.c_type, name, len_2nd_dim, contents)),
            }
        }
    }

    fn assert_contents_none(&self) {
        if let Some(_) = self.contents {
            panic!("CArray cannot be filled more than once");
        }
    }

}

// TODO refactor to recursively make arrays of arbitrary dimensions?
// Or at least re-use more code, and improve formatting

fn make_c_array1<T>(v: &Vec<T>) -> CCode
    where T: Display
{
    let lines = wrap_in_braces(&to_code_vec(v));
    // println!("{:?}", lines);
    CCode(lines.join("\n"))
}

fn make_c_array2<T>(v: &Vec<Vec<T>>) -> CCode
    where T: Display
{
    // TODO format better, don't put commas on separate line
    assert!(is_rectangular(v));

    let mut rows: Vec<CCode> = Vec::new();
    for row in v {
        rows.extend(wrap_in_braces(&to_code_vec(&row)));
        rows.push(",".to_c());
    }
    CCode::join(wrap_in_braces(&rows), "\n")
}


fn wrap_in_braces(lines: &Vec<CCode>) -> Vec<CCode> {
    let mut new: Vec<_> = lines.iter()
        .map(|s| CCode(format!(" {}", s)))
        .collect();
    new.insert(0, "{".to_c());
    new.push("}".to_c());
    new
}

fn to_code_vec<T>(v: &Vec<T>) -> Vec<CCode>
    where T: Display
{
    let items_per_line = 4;
    let mut lines: Vec<String> = Vec::new();
    let chunks = &v.iter().map(|x| x.to_string()).chunks(items_per_line);
    for chunk in chunks {
        let tmp: Vec<_> = chunk.collect();
        lines.push(tmp.join(", ") + ", ");
    }
    let code_lines: Vec<_> = lines.into_iter()
        .map(|line| CCode(line))
        .collect();
    code_lines
}

fn is_rectangular<T>(v: &Vec<Vec<T>>) -> bool
    where T: Display
{
    let len_2nd_dim = v[0].len();
    v.iter()
        .map(|v| v.len())
        .all(|x| x == len_2nd_dim)
}

