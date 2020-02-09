use std::fmt::{self, Debug};

use error::Error;
use types::Validate;

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ModeInfo {
    pub keymaps: Vec<KmapInfo>,
    #[serde(default = "return_false")]
    pub gaming: bool,
}

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapInfo {
    pub file: KmapPath,
    #[serde(default = "return_false")]
    pub use_words: bool,
}

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapPath(pub String);

impl ModeInfo {
    pub fn kmap_paths(&self) -> impl Iterator<Item = &KmapPath> {
        self.keymaps.iter().map(|info| &info.file)
    }
}

impl Validate for ModeInfo {
    fn validate(&self) -> Result<(), Error> {
        for kmap in &self.keymaps {
            kmap.validate()?;
        }
        Ok(())
    }
}

impl Validate for KmapInfo {
    fn validate(&self) -> Result<(), Error> {
        self.file.validate()
    }
}

impl Validate for KmapPath {
    fn validate(&self) -> Result<(), Error> {
        // TODO check if path exists and has .kmap extension?
        Ok(())
    }
}

impl Into<String> for KmapPath {
    fn into(self) -> String {
        self.0
    }
}

impl<'a> Into<String> for &'a KmapPath {
    fn into(self) -> String {
        self.to_owned().into()
    }
}

impl<'a> Into<KmapPath> for &'a KmapPath {
    fn into(self) -> KmapPath {
        self.to_owned()
    }
}

impl fmt::Display for KmapPath {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

fn return_false() -> bool {
    false
}
