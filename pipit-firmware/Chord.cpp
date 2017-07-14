#include "Chord.h"

Chord::Chord(conf::mode_enum mode) : mode(mode){
}

Chord::Chord(){
}


void Chord::setChordArray(const uint8_t* new_chord_bytes){
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = new_chord_bytes[i];
  }
}

void Chord::setMode(conf::mode_enum _mode){
  mode = _mode;
}

bool Chord::isEmpty() const{
  // Doesn't check the mods, just the current chord bytes.
  // This is important because sendIfEmpty should send mods.
  // TODO abort after 1st set bit?
  return !any(chord_bytes);
}

uint8_t Chord::getModByte() const{
  // Get the byte containing ctrl, shift, alt, and/or gui.
  // Used for HID keyboard protocol.
  uint8_t mod_byte = 0;
  for(uint8_t i = 0; i < NUM_PLAIN_MODS; i++){
    conf::mod_enum mod = conf::getPlainModEnum(i);
    mod_byte |= hasMod(mod) ? conf::getPlainModByte(i) : 0;
  }
  return mod_byte;
}

conf::mode_enum Chord::getMode() const{
  return mode;
}

bool Chord::matches(const uint8_t* lookup_chord_bytes, uint8_t anagram) const{
  // Use this for checking whether a lookup table entry matches this chord.
  return isEqual(chord_bytes, lookup_chord_bytes) && (anagram_num == anagram);
}

void Chord::copy(const Chord* other){
  mode = other->mode;
  for(int i = 0; i < NUM_MODIFIERS; i++){
    mods[i] = other->mods[i];
  }
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = other->chord_bytes[i];
  }
  anagram_num = other->anagram_num;
}

void Chord::clear(){
  mode = (conf::mode_enum) 0;
  for(uint8_t i = 0; i < NUM_MODIFIERS; i++){
    mods[i] = 0;
  }
  for(uint8_t i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = 0;
  }
  anagram_num = 0;
}

bool Chord::hasModCapital() const{
  return hasMod(conf::getCapitalEnum());
}

bool Chord::hasModNospace() const{
  return hasMod(conf::getNospaceEnum());
}

bool Chord::hasMod(conf::mod_enum mod) const{
  return mods[mod];
}

void Chord::extractPlainMods(){
  for(uint8_t i = 0; i < NUM_PLAIN_MODS; i++){
    extractMod(conf::getPlainModEnum(i));
  }
}

void Chord::extractWordMods(){
  for(uint8_t i = 0; i < NUM_WORD_MODS; i++){
    extractMod(conf::getWordModEnum(i));
  }
}


void Chord::extractAnagramMods(){
  // TODO how does blank anagram0 work? Other blank mods are ignored...
  // Switch to null?
  if(!isAnagramMaskBlank()){
    // At least one switch in an anagram is pressed, check to see if it's an
    //  actual mod chord.
    for(uint8_t i = 0; i < NUM_ANAGRAM_MODS; i++){
      if(extractMod(conf::getAnagramModEnum(i))){
        // Found mod!
        anagram_num = i+1; // 0 is reserved for no mod
        return;
      };
    }
  }
  // No valid anagram mod pressed
  anagram_num = 0;
}

void Chord::restoreAnagramMods(){
  if(doesAnagramHaveMod(anagram_num)){
    restoreMod(conf::getAnagramModEnum(anagram_num-1));
  }
  anagram_num = 0;
}

void Chord::restoreWordMods(){
  for(uint8_t i = 0; i < NUM_WORD_MODS; i++){
    restoreMod(conf::getWordModEnum(i));
  }
}

bool Chord::extractMod(conf::mod_enum modifier){
  // If mod is pressed in the chord:
  // - remove the mod bits from the chord
  // - set a flag saying it's present
  // - return true
  const uint8_t* mod_chord_bytes = conf::getModChord(mode, modifier);
  if(!any(mod_chord_bytes)){
    // Mod is all zeroes - that's how we represent a missing mod chord. Ignore.
    return false;
  }
  bool isPressed = false;
  switch(conf::getModType(modifier)){
  case conf::PLAIN_MOD:
  case conf::WORD_MOD:
    isPressed = isChordMaskSet(mod_chord_bytes, chord_bytes);
    break;
  case conf::ANAGRAM_MOD:
    isPressed = isExactAnagramPressed(mod_chord_bytes, chord_bytes);
  }
  if(!isPressed){
    // Mod is not pressed
    return false;
  }

  // Mod is pressed
  mods[modifier] = 1;
  unsetMask(mod_chord_bytes, chord_bytes);
  return true;
}

bool Chord::restoreMod(conf::mod_enum modifier){
  // If mod flag is set:
  // - add the mod bits to the chord
  // - unset the flag
  // - return true
  bool was_set = mods[modifier];
  if(was_set){
    mods[modifier] = 0;
    setMask(conf::getModChord(mode, modifier), chord_bytes);
  }
  return was_set;
}


/********** Anagram manipulation ***********/

bool Chord::isAnagramMaskBlank(){
  uint8_t anagram_bytes[NUM_BYTES_IN_CHORD] = {0};
  memcpy(anagram_bytes, chord_bytes, NUM_BYTES_IN_CHORD);
  andMask(conf::getAnagramMask(mode), anagram_bytes);
  return !any(anagram_bytes);
}

bool Chord::isExactAnagramPressed(const uint8_t* mod_chord,
                                  const uint8_t* _chord)
{
  // TODO inefficient! recomputes mask for every ana mod
  uint8_t anagram_bytes[NUM_BYTES_IN_CHORD] = {0};
  memcpy(anagram_bytes, _chord, NUM_BYTES_IN_CHORD);
  andMask(conf::getAnagramMask(mode), anagram_bytes);
  return isEqual(mod_chord, anagram_bytes);
}

uint8_t Chord::getAnagramNum(){
  return anagram_num;
}

bool Chord::doesAnagramHaveMod(uint8_t anagram_num){
  return (anagram_num >= 1) && (anagram_num <= NUM_ANAGRAM_MODS);
}

void Chord::setAnagramModBit(uint8_t anagram_num, bool value){
  if(!doesAnagramHaveMod(anagram_num)){
    return;
  }
  mods[conf::getAnagramModEnum(anagram_num-1)] = value;
}

uint8_t Chord::cycleAnagramModifier(){
  // Unset old mod flag
  setAnagramModBit(anagram_num, 0);
  anagram_num = (anagram_num + 1) % NUM_ANAGRAMS;
  // Set new mod flag
  setAnagramModBit(anagram_num, 1);
  return anagram_num;
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

bool Chord::any(const uint8_t* _chord_bytes) const{
  for (uint8_t byte = 0; byte < NUM_BYTES_IN_CHORD; byte++){
    for (uint8_t bit = 0; bit < 8; bit++){
      if((_chord_bytes[byte] >> bit) % 2){
        return 1;
      }
    }
  }
  return 0;
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

void Chord::printMod() const{
  for (uint8_t i = 0; i < NUM_MODIFIERS; i++) {
    Serial.print(mods[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void Chord::printChord(const uint8_t* c) const{
  for (uint8_t i = 0; i < NUM_BYTES_IN_CHORD; i++) {
    Serial.print(c[i]);
    Serial.print(", ");
  }
  Serial.println();
}

void Chord::printDebug() const{
  Serial.print("chord: ");
  printChord(chord_bytes);
  Serial.print("mod: ");
  printMod();
  Serial.println();
}
