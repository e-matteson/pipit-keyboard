use types::{CCode, Name, ToC, Validate};
use failure::{Error, ResultExt};
use types::errors::*;

use std::borrow::Borrow;
use std::string::ToString;

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
    pub fn empty_code() -> CCode {
        "0".to_c()
    }

    pub fn new(
        key: Option<String>,
        modifiers: Option<Vec<String>>,
    ) -> Result<KeyPress, Error> {
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

    pub fn is_mod_blank(&self) -> bool {
        self.mods.is_none()
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
        // TODO compare to an actual list of defined key codes?
        //  Could vary with underlying keyboard lib, though
        let mut is_empty = true;

        if let Some(ref s) = self.key {
            assert_legal(s)?;
            is_empty = false;
        }
        if let Some(ref v) = self.mods {
            for s in v.iter() {
                assert_legal(s)?;
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

fn make_key(key: Option<String>) -> Result<Option<CCode>, Error> {
    // TODO map
    Ok(match key {
        Some(s) => Some(sanitize(&s)?),
        None => None,
    })
}

fn make_mod(
    modifiers: Option<Vec<String>>,
) -> Result<Option<Vec<CCode>>, Error> {
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

fn sanitize(s: &str) -> Result<CCode, Error> {
    assert_legal(s)?;
    Ok(s.to_c())
}

fn assert_legal<T>(s: T) -> Result<(), Error>
where
    T: Borrow<str> + ToString,
{
    if !contains_illegal_char(s.borrow()) {
        Ok(())
    } else {
        Err(BadValueErr {
            thing: "KeyPress".into(),
            value: s.to_string(),
        }).context("Contains illegal characters")?
    }
}

fn contains_illegal_char(string: &str) -> bool {
    // TODO use regex, for this and c_identifiers, c_macros, etc
    lazy_static! {
        static ref LEGAL: Vec<char>  = vec![
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
    }

    for c in string.chars() {
        if !LEGAL.contains(&c) {
            return true;
        }
    }
    false
}
