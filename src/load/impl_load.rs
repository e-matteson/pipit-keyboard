// use std::collections::BTreeMap;
use std::io::prelude::*;
use std::fs::File;
use toml;

#[allow(unused_imports)]
use load::{KmapParser, Settings, OptionsConfig};
use types::{Maps, SeqType};
use types::errors::*;


impl Maps {
    pub fn load(toml_path: &str) -> Result<Maps> {
        Ok(Maps::load_helper(toml_path).chain_err(
            || format!("failure to load from settings: {}", toml_path),
        )?)
    }

    fn load_helper(toml_path: &str) -> Result<Maps> {
        /// Load stuff into Maps

        let settings: Settings = toml::from_str(&read_file(toml_path)?)?;


        let mut maps = Maps::new();

        maps.load_modes(&settings).chain_err(|| "failure to load modes")?;

        maps.load_options(&settings.options)
            .chain_err(|| "failure to load options")?;

        maps.load_chords(&settings.options)
            .chain_err(|| "failure to load chords")?;

        maps.load_plains(&settings)
            .chain_err(|| "failure to load plain keys")?;

        maps.load_macros(&settings)
            .chain_err(|| "failure to load macros")?;

        maps.load_plain_mods(&settings)
            .chain_err(|| "failure to load plain modifiers")?;

        maps.load_word_mods(&settings)
            .chain_err(|| "failure to load word modifiers")?;

        maps.load_anagram_mods(&settings)
            .chain_err(|| "failure to load anagram modifiers")?;

        maps.load_word_list(&settings) // TODO rename word_list?
            .chain_err(|| "failure to load dictionary")?;

        maps.load_commands(&settings)
            .chain_err(|| "failure to load commands")?;
        Ok(maps)
    }

    fn load_modes(&mut self, settings: &Settings) -> Result<()> {
        // TODO map?
        for (name, info) in &settings.modes {
            self.add_mode(name, info)?;
        }
        Ok(())
    }

    fn load_chords(&mut self, options: &OptionsConfig) -> Result<()> {
        let mut kmap_parser = KmapParser::new(
            &options.kmap_format,
            &options.row_pins,
            &options.column_pins,
        )?;
        for kmap in self.get_kmap_paths() {
            let named_chords = kmap_parser
                .parse(&kmap)
                .chain_err(|| format!("failure to load kmap: '{}'", kmap))?;
            self.add_chords(&kmap, named_chords)?;
        }
        Ok(())
    }

    fn load_options(&mut self, options: &OptionsConfig) -> Result<()> {
        let ops = options.to_vec();
        self.new_options = ops;
        Ok(())
    }

    fn load_macros(&mut self, settings: &Settings) -> Result<()> {
        self.add_sequences(SeqType::Macro, &settings.macros)
    }

    fn load_plains(&mut self, settings: &Settings) -> Result<()> {
        self.add_sequences(SeqType::Plain, &settings.plain_keys)
    }

    fn load_plain_mods(&mut self, settings: &Settings) -> Result<()> {
        for (name, seq) in &settings.plain_modifiers {
            self.add_plain_mod(name, seq)?;
        }
        Ok(())
    }

    fn load_word_mods(&mut self, settings: &Settings) -> Result<()> {
        for name in &settings.other.word_modifiers {
            self.add_word_mod(name)?;
        }
        Ok(())
    }

    fn load_anagram_mods(&mut self, settings: &Settings) -> Result<()> {
        for name in &settings.other.anagram_modifiers {
            self.add_anagram_mod(name)?;
        }
        Ok(())
    }

    fn load_commands(&mut self, settings: &Settings) -> Result<()> {
        // TODO use set sequences, and then process after?
        for name in &settings.other.commands {
            self.add_command(name)?;
        }
        Ok(())
    }

    fn load_word_list(&mut self, settings: &Settings) -> Result<()> {
        for kmap in &self.get_kmaps_with_words() {
            for info in &settings.other.dictionary {
                self.add_word(info.to_owned().into(), kmap)?
            }
        }
        Ok(())
    }
}

fn read_file(path: &str) -> Result<String> {
    let mut f: File = File::open(path)?;
    let mut buffer = String::new();
    f.read_to_string(&mut buffer)?;
    Ok(buffer)
}
