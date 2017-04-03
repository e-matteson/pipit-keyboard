use std::collections::HashMap;

use options::*;
use words::*;
use key_types::*;

#[derive(Debug)]
pub struct Maps{
    pub chords: HashMap<String, Chord>,
    pub plains: HashMap<String, Sequence>,
    pub macros: HashMap<String, Sequence>,
    pub words: HashMap<String, Sequence>,
    pub specials: HashMap<String, usize>,
    pub wordmods: Vec<String>,
    len_chord: usize,
}

impl Maps{
    pub fn new(num_bytes_in_chord: usize) -> Maps{
        Maps{
            chords: HashMap::new(),
            plains: HashMap::new(),
            macros: HashMap::new(),
            words: HashMap::new(),
            specials: HashMap::new(),
            wordmods: Vec::new(),
            len_chord: 8*num_bytes_in_chord,
        }
    }

    pub fn add_special(&mut self, entry: &str) {
        let num = self.specials.len() + 1;
        if self.specials.contains_key(entry){
            panic!(format!("specials map already contains key: {}", entry));
        }
        self.specials.insert(entry.to_owned(), num);
    }

    pub fn add_word(&mut self, entry: &Vec<String>) {
        let word = make_word(entry, &self.chords, self.len_chord);
        self.words.insert(word.name.clone(),  word.seq);
        self.chords.insert(word.name.clone(), word.chord);
    }

    pub fn get_modifier_position(&self, name: &str) -> usize{
        // TODO take arg for layout
        let error_message = format!("modifier must be mapped to exactly one switch: {}", name);
        let chord = &self.chords[name];

        if chord.iter().filter(|x| **x).count() > 1{
            panic!(error_message);
        }
        chord.iter().position(|x| *x).expect(&error_message)
   }

    pub fn check_for_duplicate_chords(&self) {
        // TODO handle layouts
        fn vec_to_string(v: &Vec<bool>) -> String{
            let tmp: Vec<_> = v.iter().map(|&b| if b {"1"} else {"0"}).collect();
            tmp.join("")
        }

        let mut foo: Vec<_> = self.chords.iter()
            .map(|(k, v)|
                 (vec_to_string(v), k))
            .collect();

        foo.sort();
        let mut last_chord = String::new();
        let mut last_name = "";
        for (chord, name) in foo {
            let is_duplicate = chord == last_chord
                && !self.wordmods.contains(&name.to_string())
                && !self.wordmods.contains(&last_name.to_string());

            if is_duplicate{
                println!("WARNING: duplicate chord: '{}', '{}'", last_name, name);
            }
            last_chord = chord;
            last_name = name;
        }
    }


    pub fn check_for_missing_seqs(&self) {
        // Print warnings if any chords were never assigned a key sequence.
        for name in self.chords.keys() {
            if self.plains.contains_key(name) { continue }
            if self.macros.contains_key(name) { continue }
            if self.specials.contains_key(name) { continue }
            if self.words.contains_key(name) { continue }
            if self.wordmods.contains(name) { continue }
            println!("WARNING: no key sequence: '{}'", name);
        }
    }


}

