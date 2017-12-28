use std::collections::BTreeMap;
use std::clone::Clone;
use std::path::PathBuf;

use types::{AnagramNum, CTree, Checker, Chord, KeyPress, KmapPath, ModeInfo,
            ModeName, Name, SeqType, Sequence, WordBuilder, WordConfig};
use types::errors::*;


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
            checker: Checker::new(),
            highest_anagram_num: AnagramNum(0),
        }
    }

    pub fn add_chords(
        &mut self,
        kmap: &KmapPath,
        named_chords: BTreeMap<Name, Chord>,
    ) -> Result<()> {
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
    ) -> Result<()> {
        (|| -> Result<()> {
            self.checker.insert_chord(name, chord, kmap)?;
            self.chords
                .get_mut(kmap)
                .ok_or_else(|| format!("unknown kmap: {}", kmap))?
                .insert(name.to_owned(), chord.to_owned());
            Ok(())
        })()
            .chain_err(|| "failure to add chord")
    }

    pub fn add_command(&mut self, entry: &Name) -> Result<()> {
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
    ) -> Result<()> {
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

    pub fn add_plain_mod<T>(&mut self, name: &Name, seq: &T) -> Result<()>
    where
        T: Into<Sequence> + Clone,
    {
        // TODO check if sequence is valid! length 1, no key
        self.plain_mods.push(name.to_owned());
        self.add_sequence(SeqType::Plain, name, seq)
    }


    pub fn add_word_mod(&mut self, name: &Name) -> Result<()> {
        // Add all the word_mods at once
        self.word_mods.push(name.to_owned());
        self.checker.insert_seq(name)
    }

    pub fn add_anagram_mod(&mut self, name: &Name) -> Result<()> {
        // Add all the anagram_mods at once
        // TODO share code with set_word_mods()?
        self.anagram_mods.push(name.to_owned());
        self.checker.insert_seq(name)
    }

    pub fn add_mode(&mut self, name: &ModeName, info: &ModeInfo) -> Result<()> {
        if self.modes.contains_key(name) {
            bail!("mode already exists: '{}'", name);
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
    ) -> Result<()>
    where
        T: Into<Sequence> + Clone,
    {
        // TODO check that name doesn't already exist
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
    ) -> Result<()>
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
    ) -> Result<&BTreeMap<Name, Sequence>> {
        self.sequences.get(seq_type).ok_or_else(|| {
            format!("Sequence type was not initialized: {:?}", seq_type).into()
        })
    }

    fn get_sequence(&self, name: &Name) -> Result<&Sequence> {
        for seq_type in self.sequences.keys() {
            if let Some(s) = self.get_sequences(seq_type)?.get(name) {
                return Ok(s);
            }
        }
        bail!("No sequence found for name");
    }

    pub fn get_single_keypress(&self, name: &Name) -> Result<KeyPress> {
        let seq = self.get_sequence(name)?;
        // TODO iter?
        if seq.len() != 1 {
            bail!("Expected sequence of length 1");
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

    fn get_names_for_seq(&self, seq_type: SeqType) -> Result<Vec<Name>> {
        Ok(self.get_sequences(&seq_type)?.keys().cloned().collect())
    }

    pub fn get_tutor_data(
        &self,
    ) -> Result<BTreeMap<ModeName, BTreeMap<Name, Chord>>> {
        // TODO clean up, reorganize AllData to make this less bad?
        // TODO think about borrowck
        let mut chords = BTreeMap::new();
        let mut names = self.get_names_for_seq(SeqType::Plain)?;
        names.extend(self.get_names_for_seq(SeqType::Command)?);
        names.extend(self.get_names_for_seq(SeqType::Macro)?);
        names.extend(self.anagram_mods.clone());
        names.extend(self.word_mods.clone());

        for mode in self.modes.keys() {
            let mut mode_chords = BTreeMap::new();
            for name in &names {
                if let Some(chord) = self.get_chord_in_mode(name, mode) {
                    mode_chords.insert(name.to_owned(), chord);
                }
            }
            chords.insert(mode.to_owned(), mode_chords);
        }
        Ok(chords)
    }
}
