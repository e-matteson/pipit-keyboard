extern crate failure;
extern crate pipit_keyboard;

use std::fs::File;
use std::io::{BufReader, Read};
use std::path::PathBuf;

use failure::{Error, ResultExt};

use pipit_keyboard::errors::pretty_unwrap;
use pipit_keyboard::AllData;

fn expected_dir() -> PathBuf {
    PathBuf::from("tests/expected-outputs/")
}

fn actual_dir() -> PathBuf {
    PathBuf::from("tests/actual-outputs/")
}

#[test]
fn big_settings_output() {
    let all_data =
        AllData::load(&PathBuf::from("tests/settings/big-test.yaml"))
            .expect("failed to load");

    let name_base = "auto_config-big_test";
    all_data
        .save_without_message_as(&name_base)
        .expect("Failed to save configuration");

    assert_firmware_config_eq(name_base);
}

#[test]
fn chord22_output() {
    let all_data = AllData::load(&PathBuf::from("tests/settings/test22.yaml"))
        .expect("failed to load");

    let name_base = "auto_config-22";
    all_data
        .save_without_message_as(&name_base)
        .expect("Failed to save configuration");

    assert_firmware_config_eq(name_base);
}

fn assert_firmware_config_eq(name_base: &str) {
    let expected_dir = expected_dir();
    let actual_dir = actual_dir();

    assert_files_eq(
        &expected_dir.join(name_base).with_extension("cpp"),
        &actual_dir.join(name_base).with_extension("cpp"),
    );
    assert_files_eq(
        &expected_dir.join(name_base).with_extension("h"),
        &actual_dir.join(name_base).with_extension("h"),
    );
}

fn assert_files_eq(left_file: &PathBuf, right_file: &PathBuf) {
    // let left_str = read(left_file).unwrap_or_else(|e| print_and_panic(e));
    if pretty_unwrap(read(left_file)) != pretty_unwrap(read(right_file)) {
        panic!(
            "File contents don't match: {:?}, {:?}",
            left_file, right_file
        )
    }
}

fn read(path: &PathBuf) -> Result<String, Error> {
    let mut reader = BufReader::new(
        File::open(path).context(format!("failed to open: {:?}", path))?,
    );
    let mut string = String::new();
    reader.read_to_string(&mut string)?;
    Ok(string)
}
