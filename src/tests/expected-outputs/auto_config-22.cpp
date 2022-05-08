#include "auto_config-22.h"
namespace conf {
const std::array<uint8_t,3> row_pins = {
 1, 0, 19, 
};
const std::array<uint8_t,8> column_pins = {
 15, 16, 17, 18, 
 20, 21, 5, 6, 
};
const std::array<uint8_t,3> rgb_led_pins = {
 10, 11, 12, 
};
HuffmanChar const huffman_lookup[73] = {
 {
  HuffmanBits({2}), // bits
  4, // num_bits
  static_cast<uint8_t>(0 /* blank key, when a keypress contains only modifiers and no key */), // key_code
  0, // is_mod
}, {
  HuffmanBits({0}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_T), // key_code
  0, // is_mod
}, {
  HuffmanBits({27}), // bits
  5, // num_bits
  static_cast<uint8_t>(Command::command_switch_to), // key_code
  0, // is_mod
}, {
  HuffmanBits({17}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_3), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({25}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_E), // key_code
  0, // is_mod
}, {
  HuffmanBits({9}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_H), // key_code
  0, // is_mod
}, {
  HuffmanBits({10}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_S), // key_code
  0, // is_mod
}, {
  HuffmanBits({12}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_delete_word), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({22}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_led_colors), // key_code
  0, // is_mod
}, {
  HuffmanBits({8}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_led_rainbow), // key_code
  0, // is_mod
}, {
  HuffmanBits({40}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_left_limit), // key_code
  0, // is_mod
}, {
  HuffmanBits({4}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_left_word), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({44}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_pan_left), // key_code
  0, // is_mod
}, {
  HuffmanBits({54}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_right_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({56}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_shorten_last_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({36}), // bits
  6, // num_bits
  static_cast<uint8_t>(Command::command_sticky_gui), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({30}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_0), // key_code
  0, // is_mod
}, {
  HuffmanBits({3}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_1), // key_code
  0, // is_mod
}, {
  HuffmanBits({6}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_5), // key_code
  0, // is_mod
}, {
  HuffmanBits({26}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_6), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({43}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_7), // key_code
  0, // is_mod
}, {
  HuffmanBits({52}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_A), // key_code
  0, // is_mod
}, {
  HuffmanBits({20}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_B), // key_code
  0, // is_mod
}, {
  HuffmanBits({24}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_BACKSPACE), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({28}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_I), // key_code
  0, // is_mod
}, {
  HuffmanBits({60}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_J), // key_code
  0, // is_mod
}, {
  HuffmanBits({15}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_L), // key_code
  0, // is_mod
}, {
  HuffmanBits({62}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_P), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({14}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_Q), // key_code
  0, // is_mod
}, {
  HuffmanBits({46}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_R), // key_code
  0, // is_mod
}, {
  HuffmanBits({38}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_X), // key_code
  0, // is_mod
}, {
  HuffmanBits({1}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_Y), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({58}), // bits
  6, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_ALT), // key_code
  1, // is_mod
}, {
  HuffmanBits({33}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_cycle_capital), // key_code
  0, // is_mod
}, {
  HuffmanBits({97}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_cycle_nospace), // key_code
  0, // is_mod
}, {
  HuffmanBits({99}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_cycle_word), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({7}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_led_battery), // key_code
  0, // is_mod
}, {
  HuffmanBits({115}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_pan_right), // key_code
  0, // is_mod
}, {
  HuffmanBits({71}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_pause), // key_code
  0, // is_mod
}, {
  HuffmanBits({85}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_right_limit), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({47}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_scroll_down), // key_code
  0, // is_mod
}, {
  HuffmanBits({111}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_scroll_up), // key_code
  0, // is_mod
}, {
  HuffmanBits({55}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_sticky_alt), // key_code
  0, // is_mod
}, {
  HuffmanBits({23}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_sticky_ctrl), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({29}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_sticky_shift), // key_code
  0, // is_mod
}, {
  HuffmanBits({95}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_toggle_wireless), // key_code
  0, // is_mod
}, {
  HuffmanBits({63}), // bits
  7, // num_bits
  static_cast<uint8_t>(Command::command_windows_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({75}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_2), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({103}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_4), // key_code
  0, // is_mod
}, {
  HuffmanBits({83}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_8), // key_code
  0, // is_mod
}, {
  HuffmanBits({19}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_9), // key_code
  0, // is_mod
}, {
  HuffmanBits({119}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_C), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({87}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_D), // key_code
  0, // is_mod
}, {
  HuffmanBits({125}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_ENTER), // key_code
  0, // is_mod
}, {
  HuffmanBits({61}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_F), // key_code
  0, // is_mod
}, {
  HuffmanBits({93}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_G), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({35}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_K), // key_code
  0, // is_mod
}, {
  HuffmanBits({31}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_M), // key_code
  0, // is_mod
}, {
  HuffmanBits({127}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_N), // key_code
  0, // is_mod
}, {
  HuffmanBits({51}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_O), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({45}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_SPACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({11}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_TAB), // key_code
  0, // is_mod
}, {
  HuffmanBits({53}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_U), // key_code
  0, // is_mod
}, {
  HuffmanBits({37}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_V), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({13}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_W), // key_code
  0, // is_mod
}, {
  HuffmanBits({109}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_Z), // key_code
  0, // is_mod
}, {
  HuffmanBits({21}), // bits
  7, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_CTRL), // key_code
  1, // is_mod
}, {
  HuffmanBits({117}), // bits
  7, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_GUI), // key_code
  1, // is_mod
}, 
 {
  HuffmanBits({101}), // bits
  7, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_SHIFT), // key_code
  1, // is_mod
}, {
  HuffmanBits({39}), // bits
  7, // num_bits
  static_cast<uint8_t>(Mode::default_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({77}), // bits
  7, // num_bits
  static_cast<uint8_t>(Mode::gaming_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({69}), // bits
  7, // num_bits
  static_cast<uint8_t>(Mode::left_hand_mode), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({5}), // bits
  7, // num_bits
  static_cast<uint8_t>(Mode::windows_mode), // key_code
  0, // is_mod
}, 
};

const std::array<Mod,4> word_mods = {
 Mod::mod_capital, Mod::mod_nospace, Mod::mod_double, Mod::mod_shorten, 
};
const std::array<Mod,4> plain_mods = {
 Mod::mod_alt, Mod::mod_ctrl, Mod::mod_gui, Mod::mod_shift, 
};
const std::array<Mod,2> anagram_mods = {
 Mod::mod_anagram_1, Mod::mod_anagram_2, 
};
const std::array<uint8_t,2> anagram_mod_numbers = {
 1, 2, 
};
const std::array<uint8_t,4> plain_mod_keys = {
 static_cast<uint8_t>(MODIFIERKEY_ALT), static_cast<uint8_t>(MODIFIERKEY_CTRL), static_cast<uint8_t>(MODIFIERKEY_GUI), static_cast<uint8_t>(MODIFIERKEY_SHIFT), 
};
ChordData const kmap0_Plain_len4_anagram0_chords[1] = {
 ChordData({0, 0, 1}), 
};

uint8_t const kmap0_Plain_len4_anagram0_seqs[1] = {
 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len4_anagram0 = {
  LengthAndAnagram(4, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len4_anagram0_chords, // chords
  kmap0_Plain_len4_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len5_anagram0_chords[4] = {
 ChordData({0, 0, 64}), ChordData({0, 32, 0}), ChordData({16, 0, 0}), ChordData({144, 0, 0}), 
};

uint8_t const kmap0_Plain_len5_anagram0_seqs[3] = {
 42, 229, 8, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len5_anagram0 = {
  LengthAndAnagram(5, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Plain_len5_anagram0_chords, // chords
  kmap0_Plain_len5_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len6_anagram0_chords[16] = {
 ChordData({0, 0, 16}), ChordData({0, 0, 18}), ChordData({0, 0, 128}), ChordData({0, 0, 130}), 
 ChordData({0, 0, 144}), ChordData({0, 4, 0}), ChordData({0, 32, 1}), ChordData({0, 32, 8}), 
 ChordData({0, 64, 128}), ChordData({2, 0, 0}), ChordData({4, 0, 0}), ChordData({8, 0, 0}), 
 ChordData({18, 0, 0}), ChordData({36, 0, 0}), ChordData({128, 4, 0}), ChordData({130, 0, 0}), 
};

uint8_t const kmap0_Plain_len6_anagram0_seqs[12] = {
 110, 240, 152, 60, 
 237, 105, 14, 231, 
 99, 3, 101, 172, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len6_anagram0 = {
  LengthAndAnagram(6, 0), // seq_bit_len_and_anagram
  16, // num_chords
  kmap0_Plain_len6_anagram0_chords, // chords
  kmap0_Plain_len6_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len7_anagram0_chords[17] = {
 ChordData({0, 0, 2}), ChordData({0, 0, 8}), ChordData({0, 0, 9}), ChordData({0, 0, 65}), 
 ChordData({0, 0, 72}), ChordData({0, 1, 0}), ChordData({0, 8, 0}), ChordData({0, 9, 0}), 
 ChordData({0, 64, 0}), ChordData({0, 64, 2}), ChordData({0, 128, 0}), ChordData({4, 8, 0}), 
 ChordData({16, 4, 0}), ChordData({32, 0, 0}), ChordData({32, 1, 0}), ChordData({32, 8, 0}), 
 ChordData({128, 0, 0}), 
};

uint8_t const kmap0_Plain_len7_anagram0_seqs[15] = {
 247, 255, 114, 122, 
 238, 125, 70, 215, 
 70, 171, 61, 169, 
 117, 75, 51, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  17, // num_chords
  kmap0_Plain_len7_anagram0_chords, // chords
  kmap0_Plain_len7_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len10_anagram0_chords[1] = {
 ChordData({0, 0, 4}), 
};

uint8_t const kmap0_Plain_len10_anagram0_seqs[2] = {
 186, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len10_anagram0 = {
  LengthAndAnagram(10, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len10_anagram0_chords, // chords
  kmap0_Plain_len10_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len11_anagram0_chords[3] = {
 ChordData({0, 16, 0}), ChordData({1, 0, 0}), ChordData({64, 0, 0}), 
};

uint8_t const kmap0_Plain_len11_anagram0_seqs[5] = {
 117, 169, 72, 89, 
 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Plain_len11_anagram0_chords, // chords
  kmap0_Plain_len11_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap0_Plain_lookups_array[6] = {
 &kmap0_Plain_len4_anagram0, &kmap0_Plain_len5_anagram0, &kmap0_Plain_len6_anagram0, &kmap0_Plain_len7_anagram0, 
 &kmap0_Plain_len10_anagram0, &kmap0_Plain_len11_anagram0, 
};

LookupKmapType const kmap0_Plain_lookups = {
  6, // num_lookups
  kmap0_Plain_lookups_array, // lookups
};

ChordData const kmap0_Macro_len18_anagram0_chords[1] = {
 ChordData({0, 128, 192}), 
};

uint8_t const kmap0_Macro_len18_anagram0_seqs[3] = {
 143, 234, 3, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len18_anagram0_chords, // chords
  kmap0_Macro_len18_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap0_Macro_lookups_array[1] = {
 &kmap0_Macro_len18_anagram0, 
};

LookupKmapType const kmap0_Macro_lookups = {
  1, // num_lookups
  kmap0_Macro_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap0_Command_lookups_array[0] = {
};

LookupKmapType const kmap0_Command_lookups = {
  0, // num_lookups
  kmap0_Command_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap0_Word_lookups_array[0] = {
};

LookupKmapType const kmap0_Word_lookups = {
  0, // num_lookups
  kmap0_Word_lookups_array, // lookups
};

LookupKmapType const* const kmap0_lookups_array[4] = {
 &kmap0_Plain_lookups, &kmap0_Macro_lookups, &kmap0_Command_lookups, &kmap0_Word_lookups, 
};

KmapStruct const kmap0_lookups = {
  kmap0_lookups_array, // lookups_for_kmap
};

LookupKmapTypeLenAnagram const* const kmap1_Plain_lookups_array[0] = {
};

LookupKmapType const kmap1_Plain_lookups = {
  0, // num_lookups
  kmap1_Plain_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap1_Macro_lookups_array[0] = {
};

LookupKmapType const kmap1_Macro_lookups = {
  0, // num_lookups
  kmap1_Macro_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap1_Command_lookups_array[0] = {
};

LookupKmapType const kmap1_Command_lookups = {
  0, // num_lookups
  kmap1_Command_lookups_array, // lookups
};

ChordData const kmap1_Word_len14_anagram0_chords[1] = {
 ChordData({16, 32, 1}), 
};

uint8_t const kmap1_Word_len14_anagram0_seqs[2] = {
 144, 50, 
};

LookupKmapTypeLenAnagram const kmap1_Word_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Word_len14_anagram0_chords, // chords
  kmap1_Word_len14_anagram0_seqs, // sequences
};

ChordData const kmap1_Word_len22_anagram0_chords[1] = {
 ChordData({146, 0, 0}), 
};

uint8_t const kmap1_Word_len22_anagram0_seqs[3] = {
 67, 140, 43, 
};

LookupKmapTypeLenAnagram const kmap1_Word_len22_anagram0 = {
  LengthAndAnagram(22, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Word_len22_anagram0_chords, // chords
  kmap1_Word_len22_anagram0_seqs, // sequences
};

ChordData const kmap1_Word_len23_anagram1_chords[1] = {
 ChordData({16, 32, 1}), 
};

uint8_t const kmap1_Word_len23_anagram1_seqs[3] = {
 144, 51, 36, 
};

LookupKmapTypeLenAnagram const kmap1_Word_len23_anagram1 = {
  LengthAndAnagram(23, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Word_len23_anagram1_chords, // chords
  kmap1_Word_len23_anagram1_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap1_Word_lookups_array[3] = {
 &kmap1_Word_len14_anagram0, &kmap1_Word_len22_anagram0, &kmap1_Word_len23_anagram1, 
};

LookupKmapType const kmap1_Word_lookups = {
  3, // num_lookups
  kmap1_Word_lookups_array, // lookups
};

LookupKmapType const* const kmap1_lookups_array[4] = {
 &kmap1_Plain_lookups, &kmap1_Macro_lookups, &kmap1_Command_lookups, &kmap1_Word_lookups, 
};

KmapStruct const kmap1_lookups = {
  kmap1_lookups_array, // lookups_for_kmap
};

KmapStruct const* const default_mode_kmaps_array[2] = {
 &kmap1_lookups, &kmap0_lookups, 
};

ChordData const default_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

ChordData const default_mode_anagram_mask = ChordData({8, 128, 0});

ModeStruct const default_mode_struct = {
  0, // is_gaming
  2, // num_kmaps
  default_mode_kmaps_array, // kmaps
  default_mode_mod_chord, // mod_chords
  default_mode_anagram_mask, // anagram_mask
};

KmapStruct const* const gaming_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

ChordData const gaming_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

ChordData const gaming_mode_anagram_mask = ChordData({8, 128, 0});

ModeStruct const gaming_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  gaming_mode_kmaps_array, // kmaps
  gaming_mode_mod_chord, // mod_chords
  gaming_mode_anagram_mask, // anagram_mask
};

KmapStruct const* const left_hand_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

ChordData const left_hand_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

ChordData const left_hand_mode_anagram_mask = ChordData({8, 128, 0});

ModeStruct const left_hand_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  left_hand_mode_kmaps_array, // kmaps
  left_hand_mode_mod_chord, // mod_chords
  left_hand_mode_anagram_mask, // anagram_mask
};

KmapStruct const* const windows_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

ChordData const windows_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

ChordData const windows_mode_anagram_mask = ChordData({8, 128, 0});

ModeStruct const windows_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  windows_mode_kmaps_array, // kmaps
  windows_mode_mod_chord, // mod_chords
  windows_mode_anagram_mask, // anagram_mask
};

const std::array<ModeStruct const*,4> mode_structs = {
 &default_mode_struct, &gaming_mode_struct, &left_hand_mode_struct, &windows_mode_struct, 
};

} // end namespace conf
