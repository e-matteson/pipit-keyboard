#ifndef CHORD_H_
#define CHORD_H_

#include <Arduino.h>
#include "auto_config.h"
#include "keycodes.h"
#include "conf.h"

class Chord{
public:
  Chord();
  Chord(conf::mode_enum mode);
  void clear();
  void setChordArray(const uint8_t* chord_bytes);
  void copy(const Chord* chord);

  void blankMods();
  void blankWordmods();
  void restoreWordmods();
  uint8_t getAnagramNum();
  uint8_t cycleAnagramModifier();

  bool matches(const uint8_t* lookup_chord_bytes) const;
  bool isEmpty() const;
  uint8_t getModByte() const;
  conf::mode_enum getMode() const;

  bool hasMod(conf::mod_enum mod) const;
  bool hasCapitalWordmod() const;
  bool hasNospaceWordmod() const;

  void printMod();

private:
  bool isEqual(const uint8_t* chord1, const uint8_t* chord2) const;

  void blankWordmod(const uint8_t* wordmod_chord_bytes);
  void blankMod(uint32_t mod_name, const uint8_t* mod_chord_bytes);
  void blankMod(conf::mod_enum modifier);
  void restoreMod(conf::mod_enum modifier);

  void unsetAnagram(uint8_t num);
  void setAnagram(uint8_t num);

  void setMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void unsetMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void andMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  bool isByteMaskSet(const uint8_t mask, const uint8_t byte) const;
  bool isChordMaskSet(const uint8_t* mask, const uint8_t* _chord_bytes) const;
  uint8_t countBitsSet(const uint8_t* _chord_bytes) const;

  void printBytes(const uint8_t* bytes) const;

  uint8_t chord_bytes[NUM_BYTES_IN_CHORD] = {0};
  bool mods[NUM_MODIFIERS] = {0};
  conf::mode_enum mode;
  // uint8_t mod_byte = 0;
  // uint8_t wordmod_storage[NUM_BYTES_IN_CHORD] = {0};
  // bool has_capital_wordmod;
  // bool has_nospace_wordmod;
};

#endif
