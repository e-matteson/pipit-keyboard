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

  /* TODO why are these all const? */

  const HuffmanChar* decodeHuffman(const uint32_t bits, uint8_t length);
  const ModeStruct* getMode(mode_enum mode);
  bool isGaming(mode_enum mode);
  const LookupKmapType* getLookupKmapType(const ModeStruct* mode, uint8_t kmap_num, seq_type_enum seq_type);

  const uint8_t* getAnagramMask(mode_enum mode);
  const uint8_t* getModChord(mode_enum mode, mod_enum modifier);
  uint8_t getPlainModByte(uint8_t index);
  mod_enum getPlainModEnum(uint8_t index);
  mod_enum getWordModEnum(uint8_t index);
  mod_enum getAnagramModEnum(uint8_t index);
  mod_type getModType(mod_enum modifier);

  mod_enum getNospaceEnum();
  mod_enum getCapitalEnum();
  mod_enum getDoubleEnum();
  mod_enum getModShortenEnum();
}

#endif
