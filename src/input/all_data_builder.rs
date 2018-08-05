use std::collections::{BTreeMap, HashSet};
use std::path::PathBuf;

use itertools::Itertools;
use serde_yaml;

use failure::{Error, ResultExt};
use input::Settings;
use types::errors::ConflictErr;

use types::{
    AllChordMaps, AllData, AllSeqMaps, Chord, HuffmanTable, KeyDefs, KeyPress,
    KmapPath, ModeInfo, ModeName, Name, SeqType, SpellingTable, Validate, Word,
};
use util::read_file;

pub struct AllDataBuilder {
    settings: Settings,
    chords: AllChordMaps,
    sequences: AllSeqMaps,
    word_mods: Vec<Name>,
    plain_mods: Vec<Name>,
    anagram_mods: Vec<Name>,
    modes: BTreeMap<ModeName, ModeInfo>,
}

impl AllDataBuilder {
    pub fn load(settings_path: &PathBuf) -> Result<Self, Error> {
        let settings: Settings =
            serde_yaml::from_str(&read_file(settings_path)?)?;
        settings.validate()?;

        Ok(Self {
            settings,
            chords: AllChordMaps::default(),
            sequences: AllSeqMaps::default(),
            word_mods: Vec::new(),
            plain_mods: Vec::new(),
            anagram_mods: Vec::new(),
            modes: BTreeMap::new(),
        })
    }

    pub fn finalize(mut self) -> Result<AllData, Error> {
        self.load_modes()?;

        self.load_chords().context("Failed to load chords")?;

        self.load_plains()?;

        self.load_macros()?;

        self.load_plain_mods()
            .context("Failed to load plain mods")?;

        self.make_spelling_table()
            .context("Failed to make spelling table")?;

        self.load_word_mods();

        self.load_anagram_mods();

        let spellings = self.make_spelling_table()?;

        self.load_dictionary(&spellings)
            .context("Failed to load dictionary")?;

        self.load_commands().context("Failed to load commands")?;

        Ok(AllData {
            huffman_table: self.make_huffman_table()?,
            chord_spec: self.settings.options.chord_spec()?,
            options: self.settings.options.to_vec()?,
            output_directory: self.settings.options.output_directory,

            chords: self.chords,
            sequences: self.sequences,
            word_mods: self.word_mods,
            plain_mods: self.plain_mods,
            anagram_mods: self.anagram_mods,
            modes: self.modes,
            spellings,
        })
    }

    fn load_modes(&mut self) -> Result<(), Error> {
        let modes = self.settings.modes.clone();
        for (name, info) in modes {
            self.add_mode(name, info)?;
        }
        Ok(())
    }

    fn load_chords(&mut self) -> Result<(), Error> {
        let kmaps: Vec<_> = self.chords.kmap_paths().cloned().collect();
        let kmap_format = self.settings.options.kmap_format.clone();

        for kmap in kmaps {
            let named_chords = kmap.read(&kmap_format).with_context(|_| {
                format!("Failed to load kmap file: '{}'", kmap)
            })?;

            self.chords.insert_map(named_chords, &kmap)?;
        }
        Ok(())
    }

    fn load_macros(&mut self) -> Result<(), Error> {
        let macros = self.settings.macros.clone();
        self.sequences
            .insert_map(macros, SeqType::Macro)
            .context("Failed to load macros")?;
        Ok(())
    }

    fn load_plains(&mut self) -> Result<(), Error> {
        let plain_keys = self.settings.plain_keys.clone();
        self.sequences
            .insert_map(plain_keys, SeqType::Plain)
            .context("Failed to load plain keys")?;
        Ok(())
    }

    fn load_plain_mods(&mut self) -> Result<(), Error> {
        let plain_mods = self.settings.plain_modifiers.clone();
        for (name, keypress) in plain_mods {
            self.add_plain_mod(name, keypress)
                .context("Failed to add plain_mod")?;
        }
        Ok(())
    }

    fn load_word_mods(&mut self) {
        let word_mods = self.settings.word_modifiers.clone();
        for name in word_mods {
            self.add_word_mod(name);
        }
    }

    fn load_anagram_mods(&mut self) {
        let anagram_mods = self.settings.anagram_modifiers.clone();
        for name in anagram_mods {
            self.add_anagram_mod(name);
        }
    }

    fn load_commands(&mut self) -> Result<(), Error> {
        let commands = self.settings.commands.clone();
        for name in commands {
            self.add_command(name).context("Failed to load command")?;
        }
        Ok(())
    }

    fn load_dictionary(
        &mut self,
        spellings: &SpellingTable,
    ) -> Result<(), Error> {
        let dictionary = self.settings.dictionary.clone();
        for kmap in &self.get_kmaps_with_words() {
            for info in &dictionary {
                self.add_word(info, kmap, spellings).with_context(|_| {
                    format!("Failed to add word: {}", info.word)
                })?
            }
        }
        Ok(())
    }

    pub fn make_spelling_table(&mut self) -> Result<SpellingTable, Error> {
        let mut table = BTreeMap::new();
        {
            let plain_names = self
                .sequences
                .get_seq_map(SeqType::Plain)?
                .names()
                .chain(self.plain_mods.iter());

            for name in plain_names {
                let keypress = self
                    .sequences
                    .get_seq_of_any_type(name)?
                    .lone_keypress()?;
                if let Some(spelling) =
                    KeyDefs::spelling_from_keypress(&keypress)?
                {
                    table.insert(spelling, name.to_owned());
                }
            }
        }
        Ok(SpellingTable(table))
    }

    pub fn make_huffman_table(&mut self) -> Result<HuffmanTable, Error> {
        Ok(HuffmanTable::new(self.sequences.dump_all_keypresses())
            .context("Failed to make table of huffman encodings")?)
    }

    pub fn add_mode(
        &mut self,
        mode_name: ModeName,
        info: ModeInfo,
    ) -> Result<(), Error> {
        // Check if a mode with this name has been added already
        if self.modes.contains_key(&mode_name) {
            Err(ConflictErr {
                key: mode_name.to_string(),
                container: "modes".into(),
            }).context("Mode has already been added")?;
        }

        // Initialize the kmaps that are included in this mode
        for kmap_info in &info.keymaps {
            self.chords.init_kmap(&kmap_info.file);
        }

        self.modes.insert(mode_name, info);
        Ok(())
    }

    pub fn add_plain_mod(
        &mut self,
        name: Name,
        key_press: KeyPress,
    ) -> Result<(), Error> {
        KeyDefs::ensure_plain_mod(&key_press)?;
        self.plain_mods.push(name.clone());
        self.sequences
            .insert(name, key_press.into(), SeqType::Plain)
    }

    pub fn add_command(&mut self, command_name: Name) -> Result<(), Error> {
        // Commands are a single byte code, not an actual key sequence.
        // But we'll store each one as a "fake" KeyPress for convenience.
        let fake_keypress = KeyPress::new_fake(&command_name.to_uppercase());

        self.sequences.insert(
            command_name,
            fake_keypress.into(),
            SeqType::Command,
        )
    }

    pub fn add_word(
        &mut self,
        word: &Word,
        kmap: &KmapPath,
        spelling_table: &SpellingTable,
    ) -> Result<(), Error> {
        let name = word.name();

        self.sequences
            .insert(name.clone(), word.sequence()?, SeqType::Word)?;

        // Get chords for each letter in the word and combine them.
        // This is messy and doesn't short-circuit on the first error, but
        // there's no fold1_result(), and this will get refactored away when we
        // add internationalization, so whatever.
        let mut chord: Chord = word
            .chord_spellings()?
            .iter()
            .map(|spelling| {
                let name = spelling_table.get_checked(spelling)?;
                self.chords.get(&name, kmap)
            }).fold1(|a, b| {
                if a.is_err() {
                    a
                } else if b.is_err() {
                    b
                } else {
                    Ok(a.unwrap().intersect(&b.unwrap()))
                }
            }).ok_or_else(|| format_err!("no chords to intersect"))??;

        chord.anagram_num = word.anagram_num();
        self.chords.insert(name, chord, kmap)
    }

    pub fn add_word_mod(&mut self, name: Name) {
        self.word_mods.push(name);
    }

    pub fn add_anagram_mod(&mut self, name: Name) {
        self.anagram_mods.push(name);
    }

    pub fn get_kmaps_with_words(&self) -> Vec<KmapPath> {
        let mut out = HashSet::new();
        for mode_info in self.settings.modes.values() {
            for kmap_info in &mode_info.keymaps {
                if kmap_info.use_words {
                    out.insert(kmap_info.file.clone());
                }
            }
        }
        out.into_iter().collect()
    }
}
