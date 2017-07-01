// A bunch of small, miscellaneous types

use std::fmt::{self};
use std::borrow::Borrow;
use std::ops::{AddAssign};

#[derive(Debug, PartialEq, Eq, Clone)]
pub struct SwitchPos {
    pub row: usize,
    pub col: usize,
}

impl SwitchPos{
    pub fn new(row: i64, col: i64) -> SwitchPos {
        SwitchPos{
            row: row as usize,
            col: col as usize,
        }
    }
}

//////////////////////////////

#[derive(Eq, PartialEq, PartialOrd, Ord, Clone, Copy, Debug)]
pub enum SeqType {
    Plain,
    Macro,
    Command,
    Word,
}

impl fmt::Display for SeqType {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        fmt::Debug::fmt(self, f)
    }
}

//////////////////////////////

#[derive(Clone, Debug)]
pub struct KmapInfo {
    pub path: KmapPath,
    pub use_words: bool,
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub struct ModeName ( pub String );

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub struct Name ( pub String );

impl Name {
    pub fn to_uppercase(&self) -> Name {
        Name(self.0.to_uppercase())
    }
}

impl fmt::Display for Name {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub struct KmapPath ( pub String );

impl fmt::Display for KmapPath {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub struct CCode ( pub String );

impl CCode {
    pub fn new() -> CCode {
        CCode(String::new())
    }

    // pub fn from<T>(x: T) -> CCode
    //     where T: fmt::Display + Clone
    // {
    //     CCode(x.to_string())
    // }

    // pub fn from<T>(x: T) -> CCode
    //     where T: Into<String>
    // {
    //     CCode(x.into())
    // }

    pub fn to_uppercase(&self) -> CCode {
        CCode(self.0.to_uppercase())
    }

    pub fn join(v: Vec<CCode>, separator: &str) -> CCode {
        CCode(v.join(separator))
    }
}

impl<'a> Borrow<str> for CCode {
    fn borrow(&self) -> &str {
        &(self.0)
    }
}

impl fmt::Display for CCode {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl AddAssign<CCode> for CCode {
    fn add_assign(&mut self, rhs: CCode)
    {
        self.0 += &rhs.0;
    }
}

impl<'a> AddAssign<&'a CCode> for CCode {
    fn add_assign(&mut self, rhs: &'a CCode)
    {
        self.0 += &rhs.0;
    }
}



impl AddAssign<String> for CCode {
    fn add_assign(&mut self, rhs: String)
    {
        self.0 += &rhs;
    }
}

impl<'a> AddAssign<&'a str> for CCode {
    fn add_assign(&mut self, rhs: &'a str)
    {
        self.0 += rhs;
    }
}

pub trait ToC {
    fn to_c(&self) -> CCode;
}

impl ToC for String {
    fn to_c(&self) -> CCode {
        CCode(self.clone())
    }
}

impl ToC for str {
    fn to_c(&self) -> CCode {
        CCode(self.to_owned())
    }
}

impl ToC for CCode {
    fn to_c(&self) -> CCode {
        self.clone()
    }
}

impl ToC for Name {
    fn to_c(&self) -> CCode {
        CCode(self.0.to_owned())
    }
}

impl ToC for bool {
    fn to_c(&self) -> CCode {
        let s = if *self {"1"} else {"0"};
        CCode(s.to_owned())
    }
}

impl ToC for i64 {
    fn to_c(&self) -> CCode {
        CCode(self.to_string())
    }
}
