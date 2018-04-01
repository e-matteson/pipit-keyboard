#include "Entry.h"

// Entry::Entry(Chord* _chord, bool _is_anagrammable){
//   chord.copy(_chord);
//   is_anagrammable = _is_anagrammable;
// }

Entry::Entry(){
}

Chord* Entry::getChord(){
  return &chord;
}

void Entry::init(const Chord* _chord, bool _is_anagrammable){
  chord.copy(_chord);
  is_anagrammable = _is_anagrammable;
  length = 0;
}

void Entry::copy(const Entry* other){
  length = other->length;
  is_anagrammable = other->is_anagrammable;
  chord.copy(&other->chord);
  last_key = other->last_key;
}

void Entry::clear(){
  length = 0;
  is_anagrammable = 0;
  chord.clear();
}


uint8_t Entry::getLength(){
  return length;
}


void Entry::increment(){
  static const uint32_t max_val = exp(sizeof(length) * 8) - 1;
  if(length < max_val){
    length++;
  }
}

void Entry::decrement(){
  if(length > 0){
    length--;
  }
}

void Entry::setLength(uint8_t value){
  length = value;
}

void Entry::setLastLetter(uint8_t key_code, uint8_t mod_byte) {
  last_key.set(key_code, mod_byte);
}

void Entry::getLastLetter(Key* key){
  key->copy(&last_key);
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
