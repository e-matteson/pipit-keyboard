use std::collections::{BTreeMap, HashSet};
use std::clone::Clone;
use std::path::PathBuf;
use itertools::Itertools;

use util::ensure_u8;

use types::{AnagramNum, CTree, Chord, HuffmanTable, KeyDefs, KeyPress,
            KmapPath, ModeInfo, ModeName, Name, SeqType, Sequence, Spelling,
            TutorData, Word};

use types::errors::{BadValueErr, ConflictErr, LookupErr};
use failure::{Error, Fail, ResultExt};

#[derive(Debug)]
pub struct AllData {
    pub chords: BTreeMap<KmapPath, BTreeMap<Name, Chord>>,
    pub sequences: BTreeMap<SeqType, BTreeMap<Name, Sequence>>,
    pub word_mods: Vec<Name>,
    pub plain_mods: Vec<Name>,
    pub anagram_mods: Vec<Name>,
    pub modes: BTreeMap<ModeName, ModeInfo>,
    pub options: Vec<CTree>,
    pub output_directory: Option<PathBuf>,
    pub tutor_directory: Option<PathBuf>,
    pub huffman_table: Option<HuffmanTable>,
    spellings: BTreeMap<Spelling, Name>,
    highest_anagram_num: AnagramNum,
}

impl AllData {
    pub fn new() -> AllData {
        AllData {
            chords: BTreeMap::new(),
            sequences: BTreeMap::new(),
            word_mods: Vec::new(),
            plain_mods: Vec::new(),
            anagram_mods: Vec::new(),
            modes: BTreeMap::new(),
            options: Vec::new(),
            output_directory: None,
            tutor_directory: None,
            huffman_table: None,
            highest_anagram_num: AnagramNum::default(),
            spellings: BTreeMap::new(),
        }
    }

    pub fn add_chords(
        &mut self,
        kmap: &KmapPath,
        named_chords: BTreeMap<Name, Chord>,
    ) -> Result<(), Error> {
        for (name, chord) in &named_chords {
            self.add_chord(name, chord, kmap)?;
        }
        Ok(())
    }

    fn add_chord(
        &mut self,
        name: &Name,
        chord: &Chord,
        kmap: &KmapPath,
    ) -> Result<(), Error> {
        self.chords
            .get_mut(kmap)
            .ok_or_else(|| {
                BadValueErr {
                    thing: "kmap".into(),
                    value: kmap.to_owned().into(),
                }.context("Failed to add chord to kmap")
            })?
            .insert(name.to_owned(), chord.to_owned());
        Ok(())
    }

    pub fn add_command(&mut self, entry: &Name) -> Result<(), Error> {
        // Commands are a single byte code, not an actual key sequence.
        // But we'll store each one as a KeyPress for convenience.
        let mut fake_seq_with_command_code = Sequence::new();

        fake_seq_with_command_code
            .push(KeyPress::new_fake(&entry.to_uppercase()));

        self.add_sequence(SeqType::Command, entry, &fake_seq_with_command_code)
    }

    pub fn add_word(
        &mut self,
        word: Word,
        kmap: &KmapPath,
    ) -> Result<(), Error> {
        let name = word.name();
        self.add_sequence(SeqType::Word, &name, &word.sequence()?)?;

        // Get a chord for each letter in the word, and combine them.
        let chord: Chord = word.chord_spellings()?
            .iter()
            .map(|s| self.chord_from_spelling(s, kmap))
            .fold_results(
                Chord::with_anagram(word.anagram_num()),
                |mut accumulator, ref chord| {
                    accumulator.intersect(chord);
                    accumulator
                },
            )?;

        self.add_chord(&name, &chord, kmap)?;

        if chord.anagram_num > self.highest_anagram_num {
            self.highest_anagram_num = chord.anagram_num;
        }
        Ok(())
    }

    pub fn add_plain_mod<T>(
        &mut self,
        name: &Name,
        seq: &T,
    ) -> Result<(), Error>
    where
        T: Into<Sequence> + Clone,
    {
        // TODO check if sequence is valid! length 1, no key
        self.plain_mods.push(name.to_owned());
        self.add_sequence(SeqType::Plain, name, seq)
    }

    pub fn add_word_mod(&mut self, name: &Name) {
        self.word_mods.push(name.to_owned());
    }

    pub fn add_anagram_mod(&mut self, name: &Name) {
        self.anagram_mods.push(name.to_owned());
    }

    pub fn add_mode(
        &mut self,
        name: &ModeName,
        info: &ModeInfo,
    ) -> Result<(), Error> {
        // Check if a mode with this name has been added already
        if self.modes.contains_key(name) {
            Err(ConflictErr {
                key: name.to_string(),
                container: "modes".into(),
            }).context("Mode has already been added")?;
        }
        // Store the kmaps that are included in this mode
        for kmap_info in &info.keymaps {
            let kmap_path = &kmap_info.file;
            if !self.chords.contains_key(kmap_path) {
                // Initialize new chord map
                self.chords.insert(kmap_path.clone(), BTreeMap::new());
            }
            // Otherwise, kmap was already added by another mode, do nothing.
        }
        self.modes.insert(name.to_owned(), info.to_owned());
        Ok(())
    }

    fn add_sequence<T>(
        &mut self,
        seq_type: SeqType,
        name: &Name,
        seq: &T,
    ) -> Result<(), Error>
    where
        T: Into<Sequence> + Clone,
    {
        let seq = seq.to_owned().into();
        ensure_u8(seq.len()).with_context(|_| {
            format!("Sequence contains too many keypresses: '{}'", name)
        })?;
        self.sequences
            .entry(seq_type)
            .or_insert_with(BTreeMap::new)
            .insert(name.to_owned(), seq);
        Ok(())
    }

    pub fn add_sequences<T>(
        &mut self,
        seq_type: SeqType,
        seqs: &BTreeMap<Name, T>,
    ) -> Result<(), Error>
    where
        T: Into<Sequence> + Clone,
    {
        for (name, seq) in seqs {
            self.add_sequence(seq_type, name, seq)?;
        }
        Ok(())
    }

    // TODO don't take reference to seq_type
    fn get_sequences(
        &self,
        seq_type: &SeqType,
    ) -> Result<&BTreeMap<Name, Sequence>, Error> {
        self.sequences.get(seq_type).ok_or_else(|| {
            LookupErr {
                key: format!("{:?}", seq_type),
                container: "sequences".into(),
            }.context("sequence type was not initialized")
                .into()
        })
    }

    pub fn get_sequence(&self, name: &Name) -> Result<&Sequence, Error> {
        for seq_type in self.sequences.keys() {
            if let Some(s) = self.get_sequences(seq_type)?.get(name) {
                return Ok(s);
            }
        }
        Ok(Err(LookupErr {
            key: name.into(),
            container: "sequences".into(),
        })?)
    }

    pub fn get_chord(
        &self,
        chord_name: &Name,
        kmap: &KmapPath,
    ) -> Option<Chord> {
        // TODO be consistent about argument order
        self.chords[kmap]
            .get(chord_name)
            .and_then(|x| Some(x.clone()))
    }

    // TODO handle missing mods better - here or firmware?
    pub fn get_chord_in_mode(
        &self,
        chord_name: &Name,
        mode: &ModeName,
    ) -> Option<Chord> {
        for kmap_info in &self.modes.get(mode).expect("unknown mode").keymaps {
            if let Some(chord) = self.get_chord(chord_name, &kmap_info.file) {
                return Some(chord);
            }
        }
        None
    }

    pub fn get_anagram_chords(&self, mode: &ModeName) -> Vec<Chord> {
        let mut out = Vec::new();
        for name in &self.anagram_mods {
            // TODO why default? Shouldn't that be an error?
            out.push(self.get_chord_in_mode(name, mode).unwrap_or_default());
        }
        out
    }

    pub fn get_mod_names(&self) -> Vec<Name> {
        let mut names = Vec::new();
        names.extend(self.plain_mods.clone());
        names.extend(self.word_mods.clone());
        names.extend(self.anagram_mods.clone());
        names.sort();
        names
    }

    pub fn get_mod_chords(&self, mode: &ModeName) -> Vec<Chord> {
        // Order must match get_mod_names()!
        let mut chords = Vec::new();
        for name in self.get_mod_names() {
            chords
                .push(self.get_chord_in_mode(&name, mode).unwrap_or_default());
        }
        chords
    }

    pub fn get_kmap_paths(&self) -> Vec<KmapPath> {
        self.chords.keys().cloned().collect()
    }

    pub fn get_kmaps_with_words(&self) -> Vec<KmapPath> {
        let mut out = HashSet::new();
        for mode_info in self.modes.values() {
            for kmap_info in &mode_info.keymaps {
                if kmap_info.use_words {
                    out.insert(kmap_info.file.clone());
                }
            }
        }
        out.into_iter().collect()
    }

    pub fn get_seq_types(&self) -> Vec<SeqType> {
        let v: Vec<_> = self.sequences.keys().cloned().collect();
        v
    }

    pub fn get_num_anagrams(&self) -> u8 {
        self.highest_anagram_num.unwrap() + 1
    }

    pub fn set_huffman_table(&mut self) -> Result<(), Error> {
        if self.huffman_table.is_some() {
            panic!("huffman table was already set once");
        }
        self.huffman_table =
            Some(HuffmanTable::new(self.get_all_keypresses())?);
        Ok(())
    }

    pub fn huffman_table(&self) -> &HuffmanTable {
        self.huffman_table
            .as_ref()
            .expect("huffman table was never set")
    }

    pub fn get_all_keypresses(&self) -> Vec<KeyPress> {
        let mut v = Vec::new();
        for seq_type in self.sequences.keys() {
            for (_, seq) in self.get_sequences(&seq_type).expect("bad SeqType")
            {
                v.extend(seq.keypresses().cloned())
            }
        }
        v
    }

    pub fn get_max_uncompressed_seq_length(&self) -> usize {
        let mut max_length = 0;
        for seq_type in self.sequences.keys() {
            for (_, seq) in self.get_sequences(&seq_type).expect("bad SeqType")
            {
                max_length = max_length.max(seq.len())
            }
        }
        max_length
    }

    fn get_all_names(&self) -> Vec<Name> {
        self.sequences
            .iter()
            .flat_map(|(_seq_type, inner)| inner.keys())
            .cloned()
            .chain(self.anagram_mods.clone())
            .chain(self.word_mods.clone())
            .chain(self.plain_mods.clone())
            .collect()
    }

    pub fn incorporate_anagram(
        &self,
        mut chord: Chord,
        mode: &ModeName,
    ) -> Option<Chord> {
        let num = chord.anagram_num.unwrap() as usize;
        if num > 0 {
            let mod_chord =
                self.get_chord_in_mode(self.anagram_mods.get(num - 1)?, mode)?;
            chord.intersect(&mod_chord);
            chord.anagram_num = AnagramNum::default();
        };
        Some(chord)
    }

    pub fn get_tutor_data(&self) -> Result<TutorData, Error> {
        // TODO clean up, reorganize AllData to make this less bad?
        // TODO think about borrowck
        // TODO this is pretty slow
        let mut chords = BTreeMap::new();
        let names = self.get_all_names();
        for mode in self.modes.keys() {
            let mut mode_chords = BTreeMap::new();
            for name in &names {
                if let Some(mut chord) = self.get_chord_in_mode(name, mode) {
                    // TODO speed up by fetching all anagram chords in advance?
                    if let Some(new) = self.incorporate_anagram(chord, mode) {
                        mode_chords.insert(name.to_owned(), new);
                    }
                    // Otherwise we couldn't incorporate the anagram number into
                    // the chord, so skip it.
                }
            }
            chords.insert(mode.to_owned(), mode_chords);
        }
        // TODO use references instead of cloning spellings
        Ok(TutorData {
            chords: chords,
            spellings: self.spellings.clone(),
        })
    }

    pub fn chord_from_spelling(
        &self,
        spelling: &Spelling,
        kmap: &KmapPath,
    ) -> Result<Chord, Error> {
        let name = self.name_from_spelling(spelling)?;
        Ok(self.get_chord(&name, kmap).ok_or_else(|| LookupErr {
            key: name.to_string(),
            container: "chords".into(),
        })?)
    }

    fn name_from_spelling(&self, spelling: &Spelling) -> Result<Name, Error> {
        Ok(self.spellings
            .get(spelling)
            .ok_or_else(|| LookupErr {
                key: format!("name for '{}'", spelling),
                container: "spelling table".into(),
            })?
            .to_owned())
    }

    pub fn make_spelling_table(&mut self) -> Result<(), Error> {
        let mut map = BTreeMap::new();
        {
            let plain_names = self.get_sequences(&SeqType::Plain)?
                .keys()
                .chain(self.plain_mods.iter());
            for name in plain_names {
                let keypress = self.get_sequence(name)?.lone_keypress()?;
                if let Some(spelling) =
                    KeyDefs::spelling_from_keypress(&keypress)?
                {
                    map.insert(spelling, name.to_owned());
                }
            }
        }
        self.spellings = map;
        Ok(())
    }
}
