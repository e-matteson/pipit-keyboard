use std::collections::BTreeMap;
use toml::Value;

use types::{Chord, Sequence, KeyPress, SwitchPos};


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

pub fn toml_to_vec1_string(toml_array: &Value) -> Vec<String>{
    toml_to_vec(&toml_array, toml_to_string)
}

pub fn toml_to_vec2_string(toml_array: &Value) -> Vec<Vec<String>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1, toml_to_string)
    )
}

pub fn toml_to_vec1_int(toml_array: &Value) -> Vec<i64>{
    toml_to_vec(&toml_array, toml_to_int)
}

pub fn toml_to_vec2_int(toml_array: &Value) -> Vec<Vec<i64>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1, toml_to_int)
    )
}

pub fn toml_to_vec3_int(toml_array: &Value) -> Vec<Vec<Vec<i64>>>{
    toml_to_vec(&toml_array,
                |d1| toml_to_vec(d1,
                                 |d2| toml_to_vec(d2, toml_to_int))
    )
}


fn toml_to_vec<T, F>(toml_array: &Value, f: F) -> Vec<T> where F: Fn(&Value)->T {
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

fn toml_to_keypress(toml_array: &Value) -> KeyPress {
    let string_vec = toml_to_vec(toml_array, toml_to_string);
    if string_vec.len() != 2 {
        panic!("Expected vector of length 2");
    }
    KeyPress {key: string_vec[0].to_owned(), modifier: string_vec[1].to_owned()}
}
