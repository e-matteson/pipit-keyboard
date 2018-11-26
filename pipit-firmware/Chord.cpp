#include "Chord.h"
#include <Arduino.h>
#include <type_traits>
#include "auto_config.h"
#include "conf.h"

//////////////////////////////////////////////////

Chord::Chord(conf::Mode mode) : mode(mode) {}

void Chord::setSwitch(uint8_t switch_index) { chord_data.set(switch_index); }

void Chord::setMode(conf::Mode _mode) { mode = _mode; }

bool Chord::isEmptyExceptMods() const {
  // Doesn't check the mods, just the current chord bytes.
  return chord_data.none();
}

/// Get the byte containing ctrl, shift, alt, and/or gui.
/// Needed for an HID keyboard report.
// TODO can we speed this up?
uint8_t Chord::getModByte() const {
  uint8_t mod_byte = 0;
  for (uint8_t i = 0; i < conf::plain_mods.size(); i++) {
    if (flags.hasMod(conf::plain_mods[i])) {
      mod_byte |= conf::plain_mod_keys[i];
    }
  }
  return mod_byte;
}

conf::Mode Chord::getModeName() const { return mode; }

bool Chord::hasAnagramNum(uint8_t other_anagram) const {
  return (anagram_num == other_anagram);
}

const ChordData* Chord::getData() const { return &chord_data; }

ChordData* Chord::getDataMut() { return &chord_data; }

/// Edit the capitalization of the given Keys, depending on a bunch of factors
/// like what mod flags are set for this Chord, what literal modifiers are
/// included in the Keys, etc.
void Chord::editCaps(Key* keys, uint8_t length) const {
  switch (decideCapBehavior(keys, length)) {
    case CapBehaviorEnum::CAP_DEFAULT:
      break;

    case CapBehaviorEnum::CAP_FIRST:
      keys[0].setShift(1);
      break;

    case CapBehaviorEnum::CAP_NONE:
      for (uint8_t i = 0; i < length; i++) {
        keys[i].setShift(0);
      }
      break;

    default:
      DEBUG1_LN("WARNING: unknown cap behavior");
  }
}

Chord::CapBehaviorEnum Chord::decideCapBehavior(const Key* keys,
                                                uint8_t length) const {
  bool has_cap_mod = flags.hasMod(conf::Mod::mod_capital);

  if (!flags.getFlagCycleCapital()) {
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
    if (keys[i].containsShift()) {
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

bool Chord::hasModNospace() const {
  return flags.hasMod(conf::Mod::mod_nospace);
}

bool Chord::hasModDouble() const { return flags.hasMod(conf::Mod::mod_double); }

bool Chord::hasModShorten() const {
  return flags.hasMod(conf::Mod::mod_shorten);
}

void Chord::setModNospace() { flags.setMod(conf::Mod::mod_nospace); }

bool Chord::hasMod(conf::Mod mod) const { return flags.hasMod(mod); }

void Chord::extractPlainMods() {
  for (conf::Mod plain_mod : conf::plain_mods) {
    extractMod(plain_mod);
  }
}

void Chord::extractWordMods() {
  for (conf::Mod word_mod : conf::word_mods) {
    extractMod(word_mod);
  }
}

void Chord::extractAnagramMods() {
  // TODO how does blank anagram0 work? Other blank mods are ignored...
  // Switch to null?
  if (!isAnagramMaskBlank()) {
    // At least one switch in an anagram is pressed, check to see if it's an
    //  actual mod chord.
    for (uint8_t i = 0; i < conf::anagram_mods.size(); i++) {
      if (extractMod(conf::anagram_mods[i])) {
        // Found mod!
        anagram_num = conf::anagram_mod_numbers[i];
        return;
      }
    }
  }
  // No valid anagram mod pressed
  anagram_num = 0;
}

void Chord::restoreAnagramMods() {
  const conf::Mod* mod = conf::anagramNumToMod(anagram_num);
  if (mod != nullptr) {
    // This anagram number can be directly selected by an anagram modifier.
    restoreMod(*mod);
  }
  anagram_num = 0;
}

void Chord::restoreWordMods() {
  for (conf::Mod word_mod : conf::word_mods) {
    restoreMod(word_mod);
  }
}

bool Chord::extractMod(conf::Mod modifier) {
  // If mod is pressed in the chord:
  // - remove the mod bits from the chord
  // - set a flag saying it's present
  // - return true
  const ChordData* mod_chord_data = conf::getModChord(mode, modifier);
  if (mod_chord_data->none()) {
    // Mod is all zeroes - that's how we represent a missing mod chord. Ignore.
    return false;
  }
  bool isPressed = false;
  switch (conf::getModType(modifier)) {
    case conf::ModType::Plain:
    case conf::ModType::Word:
      isPressed = chord_data.contains(*mod_chord_data);
      break;
    case conf::ModType::Anagram:
      isPressed = isExactAnagramPressed(mod_chord_data);
      // TODO add default? or will it warn on new variants?
  }
  if (!isPressed) {
    // Mod is not pressed
    return false;
  }

  // Mod is pressed, set flag and unset switches in chord
  flags.setMod(modifier);
  chord_data &= ~*mod_chord_data;
  return true;
}

bool Chord::restoreMod(conf::Mod modifier) {
  if (!flags.hasMod(modifier)) {
    return false;
  }
  flags.unsetMod(modifier);
  // Incorporate the switches of the mod chord into this chord.
  chord_data |= *conf::getModChord(mode, modifier);
  return true;
}

/// Create a chord containing the union of all of modifiers that have been
/// extracted from the this chord.
// TODO store this explicitly when extracting? space vs time
// TODO share code with restoreMod
ChordData Chord::getExtractedMods() {
  ChordData all_mods;
  for (uint8_t i = 0; i < NUM_MODIFIERS; i++) {
    conf::Mod mod = (conf::Mod)i;
    if (hasMod(mod)) {
      all_mods |= *conf::getModChord(mode, mod);
    }
  }
  return all_mods;
}

void Chord::prepareToCycle() {
  // Unset mods that affect the word before this one, like by backspacing or
  // doubling its letters. We don't want to repeat those effects every time we
  // cycle this chord.
  flags.unsetMod(conf::Mod::mod_shorten);
  flags.unsetMod(conf::Mod::mod_double);
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
  flags.toggleFlagCycleCapital();
}

void Chord::cycleNospace() {
  prepareToCycle();
  flags.toggleMod(conf::Mod::mod_nospace);
}

/********** Anagram manipulation ***********/

uint8_t Chord::cycleAnagram() {
  prepareToCycle();
  // Unset old mod flag
  setAnagramModFlag(anagram_num, false);
  anagram_num = (anagram_num + 1) % (conf::MAX_ANAGRAM_NUM + 1);

  // Set new mod flag
  setAnagramModFlag(anagram_num, true);
  return anagram_num;
}

bool Chord::isAnagramMaskBlank() {
  ChordData anagram_bytes = chord_data;
  anagram_bytes &= *conf::getAnagramMask(mode);
  return anagram_bytes.none();
}

bool Chord::isExactAnagramPressed(const ChordData* mod_chord) {
  // TODO share code with isAnagramMaskBlank()
  ChordData anagram_bytes = chord_data;
  anagram_bytes &= *conf::getAnagramMask(mode);
  return *mod_chord == anagram_bytes;
}

uint8_t Chord::getAnagramNum() const { return anagram_num; }

void Chord::setAnagramModFlag(uint8_t anagram_num, bool value) {
  const conf::Mod* mod = conf::anagramNumToMod(anagram_num);
  if (mod == nullptr) {
    return;
  }

  if (value) {
    flags.setMod(*mod);
  } else {
    flags.unsetMod(*mod);
  }
}

bool Chord::Flags::hasMod(conf::Mod mod) const {
  return bits.test(conf::to_index(mod));
}

void Chord::Flags::setMod(conf::Mod mod) { bits.set(conf::to_index(mod)); }

void Chord::Flags::unsetMod(conf::Mod mod) { bits.reset(conf::to_index(mod)); }

void Chord::Flags::toggleMod(conf::Mod mod) { bits.flip(conf::to_index(mod)); }

bool Chord::Flags::getFlagCycleCapital() const {
  return bits.test(cycleCapitalOffset());
}

void Chord::Flags::toggleFlagCycleCapital() { bits.flip(cycleCapitalOffset()); }

constexpr size_t Chord::Flags::cycleCapitalOffset() const {
  return bits.size() - 1;
}
