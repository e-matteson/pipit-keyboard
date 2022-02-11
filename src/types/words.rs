use std::borrow::Cow;
use std::fmt;
use std::str::FromStr;
use unicode_segmentation::UnicodeSegmentation;

use error::{Error, ResultExt};
use types::{KeyPress, Name, SeqType, Sequence, Spelling, Validate};

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

/// Snippets are basically just sugar around macros. Their definitions in the
/// settings file are like `word` definitions, with relative chords and strings
/// for sequences. But to the firmware, they look just like other macros.
#[derive(Deserialize, Debug, Clone)]
#[serde(deny_unknown_fields)]
pub struct Snippet {
    pub snippet: String,
    pub chord: Option<String>,
}

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Debug)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
pub struct WordListName(pub String);

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Debug)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
pub struct SnippetListName(pub String);

////////////////////////////////////////////////////////////////////////////////

// TODO shrink, make more methods default
// TODO be consistent about meaning of "spelling"
pub trait Wordlike {
    type WordlikeListName: ToString;

    fn seq_type() -> SeqType;
    fn seq_field(&self) -> &str;
    fn chord_field(&self) -> Option<&String>;
    fn anagram_num(&self) -> AnagramNum;
    fn name_prefix() -> &'static str;

    fn has_alternate_chord(&self) -> bool {
        self.chord_field().is_some()
    }

    fn chord_spellings(&self) -> Result<Vec<Spelling>, Error> {
        self.chord_string()
            .graphemes(true)
            .map(Spelling::new)
            .collect()
    }

    fn chord_string(&self) -> Cow<str> {
        // If an alternate chord string was given, use that. Otherwise, use the
        // sequence string.

        // Also return true if the chord should include
        // `shift`.  TODO wait what?

        if let Some(chord_str) = self.chord_field() {
            chord_str.into()
        } else {
            // uppercase letters in the sequence string don't affect the chord
            self.seq_field().to_lowercase().into()
        }
    }

    fn sequence(&self) -> Result<Sequence, Error> {
        let mut seq = Sequence::default();

        for letter in self.seq_field().graphemes(true) {
            let keypress = KeyPress::from_str(&letter.to_string())
                .with_context(|| {
                    format!("Invalid letter in sequence {}", self.seq_field())
                })?;
            seq.push(keypress);
        }

        if seq.is_empty() {
            return Err(Error::Empty("Sequence".into()));
        }
        Ok(seq)
    }

    /// Generate a name for this word mapping that will be unique
    fn name(&self, wordlike_list_name: &Self::WordlikeListName) -> Name {
        let mut parts: Vec<Cow<str>> = vec![
            Self::name_prefix().into(),
            wordlike_list_name.to_string().into(),
            self.seq_field().into(),
        ];
        if let Some(alternate_chord) = self.chord_field() {
            parts.push(alternate_chord.into());
        }
        parts.push(self.anagram_num().to_string().into());
        let name = parts.join("_");

        // Sanitize escape chars that are allowed in sequences, but shouldn't
        // be interepreted literally in names
        let name = name.replace("\n", r"\n").replace("\t", r"\t");
        Name(name)
    }
}

////////////////////////////////////////////////////////////////////////////////

impl Wordlike for Word {
    type WordlikeListName = WordListName;

    fn seq_type() -> SeqType {
        SeqType::Word
    }

    fn seq_field(&self) -> &str {
        &self.word
    }

    fn chord_field(&self) -> Option<&String> {
        self.chord.as_ref()
    }

    fn anagram_num(&self) -> AnagramNum {
        self.anagram.unwrap_or_default()
    }

    fn has_alternate_chord(&self) -> bool {
        self.chord.is_some()
    }

    fn name_prefix() -> &'static str {
        "word"
    }
}

impl Wordlike for Snippet {
    type WordlikeListName = SnippetListName;

    fn seq_type() -> SeqType {
        SeqType::Macro
    }

    fn seq_field(&self) -> &str {
        &self.snippet
    }

    fn chord_field(&self) -> Option<&String> {
        self.chord.as_ref()
    }

    fn anagram_num(&self) -> AnagramNum {
        // Should always be anagram 0, like macros and plain keys
        AnagramNum::default()
    }

    fn name_prefix() -> &'static str {
        "snippet"
    }
}

impl Validate for Word {
    fn validate(&self) -> Result<(), Error> {
        self.anagram.validate()
    }
}

impl Validate for Snippet {
    fn validate(&self) -> Result<(), Error> {
        Ok(())
    }
}

impl Validate for WordListName {
    fn validate(&self) -> Result<(), Error> {
        if self.0.is_empty() {
            Err(Error::BadValueErr {
                thing: "word list name".to_owned(),
                value: "(empty)".to_owned(),
            })
        } else {
            Ok(())
        }
    }
}

impl Validate for SnippetListName {
    fn validate(&self) -> Result<(), Error> {
        if self.0.is_empty() {
            Err(Error::BadValueErr {
                thing: "snippet list name".to_owned(),
                value: "(empty)".to_owned(),
            })
        } else {
            Ok(())
        }
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
    pub fn max_allowed() -> u8 {
        // We currently use 4 bits to store anagram.
        (2_u32.pow(4) - 1) as u8
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
        let max = Self::max_allowed();
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

impl fmt::Display for SnippetListName {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl From<String> for SnippetListName {
    fn from(s: String) -> SnippetListName {
        SnippetListName(s)
    }
}

impl Into<String> for SnippetListName {
    fn into(self) -> String {
        self.0
    }
}

impl fmt::Display for WordListName {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl From<String> for WordListName {
    fn from(s: String) -> WordListName {
        WordListName(s)
    }
}

impl Into<String> for WordListName {
    fn into(self) -> String {
        self.0
    }
}
