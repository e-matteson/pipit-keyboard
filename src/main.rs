
extern crate pipit_config;

use pipit_config::Maps;


fn main() {

    let maps = Maps::load("settings/settings.toml");

    // TODO automatically extract path parts
    let f = maps.format("auto_config");
    f.save("pipit-firmware/auto_config");
}
