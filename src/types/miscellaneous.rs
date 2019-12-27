// A bunch of small, miscellaneous types that don't deserve their own files

use std::collections::BTreeMap;
use std::fmt::Debug;

use error::Error;
use types::{
    CCode, Chord, ChordSpec, KmapOrder, ModeName, Name, SpellingTable, ToC,
    Validate,
};

#[derive(Deserialize, Debug, Clone, Copy)]
pub enum BoardName {
    #[serde(rename = "TEENSY_LC")]
    TeensyLC,
}

#[derive(Debug, Clone)]
pub struct TutorData {
    pub chords: BTreeMap<ModeName, BTreeMap<Name, Chord<KmapOrder>>>,
    pub spellings: SpellingTable,
    pub chord_spec: ChordSpec,
}

impl ToC for BoardName {
    fn to_c(self) -> CCode {
        match self {
            BoardName::TeensyLC => "TEENSY_LC".to_c(),
        }
    }
}

impl Validate for BoardName {
    fn validate(&self) -> Result<(), Error> {
        Ok(())
    }
}
