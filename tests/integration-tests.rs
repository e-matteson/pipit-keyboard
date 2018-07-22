extern crate failure;
extern crate pipit_keyboard;

use std::fs::File;
use std::io::{BufReader, Read};
use std::path::PathBuf;

use failure::{Error, ResultExt};

use pipit_keyboard::errors::pretty_unwrap;
use pipit_keyboard::AllData;

#[test]
fn big_settings_output() {
    let settings_path = PathBuf::from("tests/settings/big-test.yaml");

    let all_data = AllData::load(&settings_path).expect("failed to load");
    all_data.check();

    let name_base = "auto_config-big_test";

    all_data
        // .save_as(&name_base)
        .save_without_message_as(&name_base)
        .expect("Failed to save configuration");

    let expected_dir = PathBuf::from("tests/expected-outputs/");
    let actual_dir = PathBuf::from("tests/actual-outputs/");
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
        File::open(path).context(format!("failed to open: {:?}", path))?
    );
    let mut string = String::new();
    reader.read_to_string(&mut string)?;
    Ok(string)
}
