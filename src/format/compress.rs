use std::collections::HashMap;

use types::{CCode, CTree, Field, KeyPress, SeqType, ToC};
use types::errors::LookupErr;
use failure::Error;

c_struct!(
    struct HuffmanChar {
        bits: CCode,
        num_bits: usize,
        key_code: CCode
    }
);

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

pub fn render_huffman_lookup() -> CTree {
    let table = get_huffman_table();
    let mut group = Vec::new();

    group.push(CTree::Define {
        name: "NUM_HUFFMAN_CODES".to_c(),
        value: table.len().to_c(),
    });

    let mut initializers = Vec::new();
    for (key, huffman_code) in table.into_iter() {
        let name = format!("_huffman_bits_{}", key).to_c();
        let init = HuffmanChar {
            bits: name.clone(),
            num_bits: huffman_code.len(),
            key_code: key,
        }.render(CCode::new())
            .initializer();

        initializers.push(init);
        group.push(CTree::Array {
            name: name,
            values: huffman_code.into_iter().map(|b| b.to_c()).collect(),
            c_type: "bool".to_c(),
            is_extern: false,
        });
    }

    group.push(CTree::Array {
        name: "huffman_lookup".to_c(),
        values: initializers,
        c_type: "HuffmanChar".to_c(),
        is_extern: true,
    });

    CTree::Group(group)
}

pub fn get_huffman_table() -> HashMap<CCode, Vec<bool>> {
    vec![
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
                false, true, false, true, false, true, false, false, true, true
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
        .collect()
}

impl KeyPress {
    pub fn huffman(&self) -> Result<Vec<bool>, Error> {
        // TODO ensure codes are never longer than 255 bits! Firmware uses
        // uint8_t
        lazy_static! {
            static ref TABLE: HashMap<CCode, Vec<bool>> = get_huffman_table();
        }

        let key = self.key.as_ref().expect("keypress has no non-mod key");
        let bits: &Vec<bool> = TABLE.get(key).ok_or_else(|| LookupErr {
            key: key.into(),
            container: "huffman code table".into(),
        })?;

        Ok(bits.to_owned())
    }
}
