#ifndef KEY_H_
#define KEY_H_

#include "Arduino.h"
#include "auto_config.h"


class Key {
public:
  Key();
  Key(uint8_t _key_code, uint8_t _mod_byte);
  void setKey(uint8_t _key_code);
  void set(uint8_t _key_code, uint8_t _mod_byte);
  void setShift(bool is_upper);
  bool hasShift() const;
  void addMod(uint8_t new_mod_byte);
  void removeMod(uint8_t new_mod_byte);
  void copy(const Key* other);
  void clear();
  void print();

  // As small as it can get...
  uint8_t key_code = 0;
  uint8_t mod_byte = 0;
};

#endif
