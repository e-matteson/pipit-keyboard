#include "conf.h"
#include "util.h"

namespace conf {

const HuffmanChar* decodeHuffman(const uint32_t bits, uint8_t length) {
  uint32_t mask = makeMask32(length);
  for(uint8_t i = 0; i < NUM_HUFFMAN_CODES; i++) {
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
  DEBUG2_LN("WARNING: Failed to find huffman code in lookup, try again with a longer code");
  return 0;
}



  const ModeStruct* getMode(mode_enum mode){
    return mode_structs[mode];
  }

  uint8_t getNumKmaps(mode_enum mode){
    return getMode(mode)->num_kmaps;
  }

  const LookupKmapType* getLookupForKmapAndType(mode_enum mode,
                                                seq_type_enum seq_type,
                                                uint8_t kmap_num){
    return getMode(mode)->kmaps[kmap_num]->lookups_for_kmap[seq_type];
  }

  const uint8_t* getAnagramMask(mode_enum mode) {
    return getMode(mode)->anagram_mask;
  }

  const uint8_t* getModChord(mode_enum mode, mod_enum modifier) {
    return getMode(mode)->mod_chords[modifier];
  }

  const uint8_t getPlainModByte(uint8_t index) {
    // TODO be consistent about mod terminology
    return plain_mod_keys[index];
  }

  const mod_enum getPlainModEnum(uint8_t index) {
    return (mod_enum) plain_mod_indices[index];
  }

  const mod_enum getWordModEnum(uint8_t index) {
    return (mod_enum) word_mod_indices[index];
  }

  const mod_enum getAnagramModEnum(uint8_t index) {
    // if(index >= NUM_ANAGRAM_MODS) {
    //   DEBUG1_LN("ERROR: anagram mod index out of bounds");
    //   exit(1);
    // }
    return (mod_enum) anagram_mod_indices[index];
  }

  const mod_type getModType(mod_enum modifier){
    if (contains(plain_mod_indices, NUM_PLAIN_MODS, modifier)){
      return mod_type::PLAIN_MOD;
    }
    if (contains(word_mod_indices, NUM_WORD_MODS, modifier)){
      return mod_type::WORD_MOD;
    }
    if (contains(anagram_mod_indices, NUM_ANAGRAM_MODS, modifier)){
      return mod_type::ANAGRAM_MOD;
    }
    DEBUG1_LN("ERROR: Unknown modifier type");
    exit(1);
  }

  const bool contains(const mod_enum* mod_array,
                      const uint8_t len,
                      const mod_enum modifier){
    for(uint8_t i = 0; i < len; i++){
      if(mod_array[i] == modifier){
        return true;
      }
    }
    return false;
  }

  const mod_enum getNospaceEnum() {
    return mod_enum::MOD_NOSPACE_ENUM;
  }

  const mod_enum getCapitalEnum() {
    return mod_enum::MOD_CAPITAL_ENUM;
  }

  const mod_enum getDoubleEnum() {
    return mod_enum::MOD_DOUBLE_ENUM;
  }

  const mod_enum getModShortenEnum() {
    return mod_enum::MOD_SHORTEN_ENUM;
  }

}
