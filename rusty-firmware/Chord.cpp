#include "Chord.h"

Chord::Chord(mode_enum mode) : mode(mode){
}


// void Chord::clear(){
//   mod_byte = 0;
//   for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
//     chord_bytes[i] = 0;
//     wordmod_storage[i] = 0;
//   }
// }

void Chord::setChordArray(const uint8_t* new_chord_bytes){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = new_chord_bytes[i];
  }
}

void setAnagram(const uint8_t anagram_number){
  // TODO check if num is in valid range?
  self.anagram_number = anagram_number;
}

void Chord::setWordmod(const uint8_t* new_wordmod_storage){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    wordmod_storage[i] = new_wordmod_storage[i];
  }
}

bool Chord::isEmpty() const{
  // TODO should you be allowed to use a blank chord with a non-zero anagram?
  // return !countBitsSet(chord_bytes);
  return !countBitsSet(chord_bytes) && anagram_number == 0;
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
  anagram_number = chord->anagram_number;
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = chord->chord_bytes[i];
    wordmod_storage[i] = chord->wordmod_storage[i];
  }
}

void Chord::copyWordmod(const Chord* chord){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    wordmod_storage[i] = chord->wordmod_storage[i];
  }
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

void Chord::blankWordmodAnagrams(){
  self.anagram_number =
}

void Chord::blankWordmodCapital(){
  blankWordmod(wordmod_capital_chord_bytes[mode]);
}

void Chord::blankWordmodNospace(){
  blankWordmod(wordmod_nospace_chord_bytes[mode]);
}

void Chord::blankWordmod(const uint8_t* wordmod_chord_bytes){
  // Store the bit(s) of wordmod that are set in the current chord.
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

uint8_t Chord::calculateAnagramNumber(){

  // get only the anagram-relevant bits
  uint8_t anagram_bytes[NUM_BYTES_IN_CHORD] = {0};
  memcpy(anagram_bytes, chord_bytes, NUM_BYTES_IN_CHORD);
  andMask(wordmod_all_anagram_chord_bytes, anagram_bytes);

  // check which anagram wordmod matches
  for (uint8_t i = 0; i < NUM_ANAGRAMS; i++) {
    if (isEqual(wordmod_anagram_chord_bytes[mode][i],
                anagram_bytes)){
      return i;
    }
  }
  // This will happen normally sometimes, like when you press a chord that
  // contains one of the bits included in a multi-bit anagram modifier.
  DEBUG1_LN("WARNING: Maybe unknown anagram modifier");
}

void Chord::cycleAnagramModifier(){

  // Needed in case one anagram modifier chord is a subset of the other
  static const uint8_t length_anagram1 = countBitsSet(wordmod_anagram1_chord_bytes[mode]);
  static const uint8_t length_anagram2 = countBitsSet(wordmod_anagram2_chord_bytes[mode]);

  bool fits_anagram1 = areMaskBitsSet(wordmod_anagram1_chord_bytes[mode], chord_bytes);
  bool fits_anagram2 = areMaskBitsSet(wordmod_anagram2_chord_bytes[mode], chord_bytes);

  if((fits_anagram1 && (!fits_anagram2)) ||
     (fits_anagram1 && fits_anagram2 && (length_anagram1 > length_anagram2))){
    // Anagram1 modifier was pressed! Switch to anagram2.
    unsetMask(wordmod_anagram1_chord_bytes[mode], chord_bytes);
    setMask(wordmod_anagram2_chord_bytes[mode], chord_bytes);
  }
  else if((fits_anagram2 && (!fits_anagram1)) ||
          (fits_anagram1 && fits_anagram2 && (length_anagram2>length_anagram1))){
    // Anagram2 modifier was pressed! Switch to no modifier.
    unsetMask(wordmod_anagram2_chord_bytes[mode], chord_bytes);
  }
  else{
    // No modifier was pressed! Switch to anagram1.
    setMask(wordmod_anagram1_chord_bytes[mode], chord_bytes);
  }
}

bool Chord::matches(const uint8_t* other_chord_bytes, uint8_t other_anagram_num) const{
  if !isEqual(chord_bytes, other_chord_bytes){
      return 0;
  }
  if (self.anagram_number != other_anagram_num) {
    return 0;
  }
  return 1;
}

bool Chord::isEqual(const uint8_t* chord1, const uint8_t* chord2) const{
  for (uint8_t k = 0; k != NUM_BYTES_IN_CHORD; k++) {
    if (chord1[k] != chord2[k]) {
      return 0;
    }
  }
  return 1;
}

void Chord::printChord(){
  //for debugging
  // Serial.print("chord: ");
  Serial.print("anagram ");
  Serial.print(self.anagram_number);
  Serial.print(", ");
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
