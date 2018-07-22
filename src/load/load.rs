use serde_yaml;
use std::path::PathBuf;

use failure::{Error, ResultExt};
use load::{parse_kmap, OptionsConfig, Settings};
use types::{AllData, Chord, SeqType, Validate};
use util::read_file;

impl AllData {
    pub fn load(settings_path: &PathBuf) -> Result<AllData, Error> {
        let data = AllData::load_helper(settings_path).with_context(|_| {
            format!("Failed to load settings from file: '{:?}'", settings_path)
        })?;
        println!("Loaded keyboard settings from: {:?}\n", settings_path);
        Ok(data)
    }

    /// Load stuff into AllData
    fn load_helper(settings_path: &PathBuf) -> Result<AllData, Error> {
        let settings: Settings =
            serde_yaml::from_str(&read_file(settings_path)?)?;
        settings.validate()?;

        let mut all_data = AllData::new();

        all_data.output_directory = Some(settings.options.output_directory());

        Chord::set_info(settings.options.static_chord_info()?);

        all_data
            .load_modes(&settings)
            .context("Failed to load modes")?;

        all_data
            .load_options(&settings.options)
            .context("Failed to load options")?;

        all_data
            .load_chords(&settings.options)
            .context("Failed to load chords")?;

        all_data
            .load_plains(&settings)
            .context("Failed to load plain keys")?;

        all_data
            .load_macros(&settings)
            .context("Failed to load macros")?;

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
            self.add_mode(name, info)
                .with_context(|_| format!("Failed to load mode: '{}'", name))?;
        }
        Ok(())
    }

    fn load_chords(&mut self, options: &OptionsConfig) -> Result<(), Error> {
        for kmap in self.get_kmap_paths() {
            let named_chords = parse_kmap(&kmap, &options.kmap_format)
                .with_context(|_| {
                    format!("Failed to load kmap file: '{}'", kmap)
                })?;
            self.add_chords(&kmap, named_chords)?;
        }
        Ok(())
    }

    fn load_options(&mut self, options: &OptionsConfig) -> Result<(), Error> {
        self.options = options.to_vec()?;
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
            self.add_plain_mod(name, seq).with_context(|_| {
                format!("Failed to add plain_mod '{}'", name)
            })?;
        }
        Ok(())
    }

    fn load_word_mods(&mut self, settings: &Settings) {
        for name in &settings.word_modifiers {
            self.add_word_mod(name);
        }
    }

    fn load_anagram_mods(&mut self, settings: &Settings) {
        for name in &settings.anagram_modifiers {
            self.add_anagram_mod(name);
        }
    }

    fn load_commands(&mut self, settings: &Settings) -> Result<(), Error> {
        for name in &settings.commands {
            self.add_command(name).with_context(|_| {
                format!("Failed to load command: '{}'", name)
            })?;
        }
        Ok(())
    }

    fn load_dictionary(&mut self, settings: &Settings) -> Result<(), Error> {
        for kmap in &self.get_kmaps_with_words() {
            for info in &settings.dictionary {
                self.add_word(info.to_owned(), kmap).with_context(|_| {
                    format!("Failed to add word: {}", info.word)
                })?
            }
        }
        Ok(())
    }
}
