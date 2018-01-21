use std::io::prelude::*;
use std::fs::File;
use toml;

use load::{parse_kmap, OptionsConfig, Settings};
use types::{AllData, Chord, SeqType, Validate};
// use types::errors::*;
use failure::{Error, ResultExt};

impl AllData {
    pub fn load(toml_path: &str) -> Result<AllData, Error> {
        Ok(AllData::load_helper(toml_path).with_context(|_| {
            format!("Failed to load settings from file: '{}'", toml_path)
        })?)
    }

    fn load_helper(toml_path: &str) -> Result<AllData, Error> {
        /// Load stuff into AllData
        let settings: Settings = toml::from_str(&read_file(toml_path)?)?;
        settings.validate()?;

        let mut all_data = AllData::new();

        all_data.output_directory = Some(settings.options.output_directory());
        all_data.tutor_directory = Some(settings.options.tutor_directory());

        Chord::set_info(settings.options.global_chord_info()?);

        all_data
            .load_modes(&settings)
            .with_context(|_| "Failed to load modes")?;

        all_data
            .load_options(&settings.options)
            .with_context(|_| "Failed to load options")?;

        all_data
            .load_chords(&settings.options)
            .with_context(|_| "Failed to load chords")?;

        all_data
            .load_plains(&settings)
            .with_context(|_| "Failed to load plain keys")?;

        all_data
            .load_macros(&settings)
            .with_context(|_| "Failed to load macros")?;

        all_data
            .load_plain_mods(&settings)
            .with_context(|_| "Failed to load plain modifiers")?;

        all_data
            .load_word_mods(&settings)
            .with_context(|_| "Failed to load word modifiers")?;

        all_data
            .load_anagram_mods(&settings)
            .with_context(|_| "Failed to load anagram modifiers")?;

        // TODO rename word_list?
        all_data
            .load_word_list(&settings)
            .with_context(|_| "Failed to load dictionary")?;

        all_data
            .load_commands(&settings)
            .with_context(|_| "Failed to load commands")?;

        all_data.set_huffman_table();

        Ok(all_data)
    }

    fn load_modes(&mut self, settings: &Settings) -> Result<(), Error> {
        // TODO map?
        for (name, info) in &settings.modes {
            self.add_mode(name, info)?;
        }
        Ok(())
    }

    fn load_chords(&mut self, options: &OptionsConfig) -> Result<(), Error> {
        for kmap in self.get_kmap_paths() {
            let named_chords = parse_kmap(&kmap, &options.kmap_format)
                .with_context(|_| {
                    format!("Failed to load kmap from file: '{}'", kmap)
                })?;
            self.add_chords(&kmap, named_chords)?;
        }
        Ok(())
    }

    fn load_options(&mut self, options: &OptionsConfig) -> Result<(), Error> {
        self.options = options.to_vec();
        Ok(())
    }

    fn load_macros(&mut self, settings: &Settings) -> Result<(), Error> {
        self.add_sequences(SeqType::Macro, &settings.macros)
    }

    fn load_plains(&mut self, settings: &Settings) -> Result<(), Error> {
        self.add_sequences(SeqType::Plain, &settings.plain_keys)
    }

    fn load_plain_mods(&mut self, settings: &Settings) -> Result<(), Error> {
        for (name, seq) in &settings.plain_modifiers {
            self.add_plain_mod(name, seq)?;
        }
        Ok(())
    }

    fn load_word_mods(&mut self, settings: &Settings) -> Result<(), Error> {
        for name in &settings.other.word_modifiers {
            self.add_word_mod(name)?;
        }
        Ok(())
    }

    fn load_anagram_mods(&mut self, settings: &Settings) -> Result<(), Error> {
        for name in &settings.other.anagram_modifiers {
            self.add_anagram_mod(name)?;
        }
        Ok(())
    }

    fn load_commands(&mut self, settings: &Settings) -> Result<(), Error> {
        // TODO use set sequences, and then process after?
        for name in &settings.other.commands {
            self.add_command(name)?;
        }
        Ok(())
    }

    fn load_word_list(&mut self, settings: &Settings) -> Result<(), Error> {
        for kmap in &self.get_kmaps_with_words() {
            for info in &settings.other.dictionary {
                self.add_word(info.to_owned(), kmap)?
            }
        }
        Ok(())
    }
}

fn read_file(path: &str) -> Result<String, Error> {
    let mut f: File = File::open(path)?;
    let mut buffer = String::new();
    f.read_to_string(&mut buffer)?;
    Ok(buffer)
}
