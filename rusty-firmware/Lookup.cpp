#include "Lookup.h"

Lookup::Lookup(){
}

uint8_t Lookup::plain(const Chord* chord, uint8_t* data){
  return lookupChord(chord, data, plain_chord_lookup, plain_seq_lookup,  1, 0);
}

uint8_t Lookup::macro(const Chord* chord, uint8_t* data){
  return lookupChord(chord, data, macro_chord_lookup, macro_seq_lookup, 1, 0);
}

uint8_t Lookup::special(const Chord* chord, uint8_t* data){
  return lookupChord(chord, data, special_chord_lookup, special_seq_lookup, 0, 0);
}

uint8_t Lookup::word(const Chord* chord, uint8_t* data){
  return lookupChord(chord, data, word_chord_lookup, word_seq_lookup, 0, 1);
}

uint8_t Lookup::lookupChord(const Chord* chord, uint8_t* data,
                            const uint8_t** chord_lookup, const uint8_t** seq_lookup,
                            bool use_mods, bool is_word){
  // If chord is found in lookup, store data and return its length.
  // Otherwise, return 0.
  uint8_t length_index = 0;
  while(chord_lookup[length_index] != NULL){ // for each length subarray
    uint32_t chord_index = 0;
    while(!isZero(chord_lookup[length_index] + chord_index)){ // for each entry/chunk
      if(chord->isEqual(chord_lookup[length_index] + chord_index)){
        // Found match!
        if(is_word){
          // It's a word! Decompress the key sequence.
          return readCompressed(data, seq_lookup[length_index], length_index, chord_index);
        }
        else{
          // Not a word, so the key sequence is not compressed.
          return readRaw(data, seq_lookup[length_index], length_index, chord_index, use_mods);
        }
      }
      chord_index += NUM_BYTES_IN_CHORD;
    }
    length_index++;
  }
  return 0; // Fail! No match found.
}

uint8_t Lookup::readRaw(uint8_t* data_out, const uint8_t* seq_lookup_subarray,
                        uint8_t length_index, uint32_t chord_index, bool use_mods){
  uint8_t num_keys = length_index * (use_mods ? 2 : 1);
  uint32_t start_key_index = getStartKeyIndex(chord_index, num_keys);
  memcpy(data_out, seq_lookup_subarray + start_key_index, num_keys);
  return num_keys;
}

uint8_t Lookup::readCompressed(uint8_t* data_out, const uint8_t* seq_lookup_subarray,
                               uint8_t length_index, uint32_t chord_index){
  // Decompress data. Return the number of keys that were decompressed.
  uint8_t num_keys = length_index;
  uint32_t start_key_index = getStartKeyIndex(chord_index, num_keys);
  uint32_t compressed_index = getStartCompressedIndex(start_key_index);

  uint8_t key_index_offset;
  for(key_index_offset = 0; key_index_offset < num_keys; key_index_offset++){
    compressed_index += decompressKey(seq_lookup_subarray + compressed_index,
                                      start_key_index + key_index_offset,
                                      data_out + key_index_offset);
  }
  return key_index_offset;
}

uint32_t Lookup::getStartKeyIndex(uint32_t chord_index, uint8_t num_keys){
  return chord_index / NUM_BYTES_IN_CHORD * num_keys;
}

uint32_t Lookup::getStartCompressedIndex(uint32_t key_index){
  const uint8_t byte_offsets[] = {0,0,1,2};
  return (((key_index  / decompressed_cycle_length) * compressed_cycle_length)
          + (byte_offsets[key_index % this->decompressed_cycle_length]));
}

uint32_t Lookup::decompressKey(const uint8_t* compressed, uint32_t key_index, uint8_t* key_out){
  // Return number of bytes that were completely decompressed and are no longer needed.
  // Assume we always start on the 1st byte that contains part of the key.
  switch(key_index % this->decompressed_cycle_length){
  case 0:
    *key_out = compressed[0] >> 2;                                             //a
    return 0;
  case 1:
    *key_out = ((compressed[0]&0x03) << 4) |  ((compressed[1]&0xF0) >> 4);        //b
    return 1;
  case 2:
    *key_out = ((compressed[0]&0x0F) << 2) |  ((compressed[1]&0xC0) >> 6);        //c
    return 1;
  case 3:
    *key_out = (compressed[0]&0x3F);                                           //d
    return 1;
  default:
    DEBUG1("ERROR: bad decompression offset");
    return 0;
  }
}

const uint8_t* Lookup::wordmod_nospace  (){
  return  wordmod_nospace_chord_bytes;
}

const uint8_t* Lookup::wordmod_anagram1 (){
  return  wordmod_anagram1_chord_bytes;
}

const uint8_t* Lookup::wordmod_anagram2 (){
  return  wordmod_anagram2_chord_bytes;
}

const uint8_t* Lookup::wordmod_capital  (){
  return  wordmod_capital_chord_bytes;
}

bool Lookup::isZero(const uint8_t* address){
  // return true if the chord bytes at the address are all zero
  bool is_zero = 1;
  for(uint8_t k = 0; k != NUM_BYTES_IN_CHORD; k++){
    is_zero &= (address[k] == 0);
  }
  return is_zero;
}

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
