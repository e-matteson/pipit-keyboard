#ifndef CONF_H_
#define CONF_H_

#include <Arduino.h>
#include "structs.h"
#include "auto_config.h"

namespace conf {

  enum mod_type {
    PLAIN_MOD = 0,
    WORD_MOD,
    ANAGRAM_MOD
  };

  const HuffmanChar* decodeHuffman(uint32_t code, uint8_t length);

  bool areBitsEqual(const uint32_t a, const uint32_t b, uint32_t mask);

  uint32_t makeMask(uint8_t length);

  const ModeStruct* getMode(mode_enum mode);
  const LookupsOfSeqType* getLookupsOfSeqType(mode_enum mode, seq_type_enum seq_type, uint8_t kmap_num);
  uint8_t getNumKmaps(mode_enum mode);

  const uint8_t* getAnagramMask(mode_enum mode);

  const uint8_t* getModChord(mode_enum mode, mod_enum modifier);
  const uint8_t getPlainModByte(uint8_t index);
  const mod_enum getPlainModEnum(uint8_t index);
  const mod_enum getWordModEnum(uint8_t index);
  const mod_enum getAnagramModEnum(uint8_t index);
  const mod_type getModType(mod_enum modifier);

  const bool contains(const mod_enum* mod_array,
                      const uint8_t len,
                      const mod_enum modifier);
  const mod_enum getNospaceEnum();
  const mod_enum getCapitalEnum();
  const mod_enum getDoubleEnum();
  const mod_enum getModShortenEnum();

}

#endif
