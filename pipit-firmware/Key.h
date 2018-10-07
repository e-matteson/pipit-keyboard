#ifndef KEY_H_
#define KEY_H_

#include "Arduino.h"
#include "auto_config.h"


class Key {
public:
  Key() = default;
  Key(uint8_t _key_code, uint8_t _mod_byte);
  void setKey(uint8_t _key_code);
  void setShift(bool is_upper);
  bool containsShift() const;
  void addMod(uint8_t new_mod_byte);
  void removeMod(uint8_t new_mod_byte);

  // As small as it can get...
  uint8_t key_code = 0;
  uint8_t mod_byte = 0;
};

#endif
