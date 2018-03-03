// A bunch of small, miscellaneous types that don't deserve their own files

use std::iter;
use std::fmt::{self, Debug};
use std::slice::Iter;
use std::string::ToString;

use types::{CCode, KeyPress, ToC, Validate};
use types::errors::*;
use failure::Error;

#[derive(Debug, PartialEq, Eq, Clone, Copy, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Pin(pub u8);

#[derive(Debug, PartialEq, Eq, Clone, Copy, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct SwitchPos {
    pub row: Pin,
    pub col: Pin,
}

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapFormat(Vec<Vec<SwitchPos>>);

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapInfo {
    pub file: KmapPath,
    #[serde(default = "return_false")]
    pub use_words: bool,
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
    #[serde(default = "return_false")]
    pub gaming: bool,
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
    order: Vec<usize>,
    new_length: usize,
}

////////////////////////////////////////////////////////////////////////////////

impl Pin {
    pub fn to_usize(pin_vec: &[Pin]) -> Vec<usize> {
        pin_vec.iter().map(|pin| usize::from(*pin)).collect()
    }

    pub fn to_c_vec(pin_vec: &[Pin]) -> Vec<CCode> {
        pin_vec.iter().map(|pin| pin.to_c()).collect()
    }
}

impl Validate for Pin {
    fn validate(&self) -> Result<(), Error> {
        const MIN_PIN_NUM: u8 = 0;
        const MAX_PIN_NUM: u8 = 30; // TODO pick real value

        if self.0 <= MAX_PIN_NUM && self.0 >= MIN_PIN_NUM {
            Ok(())
        } else {
            Err(OutOfRangeErr {
                name: "pin number".into(),
                value: self.0 as usize,
                min: MIN_PIN_NUM as usize,
                max: MAX_PIN_NUM as usize,
            }.into())
        }
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
    fn validate(&self) -> Result<(), Error> {
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

    pub fn switches_per_line(&self) -> Vec<usize> {
        self.0.iter().map(|v| v.len()).collect()
    }

    pub fn block_length(&self) -> usize {
        // 1 extra for the first line with the names
        1 + self.0.len()
    }
}

impl Validate for KmapFormat {
    fn validate(&self) -> Result<(), Error> {
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
    fn validate(&self) -> Result<(), Error> {
        self.file.validate()
    }
}

fn return_false() -> bool {
    false
}

//////////////////////////////

impl Validate for ModeInfo {
    fn validate(&self) -> Result<(), Error> {
        for kmap in &self.keymaps {
            kmap.validate()?;
        }
        Ok(())
    }
}

//////////////////////////////

impl Validate for KmapPath {
    fn validate(&self) -> Result<(), Error> {
        // TODO check if path exists and has .kmap extension?
        Ok(())
    }
}

impl Into<String> for KmapPath {
    fn into(self) -> String {
        self.0
    }
}

impl fmt::Display for KmapPath {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

//////////////////////////////

impl Validate for ModeName {
    fn validate(&self) -> Result<(), Error> {
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
    fn validate(&self) -> Result<(), Error> {
        // TODO anything to check? Not used c_code...
        Ok(())
    }
}

impl From<String> for Name {
    fn from(s: String) -> Name {
        Name(s)
    }
}

impl Into<String> for Name {
    fn into(self) -> String {
        self.0
    }
}

impl<'a> Into<String> for &'a Name {
    fn into(self) -> String {
        self.0.to_owned()
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

    // Flatten a list of sequences into a single sequence containing all of
    // their keypresses.
    pub fn flatten(seqs: &[&Sequence]) -> Sequence {
        Sequence(
            seqs.into_iter()
                .flat_map(|seq| seq.keypresses().cloned())
                .collect(),
        )
    }

    pub fn extend(&mut self, other: Sequence) {
        // TODO unused?
        // TODO let this take a reference or iter or something? Instead of
        // cloning the sequence first.
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
    fn validate(&self) -> Result<(), Error> {
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
    /// Create a Permutation that can permute sequences from the order of the
    /// old one to the order of the new one. All elements in `old_template`
    /// must be present in `new_template`. However, there can be extra elements
    /// in `new_template`.
    pub fn from_to<T>(
        old_template: &[T],
        new_template: &[T],
    ) -> Result<Permutation, PermuteErr>
    where
        T: Clone + Eq + ToString + Debug,
    {
        let mut order = Vec::new();
        for old_item in old_template {
            let pos_in_new = new_template
                .iter()
                .position(|item| item == old_item)
                .ok_or_else(|| PermuteErr::WouldDrop)?;
            order.push(pos_in_new)
        }

        Ok(Permutation {
            order: order,
            new_length: new_template.len(),
        })
    }

    /// Permute the given sequence to the new order. If the new sequence
    /// template contained extra elements not in the old sequence template,
    /// those elements in the returned sequence will be set to their
    /// default value.
    pub fn permute<T>(&self, old: &[T]) -> Result<Vec<T>, PermuteErr>
    where
        T: Clone + Default,
    {
        if old.len() != self.order.len() {
            Err(PermuteErr::Length)?;
        }

        let mut new: Vec<_> =
            iter::repeat(T::default()).take(self.new_length).collect();

        for (old_index, &new_index) in self.order.iter().enumerate() {
            new[new_index] = old[old_index].to_owned();
        }
        Ok(new)
    }
}

#[test]
fn test_permute_reverse() {
    let p = Permutation::from_to(&[1, 2, 3], &[3, 2, 1]).unwrap();
    assert_eq!(vec!["c", "b", "a"], p.permute(&["a", "b", "c"]).unwrap())
}

#[test]
fn test_permute_identity() {
    let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]).unwrap();
    assert_eq!(vec![11, 12, 13], p.permute(&[11, 12, 13]).unwrap())
}

#[test]
fn test_permute_lengthen() {
    let p = Permutation::from_to(&[1, 2, 3], &[5, 4, 3, 2, 1]).unwrap();
    println!("lengthen permutation: {:?}", p);
    assert_eq!(vec![0, 0, 13, 12, 11], p.permute(&[11, 12, 13]).unwrap())
}

#[test]
fn test_permute_err_shorten() {
    if Permutation::from_to(&[1, 2, 3, 4, 5], &[5, 4, 3]).is_ok() {
        panic!("should be permute error, but was ok");
    }
}

#[test]
fn test_permute_err_long() {
    let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]).unwrap();
    if p.permute(&[11, 12, 13, 14]).is_ok() {
        panic!("should be permute error, but was ok");
    }
}

#[test]
fn test_permute_err_short() {
    let p = Permutation::from_to(&[1, 2, 3], &[1, 2, 3]).unwrap();
    if p.permute(&[11, 12]).is_ok() {
        panic!("should be permute error, but was ok");
    }
}
