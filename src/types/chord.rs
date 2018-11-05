use std::fmt;

use error::{Error, ResultExt};
use types::{AnagramNum, CCode, Permutation, ToC};
use util::bools_to_bytes;

/// This stores the specifications of the chord format, as learned from the
/// settings file. We'll need it when creating a new empty Chord (to know how
/// long the vec of switches should be) and when converting Chords to bytes (to
/// put the switch bits in the correct order)

#[derive(Clone, Debug)]
pub struct ChordSpec {
    /// Number of switches on the keyboard and in each kmap chord. (NOT the
    /// number of matrix positions in the circuit)
    pub num_switches: usize,
    /// How to convert the switches from kmap order to firmware order
    pub to_firmware_order: Permutation,
}

/// A chord is a set of switches pressed simultaneously. In the case of words'
/// chords, the anagram number will be stored separately, instead of literally
/// including the anagram modifier's switches in the word chord.

#[derive(
    Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Serialize, Deserialize,
)]
pub struct Chord {
    /// Invariant: the length of this vec must always equal
    /// ChordSpec::num_switches.
    switches: Vec<bool>,
    pub anagram_num: AnagramNum,
}

////////////////////////////////////////////////////////////////////////////////

impl ChordSpec {
    /// This is impl'ed here instead of on Chord because Chord doesn't know how
    /// many switches it's supposed to have.
    pub fn new_chord(&self) -> Chord {
        Chord::new_with_length(self.num_switches)
    }

    /// Convert the chord into the byte representation used in the firmware.
    /// Treat each switch as a bit (1 means pressed). Permute them from kmap
    /// order to firmware order and pack them into bytes, padding the
    /// most-significant bits with zeros as needed.
    pub fn to_bytes(&self, chord: &Chord) -> Result<Vec<u8>, Error> {
        let ordered_bools = self.to_firmware_order.permute(&chord.switches)?;
        Ok(bools_to_bytes(&ordered_bools))
    }

    /// Convert the chord into CCode strings containing the byte representation
    /// used in the firmware.
    pub fn to_c_bytes(&self, chord: &Chord) -> Result<Vec<CCode>, Error> {
        Ok(self
            .to_bytes(chord)?
            .into_iter()
            .map(|x| x.to_c())
            .collect())
    }

    // TODO put this in output  module?
    pub fn to_c_initializer(&self, chord: &Chord) -> Result<CCode, Error> {
        Ok(format!("{{{}}}", self.to_c_bytes(chord)?.join(", ")).to_c())
    }

    // TODO put this in output  module?
    pub fn to_c_constructor(&self, chord: &Chord) -> Result<CCode, Error> {
        Ok(format!(
            "{}({})",
            Self::c_type_name(),
            self.to_c_initializer(chord)?
        ).to_c())
    }

    pub fn c_type_name() -> CCode {
        "ChordData".to_c()
    }
}

impl Chord {
    /// Construct a chord from bools representing each switch, in kmap order,
    /// where true means pressed. Invariant: the length of `switches` must match
    /// AllData.chord_spec.num_switches! Unfortunately this method can't check
    /// whether it does.
    pub fn from_vec(switches: Vec<bool>) -> Result<Self, Error> {
        Ok(Self {
            switches,
            anagram_num: AnagramNum::default(),
        })
    }

    fn new_with_length(len: usize) -> Self {
        Self {
            switches: vec![false; len],
            anagram_num: AnagramNum::default(),
        }
    }

    /// The number of pressed switches in this chord.
    pub fn count_pressed(&self) -> usize {
        self.switches.iter().filter(|x| **x).count()
    }

    /// Make all the switches pressed in the other chord pressed in this chord,
    /// too. The AnagramNum of the other chord must be zero/default, or it
    /// will return an error. That's because otherwise we're probably doing
    /// something wrong, and might lose information by discarding the
    /// anagram number. Usually we'll just be intersecting plain_keys
    /// and/or plain_mods.
    pub fn intersect_mut(&mut self, other: &Self) -> () {
        assert_eq!(self.len(), other.len());

        if !other.anagram_num.is_default() {
            // TODO return Result instead of unwrapping
            return Err(Error::BadValueErr {
                thing: "anagram number of other chord".to_owned(),
                value: other.anagram_num.to_string(),
            }).context("Failed to intersect chords")
            .unwrap();
        }

        for i in 0..self.switches.len() {
            self.switches[i] |= other.switches[i];
        }
    }

    pub fn intersect(&self, other: &Self) -> Self {
        let mut new = Self::new_with_length(self.len());
        new.intersect_mut(self);
        new.intersect_mut(other);
        new
    }

    /// An iterator over the switch booleans (in kmap order)
    pub fn iter(&self) -> ::std::slice::Iter<bool> {
        self.switches.iter()
    }

    fn len(&self) -> usize {
        self.switches.len()
    }

    /// Meant only for human-friendly debug printing
    fn bit_string(&self) -> String {
        let tmp: Vec<_> = self
            .switches
            .iter()
            .map(|&b| if b { "1" } else { "0" })
            .collect();
        tmp.join("")
    }
}

impl fmt::Debug for Chord {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "Chord {{ {} : {}}}",
            self.bit_string(),
            self.anagram_num.unwrap()
        )
    }
}
