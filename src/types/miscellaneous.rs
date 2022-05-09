// A bunch of small, miscellaneous types that don't deserve their own files

use std::collections::BTreeMap;
use std::fmt::Debug;

use error::Error;
use types::{
    CIdent, Chord, ChordSpec, KmapOrder, ModeName, Name, SeqMap, SpellingTable,
    Validate, WordSpacePosition,
};

#[derive(Deserialize, Debug, Clone, Copy)]
pub enum BoardName {
    #[serde(rename = "TEENSY_LC")]
    TeensyLC,
}

#[derive(Debug, Clone)]
pub struct TutorData {
    pub chords: BTreeMap<ModeName, BTreeMap<Name, Chord<KmapOrder>>>,
    pub word_sequences: SeqMap,
    pub spellings: SpellingTable,
    pub chord_spec: ChordSpec,
    pub word_space_position: WordSpacePosition,
}

impl Into<CIdent> for BoardName {
    fn into(self) -> CIdent {
        CIdent(
            match self {
                BoardName::TeensyLC => "TEENSY_LC",
            }
            .to_string(),
        )
    }
}

impl Validate for BoardName {
    fn validate(&self) -> Result<(), Error> {
        Ok(())
    }
}
