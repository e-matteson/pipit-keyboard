#include "lookup.h"
#include <algorithm>

bool areBitsEqual(const uint32_t a, const uint32_t b, uint32_t mask) {
  // TODO use xor?
  return (a & mask) == (b & mask);
}

uint32_t makeMask32(uint8_t length) {
  // The "length" least significant bits are 1, and the rest are 0
  size_t num_unused = 32 - length;
  return (~ (uint32_t)0) >> num_unused;
}

const LookupKmapType* getLookupKmapType(const ModeStruct* mode,
                                        uint8_t kmap_num, conf::SeqType seq_type) {
  return mode->kmaps[kmap_num]->lookups_for_kmap[conf::to_index(seq_type)];
}

const HuffmanChar* decodeHuffman(uint32_t bits, uint8_t length) {
  uint32_t mask = makeMask32(length);
  for (const HuffmanChar& entry : conf::huffman_lookup) {
    // The table is sorted by increasing code length.
    if (length > entry.num_bits) {
      // Go further
      continue;
    }
    if (length < entry.num_bits) {
      // Too far! Give up.
      break;
    }
    if (areBitsEqual(entry.bits, bits, mask)) {
      // Success!
      return &entry;
    }
  }
  // Fail!
  DEBUG2("NOTE: Failed to find huffman code of length ");
  DEBUG2_LN(length);
  return nullptr;
}

uint8_t decodeSequence(const LookupKmapTypeLenAnagram* lookup, uint16_t seq_num,
                       Key* keys_out) {
  // Return the number of keys in the decoded sequence, or zero if decoding
  // failed.
  uint16_t seq_bit_length = lookup->seq_bit_length();

  // The config-tool should enforce a maximum code bit length of 32
  uint8_t code_bit_length = conf::MIN_HUFFMAN_CODE_BIT_LEN;
  uint32_t code_bit_offset = 0;
  uint32_t key_index = 0;

  while (code_bit_offset + code_bit_length <= seq_bit_length) {
    uint32_t code =
        lookup->sequence_code_bits(seq_num, code_bit_offset, code_bit_length);

    const HuffmanChar* huffman = decodeHuffman(code, code_bit_length);
    if (huffman == nullptr) {
      // Not found! Try with a longer code next time.
      code_bit_length++;
      continue;
    }

    // Found! Store the decoded key or mod and move on to the next code.
    if (huffman->is_mod) {
      // Add a mod, and wait for more keys/mods to be added to this keypress in
      // the next iteration.
      keys_out[key_index].addMod(huffman->key_code);
    } else {
      // Add a key and move on to the next keypress
      keys_out[key_index].setKey(huffman->key_code);
      key_index++;
    }

    // Move on to the next code (of unknown bit length)
    code_bit_offset += code_bit_length;
    code_bit_length = conf::MIN_HUFFMAN_CODE_BIT_LEN;
  }

  if (code_bit_length > conf::MIN_HUFFMAN_CODE_BIT_LEN) {
    DEBUG1_LN("WARNING: ignored bits at end of huffman encoded sequence");
  }

  return key_index;
}

// TODO inline?
// TODO use binary search here, once the lookups are sorted.
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
  // If chord is found in lookup, store corresponding keys and return their length.
  // Otherwise, return 0.
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
