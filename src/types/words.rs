
use types::{Chord, Sequence, KeyPress, Maps, KmapPath, Name};
use types::errors::*;

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
    pub fn finalize(&self) -> Result<Word> {
        Ok(
            Word{
                name: self.make_name(),
                seq: self.make_sequence()
                    .chain_err(||ErrorKind::BadValue(
                        "word".into(),
                        Some(self.info.seq_spelling.clone()))
                    )?,
                // TODO make general purpose failure enum?
                chord: self.make_chord()
                    .chain_err(||format!("failure to make chord for: '{}'",
                                         self.info.seq_spelling))?,
            }
        )
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

    fn make_sequence(&self) -> Result<Sequence> {
        let mut seq = Sequence::new();
        for letter in self.info.seq_spelling.chars(){
            seq.push(
                KeyPress::new(
                    Some(self.get_key_code_for_seq(letter)?),
                    self.get_mod_name_for_seq(letter)
                ) .unwrap()
            );
        }
        Ok(seq)
    }


    fn get_key_code_for_seq(&self, character: char) -> Result<String> {
        if character.is_alphanumeric() {
            return Ok(format!("KEY_{}", character.to_uppercase()).to_string());
        }
        let s = match character {
            ' '  => "KEY_SPACE",
            '<'  => "KEY_BACKSPACE",
            '\'' => "KEY_QUOTE",
            '.'  => "KEY_PERIOD",
            _ => bail!(
                ErrorKind::BadValue(
                    "character".into(),
                    Some(character.to_string())
                )
            ),
    };
    Ok(s.into())
}

    fn get_mod_name_for_seq(&self, character: char) -> Option<Vec<String>> {
        if character.is_uppercase() {
            Some(vec!["MODIFIERKEY_SHIFT".into()])
        } else {
            None
        }
    }

    fn make_chord(&self) -> Result<Chord> {
        let ignored = vec!['<', '.']; //TODO make this static?

        let mut chord = Chord::new();
        for letter in self.info.chord_spelling.chars(){
            if ignored.contains(&letter){
                continue;
            }
            chord.intersect(&self.get_letter_chord(letter)?);
        }
        check_valid_anagram(self.info.anagram_num)?;
        chord.anagram_num = self.info.anagram_num;
        Ok(chord)
    }

    fn get_letter_chord(&self, letter: char) -> Result<Chord> {
        // TODO return option<chord>, for if not found
        let name = self.get_key_name_for_chord(letter)?;
        self.maps
            .get_chord(&name, self.kmap)
            .ok_or_else(
                || ErrorKind::MissingValue(
                    "chord".into(),
                    Some(name.to_string())
                ).into()
            )
    }

    fn get_key_name_for_chord(&self, character: char) -> Result<Name> {
        if character.is_alphanumeric() {
            return Ok(Name(format!("key_{}", character.to_lowercase())))
        }
        let name = match character{
            ' '  => "key_space".into(),
            '\'' => "key_quote".into(),
            _ => bail!(
                ErrorKind::BadValue(
                    "character".into(),
                    Some(character.to_string())
                )
            )
        };
        Ok(Name(name))
    }
}

fn check_valid_anagram(anagram_num: u8) -> Result<()> {
    // TODO move max out somewere?
    // TODO how to keep this matched with make_prefix_byte()?
    const MAX_ANAGRAM: u8 = 7;
    if anagram_num > MAX_ANAGRAM {
        bail!("anagram number too large (max is {}): {}",
              MAX_ANAGRAM,
              anagram_num);
    }
    Ok(())
}
