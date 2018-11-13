use itertools::Itertools;
use std::clone::Clone;
use std::collections::BTreeMap;
use std::path::PathBuf;

use error::{Error, ResultExt};
use types::{
    AnagramNum, BoardName, CTree, Chord, ChordSpec, Command, HuffmanTable,
    KeyPress, KmapOrder, KmapPath, ModeInfo, ModeName, Name, SeqType, Sequence,
    SpellingTable, TutorData,
};
use util::ensure_u8;

#[derive(Debug)]
pub struct ChordMap(BTreeMap<Name, Chord<KmapOrder>>);

#[derive(Debug)]
pub struct SeqMap(BTreeMap<Name, Sequence>);

#[derive(Debug, Default)]
pub struct AllSeqMaps {
    maps: BTreeMap<SeqType, SeqMap>,
}

#[derive(Debug, Default)]
pub struct AllChordMaps {
    maps: BTreeMap<KmapPath, ChordMap>,
}

#[derive(Debug)]
pub struct AllData {
    pub chords: AllChordMaps,
    pub sequences: AllSeqMaps,
    // pub word_mods: Vec<Name>,
    // pub plain_mods: Vec<Name>,
    // pub anagram_mods: Vec<Name>,
    pub word_mods: Vec<Name>,
    pub plain_mods: Vec<Name>,
    pub anagram_mods: Vec<Name>,
    pub modes: BTreeMap<ModeName, ModeInfo>,
    pub huffman_table: HuffmanTable,
    pub spellings: SpellingTable,
    pub commands: Vec<Command>,

    pub options: Vec<CTree>,
    pub early_options: Vec<CTree>,
    pub output_directory: PathBuf,
    pub chord_spec: ChordSpec,
    pub board: BoardName,
}

impl AllData {
    /// Return the first chord found for the given name in any of this mode's
    /// kmaps.
    pub fn get_chord_in_mode(
        &self,
        chord_name: &Name,
        mode: &ModeName,
    ) -> Option<Chord<KmapOrder>> {
        for kmap_info in &self.modes.get(mode).expect("unknown mode").keymaps {
            if let Ok(chord) = self.chords.get(chord_name, &kmap_info.file) {
                return Some(chord);
            }
        }
        None
    }

    /// Get a Chord containing all the switches used in any anagram mod.
    pub fn get_anagram_mask(&self, mode: &ModeName) -> Chord<KmapOrder> {
        self.anagram_mods
            .iter()
            .filter_map(|name| self.get_chord_in_mode(name, mode))
            .fold1(|a, b| a.union(&b).expect("failed to union anagram"))
            .unwrap_or_else(|| self.chord_spec.new_chord())
    }

    /// Return the anagram num corresponding to each anagram mod, in the same
    /// order as the `anagram_mods` vector.
    pub fn get_anagram_mod_numbers(&self) -> Result<Vec<AnagramNum>, Error> {
        // For now, just assume the first anagram mod is 1, and the rest count
        // up from there. In the future we could do something fancier, like
        // extract the number from the end of the Name.
        (0..self.anagram_mods.len())
            .map(|i| AnagramNum::new((i as u8) + 1))
            .collect()
    }

    /// Get names of all modifiers, including `plain_mod`s, `word_mod`s, and
    /// `anagram_mods`
    pub fn modifier_names(&self) -> Vec<&Name> {
        // TODO sorting works on the references, right?
        let mut names = Vec::new();
        names.extend(self.plain_mods.iter());
        names.extend(self.word_mods.iter());
        names.extend(self.anagram_mods.iter());
        names.sort();
        names
    }

    /// Get chords the for all modifiers in the given mode, in the same order
    /// as `modifier_names()`. If any modifier was not assigned a chord in this
    /// mode, give it a blank chord instead.
    pub fn modifier_chords(&self, mode: &ModeName) -> Vec<Chord<KmapOrder>> {
        let mut chords = Vec::new();
        for name in self.modifier_names() {
            // Missing mod chords are represented in the firmware config as a
            // blank chord.
            chords.push(
                self.get_chord_in_mode(&name, mode)
                    .unwrap_or_else(|| self.chord_spec.new_chord()),
            );
        }
        chords
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

    /// Incorporate the anagram mod chord directly into this chord.
    //
    /// Lookup the anagram_mod chord that corresponds to the given chord's
    /// anagram number, and return the union of the 2 chords. If the given
    /// chord's anagram number is zero, return the given chord without
    /// modifications. If its anagram number has no corresponding anagram_mod
    /// in this mode, return None.
    pub fn incorporate_anagram(
        &self,
        mut chord: Chord<KmapOrder>,
        mode: &ModeName,
    ) -> Option<Chord<KmapOrder>> {
        let num = chord.anagram_num.get() as usize;
        if num > 0 {
            let mod_chord =
                self.get_chord_in_mode(self.anagram_mods.get(num - 1)?, mode)?;
            chord
                .union_mut(&mod_chord)
                .expect("failed to union anagram");
            chord.anagram_num = AnagramNum::default();
        };
        Some(chord)
    }

    /// Get the subset of the data needed for the typing tutor and/or the
    /// cheatsheet.
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
            chords,
            spellings: self.spellings.clone(),
            chord_spec: self.chord_spec.clone(),
        })
    }

    pub fn board(&self) -> BoardName {
        self.board
    }
}

impl AllChordMaps {
    pub fn get(
        &self,
        chord_name: &Name,
        kmap: &KmapPath,
    ) -> Result<Chord<KmapOrder>, Error> {
        // TODO be consistent about argument order
        Ok(self
            .get_kmap(kmap)?
            .get(chord_name)
            .and_then(|x| Some(x.clone()))
            .ok_or_else(|| Error::LookupErr {
                key: chord_name.into(),
                container: format!("{} chord map", kmap),
            })?)
    }

    pub fn get_kmap(&self, kmap: &KmapPath) -> Result<&ChordMap, Error> {
        self.maps.get(kmap).ok_or_else(|| Error::LookupErr {
            key: kmap.into(),
            container: "chord maps".into(),
        })
    }

    pub fn kmap_paths(&self) -> impl Iterator<Item = &KmapPath> {
        self.maps.keys()
    }

    pub fn names(&self) -> impl Iterator<Item = &Name> {
        self.maps.values().flat_map(|chord_map| chord_map.names())
    }

    pub fn max_anagram_num(&self) -> AnagramNum {
        self.maps
            .values()
            .map(|chord_map| chord_map.max_anagram_num())
            .max()
            .unwrap_or_default()
    }

    /// If this kmap was not already present, initialize its chord map and
    /// return true. Otherwise return false.
    pub fn init_kmap(&mut self, kmap: &KmapPath) -> bool {
        if self.maps.contains_key(kmap) {
            return false;
        }

        self.maps.insert(kmap.to_owned(), ChordMap::new());
        true
    }

    pub fn insert(
        &mut self,
        name: Name,
        chord: Chord<KmapOrder>,
        kmap: &KmapPath,
    ) -> Result<(), Error> {
        self.maps
            .get_mut(kmap)
            .ok_or_else(|| {
                Error::BadValueErr {
                    thing: "kmap".into(),
                    value: kmap.to_owned().into(),
                }
                .context("tried to add chord to uninitialized kmap")
            })?
            .insert(name, chord)
    }

    pub fn insert_map(
        &mut self,
        named_chords: BTreeMap<Name, Chord<KmapOrder>>,
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
    pub fn get_seq_map(&self, seq_type: SeqType) -> Result<&SeqMap, Error> {
        self.maps.get(&seq_type).ok_or_else(|| Error::LookupErr {
            key: format!("{:?}", seq_type),
            container: "sequence maps".into(),
        })
    }

    pub fn get(
        &self,
        name: &Name,
        seq_type: SeqType,
    ) -> Result<&Sequence, Error> {
        self.get_seq_map(seq_type)?
            .get(name)
            .ok_or_else(|| Error::LookupErr {
                key: name.into(),
                container: format!("{} sequence map", seq_type),
            })
    }

    pub fn get_seq_of_any_type(&self, name: &Name) -> Result<&Sequence, Error> {
        let hits: Vec<&Sequence> = self
            .maps
            .values()
            .filter_map(|seq_map| seq_map.get(name))
            .collect();

        if hits.is_empty() {
            Err(Error::LookupErr {
                key: name.into(),
                container: "sequences".into(),
            })
        } else if hits.len() == 1 {
            Ok(hits[0])
        } else {
            Err(Error::ConflictErr {
                key: name.into(),
                container: "sequences".to_owned(),
            }
            .context("Found multiple sequences with the same name"))
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

    pub fn insert(
        &mut self,
        name: Name,
        seq: Sequence,
        seq_type: SeqType,
    ) -> Result<(), Error> {
        self.maps
            .entry(seq_type)
            .or_insert_with(SeqMap::new)
            .insert(name, seq)?;
        Ok(())
    }

    /// The length of the longest sequence contained anywhere in this map.
    pub fn max_seq_length(&self) -> usize {
        self.maps
            .values()
            .map(|seq_map| seq_map.max_seq_length())
            .max()
            .unwrap_or(0)
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
    fn new() -> Self {
        ChordMap(BTreeMap::new())
    }

    pub fn get(&self, name: &Name) -> Option<&Chord<KmapOrder>> {
        self.0.get(name)
    }

    pub fn get_result(&self, name: &Name) -> Result<&Chord<KmapOrder>, Error> {
        // TODO merge with get?
        self.0.get(name).ok_or_else(|| Error::LookupErr {
            key: name.into(),
            container: "chord map".to_owned(),
        })
    }

    fn insert(
        &mut self,
        name: Name,
        chord: Chord<KmapOrder>,
    ) -> Result<(), Error> {
        if self.0.contains_key(&name) {
            return Err(Error::ConflictErr {
                key: name.clone().into(),
                container: "chord map".into(),
            });
        }

        self.0.insert(name, chord);
        Ok(())
    }

    pub fn iter(&self) -> impl Iterator<Item = (&Name, &Chord<KmapOrder>)> {
        self.0.iter()
    }

    pub fn names(&self) -> impl Iterator<Item = &Name> {
        self.0.keys()
    }

    fn max_anagram_num(&self) -> AnagramNum {
        self.0
            .values()
            .map(|chord| chord.anagram_num)
            .max()
            .unwrap_or_default()
    }
}

impl SeqMap {
    fn new() -> Self {
        SeqMap(BTreeMap::new())
    }

    fn get(&self, name: &Name) -> Option<&Sequence> {
        // TODO return result?
        self.0.get(name)
    }

    pub fn names(&self) -> impl Iterator<Item = &Name> {
        self.0.keys()
    }

    fn max_seq_length(&self) -> usize {
        self.0.values().map(|seq| seq.len()).max().unwrap_or(0)
    }

    fn insert(&mut self, name: Name, seq: Sequence) -> Result<(), Error> {
        ensure_u8(seq.len()).with_context(|| {
            format!("Sequence contains too many keypresses: '{}'", name)
        })?;

        if self.0.insert(name.to_owned(), seq).is_some() {
            Err(Error::ConflictErr {
                key: name.into(),
                container: "sequence map".into(),
            })
        } else {
            Ok(())
        }
    }
}
