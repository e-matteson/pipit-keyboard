// A bunch of small, miscellaneous types

use std::fmt::{self};
use std::borrow::Borrow;
use std::ops::{AddAssign};
use std::slice::Iter;


#[derive(Debug, PartialEq, Eq, Clone)]
pub struct SwitchPos {
    pub row: usize,
    pub col: usize,
}

impl SwitchPos{
    pub fn new(row: u8, col: u8) -> SwitchPos {
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
        let s = match self {
            &SeqType::Plain => "plain",
            &SeqType::Macro => "macro",
            &SeqType::Command => "command",
            &SeqType::Word => "word",
        };
        fmt::Display::fmt(s, f)
    }
}

//////////////////////////////

#[derive(Clone, Debug)]
pub struct KmapInfo {
    pub path: KmapPath,
    pub use_words: bool,
}

//////////////////////////////

#[derive(Clone, Debug)]
pub struct ModeInfo {
    pub keymaps: Vec<KmapInfo>,
    pub is_gaming: bool,
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
pub struct KmapPath ( pub String );

impl fmt::Display for KmapPath {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
pub struct ModeName ( pub String );

impl fmt::Display for ModeName {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd)]
pub struct Name ( pub String );

impl Name {
    pub fn from(s: &str) -> Name {
        Name(s.to_owned())
    }

    pub fn to_uppercase(&self) -> Name {
        Name(self.0.to_uppercase())
    }
}

impl fmt::Display for Name {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl fmt::Debug for Name{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

// TODO KeyPress is also used to store command codes, which is kinda a hack. Rename?

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Clone)]
pub struct KeyPress{
    pub key: CCode,
    pub modifier: CCode,
}

impl KeyPress{
    pub fn new(key: Option<String>, modifier: Option<String>) -> KeyPress {
        KeyPress{
            key: KeyPress::sanitize(key),
            modifier: KeyPress::sanitize(modifier),
        }
    }
    pub fn new_fake(code: &Name) -> KeyPress {
        // We also use KeyPresses to store command codes
        KeyPress{
            key: code.to_c(),
            modifier: "0".to_c(),
        }
    }
    pub fn new_blank() -> KeyPress {
        KeyPress{
            key: "0".to_c(),
            modifier: "0".to_c(),
        }
    }
    pub fn is_mod_blank(&self) -> bool {
        self.modifier == "0".to_c()
    }

    fn contains_illegal_char(string: &str) -> bool {
        // It's not quite worth using the regex crate for this...
        let legal = vec!['_', '|', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                         'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                         'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4',
                         '5', '6', '7', '8', '9' ];
        for c in string.chars(){
            if !legal.contains(&c) {
                return true;
            }
        }
        false
    }

    fn sanitize(string: Option<String>) -> CCode {
        // TODO compare to an actual list of defined key codes?
        //  Could vary with underlying keyboard lib, though
        match string {
            None =>
                "0".to_c(),
            Some(s) => {
                if KeyPress::contains_illegal_char(&s) {
                    panic!(format!("Keypress value is probably not valid: {}", s));
                }
                s.to_c()            }
        }
    }
}


//////////////////////////////

#[derive(Debug)]
#[derive(Clone)]
pub struct Sequence (
    pub Vec<KeyPress>
);

impl Sequence {
    pub fn new() -> Sequence {
        Sequence(Vec::new())
    }

    pub fn extend (&mut self, other: Sequence) {
        self.0.extend(other.0)
    }

    pub fn push (&mut self, keypress: KeyPress) {
        self.0.push(keypress)
    }

    pub fn len (&self) -> usize {
        self.0.len()
    }

    pub fn keypresses(&self) -> Iter<KeyPress> {
        self.0.iter()
    }
}


//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub struct CCode ( pub String );

impl CCode {
    pub fn new() -> CCode {
        CCode(String::new())
    }

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
        let s = if *self {"1"} else {"0"};
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
