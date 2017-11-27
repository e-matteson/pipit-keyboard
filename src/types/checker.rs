use std::collections::{HashMap, HashSet};
use std::fmt::{self, Display};

use types::{AnagramNum, Chord, KmapPath, Name};
use types::errors::*;

// The Checker warns about sub-optimal configuration. Any config issues that
// would break the firmware should be caught in the loading (or formatting) code
// instead.

#[derive(Debug)]
pub struct Checker {
    // TODO use more references, instead of duplicating lots of stuff
    reverse_kmaps: HashMap<KmapPath, HashMap<Chord, AnagramSet>>,
    all_seqs: HashSet<Name>,
    all_chords: HashSet<Name>,
}

impl Checker {
    pub fn new() -> Checker {
        Checker {
            reverse_kmaps: HashMap::new(),
            all_seqs: HashSet::new(),
            all_chords: HashSet::new(),
        }
    }

    pub fn check_chords(&self) {
        // TODO take args for types of checks
        // TODO option to check for mode conflicts instead
        for (kmap, reversed) in &self.reverse_kmaps {
            let v: Vec<_> = reversed
                .iter()
                .filter(|&(chord, set)| set.is_invalid(Some(chord)))
                .map(|(_, set)| set)
                .collect();
            print_conflicts(&v, kmap);
        }
    }

    pub fn check_unused(&self) {
        println!("Unused chords:");
        for name in self.all_chords.difference(&self.all_seqs) {
            println!("  {}", name);
        }
        println!("\nUnused sequences:");
        for name in self.all_seqs.difference(&self.all_chords) {
            println!("  {}", name);
        }
    }

    pub fn insert_seq(&mut self, name: &Name) -> Result<()> {
        if !self.all_seqs.insert(name.to_owned()) {
            // println!("{:?}", self.all_seqs);
            bail!("duplicate sequences for: '{}'", name);
        }
        Ok(())
    }

    pub fn insert_chord(
        &mut self,
        name: &Name,
        chord: &Chord,
        kmap: &KmapPath,
    ) -> Result<()> {
        // TODO take refs
        let mut base_chord = chord.to_owned();
        base_chord.anagram_num = AnagramNum(0);

        self.reverse_kmaps
            .entry(kmap.to_owned())
            .or_insert_with(HashMap::new)
            .entry(base_chord)
            .or_insert_with(AnagramSet::new)
            .insert(chord.anagram_num, name.clone());
        self.all_chords.insert(name.clone());
        Ok(())
    }
}


fn print_conflicts<T: Display>(conflicts: &[&AnagramSet], label: &T) {
    if conflicts.is_empty() {
        return;
    }
    println!(
        "\nConflicting chords (in parens) or useless anagrams (\"?\") in {}:",
        label
    );
    for conflict in conflicts {
        println!("  {}", conflict);
    }
    println!("");
}


//////////////////////////////

#[derive(Debug)]
pub struct AnagramSet(pub HashMap<AnagramNum, Vec<Name>>);

impl AnagramSet {
    pub fn new() -> AnagramSet {
        AnagramSet(HashMap::new())
    }

    pub fn insert(&mut self, anagram_num: AnagramNum, name: Name) {
        self.0
            .entry(anagram_num)
            .or_insert_with(Vec::new)
            .push(name);
    }

    pub fn is_invalid(&self, chord: Option<&Chord>) -> bool {
        if self.has_chord_conflict() {
            return true;
        }
        for num in 0..self.num_anagrams() {
            if self.is_anagram_missing(AnagramNum(num), chord) {
                return true;
            }
        }
        false
    }

    pub fn has_chord_conflict(&self) -> bool {
        for v in self.0.values() {
            if v.len() > 1 {
                return true;
            }
        }
        false
    }

    pub fn is_anagram_missing(
        &self,
        anagram_num: AnagramNum,
        chord: Option<&Chord>,
    ) -> bool {
        const ALLOW_MISSING_DOUBLE_SWITCHES: bool = false;

        if self.0.contains_key(&anagram_num) {
            return false;
        }
        // By convention, all words made of 2 switches on the same
        // hand use an anagram mod. It's because it's hard to
        // remember which of those would conflict with double-switch plain
        // keys. So we may not want to warn about them. (We don't
        // check which hands the switches are on, but close enough)
        if ALLOW_MISSING_DOUBLE_SWITCHES {
            chord.map_or(true, |c| c.count_switches() != 2)
        } else {
            true
        }
    }

    pub fn num_anagrams(&self) -> u8 {
        // TODO use actual max from elsewhere?
        let max_num = self.0
            .keys()
            .max()
            .expect("failed to get max anagram num")
            .to_owned();
        max_num.0 + 1
    }

    pub fn anagram_to_string(&self, anagram_num: AnagramNum) -> String {
        match self.0.get(&anagram_num) {
            None => "?".to_string(),
            Some(v) => {
                let strings: Vec<_> = v.iter().map(|x| x.to_string()).collect();
                if strings.len() == 1 {
                    strings[0].clone()
                } else {
                    format!("({})", strings.join(", "))
                }
            }
        }
    }
}

impl fmt::Display for AnagramSet {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut strings = Vec::new();
        for i in 0..self.num_anagrams() {
            // TODO get iterator over all AnagramNums?
            strings.push(self.anagram_to_string(AnagramNum(i)));
        }
        let s = format!("[{}]", strings.join(", "));
        fmt::Display::fmt(&s, f)
    }
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
