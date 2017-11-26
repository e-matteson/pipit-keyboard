use std::collections::BTreeMap;
use std::fs::File;
use std::path::PathBuf;
use std::io::{BufRead, BufReader};
use std::sync::Mutex;

use unicode_segmentation::UnicodeSegmentation;

use types::{Chord, ModeName, Name};
use types::errors::*;

pub struct TutorData(BTreeMap<ModeName, BTreeMap<Name, Chord>>);

lazy_static! {
    static ref TUTOR_DATA: Mutex<Option<TutorData>> = Mutex::new(None);
}

////////////////////////////////////////////////////////////////////////////////

impl TutorData {
    pub fn new(data: BTreeMap<ModeName, BTreeMap<Name, Chord>>) -> TutorData {
        TutorData(data)
    }

    pub fn set(data: TutorData) {
        let mut tutor_data = TUTOR_DATA.lock().unwrap();
        match *tutor_data {
            Some(_) => panic!("tutor data can only be set once"),
            None => *tutor_data = Some(data),
        }
    }

    pub fn get_chord(chord_name: Name) -> Option<Chord> {
        let mode_name = ModeName::default();

        if let Some(ref data) = *TUTOR_DATA.lock().unwrap() {
            data.0.get(&mode_name)?.get(&chord_name).cloned()
        } else {
            panic!("tutor data was not set")
        }
    }
}

pub fn char_to_chord(character: char) -> Option<Chord> {
    let (name, is_uppercase) = get_char_name(character)?;
    let mut chord = TutorData::get_chord(name)?;
    if is_uppercase {
        chord.intersect(&TutorData::get_chord(Name("mod_shift".into()))?)
    }
    Some(chord)
}


pub fn char_to_label(character: char) -> String {
    match character {
        '\n' => "ret".into(), // "⏎"
        '\t' => "tab".into(),
        ' ' => "spc".into(),
        c => c.to_string(),
    }
}

fn get_char_name(character: char) -> Option<(Name, bool)> {
    if character.is_alphanumeric() {
        return Some((
            Name(format!("key_{}", character.to_lowercase())),
            character.is_uppercase(),
        ));
    }
    let name = match character {
        '&' => "key_ampersand".into(),
        '*' => "key_asterisk".into(),
        '@' => "key_at".into(),
        '\\' => "key_backslash".into(),
        '!' => "key_bang".into(),
        '^' => "key_caret".into(),
        ':' => "key_colon".into(),
        ',' => "key_comma".into(),
        '$' => "key_dollar".into(),
        '"' => "key_doublequote".into(),
        '\n' => "key_enter".into(),
        '=' => "key_equal".into(),
        '`' => "key_grave".into(),
        '#' => "key_hash".into(),
        '<' => "key_left_angle".into(),
        '[' => "key_left_brace".into(),
        '{' => "key_left_curly".into(),
        '(' => "key_left_paren".into(),
        '-' => "key_minus".into(),
        '%' => "key_percent".into(),
        '.' => "key_period".into(),
        '|' => "key_pipe".into(),
        '+' => "key_plus".into(),
        '?' => "key_question".into(),
        '\'' => "key_quote".into(),
        '>' => "key_right_angle".into(),
        ']' => "key_right_brace".into(),
        '}' => "key_right_curly".into(),
        ')' => "key_right_paren".into(),
        ';' => "key_semicolon".into(),
        '/' => "key_slash".into(),
        ' ' => "key_space".into(),
        '\t' => "key_tab".into(),
        '~' => "key_tilde".into(),
        '_' => "key_underscore".into(),
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

pub fn read_file_lines(path: &PathBuf) -> Result<Vec<String>> {
    let file = File::open(path)
        .chain_err(|| format!("failed to open file: {}", path.display()))?;
    let buf = BufReader::new(file);
    let lines: Vec<String> = buf.lines()
        .map(|w| w.unwrap())
        .filter(|s| !s.is_empty())
        .collect();
    Ok(lines)
}

// fn read_file(path: &str) -> Result<String> {
//     let file = File::open(path)
//         .chain_err(|| format!("failed to open file: {}", path))?;
//     let mut s = String::new();
//     BufReader::new(file).read_to_string(&mut s)?;
//     Ok(s)
// }
