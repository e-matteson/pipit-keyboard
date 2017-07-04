#include "Chord.h"

Chord::Chord(conf::mode_enum mode) : mode(mode){
}

Chord::Chord(){
  mode = (conf::mode_enum) 0;
}


void Chord::setChordArray(const uint8_t* new_chord_bytes){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = new_chord_bytes[i];
  }
}

bool Chord::isEmpty() const{
  // Doesn't check the mods, just the current chord bytes.
  // This is important because sendIfEmpty should send mods.
  // TODO abort after 1st set bit?
  return countBitsSet(chord_bytes) == 0;
}

uint8_t Chord::getModByte() const{
  uint8_t mod_byte = 0;
  for(uint8_t i = 0; i < NUM_MODIFIERKEYS; i++){
    conf::mod_enum mod = conf::getModifierkeyEnum(i);
    mod_byte |= hasMod(mod) ? conf::getModifierkeyByte(i) : 0;
  }
  return mod_byte;
}

conf::mode_enum Chord::getMode() const{
  return mode;
}

bool Chord::matches(const uint8_t* lookup_chord_bytes) const{
  // Use this for checking whether a lookup table entry matches this chord.
  return isEqual(chord_bytes, lookup_chord_bytes);
}

void Chord::copy(const Chord* chord){
  mode = chord->mode;
  for(int i = 0; i < NUM_MODIFIERS; i++){
    mods[i] = chord->mods[i];
  }
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = chord->chord_bytes[i];
  }
}

void Chord::clear(){
  mode = (conf::mode_enum) 0;
  for(uint8_t i = 0; i < NUM_MODIFIERS; i++){
    mods[i] = 0;
  }
  for(uint8_t i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = 0;
  }
}

bool Chord::hasCapitalWordmod() const{
  // TODO avoid using enums outside conf?
  return hasMod(conf::getCapitalEnum());
}

bool Chord::hasNospaceWordmod() const{
  return hasMod(conf::getNospaceEnum());
}

bool Chord::hasMod(conf::mod_enum mod) const{
  return mods[mod];
}

void Chord::blankMods(){
  for(uint8_t i = 0; i < NUM_MODIFIERKEYS; i++){
    blankMod(conf::getModifierkeyEnum(i));
  }
}

void Chord::blankWordmods(){
  for(uint8_t i = 0; i < NUM_WORDMODS; i++){
    blankMod(conf::getWordmodEnum(i));
  }
}

void Chord::restoreWordmods(){
  for(uint8_t i = 0; i < NUM_WORDMODS; i++){
    restoreMod(conf::getWordmodEnum(i));
  }
}

void Chord::blankMod(conf::mod_enum modifier){
  // Store the bit(s) of wordmod that are set in the current chord.
  const uint8_t* mod_chord_bytes = conf::getModChord(mode, modifier);
  if(isChordMaskSet(mod_chord_bytes, chord_bytes)){
    mods[modifier] = 1;
    unsetMask(mod_chord_bytes, chord_bytes);
  }
}

void Chord::restoreMod(conf::mod_enum modifier){
  if(mods[modifier]){
    mods[modifier] = 0;
    setMask(conf::getModChord(mode, modifier), chord_bytes);
  }
}


/********** Anagram manipulation ***********/

uint8_t Chord::getAnagramNum(){
  // get only the anagram-relevant bits
  uint8_t anagram_bytes[NUM_BYTES_IN_CHORD] = {0};
  memcpy(anagram_bytes, chord_bytes, NUM_BYTES_IN_CHORD);
  andMask(conf::getAnagramMask(mode), anagram_bytes);

  // check which anagram modifier matches
  for (uint8_t i = 0; i < NUM_ANAGRAMS; i++) {
    if (isEqual(conf::getAnagram(mode, i),
                anagram_bytes)){
      return i;
    }
  }
  // This will happen normally sometimes, like when you press a chord that
  // contains one of the bits included in a multi-bit anagram modifier.
  DEBUG1_LN("WARNING: Maybe unknown anagram modifier");
  return 0;
}

void Chord::unsetAnagram(uint8_t num){
  if (num > NUM_ANAGRAMS) {
    DEBUG1_LN("WARNING: Failed to unset anagram modifiers");
    return;
  }
  unsetMask(conf::getAnagram(mode, num), chord_bytes);
}

void Chord::setAnagram(uint8_t num){
  if (num > NUM_ANAGRAMS) {
    DEBUG1_LN("WARNING: Failed to set anagram modifiers");
    return;
  }
  setMask(conf::getAnagram(mode, num), chord_bytes);
}

uint8_t Chord::cycleAnagramModifier(){
  uint8_t current_num = getAnagramNum();
  uint8_t next_num = (current_num + 1) % NUM_ANAGRAMS;
  unsetAnagram(current_num);
  setAnagram(next_num);
  return next_num;
}

/************* Chord int array operations ********/

void Chord::setMask(const uint8_t* mask, uint8_t* _chord_bytes) const{
  for (uint8_t byte = 0; byte < NUM_BYTES_IN_CHORD; byte++){
    _chord_bytes[byte] |= mask[byte];
  }
}

void Chord::unsetMask(const uint8_t* mask, uint8_t* _chord_bytes) const{
  for (uint8_t byte = 0; byte < NUM_BYTES_IN_CHORD; byte++){
    _chord_bytes[byte] &= ~mask[byte];
  }
}

void Chord::andMask(const uint8_t* mask, uint8_t* _chord_bytes) const{
  for (uint8_t byte = 0; byte < NUM_BYTES_IN_CHORD; byte++){
    _chord_bytes[byte] &= mask[byte];
  }
}

bool Chord::isByteMaskSet(const uint8_t mask, const uint8_t byte) const{
  return mask == (byte & mask);
}

bool Chord::isChordMaskSet(const uint8_t* mask, const uint8_t* _chord_bytes) const{
  bool return_val = 1;
  for (uint8_t byte_num = 0; byte_num < NUM_BYTES_IN_CHORD; byte_num++){
    return_val &= isByteMaskSet(mask[byte_num], _chord_bytes[byte_num]);
  }
  return return_val;
}

uint8_t Chord::countBitsSet(const uint8_t* _chord_bytes) const{
  uint8_t count = 0;
  for (uint8_t byte = 0; byte < NUM_BYTES_IN_CHORD; byte++){
    for (uint8_t bit = 0; bit < 8; bit++){
      count += (_chord_bytes[byte] >> bit) % 2 ;
    }
  }
  return count;
}

bool Chord::isEqual(const uint8_t* chord1, const uint8_t* chord2) const{
  for (uint8_t k = 0; k != NUM_BYTES_IN_CHORD; k++) {
    if (chord1[k] != chord2[k]) {
      return 0;
    }
  }
  return 1;
}

///// debug

void Chord::printMod(){
  for (uint8_t i = 0; i < NUM_MODIFIERS; i++) {
    Serial.print(mods[i]);
    Serial.print(" ");
  }
  Serial.println();
}
