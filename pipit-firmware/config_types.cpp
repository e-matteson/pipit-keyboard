#include "config_types.h"
#include "Arduino.h"
#include <limits.h>

// Should sum to 16
#define BITS_FOR_ANAGRAM 4
#define BITS_FOR_LEN 12

uint32_t getUnalignedBits(const uint8_t* address, uint32_t start_bit_offset,
                          uint8_t num_bits) {
  if (num_bits > 32) {
    // Needs to fit in uint32_t!
    // DEBUG1_LN("ERROR: getUnalignedBits can only get up to 32 bits!");
    return 0;
  }
  uint32_t byte_offset = start_bit_offset / CHAR_BIT;
  uint8_t local_bit_offset = start_bit_offset % CHAR_BIT;
  // uint8_t num_bytes = (num_bits + CHAR_BIT - 1) / CHAR_BIT; // ceiling

  uint32_t out = 0;
  const uint8_t total_bytes = 4;
  for (uint8_t i = 0; i < total_bytes; i++) {
    uint8_t byte_index = (total_bytes-1-i);
    out |= (address[byte_offset + i] << (byte_index*CHAR_BIT + local_bit_offset));
 }
 return out;
}

uint16_t makeMask16(uint8_t length) {
  // The "length" least-significant bits are 1, and the rest are 0
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

uint32_t LookupKmapTypeLenAnagram::sequence_code_bits(
    uint16_t seq_num, uint32_t code_bit_offset, uint8_t code_bit_length) const {
  uint32_t start_bit_offset = seq_num * seq_bit_length();
  return getUnalignedBits(sequences, start_bit_offset + code_bit_offset,
                          code_bit_length);
}
