#include "conf.h"
#include "util.h"

const bool contains(const conf::Mod* mod_array, const uint8_t len,
                    const conf::Mod modifier) {
  for (uint8_t i = 0; i < len; i++) {
    if (mod_array[i] == modifier) {
      return true;
    }
  }
  return false;
}

namespace conf {
// Cast the enum to its underlying type
std::underlying_type<Mod>::type to_index(Mod variant) {
  return static_cast<std::underlying_type<Mod>::type>(variant);
}

// Cast the enum to its underlying type
std::underlying_type<SeqType>::type to_index(SeqType variant) {
  return static_cast<std::underlying_type<SeqType>::type>(variant);
}

// Cast the enum to its underlying type
std::underlying_type<Mode>::type to_index(Mode variant) {
  return static_cast<std::underlying_type<Mode>::type>(variant);
}

const HuffmanChar* decodeHuffman(const uint32_t bits, uint8_t length) {
  uint32_t mask = makeMask32(length);
  for (uint8_t i = 0; i < NUM_HUFFMAN_CODES; i++) {
    if (length != huffman_lookup[i].num_bits) {
      // Can't be a match, wrong length.
      continue;
    }
    if (areBitsEqual(huffman_lookup[i].bits, bits, mask)) {
      // Success!
      return huffman_lookup + i;
    }
  }
  // Fail!
  DEBUG2_LN(
      "WARNING: Failed to find huffman code in lookup, try again with a longer "
      "code");
  return 0;
}

const LookupKmapType* getLookupKmapType(const ModeStruct* mode,
                                        uint8_t kmap_num, SeqType seq_type) {
  return mode->kmaps[kmap_num]->lookups_for_kmap[to_index(seq_type)];
}

const ModeStruct* getMode(Mode mode) { return mode_structs[to_index(mode)]; }

bool isGaming(Mode mode) { return getMode(mode)->is_gaming; }

const uint8_t* getAnagramMask(Mode mode) { return getMode(mode)->anagram_mask; }

const uint8_t* getModChord(Mode mode, Mod modifier) {
  return getMode(mode)->mod_chords[to_index(modifier)];
}

uint8_t getPlainModByte(uint8_t index) {
  // TODO be consistent about mod terminology
  return plain_mod_keys[index];
}

Mod getPlainModEnum(uint8_t index) { return (Mod)plain_mod_indices[index]; }

Mod getWordModEnum(uint8_t index) { return (Mod)word_mod_indices[index]; }

Mod getAnagramModEnum(uint8_t index) { return (Mod)anagram_mod_indices[index]; }

ModType getModType(Mod modifier) {
  if (contains(plain_mod_indices, NUM_PLAIN_MODS, modifier)) {
    return ModType::Plain;
  }
  if (contains(word_mod_indices, NUM_WORD_MODS, modifier)) {
    return ModType::Word;
  }
  if (contains(anagram_mod_indices, NUM_ANAGRAM_MODS, modifier)) {
    return ModType::Anagram;
  }
  DEBUG1_LN("ERROR: Unknown modifier type");
  exit(1);
}

Mod getNospaceEnum() { return Mod::mod_nospace; }

Mod getCapitalEnum() { return Mod::mod_capital; }

Mod getDoubleEnum() { return Mod::mod_double; }

Mod getModShortenEnum() { return Mod::mod_shorten; }
}  // namespace conf
