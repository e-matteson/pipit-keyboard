use unicode_segmentation::UnicodeSegmentation;

use tutor::State;
use types::{Chord, Spelling};

#[derive(Clone, Debug)]
pub struct LabeledChord {
    pub chord: Chord,
    pub label: Label,
}

#[derive(Debug, Clone)]
pub struct Label(String);

#[derive(Debug, Clone)]
pub enum PrevCharStatus {
    Correct,
    Incorrect(Option<LabeledChord>),
}

////////////////////////////////////////////////////////////////////////////////

impl LabeledChord {
    pub fn from_letter(letter: &str) -> Option<LabeledChord> {
        let spelling = Spelling::new(letter).ok()?;
        Some(LabeledChord {
            chord: State::chord_from_spelling(&spelling)?,
            label: Label::from_char(&letter),
        })
    }

    fn backspace() -> Option<LabeledChord> {
        Some(LabeledChord {
            chord: backspace_chord()?,
            label: "bak".into(),
        })
    }
}

impl PrevCharStatus {
    pub fn backspace(&self) -> Option<LabeledChord> {
        if State::freeze_on_error() {
            None
        } else {
            match self {
                PrevCharStatus::Correct => None,
                PrevCharStatus::Incorrect(_) => LabeledChord::backspace(),
            }
        }
    }

    pub fn error(&self) -> Option<LabeledChord> {
        match self {
            PrevCharStatus::Correct => None,
            PrevCharStatus::Incorrect(x) => x.clone(),
        }
    }

    pub fn is_correct(&self) -> bool {
        match self {
            PrevCharStatus::Correct => true,
            PrevCharStatus::Incorrect(_) => false,
        }
    }
}

impl Label {
    pub fn from_char(character: &str) -> Label {
        match character {
            "\n" => "ret".into(), // "⏎"
            "\t" => "tab".into(),
            " " => "spc".into(),
            c => c.into(),
        }
    }

    pub fn pad(&self, width: usize) -> String {
        let start = (width - self.len()) / 2. as usize;
        " ".repeat(start) + &self.0 + &" ".repeat(width - start)
    }

    fn len(&self) -> usize {
        self.0.graphemes(true).count()
    }
}

impl Default for Label {
    fn default() -> Label {
        Label(String::new())
    }
}

impl Into<Label> for String {
    fn into(self) -> Label {
        Label(self)
    }
}

impl<'a> Into<Label> for &'a str {
    fn into(self) -> Label {
        self.to_owned().into()
    }
}

fn backspace_chord() -> Option<Chord> {
    State::chord(&"key_backspace".into())
}
