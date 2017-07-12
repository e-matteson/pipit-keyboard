#ifndef KEY_H_
#define KEY_H_

#include "Arduino.h"
#include "auto_config.h"


class Key {
public:
  Key();
  Key(uint8_t _key_code, uint8_t _mod_byte);
  void set(uint8_t _key_code, uint8_t _mod_byte);
  void addMod(uint8_t new_mod_byte);
  void copy(const Key* other);
  void clear();

  uint8_t key_code = 0;
  uint8_t mod_byte = 0;
};

#endif
