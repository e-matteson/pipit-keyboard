use std::collections::{BTreeMap, HashMap, HashSet};
use std::collections::hash_map::Entry;
use std::clone::Clone;

use types::{Chord, Sequence, KeyPress, WordBuilder, Options, SeqType, KmapPath,
            KmapInfo, Name, ModeName, CCode, ToC};


// TODO typealias kmap names
#[derive(Debug)]
pub struct Maps {
    pub chords:       BTreeMap<KmapPath, BTreeMap<Name, Chord>>, // full kmap name to chord map
    pub sequences:    BTreeMap<SeqType, BTreeMap<Name, Sequence>>,
    pub wordmods:     Vec<Name>,
    pub modifierkeys: Vec<Name>,
    pub anagrams:     Vec<Name>,
    pub modes:        BTreeMap<ModeName, Vec<KmapInfo>>,
    pub kmap_ids:     BTreeMap<KmapPath, String>, // kmap path to short kmap nickname
    pub options:      Options,
}

impl Maps {
    pub fn new() -> Maps {
        Maps{
            chords: BTreeMap::new(),
            sequences: BTreeMap::new(),
            wordmods: Vec::new(),
            modifierkeys: Vec::new(),
            anagrams: Vec::new(),
            modes: BTreeMap::new(),
            kmap_ids: BTreeMap::new(),
            options: Options::new(),
        }
    }

    pub fn add_command(&mut self, entry: &Name) {
        if self.get_sequences(&SeqType::Command).contains_key(entry){
            panic!(format!("commands map already contains key: {}", entry));
        }
        // commands are a single byte code, not an actual key sequence.
        // But we'll store it as a KeyPress for convenience.
        let mut fake_seq_with_command_code = Sequence::new();
        fake_seq_with_command_code.push(KeyPress::new_fake(&entry.to_uppercase()));

        self.get_sequences_mut(SeqType::Command)
            .insert(entry.to_owned(), fake_seq_with_command_code);
    }

    pub fn add_word(&mut self, seq_spelling: &str, chord_spelling: &str,
                    anagram: u64, kmap: &KmapPath)
    {
        // TODO build word in loader code instead?
        let word = WordBuilder {
            seq_spelling: seq_spelling,
            chord_spelling: chord_spelling,
            anagram: anagram,
            kmap: kmap,
            maps: &self,
        }.finalize();
        self.get_sequences_mut(SeqType::Word).insert(word.name.clone(),  word.seq);
        self.get_chords_mut(&kmap).insert(word.name.clone(), word.chord);
    }

    pub fn add_modifierkey(&mut self, name: Name, seq: &Sequence) {
        self.modifierkeys.push(name.clone());
        self.get_sequences_mut(SeqType::Plain).insert(name, seq.clone());
    }

    pub fn set_sequences(&mut self, seq_type: &SeqType, val: BTreeMap<Name, Sequence>) {
        assert!(!self.sequences.contains_key(&seq_type));
        self.sequences.insert(seq_type.clone(), val);
    }

    pub fn get_sequences(&self, seq_type: &SeqType) -> &BTreeMap<Name, Sequence>{
        self.sequences.get(&seq_type)
            .expect(&format!("Sequences has not been initialized for SeqType: {:?}", seq_type))
    }

    pub fn get_sequences_mut(&mut self, seq_type: SeqType) -> &mut BTreeMap<Name, Sequence>{
        self.sequences.get_mut(&seq_type)
            .expect(&format!("Sequences has not been initialized for SeqType: {:?}", seq_type))
    }

    fn get_sequence(&self, name: &Name) -> &Sequence {
        for seq_type in self.sequences.keys() {
            match self.get_sequences(seq_type).get(name){
                Some(s) => return s,
                None => (),
            }
        }
        panic!("No sequence found for name");
    }

    pub fn get_mod_key(&self, name: &Name) -> CCode {
        let seq = self.get_sequence(name);
        if seq.len() != 1 || seq.0[0].key != "0".to_c() {
            panic!("bad modifierkey sequence");
        }
        seq.0[0].modifier.clone()
    }

    // TODO handle missing mods better - here or firmware?
    pub fn get_chord_in_mode(&self, chord_name: &Name, mode: &ModeName) -> Chord {
        for kmap_info in self.modes.get(mode).expect("unknown mode"){
            if let Some(chord) = self.get_chord(chord_name, &kmap_info.path) {
                return chord;
            }
        }
        Chord::new()
    }

    pub fn get_anagrams(&self, mode: &ModeName) -> Vec<Chord> {
        let mut out = Vec::new();
        for name in self.anagrams.iter() {
            out.push(self.get_chord_in_mode(&name, mode));
        }
        out
    }

    pub fn get_mod_names(&self) -> Vec<Name> {
        let mut names = Vec::new();
        names.extend(self.modifierkeys.clone());
        names.extend(self.wordmods.clone());
        names
    }

    pub fn get_mod_chords(&self, mode: &ModeName) -> Vec<Chord> {
        let mut chords = Vec::new();
        for name in self.get_mod_names() {
            chords.push(self.get_chord_in_mode(&name, &mode));
        }
        chords
    }

    fn get_wordmod_helper(&self, name: &Name, mode: &ModeName) -> Chord {
        // TODO what should happen when there's no chord?
        if !self.wordmods.contains(name){
            panic!(format!("Required wordmod is missing from settings: {}", name));
        }
        self.get_chord_in_mode(name, mode)
    }

    pub fn check_for_conflicts(&self) {
        for mode in self.chords.keys() {
            let reversed = self.reverse_chord_map(mode);
            print_conflict_stats(reversed, mode);
        }
    }

    fn reverse_chord_map(&self, mode: &KmapPath) -> HashMap<Chord, Vec<Name>>{
        let exclude_anagrams = false;
        let mut reversed: HashMap<Chord, Vec<Name>> = HashMap::new();
        for (name, chord) in self.chords[mode].iter(){
            match reversed.entry(chord.clone()){
                Entry::Occupied(entry) => {
                    let list = entry.into_mut();
                    if exclude_anagrams && list.iter().any(|x| is_simple_anagram(x, name)){
                        continue;
                    }
                    list.push(name.to_owned());
                }
                Entry::Vacant(entry) => {
                    let mut v = Vec::new();
                    v.push(name.to_owned());
                    entry.insert(v);
                }
            }
        }
        reversed
    }


    pub fn get_wordmod_capital(&self, mode: &ModeName) -> Chord {
        self.get_wordmod_helper(&Name::from("wordmod_capital"), mode)
    }

    pub fn get_wordmod_nospace(&self, mode: &ModeName) -> Chord {
        self.get_wordmod_helper(&Name::from("wordmod_nospace"), mode)
    }

    pub fn get_mod_ctrl(&self, mode: &ModeName) -> Chord {
        self.get_chord_in_mode(&Name::from("modifierkey_ctrl"), mode)
    }

    pub fn get_mod_alt(&self, mode: &ModeName) -> Chord {
        self.get_chord_in_mode(&Name::from("modifierkey_alt"), mode)
    }

    pub fn get_mod_shift(&self, mode: &ModeName) -> Chord {
        self.get_chord_in_mode(&Name::from("modifierkey_shift"), mode)
    }

    pub fn get_mod_gui(&self, mode: &ModeName) -> Chord {
        self.get_chord_in_mode(&Name::from("modifierkey_gui"), mode)
    }

    pub fn get_chord(&self, chord_name: &Name, kmap: &KmapPath) -> Option<Chord>{
        match self.chords[kmap].get(chord_name) {
            Some(chord) => Some(chord.clone()),
            None => None,
        }
    }

    pub fn get_chords(&self, kmap: &KmapPath) -> &BTreeMap<Name, Chord>{
        self.chords.get(kmap)
            .expect(&format!("Failed to get chords for kmap: {}", kmap))
    }

    pub fn get_chords_mut(&mut self, kmap: &KmapPath) -> &mut BTreeMap<Name, Chord>{
        self.chords.get_mut(kmap)
            .expect(&format!("Failed to get chords for kmap: {}", kmap))
    }

    pub fn get_kmap_paths(&self) -> Vec<KmapPath> {
        let v: Vec<_> = self.kmap_ids.keys()
            .map(|s| s.clone())
            .collect();
        v
    }

    pub fn get_kmaps_with_words(&self) -> Vec<KmapPath> {
        let mut out = Vec::new();
        for mode in self.modes.values() {
            for kmap_info in mode.iter() {
                if kmap_info.use_words {
                    out.push(kmap_info.path.clone());
                }
            }
        }
        out
    }

    pub fn get_seq_types(&self) -> Vec<SeqType> {
        let v: Vec<_> = self.sequences.keys()
            .map(|s| s.to_owned())
            .collect();
        v
    }

    pub fn add_mode(&mut self, mode: ModeName, kmaps: Vec<KmapInfo>) {
        assert!(!self.modes.contains_key(&mode));
        // Store the kmaps that are included in this mode
        for kmap_info in kmaps.iter() {
            let kmap_path = &kmap_info.path;
            if self.kmap_ids.contains_key(kmap_path){
                continue;
            }
            // Initialize new chord map
            self.chords.insert(kmap_path.clone(), BTreeMap::new());
            // Generate nickname, for later formatting
            let nickname = format!("kmap{}", self.kmap_ids.len());
            self.kmap_ids.insert(kmap_path.clone(), nickname);
        }
        self.modes.insert(mode, kmaps);
    }

    pub fn add_chords(&mut self, kmap: &KmapPath, mut new_chords: BTreeMap<Name, Chord>) {
        self.chords
            .get_mut(kmap)
            .expect(&format!("Failed to add chord because kmap is unknown: {}",
                             kmap))
            .append(&mut new_chords);
    }
}

fn print_conflict_stats(reversed: HashMap<Chord, Vec<Name>>, mode: &KmapPath){
    let mut conflicts = HashMap::new();
    for (_, names) in reversed {
        let len = names.len();
        if len == 1 {
            continue;
        }
        println!("WARNING: duplicate chords: {:?}", names);
        *conflicts.entry(len).or_insert(0) += 1;
    }
    let total: i64 = conflicts.values().sum();
    let mut conflict_vec: Vec<_> = conflicts.iter().collect();
    conflict_vec.sort_by(|a, b| b.1.cmp(a.1));
    println!("{}: {} conflicts: {:?}", mode, total, conflict_vec);
}

fn is_simple_anagram(word1: &Name, word2: &Name) -> bool {
    let chars1: HashSet<_> = word1.0.chars().collect();
    let chars2: HashSet<_> = word2.0.chars().collect();
    chars1 == chars2
}
