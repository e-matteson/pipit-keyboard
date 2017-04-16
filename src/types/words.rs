use std::collections::BTreeMap;

use types::{Chord, Sequence, KeyPress};

pub struct Word {
    pub name: String,
    pub seq: Sequence,
    pub chord: Chord,
}


impl Word {
    pub fn new(entry: &Vec<String>, chords: &BTreeMap<String, Chord>) -> Word {
        let name = make_word_name(entry);
        let seq_spelling = entry.first().unwrap();
        let chord_spelling = entry.last().unwrap();

        Word{
            name: name,
            seq: make_word_sequence(seq_spelling),
            chord: make_word_chord(chord_spelling, chords),
        }
    }
}


fn make_word_sequence(word: &str) -> Sequence {
    let mut seq = Sequence::new();
    for letter in word.chars(){
        seq.push(KeyPress{key: get_key_name_for_seq(letter),
                          modifier: get_mod_name_for_seq(letter)})
    }
    seq
}

fn make_word_name(entry: &Vec<String>) -> String{
    format!("word_{}", entry.join("_"))
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

fn make_word_chord(word: &str, chords: &BTreeMap<String, Chord>) -> Chord {
    let ignored = vec!['<', '.']; //TODO make this static?

    let mut chord = Chord::new();
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
        '~'  => "wordmod_anagram1".to_owned(),
        '+'  => "wordmod_anagram2".to_owned(),
        _ => panic!("illegal character in chord: {}", character),
    }
}
