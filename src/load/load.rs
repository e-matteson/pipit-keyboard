use std::collections::BTreeMap;
use std::io::prelude::*;
use std::fs::File;
use toml::Value;

use types::{Sequence, Maps, SeqType, Options, KmapPath, ModeName, Name};
use load::toml_conversion::*;
use load::kmap_parser::KmapParser;


pub fn load_settings(toml_path: &str, maps: &mut Maps) -> Options {
    // Store settings in both Maps and Options
    let toml = parse_toml(toml_path);
    let options = Options::load(&toml["options"]);
    let other = toml_to_map(&toml["other"]);

    load_modes(&toml, maps);
    load_chords(&options, maps.get_kmap_paths(), maps);
    load_plains(&toml, maps);
    load_macros(&toml, maps);
    load_plain_mods(&toml, maps);
    load_word_mods(&other, maps);
    load_anagram_mods(&other, maps);
    load_word_list(&other, maps);
    load_commands(&other, maps);

    options
}

fn load_modes(toml: &Value, maps: &mut Maps) {
    let modes = toml_to_vec(toml.get("mode").expect("Modes are missing"),
                            |x| x.clone());
    for mode_table in modes.iter(){
        let name = mode_table.get("name").expect("Mode name is missing");
        maps.add_mode(
            ModeName(toml_to_string(name)),
            toml_to_mode(mode_table)
        );
    }
}

fn load_chords(options: &Options, kmap_paths: Vec<KmapPath>, maps: &mut Maps) {
    let mut kmap_parser = KmapParser::new(options);
    for kmap in kmap_paths {
        maps.add_chords(&kmap, kmap_parser.parse(&kmap));
    }
}

fn load_macros(toml: &Value, maps: &mut Maps) {
    let table = toml.get("macros").expect("Missing table: macros");
    maps.set_sequences(&SeqType::Macro, load_sequence_map(&table));
}

fn load_plains(toml: &Value, maps: &mut Maps) {
    let table = toml.get("plain_keys").expect("Missing table: plain_keys");
    maps.set_sequences(&SeqType::Plain, load_sequence_map(&table));
}

fn load_plain_mods(toml: &Value, maps: &mut Maps) {
    let table = toml.get("plain_modifiers").expect("Missing table: plain_modifiers");
    for (name, seq) in load_sequence_map(&table).iter() {
        maps.add_modifierkey(name.to_owned(), seq);
    }
}

fn load_word_mods(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let array = other.get("word_modifiers").expect("Missing array: word_modifiers");
    let wordmod_list = toml_to_vec(&array, toml_to_name);
    maps.wordmods = wordmod_list;
}

fn load_anagram_mods(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let array = other.get("anagram_modifiers").expect("Missing array: anagram_modifiers");
    let anagram_list = toml_to_vec(&array, toml_to_name);
    maps.anagrams = anagram_list;
}

fn load_commands(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let array = other.get("commands").expect("Missing array: commands");
    let command_list = toml_to_vec(&array, toml_to_name);
    maps.set_sequences(&SeqType::Command, BTreeMap::new());
    for entry in command_list.iter() {
        maps.add_command(entry)
    }
}

fn load_word_list(other: &BTreeMap<String, Value>, maps: &mut Maps) {
    let array = other.get("dictionary").expect("Missing array: dictionary");
    let word_list = toml_to_vec1_map(&array);
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
        let seq = match val {
            &Value::Table(_) => Sequence(vec![toml_to_keypress(&val)]),
            &Value::Array(_) => toml_to_sequence(&val),
            // 1 => ,
            // 2 => toml_to_sequence(&val),
            _ => panic!(format!("Invalid key sequence for {}", key)),
        };
        new_map.insert(Name::from(key), seq);
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
