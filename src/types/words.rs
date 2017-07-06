// use std::collections::BTreeMap;

use types::{Chord, Sequence, KeyPress, Maps, KmapPath, Name, CCode, ToC};
#[derive(Debug)]
pub struct Word {
    pub name: Name,
    pub seq: Sequence,
    pub chord: Chord,
    pub base_chord: Chord,
    pub anagram_num: u64
}

pub struct WordBuilder<'a> {
    pub seq_spelling: &'a str,
    pub chord_spelling: &'a str,
    pub anagram: u64,
    pub kmap: &'a KmapPath,
    pub maps: &'a Maps,
}

impl<'a> WordBuilder<'a> {
    pub fn finalize(&self) -> Word {
        let base = self.make_base_chord();
        Word{
            name: self.make_name(),
            seq: self.make_sequence(),
            chord: self.make_chord(&base),
            base_chord: base,
            anagram_num: self.anagram,

        }
    }

    fn make_name(&self) -> Name {
        // Ensure that each word has a unique name.

        let mut name = format!("word_{}", self.seq_spelling);
        if self.chord_spelling != self.seq_spelling {
            name += &format!("_{}", self.chord_spelling);
        }
        if self.anagram != 0 {
            name += &format!("_{}", self.anagram);
        }
        Name(name)
    }


    fn make_sequence(&self) -> Sequence {
        let mut seq = Sequence::new();
        for letter in self.seq_spelling.chars(){
            seq.push(KeyPress{key: self.get_key_name_for_seq(letter),
                              modifier: self.get_mod_name_for_seq(letter)})
        }
        seq
    }


    fn get_key_name_for_seq(&self, character: char) -> CCode {
        if character.is_alphanumeric() {
            return format!("KEY_{}", character.to_uppercase()).to_c();
        }
        let s = match character {
            ' '  => "KEY_SPACE",
            '<'  => "KEY_BACKSPACE",
            '\'' => "KEY_QUOTE",
            '.'  => "KEY_PERIOD",
            _ => panic!("illegal character in sequence: {}", character),
        };
        s.to_c()
    }

    fn get_mod_name_for_seq(&self, character: char) -> CCode {
        if character.is_uppercase() {
            "MODIFIERKEY_SHIFT".to_c()
        } else {
            "0".to_c()
        }
    }

    fn make_chord(&self, base: &Chord) -> Chord {
        let mut chord = base.to_owned();
        chord.intersect(&self.maps.get_anagram_chord(self.anagram, self.kmap));
        chord
    }

    fn make_base_chord(&self) -> Chord {
        let ignored = vec!['<', '.']; //TODO make this static?

        let mut chord = Chord::new();
        for letter in self.chord_spelling.chars(){
            if ignored.contains(&letter){
                continue;
            }
            chord.intersect(&self.get_letter_chord(letter));
        }
        chord
    }


    fn get_letter_chord(&self, letter: char) -> Chord {
        // TODO return option<chord>, for if not found
        let name = self.get_key_name_for_chord(letter);
        self.maps.get_chord(&name, self.kmap)
            .expect(&format!("no chord for key name: {}", name))
    }

    fn get_key_name_for_chord(&self, character: char) -> Name {
        if character.is_alphanumeric() {
            return Name(format!("key_{}", character.to_lowercase()))
        }
        Name(match character{
            ' '  => "key_space".to_owned(),
            '\'' => "key_quote".to_owned(),
            _ => panic!("illegal character in chord: {}", character),
        })
    }

}
