use std::collections::BTreeMap;
use std::fmt::{self, Debug};
use std::string::ToString;

use error::{Error, ResultExt};
use types::Name;

#[derive(Eq, PartialEq, PartialOrd, Ord, Clone, Copy, Debug)]
/// How a key would be represented in text. The Spelling for `key_a` would be
/// "a".
pub struct Spelling(pub char);

#[derive(Clone, Debug)]
pub struct SpellingTable(pub BTreeMap<Spelling, Name>);

impl Spelling {
    pub fn new(s: &str) -> Result<Self, Error> {
        let mut chars = s.chars();
        match (chars.next(), chars.next()) {
            (Some(first), None) => Ok(Spelling(first)),
            (_, _) => Err(Error::BadValueErr {
                thing: "single ascii character".to_owned(),
                value: s.to_owned(),
            })
            .context("failed to make spelling"),
        }
    }

    pub fn is_uppercase(self) -> bool {
        self.0.is_uppercase()
    }

    pub fn to_lowercase(self) -> Self {
        Spelling(
            self.0
                .to_lowercase()
                .next()
                .expect("failed to get lowercase spelling"),
        )
    }
}

impl fmt::Display for Spelling {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let s = self.0.to_string();
        fmt::Display::fmt(&s, f)
    }
}

impl SpellingTable {
    /// Return None if not found.
    // TODO return Cow<Name>
    pub fn get(&self, spelling: Spelling) -> Vec<Name> {
        if let Some(exact_name) = self.0.get(&spelling) {
            return vec![exact_name.to_owned()];
        }
        if spelling.is_uppercase() {
            if let Some(name) = self.0.get(&(spelling.to_lowercase())) {
                // TODO don't hardcode shift name
                return vec![name.to_owned(), Name::from("mod_shift")];
            }
        }
        Vec::new()
    }

    /// Return a LookupErr if not found.
    /// TODO is this a good name?
    pub fn get_checked(&self, spelling: Spelling) -> Result<Vec<Name>, Error> {
        let names = self.get(spelling);
        if names.is_empty() {
            Err(Error::LookupErr {
                key: format!("name for '{}'", spelling),
                container: "spelling table".to_owned(),
            })
        } else {
            Ok(names)
        }
    }
}
