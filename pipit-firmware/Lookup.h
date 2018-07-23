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

  uint8_t lookupChord(const Chord* chord, const LookupKmapType* table, Key* keys_out);

  uint8_t readSequence(const uint8_t* seq_lookup,
                       uint16_t seq_length_in_bits,
                       uint16_t seq_num,
                       Key* keys_out);


  // void printData(const uint8_t* data, uint8_t data_length);
  // void printBinary(uint8_t byte);
};

#endif
