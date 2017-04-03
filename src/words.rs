use std::collections::HashMap;

use options::*;
use key_types::*;

pub struct Word{
    pub name: String,
    pub seq: Sequence,
    pub chord: Chord,
}

pub fn make_word(entry: &Vec<String>, chords: &HashMap<String, Chord>, len_chord: usize)
                 -> Word {
    let name = get_word_name(entry);
    let seq_spelling = entry.first().unwrap();
    let chord_spelling = entry.last().unwrap();

    Word{
        name: name,
        seq: make_word_sequence(seq_spelling),
        chord: make_word_chord(chord_spelling, chords, len_chord),
    }
}


fn make_word_sequence(word: &str) -> Sequence {
    let mut seq: Sequence = Vec::new();
    for letter in word.chars(){
        seq.push(KeyPress{key: get_key_name_for_seq(letter),
                          modifier: get_mod_name_for_seq(letter)})
    }
    // println!("{:?}", seq);
    seq
}

fn get_word_name(entry: &Vec<String>) -> String{
    format!("word_{}", entry.join("_"))
}

fn get_key_name_for_seq(character: char) -> String {
    if character.is_alphabetic() {
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

fn make_word_chord(word: &str,
                   chords: &HashMap<String, Chord>,
                   len_chord: usize) -> Chord {
    // TODO test if the chord is right
    let ignored = vec!['<', '.']; //TODO make this static?

    // let chord = Vec::new();
    let mut chord = vec![false ; len_chord];
    for letter in word.chars(){
        if ignored.contains(&letter){
            continue;
        }
        let name = get_key_name_for_chord(letter);
        chord_intersect(&mut chord, &chords[&name]);
    }
    chord
}

fn chord_intersect(a: &mut Chord, b: &Chord){
    assert_eq!(a.len(), b.len());
    for i in 0..a.len(){
        a[i] |= b[i];
    }
}

fn get_key_name_for_chord(character: char) -> String {
    if character.is_alphabetic() {
        return format!("key_{}", character)
    }
    match character{
        ' '  => "key_space".to_owned(),
        '\'' => "key_quote".to_owned(),
        '~'  => "wordmod_anagram1".to_owned(),
        '+'  => "wordmod_anagram2".to_owned(),
        _ => panic!("illegal character in chord: {}", character),
    }
}
