use itertools::Itertools;
use std::clone::Clone;
use std::collections::{BTreeMap, HashSet};
use std::path::PathBuf;

use util::ensure_u8;

use types::{
    AnagramNum, CTree, Chord, ChordSpec, HuffmanTable, KeyDefs, KeyPress,
    KmapPath, ModeInfo, ModeName, Name, SeqType, Sequence, Spelling, TutorData,
    Word,
};

use failure::{Error, Fail, ResultExt};
use types::errors::{BadValueErr, ConflictErr, LookupErr};

#[derive(Debug)]
pub struct ChordMap(BTreeMap<Name, Chord>);

#[derive(Debug)]
pub struct SeqMap(BTreeMap<Name, Sequence>);

#[derive(Debug)]
pub struct AllSeqMaps {
    maps: BTreeMap<SeqType, SeqMap>,
    pub max_seq_length: usize,
}

#[derive(Debug)]
pub struct AllChordMaps {
    maps: BTreeMap<KmapPath, ChordMap>,
    max_anagram_num: AnagramNum,
}

#[derive(Debug)]
pub struct AllData {
    pub chords: AllChordMaps,
    pub sequences: AllSeqMaps,
    pub word_mods: Vec<Name>,
    pub plain_mods: Vec<Name>,
    pub anagram_mods: Vec<Name>,
    pub modes: BTreeMap<ModeName, ModeInfo>,
    pub huffman_table: Option<HuffmanTable>,
    pub spellings: BTreeMap<Spelling, Name>,

    pub options: Vec<CTree>,
    pub output_directory: PathBuf,
    pub chord_spec: ChordSpec,
}

impl AllData {
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
        word: Word,
        kmap: &KmapPath,
    ) -> Result<(), Error> {
        let name = word.name();

        self.sequences
            .insert(name.clone(), word.sequence()?, SeqType::Word)?;

        // Get chords for each letter in the word and combine them.
        let mut chord: Chord = word.chord_spellings()?
            .iter()
            .map(|s| self.chord_from_spelling(s, kmap))
        // This is messy and doesn't short-circuit on the first error,
        // but there's no fold1_result(), so whatever.
            .fold1(|a, b| {
                if a.is_err() {
                    a
                } else if b.is_err() {
                    b
                } else {
                    Ok(a.unwrap().intersect(&b.unwrap()))
                }
            })
            .ok_or_else(|| format_err!("no chords to intersect"))??;

        chord.anagram_num = word.anagram_num();
        self.chords.insert(name, chord, kmap)
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

    pub fn add_word_mod(&mut self, name: Name) {
        self.word_mods.push(name);
    }

    pub fn add_anagram_mod(&mut self, name: Name) {
        self.anagram_mods.push(name);
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

    /// Return the first chord found for the given name in any of this mode's
    /// kmaps.
    pub fn get_chord_in_mode(
        &self,
        chord_name: &Name,
        mode: &ModeName,
    ) -> Option<Chord> {
        for kmap_info in &self.modes.get(mode).expect("unknown mode").keymaps {
            if let Ok(chord) = self.chords.get(chord_name, &kmap_info.file) {
                return Some(chord);
            }
        }
        None
    }

    pub fn get_anagram_mod_chords(&self, mode: &ModeName) -> Vec<Chord> {
        // Missing mod chords are represented in the firmware config as a
        // blank chord.
        self.anagram_mods
            .iter()
            .map(|name| {
                self.get_chord_in_mode(name, mode)
                    .unwrap_or_else(|| self.chord_spec.new_chord())
            })
            .collect()
    }

    pub fn get_mod_chords(&self, mode: &ModeName) -> Vec<Chord> {
        // Order must match get_mod_names()!
        let mut chords = Vec::new();
        for name in self.get_mod_names() {
            // Missing mod chords are represented in the firmware config as a
            // blank chord.
            chords.push(
                self.get_chord_in_mode(&name, mode)
                    .unwrap_or_else(|| self.chord_spec.new_chord()),
            );
        }
        chords
    }

    /// The number of bytes required to represent a chord in the firmware.
    pub fn num_bytes_in_chord(&self) -> Result<usize, Error> {
        // The best way to be sure we're calculating num_bytes_in_chord
        // correctly is to just create a chord, turn it to bytes like we will
        // during rendering, and check how many bytes are in it.
        Ok(self.chord_spec
            .to_bytes(&self.chord_spec.new_chord())?
            .len())
    }

    pub fn get_mod_names(&self) -> Vec<Name> {
        let mut names = Vec::new();
        names.extend(self.plain_mods.clone());
        names.extend(self.word_mods.clone());
        names.extend(self.anagram_mods.clone());
        names.sort();
        names
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

    pub fn set_huffman_table(&mut self) -> Result<(), Error> {
        if self.huffman_table.is_some() {
            panic!("huffman table was already set once");
        }
        self.huffman_table =
            Some(HuffmanTable::new(self.sequences.dump_all_keypresses())?);
        Ok(())
    }

    pub fn huffman_table(&self) -> &HuffmanTable {
        self.huffman_table
            .as_ref()
            .expect("huffman table was never set")
    }

    fn get_all_names(&self) -> Vec<Name> {
        self.sequences
            .names()
            .chain(self.anagram_mods.iter())
            .chain(self.word_mods.iter())
            .chain(self.plain_mods.iter())
            .cloned()
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
            chord.intersect_mut(&mod_chord);
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
            chord_spec: self.chord_spec.clone(),
        })
    }

    pub fn chord_from_spelling(
        &self,
        spelling: &Spelling,
        kmap: &KmapPath,
    ) -> Result<Chord, Error> {
        let name = self.name_from_spelling(spelling)?;
        self.chords.get(&name, kmap)
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
            let plain_names = self.sequences
                .get_seq_map(SeqType::Plain)?
                .names()
                .chain(self.plain_mods.iter());

            for name in plain_names {
                let keypress =
                    self.sequences.get_seq_of_any_type(name)?.lone_keypress()?;
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

impl AllChordMaps {
    pub fn new() -> AllChordMaps {
        AllChordMaps {
            maps: BTreeMap::new(),
            max_anagram_num: AnagramNum::default(),
        }
    }

    pub fn get(
        &self,
        chord_name: &Name,
        kmap: &KmapPath,
    ) -> Result<Chord, Error> {
        // TODO be consistent about argument order
        Ok(self.get_kmap(kmap)?
            .get(chord_name)
            .and_then(|x| Some(x.clone()))
            .ok_or_else(|| LookupErr {
                key: chord_name.into(),
                container: format!("{} chord map", kmap),
            })?)
    }

    pub fn get_kmap(&self, kmap: &KmapPath) -> Result<&ChordMap, Error> {
        Ok(self.maps.get(kmap).ok_or_else(|| LookupErr {
            key: kmap.into(),
            container: "chord maps".into(),
        })?)
    }

    pub fn kmap_paths(&self) -> impl Iterator<Item = &KmapPath> {
        self.maps.keys()
    }

    pub fn names(&self) -> impl Iterator<Item = &Name> {
        self.maps.values().flat_map(|chord_map| chord_map.names())
    }

    pub fn num_anagrams(&self) -> u8 {
        self.max_anagram_num.unwrap() + 1
    }

    /// If this kmap was not already present, initialize its chord map and
    /// return true. Otherwise return false.
    fn init_kmap(&mut self, kmap: &KmapPath) -> bool {
        if self.maps.contains_key(kmap) {
            return false;
        }

        self.maps.insert(kmap.to_owned(), ChordMap::new());
        true
    }

    fn insert(
        &mut self,
        name: Name,
        chord: Chord,
        kmap: &KmapPath,
    ) -> Result<(), Error> {
        let anagram_num = chord.anagram_num;

        self.maps
            .get_mut(kmap)
            .ok_or_else(|| {
                BadValueErr {
                    thing: "kmap".into(),
                    value: kmap.to_owned().into(),
                }.context("tried to add chord to uninitialized kmap")
            })?
            .insert(name, chord)?;

        if anagram_num > self.max_anagram_num {
            self.max_anagram_num = anagram_num;
        }

        Ok(())
    }

    pub fn insert_map(
        &mut self,
        named_chords: BTreeMap<Name, Chord>,
        kmap: &KmapPath,
    ) -> Result<(), Error> {
        for (name, chord) in named_chords {
            self.insert(name, chord, kmap)?;
        }
        Ok(())
    }

    pub fn iter(&self) -> impl Iterator<Item = (&KmapPath, &ChordMap)> {
        self.maps.iter()
    }
}

impl AllSeqMaps {
    pub fn new() -> AllSeqMaps {
        AllSeqMaps {
            maps: BTreeMap::new(),
            max_seq_length: 0,
        }
    }

    pub fn get_seq_map(&self, seq_type: SeqType) -> Result<&SeqMap, Error> {
        Ok(self.maps.get(&seq_type).ok_or_else(|| LookupErr {
            key: format!("{:?}", seq_type),
            container: "sequence maps".into(),
        })?)
    }

    pub fn get(
        &self,
        name: &Name,
        seq_type: SeqType,
    ) -> Result<&Sequence, Error> {
        Ok(self.get_seq_map(seq_type)?
            .get(name)
            .ok_or_else(|| LookupErr {
                key: name.into(),
                container: format!("{} sequence map", seq_type),
            })?)
    }

    pub fn get_seq_of_any_type(&self, name: &Name) -> Result<&Sequence, Error> {
        let hits: Vec<&Sequence> = self.maps
            .values()
            .filter_map(|seq_map| seq_map.get(name))
            .collect();

        if hits.is_empty() {
            Err(LookupErr {
                key: name.into(),
                container: "sequences".into(),
            }.into())
        } else if hits.len() == 1 {
            Ok(hits[0])
        } else {
            bail!("Found multiple sequences with the same name: {}", name)
        }
    }

    pub fn seq_types(&self) -> impl Iterator<Item = &SeqType> {
        self.maps.keys()
    }

    pub fn names(&self) -> impl Iterator<Item = &Name> {
        self.maps.values().flat_map(|seq_map| seq_map.names())
    }

    pub fn insert_map<T>(
        &mut self,
        seqs: BTreeMap<Name, T>,
        seq_type: SeqType,
    ) -> Result<(), Error>
    where
        T: Into<Sequence>,
    {
        for (name, seq) in seqs {
            self.insert(name, seq.into(), seq_type)?;
        }
        Ok(())
    }

    fn insert(
        &mut self,
        name: Name,
        seq: Sequence,
        seq_type: SeqType,
    ) -> Result<(), Error> {
        let length = seq.len();

        self.maps
            .entry(seq_type)
            .or_insert_with(SeqMap::new)
            .insert(name.to_owned(), seq)?;

        if length > self.max_seq_length {
            self.max_seq_length = length;
        }
        Ok(())
    }

    pub fn dump_all_keypresses(&self) -> Vec<KeyPress> {
        let mut v = Vec::new();
        for seq_map in self.maps.values() {
            for seq in seq_map.0.values() {
                v.extend(seq.keypresses().cloned())
            }
        }
        v
    }
}

impl ChordMap {
    fn new() -> ChordMap {
        ChordMap(BTreeMap::new())
    }

    pub fn get(&self, name: &Name) -> Option<&Chord> {
        self.0.get(name)
    }

    pub fn get_result(&self, name: &Name) -> Result<&Chord, Error> {
        // TODO merge with get?
        Ok(self.0.get(name).ok_or_else(|| LookupErr {
            key: format!("{:?}", name),
            container: "chord map".into(),
        })?)
    }

    fn insert(&mut self, name: Name, chord: Chord) -> Result<(), Error> {
        if self.0.contains_key(&name) {
            Err(ConflictErr {
                key: name.clone().into(),
                container: "chord map".into(),
            })?
        }

        self.0.insert(name, chord);
        Ok(())
    }

    pub fn iter(&self) -> impl Iterator<Item = (&Name, &Chord)> {
        self.0.iter()
    }

    pub fn names(&self) -> impl Iterator<Item = &Name> {
        self.0.keys()
    }
}

impl SeqMap {
    fn new() -> SeqMap {
        SeqMap(BTreeMap::new())
    }

    fn get(&self, name: &Name) -> Option<&Sequence> {
        // TODO return result?
        self.0.get(name)
    }

    pub fn names(&self) -> impl Iterator<Item = &Name> {
        self.0.keys()
    }

    fn insert(&mut self, name: Name, seq: Sequence) -> Result<(), Error> {
        ensure_u8(seq.len()).with_context(|_| {
            format!("Sequence contains too many keypresses: '{}'", name)
        })?;

        if self.0.insert(name.to_owned(), seq).is_some() {
            Err(ConflictErr {
                key: name.into(),
                container: "seq map".into(),
            })?;
        }

        Ok(())
    }
}
