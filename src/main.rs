extern crate bit_vec;
extern crate cursive;
extern crate itertools;
extern crate natord;
extern crate serde;
extern crate serde_yaml;
extern crate svg;
extern crate time;
extern crate unicode_segmentation;
#[macro_use]
extern crate lazy_static;
#[macro_use]
extern crate serde_derive;
#[macro_use]
extern crate clap;

#[macro_use]
mod types;
mod error;
#[macro_use]
mod input;
mod arduino;
mod cheatsheet;
mod output;
#[cfg(test)]
mod tests;
mod tutor;
mod util;

use std::path::PathBuf;

use arduino::ArduinoIDE;
use cheatsheet::CheatSheet;
use error::{Error, ResultExt};
use input::AllDataBuilder;
use tutor::TutorApp;

use clap::{Arg, ArgGroup};

fn run() -> Result<(), Error> {
    // Parse command-line arguments
    let args = app_from_crate!()
        .arg(
            Arg::with_name("cheatsheet")
                .short("c")
                .long("cheatsheet")
                .takes_value(true)
                .value_name("cheatsheet_config_file")
                .help("Generate a cheatsheet, according to given cheatsheet config file"),
        ).arg(
            Arg::with_name("nosave")
                .short("n")
                .long("nosave")
                .help("Don't save an updated firmware configuration, only perform the other specified action(s)"),
        ).arg(
            Arg::with_name("tutor")
                .short("t")
                .long("tutor")
                .help("Run the typing tutor"),
        ).arg(
            Arg::with_name("verify")
                .short("v")
                .long("verify")
                .help("Verify the updated firmware, using the Arduino IDE"),
        ).arg(
            Arg::with_name("upload")
                .short("u")
                .long("upload")
                // .requires("port")
                .help("Upload the updated firmware to the keyboard, using the Arduino IDE"),
        ).arg(
            Arg::with_name("port")
                .short("p")
                .long("port")
                .takes_value(true)
                .value_name("port_name")
                .help("Select the serial port over which to upload the updated firmware"),
        ).group(
            ArgGroup::with_name("commands").args(&["cheatsheet", "tutor", "verify","upload"]).multiple(false)
        ).arg(
            Arg::with_name("settings")
                .takes_value(true)
                .value_name("settings_file")
                .default_value("settings/settings.yaml")
                .help("Settings file that specifies the keymaps, dictionary, etc"),
        ).get_matches();

    println!();

    let settings_path = PathBuf::from(
        args.value_of("settings")
            .expect("settings file not specified"),
    );

    let all_data = AllDataBuilder::load(&settings_path)?.finalize()?;
    all_data.check();

    if args.is_present("nosave") {
        println!("Not configuring the firmware (because --nosave was passed)");
    } else {
        all_data
            .save_as("auto_config")
            .context("Failed to save updated firmware")?;
    }

    if let Some(config_path) = args.value_of_os("cheatsheet") {
        let tutor_data = all_data.get_tutor_data()?;
        let path = PathBuf::from(config_path);
        CheatSheet::from_yaml(&path, &tutor_data)
            .context("Failed to make cheatsheet")?
            .save(None)?;
        return Ok(());
    }

    if args.is_present("tutor") {
        let tutor_data = all_data.get_tutor_data()?;
        drop(all_data);
        TutorApp::run(tutor_data);
        return Ok(());
    }

    if args.is_present("verify") {
        let ide = ArduinoIDE::new(all_data.board());
        drop(all_data);
        ide.verify()?;
        return Ok(());
    }

    if args.is_present("upload") {
        let ide = ArduinoIDE::new(all_data.board());
        drop(all_data);
        ide.upload(args.value_of("port"))?;
        return Ok(());
    }
    Ok(())
}

fn main() {
    if let Err(error) = run() {
        println!("{}", error);
        // TODO impl exit code on error?
        ::std::process::exit(1);
    } else {
        println!("Done.");
    }
}
