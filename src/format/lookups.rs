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
    let names_by_len = make_length_map(&seq_map, &chord_maps);

    let seq_arrays = make_seq_arrays(seq_map, &names_by_len, use_compression, use_mods);
    let chord_arrays = make_chord_arrays(chord_maps, &names_by_len);

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

fn max_len(names_by_len: &LenMap) -> usize {
    *names_by_len.keys().max()
        .expect("failed to get max length")
}

fn make_seq_arrays(seq_map: &SeqMap, names_by_len: &LenMap,
                   use_compression: bool, use_mods: bool)
                   -> Vec<Vec<String>>
{
    let mut seq_arrays = Vec::new();
    for length in 0..max_len(names_by_len)+1 {
        let subarray =
            match names_by_len.get(&length) {
                Some(names) =>
                    make_flat_sequence(seq_map, names)
                    .to_bytes(use_compression, use_mods) ,
                None => Vec::new(),
            };
        seq_arrays.push(subarray);
    }
    seq_arrays
}

fn make_chord_arrays(chord_maps: &BTreeMap<String, ChordMap>,
                     names_by_len: &LenMap)
                     -> Vec<Vec<Vec<i64>>>
{
    let mut chord_arrays = Vec::new();
    for mode in chord_maps.keys() {
        let mut mode_array = Vec::new();

        for length in 0..max_len(names_by_len)+1 {
            mode_array.push(
                make_chord_subarray(&names_by_len, length, &chord_maps[mode])
            );
        }
        chord_arrays.push(mode_array);
    }
    chord_arrays
}

fn make_chord_subarray(names_by_len: &LenMap, length: usize, chords: &ChordMap)
                       -> Vec<i64>
{
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
    reorder_length_map(names_by_len, chord_maps)
}

fn reorder_length_map(names_by_len: LenMap, chord_maps: &BTreeMap<String, ChordMap>)
                      -> LenMap
{
    /// Alternately pick one name from each mode, so no 2 successive chords for
    /// a mode will be too far apart.

    // Find the first name that's used in the given mode.
    let find_name =
        |names: &Vec<String>, mode| names.iter()
        .position(|name| chord_maps[mode].contains_key(name));

    let mut new_map: LenMap = BTreeMap::new();
    for (length, mut names) in names_by_len.into_iter() {
        let mut v: Vec<String> = Vec::new();
        let mut remaining_modes: Vec<_> = chord_maps.keys().collect();
        while !names.is_empty() {   // For each entry/sequence:
            if remaining_modes.len() == 1 {
                // Just dump in all the remaining entries.
                v.extend(names.clone());
                // Done with this length!
                break;
            }
            for (mode_index, &mode) in remaining_modes.clone().iter().enumerate() {
                match find_name(&names, mode) {
                    Some(position) => {
                        // Move the entry to the new map
                        v.push(names[position].clone());
                        names.swap_remove(position);
                    },
                    None => {
                        // All of this mode's entries have already been moved.
                        // Skip it from now on.
                        remaining_modes.remove(mode_index);
                    },
                }
            }
        }
        new_map.insert(length, v);
    }
    new_map
}
