// use std::collections::HashMap;
#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

extern crate rusty_pipit;

// use rusty_pipit::options::*;
use rusty_pipit::maps::*;
// use rusty_pipit::key_types::*;
// use rusty_pipit::toml_convertor::*;
use rusty_pipit::toml_loader::*;
use rusty_pipit::parser::*;

fn main() {
    let loader = TomlLoader::load("settings.toml");
    let options = loader.options;

    let mut parser = Parser::new(&options);
    let mut maps = Maps::new(3);
    parser.parse("keymaps/dvorak24.kmap", &mut maps.chords);


    // let macros = loader.macros;
    // println!("{:#?}", loader.options.get("kmap_format"));

    // // let maps = Maps::new(loader.options["num_bytes_in_chord"]);
    // for entry in loader.word_list.iter(){
    //     maps.add_word(entry)
    // }
    // for entry in loader.special_list.iter(){
    //     maps.add_special(entry)
    // }
    // maps.plains = loader.plain_keys;
    // maps.macros = loader.macros;

    // println!("{:?}", maps);
}
