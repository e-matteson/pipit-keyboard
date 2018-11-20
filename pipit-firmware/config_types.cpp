#include "config_types.h"
#include <limits.h>
#include <algorithm>
#include "Arduino.h"

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

BitSlice<uint8_t> LookupKmapTypeLenAnagram::sequence_bits(uint16_t seq_num) const {
  size_t length = seq_bit_length();
  size_t start_bit_offset = seq_num * length;
  BitSlice<uint8_t> b(sequences, start_bit_offset, length);
  return b;
}

BitSlice<uint8_t> LookupKmapTypeLenAnagram::find(const ChordData* chord_data) const {
  auto end = this->end();
  auto pos = std::lower_bound(this->begin(), end, *chord_data);
  if (pos != end && *pos == *chord_data) {
    // Found match!
    size_t seq_num = pos - this->begin();
    // BitSlice<uint8_t> seq_bits = this->sequence_bits(seq_num);
    return this->sequence_bits(seq_num);
  }
  return BitSlice<uint8_t>();  // Fail! No match found.
}

BitSlice<uint8_t> LookupKmapType::find(const ChordData* chord_data, uint8_t chord_anagram_num) const {
// BitSlice<uint8_t> LookupKmapType::find(const Chord* chord) const {
  // If chord is found in lookup, store corresponding keys and return their
  // length. Otherwise, return 0.
  BitSlice<uint8_t> seq_bits;

  for (uint32_t i = 0; i < this->num_lookups; i++) {
    const LookupKmapTypeLenAnagram* lookup = this->lookups[i];

    if (chord_anagram_num != lookup->anagram()) {
    // if (!chord->hasAnagramNum(lookup->anagram())) {
      // The chords in this lookup all have the wrong anagram number, skip it.
      continue;
    }

    seq_bits = lookup->find(chord_data);
    // seq_bits = lookup->find(chord->getData());

    if (!seq_bits.is_null()) {
      // Success!
      // return decodeSequence(seq_bits, keys_out);
      return seq_bits;
    }
  }
  // Fail! No match found, we know this BitSlice is null.
  return seq_bits;
}
