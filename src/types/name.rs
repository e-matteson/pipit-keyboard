use std::fmt;

use error::Error;
use types::Validate;

#[derive(
    Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Serialize,
)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
// #[serde(finalize = "Name::sanitize")]
pub struct Name(pub String);

impl Name {
    pub fn is_empty(&self) -> bool {
        self.0.is_empty()
    }
}

impl Validate for Name {
    fn validate(&self) -> Result<(), Error> {
        // TODO anything to check? Not used c_code...
        if self.is_empty() {
            Err(Error::BadValueErr {
                thing: "binding name".to_owned(),
                value: "(empty)".to_owned(),
            })
        } else {
            Ok(())
        }
    }
}

impl From<String> for Name {
    fn from(s: String) -> Name {
        Name(s)
    }
}

impl Into<String> for Name {
    fn into(self) -> String {
        self.0
    }
}

impl<'a> Into<String> for &'a Name {
    fn into(self) -> String {
        self.0.to_owned()
    }
}

impl<'a> From<&'a str> for Name {
    fn from(s: &str) -> Name {
        Name(s.to_owned())
    }
}

impl fmt::Display for Name {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl fmt::Debug for Name {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}
