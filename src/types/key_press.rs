use types::{CCode, Name, ToC, Validate};
use failure::{Error, ResultExt};
use types::errors::*;

use std::string::ToString;
use std::str::FromStr;
use std::collections::BTreeMap;

// Used for when a keypress contains only modifiers and no key.
pub const BLANK_KEY: &str = "BLANK_KEY";

// TODO KeyPress is also used to store command codes, which is kinda a hack.
// Rename?
#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KeyPress {
    pub key: Option<CCode>,
    pub mods: Option<Vec<CCode>>,
}

////////////////////////////////////////////////////////////////////////////////

impl KeyPress {
    pub fn blank() -> CCode {
        BLANK_KEY.to_c()
    }

    pub fn empty_code() -> CCode {
        "0".to_c()
    }

    pub fn new_fake(code: &Name) -> KeyPress {
        // We also use KeyPresses to store command codes
        KeyPress {
            key: Some(code.to_c()),
            mods: None,
        }
    }

    pub fn is_mod_blank(&self) -> bool {
        self.mods.is_none()
    }

    pub fn key_or_blank(&self) -> CCode {
        if let Some(key_code) = &self.key {
            key_code.to_owned()
        } else {
            KeyPress::blank()
        }
    }

    pub fn defined_keycodes() -> &'static BTreeMap<CCode, CCode> {
        lazy_static!{
            static ref CODES: BTreeMap<CCode, CCode> = vec![
                ("MODIFIERKEY_CTRL", "0x01"),
                ("MODIFIERKEY_SHIFT",        "0x02"),
                ("MODIFIERKEY_ALT",          "0x04"),
                ("MODIFIERKEY_GUI",          "0x08"),
                ("MODIFIERKEY_LEFT_CTRL",    "0x01"),
                ("MODIFIERKEY_LEFT_SHIFT",   "0x02"),
                ("MODIFIERKEY_LEFT_ALT",     "0x04"),
                ("MODIFIERKEY_LEFT_GUI",     "0x08"),
                ("MODIFIERKEY_RIGHT_CTRL",   "0x10"),
                ("MODIFIERKEY_RIGHT_SHIFT",  "0x20"),
                ("MODIFIERKEY_RIGHT_ALT",    "0x40"),
                ("MODIFIERKEY_RIGHT_GUI",    "0x80"),
                ("KEY_A",            "4"),
                ("KEY_B",            "5"),
                ("KEY_C",            "6"),
                ("KEY_D",            "7"),
                ("KEY_E",            "8"),
                ("KEY_F",            "9"),
                ("KEY_G",            "10"),
                ("KEY_H",            "11"),
                ("KEY_I",            "12"),
                ("KEY_J",            "13"),
                ("KEY_K",            "14"),
                ("KEY_L",            "15"),
                ("KEY_M",            "16"),
                ("KEY_N",            "17"),
                ("KEY_O",            "18"),
                ("KEY_P",            "19"),
                ("KEY_Q",            "20"),
                ("KEY_R",            "21"),
                ("KEY_S",            "22"),
                ("KEY_T",            "23"),
                ("KEY_U",            "24"),
                ("KEY_V",            "25"),
                ("KEY_W",            "26"),
                ("KEY_X",            "27"),
                ("KEY_Y",            "28"),
                ("KEY_Z",            "29"),
                ("KEY_1",            "30"),
                ("KEY_2",            "31"),
                ("KEY_3",            "32"),
                ("KEY_4",            "33"),
                ("KEY_5",            "34"),
                ("KEY_6",            "35"),
                ("KEY_7",            "36"),
                ("KEY_8",            "37"),
                ("KEY_9",            "38"),
                ("KEY_0",            "39"),
                ("KEY_ENTER",        "40"),
                ("KEY_ESC",          "41"),
                ("KEY_BACKSPACE",    "42"),
                ("KEY_TAB",          "43"),
                ("KEY_SPACE",        "44"),
                ("KEY_MINUS",        "45"),
                ("KEY_EQUAL",        "46"),
                ("KEY_LEFT_BRACE",   "47"),
                ("KEY_RIGHT_BRACE",  "48"),
                ("KEY_BACKSLASH",    "49"),
                ("KEY_NON_US_NUM",   "50"),
                ("KEY_SEMICOLON",    "51"),
                ("KEY_QUOTE",        "52"),
                ("KEY_TILDE",        "53"),
                ("KEY_COMMA",        "54"),
                ("KEY_PERIOD",       "55"),
                ("KEY_SLASH",        "56"),
                ("KEY_CAPS_LOCK",    "57"),
                ("KEY_F1",           "58"),
                ("KEY_F2",           "59"),
                ("KEY_F3",           "60"),
                ("KEY_F4",           "61"),
                ("KEY_F5",           "62"),
                ("KEY_F6",           "63"),
                ("KEY_F7",           "64"),
                ("KEY_F8",           "65"),
                ("KEY_F9",           "66"),
                ("KEY_F10",          "67"),
                ("KEY_F11",          "68"),
                ("KEY_F12",          "69"),
                ("KEY_PRINTSCREEN",  "70"),
                ("KEY_SCROLL_LOCK",  "71"),
                ("KEY_PAUSE",        "72"),
                ("KEY_INSERT",       "73"),
                ("KEY_HOME",         "74"),
                ("KEY_PAGE_UP",      "75"),
                ("KEY_DELETE",       "76"),
                ("KEY_END",          "77"),
                ("KEY_PAGE_DOWN",    "78"),
                ("KEY_RIGHT",        "79"),
                ("KEY_LEFT",         "80"),
                ("KEY_DOWN",         "81"),
                ("KEY_UP",           "82"),
                ("KEY_NUM_LOCK",     "83"),
                ("KEYPAD_SLASH",     "84"),
                ("KEYPAD_ASTERIX",   "85"),
                ("KEYPAD_MINUS",     "86"),
                ("KEYPAD_PLUS",      "87"),
                ("KEYPAD_ENTER",     "88"),
                ("KEYPAD_1",         "89"),
                ("KEYPAD_2",         "90"),
                ("KEYPAD_3",         "91"),
                ("KEYPAD_4",         "92"),
                ("KEYPAD_5",         "93"),
                ("KEYPAD_6",         "94"),
                ("KEYPAD_7",         "95"),
                ("KEYPAD_8",         "96"),
                ("KEYPAD_9",         "97"),
                ("KEYPAD_0",         "98"),
                ("KEYPAD_PERIOD",    "99"),
                ("KEY_MENU",	       "101"),
                ("KEY_F13",          "104"),
                ("KEY_F14",          "105"),
                ("KEY_F15",          "106"),
                ("KEY_F16",          "107"),
                ("KEY_F17",          "108"),
                ("KEY_F18",          "109"),
                ("KEY_F19",          "110"),
                ("KEY_F20",          "111"),
                ("KEY_F21",          "112"),
                ("KEY_F22",          "113"),
                ("KEY_F23",          "114"),
                ("KEY_F24",          "115"),
            ].into_iter().map(|(x,y)| (x.to_c(), y.to_c())).collect();
        }
        &CODES
    }
}

impl Default for KeyPress {
    fn default() -> KeyPress {
        KeyPress {
            key: None,
            mods: None,
        }
    }
}

impl Validate for KeyPress {
    fn validate(&self) -> Result<(), Error> {
        let mut is_empty = true;

        if let Some(ref s) = self.key {
            assert_defined_keycode(s)?;
            is_empty = false;
        }
        if let Some(ref v) = self.mods {
            for s in v.iter() {
                assert_defined_keycode(s)?;
                is_empty = false;
            }
        }

        if is_empty {
            Err(MissingErr {
                missing: "key or modifier".into(),
                container: "key press".into(),
            })?;
        }

        Ok(())
    }
}

impl FromStr for KeyPress {
    type Err = Error;

    fn from_str(character_string: &str) -> Result<Self, Self::Err> {
        let character = to_single_char(character_string)?;
        let shift = Some(vec!["MODIFIERKEY_SHIFT".to_c()]);
        if character.is_alphanumeric() {
            return Ok(KeyPress {
                key: Some(format!("KEY_{}", character.to_uppercase()).to_c()),
                mods: if character.is_uppercase() {
                    shift
                } else {
                    None
                },
            });
        }
        // TODO share info with plain_keys in settings?
        // Want it to be visible in settings, as an example of how to write
        // macros manually. And don't want weird order dependencies in
        // deserializing settings.
        let (key, mods) = match character {
            ' ' => ("KEY_SPACE", None),
            '.' => ("KEY_PERIOD", None),
            ',' => ("KEY_COMMA", None),
            '&' => ("KEY_7", shift),
            '*' => ("KEY_8", shift),
            '@' => ("KEY_2", shift),
            '\\' => ("KEY_BACKSLASH", None),
            '!' => ("KEY_1", shift),
            '^' => ("KEY_6", shift),
            ':' => ("KEY_SEMICOLON", shift),
            '$' => ("KEY_4", shift),
            '"' => ("KEY_QUOTE", shift),
            '=' => ("KEY_EQUAL", None),
            '`' => ("KEY_TILDE", None),
            '~' => ("KEY_TILDE", shift),
            '#' => ("KEY_3", shift),
            '<' => ("KEY_COMMA", shift),
            '[' => ("KEY_LEFT_BRACE", None),
            '{' => ("KEY_LEFT_BRACE", shift),
            '(' => ("KEY_9", shift),
            '-' => ("KEY_MINUS", None),
            '%' => ("KEY_5", shift),
            '|' => ("KEY_BACKSLASH", shift),
            '+' => ("KEY_EQUAL", shift),
            '?' => ("KEY_SLASH", shift),
            '\'' => ("KEY_QUOTE", None),
            '>' => ("KEY_PERIOD", shift),
            ']' => ("KEY_RIGHT_BRACE", None),
            '}' => ("KEY_RIGHT_BRACE", shift),
            ')' => ("KEY_0", shift),
            ';' => ("KEY_SEMICOLON", None),
            '/' => ("KEY_SLASH", None),
            '_' => ("KEY_MINUS", shift),
            _ => Err(BadValueErr {
                thing: "character".into(),
                value: character.to_string(),
            }).context("Character not allowed in sequence")?,
        };

        Ok(KeyPress {
            key: Some(key.to_c()),
            mods: mods,
        })
    }
}

fn to_single_char(character_string: &str) -> Result<char, Error> {
    let chars: Vec<_> = character_string.chars().collect();
    if chars.len() != 1 {
        Err(BadValueErr {
            thing: "single ascii character".into(),
            value: character_string.into(),
        })?;
    }
    Ok(chars[0])
}

fn assert_defined_keycode(name: &CCode) -> Result<(), Error> {
    if KeyPress::defined_keycodes().contains_key(name) {
        Ok(())
    } else {
        Err(BadValueErr {
            thing: "keycode name".into(),
            value: name.to_string(),
        }).context("Not defined in the firmware")?
    }
}
