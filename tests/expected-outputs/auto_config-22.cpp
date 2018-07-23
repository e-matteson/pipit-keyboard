#include "auto_config-22.h"
namespace conf {
const uint8_t row_pins_0[] = {
 1, 0, 19, 
};

const uint8_t* row_pins[] = {
 row_pins_0, 
};

const uint8_t column_pins_0[] = {
 15, 16, 17, 18, 
 20, 21, 5, 6, 
};

const uint8_t* column_pins[] = {
 column_pins_0, 
};

const uint8_t rgb_led_pins[] = {
 10, 11, 12, 
};

const uint8_t battery_level_pin = 9;

const HuffmanChar huffman_lookup[] = {
 {
  19, // bits
  5, // num_bits
  (BLANK_KEY)&0xff, // key_code
  0, // is_mod
}, {
  45, // bits
  7, // num_bits
  (COMMAND_CYCLE_CAPITAL)&0xff, // key_code
  0, // is_mod
}, {
  109, // bits
  7, // num_bits
  (COMMAND_CYCLE_NOSPACE)&0xff, // key_code
  0, // is_mod
}, {
  87, // bits
  7, // num_bits
  (COMMAND_CYCLE_WORD)&0xff, // key_code
  0, // is_mod
}, 
 {
  11, // bits
  7, // num_bits
  (COMMAND_DEFAULT_MODE)&0xff, // key_code
  0, // is_mod
}, {
  14, // bits
  6, // num_bits
  (COMMAND_DELETE_WORD)&0xff, // key_code
  0, // is_mod
}, {
  6, // bits
  6, // num_bits
  (COMMAND_GAMING_MODE)&0xff, // key_code
  0, // is_mod
}, {
  50, // bits
  6, // num_bits
  (COMMAND_LED_BATTERY)&0xff, // key_code
  0, // is_mod
}, 
 {
  1, // bits
  6, // num_bits
  (COMMAND_LED_COLORS)&0xff, // key_code
  0, // is_mod
}, {
  52, // bits
  6, // num_bits
  (COMMAND_LED_RAINBOW)&0xff, // key_code
  0, // is_mod
}, {
  75, // bits
  7, // num_bits
  (COMMAND_LEFT_HAND_MODE)&0xff, // key_code
  0, // is_mod
}, {
  79, // bits
  7, // num_bits
  (COMMAND_LEFT_LIMIT)&0xff, // key_code
  0, // is_mod
}, 
 {
  46, // bits
  6, // num_bits
  (COMMAND_LEFT_WORD)&0xff, // key_code
  0, // is_mod
}, {
  95, // bits
  7, // num_bits
  (COMMAND_PAUSE)&0xff, // key_code
  0, // is_mod
}, {
  38, // bits
  6, // num_bits
  (COMMAND_RIGHT_LIMIT)&0xff, // key_code
  0, // is_mod
}, {
  12, // bits
  6, // num_bits
  (COMMAND_RIGHT_WORD)&0xff, // key_code
  0, // is_mod
}, 
 {
  44, // bits
  6, // num_bits
  (COMMAND_SHORTEN_LAST_WORD)&0xff, // key_code
  0, // is_mod
}, {
  36, // bits
  6, // num_bits
  (COMMAND_STICKY_ALT)&0xff, // key_code
  0, // is_mod
}, {
  33, // bits
  6, // num_bits
  (COMMAND_STICKY_CTRL)&0xff, // key_code
  0, // is_mod
}, {
  43, // bits
  7, // num_bits
  (COMMAND_STICKY_GUI)&0xff, // key_code
  0, // is_mod
}, 
 {
  24, // bits
  6, // num_bits
  (COMMAND_STICKY_SHIFT)&0xff, // key_code
  0, // is_mod
}, {
  47, // bits
  7, // num_bits
  (COMMAND_WINDOWS_MODE)&0xff, // key_code
  0, // is_mod
}, {
  55, // bits
  7, // num_bits
  (KEY_0)&0xff, // key_code
  0, // is_mod
}, {
  7, // bits
  6, // num_bits
  (KEY_1)&0xff, // key_code
  0, // is_mod
}, 
 {
  63, // bits
  7, // num_bits
  (KEY_2)&0xff, // key_code
  0, // is_mod
}, {
  21, // bits
  5, // num_bits
  (KEY_3)&0xff, // key_code
  0, // is_mod
}, {
  30, // bits
  6, // num_bits
  (KEY_4)&0xff, // key_code
  0, // is_mod
}, {
  49, // bits
  6, // num_bits
  (KEY_5)&0xff, // key_code
  0, // is_mod
}, 
 {
  16, // bits
  6, // num_bits
  (KEY_6)&0xff, // key_code
  0, // is_mod
}, {
  26, // bits
  5, // num_bits
  (KEY_7)&0xff, // key_code
  0, // is_mod
}, {
  3, // bits
  7, // num_bits
  (KEY_8)&0xff, // key_code
  0, // is_mod
}, {
  22, // bits
  6, // num_bits
  (KEY_9)&0xff, // key_code
  0, // is_mod
}, 
 {
  54, // bits
  6, // num_bits
  (KEY_A)&0xff, // key_code
  0, // is_mod
}, {
  34, // bits
  6, // num_bits
  (KEY_B)&0xff, // key_code
  0, // is_mod
}, {
  2, // bits
  6, // num_bits
  (KEY_BACKSPACE)&0xff, // key_code
  0, // is_mod
}, {
  37, // bits
  6, // num_bits
  (KEY_C)&0xff, // key_code
  0, // is_mod
}, 
 {
  5, // bits
  6, // num_bits
  (KEY_D)&0xff, // key_code
  0, // is_mod
}, {
  27, // bits
  5, // num_bits
  (KEY_E)&0xff, // key_code
  0, // is_mod
}, {
  4, // bits
  6, // num_bits
  (KEY_ENTER)&0xff, // key_code
  0, // is_mod
}, {
  18, // bits
  6, // num_bits
  (KEY_F)&0xff, // key_code
  0, // is_mod
}, 
 {
  107, // bits
  7, // num_bits
  (KEY_G)&0xff, // key_code
  0, // is_mod
}, {
  29, // bits
  5, // num_bits
  (KEY_H)&0xff, // key_code
  0, // is_mod
}, {
  56, // bits
  6, // num_bits
  (KEY_I)&0xff, // key_code
  0, // is_mod
}, {
  20, // bits
  6, // num_bits
  (KEY_J)&0xff, // key_code
  0, // is_mod
}, 
 {
  111, // bits
  7, // num_bits
  (KEY_K)&0xff, // key_code
  0, // is_mod
}, {
  10, // bits
  5, // num_bits
  (KEY_L)&0xff, // key_code
  0, // is_mod
}, {
  119, // bits
  7, // num_bits
  (KEY_M)&0xff, // key_code
  0, // is_mod
}, {
  103, // bits
  7, // num_bits
  (KEY_N)&0xff, // key_code
  0, // is_mod
}, 
 {
  23, // bits
  7, // num_bits
  (KEY_O)&0xff, // key_code
  0, // is_mod
}, {
  39, // bits
  7, // num_bits
  (KEY_P)&0xff, // key_code
  0, // is_mod
}, {
  127, // bits
  7, // num_bits
  (KEY_Q)&0xff, // key_code
  0, // is_mod
}, {
  15, // bits
  7, // num_bits
  (KEY_R)&0xff, // key_code
  0, // is_mod
}, 
 {
  28, // bits
  5, // num_bits
  (KEY_S)&0xff, // key_code
  0, // is_mod
}, {
  62, // bits
  6, // num_bits
  (KEY_SPACE)&0xff, // key_code
  0, // is_mod
}, {
  9, // bits
  4, // num_bits
  (KEY_T)&0xff, // key_code
  0, // is_mod
}, {
  40, // bits
  6, // num_bits
  (KEY_TAB)&0xff, // key_code
  0, // is_mod
}, 
 {
  8, // bits
  6, // num_bits
  (KEY_U)&0xff, // key_code
  0, // is_mod
}, {
  17, // bits
  6, // num_bits
  (KEY_V)&0xff, // key_code
  0, // is_mod
}, {
  48, // bits
  6, // num_bits
  (KEY_W)&0xff, // key_code
  0, // is_mod
}, {
  99, // bits
  7, // num_bits
  (KEY_X)&0xff, // key_code
  0, // is_mod
}, 
 {
  31, // bits
  7, // num_bits
  (KEY_Y)&0xff, // key_code
  0, // is_mod
}, {
  35, // bits
  7, // num_bits
  (KEY_Z)&0xff, // key_code
  0, // is_mod
}, {
  67, // bits
  7, // num_bits
  (MODIFIERKEY_ALT)&0xff, // key_code
  1, // is_mod
}, {
  13, // bits
  6, // num_bits
  (MODIFIERKEY_CTRL)&0xff, // key_code
  1, // is_mod
}, 
 {
  32, // bits
  6, // num_bits
  (MODIFIERKEY_GUI)&0xff, // key_code
  1, // is_mod
}, {
  0, // bits
  6, // num_bits
  (MODIFIERKEY_SHIFT)&0xff, // key_code
  1, // is_mod
}, 
};

const mod_enum word_mod_indices[] = {
 MOD_CAPITAL_ENUM, MOD_NOSPACE_ENUM, MOD_DOUBLE_ENUM, MOD_SHORTEN_ENUM, 
};

const mod_enum plain_mod_indices[] = {
 MOD_ALT_ENUM, MOD_CTRL_ENUM, MOD_GUI_ENUM, MOD_SHIFT_ENUM, 
};

const mod_enum anagram_mod_indices[] = {
 MOD_ANAGRAM_1_ENUM, MOD_ANAGRAM_2_ENUM, 
};

const uint8_t plain_mod_keys[] = {
 (MODIFIERKEY_ALT)&0xff, (MODIFIERKEY_CTRL)&0xff, (MODIFIERKEY_GUI)&0xff, (MODIFIERKEY_SHIFT)&0xff, 
};

const uint8_t kmap0_plain_len4_anagram0_chords[] = {
 0, 0, 1, 
};

const uint8_t kmap0_plain_len4_anagram0_seqs[] = {
 9, 
};

const LookupOfLength kmap0_plain_len4_anagram0 = {
  64, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_plain_len4_anagram0_chords, // chords
  kmap0_plain_len4_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len5_anagram0_chords[] = {
 144, 0, 0, 130, 
 0, 0, 16, 0, 
 0, 0, 32, 0, 
 0, 0, 128, 0, 
 0, 64, 
};

const uint8_t kmap0_plain_len5_anagram0_seqs[] = {
 85, 239, 174, 56, 
};

const LookupOfLength kmap0_plain_len5_anagram0 = {
  80, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_plain_len5_anagram0_chords, // chords
  kmap0_plain_len5_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len6_anagram0_chords[] = {
 18, 0, 0, 0, 
 0, 72, 128, 4, 
 0, 0, 32, 8, 
 16, 4, 0, 0, 
 4, 0, 36, 0, 
 0, 8, 0, 0, 
 0, 0, 2, 0, 
 64, 0, 0, 1, 
 0, 2, 0, 0, 
 0, 0, 144, 0, 
 128, 0, 32, 0, 
 0, 32, 8, 0, 
 0, 64, 2, 
};

const uint8_t kmap0_plain_len6_anagram0_seqs[] = {
 135, 23, 67, 150, 
 45, 10, 101, 33, 
 225, 148, 143, 68, 
 48, 
};

const LookupOfLength kmap0_plain_len6_anagram0 = {
  96, // seq_bit_len_and_anagram
  17, // num_chords
  kmap0_plain_len6_anagram0_chords, // chords
  kmap0_plain_len6_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len7_anagram0_chords[] = {
 0, 32, 1, 0, 
 0, 9, 0, 0, 
 65, 32, 1, 0, 
 0, 9, 0, 0, 
 8, 0, 0, 0, 
 8, 128, 0, 0, 
 4, 0, 0, 0, 
 64, 128, 0, 0, 
 16, 0, 0, 130, 
 0, 0, 18, 4, 
 8, 0, 
};

const uint8_t kmap0_plain_len7_anagram0_seqs[] = {
 183, 223, 96, 253, 
 190, 159, 47, 167, 
 255, 99, 252, 25, 
 1, 
};

const LookupOfLength kmap0_plain_len7_anagram0 = {
  112, // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_plain_len7_anagram0_chords, // chords
  kmap0_plain_len7_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len11_anagram0_chords[] = {
 1, 0, 0, 0, 
 16, 0, 64, 0, 
 0, 
};

const uint8_t kmap0_plain_len11_anagram0_seqs[] = {
 205, 4, 39, 48, 
 1, 
};

const LookupOfLength kmap0_plain_len11_anagram0 = {
  176, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_plain_len11_anagram0_chords, // chords
  kmap0_plain_len11_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len12_anagram0_chords[] = {
 0, 0, 4, 
};

const uint8_t kmap0_plain_len12_anagram0_seqs[] = {
 195, 9, 
};

const LookupOfLength kmap0_plain_len12_anagram0 = {
  192, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_plain_len12_anagram0_chords, // chords
  kmap0_plain_len12_anagram0_seqs, // sequences
};

const LookupOfLength* kmap0_plain_lookups_array[] = {
 &kmap0_plain_len4_anagram0, &kmap0_plain_len5_anagram0, &kmap0_plain_len6_anagram0, &kmap0_plain_len7_anagram0, 
 &kmap0_plain_len11_anagram0, &kmap0_plain_len12_anagram0, 
};

const LookupsOfSeqType kmap0_plain_lookups = {
  6, // num_lookups
  kmap0_plain_lookups_array, // lookups
};

const uint8_t kmap0_macro_len16_anagram0_chords[] = {
 0, 128, 192, 
};

const uint8_t kmap0_macro_len16_anagram0_seqs[] = {
 138, 19, 
};

const LookupOfLength kmap0_macro_len16_anagram0 = {
  256, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len16_anagram0_chords, // chords
  kmap0_macro_len16_anagram0_seqs, // sequences
};

const LookupOfLength* kmap0_macro_lookups_array[] = {
 &kmap0_macro_len16_anagram0, 
};

const LookupsOfSeqType kmap0_macro_lookups = {
  1, // num_lookups
  kmap0_macro_lookups_array, // lookups
};

const LookupOfLength* kmap0_command_lookups_array[] = {
};

const LookupsOfSeqType kmap0_command_lookups = {
  0, // num_lookups
  kmap0_command_lookups_array, // lookups
};

const uint8_t kmap0_word_len14_anagram0_chords[] = {
 16, 32, 1, 
};

const uint8_t kmap0_word_len14_anagram0_seqs[] = {
 217, 55, 
};

const LookupOfLength kmap0_word_len14_anagram0 = {
  224, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len14_anagram0_chords, // chords
  kmap0_word_len14_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len21_anagram0_chords[] = {
 146, 0, 0, 
};

const uint8_t kmap0_word_len21_anagram0_seqs[] = {
 71, 173, 26, 
};

const LookupOfLength kmap0_word_len21_anagram0 = {
  336, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len21_anagram0_chords, // chords
  kmap0_word_len21_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len23_anagram1_chords[] = {
 16, 32, 1, 
};

const uint8_t kmap0_word_len23_anagram1_seqs[] = {
 185, 119, 118, 
};

const LookupOfLength kmap0_word_len23_anagram1 = {
  369, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len23_anagram1_chords, // chords
  kmap0_word_len23_anagram1_seqs, // sequences
};

const LookupOfLength* kmap0_word_lookups_array[] = {
 &kmap0_word_len14_anagram0, &kmap0_word_len21_anagram0, &kmap0_word_len23_anagram1, 
};

const LookupsOfSeqType kmap0_word_lookups = {
  3, // num_lookups
  kmap0_word_lookups_array, // lookups
};

const LookupsOfSeqType* kmap0_lookups_array[] = {
 &kmap0_plain_lookups, &kmap0_macro_lookups, &kmap0_command_lookups, &kmap0_word_lookups, 
};

const KmapStruct kmap0_lookups = {
  kmap0_lookups_array, // lookups_by_seq_type
};

const KmapStruct* default_mode_kmaps_array[] = {
 &kmap0_lookups, 
};

const uint8_t default_mode_mod_chord_0[] = {
 0, 0, 4, 
};

const uint8_t default_mode_mod_chord_1[] = {
 8, 0, 0, 
};

const uint8_t default_mode_mod_chord_2[] = {
 8, 128, 0, 
};

const uint8_t default_mode_mod_chord_3[] = {
 64, 0, 0, 
};

const uint8_t default_mode_mod_chord_4[] = {
 1, 0, 0, 
};

const uint8_t default_mode_mod_chord_5[] = {
 1, 0, 0, 
};

const uint8_t default_mode_mod_chord_6[] = {
 0, 16, 0, 
};

const uint8_t default_mode_mod_chord_7[] = {
 0, 0, 4, 
};

const uint8_t default_mode_mod_chord_8[] = {
 64, 0, 0, 
};

const uint8_t default_mode_mod_chord_9[] = {
 0, 16, 0, 
};

const uint8_t* default_mode_mod_chord[] = {
 default_mode_mod_chord_0, default_mode_mod_chord_1, default_mode_mod_chord_2, default_mode_mod_chord_3, 
 default_mode_mod_chord_4, default_mode_mod_chord_5, default_mode_mod_chord_6, default_mode_mod_chord_7, 
 default_mode_mod_chord_8, default_mode_mod_chord_9, 
};

const uint8_t default_mode_anagram_mask[] = {
 8, 128, 0, 
};

const ModeStruct default_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  default_mode_kmaps_array, // kmaps
  default_mode_mod_chord, // mod_chords
  default_mode_anagram_mask, // anagram_mask
};

const KmapStruct* gaming_mode_kmaps_array[] = {
 &kmap0_lookups, 
};

const uint8_t gaming_mode_mod_chord_0[] = {
 0, 0, 4, 
};

const uint8_t gaming_mode_mod_chord_1[] = {
 8, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_2[] = {
 8, 128, 0, 
};

const uint8_t gaming_mode_mod_chord_3[] = {
 64, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_4[] = {
 1, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_5[] = {
 1, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_6[] = {
 0, 16, 0, 
};

const uint8_t gaming_mode_mod_chord_7[] = {
 0, 0, 4, 
};

const uint8_t gaming_mode_mod_chord_8[] = {
 64, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_9[] = {
 0, 16, 0, 
};

const uint8_t* gaming_mode_mod_chord[] = {
 gaming_mode_mod_chord_0, gaming_mode_mod_chord_1, gaming_mode_mod_chord_2, gaming_mode_mod_chord_3, 
 gaming_mode_mod_chord_4, gaming_mode_mod_chord_5, gaming_mode_mod_chord_6, gaming_mode_mod_chord_7, 
 gaming_mode_mod_chord_8, gaming_mode_mod_chord_9, 
};

const uint8_t gaming_mode_anagram_mask[] = {
 8, 128, 0, 
};

const ModeStruct gaming_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  gaming_mode_kmaps_array, // kmaps
  gaming_mode_mod_chord, // mod_chords
  gaming_mode_anagram_mask, // anagram_mask
};

const KmapStruct* left_hand_mode_kmaps_array[] = {
 &kmap0_lookups, 
};

const uint8_t left_hand_mode_mod_chord_0[] = {
 0, 0, 4, 
};

const uint8_t left_hand_mode_mod_chord_1[] = {
 8, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_2[] = {
 8, 128, 0, 
};

const uint8_t left_hand_mode_mod_chord_3[] = {
 64, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_4[] = {
 1, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_5[] = {
 1, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_6[] = {
 0, 16, 0, 
};

const uint8_t left_hand_mode_mod_chord_7[] = {
 0, 0, 4, 
};

const uint8_t left_hand_mode_mod_chord_8[] = {
 64, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_9[] = {
 0, 16, 0, 
};

const uint8_t* left_hand_mode_mod_chord[] = {
 left_hand_mode_mod_chord_0, left_hand_mode_mod_chord_1, left_hand_mode_mod_chord_2, left_hand_mode_mod_chord_3, 
 left_hand_mode_mod_chord_4, left_hand_mode_mod_chord_5, left_hand_mode_mod_chord_6, left_hand_mode_mod_chord_7, 
 left_hand_mode_mod_chord_8, left_hand_mode_mod_chord_9, 
};

const uint8_t left_hand_mode_anagram_mask[] = {
 8, 128, 0, 
};

const ModeStruct left_hand_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  left_hand_mode_kmaps_array, // kmaps
  left_hand_mode_mod_chord, // mod_chords
  left_hand_mode_anagram_mask, // anagram_mask
};

const KmapStruct* windows_mode_kmaps_array[] = {
 &kmap0_lookups, 
};

const uint8_t windows_mode_mod_chord_0[] = {
 0, 0, 4, 
};

const uint8_t windows_mode_mod_chord_1[] = {
 8, 0, 0, 
};

const uint8_t windows_mode_mod_chord_2[] = {
 8, 128, 0, 
};

const uint8_t windows_mode_mod_chord_3[] = {
 64, 0, 0, 
};

const uint8_t windows_mode_mod_chord_4[] = {
 1, 0, 0, 
};

const uint8_t windows_mode_mod_chord_5[] = {
 1, 0, 0, 
};

const uint8_t windows_mode_mod_chord_6[] = {
 0, 16, 0, 
};

const uint8_t windows_mode_mod_chord_7[] = {
 0, 0, 4, 
};

const uint8_t windows_mode_mod_chord_8[] = {
 64, 0, 0, 
};

const uint8_t windows_mode_mod_chord_9[] = {
 0, 16, 0, 
};

const uint8_t* windows_mode_mod_chord[] = {
 windows_mode_mod_chord_0, windows_mode_mod_chord_1, windows_mode_mod_chord_2, windows_mode_mod_chord_3, 
 windows_mode_mod_chord_4, windows_mode_mod_chord_5, windows_mode_mod_chord_6, windows_mode_mod_chord_7, 
 windows_mode_mod_chord_8, windows_mode_mod_chord_9, 
};

const uint8_t windows_mode_anagram_mask[] = {
 8, 128, 0, 
};

const ModeStruct windows_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  windows_mode_kmaps_array, // kmaps
  windows_mode_mod_chord, // mod_chords
  windows_mode_anagram_mask, // anagram_mask
};

const ModeStruct* mode_structs[] = {
 &default_mode_struct, &gaming_mode_struct, &left_hand_mode_struct, &windows_mode_struct, 
};


} // end namespace conf
