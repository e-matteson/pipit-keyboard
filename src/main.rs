// extern crate cpuprofiler;
extern crate failure;
extern crate pipit_config;
#[macro_use]
extern crate structopt;

use std::path::PathBuf;
use structopt::StructOpt;

use pipit_config::AllData;
use pipit_config::errors::*;

use pipit_config::tutor::TutorApp;
use pipit_config::cheatsheet::CheatSheet;

use failure::{Error, ResultExt};

// use cpuprofiler::PROFILER;

/// Pipit keyboard configuration tool, typing tutor, and cheatsheet generator
#[derive(StructOpt, Debug)]
#[structopt(name = "pipit-config")]
struct Opt {
    /// Runs the typing tutor
    #[structopt(short = "t", long = "tutor")]
    tutor: bool,

    /// Generates a cheatsheet, according to the given config file
    #[structopt(short = "c", long = "cheatsheet", parse(from_os_str))]
    cheatsheet: Option<PathBuf>,

    // #[structopt(short = "o", long = "output", parse(from_os_str))]
    // output: Option<PathBuf>
    //
    /// Settings file that includes the keymaps, dictionary, etc
    #[structopt(parse(from_os_str))]
    settings: Option<PathBuf>,
}

fn run() -> Result<(), Error> {
    println!("");
    let opt = Opt::from_args();

    let settings_path = opt.settings
        .unwrap_or_else(|| PathBuf::from("settings/settings.yaml"));

    let all_data = AllData::load(&settings_path)?;
    all_data.check();

    let tutor_data = all_data.get_tutor_data()?;

    if let Some(ref config) = opt.cheatsheet {
        CheatSheet::from_yaml(config, &tutor_data)
            .context("Failed to make cheatsheet")?
            .save("cheatsheet.svg")?;
    } else if opt.tutor {
        TutorApp::run(tutor_data);
    } else {
        all_data
            .save_as("auto_config")
            .context("Failed to save configuration")?;
    }

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
