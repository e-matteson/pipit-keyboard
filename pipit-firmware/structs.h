#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <Arduino.h>


struct LookupKmapTypeLenAnagram {
  const uint16_t seq_bit_len_and_anagram;
  const uint16_t num_chords;
  const uint8_t* chords;
  const uint8_t* sequences;

  uint16_t  seq_bit_len() const ;
  uint8_t  anagram() const;
};

struct LookupKmapType {
  // TODO or just make the last element NULL?
  const uint32_t num_lookups;
  const LookupKmapTypeLenAnagram** lookups;
};

struct KmapStruct {
  const LookupKmapType** lookups_for_kmap;
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
