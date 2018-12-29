use std::borrow::Borrow;
use std::fmt;
use unicode_segmentation::UnicodeSegmentation;

use tutor::State;
use types::{Chord, KmapOrder, Spelling};

#[derive(Clone, Debug)]
pub struct LabeledChord {
    pub chord: Chord<KmapOrder>,
    pub label: Label,
}

#[derive(Debug, Clone)]
pub struct Label(String);

////////////////////////////////////////////////////////////////////////////////

impl LabeledChord {
    pub fn from_letter(letter: &str) -> Option<Self> {
        let spelling = Spelling::new(letter).ok()?;
        Some(Self {
            chord: State::chord_from_spelling(spelling)?,
            label: Label::from_char(&letter),
        })
    }

    pub fn backspace() -> Option<Self> {
        Some(Self {
            chord: backspace_chord()?,
            label: "bak".into(),
        })
    }
}

impl Label {
    pub fn new(s: String) -> Option<Label> {
        if s.len() > Label::max_len() {
            None
        } else {
            Some(Label(s))
        }
    }

    pub fn from_char(character: &str) -> Self {
        let s = match character {
            "\n" => "ret".into(), // "⏎"
            "\t" => "tab".into(),
            " " => "spc".into(),
            c => c.into(),
        };
        Label::new(s).expect("label too long")
    }

    fn pad(&self, width: usize) -> String {
        let start = (width - self.len()) / 2. as usize;
        " ".repeat(start) + &self.0 + &" ".repeat(width - start)
    }

    fn len(&self) -> usize {
        self.0.graphemes(true).count()
    }

    pub fn join(labels: &[Label]) -> Option<Label> {
        if labels.is_empty() {
            return None;
        }
        if labels.len() == 1 {
            return Some(labels[0].to_owned());
        }
        // Try concatening everything, separated by spaces
        // If that's too long, try without spaces.
        // If that's still too long, give and return a placeholder
        Label::new(labels.join(" "))
            .or_else(|| Label::new(labels.join("")))
            .or_else(|| Some(Label::new_conflict()))
    }

    fn new_conflict() -> Label {
        Label::new("…".into()).expect("label conflict placeholder too long")
    }

    fn max_len() -> usize {
        3
    }
}

impl fmt::Display for Label {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let s = self.pad(Self::max_len());
        fmt::Display::fmt(&s, f)
    }
}

impl Default for Label {
    fn default() -> Self {
        Label(String::new())
    }
}

impl Into<Label> for String {
    fn into(self) -> Label {
        Label(self)
    }
}

impl From<Label> for String {
    fn from(label: Label) -> String {
        label.0
    }
}

impl<'a> From<&'a Label> for String {
    fn from(label: &'a Label) -> String {
        label.to_owned().into()
    }
}

impl<'a> Into<Label> for &'a str {
    fn into(self) -> Label {
        self.to_owned().into()
    }
}

impl Borrow<str> for Label {
    fn borrow(&self) -> &str {
        &self.0
    }
}

fn backspace_chord() -> Option<Chord<KmapOrder>> {
    State::chord(&"key_backspace".into()).ok()
}
