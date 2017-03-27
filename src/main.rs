// use std::collections::HashMap;

extern crate rusty_pipit;

// use rusty_pipit::options::*;
use rusty_pipit::maps::*;
// use rusty_pipit::key_types::*;
// use rusty_pipit::toml_convertor::*;
use rusty_pipit::toml_loader::*;

fn main() {
    let loader = TomlLoader::load("settings.toml");
    // let options = loader.options;
    // let macros = loader.macros;
    // make_words(&config.words, &config.options, &mut seq_map, &mut chord_map);
    // println!("{:#?}", config.options["kmap_format"]);
    // let maps = Maps::new(loader.options["num_bytes_in_chord"]);
    let mut maps = Maps::new(3);
    for entry in loader.word_list.iter(){
        maps.add_word(entry)
    }
    println!("{:?}", maps);
}
