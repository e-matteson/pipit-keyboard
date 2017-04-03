// use std::collections::HashMap;
#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

extern crate rusty_pipit;

// use rusty_pipit::options::*;
use rusty_pipit::maps::*;
// use rusty_pipit::key_types::*;
// use rusty_pipit::toml_convertor::*;
use rusty_pipit::options::load::Loader;
use rusty_pipit::options::format::*;
use rusty_pipit::parser::*;
// use rusty_pipit::settings::SETTINGS;

fn main() {


    let loader = Loader::load("settings.toml");
    let mut options = loader.options;

    let mut parser = Parser::new(&options);
    let mut maps = Maps::new(options.get_val("num_bytes_in_chord")
                         .unwrap_int() as usize);

    parser.parse("keymaps/dvorak24.kmap", &mut maps.chords);
    options.set_auto(&maps);

    maps.plains = loader.plain_keys;
    maps.macros = loader.macros;
    for entry in loader.special_list.iter(){
        maps.add_special(entry)
    }
    for entry in loader.word_list.iter(){
        maps.add_word(entry)
    }

    maps.check_for_missing_seqs();
    maps.check_for_duplicate_chords();
    // println!("{:?}", options.get("debug_messages").format("debug_messages"));
    // println!("{:?}", options.get("stickymod_key").format("stickymod_key"));
    // println!("{:?}", options.get("board_name").format("board_name"));
    // println!("{:?}", options.get("has_battery").format("has_battery"));
    // println!("{:?}", options.get("battery_level_pin").format("battery_level_pin"));
    // println!("{:?}", options.get("row_pins").format("row_pins"));
    // println!("{:?}", make_c_array2());
    // println!("{:?}", make_c_array(vec![0,1,2,3,4,5,6,7,8,9,10,11,12,13]));

    // println!("{}", make_c_array2(&vec![vec![0,1,2,3,4,5], vec![6,7,8,9,10,11]]));
    // println!("{}\n\n***\n", make_c_array(vec![0,1,2,3,4,5]));
    // println!("{}", make_c_array2(vec![vec![0,1,2,3,4,5], vec![6,7,8,9,10,11]]));
    // make_c_array(vec![0,1,2]);

}
