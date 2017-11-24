// A bunch of small, miscellaneous types

use std::fmt;
use std::slice::Iter;
// use std::collections::BTreeMap;

use types::{CCode, KeyPress, Validate};
use types::errors::*;

#[derive(Debug, Clone)]
pub enum COption {
    DefineInt(CCode, usize),
    DefineString(CCode, CCode),
    Ifdef(CCode, bool),
    Uint8(CCode, u8),
    Array1D(CCode, Vec<usize>),
    // Array2D (Vec<Vec<u8>>),
    // Mode { use_words: bool },
}

#[derive(Debug, PartialEq, Eq, Clone, Copy, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Pin(pub u8);

impl Pin {
    pub fn to_usize(pin_vec: &Vec<Pin>) -> Vec<usize> {
        pin_vec.iter().map(|pin| usize::from(*pin)).collect()
    }
}

impl Validate for Pin {
    fn validate(&self) -> Result<()> {
        const MAX_PIN_NUM: u8 = 30; // TODO pick value
        if self.0 > MAX_PIN_NUM {
            bail!("invalid pin number: {}", self.0);
        }
        Ok(())
    }
}

impl From<Pin> for usize {
    fn from(pin: Pin) -> usize {
        pin.0 as usize
    }
}

impl From<Pin> for u8 {
    fn from(pin: Pin) -> u8 {
        pin.0
    }
}

// impl <T> From<Vec<T>> for Vec<usize>
// where T: From<Pin> for usize {
//     fn from(pin: Pin) -> usize {
//         pin.0 as usize
//     }
// }

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct SwitchPos {
    pub row: Pin,
    pub col: Pin,
}

impl SwitchPos {
    pub fn new(row: Pin, col: Pin) -> SwitchPos {
        SwitchPos {
            // row: row as usize,
            // col: col as usize,
            row: row,
            col: col,
        }
    }
}

impl Validate for SwitchPos {
    fn validate(&self) -> Result<()> {
        self.row.validate()?;
        self.col.validate()?;
        Ok(())
    }
}

impl fmt::Display for SwitchPos {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "[{:?},{:?}]", self.row, self.col)
    }
}

//////////////////////////////

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapFormat(pub Vec<Vec<SwitchPos>>);

impl Validate for KmapFormat {
    fn validate(&self) -> Result<()> {
        for row in self.0.iter() {
            for pair in row.iter() {
                pair.validate()?;
            }
        }
        Ok(())
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
#[serde(deny_unknown_fields)]
pub struct KmapInfo {
    pub file: KmapPath,

    #[serde(default = "return_false")] pub use_words: bool,
}

impl Validate for KmapInfo {
    fn validate(&self) -> Result<()> {
        self.file.validate()
    }
}

fn return_false() -> bool {
    false
}

//////////////////////////////

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ModeInfo {
    pub keymaps: Vec<KmapInfo>,

    #[serde(default = "return_false")] pub gaming: bool,
}

impl Validate for ModeInfo {
    fn validate(&self) -> Result<()> {
        for kmap in &self.keymaps {
            kmap.validate()?;
        }
        Ok(())
    }
}



//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapPath(pub String);

impl Validate for KmapPath {
    fn validate(&self) -> Result<()> {
        // TODO check if path exists and has .kmap extension?
        Ok(())
    }
}

impl fmt::Display for KmapPath {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize,
         Serialize)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
pub struct ModeName(pub String);

impl Validate for ModeName {
    fn validate(&self) -> Result<()> {
        // TODO check if contains chars other than a-zA-Z_
        Ok(())
    }
}

impl Default for ModeName {
    fn default() -> Self {
        ModeName("default_mode".into())
    }
}


impl fmt::Display for ModeName {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl<'a> From<&'a str> for ModeName {
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

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Serialize)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
// #[serde(finalize = "Name::sanitize")]
pub struct Name(pub String);

// TODO: sanitize name?
impl Name {
    pub fn to_uppercase(&self) -> Name {
        // TODO remove?
        Name(self.0.to_uppercase())
    }
}

impl Validate for Name {
    fn validate(&self) -> Result<()> {
        // TODO anything to check? Not used c_code...
        Ok(())
    }
}

impl From<String> for Name {
    fn from(s: String) -> Name {
        Name(s)
    }
}

impl<'a> From<&'a str> for Name {
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
#[serde(deny_unknown_fields)]
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

impl Validate for Sequence {
    fn validate(&self) -> Result<()> {
        for keypress in &self.0 {
            keypress.validate()?;
        }
        Ok(())
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
