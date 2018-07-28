#include "structs.h"
#include "util.h"

// Should sum to 16
#define BITS_FOR_ANAGRAM 4
#define BITS_FOR_LEN 12

uint16_t LookupKmapTypeLenAnagram::seq_bit_length() const{
  return makeMask16(BITS_FOR_LEN) & (seq_bit_len_and_anagram >> BITS_FOR_ANAGRAM);
}

uint8_t LookupKmapTypeLenAnagram::anagram() const {
  return makeMask16(BITS_FOR_ANAGRAM) & seq_bit_len_and_anagram;
}

const uint8_t* LookupKmapTypeLenAnagram::chord(uint16_t chord_num, uint8_t num_bytes_in_chord) const {
  return chords + (chord_num * num_bytes_in_chord);
}

uint32_t LookupKmapTypeLenAnagram::sequence_code_bits(uint16_t seq_num,
                                                      uint32_t code_bit_offset,
                                                      uint8_t code_bit_length)
  const
{
  uint32_t start_bit_offset = seq_num * seq_bit_length();
  return getUnalignedBits(sequences, start_bit_offset+code_bit_offset, code_bit_length);
}

