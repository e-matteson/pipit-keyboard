use std::collections::{BTreeMap, BTreeSet};

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

