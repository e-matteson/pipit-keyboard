use std::fmt::Display;
use std::collections::BTreeMap;

use types::{Chord, Sequence};
use format::*;
use format::c_array::CArray;

type SeqMap =   BTreeMap<String, Sequence>;
type ChordMap = BTreeMap<String, Chord>;
type LenMap =   BTreeMap<usize, Vec<String>>;


pub fn format_lookups (seq_map: &SeqMap, chord_maps: &BTreeMap<String, ChordMap>,
                       name: &str, use_compression: bool,
                       use_mods: bool) -> Format
{
    // TODO refactor!!!
    let names_by_len = make_length_map(&seq_map, &chord_maps);
    let max_len: usize = *names_by_len.keys().max()
        .expect("failed to get max length");

    let mut seq_arrays: Vec<Vec<String>> = vec![Vec::new() ; 1+max_len];
    // TODO hashmap by mode instead?
    let mut chord_arrays: Vec<Vec<Vec<i64>>> =
        vec![vec![Vec::new() ; 1+max_len] ; chord_maps.keys().len()];

    for length in 0..max_len+1 {
        seq_arrays[length] =
            match names_by_len.get(&length) {
                Some(names) =>
                    make_flat_sequence(seq_map, names)
                    .to_bytes(use_compression, use_mods) ,
                None => Vec::new(),
            };

        for (mode_index, mode) in chord_maps.keys().enumerate(){
            chord_arrays[mode_index][length] =
                make_chord_array(&names_by_len, length, &chord_maps[mode]);
        }
    }

    let mut f = Format::new();

    let mut chord_mode_array_names: Vec<String> = Vec::new();
    for (mode_index, mode) in chord_maps.keys().enumerate(){
        // TODO don't clone so much
        let array_name = format!("{}_{}_chord_lookup", name, mode);
        chord_mode_array_names.push(array_name.clone());
        f.append(
            // TODO not extern
            &format_length_arrays(
                chord_arrays[mode_index].clone(),
                &array_name));
    }

    f.append(&CArray::new(&format!("{}_chord_lookup", name))
             .is_extern(true)
             .c_type("uint8_t**")
             .fill_1d(&chord_mode_array_names)
             .format());

   f.append(&format_length_arrays(seq_arrays,
                                  &format!("{}_seq_lookup", name)));
    f
}

fn make_chord_array(names_by_len: &LenMap, length: usize, chords: &ChordMap) -> Vec<i64>{
    // names: &Vec<String>
    let mut ints: Vec<i64> = Vec::new();
    if let Some(names) = names_by_len.get(&length) {
        let mut last_index: usize = 0;
        for (index, name) in names.iter().enumerate() {
            if !chords.contains_key(name) {
                continue
            }
            ints.push((index - last_index) as i64); // offset from last chord
            ints.extend(chords.get(name)
                      .expect("failed to get chord")
                      .to_ints());
            last_index = index;
        }
    }
    ints.push(0);  // last blank offset
    ints.extend(Chord::new().to_ints());  // last blank chord
    ints
}


fn format_length_arrays <T> (arrays: Vec<Vec<T>>, name: &str) -> Format
    where T: Display + Clone
{
    let mut subarray_names: Vec<_> = (0..arrays.len())
        .map(|x| format!("{}_{}", name, x))
        .collect();
    let mut f = Format::new();
    for i in 0..subarray_names.len() {
        f.append(&CArray::new(&subarray_names[i])
                 .is_extern(false)
                 .fill_1d(&arrays[i])
                 .format()
        );
    }

    subarray_names.push("NULL".to_string());
    f.append(&CArray::new(&name)
             .is_extern(true)
             .c_type("uint8_t*")
             .fill_1d(&subarray_names)
             .format());
    f
}


fn make_flat_sequence(seq_map: &SeqMap, names: &Vec<String>)
                      -> Sequence {
    let mut flat_seq = Sequence::new();
    for name in names {
        flat_seq.extend(seq_map[name].clone());
    }
    flat_seq
}

fn make_length_map(seq_map: &SeqMap, chord_maps: &BTreeMap<String, ChordMap>) -> LenMap {
    // collect names by the lengths of their sequences
    let mut names_by_len = BTreeMap::new();
    let mut names: Vec<_> = seq_map.keys().collect();
    names.sort();
    for name in names{
        let length = seq_map[name].len();
        names_by_len.entry(length).or_insert(Vec::new()).push(name.to_owned());
    }
    // re-order the names
    // TODO clone less?
    let mut new_names_by_len: LenMap = BTreeMap::new();
    for (length, mut list) in names_by_len.into_iter() {
        new_names_by_len.insert(length, Vec::new());

        while !list.is_empty() {
            for chords in chord_maps.values() {
                match list.iter().position(|name| chords.contains_key(name)) {
                    Some(index) => {
                        new_names_by_len
                            .get_mut(&length)
                            .unwrap()
                            .push(list[index].clone());
                        list.swap_remove(index);
                    },
                    None => (), //TODO remove mode from a list
                }
            }
        }
    }
    new_names_by_len
}
