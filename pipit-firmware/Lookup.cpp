#include "Lookup.h"

Lookup::Lookup(){
}

uint8_t Lookup::get(conf::seq_type_enum type, const Chord* chord, Key* keys_out){
  conf::mode_enum mode = chord->getMode();
  for (uint8_t i = 0; i < conf::getNumKmaps(mode); i++){
    const KmapStruct* kmap = conf::getKmap(mode, type, i);
    if (kmap == NULL || kmap->sequences == NULL || kmap->chords == NULL) {
     continue;
    }
    uint8_t length = lookupChord(chord, kmap, keys_out);
    if (length > 0) {
      return length; // Success!
    }
  }
  return 0; // Fail!
}

uint8_t Lookup::lookupChord(const Chord* chord, const KmapStruct* kmap, Key* keys_out){
  // If chord is found in lookup, store data and return its length.
  // Otherwise, return 0.
  uint8_t length_index = 0;
  while(kmap->chords[length_index] != NULL){ // for each length subarray
    uint8_t* entry = (uint8_t*) kmap->chords[length_index];
    uint32_t seq_num = 0;
    while(!isEnd(entry)){ // for each entry/chunk
      seq_num += readOffset(entry);
      if(chord->matches(getChordAddress(entry), readAnagramNum(entry))){
        // Found match!
        return readSequence(kmap->sequences[length_index], length_index, seq_num, keys_out);
      }
      // Keep looking.
      entry = nextChordEntry(entry);
    }
    length_index++;
  }
  return 0; // Fail! No match found.
}

/**** Chord lookup utilities ****/

uint8_t Lookup::readOffset(const uint8_t* start_of_entry) {
  // Offset is in the 5 least significant bits of the first byte.
  // This must match ChordEntry.make_prefix_byte() in the config code.
  // TODO write in auto_config
  return start_of_entry[0] & 0x1F;
}

uint8_t Lookup::readAnagramNum(const uint8_t* start_of_entry) {
  // Anagram num is in the 3 most significant bits of the first byte.
  // This must match ChordEntry.make_prefix_byte() in the config code.
  // TODO write in auto_config
  return (start_of_entry[0] & 0xE0) >> 5;
}

uint8_t* Lookup::getChordAddress(const uint8_t* start_of_entry) {
  return (uint8_t*) start_of_entry + num_bytes_in_prefix;
}

bool Lookup::isEnd(const uint8_t* start_of_entry){
  // return true if the chord bytes of the entry at the address are all zero
  const uint8_t* chord_address = getChordAddress(start_of_entry);
  bool is_zero = 1;
  for(uint8_t k = 0; k != NUM_BYTES_IN_CHORD; k++){
    is_zero &= (chord_address[k] == 0);
  }
  return is_zero;
}

uint8_t* Lookup::nextChordEntry(uint8_t* start_of_entry){
  return start_of_entry + num_bytes_in_prefix + NUM_BYTES_IN_CHORD;
}

/**** Sequence lookup utilities ****/

uint8_t Lookup::readSequence(const uint8_t* seq_lookup,
                             uint16_t seq_length_in_bits, uint32_t seq_num, Key* keys_out){
  // Decompress data. Return the number of bytes that were decompressed.
  uint32_t bit_offset = seq_num * seq_length_in_bits;
  bool bits[seq_length_in_bits];
  getBitArray(bits, seq_length_in_bits, seq_lookup, bit_offset);

  uint16_t code_index = 0;
  uint16_t code_length = 1;
  uint32_t key_index = 0;

  while (code_index + code_length <= seq_length_in_bits) {
    const HuffmanChar* huffman = conf::decode_huffman(bits+code_index, code_length);
    if (huffman == 0) {
      // Not found! Try with a longer code next time.
      code_length++;
    } else {
      // Found! Store the letter and move on to the next code.
      if (huffman->is_mod) {
        keys_out[key_index].addMod(huffman->key_code);
      } else {
        keys_out[key_index].setKey(huffman->key_code);
        key_index++;
      }
      code_index += code_length;
      code_length = 1;
    }
  }
  if (code_length > 1) {
    DEBUG1_LN("WARNING: unused bits in huffman code");
  }
  return key_index;
}

void Lookup::getBitArray(bool* bits_out, uint16_t len_bits_out, const uint8_t* start, uint32_t bit_offset) {
  for(uint16_t i = 0; i < len_bits_out; i++) {
    bits_out[i] = bitToBool(start, bit_offset + i);
  }
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
