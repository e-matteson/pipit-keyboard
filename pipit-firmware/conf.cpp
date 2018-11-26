/*
 * Convenient methods for accessing data in auto_config.cpp
 */

#include "conf.h"
#include <Arduino.h>

const HuffmanChar* decodeHuffman(BitSlice<uint8_t>& seq_bits) {
  for (const HuffmanChar& entry : conf::huffman_lookup) {
    if (seq_bits.has_prefix(entry.code_bits())) {
      // Success!
      seq_bits.skip(entry.num_bits);
      return &entry;
    }
  }
  return nullptr;  // Fail!
}

/// Return the number of keys in the decoded sequence, or zero if decoding
/// failed.
uint8_t decodeSequence(BitSlice<uint8_t> seq_bits, Key* keys_out) {
  uint32_t key_index = 0;
  while (seq_bits.size() != 0) {
    const HuffmanChar* entry = decodeHuffman(seq_bits);
    if (entry == nullptr) {
      DEBUG1("ERROR: failed to decode item ");
      DEBUG1(key_index);
      DEBUG1_LN(" in sequence");
      return 0;  // Fail
    }

    if (entry->is_mod) {
      // Add a mod, and wait for more keys/mods to be added to this keypress in
      // the next iteration.
      keys_out[key_index].addMod(entry->key_code);
    } else {
      // Add a key and move on to the next keypress
      keys_out[key_index].setKey(entry->key_code);
      key_index++;
    }
  }
  return key_index;  // Success
}

namespace conf {

uint8_t lookup(const Chord* chord, SeqType type, Key* keys_out) {
  const ModeStruct* mode = conf::getModeStruct(chord->getModeName());
  BitSlice<uint8_t> seq_bits = mode->find(chord, type);
  if (!seq_bits.is_null()) {
    // Success!
    return decodeSequence(seq_bits, keys_out);
  }
  return 0;  // Fail!
}

const ModeStruct* getModeStruct(Mode mode) {
  return mode_structs[to_index(mode)];
}

bool isGaming(Mode mode) { return getModeStruct(mode)->is_gaming; }

const ChordData* getAnagramMask(Mode mode) {
  return &getModeStruct(mode)->anagram_mask;
}

const ChordData* getModChord(Mode mode, Mod modifier) {
  return &(getModeStruct(mode)->mod_chords[to_index(modifier)]);
}

ModType getModType(Mod modifier) {
  for (Mod m : plain_mods) {
    if (m == modifier) {
      return ModType::Plain;
    }
  }
  for (Mod m : word_mods) {
    if (m == modifier) {
      return ModType::Word;
    }
  }
  for (Mod m : anagram_mods) {
    if (m == modifier) {
      return ModType::Anagram;
    }
  }
  DEBUG1_LN("ERROR: Unknown modifier type");
  exit(1);
}

/// If this anagram number has a corresponding anagram number, return a pointer
/// to it. Otherwise, return a nullptr.
// TODO the pointer is slower than returning the small type directly. But how to
// express failure?
const Mod* anagramNumToMod(uint8_t anagram_num) {
  for (uint8_t i = 0; i < anagram_mod_numbers.size(); i++) {
    if (anagram_mod_numbers[i] == anagram_num) {
      return &anagram_mods[i];
    }
  }
  return nullptr;
}

void red() {
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
}

void green() {
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  digitalWrite(12, 0);
}

void blue() {
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  digitalWrite(12, 1);
}

void white() {
  digitalWrite(10, 1);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
}

void purple() {
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  digitalWrite(12, 1);
}

void black() {
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
}

void cyan() {
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
}

void redgreen() {
  static uint8_t toggle = 0;
  switch (toggle) {
    case 0:
      red();
      break;
    case 1:
      green();
      break;
  }
  toggle = (toggle + 1) % 2;
}

void redgreenblue() {
  static uint8_t toggle = 0;
  switch (toggle) {
    case 0:
      red();
      break;
    case 1:
      green();
      break;
    case 2:
      blue();
      break;
  }
  toggle = (toggle + 1) % 3;
}

int readPinMode(uint8_t pin) {
  if (pin >= NUM_DIGITAL_PINS) return (-1);

  auto bit = digitalPinToBitMask(pin);
  auto port = digitalPinToPort(pin);
  volatile uint32_t* reg = portModeRegister(port);
  if (*reg & bit) return (OUTPUT);

  volatile uint32_t* out = portOutputRegister(port);
  return ((*out & bit) ? INPUT_PULLUP : INPUT);
}
}  // namespace conf
