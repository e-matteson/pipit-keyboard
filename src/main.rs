// extern crate cpuprofiler;
extern crate failure;
extern crate pipit_config;

use pipit_config::AllData;
use pipit_config::errors::*;

// use pipit_config::tutor::TutorApp;
// use pipit_config::cheatsheet::CheatSheet;

use failure::{Error, ResultExt};

// use cpuprofiler::PROFILER;

use std::env::args;

const DEFAULT_SETTINGS_FILE: &str = "settings/settings.yaml";

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
    println!("");
    let settings_path = get_settings_path()?;
    let all_data = AllData::load(&settings_path)?;
    all_data.check();
    // TODO automatically extract path parts
    all_data
        .save_as("auto_config")
        .context("Failed to save configuration")?;

    // let tutor_data = all_data.get_tutor_data()?;
    // CheatSheet::from_yaml("settings/cheatsheet_full.yaml", &tutor_data)
    //     .context("Failed to make cheatsheet")?
    //     .save("out.svg");
    // TutorApp::run(tutor_data);
    Ok(())
}

fn main() {
    // PROFILER.lock().unwrap().start("./my-prof.profile").unwrap();
    if let Err(error) = run() {
        print_error(error);
        ::std::process::exit(1);
    } else {
        println!("Done.");
    }
    // PROFILER.lock().unwrap().stop().unwrap();
}
