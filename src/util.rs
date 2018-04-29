use types::errors::OutOfRangeErr;
use failure::Error;

pub fn bools_to_bytes(v: &[bool]) -> Vec<u8> {
    let mut bytes = Vec::new();
    for chunk in v.chunks(8) {
        bytes.push(bools_to_u8(chunk));
    }
    bytes
}

fn bools_to_u8(v: &[bool]) -> u8 {
    // If v is shorter than 8, the missing most-significant digits will be zero
    assert!(v.len() <= 8);
    let mut num: u8 = 0;
    let base: u8 = 2;
    for b in 0..8 {
        let bit = if *v.get(b).unwrap_or(&false) { 1 } else { 0 };
        num += base.pow(b as u32) * bit
    }
    num
}

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
