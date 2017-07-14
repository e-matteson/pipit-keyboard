use std::collections::BTreeMap;
use std::io::prelude::*;
use std::fs::File;
use toml::Value;

use types::{Maps, SeqType, Options, ModeName, ModeInfo, WordInfo};
use load::{KmapParser, FromToml, toml_to_vec};


impl Options {
    pub fn load(parsed_options: &Value) -> Options{
        let mut options = Options::from_toml(parsed_options);
        options.verify_requirements();
        options.set_auto();
        options
    }
}

impl Maps {
    pub fn load(toml_path: &str) -> Maps {
        /// Load stuff into both Options and Maps
        // TODO don't clone things so much?
        let toml = parse_toml(toml_path);
        let options = Options::load(get_entry(&toml, "options"));

        let mut maps = Maps::new();
        maps.load_modes(&toml);

        maps.load_chords(&options);
        maps.options = options;

        maps.load_plains(&toml);
        maps.load_macros(&toml);
        maps.load_plain_mods(&toml);

        let other = get_entry(&toml, "other");
        maps.load_word_mods(&other);
        maps.load_anagram_mods(&other);
        maps.load_word_list(&other);
        maps.load_commands(&other);
        maps
    }

    fn load_modes(&mut self, toml: &Value) {
        let modes = toml_to_vec(get_entry(toml, "mode"), |x| x.clone());
        for mode_table in modes.iter(){
            let name = mode_table.get("name").expect("Mode name is missing");
            self.add_mode(
                ModeName::from_toml(name),
                ModeInfo::from_toml(mode_table)
            );
        }
    }

    fn load_chords(&mut self, options: &Options) {
        let mut kmap_parser = KmapParser::new(options);
        for kmap in self.get_kmap_paths() {
            self.add_chords(&kmap, kmap_parser.parse(&kmap));
        }
    }

    fn load_macros(&mut self, toml: &Value) {
        let table = get_entry(toml, "macros");
        self.set_sequences(&SeqType::Macro, BTreeMap::from_toml(&table));
    }

    fn load_plains(&mut self, toml: &Value) {
        let table = get_entry(toml, "plain_keys");
        self.set_sequences(&SeqType::Plain, BTreeMap::from_toml(&table));
    }

    fn load_plain_mods(&mut self, toml: &Value) {
        let table = get_entry(toml, "plain_modifiers");
        for (name, seq) in BTreeMap::from_toml(&table).iter() {
            self.add_modifierkey(name.to_owned(), seq);
        }
    }

    fn load_word_mods(&mut self, other: &Value) {
        self.wordmods = Vec::from_toml(&get_entry(other, "word_modifiers"));
    }

    fn load_anagram_mods(&mut self, other: &Value) {
        let array = other.get("anagram_modifiers").expect("Missing array: anagram_modifiers");
        self.anagrams = Vec::from_toml(&array);
    }

    fn load_commands(&mut self, other: &Value) {
        // TODO use set sequences, and then process after?
        let array = get_entry(other, "commands");
        let command_list = Vec::from_toml(&array);
        self.set_sequences(&SeqType::Command, BTreeMap::new());
        for name in command_list.iter() {
            self.add_command(name)
        }
    }

    fn load_word_list(&mut self, other: &Value) {
        let array = get_entry(other, "dictionary");
        let word_list = toml_to_vec(&array, WordInfo::from_toml);
        self.set_sequences(&SeqType::Word, BTreeMap::new());
        for kmap in &self.get_kmaps_with_words(){
            for info in word_list.iter() {
                self.add_word(info.to_owned(), kmap)
            }
        }
    }
}

fn parse_toml(toml_path: &str) -> Value {
    let mut f: File = File::open(toml_path)
        .expect("failed to open settings file!");
    let mut buffer = String::new();
    f.read_to_string(&mut buffer).expect("failed to read settings file!");
    let toml = buffer.parse::<Value>().expect("failed to parse settings file!");
    toml
}

fn get_entry<'a>(toml: &'a Value, table_name: &str) -> &'a Value {
    // TODO include name in error
    match toml.get(table_name){
        Some(t) => t,
        None => panic!("Missing entry in settings"),
    }
}
