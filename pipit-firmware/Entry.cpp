#include "Entry.h"


Entry::Entry(const Chord* _chord, bool _is_anagrammable)
  : is_anagrammable(_is_anagrammable), chord(*_chord) {
}

const Chord* Entry::getChord(){
  return &chord;
}

uint8_t Entry::getLength(){
  return length;
}


/// Increment the entry length, saturating at the max value.
void Entry::increment(){
  length++;
  if(length == 0) {
    // Oops, we were at the max value before incrementing, so let's underflow
    // back to the max.
    length--;
  }
}

/// Decrement the entry length, saturating at 0.
void Entry::decrement(){
  if(length > 0){
    length--;
  }
}

void Entry::setLength(uint8_t value){
  length = value;
}

void Entry::setLastLetter(uint8_t key_code, uint8_t mod_byte) {
  last_key = Key(key_code, mod_byte);
}

Key* Entry::getLastLetter(){
  return &last_key;
}

void Entry::setAnagrammable(bool value){
  is_anagrammable = value;
}

bool Entry::isAnagrammable(){
  return is_anagrammable;
}

bool Entry::isClear(){
  return length == 0;
}
