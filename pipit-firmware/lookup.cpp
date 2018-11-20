#include "lookup.h"
#include <algorithm>

const LookupKmapType* getLookupForKmapAndType(const ModeStruct* mode,
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
uint8_t decodeSequence(BitSlice<uint8_t> seq_bits, Key* keys_out) {
  uint32_t key_index = 0;
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

namespace conf {

uint8_t lookup(const Chord* chord, SeqType type, Key* keys_out) {
  BitSlice<uint8_t> seq_bits;
  const ModeStruct* mode = conf::getModeStruct(chord->getModeName());
  for (uint8_t i = 0; i < mode->num_kmaps; i++) {
    // return mode->kmaps[kmap_num]->lookups_for_kmap[conf::to_index(seq_type)];
    const LookupKmapType* table = getLookupForKmapAndType(mode, i, type);

    seq_bits = table->find(chord->getData(), chord->getAnagramNum());
    // seq_bits = table->find(chord);
    if (!seq_bits.is_null()) {
      // Success!
      return decodeSequence(seq_bits, keys_out);
    }
  }
  return 0;  // Fail!
}
}  // namespace conf
