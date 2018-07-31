use serde_yaml;
use std::collections::BTreeMap;
use std::path::PathBuf;

use failure::{Error, ResultExt};
use load::{OptionsConfig, Settings};
use types::{AllChordMaps, AllData, AllSeqMaps, SeqType, Validate};
use util::read_file;

impl AllData {
    pub fn load(settings_path: &PathBuf) -> Result<Self, Error> {
        let data = Self::load_helper(settings_path).with_context(|_| {
            format!("Failed to load settings from file: '{:?}'", settings_path)
        })?;
        println!("Loaded keyboard settings from: {:?}\n", settings_path);
        Ok(data)
    }

    /// Load stuff into AllData
    fn load_helper(settings_path: &PathBuf) -> Result<Self, Error> {
        let settings: Settings =
            serde_yaml::from_str(&read_file(settings_path)?)?;
        settings.validate()?;

        let mut all_data = Self {
            chord_spec: settings.options.chord_spec()?,
            output_directory: settings.options.output_directory.clone(),
            options: settings.options.to_vec()?,

            chords: AllChordMaps::default(),
            sequences: AllSeqMaps::default(),
            word_mods: Vec::new(),
            plain_mods: Vec::new(),
            anagram_mods: Vec::new(),
            modes: BTreeMap::new(),
            huffman_table: None,
            spellings: BTreeMap::new(),
        };

        all_data.load_modes(&settings)?;

        all_data
            .load_chords(&settings.options)
            .context("Failed to load chords")?;

        all_data.load_plains(&settings)?;

        all_data.load_macros(&settings)?;

        all_data
            .load_plain_mods(&settings)
            .context("Failed to load plain mods")?;

        all_data
            .make_spelling_table()
            .context("Failed to make spelling table")?;

        all_data.load_word_mods(&settings);

        all_data.load_anagram_mods(&settings);

        all_data
            .load_dictionary(&settings)
            .context("Failed to load dictionary")?;

        all_data
            .load_commands(&settings)
            .context("Failed to load commands")?;

        all_data
            .set_huffman_table()
            .context("Failed to make table of huffman encodings")?;

        Ok(all_data)
    }

    fn load_modes(&mut self, settings: &Settings) -> Result<(), Error> {
        for (name, info) in &settings.modes {
            self.add_mode(name.to_owned(), info.to_owned())
                .with_context(|_| format!("Failed to load mode: '{}'", name))?;
        }
        Ok(())
    }

    fn load_chords(&mut self, options: &OptionsConfig) -> Result<(), Error> {
        let kmaps: Vec<_> = self.chords.kmap_paths().cloned().collect();

        for kmap in kmaps {
            let named_chords =
                kmap.read(&options.kmap_format).with_context(|_| {
                    format!("Failed to load kmap file: '{}'", kmap)
                })?;

            self.chords.insert_map(named_chords, &kmap)?;
        }
        Ok(())
    }

    fn load_macros(&mut self, settings: &Settings) -> Result<(), Error> {
        self.sequences
            .insert_map(settings.macros.clone(), SeqType::Macro)
            .context("Failed to load macros")?;
        Ok(())
    }

    fn load_plains(&mut self, settings: &Settings) -> Result<(), Error> {
        self.sequences
            .insert_map(settings.plain_keys.clone(), SeqType::Plain)
            .context("Failed to load plain keys")?;
        Ok(())
    }

    fn load_plain_mods(&mut self, settings: &Settings) -> Result<(), Error> {
        for (name, keypress) in &settings.plain_modifiers {
            self.add_plain_mod(name.to_owned(), keypress.to_owned())
                .with_context(|_| {
                    format!("Failed to add plain_mod '{}'", name)
                })?;
        }
        Ok(())
    }

    fn load_word_mods(&mut self, settings: &Settings) {
        for name in &settings.word_modifiers {
            self.add_word_mod(name.to_owned());
        }
    }

    fn load_anagram_mods(&mut self, settings: &Settings) {
        for name in &settings.anagram_modifiers {
            self.add_anagram_mod(name.to_owned());
        }
    }

    fn load_commands(&mut self, settings: &Settings) -> Result<(), Error> {
        for name in &settings.commands {
            self.add_command(name.to_owned()).with_context(|_| {
                format!("Failed to load command: '{}'", name)
            })?;
        }
        Ok(())
    }

    fn load_dictionary(&mut self, settings: &Settings) -> Result<(), Error> {
        for kmap in &self.get_kmaps_with_words() {
            for info in &settings.dictionary {
                self.add_word(info, kmap).with_context(|_| {
                    format!("Failed to add word: {}", info.word)
                })?
            }
        }
        Ok(())
    }
}
