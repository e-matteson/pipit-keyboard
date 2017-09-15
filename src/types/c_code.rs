use std::fmt;
use std::borrow::Borrow;
use std::ops::AddAssign;

use types::{ModeName, Name, SeqType};

//////////////////////////////

#[derive(Clone, Debug, Default, Eq, PartialEq, Ord, PartialOrd, Deserialize)]
pub struct CCode(pub String);

impl CCode {
    pub fn new() -> CCode {
        CCode(String::new())
    }

    pub fn to_uppercase(&self) -> CCode {
        CCode(self.0.to_uppercase())
    }

    pub fn join(v: &[CCode], separator: &str) -> CCode {
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
    fn add_assign(&mut self, rhs: CCode) {
        self.0 += &rhs.0;
    }
}

impl<'a> AddAssign<&'a CCode> for CCode {
    fn add_assign(&mut self, rhs: &'a CCode) {
        self.0 += &rhs.0;
    }
}

impl AddAssign<String> for CCode {
    fn add_assign(&mut self, rhs: String) {
        self.0 += &rhs;
    }
}

impl<'a> AddAssign<&'a str> for CCode {
    fn add_assign(&mut self, rhs: &'a str) {
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

impl ToC for ModeName {
    fn to_c(&self) -> CCode {
        CCode(self.0.to_owned())
    }
}

impl ToC for SeqType {
    fn to_c(&self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for bool {
    fn to_c(&self) -> CCode {
        let s = if *self { "1" } else { "0" };
        CCode(s.to_owned())
    }
}

impl ToC for i32 {
    fn to_c(&self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for u8 {
    fn to_c(&self) -> CCode {
        CCode(self.to_string())
    }
}

impl ToC for usize {
    fn to_c(&self) -> CCode {
        CCode(self.to_string())
    }
}
