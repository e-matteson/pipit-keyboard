use itertools::Itertools;
use std::fmt;
use unicode_segmentation::UnicodeSegmentation;

use error::{Error, ResultExt};
use tutor::{Label, LabeledChord, State};
use types::{Chord, KmapOrder, Name};

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct Slide {
    #[serde(default)]
    pub instruction: String,
    pub line: SlideLine,
}

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub enum SlideLine {
    Letters(String),
    Words {
        words: Vec<SlideWord>,
        #[serde(default = "return_true")]
        show_errors: bool,
    },
}

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct SlideWord {
    pub names: Vec<Name>,
    #[serde(default)]
    pub text: String,
    #[serde(default)]
    pub length_override: Option<usize>,
}

#[derive(Debug, Clone)]
pub struct SlideEntry {
    pub text: String,
    pub chord: Chord<KmapOrder>,
    pub length: usize,
}

impl SlideLine {
    pub fn show_errors(&self) -> bool {
        match self {
            SlideLine::Letters(_) => true,
            SlideLine::Words { show_errors, .. } => *show_errors,
        }
    }

    pub fn has_length_overrides(&self) -> bool {
        match self {
            SlideLine::Letters(_) => false,
            SlideLine::Words { words, .. } => {
                words.iter().any(|w| w.length_override.is_some())
            }
        }
    }

    pub fn to_entries(&self) -> Result<(Vec<SlideEntry>, String), Error> {
        Ok(match self {
            SlideLine::Letters(string) => (Vec::new(), string.to_owned()),
            SlideLine::Words { words, .. } => {
                let entries: Result<Vec<_>, _> = words
                    .iter()
                    .map(|word| {
                        SlideEntry::from_word(word).with_context(|| {
                            format!(
                                "Failed to make slide entry from word: {}",
                                word
                            )
                        })
                    }).collect();
                let entries = entries?;
                let string =
                    entries.iter().map(|entry| entry.text.clone()).join("");
                (entries, string)
            }
        })
    }
}

impl SlideEntry {
    // fn from_letter(letter: String) -> Result<SlideEntry, Error> {
    //     Ok(SlideEntry {
    //         chord: char_to_chord(&letter).ok_or_else(|| BadValueErr {
    //             thing: "character".into(),
    //             value: letter.clone(),
    //         })?,
    //         length: letter.graphemes(true).count(),
    //         text: letter.clone(),
    //     })
    // }

    fn from_word(word: &SlideWord) -> Result<Self, Error> {
        let chords = word
            .names
            .iter()
            .map(|name| State::chord(name))
            .collect::<Result<Vec<_>, _>>()?;

        let chord = chords
            .into_iter()
            .fold1(|a, b| a.union(&b).expect("failed to union word chords"))
            .ok_or_else(|| Error::Empty("word chords".to_owned()))?;

        Ok(Self {
            chord,
            length: word
                .length_override
                .unwrap_or_else(|| word.text.graphemes(true).count()),
            text: word.text.clone(),
        })
    }

    pub fn len(&self) -> usize {
        self.length
    }

    pub fn to_labeled_chord(&self) -> LabeledChord {
        LabeledChord {
            label: self.label(),
            chord: self.chord.clone(),
        }
    }

    pub fn label(&self) -> Label {
        if self.text.graphemes(true).count() == 1 {
            Label::from_char(&self.text)
        } else {
            Label::default()
        }
    }
}

impl fmt::Display for SlideWord {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.text.fmt(f)
    }
}

fn return_true() -> bool {
    true
}
