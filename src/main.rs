extern crate failure;
extern crate pipit_config;

use pipit_config::AllData;
use pipit_config::errors::*;

use pipit_config::tutor::TutorData;
// use pipit_config::tutor::TutorApp;
use pipit_config::cheatsheet::CheatSheet;

use failure::{Error, ResultExt};

use std::env::args;

const DEFAULT_SETTINGS_FILE: &str = "settings/settings.toml";

fn get_settings_path() -> Result<String, Error> {
    // check command line arguments
    // TODO use docopt or something
    match args().len() {
        1 => Ok(DEFAULT_SETTINGS_FILE.to_string()),
        2 => Ok(args().nth(1).unwrap()),
        x => Err(NumArgsErr(x).into()),
    }
}

fn run() -> Result<(), Error> {
    let settings_path = get_settings_path()?;
    let all_data = AllData::load(&settings_path)?;
    all_data.check();
    // TODO automatically extract path parts
    all_data
        .save_as("auto_config")
        .context("Failed to save configuration")?;
    let tutor_data = TutorData::new(all_data.get_tutor_data()?);
    CheatSheet::from_toml("settings/cheatsheet.toml", &tutor_data)
        .save("out.svg");
    // TutorApp::run(tutor_data);
    Ok(())
}

fn main() {
    if let Err(error) = run() {
        print_error(error);
        ::std::process::exit(1);
    } else {
        println!("Done.");
    }
}
