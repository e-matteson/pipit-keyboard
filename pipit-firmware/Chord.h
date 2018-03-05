#ifndef CHORD_H_
#define CHORD_H_

#include <Arduino.h>
#include "auto_config.h"
#include "keycodes.h"
#include "conf.h"
#include "Key.h"

enum CapBehaviorEnum {
  CAP_DEFAULT,
  CAP_FIRST,
  CAP_NONE,
};

class Chord{
public:
  Chord();
  Chord(conf::mode_enum mode);
  void clear();
  void setChordArray(const uint8_t* chord_bytes);
  void copy(const Chord* chord);
  void setMode(conf::mode_enum _mode);
  void extractPlainMods();
  void extractWordMods();
  void extractAnagramMods();
  void restoreWordMods();
  void restoreAnagramMods();
  uint8_t getAnagramNum();
  uint8_t cycleAnagram();
  void cycleCapital();

  bool matches(const uint8_t* lookup_chord_bytes, uint8_t anagram) const;
  bool isEmpty() const;
  uint8_t getModByte() const;
  conf::mode_enum getMode() const;

  bool hasMod(conf::mod_enum mod) const;
  void editCaps( Key* data, uint8_t length) const;
  bool hasModNospace() const;
  bool hasModDouble() const;
  bool hasModShorten() const;
  void setModNospace();

  void printDebug() const;

private:
  bool isEqual(const uint8_t* chord1, const uint8_t* chord2) const;

  void setMod(conf::mod_enum mod);
  void unsetMod(conf::mod_enum mod);
  bool toggleMod(conf::mod_enum modifier);
  bool extractMod(conf::mod_enum modifier);
  bool restoreMod(conf::mod_enum modifier);

  CapBehaviorEnum decideCapBehavior(const Key* data, uint8_t length) const;
  void prepareToCycle();

  void setAnagramModFlag(uint8_t anagram_num, bool value);
  bool doesAnagramHaveMod(uint8_t anagram_num);
  bool isAnagramMaskBlank();
  bool isExactAnagramPressed(const uint8_t* mod_chord,
                             const uint8_t* _chord);

  void setMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void unsetMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  void andMask(const uint8_t* mask, uint8_t* _chord_bytes) const;
  bool isByteMaskSet(const uint8_t mask, const uint8_t byte) const;
  bool isChordMaskSet(const uint8_t* mask, const uint8_t* _chord_bytes) const;
  bool allZeroes(const uint8_t* _chord_bytes) const;

  void printChord(const uint8_t* c) const;
  void printMod() const;

  uint8_t chord_bytes[NUM_BYTES_IN_CHORD] = {0};
  bool mods[NUM_MODIFIERS] = {0};
  uint8_t anagram_num = 0;
  conf::mode_enum mode = (conf::mode_enum) 0;
  bool flag_cycle_capital = 0;
};

#endif
