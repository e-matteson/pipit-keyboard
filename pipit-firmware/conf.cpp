#include "conf.h"

// using namespace conf;
namespace conf {

  const ModeStruct* getMode(mode_enum mode){
    return mode_structs[mode];
  }

  uint8_t getNumKmaps(mode_enum mode){
    return getMode(mode)->num_kmaps;
  }

  const KmapStruct* getKmap(mode_enum mode,
                      seq_type_enum seq_type,
                      uint8_t kmap_num){
    return getMode(mode)->kmaps[seq_type][kmap_num];
  }

  const uint8_t* getAnagramMask(mode_enum mode) {
    return getMode(mode)->anagram_mask;
  }

  const uint8_t* getAnagram(mode_enum mode, uint8_t num) {
    // TODO assert num < NUM_ANAGRAMS?
    return getMode(mode)->anagram_chords[num];
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
    return (mod_enum) anagram_mod_indices[index];
  }

  const mod_type getModType(mod_enum modifier){
    if (contains(plain_mod_indices, NUM_PLAIN_MODS, modifier)){
      return conf::PLAIN_MOD;
    }
    if (contains(word_mod_indices, NUM_WORD_MODS, modifier)){
      return conf::WORD_MOD;
    }
    if (contains(anagram_mod_indices, NUM_ANAGRAM_MODS, modifier)){
      return conf::ANAGRAM_MOD;
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
    return MOD_NOSPACE_ENUM;
  }

  const mod_enum getCapitalEnum() {
    return MOD_CAPITAL_ENUM;
  }

  const mod_enum getDoubleEnum() {
    return MOD_DOUBLE_ENUM;
  }

}
