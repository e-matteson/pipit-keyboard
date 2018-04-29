#ifndef LOOKUP_H_
#define LOOKUP_H_

#include <Arduino.h>
#include "auto_config.h"
#include "conf.h"
#include "Chord.h"
#include "Key.h"

class Lookup{

public:
  Lookup();

  uint8_t get(conf::seq_type_enum type, const Chord* chord, Key* keys);

private:

  uint8_t lookupChord(const Chord* chord, const LookupsOfSeqType* table, Key* keys_out);

  uint8_t readSequence(const uint8_t* seq_lookup,
                       uint8_t seq_length_in_bits, uint16_t seq_num, Key* keys_out);

  uint32_t getUnalignedCode(uint32_t bit_offset, uint8_t length, const uint8_t* array);

  bool bitToBool(const uint8_t* address, uint32_t bit_offset);

  // void printData(const uint8_t* data, uint8_t data_length);
  // void printBinary(uint8_t byte);
};

#endif
