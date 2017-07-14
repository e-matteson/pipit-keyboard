use std::collections::BTreeMap;
use toml::Value;

use types::{Sequence, KeyPress, SwitchPos, KmapInfo, KmapPath, Name, ModeInfo};


pub fn toml_to_map(toml_table: &Value) -> BTreeMap<String, Value>{
    match toml_table {
        &Value::Table(ref m) => {
            m.clone()
        },
        _ => panic!("Expected table value"),
    }
}

pub fn toml_to_sequence(toml_array: &Value) -> Sequence {
    Sequence(toml_to_vec(toml_array, toml_to_keypress))
}

pub fn toml_to_kmap(toml_array: &Value) -> Vec<Vec<SwitchPos>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1, |d2| toml_to_switchpos(d2))
    )
}


pub fn toml_to_kmap_info(toml_array: &Value) -> KmapInfo {
    // println!("info: {:?}", toml_array);
    let map = toml_to_map(toml_array);
    KmapInfo {
        path: toml_to_kmap_path(map.get("file").expect("Missing file for mode")),
        use_words: match map.get("words") {
            Some(x) => toml_to_bool(x),
            None => false,
        }
    }
}

pub fn toml_to_kmap_path(toml_value: &Value) -> KmapPath {
    KmapPath(toml_to_string(toml_value))
}

pub fn toml_to_name(toml_value: &Value) -> Name {
    Name(toml_to_string(toml_value))
}

pub fn toml_to_vec1_string(toml_array: &Value) -> Vec<String>{
    toml_to_vec(&toml_array, toml_to_string)
}


// pub fn toml_to_vec2_string(toml_array: &Value) -> Vec<Vec<String>>{
//     toml_to_vec(&toml_array,
//                 |d1| toml_to_vec(d1, toml_to_string)
//     )
// }

pub fn toml_to_vec1_int(toml_array: &Value) -> Vec<i64>{
    toml_to_vec(&toml_array, toml_to_int)
}

pub fn toml_to_vec2_int(toml_array: &Value) -> Vec<Vec<i64>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1, toml_to_int)
    )
}

// pub fn toml_to_vec3_int(toml_array: &Value) -> Vec<Vec<Vec<i64>>>{
//     toml_to_vec(&toml_array,
//                 |d1| toml_to_vec(d1,
//                                  |d2| toml_to_vec(d2, toml_to_int))
//     )
// }

pub fn toml_to_vec1_map(toml_array: &Value) -> Vec<BTreeMap<String, Value>>{
    toml_to_vec(&toml_array, toml_to_map)
}


pub fn toml_to_vec<T, F>(toml_array: &Value, f: F) -> Vec<T> where F: Fn(&Value)->T {
    match toml_array {
        &Value::Array(ref vector) => {
            vector.iter()
                .map(f)
                .collect()
        },
        _ => panic!("Expected array value"),
    }
}

fn toml_to_int(toml_value: &Value) -> i64 {
    match toml_value {
        &Value::Integer(i) => i,
        _ => panic!("Expected integer value"),
    }
}

fn toml_to_bool(toml_value: &Value) -> bool {
    match toml_value {
        &Value::Boolean(b) => b,
        _ => panic!("Expected boolean value"),
    }
}

pub fn toml_to_string(toml_value: &Value) -> String {
    match toml_value {
        &Value::String(ref s) => s.clone(),
        _ => panic!("Expected string value"),
    }
}

fn toml_to_switchpos(toml_array: &Value) -> SwitchPos {
    let int_vec = toml_to_vec(toml_array, toml_to_int);
    if int_vec.len() != 2 {
        panic!("Expected vector of length 2");
    }
    SwitchPos {row: int_vec[0] as usize, col: int_vec[1] as usize}
}

pub fn toml_to_keypress(toml_table: &Value) -> KeyPress {
    let key_press_map: BTreeMap<_,_> = match toml_table {
        &Value::Table(ref t) =>
            t.iter()
            .map(|(k, v)| (k.to_owned(), toml_to_string(v)))
            .collect(),
        _ => panic!("Expected table value"),
    };
    KeyPress::new(key_press_map.get("key"), key_press_map.get("mod"))
}

pub fn toml_to_mode(toml_map: &Value) -> ModeInfo {
    let kmap_array = toml_map.get("keymaps").expect("Mode is missing keymaps");
    let is_gaming = match toml_map.get("gaming") {
        Some(b) => toml_to_bool(b),
        None    => false, // default value if "gaming" not specified
    };
    ModeInfo {
        keymaps: toml_to_vec(kmap_array, toml_to_kmap_info),
        is_gaming: is_gaming,
    }
}
