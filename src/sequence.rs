use itertools::Itertools;
use std::cmp::max;
use std::slice::Iter;

// Constants used for compression
const NUM_BYTES: usize =  3;
const NUM_KEYS: usize = 4;


// TODO KeyPress is also used to store special codes, which is kinda a hack. Rename?

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Eq)]
#[derive(Clone)]
pub struct KeyPress{
    pub key: String,
    pub modifier: String,
}

impl KeyPress{
    pub fn new(key: usize, modifier: usize) -> KeyPress {
        KeyPress{
            key: format!("{}", key),
            modifier: format!("{}", modifier),
        }
    }
    pub fn new_blank() -> KeyPress {
        KeyPress{
            key: "0".to_owned(),
            modifier: "0".to_owned(),
        }
    }
    pub fn is_mod_blank(&self) -> bool {
        self.modifier == "0"
    }
}


#[derive(Debug)]
#[derive(Clone)]
pub struct Sequence (
    pub Vec<KeyPress>
);

impl Sequence {
    pub fn new() -> Sequence {
        Sequence(Vec::new())
    }

    pub fn extend (&mut self, other: Sequence) {
        self.0.extend(other.0)
    }

    pub fn push (&mut self, keypress: KeyPress) {
        self.0.push(keypress)
    }

    pub fn len (&self) -> usize {
        self.0.len()
    }

    pub fn keypresses(&self) -> Iter<KeyPress> {
        self.0.iter()
    }

    pub fn get_only_value(&self) -> &str{

        assert_eq!(self.len(), 1);
        let only_key = &self.0[0];
        assert!(only_key.is_mod_blank());
        &only_key.key
    }

    pub fn to_bytes(&self, use_compression: bool, use_mods: bool) -> Vec<String>{
        // TODO different name for "bytes"?
        if use_compression{
            self.to_compressed_bytes(use_mods)
        }
        else {
            self.to_raw_bytes(use_mods)
        }
    }

    fn to_raw_bytes(&self, use_mods: bool) -> Vec<String> {
        let mut v: Vec<String> = Vec::new();
        for keypress in self.keypresses() {
            v.extend(keypress.as_bytes(use_mods));
        }
        v
    }

    fn to_compressed_bytes(&self, use_mods: bool) -> Vec<String> {
        let mut compressed: Vec<String> = Vec::new();
        let chunks = &self.keypresses().cloned().chunks(NUM_KEYS);
        for chunk in chunks{
            let vals: Vec<_> = chunk.collect();
            compressed.extend(compress_chunk(vals));
        }
        compressed
    }

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
