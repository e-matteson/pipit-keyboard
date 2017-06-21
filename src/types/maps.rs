use std::collections::BTreeMap;
use std::clone::Clone;

use types::{Chord, Sequence, KeyPress, Word, WordBuilder, Options};


pub enum SeqType {
    Plain,
    Macro,
    Word,
    Command,
}

#[derive(Debug)]
pub struct Maps {
    pub chords:     BTreeMap<String, BTreeMap<String, Chord>>, // full kmap name to chord map
    // pub plains:     BTreeMap<String, Sequence>,
    // pub macros:     BTreeMap<String, Sequence>,
    // pub words:      BTreeMap<String, Sequence>,
    // pub commands:   BTreeMap<String, Sequence>,
    pub sequences:  BTreeMap<SeqType, BTreeMap<String, Chord>>,
    pub wordmods:   Vec<String>,
    pub anagrams:   Vec<String>,
    pub modes:      BTreeMap<String, Vec<String>>, // mode name to full kmap name
    pub kmap_names: BTreeMap<String, String>, // kmap path to short kmap nickname
    pub options:    Options,
}

impl Maps {
    pub fn new() -> Maps {
        Maps{
            chords: BTreeMap::new(),
            // plains: BTreeMap::new(),
            // macros: BTreeMap::new(),
            // words: BTreeMap::new(),
            // commands: BTreeMap::new(),
            sequences: BTreeMap::new(),
            anagrams: Vec::new(),
            wordmods: Vec::new(),
            options: Options::new(),
        }
    }

    pub fn add_command(&mut self, entry: &str) {
        if self.commands.contains_key(entry){
            panic!(format!("commands map already contains key: {}", entry));
        }
        // commands are a single byte code, not an actual key sequence.
        // But we'll store it as a KeyPress for convenience.
        let mut fake_seq_with_command_code = Sequence::new();
        fake_seq_with_command_code.push(KeyPress::new_fake(&entry.to_uppercase()));

        self.commands.insert(entry.to_owned(),
                             fake_seq_with_command_code);
    }

    pub fn add_word(&mut self, seq_spelling: &str, chord_spelling: &str,
                    anagram: u64, mode: &str)
    {
        // TODO build word in loader code instead?
        let word = WordBuilder {
            seq_spelling: seq_spelling,
            chord_spelling: chord_spelling,
            anagram: anagram,
            mode: mode,
            maps: &self,
        }.finalize();
        self.words.insert(word.name.clone(),  word.seq);
        let kmap = self.modes[0]; // TODO which kmap should the word be added to?
        self.get_chords_mut(kmap).insert(word.name.clone(), word.chord);
    }

    // pub fn get_modifier_position(&self, name: &str, kmap: &str) -> usize {
    //     // TODO take kmap list, return None if not found
    //     // TODO remove single switch limitation
    //     self.get_chords(kmap).get(name)
    //         .expect(&format!("modifier not found in kmap: {}, {}", name, kmap))
    //         .get_single_switch_index()
    //         .expect(&format!("modifier must be mapped to exactly one switch: {}, {}",
    //                          name, kmap))
    // }

    pub fn set_sequences(&mut self, seq_type: SeqType, val: BTreeMap<String, Sequence>) {
        assert!(!self.sequences.contains_key(seq_type));
        self.sequences.insert(seq_type, val);
    }

    pub fn get_sequences(&self, seq_type: SeqType) -> &BTreeMap<String, Chord>{
        self.sequences.get(seq_type)
            .expect(&format!("Failed to get sequences for SeqType: {:?}", seq_type))
    }

    pub fn get_sequences_mut(&self, seq_type: SeqType) -> &BTreeMap<String, Chord>{
        self.sequences.get_mut(seq_type)
            .expect(&format!("Failed to get sequences for SeqType: {:?}", seq_type))
    }

    pub fn get_chord(&self, chord_name: &str, mode: &str) -> Option<Chord>{
        for kmap in self.modes.get(mode).expect("unknown mode"){
            if self.chords.kmap.contains_key(chord_name){
                return self.chords.kmap.get(chord_name).clone();
            }
        }
        None
    }

    pub fn get_chords(&self, kmap: &str) -> &BTreeMap<String, Chord>{
        self.chords.get(kmap)
            .expect(&format!("Failed to get chords for kmap: {}", kmap))
    }

    pub fn get_chords_mut(&mut self, kmap: &str) -> &mut BTreeMap<String, Chord>{
        self.chords.get_mut(kmap)
            .expect(&format!("Failed to get chords for kmap: {}", kmap))
    }

    // fn get_all_chords_for_mode(&self, mode: &str) -> &Vec<BTreeMap<String, Chord>>{
    //     self.chords.iter()
    //         .filter(|(key,_)| self.modes[mode].contains_key(key))
    //         .map(|(_,val)| val)
    //         .collect()
    // }

    pub fn add_mode(&mut self, mode: &str, kmaps: &Vec<String>) {
        assert!(!self.modes.contains_key(mode));
        // Store the kmaps that are included in this mode
        self.modes.insert(mode, kmaps.clone());
        for kmap in kmaps{
            if !self.kmap_names.contains_key(kmap){
                // Initialize new chord map
                self.chords.insert(kmap.to_owned(), BTreeMap::new());
                // Generate nickname, for later formatting
                let nickname = format!("kmap{}", self.kmap_names.len());
                self.kmap_names.insert(kmap.to_owned(), nickname);
            }
            // Else another mode already contained this kmap, skip it.
        }
    }

    pub fn add_chords(&mut self, kmap: &str, mut new_chords: BTreeMap<String, Chord>) {
        self.chords
            .get_mut(kmap)
            .expect(&format!("Failed to add chord because kmap is unknown: {}",
                             kmap))
            .append(&mut new_chords);
    }

    pub fn check_for_duplicate_chords(&self) {
        for kmap in self.chords.keys(){
            let mut foo: Vec<_> = self.chords[kmap].iter()
                .map(|(k, v)|
                     (v.to_string(), k))
                .collect();

            foo.sort();
            let mut last_chord = String::new();
            let mut last_name = "";
            for (chord, name) in foo {
                let is_duplicate = chord == last_chord
                    && !self.wordmods.contains(&name.to_string())
                    && !self.wordmods.contains(&last_name.to_string());

                if is_duplicate {
                    println!("WARNING: duplicate chord: '{}', '{}'", last_name, name);
                }
                last_chord = chord;
                last_name = name;
            }
        }
    }


    // pub fn check_for_missing_seqs(&self) {
    //     // TODO new self.sequences
    //     // Print warnings if any chords were never assigned a key sequence.
    //     for kmap in self.chords.keys(){
    //         for name in self.chords[kmap].keys() {
    //             if self.wordmods.contains(name) { continue }
    //             if self.commands.contains_key(name) { continue }
    //             if self.plains.contains_key(name) { continue }
    //             if self.macros.contains_key(name) { continue }
    //             if self.words.contains_key(name) { continue }
    //             println!("WARNING: no key sequence: '{}'", name);
    //         }
    //     }
    // }

    // pub fn make_anagram_bit_masks(&self) -> Vec<Chord> {
    //     // TODO Making this for all kmaps isn't very useful - used to be all modes.
    //     //      Remove this entirely and OR in firmware?
    //     let mut v: Vec<Chord> = Vec::new();
    //     // TODO why get kmaps from options? why not self.chords.keys()?
    //     for kmap in &self.options.get_kmaps() {
    //         let mut all_bits = Chord::new();

    //         for name in &self.anagrams {
    //             if let Some(chord) = self.chords[kmap].get(name) {
    //                 all_bits.intersect(chord);
    //             }
    //             // Else this kmap doesn't have this anagram mod, fine.
    //             // TODO should we explicitly handle non-word kmaps differently?
    //         }
    //         v.push(all_bits);
    //     }
    //     v
    // }

}


