use types::{CCode, Name, ToC};
use types::errors::*;

// TODO KeyPress is also used to store command codes, which is kinda a hack.
// Rename?

#[derive(Debug, PartialEq, Eq, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KeyPress {
    pub key: Option<CCode>,
    pub mods: Option<Vec<CCode>>,
}


impl KeyPress {
    pub fn empty_code() -> CCode {
        "0".to_c()
    }

    pub fn new(
        key: Option<String>,
        modifiers: Option<Vec<String>>,
    ) -> Result<KeyPress> {
        Ok(KeyPress {
            key: make_key(key)?,
            mods: make_mod(modifiers)?,
        })
    }

    pub fn new_fake(code: &Name) -> KeyPress {
        // We also use KeyPresses to store command codes
        KeyPress {
            key: Some(code.to_c()),
            mods: None,
        }
    }

    pub fn new_blank() -> KeyPress {
        KeyPress {
            key: None,
            mods: None,
        }
    }

    pub fn is_mod_blank(&self) -> bool {
        self.mods.is_none()
    }
}

fn make_key(key: Option<String>) -> Result<Option<CCode>> {
    // TODO map
    Ok(match key {
        Some(s) => Some(sanitize(&s)?),
        None => None,
    })
}

fn make_mod(modifiers: Option<Vec<String>>) -> Result<Option<Vec<CCode>>> {
    // TODO map
    Ok(match modifiers {
        Some(v) => {
            let mut mod_codes = Vec::new();
            for m in v {
                mod_codes.push(sanitize(&m)?);
            }
            Some(mod_codes)
        }
        None => None,
    })
}

// fn or_default(string: Option<String>) -> String {
//     string.unwrap_or_else(|| "0".into())
// }

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
