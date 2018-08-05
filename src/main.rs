extern crate cursive;
extern crate itertools;
extern crate natord;
extern crate serde;
extern crate serde_yaml;
extern crate svg;
extern crate time;
extern crate unicode_segmentation;
#[macro_use]
extern crate failure;
#[macro_use]
extern crate lazy_static;
#[macro_use]
extern crate serde_derive;
#[macro_use]
extern crate structopt;

#[macro_use]
mod types;
#[macro_use]
mod input;
mod cheatsheet;
mod output;
#[cfg(test)]
mod tests;
mod tutor;
mod util;

use std::path::PathBuf;
use structopt::StructOpt;

use cheatsheet::CheatSheet;
use input::AllDataBuilder;
use tutor::TutorApp;
use types::errors::print_error;

use failure::{Error, ResultExt};

/// Pipit keyboard configuration tool, typing tutor, and cheatsheet generator
#[derive(StructOpt, Debug)]
#[structopt(name = "pipit-keyboard")]
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
    /// Settings file that specifies the keymaps, dictionary, etc
    #[structopt(parse(from_os_str))]
    settings: Option<PathBuf>,
}

fn run() -> Result<(), Error> {
    println!();
    let opt = Opt::from_args();

    let settings_path = opt
        .settings
        .unwrap_or_else(|| PathBuf::from("settings/settings.yaml"));

    let all_data = AllDataBuilder::load(&settings_path)?.finalize()?;
    all_data.check();

    let tutor_data = all_data.get_tutor_data()?;

    if let Some(ref config) = opt.cheatsheet {
        CheatSheet::from_yaml(config, &tutor_data)
            .context("Failed to make cheatsheet")?
            .save(None)?;
    } else if opt.tutor {
        drop(all_data);
        TutorApp::run(tutor_data);
    } else {
        all_data
            .save_as("auto_config")
            .context("Failed to save configuration")?;
    }

    Ok(())
}

fn main() {
    if let Err(error) = run() {
        print_error(&error);
        ::std::process::exit(1);
    } else {
        println!("Done.");
    }
}
