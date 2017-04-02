// use std::collections::HashMap;
#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

extern crate rusty_pipit;

// use rusty_pipit::options::*;
use rusty_pipit::maps::*;
// use rusty_pipit::key_types::*;
// use rusty_pipit::toml_convertor::*;
use rusty_pipit::options::toml_loader::*;
use rusty_pipit::options::loader::*;
use rusty_pipit::parser::*;
// use rusty_pipit::settings::SETTINGS;

fn main() {
    let loader = Loader::load();


    // let loader = TomlLoader::load("settings.toml");
    // let mut options = loader.options;

    // let mut parser = Parser::new(&options);
    // let mut maps = Maps::new(options.get_val("num_bytes_in_chord")
    //                      .unwrap_int() as usize);

    // parser.parse("keymaps/dvorak24.kmap", &mut maps.chords);
    // options.set_auto(&maps);

    // maps.plains = loader.plain_keys;
    // maps.macros = loader.macros;
    // for entry in loader.special_list.iter(){
    //     maps.add_special(entry)
    // }
    // for entry in loader.word_list.iter(){
    //     maps.add_word(entry)
    // }

    // options.get("debug_messages").format();
}
