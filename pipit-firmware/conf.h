#pragma once

#include <stdint.h>
#include <type_traits>
#include "auto_config.h"

namespace conf {

void black();
void white();
void red();
void green();
void blue();
void purple();
void cyan();
void redgreen();
void redgreenblue();
int readPinMode(uint8_t pin);

enum class ModType { Plain = 0, Word, Anagram };

uint8_t lookup(const Chord* chord, SeqType type, Key* keys_out);
const ModeStruct* getModeStruct(Mode mode);
bool isGaming(Mode mode);
const ChordData* getAnagramMask(Mode mode);
const ChordData* getModChord(Mode mode, Mod modifier);
ModType getModType(Mod modifier);
const Mod* anagramNumToMod(uint8_t anagram_num);

// Get the underlying type of the enum, to be used as an index
template <typename TEnum>
typename std::underlying_type<TEnum>::type to_index(TEnum variant) {
  return static_cast<typename std::underlying_type<TEnum>::type>(variant);
}

}  // namespace conf
