use std::collections::BTreeMap;
use std::io::prelude::*;
use std::fs::File;
use toml::Value;

use types::{Sequence, Maps, Options};
use load::toml_conversion::*;
use load::kmap_parser::KmapParser;


pub fn load_settings(toml_path: &str, maps: &mut Maps) -> Options {
    // Stores settings in both Maps and Options
    let toml = parse_toml(toml_path);
    let options = Options::load(&toml["options"]);
    let other = toml_to_map(&toml["other"]);

    maps.add_modes(&options.get_modes());

    load_chords(&options, maps);
    load_macros(&toml, maps);
    load_plains(&toml, maps);
    load_word_list(&other, maps);
    load_wordmod_list(&other, maps);
    load_special_list(&other, maps);

    options
}

fn load_chords(options: &Options, maps: &mut Maps) {
    let mut kmap_parser = KmapParser::new(options);

    for mode in &options.get_modes(){
        let kmap_path = options.get_val(mode).unwrap_str();
        maps.add_chords(mode, kmap_parser.parse(kmap_path));
    }
}

fn load_macros(toml: &Value, maps: &mut Maps) {
    maps.macros = load_sequence_map(&toml["macros"]);
}

fn load_plains(toml: &Value, maps: &mut Maps) {
    maps.plains = load_sequence_map(&toml["plain_keys"]);
}

fn load_wordmod_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let mut wordmod_list = toml_to_vec1_string(&other["wordmods"]);
    wordmod_list.sort();
    maps.wordmods = wordmod_list;
}

fn load_special_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let mut special_list = toml_to_vec1_string(&other["special_functions"]);
    special_list.sort();
    for entry in special_list.iter() {
        maps.add_special(entry)
    }
}

fn load_word_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    // TODO use separate word lists for different modes?
    let mut word_list = toml_to_vec2_string(&other["words"]);
    word_list.sort();
    for mode in &maps.options.get_modes_with_words(){
        for entry in word_list.iter() {
            maps.add_word(entry, mode)
        }
    }
}

fn load_sequence_map(parsed_toml: &Value) -> BTreeMap<String, Sequence>{
    let map = toml_to_map(parsed_toml);
    let mut new_map: BTreeMap<String, Sequence> = BTreeMap::new();
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
    let toml = buffer.parse::<Value>().expect("failed to parse settings file!");
    toml
}
