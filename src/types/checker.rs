use itertools::Itertools;
use std::borrow::Cow;
use std::collections::{BTreeMap, HashMap, HashSet};
use std::fmt::{self, Display};

use types::{
    AllData, AnagramNum, Chord, KmapOrder, LayerInfo, LayerName, ModeInfo,
    ModeName, Name,
};

/// The Checker warns about sub-optimal configuration, like conflicting chords
/// or skipped anagram numbers. Any config issues that would break the firmware
/// should be caught in the loading or formatting code instead.
#[derive(Debug)]
struct Checker {
    // TODO use more references, instead of duplicating lots of stuff
    reverse_layer_lookups:
        HashMap<LayerName, HashMap<Chord<KmapOrder>, AnagramSet>>,
    seq_names: HashSet<Name>,
    chord_names: HashSet<Name>,
    word_mod_names: HashSet<Name>,
    modes: BTreeMap<ModeName, ModeInfo>,
    layers: BTreeMap<LayerName, LayerInfo>,
}

#[derive(Debug)]
struct AnagramSet(HashMap<AnagramNum, Vec<Name>>);

////////////////////////////////////////////////////////////////////////////////

impl AllData {
    pub fn check(&self) {
        let checker = self.checker();
        checker.check_unused();
        checker.check_conflicts();
        checker.check_gaming_modes();
        // checker.check_big_chords(4);
    }

    fn checker(&self) -> Checker {
        Checker {
            reverse_layer_lookups: self.reverse_chords(),
            seq_names: self.sequences.names().cloned().collect(),
            chord_names: self.chords.names().cloned().collect(),
            word_mod_names: self.word_mods(),
            modes: self.modes.clone(),
            layers: self.layers.clone(),
        }
    }

    fn reverse_chords(
        &self,
    ) -> HashMap<LayerName, HashMap<Chord<KmapOrder>, AnagramSet>> {
        let mut reversed = HashMap::new();
        for (layer_name, chord_map) in self.chords.iter() {
            for (name, chord) in chord_map.iter() {
                let mut base_chord = chord.to_owned();
                base_chord.anagram_num = AnagramNum::default();

                reversed
                    .entry(layer_name.to_owned())
                    .or_insert_with(HashMap::new)
                    .entry(base_chord)
                    .or_insert_with(AnagramSet::new)
                    .insert(chord.anagram_num, name.clone());
            }
        }
        reversed
    }

    fn word_mods(&self) -> HashSet<Name> {
        self.word_mods
            .iter()
            .chain(self.anagram_mods.iter())
            .cloned()
            .collect()
    }
}

impl Checker {
    /// If two names have the same chord in the same mode, or there's a skipped
    /// anagram number, print out that whole set of names.
    fn check_conflicts(&self) {
        for (mode_name, mode_info) in &self.modes {
            let mut reverse_mode: HashMap<Chord<KmapOrder>, AnagramSet> =
                HashMap::new();
            for layer_name in &mode_info.layers {
                for (chord, anagram_set) in
                    self.reverse_layer_lookups.get(layer_name).unwrap()
                {
                    reverse_mode
                        .entry(chord.to_owned())
                        .or_insert_with(AnagramSet::new)
                        .extend(anagram_set);
                }
            }
            let heading = format!(
                "\nConflicting chords (in parens) or skipped anagrams \
                 (\"{}\") in \'{}\':",
                AnagramSet::missing_symbol(),
                mode_name
            );
            print_iter(
                heading,
                reverse_mode
                    .iter()
                    .filter(|&(_chord, set)| {
                        set.is_invalid(&self.word_mod_names)
                    })
                    .map(|(_chord, set)| set),
            );
        }
    }

    /// Compare the stored chords and sequences (and word mods), and print
    /// any names that don't appear in both.
    fn check_unused(&self) {
        let seqs_and_mods: HashSet<_> = self
            .seq_names
            .union(&self.word_mod_names)
            .cloned()
            .collect();
        print_iter(
            "Unused chords:",
            self.chord_names.difference(&seqs_and_mods),
        );
        print_iter(
            "Unused sequences:",
            seqs_and_mods.difference(&self.chord_names),
        );
    }

    fn check_gaming_modes(&self) {
        for (mode_name, mode_info) in &self.modes {
            if !mode_info.gaming {
                continue;
            }
            for layer_name in &mode_info.layers {
                let layer_info =
                    self.layers.get(layer_name).expect("unknown layer name");
                match layer_info {
                    LayerInfo::KmapLayer { .. } => (),
                    LayerInfo::WordLayer { .. }
                    | LayerInfo::SnippetLayer { .. } => {
                        println!(
                            "Don't use words in a gaming mode, \
                             multi-switch chords won't work: '{}' \n",
                            mode_name
                        );
                    }
                }
                print_iter(
                    format!(
                        "Multi-switch chords won't work in gaming modes.\nIn {}'s {}:",
                        mode_name,
                        layer_name),
                    self.multiswitch_chords(layer_name, 1),
                );
            }
        }
    }

    #[allow(unused)]
    fn check_big_chords(&self, chord_size_threshold: usize) {
        for (mode_name, mode_info) in &self.modes {
            let mut size_groups: BTreeMap<usize, Vec<String>> = BTreeMap::new();
            for layer_name in &mode_info.layers {
                let layer_info =
                    self.layers.get(layer_name).expect("unknown layer name");
                match layer_info {
                    LayerInfo::KmapLayer { .. }
                    | LayerInfo::SnippetLayer { .. } => (),
                    LayerInfo::WordLayer { .. } => {
                        for (chord, anagram_set) in self
                            .reverse_layer_lookups
                            .get(layer_name)
                            .expect(
                                "checker's layers don't match all_data's modes",
                            )
                            .iter()
                        {
                            let size = chord.count_pressed();
                            if size >= chord_size_threshold {
                                size_groups
                                    .entry(size)
                                    .or_default()
                                    .push(anagram_set.all_names().join(", "));
                            }
                        }
                    }
                }
            }
            if !size_groups.is_empty() {
                println!("Big chords in {}:", mode_name);
                for (size, mut entries) in size_groups.into_iter() {
                    println!("  {}:", size);
                    entries.sort();
                    for entry in entries.iter() {
                        println!("    {}:", entry);
                    }
                }
            }
        }
    }

    fn multiswitch_chords(
        &self,
        layer_name: &LayerName,
        allowed_num_switches: usize,
    ) -> impl Iterator<Item = &Name> {
        self.reverse_layer_lookups
            .get(layer_name)
            .expect("checker's layers don't match all_data's modes")
            .iter()
            .filter(move |(chord, _)| {
                chord.count_pressed() > allowed_num_switches
            })
            .flat_map(|(_, anagram_set)| anagram_set.all_names())
    }
}

impl AnagramSet {
    fn new() -> Self {
        AnagramSet(HashMap::new())
    }

    fn insert(&mut self, anagram_num: AnagramNum, name: Name) {
        self.0
            .entry(anagram_num)
            .or_insert_with(Vec::new)
            .push(name);
    }

    fn extend(&mut self, other: &AnagramSet) {
        for (&anagram_num, names) in other.iter() {
            self.0
                .entry(anagram_num)
                .or_insert_with(Vec::new)
                .extend_from_slice(names);
        }
    }

    fn is_invalid(&self, word_mod_names: &HashSet<Name>) -> bool {
        if self.has_chord_conflict(word_mod_names) {
            return true;
        }
        for num in self.max_anagram().up_to() {
            if !self.contains_anagram(num) {
                return true;
            }
        }
        false
    }

    fn has_chord_conflict(&self, word_mod_names: &HashSet<Name>) -> bool {
        for v in self.0.values() {
            match v.len() {
                1 => continue,
                2 => {
                    if !is_pair_legal(&v[0], &v[1], word_mod_names) {
                        return true;
                    }
                }
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
            None => Self::missing_symbol(),
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

    fn all_names(&self) -> impl Iterator<Item = &Name> {
        self.0.values().flat_map(|v| v.iter())
    }

    fn iter(&self) -> impl Iterator<Item = (&AnagramNum, &Vec<Name>)> {
        self.0.iter()
    }
}

impl fmt::Display for AnagramSet {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // TODO use color?
        let mut strings = Vec::new();
        for num in self.max_anagram().up_to() {
            // TODO get iterator over all AnagramNums?
            strings.push(self.anagram_to_string(num));
        }
        let s = format!("anagrams: [{}]", strings.join(", "));
        fmt::Display::fmt(&s, f)
    }
}

/// If the iterator is non-empty, print the given heading and then print each
/// element of the iterator on a separate line with some spaces before it.
fn print_iter<'a, T, U>(heading: U, iter: T)
where
    T: Iterator,
    <T as Iterator>::Item: Display,
    U: Into<Cow<'a, str>>,
{
    let mut iter = iter.peekable();
    if iter.peek().is_none() {
        return;
    }
    println!("{}", heading.into());
    for thing in iter {
        println!("  {}", thing);
    }
    println!();
}

/// Return true if one is a `word_mod` or `anagram_mod`, and the other cannot be
/// used in a word chord (letters, mostly). This lets us map
/// `word_mods`/`anagram_mods` to chords that do something different when
/// pressed separately from a word (like `mod_shift` and `mod_capital`). It
/// doesn't catch all bad mappings, though! If a `word_mod`/`anagram_mod`
/// shares even a single switch with a multi-switch letter, that will mess up
/// the word lookup process. We don't check for that yet, because it's unlikely
/// to happen accidentally and it's annoying to implement.
// TODO make sure the above warning is easily findable
fn is_pair_legal(
    name1: &Name,
    name2: &Name,
    word_mod_names: &HashSet<Name>,
) -> bool {
    let okay = |a, b| {
        word_mod_names.contains(a) && !word_mod_names.contains(b)
        // TODO re-add some test like this one
        // && !WordBuilder::allowed_in_chord(b)
    };
    okay(name1, name2) || okay(name2, name1)
}
