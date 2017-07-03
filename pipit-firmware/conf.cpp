#include "conf.h"

// using namespace conf;
namespace conf {

  const ModeStruct* getMode(mode_enum mode){
    return mode_structs[mode];
  }

  uint8_t getNumKmaps(mode_enum mode){
    return getMode(mode)->num_kmaps;
  }

  // ModeStruct getSeqType(mode_enum mode, conf::seq_type_enum seq_type){
  //   return getMode(mode)[seq_type];
  // }

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

  const uint8_t* getModifier(mode_enum mode, mod_enum modifier) {
    return getMode(mode)->mod_chords[modifier];
  }

  const uint8_t* getNospace(mode_enum mode) {
    return getModifier(mode, WORDMOD_NOSPACE_ENUM);
  }

  const uint8_t* getCapital(mode_enum mode) {
    return getModifier(mode, WORDMOD_CAPITAL_ENUM);
  }

  const uint8_t* getCtrl(mode_enum mode) {
    return getModifier(mode, MODIFIERKEY_CTRL_ENUM);
  }

  const uint8_t* getShift(mode_enum mode) {
    return getModifier(mode, MODIFIERKEY_SHIFT_ENUM);
  }

  const uint8_t* getAlt(mode_enum mode) {
    return getModifier(mode, MODIFIERKEY_ALT_ENUM);
  }

  const uint8_t* getGUI(mode_enum mode) {
    return getModifier(mode, MODIFIERKEY_GUI_ENUM);
  }
}
