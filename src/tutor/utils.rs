use std::fs::File;
use std::path::PathBuf;
use std::io::{BufRead, BufReader};
use std::sync::Mutex;

use itertools::Itertools;
use unicode_segmentation::UnicodeSegmentation;

use types::{Chord, ModeName, Name, TutorData};
use types::errors::BadValueErr;
// use types::errors::*;
use failure::{Error, ResultExt};

lazy_static! {
    static ref TUTOR_DATA: Mutex<Option<TutorData>> = Mutex::new(None);
}

#[derive(Debug, Clone)]
pub enum SlideLine {
    Letters(String),
    Words {
        words: Vec<SlideWord>,
        check_errors: bool,
    },
}

#[derive(Debug, Clone)]
pub struct SlideWord {
    pub names: Vec<Name>,
    pub text: String,
}

#[derive(Debug, Clone)]
pub struct SlideEntry {
    pub text: String,
    pub chord: Chord,
}

#[derive(Debug, Clone)]
pub struct Slide {
    // pub instructions: Option<String>,
    pub line: SlideLine,
}

#[derive(Debug, Clone)]
pub enum LastChar {
    Correct,
    Incorrect(Option<LabeledChord>),
}

#[derive(Debug, Clone)]
pub struct LabeledChord {
    pub chord: Chord,
    pub label: Label,
}

#[derive(Debug, Clone)]
pub struct Label(String);

////////////////////////////////////////////////////////////////////////////////

impl LastChar {
    pub fn backspace(&self) -> Option<LabeledChord> {
        match self {
            LastChar::Correct => None,
            LastChar::Incorrect(_) => LabeledChord::backspace(),
        }
    }

    pub fn error(&self) -> Option<LabeledChord> {
        match self {
            LastChar::Correct => None,
            LastChar::Incorrect(x) => x.clone(),
        }
    }

    pub fn is_correct(&self) -> bool {
        match self {
            LastChar::Correct => true,
            LastChar::Incorrect(_) => false,
        }
    }
}

impl TutorData {
    pub fn get_chord(&self, chord_name: &Name) -> Option<Chord> {
        // TODO don't assume default mode
        if chord_name == &Name(String::new()) {
            // Used for skipping colors in the cheatsheet config
            Some(Chord::default())
        } else {
            let mode_name = ModeName::default();
            self.chords.get(&mode_name)?.get(chord_name).cloned()
        }
    }
}

pub fn set_tutor_data(data: TutorData) {
    let mut tutor_data = TUTOR_DATA.lock().unwrap();
    match *tutor_data {
        Some(_) => panic!("tutor data can only be set once"),
        None => *tutor_data = Some(data),
    }
}

pub fn get_tutor_data_chord(name: &Name) -> Option<Chord> {
    if let Some(ref data) = *TUTOR_DATA.lock().unwrap() {
        data.get_chord(name)
    } else {
        panic!("tutor data was not set")
    }
}

impl SlideLine {
    pub fn check_errors(&self) -> bool {
        match self {
            SlideLine::Letters(_) => true,
            SlideLine::Words { check_errors, .. } => *check_errors,
        }
    }

    pub fn to_entries(&self) -> Result<(Vec<SlideEntry>, String), Error> {
        Ok(match self {
            SlideLine::Letters(string) => {
                let entries: Result<Vec<_>, Error> = string
                    .graphemes(true)
                    .map(|letter| SlideEntry::new(letter.into()))
                    .collect();
                (entries?, string.to_owned())
            }
            SlideLine::Words { words, .. } => {
                let entries: Result<Vec<_>, _> =
                    words.iter().map(|word| word.to_entry()).collect();
                let entries = entries?;
                let string =
                    entries.iter().map(|entry| entry.text.clone()).join("");
                (entries, string)
            }
        })
    }
}

impl SlideWord {
    fn to_entry(&self) -> Result<SlideEntry, Error> {
        let chords: Option<Vec<_>> = self.names
            .iter()
            .map(|name| get_tutor_data_chord(name))
            .collect();

        let chord = match chords {
            None => bail!("failed to create chords for word"),
            Some(v) => v.into_iter().fold(Chord::default(), |acc, mut c| {
                c.intersect(&acc);
                c
            }),
        };

        Ok(SlideEntry {
            chord: chord,
            text: self.text.clone(),
        })
    }
}

impl SlideEntry {
    fn new(letter: String) -> Result<SlideEntry, Error> {
        Ok(SlideEntry {
            chord: char_to_chord(&letter).ok_or_else(|| BadValueErr {
                thing: "character".into(),
                value: letter.clone(),
            })?,
            text: letter,
        })
    }

    pub fn len(&self) -> usize {
        self.text.graphemes(true).count()
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

impl LabeledChord {
    pub fn from_letter(letter: &str) -> Option<LabeledChord> {
        Some(LabeledChord {
            chord: char_to_chord(&letter)?,
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

pub fn char_to_chord(character: &str) -> Option<Chord> {
    let (name, is_uppercase) = get_char_name(character)?;
    let mut chord = get_tutor_data_chord(&name)?;
    if is_uppercase {
        chord.intersect(&get_tutor_data_chord(&Name("mod_shift".into()))?)
    }
    Some(chord)
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

// impl<'a, T> Into<Label> for &'a T
// where
//     T: Into<Label>,
// {
//     fn into(t: &T) -> Label {
//         t.to_owned().into()
//     }
// }

fn to_ascii(character: &str) -> Option<char> {
    let mut chars = character.chars();
    let first_char = chars
        .next()
        .expect("string should contain exactly one grapheme, but is empty");
    if chars.count() > 0 {
        // this grapheme contained more than one byte, so it's not ascii.
        None
    } else {
        Some(first_char)
    }
}

fn get_char_name(character: &str) -> Option<(Name, bool)> {
    if let Some(c) = to_ascii(character) {
        if c.is_alphanumeric() {
            return Some((
                Name(format!("key_{}", c.to_lowercase())),
                c.is_uppercase(),
            ));
        }
    }
    let name = match character {
        "&" => "key_ampersand".into(),
        "*" => "key_asterisk".into(),
        "@" => "key_at".into(),
        "\\" => "key_backslash".into(),
        "!" => "key_bang".into(),
        "^" => "key_caret".into(),
        ":" => "key_colon".into(),
        "," => "key_comma".into(),
        "$" => "key_dollar".into(),
        "\"" => "key_doublequote".into(),
        "\n" => "key_enter".into(),
        "=" => "key_equal".into(),
        "`" => "key_grave".into(),
        "#" => "key_hash".into(),
        "<" => "key_left_angle".into(),
        "[" => "key_left_brace".into(),
        "{" => "key_left_curly".into(),
        "(" => "key_left_paren".into(),
        "-" => "key_minus".into(),
        "%" => "key_percent".into(),
        "." => "key_period".into(),
        "|" => "key_pipe".into(),
        "+" => "key_plus".into(),
        "?" => "key_question".into(),
        "'" => "key_quote".into(),
        ">" => "key_right_angle".into(),
        "]" => "key_right_brace".into(),
        "}" => "key_right_curly".into(),
        ")" => "key_right_paren".into(),
        ";" => "key_semicolon".into(),
        "/" => "key_slash".into(),
        " " => "key_space".into(),
        "\t" => "key_tab".into(),
        "~" => "key_tilde".into(),
        "_" => "key_underscore".into(),
        _ => return None,
    };
    Some((Name(name), false))
}

pub fn grapheme_slice<'a>(
    s: &'a str,
    start: usize,
    end: usize,
) -> Box<Iterator<Item = &'a str> + 'a> {
    Box::new(s.graphemes(true).skip(start).take(end))
}

pub fn read_file_lines(path: &PathBuf) -> Result<Vec<String>, Error> {
    let file = open_file(path)
        .context(format!("failed to open file: {}", path.display()))?;
    let buf = BufReader::new(file);
    let lines: Vec<String> = buf.lines()
        .map(|w| w.unwrap())
        .filter(|s| !s.is_empty())
        .collect();
    Ok(lines)
}

fn open_file(path: &PathBuf) -> Result<File, Error> {
    Ok(File::open(path)?)
}

pub fn offset(width1: usize, width2: usize) -> usize {
    ((width2 - width1) as f32 / 2.).round() as usize
}

fn backspace_chord() -> Option<Chord> {
    get_tutor_data_chord(&"key_backspace".into())
}
