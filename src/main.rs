
extern crate pipit_config;

use pipit_config::Maps;
use std::env::args;

const DEFAULT_SETTINGS_FILE: &str = "settings/settings.toml";

fn get_settings_path() -> String {
    // check command line arguments
    match args().len() {
        0 => panic!("Zero arguments!?"),
        1 => DEFAULT_SETTINGS_FILE.to_string(),
        2 => args().nth(1).unwrap(),
        _ => panic!("Too many arguments"), // TODO print usage
    }
}


fn main() {
    let settings_path = get_settings_path();
    let maps = Maps::load(&settings_path);

    // TODO automatically extract path parts
    let f = maps.format("auto_config");
    println!("DRY RUN, NOT SAVING");
    // f.save("pipit-firmware/auto_config");
}
