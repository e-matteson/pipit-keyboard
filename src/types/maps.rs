use std::collections::BTreeMap;
use std::clone::Clone;

use types::{Chord, Sequence, KeyPress, WordBuilder, Options, SeqType, KmapPath,
            KmapInfo, Name, ModeName};


// TODO typealias kmap names
#[derive(Debug)]
pub struct Maps {
    pub chords:     BTreeMap<KmapPath, BTreeMap<Name, Chord>>, // full kmap name to chord map
    pub sequences:  BTreeMap<SeqType, BTreeMap<Name, Sequence>>,
    pub wordmods:   Vec<Name>,
    pub anagrams:   Vec<Name>,
    pub modes:      BTreeMap<ModeName, Vec<KmapInfo>>,
    pub kmap_ids:   BTreeMap<KmapPath, String>, // kmap path to short kmap nickname
    pub options:    Options,
}

impl Maps {
    pub fn new() -> Maps {
        Maps{
            chords: BTreeMap::new(),
            sequences: BTreeMap::new(),
            wordmods: Vec::new(),
            anagrams: Vec::new(),
            modes: BTreeMap::new(),
            kmap_ids: BTreeMap::new(),
            options: Options::new(),
        }
    }

    pub fn add_command(&mut self, entry: &Name) {
        if self.get_sequences(SeqType::Command).contains_key(entry){
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

    // pub fn get_modifier_position(&self, name: &str, kmap: &str) -> usize {
    //     // TODO take kmap list, return None if not found
    //     // TODO remove single switch limitation
    //     self.get_chords(kmap).get(name)
    //         .expect(&format!("modifier not found in kmap: {}, {}", name, kmap))
    //         .get_single_switch_index()
    //         .expect(&format!("modifier must be mapped to exactly one switch: {}, {}",
    //                          name, kmap))
    // }

    pub fn set_sequences(&mut self, seq_type: SeqType, val: BTreeMap<Name, Sequence>) {
        assert!(!self.sequences.contains_key(&seq_type));
        self.sequences.insert(seq_type, val);
    }

    pub fn get_sequences(&self, seq_type: SeqType) -> &BTreeMap<Name, Sequence>{
        self.sequences.get(&seq_type)
            .expect(&format!("Sequences has not been initialized for SeqType: {:?}", seq_type))
    }

    pub fn get_sequences_mut(&mut self, seq_type: SeqType) -> &mut BTreeMap<Name, Sequence>{
        self.sequences.get_mut(&seq_type)
            .expect(&format!("Sequences has not been initialized for SeqType: {:?}", seq_type))
    }

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

    fn get_wordmod_helper(&self, name: &Name, mode: &ModeName) -> Chord {
        // TODO what should happen when there's no chord?
        if !self.wordmods.contains(name){
            panic!(format!("Required wordmod is missing from settings: {}", name));
        }
        self.get_chord_in_mode(name, mode)
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

    // fn get_all_chords_for_mode(&self, mode: &str) -> &Vec<BTreeMap<Name, Chord>>{
    //     self.chords.iter()
    //         .filter(|(key,_)| self.modes[mode].contains_key(key))
    //         .map(|(_,val)| val)
    //         .collect()
    // }

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

    // pub fn check_for_duplicate_chords(&self) {
    //     for kmap in self.chords.keys(){
    //         let mut foo: Vec<_> = self.chords[kmap].iter()
    //             .map(|(k, v)|
    //                  (v.to_string(), k))
    //             .collect();

    //         foo.sort();
    //         let mut last_chord = String::new();
    //         let mut last_name = "";
    //         for (chord, name) in foo {
    //             let is_duplicate = chord == last_chord
    //                 && !self.wordmods.contains(&name.to_string())
    //                 && !self.wordmods.contains(&last_name.to_string());

    //             if is_duplicate {
    //                 println!("WARNING: duplicate chord: '{}', '{}'", last_name, name);
    //             }
    //             last_chord = chord;
    //             last_name = name;
    //         }
    //     }
    // }


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


