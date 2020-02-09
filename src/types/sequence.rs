use std::fmt::Debug;
use std::slice::Iter;
use std::string::ToString;

use std::str::FromStr;

use unicode_segmentation::UnicodeSegmentation;

use error::{Error, ResultExt};
use types::{KeyPress, Validate};

#[derive(Debug, Clone, Default)]
pub struct Sequence(pub Vec<KeyPress>);

impl Sequence {
    /// Flatten a list of sequences into a single sequence containing all of
    /// their keypresses.
    pub fn flatten(seqs: &[&Self]) -> Self {
        Sequence(
            seqs.iter()
                .flat_map(|seq| seq.keypresses().cloned())
                .collect(),
        )
    }

    pub fn push(&mut self, keypress: KeyPress) {
        self.0.push(keypress)
    }

    pub fn is_empty(&self) -> bool {
        self.0.is_empty()
    }

    pub fn len(&self) -> usize {
        self.0.len()
    }

    pub fn keypresses(&self) -> Iter<KeyPress> {
        self.0.iter()
    }

    pub fn lone_keypress(&self) -> Result<KeyPress, Error> {
        if self.len() == 1 {
            Ok(self.0[0].clone())
        } else {
            Err(Error::BadValueErr {
                thing: "sequence length".to_owned(),
                value: self.len().to_string(),
            })
            .context("Expected sequence containing only a single keypress")
        }
    }
}

impl FromStr for Sequence {
    type Err = Error;

    /// Construct a Sequence from the letters in a string, using each letter as
    /// the Spelling of a KeyPress.
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let presses: Result<Vec<_>, Self::Err> =
            s.graphemes(true).map(|c| KeyPress::from_str(c)).collect();
        Ok(Sequence(presses?))
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
        let mut s = Sequence::default();
        s.push(single);
        s
    }
}

impl<'a> From<&'a KeyPress> for Sequence {
    fn from(single: &'a KeyPress) -> Sequence {
        Sequence::from(single.to_owned())
    }
}
