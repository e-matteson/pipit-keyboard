#ifndef LOOKUP_H_
#define LOOKUP_H_

#include <Arduino.h>
#include "keycodes.h"
#include "auto_config.h"
#include "conf.h"
#include "Chord.h"
#include "Key.h"

// Max # of bytes of data in a word/macro lookup array entry.
#define MAX_LOOKUP_DATA_LENGTH 256

class Lookup{

public:
  Lookup();

  uint8_t get(conf::seq_type_enum type, const Chord* chord, Key* keys);

private:

  uint8_t lookupChord(const Chord* chord, const KmapStruct* kmap, Key* keys);
  uint8_t readOffset(const uint8_t* start_of_entry);
  uint8_t readAnagramNum(const uint8_t* start_of_entry);
  uint8_t* getChordAddress(const uint8_t* start_of_entry);
  bool isEnd(const uint8_t* start_of_entry);
  uint8_t* nextChordEntry(uint8_t* start_of_entry);


  uint8_t readSequence(const uint8_t* seq_lookup,
                       uint16_t seq_length_in_bits, uint32_t seq_num, Key* keys_out);

  void getBitArray(bool* bits_out, uint16_t len_bits_out, const uint8_t* start, uint32_t bit_offset);
  bool bitToBool(const uint8_t* address, uint32_t bit_offset);


  // void printData(const uint8_t* data, uint8_t data_length);
  // void printBinary(uint8_t byte);

  // length of prefix that stores offset, and maybe other info someday
  // This must match ChordEntry.make_prefix_byte() in the config code.
  // TODO write in auto_config
  const uint8_t num_bytes_in_prefix = 1;
};

#endif
