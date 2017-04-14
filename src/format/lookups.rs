use std::fmt::Display;
use std::collections::BTreeMap;

use types::{Chord, Sequence};
use format::*;
use format::c_array::CArray;

//  TODO don't redefine type here...
type SeqMap = BTreeMap<String, Sequence>;
type ChordMap = BTreeMap<String, Chord>;
type LenMap = BTreeMap<usize, Vec<String>>;


pub fn format_lookups (seq_map: &SeqMap,
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
