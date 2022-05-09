use std::fmt;

use error::Error;
use types::{CEnumVariant, CIdent, CType, Name, Validate};

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
    fn enum_type() -> CIdent {
        "Mode".into()
    }

    fn underlying_type() -> Option<CType> {
        Some(CType::U8)
    }

    fn enum_variant(&self) -> CIdent {
        CIdent(self.0.to_owned())
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

impl From<ModeName> for String {
    fn from(m: ModeName) -> Self {
        m.0
    }
}

impl<'a> From<&'a ModeName> for String {
    fn from(m: &'a ModeName) -> Self {
        m.0.to_owned()
    }
}

impl Command {
    pub fn name(&self) -> &Name {
        &self.0
    }
}

impl CEnumVariant for Command {
    fn enum_type() -> CIdent {
        "Command".into()
    }

    fn underlying_type() -> Option<CType> {
        Some(CType::U8)
    }

    fn enum_variant(&self) -> CIdent {
        CIdent(self.name().to_string())
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
    fn enum_type() -> CIdent {
        "Mod".into()
    }

    fn underlying_type() -> Option<CType> {
        Some(CType::U8)
    }

    fn enum_variant(&self) -> CIdent {
        CIdent(self.name.to_string())
    }
}

impl CEnumVariant for SeqType {
    /// The type name of C++ enum
    fn enum_type() -> CIdent {
        "SeqType".into()
    }

    /// The variant name of this SeqType in the C++ enum
    fn enum_variant(&self) -> CIdent {
        CIdent(self.to_string())
    }

    /// The underlying type determining the size of the C++ enum
    fn underlying_type() -> Option<CType> {
        Some(CType::U8)
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
