use bit_vec::BitVec;
use byteorder::{ByteOrder, LittleEndian};
use std;
use std::collections::binary_heap::BinaryHeap;
use std::collections::BTreeMap;
use std::iter;

use error::{Error, ResultExt};
use types::{CCode, KeyPress, ToC};
use util::ensure_u8;

#[derive(Debug, Clone)]
pub struct HuffmanTable(pub BTreeMap<CCode, HuffmanEntry>);

#[derive(Debug, Clone)]
pub struct HuffmanEntry {
    pub is_mod: bool,
    bits: BitVec<u8>,
}

#[derive(Debug, Eq, PartialEq)]
enum HuffmanNode {
    Leaf {
        count: usize,
        key: CCode,
        is_mod: bool,
    },
    Branch {
        left: Box<HuffmanNode>,
        right: Box<HuffmanNode>,
    },
}

impl HuffmanEntry {
    pub fn num_bits(&self) -> usize {
        self.bits.len()
    }

    pub fn as_uint32(&self) -> Result<CCode, Error> {
        const MAX_LEN: usize = 32;
        if self.num_bits() > MAX_LEN {
            return Err(Error::OutOfRangeErr {
                name: "huffman encoding length".into(),
                value: self.num_bits(),
                min: 0,
                max: MAX_LEN,
            });
        }

        let mut bytes: Vec<_> = self.bits.blocks().collect();
        let padding = 4 - bytes.len();
        bytes.extend(iter::repeat(0u8).take(padding));

        let out = LittleEndian::read_u32(&bytes);
        Ok(out.to_c())
    }
}

impl HuffmanTable {
    pub fn new(keys: Vec<KeyPress>) -> Result<Self, Error> {
        assert!(!keys.is_empty());
        let counts = count(keys);
        let tree = make_tree(counts).expect("failed to make huffman tree");
        let mut map = BTreeMap::new();
        make_codes(&tree, BitVec::default(), &mut map)?;
        ensure_u8(map.len())
            .context("Huffman table contains too many encodings")?;
        Ok(HuffmanTable(map))
    }

    pub fn bits(&self, key: &CCode) -> Result<&BitVec<u8>, Error> {
        Ok(&self.get(key)?.bits)
    }

    pub fn get(&self, key: &CCode) -> Result<&HuffmanEntry, Error> {
        self.0.get(key).ok_or_else(|| Error::LookupErr {
            key: key.into(),
            container: "huffman code table".into(),
        })
    }
}

impl HuffmanNode {
    fn count(&self) -> usize {
        match self {
            HuffmanNode::Leaf { count, .. } => *count,
            HuffmanNode::Branch { left, right } => left.count() + right.count(),
        }
    }
}

impl Ord for HuffmanNode {
    /// Most frequent nodes come first.
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        other.count().cmp(&self.count())
    }
}

impl PartialOrd for HuffmanNode {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(&other))
    }
}

fn make_codes(
    node: &HuffmanNode,
    prefix: BitVec<u8>,
    out: &mut BTreeMap<CCode, HuffmanEntry>,
) -> Result<(), Error> {
    match node {
        HuffmanNode::Branch {
            ref left,
            ref right,
        } => {
            let mut left_prefix = prefix.clone();
            left_prefix.push(false);
            make_codes(&left, left_prefix, out)?;

            let mut right_prefix = prefix;
            right_prefix.push(true);
            make_codes(&right, right_prefix, out)?;
        }
        HuffmanNode::Leaf {
            ref key, is_mod, ..
        } => {
            out.insert(
                key.to_owned(),
                HuffmanEntry {
                    bits: prefix,
                    is_mod: *is_mod,
                },
            );
        }
    }
    Ok(())
}

fn make_tree(counts: BTreeMap<CCode, (usize, bool)>) -> Option<HuffmanNode> {
    let mut queue = BinaryHeap::new();
    for (key, (count, is_mod)) in counts {
        queue.push(HuffmanNode::Leaf { key, is_mod, count });
    }
    while queue.len() >= 2 {
        let left = queue.pop().unwrap();
        let right = queue.pop().unwrap();
        queue.push(HuffmanNode::Branch {
            left: Box::new(left),
            right: Box::new(right),
        });
    }
    queue.pop()
}

fn count(keys: Vec<KeyPress>) -> BTreeMap<CCode, (usize, bool)> {
    let mut counts: BTreeMap<CCode, (usize, bool)> = BTreeMap::new();
    for keypress in keys {
        increment(&mut counts, keypress.key_or_blank(), false);
        for modifier in keypress.mods {
            increment(&mut counts, modifier, true);
        }
    }
    counts
}
// TODO closure
fn increment(
    map: &mut BTreeMap<CCode, (usize, bool)>,
    key: CCode,
    is_mod: bool,
) {
    let count = map.entry(key).or_insert((0, is_mod));
    (*count).0 += 1;
}

// #[test]
// fn test_huffman_bits() {
//     let table = make_test_table();
//     println!("{:?}", table);
//     let a_entry = &table.get(&"a".to_c()).unwrap().bits;
//     let b_entry = &table.get(&"b".to_c()).unwrap().bits;
//     let c_entry = &table.get(&"c".to_c()).unwrap().bits;
//     assert!(a_entry.get(0).unwrap() == true);
//     assert!(b_entry.get(0).unwrap() == false);
//     assert!(b_entry.get(1).unwrap() == true);
//     assert!(c_entry.get(0).unwrap() == false);
//     assert!(c_entry.get(1).unwrap() == false);
// }

// #[test]
// fn test_huffman_u32() {
//     let table = make_test_table();
//     let a_entry = table.get(&"a".to_c()).unwrap();
//     let b_entry = table.get(&"b".to_c()).unwrap();
//     let c_entry = table.get(&"c".to_c()).unwrap();
//     assert_eq!(a_entry.as_uint32(), 1.to_c());
//     assert_eq!(b_entry.as_uint32(), 2.to_c());
//     assert_eq!(c_entry.as_uint32(), 0.to_c());
// }

// #[cfg(test)]
// fn make_test_table() -> HuffmanTable {
//     let a = KeyPress::new_key("a");
//     let b = KeyPress::new_key("b");
//     let c = KeyPress::new_key("c");
//     let input =
//         vec![a.clone(), a.clone(), a.clone(), a.clone(), b.clone(), b, c];
//     HuffmanTable::new(input).unwrap()
// }
