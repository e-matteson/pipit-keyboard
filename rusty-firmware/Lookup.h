#ifndef LOOKUP_H_
#define LOOKUP_H_

#include <Arduino.h>
#include "keycodes.h"
#include "auto_config.h"
#include "Chord.h"

// Max # of bytes of data in a word/macro lookup array entry.
#define MAX_LOOKUP_DATA_LENGTH 256

class Lookup{

public:
  Lookup();
  uint8_t plain(const Chord* chord, uint8_t* data);
  uint8_t macro(const Chord* chord, uint8_t* data);
  uint8_t special(const Chord* chord, uint8_t* data);
  uint8_t word(const Chord* chord, uint8_t* data);

  const uint8_t* wordmod_nospace();
  const uint8_t* wordmod_anagram1();
  const uint8_t* wordmod_anagram2();
  const uint8_t* wordmod_capital();

private:
  uint8_t lookupChord(const Chord* chord, uint8_t* data, const uint8_t** chord_lookup,
                      const uint8_t** seq_lookup, bool use_mods, bool is_word);

  uint8_t readRaw(uint8_t* data_out, const uint8_t* seq_lookup_subarray,
                  uint8_t length_index, uint32_t chord_index, bool use_mods);
  uint8_t readCompressed(uint8_t* data_out, const uint8_t* seq_lookup_subarray,
                         uint8_t length_index, uint32_t chord_index);
  uint32_t decompressKey(const uint8_t* compressed, uint32_t key_index, uint8_t* key_out);
  uint32_t getStartCompressedIndex(uint32_t key_index);
  uint32_t getStartKeyIndex(uint32_t chord_index, uint8_t num_keys);

  bool isZero(const uint8_t* address);

  // void printData(const uint8_t* data, uint8_t data_length);
  // void printBinary(uint8_t byte);

  const uint8_t decompressed_cycle_length = 4;
  const uint8_t compressed_cycle_length = 3;
};

#endif
