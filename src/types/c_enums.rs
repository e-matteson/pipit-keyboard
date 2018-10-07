use std::fmt;

use failure::Error;
use types::{CCode, CEnumVariant, Name, ToC, Validate};

#[derive(
    Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Serialize,
)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
pub struct ModeName(pub String);

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Debug)]
#[serde(deny_unknown_fields)]
/// The name of a command binding.
pub struct Command(pub Name);

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Debug)]
/// The name of a modifier key.
pub struct Modifier {
    name: Name,
}

#[derive(Eq, PartialEq, PartialOrd, Ord, Clone, Copy, Debug)]
pub enum SeqType {
    Plain,
    Macro,
    Command,
    Word,
}

impl CEnumVariant for ModeName {
    fn enum_type() -> CCode {
        "Mode".to_c()
    }

    fn underlying_type() -> Option<CCode> {
        Some("uint8_t".to_c())
    }

    fn enum_variant(&self) -> CCode {
        self.to_c()
    }
}

impl Validate for ModeName {
    fn validate(&self) -> Result<(), Error> {
        // TODO check if contains chars other than a-zA-Z_
        Ok(())
    }
}

impl Default for ModeName {
    fn default() -> Self {
        ModeName("default_mode".into())
    }
}

impl fmt::Display for ModeName {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl<'a> From<&'a str> for ModeName {
    fn from(s: &str) -> Self {
        ModeName(s.to_owned())
    }
}

impl From<String> for ModeName {
    fn from(s: String) -> Self {
        ModeName(s)
    }
}

impl Command {
    pub fn name(&self) -> &Name {
        &self.0
    }
}

impl CEnumVariant for Command {
    fn enum_type() -> CCode {
        "Command".to_c()
    }

    fn underlying_type() -> Option<CCode> {
        Some("uint8_t".to_c())
    }

    fn enum_variant(&self) -> CCode {
        self.name().to_c()
    }
}

impl Validate for Command {
    fn validate(&self) -> Result<(), Error> {
        // TODO check if it starts with "command_"?
        self.0.validate()
    }
}
impl Modifier {
    pub fn new(name: &Name) -> Self {
        Modifier {
            name: name.to_owned(),
        }
    }
}

impl CEnumVariant for Modifier {
    fn enum_type() -> CCode {
        "Mod".to_c()
    }

    fn underlying_type() -> Option<CCode> {
        Some("uint8_t".to_c())
    }

    fn enum_variant(&self) -> CCode {
        (&self.name).to_c()
    }
}

impl CEnumVariant for SeqType {
    /// The type name of C++ enum
    fn enum_type() -> CCode {
        "SeqType".to_c()
    }

    /// The variant name of this SeqType in the C++ enum
    fn enum_variant(&self) -> CCode {
        // self.to_c().to_uppercase()
        self.to_c()
    }

    /// The underlying type determining the size of the C++ enum
    fn underlying_type() -> Option<CCode> {
        Some("uint8_t".to_c())
    }
}

impl fmt::Display for SeqType {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let s = match *self {
            SeqType::Plain => "Plain",
            SeqType::Macro => "Macro",
            SeqType::Command => "Command",
            SeqType::Word => "Word",
        };
        fmt::Display::fmt(s, f)
    }
}
