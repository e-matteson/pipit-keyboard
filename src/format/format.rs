use std::path::Path;
use std::io::{Write};
use std::fs::OpenOptions;


#[derive(Debug)]
pub struct Format {
    pub h: String,   // for header file
    pub c: String,   // for cpp file
}

// TODO rename to a noun
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


