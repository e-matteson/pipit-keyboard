use std::collections::{HashMap};
use std::collections::hash_map::Entry;
use std::fmt::Display;

use types::{Chord, Word, KmapPath, Name, ModeName, Maps};

#[derive(Debug)]
pub struct Checker <'a>{
    // TODO use more references, instead of duplicating lots of stuff
    pub reverse_anagrams: HashMap<KmapPath, HashMap<Chord, HashMap<u64, Name>>>,
    pub reverse_kmaps:    HashMap<KmapPath, HashMap<Chord, Vec<Name>>>,
    pub reverse_modes:    HashMap<ModeName, HashMap<Chord, Vec<Name>>>,
    maps: &'a Maps
}

impl <'a> Checker <'a> {
    pub fn new(maps: &'a Maps) -> Checker<'a> {
        Checker {
            reverse_anagrams: HashMap::new(),
            reverse_kmaps: HashMap::new(),
            reverse_modes: HashMap::new(),
            maps: maps
        }
    }

    pub fn check(&mut self) {
        // TODO take args for types of checks
        self.make_reverse_kmaps();
        self.make_reverse_modes();
        self.make_reverse_anagrams();
        self.check_for_conflicts();
        self.check_anagrams(true);
    }

    pub fn check_for_conflicts(&self) {
        // TODO option to check for mode conflicts instead
        for (name, reverse_kmap) in self.reverse_kmaps.iter() {
            let v = get_conflicts(reverse_kmap);
            print_conflicts(&v, name);
        }
    }

    pub fn check_anagrams(&self, allow_two_key: bool) {
        for kmap in self.reverse_anagrams.keys() {
            let conflicts = self.get_anagram_conflicts(kmap, allow_two_key);
            print_anagram_conflicts(&conflicts, kmap);
        }
    }

    fn get_anagram_conflicts(&self, kmap: &KmapPath, allow_two_key: bool) -> Vec<Vec<&Name>> {
        // TODO rename, not a conflict. Useless anagrams.
        let mut out = Vec::new();
        for chord in self.reverse_anagrams[kmap].keys() {
            let anagrams = &self.reverse_anagrams
                .get(kmap).unwrap().get(chord).unwrap();
            if self.is_anagram_bad(kmap, chord, anagrams, allow_two_key) {
                out.push(anagrams.values().collect());
            }
        }
        out
    }

    fn is_anagram_bad(&self, kmap: &KmapPath,
                      base_chord: &Chord,
                      anagrams: &HashMap<u64, Name>,
                      allow_two_key: bool)
                      -> bool
    {
        let max = anagrams.keys().max()
            .expect("failed to get max anagram num")
            .to_owned();
        if max+1 == (anagrams.len() as u64){
            return false;
        }
        for num in 0..max {
            if anagrams.keys().any(|&x| x == num) {
                continue;
            }
            let mut new_chord = base_chord.to_owned();
            new_chord.intersect(&self.maps.get_anagram_chord(num, kmap));
            if !self.contains_chord(&new_chord, kmap) {
                if allow_two_key && base_chord.count_switches() == 2 {
                    // By convention, all words made of 2 switches, one on each
                    // hand, use an anagram mod. It's because it's hard to
                    // remember which of those would conflict with 2-hand plain
                    // keys. So we may not want to warn about them. (We don't
                    // check which hands the switches are on, but close enough)
                    continue;
                }
                return true;
            }
        }
        return false;
    }

    fn make_reverse_kmaps(&mut self) {
        let mut new = HashMap::new();
        for kmap in self.maps.chords.keys(){
            new.insert(kmap.to_owned(), HashMap::new());
            for (name, chord) in self.maps.chords[kmap].iter() {
                add_to(&mut new.get_mut(kmap).unwrap(), chord, name);
            }
        }
        self.reverse_kmaps = new;
    }

    fn make_reverse_modes(&mut self) {
        let mut new = HashMap::new();
        for mode in self.maps.modes.keys() {
            let kmaps_vec = self.maps.get_kmaps_for_mode(mode);
            let mut kmaps = kmaps_vec.iter();
            new.insert(
                mode.to_owned(),
                self.reverse_kmaps.get(kmaps.next().expect("no kmaps"))
                    .expect("reverse kmap not found")
                    .to_owned());
            for kmap in kmaps {
                println!("{}", kmap);
                for (chord, names) in self.reverse_kmaps[kmap].iter() {
                    for name in names.iter(){
                        add_to(new.get_mut(mode).unwrap(), chord, name);
                    }
                }
            }
        }
        self.reverse_modes = new;
    }

    fn make_reverse_anagrams(&mut self) {
        let mut new = HashMap::new();
        for (kmap, words) in self.maps.anagram_records.iter() {
            for word in words {
                insert_anagram(&mut new, kmap, word);
            }
        }
        self.reverse_anagrams = new;
    }

    fn contains_chord(&self, chord: &Chord, kmap: &KmapPath) -> bool {
        self.reverse_kmaps.get(kmap)
            .expect("reverse kmap not found")
            .contains_key(chord)
    }
}

fn insert_anagram(reverse_anagrams: &mut HashMap<KmapPath,
                                                 HashMap<Chord,
                                                         HashMap<u64, Name>>>,
                  kmap: &KmapPath, word: &Word)
{
    reverse_anagrams
        .entry(kmap.to_owned())
        .or_insert(HashMap::new())
        .entry(word.base_chord.to_owned())
        .or_insert(HashMap::new())
    // TODO check for conflicts?
        .insert(word.anagram_num, word.name.clone());
}

fn add_to(reversed: &mut HashMap<Chord, Vec<Name>>,
          chord: &Chord,
          name: &Name)
{
    match reversed.entry(chord.to_owned()) {
        Entry::Occupied(entry) => {
            entry.into_mut().push(name.to_owned());
        }
        Entry::Vacant(entry) => {
            let mut v = Vec::new();
            v.push(name.to_owned());
            entry.insert(v);
        }
    }
}

fn get_conflicts<'a>(reversed: &'a HashMap<Chord, Vec<Name>>)
                     -> Vec<&'a Vec<Name>>
{
    // TODO rewrite with filter?
    let mut v = Vec::new();
    for (_, names) in reversed {
        if names.len() > 1 {
            v.push(names);
        }
    }
    v
}

fn print_conflicts <T: Display>(conflicts: &Vec<&Vec<Name>>, label: &T) {
    if conflicts.is_empty() {
        return;
    }
    println!("Conflicting chords in {}:", label);
    for conflict in conflicts {
        println!("  {:?}", conflict);
    }
    println!("");
}

fn print_anagram_conflicts <T: Display>(conflicts: &Vec<Vec<&Name>>, label: &T) {
    if conflicts.is_empty() {
        return;
    }
    println!("Words with unnecessary anagram modifiers in {}:", label);
    for conflict in conflicts {
        println!("  {:?}", conflict);
    }
    println!("");
}


// fn print_conflict_stats( kmap: &KmapPath){
//     let mut conflicts = HashMap::new();
//     for (_, names) in reversed {
//         let len = names.len();
//         if len == 1 {
//             continue;
//         }
//         println!("WARNING: duplicate chords: {:?}", names);
//         *conflicts.entry(len).or_insert(0) += 1;
//     }
//     let total: i64 = conflicts.values().sum();
//     let mut conflict_vec: Vec<_> = conflicts.iter().collect();
//     conflict_vec.sort_by(|a, b| b.1.cmp(a.1));
//     println!("{}: {} conflicts: {:?}", kmap, total, conflict_vec);
// }
