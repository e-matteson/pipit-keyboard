use std::collections::{BTreeMap, BTreeSet};
use std::path::PathBuf;

use itertools::Itertools;
use serde_yaml;

use input::Settings;

use error::{Error, ResultExt};
use types::{
    AllChordMaps, AllData, AllSeqMaps, CCode, CEnumVariant, Chord, Command,
    HuffmanTable, KeyDefs, KeyPress, KmapPath, ModeInfo, ModeName, Name,
    SeqType, Sequence, SpellingTable, Validate, Word,
};
use util::read_file;

/// This handles all the details of building an AllData struct from
/// configuration files. It loads sequences and chords, generates word chords,
/// generates huffman encodings, and so on.
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
    /// Read the contents of the given settings file, and return a
    /// AllDataBuilder that's prepared to build an AllData struct.
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

    /// Attempt to build an AllData struct, using the settings file that was
    /// passed to `load()`.
    pub fn finalize(mut self) -> Result<AllData, Error> {
        // The order of these calls matters! Some depend on data loaded in
        // previous ones.
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

        let command_variants =
            self.load_commands().context("Failed to load commands")?;

        Ok(AllData {
            huffman_table: self.make_huffman_table()?,
            chord_spec: self.settings.options.chord_spec()?,
            options: self.settings.options.to_vec()?,
            output_directory: self.settings.options.output_directory,
            commands: command_variants.into_iter().collect(),

            board: self.settings.options.board_name,
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
        // Get the names of all the kmap files we found when calling
        // `load_modes()`
        let kmaps: Vec<_> = self.chords.kmap_paths().cloned().collect();
        let kmap_format = self.settings.options.kmap_format.clone();

        for kmap in kmaps {
            let named_chords = kmap.read(&kmap_format).with_context(|| {
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

    /// In addition to loading commands from the settings file, automatically
    /// create command bindings for switching to every mode (eg.
    /// "command_switch_to_default_mode"). This means you don't need to manually
    /// list mode-switching commands in the settings file, or more importantly,
    /// in the firmware's `Command` enum or `Pipit::doCommand()`. Otherwise,
    /// deleting modes in the settings file would cause a firmware compilation
    /// error, because `doCommand()` would reference an unknown `Command`
    /// variant. Instead, we store mode-switching commands in the lookup using a
    /// single `Command::command_switch_to` variant, followed by a mode
    /// argument.
    fn load_commands(&mut self) -> Result<BTreeSet<Command>, Error> {
        let mut variants = BTreeSet::new();
        for normal_command in self.settings.commands.clone() {
            variants.insert(normal_command.clone());
            self.add_command(
                normal_command.name().to_owned(),
                normal_command,
                &[],
            ).context("Failed to add command")?;
        }

        let modes = { self.modes.keys().cloned().collect::<Vec<ModeName>>() };
        let base_name = "command_switch_to";
        let variant = Command(base_name.into());
        variants.insert(variant.clone());
        for mode in modes {
            let name = Name::from(format!("{}_{}", base_name, mode));
            self.add_command(
                name,
                variant.clone(),
                &[mode.qualified_enum_variant()],
            ).context("Failed to add mode-switching command")?;
        }

        Ok(variants)
    }

    fn load_dictionary(
        &mut self,
        spellings: &SpellingTable,
    ) -> Result<(), Error> {
        let dictionary = self.settings.dictionary.clone();
        for kmap in &self.get_kmaps_with_words() {
            for info in &dictionary {
                self.add_word(info, kmap, spellings).with_context(|| {
                    format!("Failed to add word: {}", info.word)
                })?
            }
        }
        Ok(())
    }

    fn make_spelling_table(&mut self) -> Result<SpellingTable, Error> {
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

    fn make_huffman_table(&mut self) -> Result<HuffmanTable, Error> {
        Ok(HuffmanTable::new(self.sequences.dump_all_keypresses())
            .context("Failed to make table of huffman encodings")?)
    }

    fn add_mode(
        &mut self,
        mode_name: ModeName,
        info: ModeInfo,
    ) -> Result<(), Error> {
        // Check if a mode with this name has been added already
        if self.modes.contains_key(&mode_name) {
            return Err(Error::ConflictErr {
                key: mode_name.into(),
                container: "modes".to_owned(),
            }).context("Mode has already been added");
        }

        // Initialize the kmaps that are included in this mode
        for kmap_info in &info.keymaps {
            self.chords.init_kmap(&kmap_info.file);
        }

        self.modes.insert(mode_name, info);
        Ok(())
    }

    fn add_plain_mod(
        &mut self,
        name: Name,
        key_press: KeyPress,
    ) -> Result<(), Error> {
        KeyDefs::ensure_plain_mod(&key_press)?;
        self.plain_mods.push(name.clone());
        self.sequences
            .insert(name, key_press.into(), SeqType::Plain)
    }

    /// Create a sequence for this command. The command variants will be
    /// collected separately.
    fn add_command(
        &mut self,
        name: Name,
        variant: Command,
        args: &[CCode],
    ) -> Result<(), Error> {
        // Commands don't have actual key sequences, just a byte containing an
        // enum value, and maybe some extra bytes as argument. But we'll
        // store them as Sequences for convenience.
        let mut fake_seq: Sequence =
            KeyPress::new_fake(variant.qualified_enum_variant()).into();
        for arg in args {
            fake_seq.push(KeyPress::new_fake(arg.to_owned()))
        }

        self.sequences.insert(name, fake_seq, SeqType::Command)
    }

    fn add_word(
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
            }).expect("no chords spellings to intersect")?;
        // TODO see if that expect is triggered by an empty word chord

        chord.anagram_num = word.anagram_num();
        self.chords.insert(name, chord, kmap)
    }

    fn add_word_mod(&mut self, name: Name) {
        self.word_mods.push(name);
    }

    fn add_anagram_mod(&mut self, name: Name) {
        self.anagram_mods.push(name);
    }

    fn get_kmaps_with_words(&self) -> Vec<KmapPath> {
        let mut out = BTreeSet::new();
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
