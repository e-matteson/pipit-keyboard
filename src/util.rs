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

pub fn bools_to_bytes(v: &[bool]) -> Vec<u8> {
    let mut bytes = Vec::new();
    for chunk in v.chunks(8) {
        bytes.push(bools_to_u8(chunk).unwrap());
    }
    bytes
}

pub fn bools_to_u32(v: &[bool]) -> Result<u32, Error> {
    // If v is shorter than 32, the missing most-significant digits will be zero
    // TODO static? const?
    let max = 32;
    if v.len() > max {
        return Err(Error::OutOfRangeErr {
            name: "number of bits to convert to a u32".into(),
            value: v.len(),
            min: 0,
            max,
        });
    }

    let mut num: u32 = 0;
    let base: u32 = 2;
    for b in 0..32 {
        let bit = if *v.get(b).unwrap_or(&false) { 1 } else { 0 };
        num += base.pow(b as u32) * bit
    }
    Ok(num)
}

/// If v is shorter than 8, the missing most-significant digits will be zero
fn bools_to_u8(v: &[bool]) -> Result<u8, Error> {
    let max = 8;
    if v.len() > max {
        return Err(Error::OutOfRangeErr {
            name: "number of bits to convert to a u8".into(),
            value: v.len(),
            min: 0,
            max,
        });
    }
    let mut num: u8 = 0;
    let base: u8 = 2;
    for b in 0..8 {
        let bit = if *v.get(b).unwrap_or(&false) { 1 } else { 0 };
        num += base.pow(b as u32) * bit
    }
    Ok(num)
}

#[allow(dead_code)]
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

pub fn user_confirm(
    message: &str,
    default: ConfirmDefault,
) -> Result<bool, Error> {
    let suggestion = match default {
        ConfirmDefault::Yes => "(Y/n)",
        ConfirmDefault::No => "(y/N)",
        ConfirmDefault::None => "(y/n)",
    };

    print!("{} {}: ", message, suggestion);

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
