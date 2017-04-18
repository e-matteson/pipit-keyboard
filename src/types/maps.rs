use std::collections::BTreeMap;
use std::clone::Clone;

use types::{Chord, Sequence, KeyPress, Word, Options};


#[derive(Debug)]
pub struct Maps {
    pub chords:   BTreeMap<String, BTreeMap<String, Chord>>,
    pub plains:   BTreeMap<String, Sequence>,
    pub macros:   BTreeMap<String, Sequence>,
    pub words:    BTreeMap<String, Sequence>,
    pub commands: BTreeMap<String, Sequence>,
    pub wordmods: Vec<String>,
    pub options:  Options,
}

impl Maps {
    pub fn new() -> Maps {
        Maps{
            chords: BTreeMap::new(),
            plains: BTreeMap::new(),
            macros: BTreeMap::new(),
            words: BTreeMap::new(),
            commands: BTreeMap::new(),
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
        let word = Word::new(seq_spelling, chord_spelling, anagram, &self.chords[mode]);
        self.words.insert(word.name.clone(),  word.seq);
        self.get_chords_mut(mode).insert(word.name.clone(), word.chord);
    }

    pub fn get_modifier_position(&self, name: &str, mode: &str) -> usize {
        // TODO take arg for layout
        self.get_chords(mode).get(name)
            .expect(&format!("modifier not found in mode: {}, {}", name, mode))
            .get_single_switch_index()
            .expect(&format!("modifier must be mapped to exactly one switch: {}, {}",
                             name, mode))
    }

    pub fn get_chords(&self, mode: &str) -> &BTreeMap<String, Chord>{
        self.chords.get(mode)
            .expect(&format!("Failed to get chords for mode: {}", mode))
    }

    pub fn get_chords_mut(&mut self, mode: &str) -> &mut BTreeMap<String, Chord>{
        self.chords.get_mut(mode)
            .expect(&format!("Failed to get chords for mode: {}", mode))
    }

    pub fn add_modes(&mut self, modes: &Vec<String>) {
        for mode in modes{
            assert!(!self.chords.contains_key(mode));
            self.chords.insert(mode.to_owned(), BTreeMap::new());
        }
    }

    pub fn add_chords(&mut self, mode: &str, mut new_chords: BTreeMap<String, Chord>) {
        self.chords
            .get_mut(mode)
            .expect(&format!("Failed to add chord because mode is unknown: {}",
                             mode))
            .append(&mut new_chords);
    }

    pub fn check_for_duplicate_chords(&self) {
        // TODO handle layouts
        for mode in self.chords.keys(){
            let mut foo: Vec<_> = self.chords[mode].iter()
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


    pub fn check_for_missing_seqs(&self) {
        // Print warnings if any chords were never assigned a key sequence.
        for mode in self.chords.keys(){
            for name in self.chords[mode].keys() {
                if self.wordmods.contains(name) { continue }
                if self.commands.contains_key(name) { continue }
                if self.plains.contains_key(name) { continue }
                if self.macros.contains_key(name) { continue }
                if self.words.contains_key(name) { continue }
                println!("WARNING: no key sequence: '{}'", name);
            }
        }
    }

}


