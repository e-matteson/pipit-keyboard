
use types::{AllData, Chord, KeyPress, KmapPath, Name, Sequence, Validate};
use types::errors::*;

#[derive(Deserialize, Debug, Clone)]
#[serde(deny_unknown_fields)]
pub struct WordConfig {
    pub word: String,
    pub anagram: Option<AnagramNum>,
    pub chord: Option<String>,
}

impl Validate for WordConfig {
    fn validate(&self) -> Result<()> {
        self.anagram.validate()
        // TODO check for illegal characters?
        // self.word
        // self.chord
    }
}

impl WordConfig {
    fn seq_spelling(&self) -> String {
        self.word.clone()
    }

    fn chord_spelling(&self) -> String {
        self.chord.clone().unwrap_or(self.word.clone())
    }

    fn anagram_num(&self) -> AnagramNum {
        self.anagram.unwrap_or(AnagramNum(0))
    }

    fn has_alternate_chord(&self) -> bool {
        self.chord.is_some()
    }
}

#[derive(Debug)]
pub struct Word {
    pub name: Name,
    pub seq: Sequence,
    pub chord: Chord,
}

#[derive(Deserialize, Serialize, Debug, Clone, Copy, Eq, PartialEq, Ord,
         PartialOrd, Hash)]
#[serde(deny_unknown_fields)]
pub struct AnagramNum(pub u8);

impl Default for AnagramNum {
    fn default() -> AnagramNum {
        AnagramNum(0)
    }
}

impl Validate for AnagramNum {
    fn validate(&self) -> Result<()> {
        // TODO move max out somewere?
        // TODO how to keep this matched with make_prefix_byte()?
        const MAX_ANAGRAM: u8 = 7;
        if self.0 > MAX_ANAGRAM {
            bail!(
                "anagram number too large (max is {}): {}",
                MAX_ANAGRAM,
                self.0
            );
        }
        Ok(())
    }
}

impl From<AnagramNum> for usize {
    fn from(num: AnagramNum) -> usize {
        num.0 as usize
    }
}

pub struct WordBuilder<'a> {
    pub info: WordConfig,
    pub kmap: &'a KmapPath,
    pub all_data: &'a AllData,
}

impl<'a> WordBuilder<'a> {
    pub fn finalize(&self) -> Result<Word> {
        let seq_spelling = self.info.seq_spelling();
        let error_message = |thing| {
            format!("failure to make {} for: '{}'", thing, &seq_spelling)
        };
        Ok(Word {
            name: self.make_name(),
            chord: self.make_chord().chain_err(|| error_message("chord"))?,
            seq: self.make_sequence()
                .chain_err(|| error_message("sequence"))?,
        })
    }

    fn make_name(&self) -> Name {
        // Ensure that each word has a unique name.

        let mut name = format!("word_{}", self.info.seq_spelling());
        if self.info.has_alternate_chord() {
            name += &format!("_{}", self.info.chord_spelling());
        }
        let num = self.info.anagram_num();
        if num != AnagramNum(0) {
            name += &format!("_{}", num.0);
        }
        Name(name)
    }

    fn make_sequence(&self) -> Result<Sequence> {
        let mut seq = Sequence::new();
        for letter in self.info.seq_spelling().chars() {
            seq.push(
                KeyPress::new(
                    Some(self.get_key_code_for_seq(letter)?),
                    self.get_mod_name_for_seq(letter),
                ).unwrap(),
            );
        }
        Ok(seq)
    }

    fn get_key_code_for_seq(&self, character: char) -> Result<String> {
        if character.is_alphanumeric() {
            return Ok(format!("KEY_{}", character.to_uppercase()).to_string());
        }
        let s = match character {
            ' ' => "KEY_SPACE",
            '<' => "KEY_BACKSPACE",
            '\'' => "KEY_QUOTE",
            '.' => "KEY_PERIOD",
            ',' => "KEY_COMMA",
            _ => bail!(ErrorKind::BadValue(
                "character".into(),
                Some(character.to_string())
            )),
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
        let ignored = vec!['<'];

        let mut chord = Chord::new();

        let num = self.info.anagram_num();
        num.validate()?;
        chord.anagram_num = num;

        for letter in self.info.chord_spelling().chars() {
            if ignored.contains(&letter) {
                continue;
            }
            chord.intersect(&self.get_letter_chord(letter)?);
        }

        Ok(chord)
    }

    fn get_letter_chord(&self, letter: char) -> Result<Chord> {
        // TODO return option<chord>, for if not found
        let name = self.get_key_name_for_chord(letter)?;
        self.all_data.get_chord(&name, self.kmap).ok_or_else(|| {
            ErrorKind::MissingValue("chord".into(), Some(name.to_string()))
                .into()
        })
    }

    fn get_key_name_for_chord(&self, character: char) -> Result<Name> {
        if character.is_alphanumeric() {
            return Ok(Name(format!("key_{}", character.to_lowercase())));
        }
        let name = match character {
            ' ' => "key_space".into(),
            '.' => "key_period".into(),
            ',' => "key_comma".into(),
            '\'' => "key_quote".into(),
            _ => bail!(ErrorKind::BadValue(
                "character".into(),
                Some(character.to_string())
            )),
        };
        Ok(Name(name))
    }
}
