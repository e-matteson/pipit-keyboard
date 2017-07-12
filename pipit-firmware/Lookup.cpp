#include "Lookup.h"

Lookup::Lookup(){
}

uint8_t Lookup::get(conf::seq_type_enum type, const Chord* chord, Key* keys){
  conf::mode_enum mode = chord->getMode();
  for (uint8_t i = 0; i < conf::getNumKmaps(mode); i++){
    const KmapStruct* kmap = conf::getKmap(mode, type, i);
    if (kmap == NULL || kmap->sequences == NULL || kmap->chords == NULL) {
     continue;
    }
    uint8_t length = getKeys(chord, kmap, keys);
    if (length > 0) {
      return length; // Success!
    }
  }
  return 0; // Fail!
}

uint8_t Lookup::getKeys(const Chord* chord, const KmapStruct* kmap, Key* keys){
  // TODO arg order
  uint8_t data[MAX_LOOKUP_DATA_LENGTH] = {0};
  uint8_t data_length = lookupChord(chord, kmap, data);
  if(data_length == 0){
    return 0;
  }
  uint8_t byte_index = 0;
  uint8_t key_index = 0;
  while(byte_index < data_length){
    if(kmap->use_mods){
      keys[key_index].set(data[byte_index], data[byte_index+1]);
      byte_index += 2;
    }
    else{
      keys[key_index].set(data[byte_index], 0);
      byte_index++;
    }
    key_index++;
  }
  return key_index;
}

uint8_t Lookup::lookupChord(const Chord* chord, const KmapStruct* kmap, uint8_t* data){
  // If chord is found in lookup, store data and return its length.
  // Otherwise, return 0.
  uint8_t length_index = 0;
  while(kmap->chords[length_index] != NULL){ // for each length subarray
    uint8_t* entry = (uint8_t*) kmap->chords[length_index];
    uint32_t seq_num = 0;
    while(!isZero(entry)){ // for each entry/chunk
      seq_num += readOffset(entry);
      if(chord->matches(getChordAddress(entry), readAnagramNum(entry))){
        // Found match!
        if(kmap->use_compression){
          return readCompressed(data, kmap->sequences, length_index, seq_num);
        }
        else{
          return readRaw(data, kmap->sequences, length_index, seq_num, kmap->use_mods);
        }
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
  // Offset is in the 4 least significant bits of the first byte
  return start_of_entry[0] & 0x0F;
}

uint8_t Lookup::readAnagramNum(const uint8_t* start_of_entry) {
  // Anagram num is in the 4 most significant bits of the first byte
  return (start_of_entry[0] & 0xF0) >> 4;
}

uint8_t* Lookup::getChordAddress(const uint8_t* start_of_entry) {
  return (uint8_t*) start_of_entry + num_bytes_in_prefix;
}

bool Lookup::isZero(const uint8_t* start_of_entry){
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

uint8_t Lookup::readRaw(uint8_t* data_out, const uint8_t** seq_lookup,
                        uint8_t length_index, uint32_t seq_num, bool use_mods){
  uint8_t num_keys = length_index * (use_mods ? 2 : 1);
  uint32_t start_key_index = seq_num * num_keys;
  memcpy(data_out, seq_lookup[length_index] + start_key_index, num_keys);
  return num_keys;
}

uint8_t Lookup::readCompressed(uint8_t* data_out, const uint8_t** seq_lookup,
                               uint8_t length_index, uint32_t seq_num){
  // Decompress data. Return the number of keys that were decompressed.
  uint8_t num_keys = length_index;
  uint32_t start_key_index = seq_num * num_keys;
  uint32_t compressed_index = getStartCompressedIndex(start_key_index);

  uint8_t key_index_offset;
  for(key_index_offset = 0; key_index_offset < num_keys; key_index_offset++){
    compressed_index += decompressKey(seq_lookup[length_index] + compressed_index,
                                      start_key_index + key_index_offset,
                                      data_out + key_index_offset);
  }
  return key_index_offset;
}

uint32_t Lookup::getStartCompressedIndex(uint32_t key_index){
  const uint8_t byte_offsets[] = {0,0,1,2};
  return (((key_index / decompressed_cycle_length) * compressed_cycle_length)
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
