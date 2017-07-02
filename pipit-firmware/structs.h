#ifndef STRUCTS_H_
#define STRUCTS_H_

struct foo{
  uint8_t a;
  uint8_t b;
};

// extern const KmapStruct plain_default = {plain_default_mode_chord_lookup,
//                                            plain_seq_lookup,
//                                            0, // use_compression
//                                            1, // use_mods
//                                            1, // use_offsets
// };

struct KmapStruct{
  const uint8_t** chords;
  const uint8_t** sequences;
  bool use_compression;
  bool use_mods;
  bool use_offsets;
};

struct ModeStruct{
  uint8_t num_kmaps;
  KmapStruct** kmaps;
  uint8_t* mod_ctrl_chord;
  uint8_t* mod_shift_chord;
  uint8_t* mod_alt_chord;
  uint8_t* mod_gui_chord;
  uint8_t* wordmod_capital_chord;
  uint8_t* wordmod_nospace_chord;
  uint8_t** anagram_chords;
  uint8_t* anagram_mask;
};


#endif
