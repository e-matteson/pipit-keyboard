// TODO replace all this with a struct-based settings.rs?

use std::collections::HashMap;
use std::collections::BTreeMap;
use std::io::prelude::*;
use std::fs::File;


use toml::Value;

use sequence::*;
use options::*;
use maps::*;
use self::toml_convertor::*;
use self::options::*;

pub struct Loader{
    // For temporarily holding the loaded values
    pub options: Options,
    pub macros: HashMap<String, Sequence>,
    pub plain_keys: HashMap<String, Sequence>,
    pub special_list: Vec<String>,
    pub word_list: Vec<Vec<String>>,
    pub wordmod_list: Vec<String>,
}

impl Loader{

    pub fn load(toml_path: &str) -> Loader{
        let parsed = parse_toml(toml_path);

        let mut options = Options::new();
        options.load(&parsed["options"]);

        let macros = load_sequence_map(&parsed["macros"]);
        let plain_keys = load_sequence_map(&parsed["plain_keys"]);

        let other = toml_to_map(&parsed["other"]);
        let special_list = toml_to_vec1_string(&other["special_functions"]);
        let wordmod_list = toml_to_vec1_string(&other["wordmods"]);
        let word_list = toml_to_vec2_string(&other["words"]);

        Loader{
            options: options,
            macros: macros,
            plain_keys: plain_keys,
            special_list: special_list,
            word_list: word_list,
            wordmod_list: wordmod_list,
        }
    }
}

fn load_sequence_map(parsed_toml: &Value) -> HashMap<String, Sequence>{
    let map = toml_to_map(parsed_toml);
    let mut new_map: HashMap<String, Sequence> = HashMap::new();
    for (key,val) in map.iter(){
        new_map.insert(key.clone(), toml_to_sequence(&val));
    }
    new_map
}

fn parse_toml(toml_path: &str) -> Value {
    let mut f: File = File::open(toml_path)
        .expect("failed to open settings file!");
    let mut buffer = String::new();
    f.read_to_string(&mut buffer).expect("failed to read settings file!");
    let parsed = buffer.parse::<Value>().expect("failed to parse settings file!");
    parsed
}
