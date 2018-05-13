#include "structs.h"
#include "util.h"

// Should sum to 16
#define BITS_FOR_ANAGRAM 4
#define BITS_FOR_LEN 12

uint16_t LookupOfLength::seq_bit_len() const{
  return makeMask16(BITS_FOR_LEN) & (seq_bit_len_and_anagram >> BITS_FOR_ANAGRAM);
}

uint8_t LookupOfLength::anagram() const {
  return makeMask16(BITS_FOR_ANAGRAM) & seq_bit_len_and_anagram;
}
