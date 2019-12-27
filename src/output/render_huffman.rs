use std::cmp::Ordering;

use error::Error;
use types::{CCode, CTree, Field, HuffmanEntry, HuffmanTable, KeyPress, ToC};

c_struct!(
    struct HuffmanChar {
        bits: CCode,
        num_bits: usize,
        key_code: CCode,
        is_mod: bool,
    }
);

impl HuffmanTable {
    pub fn render(&self) -> Result<CTree, Error> {
        let mut group = Vec::new();
        group.push(CTree::ConstVar {
            name: "MIN_HUFFMAN_CODE_BIT_LEN".to_c(),
            value: self.min_length().to_c(),
            c_type: "uint8_t".to_c(),
            is_extern: true,
        });

        group.push(CTree::Array {
            name: "huffman_lookup".to_c(),
            values: self.initializers(),
            c_type: HuffmanChar::c_type(),
            is_extern: true,
        });

        Ok(CTree::Group(group))
    }

    pub fn render_early(&self) -> CTree {
        CTree::Define {
            name: "MAX_HUFFMAN_CODE_BIT_LEN".to_c(),
            value: self.max_length().to_c(),
        }
    }

    fn initializers(&self) -> Vec<CCode> {
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
    fn to_huffman_char(&self, key: &CCode) -> HuffmanChar {
        HuffmanChar {
            bits: self.to_c_constructor(),
            num_bits: self.num_bits(),
            key_code: KeyPress::truncate(key),
            is_mod: self.is_mod,
        }
    }

    fn to_c_bytes(&self) -> Vec<CCode> {
        // TODO impl ToC for BitVec?
        self.bits().blocks().map(|x| x.to_c()).collect()
    }

    fn to_c_initializer(&self) -> CCode {
        format!("{{{}}}", self.to_c_bytes().join(", ")).to_c()
    }

    fn to_c_constructor(&self) -> CCode {
        // TODO there are a bunch of extra allocations here...
        format!("{}({})", Self::c_type_name(), self.to_c_initializer()).to_c()
    }

    fn c_type_name() -> CCode {
        "HuffmanBits".to_c()
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
