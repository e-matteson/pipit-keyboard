use itertools::Itertools;
use std::fmt;

use types::AnagramNum;

// The chord length should be set once after the Options are read, and then be
// the same for all chords.

static mut CHORD_LENGTH: usize = 0;

fn set_chord_length(len: usize) {
    unsafe {
        CHORD_LENGTH = len;
    }
}

fn get_chord_length() -> usize {
    unsafe { CHORD_LENGTH }
}


#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Serialize, Deserialize)]
pub struct Chord {
    bits: Vec<bool>,
    pub anagram_num: AnagramNum,
}

impl Chord {
    pub fn set_num_bytes(x: usize) {
        set_chord_length(x * 8);
    }

    pub fn new() -> Chord {
        Chord {
            bits: vec![false; get_chord_length()],
            anagram_num: AnagramNum(0),
        }
    }

    pub fn from_vec(v: Vec<bool>) -> Chord {
        if get_chord_length() == 0 {
            panic!("chord length was not set");
        }
        if v.len() != get_chord_length() {
            panic!("wrong chord length");
        }
        Chord {
            bits: v,
            anagram_num: AnagramNum(0),
        }
    }

    pub fn len(&self) -> usize {
        self.bits.len()
    }

    pub fn count_switches(&self) -> usize {
        self.bits.iter().filter(|x| **x).count()
    }

    pub fn intersect(&mut self, other: &Chord) {
        assert_eq!(self.len(), other.len());
        for i in 0..self.len() {
            self.bits[i] |= other.bits[i];
        }
    }

    pub fn permute(&self, order: &[usize]) -> Chord {
        // TODO use different types for different permutations?
        assert_eq!(self.len(), order.len());
        let mut new = Chord::new();
        for i in 0..self.len() {
            new.bits[order[i]] = self.bits[i];
        }
        new
    }

    // pub fn to_string(&self) -> String {
    // let tmp: Vec<_> = self.bits.iter().map(|&b| if b {"1"} else
    // {"0"}).collect();
    //     tmp.join("")
    // }

    pub fn bits(&self) -> String {
        let tmp: Vec<_> = self.bits
            .iter()
            .map(|&b| if b { "1" } else { "0" })
            .collect();
        tmp.join("")
    }

    pub fn to_bools(&self) -> Vec<bool> {
        self.bits.clone()
    }

    pub fn to_ints(&self) -> Vec<u8> {
        let mut v: Vec<u8> = Vec::new();
        for chunk in &self.bits.iter().cloned().chunks(8) {
            let byte: Vec<_> = chunk.collect();
            v.push(byte_to_int(&byte));
        }
        v
    }

    // pub fn get_anagram(&self)
}

impl Default for Chord {
    fn default() -> Chord {
        Chord::new()
    }
}

impl fmt::Debug for Chord {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Chord {{ {} : {}}}", self.bits(), self.anagram_num.0)
    }
}

fn byte_to_int(v: &[bool]) -> u8 {
    assert_eq!(v.len(), 8);
    let mut num: u8 = 0;
    let base: u8 = 2;

    let bits: Vec<u8> = v.iter().map(|&b| if b { 1 } else { 0 }).collect();
    for b in 0..8 {
        num += base.pow(b) * bits[b as usize]
    }
    num
}
