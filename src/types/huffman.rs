use std;
use std::collections::BTreeMap;
use std::collections::binary_heap::BinaryHeap;

use types::{CCode, KeyPress};

#[derive(Debug, Clone)]
pub struct HuffmanTable(pub BTreeMap<CCode, Vec<bool>>);

#[derive(Debug, Eq, PartialEq)]
enum HuffmanNode {
    Leaf {
        count: usize,
        key: CCode,
    },
    Branch {
        left: Box<HuffmanNode>,
        right: Box<HuffmanNode>,
    },
}

impl HuffmanTable {
    pub fn new(keys: Vec<KeyPress>) -> HuffmanTable {
        assert!(!keys.is_empty());
        let counts = count(keys);
        let tree = make_tree(counts).expect("failed to get huffman tree");
        let mut map = BTreeMap::new();
        make_codes(&tree, Vec::new(), &mut map);
        HuffmanTable(map)
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
    prefix: Vec<bool>,
    out: &mut BTreeMap<CCode, Vec<bool>>,
) {
    match node {
        HuffmanNode::Branch {
            ref left,
            ref right,
        } => {
            let mut left_prefix = prefix.clone();
            left_prefix.push(false);
            make_codes(&left, left_prefix, out);

            let mut right_prefix = prefix;
            right_prefix.push(true);
            make_codes(&right, right_prefix, out);
        }
        HuffmanNode::Leaf { ref key, .. } => {
            out.insert(key.to_owned(), prefix);
        }
    }
}

fn make_tree(counts: BTreeMap<CCode, usize>) -> Option<HuffmanNode> {
    let mut queue = BinaryHeap::new();
    for (key, count) in counts {
        queue.push(HuffmanNode::Leaf {
            key: key,
            count: count,
        });
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

fn count(keys: Vec<KeyPress>) -> BTreeMap<CCode, usize> {
    let mut counts = BTreeMap::new();
    for key_press in keys {
        if let Some(key_code) = key_press.key {
            increment(&mut counts, key_code);
        }
        if let Some(modifiers) = key_press.mods {
            for modifier in modifiers {
                increment(&mut counts, modifier);
            }
        }
    }
    counts
}

fn increment(map: &mut BTreeMap<CCode, usize>, key: CCode) {
    let count = map.entry(key).or_insert(0);
    *count += 1;
}
