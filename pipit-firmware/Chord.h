#pragma once

#include <stdint.h>
#include "BitArray.h"
#include "Key.h"
#include "auto_config.h"
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
  const ChordData* getData() const;
  ChordData* getDataMut();
  bool isEmptyExceptMods() const;
  uint8_t getModByte() const;
  conf::Mode getModeName() const;

  bool hasMod(conf::Mod mod) const;
  void editCaps(Key* keys, uint8_t length) const;
  bool hasModNospace() const;
  bool hasModDouble() const;
  bool hasModShorten() const;
  void setModNospace();

 private:
  struct Flags {
    // The least significants bits will each represent one modifier, and the
    // most significant bit will store the flag_cycle_capital. It's important to
    // keep Chords as small as possible, since we create a bunch of them
    // (especially in the history).
    BitArray<uint16_t, NUM_MODIFIERS + 1> bits;

    bool hasMod(conf::Mod mod) const;
    void setMod(conf::Mod mod);
    void unsetMod(conf::Mod mod);
    void toggleMod(conf::Mod mod);
    bool getFlagCycleCapital() const;
    void toggleFlagCycleCapital();
    constexpr size_t cycleCapitalOffset() const;
  };

  enum CapBehaviorEnum {
    CAP_DEFAULT,
    CAP_FIRST,
    CAP_NONE,
  };

  bool extractMod(conf::Mod modifier);
  bool restoreMod(conf::Mod modifier);

  uint8_t cycleAnagram();
  void cycleCapital();
  void cycleNospace();
  uint8_t getAnagramNum();
  CapBehaviorEnum decideCapBehavior(const Key* keys, uint8_t length) const;
  void prepareToCycle();

  void setAnagramModFlag(uint8_t anagram_num, bool value);
  bool isAnagramMaskBlank();
  bool isExactAnagramPressed(const ChordData* mod_chord);

  Flags flags;

  uint8_t anagram_num = 0;

  ChordData chord_data;

  // TODO what happens if there are no modes, so no variant with value 0, and
  // this cast is invalid?
  conf::Mode mode = static_cast<conf::Mode>(0);
};
