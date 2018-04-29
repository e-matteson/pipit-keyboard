#ifndef LOOKUP_H_
#define LOOKUP_H_

#include <Arduino.h>
#include "auto_config.h"
#include "conf.h"
#include "Chord.h"
#include "Key.h"

// Max # of bytes of data in a word/macro lookup array entry.
//  TODO enforce in config!
#define MAX_LOOKUP_DATA_LENGTH 50

class Lookup{

public:
  Lookup();

  uint8_t get(conf::seq_type_enum type, const Chord* chord, Key* keys);

private:

  uint8_t lookupChord(const Chord* chord, const LookupsOfSeqType* table, Key* keys_out);

  uint8_t readSequence(const uint8_t* seq_lookup,
                       uint8_t seq_length_in_bits, uint16_t seq_num, Key* keys_out);

  void getBitArray(bool* bits_out, uint8_t len_bits_out, const uint8_t* start, uint32_t bit_offset);
  bool bitToBool(const uint8_t* address, uint32_t bit_offset);


  // void printData(const uint8_t* data, uint8_t data_length);
  // void printBinary(uint8_t byte);
};

#endif
