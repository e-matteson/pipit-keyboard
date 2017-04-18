use std::collections::BTreeMap;

use types::{Chord, Sequence, KeyPress};

pub struct Word {
    pub name: String,
    pub seq: Sequence,
    pub chord: Chord,
}


impl Word {
    pub fn new(seq_spelling: &str, chord_spelling: &str, anagram: u64,
               chords: &BTreeMap<String, Chord>) -> Word
    {
        let name = make_word_name(seq_spelling, chord_spelling, anagram);

        Word{
            name: name,
            seq: make_word_sequence(seq_spelling),
            chord: make_word_chord(chord_spelling, anagram, chords),
        }
    }
}

fn make_word_name(seq_spelling: &str, chord_spelling: &str,
                  anagram: u64) -> String {
    // Ensure that each word has a unique name.

    let mut name = format!("word_{}", seq_spelling);
    if chord_spelling != seq_spelling {
        name += &format!("_{}", chord_spelling);
    }
    if anagram != 0 {
        name += &format!("_{}", anagram);
    }
    name
}


fn make_word_sequence(word: &str) -> Sequence {
    let mut seq = Sequence::new();
    for letter in word.chars(){
        seq.push(KeyPress{key: get_key_name_for_seq(letter),
                          modifier: get_mod_name_for_seq(letter)})
    }
    seq
}


fn get_key_name_for_seq(character: char) -> String {
    if character.is_alphanumeric() {
        return format!("KEY_{}", character.to_uppercase());
    }
    match character{
        ' '  => "KEY_SPACE".to_owned(),
        '<'  => "KEY_BACKSPACE".to_owned(),
        '\'' => "KEY_QUOTE".to_owned(),
        '.'  => "KEY_PERIOD".to_owned(),
        _ => panic!("illegal character in sequence: {}", character),
    }
}

fn get_mod_name_for_seq(character: char) -> String {
    if character.is_uppercase() {
        "MODIFIERKEY_SHIFT".to_owned()
    } else {
        "0".to_owned()
    }
}

fn make_word_chord(word: &str, anagram: u64, chords: &BTreeMap<String, Chord>) -> Chord {
    let ignored = vec!['<', '.']; //TODO make this static?

    let mut chord = Chord::new();
    chord.set_anagram(anagram);
    for letter in word.chars(){
        if ignored.contains(&letter){
            continue;
        }
        chord.intersect(get_letter_chord(letter, chords));
    }
    chord
}


fn get_letter_chord(letter: char, chords: &BTreeMap<String, Chord>) -> &Chord {
    let name = get_key_name_for_chord(letter);
    chords.get(&name)
        .expect(&format!("no chord for key name: {}", name))
}

fn get_key_name_for_chord(character: char) -> String {
    if character.is_alphanumeric() {
        return format!("key_{}", character.to_lowercase())
    }
    match character{
        ' '  => "key_space".to_owned(),
        '\'' => "key_quote".to_owned(),
        _ => panic!("illegal character in chord: {}", character),
    }
}
