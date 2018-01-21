#include "Key.h"

Key::Key(){
}

Key::Key(uint8_t _key_code, uint8_t _mod_byte){
  set(_key_code,  _mod_byte);
}

void Key::setKey(uint8_t _key_code){
  key_code = _key_code;
}

void Key::set(uint8_t _key_code, uint8_t _mod_byte){
  key_code = _key_code;
  mod_byte = _mod_byte;
}

void Key::addMod(uint8_t new_mod_byte){
  mod_byte |= new_mod_byte;
}

void Key::copy(const Key* other){
  set(other->key_code, other->mod_byte);
}

void Key::clear(){
  set(0,0);
}

void Key::print(){
  Serial.print("key: ");
  Serial.print(key_code);
  Serial.print(", ");
  Serial.println(mod_byte);
}
