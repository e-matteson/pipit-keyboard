#include "Chord.h"
#include "util.h"

#define FLAG_BIT 15


static uint8_t index(conf::Mod modifier){
  return static_cast<uint8_t>(modifier);
}

Chord::Chord(){}

Chord::Chord(conf::Mode mode) : mode(mode){}

void Chord::setSwitch(uint8_t switch_index){
  if(switch_index >= NUM_MATRIX_POSITIONS) {
    DEBUG1_LN("WARNING: invalid chord switch index");
    return;
  }
  uint8_t byte = switch_index / 8;
  uint8_t bit = switch_index % 8;
  chord_bytes[byte] |= (0x01 << bit);
}

void Chord::setMode(conf::Mode _mode){
  mode = _mode;
}

bool Chord::isEmptyExceptMods() const{
  // Doesn't check the mods, just the current chord bytes.
  return allZeroes(chord_bytes);
}

uint8_t Chord::getModByte() const{
  // Get the byte containing ctrl, shift, alt, and/or gui.
  // Used for HID keyboard protocol.
  uint8_t mod_byte = 0;
  for(uint8_t i = 0; i < NUM_PLAIN_MODS; i++){
    conf::Mod mod = conf::getPlainModEnum(i);
    mod_byte |= hasMod(mod) ? conf::getPlainModByte(i) : 0;
  }
  return mod_byte;
}

conf::Mode Chord::getMode() const{
  return mode;
}

bool Chord::hasAnagramNum(uint8_t other_anagram) const{
  return (anagram_num == other_anagram);
}

bool Chord::hasChordBytes(const uint8_t* other_chord_bytes) const{
  return isEqual(chord_bytes, other_chord_bytes);
}

void Chord::copy(const Chord* other){
  mode = other->mode;
  mods_and_flags = other->mods_and_flags;
  for(int i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = other->chord_bytes[i];
  }
  anagram_num = other->anagram_num;
}

void Chord::clear(){
  mode = (conf::Mode) 0;
  mods_and_flags = 0;
  for(uint8_t i = 0; i < NUM_BYTES_IN_CHORD; i++){
    chord_bytes[i] = 0;
  }
  anagram_num = 0;
}

void Chord::editCaps(Key* data, uint8_t length) const {
  switch(decideCapBehavior(data, length)) {
  case CapBehaviorEnum::CAP_DEFAULT:
    break;

  case CapBehaviorEnum::CAP_FIRST:
    data[0].setShift(1);
    break;

  case CapBehaviorEnum::CAP_NONE:
    for(uint8_t i = 0; i<length; i++){
      data[i].setShift(0);
    }
    break;

  default:
    DEBUG1_LN("WARNING: unknown cap behavior");
  }
}

Chord::CapBehaviorEnum Chord::decideCapBehavior(const Key* data, uint8_t length) const {
  bool has_cap_mod = hasMod(conf::getCapitalEnum());

  if(!getFlagCycleCapital()) {
    // The simple case, without cap cycling.
    if(has_cap_mod) {
      return CAP_FIRST;
    }
    return CAP_DEFAULT;
  }

  // The complicated case, where we might force capitalized dictionary words to
  // be lowercase.
  bool has_literal_shift = 0;
  for(uint8_t i = 0; i < length; i++) {
    if(data[i].containsShift()) {
      has_literal_shift = 1;
      break;
    }
  }

  if(has_literal_shift) {
    // If the word already contained capitalization, force it all to lowercase.
    return CAP_NONE;
  }

  // Otherwise, invert the cap mod.
  if(has_cap_mod) {
    return CAP_DEFAULT;
  }
  return CAP_FIRST;
}


bool Chord::hasModNospace() const{
  return hasMod(conf::getNospaceEnum());
}

bool Chord::hasModDouble() const{
  return hasMod(conf::getDoubleEnum());
}

bool Chord::hasModShorten() const{
  return hasMod(conf::getModShortenEnum());
}

void Chord::setModNospace() {
  setMod(conf::getNospaceEnum());
}

bool Chord::hasMod(conf::Mod mod) const{
  return (mods_and_flags >> index(mod)) & 1;
}

void Chord::setMod(conf::Mod mod) {
  mods_and_flags |= (1 << index(mod));
}

void Chord::unsetMod(conf::Mod mod) {
  mods_and_flags &= ~(1 << index(mod));
}

void Chord::toggleMod(conf::Mod mod){
  mods_and_flags ^= (1 << index(mod));
}

bool Chord::getFlagCycleCapital() const {
  return 1 & (mods_and_flags >> FLAG_BIT);
}

void Chord::toggleFlagCycleCapital() {
  mods_and_flags ^= (1 << FLAG_BIT);
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
      }
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

bool Chord::extractMod(conf::Mod modifier){
  // If mod is pressed in the chord:
  // - remove the mod bits from the chord
  // - set a flag saying it's present
  // - return true
  const uint8_t* mod_chord_bytes = conf::getModChord(mode, modifier);
  if(allZeroes(mod_chord_bytes)){
    // Mod is all zeroes - that's how we represent a missing mod chord. Ignore.
    return false;
  }
  bool isPressed = false;
  switch(conf::getModType(modifier)){
  case conf::ModType::Plain:
  case conf::ModType::Word:
    isPressed = isChordMaskSet(mod_chord_bytes, chord_bytes);
    break;
  case conf::ModType::Anagram:
    isPressed = isExactAnagramPressed(mod_chord_bytes, chord_bytes);
  }
  if(!isPressed){
    // Mod is not pressed
    return false;
  }

  // Mod is pressed
  setMod(modifier);
  unsetMask(mod_chord_bytes, chord_bytes);
  return true;
}

bool Chord::restoreMod(conf::Mod modifier){
  // If mod flag is set:
  // - add the mod bits to the chord
  // - unset the flag
  // - return true
  bool was_set = hasMod(modifier);
  if(was_set){
    unsetMod(modifier);
    setMask(conf::getModChord(mode, modifier), chord_bytes);
  }
  return was_set;
}

void Chord::prepareToCycle(){
  // Unset mods that affect the word before this one, like by backspacing or
  // doubling its letters. We don't want to repeat those effects every time we
  // cycle this chord.
  unsetMod(conf::getModShortenEnum());
  unsetMod(conf::getDoubleEnum());
}

void Chord::cycle(CycleType operation){
  switch(operation) {
  case CycleType::Capital:
    cycleCapital();
    break;

  case CycleType::Nospace:
    cycleNospace();
    break;

  case CycleType::Anagram:
    cycleAnagram();
    break;

  default:
    DEBUG1_LN("WARNING: unknown cycle type");
  }
}

void Chord::cycleCapital(){
  prepareToCycle();
  toggleFlagCycleCapital();
}

void Chord::cycleNospace(){
  prepareToCycle();
  toggleMod(conf::getNospaceEnum());
}


/********** Anagram manipulation ***********/

uint8_t Chord::cycleAnagram(){
  prepareToCycle();
  // Unset old mod flag
  setAnagramModFlag(anagram_num, 0);
  anagram_num = (anagram_num + 1) % (MAX_ANAGRAM_NUM + 1);
  // Set new mod flag
  setAnagramModFlag(anagram_num, 1);
  return anagram_num;
}

bool Chord::isAnagramMaskBlank(){
  uint8_t anagram_bytes[NUM_BYTES_IN_CHORD] = {0};
  memcpy(anagram_bytes, chord_bytes, NUM_BYTES_IN_CHORD);
  andMask(conf::getAnagramMask(mode), anagram_bytes);
  return allZeroes(anagram_bytes);
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

void Chord::setAnagramModFlag(uint8_t anagram_num, bool value){
  if(!doesAnagramHaveMod(anagram_num)){
    return;
  }
  // TODO why subtract 1? Can we avoid that...
  conf::Mod mod = conf::getAnagramModEnum(anagram_num-1);

  if (value) {
    setMod(mod);
  }
  else {
    unsetMod(mod);
  }
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

bool Chord::isChordMaskSet(const uint8_t* mask, const uint8_t* _chord_bytes) const{
  bool return_val = 1;
  for (uint8_t byte_num = 0; byte_num < NUM_BYTES_IN_CHORD; byte_num++){
    return_val &= isByteMaskSet(mask[byte_num], _chord_bytes[byte_num]);
  }
  return return_val;
}

bool Chord::allZeroes(const uint8_t* _chord_bytes) const{
  for (uint8_t byte = 0; byte < NUM_BYTES_IN_CHORD; byte++){
    if(_chord_bytes[byte]) {
      return 0;
    }
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

///// debug

void Chord::printMod() const{
  for (uint8_t i = 0; i < NUM_MODIFIERS; i++) {
    Serial.print(hasMod((conf::Mod) i));
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
