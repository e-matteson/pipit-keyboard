/*
 * Here's where we define things that require "auto_config_early.h", and are required by "auto_config.h"
 */

#pragma once

#include <stdint.h>

#include "BitArray.h"
#include "BitSlice.h"
#include "auto_config_early.h"

// TODO automatically pick most efficient block type?
typedef BitArray<uint8_t, NUM_MATRIX_POSITIONS> ChordData;

typedef BitArray<uint8_t, MAX_HUFFMAN_CODE_BIT_LEN> HuffmanBits;

struct LookupKmapTypeLenAnagram {
  uint16_t seq_bit_len_and_anagram;
  uint16_t num_chords;
  const ChordData* chords;
  const uint8_t* sequences;

  uint16_t seq_bit_length() const;
  uint8_t anagram() const;
  BitSlice<uint8_t> sequence_bits (uint16_t seq_num) const;
  constexpr const ChordData* begin() const {
    return chords;
  }
  constexpr const ChordData* end() const {
    return chords + num_chords;
  }
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
  HuffmanBits bits;
  uint8_t num_bits;
  uint8_t key_code;
  bool is_mod;

  constexpr BitSlice<uint8_t> code_bits() const {
    return bits.slice_to(num_bits);
  }
};

enum class WordSpacePosition {
  Before,
  After,
  None,
};

