use bit_vec::{self, BitVec};
use std::fmt::Debug;
use std::hash::Hash;
use std::iter::{repeat, FromIterator};
use std::marker::PhantomData;

use error::{Error, ResultExt};
use types::{AnagramNum, Permutation};

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
#[derive(Clone, Eq, PartialEq, PartialOrd, Hash, Debug)]
pub struct Chord<T>
where
    T: ChordOrdering,
{
    /// Invariant: the length of this vec must always be equal to
    /// ChordSpec::num_switches.
    switches: BitVec<u8>,
    pub anagram_num: AnagramNum,
    order: PhantomData<T>,
}

pub trait ChordOrdering:
    Clone + Eq + PartialEq + Ord + PartialOrd + Hash + Debug
{
}

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Debug)]
pub enum KmapOrder {}

#[derive(Clone, Eq, PartialEq, Ord, PartialOrd, Hash, Debug)]
pub enum FirmwareOrder {}

impl ChordOrdering for KmapOrder {}
impl ChordOrdering for FirmwareOrder {}

////////////////////////////////////////////////////////////////////////////////

impl ChordSpec {
    /// This is impl'ed here instead of on Chord because Chord doesn't know how
    /// many switches it's supposed to have.
    pub fn new_chord(&self) -> Chord<KmapOrder> {
        Chord::new_with_length(self.num_switches)
    }

    pub fn to_firmware(
        &self,
        chord: &Chord<KmapOrder>,
    ) -> Result<Chord<FirmwareOrder>, Error> {
        let ordered = self.to_firmware_order.permute(chord.switches())?;
        Ok(Chord {
            switches: ordered,
            anagram_num: chord.anagram_num,
            order: PhantomData,
        })
    }
}

impl<T> Chord<T>
where
    T: ChordOrdering,
{
    /// The number of pressed switches in this chord.
    pub fn count_pressed(&self) -> usize {
        self.switches
            .blocks()
            .fold(0, |accum, b| accum + b.count_ones()) as usize
    }

    /// Make all the switches pressed in the other chord pressed in this chord,
    /// too. The AnagramNum of the other chord must be zero/default, or it
    /// will return an error. That's because otherwise we're probably doing
    /// something wrong, and might lose information by discarding the
    /// anagram number. Usually we'll just be unioning plain_keys
    /// and/or plain_mods.
    pub fn union_mut(&mut self, other: &Self) -> Result<(), Error> {
        assert_eq!(self.len(), other.len());

        if !other.anagram_num.is_default() {
            return Err(Error::BadValueErr {
                thing: "anagram number of other chord".to_owned(),
                value: other.anagram_num.to_string(),
            })
            .context("Failed to union chords");
        }
        self.switches.union(&other.switches);
        Ok(())
    }

    /// Return a new chord that's the union of this one and the given one.
    pub fn union(&self, other: &Self) -> Result<Self, Error> {
        let mut new = self.to_owned();
        new.union_mut(other)?;
        Ok(new)
    }

    pub fn intersect_mut(&mut self, other: &Self) -> Result<(), Error> {
        assert_eq!(self.len(), other.len());
        if !other.anagram_num.is_default() {
            return Err(Error::BadValueErr {
                thing: "anagram number of other chord".to_owned(),
                value: other.anagram_num.to_string(),
            })
            .context("Failed to intersect chords");
        }
        self.switches.intersect(&other.switches);
        Ok(())
    }

    fn len(&self) -> usize {
        self.switches.len()
    }

    pub fn switches(&self) -> &BitVec<u8> {
        &self.switches
    }
}

impl Chord<KmapOrder> {
    /// Construct a chord from bools representing each switch, in kmap order,
    /// where true means pressed. Invariant: the length of `switches` must match
    /// AllData.chord_spec.num_switches! Unfortunately this method can't check
    /// whether it does.
    pub fn from_vec(switches: Vec<bool>) -> Result<Self, Error> {
        Ok(Self {
            switches: BitVec::from_iter(switches.into_iter()),
            anagram_num: AnagramNum::default(),
            order: PhantomData,
        })
    }

    fn new_with_length(len: usize) -> Self {
        Self {
            switches: BitVec::from_iter(repeat(false).take(len)),
            anagram_num: AnagramNum::default(),
            order: PhantomData,
        }
    }

    // An iterator over the switch booleans (in kmap order). The type signature
    // says u8, but the iterator's Item is actually a bool.
    pub fn iter(&self) -> bit_vec::Iter<'_, u8> {
        self.switches.iter()
    }
}

// impl fmt::Debug for Chord<T>
// where
//     T: ChordOrdering,
// {
//     fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
//         write!(
//             f,
//             "Chord<{}> {{ {:?} : {}}}",
//             self.order_label(),
//             self.switches,
//             self.anagram_num.get()
//         )
//     }
// }
