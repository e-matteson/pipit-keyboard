#![allow(unused_variables)]
#![allow(unused_imports)]
#![allow(dead_code)]

extern crate rusty_pipit;

// use rusty_pipit::options::*;
use rusty_pipit::maps::Maps;
use rusty_pipit::options::load::Loader;
use rusty_pipit::options::format::*;
use rusty_pipit::parser::Parser;
use rusty_pipit::write::*;

// use rusty_pipit::settings::SETTINGS;

fn main() {

    let loader = Loader::load("settings.toml");
    let mut options = loader.options;

    let mut parser = Parser::new(&options);
    let mut maps = Maps::new();

    parser.parse("keymaps/dvorak24.kmap", &mut maps.chords);
    options.set_auto(&maps);

    maps.plains = loader.plain_keys;
    maps.macros = loader.macros;
    maps.wordmods = loader.wordmod_list;
    maps.wordmods.sort();

    for entry in loader.special_list.iter() {
        maps.add_special(entry)
    }

    for entry in loader.word_list.iter() {
        maps.add_word(entry)
    }

    // let f = format_plains(&maps.plains, &maps.chords);
    // let f = format_words(&maps.words, &maps.chords);
    // let f = maps.format_specials();
    let output_name_base = "auto_config";
    let f = format_autoconfig(&maps, &options, output_name_base);

    f.save(output_name_base);

    let f = options.format();
    println!("{}", f.h);
    println!("{}", f.c);
    // let f = format_lookups(&maps.words, &maps.chords, "word", false, false);
    // println!("{:?}", chord_to_ints(&maps.chords["key_0"]));

    // println!("{:?}", chord_to_ints(&maps.chords["key_0"]));
    // println!("{:?}", format_wordmod("wordmod_anagram1", &maps));

    // println!("{}", format_intro("foo.h").h);
    // println!("{}", format_intro("foo.h").c);

    // maps.check_for_missing_seqs();
    // maps.check_for_duplicate_chords();
    // println!("{:?}", options.get("debug_messages").format("debug_messages"));
    // println!("{:?}", options.get("stickymod_key").format("stickymod_key"));
    // println!("{:?}", options.get("board_name").format("board_name"));
    // println!("{:?}", options.get("has_battery").format("has_battery"));
    // println!("{:?}", options.get("battery_level_pin").format("battery_level_pin"));
    // println!("{:?}", options.get("row_pins").format("row_pins"));
    // println!("{:?}", maps.get_modifier_position("modifierkey_shift"));
    // println!("{:?}", maps.get_modifier_position("blank_mapping"));
    // println!("{:?}", make_c_array2());
    // println!("{:?}", make_c_array(vec![0,1,2,3,4,5,6,7,8,9,10,11,12,13]));
    // println!("{}", make_c_array2(&vec![vec![0,1,2,3,4,5], vec![6,7,8,9,10,11]]));
    // println!("{}\n\n***\n", make_c_array(vec![0,1,2,3,4,5]));
    // println!("{}", make_c_array2(vec![vec![0,1,2,3,4,5], vec![6,7,8,9,10,11]]));
    // make_c_array(vec![0,1,2]);

}
