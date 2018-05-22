use std::io::prelude::*;
use std::fs::File;
use std::path::PathBuf;

use types::errors::OutOfRangeErr;
use failure::Error;

pub fn bools_to_bytes(v: &[bool]) -> Vec<u8> {
    let mut bytes = Vec::new();
    for chunk in v.chunks(8) {
        bytes.push(bools_to_u8(chunk).unwrap());
    }
    bytes
}

pub fn bools_to_u32(v: &[bool]) -> Result<u32, Error> {
    // If v is shorter than 32, the missing most-significant digits will be zero
    let max = 32;
    if v.len() > max {
        Err(OutOfRangeErr {
            name: "number of bits to convert to a u32".into(),
            value: v.len(),
            min: 0,
            max: max,
        })?;
    }

    let mut num: u32 = 0;
    let base: u32 = 2;
    for b in 0..32 {
        let bit = if *v.get(b).unwrap_or(&false) { 1 } else { 0 };
        num += base.pow(b as u32) * bit
    }
    Ok(num)
}

fn bools_to_u8(v: &[bool]) -> Result<u8, Error> {
    // If v is shorter than 8, the missing most-significant digits will be zero
    let max = 8;
    if v.len() > max {
        Err(OutOfRangeErr {
            name: "number of bits to convert to a u8".into(),
            value: v.len(),
            min: 0,
            max: max,
        })?;
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
        Err(OutOfRangeErr {
            name: "unsigned 8 bit int value".into(),
            value: input,
            min: u8::min_value() as usize,
            max: u8::max_value() as usize,
        })?;
    }
    Ok(())
}

pub fn usize_to_u16(input: usize) -> Result<u16, Error> {
    ensure_u16(input)?;
    Ok(input as u16)
}

pub fn ensure_u16(input: usize) -> Result<(), Error> {
    let truncated = input as u16;
    if input != (truncated as usize) {
        Err(OutOfRangeErr {
            name: "unsigned 16 bit int value".into(),
            value: input,
            min: u16::min_value() as usize,
            max: u16::max_value() as usize,
        })?;
    }
    Ok(())
}

pub fn read_file(path: &PathBuf) -> Result<String, Error> {
    let mut f: File = File::open(path)?;
    let mut buffer = String::new();
    f.read_to_string(&mut buffer)?;
    Ok(buffer)
}
