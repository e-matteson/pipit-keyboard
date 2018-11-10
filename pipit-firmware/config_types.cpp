#include "config_types.h"
#include "Arduino.h"
#include <limits.h>

// Should sum to 16
#define BITS_FOR_ANAGRAM 4
#define BITS_FOR_LEN 12

uint16_t makeMask16(uint8_t length) {
  // The "length" least-significant bits are 1, and the rest are 0
  // TODO compute by shifting all 1s, instead!
  if (length >= 16) {
    return ~((uint16_t)0);
  }
  return (1 << length) - 1;
}

uint16_t LookupKmapTypeLenAnagram::seq_bit_length() const {
  return makeMask16(BITS_FOR_LEN) &
         (seq_bit_len_and_anagram >> BITS_FOR_ANAGRAM);
}

uint8_t LookupKmapTypeLenAnagram::anagram() const {
  return makeMask16(BITS_FOR_ANAGRAM) & seq_bit_len_and_anagram;
}

BitSlice<uint8_t> LookupKmapTypeLenAnagram::sequence_bits (uint16_t seq_num) const {
  size_t length = seq_bit_length();
  size_t start_bit_offset = seq_num * length;
  BitSlice<uint8_t> b (sequences, start_bit_offset, length);
  return b;
}
