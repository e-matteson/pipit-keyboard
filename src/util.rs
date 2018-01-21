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
