#include "auto_config-22.h"
namespace conf {
const uint32_t CHORD_DELAY = 30;

const uint32_t HELD_DELAY = 200;

const uint32_t DEBOUNCE_DELAY = 10;

const WordSpacePosition SPACE_POS = WordSpacePosition::Before;

const uint8_t row_pins[3] = {
 1, 0, 19, 
};

const uint8_t column_pins[8] = {
 15, 16, 17, 18, 
 20, 21, 5, 6, 
};

const bool USE_STANDBY_INTERRUPTS = 1;

const uint8_t rgb_led_pins[3] = {
 10, 11, 12, 
};

const uint8_t battery_level_pin = 9;

const uint8_t MIN_HUFFMAN_CODE_BIT_LEN = 4;

const HuffmanChar huffman_lookup[68] = {
 {
  21, // bits
  5, // num_bits
  static_cast<uint8_t>(0 /* blank key, when a keypress contains only modifiers and no key */), // key_code
  0, // is_mod
}, {
  6, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_cycle_capital), // key_code
  0, // is_mod
}, {
  38, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_cycle_nospace), // key_code
  0, // is_mod
}, {
  51, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_cycle_word), // key_code
  0, // is_mod
}, 
 {
  115, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_delete_word), // key_code
  0, // is_mod
}, {
  12, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_led_battery), // key_code
  0, // is_mod
}, {
  22, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_led_colors), // key_code
  0, // is_mod
}, {
  87, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_led_rainbow), // key_code
  0, // is_mod
}, 
 {
  3, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_left_limit), // key_code
  0, // is_mod
}, {
  125, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_left_word), // key_code
  0, // is_mod
}, {
  45, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_pause), // key_code
  0, // is_mod
}, {
  60, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_right_limit), // key_code
  0, // is_mod
}, 
 {
  44, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_right_word), // key_code
  0, // is_mod
}, {
  9, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_shorten_last_word), // key_code
  0, // is_mod
}, {
  54, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_sticky_alt), // key_code
  0, // is_mod
}, {
  52, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_sticky_ctrl), // key_code
  0, // is_mod
}, 
 {
  15, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_sticky_gui), // key_code
  0, // is_mod
}, {
  99, // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_sticky_shift), // key_code
  0, // is_mod
}, {
  7, // bits
  5, // num_bits
  static_cast<uint8_t>(Command::command_switch_to), // key_code
  0, // is_mod
}, {
  56, // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_windows_mode), // key_code
  0, // is_mod
}, 
 {
  8, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_0), // key_code
  0, // is_mod
}, {
  13, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_1), // key_code
  0, // is_mod
}, {
  109, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_2), // key_code
  0, // is_mod
}, {
  5, // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_3), // key_code
  0, // is_mod
}, 
 {
  18, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_4), // key_code
  0, // is_mod
}, {
  36, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_5), // key_code
  0, // is_mod
}, {
  47, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_6), // key_code
  0, // is_mod
}, {
  43, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_7), // key_code
  0, // is_mod
}, 
 {
  41, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_8), // key_code
  0, // is_mod
}, {
  95, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_9), // key_code
  0, // is_mod
}, {
  16, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_A), // key_code
  0, // is_mod
}, {
  62, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_B), // key_code
  0, // is_mod
}, 
 {
  1, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_BACKSPACE), // key_code
  0, // is_mod
}, {
  30, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_C), // key_code
  0, // is_mod
}, {
  79, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_D), // key_code
  0, // is_mod
}, {
  27, // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_E), // key_code
  0, // is_mod
}, 
 {
  20, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_ENTER), // key_code
  0, // is_mod
}, {
  67, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_F), // key_code
  0, // is_mod
}, {
  35, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_G), // key_code
  0, // is_mod
}, {
  25, // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_H), // key_code
  0, // is_mod
}, 
 {
  23, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_I), // key_code
  0, // is_mod
}, {
  24, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_J), // key_code
  0, // is_mod
}, {
  40, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_K), // key_code
  0, // is_mod
}, {
  19, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_L), // key_code
  0, // is_mod
}, 
 {
  61, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_M), // key_code
  0, // is_mod
}, {
  93, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_N), // key_code
  0, // is_mod
}, {
  29, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_O), // key_code
  0, // is_mod
}, {
  14, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_P), // key_code
  0, // is_mod
}, 
 {
  46, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_Q), // key_code
  0, // is_mod
}, {
  50, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_R), // key_code
  0, // is_mod
}, {
  11, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_S), // key_code
  0, // is_mod
}, {
  28, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_SPACE), // key_code
  0, // is_mod
}, 
 {
  10, // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_T), // key_code
  0, // is_mod
}, {
  4, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_TAB), // key_code
  0, // is_mod
}, {
  111, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_U), // key_code
  0, // is_mod
}, {
  0, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_V), // key_code
  0, // is_mod
}, 
 {
  32, // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_W), // key_code
  0, // is_mod
}, {
  119, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_X), // key_code
  0, // is_mod
}, {
  55, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_Y), // key_code
  0, // is_mod
}, {
  127, // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_Z), // key_code
  0, // is_mod
}, 
 {
  63, // bits
  7, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_ALT), // key_code
  1, // is_mod
}, {
  17, // bits
  6, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_CTRL), // key_code
  1, // is_mod
}, {
  48, // bits
  6, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_GUI), // key_code
  1, // is_mod
}, {
  33, // bits
  6, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_SHIFT), // key_code
  1, // is_mod
}, 
 {
  31, // bits
  7, // num_bits
  static_cast<uint8_t>(Mode::default_mode), // key_code
  0, // is_mod
}, {
  49, // bits
  6, // num_bits
  static_cast<uint8_t>(Mode::gaming_mode), // key_code
  0, // is_mod
}, {
  34, // bits
  6, // num_bits
  static_cast<uint8_t>(Mode::left_hand_mode), // key_code
  0, // is_mod
}, {
  2, // bits
  6, // num_bits
  static_cast<uint8_t>(Mode::windows_mode), // key_code
  0, // is_mod
}, 
};

const uint8_t MAX_ANAGRAM_NUM = 1;

const Mod word_mods[4] = {
 Mod::mod_capital, Mod::mod_nospace, Mod::mod_double, Mod::mod_shorten, 
};

const Mod plain_mods[4] = {
 Mod::mod_alt, Mod::mod_ctrl, Mod::mod_gui, Mod::mod_shift, 
};

const Mod anagram_mods[2] = {
 Mod::mod_anagram_1, Mod::mod_anagram_2, 
};

const uint8_t anagram_mod_numbers[2] = {
 1, 2, 
};

const uint8_t plain_mod_keys[4] = {
 static_cast<uint8_t>(MODIFIERKEY_ALT), static_cast<uint8_t>(MODIFIERKEY_CTRL), static_cast<uint8_t>(MODIFIERKEY_GUI), static_cast<uint8_t>(MODIFIERKEY_SHIFT), 
};

const uint8_t MAX_KEYS_IN_SEQUENCE = 5;

const ChordData kmap0_Plain_len4_anagram0_chords[1] = {
 {0, 0, 1}, 
};

const uint8_t kmap0_Plain_len4_anagram0_seqs[1] = {
 10, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len4_anagram0 = {
  64, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len4_anagram0_chords, // chords
  kmap0_Plain_len4_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len5_anagram0_chords[3] = {
 {144, 0, 0}, {16, 0, 0}, {0, 32, 0}, 
};

const uint8_t kmap0_Plain_len5_anagram0_seqs[2] = {
 101, 103, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len5_anagram0 = {
  80, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Plain_len5_anagram0_chords, // chords
  kmap0_Plain_len5_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len6_anagram0_chords[20] = {
 {0, 32, 1}, {18, 0, 0}, {0, 0, 72}, {128, 4, 0}, 
 {130, 0, 0}, {0, 0, 65}, {0, 4, 0}, {36, 0, 0}, 
 {8, 0, 0}, {0, 0, 2}, {0, 0, 144}, {0, 9, 0}, 
 {0, 0, 128}, {4, 0, 0}, {0, 64, 128}, {0, 0, 16}, 
 {0, 0, 64}, {0, 128, 0}, {32, 8, 0}, {0, 64, 2}, 
};

const uint8_t kmap0_Plain_len6_anagram0_seqs[15] = {
 72, 35, 145, 107, 
 10, 249, 129, 135, 
 161, 147, 227, 202, 
 11, 7, 128, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len6_anagram0 = {
  96, // seq_bit_len_and_anagram
  20, // num_chords
  kmap0_Plain_len6_anagram0_chords, // chords
  kmap0_Plain_len6_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len7_anagram0_chords[14] = {
 {0, 0, 9}, {0, 32, 8}, {16, 4, 0}, {0, 64, 0}, 
 {0, 1, 0}, {32, 1, 0}, {2, 0, 0}, {0, 8, 0}, 
 {0, 0, 8}, {128, 0, 0}, {32, 0, 0}, {0, 0, 130}, 
 {0, 0, 18}, {4, 8, 0}, 
};

const uint8_t kmap0_Plain_len7_anagram0_seqs[13] = {
 237, 215, 247, 57, 
 28, 93, 122, 221, 
 206, 251, 126, 251, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len7_anagram0 = {
  112, // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_Plain_len7_anagram0_chords, // chords
  kmap0_Plain_len7_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len11_anagram0_chords[3] = {
 {1, 0, 0}, {0, 16, 0}, {64, 0, 0}, 
};

const uint8_t kmap0_Plain_len11_anagram0_seqs[5] = {
 81, 133, 107, 88, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len11_anagram0 = {
  176, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Plain_len11_anagram0_chords, // chords
  kmap0_Plain_len11_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len12_anagram0_chords[1] = {
 {0, 0, 4}, 
};

const uint8_t kmap0_Plain_len12_anagram0_seqs[2] = {
 191, 10, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len12_anagram0 = {
  192, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len12_anagram0_chords, // chords
  kmap0_Plain_len12_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap0_Plain_lookups_array[6] = {
 &kmap0_Plain_len4_anagram0, &kmap0_Plain_len5_anagram0, &kmap0_Plain_len6_anagram0, &kmap0_Plain_len7_anagram0, 
 &kmap0_Plain_len11_anagram0, &kmap0_Plain_len12_anagram0, 
};

const LookupKmapType kmap0_Plain_lookups = {
  6, // num_lookups
  kmap0_Plain_lookups_array, // lookups
};

const ChordData kmap0_Macro_len18_anagram0_chords[1] = {
 {0, 128, 192}, 
};

const uint8_t kmap0_Macro_len18_anagram0_seqs[3] = {
 211, 66, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len18_anagram0 = {
  288, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len18_anagram0_chords, // chords
  kmap0_Macro_len18_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap0_Macro_lookups_array[1] = {
 &kmap0_Macro_len18_anagram0, 
};

const LookupKmapType kmap0_Macro_lookups = {
  1, // num_lookups
  kmap0_Macro_lookups_array, // lookups
};

const LookupKmapTypeLenAnagram* kmap0_Command_lookups_array[0] = {
};

const LookupKmapType kmap0_Command_lookups = {
  0, // num_lookups
  kmap0_Command_lookups_array, // lookups
};

const ChordData kmap0_Word_len14_anagram0_chords[1] = {
 {16, 32, 1}, 
};

const uint8_t kmap0_Word_len14_anagram0_seqs[2] = {
 154, 55, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len14_anagram0 = {
  224, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len14_anagram0_chords, // chords
  kmap0_Word_len14_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram0_chords[1] = {
 {146, 0, 0}, 
};

const uint8_t kmap0_Word_len22_anagram0_seqs[3] = {
 77, 41, 43, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram0 = {
  352, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len22_anagram0_chords, // chords
  kmap0_Word_len22_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len23_anagram1_chords[1] = {
 {16, 32, 1}, 
};

const uint8_t kmap0_Word_len23_anagram1_seqs[3] = {
 186, 183, 102, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len23_anagram1 = {
  369, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len23_anagram1_chords, // chords
  kmap0_Word_len23_anagram1_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap0_Word_lookups_array[3] = {
 &kmap0_Word_len14_anagram0, &kmap0_Word_len22_anagram0, &kmap0_Word_len23_anagram1, 
};

const LookupKmapType kmap0_Word_lookups = {
  3, // num_lookups
  kmap0_Word_lookups_array, // lookups
};

const LookupKmapType* kmap0_lookups_array[4] = {
 &kmap0_Plain_lookups, &kmap0_Macro_lookups, &kmap0_Command_lookups, &kmap0_Word_lookups, 
};

const KmapStruct kmap0_lookups = {
  kmap0_lookups_array, // lookups_for_kmap
};

const KmapStruct* default_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

const ChordData default_mode_mod_chord[10] = {
 {0, 0, 4}, {8, 0, 0}, {8, 128, 0}, {64, 0, 0}, 
 {1, 0, 0}, {1, 0, 0}, {0, 16, 0}, {0, 0, 4}, 
 {64, 0, 0}, {0, 16, 0}, 
};

const ChordData default_mode_anagram_mask = {8, 128, 0};

const ModeStruct default_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  default_mode_kmaps_array, // kmaps
  default_mode_mod_chord, // mod_chords
  default_mode_anagram_mask, // anagram_mask
};

const KmapStruct* gaming_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

const ChordData gaming_mode_mod_chord[10] = {
 {0, 0, 4}, {8, 0, 0}, {8, 128, 0}, {64, 0, 0}, 
 {1, 0, 0}, {1, 0, 0}, {0, 16, 0}, {0, 0, 4}, 
 {64, 0, 0}, {0, 16, 0}, 
};

const ChordData gaming_mode_anagram_mask = {8, 128, 0};

const ModeStruct gaming_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  gaming_mode_kmaps_array, // kmaps
  gaming_mode_mod_chord, // mod_chords
  gaming_mode_anagram_mask, // anagram_mask
};

const KmapStruct* left_hand_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

const ChordData left_hand_mode_mod_chord[10] = {
 {0, 0, 4}, {8, 0, 0}, {8, 128, 0}, {64, 0, 0}, 
 {1, 0, 0}, {1, 0, 0}, {0, 16, 0}, {0, 0, 4}, 
 {64, 0, 0}, {0, 16, 0}, 
};

const ChordData left_hand_mode_anagram_mask = {8, 128, 0};

const ModeStruct left_hand_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  left_hand_mode_kmaps_array, // kmaps
  left_hand_mode_mod_chord, // mod_chords
  left_hand_mode_anagram_mask, // anagram_mask
};

const KmapStruct* windows_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

const ChordData windows_mode_mod_chord[10] = {
 {0, 0, 4}, {8, 0, 0}, {8, 128, 0}, {64, 0, 0}, 
 {1, 0, 0}, {1, 0, 0}, {0, 16, 0}, {0, 0, 4}, 
 {64, 0, 0}, {0, 16, 0}, 
};

const ChordData windows_mode_anagram_mask = {8, 128, 0};

const ModeStruct windows_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  windows_mode_kmaps_array, // kmaps
  windows_mode_mod_chord, // mod_chords
  windows_mode_anagram_mask, // anagram_mask
};

const ModeStruct* mode_structs[4] = {
 &default_mode_struct, &gaming_mode_struct, &left_hand_mode_struct, &windows_mode_struct, 
};


} // end namespace conf
