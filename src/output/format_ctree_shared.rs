use std::fs::{create_dir_all, OpenOptions};
use std::io::Write;
use std::ops::AddAssign;
use std::path::PathBuf;

use error::{Error, ResultExt};
use types::{AnagramNum, CLiteral, CTree, Delay, Pin};

#[derive(Debug, Default)]
pub struct COut(pub String);

impl COut {
    pub fn new() -> COut {
        COut(String::new())
    }

    pub fn save(
        &self,
        directory: &PathBuf,
        name_base: &str,
        extension: &str,
    ) -> Result<PathBuf, Error> {
        create_dir_all(directory)?;
        let mut path = directory.to_owned();
        path.push(name_base);
        path.set_extension(extension);
        write_to_file(path.clone(), &self.0)?;
        Ok(path)
    }
}

pub fn write_to_file(full_path: PathBuf, s: &str) -> Result<(), Error> {
    let mut file = OpenOptions::new()
        .create(true)
        .write(true)
        .open(full_path)
        .context("Failed to open output file")?;

    file.set_len(0).context("Failed to clear output file")?;

    file.write_all(s.as_bytes())
        .context("Failed to write to output file")?;
    Ok(())
}

impl AddAssign<COut> for COut {
    fn add_assign(&mut self, rhs: COut) {
        self.0 += &rhs.0;
    }
}

impl AddAssign<String> for COut {
    fn add_assign(&mut self, rhs: String) {
        self.0 += &rhs;
    }
}

impl<'a> AddAssign<&'a COut> for COut {
    fn add_assign(&mut self, rhs: &'a COut) {
        self.0 += &rhs.0;
    }
}

impl Into<CTree> for AnagramNum {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for Delay {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.0.to_string()))
    }
}

impl Into<CTree> for Pin {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.0.to_string()))
    }
}

impl Into<CTree> for u8 {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for u16 {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for usize {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}

impl Into<CTree> for bool {
    fn into(self) -> CTree {
        CTree::Literal(CLiteral(self.to_string()))
    }
}
