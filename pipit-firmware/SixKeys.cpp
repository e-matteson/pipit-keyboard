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
};

bool SixKeys::isEqual(const SixKeys* other) const{
  if(mod_byte != other->mod_byte){
    return false;
  }
  for(uint8_t i = 0; i < 6; i++) {
    if(key_codes[i] != other->key_codes[i]){
      return false;
    }
  }
  return true;
}

void SixKeys::copy(const SixKeys* other){
  for(uint8_t i = 0; i < 6; i++) {
    key_codes[i] = other->key_codes[i];
  }
  mod_byte = other->mod_byte;
}

void SixKeys::clear(){
  for(uint8_t i = 0; i < 6; i++) {
    key_codes[i] = 0;
  }
  mod_byte = 0;
  num_keys = 0;
}

void SixKeys::printDebug() const{
  DEBUG1("sending keys: ");
  for(uint8_t i = 0; i < 6; i++){
    DEBUG1(key_codes[i]);
    DEBUG1(" ");
  }
  DEBUG1(", mod: ");
  DEBUG1_LN(mod_byte);
}
