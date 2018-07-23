#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <Arduino.h>

// uint8_t* kmap0_plain_len3_anagram0_chords = {0, 2, 0 ...};
// uint8_t* kmap0_plain_len3_anagram0_sequences = {6, ...};

// LookupOfLength kmap0_plain_len3_anagram0 = {
//   3,
//   0,
//   42,
//   kmap0_plain_len3_anagram0_chords,
//   kmap0_plain_len3_anagram0_sequences,
// };

// LookupOfLength* kmap0_plain_lookups_array = {kmap0_plain_len3_anagram0, ...};

// LookupsOfSeqType kmap0_plain_lookups = {
//   100,
//   kmap0_plain_lookups_array,
// };

// KmapStruct kmap0_lookups = {kmap0_plain_lookups, kmap0_macro_lookups, ... };

// ModeStruct default_mode = {
//   2, // num_kmaps
//   {kmap0_lookups, kmap3_lookups} // kmaps
//   default_mode_mod_chords, // mod_chords
//   default_mode_anagram_mask, // anagram_mask
//   0, // is_gaming
// };

struct LookupOfLength {
  const uint16_t seq_bit_len_and_anagram;
  const uint16_t num_chords;
  const uint8_t* chords;
  const uint8_t* sequences;

  uint16_t  seq_bit_len() const ;
  uint8_t  anagram() const;
};

struct LookupsOfSeqType {
  // TODO or just make the last element NULL?
  const uint32_t num_lookups;
  const LookupOfLength** lookups;
};

struct KmapStruct {
  const LookupsOfSeqType** lookups_by_seq_type;
  // const uint32_t length; // not needed, only indexing by seq_type_enum
};

struct ModeStruct {
  const bool is_gaming;
  const uint8_t num_kmaps;
  const KmapStruct** kmaps;
  const uint8_t** mod_chords;
  const uint8_t* anagram_mask;
};

struct HuffmanChar {
  const uint32_t bits;
  const uint8_t num_bits; // actual max is 32, not 255
  const uint8_t key_code;
  const bool is_mod;
};


#endif
