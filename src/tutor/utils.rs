use std::fs::{self, File};
use std::path::PathBuf;
use std::sync::Mutex;
use std::collections::BTreeMap;

use itertools::Itertools;
use unicode_segmentation::UnicodeSegmentation;
use ron::de::from_reader;

use types::{Chord, ModeName, Name, TutorData};
use failure::{Error, ResultExt};

lazy_static! {
    static ref TUTOR_DATA: Mutex<Option<TutorData>> = Mutex::new(None);
}

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
    pub chord: Chord,
    pub length: usize,
}

#[derive(Debug, Clone)]
pub enum LastChar {
    Correct,
    Incorrect(Option<LabeledChord>),
}

#[derive(Clone, Debug)]
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
                    .map(|word| SlideEntry::from_word(word))
                    .collect();
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

    fn from_word(word: &SlideWord) -> Result<SlideEntry, Error> {
        let chords: Option<Vec<_>> = word.names
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
            length: word.length_override
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

pub fn offset(width1: usize, width2: usize) -> usize {
    ((width2 - width1) as f32 / 2.).round() as usize
}

fn backspace_chord() -> Option<Chord> {
    get_tutor_data_chord(&"key_backspace".into())
}

pub fn load_lessons(
    lesson_dir: &str,
) -> Result<BTreeMap<String, Vec<Slide>>, Error> {
    let entries = fs::read_dir(lesson_dir)?;
    let mut map = BTreeMap::new();
    for entry in entries {
        let path = entry?.path();
        let name = lesson_path_to_name(&path);
        map.insert(name, read_lesson_file(&path)?);
    }
    Ok(map)
}

// vec![
//     (
//         "fake lesson".into(),
//         vec![
//             Slide {
//                 line: SlideLine::Letters("abababababab".into()),
//             },
//             Slide {
//                 line: SlideLine::Words {
//                     show_errors: false,
//                     words: vec![
//                         // SlideWord {
//                         //     names: vec!["word_the".into()],
//                         //     text: " teeth".into(),
//                         //     length_override: Some(4),
//                         // },
//                         // SlideWord {
//                         //     names: vec!["command_cycle_word".into()],
//                         //     text: "".into(),
//                         //     length_override: None,
//                         // },
//                         SlideWord {
//                             names: vec!["word_raw_2".into()],
//                             text: " raw".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["word_teeth_1".into()],
//                             text: " the".into(),
//                             length_override: Some(6),
//                         },
//                         SlideWord {
//                             names: vec!["command_cycle_word".into()],
//                             text: "".into(),
//                             length_override: None,
//                         },
//                         /* SlideWord {
//                          *     names: vec!["word_different_dif".into()],
//                          *     text: "different".into(),
//                          *     length_override: None,
//                          * }, */
//                     ],
//                 },
//             },
//             Slide {
//                 line: SlideLine::Words {
//                     show_errors: true,
//                     words: vec![
//                         SlideWord {
//                             names: vec![
//                                 "word_tap".into(),
//                                 "mod_nospace".into(),
//                                 "mod_capital".into(),
//                             ],
//                             text: "Tap".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec![
//                                 "word_ing".into(),
//                                 "mod_double".into(),
//                             ],
//                             text: "ping".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["key_space".into()],
//                             text: " ".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["key_l".into()],
//                             text: "l".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["key_e".into()],
//                             text: "e".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["key_t".into()],
//                             text: "t".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["key_t".into()],
//                             text: "t".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["key_e".into()],
//                             text: "e".into(),
//                             length_override: None,
//                         },
//                         SlideWord {
//                             names: vec!["key_r".into()],
//                             text: "r".into(),
//                             length_override: None,
//                         },
//                     ],
//                 },
//             },
//             Slide {
//                 line: SlideLine::Letters("goodbye".into()),
//             },
//         ],
//     ),
// ].into_iter()
//     .collect()

fn lesson_path_to_name(path: &PathBuf) -> String {
    let s = path.file_stem()
        .expect("invalid lesson file name")
        .to_str()
        .expect("lesson path is not valid unicode");
    let mut sections = s.split("_");
    let number = sections.next().expect("invalid lesson file name");
    let words: Vec<_> = sections.collect();
    format!("{}) {}", number, words.join(" "))
}

pub fn read_lesson_file(path: &PathBuf) -> Result<Vec<Slide>, Error> {
    let file = open_file(path)
        .context(format!("failed to open file: {}", path.display()))?;
    let slides: Vec<Slide> = from_reader(file)
        .context(format!("failed to read RON file: {}", path.display()))?;
    Ok(slides)
}

fn open_file(path: &PathBuf) -> Result<File, Error> {
    Ok(File::open(path)?)
}

fn return_true() -> bool {
    true
}
