#include "lookup.h"
#include <algorithm>

bool areBitsEqual(const uint32_t a, const uint32_t b, uint32_t mask) {
  // TODO use xor?
  return (a & mask) == (b & mask);
}

uint32_t makeMask32(uint8_t length) {
  // The "length" least significant bits are 1, and the rest are 0
  size_t num_unused = 32 - length;
  return (~(uint32_t)0) >> num_unused;
}

const LookupKmapType* getLookupKmapType(const ModeStruct* mode,
                                        uint8_t kmap_num,
                                        conf::SeqType seq_type) {
  return mode->kmaps[kmap_num]->lookups_for_kmap[conf::to_index(seq_type)];
}

const HuffmanChar* decodeHuffman(BitSlice<uint8_t>& seq_bits) {
  for (const HuffmanChar& entry : conf::huffman_lookup) {
    if (seq_bits.has_prefix(entry.code_bits())) {
      // Success!
      seq_bits.skip(entry.num_bits);
      return &entry;
    }
  }
  return nullptr;  // Fail!
}

/// Return the number of keys in the decoded sequence, or zero if decoding
/// failed.
uint8_t decodeSequence(const LookupKmapTypeLenAnagram* lookup, uint16_t seq_num,
                       Key* keys_out) {
  uint32_t key_index = 0;
  BitSlice<uint8_t> seq_bits = lookup->sequence_bits(seq_num);

  while (seq_bits.size() != 0) {
    const HuffmanChar* entry = decodeHuffman(seq_bits);
    if (entry == nullptr) {
      DEBUG1("ERROR: failed to decode item ");
      DEBUG1(key_index);
      DEBUG1_LN(" in sequence");
      return 0;  // Fail
    }

    if (entry->is_mod) {
      // Add a mod, and wait for more keys/mods to be added to this keypress in
      // the next iteration.
      keys_out[key_index].addMod(entry->key_code);
    } else {
      // Add a key and move on to the next keypress
      keys_out[key_index].setKey(entry->key_code);
      key_index++;
    }
  }
  return key_index;  // Success
}

uint8_t lookupInKmapTypeLenAndAnagram(const Chord* chord,
                                      const LookupKmapTypeLenAnagram* lookup,
                                      Key* keys_out) {
  const ChordData* chord_data = chord->getData();
  auto end = lookup->end();
  auto pos = std::lower_bound(lookup->begin(), end, *chord_data);
  if (pos != end && *pos == *chord_data) {
    // Found match!
    size_t index = pos - lookup->begin();
    return decodeSequence(lookup, index, keys_out);
  }
  return 0;  // Fail! No match found.
}

uint8_t lookupInKmapAndType(const Chord* chord, const LookupKmapType* table,
                            Key* keys_out) {
  // If chord is found in lookup, store corresponding keys and return their
  // length. Otherwise, return 0.
  for (uint32_t lookup_index = 0; lookup_index < table->num_lookups;
       lookup_index++) {
    const LookupKmapTypeLenAnagram* lookup = table->lookups[lookup_index];

    if (!chord->hasAnagramNum(lookup->anagram())) {
      // The chords in this lookup all have the wrong anagram number, skip it.
      continue;
    }

    uint8_t length = lookupInKmapTypeLenAndAnagram(chord, lookup, keys_out);
    if (length > 0) {
      return length;  // Success!
    }
  }
  return 0;  // Fail! No match found.
}

namespace conf {

uint8_t lookup(const Chord* chord, SeqType type, Key* keys_out) {
  const ModeStruct* mode = conf::getModeStruct(chord->getModeName());
  for (uint8_t i = 0; i < mode->num_kmaps; i++) {
    const LookupKmapType* table = getLookupKmapType(mode, i, type);

    uint8_t length = lookupInKmapAndType(chord, table, keys_out);
    if (length > 0) {
      return length;  // Success!
    }
  }
  return 0;  // Fail!
}
}  // namespace conf
