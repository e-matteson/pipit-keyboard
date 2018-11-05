/*
 * Here's where we define things that require "auto_config_early.h", and are required by "auto_config.h"
 */

#pragma once

#include <stdint.h>

#include "BitArray.h"
#include "auto_config_early.h"

// TODO automatically pick most efficient block type?
typedef BitArray<uint8_t, NUM_MATRIX_POSITIONS> ChordData;


struct LookupKmapTypeLenAnagram {
  uint16_t seq_bit_len_and_anagram;
  uint16_t num_chords;
  const ChordData* chords;
  const uint8_t* sequences;

  uint16_t seq_bit_length() const;
  uint8_t anagram() const;
  uint32_t sequence_code_bits(uint16_t seq_num, uint32_t code_bit_offset,
                              uint8_t code_bit_length) const;
};

struct LookupKmapType {
  // TODO or just make the last element NULL?
  uint32_t num_lookups;
  const LookupKmapTypeLenAnagram** lookups;
};

struct KmapStruct {
  const LookupKmapType** lookups_for_kmap;
};

struct ModeStruct {
  bool is_gaming;
  uint8_t num_kmaps;
  const KmapStruct** kmaps;
  const ChordData* mod_chords;
  ChordData anagram_mask;
};

struct HuffmanChar {
  uint32_t bits;
  uint8_t num_bits;  // actual max is 32, not 255
  uint8_t key_code;
  bool is_mod;
};

enum class WordSpacePosition {
  Before,
  After,
  None,
};

