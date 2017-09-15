use std::collections::BTreeMap;
use std::clone::Clone;

use types::{Checker, Chord, KeyPress, KmapPath, ModeInfo, ModeName,
            Name, Options, SeqType, Sequence, WordBuilder, WordInfo};
use types::errors::*;


// TODO typealias kmap names?
#[derive(Debug)]
pub struct Maps {
    pub chords: BTreeMap<KmapPath, BTreeMap<Name, Chord>>,
    pub sequences: BTreeMap<SeqType, BTreeMap<Name, Sequence>>,
    pub word_mods: Vec<Name>,
    pub plain_mods: Vec<Name>,
    pub anagram_mods: Vec<Name>,
    // pub modes:        BTreeMap<ModeName, Vec<KmapInfo>>,
    pub modes: BTreeMap<ModeName, ModeInfo>,
    pub kmap_ids: BTreeMap<KmapPath, String>,
    pub options: Options,
    checker: Checker,
    max_anagram_num: u8,
}

impl Maps {
    pub fn new() -> Maps {
        Maps {
            chords: BTreeMap::new(),
            sequences: BTreeMap::new(),
            word_mods: Vec::new(),
            plain_mods: Vec::new(),
            anagram_mods: Vec::new(),
            modes: BTreeMap::new(),
            kmap_ids: BTreeMap::new(),
            options: Options::new(),
            checker: Checker::new(),
            max_anagram_num: 0,
        }
    }

    pub fn add_chord(
        &mut self,
        name: Name,
        chord: Chord,
        kmap: &KmapPath,
    ) -> Result<()> {
        self.checker.insert_chord(&name, &chord, kmap)?;
        self.chords
            .get_mut(kmap)
            .expect(&format!(
                "Failed to add chord because kmap is unknown: {}",
                kmap
            ))
            .insert(name, chord);
        Ok(())
    }

    pub fn add_chords(
        &mut self,
        kmap: &KmapPath,
        named_chords: BTreeMap<Name, Chord>,
    ) -> Result<()> {
        for (name, chord) in named_chords {
            self.add_chord(name, chord, kmap)?;
        }
        Ok(())
    }

    pub fn add_command(&mut self, entry: &Name) -> Result<()> {
        // Commands are a single byte code, not an actual key sequence.
        // But we'll store each one as a KeyPress for convenience.
        let mut fake_seq_with_command_code = Sequence::new();

        fake_seq_with_command_code
            .push(KeyPress::new_fake(&entry.to_uppercase()));

        self.add_sequence(
            SeqType::Command,
            entry.to_owned(),
            fake_seq_with_command_code,
        )
    }


    pub fn add_word(&mut self, info: WordInfo, kmap: &KmapPath) -> Result<()> {
        // TODO build word in loader code instead?
        let word = WordBuilder {
            info: info,
            kmap: kmap,
            maps: self,
        }.finalize()?;
        self.add_sequence(SeqType::Word, word.name.clone(), word.seq.clone())?;
        self.add_chord(word.name.clone(), word.chord.clone(), kmap)?;
        if word.chord.anagram_num > self.max_anagram_num {
            self.max_anagram_num = word.chord.anagram_num;
        }
        Ok(())
    }

    pub fn add_plain_mod(&mut self, name: Name, seq: &Sequence) -> Result<()> {
        // TODO check if sequence is valid! length 1, no key
        self.plain_mods.push(name.clone());
        self.add_sequence(SeqType::Plain, name, seq.clone())
    }


    pub fn set_word_mods(&mut self, names: Vec<Name>) -> Result<()> {
        // Add all the word_mods at once
        assert!(self.word_mods.is_empty());

        for name in &names {
            self.checker.insert_seq(name)?;
        }
        self.word_mods = names;
        Ok(())
    }

    pub fn set_anagram_mods(&mut self, names: Vec<Name>) -> Result<()> {
        // Add all the anagram_mods at once
        // TODO share code with set_word_mods()?
        assert!(self.anagram_mods.is_empty());

        for name in &names {
            self.checker.insert_seq(name)?;
        }
        self.anagram_mods = names;
        Ok(())
    }

    pub fn add_mode(&mut self, name: ModeName, info: ModeInfo) -> Result<()> {
        if self.modes.contains_key(&name) {
            bail!("mode already exists: '{}'", &name);
        }
        // Store the kmaps that are included in this mode
        for kmap_info in &info.keymaps {
            let kmap_path = &kmap_info.file;
            if self.kmap_ids.contains_key(kmap_path) {
                continue;
            }
            // Initialize new chord map
            self.chords.insert(kmap_path.clone(), BTreeMap::new());
            // Generate nickname, for later formatting
            let nickname = format!("kmap{}", self.kmap_ids.len());
            self.kmap_ids.insert(kmap_path.clone(), nickname);
        }
        self.modes.insert(name, info);
        Ok(())
    }

    pub fn add_sequence(
        &mut self,
        seq_type: SeqType,
        name: Name,
        seq: Sequence,
    ) -> Result<()> {
        // TODO check that name doesn't already exist
        self.checker.insert_seq(&name)?;
        self.sequences
            .entry(seq_type)
            .or_insert_with(BTreeMap::new)
            .insert(name, seq);
        Ok(())
    }

    pub fn set_sequences(
        &mut self,
        seq_type: SeqType,
        val: BTreeMap<Name, Sequence>,
    ) -> Result<()> {
        // Add an entire seq_type's worth of sequences all at once
        assert!(!self.sequences.contains_key(&seq_type));

        for name in val.keys() {
            self.checker.insert_seq(name)?;
        }
        self.sequences.insert(seq_type, val);
        Ok(())
    }

    pub fn get_sequences(
        &self,
        seq_type: &SeqType,
    ) -> &BTreeMap<Name, Sequence> {
        self.sequences.get(seq_type).expect(&format!(
            "Sequences has not been initialized for SeqType: {:?}",
            seq_type
        ))
    }

    pub fn get_sequences_mut(
        &mut self,
        seq_type: SeqType,
    ) -> &mut BTreeMap<Name, Sequence> {
        self.sequences.get_mut(&seq_type).expect(&format!(
            "Sequences has not been initialized for SeqType: {:?}",
            seq_type
        ))
    }

    fn get_sequence(&self, name: &Name) -> &Sequence {
        for seq_type in self.sequences.keys() {
            if let Some(s) = self.get_sequences(seq_type).get(name) {
                return s;
            }
        }
        panic!("No sequence found for name");
    }

    pub fn get_single_keypress(&self, name: &Name) -> KeyPress {
        let seq = self.get_sequence(name);
        if seq.len() != 1 {
            panic!("Expected sequence of length 1");
        }
        seq.0[0].clone()
    }

    // pub fn get_mod_key(&self, name: &Name) -> KeyPress {
    //     if seq.len() != 1 || seq.0[0].key.is_some() {
    //         panic!("bad modifier key sequence");
    //     }
    //     seq.0[0].modifier.clone()
    // }

    // pub

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
    ) -> Chord {
        for kmap_info in &self.modes.get(mode).expect("unknown mode").keymaps {
            if let Some(chord) = self.get_chord(chord_name, &kmap_info.file) {
                return chord;
            }
        }
        Chord::new()
    }

    pub fn get_anagram_chords(&self, mode: &ModeName) -> Vec<Chord> {
        let mut out = Vec::new();
        for name in &self.anagram_mods {
            out.push(self.get_chord_in_mode(name, mode));
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
            chords.push(self.get_chord_in_mode(&name, mode));
        }
        chords
    }

    pub fn get_kmap_paths(&self) -> Vec<KmapPath> {
        let v: Vec<_> = self.kmap_ids.keys().cloned().collect();
        v
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

    pub fn get_kmaps_for_mode(&self, mode: &ModeName) -> Vec<KmapPath> {
        let v: Vec<_> = self.modes
            .get(mode)
            .expect("mode not found")
            .keymaps
            .iter()
            .map(|x| x.file.to_owned())
            .collect();
        v
    }

    pub fn get_seq_types(&self) -> Vec<SeqType> {
        let v: Vec<_> = self.sequences.keys().cloned().collect();
        v
    }

    pub fn get_num_anagrams(&self) -> u8 {
        self.max_anagram_num + 1
    }

    pub fn check(&self) {
        // TODO check for missing sequences
        self.checker.check_unused();
        self.checker.check_chords();
    }
}
