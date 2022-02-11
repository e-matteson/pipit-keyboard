use std::fmt::{self, Debug};

use error::Error;
use types::{SnippetListName, Validate, WordListName};

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ModeInfo {
    pub layers: Vec<LayerName>,
    #[serde(default = "return_false")]
    pub gaming: bool,
}

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize, Debug)]
#[serde(deny_unknown_fields)]
#[serde(from = "String")]
pub struct LayerName(pub String);

#[derive(Clone, Debug, Deserialize)]
#[serde(deny_unknown_fields)]
#[serde(tag = "type")]
pub enum LayerInfo {
    /// Uses the KmapPath to generate the word chords and adds those words to
    /// the lookup table. But it doesn't add the mapping names in KmapPath to
    /// the lookup table.
    WordLayer {
        word_list_name: WordListName,
        kmap_file_for_chord_generation: KmapPath,
    },
    /// Same as WordLayer but for snippets.
    SnippetLayer {
        snippet_list_name: SnippetListName,
        kmap_file_for_chord_generation: KmapPath,
    },
    /// Add the mapping names in KmapPath to the lookup table.
    KmapLayer { kmap_file: KmapPath },
}

#[derive(Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct KmapPath(pub String);

impl Validate for ModeInfo {
    fn validate(&self) -> Result<(), Error> {
        for layer_name in &self.layers {
            layer_name.validate()?;
        }
        Ok(())
    }
}

impl Validate for LayerName {
    fn validate(&self) -> Result<(), Error> {
        if self.0.is_empty() {
            Err(Error::BadValueErr {
                thing: "layer name".to_owned(),
                value: "(empty)".to_owned(),
            })
        } else {
            Ok(())
        }
    }
}
impl Validate for LayerInfo {
    fn validate(&self) -> Result<(), Error> {
        match self {
            LayerInfo::KmapLayer { kmap_file } => kmap_file.validate(),
            LayerInfo::WordLayer {
                kmap_file_for_chord_generation,
                ..
            } => kmap_file_for_chord_generation.validate(),
            LayerInfo::SnippetLayer {
                kmap_file_for_chord_generation,
                ..
            } => kmap_file_for_chord_generation.validate(),
        }
    }
}

impl Validate for KmapPath {
    fn validate(&self) -> Result<(), Error> {
        // TODO check if path exists and has .kmap extension?
        Ok(())
    }
}

impl From<String> for LayerName {
    fn from(s: String) -> Self {
        LayerName(s)
    }
}

impl Into<String> for LayerName {
    fn into(self) -> String {
        self.0
    }
}

impl fmt::Display for LayerName {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
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
