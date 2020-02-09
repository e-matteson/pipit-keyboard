use serde::de::{self, Deserialize, Deserializer, SeqAccess, Visitor};
use std::collections::{BTreeMap, BTreeSet};
use std::fmt;
use std::str::FromStr;

use error::{Error, ResultExt};
use types::{
    Command, KeyPress, KmapPath, ModeInfo, ModeName, Name, Sequence, Snippet,
    UserOptions, Validate, Word,
};

validated_struct! {
    #[derive(Deserialize, Debug)]
    #[serde(deny_unknown_fields)]
    pub struct Settings {
        pub options: UserOptions,
        pub modes: BTreeMap<ModeName, ModeInfo>,
        pub plain_modifiers: BTreeMap<Name, KeyPress>,
        pub plain_keys: BTreeMap<Name, KeyPress>,
        pub macros: BTreeMap<Name, Sequence>,
        pub word_modifiers: Vec<Name>,
        pub anagram_modifiers: Vec<Name>,
        pub commands: Vec<Command>,
        pub dictionary: Vec<Word>,
        #[serde(default)]
        pub snippets: Vec<Snippet>,
    }
}

////////////////////////////////////////////////////////////////////////////////

impl Settings {
    pub fn mode_names(&self) -> impl Iterator<Item = &ModeName> {
        self.modes.keys()
    }

    pub fn kmaps(&self) -> BTreeSet<&KmapPath> {
        self.modes
            .values()
            .flat_map(|mode_info| mode_info.kmap_paths())
            .collect()
    }

    pub fn kmaps_with_words(&self) -> BTreeSet<&KmapPath> {
        self.modes
            .values()
            .flat_map(|mode_info| mode_info.keymaps.iter())
            .filter(|kmap_info| kmap_info.use_words)
            .map(|kmap_info| &kmap_info.file)
            .collect()
    }
}

impl<'de> Deserialize<'de> for Sequence {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: Deserializer<'de>,
    {
        // We create a `Visitor` type, with one method for each data type
        // we support.  The deserializer will call the method corresponding
        // to the data that's actually in the file.
        struct SequenceVisitor;

        impl<'de> Visitor<'de> for SequenceVisitor {
            type Value = Sequence;

            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                formatter.write_str("a sequence of keypresses")
            }

            // The deserializer found a string, so handle it.
            fn visit_str<E>(self, value: &str) -> Result<Sequence, E>
            where
                E: de::Error,
            {
                Sequence::from_str(value).map_err(|error| {
                    // TODO figure out a proper way to get error info
                    // into de::Error
                    println!("{}", error);
                    de::Error::custom("invalid sequence string")
                })
            }

            fn visit_seq<A>(self, mut seq: A) -> Result<Self::Value, A::Error>
            where
                A: SeqAccess<'de>,
            {
                let mut values = Vec::new();

                while let Some(value) = seq.next_element()? {
                    values.push(value)
                }

                Ok(Sequence(values))
            }
        }
        deserializer.deserialize_seq(SequenceVisitor)
    }
}
