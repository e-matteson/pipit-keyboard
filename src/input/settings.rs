use std::collections::BTreeMap;

use error::{Error, ResultExt};
use types::{
    Command, KeyPress, LayerInfo, LayerName, ModeInfo, ModeName, Name,
    Sequence, Snippet, SnippetListName, UserOptions, Validate, Word,
    WordListName,
};

validated_struct! {
    #[derive(Deserialize, Debug)]
    #[serde(deny_unknown_fields)]
    pub struct Settings {
        pub options: UserOptions,
        pub layers: BTreeMap<LayerName, LayerInfo>,
        pub modes: BTreeMap<ModeName, ModeInfo>,
        pub plain_modifiers: BTreeMap<Name, KeyPress>,
        pub plain_keys: BTreeMap<Name, KeyPress>,
        pub macros: BTreeMap<Name, Sequence>,
        pub word_modifiers: Vec<Name>,
        pub anagram_modifiers: Vec<Name>,
        pub commands: Vec<Command>,
        pub word_lists: BTreeMap<WordListName, Vec<Word>>,

        #[serde(default)]
        pub snippets: BTreeMap<SnippetListName, Vec<Snippet>>,
    }
}

////////////////////////////////////////////////////////////////////////////////

impl Settings {
    pub fn mode_names(&self) -> impl Iterator<Item = &ModeName> {
        self.modes.keys()
    }

    pub fn validate_layer_list(&self) -> Result<(), Error> {
        for (mode_name, mode_info) in &self.modes {
            for layer_name in &mode_info.layers {
                if !self.layers.contains_key(layer_name) {
                    Err(Error::LookupErr {
                        key: layer_name.to_string(),
                        container: "layer definitions".into(),
                    })
                    .with_context(|| {
                        format!(
                            "Invalid layer name in mode: '{}'",
                            mode_name.to_string()
                        )
                    })?;
                }
            }
        }
        Ok(())
    }
}
