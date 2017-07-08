use std::collections::BTreeMap;
use std::io::prelude::*;
use std::fs::File;
use toml::Value;

use types::{Sequence, Maps, SeqType, Options, KmapPath, ModeName, Name};
use load::toml_conversion::*;
use load::kmap_parser::KmapParser;


pub fn load_settings(toml_path: &str, maps: &mut Maps) -> Options {
    // Stores settings in both Maps and Options
    let toml = parse_toml(toml_path);
    let options = Options::load(&toml["options"]);
    let other = toml_to_map(&toml["other"]);

    load_modes(&toml, maps);
    load_chords(&options, maps.get_kmap_paths(), maps);
    load_wordmod_list(&other, maps);
    load_anagram_list(&other, maps);
    load_macros(&toml, maps);
    load_plains(&toml, maps);
    load_modifierkeys(&toml, maps);
    load_word_list(&other, maps);
    load_command_list(&other, maps);

    options
}

fn load_modes(toml: &Value, maps: &mut Maps) {
    let map = toml_to_map(&toml["modes"]);
    for (key,val) in map.iter(){
        maps.add_mode(ModeName(key.to_string()),
                      toml_to_vec(&val, toml_to_kmap_info));
    }


    // Must be called before loading chords or sequences.
    // for mode in options.get_modes(){
    //     maps.add_mode(&mode, &options.get_kmaps(&mode));
    // }
}

fn load_chords(options: &Options, kmap_paths: Vec<KmapPath>, maps: &mut Maps) {
    let mut kmap_parser = KmapParser::new(options);
    for kmap in kmap_paths {
        maps.add_chords(&kmap, kmap_parser.parse(&kmap));
    }
}

fn load_macros(toml: &Value, maps: &mut Maps) {
    maps.set_sequences(&SeqType::Macro, load_sequence_map(&toml["macros"]));
}

fn load_plains(toml: &Value, maps: &mut Maps) {
    maps.set_sequences(&SeqType::Plain, load_sequence_map(&toml["plain_keys"]));
}

fn load_modifierkeys(toml: &Value, maps: &mut Maps) {
    for (name, seq) in load_sequence_map(&toml["modifiers"]).iter() {
        maps.add_modifierkey(name.to_owned(), seq);
    }
}

fn load_wordmod_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let wordmod_list = toml_to_vec(&other["word_modifiers"], toml_to_name);
    maps.wordmods = wordmod_list;
}

fn load_anagram_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let anagram_list = toml_to_vec(&other["anagram_modifiers"], toml_to_name);
    maps.anagrams = anagram_list;
}

fn load_command_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let command_list = toml_to_vec(&other["commands"], toml_to_name);
    maps.set_sequences(&SeqType::Command, BTreeMap::new());
    for entry in command_list.iter() {
        maps.add_command(entry)
    }
}

fn load_word_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    // TODO use separate word lists for different modes?
    let word_list = toml_to_vec1_map(&other["dictionary"]);
    // Initialize empty word sequence map before adding words to it
    maps.set_sequences(&SeqType::Word, BTreeMap::new());
    for mode in &maps.get_kmaps_with_words(){
        for entry in word_list.iter() {
            let (seq_spelling, chord_spelling, anagram) = parse_word_entry(entry);
            maps.add_word(&seq_spelling, &chord_spelling, anagram, mode)
        }
    }
}

fn parse_word_entry(entry: &BTreeMap<String, Value>) -> (String, String, u8){
    let seq_spelling = match entry.get("word") {
        Some(x) => match x {
            &Value::String(ref s) => s.clone(),
            _ => panic!("expected string")
        },
        _ => panic!("No word provided in word_list entry")
    };

    let chord_spelling = match entry.get("chord") {
        Some(x) => match x {
            &Value::String(ref s) => s.clone(),
            _ => panic!("expected string"),
        },
        _ => seq_spelling.clone(),
    };

    let anagram: u8 = match entry.get("anagram") {
        Some(a) => match a {
            &Value::Integer(i) => i as u8,
            _ => panic!("expected integer"),
        },
        _ => 0,
    };
    (seq_spelling, chord_spelling, anagram)
}


fn load_sequence_map(parsed_toml: &Value) -> BTreeMap<Name, Sequence>{
    let map = toml_to_map(parsed_toml);
    let mut new_map: BTreeMap<Name, Sequence> = BTreeMap::new();
    for (key,val) in map.iter(){
        new_map.insert(Name(key.clone()), toml_to_sequence(&val));
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
