use std::path::Path;
use std::io::Write;
use std::fs::OpenOptions;
use std::ops::AddAssign;

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

    pub fn save(&self, directory: &str, name_base: &str) -> Result<()> {
        write_to_file(&format!("{}/{}.h", directory, name_base), &self.h)?;
        write_to_file(&format!("{}/{}.cpp", directory, name_base), &self.c)?;
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



fn write_to_file(full_path: &str, s: &CCode) -> Result<()> {
    let path = Path::new(full_path);
    let mut file = OpenOptions::new()
        .create(true)
        .write(true)
        .open(path)
        .chain_err(|| "failure to open output file")?;
    file.set_len(0).chain_err(|| "failure to clear output file")?;
    file.write_all(s.to_string().as_bytes())
        .chain_err(|| "failure to write to output file")?;
    Ok(())
}
