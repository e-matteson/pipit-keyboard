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
  // is_clear = 0;
  length = 0;
}

void Entry::copy(const Entry* other){
  length = other->length;
  is_anagrammable = other->is_anagrammable;
  // is_clear = other->is_clear;
  chord.copy(&other->chord);
}

void Entry::clear(){
  // is_clear = 1;
  length = 0;
  is_anagrammable = 0;
  chord.clear();
}


uint8_t Entry::getLength(){
  return length;
}


void Entry::increment(){
  static const uint32_t max_val = sizeof(length) * 8 - 1;
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

void Entry::setAnagrammable(bool value){
  is_anagrammable = value;
}

bool Entry::isAnagrammable(){
  return is_anagrammable;
}

bool Entry::isClear(){
  return length == 0;
}

