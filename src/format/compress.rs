use itertools::Itertools;

use types::{Sequence, KeyPress};

// Constants used for compression
const NUM_BYTES: usize =  3;
const NUM_KEYS: usize = 4;



pub fn compress(seq: &Sequence, use_mods: bool) -> Vec<String> {
    let mut compressed: Vec<String> = Vec::new();
    let chunks = &seq.0.iter().cloned().chunks(NUM_KEYS);
    for chunk in chunks {
        let vals: Vec<_> = chunk.collect();
        compressed.extend(compress_chunk(vals));
    }
    compressed
}


fn compress_chunk(mut data: Vec<KeyPress>) -> Vec<String> {
    // byte0            byte1            byte2
    // 0x3F             0x0F             0x03
    // --aaaaaa         ----bbbb         ------cc
    // 0x30                              0x3F
    // --bb----         --cccc--         --dddddd
    // aaaaaabb         bbbbcccc         ccdddddd

    pad(&mut data, NUM_KEYS);

    let mut bytes: Vec<String> = Vec::new();
    for i in 0..NUM_BYTES {
        let s1 = &data[i].key;
        let s2 = &data[i+1].key;
        let m = format_mask(i, s1, s2);
        // we don't use the modifiers, just the keys
        bytes.push(m);
    }
    bytes
}

fn format_mask(i: usize, s1: &str, s2: &str) -> String {
    match i{
        0 => format!("(({}&0x3F)<<2)|(({}&0x30)>>4)", s1, s2),
        1 => format!("({}&0x0F)<<4|(({}&0x3C)>>2)", s1, s2),
        2 => format!("({}&0x03)<<6|({}&0x3F)", s1, s2),
        _ => panic!("format_mask: bad index"),
    }
}

fn pad(v: &mut Vec<KeyPress>, length: usize) {
    assert!(v.len() <= length);
    let num_to_pad = length.saturating_sub(v.len());
    for i in 0..num_to_pad {
        v.push( KeyPress::new_blank());
    }
}
