#ifndef CONF_H_
#define CONF_H_

#include <Arduino.h>
#include "structs.h"
#include "auto_config.h"

namespace conf {

  enum class ModType {
    Plain = 0,
    Word,
    Anagram
  };

  /* TODO why are these all const? */

  const HuffmanChar* decodeHuffman(const uint32_t bits, uint8_t length);
  const ModeStruct* getMode(Mode mode);
  bool isGaming(Mode mode);
  const LookupKmapType* getLookupKmapType(const ModeStruct* mode, uint8_t kmap_num, SeqType seq_type);

  const uint8_t* getAnagramMask(Mode mode);
  const uint8_t* getModChord(Mode mode, Mod modifier);
  uint8_t getPlainModByte(uint8_t index);
  Mod getPlainModEnum(uint8_t index);
  Mod getWordModEnum(uint8_t index);
  Mod getAnagramModEnum(uint8_t index);
  ModType getModType(Mod modifier);

  Mod getNospaceEnum();
  Mod getCapitalEnum();
  Mod getDoubleEnum();
  Mod getModShortenEnum();
}

#endif
