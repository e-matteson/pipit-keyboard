#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <Arduino.h>


struct KmapStruct{
  const uint8_t** chords;
  const uint8_t** sequences;
  bool use_compression;
  bool use_mods;
  bool use_offsets;
  // uint8_t magic;
};

struct ModeStruct{
  const uint8_t num_kmaps;
  const KmapStruct*** kmaps;
  const uint8_t** mod_chords;
  const uint8_t** anagram_chords;
  const uint8_t* anagram_mask;
  const bool is_gaming;
};


#endif
