use itertools::Itertools;

use types::{CCode, KeyPress, Sequence};

// Constants used for compression
const NUM_BYTES: usize = 3;
const NUM_KEYS: usize = 4;


pub fn make_compression_macros() -> CCode {
    let mut s = String::new();
    s += "#define BY0(X,Y) (( X &0x3F)<<2) | (( Y &0x30)>>4)\n";
    s += "#define BY1(X,Y) (( X &0x0F)<<4) | (( Y &0x3C)>>2)\n";
    s += "#define BY2(X,Y) (( X &0x03)<<6) | ( Y &0x3F)\n\n";
    CCode(s)
}


pub fn compress(seq: &Sequence, use_mods: bool) -> Vec<CCode> {
    if use_mods {
        panic!("Not implemented: compression with stored modifiers")
    }
    let mut compressed: Vec<CCode> = Vec::new();
    let chunks = &seq.0.iter().cloned().chunks(NUM_KEYS);
    for chunk in chunks {
        let vals: Vec<_> = chunk.collect();
        compressed.extend(compress_chunk(vals));
    }
    compressed
}


fn compress_chunk(mut data: Vec<KeyPress>) -> Vec<CCode> {
    // byte0            byte1            byte2
    // 0x3F             0x0F             0x03
    // --aaaaaa         ----bbbb         ------cc
    // 0x30                              0x3F
    // --bb----         --cccc--         --dddddd
    // aaaaaabb         bbbbcccc         ccdddddd

    pad_to_length(&mut data, NUM_KEYS);

    let mut bytes: Vec<CCode> = Vec::new();
    for i in 0..NUM_BYTES {
        let s1 = &data[i].format_key();
        let s2 = &data[i + 1].format_key();
        let m = format_mask(i, s1, s2);
        // we don't use the modifiers, just the keys
        bytes.push(m);
    }
    bytes
}

fn format_mask(i: usize, s1: &CCode, s2: &CCode) -> CCode {
    let macro_name = match i {
        0 => "BY0",
        1 => "BY1",
        2 => "BY2",
        _ => panic!("format_mask: bad index"),
    };
    CCode(format!("{}({},{})", macro_name, s1, s2))
}

fn pad_to_length<T>(v: &mut Vec<T>, length: usize)
where
    T: Default,
{
    assert!(v.len() <= length);
    let pad_width = length.saturating_sub(v.len());
    for _ in 0..pad_width {
        v.push(T::default());
    }
}
