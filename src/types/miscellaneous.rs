// A bunch of small, miscellaneous types that don't deserve their own files

use std::iter;
use std::fmt::{self, Debug};
use std::slice::Iter;
use std::string::ToString;

use types::{CCode, KeyPress, ToC, Validate};
use types::errors::*;

#[derive(Debug, PartialEq, Eq, Clone, Copy, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Pin(pub u8);

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct SwitchPos {
    pub row: Pin,
    pub col: Pin,
}

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapFormat(pub Vec<Vec<SwitchPos>>);

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapInfo {
    pub file: KmapPath,
    #[serde(default = "return_false")] pub use_words: bool,
}

#[derive(Eq, PartialEq, PartialOrd, Ord, Clone, Copy, Debug)]
pub enum SeqType {
    Plain,
    Macro,
    Command,
    Word,
}

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ModeInfo {
    pub keymaps: Vec<KmapInfo>,
    #[serde(default = "return_false")] pub gaming: bool,
}

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapPath(pub String);

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize,
         Serialize)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
pub struct ModeName(pub String);

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Serialize)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
// #[serde(finalize = "Name::sanitize")]
pub struct Name(pub String);

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Sequence(pub Vec<KeyPress>);

#[derive(Debug, Clone)]
pub struct Permutation {
    order: Vec<Option<usize>>,
    old_length: usize,
}

////////////////////////////////////////////////////////////////////////////////

impl Pin {
    pub fn to_usize(pin_vec: &Vec<Pin>) -> Vec<usize> {
        pin_vec.iter().map(|pin| usize::from(*pin)).collect()
    }

    pub fn to_c_vec(pin_vec: &Vec<Pin>) -> Vec<CCode> {
        pin_vec.iter().map(|pin| pin.to_c()).collect()
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

impl ToC for Pin {
    fn to_c(self) -> CCode {
        self.0.to_c()
    }
}



////////////////////////////////////////////////////////////////////////////////

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

impl KmapFormat {
    pub fn chord_length(&self) -> usize {
        let mut count = 0;
        for row in self.0.iter() {
            for _ in row.iter() {
                count += 1;
            }
        }
        count
    }

    pub fn flat_order(&self) -> Vec<SwitchPos> {
        let mut flat: Vec<SwitchPos> = Vec::new();
        for row in self.0.iter() {
            flat.extend_from_slice(row);
        }
        flat
    }
}

impl Validate for KmapFormat {
    fn validate(&self) -> Result<()> {
        for row in self.0.iter() {
            for switch_pos in row.iter() {
                switch_pos.validate()?;
            }
        }
        Ok(())
    }
}

//////////////////////////////

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

impl Validate for KmapInfo {
    fn validate(&self) -> Result<()> {
        self.file.validate()
    }
}

fn return_false() -> bool {
    false
}

//////////////////////////////

impl Validate for ModeInfo {
    fn validate(&self) -> Result<()> {
        for kmap in &self.keymaps {
            kmap.validate()?;
        }
        Ok(())
    }
}



//////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

impl Permutation {
    pub fn from_to<T>(old: &[T], new: &[T]) -> Permutation
    where
        T: Clone + Eq + ToString + Debug,
    {
        let mut order = Vec::new();
        for new_item in new {
            let pos_in_old = old.iter().position(|item| item == new_item);
            order.push(pos_in_old)
        }
        Permutation {
            order: order,
            old_length: old.len(),
        }
    }

    pub fn permute<T>(&self, old: &[T]) -> Result<Vec<T>>
    where
        T: Clone + Default,
    {
        if old.len() != self.old_length {
            bail!(ErrorKind::Permute);
        }

        let length = self.order.len();
        let mut new: Vec<_> = iter::repeat(T::default()).take(length).collect();
        for new_index in 0..length {
            if let Some(old_index) = self.order[new_index] {
                new[new_index] = old[old_index].to_owned();
            }
            // Otherwise, leave the default value alone.
        }
        Ok(new)
    }
}

#[test]
fn test_permute_reverse() {
    let p = Permutation::from_to(&[1, 2, 3], &[3, 2, 1]);
    assert_eq!(vec!["c", "b", "a"], p.permute(&["a", "b", "c"]).unwrap())
}

#[test]
fn test_permute_identity() {
    let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]);
    assert_eq!(vec![11, 12, 13], p.permute(&[11, 12, 13]).unwrap())
}

#[test]
fn test_permute_shorten() {
    let p = Permutation::from_to(&[1, 2, 3, 4, 5], &[5, 4, 3]);
    assert_eq!(vec![15, 14, 13], p.permute(&[11, 12, 13, 14, 15]).unwrap())
}

#[test]
fn test_permute_lengthen() {
    let p = Permutation::from_to(&[1, 2, 3], &[5, 4, 3, 2, 1]);
    assert_eq!(vec![0, 0, 13, 12, 11], p.permute(&[11, 12, 13]).unwrap())
}

#[test]
fn test_permute_err_long() {
    let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]);
    match p.permute(&[11, 12, 13, 14]) {
        Err(Error(ErrorKind::Permute, _)) => (),
        _ => panic!("should have returned permute error"),
    }
}

#[test]
fn test_permute_err_short() {
    let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]);
    match p.permute(&[11, 12]) {
        Err(Error(ErrorKind::Permute, _)) => (),
        _ => panic!("should have returned permute error"),
    }
}
