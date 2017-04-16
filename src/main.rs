
extern crate rusty_pipit;

use rusty_pipit::Maps;


fn main() {

    let maps = Maps::load("settings.toml");

    // TODO automatically extract path parts
    let f = maps.format("auto_config");
    f.save("rusty-firmware/auto_config");
}
