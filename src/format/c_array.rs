use std::fmt::Display;
use std::clone::Clone;
use itertools::Itertools; // TODO unused?

use format::format::Format;
use types::{CCode, ToC};


pub struct CArray <T> where T: Display + Clone
{
    name: CCode,
    is_extern: bool,
    c_type: CCode,
    contents_1d: Option<Vec<T>>,
    contents_2d: Option<Vec<Vec<T>>>,
    contents_3d: Option<Vec<Vec<Vec<T>>>>,
}

impl <T> CArray<T> where T: Display + Clone
{
    pub fn new(name: &CCode) -> CArray<T>  {
        CArray {
            name: name.to_owned(),
            is_extern: true,
            c_type: "uint8_t".to_c(),
            contents_1d: None,
            contents_2d: None,
            contents_3d: None,
        }
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
        self.contents_1d = Some(contents.to_vec());
        assert!(self.contents_2d.is_none() && self.contents_3d.is_none());
        self
    }
    pub fn fill_2d(mut self, contents: &Vec<Vec<T>>) -> CArray<T> {
        self.contents_2d = Some(contents.to_vec());
        assert!(self.contents_1d.is_none() && self.contents_3d.is_none());
        self
    }
    // pub fn fill_3d(mut self, contents: &Vec<Vec<Vec<T>>>) -> CArray<T> {
    //     self.contents_3d = Some(contents.to_vec());
    //     assert!(self.contents_1d.is_none() && self.contents_2d.is_none());
    //     self
    // }
    pub fn format(self) -> Format {
        if let Some(contents) = self.contents_1d {
            return format_c_array(&self.name, &contents, &self.c_type, self.is_extern);
        }
        else if let Some(contents) = self.contents_2d {
            return format_c_array2(&self.name, &contents, &self.c_type, self.is_extern);
        }
        else if let Some(contents) = self.contents_3d {
           return format_c_array3(&self.name, &contents, &self.c_type, self.is_extern);
        }
        else {
            panic!("CArray: no array contents were given");
        }
    }
}


fn format_c_array<T>(name: &CCode, v: &Vec<T>, ctype: &CCode, is_extern: bool) -> Format
    where T: Display + Clone
{
    let contents = make_c_array(&v);
    if is_extern {
        Format {
            h: CCode(format!("extern const {} {}[];\n", ctype, name)),
            c: CCode(format!("extern const {} {}[] = {};\n\n", ctype, name, contents)),
        }
    }
    else {
        Format {
            h: CCode::new(),
            c: CCode(format!("const {} {}[] = {};\n\n", ctype, name, contents)),
        }
    }
}

fn format_c_array2<T>(name: &CCode, v: &Vec<Vec<T>>, ctype: &CCode, is_extern: bool) -> Format
    where T: Display
{
    let contents = make_c_array2(&v);
    let len_2nd_dim = v[0].len();

    if is_extern {
        Format {
            h: CCode(format!("extern const {} {}[][{}];\n",
                       ctype, name, len_2nd_dim)),
            c: CCode(format!("extern const {} {}[][{}] = {};\n\n",
                       ctype, name, len_2nd_dim, contents)),
        }
    }
    else {
        Format {
            h: CCode::new(),
            c: CCode(format!("const {} {}[][{}] = {};\n\n",
                       ctype, name, len_2nd_dim, contents)),
        }
    }
}


fn format_c_array3<T>(name: &CCode, v: &Vec<Vec<Vec<T>>>, ctype: &CCode, is_extern: bool) -> Format
    where T: Display
{
    let contents = make_c_array3(&v);
    let len_2nd_dim = v[0].len();
    let len_3rd_dim = v[0][0].len();

    // TODO combine extern cases better
    if is_extern {
        Format {
            h: CCode(format!("extern const {} {}[][{}][{}];\n",
                       ctype, name, len_2nd_dim, len_3rd_dim)),
            c: CCode(format!("extern const {} {}[][{}][{}] = {};\n\n",
                       ctype, name, len_2nd_dim, len_3rd_dim, contents)),
        }
    }
    else {
        Format {
            h: CCode::new(),
            c: CCode(format!("const {} {}[][{}][{}] = {};\n\n",
                       ctype, name, len_2nd_dim, len_3rd_dim, contents)),
        }
    }
}

// TODO refactor to recursively make arrays of arbitrary dimensions?
// Or at least re-use more code, and improve formatting

fn make_c_array<T>(v: &Vec<T>) -> CCode
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

fn make_c_array3<T>(v: &Vec<Vec<Vec<T>>>) -> CCode
    where T: Display
{
    // TODO format better, don't put commas on separate line!!!!
    assert!(is_cubic(v));

    let mut subarrays: Vec<CCode> = Vec::new();
    for subarray in v {
        // subarrays.extend(wrap_in_braces(&to_code_vec(&subarray)));
        // subarrays.extend(wrap_in_braces(subarray));
        subarrays.push(make_c_array2(subarray));
        subarrays.push(",".to_c());
    }
    CCode::join(wrap_in_braces(&subarrays), ("\n"))
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

fn is_cubic<T>(v: &Vec<Vec<Vec<T>>>) -> bool
    where T: Display
{
    v.iter()
        .fold(true,
              |acc, x| acc && is_rectangular(x))
}
