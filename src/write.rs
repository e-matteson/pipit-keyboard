use std::fmt::Display;
use std::collections::HashMap;
use std::path::Path;
use std::ffi::OsStr;
use time::*;

use options::format::*;
use sequence::*;
use chord::*;

use maps::*;
use c_array::*;
use options::format::*;

const AUTHOR: &str = "rusty-pipit";

type LenMap = HashMap<usize, Vec<String>>;
type SeqMap = HashMap<String, Sequence>;
type ChordMap = HashMap<String, Chord>;


pub fn format_special(name: &str, maps: &Maps) -> Format {
    Format{
        h: format!("#define {} {}\n", name, maps.specials[name]),
        c: String::new(),
    }
}

pub fn format_wordmod(name: &str, maps: &Maps) -> Format {
    let full_name = format!("{}_chord_bytes", name);
    // format_c_array(&full_name, &maps.chords[name].to_ints(), "uint8_t")
    CArray::new(&full_name)
        .fill_1d(&maps.chords[name].to_ints())
        .format()
}


pub fn format_words (seq_map: &SeqMap, chord_map: &ChordMap) -> Format {
    format_lookups(seq_map, chord_map, "word", true, false)
}

pub fn format_plains (seq_map: &SeqMap, chord_map: &ChordMap) -> Format {
    format_lookups(seq_map, chord_map, "plain", false, true)
}

pub fn format_macros (seq_map: &SeqMap, chord_map: &ChordMap) -> Format {
    format_lookups(seq_map, chord_map, "macro", false, true)
}


fn format_lookups (seq_map: &SeqMap,
                       chord_map: &ChordMap,
                       name: &str,
                       use_compression: bool,
                       use_mods: bool)
                       -> Format
{

    let names_by_len = make_length_map(seq_map);
    let max_len: usize = *names_by_len.keys().max()
        .expect("failed to get max length");

    let mut seq_arrays: Vec<Vec<String>> = vec![Vec::new() ; 1+max_len];
    let mut chord_arrays: Vec<Vec<i64>> = vec![Vec::new() ; 1+max_len];

    for &length in names_by_len.keys() {
        let flat_seq = make_flat_sequence(seq_map, &names_by_len, length);
        println!("{:?}", flat_seq);
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
    println!("{:?}, {}", names_by_len, length);
    for name in &names_by_len[&length] {
        flat_seq.extend(seq_map[name].clone());
    }
    flat_seq
}

fn make_length_map(seq_map: &HashMap<String, Sequence>) -> LenMap {
    // TODO layouts: weave name order
    let mut names_by_len = HashMap::new();
    let mut names: Vec<_> = seq_map.keys().collect();
    names.sort();
    for name in names{
        let length = seq_map[name].len();
        names_by_len.entry(length).or_insert(Vec::new()).push(name.to_owned());
    }
    names_by_len
}

pub fn format_intro(h_file_name: &str) -> Format{
    let autogen_message = make_autogen_message();
    let guard_name = make_guard_name(h_file_name);
    let mut f = Format::new();

    f.h += &autogen_message;
    f.h += &format!("#ifndef {}\n#define {}\n\n", guard_name, guard_name);
    f.h += "#include <Arduino.h>\n";
    f.h += "#include \"keycodes.h\"\n\n";
    f.h += "typedef void (*voidFuncPtr)(void);\n\n";
    f.h += make_debug_macros().as_ref();

    f.c += &autogen_message;
    f.c += &format!("#include \"{}\"\n\n", h_file_name);
    f
}

fn make_debug_macros() -> String {
    // TODO clean up debug macros
    let mut s = String::new();
    s += "#if DEBUG_MESSAGES == 0\n";
    s += "#define DEBUG1(msg)\n";
    s += "#define DEBUG1_LN(msg)\n";
    s += "#define DEBUG2(msg)\n";
    s += "#define DEBUG2_LN(msg)\n";
    s += "#endif\n\n";
    s += "#if DEBUG_MESSAGES == 1\n";
    s += "#define DEBUG1(msg) Serial.print(msg)\n";
    s += "#define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "#define DEBUG2(msg)\n";
    s += "#define DEBUG2_LN(msg)\n";
    s += "#endif\n\n";
    s += "#if DEBUG_MESSAGES == 2\n";
    s += "#define DEBUG1(msg) Serial.print(msg)\n";
    s += "#define DEBUG1_LN(msg) Serial.println(msg)\n";
    s += "#define DEBUG2(msg) Serial.print(msg)\n";
    s += "#define DEBUG2_LN(msg) Serial.println(msg)\n";
    s += "#endif\n\n ";
    s
}

pub fn format_outro() -> Format {
    Format {
        h: "\n#endif\n".to_string(),
        c: String::new(),
    }
}

fn make_autogen_message( ) -> String {
    let s = format!("/**\n * Automatically generated by {} on:  {}\n",
                    AUTHOR,
                    now().strftime("%c").unwrap()
    );
    s + " * Do not make changes here, they will be overwritten.\n */\n\n"
}

fn make_guard_name(h_file_name: &str) -> String {
    // TODO remove unsafe characters, like the python version
    // TODO is this guaranteed to be the basename already?
    let p = Path::new(h_file_name)
        .file_name()
        .expect("failed to get file name")
        .to_str()
        .unwrap()
        .to_string()
        .to_uppercase()
        .replace(".", "_");
    p + "_"

}
