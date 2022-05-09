use std::fs::File;
use std::io::{BufReader, Read};
use std::path::PathBuf;

use error::{Error, ResultExt};

use input::load_all_data;

fn expected_dir() -> PathBuf {
    PathBuf::from("src/tests/expected-outputs/")
}

fn actual_dir() -> PathBuf {
    PathBuf::from("src/tests/actual-outputs/")
}

// TODO delete old files in actual_dir before running the tests. Otherwise they
// can pass using old copies if the current code writes nothing.

#[test]
fn big_settings_output() {
    let all_data =
        load_all_data(&PathBuf::from("src/tests/settings/big-test.yaml"))
            .unwrap();

    let name_base = "auto_config-big_test";
    all_data
        .save_without_message_as(&name_base)
        .expect("Failed to save configuration");

    assert_firmware_config_eq(name_base);
}

#[test]
fn chord22_output() {
    let all_data =
        load_all_data(&PathBuf::from("src/tests/settings/test22.yaml"))
            .unwrap();

    let name_base = "auto_config-22";
    // let name_base = "auto_config";
    all_data
        .save_without_message_as(&name_base)
        .expect("Failed to save configuration");

    assert_firmware_config_eq(name_base);
}

fn assert_firmware_config_eq(name_base: &str) {
    let expected_dir = expected_dir();
    let actual_dir = actual_dir();

    assert_files_eq(
        &expected_dir.join(name_base).with_extension("h"),
        &actual_dir.join(name_base).with_extension("h"),
    );
    let early_base = format!("{}_early", name_base);
    assert_files_eq(
        &expected_dir.join(&early_base).with_extension("h"),
        &actual_dir.join(&early_base).with_extension("h"),
    );
}

fn assert_files_eq(left_file: &PathBuf, right_file: &PathBuf) {
    // let left_str = read(left_file).unwrap_or_else(|e| print_and_panic(e));
    // if pretty_unwrap(read(left_file)) != pretty_unwrap(read(right_file)) {
    if read(left_file).unwrap() != read(right_file).unwrap() {
        panic!(
            "File contents don't match: {:?}, {:?}",
            left_file, right_file
        )
    }
}

fn read(path: &PathBuf) -> Result<String, Error> {
    let mut reader = BufReader::new(
        File::open(path)
            .with_context(|| format!("failed to open: {:?}", path))?,
    );
    let mut string = String::new();
    reader.read_to_string(&mut string)?;
    Ok(string)
}
