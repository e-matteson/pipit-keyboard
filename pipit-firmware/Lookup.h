#ifndef LOOKUP_H_
#define LOOKUP_H_

#include <Arduino.h>
#include "keycodes.h"
#include "auto_config.h"
#include "conf.h"
#include "Chord.h"

// Max # of bytes of data in a word/macro lookup array entry.
#define MAX_LOOKUP_DATA_LENGTH 256

class Lookup{

public:
  Lookup();

  uint8_t get(conf::seq_type_enum type, const Chord* chord, uint8_t* data);

private:
  uint8_t lookupChord(const Chord* chord, uint8_t* data, const KmapStruct* kmap);
  uint8_t readOffset(const uint8_t* start_of_entry);
  uint8_t* getChordAddress(const uint8_t* start_of_entry);
  bool isZero(const uint8_t* start_of_entry);
  uint8_t* nextChordEntry(uint8_t* start_of_entry);


  uint8_t readRaw(uint8_t* data_out, const uint8_t** seq_lookup,
                  uint8_t length_index, uint32_t seq_num, bool use_mods);
  uint8_t readCompressed(uint8_t* data_out, const uint8_t** seq_lookup,
                         uint8_t length_index, uint32_t seq_num);
  uint32_t decompressKey(const uint8_t* compressed, uint32_t key_index, uint8_t* key_out);
  uint32_t getStartCompressedIndex(uint32_t key_index);


  // void printData(const uint8_t* data, uint8_t data_length);
  // void printBinary(uint8_t byte);

  const uint8_t decompressed_cycle_length = 4;
  const uint8_t compressed_cycle_length = 3;

  // length of prefix that stores offset, and maybe other info someday
  const uint8_t num_bytes_in_prefix = 1;
};

#endif
