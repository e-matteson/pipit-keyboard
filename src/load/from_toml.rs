use std::collections::BTreeMap;
use toml::Value;

use types::{Options, OpDef, OpType, OpVal, Sequence, KeyPress, SwitchPos, KmapInfo, KmapPath, Name, WordInfo, ModeInfo, ModeName};

pub trait FromToml {
    fn from_toml(toml_value: &Value) -> Self;
}

impl FromToml for Options {
    fn from_toml(toml_value: &Value) -> Options {
        let mut options = Options::new();
        let map = toml_to_map(&toml_value);
        for key in map.keys(){
            let op_def: &mut OpDef = options.0.get_mut(key)
                .expect(&format!("Unknown option: {}", key));
            let val = map.get(key).expect("missing option");
            let op_val = match op_def.op_type {
                OpType::DefineString | OpType::IfdefValue =>
                    OpVal::Str(String::from_toml(val)),
                OpType::DefineInt => OpVal::Int32(i32::from_toml(val)),
                OpType::Uint8 => OpVal::Uint8(u8::from_toml(val)),
                OpType::IfdefKey => OpVal::Bool(bool::from_toml(val)),
                OpType::Mode {..} => OpVal::StrVec(Vec::from_toml(&val)),
                OpType::Array1D => OpVal::Vec(Vec::from_toml(&val)),
                OpType::Array2D => OpVal::Vec2(Vec::from_toml(&val)),
                OpType::ArrayKmap => OpVal::VecKmap(Vec::from_toml(&val)),
            };
            op_def.val = Some(op_val);
        }
        options
    }
}

impl FromToml for BTreeMap<Name, Sequence> {
    fn from_toml(toml_table: &Value) -> BTreeMap<Name, Sequence>{
        // use table directly?
        let map = toml_to_map(toml_table);
        let mut new_map = BTreeMap::new();
        for (key,val) in map.iter(){
            new_map.insert(Name::from(key), Sequence::from_toml(&val));
        }
        new_map
    }
}


impl FromToml for Vec<Name> {
    fn from_toml(toml_array: &Value) -> Vec<Name>{
        toml_to_vec(&toml_array, Name::from_toml)
    }
}

impl FromToml for Vec<String> {
    fn from_toml(toml_array: &Value) -> Vec<String>{
        toml_to_vec(&toml_array, String::from_toml)
    }
}

impl FromToml for Vec<u8> {
    fn from_toml(toml_array: &Value) -> Vec<u8>{
        toml_to_vec(&toml_array, u8::from_toml)
    }
}

impl FromToml for Vec<Vec<u8>> {
    fn from_toml(toml_array: &Value) -> Vec<Vec<u8>> {
        toml_to_vec(&toml_array, Vec::from_toml)
    }
}

impl FromToml for WordInfo {
    fn from_toml(toml_table: &Value) -> WordInfo {
        let entry = toml_to_map(toml_table);

        let seq_spelling = String::from_toml(
            entry.get("word").expect("Missing word value")
        );

        let chord_spelling = match entry.get("chord") {
            Some(x) => String::from_toml(x),
            None => seq_spelling.clone(),
        };

        let anagram_num: u8 = match entry.get("anagram") {
            Some(x) => u8::from_toml(x),
            None => 0,
        };
        WordInfo{
            seq_spelling: seq_spelling,
            chord_spelling: chord_spelling,
            anagram_num: anagram_num
        }
    }
}

impl FromToml for Sequence {
    fn from_toml(toml_value: &Value) -> Sequence {
        let key_vec =
            match toml_value {
                &Value::Table(_) => vec![KeyPress::from_toml(&toml_value)],
                &Value::Array(_) => toml_to_vec(toml_value, KeyPress::from_toml),
                _ => panic!(format!("Invalid key sequence")),
            };
        Sequence(key_vec)
    }
}

impl FromToml for KeyPress {
    fn from_toml(toml_table: &Value) -> KeyPress {
        let map =
            match toml_table {
                &Value::Table(ref t) => t,
                _ => panic!("Expected table value"),
            };
        let key = match map.get("key") {
            Some(v) => Some(String::from_toml(v)),
            None => None,
        };
        let modifier = match map.get("mod") {
            Some(v) => Some(String::from_toml(v)),
            None => None,
        };
        KeyPress::new(key, modifier)
    }
}

impl FromToml for KmapInfo {
    fn from_toml(toml_array: &Value) -> KmapInfo {
        let map = toml_to_map(toml_array);
        KmapInfo {
            path: KmapPath::from_toml(map.get("file").expect("Missing file for mode")),
            use_words: match map.get("words") {
                Some(x) => bool::from_toml(x),
                None => false,
            }
        }
    }
}

impl FromToml for KmapPath {
    fn from_toml(toml_value: &Value) -> KmapPath {
        KmapPath(String::from_toml(toml_value))
    }
}

impl FromToml for Name {
    fn from_toml(toml_value: &Value) -> Name {
        Name(String::from_toml(toml_value))
    }
}

impl FromToml for ModeName {
    fn from_toml(toml_value: &Value) -> ModeName {
        ModeName(String::from_toml(toml_value))
    }
}

impl FromToml for SwitchPos {
    fn from_toml(toml_array: &Value) -> SwitchPos {
        let int_vec = toml_to_vec(toml_array, u8::from_toml);
        if int_vec.len() != 2 {
            panic!("Expected vector of length 2");
        }
        SwitchPos {row: int_vec[0] as usize, col: int_vec[1] as usize}
    }
}

impl FromToml for ModeInfo {
    fn from_toml(toml_map: &Value) -> ModeInfo {
        let kmap_array = toml_map.get("keymaps").expect("Mode is missing keymaps");
        let is_gaming = match toml_map.get("gaming") {
            Some(b) => bool::from_toml(b),
            None    => false, // default value if "gaming" not specified
        };
        ModeInfo {
            keymaps: toml_to_vec(kmap_array, KmapInfo::from_toml),
            is_gaming: is_gaming,
        }
    }
}

impl FromToml for Vec<Vec<SwitchPos>> {
    fn from_toml(toml_array: &Value) -> Vec<Vec<SwitchPos>>{
        toml_to_vec(&toml_array,
                    |d1| toml_to_vec(d1, |d2| SwitchPos::from_toml(d2))
        )
    }
}

impl FromToml for bool {
    fn from_toml(toml_value: &Value) -> bool {
        match toml_value {
            &Value::Boolean(b) => b,
            _ => panic!("Expected boolean value"),
        }
    }
}

impl FromToml for String {
    fn from_toml(toml_value: &Value) -> String {
        match toml_value {
            &Value::String(ref s) => s.clone(),
            _ => panic!("Expected string value"),
        }
    }
}

impl FromToml for u8 {
    fn from_toml(toml_value: &Value) -> u8 {
        match toml_value {
            &Value::Integer(i) => i as u8,
            _ => panic!("Expected integer value"),
        }
    }
}

impl FromToml for i32 {
    fn from_toml(toml_value: &Value) -> i32 {
        match toml_value {
            &Value::Integer(i) => i as i32,
            _ => panic!("Expected integer value"),
        }
    }
}

pub fn toml_to_map(toml_table: &Value) -> BTreeMap<String, Value>{
    match toml_table {
        &Value::Table(ref m) => {
            m.clone()
        },
        _ => panic!("Expected table value"),
    }
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
