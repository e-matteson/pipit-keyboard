/*
 * Here's where we define things that require "auto_config_early.h", and are
 * required by "auto_config.h"
 */

#pragma once

#include <stdint.h>
// Undefine these arduino macros that conflict with std::min/std::max, breaking
// other std lib stuff
#undef max
#undef min
#include <limits>

#include "BitArray.h"
#include "BitSlice.h"
#include "auto_config_early.h"
#include "Chord.h"

typedef BitArray<uint8_t, conf::MAX_HUFFMAN_CODE_BIT_LEN> HuffmanBits;

class LengthAndAnagram {
public:
  constexpr LengthAndAnagram(uint16_t length, uint8_t anagram)
    : combined( combine(length, anagram))  {}

  constexpr uint16_t length() const {
    return (combined & length_mask()) >> length_offset;
  }
  constexpr uint8_t anagram() const {
    return combined & anagram_mask();
  }

  static constexpr uint8_t max_anagram() {
    return max_val_of_bits(length_offset);
  }

  static constexpr uint16_t max_length() {
    return max_val_of_bits(std::numeric_limits<uint16_t>::digits - length_offset);
  }

private:
  static constexpr uint16_t combine(uint16_t length, uint8_t anagram) {
    return (anagram & anagram_mask()) | (length << length_offset);
  }

  static constexpr uint16_t anagram_mask() {
    return max_val_of_bits(length_offset);
  }

  static constexpr uint16_t length_mask() {
    return std::numeric_limits<uint16_t>::max() - anagram_mask();
  }

  static constexpr uint16_t max_val_of_bits(size_t num_bits) {
    return (1 << num_bits)-1;
  }

  uint16_t combined;
  static const uint8_t length_offset = 4;
};

static_assert(conf::MAX_ALLOWED_ANAGRAM == LengthAndAnagram::max_anagram(),
              "The firmware and config program disagree about how big anagram numbers can be");

static_assert(conf::MAX_ALLOWED_SEQUENCE_BIT_LENGTH == LengthAndAnagram::max_length(),
              "The firmware and config program disagree about how long compressed sequences can be");

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
  LookupKmapTypeLenAnagram const* const* lookups;
  BitSlice<uint8_t> find(const Chord* chord) const;
};

struct KmapStruct {
  LookupKmapType const* const* lookups_for_kmap;

  constexpr const LookupKmapType* get(conf::SeqType seq_type) const;
};

struct ModeStruct {
  bool is_gaming;
  uint8_t num_kmaps;
  KmapStruct const* const* kmaps;
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
