#include "Chord.h"

Chord::Chord(mode_enum mode) : mode(mode){
}

Chord::Chord(){
  mode = (mode_enum) 0;
}


void Chord::setChordArray(const uint8_t* new_chord_bytes){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = new_chord_bytes[i];
  }
}

void Chord::setWordmod(const uint8_t* new_wordmod_storage){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    wordmod_storage[i] = new_wordmod_storage[i];
  }
}

bool Chord::isEmpty() const{
  // Doesn't check the modbyte, just the current chord bytes.
  return countBitsSet(chord_bytes) == 0;
}

uint8_t Chord::getModByte() const{
  return mod_byte;
}

mode_enum Chord::getMode() const{
  return mode;
}

void Chord::copy(const Chord* chord){
  mode = chord->mode;
  mod_byte = chord->mod_byte;
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = chord->chord_bytes[i];
    wordmod_storage[i] = chord->wordmod_storage[i];
  }
}

void Chord::clear(){
  mode = (mode_enum) 0;
  mod_byte = 0;
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = 0;
    wordmod_storage[i] = 0;
  }
}

void Chord::copyWordmod(const Chord* chord){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    wordmod_storage[i] = chord->wordmod_storage[i];
  }
}

uint8_t Chord::getAnagramNum(){

  // get only the anagram-relevant bits
  uint8_t anagram_bytes[NUM_BYTES_IN_CHORD] = {0};
  memcpy(anagram_bytes, chord_bytes, NUM_BYTES_IN_CHORD);
  andMask(anagram_mask_chord_bytes[mode], anagram_bytes);

  // check which anagram modifier matches
  for (uint8_t i = 0; i < NUM_ANAGRAMS; i++) {
    if (isEqual(anagram_chord_bytes[mode][i],
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
  }
  unsetMask(anagram_chord_bytes[mode][num], chord_bytes);
}

void Chord::setAnagram(uint8_t num){
  if (num > NUM_ANAGRAMS) {
    DEBUG1_LN("WARNING: Failed to set anagram modifiers");
  }
  setMask(anagram_chord_bytes[mode][num], chord_bytes);
}

uint8_t Chord::cycleAnagramModifier(){
  uint8_t current_num = getAnagramNum();
  uint8_t next_num = (current_num + 1) % NUM_ANAGRAMS;
  unsetAnagram(current_num);
  setAnagram(next_num);
  return next_num;
}

bool Chord::matches(const uint8_t* lookup_chord_bytes) const{
  // Use this for checking whether a lookup table entry matches this chord.
  return isEqual(chord_bytes, lookup_chord_bytes);
}

void Chord::blankCtrl(){
  blankModifier(MODIFIERKEY_CTRL);
}

void Chord::blankAlt(){
  blankModifier(MODIFIERKEY_ALT);
}

void Chord::blankShift(){
  blankModifier(MODIFIERKEY_SHIFT);
}

void Chord::blankGUI(){
  blankModifier(MODIFIERKEY_GUI);
}


void Chord::blankModifier(uint32_t modifier){
  uint8_t position;
  switch(modifier){
  case MODIFIERKEY_SHIFT:
    position = shift_position[mode];
    break;
  case MODIFIERKEY_GUI:
    position = gui_position[mode];
    break;
  case MODIFIERKEY_CTRL:
    position = ctrl_position[mode];
    break;
  case MODIFIERKEY_ALT:
    position = alt_position[mode];
    break;
  default:
    DEBUG1("ERROR: blankModifier: unknown modifier: ");
    DEBUG1_LN(modifier);
    return;
  }

  //If the modifier at the specified switch position is pressed:
  // Set the corresponding bit in mod_byte,
  // and unset the corresponding bit in the chord array.
  if(chord_bytes[position/8] & 1<<position%8){
    mod_byte |= modifier&0xff;
    chord_bytes[position/8] &= ~(1<<position%8);
  }
}

void Chord::blankWordmods(){
  blankWordmod(wordmod_capital_chord_bytes[mode]);
  blankWordmod(wordmod_nospace_chord_bytes[mode]);
}

void Chord::blankWordmod(const uint8_t* wordmod_chord_bytes){
  // Store the bit(s) of wordmod that are set in the current chord.
  // TODO refactor to be more like anagram setting?

  uint8_t tmp[NUM_BYTES_IN_CHORD] = {0};
  memcpy(tmp, chord_bytes, NUM_BYTES_IN_CHORD);
  andMask(wordmod_chord_bytes, tmp);
  setMask(tmp, wordmod_storage);

  // Unset those bits.
  unsetMask(wordmod_chord_bytes, chord_bytes);
}

void Chord::restoreWordmods(){
  setMask(wordmod_storage, chord_bytes);
}

bool Chord::hasCapitalWordmod() const{
  return areMaskBitsSet(wordmod_capital_chord_bytes[mode], wordmod_storage);
}

bool Chord::hasNospaceWordmod() const{
  return areMaskBitsSet(wordmod_nospace_chord_bytes[mode], wordmod_storage);
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

bool Chord::areMaskBitsSet(const uint8_t* mask, const uint8_t* _chord_bytes) const{
  bool return_val = 1;
  for (uint8_t byte = 0; byte < NUM_BYTES_IN_CHORD; byte++){
    return_val &= (mask[byte] == (_chord_bytes[byte] & mask[byte]));
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


/******* Debugging *******/

void Chord::printChord(){
  //for debugging
  // Serial.print("chord: ");
  printBytes(chord_bytes);
}

void Chord::printWordmod(){
  //for debugging
  // Serial.print("wordmod: ");
  printBytes(wordmod_storage);
}

void Chord::printBytes(const uint8_t* bytes) const{
  for(uint8_t byte_num = 0; byte_num != NUM_BYTES_IN_CHORD; byte_num++){
    Serial.print(bytes[byte_num]);
    Serial.print(" ");
  }
  Serial.println("");
}
