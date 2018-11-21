#include "config_types.h"
#include <limits.h>
#include <algorithm>
#include "Arduino.h"


uint8_t LookupKmapTypeLenAnagram::anagram() const {
  return seq_bit_len_and_anagram.anagram();
}

BitSlice<uint8_t> LookupKmapTypeLenAnagram::getSequence(uint16_t seq_num) const {
  size_t length = seq_bit_len_and_anagram.length();
  size_t start_bit_offset = seq_num * length;
  BitSlice<uint8_t> b(sequences, start_bit_offset, length);
  return b;
}

BitSlice<uint8_t> LookupKmapTypeLenAnagram::find(const Chord* chord) const {
  auto chord_data = chord->getData();
  auto end = this->end();
  auto pos = std::lower_bound(this->begin(), end, *chord_data);
  if (pos != end && *pos == *chord_data) {
    // Found match!
    size_t seq_num = pos - this->begin();
    return this->getSequence(seq_num);
  }
  return BitSlice<uint8_t>();  // Fail! No match found.
}

BitSlice<uint8_t> LookupKmapType::find(const Chord* chord) const {
  // If chord is found in lookup, store corresponding keys and return their
  // length. Otherwise, return 0.
  BitSlice<uint8_t> seq_bits;

  for (size_t i = 0; i < this->num_lookups; i++) {
    const LookupKmapTypeLenAnagram* lookup = this->lookups[i];

    if (!chord->hasAnagramNum(lookup->anagram())) {
      // The chords in this lookup all have the wrong anagram number, skip it.
      continue;
    }

    seq_bits = lookup->find(chord);

    if (!seq_bits.is_null()) {
      return seq_bits; // Success!
    }
  }
  // Fail! No match found, we know this BitSlice is null.
  return seq_bits;
}

constexpr const LookupKmapType* KmapStruct::get(conf::SeqType seq_type) const {
  return this
      ->lookups_for_kmap[static_cast<std::underlying_type<conf::SeqType>::type>(
          seq_type)];
}

BitSlice<uint8_t> ModeStruct::find(const Chord* chord, conf::SeqType seq_type) const {
  BitSlice<uint8_t> seq_bits;
  for (uint8_t i = 0; i < this->num_kmaps; i++) {
    seq_bits = this->kmaps[i]->get(seq_type)->find(chord);
    if (!seq_bits.is_null()) {
      return seq_bits; // Success!
    }
  }
  // Fail! No match found, we know this BitSlice is null.
  return seq_bits;
}
