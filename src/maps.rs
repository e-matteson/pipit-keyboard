use std::collections::BTreeMap;
use std::fmt::Display;
use std::clone::Clone;

use options::*;
use words::*;
use chord::*;
use sequence::*;
use c_array::*;
use options::format::*;

type LenMap = BTreeMap<usize, Vec<String>>;
type SeqMap = BTreeMap<String, Sequence>;
// type SpecialMap = BTreeMap<String, usize>;
type SpecialMap = BTreeMap<String, Sequence>;
type ChordMap = BTreeMap<String, Chord>;


#[derive(Debug)]
pub struct Maps {
    pub chords: ChordMap,
    pub plains: SeqMap,
    pub macros: SeqMap,
    pub words:  SeqMap,
    pub specials: SpecialMap,
    pub wordmods: Vec<String>,
}

impl Maps {
    pub fn new() -> Maps {
        Maps{
            chords: BTreeMap::new(),
            plains: BTreeMap::new(),
            macros: BTreeMap::new(),
            words: BTreeMap::new(),
            specials: BTreeMap::new(),
            wordmods: Vec::new(),
        }
    }

    pub fn add_special(&mut self, entry: &str) {
        let num = self.specials.len() + 1;
        if self.specials.contains_key(entry){
            panic!(format!("specials map already contains key: {}", entry));
        }
        // Specials are a single byte code, not an actual key sequence.
        // But we'll store it as a KeyPress for convenience.
        let mut fake_seq_with_special_code = Sequence::new();
        fake_seq_with_special_code.push(KeyPress::new(num, 0));

        self.specials.insert(entry.to_owned(),
                             fake_seq_with_special_code);
    }

    pub fn add_word(&mut self, entry: &Vec<String>) {
        let word = Word::new(entry, &self.chords);
        self.words.insert(word.name.clone(),  word.seq);
        self.chords.insert(word.name.clone(), word.chord);
    }

    pub fn get_modifier_position(&self, name: &str) -> usize {
        // TODO take arg for layout
        self.chords[name].get_single_switch_index()
            .expect("modifier must be mapped to exactly one switch")
    }

    pub fn check_for_duplicate_chords(&self) {
        // TODO handle layouts
        let mut foo: Vec<_> = self.chords.iter()
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


    pub fn check_for_missing_seqs(&self) {
        // Print warnings if any chords were never assigned a key sequence.
        for name in self.chords.keys() {
            if self.wordmods.contains(name) { continue }
            if self.specials.contains_key(name) { continue }
            if self.plains.contains_key(name) { continue }
            if self.macros.contains_key(name) { continue }
            if self.words.contains_key(name) { continue }
            println!("WARNING: no key sequence: '{}'", name);
        }
    }

    pub fn format_words (&self) -> Format {
        let chord_map = &self.chords;
        format_lookups(&self.words, chord_map, "word", true, false)
    }

    pub fn format_plains (&self) -> Format {
        let chord_map = &self.chords;
        format_lookups(&self.plains, chord_map, "plain", false, true)
    }

    pub fn format_macros (&self) -> Format {
        let chord_map = &self.chords;
        format_lookups(&self.macros, chord_map, "macro", false, true)
    }

    pub fn format_specials (&self) -> Format {
        let mut f = Format {
            h: self.specials.keys()
                .fold(String::new(),
                      |acc, name|
                      acc + &format!("#define {} {}\n",
                                     name,
                                     self.specials[name].get_only_value()))
                + "\n",
            c: String::new(),
        };
        let chord_map = &self.chords;
        f.append(&format_lookups(&self.specials, chord_map, "special", false, false));
        f
    }

    pub fn format_wordmods(&self) -> Format {
        let mut f = Format::new();
        for name in &self.wordmods {
            let full_name = format!("{}_chord_bytes", name);
            f.append(&CArray::new(&full_name)
                     .fill_1d(&self.chords[name].to_ints())
                     .format())
        }
        f
    }

}


fn format_lookups (seq_map: &SeqMap,
                   chord_map: &ChordMap,
                   name: &str,
                   use_compression: bool,
                   use_mods: bool)
                   -> Format
{

    let names_by_len = make_length_map(&seq_map);
    let max_len: usize = *names_by_len.keys().max()
        .expect("failed to get max length");

    let mut seq_arrays: Vec<Vec<String>> = vec![Vec::new() ; 1+max_len];
    let mut chord_arrays: Vec<Vec<i64>> = vec![Vec::new() ; 1+max_len];

    for &length in names_by_len.keys() {
        let flat_seq = make_flat_sequence(seq_map, &names_by_len, length);
        // length + 1;
        seq_arrays[length] = flat_seq.to_bytes(use_compression, use_mods);
        for name in &names_by_len[&length]{
            chord_arrays[length].extend(chord_map[name].to_ints());
            // TODO what happens if a chord is missing?
        }
    }

    for subarray in &mut chord_arrays {
        // append zeros to mark the end of each length-subarray
        subarray.extend(Chord::new().to_ints());
    }
    let mut f = Format::new();

    f.append(&format_length_arrays(chord_arrays,
                                  &format!("{}_chord_lookup", name)));
    f.append(&format_length_arrays(seq_arrays,
                                  &format!("{}_seq_lookup", name)));
    f
}

fn format_length_arrays <T> (arrays: Vec<Vec<T>>, name: &str) -> Format
    where T: Display + Clone
{
    let subarray_names: Vec<_> = (0..arrays.len())
        .map(|x| format!("{}_{}", name, x))
        .collect();
    let mut f = Format::new();
    for i in 0..subarray_names.len() {
        f.append(&CArray::new(&subarray_names[i])
                 .fill_1d(&arrays[i])
                 .format()
        );
    }
    f.append(&CArray::new(&name).is_extern(true).c_type("uint8_t*")
             .fill_1d(&subarray_names)
             .format());
    f
}


fn make_flat_sequence(seq_map: &SeqMap, names_by_len: &LenMap, length: usize)
                      -> Sequence {
    let mut flat_seq = Sequence::new();
    for name in &names_by_len[&length] {
        flat_seq.extend(seq_map[name].clone());
    }
    flat_seq
}

fn make_length_map(seq_map: &BTreeMap<String, Sequence>) -> LenMap {
    // TODO layouts: weave name order
    let mut names_by_len = BTreeMap::new();
    let mut names: Vec<_> = seq_map.keys().collect();
    names.sort();
    for name in names{
        let length = seq_map[name].len();
        names_by_len.entry(length).or_insert(Vec::new()).push(name.to_owned());
    }
    names_by_len
}
