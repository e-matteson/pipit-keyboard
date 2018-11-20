#include "Key.h"
#include "auto_config.h"
#include <Arduino.h>

Key::Key(uint8_t _key_code, uint8_t _mod_byte)
    : key_code(_key_code), mod_byte(_mod_byte) {}

void Key::setKey(uint8_t _key_code) { key_code = _key_code; }

void Key::setShift(bool is_upper) {
  if (is_upper) {
    addMod(MODIFIERKEY_SHIFT & 0xff);
  } else {
    removeMod(MODIFIERKEY_SHIFT & 0xff);
  }
}

bool Key::containsShift() const {
  return mod_byte & (MODIFIERKEY_SHIFT & 0xff);
}

void Key::addMod(uint8_t new_mod_byte) { mod_byte |= new_mod_byte; }

void Key::removeMod(uint8_t new_mod_byte) { mod_byte &= !new_mod_byte; }
