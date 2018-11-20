/*
 * Here's where we define things that require "auto_config_early.h", and are
 * required by "auto_config.h"
 */

#pragma once

#include <stdint.h>

#include "BitArray.h"
#include "BitSlice.h"
#include "auto_config_early.h"
#include "Chord.h"

typedef BitArray<uint8_t, MAX_HUFFMAN_CODE_BIT_LEN> HuffmanBits;


class LengthAndAnagram {
public:
  // constexpr LengthAndAnagram(uint16_t length, uint8_t anagram) : combined( anagram & (length << length_offset) ) {}
  constexpr LengthAndAnagram(uint16_t combined_) : combined(combined_) {}

  uint16_t length() const;
  uint8_t anagram() const;

private:
  uint16_t combined;
  // static const uint8_t anagram_offset = 0;
  // static const uint8_t length_offset = 4;
};

struct LookupKmapTypeLenAnagram {
  LengthAndAnagram seq_bit_len_and_anagram;
  uint16_t num_chords;
  const ChordData* chords;
  const uint8_t* sequences;

  BitSlice<uint8_t> find(const Chord* chord) const;

  uint8_t anagram() const;
  BitSlice<uint8_t> getSequence(uint16_t seq_num) const;
  constexpr const ChordData* begin() const { return chords; }
  constexpr const ChordData* end() const { return chords + num_chords; }
};

struct LookupKmapType {
  // TODO or just make the last element NULL?
  uint32_t num_lookups;
  const LookupKmapTypeLenAnagram** lookups;
  BitSlice<uint8_t> find(const Chord* chord) const;
};

struct KmapStruct {
  const LookupKmapType** lookups_for_kmap;

  constexpr const LookupKmapType* get(conf::SeqType seq_type) const;
};

struct ModeStruct {
  bool is_gaming;
  uint8_t num_kmaps;
  const KmapStruct** kmaps;
  const ChordData* mod_chords;
  ChordData anagram_mask;

  BitSlice<uint8_t> find(const Chord* chord, conf::SeqType seq_type) const;

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
