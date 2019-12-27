use std::borrow::Cow;
use std::fs::File;
use std::io::prelude::*;
use std::io::{stdin, stdout};
use std::path::PathBuf;

use error::{Error, ResultExt};

#[allow(dead_code)]
#[derive(Clone, Copy)]
pub enum ConfirmDefault {
    Yes,
    No,
    None,
}

pub fn usize_to_u8(input: usize) -> Result<u8, Error> {
    ensure_u8(input)?;
    Ok(input as u8)
}

pub fn ensure_u8(input: usize) -> Result<(), Error> {
    let truncated = input as u8;
    if input != (truncated as usize) {
        Err(Error::OutOfRangeErr {
            name: "unsigned 8 bit int value".to_owned(),
            value: input,
            min: u8::min_value() as usize,
            max: u8::max_value() as usize,
        })
    } else {
        Ok(())
    }
}

pub fn usize_to_u16(input: usize) -> Result<u16, Error> {
    ensure_u16(input)?;
    Ok(input as u16)
}

pub fn ensure_u16(input: usize) -> Result<(), Error> {
    let truncated = input as u16;
    if input == (truncated as usize) {
        Ok(())
    } else {
        Err(Error::OutOfRangeErr {
            name: "unsigned 16 bit int value".into(),
            value: input,
            min: u16::min_value() as usize,
            max: u16::max_value() as usize,
        })
    }
}

pub fn read_file(path: &PathBuf) -> Result<String, Error> {
    let mut f: File = File::open(path)?;
    let mut buffer = String::new();
    f.read_to_string(&mut buffer)?;
    Ok(buffer)
}

fn get_input() -> Result<String, Error> {
    stdout().flush()?;
    let mut buffer = String::new();
    stdin().read_line(&mut buffer)?;
    Ok(buffer)
}

pub fn user_confirm<'a, T>(
    message: T,
    default: ConfirmDefault,
) -> Result<bool, Error>
where
    T: Into<Cow<'a, str>>,
{
    let suggestion = match default {
        ConfirmDefault::Yes => "(Y/n)",
        ConfirmDefault::No => "(y/N)",
        ConfirmDefault::None => "(y/n)",
    };

    print!("{} {}: ", message.into(), suggestion);

    loop {
        let input = get_input().context("Failed to get user input")?;
        let output = match input.trim() {
            "y" | "Y" | "yes" => true,
            "n" | "N" | "no" => false,
            _ => match default {
                ConfirmDefault::Yes => true,
                ConfirmDefault::No => false,
                ConfirmDefault::None => {
                    print!("Please respond with yes or no: ");
                    continue;
                }
            },
        };
        return Ok(output);
    }
}
