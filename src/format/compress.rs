use itertools::Itertools;
use std::collections::HashMap;

use types::{CCode, CTree, KeyPress, SeqType, Sequence, ToC};
use types::errors::LookupErr;
use failure::Error;

impl SeqType {
    pub fn use_compression(&self) -> bool {
        match *self {
            SeqType::Word => true,
            SeqType::Command | SeqType::Macro | SeqType::Plain => false,
        }
    }
    pub fn use_modifiers(&self) -> bool {
        match *self {
            SeqType::Plain | SeqType::Macro => true,
            SeqType::Command | SeqType::Word => false,
        }
    }
}

impl KeyPress {
    pub fn huffman(&self) -> Result<Vec<bool>, Error> {
        lazy_static! {
            static ref TABLE: HashMap<CCode, Vec<bool>> = vec![
                ("KEY_A".to_c(), vec![false, false, false]),
                ("KEY_E".to_c(), vec![false, true, true]),
                ("KEY_C".to_c(), vec![false, false, true, false]),
                ("KEY_I".to_c(), vec![true, true, false, false]),
                ("KEY_L".to_c(), vec![false, false, true, true]),
                ("KEY_N".to_c(), vec![true, false, false, false]),
                ("KEY_O".to_c(), vec![true, false, false, true]),
                ("KEY_R".to_c(), vec![true, true, false, true]),
                ("KEY_S".to_c(), vec![false, true, false, false]),
                ("KEY_T".to_c(), vec![true, true, true, false]),
                ("KEY_D".to_c(), vec![false, true, false, true, true]),
                ("KEY_M".to_c(), vec![true, false, true, false, false]),
                ("KEY_P".to_c(), vec![true, false, true, true, false]),
                ("KEY_U".to_c(), vec![true, false, true, false, true]),
                ("KEY_B".to_c(), vec![true, true, true, true, false, false]),
                ("KEY_F".to_c(), vec![true, false, true, true, true, true]),
                ("KEY_G".to_c(), vec![true, true, true, true, true, false]),
                ("KEY_H".to_c(), vec![true, true, true, true, true, true]),
                ("KEY_V".to_c(), vec![false, true, false, true, false, false]),
                ("KEY_Y".to_c(), vec![true, false, true, true, true, false]),
                (
                    "KEY_K".to_c(),
                    vec![false, true, false, true, false, true, true],
                ),
                (
                    "KEY_W".to_c(),
                    vec![true, true, true, true, false, true, true],
                ),
                (
                    "KEY_J".to_c(),
                    vec![false, true, false, true, false, true, false, true],
                ),
                (
                    "KEY_X".to_c(),
                    vec![true, true, true, true, false, true, false, true],
                ),
                (
                    "KEY_Q".to_c(),
                    vec![true, true, true, true, false, true, false, false, true],
                ),
                (
                    "KEY_Z".to_c(),
                    vec![true, true, true, true, false, true, false, false, false],
                ),
                (
                    "KEY_QUOTE".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, true,
                        true,
                    ],
                ),
                (
                    "KEY_BACKSPACE".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, true,
                        false,
                    ],
                ),
                (
                    "KEY_PERIOD".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        true, false,
                    ],
                ),
                (
                    "KEY_EQUAL".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        false, true,
                    ],
                ),
                (
                    "KEY_SPACE".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        true, true, false,
                    ],
                ),
                (
                    "KEY_5".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        false, false, true,
                    ],
                ),
                (
                    "KEY_2".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        true, true, true, true,
                    ],
                ),
                (
                    "KEY_4".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        false, false, false, false,
                    ],
                ),
                (
                    "KEY_6".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        false, false, false, true,
                    ],
                ),
                (
                    "KEY_0".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        true, true, true, false, false,
                    ],
                ),
                (
                    "KEY_3".to_c(),
                    vec![
                        false, true, false, true, false, true, false, false, false,
                        true, true, true, false, true,
                    ],
                ),
            ].into_iter()
                .collect();
        }

        let key = self.key.as_ref().expect("keypress has no non-mod key");
        let bits: &Vec<bool> = TABLE.get(key).ok_or_else(|| LookupErr {
            key: key.into(),
            container: "huffman code table".into(),
        })?;

        Ok(bits.to_owned())
    }
}

// Constants used for compression
const NUM_BYTES: usize = 3;
const NUM_KEYS: usize = 4;


pub fn make_compression_macros() -> CTree {
    let mut g = Vec::new();
    g.push(CTree::Define {
        name: "BY0(X,Y)".to_c(),
        value: "(( X &0x3F)<<2) | (( Y &0x30)>>4)".to_c(),
    });
    g.push(CTree::Define {
        name: "BY1(X,Y)".to_c(),
        value: "(( X &0x0F)<<4) | (( Y &0x3C)>>2)".to_c(),
    });
    g.push(CTree::Define {
        name: "BY2(X,Y)".to_c(),
        value: "(( X &0x03)<<6) | ( Y &0x3F)".to_c(),
    });
    CTree::Group(g)
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
