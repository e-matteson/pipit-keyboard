#pragma once

#include <stdint.h>
#include "auto_config.h"
#include "Key.h"
#include "conf.h"

/// How to modify cycled words
enum class CycleType {
  Anagram,  /// Replace word with the next anagram of the same chord
  Nospace,  /// Toggle whether a space is automatically inserted.
  Capital,  /// Toggle the capitalization of the word.
};

/// The Chord class stores which switches are pressed in a chord. It can check
/// whether the chord contains modifiers, extract modifiers out of the explicit
/// representation to be stored as flags, insert them back into the explicit
/// representation, and edit modifiers when cycling words.
class Chord {
 public:
  Chord() = default;
  Chord(conf::Mode mode);

  void setSwitch(uint8_t switch_index);
  void setMode(conf::Mode _mode);
  void extractPlainMods();
  void extractWordMods();
  void extractAnagramMods();
  void restoreWordMods();
  void restoreAnagramMods();
  void cycle(CycleType operation);

  bool hasAnagramNum(uint8_t other_anagram) const;
  const ChordData* getChordData() const;
  bool isEmptyExceptMods() const;
  uint8_t getModByte() const;
  conf::Mode getMode() const;

  bool hasMod(conf::Mod mod) const;
  void editCaps(Key* data, uint8_t length) const;
  bool hasModNospace() const;
  bool hasModDouble() const;
  bool hasModShorten() const;
  void setModNospace();

  void printDebug() const;

 private:
  enum CapBehaviorEnum {
    CAP_DEFAULT,
    CAP_FIRST,
    CAP_NONE,
  };


  void setMod(conf::Mod mod);
  void unsetMod(conf::Mod mod);
  void toggleMod(conf::Mod modifier);
  bool extractMod(conf::Mod modifier);
  bool restoreMod(conf::Mod modifier);

  uint8_t cycleAnagram();
  void cycleCapital();
  void cycleNospace();
  uint8_t getAnagramNum();
  CapBehaviorEnum decideCapBehavior(const Key* data, uint8_t length) const;
  void prepareToCycle();
  bool getFlagCycleCapital() const;
  void toggleFlagCycleCapital();

  void setAnagramModFlag(uint8_t anagram_num, bool value);
  bool isAnagramMaskBlank();
  bool isExactAnagramPressed(const ChordData* mod_chord);

  void printChord(const ChordData& c) const;
  void printMod() const;

  // Make sure the modifiers will fit in the bits of a uint16_t. The least
  // significants bits will each represent one modifier, and the most
  // significant bit will store the flag_cycle_capital. It's important to keep
  // Chords as small as possible, since we create a bunch of them (especially in
  // the history).
#if NUM_MODIFIERS > 15
#error "Too many modifiers, increase mods storage size in Chord.h"
#endif
  uint16_t mods_and_flags = 0;

  uint8_t anagram_num = 0;

  ChordData chord_bytes = {{0}};

  // TODO what happens if there are no modes, so no variant with value 0, and
  // this cast is invalid?
  conf::Mode mode = static_cast<conf::Mode>(0);
};
