#ifndef CHORD_H_
#define CHORD_H_

#include <Arduino.h>
#include "auto_config.h"
#include "keycodes.h"

class Chord{
public:
  Chord();
  void clear();
  void setChordArray(const uint8_t* chord_bytes);
  void copy(const Chord* chord);
  void copyWordmod(const Chord* chord);

  // TODO s/blank/extract/
  void blankCtrl();
  void blankAlt();
  void blankShift();
  void blankGUI();
  void blankWordmodCapital();
  void blankWordmodNospace();
  void restoreWordmods();
  void cycleAnagramModifier();

  bool isEqual(const uint8_t* other_chord_bytes) const;
  // bool isEqual(const uint8_t* other_chord_bytes);
  bool isEmpty() const;
  uint8_t getModByte() const;
  bool hasCapitalWordmod() const;
  bool hasNospaceWordmod() const;

  void printChord();
  void printWordmod();

private:
  void setWordmod(const uint8_t* new_wordmod_storage);
  void blankModifier(uint32_t modifier);
  void blankWordmod(const uint8_t* wordmod_chord_bytes);

  void setMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void unsetMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void andMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  bool areMaskBitsSet(const uint8_t* mask, const uint8_t* _chord_bytes) const;
  uint8_t countBitsSet(const uint8_t* _chord_bytes) const;

  void printBytes(const uint8_t* bytes) const;

  uint8_t chord_bytes[NUM_BYTES_IN_CHORD] = {0};
  uint8_t wordmod_storage[NUM_BYTES_IN_CHORD] = {0};
  uint8_t mod_byte = 0;
};

#endif
