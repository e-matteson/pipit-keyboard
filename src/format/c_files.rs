use std::io::Write;
use std::fs::OpenOptions;
use std::ops::AddAssign;
use std::path::PathBuf;

use types::CCode;
use types::errors::*;


#[derive(Debug, Default)]
pub struct CFiles {
    pub h: CCode, // for header file
    pub c: CCode, // for cpp file
}

// TODO rename to a noun!
impl CFiles {
    pub fn new() -> CFiles {
        CFiles {
            h: CCode::new(),
            c: CCode::new(),
        }
    }

    pub fn append(&mut self, other: &CFiles) {
        self.h += &other.h;
        self.c += &other.c;
    }

    pub fn append_newline(&mut self) {
        self.h += "\n";
        self.c += "\n";
    }

    pub fn save(&self, directory: &PathBuf, name_base: &str) -> Result<()> {
        let mut base = directory.to_owned();
        base.push(name_base);

        let mut h_path = base.clone();
        h_path.set_extension("h");

        let mut cpp_path = base;
        cpp_path.set_extension("cpp");

        write_to_file(h_path, &self.h)?;
        write_to_file(cpp_path, &self.c)?;
        Ok(())
    }
}

impl AddAssign<CFiles> for CFiles {
    fn add_assign(&mut self, rhs: CFiles) {
        self.append(&rhs)
    }
}

impl<'a> AddAssign<&'a CFiles> for CFiles {
    fn add_assign(&mut self, rhs: &'a CFiles) {
        self.append(rhs)
    }
}


fn write_to_file(full_path: PathBuf, s: &CCode) -> Result<()> {
    // let path = Path::new(full_path);
    let mut file = OpenOptions::new()
        .create(true)
        .write(true)
        .open(full_path)
        .chain_err(|| "failure to open output file")?;
    file.set_len(0).chain_err(|| "failure to clear output file")?;
    file.write_all(s.to_string().as_bytes())
        .chain_err(|| "failure to write to output file")?;
    Ok(())
}
