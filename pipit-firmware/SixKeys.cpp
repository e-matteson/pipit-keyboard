#include "SixKeys.h"


SixKeys::SixKeys(){
  clear();
}

void SixKeys::add(const Key* key){
  // We can always add to the mod_byte, but we can only fit 6 key_codes
  addMod(key->mod_byte);
  if(key->key_code == 0){
    return;
  }
  if(isFull()){
    DEBUG1_LN("WARNING: SixKeys is full");
    return;
  }
  key_codes[num_keys] = key->key_code;
  num_keys++;
}

void SixKeys::addMod(uint8_t _mod_byte){
  mod_byte = mod_byte | _mod_byte;
}

uint8_t SixKeys::get(uint8_t index) const{
  if(index >= 6){
    DEBUG1_LN("WARNING: SixKeys index out of range");
  }
  return key_codes[index];
}

uint8_t SixKeys::getMod() const{
  return mod_byte;
}

bool SixKeys::isFull() const{
  return num_keys >= 6;
}

uint8_t SixKeys::numKeys() const{
  return num_keys;
}

bool SixKeys::isEmpty() const{
  if(mod_byte != 0){
    return false;
  }
  for(uint8_t i = 0; i < 6; i++) {
    if(key_codes[i] != 0){
      return false;
    }
  }
  return true;
}

bool SixKeys::needsExtraRelease(const SixKeys* next) const{
  // Check whether we need to send an extra report between these two, to
  // explicitly release all keys. Usually we don't bother, because if the old
  // key is not included in the new report, it will be released. But if we send
  // the same key twice in a row, without an explicit release in between, the
  // host will think it was pressed once and held. This only matters in
  // words/macros, because you already release the switch when double-tapping it
  // manually.
  if (is_gaming && next->is_gaming) {
    // Plain keys in gaming mode are an exception. You want to be able to press
    // and hold changing sets of keys with sending a release when you add a new
    // one.
    return false;
  }

  if (mod_byte && (mod_byte == next->mod_byte)) {
    return true;
  }

  for(uint8_t i = 0; i < 6; i++) {
    if(key_codes[i] && (key_codes[i] == next->key_codes[i])) {
      return true;
    }
  }

  return false;
}

void SixKeys::copy(const SixKeys* other){
  for(uint8_t i = 0; i < 6; i++) {
    key_codes[i] = other->key_codes[i];
  }
  mod_byte = other->mod_byte;
  is_gaming = other->is_gaming;
}

void SixKeys::clear(){
  for(uint8_t i = 0; i < 6; i++) {
    key_codes[i] = 0;
  }
  mod_byte = 0;
  num_keys = 0;
}

// TODO are debug macros broken?
void SixKeys::printDebug() const{
  DEBUG1("sending keys: ");
  for(uint8_t i = 0; i < 6; i++){
    DEBUG1(key_codes[i]);
    DEBUG1(" ");
  }
  DEBUG1(", mod: ");
  DEBUG1_LN(mod_byte);
}
