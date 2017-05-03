#ifndef CHORD_H_
#define CHORD_H_

#include <Arduino.h>
#include "auto_config.h"
#include "keycodes.h"

class Chord{
public:
  Chord(mode_enum mode);
  // void clear();
  void setChordArray(const uint8_t* chord_bytes);
  void copy(const Chord* chord);
  void copyWordmod(const Chord* chord);

  // TODO s/blank/extract/
  void blankCtrl();
  void blankAlt();
  void blankShift();
  void blankGUI();
  void blankWordmods();
  void restoreWordmods();
  uint8_t getAnagramNum();
  uint8_t cycleAnagramModifier();
  bool matches(const uint8_t* lookup_chord_bytes) const;
  bool isEmpty() const;
  uint8_t getModByte() const;
  mode_enum getMode() const;
  bool hasCapitalWordmod() const;
  bool hasNospaceWordmod() const;

  void printChord();
  void printWordmod();

private:
  bool isEqual(const uint8_t* chord1, const uint8_t* chord2) const;

  void setWordmod(const uint8_t* new_wordmod_storage);
  void blankModifier(uint32_t modifier);
  void blankWordmod(const uint8_t* wordmod_chord_bytes);

  void unsetAnagram(uint8_t num);
  void setAnagram(uint8_t num);

  void setMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void unsetMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void andMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  bool areMaskBitsSet(const uint8_t* mask, const uint8_t* _chord_bytes) const;
  uint8_t countBitsSet(const uint8_t* _chord_bytes) const;

  void printBytes(const uint8_t* bytes) const;

  uint8_t chord_bytes[NUM_BYTES_IN_CHORD] = {0};
  uint8_t mod_byte = 0;
  // bool has_capital_wordmod;
  // bool has_nospace_wordmod;
  mode_enum mode;
  uint8_t wordmod_storage[NUM_BYTES_IN_CHORD] = {0};
};

#endif
