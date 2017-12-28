use std::io::Write;
use std::fs::OpenOptions;
use std::ops::AddAssign;
use std::path::PathBuf;

use types::{CCode, ToC};
use types::errors::*;

// TODO move to c_code.rs

#[derive(Debug, Default)]
pub struct CFiles {
    pub h: CCode, // for header file
    pub c: CCode, // for cpp file
}

////////////////////////////////////////////////////////////////////////////////

impl CFiles {
    pub fn new() -> CFiles {
        CFiles {
            h: CCode::new(),
            c: CCode::new(),
        }
    }

    pub fn with_c<T>(contents: T) -> CFiles
    where
        T: ToC,
    {
        CFiles {
            h: CCode::new(),
            c: contents.to_c(),
        }
    }

    pub fn with_h<T>(contents: T) -> CFiles
    where
        T: ToC,
    {
        CFiles {
            h: contents.to_c(),
            c: CCode::new(),
        }
    }

    pub fn with<T>(contents: T) -> CFiles
    where
        T: ToC,
    {
        let contents = contents.to_c();
        CFiles {
            h: contents.clone(),
            c: contents,
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

    // pub fn join(v: &[CFiles]) -> CFiles {
    //     v.iter().fold(CFiles::new(), |acc, f| acc + f)
    // }
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

// impl Add<CFiles> for CFiles {
//     type Output = P2;
//     fn add(self, rhs: V2) -> P2 {
//         P2::new(self.x + rhs.x, self.y + rhs.y)
//     }
// }

pub fn write_to_file(full_path: PathBuf, s: &CCode) -> Result<()> {
    // let path = Path::new(full_path);
    let mut file = OpenOptions::new()
        .create(true)
        .write(true)
        .open(full_path)
        .chain_err(|| "failure to open output file")?;
    file.set_len(0)
        .chain_err(|| "failure to clear output file")?;
    file.write_all(s.to_string().as_bytes())
        .chain_err(|| "failure to write to output file")?;
    Ok(())
}
