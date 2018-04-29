#include "Lookup.h"

Lookup::Lookup(){
}

uint8_t Lookup::get(conf::seq_type_enum type, const Chord* chord, Key* keys_out){
  conf::mode_enum mode = chord->getMode();
  for (uint8_t i = 0; i < conf::getNumKmaps(mode); i++){
    uint8_t length = lookupChord(chord,
                                 conf::getLookupsOfSeqType(mode, type, i),
                                 keys_out);
    if (length > 0) {
      return length; // Success!
    }
  }
  return 0; // Fail!
}

uint8_t Lookup::lookupChord(const Chord* chord, const LookupsOfSeqType* table, Key* keys_out){
  // If chord is found in lookup, store data and return its length.
  // Otherwise, return 0.
  for(uint32_t lookup_index = 0; lookup_index < table->num_lookups; lookup_index++){
    const LookupOfLength* lookup =  table->lookups[lookup_index];

    for(uint16_t chord_index = 0; chord_index < lookup->num_chords; chord_index++){
      // for each entry/chunk:
      // TODO accumulate instead of multiplying, to be faster?
      if(chord->matches(lookup->chords + chord_index*NUM_BYTES_IN_CHORD,
                        lookup->anagram()))
      {
        // Found match!
        return readSequence(lookup->sequences, lookup->seq_bit_len(), chord_index, keys_out);
      }
    }
  }
  return 0; // Fail! No match found.
}


/**** Sequence lookup utilities ****/

uint8_t Lookup::readSequence (const uint8_t* seq_lookup,
                              uint8_t seq_length_in_bits,
                              uint16_t seq_num,
                              Key* keys_out)
{
  // Decompress huffman-encoded data.
  // Return the number of bytes that were decompressed.
  uint32_t start_bit_offset = seq_num * seq_length_in_bits;

  uint32_t code_index = 0;
  uint32_t code_length = 1;
  uint32_t key_index = 0;

  while (code_index + code_length <= seq_length_in_bits) {
    uint32_t code = getUnalignedCode(start_bit_offset+code_index, code_length, seq_lookup);

    const HuffmanChar* huffman = conf::decodeHuffman(code, code_length);
    if (huffman == 0) {
      // Not found! Try with a longer code next time.
      code_length++;
      continue;
    }
    // Found! Store the decoded key or mod and move on to the next code.

    if (huffman->is_mod) {
      // Add a mod, and wait for more keys/mods to be added to this keypress in
      // the next iteration.
      keys_out[key_index].addMod(huffman->key_code);
    } else {
      // Add a key and move on
      keys_out[key_index].setKey(huffman->key_code);
      key_index++;
    }
    code_index += code_length;
    code_length = 1;
  }
  if (code_length > 1) {
    DEBUG1_LN("WARNING: unused bits in huffman code");
  }
  return key_index;
}

uint32_t Lookup::getUnalignedCode(uint32_t bit_offset, uint8_t length, const uint8_t* array) {
  uint32_t out = 0;
  for(int16_t i = length-1; i >= 0; i--) {
    if(bitToBool(array, bit_offset+i)){
      out |= (1 << i);
   }
  }
 return out;
}

bool Lookup::bitToBool(const uint8_t* address, uint32_t bit_offset) {
  uint32_t byte_offset = bit_offset / 8;
  uint8_t local_bit_offset = bit_offset % 8;

  uint8_t byte = address[byte_offset];
  return (byte >> local_bit_offset) & 0x01;
}


/***** Debugging *****/

// void Lookup::printData(const uint8_t* data, uint8_t data_length){
//   Serial.print("data: ");
//   for(int i = 0; i < data_length; i++){
//     Serial.print(data[i]);
//     Serial.print(" ");
//   }
//   Serial.println("");
// }

// void Lookup::printBinary(uint8_t byte){
//   Serial.print(" ");
//   for(int i = 7; i >= 0; i--){
//     Serial.print((byte >> i) & 1);
//     if(i == 4){
//       Serial.print(" ");
//     }
//   }
//   Serial.print("  ");
//   Serial.println(byte);
// }
