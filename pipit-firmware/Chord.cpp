#include "Chord.h"
#include <type_traits>
#include "util.h"
#include <Arduino.h>

#define FLAG_BIT 15

void setMask(const ChordData* mask, ChordData* bytes)  {
  for (uint8_t i = 0; i < mask->size(); i++) {
    (*bytes)[i] |= (*mask)[i];
  }
}

void unsetMask(const ChordData* mask, ChordData* bytes) {
  for (uint8_t i = 0; i < mask->size(); i++) {
    (*bytes)[i] &= ~(*mask)[i];
  }
}

void andMask(const ChordData* mask, ChordData* bytes) {
  for (uint8_t i = 0; i < mask->size(); i++) {
    (*bytes)[i] &= (*mask)[i];
  }
}

constexpr bool isByteMaskSet(const uint8_t mask, const uint8_t byte) {
  return mask == (byte & mask);
}

bool isChordMaskSet(const ChordData* mask, const ChordData* bytes) {
  bool return_val = 1;
  for (uint8_t i = 0; i < mask->size(); i++) {
    return_val &= isByteMaskSet((*mask)[i], (*bytes)[i]);
  }
  return return_val;
}

bool allZeroes(const ChordData* bytes) {
  for(uint8_t byte : *bytes) {
    if(byte) {
      return 0;
    }
  }
  return 1;
}

/// If this anagram number has a corresponding anagram number, return a pointer to it. Otherwise, return a nullptr.
// TODO put this in conf.cpp?
const conf::Mod* getAnagramModFromNumber(uint8_t anagram_num) {
  uint8_t index = 0;
  for (uint8_t num : conf::anagram_mod_numbers) {
    if (num == anagram_num) {
      return conf::anagram_mod_indices + index;
    }
    index++;
  }
  return nullptr;
}

//////////////////////////////////////////////////

Chord::Chord(conf::Mode mode) : mode(mode) {}

void Chord::setSwitch(uint8_t switch_index) {
  // TODO this seems inefficient to call for every index...
  if (switch_index >= NUM_MATRIX_POSITIONS) {
    DEBUG1_LN("WARNING: invalid chord switch index");
    return;
  }
  uint8_t byte = switch_index / 8;
  uint8_t bit = switch_index % 8;
  chord_bytes[byte] |= (0x01 << bit);
}

void Chord::setMode(conf::Mode _mode) { mode = _mode; }

bool Chord::isEmptyExceptMods() const {
  // Doesn't check the mods, just the current chord bytes.
  return allZeroes(&chord_bytes);
}

/// Get the byte containing ctrl, shift, alt, and/or gui.
/// Needed for an HID keyboard report.
uint8_t Chord::getModByte() const {
  uint8_t mod_byte = 0;
  uint8_t index = 0;
  for (conf::Mod mod : conf::plain_mod_indices) {
    if (hasMod(mod)) {
      mod_byte |=  conf::getPlainModByte(index);
    }
    index++;
  }
  return mod_byte;
}

conf::Mode Chord::getMode() const { return mode; }

bool Chord::hasAnagramNum(uint8_t other_anagram) const {
  return (anagram_num == other_anagram);
}

const ChordData* Chord::getChordData() const {
  return &chord_bytes;
}

/// Edit the capitalization of the given Keys, depending on a bunch of factors
/// like what mod flags are set for this Chord, what literal modifiers are
/// included in the Keys, etc.
void Chord::editCaps(Key* data, uint8_t length) const {
  switch (decideCapBehavior(data, length)) {
    case CapBehaviorEnum::CAP_DEFAULT:
      break;

    case CapBehaviorEnum::CAP_FIRST:
      data[0].setShift(1);
      break;

    case CapBehaviorEnum::CAP_NONE:
      for (uint8_t i = 0; i < length; i++) {
        data[i].setShift(0);
      }
      break;

    default:
      DEBUG1_LN("WARNING: unknown cap behavior");
  }
}

Chord::CapBehaviorEnum Chord::decideCapBehavior(const Key* data,
                                                uint8_t length) const {
  bool has_cap_mod = hasMod(conf::getCapitalEnum());

  if (!getFlagCycleCapital()) {
    // The simple case, without cap cycling.
    if (has_cap_mod) {
      return CAP_FIRST;
    }
    return CAP_DEFAULT;
  }

  // The complicated case, where we might force capitalized dictionary words to
  // be lowercase.
  bool has_literal_shift = 0;
  for (uint8_t i = 0; i < length; i++) {
    if (data[i].containsShift()) {
      has_literal_shift = 1;
      break;
    }
  }

  if (has_literal_shift) {
    // If the word already contained capitalization, force it all to lowercase.
    return CAP_NONE;
  }

  // Otherwise, invert the cap mod.
  if (has_cap_mod) {
    return CAP_DEFAULT;
  }
  return CAP_FIRST;
}

bool Chord::hasModNospace() const { return hasMod(conf::getNospaceEnum()); }

bool Chord::hasModDouble() const { return hasMod(conf::getDoubleEnum()); }

bool Chord::hasModShorten() const { return hasMod(conf::getModShortenEnum()); }

void Chord::setModNospace() { setMod(conf::getNospaceEnum()); }


/// Return a mask where only the bit corresponding to the given modifier is set.
/// For use with mods_and_flags.
// TODO constexpr?
uint16_t getModMask(conf::Mod modifier) {
  // Mask must be the same size as mods_and_flags member.
  return (0x1 << conf::to_index(modifier));
}

bool Chord::hasMod(conf::Mod mod) const {
  return mods_and_flags & getModMask(mod);
}

void Chord::setMod(conf::Mod mod) {
  mods_and_flags |= getModMask(mod);
}

void Chord::unsetMod(conf::Mod mod) {
  mods_and_flags &= ~getModMask(mod);
}

void Chord::toggleMod(conf::Mod mod) {
  mods_and_flags ^= getModMask(mod);
}

/// Return a mask where only the bit corresponding to flag_cycle_capital is set.
/// For use with mods_and_flags.
// TODO just make this a const instead?
uint16_t getFlagCycleCapitalMask() {
  // Mask must be the same size as mods_and_flags member.
  return (0x1 << FLAG_BIT);
}


bool Chord::getFlagCycleCapital() const {
  return mods_and_flags & getFlagCycleCapitalMask();
}

void Chord::toggleFlagCycleCapital() {
  mods_and_flags ^= getFlagCycleCapitalMask();
}

void Chord::extractPlainMods() {
  for (conf::Mod plain_mod : conf::plain_mod_indices) {
    extractMod(plain_mod);
  }
}

void Chord::extractWordMods() {
  for (conf::Mod word_mod : conf::word_mod_indices) {
    extractMod(word_mod);
  }
}

void Chord::extractAnagramMods() {
  // TODO how does blank anagram0 work? Other blank mods are ignored...
  // Switch to null?
  if (!isAnagramMaskBlank()) {
    // At least one switch in an anagram is pressed, check to see if it's an
    //  actual mod chord.
    uint8_t index = 0;
    for (conf::Mod mod : conf::anagram_mod_indices) {
      if (extractMod(mod)) {
        // Found mod!
        anagram_num = index + 1;  // 0 is reserved for no mod
        return;
      }
      index++;
    }
  }
  // No valid anagram mod pressed
  anagram_num = 0;
}

void Chord::restoreAnagramMods() {
  const conf::Mod* mod = getAnagramModFromNumber(anagram_num);
  if (mod != nullptr) {
    // This anagram number can be directly selected by an anagram modifier.
    restoreMod(*mod);
  }
  anagram_num = 0;
}

void Chord::restoreWordMods() {
  for (conf::Mod word_mod : conf::word_mod_indices) {
      restoreMod(word_mod);
  }
}

bool Chord::extractMod(conf::Mod modifier) {
  // If mod is pressed in the chord:
  // - remove the mod bits from the chord
  // - set a flag saying it's present
  // - return true
  const ChordData* mod_chord_bytes = conf::getModChord(mode, modifier);
  if (allZeroes(mod_chord_bytes)) {
    // Mod is all zeroes - that's how we represent a missing mod chord. Ignore.
    return false;
  }
  bool isPressed = false;
  switch (conf::getModType(modifier)) {
    case conf::ModType::Plain:
    case conf::ModType::Word:
      isPressed = isChordMaskSet(mod_chord_bytes, &chord_bytes);
      break;
    case conf::ModType::Anagram:
      isPressed = isExactAnagramPressed(mod_chord_bytes);
      // TODO add default? or will it warn on new variants?
  }
  if (!isPressed) {
    // Mod is not pressed
    return false;
  }

  // Mod is pressed
  setMod(modifier);
  unsetMask(mod_chord_bytes, &chord_bytes);
  return true;
}

bool Chord::restoreMod(conf::Mod modifier) {
  // If mod flag is set:
  // - add the mod bits to the chord
  // - unset the flag
  // - return true
  bool was_set = hasMod(modifier);
  if (was_set) {
    unsetMod(modifier);
    setMask(conf::getModChord(mode, modifier), &chord_bytes);
  }
  return was_set;
}

void Chord::prepareToCycle() {
  // Unset mods that affect the word before this one, like by backspacing or
  // doubling its letters. We don't want to repeat those effects every time we
  // cycle this chord.
  unsetMod(conf::getModShortenEnum());
  unsetMod(conf::getDoubleEnum());
}

void Chord::cycle(CycleType operation) {
  switch (operation) {
    case CycleType::Capital:
      cycleCapital();
      break;

    case CycleType::Nospace:
      cycleNospace();
      break;

    case CycleType::Anagram:
      cycleAnagram();
      break;

    default:
      DEBUG1_LN("WARNING: unknown cycle type");
  }
}

void Chord::cycleCapital() {
  prepareToCycle();
  toggleFlagCycleCapital();
}

void Chord::cycleNospace() {
  prepareToCycle();
  toggleMod(conf::getNospaceEnum());
}

/********** Anagram manipulation ***********/

uint8_t Chord::cycleAnagram() {
  prepareToCycle();
  // Unset old mod flag
  setAnagramModFlag(anagram_num, 0);
  anagram_num = (anagram_num + 1) % (conf::MAX_ANAGRAM_NUM + 1);

  // Set new mod flag
  setAnagramModFlag(anagram_num, 1);
  return anagram_num;
}

bool Chord::isAnagramMaskBlank() {
  ChordData anagram_bytes = chord_bytes;
  andMask(conf::getAnagramMask(mode), &anagram_bytes);
  return allZeroes(&anagram_bytes);
}

bool Chord::isExactAnagramPressed(const ChordData* mod_chord) {
  // TODO share code with isAnagramMaskBlank()
  ChordData anagram_bytes = chord_bytes;
  andMask(conf::getAnagramMask(mode), &anagram_bytes);
  return *mod_chord == anagram_bytes;
}

uint8_t Chord::getAnagramNum() { return anagram_num; }

void Chord::setAnagramModFlag(uint8_t anagram_num, bool value) {
  const conf::Mod* mod = getAnagramModFromNumber(anagram_num);
  if (mod == nullptr) {
    return;
  }

  if (value) {
    setMod(*mod);
  } else {
    unsetMod(*mod);
  }
}
