
extern crate pipit_config;

use pipit_config::{Maps};
use pipit_config::errors::*;

use std::env::args;

const DEFAULT_SETTINGS_FILE: &str = "settings/settings.toml";

fn get_settings_path() -> Result<String> {
    // check command line arguments
    // TODO use docopt or something
    match args().len() {
        1 => Ok(DEFAULT_SETTINGS_FILE.to_string()),
        2 => Ok(args().nth(1).unwrap()),
        x => Err(ErrorKind::NumArgs(x).into()),
    }
}

fn run() -> Result<()>{
    let settings_path = get_settings_path()?;
    let maps = Maps::load(&settings_path)?;
    maps.check();
    // TODO automatically extract path parts
    let f = maps.format("auto_config");
    // println!("DRY RUN, NOT SAVING");
    f.save("pipit-firmware/auto_config");
    Ok(())
}

fn main() {
  if let Err(ref e) = run() {
        use std::io::Write;
        let stderr = &mut ::std::io::stderr();
        let errmsg = "Error writing to stderr";

        writeln!(stderr, "\nerror: {}", e).expect(errmsg);

        for e in e.iter().skip(1) {
            writeln!(stderr, "caused by: {}", e).expect(errmsg);
        }

        // The backtrace is not always generated. Try to run this example
        // with `RUST_BACKTRACE=1`.
        // if let Some(backtrace) = e.backtrace() {
        //     writeln!(stderr, "backtrace: {:?}", backtrace).expect(errmsg);
        // }

        ::std::process::exit(1);
    }
}

