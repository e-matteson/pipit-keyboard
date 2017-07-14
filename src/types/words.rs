
use types::{Chord, Sequence, KeyPress, Maps, KmapPath, Name};

#[derive(Debug, Clone)]
pub struct WordInfo {
    pub seq_spelling: String,
    pub chord_spelling: String,
    pub anagram_num: u8,
}

#[derive(Debug)]
pub struct Word {
    pub name: Name,
    pub seq: Sequence,
    pub chord: Chord,
}

pub struct WordBuilder<'a> {
    pub info: WordInfo,
    pub kmap: &'a KmapPath,
    pub maps: &'a Maps,
}

impl<'a> WordBuilder<'a> {
    pub fn finalize(&self) -> Word {
        Word{
            name: self.make_name(),
            seq: self.make_sequence(),
            chord: self.make_chord(),
        }
    }

    fn make_name(&self) -> Name {
        // Ensure that each word has a unique name.

        let mut name = format!("word_{}", self.info.seq_spelling);
        if self.info.chord_spelling != self.info.seq_spelling {
            name += &format!("_{}", self.info.chord_spelling);
        }
        if self.info.anagram_num != 0 {
            name += &format!("_{}", self.info.anagram_num);
        }
        Name(name)
    }

    fn make_sequence(&self) -> Sequence {
        let mut seq = Sequence::new();
        for letter in self.info.seq_spelling.chars(){
            // TODO use new
            seq.push(
                KeyPress::new(
                    Some(self.get_key_code_for_seq(letter)),
                    self.get_mod_name_for_seq(letter)
                )
            );
        }
        seq
    }


    fn get_key_code_for_seq(&self, character: char) -> String {
        if character.is_alphanumeric() {
            return format!("KEY_{}", character.to_uppercase()).to_string();
        }
        let s = match character {
            ' '  => "KEY_SPACE",
            '<'  => "KEY_BACKSPACE",
            '\'' => "KEY_QUOTE",
            '.'  => "KEY_PERIOD",
            _ => panic!("illegal character in sequence: {}", character),
        };
        s.to_owned()
    }

    fn get_mod_name_for_seq(&self, character: char) -> Option<String> {
        if character.is_uppercase() {
            Some("MODIFIERKEY_SHIFT".to_owned())
        } else {
            None
        }
    }

    fn make_chord(&self) -> Chord {
        let ignored = vec!['<', '.']; //TODO make this static?

        let mut chord = Chord::new();
        for letter in self.info.chord_spelling.chars(){
            if ignored.contains(&letter){
                continue;
            }
            chord.intersect(&self.get_letter_chord(letter));
        }
        chord.anagram_num = self.info.anagram_num;
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
