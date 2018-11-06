use std::borrow::Cow;
use std::fmt;
use std::str::FromStr;
use unicode_segmentation::UnicodeSegmentation;

use error::Error;
use types::{KeyPress, Name, Sequence, Spelling, Validate};

const DEFAULT_ANAGRAM_NUM: u8 = 0;

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
    // pub fn seq_spelling(&self) -> String {
    //     self.word.clone()
    // }
    pub fn seq_spelling(&self) -> &str {
        &self.word
    }

    fn chord_spelling(&self) -> &str {
        // self.chord.clone().unwrap_or_else(|| self.word.clone())
        self.chord.as_ref().unwrap_or_else(|| &self.word)
    }

    pub fn chord_spellings(&self) -> Result<Vec<Spelling>, Error> {
        self.chord_spelling()
            .graphemes(true)
            .map(|letter| Ok(Spelling::new(letter)?.to_lowercase()))
            .collect()
    }

    pub fn anagram_num(&self) -> AnagramNum {
        self.anagram.unwrap_or_default()
    }

    fn has_alternate_chord(&self) -> bool {
        self.chord.is_some()
    }

    /// Generate a name for this word mapping that will be unique
    pub fn name(&self) -> Name {
        let mut parts: Vec<Cow<str>> =
            vec!["word".into(), self.seq_spelling().into()];
        if self.has_alternate_chord() {
            parts.push(self.chord_spelling().into());
        }
        parts.push(self.anagram_num().to_string().into());
        let name = parts.join("_");

        // Sanitize escape chars that are allowed in sequences, but shouldn't
        // be interepreted literally in names
        let name = name.replace("\n", r"\n").replace("\t", r"\t");
        Name(name)
    }

    pub fn sequence(&self) -> Result<Sequence, Error> {
        let mut seq = Sequence::default();

        for letter in self.seq_spelling().graphemes(true) {
            let keypress = KeyPress::from_str(&letter.to_string())?;
            seq.push(keypress);
        }

        if seq.is_empty() {
            return Err(Error::Empty("Sequence".into()));
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

    pub fn get(self) -> u8 {
        self.0
    }

    /// This depends on the representation in the firmware lookup tables.
    pub fn max_allowable() -> u8 {
        15
    }

    /// Return an iterator over all the anagram numbers from zero to self,
    /// in order.
    pub fn up_to(self) -> impl Iterator<Item = Self> {
        Box::new((0..=self.0).map(AnagramNum))
    }

    pub fn is_default(self) -> bool {
        self.0 == DEFAULT_ANAGRAM_NUM
    }
}

impl Default for AnagramNum {
    fn default() -> Self {
        AnagramNum(DEFAULT_ANAGRAM_NUM)
    }
}

impl Validate for AnagramNum {
    fn validate(&self) -> Result<(), Error> {
        let max = Self::max_allowable();
        if self.0 <= max {
            Ok(())
        } else {
            Err(Error::OutOfRangeErr {
                name: "anagram number".into(),
                value: self.0 as usize,
                min: 0,
                max: max as usize,
            })
        }
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
        let s = format!("{}", self.get());
        fmt::Display::fmt(&s, f)
    }
}
