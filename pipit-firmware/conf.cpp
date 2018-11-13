/*
 * Convenient methods for accessing data in auto_config.cpp
 */

#include "conf.h"
#include <Arduino.h>

namespace conf {

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

}  // namespace conf
