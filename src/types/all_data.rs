use std::collections::BTreeMap;
use std::clone::Clone;
use std::path::PathBuf;

use types::{AnagramNum, CTree, Checker, Chord, HuffmanTable, KeyPress,
            KmapPath, ModeInfo, ModeName, Name, SeqType, Sequence, TutorData,
            WordBuilder, WordConfig};

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
    checker: Checker,
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
            checker: Checker::new(),
            highest_anagram_num: AnagramNum(0),
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
        self.checker.insert_chord(name, chord, kmap);
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
        info: WordConfig,
        kmap: &KmapPath,
    ) -> Result<(), Error> {
        // TODO build word in loader code instead?
        let word = WordBuilder {
            info: info,
            kmap: kmap,
            all_data: self,
        }.finalize()?;
        self.add_sequence(SeqType::Word, &word.name, &word.seq)?;
        self.add_chord(&word.name, &word.chord, kmap)?;
        if word.chord.anagram_num > self.highest_anagram_num {
            self.highest_anagram_num = word.chord.anagram_num;
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

    pub fn add_word_mod(&mut self, name: &Name) -> Result<(), Error> {
        // Add all the word_mods at once
        self.word_mods.push(name.to_owned());
        self.checker.insert_word_mod_or_anagram_mod(name)
    }

    pub fn add_anagram_mod(&mut self, name: &Name) -> Result<(), Error> {
        // Add all the anagram_mods at once
        // TODO share code with set_word_mods()?
        self.anagram_mods.push(name.to_owned());
        self.checker.insert_word_mod_or_anagram_mod(name)
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
        self.checker.insert_seq(name)?;
        self.sequences
            .entry(seq_type)
            .or_insert_with(BTreeMap::new)
            .insert(name.to_owned(), seq.to_owned().into());
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

    fn get_sequence(&self, name: &Name) -> Result<&Sequence, Error> {
        for seq_type in self.sequences.keys() {
            if let Some(s) = self.get_sequences(seq_type)?.get(name) {
                return Ok(s);
            }
        }
        Err(LookupErr {
            key: name.into(),
            container: "sequences".into(),
        })?
    }

    pub fn get_single_keypress(&self, name: &Name) -> Result<KeyPress, Error> {
        let seq = self.get_sequence(name).context("failed to get sequence")?;
        // TODO iter?
        let length = seq.len();
        if length != 1 {
            Err(BadValueErr {
                thing: "sequence length".into(),
                value: length.to_string(),
            }).context("Expected sequence containing a single keypress")?;
        }
        Ok(seq.0[0].clone())
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
        let mut out = Vec::new();
        for mode_info in self.modes.values() {
            for kmap_info in &mode_info.keymaps {
                if kmap_info.use_words {
                    out.push(kmap_info.file.clone());
                }
            }
        }
        out
    }

    pub fn get_seq_types(&self) -> Vec<SeqType> {
        let v: Vec<_> = self.sequences.keys().cloned().collect();
        v
    }

    pub fn get_num_anagrams(&self) -> u8 {
        self.highest_anagram_num.0 + 1
    }

    pub fn check(&self) {
        // TODO check for missing sequences
        self.checker.check_unused();
        self.checker.check_chords();
    }

    pub fn set_huffman_table(&mut self) {
        if self.huffman_table.is_some() {
            panic!("huffman table was already set once");
        }
        self.huffman_table = Some(HuffmanTable::new(self.get_all_keypresses()));
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
        let num = chord.anagram_num.0 as usize;
        if num > 0 {
            let mod_chord =
                self.get_chord_in_mode(self.anagram_mods.get(num - 1)?, mode)?;
            chord.intersect(&mod_chord);
            chord.anagram_num = AnagramNum(0);
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
        Ok(TutorData { chords: chords })
    }
}
