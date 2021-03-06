#pragma once

#include <stdint.h>

#include "Key.h"
#include "auto_config.h"

class Report {
 public:
  void addKey(const Key* key);
  void addMod(uint8_t _mod_byte);
  bool isEmpty() const;
  bool isFull() const;
  bool needsExtraRelease(const Report* next) const;
  void copyModsFrom(const Report* other);
  uint8_t get(uint8_t index) const;
  uint8_t getMod() const;
  uint8_t numKeys() const;

  void printDebug() const;

  bool is_gaming = 0;

 private:
  static const uint8_t report_length = 6;  // Standard length of USB HID report
  uint8_t key_codes[report_length] = {0};
  uint8_t mod_byte = 0;
  uint8_t num_keys = 0;
};
