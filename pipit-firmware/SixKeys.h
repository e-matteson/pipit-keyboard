#ifndef SIXKEYS_H_
#define SIXKEYS_H_

#include "Arduino.h"
#include "Key.h"
#include "auto_config.h"

class SixKeys {
public:
  SixKeys();
  void add(const Key* key);
  void addMod(uint8_t _mod_byte);
  void clear();
  bool isEmpty() const;
  bool isFull() const;
  bool needsExtraRelease(const SixKeys* next) const;
  void copy(const SixKeys* other);
  uint8_t get(uint8_t index) const;
  uint8_t getMod() const;
  uint8_t numKeys() const;

  void printDebug() const;

private:
  uint8_t key_codes[6];
  uint8_t mod_byte;
  uint8_t num_keys = 0;
  bool is_gaming = 0;
};

#endif
