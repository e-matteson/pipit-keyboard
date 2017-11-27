extern crate pipit_config;

use pipit_config::AllData;
use pipit_config::errors::*;

use pipit_config::tutor::{TutorApp, TutorData};

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

fn run() -> Result<()> {
    let settings_path = get_settings_path()?;
    let all_data = AllData::load(&settings_path)?;
    all_data.check();
    // TODO automatically extract path parts
    all_data.save_as("auto_config")?;
    // TutorApp::run(TutorData::new(all_data.get_tutor_data()?));
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
