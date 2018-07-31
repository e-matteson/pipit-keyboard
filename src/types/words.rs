use std::fmt;
use std::str::FromStr;
use unicode_segmentation::UnicodeSegmentation;

use failure::Error;
use types::errors::*;
use types::{KeyPress, Name, Sequence, Spelling, Validate};

#[derive(Deserialize, Debug, Clone)]
#[serde(deny_unknown_fields)]
pub struct Word {
    pub word: String,
    pub anagram: Option<AnagramNum>,
    pub chord: Option<String>,
}

#[derive(
    Deserialize,
    Serialize,
    Debug,
    Clone,
    Copy,
    Eq,
    PartialEq,
    Ord,
    PartialOrd,
    Hash,
)]
#[serde(deny_unknown_fields)]
pub struct AnagramNum(u8);

////////////////////////////////////////////////////////////////////////////////

impl Word {
    pub fn seq_spelling(&self) -> String {
        self.word.clone()
    }

    fn chord_spelling(&self) -> String {
        self.chord.clone().unwrap_or_else(|| self.word.clone())
    }

    pub fn chord_spellings(&self) -> Result<Vec<Spelling>, Error> {
        self.chord_spelling()
            .graphemes(true)
            .map(|letter| Ok(Spelling::new(letter)?.to_lowercase()))
            .collect()
    }

    pub fn anagram_num(&self) -> AnagramNum {
        self.anagram.unwrap_or(AnagramNum(0))
    }

    fn has_alternate_chord(&self) -> bool {
        self.chord.is_some()
    }

    /// Generate a name for this word mapping that will be unique
    pub fn name(&self) -> Name {
        let mut name = format!("word_{}", self.seq_spelling());
        if self.has_alternate_chord() {
            name += &format!("_{}", self.chord_spelling());
        }
        name += &format!("_{}", self.anagram_num().0);
        Name(name)
    }

    pub fn sequence(&self) -> Result<Sequence, Error> {
        let mut seq = Sequence::default();
        for letter in self.seq_spelling().graphemes(true) {
            let keypress = KeyPress::from_str(&letter.to_string())?;
            seq.push(keypress);
        }
        Ok(seq)
    }
}

impl Validate for Word {
    fn validate(&self) -> Result<(), Error> {
        self.anagram.validate()
    }
}

impl AnagramNum {
    pub fn new(num: u8) -> Result<Self, Error> {
        let a = AnagramNum(num);
        a.validate()?;
        Ok(a)
    }

    pub fn unwrap(self) -> u8 {
        self.0
    }

    /// This depends on the representation in the firmware lookup tables.
    pub fn max_allowable() -> u8 {
        15
    }

    /// Return an iterator over all the anagram numbers from zero to self,
    /// in order.
    pub fn up_to(self) -> Box<Iterator<Item = Self>> {
        Box::new((0..=self.0).map(AnagramNum))
    }
}

impl Default for AnagramNum {
    fn default() -> Self {
        AnagramNum(0)
    }
}

impl Validate for AnagramNum {
    fn validate(&self) -> Result<(), Error> {
        let max = Self::max_allowable();
        if self.0 > max {
            Err(OutOfRangeErr {
                name: "anagram number".into(),
                value: self.0 as usize,
                min: 0,
                max: max as usize,
            })?
        }
        Ok(())
    }
}

impl From<AnagramNum> for usize {
    fn from(num: AnagramNum) -> usize {
        num.0 as usize
    }
}

impl fmt::Display for AnagramNum {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // TODO use color?
        let s = format!("{}", self.unwrap());
        fmt::Display::fmt(&s, f)
    }
}
