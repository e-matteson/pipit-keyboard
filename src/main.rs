extern crate rusty_pipit;
use rusty_pipit::options::*;


fn main() {
    let mut op_def_map = define_options();
    let parsed = get_parsed_settings();
    // println!("{:#?}", parsed);
    set_options(&mut op_def_map, &parsed["options"]);
}
