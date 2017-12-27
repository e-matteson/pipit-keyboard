// use itertools::Itertools;
use std::fmt;
use std::sync::Mutex;

use types::{AnagramNum, Permutation};

// The chord length should be set once after the Options are read, and then be
// the same for all chords.

// static mut INFO: Option<GlobalChordInfo> = None;

lazy_static! {
    static ref INFO: Mutex<Option<GlobalChordInfo>> = Mutex::new(None);
}

#[derive(Clone, Debug)]
pub struct GlobalChordInfo {
    pub num_bytes: usize,
    pub num_switches: usize,
    pub num_matrix_positions: usize,
    pub to_firmware_order: Permutation,
}

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Serialize, Deserialize)]
pub struct Chord {
    bits: Vec<bool>,
    pub anagram_num: AnagramNum,
}

////////////////////////////////////////////////////////////////////////////////

impl Chord {
    pub fn set_info(info: GlobalChordInfo) {
        set_static_info(info);
    }

    pub fn global_length() -> usize {
        static_info().num_switches
    }

    pub fn new() -> Chord {
        Chord {
            bits: vec![false; Chord::global_length()],
            anagram_num: AnagramNum(0),
        }
    }

    pub fn from_vec(v: Vec<bool>) -> Chord {
        if v.len() != Chord::global_length() {
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

    pub fn count_pressed(&self) -> usize {
        self.bits.iter().filter(|x| **x).count()
    }

    pub fn intersect(&mut self, other: &Chord) {
        assert_eq!(self.len(), other.len());
        for i in 0..self.len() {
            self.bits[i] |= other.bits[i];
        }
    }

    fn bit_string(&self) -> String {
        let tmp: Vec<_> = self.bits
            .iter()
            .map(|&b| if b { "1" } else { "0" })
            .collect();
        tmp.join("")
    }

    pub fn iter(&self) -> ::std::slice::Iter<bool> {
        self.bits.iter()
    }

    pub fn to_bytes(&self) -> Vec<u8> {
        // Permute to the order used in the firmware, pad to a whole number of
        // bytes, and convert to 8-bit ints
        // TODO return result
        let ordered_bools = static_info()
            .to_firmware_order
            .permute(&self.bits)
            .expect("failed to permute chord");

        let mut bytes: Vec<u8> = Vec::new();
        for chunk in ordered_bools.chunks(8) {
            bytes.push(bools_to_u8(chunk));
        }
        bytes
    }
}

impl Default for Chord {
    fn default() -> Chord {
        Chord::new()
    }
}

impl fmt::Debug for Chord {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "Chord {{ {} : {}}}",
            self.bit_string(),
            self.anagram_num.0
        )
    }
}

fn bools_to_u8(v: &[bool]) -> u8 {
    // If v is shorter than 8, the missing most-significant digits will be zero
    assert!(v.len() <= 8);
    let mut num: u8 = 0;
    let base: u8 = 2;
    for b in 0..8 {
        let bit = if *v.get(b).unwrap_or(&false) { 1 } else { 0 };
        num += base.pow(b as u32) * bit
    }
    num
}

// fn right_pad_default<T>(v: Vec<T>, pad_width: usize) -> Vec<T>
// where
//     T: Default + Clone,
// {
//     iter::repeat(T::default())
//         .take(pad_width)
//         .chain(v.into_iter())
//         .collect()
// }


fn set_static_info(info: GlobalChordInfo) {
    let mut static_info = INFO.lock().unwrap();
    match *static_info {
        Some(_) => panic!("static chord info can only be set once"),
        None => *static_info = Some(info),
    }
}

fn static_info() -> GlobalChordInfo {
    INFO.lock()
        .unwrap()
        .clone()
        .expect("static chord info was not set")
}
