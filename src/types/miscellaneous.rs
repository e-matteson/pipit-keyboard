// A bunch of small, miscellaneous types

use std::fmt;
use std::slice::Iter;
// use std::collections::BTreeMap;

use types::{KeyPress, CCode};

#[derive(Debug, Clone)]
pub enum OpNew {
    DefineInt ( CCode, usize ),
    DefineString ( CCode, CCode ),
    Ifdef (CCode, bool),
    Uint8 (CCode, u8),
    Array1D (CCode, Vec<u8>),
    // Array2D (Vec<Vec<u8>>),
    // Mode { use_words: bool },
}


#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
pub struct SwitchPos {
    pub row: u8,
    pub col: u8,
}

impl SwitchPos {
    pub fn new(row: u8, col: u8) -> SwitchPos {
        SwitchPos {
            // row: row as usize,
            // col: col as usize,
            row: row,
            col: col,
        }
    }
}

impl fmt::Display for SwitchPos {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[{},{}]", self.row, self.col)
    }
}

//////////////////////////////

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
pub struct KmapFormat (pub Vec<Vec<SwitchPos>>);

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
        let s = match *self {
            SeqType::Plain => "plain",
            SeqType::Macro => "macro",
            SeqType::Command => "command",
            SeqType::Word => "word",
        };
        fmt::Display::fmt(s, f)
    }
}

//////////////////////////////

#[derive(Clone, Debug, Deserialize)]
pub struct KmapInfo {
    pub file: KmapPath,

    #[serde(default = "return_false")]
    pub use_words: bool,
}

fn return_false() -> bool {
    false
}

//////////////////////////////

#[derive(Clone, Debug, Deserialize)]
pub struct ModeInfo {
    pub keymaps: Vec<KmapInfo>,

    #[serde(default = "return_false")]
    pub gaming: bool,
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize)]
pub struct KmapPath(pub String);

impl fmt::Display for KmapPath {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize)]
#[serde(from = "String")]
pub struct ModeName(pub String);

impl fmt::Display for ModeName {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl <'a> From<&'a str> for ModeName {
    fn from(s: &str) -> ModeName {
        ModeName(s.to_owned())
    }
}

impl From<String> for ModeName {
    fn from(s: String) -> ModeName {
        ModeName(s)
    }
}


//////////////////////////////

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize)]
#[serde(from = "String")]
pub struct Name(pub String);

// TODO: sanitize name?
impl Name {
    pub fn to_uppercase(&self) -> Name {
        // TODO remove?
        Name(self.0.to_uppercase())
    }
}

impl From<String> for Name {
    fn from(s: String) -> Name {
        Name(s)
    }
}

impl <'a> From<&'a str> for Name {
    fn from(s: &str) -> Name {
        Name(s.to_owned())
    }
}

impl fmt::Display for Name {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl fmt::Debug for Name {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}


//////////////////////////////

#[derive(Debug, Clone, Deserialize)]
// #[serde(from = "KeyPress")]
pub struct Sequence(pub Vec<KeyPress>);

impl Sequence {
    pub fn new() -> Sequence {
        Sequence(Vec::new())
    }

    pub fn extend(&mut self, other: Sequence) {
        self.0.extend(other.0)
    }

    pub fn push(&mut self, keypress: KeyPress) {
        self.0.push(keypress)
    }

    pub fn len(&self) -> usize {
        self.0.len()
    }

    pub fn keypresses(&self) -> Iter<KeyPress> {
        self.0.iter()
    }
}

impl From<KeyPress> for Sequence {
    fn from(single: KeyPress) -> Self {
        let mut s = Sequence::new();
        s.push(single);
        s
    }
}

// impl From<BTreeMap<Name, KeyPress>> for BTreeMap<Name, Sequence> {
//     fn from(kp_map: BTreeMap<Name, KeyPress>) -> Self {
//         kp_map.iter()
//             .map(|(name, keypress)|
//                  (name.to_owned(), Sequence::from(keypress.to_owned())))
//             .collect()
//     }
// }
