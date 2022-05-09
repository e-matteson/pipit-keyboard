use std::cmp::Ordering;

use error::Error;
use types::{
    CIdent, CLiteral, CTree, CType, HuffmanEntry, HuffmanTable, KeyPress,
};

c_struct!(
    struct HuffmanChar {
        bits: CTree,
        num_bits: usize,
        key_code: CTree,
        is_mod: bool,
    }
);

impl HuffmanTable {
    pub fn render(&self) -> Result<CTree, Error> {
        let mut group = Vec::new();

        group.push(CTree::ConstDef {
            name: KeyPress::blank_ident(),
            value: Box::new(KeyPress::blank_value().into()),
            c_type: CType::U8,
        });

        group.push(CTree::ConstDef {
            name: "MIN_HUFFMAN_CODE_BIT_LEN".into(),
            value: Box::new(self.min_length().into()),
            c_type: CType::U8,
        });

        let initializers = self.initializers();
        group.push(CTree::ConstDef {
            name: "huffman_lookup".into(),
            c_type: CType::array(HuffmanChar::c_type(), initializers.len()),
            value: Box::new(CTree::ArrayInit {
                values: initializers,
            }),
        });

        Ok(CTree::Group(group))
    }

    pub fn render_early(&self) -> CTree {
        CTree::ConstDef {
            name: "MAX_HUFFMAN_CODE_BIT_LEN".into(),
            value: Box::new(self.max_length().into()),
            c_type: CType::U8,
        }
    }

    fn initializers(&self) -> Vec<CTree> {
        let mut v: Vec<_> = self
            .0
            .iter()
            .map(|(key, entry)| entry.to_huffman_char(key))
            .collect();
        v.sort();
        v.into_iter()
            .map(|huffchar| huffchar.initializer())
            .collect()
    }
}

impl HuffmanEntry {
    fn to_huffman_char(&self, key: &CIdent) -> HuffmanChar {
        HuffmanChar {
            bits: self.to_struct_initializer(),
            num_bits: self.num_bits(),
            key_code: CTree::Cast {
                value: Box::new(key.to_owned().into()),
                new_type: CType::U8,
            },
            is_mod: self.is_mod,
        }
    }

    fn to_c_bytes(&self) -> Vec<CTree> {
        self.bits()
            .blocks()
            .map(|x| CTree::Literal(CLiteral(x.to_string())))
            .collect()
    }

    pub fn to_struct_initializer(&self) -> CTree {
        CTree::StructInit {
            struct_type: Self::c_type_name(),
            values: vec![CTree::ArrayInit {
                values: self.to_c_bytes(),
            }],
        }
    }

    fn c_type_name() -> CType {
        CType::custom("HuffmanBits")
    }
}

impl PartialOrd for HuffmanChar {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for HuffmanChar {
    fn cmp(&self, other: &Self) -> Ordering {
        self.num_bits.cmp(&other.num_bits)
    }
}
