use std::collections::{HashMap, HashSet};
use std::fmt::{self, Display};

use types::{AnagramNum, Chord, KmapPath, Name, Word};
use types::errors::ConflictErr;
use failure::Error;

/// The Checker warns about sub-optimal configuration, like conflicting chords
/// or skipped anagram numbers. Any config issues that would break the firmware
/// should be caught in the loading or formatting code instead.
#[derive(Debug)]
pub struct Checker {
    // TODO use more references, instead of duplicating lots of stuff
    reverse_kmaps: HashMap<KmapPath, HashMap<Chord, AnagramSet>>,
    seq_names: HashSet<Name>,
    chord_names: HashSet<Name>,
    word_mod_names: HashSet<Name>,
}

#[derive(Debug)]
struct AnagramSet(HashMap<AnagramNum, Vec<Name>>);

////////////////////////////////////////////////////////////////////////////////

impl Checker {
    /// Create an empty checker.
    pub fn new() -> Checker {
        Checker {
            reverse_kmaps: HashMap::new(),
            seq_names: HashSet::new(),
            word_mod_names: HashSet::new(),
            chord_names: HashSet::new(),
        }
    }

    /// If two names have the same chord, or there's a skipped anagram
    /// number, print out that whole set of names.
    pub fn check_chords(&self) {
        // TODO take args for types of checks
        // TODO option to check for mode conflicts instead
        for (kmap, reversed) in &self.reverse_kmaps {
            let heading = format!(
                "Conflicting chords (in parens) or skipped anagrams (\"{}\") \
                 in {}:",
                AnagramSet::missing_symbol(),
                kmap
            );
            print_iter(
                &heading,
                reversed
                    .iter()
                    .filter(|&(_chord, set)| set.is_invalid())
                    .map(|(_chord, set)| set),
            );
        }
    }

    /// Compare the stored chords and sequences (and word mods), and print
    /// any names that don't appear in both.
    pub fn check_unused(&self) {
        let seqs_etc: HashSet<_> = self.seq_names
            .union(&self.word_mod_names)
            .cloned()
            .collect();
        print_iter("Unused chords:", self.chord_names.difference(&seqs_etc));
        print_iter("Unused sequences:", seqs_etc.difference(&self.chord_names));
    }

    /// Store the name of a sequence in the checker.
    pub fn insert_seq(&mut self, name: &Name) -> Result<(), Error> {
        if !self.seq_names.insert(name.to_owned()) {
            Err(ConflictErr {
                key: name.to_string(),
                container: "sequence names".into(),
            })?;
        }
        Ok(())
    }

    /// Store the name of a word mod or anagram mod in the checker. These
    /// are treated separately from sequences because it's sometimes okay for
    /// their chords to conflict with some other chords.
    pub fn insert_word_mod_or_anagram_mod(
        &mut self,
        name: &Name,
    ) -> Result<(), Error> {
        if !self.word_mod_names.insert(name.to_owned()) {
            Err(ConflictErr {
                key: name.to_string(),
                container: "word mod and anagram mod names".into(),
            })?;
        }
        Ok(())
    }

    /// Store a chord, its name, and the kmap its defined in.
    pub fn insert_chord(
        &mut self,
        name: &Name,
        chord: &Chord,
        kmap: &KmapPath,
    ) {
        let mut base_chord = chord.to_owned();
        base_chord.anagram_num = AnagramNum(0);

        self.reverse_kmaps
            .entry(kmap.to_owned())
            .or_insert_with(HashMap::new)
            .entry(base_chord)
            .or_insert_with(AnagramSet::new)
            .insert(chord.anagram_num, name.clone());
        self.chord_names.insert(name.clone());
    }
}

//////////////////////////////

impl AnagramSet {
    fn new() -> AnagramSet {
        AnagramSet(HashMap::new())
    }

    fn insert(&mut self, anagram_num: AnagramNum, name: Name) {
        self.0
            .entry(anagram_num)
            .or_insert_with(Vec::new)
            .push(name);
    }

    fn is_invalid(&self) -> bool {
        if self.has_chord_conflict() {
            return true;
        }
        for num in self.max_anagram().up_to() {
            if !self.contains_anagram(num) {
                return true;
            }
        }
        false
    }

    fn has_chord_conflict(&self) -> bool {
        for v in self.0.values() {
            match v.len() {
                1 => continue,
                // 2 => ,
                // TODO check if one is in word_mods and the other is not in
                // names_for_chord
                _ => return true,
            }
        }
        false
    }

    fn contains_anagram(&self, anagram_num: AnagramNum) -> bool {
        self.0.contains_key(&anagram_num)
    }

    fn max_anagram(&self) -> AnagramNum {
        self.0
            .keys()
            .max()
            .expect("failed to get max anagram num")
            .to_owned()
    }

    fn anagram_to_string(&self, anagram_num: AnagramNum) -> String {
        match self.0.get(&anagram_num) {
            None => AnagramSet::missing_symbol(),
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

    /// String used when there is no mapping for a give anagram number.
    fn missing_symbol() -> String {
        "???".to_string()
    }
}

impl fmt::Display for AnagramSet {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut strings = Vec::new();
        for num in self.max_anagram().up_to() {
            // TODO get iterator over all AnagramNums?
            strings.push(self.anagram_to_string(num));
        }
        let s = format!("[{}]", strings.join(", "));
        fmt::Display::fmt(&s, f)
    }
}

/// If the iterator is non-empty, print the given heading and then print each
/// element of the iterator on a separate line with some spaces before it.
fn print_iter<T>(heading: &str, iter: T)
where
    T: Iterator,
    <T as Iterator>::Item: Display,
{
    let mut iter = iter.peekable();
    if !iter.peek().is_some() {
        return;
    }
    println!("{}", heading);
    for thing in iter {
        println!("  {}", thing);
    }
    println!("\n");
}
