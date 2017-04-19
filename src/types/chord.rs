use itertools::Itertools;


// The chord length should be set once after the Options are read, and then be
// the same for all chords.

static mut CHORD_LENGTH: usize = 0;

fn set_chord_length(len: usize) {
    unsafe {
        CHORD_LENGTH = len;
    }
}

fn get_chord_length() -> usize {
    unsafe {
        CHORD_LENGTH
    }
}


#[derive(Debug)]
#[derive(Clone)]
pub struct Chord {
    bits: Vec<bool>,
}

impl Chord {
    pub fn set_num_bytes(x: i64) {
        set_chord_length((x*8) as usize);
    }

    pub fn new() -> Chord {
        Chord {
            bits: vec![false; get_chord_length()],
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
        }
    }

    pub fn len(&self) -> usize {
        self.bits.len()
    }

    pub fn get_single_switch_index(&self) -> Option<usize>{
        // If chord contains exactly 1 pressed switch, return its index.
        // Otherwise, return None.
        if self.bits.iter().filter(|x| **x).count() > 1 {
            return None;
        }
        self.bits.iter().position(|x| *x)
    }


    pub fn intersect(&mut self, other: &Chord){
        assert_eq!(self.len(), other.len());
        for i in 0..self.len(){
            self.bits[i] |= other.bits[i];
        }
    }

    pub fn permute(&mut self, order: &Vec<usize>) {
        assert_eq!(self.len(), order.len());
        let mut new = Chord::new();
        for i in 0..self.len(){
            new.bits[order[i]] = self.bits[i];
        }
        self.bits = new.bits;
    }

    pub fn to_string(&self) -> String {
        let tmp: Vec<_> = self.bits.iter().map(|&b| if b {"1"} else {"0"}).collect();
        tmp.join("")
    }

    pub fn to_ints(&self) -> Vec<i64> {
        let mut v: Vec<i64> = Vec::new();
        for chunk in &self.bits.iter().cloned().chunks(8) {
            let byte: Vec<_> = chunk.collect();
            v.push(byte_to_int(&byte));
        }
        v
    }

}

fn byte_to_int(v: &Vec<bool>) -> i64 {
    assert_eq!(v.len(), 8);
    let mut num: i64 = 0;
    let tmp: Vec<_> = v.iter().map(|&b| if b {1} else {0}).collect();
    let base: i64 = 2;
    for b in 0..8{
        num +=  base.pow(b) * tmp[b as usize]
    }
    num
}
