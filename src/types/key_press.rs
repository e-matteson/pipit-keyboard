use types::{CCode, Name, ToC};
use types::errors::*;

// TODO KeyPress is also used to store command codes, which is kinda a hack.
// Rename?

#[derive(Debug, PartialEq, Eq, Clone)]
pub struct KeyPress {
    pub key: CCode,
    pub modifier: CCode,
}

impl KeyPress {
    pub fn new(
        key: Option<String>,
        modifiers: Option<Vec<String>>,
    ) -> Result<KeyPress> {
        Ok(KeyPress {
            key: make_key(key)?,
            modifier: make_mod(modifiers)?,
        })
    }

    pub fn new_fake(code: &Name) -> KeyPress {
        // We also use KeyPresses to store command codes
        KeyPress {
            key: code.to_c(),
            modifier: "0".to_c(),
        }
    }
    pub fn new_blank() -> KeyPress {
        KeyPress {
            key: "0".to_c(),
            modifier: "0".to_c(),
        }
    }
    pub fn is_mod_blank(&self) -> bool {
        self.modifier == "0".to_c()
    }
}

fn make_key(key: Option<String>) -> Result<CCode> {
    Ok(sanitize(&or_default(key))?)
}

fn make_mod(modifiers: Option<Vec<String>>) -> Result<CCode> {
    Ok(match modifiers {
        Some(v) => {
            let mut mod_codes = Vec::new();
            for m in v {
                mod_codes.push(sanitize(&m)?);
            }
            mod_codes.join("|").to_c()
        }
        None => or_default(None).to_c(),
    })
}

fn or_default(string: Option<String>) -> String {
    string.unwrap_or_else(|| "0".into())
}

fn sanitize(s: &str) -> Result<CCode> {
    // TODO compare to an actual list of defined key codes?
    //  Could vary with underlying keyboard lib, though
    if contains_illegal_char(s) {
        bail!(ErrorKind::BadValue("KeyPress".into(), Some(s.to_owned())))
    } else {
        Ok(s.to_c())
    }
}

fn contains_illegal_char(string: &str) -> bool {
    // It's not quite worth using the regex crate for this...
    let legal = vec![
        '_',
        '|',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        'V',
        'W',
        'X',
        'Y',
        'Z',
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    ];
    for c in string.chars() {
        if !legal.contains(&c) {
            return true;
        }
    }
    false
}
