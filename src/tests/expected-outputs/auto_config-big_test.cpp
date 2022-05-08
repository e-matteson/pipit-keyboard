#include "auto_config-big_test.h"
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
HuffmanChar const huffman_lookup[105] = {
 {
  HuffmanBits({6}), // bits
  3, // num_bits
  static_cast<uint8_t>(KEY_E), // key_code
  0, // is_mod
}, {
  HuffmanBits({15}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_A), // key_code
  0, // is_mod
}, {
  HuffmanBits({8}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_C), // key_code
  0, // is_mod
}, {
  HuffmanBits({3}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_I), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({4}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_L), // key_code
  0, // is_mod
}, {
  HuffmanBits({10}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_N), // key_code
  0, // is_mod
}, {
  HuffmanBits({9}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_O), // key_code
  0, // is_mod
}, {
  HuffmanBits({11}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_R), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({2}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_S), // key_code
  0, // is_mod
}, {
  HuffmanBits({7}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_T), // key_code
  0, // is_mod
}, {
  HuffmanBits({1}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_D), // key_code
  0, // is_mod
}, {
  HuffmanBits({16}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_G), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({12}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_H), // key_code
  0, // is_mod
}, {
  HuffmanBits({17}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_M), // key_code
  0, // is_mod
}, {
  HuffmanBits({13}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_P), // key_code
  0, // is_mod
}, {
  HuffmanBits({21}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_U), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({61}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_B), // key_code
  0, // is_mod
}, {
  HuffmanBits({29}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_F), // key_code
  0, // is_mod
}, {
  HuffmanBits({28}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_V), // key_code
  0, // is_mod
}, {
  HuffmanBits({0}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_W), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({37}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_Y), // key_code
  0, // is_mod
}, {
  HuffmanBits({60}), // bits
  6, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_SHIFT), // key_code
  1, // is_mod
}, {
  HuffmanBits({69}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_K), // key_code
  0, // is_mod
}, {
  HuffmanBits({32}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_X), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({224}), // bits
  8, // num_bits
  static_cast<uint8_t>(KEY_J), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 0}), // bits
  9, // num_bits
  static_cast<uint8_t>(KEY_Q), // key_code
  0, // is_mod
}, {
  HuffmanBits({5, 1}), // bits
  9, // num_bits
  static_cast<uint8_t>(KEY_Z), // key_code
  0, // is_mod
}, {
  HuffmanBits({5, 2}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_QUOTE), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 0}), // bits
  11, // num_bits
  static_cast<uint8_t>(KEY_PERIOD), // key_code
  0, // is_mod
}, {
  HuffmanBits({5, 0}), // bits
  11, // num_bits
  static_cast<uint8_t>(KEY_SPACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 1}), // bits
  12, // num_bits
  static_cast<uint8_t>(0 /* blank key, when a keypress contains only modifiers and no key */), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 5}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_ESC), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 3}), // bits
  12, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_CTRL), // key_code
  1, // is_mod
}, {
  HuffmanBits({133, 25}), // bits
  13, // num_bits
  static_cast<uint8_t>(Command::command_switch_to), // key_code
  0, // is_mod
}, {
  HuffmanBits({5, 4}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_0), // key_code
  0, // is_mod
}, {
  HuffmanBits({5, 28}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_1), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 29}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_2), // key_code
  0, // is_mod
}, {
  HuffmanBits({5, 12}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_3), // key_code
  0, // is_mod
}, {
  HuffmanBits({5, 20}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_4), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 17}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_5), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 1}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_6), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 26}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_7), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 31}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_8), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 25}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_9), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 7}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_BACKSLASH), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 30}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_COMMA), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 29}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_ENTER), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 9}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_EQUAL), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 10}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_LEFT_BRACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 5}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_MINUS), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 9}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_PAGE_DOWN), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 23}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_PAGE_UP), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 6}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_SEMICOLON), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 7}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_SLASH), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 13}), // bits
  13, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_ALT), // key_code
  1, // is_mod
}, {
  HuffmanBits({96, 14}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_delete_word), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 34}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_led_battery), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 3}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_left_limit), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 22}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_left_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 46}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_pan_left), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 4}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_right_limit), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 59}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_scroll_down), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 28}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_scroll_up), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 27}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_shorten_last_word), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 35}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_sticky_alt), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 19}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_sticky_ctrl), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 54}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_sticky_gui), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 12}), // bits
  14, // num_bits
  static_cast<uint8_t>(Command::command_sticky_shift), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 21}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_BACKSPACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 51}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_CAPS_LOCK), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 15}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_DELETE), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 44}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_DOWN), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 11}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_END), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 50}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_F1), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 18}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_F4), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 2}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_F6), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 36}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_F7), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 20}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_HOME), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 60}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_LEFT), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 53}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_PRINTSCREEN), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 47}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_RIGHT_BRACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 47}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_TAB), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 31}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_TILDE), // key_code
  0, // is_mod
}, {
  HuffmanBits({96, 43}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_UP), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({96, 52}), // bits
  14, // num_bits
  static_cast<uint8_t>(Mode::windows_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 13}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_cycle_capital), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 77}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_cycle_nospace), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 127}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_cycle_word), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 45}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_led_colors), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 79}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_led_rainbow), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 59}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_pan_right), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 27}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_pause), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 109}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_right_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 63}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_toggle_wireless), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 123}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_windows_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 23}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F2), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 91}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F3), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 107}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F5), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 43}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F8), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 11}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F9), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 15}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_RIGHT), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 119}), // bits
  15, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_GUI), // key_code
  1, // is_mod
}, {
  HuffmanBits({133, 55}), // bits
  15, // num_bits
  static_cast<uint8_t>(Mode::default_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({133, 75}), // bits
  15, // num_bits
  static_cast<uint8_t>(Mode::gaming_mode), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({133, 87}), // bits
  15, // num_bits
  static_cast<uint8_t>(Mode::left_hand_mode), // key_code
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
ChordData const kmap0_Plain_len3_anagram0_chords[1] = {
 ChordData({16, 0, 0}), 
};

uint8_t const kmap0_Plain_len3_anagram0_seqs[1] = {
 6, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len3_anagram0 = {
  LengthAndAnagram(3, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len3_anagram0_chords, // chords
  kmap0_Plain_len3_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len4_anagram0_chords[9] = {
 ChordData({0, 0, 1}), ChordData({0, 0, 2}), ChordData({0, 0, 8}), ChordData({0, 0, 16}), 
 ChordData({0, 0, 64}), ChordData({0, 0, 128}), ChordData({0, 4, 0}), ChordData({2, 0, 0}), 
 ChordData({128, 0, 0}), 
};

uint8_t const kmap0_Plain_len4_anagram0_seqs[5] = {
 135, 186, 66, 63, 
 9, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len4_anagram0 = {
  LengthAndAnagram(4, 0), // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_Plain_len4_anagram0_chords, // chords
  kmap0_Plain_len4_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len5_anagram0_chords[6] = {
 ChordData({0, 8, 0}), ChordData({0, 32, 0}), ChordData({0, 64, 0}), ChordData({4, 0, 0}), 
 ChordData({32, 0, 0}), ChordData({32, 1, 0}), 
};

uint8_t const kmap0_Plain_len5_anagram0_seqs[4] = {
 145, 133, 86, 33, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len5_anagram0 = {
  LengthAndAnagram(5, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Plain_len5_anagram0_chords, // chords
  kmap0_Plain_len5_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len6_anagram0_chords[5] = {
 ChordData({0, 0, 18}), ChordData({0, 1, 0}), ChordData({0, 64, 2}), ChordData({32, 8, 0}), 
 ChordData({36, 0, 0}), 
};

uint8_t const kmap0_Plain_len6_anagram0_seqs[4] = {
 101, 7, 112, 61, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len6_anagram0 = {
  LengthAndAnagram(6, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Plain_len6_anagram0_chords, // chords
  kmap0_Plain_len6_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len7_anagram0_chords[2] = {
 ChordData({0, 0, 130}), ChordData({0, 9, 0}), 
};

uint8_t const kmap0_Plain_len7_anagram0_seqs[2] = {
 160, 34, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len7_anagram0_chords, // chords
  kmap0_Plain_len7_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len8_anagram0_chords[1] = {
 ChordData({0, 0, 144}), 
};

uint8_t const kmap0_Plain_len8_anagram0_seqs[1] = {
 224, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len8_anagram0 = {
  LengthAndAnagram(8, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len8_anagram0_chords, // chords
  kmap0_Plain_len8_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len9_anagram0_chords[2] = {
 ChordData({0, 64, 128}), ChordData({4, 8, 0}), 
};

uint8_t const kmap0_Plain_len9_anagram0_seqs[3] = {
 133, 10, 2, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len9_anagram0_chords, // chords
  kmap0_Plain_len9_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len10_anagram0_chords[1] = {
 ChordData({0, 32, 128}), 
};

uint8_t const kmap0_Plain_len10_anagram0_seqs[2] = {
 5, 2, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len10_anagram0 = {
  LengthAndAnagram(10, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len10_anagram0_chords, // chords
  kmap0_Plain_len10_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len11_anagram0_chords[2] = {
 ChordData({0, 64, 16}), ChordData({0, 128, 0}), 
};

uint8_t const kmap0_Plain_len11_anagram0_seqs[3] = {
 96, 40, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len11_anagram0_chords, // chords
  kmap0_Plain_len11_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len12_anagram0_chords[1] = {
 ChordData({16, 0, 1}), 
};

uint8_t const kmap0_Plain_len12_anagram0_seqs[2] = {
 133, 5, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len12_anagram0 = {
  LengthAndAnagram(12, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len12_anagram0_chords, // chords
  kmap0_Plain_len12_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len13_anagram0_chords[20] = {
 ChordData({0, 0, 9}), ChordData({0, 0, 65}), ChordData({0, 0, 72}), ChordData({0, 2, 32}), 
 ChordData({0, 32, 1}), ChordData({0, 32, 2}), ChordData({0, 32, 8}), ChordData({0, 32, 16}), 
 ChordData({0, 33, 0}), ChordData({0, 64, 8}), ChordData({0, 64, 64}), ChordData({0, 130, 0}), 
 ChordData({4, 1, 0}), ChordData({8, 128, 0}), ChordData({16, 4, 0}), ChordData({18, 0, 0}), 
 ChordData({34, 0, 0}), ChordData({128, 4, 0}), ChordData({130, 0, 0}), ChordData({144, 0, 0}), 
};

uint8_t const kmap0_Plain_len13_anagram0_seqs[33] = {
 133, 29, 236, 23, 
 80, 176, 84, 64, 
 10, 79, 97, 0, 
 43, 96, 10, 204, 
 20, 38, 176, 11, 
 230, 193, 58, 88, 
 46, 224, 96, 167, 
 48, 130, 233, 2, 
 6, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len13_anagram0 = {
  LengthAndAnagram(13, 0), // seq_bit_len_and_anagram
  20, // num_chords
  kmap0_Plain_len13_anagram0_chords, // chords
  kmap0_Plain_len13_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len14_anagram0_chords[16] = {
 ChordData({0, 0, 32}), ChordData({0, 0, 80}), ChordData({0, 1, 1}), ChordData({0, 2, 0}), 
 ChordData({0, 128, 16}), ChordData({0, 128, 128}), ChordData({0, 128, 216}), ChordData({0, 129, 72}), 
 ChordData({0, 161, 8}), ChordData({0, 192, 0}), ChordData({0, 224, 3}), ChordData({8, 0, 0}), 
 ChordData({18, 129, 0}), ChordData({54, 128, 0}), ChordData({128, 8, 0}), ChordData({130, 129, 0}), 
};

uint8_t const kmap0_Plain_len14_anagram0_seqs[28] = {
 96, 107, 225, 87, 
 248, 130, 177, 96, 
 20, 216, 2, 86, 
 131, 73, 96, 2, 
 24, 15, 54, 131, 
 85, 96, 50, 216, 
 3, 246, 130, 145, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  16, // num_chords
  kmap0_Plain_len14_anagram0_chords, // chords
  kmap0_Plain_len14_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len15_anagram0_chords[6] = {
 ChordData({0, 128, 2}), ChordData({0, 129, 9}), ChordData({0, 129, 65}), ChordData({16, 133, 0}), 
 ChordData({128, 133, 0}), ChordData({144, 129, 0}), 
};

uint8_t const kmap0_Plain_len15_anagram0_seqs[12] = {
 133, 143, 194, 75, 
 225, 170, 112, 81, 
 184, 46, 220, 2, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Plain_len15_anagram0_chords, // chords
  kmap0_Plain_len15_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len16_anagram0_chords[1] = {
 ChordData({2, 8, 0}), 
};

uint8_t const kmap0_Plain_len16_anagram0_seqs[2] = {
 124, 129, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len16_anagram0_chords, // chords
  kmap0_Plain_len16_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len17_anagram0_chords[1] = {
 ChordData({0, 8, 1}), 
};

uint8_t const kmap0_Plain_len17_anagram0_seqs[3] = {
 60, 24, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len17_anagram0 = {
  LengthAndAnagram(17, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len17_anagram0_chords, // chords
  kmap0_Plain_len17_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len18_anagram0_chords[1] = {
 ChordData({64, 0, 0}), 
};

uint8_t const kmap0_Plain_len18_anagram0_seqs[3] = {
 60, 88, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len18_anagram0_chords, // chords
  kmap0_Plain_len18_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len19_anagram0_chords[17] = {
 ChordData({0, 0, 10}), ChordData({0, 0, 17}), ChordData({0, 0, 66}), ChordData({0, 32, 64}), 
 ChordData({0, 40, 0}), ChordData({0, 64, 1}), ChordData({2, 1, 0}), ChordData({2, 4, 0}), 
 ChordData({4, 0, 1}), ChordData({4, 4, 0}), ChordData({4, 32, 0}), ChordData({16, 1, 0}), 
 ChordData({20, 0, 0}), ChordData({32, 4, 0}), ChordData({32, 32, 0}), ChordData({132, 0, 0}), 
 ChordData({160, 0, 0}), 
};

uint8_t const kmap0_Plain_len19_anagram0_seqs[41] = {
 124, 97, 228, 193, 
 52, 95, 192, 248, 
 194, 195, 131, 121, 
 190, 128, 242, 96, 
 133, 47, 224, 124, 
 1, 225, 11, 19, 
 15, 150, 121, 176, 
 195, 23, 6, 190, 
 176, 243, 96, 138, 
 7, 51, 60, 216, 
 7, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len19_anagram0 = {
  LengthAndAnagram(19, 0), // seq_bit_len_and_anagram
  17, // num_chords
  kmap0_Plain_len19_anagram0_chords, // chords
  kmap0_Plain_len19_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len20_anagram0_chords[2] = {
 ChordData({0, 5, 0}), ChordData({32, 0, 1}), 
};

uint8_t const kmap0_Plain_len20_anagram0_seqs[5] = {
 124, 225, 199, 23, 
 190, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len20_anagram0 = {
  LengthAndAnagram(20, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len20_anagram0_chords, // chords
  kmap0_Plain_len20_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len24_anagram0_chords[1] = {
 ChordData({1, 0, 0}), 
};

uint8_t const kmap0_Plain_len24_anagram0_seqs[3] = {
 133, 3, 22, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len24_anagram0 = {
  LengthAndAnagram(24, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len24_anagram0_chords, // chords
  kmap0_Plain_len24_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len25_anagram0_chords[1] = {
 ChordData({0, 0, 4}), 
};

uint8_t const kmap0_Plain_len25_anagram0_seqs[4] = {
 96, 13, 44, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len25_anagram0 = {
  LengthAndAnagram(25, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len25_anagram0_chords, // chords
  kmap0_Plain_len25_anagram0_seqs, // sequences
};

ChordData const kmap0_Plain_len27_anagram0_chords[1] = {
 ChordData({0, 16, 0}), 
};

uint8_t const kmap0_Plain_len27_anagram0_seqs[4] = {
 133, 119, 176, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Plain_len27_anagram0 = {
  LengthAndAnagram(27, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len27_anagram0_chords, // chords
  kmap0_Plain_len27_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap0_Plain_lookups_array[21] = {
 &kmap0_Plain_len3_anagram0, &kmap0_Plain_len4_anagram0, &kmap0_Plain_len5_anagram0, &kmap0_Plain_len6_anagram0, 
 &kmap0_Plain_len7_anagram0, &kmap0_Plain_len8_anagram0, &kmap0_Plain_len9_anagram0, &kmap0_Plain_len10_anagram0, 
 &kmap0_Plain_len11_anagram0, &kmap0_Plain_len12_anagram0, &kmap0_Plain_len13_anagram0, &kmap0_Plain_len14_anagram0, 
 &kmap0_Plain_len15_anagram0, &kmap0_Plain_len16_anagram0, &kmap0_Plain_len17_anagram0, &kmap0_Plain_len18_anagram0, 
 &kmap0_Plain_len19_anagram0, &kmap0_Plain_len20_anagram0, &kmap0_Plain_len24_anagram0, &kmap0_Plain_len25_anagram0, 
 &kmap0_Plain_len27_anagram0, 
};

LookupKmapType const kmap0_Plain_lookups = {
  21, // num_lookups
  kmap0_Plain_lookups_array, // lookups
};

ChordData const kmap0_Macro_len16_anagram0_chords[1] = {
 ChordData({0, 132, 0}), 
};

uint8_t const kmap0_Macro_len16_anagram0_seqs[2] = {
 133, 243, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len16_anagram0_chords, // chords
  kmap0_Macro_len16_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len20_anagram0_chords[2] = {
 ChordData({0, 96, 0}), ChordData({6, 0, 0}), 
};

uint8_t const kmap0_Macro_len20_anagram0_seqs[5] = {
 96, 13, 84, 56, 
 56, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len20_anagram0 = {
  LengthAndAnagram(20, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len20_anagram0_chords, // chords
  kmap0_Macro_len20_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len25_anagram0_chords[3] = {
 ChordData({0, 128, 8}), ChordData({0, 128, 64}), ChordData({36, 192, 2}), 
};

uint8_t const kmap0_Macro_len25_anagram0_seqs[10] = {
 133, 3, 118, 11, 
 7, 44, 21, 158, 
 194, 2, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len25_anagram0 = {
  LengthAndAnagram(25, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Macro_len25_anagram0_chords, // chords
  kmap0_Macro_len25_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len26_anagram0_chords[1] = {
 ChordData({6, 128, 0}), 
};

uint8_t const kmap0_Macro_len26_anagram0_seqs[4] = {
 133, 131, 252, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len26_anagram0 = {
  LengthAndAnagram(26, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len26_anagram0_chords, // chords
  kmap0_Macro_len26_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len27_anagram0_chords[1] = {
 ChordData({16, 132, 1}), 
};

uint8_t const kmap0_Macro_len27_anagram0_seqs[4] = {
 95, 128, 194, 2, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len27_anagram0 = {
  LengthAndAnagram(27, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len27_anagram0_chords, // chords
  kmap0_Macro_len27_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len32_anagram0_chords[2] = {
 ChordData({0, 192, 128}), ChordData({20, 132, 1}), 
};

uint8_t const kmap0_Macro_len32_anagram0_seqs[8] = {
 133, 3, 42, 224, 
 95, 128, 194, 106, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len32_anagram0 = {
  LengthAndAnagram(32, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len32_anagram0_chords, // chords
  kmap0_Macro_len32_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len33_anagram0_chords[1] = {
 ChordData({80, 132, 1}), 
};

uint8_t const kmap0_Macro_len33_anagram0_seqs[5] = {
 252, 23, 160, 176, 
 0, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len33_anagram0 = {
  LengthAndAnagram(33, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len33_anagram0_chords, // chords
  kmap0_Macro_len33_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len38_anagram0_chords[1] = {
 ChordData({84, 132, 1}), 
};

uint8_t const kmap0_Macro_len38_anagram0_seqs[5] = {
 252, 23, 160, 176, 
 26, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len38_anagram0 = {
  LengthAndAnagram(38, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len38_anagram0_chords, // chords
  kmap0_Macro_len38_anagram0_seqs, // sequences
};

ChordData const kmap0_Macro_len43_anagram0_chords[1] = {
 ChordData({0, 132, 130}), 
};

uint8_t const kmap0_Macro_len43_anagram0_seqs[6] = {
 133, 3, 42, 172, 
 194, 2, 
};

LookupKmapTypeLenAnagram const kmap0_Macro_len43_anagram0 = {
  LengthAndAnagram(43, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len43_anagram0_chords, // chords
  kmap0_Macro_len43_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap0_Macro_lookups_array[9] = {
 &kmap0_Macro_len16_anagram0, &kmap0_Macro_len20_anagram0, &kmap0_Macro_len25_anagram0, &kmap0_Macro_len26_anagram0, 
 &kmap0_Macro_len27_anagram0, &kmap0_Macro_len32_anagram0, &kmap0_Macro_len33_anagram0, &kmap0_Macro_len38_anagram0, 
 &kmap0_Macro_len43_anagram0, 
};

LookupKmapType const kmap0_Macro_lookups = {
  9, // num_lookups
  kmap0_Macro_lookups_array, // lookups
};

ChordData const kmap0_Command_len14_anagram0_chords[6] = {
 ChordData({0, 32, 9}), ChordData({0, 192, 1}), ChordData({20, 128, 0}), ChordData({36, 128, 0}), 
 ChordData({36, 169, 0}), ChordData({146, 16, 0}), 
};

uint8_t const kmap0_Command_len14_anagram0_seqs[11] = {
 96, 14, 24, 1, 
 54, 128, 89, 96, 
 34, 216, 6, 
};

LookupKmapTypeLenAnagram const kmap0_Command_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Command_len14_anagram0_chords, // chords
  kmap0_Command_len14_anagram0_seqs, // sequences
};

ChordData const kmap0_Command_len15_anagram0_chords[7] = {
 ChordData({0, 192, 2}), ChordData({36, 73, 146}), ChordData({36, 137, 2}), ChordData({36, 137, 16}), 
 ChordData({146, 0, 0}), ChordData({146, 0, 4}), ChordData({210, 0, 0}), 
};

uint8_t const kmap0_Command_len15_anagram0_seqs[14] = {
 133, 237, 194, 77, 
 97, 171, 240, 89, 
 248, 47, 108, 22, 
 54, 0, 
};

LookupKmapTypeLenAnagram const kmap0_Command_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Command_len15_anagram0_chords, // chords
  kmap0_Command_len15_anagram0_seqs, // sequences
};

ChordData const kmap0_Command_len28_anagram0_chords[2] = {
 ChordData({0, 64, 146}), ChordData({36, 9, 0}), 
};

uint8_t const kmap0_Command_len28_anagram0_seqs[7] = {
 133, 185, 112, 89, 
 152, 11, 175, 
};

LookupKmapTypeLenAnagram const kmap0_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Command_len28_anagram0_chords, // chords
  kmap0_Command_len28_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap0_Command_lookups_array[3] = {
 &kmap0_Command_len14_anagram0, &kmap0_Command_len15_anagram0, &kmap0_Command_len28_anagram0, 
};

LookupKmapType const kmap0_Command_lookups = {
  3, // num_lookups
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

ChordData const kmap1_Plain_len3_anagram0_chords[1] = {
 ChordData({4, 0, 0}), 
};

uint8_t const kmap1_Plain_len3_anagram0_seqs[1] = {
 6, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len3_anagram0 = {
  LengthAndAnagram(3, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len3_anagram0_chords, // chords
  kmap1_Plain_len3_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len4_anagram0_chords[2] = {
 ChordData({16, 0, 0}), ChordData({128, 0, 0}), 
};

uint8_t const kmap1_Plain_len4_anagram0_seqs[1] = {
 242, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len4_anagram0 = {
  LengthAndAnagram(4, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap1_Plain_len4_anagram0_chords, // chords
  kmap1_Plain_len4_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len5_anagram0_chords[1] = {
 ChordData({2, 0, 0}), 
};

uint8_t const kmap1_Plain_len5_anagram0_seqs[1] = {
 1, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len5_anagram0 = {
  LengthAndAnagram(5, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len5_anagram0_chords, // chords
  kmap1_Plain_len5_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len6_anagram0_chords[1] = {
 ChordData({32, 0, 0}), 
};

uint8_t const kmap1_Plain_len6_anagram0_seqs[1] = {
 0, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len6_anagram0 = {
  LengthAndAnagram(6, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len6_anagram0_chords, // chords
  kmap1_Plain_len6_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len9_anagram0_chords[1] = {
 ChordData({0, 1, 0}), 
};

uint8_t const kmap1_Plain_len9_anagram0_seqs[2] = {
 133, 0, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len9_anagram0_chords, // chords
  kmap1_Plain_len9_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len11_anagram0_chords[1] = {
 ChordData({8, 0, 0}), 
};

uint8_t const kmap1_Plain_len11_anagram0_seqs[2] = {
 5, 0, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len11_anagram0_chords, // chords
  kmap1_Plain_len11_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len14_anagram0_chords[1] = {
 ChordData({0, 8, 0}), 
};

uint8_t const kmap1_Plain_len14_anagram0_seqs[2] = {
 96, 47, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len14_anagram0_chords, // chords
  kmap1_Plain_len14_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len18_anagram0_chords[1] = {
 ChordData({0, 4, 0}), 
};

uint8_t const kmap1_Plain_len18_anagram0_seqs[3] = {
 60, 88, 0, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len18_anagram0_chords, // chords
  kmap1_Plain_len18_anagram0_seqs, // sequences
};

ChordData const kmap1_Plain_len24_anagram0_chords[1] = {
 ChordData({1, 0, 0}), 
};

uint8_t const kmap1_Plain_len24_anagram0_seqs[3] = {
 133, 3, 22, 
};

LookupKmapTypeLenAnagram const kmap1_Plain_len24_anagram0 = {
  LengthAndAnagram(24, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len24_anagram0_chords, // chords
  kmap1_Plain_len24_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap1_Plain_lookups_array[9] = {
 &kmap1_Plain_len3_anagram0, &kmap1_Plain_len4_anagram0, &kmap1_Plain_len5_anagram0, &kmap1_Plain_len6_anagram0, 
 &kmap1_Plain_len9_anagram0, &kmap1_Plain_len11_anagram0, &kmap1_Plain_len14_anagram0, &kmap1_Plain_len18_anagram0, 
 &kmap1_Plain_len24_anagram0, 
};

LookupKmapType const kmap1_Plain_lookups = {
  9, // num_lookups
  kmap1_Plain_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap1_Macro_lookups_array[0] = {
};

LookupKmapType const kmap1_Macro_lookups = {
  0, // num_lookups
  kmap1_Macro_lookups_array, // lookups
};

ChordData const kmap1_Command_len28_anagram0_chords[1] = {
 ChordData({0, 0, 1}), 
};

uint8_t const kmap1_Command_len28_anagram0_seqs[4] = {
 133, 185, 240, 6, 
};

LookupKmapTypeLenAnagram const kmap1_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Command_len28_anagram0_chords, // chords
  kmap1_Command_len28_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap1_Command_lookups_array[1] = {
 &kmap1_Command_len28_anagram0, 
};

LookupKmapType const kmap1_Command_lookups = {
  1, // num_lookups
  kmap1_Command_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap1_Word_lookups_array[0] = {
};

LookupKmapType const kmap1_Word_lookups = {
  0, // num_lookups
  kmap1_Word_lookups_array, // lookups
};

LookupKmapType const* const kmap1_lookups_array[4] = {
 &kmap1_Plain_lookups, &kmap1_Macro_lookups, &kmap1_Command_lookups, &kmap1_Word_lookups, 
};

KmapStruct const kmap1_lookups = {
  kmap1_lookups_array, // lookups_for_kmap
};

ChordData const kmap2_Plain_len3_anagram0_chords[1] = {
 ChordData({16, 0, 0}), 
};

uint8_t const kmap2_Plain_len3_anagram0_seqs[1] = {
 6, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len3_anagram0 = {
  LengthAndAnagram(3, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Plain_len3_anagram0_chords, // chords
  kmap2_Plain_len3_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len4_anagram0_chords[9] = {
 ChordData({0, 4, 0}), ChordData({2, 0, 0}), ChordData({64, 1, 0}), ChordData({64, 4, 0}), 
 ChordData({64, 8, 0}), ChordData({80, 0, 0}), ChordData({96, 0, 0}), ChordData({128, 0, 0}), 
 ChordData({192, 0, 0}), 
};

uint8_t const kmap2_Plain_len4_anagram0_seqs[5] = {
 63, 43, 116, 152, 
 10, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len4_anagram0 = {
  LengthAndAnagram(4, 0), // seq_bit_len_and_anagram
  9, // num_chords
  kmap2_Plain_len4_anagram0_chords, // chords
  kmap2_Plain_len4_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len5_anagram0_chords[6] = {
 ChordData({0, 8, 0}), ChordData({4, 0, 0}), ChordData({32, 0, 0}), ChordData({32, 1, 0}), 
 ChordData({66, 0, 0}), ChordData({68, 0, 0}), 
};

uint8_t const kmap2_Plain_len5_anagram0_seqs[4] = {
 177, 85, 200, 2, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len5_anagram0 = {
  LengthAndAnagram(5, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap2_Plain_len5_anagram0_chords, // chords
  kmap2_Plain_len5_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len6_anagram0_chords[5] = {
 ChordData({0, 1, 0}), ChordData({32, 8, 0}), ChordData({36, 0, 0}), ChordData({96, 1, 0}), 
 ChordData({100, 0, 0}), 
};

uint8_t const kmap2_Plain_len6_anagram0_seqs[4] = {
 29, 215, 151, 0, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len6_anagram0 = {
  LengthAndAnagram(6, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_Plain_len6_anagram0_chords, // chords
  kmap2_Plain_len6_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len7_anagram0_chords[2] = {
 ChordData({0, 9, 0}), ChordData({96, 8, 0}), 
};

uint8_t const kmap2_Plain_len7_anagram0_seqs[2] = {
 69, 16, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len7_anagram0_chords, // chords
  kmap2_Plain_len7_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len8_anagram0_chords[1] = {
 ChordData({64, 9, 0}), 
};

uint8_t const kmap2_Plain_len8_anagram0_seqs[1] = {
 224, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len8_anagram0 = {
  LengthAndAnagram(8, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Plain_len8_anagram0_chords, // chords
  kmap2_Plain_len8_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len9_anagram0_chords[2] = {
 ChordData({4, 8, 0}), ChordData({68, 8, 0}), 
};

uint8_t const kmap2_Plain_len9_anagram0_seqs[3] = {
 5, 11, 1, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len9_anagram0_chords, // chords
  kmap2_Plain_len9_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len10_anagram0_chords[1] = {
 ChordData({66, 8, 0}), 
};

uint8_t const kmap2_Plain_len10_anagram0_seqs[2] = {
 5, 2, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len10_anagram0 = {
  LengthAndAnagram(10, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Plain_len10_anagram0_chords, // chords
  kmap2_Plain_len10_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len11_anagram0_chords[2] = {
 ChordData({64, 0, 0}), ChordData({68, 1, 0}), 
};

uint8_t const kmap2_Plain_len11_anagram0_seqs[3] = {
 5, 0, 3, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len11_anagram0_chords, // chords
  kmap2_Plain_len11_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len12_anagram0_chords[1] = {
 ChordData({19, 0, 0}), 
};

uint8_t const kmap2_Plain_len12_anagram0_seqs[2] = {
 133, 5, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len12_anagram0 = {
  LengthAndAnagram(12, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Plain_len12_anagram0_chords, // chords
  kmap2_Plain_len12_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len13_anagram0_chords[19] = {
 ChordData({1, 0, 0}), ChordData({4, 1, 0}), ChordData({6, 0, 0}), ChordData({16, 4, 0}), 
 ChordData({18, 0, 0}), ChordData({34, 0, 0}), ChordData({48, 0, 0}), ChordData({66, 1, 0}), 
 ChordData({68, 4, 0}), ChordData({80, 4, 0}), ChordData({82, 0, 0}), ChordData({98, 0, 0}), 
 ChordData({128, 4, 0}), ChordData({130, 0, 0}), ChordData({144, 0, 0}), ChordData({192, 4, 0}), 
 ChordData({194, 0, 0}), ChordData({196, 0, 0}), ChordData({208, 0, 0}), 
};

uint8_t const kmap2_Plain_len13_anagram0_seqs[31] = {
 96, 29, 204, 131, 
 93, 176, 92, 192, 
 193, 14, 88, 2, 
 43, 133, 9, 236, 
 23, 144, 194, 83, 
 24, 193, 116, 1, 
 43, 160, 133, 1, 
 204, 20, 118, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len13_anagram0 = {
  LengthAndAnagram(13, 0), // seq_bit_len_and_anagram
  19, // num_chords
  kmap2_Plain_len13_anagram0_chords, // chords
  kmap2_Plain_len13_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len14_anagram0_chords[14] = {
 ChordData({0, 2, 0}), ChordData({1, 1, 0}), ChordData({1, 8, 0}), ChordData({8, 0, 0}), 
 ChordData({18, 1, 0}), ChordData({33, 0, 0}), ChordData({54, 0, 0}), ChordData({64, 2, 0}), 
 ChordData({64, 5, 0}), ChordData({128, 8, 0}), ChordData({128, 13, 0}), ChordData({130, 1, 0}), 
 ChordData({192, 5, 0}), ChordData({194, 1, 0}), 
};

uint8_t const kmap2_Plain_len14_anagram0_seqs[25] = {
 96, 44, 216, 2, 
 70, 129, 85, 96, 
 50, 24, 15, 246, 
 128, 173, 133, 31, 
 216, 11, 54, 131, 
 145, 96, 18, 152, 
 0, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  14, // num_chords
  kmap2_Plain_len14_anagram0_chords, // chords
  kmap2_Plain_len14_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len15_anagram0_chords[6] = {
 ChordData({5, 0, 0}), ChordData({16, 5, 0}), ChordData({80, 5, 0}), ChordData({128, 5, 0}), 
 ChordData({144, 1, 0}), ChordData({208, 1, 0}), 
};

uint8_t const kmap2_Plain_len15_anagram0_seqs[12] = {
 133, 143, 194, 69, 
 225, 170, 112, 93, 
 184, 45, 188, 0, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap2_Plain_len15_anagram0_chords, // chords
  kmap2_Plain_len15_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len16_anagram0_chords[1] = {
 ChordData({2, 8, 0}), 
};

uint8_t const kmap2_Plain_len16_anagram0_seqs[2] = {
 124, 129, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Plain_len16_anagram0_chords, // chords
  kmap2_Plain_len16_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len19_anagram0_chords[13] = {
 ChordData({2, 1, 0}), ChordData({2, 4, 0}), ChordData({4, 4, 0}), ChordData({16, 1, 0}), 
 ChordData({20, 0, 0}), ChordData({32, 4, 0}), ChordData({66, 4, 0}), ChordData({80, 1, 0}), 
 ChordData({84, 0, 0}), ChordData({96, 4, 0}), ChordData({132, 0, 0}), ChordData({160, 0, 0}), 
 ChordData({224, 0, 0}), 
};

uint8_t const kmap2_Plain_len19_anagram0_seqs[31] = {
 60, 88, 225, 11, 
 56, 95, 152, 120, 
 176, 195, 23, 6, 
 190, 176, 243, 133, 
 135, 7, 211, 124, 
 1, 229, 11, 24, 
 15, 102, 120, 176, 
 207, 23, 70, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len19_anagram0 = {
  LengthAndAnagram(19, 0), // seq_bit_len_and_anagram
  13, // num_chords
  kmap2_Plain_len19_anagram0_chords, // chords
  kmap2_Plain_len19_anagram0_seqs, // sequences
};

ChordData const kmap2_Plain_len20_anagram0_chords[1] = {
 ChordData({0, 5, 0}), 
};

uint8_t const kmap2_Plain_len20_anagram0_seqs[3] = {
 124, 225, 7, 
};

LookupKmapTypeLenAnagram const kmap2_Plain_len20_anagram0 = {
  LengthAndAnagram(20, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Plain_len20_anagram0_chords, // chords
  kmap2_Plain_len20_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap2_Plain_lookups_array[16] = {
 &kmap2_Plain_len3_anagram0, &kmap2_Plain_len4_anagram0, &kmap2_Plain_len5_anagram0, &kmap2_Plain_len6_anagram0, 
 &kmap2_Plain_len7_anagram0, &kmap2_Plain_len8_anagram0, &kmap2_Plain_len9_anagram0, &kmap2_Plain_len10_anagram0, 
 &kmap2_Plain_len11_anagram0, &kmap2_Plain_len12_anagram0, &kmap2_Plain_len13_anagram0, &kmap2_Plain_len14_anagram0, 
 &kmap2_Plain_len15_anagram0, &kmap2_Plain_len16_anagram0, &kmap2_Plain_len19_anagram0, &kmap2_Plain_len20_anagram0, 
};

LookupKmapType const kmap2_Plain_lookups = {
  16, // num_lookups
  kmap2_Plain_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap2_Macro_lookups_array[0] = {
};

LookupKmapType const kmap2_Macro_lookups = {
  0, // num_lookups
  kmap2_Macro_lookups_array, // lookups
};

ChordData const kmap2_Command_len14_anagram0_chords[4] = {
 ChordData({1, 4, 0}), ChordData({3, 0, 0}), ChordData({17, 0, 0}), ChordData({129, 0, 0}), 
};

uint8_t const kmap2_Command_len14_anagram0_seqs[7] = {
 96, 35, 216, 4, 
 102, 131, 49, 
};

LookupKmapTypeLenAnagram const kmap2_Command_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap2_Command_len14_anagram0_chords, // chords
  kmap2_Command_len14_anagram0_seqs, // sequences
};

ChordData const kmap2_Command_len28_anagram0_chords[1] = {
 ChordData({16, 0, 1}), 
};

uint8_t const kmap2_Command_len28_anagram0_seqs[4] = {
 133, 185, 240, 6, 
};

LookupKmapTypeLenAnagram const kmap2_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Command_len28_anagram0_chords, // chords
  kmap2_Command_len28_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap2_Command_lookups_array[2] = {
 &kmap2_Command_len14_anagram0, &kmap2_Command_len28_anagram0, 
};

LookupKmapType const kmap2_Command_lookups = {
  2, // num_lookups
  kmap2_Command_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap2_Word_lookups_array[0] = {
};

LookupKmapType const kmap2_Word_lookups = {
  0, // num_lookups
  kmap2_Word_lookups_array, // lookups
};

LookupKmapType const* const kmap2_lookups_array[4] = {
 &kmap2_Plain_lookups, &kmap2_Macro_lookups, &kmap2_Command_lookups, &kmap2_Word_lookups, 
};

KmapStruct const kmap2_lookups = {
  kmap2_lookups_array, // lookups_for_kmap
};

LookupKmapTypeLenAnagram const* const kmap3_Plain_lookups_array[0] = {
};

LookupKmapType const kmap3_Plain_lookups = {
  0, // num_lookups
  kmap3_Plain_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap3_Macro_lookups_array[0] = {
};

LookupKmapType const kmap3_Macro_lookups = {
  0, // num_lookups
  kmap3_Macro_lookups_array, // lookups
};

ChordData const kmap3_Command_len28_anagram0_chords[1] = {
 ChordData({36, 9, 0}), 
};

uint8_t const kmap3_Command_len28_anagram0_seqs[4] = {
 133, 185, 240, 6, 
};

LookupKmapTypeLenAnagram const kmap3_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap3_Command_len28_anagram0_chords, // chords
  kmap3_Command_len28_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap3_Command_lookups_array[1] = {
 &kmap3_Command_len28_anagram0, 
};

LookupKmapType const kmap3_Command_lookups = {
  1, // num_lookups
  kmap3_Command_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap3_Word_lookups_array[0] = {
};

LookupKmapType const kmap3_Word_lookups = {
  0, // num_lookups
  kmap3_Word_lookups_array, // lookups
};

LookupKmapType const* const kmap3_lookups_array[4] = {
 &kmap3_Plain_lookups, &kmap3_Macro_lookups, &kmap3_Command_lookups, &kmap3_Word_lookups, 
};

KmapStruct const kmap3_lookups = {
  kmap3_lookups_array, // lookups_for_kmap
};

LookupKmapTypeLenAnagram const* const kmap4_Plain_lookups_array[0] = {
};

LookupKmapType const kmap4_Plain_lookups = {
  0, // num_lookups
  kmap4_Plain_lookups_array, // lookups
};

ChordData const kmap4_Macro_len21_anagram0_chords[1] = {
 ChordData({0, 128, 192}), 
};

uint8_t const kmap4_Macro_len21_anagram0_seqs[3] = {
 36, 96, 29, 
};

LookupKmapTypeLenAnagram const kmap4_Macro_len21_anagram0 = {
  LengthAndAnagram(21, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap4_Macro_len21_anagram0_chords, // chords
  kmap4_Macro_len21_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap4_Macro_lookups_array[1] = {
 &kmap4_Macro_len21_anagram0, 
};

LookupKmapType const kmap4_Macro_lookups = {
  1, // num_lookups
  kmap4_Macro_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap4_Command_lookups_array[0] = {
};

LookupKmapType const kmap4_Command_lookups = {
  0, // num_lookups
  kmap4_Command_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap4_Word_lookups_array[0] = {
};

LookupKmapType const kmap4_Word_lookups = {
  0, // num_lookups
  kmap4_Word_lookups_array, // lookups
};

LookupKmapType const* const kmap4_lookups_array[4] = {
 &kmap4_Plain_lookups, &kmap4_Macro_lookups, &kmap4_Command_lookups, &kmap4_Word_lookups, 
};

KmapStruct const kmap4_lookups = {
  kmap4_lookups_array, // lookups_for_kmap
};

LookupKmapTypeLenAnagram const* const kmap5_Plain_lookups_array[0] = {
};

LookupKmapType const kmap5_Plain_lookups = {
  0, // num_lookups
  kmap5_Plain_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap5_Macro_lookups_array[0] = {
};

LookupKmapType const kmap5_Macro_lookups = {
  0, // num_lookups
  kmap5_Macro_lookups_array, // lookups
};

LookupKmapTypeLenAnagram const* const kmap5_Command_lookups_array[0] = {
};

LookupKmapType const kmap5_Command_lookups = {
  0, // num_lookups
  kmap5_Command_lookups_array, // lookups
};

ChordData const kmap5_Word_len4_anagram1_chords[3] = {
 ChordData({0, 0, 16}), ChordData({0, 0, 64}), ChordData({0, 4, 0}), 
};

uint8_t const kmap5_Word_len4_anagram1_seqs[2] = {
 43, 15, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len4_anagram1 = {
  LengthAndAnagram(4, 1), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len4_anagram1_chords, // chords
  kmap5_Word_len4_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len5_anagram1_chords[2] = {
 ChordData({0, 64, 0}), ChordData({32, 0, 0}), 
};

uint8_t const kmap5_Word_len5_anagram1_seqs[2] = {
 161, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len5_anagram1 = {
  LengthAndAnagram(5, 1), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len5_anagram1_chords, // chords
  kmap5_Word_len5_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len7_anagram0_chords[2] = {
 ChordData({16, 0, 8}), ChordData({16, 0, 16}), 
};

uint8_t const kmap5_Word_len7_anagram0_seqs[2] = {
 86, 47, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len7_anagram0_chords, // chords
  kmap5_Word_len7_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len7_anagram1_chords[3] = {
 ChordData({0, 0, 130}), ChordData({16, 0, 16}), ChordData({16, 0, 64}), 
};

uint8_t const kmap5_Word_len7_anagram1_seqs[3] = {
 160, 181, 5, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len7_anagram1 = {
  LengthAndAnagram(7, 1), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len7_anagram1_chords, // chords
  kmap5_Word_len7_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len8_anagram0_chords[18] = {
 ChordData({0, 0, 136}), ChordData({0, 0, 192}), ChordData({0, 4, 1}), ChordData({0, 4, 2}), 
 ChordData({0, 4, 8}), ChordData({0, 4, 64}), ChordData({2, 0, 1}), ChordData({2, 0, 2}), 
 ChordData({2, 0, 8}), ChordData({2, 0, 64}), ChordData({16, 8, 0}), ChordData({16, 32, 0}), 
 ChordData({16, 64, 0}), ChordData({128, 0, 1}), ChordData({128, 0, 2}), ChordData({128, 0, 8}), 
 ChordData({128, 0, 16}), ChordData({128, 0, 64}), 
};

uint8_t const kmap5_Word_len8_anagram0_seqs[18] = {
 164, 36, 127, 143, 
 175, 47, 115, 131, 
 163, 35, 209, 204, 
 14, 151, 152, 169, 
 185, 146, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len8_anagram0 = {
  LengthAndAnagram(8, 0), // seq_bit_len_and_anagram
  18, // num_chords
  kmap5_Word_len8_anagram0_chords, // chords
  kmap5_Word_len8_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len8_anagram1_chords[4] = {
 ChordData({0, 4, 128}), ChordData({16, 8, 0}), ChordData({16, 64, 0}), ChordData({128, 0, 8}), 
};

uint8_t const kmap5_Word_len8_anagram1_seqs[4] = {
 79, 142, 193, 154, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len8_anagram1 = {
  LengthAndAnagram(8, 1), // seq_bit_len_and_anagram
  4, // num_chords
  kmap5_Word_len8_anagram1_chords, // chords
  kmap5_Word_len8_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len9_anagram0_chords[12] = {
 ChordData({0, 8, 16}), ChordData({0, 12, 0}), ChordData({0, 36, 0}), ChordData({2, 32, 0}), 
 ChordData({4, 0, 64}), ChordData({16, 64, 2}), ChordData({32, 0, 8}), ChordData({32, 0, 64}), 
 ChordData({52, 0, 0}), ChordData({128, 32, 0}), ChordData({128, 64, 0}), ChordData({160, 1, 0}), 
};

uint8_t const kmap5_Word_len9_anagram0_seqs[14] = {
 27, 63, 62, 99, 
 211, 4, 112, 213, 
 42, 189, 147, 133, 
 132, 9, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  12, // num_chords
  kmap5_Word_len9_anagram0_chords, // chords
  kmap5_Word_len9_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len9_anagram1_chords[6] = {
 ChordData({0, 36, 0}), ChordData({0, 64, 2}), ChordData({2, 8, 0}), ChordData({6, 0, 0}), 
 ChordData({32, 1, 8}), ChordData({132, 0, 0}), 
};

uint8_t const kmap5_Word_len9_anagram1_seqs[7] = {
 236, 49, 76, 108, 
 163, 48, 27, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len9_anagram1 = {
  LengthAndAnagram(9, 1), // seq_bit_len_and_anagram
  6, // num_chords
  kmap5_Word_len9_anagram1_chords, // chords
  kmap5_Word_len9_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len9_anagram2_chords[2] = {
 ChordData({4, 4, 0}), ChordData({6, 0, 0}), 
};

uint8_t const kmap5_Word_len9_anagram2_seqs[3] = {
 223, 166, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len9_anagram2 = {
  LengthAndAnagram(9, 2), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len9_anagram2_chords, // chords
  kmap5_Word_len9_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len9_anagram4_chords[1] = {
 ChordData({34, 1, 0}), 
};

uint8_t const kmap5_Word_len9_anagram4_seqs[2] = {
 112, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len9_anagram4 = {
  LengthAndAnagram(9, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len9_anagram4_chords, // chords
  kmap5_Word_len9_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len10_anagram0_chords[5] = {
 ChordData({0, 0, 146}), ChordData({0, 1, 8}), ChordData({16, 0, 64}), ChordData({38, 0, 0}), 
 ChordData({128, 1, 0}), 
};

uint8_t const kmap5_Word_len10_anagram0_seqs[7] = {
 84, 118, 42, 118, 
 63, 217, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len10_anagram0 = {
  LengthAndAnagram(10, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len10_anagram0_chords, // chords
  kmap5_Word_len10_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len10_anagram1_chords[8] = {
 ChordData({0, 0, 18}), ChordData({2, 0, 0}), ChordData({2, 1, 0}), ChordData({16, 0, 1}), 
 ChordData({16, 0, 130}), ChordData({32, 8, 1}), ChordData({32, 8, 64}), ChordData({36, 0, 0}), 
};

uint8_t const kmap5_Word_len10_anagram1_seqs[10] = {
 91, 242, 51, 221, 
 217, 6, 29, 199, 
 73, 109, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len10_anagram1 = {
  LengthAndAnagram(10, 1), // seq_bit_len_and_anagram
  8, // num_chords
  kmap5_Word_len10_anagram1_chords, // chords
  kmap5_Word_len10_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len10_anagram2_chords[1] = {
 ChordData({32, 8, 0}), 
};

uint8_t const kmap5_Word_len10_anagram2_seqs[2] = {
 53, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len10_anagram2 = {
  LengthAndAnagram(10, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len10_anagram2_chords, // chords
  kmap5_Word_len10_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len10_anagram3_chords[2] = {
 ChordData({32, 8, 0}), ChordData({34, 8, 0}), 
};

uint8_t const kmap5_Word_len10_anagram3_seqs[3] = {
 177, 114, 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len10_anagram3 = {
  LengthAndAnagram(10, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len10_anagram3_chords, // chords
  kmap5_Word_len10_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len11_anagram0_chords[23] = {
 ChordData({0, 0, 131}), ChordData({0, 8, 18}), ChordData({0, 65, 0}), ChordData({0, 72, 2}), 
 ChordData({16, 0, 3}), ChordData({16, 0, 9}), ChordData({16, 0, 17}), ChordData({16, 0, 66}), 
 ChordData({16, 0, 129}), ChordData({16, 0, 136}), ChordData({16, 0, 144}), ChordData({16, 4, 1}), 
 ChordData({16, 4, 2}), ChordData({16, 4, 16}), ChordData({18, 0, 1}), ChordData({18, 0, 2}), 
 ChordData({18, 0, 16}), ChordData({18, 0, 64}), ChordData({18, 0, 128}), ChordData({128, 9, 0}), 
 ChordData({144, 0, 1}), ChordData({144, 0, 2}), ChordData({144, 0, 8}), 
};

uint8_t const kmap5_Word_len11_anagram0_seqs[32] = {
 7, 138, 101, 23, 
 128, 232, 195, 179, 
 158, 87, 140, 228, 
 35, 235, 154, 252, 
 247, 232, 95, 223, 
 120, 208, 227, 29, 
 11, 141, 179, 120, 
 105, 99, 166, 26, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  23, // num_chords
  kmap5_Word_len11_anagram0_chords, // chords
  kmap5_Word_len11_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len11_anagram1_chords[8] = {
 ChordData({16, 0, 9}), ChordData({16, 0, 65}), ChordData({16, 0, 80}), ChordData({16, 4, 1}), 
 ChordData({16, 4, 64}), ChordData({20, 0, 0}), ChordData({32, 1, 0}), ChordData({32, 8, 0}), 
};

uint8_t const kmap5_Word_len11_anagram1_seqs[11] = {
 234, 19, 223, 90, 
 254, 44, 254, 102, 
 119, 48, 114, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len11_anagram1 = {
  LengthAndAnagram(11, 1), // seq_bit_len_and_anagram
  8, // num_chords
  kmap5_Word_len11_anagram1_chords, // chords
  kmap5_Word_len11_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len11_anagram2_chords[3] = {
 ChordData({0, 0, 146}), ChordData({16, 0, 65}), ChordData({16, 4, 1}), 
};

uint8_t const kmap5_Word_len11_anagram2_seqs[5] = {
 11, 178, 220, 249, 
 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len11_anagram2 = {
  LengthAndAnagram(11, 2), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len11_anagram2_chords, // chords
  kmap5_Word_len11_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len11_anagram3_chords[2] = {
 ChordData({16, 4, 16}), ChordData({144, 0, 8}), 
};

uint8_t const kmap5_Word_len11_anagram3_seqs[3] = {
 222, 87, 39, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len11_anagram3 = {
  LengthAndAnagram(11, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len11_anagram3_chords, // chords
  kmap5_Word_len11_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len11_anagram4_chords[1] = {
 ChordData({16, 4, 16}), 
};

uint8_t const kmap5_Word_len11_anagram4_seqs[2] = {
 254, 5, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len11_anagram4 = {
  LengthAndAnagram(11, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len11_anagram4_chords, // chords
  kmap5_Word_len11_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len12_anagram0_chords[50] = {
 ChordData({0, 0, 81}), ChordData({0, 0, 82}), ChordData({0, 0, 208}), ChordData({0, 4, 3}), 
 ChordData({0, 4, 9}), ChordData({0, 4, 10}), ChordData({0, 4, 17}), ChordData({0, 4, 24}), 
 ChordData({0, 4, 65}), ChordData({0, 4, 128}), ChordData({0, 4, 136}), ChordData({2, 0, 9}), 
 ChordData({2, 0, 17}), ChordData({2, 0, 65}), ChordData({2, 0, 66}), ChordData({2, 0, 72}), 
 ChordData({2, 0, 128}), ChordData({2, 0, 129}), ChordData({2, 0, 136}), ChordData({2, 4, 8}), 
 ChordData({2, 4, 16}), ChordData({4, 0, 130}), ChordData({16, 0, 18}), ChordData({16, 8, 8}), 
 ChordData({16, 32, 1}), ChordData({16, 32, 64}), ChordData({16, 64, 8}), ChordData({16, 64, 16}), 
 ChordData({16, 64, 128}), ChordData({18, 64, 0}), ChordData({20, 0, 1}), ChordData({20, 0, 8}), 
 ChordData({20, 0, 16}), ChordData({20, 4, 0}), ChordData({36, 0, 18}), ChordData({48, 0, 2}), 
 ChordData({48, 0, 16}), ChordData({48, 0, 64}), ChordData({48, 1, 1}), ChordData({48, 1, 128}), 
 ChordData({48, 5, 0}), ChordData({128, 0, 9}), ChordData({128, 0, 10}), ChordData({128, 0, 24}), 
 ChordData({128, 0, 128}), ChordData({128, 0, 129}), ChordData({130, 0, 8}), ChordData({130, 0, 16}), 
 ChordData({130, 0, 64}), ChordData({130, 0, 128}), 
};

uint8_t const kmap5_Word_len12_anagram0_seqs[75] = {
 114, 43, 139, 224, 
 130, 127, 175, 135, 
 175, 247, 187, 175, 
 242, 247, 68, 244, 
 58, 122, 183, 51, 
 39, 56, 34, 163, 
 67, 68, 115, 58, 
 52, 175, 63, 11, 
 106, 46, 29, 173, 
 199, 44, 204, 214, 
 176, 14, 228, 16, 
 198, 205, 215, 172, 
 109, 253, 205, 125, 
 137, 213, 117, 93, 
 197, 208, 71, 134, 
 15, 173, 121, 152, 
 170, 185, 148, 68, 
 121, 147, 58, 185, 
 35, 153, 67, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len12_anagram0 = {
  LengthAndAnagram(12, 0), // seq_bit_len_and_anagram
  50, // num_chords
  kmap5_Word_len12_anagram0_chords, // chords
  kmap5_Word_len12_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len12_anagram1_chords[21] = {
 ChordData({0, 4, 3}), ChordData({0, 4, 9}), ChordData({0, 4, 17}), ChordData({0, 4, 18}), 
 ChordData({0, 4, 129}), ChordData({2, 0, 65}), ChordData({2, 0, 66}), ChordData({2, 0, 80}), 
 ChordData({16, 1, 0}), ChordData({16, 8, 1}), ChordData({16, 32, 16}), ChordData({20, 0, 16}), 
 ChordData({22, 0, 0}), ChordData({48, 0, 64}), ChordData({48, 1, 8}), ChordData({48, 1, 16}), 
 ChordData({128, 0, 1}), ChordData({128, 0, 9}), ChordData({128, 0, 72}), ChordData({128, 0, 130}), 
 ChordData({144, 8, 0}), 
};

uint8_t const kmap5_Word_len12_anagram1_seqs[32] = {
 143, 167, 127, 191, 
 135, 191, 79, 55, 
 114, 130, 35, 179, 
 157, 29, 125, 204, 
 219, 188, 109, 44, 
 213, 208, 186, 134, 
 151, 121, 169, 146, 
 138, 73, 142, 9, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len12_anagram1 = {
  LengthAndAnagram(12, 1), // seq_bit_len_and_anagram
  21, // num_chords
  kmap5_Word_len12_anagram1_chords, // chords
  kmap5_Word_len12_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len12_anagram2_chords[10] = {
 ChordData({0, 4, 9}), ChordData({0, 4, 17}), ChordData({0, 4, 65}), ChordData({0, 4, 129}), 
 ChordData({2, 0, 9}), ChordData({2, 0, 65}), ChordData({16, 64, 8}), ChordData({48, 1, 64}), 
 ChordData({48, 1, 128}), ChordData({128, 0, 8}), 
};

uint8_t const kmap5_Word_len12_anagram2_seqs[15] = {
 247, 186, 127, 114, 
 79, 127, 55, 42, 
 115, 193, 42, 134, 
 208, 164, 169, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len12_anagram2 = {
  LengthAndAnagram(12, 2), // seq_bit_len_and_anagram
  10, // num_chords
  kmap5_Word_len12_anagram2_chords, // chords
  kmap5_Word_len12_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len12_anagram3_chords[1] = {
 ChordData({0, 4, 18}), 
};

uint8_t const kmap5_Word_len12_anagram3_seqs[2] = {
 191, 8, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len12_anagram3 = {
  LengthAndAnagram(12, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len12_anagram3_chords, // chords
  kmap5_Word_len12_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len13_anagram0_chords[71] = {
 ChordData({0, 12, 1}), ChordData({0, 12, 2}), ChordData({0, 12, 8}), ChordData({0, 12, 16}), 
 ChordData({0, 12, 128}), ChordData({0, 36, 64}), ChordData({0, 64, 65}), ChordData({0, 64, 129}), 
 ChordData({0, 64, 130}), ChordData({0, 68, 8}), ChordData({0, 68, 64}), ChordData({2, 8, 1}), 
 ChordData({2, 8, 2}), ChordData({2, 8, 8}), ChordData({2, 8, 16}), ChordData({2, 12, 0}), 
 ChordData({2, 32, 1}), ChordData({2, 32, 64}), ChordData({2, 64, 16}), ChordData({2, 64, 64}), 
 ChordData({2, 64, 128}), ChordData({2, 68, 0}), ChordData({4, 0, 129}), ChordData({4, 4, 1}), 
 ChordData({4, 4, 2}), ChordData({4, 4, 8}), ChordData({4, 4, 128}), ChordData({6, 0, 1}), 
 ChordData({6, 0, 8}), ChordData({6, 0, 16}), ChordData({16, 0, 19}), ChordData({16, 0, 26}), 
 ChordData({16, 0, 82}), ChordData({16, 40, 0}), ChordData({16, 64, 10}), ChordData({16, 72, 0}), 
 ChordData({20, 32, 0}), ChordData({32, 0, 3}), ChordData({32, 0, 9}), ChordData({32, 0, 24}), 
 ChordData({32, 0, 72}), ChordData({32, 0, 80}), ChordData({32, 1, 2}), ChordData({32, 4, 128}), 
 ChordData({32, 5, 1}), ChordData({32, 5, 2}), ChordData({32, 5, 16}), ChordData({32, 5, 64}), 
 ChordData({32, 5, 128}), ChordData({34, 1, 1}), ChordData({34, 1, 8}), ChordData({34, 1, 64}), 
 ChordData({48, 8, 2}), ChordData({48, 9, 0}), ChordData({48, 12, 0}), ChordData({48, 64, 0}), 
 ChordData({50, 8, 0}), ChordData({52, 0, 1}), ChordData({128, 8, 2}), ChordData({128, 32, 1}), 
 ChordData({128, 64, 128}), ChordData({132, 0, 1}), ChordData({132, 0, 2}), ChordData({132, 0, 16}), 
 ChordData({132, 0, 64}), ChordData({160, 0, 1}), ChordData({160, 0, 16}), ChordData({160, 0, 64}), 
 ChordData({160, 1, 1}), ChordData({160, 1, 128}), ChordData({160, 5, 0}), 
};

uint8_t const kmap5_Word_len13_anagram0_seqs[116] = {
 241, 47, 62, 198, 
 215, 223, 24, 159, 
 216, 139, 92, 40, 
 116, 132, 225, 53, 
 200, 135, 56, 23, 
 7, 227, 232, 78, 
 252, 137, 108, 142, 
 141, 132, 217, 48, 
 66, 19, 126, 66, 
 163, 187, 111, 248, 
 173, 189, 210, 183, 
 155, 214, 70, 119, 
 90, 233, 43, 173, 
 165, 37, 154, 169, 
 129, 232, 208, 152, 
 177, 158, 214, 219, 
 170, 82, 181, 202, 
 66, 196, 250, 116, 
 15, 33, 254, 47, 
 132, 47, 244, 16, 
 206, 141, 66, 25, 
 200, 25, 29, 225, 
 115, 14, 213, 195, 
 185, 247, 97, 70, 
 150, 151, 20, 46, 
 27, 102, 107, 155, 
 45, 37, 235, 101, 
 221, 172, 2, 243, 
 40, 225, 195, 4, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len13_anagram0 = {
  LengthAndAnagram(13, 0), // seq_bit_len_and_anagram
  71, // num_chords
  kmap5_Word_len13_anagram0_chords, // chords
  kmap5_Word_len13_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len13_anagram1_chords[30] = {
 ChordData({0, 12, 2}), ChordData({0, 12, 16}), ChordData({0, 32, 64}), ChordData({0, 36, 1}), 
 ChordData({0, 68, 2}), ChordData({2, 8, 64}), ChordData({2, 32, 64}), ChordData({2, 64, 16}), 
 ChordData({4, 4, 1}), ChordData({4, 4, 2}), ChordData({4, 4, 16}), ChordData({4, 4, 64}), 
 ChordData({4, 4, 128}), ChordData({6, 0, 1}), ChordData({6, 0, 2}), ChordData({6, 0, 128}), 
 ChordData({16, 1, 16}), ChordData({16, 64, 3}), ChordData({32, 0, 24}), ChordData({34, 0, 8}), 
 ChordData({48, 1, 0}), ChordData({48, 8, 16}), ChordData({48, 9, 0}), ChordData({52, 1, 0}), 
 ChordData({128, 64, 1}), ChordData({128, 64, 2}), ChordData({128, 64, 16}), ChordData({132, 0, 1}), 
 ChordData({144, 64, 2}), ChordData({160, 1, 16}), 
};

uint8_t const kmap5_Word_len13_anagram1_seqs[49] = {
 248, 113, 63, 138, 
 48, 246, 135, 31, 
 70, 226, 8, 219, 
 9, 237, 175, 61, 
 182, 95, 249, 214, 
 158, 218, 92, 27, 
 164, 105, 235, 14, 
 240, 213, 213, 170, 
 99, 8, 57, 111, 
 52, 108, 134, 33, 
 47, 36, 110, 134, 
 150, 151, 128, 115, 
 33, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len13_anagram1 = {
  LengthAndAnagram(13, 1), // seq_bit_len_and_anagram
  30, // num_chords
  kmap5_Word_len13_anagram1_chords, // chords
  kmap5_Word_len13_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len13_anagram2_chords[5] = {
 ChordData({0, 12, 64}), ChordData({4, 4, 64}), ChordData({16, 8, 0}), ChordData({48, 9, 0}), 
 ChordData({132, 0, 1}), 
};

uint8_t const kmap5_Word_len13_anagram2_seqs[9] = {
 47, 81, 218, 71, 
 71, 232, 152, 237, 
 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len13_anagram2 = {
  LengthAndAnagram(13, 2), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len13_anagram2_chords, // chords
  kmap5_Word_len13_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len13_anagram3_chords[2] = {
 ChordData({6, 0, 64}), ChordData({128, 64, 2}), 
};

uint8_t const kmap5_Word_len13_anagram3_seqs[4] = {
 50, 13, 51, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len13_anagram3 = {
  LengthAndAnagram(13, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len13_anagram3_chords, // chords
  kmap5_Word_len13_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len14_anagram0_chords[75] = {
 ChordData({0, 0, 19}), ChordData({0, 0, 90}), ChordData({0, 4, 26}), ChordData({0, 4, 82}), 
 ChordData({0, 4, 146}), ChordData({0, 5, 1}), ChordData({0, 5, 8}), ChordData({0, 5, 16}), 
 ChordData({0, 32, 129}), ChordData({0, 32, 192}), ChordData({0, 44, 0}), ChordData({0, 68, 0}), 
 ChordData({0, 68, 66}), ChordData({0, 68, 130}), ChordData({0, 76, 0}), ChordData({0, 100, 0}), 
 ChordData({2, 0, 19}), ChordData({2, 0, 146}), ChordData({2, 1, 1}), ChordData({2, 1, 2}), 
 ChordData({2, 1, 8}), ChordData({2, 40, 0}), ChordData({2, 64, 0}), ChordData({2, 64, 10}), 
 ChordData({2, 72, 0}), ChordData({4, 0, 2}), ChordData({4, 8, 1}), ChordData({4, 8, 2}), 
 ChordData({4, 8, 16}), ChordData({4, 12, 0}), ChordData({4, 68, 0}), ChordData({6, 32, 0}), 
 ChordData({6, 64, 0}), ChordData({16, 0, 10}), ChordData({16, 0, 72}), ChordData({16, 0, 192}), 
 ChordData({16, 32, 18}), ChordData({16, 65, 0}), ChordData({32, 5, 0}), ChordData({32, 8, 1}), 
 ChordData({32, 8, 8}), ChordData({32, 8, 16}), ChordData({32, 8, 64}), ChordData({32, 9, 64}), 
 ChordData({32, 12, 1}), ChordData({32, 12, 8}), ChordData({32, 12, 16}), ChordData({32, 12, 128}), 
 ChordData({32, 64, 16}), ChordData({34, 12, 0}), ChordData({34, 65, 0}), ChordData({36, 1, 64}), 
 ChordData({36, 4, 1}), ChordData({36, 4, 2}), ChordData({36, 4, 8}), ChordData({36, 4, 16}), 
 ChordData({36, 4, 128}), ChordData({38, 0, 1}), ChordData({38, 0, 8}), ChordData({38, 0, 128}), 
 ChordData({48, 72, 0}), ChordData({52, 64, 0}), ChordData({128, 0, 18}), ChordData({128, 0, 19}), 
 ChordData({128, 1, 16}), ChordData({128, 64, 3}), ChordData({128, 64, 10}), ChordData({128, 64, 18}), 
 ChordData({128, 64, 130}), ChordData({128, 72, 0}), ChordData({132, 32, 0}), ChordData({132, 64, 0}), 
 ChordData({160, 33, 0}), ChordData({160, 64, 0}), ChordData({166, 0, 0}), 
};

uint8_t const kmap5_Word_len14_anagram0_seqs[132] = {
 183, 165, 148, 250, 
 90, 202, 151, 244, 
 101, 247, 215, 189, 
 118, 191, 5, 94, 
 129, 194, 62, 126, 
 8, 192, 11, 61, 
 16, 63, 176, 15, 
 115, 229, 80, 217, 
 205, 117, 131, 163, 
 29, 155, 24, 38, 
 0, 163, 113, 2, 
 182, 118, 177, 197, 
 134, 219, 98, 252, 
 214, 62, 52, 54, 
 97, 154, 21, 45, 
 182, 154, 196, 204, 
 101, 112, 7, 31, 
 198, 122, 90, 227, 
 214, 40, 53, 70, 
 129, 220, 31, 247, 
 202, 253, 114, 79, 
 161, 46, 55, 31, 
 6, 194, 38, 247, 
 61, 126, 223, 191, 
 246, 191, 244, 125, 
 63, 215, 143, 210, 
 244, 193, 92, 239, 
 144, 91, 94, 150, 
 93, 238, 1, 169, 
 9, 108, 2, 148, 
 64, 204, 192, 178, 
 181, 12, 44, 97, 
 168, 217, 79, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  75, // num_chords
  kmap5_Word_len14_anagram0_chords, // chords
  kmap5_Word_len14_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len14_anagram1_chords[28] = {
 ChordData({0, 0, 82}), ChordData({0, 68, 0}), ChordData({0, 68, 66}), ChordData({2, 64, 3}), 
 ChordData({2, 72, 0}), ChordData({4, 4, 0}), ChordData({4, 12, 0}), ChordData({6, 32, 0}), 
 ChordData({16, 0, 17}), ChordData({16, 0, 131}), ChordData({16, 0, 144}), ChordData({16, 0, 194}), 
 ChordData({16, 64, 2}), ChordData({32, 1, 16}), ChordData({32, 12, 16}), ChordData({34, 8, 0}), 
 ChordData({36, 0, 1}), ChordData({36, 0, 2}), ChordData({36, 0, 192}), ChordData({36, 4, 1}), 
 ChordData({36, 4, 2}), ChordData({36, 5, 0}), ChordData({38, 1, 0}), ChordData({128, 8, 0}), 
 ChordData({128, 64, 0}), ChordData({128, 64, 3}), ChordData({128, 64, 10}), ChordData({160, 65, 0}), 
};

uint8_t const kmap5_Word_len14_anagram1_seqs[49] = {
 82, 74, 248, 32, 
 15, 0, 115, 97, 
 226, 183, 246, 177, 
 177, 105, 183, 246, 
 25, 180, 54, 137, 
 65, 128, 195, 86, 
 248, 220, 78, 141, 
 173, 30, 214, 70, 
 189, 244, 127, 223, 
 35, 252, 214, 6, 
 198, 140, 25, 194, 
 37, 144, 128, 134, 
 132, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len14_anagram1 = {
  LengthAndAnagram(14, 1), // seq_bit_len_and_anagram
  28, // num_chords
  kmap5_Word_len14_anagram1_chords, // chords
  kmap5_Word_len14_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len14_anagram2_chords[12] = {
 ChordData({0, 0, 18}), ChordData({0, 68, 18}), ChordData({16, 0, 9}), ChordData({16, 0, 129}), 
 ChordData({16, 65, 0}), ChordData({32, 1, 8}), ChordData({32, 8, 64}), ChordData({128, 1, 0}), 
 ChordData({132, 0, 0}), ChordData({160, 65, 0}), ChordData({164, 0, 1}), ChordData({164, 0, 16}), 
};

uint8_t const kmap5_Word_len14_anagram2_seqs[21] = {
 184, 229, 62, 112, 
 182, 158, 201, 157, 
 3, 172, 26, 171, 
 116, 153, 45, 27, 
 204, 208, 231, 109, 
 246, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len14_anagram2 = {
  LengthAndAnagram(14, 2), // seq_bit_len_and_anagram
  12, // num_chords
  kmap5_Word_len14_anagram2_chords, // chords
  kmap5_Word_len14_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len14_anagram3_chords[5] = {
 ChordData({32, 1, 8}), ChordData({32, 13, 0}), ChordData({34, 1, 0}), ChordData({128, 64, 10}), 
 ChordData({164, 0, 16}), 
};

uint8_t const kmap5_Word_len14_anagram3_seqs[9] = {
 80, 107, 124, 8, 
 7, 2, 169, 125, 
 46, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len14_anagram3 = {
  LengthAndAnagram(14, 3), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len14_anagram3_chords, // chords
  kmap5_Word_len14_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len14_anagram4_chords[3] = {
 ChordData({0, 4, 18}), ChordData({128, 64, 2}), ChordData({164, 0, 16}), 
};

uint8_t const kmap5_Word_len14_anagram4_seqs[6] = {
 251, 37, 38, 208, 
 111, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len14_anagram4 = {
  LengthAndAnagram(14, 4), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len14_anagram4_chords, // chords
  kmap5_Word_len14_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len14_anagram7_chords[1] = {
 ChordData({0, 68, 18}), 
};

uint8_t const kmap5_Word_len14_anagram7_seqs[2] = {
 192, 47, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len14_anagram7 = {
  LengthAndAnagram(14, 7), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len14_anagram7_chords, // chords
  kmap5_Word_len14_anagram7_seqs, // sequences
};

ChordData const kmap5_Word_len15_anagram0_chords[77] = {
 ChordData({0, 4, 131}), ChordData({0, 8, 82}), ChordData({0, 8, 146}), ChordData({0, 9, 1}), 
 ChordData({0, 12, 18}), ChordData({0, 13, 64}), ChordData({0, 64, 18}), ChordData({0, 64, 82}), 
 ChordData({0, 96, 128}), ChordData({2, 0, 194}), ChordData({2, 9, 1}), ChordData({2, 9, 8}), 
 ChordData({4, 0, 82}), ChordData({4, 1, 1}), ChordData({4, 4, 18}), ChordData({4, 68, 2}), 
 ChordData({16, 0, 11}), ChordData({16, 0, 25}), ChordData({16, 0, 65}), ChordData({16, 0, 67}), 
 ChordData({16, 0, 73}), ChordData({16, 0, 81}), ChordData({16, 0, 130}), ChordData({16, 0, 200}), 
 ChordData({16, 4, 10}), ChordData({16, 4, 17}), ChordData({16, 4, 24}), ChordData({16, 4, 66}), 
 ChordData({16, 4, 129}), ChordData({16, 4, 136}), ChordData({16, 4, 144}), ChordData({16, 4, 192}), 
 ChordData({16, 8, 1}), ChordData({16, 8, 16}), ChordData({16, 8, 64}), ChordData({16, 32, 16}), 
 ChordData({16, 32, 130}), ChordData({16, 64, 64}), ChordData({16, 65, 2}), ChordData({16, 73, 0}), 
 ChordData({18, 0, 3}), ChordData({18, 0, 8}), ChordData({18, 0, 10}), ChordData({18, 0, 17}), 
 ChordData({18, 0, 18}), ChordData({18, 0, 65}), ChordData({18, 0, 130}), ChordData({18, 0, 136}), 
 ChordData({20, 0, 130}), ChordData({32, 1, 8}), ChordData({32, 1, 16}), ChordData({32, 5, 18}), 
 ChordData({32, 33, 0}), ChordData({34, 1, 0}), ChordData({34, 8, 0}), ChordData({36, 0, 1}), 
 ChordData({36, 0, 16}), ChordData({36, 0, 64}), ChordData({36, 5, 0}), ChordData({36, 68, 0}), 
 ChordData({38, 1, 0}), ChordData({38, 8, 0}), ChordData({38, 64, 0}), ChordData({48, 1, 8}), 
 ChordData({52, 0, 18}), ChordData({52, 64, 2}), ChordData({128, 13, 0}), ChordData({128, 96, 2}), 
 ChordData({144, 0, 9}), ChordData({144, 0, 10}), ChordData({144, 0, 18}), ChordData({144, 0, 72}), 
 ChordData({144, 0, 80}), ChordData({144, 0, 136}), ChordData({144, 0, 144}), ChordData({144, 0, 192}), 
 ChordData({160, 0, 18}), 
};

uint8_t const kmap5_Word_len15_anagram0_seqs[145] = {
 247, 32, 41, 99, 
 25, 169, 187, 24, 
 191, 124, 41, 134, 
 45, 67, 41, 5, 
 6, 25, 80, 113, 
 110, 180, 40, 173, 
 236, 174, 181, 47, 
 219, 3, 104, 189, 
 181, 222, 89, 78, 
 140, 39, 214, 91, 
 203, 161, 137, 200, 
 42, 175, 232, 253, 
 179, 250, 23, 95, 
 76, 127, 38, 191, 
 174, 159, 228, 201, 
 209, 190, 232, 181, 
 216, 145, 121, 205, 
 12, 18, 59, 116, 
 6, 138, 193, 56, 
 103, 29, 181, 14, 
 250, 102, 237, 29, 
 148, 57, 163, 135, 
 104, 212, 6, 181, 
 174, 106, 87, 23, 
 126, 201, 42, 236, 
 6, 114, 19, 251, 
 122, 91, 123, 169, 
 125, 255, 176, 255, 
 208, 15, 156, 62, 
 246, 19, 160, 213, 
 125, 105, 192, 125, 
 126, 145, 37, 160, 
 121, 78, 69, 99, 
 174, 53, 197, 155, 
 98, 74, 245, 38, 
 153, 82, 92, 102, 
 5, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  77, // num_chords
  kmap5_Word_len15_anagram0_chords, // chords
  kmap5_Word_len15_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len15_anagram1_chords[33] = {
 ChordData({0, 9, 1}), ChordData({0, 13, 2}), ChordData({0, 68, 18}), ChordData({0, 69, 0}), 
 ChordData({4, 32, 0}), ChordData({4, 72, 0}), ChordData({16, 0, 19}), ChordData({16, 0, 129}), 
 ChordData({16, 0, 145}), ChordData({16, 0, 192}), ChordData({16, 4, 16}), ChordData({16, 4, 18}), 
 ChordData({16, 4, 24}), ChordData({16, 4, 65}), ChordData({16, 4, 129}), ChordData({16, 4, 130}), 
 ChordData({16, 4, 136}), ChordData({16, 4, 192}), ChordData({16, 32, 128}), ChordData({16, 64, 8}), 
 ChordData({18, 0, 17}), ChordData({18, 0, 18}), ChordData({18, 0, 72}), ChordData({18, 0, 80}), 
 ChordData({32, 1, 128}), ChordData({32, 9, 0}), ChordData({32, 32, 0}), ChordData({32, 72, 0}), 
 ChordData({128, 96, 2}), ChordData({144, 0, 8}), ChordData({144, 0, 9}), ChordData({144, 0, 10}), 
 ChordData({160, 1, 0}), 
};

uint8_t const kmap5_Word_len15_anagram1_seqs[62] = {
 241, 186, 199, 98, 
 248, 178, 251, 208, 
 88, 139, 45, 172, 
 241, 206, 68, 224, 
 62, 178, 200, 175, 
 31, 127, 237, 95, 
 21, 255, 221, 147, 
 233, 209, 244, 106, 
 241, 19, 179, 73, 
 237, 112, 227, 221, 
 65, 203, 168, 197, 
 59, 93, 165, 88, 
 33, 171, 44, 214, 
 0, 176, 212, 84, 
 95, 170, 49, 213, 
 93, 66, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len15_anagram1 = {
  LengthAndAnagram(15, 1), // seq_bit_len_and_anagram
  33, // num_chords
  kmap5_Word_len15_anagram1_chords, // chords
  kmap5_Word_len15_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len15_anagram2_chords[22] = {
 ChordData({0, 36, 18}), ChordData({2, 9, 64}), ChordData({16, 0, 25}), ChordData({16, 0, 72}), 
 ChordData({16, 0, 73}), ChordData({16, 0, 192}), ChordData({16, 4, 16}), ChordData({16, 4, 17}), 
 ChordData({16, 4, 18}), ChordData({16, 4, 65}), ChordData({16, 32, 1}), ChordData({18, 0, 17}), 
 ChordData({18, 0, 80}), ChordData({18, 0, 129}), ChordData({20, 0, 16}), ChordData({32, 1, 128}), 
 ChordData({32, 13, 0}), ChordData({34, 1, 0}), ChordData({36, 0, 1}), ChordData({36, 0, 64}), 
 ChordData({144, 0, 8}), ChordData({144, 0, 192}), 
};

uint8_t const kmap5_Word_len15_anagram2_seqs[42] = {
 236, 75, 41, 206, 
 121, 85, 45, 162, 
 150, 19, 19, 237, 
 175, 207, 191, 251, 
 104, 191, 220, 49, 
 123, 206, 187, 35, 
 190, 33, 55, 123, 
 59, 170, 207, 65, 
 56, 221, 213, 190, 
 175, 162, 78, 149, 
 36, 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len15_anagram2 = {
  LengthAndAnagram(15, 2), // seq_bit_len_and_anagram
  22, // num_chords
  kmap5_Word_len15_anagram2_chords, // chords
  kmap5_Word_len15_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len15_anagram3_chords[1] = {
 ChordData({16, 0, 9}), 
};

uint8_t const kmap5_Word_len15_anagram3_seqs[2] = {
 103, 61, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len15_anagram3 = {
  LengthAndAnagram(15, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len15_anagram3_chords, // chords
  kmap5_Word_len15_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len15_anagram5_chords[1] = {
 ChordData({16, 4, 16}), 
};

uint8_t const kmap5_Word_len15_anagram5_seqs[2] = {
 235, 95, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len15_anagram5 = {
  LengthAndAnagram(15, 5), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len15_anagram5_chords, // chords
  kmap5_Word_len15_anagram5_seqs, // sequences
};

ChordData const kmap5_Word_len16_anagram0_chords[140] = {
 ChordData({0, 0, 147}), ChordData({0, 1, 18}), ChordData({0, 1, 146}), ChordData({0, 4, 19}), 
 ChordData({0, 4, 67}), ChordData({0, 4, 74}), ChordData({0, 4, 129}), ChordData({0, 4, 130}), 
 ChordData({0, 4, 144}), ChordData({0, 4, 193}), ChordData({0, 8, 130}), ChordData({0, 12, 130}), 
 ChordData({0, 68, 18}), ChordData({2, 0, 80}), ChordData({2, 0, 137}), ChordData({2, 0, 192}), 
 ChordData({2, 0, 193}), ChordData({2, 1, 18}), ChordData({2, 4, 9}), ChordData({2, 4, 24}), 
 ChordData({2, 4, 129}), ChordData({2, 4, 136}), ChordData({2, 4, 144}), ChordData({2, 8, 130}), 
 ChordData({2, 73, 0}), ChordData({4, 65, 0}), ChordData({16, 0, 128}), ChordData({16, 1, 1}), 
 ChordData({16, 1, 16}), ChordData({16, 1, 128}), ChordData({16, 8, 9}), ChordData({16, 8, 17}), 
 ChordData({16, 8, 65}), ChordData({16, 8, 129}), ChordData({16, 9, 18}), ChordData({16, 12, 1}), 
 ChordData({16, 12, 2}), ChordData({16, 12, 8}), ChordData({16, 12, 64}), ChordData({16, 12, 128}), 
 ChordData({16, 32, 3}), ChordData({16, 32, 9}), ChordData({16, 32, 128}), ChordData({16, 36, 1}), 
 ChordData({16, 36, 2}), ChordData({16, 36, 16}), ChordData({16, 64, 9}), ChordData({16, 64, 18}), 
 ChordData({16, 64, 72}), ChordData({16, 64, 136}), ChordData({16, 68, 1}), ChordData({16, 68, 8}), 
 ChordData({16, 68, 16}), ChordData({16, 68, 128}), ChordData({18, 8, 1}), ChordData({18, 8, 2}), 
 ChordData({18, 8, 8}), ChordData({18, 8, 64}), ChordData({18, 8, 128}), ChordData({18, 32, 16}), 
 ChordData({18, 64, 1}), ChordData({18, 64, 16}), ChordData({18, 64, 64}), ChordData({18, 64, 128}), 
 ChordData({18, 68, 0}), ChordData({20, 0, 65}), ChordData({20, 0, 66}), ChordData({20, 0, 144}), 
 ChordData({20, 4, 1}), ChordData({20, 4, 2}), ChordData({20, 4, 64}), ChordData({20, 4, 128}), 
 ChordData({20, 8, 8}), ChordData({20, 64, 0}), ChordData({22, 0, 8}), ChordData({22, 0, 16}), 
 ChordData({22, 0, 128}), ChordData({22, 8, 0}), ChordData({32, 1, 18}), ChordData({32, 4, 130}), 
 ChordData({32, 8, 18}), ChordData({32, 9, 18}), ChordData({32, 72, 0}), ChordData({32, 76, 2}), 
 ChordData({36, 1, 0}), ChordData({36, 32, 0}), ChordData({48, 0, 3}), ChordData({48, 0, 9}), 
 ChordData({48, 0, 17}), ChordData({48, 0, 18}), ChordData({48, 0, 80}), ChordData({48, 0, 144}), 
 ChordData({48, 5, 1}), ChordData({48, 5, 2}), ChordData({48, 5, 64}), ChordData({48, 8, 8}), 
 ChordData({48, 8, 16}), ChordData({48, 65, 0}), ChordData({52, 0, 8}), ChordData({128, 0, 17}), 
 ChordData({128, 0, 25}), ChordData({128, 0, 67}), ChordData({128, 0, 72}), ChordData({128, 0, 81}), 
 ChordData({128, 0, 130}), ChordData({128, 0, 144}), ChordData({128, 0, 192}), ChordData({128, 0, 193}), 
 ChordData({128, 4, 3}), ChordData({128, 4, 8}), ChordData({128, 4, 18}), ChordData({128, 4, 136}), 
 ChordData({128, 4, 144}), ChordData({128, 4, 192}), ChordData({130, 0, 9}), ChordData({130, 0, 10}), 
 ChordData({130, 0, 24}), ChordData({130, 0, 72}), ChordData({130, 0, 130}), ChordData({130, 0, 136}), 
 ChordData({130, 0, 192}), ChordData({144, 8, 1}), ChordData({144, 8, 2}), ChordData({144, 8, 16}), 
 ChordData({144, 8, 64}), ChordData({144, 32, 2}), ChordData({144, 32, 16}), ChordData({144, 32, 64}), 
 ChordData({144, 64, 2}), ChordData({144, 64, 8}), ChordData({144, 64, 64}), ChordData({148, 0, 1}), 
 ChordData({148, 0, 2}), ChordData({148, 0, 8}), ChordData({148, 0, 64}), ChordData({164, 0, 18}), 
 ChordData({164, 64, 2}), ChordData({176, 0, 16}), ChordData({176, 1, 8}), ChordData({176, 1, 64}), 
};

uint8_t const kmap5_Word_len16_anagram0_seqs[280] = {
 120, 75, 221, 150, 
 29, 149, 248, 123, 
 248, 114, 130, 175, 
 247, 68, 248, 68, 
 224, 191, 244, 114, 
 160, 72, 241, 65, 
 192, 151, 179, 35, 
 52, 122, 50, 68, 
 52, 114, 211, 149, 
 175, 55, 251, 163, 
 247, 67, 250, 67, 
 251, 67, 113, 64, 
 197, 9, 45, 116, 
 60, 217, 157, 125, 
 221, 218, 157, 77, 
 209, 122, 231, 141, 
 114, 142, 209, 116, 
 69, 151, 231, 143, 
 248, 209, 250, 209, 
 242, 209, 209, 79, 
 103, 100, 199, 172, 
 204, 68, 204, 127, 
 126, 100, 204, 191, 
 103, 13, 128, 215, 
 98, 13, 100, 13, 
 225, 207, 193, 175, 
 235, 15, 193, 79, 
 55, 209, 113, 208, 
 113, 212, 226, 56, 
 113, 200, 108, 214, 
 14, 115, 59, 193, 
 50, 193, 19, 200, 
 19, 252, 114, 110, 
 210, 140, 205, 75, 
 247, 205, 248, 205, 
 205, 47, 237, 201, 
 5, 173, 193, 110, 
 109, 212, 59, 205, 
 109, 200, 83, 208, 
 176, 150, 95, 65, 
 101, 141, 176, 140, 
 129, 11, 192, 115, 
 125, 133, 172, 246, 
 88, 207, 87, 213, 
 183, 213, 88, 215, 
 82, 215, 91, 201, 
 240, 207, 248, 208, 
 242, 208, 230, 172, 
 230, 188, 14, 208, 
 189, 173, 155, 121, 
 183, 169, 152, 114, 
 146, 169, 146, 123, 
 152, 73, 155, 68, 
 148, 34, 148, 114, 
 152, 127, 250, 154, 
 185, 248, 148, 175, 
 185, 79, 79, 146, 
 55, 169, 131, 169, 
 179, 169, 50, 169, 
 152, 67, 52, 169, 
 146, 67, 49, 207, 
 152, 209, 49, 215, 
 146, 209, 70, 150, 
 204, 155, 194, 210, 
 152, 193, 33, 213, 
 33, 45, 45, 125, 
 152, 205, 217, 172, 
 45, 197, 125, 150, 
 125, 2, 174, 155, 
 48, 213, 48, 45, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  140, // num_chords
  kmap5_Word_len16_anagram0_chords, // chords
  kmap5_Word_len16_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len16_anagram1_chords[42] = {
 ChordData({0, 4, 65}), ChordData({0, 4, 81}), ChordData({0, 4, 130}), ChordData({0, 4, 193}), 
 ChordData({2, 0, 9}), ChordData({2, 0, 129}), ChordData({2, 4, 129}), ChordData({2, 4, 192}), 
 ChordData({6, 0, 130}), ChordData({16, 8, 64}), ChordData({16, 12, 1}), ChordData({16, 12, 8}), 
 ChordData({16, 12, 128}), ChordData({16, 36, 1}), ChordData({16, 36, 2}), ChordData({16, 64, 24}), 
 ChordData({16, 68, 16}), ChordData({16, 68, 128}), ChordData({16, 72, 0}), ChordData({18, 8, 1}), 
 ChordData({18, 8, 128}), ChordData({18, 64, 1}), ChordData({22, 0, 2}), ChordData({38, 0, 0}), 
 ChordData({48, 0, 80}), ChordData({48, 5, 16}), ChordData({52, 0, 16}), ChordData({128, 0, 129}), 
 ChordData({128, 0, 192}), ChordData({128, 0, 193}), ChordData({128, 1, 0}), ChordData({128, 4, 129}), 
 ChordData({128, 4, 130}), ChordData({130, 0, 9}), ChordData({130, 0, 10}), ChordData({144, 32, 64}), 
 ChordData({144, 32, 128}), ChordData({144, 64, 8}), ChordData({144, 64, 64}), ChordData({148, 0, 8}), 
 ChordData({148, 0, 16}), ChordData({148, 0, 128}), 
};

uint8_t const kmap5_Word_len16_anagram1_seqs[84] = {
 114, 127, 114, 191, 
 248, 132, 242, 116, 
 163, 115, 55, 116, 
 55, 79, 242, 67, 
 109, 64, 209, 34, 
 241, 207, 209, 175, 
 241, 201, 236, 207, 
 143, 204, 234, 13, 
 193, 191, 228, 15, 
 193, 142, 115, 142, 
 52, 209, 97, 124, 
 110, 131, 253, 244, 
 85, 188, 208, 191, 
 189, 189, 151, 73, 
 146, 148, 66, 121, 
 217, 117, 79, 151, 
 152, 79, 163, 151, 
 152, 163, 44, 197, 
 44, 201, 154, 193, 
 33, 197, 154, 205, 
 155, 205, 45, 201, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len16_anagram1 = {
  LengthAndAnagram(16, 1), // seq_bit_len_and_anagram
  42, // num_chords
  kmap5_Word_len16_anagram1_chords, // chords
  kmap5_Word_len16_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len16_anagram2_chords[16] = {
 ChordData({0, 4, 3}), ChordData({2, 0, 193}), ChordData({16, 12, 1}), ChordData({16, 68, 16}), 
 ChordData({18, 64, 1}), ChordData({18, 64, 2}), ChordData({20, 4, 2}), ChordData({36, 0, 0}), 
 ChordData({36, 4, 18}), ChordData({48, 1, 8}), ChordData({48, 5, 16}), ChordData({128, 0, 129}), 
 ChordData({128, 64, 2}), ChordData({144, 64, 8}), ChordData({148, 0, 16}), ChordData({176, 1, 16}), 
};

uint8_t const kmap5_Word_len16_anagram2_seqs[32] = {
 247, 120, 66, 115, 
 209, 127, 225, 215, 
 55, 193, 97, 208, 
 237, 209, 173, 246, 
 253, 151, 86, 168, 
 251, 208, 151, 68, 
 64, 2, 214, 144, 
 235, 150, 48, 215, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len16_anagram2 = {
  LengthAndAnagram(16, 2), // seq_bit_len_and_anagram
  16, // num_chords
  kmap5_Word_len16_anagram2_chords, // chords
  kmap5_Word_len16_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len16_anagram3_chords[4] = {
 ChordData({16, 8, 0}), ChordData({16, 12, 1}), ChordData({20, 4, 16}), ChordData({128, 0, 8}), 
};

uint8_t const kmap5_Word_len16_anagram3_seqs[8] = {
 209, 209, 209, 247, 
 235, 111, 154, 169, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len16_anagram3 = {
  LengthAndAnagram(16, 3), // seq_bit_len_and_anagram
  4, // num_chords
  kmap5_Word_len16_anagram3_chords, // chords
  kmap5_Word_len16_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len17_anagram0_chords[173] = {
 ChordData({0, 5, 130}), ChordData({0, 9, 82}), ChordData({0, 12, 17}), ChordData({0, 12, 64}), 
 ChordData({0, 12, 80}), ChordData({0, 36, 1}), ChordData({0, 36, 3}), ChordData({0, 36, 9}), 
 ChordData({0, 36, 10}), ChordData({0, 36, 18}), ChordData({0, 36, 66}), ChordData({0, 36, 128}), 
 ChordData({0, 36, 129}), ChordData({0, 64, 192}), ChordData({0, 68, 1}), ChordData({0, 68, 17}), 
 ChordData({0, 68, 24}), ChordData({0, 68, 72}), ChordData({0, 68, 136}), ChordData({0, 77, 2}), 
 ChordData({0, 96, 18}), ChordData({2, 1, 130}), ChordData({2, 8, 9}), ChordData({2, 8, 17}), 
 ChordData({2, 8, 64}), ChordData({2, 8, 66}), ChordData({2, 8, 128}), ChordData({2, 8, 192}), 
 ChordData({2, 12, 8}), ChordData({2, 12, 128}), ChordData({2, 32, 9}), ChordData({2, 32, 10}), 
 ChordData({2, 32, 18}), ChordData({2, 32, 65}), ChordData({2, 36, 16}), ChordData({2, 64, 3}), 
 ChordData({2, 64, 17}), ChordData({2, 64, 65}), ChordData({2, 64, 66}), ChordData({2, 64, 192}), 
 ChordData({2, 68, 2}), ChordData({2, 68, 16}), ChordData({2, 68, 64}), ChordData({2, 68, 128}), 
 ChordData({4, 4, 16}), ChordData({4, 4, 17}), ChordData({4, 4, 64}), ChordData({4, 4, 65}), 
 ChordData({4, 4, 72}), ChordData({4, 4, 136}), ChordData({6, 0, 17}), ChordData({6, 0, 72}), 
 ChordData({6, 0, 128}), ChordData({6, 0, 130}), ChordData({6, 0, 192}), ChordData({6, 4, 8}), 
 ChordData({6, 4, 16}), ChordData({16, 0, 146}), ChordData({16, 1, 129}), ChordData({16, 1, 192}), 
 ChordData({16, 4, 18}), ChordData({16, 4, 82}), ChordData({16, 5, 1}), ChordData({16, 5, 2}), 
 ChordData({16, 5, 16}), ChordData({16, 5, 64}), ChordData({16, 5, 128}), ChordData({16, 9, 8}), 
 ChordData({16, 9, 64}), ChordData({16, 32, 144}), ChordData({16, 40, 1}), ChordData({16, 40, 2}), 
 ChordData({16, 40, 64}), ChordData({16, 40, 128}), ChordData({16, 64, 11}), ChordData({16, 64, 130}), 
 ChordData({16, 68, 0}), ChordData({16, 72, 8}), ChordData({16, 76, 0}), ChordData({16, 96, 64}), 
 ChordData({16, 96, 128}), ChordData({16, 100, 0}), ChordData({18, 1, 8}), ChordData({18, 1, 16}), 
 ChordData({18, 1, 64}), ChordData({18, 1, 128}), ChordData({18, 8, 0}), ChordData({18, 64, 10}), 
 ChordData({18, 64, 18}), ChordData({18, 64, 66}), ChordData({18, 72, 0}), ChordData({18, 96, 0}), 
 ChordData({20, 8, 1}), ChordData({20, 32, 128}), ChordData({20, 36, 0}), ChordData({20, 64, 2}), 
 ChordData({22, 0, 0}), ChordData({32, 0, 25}), ChordData({32, 0, 81}), ChordData({32, 0, 131}), 
 ChordData({32, 0, 136}), ChordData({32, 5, 136}), ChordData({34, 0, 9}), ChordData({34, 0, 65}), 
 ChordData({34, 0, 129}), ChordData({34, 1, 24}), ChordData({34, 1, 72}), ChordData({34, 1, 128}), 
 ChordData({34, 1, 144}), ChordData({34, 5, 128}), ChordData({48, 1, 16}), ChordData({48, 8, 17}), 
 ChordData({48, 8, 65}), ChordData({48, 12, 2}), ChordData({48, 64, 2}), ChordData({48, 64, 8}), 
 ChordData({48, 64, 16}), ChordData({50, 8, 2}), ChordData({50, 8, 128}), ChordData({52, 0, 9}), 
 ChordData({52, 0, 16}), ChordData({52, 0, 65}), ChordData({52, 1, 16}), ChordData({52, 4, 1}), 
 ChordData({52, 4, 8}), ChordData({52, 4, 16}), ChordData({52, 4, 64}), ChordData({52, 4, 128}), 
 ChordData({52, 5, 0}), ChordData({54, 0, 1}), ChordData({54, 0, 128}), ChordData({128, 1, 130}), 
 ChordData({128, 8, 1}), ChordData({128, 8, 16}), ChordData({128, 8, 24}), ChordData({128, 8, 64}), 
 ChordData({128, 8, 65}), ChordData({128, 8, 129}), ChordData({128, 12, 1}), ChordData({128, 12, 64}), 
 ChordData({128, 32, 65}), ChordData({128, 64, 16}), ChordData({128, 64, 129}), ChordData({128, 64, 144}), 
 ChordData({128, 64, 192}), ChordData({128, 68, 16}), ChordData({128, 68, 128}), ChordData({130, 8, 1}), 
 ChordData({130, 64, 128}), ChordData({132, 0, 17}), ChordData({132, 0, 65}), ChordData({132, 0, 128}), 
 ChordData({132, 0, 129}), ChordData({132, 4, 64}), ChordData({144, 8, 0}), ChordData({144, 40, 0}), 
 ChordData({144, 72, 0}), ChordData({148, 8, 0}), ChordData({148, 32, 0}), ChordData({160, 0, 8}), 
 ChordData({160, 0, 17}), ChordData({160, 0, 192}), ChordData({160, 1, 72}), ChordData({160, 1, 136}), 
 ChordData({160, 4, 1}), ChordData({160, 5, 128}), ChordData({162, 0, 64}), ChordData({164, 0, 130}), 
 ChordData({176, 8, 1}), ChordData({176, 8, 8}), ChordData({176, 8, 16}), ChordData({176, 8, 128}), 
 ChordData({180, 0, 8}), 
};

uint8_t const kmap5_Word_len17_anagram0_seqs[368] = {
 221, 131, 164, 88, 
 198, 223, 139, 47, 
 18, 127, 229, 216, 
 31, 178, 191, 99, 
 175, 200, 94, 145, 
 253, 226, 11, 99, 
 79, 196, 158, 78, 
 10, 81, 248, 251, 
 240, 123, 251, 26, 
 228, 53, 208, 107, 
 120, 160, 8, 176, 
 178, 27, 80, 28, 
 189, 219, 137, 113, 
 68, 226, 8, 198, 
 33, 18, 154, 24, 
 127, 52, 254, 16, 
 27, 189, 81, 100, 
 59, 200, 142, 141, 
 176, 159, 13, 131, 
 23, 102, 47, 140, 
 92, 24, 65, 161, 
 9, 143, 19, 246, 
 39, 200, 79, 160, 
 159, 208, 126, 191, 
 253, 94, 123, 145, 
 246, 114, 162, 223, 
 26, 189, 222, 78, 
 147, 54, 218, 134, 
 8, 105, 26, 141, 
 180, 246, 163, 237, 
 103, 215, 84, 146, 
 187, 19, 83, 87, 
 250, 215, 47, 101, 
 231, 191, 238, 209, 
 157, 127, 229, 59, 
 119, 228, 47, 170, 
 45, 118, 177, 192, 
 245, 49, 199, 104, 
 100, 209, 194, 152, 
 41, 2, 214, 3, 
 76, 20, 252, 33, 
 90, 67, 252, 96, 
 97, 14, 204, 20, 
 152, 63, 116, 163, 
 238, 102, 221, 141, 
 165, 27, 114, 156, 
 104, 96, 212, 192, 
 172, 129, 17, 7, 
 199, 97, 19, 124, 
 142, 141, 153, 26, 
 243, 55, 192, 110, 
 109, 154, 175, 174, 
 110, 149, 195, 74, 
 167, 149, 136, 94, 
 97, 213, 57, 169, 
 115, 245, 134, 118, 
 20, 202, 40, 132, 
 67, 4, 103, 9, 
 210, 124, 93, 104, 
 206, 123, 156, 229, 
 240, 57, 135, 138, 
 214, 26, 188, 53, 
 152, 27, 180, 185, 
 161, 222, 122, 173, 
 174, 123, 203, 193, 
 117, 235, 125, 223, 
 251, 181, 255, 117, 
 255, 226, 239, 201, 
 237, 161, 251, 57, 
 79, 79, 238, 18, 
 20, 51, 111, 51, 
 163, 230, 198, 152, 
 34, 49, 229, 46, 
 35, 253, 101, 148, 
 140, 207, 82, 46, 
 100, 238, 37, 5, 
 202, 13, 146, 20, 
 54, 63, 80, 126, 
 200, 56, 55, 33, 
 169, 229, 158, 92, 
 54, 202, 108, 141, 
 242, 36, 191, 69, 
 199, 100, 25, 29, 
 51, 184, 165, 35, 
 203, 102, 205, 170, 
 151, 117, 37, 169, 
 74, 42, 164, 84, 
 248, 245, 18, 230, 
 211, 100, 149, 62, 
 65, 92, 158, 147, 
 179, 38, 231, 165, 
 228, 220, 167, 26, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len17_anagram0 = {
  LengthAndAnagram(17, 0), // seq_bit_len_and_anagram
  173, // num_chords
  kmap5_Word_len17_anagram0_chords, // chords
  kmap5_Word_len17_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len17_anagram1_chords[65] = {
 ChordData({0, 12, 130}), ChordData({0, 12, 144}), ChordData({0, 36, 18}), ChordData({2, 8, 8}), 
 ChordData({2, 8, 65}), ChordData({2, 12, 128}), ChordData({2, 32, 9}), ChordData({2, 32, 65}), 
 ChordData({2, 32, 128}), ChordData({2, 68, 128}), ChordData({4, 4, 18}), ChordData({4, 4, 72}), 
 ChordData({6, 0, 192}), ChordData({16, 1, 128}), ChordData({16, 1, 129}), ChordData({16, 5, 1}), 
 ChordData({16, 5, 2}), ChordData({16, 5, 16}), ChordData({16, 5, 128}), ChordData({16, 9, 8}), 
 ChordData({16, 64, 18}), ChordData({16, 64, 67}), ChordData({16, 64, 146}), ChordData({16, 65, 0}), 
 ChordData({18, 1, 16}), ChordData({18, 1, 128}), ChordData({20, 64, 8}), ChordData({20, 64, 64}), 
 ChordData({32, 5, 65}), ChordData({34, 1, 72}), ChordData({34, 5, 8}), ChordData({36, 0, 18}), 
 ChordData({48, 1, 128}), ChordData({48, 8, 8}), ChordData({48, 12, 64}), ChordData({48, 13, 0}), 
 ChordData({50, 8, 8}), ChordData({50, 8, 128}), ChordData({52, 0, 0}), ChordData({52, 0, 128}), 
 ChordData({52, 0, 129}), ChordData({52, 4, 1}), ChordData({52, 4, 16}), ChordData({128, 8, 8}), 
 ChordData({128, 8, 24}), ChordData({128, 32, 24}), ChordData({128, 32, 65}), ChordData({128, 36, 128}), 
 ChordData({128, 64, 128}), ChordData({128, 64, 130}), ChordData({132, 0, 16}), ChordData({132, 0, 18}), 
 ChordData({132, 0, 64}), ChordData({132, 0, 65}), ChordData({132, 0, 128}), ChordData({132, 0, 192}), 
 ChordData({132, 8, 0}), ChordData({144, 1, 16}), ChordData({144, 72, 0}), ChordData({160, 0, 192}), 
 ChordData({160, 1, 1}), ChordData({160, 1, 128}), ChordData({160, 5, 1}), ChordData({160, 5, 128}), 
 ChordData({180, 0, 16}), 
};

uint8_t const kmap5_Word_len17_anagram1_seqs[139] = {
 248, 20, 193, 63, 
 254, 34, 139, 163, 
 35, 55, 113, 226, 
 211, 177, 81, 97, 
 115, 108, 136, 194, 
 60, 225, 126, 147, 
 246, 42, 52, 173, 
 51, 81, 103, 186, 
 238, 207, 248, 157, 
 187, 95, 147, 191, 
 43, 218, 138, 107, 
 0, 176, 28, 184, 
 129, 206, 14, 221, 
 120, 105, 58, 55, 
 107, 144, 230, 32, 
 247, 80, 6, 42, 
 252, 209, 190, 150, 
 144, 170, 173, 53, 
 202, 115, 134, 31, 
 205, 121, 148, 134, 
 115, 111, 183, 222, 
 68, 189, 233, 122, 
 255, 245, 254, 141, 
 169, 25, 115, 149, 
 229, 170, 176, 60, 
 246, 148, 33, 137, 
 48, 41, 180, 204, 
 197, 205, 150, 217, 
 164, 165, 92, 75, 
 34, 161, 108, 5, 
 51, 187, 92, 7, 
 199, 148, 172, 4, 
 243, 146, 18, 38, 
 204, 191, 39, 152, 
 125, 174, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len17_anagram1 = {
  LengthAndAnagram(17, 1), // seq_bit_len_and_anagram
  65, // num_chords
  kmap5_Word_len17_anagram1_chords, // chords
  kmap5_Word_len17_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len17_anagram2_chords[18] = {
 ChordData({0, 12, 130}), ChordData({0, 68, 130}), ChordData({2, 32, 65}), ChordData({4, 4, 17}), 
 ChordData({6, 0, 64}), ChordData({16, 0, 130}), ChordData({16, 64, 2}), ChordData({16, 68, 18}), 
 ChordData({34, 1, 144}), ChordData({36, 1, 0}), ChordData({48, 8, 8}), ChordData({48, 12, 128}), 
 ChordData({48, 13, 0}), ChordData({128, 8, 8}), ChordData({128, 32, 1}), ChordData({132, 0, 18}), 
 ChordData({132, 0, 65}), ChordData({132, 0, 128}), 
};

uint8_t const kmap5_Word_len17_anagram2_seqs[39] = {
 72, 31, 129, 7, 
 177, 145, 187, 253, 
 214, 70, 196, 32, 
 35, 96, 7, 224, 
 215, 224, 3, 251, 
 218, 69, 107, 53, 
 247, 20, 13, 63, 
 102, 42, 203, 188, 
 182, 137, 210, 242, 
 90, 38, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len17_anagram2 = {
  LengthAndAnagram(17, 2), // seq_bit_len_and_anagram
  18, // num_chords
  kmap5_Word_len17_anagram2_chords, // chords
  kmap5_Word_len17_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len17_anagram3_chords[3] = {
 ChordData({16, 68, 18}), ChordData({20, 0, 16}), ChordData({128, 64, 18}), 
};

uint8_t const kmap5_Word_len17_anagram3_seqs[7] = {
 128, 127, 219, 186, 
 97, 110, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len17_anagram3 = {
  LengthAndAnagram(17, 3), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len17_anagram3_chords, // chords
  kmap5_Word_len17_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len17_anagram5_chords[1] = {
 ChordData({0, 68, 18}), 
};

uint8_t const kmap5_Word_len17_anagram5_seqs[3] = {
 248, 27, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len17_anagram5 = {
  LengthAndAnagram(17, 5), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len17_anagram5_chords, // chords
  kmap5_Word_len17_anagram5_seqs, // sequences
};

ChordData const kmap5_Word_len18_anagram0_chords[147] = {
 ChordData({0, 4, 83}), ChordData({0, 5, 3}), ChordData({0, 5, 65}), ChordData({0, 5, 128}), 
 ChordData({0, 5, 129}), ChordData({0, 32, 137}), ChordData({0, 40, 129}), ChordData({0, 44, 1}), 
 ChordData({0, 44, 16}), ChordData({0, 44, 64}), ChordData({0, 68, 11}), ChordData({0, 68, 26}), 
 ChordData({0, 68, 138}), ChordData({0, 76, 8}), ChordData({0, 100, 8}), ChordData({0, 100, 16}), 
 ChordData({0, 100, 64}), ChordData({2, 0, 27}), ChordData({2, 1, 65}), ChordData({2, 1, 128}), 
 ChordData({2, 1, 129}), ChordData({2, 5, 16}), ChordData({2, 5, 128}), ChordData({2, 64, 11}), 
 ChordData({2, 64, 130}), ChordData({2, 68, 3}), ChordData({2, 72, 8}), ChordData({2, 72, 128}), 
 ChordData({2, 96, 64}), ChordData({4, 8, 65}), ChordData({4, 12, 2}), ChordData({4, 12, 64}), 
 ChordData({4, 12, 128}), ChordData({4, 36, 1}), ChordData({4, 36, 16}), ChordData({4, 40, 64}), 
 ChordData({6, 8, 0}), ChordData({6, 8, 128}), ChordData({6, 12, 0}), ChordData({6, 32, 2}), 
 ChordData({6, 32, 64}), ChordData({6, 68, 0}), ChordData({16, 0, 74}), ChordData({16, 0, 131}), 
 ChordData({16, 0, 139}), ChordData({16, 9, 10}), ChordData({16, 9, 17}), ChordData({16, 13, 1}), 
 ChordData({16, 13, 2}), ChordData({16, 13, 64}), ChordData({16, 13, 128}), ChordData({16, 32, 19}), 
 ChordData({16, 33, 2}), ChordData({16, 36, 18}), ChordData({16, 64, 26}), ChordData({16, 65, 8}), 
 ChordData({16, 69, 0}), ChordData({16, 96, 10}), ChordData({18, 9, 128}), ChordData({18, 65, 0}), 
 ChordData({20, 9, 0}), ChordData({20, 40, 0}), ChordData({32, 1, 136}), ChordData({32, 5, 8}), 
 ChordData({32, 8, 65}), ChordData({32, 12, 65}), ChordData({32, 13, 16}), ChordData({32, 32, 9}), 
 ChordData({32, 32, 65}), ChordData({32, 32, 66}), ChordData({32, 32, 80}), ChordData({32, 32, 128}), 
 ChordData({32, 36, 1}), ChordData({32, 37, 8}), ChordData({32, 64, 65}), ChordData({32, 68, 16}), 
 ChordData({32, 69, 16}), ChordData({32, 69, 128}), ChordData({34, 12, 16}), ChordData({34, 12, 64}), 
 ChordData({34, 12, 128}), ChordData({34, 65, 16}), ChordData({36, 0, 9}), ChordData({36, 0, 72}), 
 ChordData({36, 0, 128}), ChordData({36, 0, 192}), ChordData({36, 1, 144}), ChordData({36, 4, 18}), 
 ChordData({36, 4, 64}), ChordData({38, 1, 8}), ChordData({38, 1, 16}), ChordData({38, 4, 128}), 
 ChordData({48, 1, 18}), ChordData({48, 13, 0}), ChordData({48, 33, 0}), ChordData({48, 44, 0}), 
 ChordData({48, 65, 18}), ChordData({48, 69, 2}), ChordData({48, 72, 8}), ChordData({50, 9, 0}), 
 ChordData({52, 0, 2}), ChordData({52, 0, 128}), ChordData({52, 1, 0}), ChordData({52, 8, 16}), 
 ChordData({52, 12, 0}), ChordData({52, 32, 16}), ChordData({52, 64, 1}), ChordData({52, 64, 8}), 
 ChordData({52, 68, 0}), ChordData({128, 0, 154}), ChordData({128, 1, 1}), ChordData({128, 1, 9}), 
 ChordData({128, 1, 10}), ChordData({128, 1, 17}), ChordData({128, 1, 65}), ChordData({128, 1, 128}), 
 ChordData({128, 5, 64}), ChordData({128, 64, 11}), ChordData({128, 64, 26}), ChordData({128, 64, 67}), 
 ChordData({128, 64, 74}), ChordData({128, 64, 194}), ChordData({128, 72, 128}), ChordData({128, 96, 0}), 
 ChordData({128, 96, 128}), ChordData({130, 1, 8}), ChordData({132, 8, 2}), ChordData({132, 32, 64}), 
 ChordData({132, 64, 8}), ChordData({132, 64, 16}), ChordData({160, 8, 129}), ChordData({160, 12, 8}), 
 ChordData({160, 12, 128}), ChordData({160, 32, 16}), ChordData({160, 64, 2}), ChordData({160, 64, 64}), 
 ChordData({160, 64, 128}), ChordData({160, 65, 0}), ChordData({160, 65, 128}), ChordData({164, 0, 24}), 
 ChordData({164, 0, 64}), ChordData({164, 0, 128}), ChordData({164, 0, 129}), ChordData({164, 0, 144}), 
 ChordData({166, 0, 64}), ChordData({176, 1, 0}), ChordData({176, 8, 0}), 
};

uint8_t const kmap5_Word_len18_anagram0_seqs[331] = {
 114, 95, 118, 143, 
 215, 189, 92, 247, 
 68, 29, 253, 105, 
 129, 199, 46, 82, 
 252, 99, 236, 55, 
 198, 23, 6, 188, 
 30, 240, 171, 244, 
 128, 134, 143, 202, 
 94, 3, 251, 13, 
 225, 133, 221, 104, 
 217, 141, 92, 55, 
 68, 52, 221, 117, 
 63, 219, 253, 208, 
 1, 163, 192, 16, 
 1, 63, 23, 71, 
 67, 28, 10, 97, 
 132, 73, 188, 134, 
 31, 155, 180, 143, 
 244, 177, 181, 63, 
 198, 126, 91, 65, 
 97, 5, 167, 77, 
 108, 52, 241, 27, 
 178, 105, 194, 166, 
 181, 159, 32, 104, 
 245, 25, 116, 106, 
 208, 169, 177, 120, 
 235, 226, 125, 209, 
 248, 69, 203, 23, 
 77, 254, 226, 49, 
 151, 200, 220, 149, 
 126, 22, 172, 101, 
 112, 167, 221, 7, 
 3, 204, 74, 83, 
 116, 55, 14, 69, 
 187, 57, 54, 70, 
 85, 33, 124, 133, 
 177, 202, 113, 47, 
 7, 247, 35, 171, 
 122, 194, 234, 73, 
 69, 182, 85, 24, 
 171, 68, 95, 143, 
 177, 87, 24, 170, 
 92, 168, 251, 112, 
 63, 64, 250, 192, 
 253, 14, 55, 242, 
 220, 60, 193, 157, 
 208, 170, 158, 180, 
 170, 173, 18, 53, 
 170, 2, 222, 32, 
 254, 246, 253, 139, 
 180, 81, 8, 119, 
 90, 255, 67, 112, 
 93, 194, 231, 204, 
 42, 52, 123, 206, 
 112, 13, 0, 15, 
 205, 89, 3, 28, 
 206, 88, 123, 247, 
 84, 221, 219, 93, 
 91, 115, 189, 63, 
 50, 111, 31, 220, 
 95, 111, 13, 189, 
 63, 164, 82, 217, 
 101, 94, 151, 122, 
 152, 218, 117, 185, 
 39, 217, 93, 151, 
 73, 146, 221, 95, 
 2, 10, 228, 170, 
 92, 2, 162, 9, 
 8, 37, 16, 147, 
 2, 203, 12, 44, 
 41, 140, 118, 137, 
 25, 155, 176, 108, 
 45, 53, 132, 205, 
 198, 37, 157, 38, 
 247, 201, 61, 177, 
 172, 27, 18, 171, 
 212, 144, 148, 53, 
 192, 204, 0, 147, 
 66, 159, 171, 146, 
 181, 245, 153, 212, 
 39, 29, 120, 246, 
 253, 164, 240, 208, 
 25, 147, 51, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  147, // num_chords
  kmap5_Word_len18_anagram0_chords, // chords
  kmap5_Word_len18_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len18_anagram1_chords[40] = {
 ChordData({0, 0, 90}), ChordData({0, 4, 26}), ChordData({0, 4, 146}), ChordData({0, 5, 130}), 
 ChordData({0, 32, 128}), ChordData({0, 36, 64}), ChordData({0, 68, 130}), ChordData({2, 0, 19}), 
 ChordData({4, 12, 16}), ChordData({4, 12, 64}), ChordData({4, 12, 128}), ChordData({4, 32, 1}), 
 ChordData({16, 0, 25}), ChordData({16, 0, 72}), ChordData({16, 0, 73}), ChordData({16, 0, 193}), 
 ChordData({16, 69, 0}), ChordData({18, 0, 131}), ChordData({18, 64, 2}), ChordData({20, 0, 19}), 
 ChordData({20, 9, 0}), ChordData({32, 32, 17}), ChordData({32, 32, 65}), ChordData({32, 64, 65}), 
 ChordData({32, 68, 128}), ChordData({36, 4, 24}), ChordData({36, 4, 192}), ChordData({38, 4, 64}), 
 ChordData({48, 1, 64}), ChordData({48, 64, 0}), ChordData({52, 0, 1}), ChordData({128, 0, 146}), 
 ChordData({128, 1, 16}), ChordData({128, 72, 0}), ChordData({164, 0, 1}), ChordData({164, 0, 16}), 
 ChordData({164, 0, 64}), ChordData({164, 0, 144}), ChordData({164, 1, 16}), ChordData({164, 4, 1}), 
};

uint8_t const kmap5_Word_len18_anagram1_seqs[90] = {
 82, 42, 150, 191, 
 250, 68, 37, 62, 
 117, 5, 18, 177, 
 23, 6, 60, 17, 
 206, 149, 251, 177, 
 181, 151, 216, 158, 
 34, 187, 107, 214, 
 243, 138, 85, 124, 
 86, 177, 156, 77, 
 193, 223, 25, 52, 
 7, 76, 240, 149, 
 205, 205, 46, 178, 
 186, 119, 172, 138, 
 92, 13, 161, 62, 
 245, 191, 42, 244, 
 125, 63, 47, 93, 
 21, 135, 26, 124, 
 181, 55, 120, 150, 
 155, 217, 197, 204, 
 208, 103, 94, 203, 
 186, 125, 138, 100, 
 15, 222, 54, 97, 
 159, 127, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len18_anagram1 = {
  LengthAndAnagram(18, 1), // seq_bit_len_and_anagram
  40, // num_chords
  kmap5_Word_len18_anagram1_chords, // chords
  kmap5_Word_len18_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len18_anagram2_chords[15] = {
 ChordData({0, 4, 19}), ChordData({0, 4, 146}), ChordData({0, 64, 2}), ChordData({4, 12, 0}), 
 ChordData({16, 0, 131}), ChordData({16, 4, 192}), ChordData({16, 13, 0}), ChordData({16, 64, 130}), 
 ChordData({32, 8, 1}), ChordData({32, 69, 16}), ChordData({36, 4, 128}), ChordData({38, 0, 128}), 
 ChordData({50, 72, 0}), ChordData({128, 64, 130}), ChordData({128, 72, 0}), 
};

uint8_t const kmap5_Word_len18_anagram2_seqs[34] = {
 183, 95, 34, 125, 
 9, 0, 64, 193, 
 111, 38, 227, 145, 
 95, 220, 125, 52, 
 96, 10, 177, 222, 
 133, 125, 216, 63, 
 81, 63, 68, 97, 
 56, 3, 153, 20, 
 50, 35, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len18_anagram2 = {
  LengthAndAnagram(18, 2), // seq_bit_len_and_anagram
  15, // num_chords
  kmap5_Word_len18_anagram2_chords, // chords
  kmap5_Word_len18_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len18_anagram3_chords[6] = {
 ChordData({0, 4, 146}), ChordData({16, 0, 81}), ChordData({16, 13, 128}), ChordData({18, 0, 129}), 
 ChordData({48, 1, 128}), ChordData({48, 9, 0}), 
};

uint8_t const kmap5_Word_len18_anagram3_seqs[14] = {
 224, 95, 202, 217, 
 75, 95, 180, 105, 
 206, 93, 53, 65, 
 187, 8, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len18_anagram3 = {
  LengthAndAnagram(18, 3), // seq_bit_len_and_anagram
  6, // num_chords
  kmap5_Word_len18_anagram3_chords, // chords
  kmap5_Word_len18_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len19_anagram0_chords[140] = {
 ChordData({0, 12, 26}), ChordData({0, 12, 146}), ChordData({0, 13, 9}), ChordData({0, 13, 10}), 
 ChordData({0, 13, 18}), ChordData({0, 13, 24}), ChordData({0, 13, 65}), ChordData({0, 13, 66}), 
 ChordData({0, 13, 129}), ChordData({0, 13, 130}), ChordData({0, 37, 128}), ChordData({0, 68, 146}), 
 ChordData({0, 76, 18}), ChordData({0, 100, 3}), ChordData({0, 100, 66}), ChordData({2, 4, 194}), 
 ChordData({2, 9, 3}), ChordData({2, 9, 9}), ChordData({2, 9, 10}), ChordData({2, 9, 16}), 
 ChordData({2, 9, 66}), ChordData({2, 9, 72}), ChordData({2, 9, 80}), ChordData({2, 9, 128}), 
 ChordData({2, 9, 136}), ChordData({2, 33, 64}), ChordData({2, 65, 8}), ChordData({2, 72, 66}), 
 ChordData({2, 96, 3}), ChordData({2, 96, 66}), ChordData({4, 4, 146}), ChordData({4, 5, 128}), 
 ChordData({4, 68, 18}), ChordData({4, 68, 66}), ChordData({6, 1, 128}), ChordData({16, 4, 65}), 
 ChordData({16, 4, 130}), ChordData({16, 4, 138}), ChordData({16, 4, 145}), ChordData({16, 4, 152}), 
 ChordData({16, 4, 193}), ChordData({16, 4, 194}), ChordData({16, 12, 130}), ChordData({16, 13, 0}), 
 ChordData({16, 32, 10}), ChordData({16, 32, 17}), ChordData({16, 32, 65}), ChordData({16, 32, 80}), 
 ChordData({16, 64, 144}), ChordData({16, 73, 2}), ChordData({16, 73, 64}), ChordData({18, 0, 24}), 
 ChordData({18, 0, 72}), ChordData({18, 0, 74}), ChordData({18, 0, 88}), ChordData({18, 0, 137}), 
 ChordData({18, 0, 194}), ChordData({18, 4, 80}), ChordData({18, 4, 136}), ChordData({18, 41, 0}), 
 ChordData({18, 65, 2}), ChordData({20, 0, 18}), ChordData({20, 0, 192}), ChordData({20, 9, 1}), 
 ChordData({20, 13, 0}), ChordData({22, 0, 2}), ChordData({22, 9, 0}), ChordData({32, 0, 16}), 
 ChordData({32, 1, 10}), ChordData({32, 1, 80}), ChordData({32, 1, 128}), ChordData({32, 9, 8}), 
 ChordData({32, 33, 2}), ChordData({32, 33, 8}), ChordData({32, 40, 2}), ChordData({32, 40, 64}), 
 ChordData({32, 65, 16}), ChordData({32, 72, 16}), ChordData({34, 33, 0}), ChordData({34, 65, 10}), 
 ChordData({36, 0, 24}), ChordData({36, 0, 130}), ChordData({36, 0, 144}), ChordData({36, 5, 8}), 
 ChordData({36, 5, 16}), ChordData({36, 32, 64}), ChordData({36, 36, 1}), ChordData({36, 36, 64}), 
 ChordData({36, 36, 128}), ChordData({36, 68, 8}), ChordData({38, 8, 128}), ChordData({38, 64, 8}), 
 ChordData({38, 64, 16}), ChordData({48, 1, 24}), ChordData({48, 5, 16}), ChordData({48, 8, 18}), 
 ChordData({48, 9, 8}), ChordData({48, 40, 128}), ChordData({48, 76, 2}), ChordData({50, 72, 2}), 
 ChordData({52, 0, 19}), ChordData({128, 4, 138}), ChordData({128, 8, 8}), ChordData({128, 9, 1}), 
 ChordData({128, 9, 2}), ChordData({128, 9, 16}), ChordData({128, 9, 66}), ChordData({128, 9, 128}), 
 ChordData({128, 9, 130}), ChordData({128, 64, 2}), ChordData({128, 65, 0}), ChordData({128, 65, 128}), 
 ChordData({128, 96, 66}), ChordData({128, 100, 2}), ChordData({130, 9, 128}), ChordData({130, 65, 0}), 
 ChordData({132, 0, 18}), ChordData({132, 0, 19}), ChordData({132, 0, 146}), ChordData({144, 0, 16}), 
 ChordData({144, 0, 73}), ChordData({144, 0, 81}), ChordData({144, 0, 82}), ChordData({144, 0, 138}), 
 ChordData({144, 0, 193}), ChordData({144, 0, 194}), ChordData({144, 0, 208}), ChordData({144, 4, 10}), 
 ChordData({144, 4, 136}), ChordData({148, 0, 130}), ChordData({160, 0, 128}), ChordData({160, 1, 16}), 
 ChordData({160, 65, 18}), ChordData({160, 65, 130}), ChordData({162, 72, 0}), ChordData({164, 0, 16}), 
 ChordData({164, 1, 128}), ChordData({164, 8, 0}), ChordData({164, 32, 1}), ChordData({164, 64, 128}), 
};

uint8_t const kmap5_Word_len19_anagram0_seqs[333] = {
 241, 181, 44, 63, 
 210, 189, 22, 245, 
 177, 184, 143, 197, 
 125, 45, 222, 75, 
 81, 30, 139, 247, 
 84, 164, 199, 34, 
 123, 234, 232, 67, 
 9, 252, 70, 128, 
 253, 1, 47, 236, 
 65, 35, 55, 88, 
 44, 234, 156, 14, 
 22, 187, 217, 40, 
 131, 69, 25, 45, 
 238, 72, 177, 56, 
 68, 52, 90, 236, 
 70, 88, 55, 26, 
 4, 152, 8, 204, 
 49, 96, 132, 53, 
 250, 178, 163, 111, 
 192, 126, 19, 224, 
 91, 71, 211, 228, 
 254, 252, 136, 38, 
 36, 191, 210, 159, 
 151, 252, 171, 228, 
 151, 19, 124, 178, 
 65, 31, 227, 23, 
 205, 172, 232, 99, 
 94, 31, 179, 88, 
 152, 189, 166, 224, 
 5, 236, 98, 176, 
 20, 71, 213, 59, 
 106, 17, 25, 69, 
 175, 101, 116, 244, 
 76, 66, 131, 222, 
 31, 241, 211, 88, 
 217, 20, 13, 76, 
 103, 92, 187, 9, 
 217, 173, 232, 118, 
 205, 95, 108, 99, 
 116, 155, 162, 203, 
 172, 219, 85, 69, 
 169, 219, 117, 149, 
 40, 86, 133, 200, 
 42, 100, 85, 97, 
 172, 200, 98, 21, 
 22, 182, 194, 176, 
 53, 178, 129, 12, 
 24, 133, 125, 93, 
 69, 170, 125, 79, 
 117, 251, 87, 8, 
 247, 251, 86, 133, 
 245, 127, 172, 127, 
 97, 61, 61, 235, 
 95, 3, 77, 236, 
 251, 209, 208, 207, 
 6, 184, 182, 62, 
 92, 155, 243, 150, 
 90, 139, 46, 144, 
 51, 240, 156, 185, 
 49, 208, 151, 231, 
 7, 165, 242, 49, 
 245, 50, 139, 152, 
 89, 236, 54, 163, 
 36, 22, 41, 179, 
 72, 137, 69, 32, 
 51, 116, 153, 161, 
 75, 10, 194, 18, 
 0, 242, 89, 113, 
 40, 187, 9, 137, 
 217, 202, 43, 91, 
 182, 164, 210, 187, 
 185, 169, 226, 147, 
 203, 181, 96, 174, 
 145, 82, 45, 151, 
 100, 164, 20, 83, 
 138, 55, 209, 175, 
 79, 169, 54, 168, 
 37, 79, 89, 187, 
 172, 11, 55, 1, 
 72, 9, 112, 57, 
 161, 109, 246, 61, 
 37, 236, 51, 99, 
 159, 199, 250, 164, 
 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len19_anagram0 = {
  LengthAndAnagram(19, 0), // seq_bit_len_and_anagram
  140, // num_chords
  kmap5_Word_len19_anagram0_chords, // chords
  kmap5_Word_len19_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len19_anagram1_chords[57] = {
 ChordData({0, 12, 64}), ChordData({0, 13, 3}), ChordData({0, 13, 16}), ChordData({0, 68, 10}), 
 ChordData({2, 4, 131}), ChordData({2, 9, 64}), ChordData({2, 9, 72}), ChordData({2, 9, 128}), 
 ChordData({2, 9, 192}), ChordData({2, 64, 10}), ChordData({2, 64, 130}), ChordData({4, 68, 18}), 
 ChordData({16, 0, 147}), ChordData({16, 4, 17}), ChordData({16, 4, 19}), ChordData({16, 4, 81}), 
 ChordData({16, 4, 82}), ChordData({16, 4, 145}), ChordData({16, 4, 152}), ChordData({16, 4, 193}), 
 ChordData({16, 4, 208}), ChordData({16, 8, 17}), ChordData({16, 32, 1}), ChordData({16, 32, 17}), 
 ChordData({16, 32, 18}), ChordData({16, 32, 65}), ChordData({16, 32, 130}), ChordData({16, 64, 72}), 
 ChordData({16, 73, 2}), ChordData({18, 0, 25}), ChordData({18, 0, 129}), ChordData({20, 0, 144}), 
 ChordData({20, 4, 2}), ChordData({20, 4, 130}), ChordData({32, 5, 18}), ChordData({32, 5, 128}), 
 ChordData({34, 1, 1}), ChordData({36, 1, 128}), ChordData({48, 1, 17}), ChordData({48, 1, 24}), 
 ChordData({50, 1, 8}), ChordData({50, 9, 0}), ChordData({52, 0, 8}), ChordData({128, 9, 16}), 
 ChordData({128, 9, 18}), ChordData({128, 13, 0}), ChordData({128, 32, 146}), ChordData({128, 64, 18}), 
 ChordData({128, 72, 18}), ChordData({144, 0, 17}), ChordData({144, 0, 73}), ChordData({144, 0, 192}), 
 ChordData({146, 0, 72}), ChordData({160, 0, 18}), ChordData({160, 5, 18}), ChordData({160, 33, 0}), 
 ChordData({164, 1, 128}), 
};

uint8_t const kmap5_Word_len19_anagram1_seqs[136] = {
 188, 124, 188, 199, 
 98, 247, 27, 195, 
 3, 122, 15, 154, 
 226, 136, 72, 113, 
 180, 27, 138, 50, 
 84, 4, 70, 3, 
 48, 20, 128, 223, 
 6, 110, 188, 91, 
 255, 173, 31, 79, 
 238, 215, 130, 191, 
 126, 58, 47, 184, 
 95, 229, 252, 68, 
 47, 222, 232, 243, 
 158, 125, 204, 199, 
 188, 200, 236, 21, 
 102, 31, 217, 200, 
 130, 85, 28, 140, 
 197, 209, 243, 222, 
 28, 25, 220, 110, 
 205, 143, 254, 102, 
 16, 220, 47, 59, 
 122, 8, 167, 187, 
 70, 21, 194, 181, 
 15, 90, 215, 30, 
 104, 237, 134, 51, 
 223, 91, 187, 220, 
 184, 137, 197, 46, 
 63, 178, 164, 18, 
 200, 13, 64, 110, 
 92, 223, 166, 92, 
 170, 41, 83, 172, 
 57, 226, 50, 235, 
 150, 9, 63, 43, 
 100, 144, 178, 7, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len19_anagram1 = {
  LengthAndAnagram(19, 1), // seq_bit_len_and_anagram
  57, // num_chords
  kmap5_Word_len19_anagram1_chords, // chords
  kmap5_Word_len19_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len19_anagram2_chords[14] = {
 ChordData({4, 4, 18}), ChordData({16, 4, 19}), ChordData({16, 4, 24}), ChordData({16, 4, 146}), 
 ChordData({16, 32, 17}), ChordData({32, 1, 16}), ChordData({34, 8, 0}), ChordData({36, 0, 128}), 
 ChordData({128, 9, 18}), ChordData({128, 64, 10}), ChordData({144, 0, 73}), ChordData({160, 1, 16}), 
 ChordData({160, 1, 128}), ChordData({164, 64, 8}), 
};

uint8_t const kmap5_Word_len19_anagram2_seqs[34] = {
 109, 191, 188, 125, 
 244, 175, 245, 145, 
 252, 123, 108, 109, 
 88, 183, 78, 172, 
 177, 175, 68, 152, 
 91, 12, 9, 168, 
 156, 53, 187, 77, 
 216, 101, 165, 62, 
 53, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len19_anagram2 = {
  LengthAndAnagram(19, 2), // seq_bit_len_and_anagram
  14, // num_chords
  kmap5_Word_len19_anagram2_chords, // chords
  kmap5_Word_len19_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len19_anagram3_chords[7] = {
 ChordData({0, 68, 18}), ChordData({16, 4, 19}), ChordData({16, 4, 65}), ChordData({16, 4, 138}), 
 ChordData({48, 1, 24}), ChordData({52, 8, 16}), ChordData({160, 1, 128}), 
};

uint8_t const kmap5_Word_len19_anagram3_seqs[17] = {
 97, 31, 192, 63, 
 239, 189, 156, 233, 
 21, 13, 173, 94, 
 206, 219, 195, 164, 
 14, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len19_anagram3 = {
  LengthAndAnagram(19, 3), // seq_bit_len_and_anagram
  7, // num_chords
  kmap5_Word_len19_anagram3_chords, // chords
  kmap5_Word_len19_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len19_anagram4_chords[2] = {
 ChordData({0, 68, 18}), ChordData({16, 4, 145}), 
};

uint8_t const kmap5_Word_len19_anagram4_seqs[5] = {
 192, 111, 120, 242, 
 30, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len19_anagram4 = {
  LengthAndAnagram(19, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len19_anagram4_chords, // chords
  kmap5_Word_len19_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len20_anagram0_chords[155] = {
 ChordData({0, 4, 81}), ChordData({0, 4, 89}), ChordData({0, 4, 138}), ChordData({0, 4, 194}), 
 ChordData({0, 4, 200}), ChordData({0, 13, 16}), ChordData({0, 45, 2}), ChordData({0, 65, 74}), 
 ChordData({0, 77, 16}), ChordData({2, 0, 67}), ChordData({2, 1, 16}), ChordData({2, 4, 17}), 
 ChordData({2, 4, 25}), ChordData({2, 4, 72}), ChordData({2, 4, 81}), ChordData({2, 4, 145}), 
 ChordData({2, 4, 192}), ChordData({2, 4, 200}), ChordData({2, 9, 64}), ChordData({2, 73, 8}), 
 ChordData({2, 73, 64}), ChordData({4, 13, 2}), ChordData({4, 13, 16}), ChordData({6, 9, 2}), 
 ChordData({6, 9, 8}), ChordData({6, 9, 64}), ChordData({16, 1, 10}), ChordData({16, 1, 130}), 
 ChordData({16, 8, 192}), ChordData({16, 12, 9}), ChordData({16, 12, 65}), ChordData({16, 12, 66}), 
 ChordData({16, 12, 129}), ChordData({16, 32, 67}), ChordData({16, 32, 192}), ChordData({16, 36, 3}), 
 ChordData({16, 36, 9}), ChordData({16, 36, 66}), ChordData({16, 36, 80}), ChordData({16, 64, 25}), 
 ChordData({16, 64, 67}), ChordData({16, 64, 80}), ChordData({16, 68, 10}), ChordData({16, 68, 17}), 
 ChordData({16, 68, 65}), ChordData({16, 68, 129}), ChordData({16, 68, 136}), ChordData({16, 73, 10}), 
 ChordData({16, 77, 2}), ChordData({18, 8, 17}), ChordData({18, 8, 18}), ChordData({18, 8, 192}), 
 ChordData({18, 12, 128}), ChordData({18, 32, 3}), ChordData({18, 32, 17}), ChordData({18, 32, 72}), 
 ChordData({18, 64, 17}), ChordData({18, 64, 192}), ChordData({18, 68, 128}), ChordData({20, 0, 67}), 
 ChordData({20, 0, 73}), ChordData({20, 0, 80}), ChordData({20, 0, 193}), ChordData({20, 4, 65}), 
 ChordData({20, 4, 66}), ChordData({20, 4, 80}), ChordData({20, 4, 129}), ChordData({20, 4, 130}), 
 ChordData({20, 4, 136}), ChordData({20, 32, 64}), ChordData({20, 64, 64}), ChordData({22, 0, 3}), 
 ChordData({22, 0, 18}), ChordData({22, 0, 72}), ChordData({22, 0, 80}), ChordData({22, 8, 64}), 
 ChordData({32, 9, 66}), ChordData({32, 9, 130}), ChordData({32, 9, 144}), ChordData({32, 12, 18}), 
 ChordData({32, 12, 26}), ChordData({32, 64, 19}), ChordData({32, 65, 8}), ChordData({34, 9, 8}), 
 ChordData({36, 8, 0}), ChordData({36, 68, 66}), ChordData({36, 72, 0}), ChordData({48, 0, 88}), 
 ChordData({48, 0, 138}), ChordData({48, 4, 3}), ChordData({48, 4, 66}), ChordData({48, 5, 9}), 
 ChordData({48, 5, 17}), ChordData({48, 5, 18}), ChordData({48, 5, 24}), ChordData({48, 5, 65}), 
 ChordData({48, 5, 128}), ChordData({48, 5, 136}), ChordData({48, 5, 144}), ChordData({48, 8, 9}), 
 ChordData({48, 8, 24}), ChordData({48, 8, 72}), ChordData({48, 8, 80}), ChordData({48, 8, 128}), 
 ChordData({48, 8, 144}), ChordData({48, 9, 16}), ChordData({48, 65, 128}), ChordData({50, 0, 9}), 
 ChordData({50, 0, 64}), ChordData({52, 13, 0}), ChordData({54, 9, 0}), ChordData({128, 0, 75}), 
 ChordData({128, 0, 145}), ChordData({128, 0, 146}), ChordData({128, 0, 216}), ChordData({128, 4, 10}), 
 ChordData({128, 4, 19}), ChordData({128, 4, 65}), ChordData({128, 4, 67}), ChordData({128, 4, 129}), 
 ChordData({128, 4, 130}), ChordData({128, 4, 200}), ChordData({128, 4, 208}), ChordData({128, 41, 0}), 
 ChordData({128, 73, 2}), ChordData({128, 104, 2}), ChordData({130, 0, 11}), ChordData({130, 0, 25}), 
 ChordData({130, 0, 74}), ChordData({130, 0, 152}), ChordData({130, 4, 9}), ChordData({130, 4, 17}), 
 ChordData({130, 4, 64}), ChordData({132, 9, 16}), ChordData({132, 32, 18}), ChordData({144, 8, 129}), 
 ChordData({144, 8, 136}), ChordData({144, 32, 17}), ChordData({144, 32, 24}), ChordData({144, 32, 65}), 
 ChordData({144, 32, 72}), ChordData({144, 32, 80}), ChordData({144, 32, 128}), ChordData({144, 32, 129}), 
 ChordData({144, 64, 16}), ChordData({144, 64, 24}), ChordData({148, 0, 66}), ChordData({148, 0, 192}), 
 ChordData({148, 4, 16}), ChordData({148, 8, 8}), ChordData({148, 8, 16}), ChordData({162, 8, 0}), 
 ChordData({164, 64, 130}), ChordData({176, 0, 17}), ChordData({176, 0, 24}), 
};

uint8_t const kmap5_Word_len20_anagram0_seqs[388] = {
 114, 191, 119, 251, 
 42, 248, 250, 132, 
 244, 34, 250, 242, 
 20, 127, 139, 236, 
 177, 168, 210, 1, 
 225, 183, 56, 114, 
 131, 124, 183, 115, 
 251, 115, 163, 183, 
 47, 163, 63, 114, 
 63, 123, 59, 79, 
 79, 243, 34, 250, 
 67, 82, 156, 88, 
 28, 13, 97, 164, 
 216, 30, 139, 237, 
 183, 216, 6, 139, 
 109, 180, 40, 197, 
 105, 157, 21, 221, 
 145, 65, 18, 77, 
 20, 253, 122, 114, 
 254, 232, 248, 40, 
 209, 247, 132, 204, 
 114, 194, 76, 116, 
 126, 100, 234, 63, 
 134, 236, 197, 194, 
 126, 125, 107, 13, 
 2, 216, 23, 214, 
 34, 225, 21, 125, 
 251, 193, 114, 254, 
 16, 76, 247, 244, 
 193, 90, 84, 3, 
 192, 23, 125, 19, 
 189, 184, 19, 45, 
 113, 200, 142, 63, 
 228, 99, 131, 199, 
 60, 43, 108, 212, 
 183, 227, 32, 52, 
 193, 19, 252, 36, 
 205, 120, 210, 172, 
 215, 214, 34, 66, 
 110, 215, 94, 206, 
 210, 30, 221, 126, 
 197, 141, 254, 220, 
 232, 209, 141, 94, 
 45, 204, 110, 210, 
 236, 128, 115, 110, 
 109, 7, 45, 109, 
 212, 210, 102, 45, 
 83, 208, 82, 177, 
 72, 21, 139, 84, 
 183, 200, 253, 150, 
 250, 92, 25, 234, 
 149, 93, 213, 80, 
 28, 133, 173, 198, 
 38, 192, 247, 161, 
 198, 166, 117, 197, 
 85, 145, 252, 88, 
 207, 248, 85, 252, 
 208, 122, 112, 253, 
 7, 247, 209, 251, 
 10, 45, 247, 208, 
 100, 248, 244, 10, 
 201, 244, 11, 109, 
 206, 122, 106, 206, 
 43, 230, 172, 226, 
 229, 76, 230, 76, 
 107, 206, 20, 189, 
 208, 228, 0, 93, 
 117, 206, 35, 82, 
 221, 127, 209, 253, 
 20, 141, 169, 114, 
 183, 73, 132, 73, 
 185, 224, 146, 138, 
 175, 169, 143, 151, 
 123, 249, 114, 152, 
 47, 119, 121, 79, 
 148, 248, 36, 79, 
 169, 146, 244, 203, 
 50, 139, 33, 177, 
 8, 176, 140, 151, 
 58, 56, 122, 155, 
 146, 58, 8, 158, 
 163, 127, 147, 186, 
 127, 147, 249, 50, 
 210, 114, 139, 172, 
 108, 25, 243, 76, 
 228, 152, 154, 199, 
 188, 204, 155, 122, 
 44, 197, 194, 82, 
 45, 44, 215, 204, 
 68, 201, 242, 76, 
 185, 193, 27, 54, 
 213, 130, 217, 44, 
 148, 205, 217, 188, 
 95, 48, 213, 5, 
 189, 201, 13, 151, 
 61, 37, 176, 89, 
 207, 234, 186, 9, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len20_anagram0 = {
  LengthAndAnagram(20, 0), // seq_bit_len_and_anagram
  155, // num_chords
  kmap5_Word_len20_anagram0_chords, // chords
  kmap5_Word_len20_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len20_anagram1_chords[47] = {
 ChordData({0, 4, 19}), ChordData({0, 13, 64}), ChordData({0, 40, 19}), ChordData({2, 0, 193}), 
 ChordData({2, 0, 194}), ChordData({2, 4, 9}), ChordData({2, 4, 25}), ChordData({2, 4, 73}), 
 ChordData({2, 4, 137}), ChordData({2, 4, 144}), ChordData({2, 4, 145}), ChordData({2, 65, 2}), 
 ChordData({16, 12, 18}), ChordData({16, 13, 0}), ChordData({16, 32, 66}), ChordData({16, 36, 3}), 
 ChordData({16, 36, 18}), ChordData({16, 40, 1}), ChordData({16, 68, 17}), ChordData({16, 68, 144}), 
 ChordData({16, 77, 2}), ChordData({18, 8, 17}), ChordData({18, 68, 64}), ChordData({20, 0, 192}), 
 ChordData({20, 4, 80}), ChordData({20, 4, 136}), ChordData({20, 4, 192}), ChordData({22, 0, 66}), 
 ChordData({32, 1, 146}), ChordData({34, 0, 138}), ChordData({36, 5, 16}), ChordData({36, 32, 64}), 
 ChordData({36, 68, 0}), ChordData({48, 5, 136}), ChordData({48, 8, 24}), ChordData({48, 12, 128}), 
 ChordData({52, 0, 144}), ChordData({128, 0, 82}), ChordData({128, 65, 130}), ChordData({130, 0, 8}), 
 ChordData({144, 32, 66}), ChordData({144, 32, 80}), ChordData({144, 64, 17}), ChordData({160, 9, 16}), 
 ChordData({164, 64, 130}), ChordData({176, 0, 17}), ChordData({176, 1, 64}), 
};

uint8_t const kmap5_Word_len20_anagram1_seqs[118] = {
 183, 143, 23, 95, 
 138, 177, 60, 38, 
 55, 68, 130, 67, 
 115, 115, 175, 183, 
 63, 42, 247, 163, 
 244, 55, 10, 254, 
 67, 183, 63, 4, 
 76, 55, 184, 254, 
 216, 125, 209, 200, 
 44, 130, 204, 127, 
 235, 71, 118, 204, 
 209, 183, 254, 0, 
 254, 193, 128, 191, 
 24, 189, 115, 47, 
 19, 44, 205, 68, 
 210, 126, 221, 94, 
 77, 244, 77, 44, 
 109, 208, 21, 82, 
 89, 117, 64, 253, 
 111, 215, 87, 97, 
 253, 215, 240, 10, 
 77, 234, 229, 76, 
 126, 206, 235, 222, 
 132, 155, 34, 29, 
 37, 144, 58, 169, 
 200, 82, 204, 114, 
 197, 183, 25, 12, 
 55, 139, 125, 2, 
 148, 245, 188, 48, 
 83, 12, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len20_anagram1 = {
  LengthAndAnagram(20, 1), // seq_bit_len_and_anagram
  47, // num_chords
  kmap5_Word_len20_anagram1_chords, // chords
  kmap5_Word_len20_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len20_anagram2_chords[17] = {
 ChordData({0, 4, 193}), ChordData({2, 9, 128}), ChordData({16, 1, 16}), ChordData({16, 1, 129}), 
 ChordData({16, 36, 1}), ChordData({16, 36, 2}), ChordData({16, 36, 17}), ChordData({16, 64, 3}), 
 ChordData({18, 64, 18}), ChordData({20, 4, 66}), ChordData({20, 4, 80}), ChordData({20, 4, 144}), 
 ChordData({48, 4, 66}), ChordData({48, 5, 24}), ChordData({128, 65, 130}), ChordData({144, 8, 17}), 
 ChordData({180, 0, 64}), 
};

uint8_t const kmap5_Word_len20_anagram2_seqs[43] = {
 114, 79, 20, 135, 
 138, 235, 206, 219, 
 145, 125, 199, 124, 
 143, 143, 204, 254, 
 61, 118, 128, 125, 
 56, 193, 43, 248, 
 205, 226, 246, 219, 
 252, 75, 242, 21, 
 253, 10, 189, 64, 
 82, 23, 125, 155, 
 217, 91, 12, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len20_anagram2 = {
  LengthAndAnagram(20, 2), // seq_bit_len_and_anagram
  17, // num_chords
  kmap5_Word_len20_anagram2_chords, // chords
  kmap5_Word_len20_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len20_anagram3_chords[2] = {
 ChordData({16, 36, 17}), ChordData({32, 1, 128}), 
};

uint8_t const kmap5_Word_len20_anagram3_seqs[5] = {
 204, 191, 7, 43, 
 117, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len20_anagram3 = {
  LengthAndAnagram(20, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len20_anagram3_chords, // chords
  kmap5_Word_len20_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len20_anagram6_chords[1] = {
 ChordData({48, 8, 80}), 
};

uint8_t const kmap5_Word_len20_anagram6_seqs[3] = {
 156, 87, 12, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len20_anagram6 = {
  LengthAndAnagram(20, 6), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len20_anagram6_chords, // chords
  kmap5_Word_len20_anagram6_seqs, // sequences
};

ChordData const kmap5_Word_len21_anagram0_chords[171] = {
 ChordData({0, 12, 81}), ChordData({0, 12, 144}), ChordData({0, 12, 192}), ChordData({0, 36, 19}), 
 ChordData({0, 36, 26}), ChordData({0, 36, 81}), ChordData({0, 36, 82}), ChordData({0, 36, 192}), 
 ChordData({0, 64, 209}), ChordData({0, 68, 16}), ChordData({0, 68, 73}), ChordData({0, 68, 192}), 
 ChordData({0, 77, 130}), ChordData({2, 0, 11}), ChordData({2, 8, 129}), ChordData({2, 12, 10}), 
 ChordData({2, 12, 130}), ChordData({2, 32, 81}), ChordData({2, 36, 10}), ChordData({2, 36, 18}), 
 ChordData({2, 64, 144}), ChordData({2, 68, 8}), ChordData({2, 68, 24}), ChordData({2, 73, 2}), 
 ChordData({4, 4, 73}), ChordData({4, 4, 81}), ChordData({4, 4, 137}), ChordData({4, 13, 0}), 
 ChordData({6, 0, 25}), ChordData({6, 0, 81}), ChordData({6, 0, 193}), ChordData({6, 4, 9}), 
 ChordData({6, 4, 10}), ChordData({6, 4, 136}), ChordData({6, 8, 10}), ChordData({16, 0, 211}), 
 ChordData({16, 1, 131}), ChordData({16, 4, 83}), ChordData({16, 5, 17}), ChordData({16, 5, 129}), 
 ChordData({16, 5, 192}), ChordData({16, 8, 26}), ChordData({16, 44, 1}), ChordData({16, 44, 64}), 
 ChordData({16, 64, 82}), ChordData({16, 65, 16}), ChordData({16, 68, 19}), ChordData({16, 68, 67}), 
 ChordData({16, 76, 8}), ChordData({16, 76, 16}), ChordData({16, 76, 128}), ChordData({16, 96, 18}), 
 ChordData({16, 96, 130}), ChordData({16, 100, 1}), ChordData({16, 100, 16}), ChordData({16, 100, 64}), 
 ChordData({18, 64, 3}), ChordData({18, 64, 19}), ChordData({18, 72, 2}), ChordData({18, 76, 0}), 
 ChordData({20, 4, 16}), ChordData({20, 8, 80}), ChordData({20, 12, 128}), ChordData({20, 36, 2}), 
 ChordData({20, 36, 64}), ChordData({20, 44, 0}), ChordData({20, 64, 72}), ChordData({22, 8, 16}), 
 ChordData({22, 64, 16}), ChordData({32, 0, 209}), ChordData({32, 4, 145}), ChordData({32, 4, 152}), 
 ChordData({32, 5, 25}), ChordData({32, 5, 192}), ChordData({32, 73, 2}), ChordData({34, 0, 137}), 
 ChordData({34, 5, 8}), ChordData({34, 5, 9}), ChordData({34, 5, 24}), ChordData({36, 0, 82}), 
 ChordData({36, 9, 8}), ChordData({36, 13, 2}), ChordData({36, 13, 8}), ChordData({48, 1, 64}), 
 ChordData({48, 9, 1}), ChordData({48, 12, 192}), ChordData({48, 64, 24}), ChordData({48, 69, 16}), 
 ChordData({50, 8, 16}), ChordData({50, 8, 144}), ChordData({50, 12, 8}), ChordData({50, 13, 0}), 
 ChordData({52, 0, 80}), ChordData({52, 0, 129}), ChordData({52, 0, 192}), ChordData({52, 4, 65}), 
 ChordData({52, 4, 129}), ChordData({52, 4, 130}), ChordData({52, 64, 16}), ChordData({52, 64, 128}), 
 ChordData({54, 0, 144}), ChordData({128, 8, 17}), ChordData({128, 8, 81}), ChordData({128, 12, 18}), 
 ChordData({128, 12, 72}), ChordData({128, 13, 18}), ChordData({128, 32, 24}), ChordData({128, 32, 25}), 
 ChordData({128, 32, 81}), ChordData({128, 32, 131}), ChordData({128, 36, 2}), ChordData({128, 36, 18}), 
 ChordData({128, 36, 66}), ChordData({128, 64, 24}), ChordData({128, 64, 65}), ChordData({128, 73, 10}), 
 ChordData({128, 73, 18}), ChordData({130, 8, 2}), ChordData({130, 8, 18}), ChordData({130, 8, 24}), 
 ChordData({130, 8, 65}), ChordData({130, 32, 18}), ChordData({130, 64, 1}), ChordData({130, 64, 65}), 
 ChordData({130, 64, 66}), ChordData({130, 64, 192}), ChordData({130, 68, 16}), ChordData({132, 0, 66}), 
 ChordData({132, 0, 81}), ChordData({132, 0, 192}), ChordData({132, 4, 144}), ChordData({134, 0, 3}), 
 ChordData({134, 0, 16}), ChordData({134, 0, 129}), ChordData({134, 0, 192}), ChordData({134, 4, 1}), 
 ChordData({134, 4, 8}), ChordData({144, 1, 9}), ChordData({144, 1, 18}), ChordData({144, 64, 19}), 
 ChordData({144, 64, 82}), ChordData({144, 72, 8}), ChordData({144, 72, 128}), ChordData({146, 64, 0}), 
 ChordData({148, 32, 2}), ChordData({148, 32, 8}), ChordData({160, 0, 11}), ChordData({160, 0, 19}), 
 ChordData({160, 0, 67}), ChordData({160, 1, 80}), ChordData({160, 5, 1}), ChordData({160, 5, 8}), 
 ChordData({160, 5, 18}), ChordData({160, 5, 24}), ChordData({160, 5, 136}), ChordData({162, 0, 8}), 
 ChordData({162, 1, 130}), ChordData({162, 1, 136}), ChordData({164, 9, 0}), ChordData({164, 9, 8}), 
 ChordData({164, 64, 18}), ChordData({176, 8, 18}), ChordData({176, 8, 64}), ChordData({176, 8, 136}), 
 ChordData({176, 8, 192}), ChordData({176, 13, 0}), ChordData({176, 32, 64}), ChordData({176, 65, 128}), 
 ChordData({178, 8, 2}), ChordData({178, 8, 128}), ChordData({180, 0, 136}), 
};

uint8_t const kmap5_Word_len21_anagram0_seqs[449] = {
 18, 127, 239, 233, 
 55, 74, 124, 34, 
 100, 191, 183, 175, 
 200, 110, 95, 24, 
 238, 11, 19, 246, 
 68, 82, 104, 111, 
 63, 252, 202, 189, 
 6, 121, 250, 0, 
 60, 21, 167, 176, 
 35, 77, 156, 139, 
 175, 131, 72, 63, 
 81, 216, 236, 33, 
 251, 81, 100, 63, 
 27, 118, 136, 70, 
 195, 124, 216, 31, 
 5, 166, 56, 237, 
 245, 68, 110, 191, 
 53, 122, 189, 98, 
 252, 214, 118, 244, 
 228, 118, 154, 52, 
 154, 107, 63, 122, 
 237, 117, 176, 209, 
 143, 22, 28, 69, 
 185, 146, 220, 145, 
 241, 74, 191, 220, 
 119, 231, 237, 232, 
 207, 221, 147, 216, 
 234, 88, 30, 115, 
 124, 97, 31, 45, 
 184, 6, 130, 59, 
 47, 240, 231, 5, 
 94, 206, 31, 173, 
 33, 172, 63, 70, 
 135, 39, 128, 121, 
 13, 48, 155, 130, 
 255, 24, 243, 111, 
 16, 246, 193, 7, 
 12, 26, 216, 57, 
 71, 135, 193, 232, 
 48, 223, 190, 121, 
 165, 121, 99, 252, 
 70, 70, 230, 111, 
 194, 190, 153, 125, 
 65, 75, 179, 134, 
 182, 19, 221, 118, 
 130, 193, 171, 92, 
 165, 219, 175, 164, 
 191, 112, 95, 15, 
 210, 139, 132, 138, 
 197, 170, 55, 244, 
 240, 71, 225, 188, 
 30, 220, 31, 237, 
 171, 148, 173, 106, 
 177, 127, 44, 246, 
 175, 69, 88, 45, 
 194, 25, 250, 132, 
 158, 115, 213, 224, 
 133, 251, 193, 59, 
 156, 151, 134, 243, 
 234, 15, 231, 137, 
 15, 45, 181, 121, 
 175, 54, 114, 171, 
 36, 238, 253, 114, 
 247, 61, 25, 191, 
 39, 247, 107, 135, 
 158, 236, 64, 211, 
 175, 99, 94, 174, 
 92, 110, 140, 143, 
 155, 241, 37, 53, 
 139, 95, 178, 212, 
 92, 205, 61, 38, 
 44, 247, 144, 242, 
 24, 230, 35, 219, 
 124, 100, 200, 62, 
 37, 164, 230, 202, 
 101, 134, 162, 38, 
 0, 228, 22, 49, 
 227, 96, 28, 220, 
 140, 163, 185, 49, 
 71, 14, 89, 206, 
 78, 152, 60, 185, 
 48, 25, 70, 48, 
 37, 105, 194, 126, 
 152, 20, 204, 108, 
 210, 114, 79, 90, 
 38, 181, 164, 223, 
 203, 54, 216, 118, 
 114, 219, 80, 158, 
 180, 28, 106, 127, 
 147, 109, 94, 51, 
 187, 179, 118, 185, 
 104, 96, 243, 12, 
 228, 138, 131, 99, 
 106, 204, 96, 10, 
 147, 193, 110, 137, 
 172, 177, 84, 99, 
 86, 61, 204, 186, 
 39, 152, 245, 224, 
 166, 8, 204, 187, 
 135, 169, 250, 248, 
 11, 51, 23, 190, 
 62, 165, 194, 170, 
 147, 74, 9, 7, 
 41, 225, 104, 159, 
 89, 44, 106, 246, 
 125, 134, 18, 147, 
 243, 198, 172, 98, 
 77, 206, 36, 73, 
 156, 51, 26, 62, 
 203, 42, 166, 12, 
 208, 92, 14, 58, 
 105, 56, 107, 246, 
 100, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len21_anagram0 = {
  LengthAndAnagram(21, 0), // seq_bit_len_and_anagram
  171, // num_chords
  kmap5_Word_len21_anagram0_chords, // chords
  kmap5_Word_len21_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len21_anagram1_chords[44] = {
 ChordData({0, 36, 3}), ChordData({0, 36, 192}), ChordData({2, 12, 8}), ChordData({2, 64, 0}), 
 ChordData({2, 65, 0}), ChordData({4, 4, 17}), ChordData({4, 4, 65}), ChordData({4, 4, 82}), 
 ChordData({16, 0, 27}), ChordData({16, 0, 146}), ChordData({16, 4, 146}), ChordData({16, 100, 0}), 
 ChordData({20, 4, 128}), ChordData({20, 36, 64}), ChordData({32, 0, 81}), ChordData({32, 1, 2}), 
 ChordData({32, 4, 144}), ChordData({32, 5, 80}), ChordData({34, 1, 144}), ChordData({34, 5, 128}), 
 ChordData({34, 5, 136}), ChordData({36, 0, 128}), ChordData({36, 8, 0}), ChordData({36, 72, 0}), 
 ChordData({48, 1, 65}), ChordData({48, 64, 18}), ChordData({50, 33, 1}), ChordData({50, 65, 16}), 
 ChordData({52, 0, 65}), ChordData({52, 0, 192}), ChordData({52, 4, 64}), ChordData({52, 4, 128}), 
 ChordData({54, 0, 17}), ChordData({128, 9, 128}), ChordData({128, 12, 144}), ChordData({128, 32, 1}), 
 ChordData({132, 0, 17}), ChordData({134, 0, 3}), ChordData({134, 0, 9}), ChordData({144, 0, 144}), 
 ChordData({144, 64, 19}), ChordData({160, 0, 17}), ChordData({164, 8, 0}), ChordData({176, 9, 8}), 
};

uint8_t const kmap5_Word_len21_anagram1_seqs[116] = {
 248, 135, 76, 232, 
 133, 197, 215, 121, 
 126, 248, 16, 166, 
 235, 190, 253, 94, 
 123, 185, 23, 220, 
 111, 214, 219, 18, 
 75, 36, 251, 151, 
 202, 103, 254, 240, 
 173, 145, 27, 123, 
 241, 109, 149, 195, 
 218, 117, 91, 247, 
 9, 238, 139, 192, 
 29, 34, 72, 243, 
 244, 52, 80, 251, 
 74, 125, 95, 99, 
 11, 53, 246, 176, 
 90, 14, 183, 6, 
 123, 32, 187, 157, 
 0, 45, 190, 218, 
 122, 178, 72, 251, 
 42, 166, 239, 77, 
 183, 211, 187, 75, 
 42, 198, 220, 167, 
 203, 60, 118, 155, 
 217, 178, 221, 96, 
 203, 209, 227, 193, 
 211, 151, 128, 247, 
 234, 229, 246, 25, 
 123, 168, 25, 13, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len21_anagram1 = {
  LengthAndAnagram(21, 1), // seq_bit_len_and_anagram
  44, // num_chords
  kmap5_Word_len21_anagram1_chords, // chords
  kmap5_Word_len21_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len21_anagram2_chords[12] = {
 ChordData({0, 12, 18}), ChordData({6, 0, 192}), ChordData({36, 0, 18}), ChordData({48, 8, 24}), 
 ChordData({48, 9, 16}), ChordData({52, 0, 80}), ChordData({128, 9, 16}), ChordData({128, 32, 65}), 
 ChordData({132, 0, 17}), ChordData({160, 0, 17}), ChordData({160, 0, 18}), ChordData({176, 8, 16}), 
};

uint8_t const kmap5_Word_len21_anagram2_seqs[32] = {
 252, 199, 82, 218, 
 16, 109, 237, 75, 
 173, 209, 203, 121, 
 161, 91, 93, 113, 
 151, 91, 20, 150, 
 121, 109, 243, 242, 
 54, 235, 37, 98, 
 221, 77, 206, 11, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len21_anagram2 = {
  LengthAndAnagram(21, 2), // seq_bit_len_and_anagram
  12, // num_chords
  kmap5_Word_len21_anagram2_chords, // chords
  kmap5_Word_len21_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len21_anagram3_chords[4] = {
 ChordData({16, 0, 130}), ChordData({16, 4, 82}), ChordData({48, 8, 8}), ChordData({176, 1, 16}), 
};

uint8_t const kmap5_Word_len21_anagram3_seqs[11] = {
 6, 161, 201, 34, 
 95, 114, 214, 234, 
 77, 88, 13, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len21_anagram3 = {
  LengthAndAnagram(21, 3), // seq_bit_len_and_anagram
  4, // num_chords
  kmap5_Word_len21_anagram3_chords, // chords
  kmap5_Word_len21_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len21_anagram4_chords[2] = {
 ChordData({16, 4, 146}), ChordData({176, 1, 16}), 
};

uint8_t const kmap5_Word_len21_anagram4_seqs[6] = {
 107, 250, 114, 179, 
 66, 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len21_anagram4 = {
  LengthAndAnagram(21, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len21_anagram4_chords, // chords
  kmap5_Word_len21_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len21_anagram5_chords[3] = {
 ChordData({16, 68, 18}), ChordData({128, 64, 2}), ChordData({128, 64, 18}), 
};

uint8_t const kmap5_Word_len21_anagram5_seqs[8] = {
 15, 252, 154, 15, 
 9, 96, 230, 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len21_anagram5 = {
  LengthAndAnagram(21, 5), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len21_anagram5_chords, // chords
  kmap5_Word_len21_anagram5_seqs, // sequences
};

ChordData const kmap5_Word_len22_anagram0_chords[191] = {
 ChordData({0, 1, 16}), ChordData({0, 4, 18}), ChordData({0, 4, 80}), ChordData({0, 4, 91}), 
 ChordData({0, 5, 19}), ChordData({0, 44, 3}), ChordData({0, 44, 18}), ChordData({0, 44, 80}), 
 ChordData({0, 68, 10}), ChordData({0, 72, 0}), ChordData({0, 76, 16}), ChordData({2, 0, 210}), 
 ChordData({2, 1, 81}), ChordData({2, 4, 64}), ChordData({2, 5, 24}), ChordData({2, 5, 136}), 
 ChordData({2, 9, 2}), ChordData({2, 32, 193}), ChordData({2, 64, 67}), ChordData({2, 64, 83}), 
 ChordData({2, 68, 67}), ChordData({2, 72, 16}), ChordData({2, 76, 1}), ChordData({2, 76, 8}), 
 ChordData({2, 96, 17}), ChordData({2, 96, 130}), ChordData({4, 12, 16}), ChordData({4, 12, 17}), 
 ChordData({4, 12, 65}), ChordData({4, 12, 130}), ChordData({4, 36, 3}), ChordData({4, 36, 80}), 
 ChordData({4, 36, 128}), ChordData({4, 68, 1}), ChordData({6, 32, 3}), ChordData({6, 68, 16}), 
 ChordData({16, 0, 27}), ChordData({16, 0, 90}), ChordData({16, 0, 145}), ChordData({16, 0, 193}), 
 ChordData({16, 0, 195}), ChordData({16, 4, 19}), ChordData({16, 4, 73}), ChordData({16, 4, 131}), 
 ChordData({16, 4, 147}), ChordData({16, 8, 18}), ChordData({16, 8, 19}), ChordData({16, 9, 144}), 
 ChordData({16, 9, 146}), ChordData({16, 13, 16}), ChordData({16, 13, 65}), ChordData({16, 13, 72}), 
 ChordData({16, 32, 66}), ChordData({16, 33, 1}), ChordData({16, 33, 3}), ChordData({16, 33, 80}), 
 ChordData({16, 33, 192}), ChordData({16, 64, 129}), ChordData({16, 65, 144}), ChordData({16, 68, 18}), 
 ChordData({16, 100, 3}), ChordData({16, 100, 130}), ChordData({18, 0, 25}), ChordData({18, 0, 80}), 
 ChordData({18, 0, 195}), ChordData({18, 33, 2}), ChordData({18, 64, 146}), ChordData({18, 65, 16}), 
 ChordData({18, 65, 128}), ChordData({18, 96, 3}), ChordData({18, 96, 130}), ChordData({20, 0, 26}), 
 ChordData({20, 0, 146}), ChordData({20, 96, 1}), ChordData({22, 64, 66}), ChordData({32, 1, 130}), 
 ChordData({32, 4, 192}), ChordData({32, 5, 80}), ChordData({32, 8, 82}), ChordData({32, 9, 2}), 
 ChordData({32, 12, 0}), ChordData({32, 12, 144}), ChordData({32, 32, 17}), ChordData({32, 32, 138}), 
 ChordData({32, 68, 128}), ChordData({32, 68, 129}), ChordData({32, 69, 24}), ChordData({34, 1, 129}), 
 ChordData({34, 8, 65}), ChordData({34, 8, 66}), ChordData({34, 8, 72}), ChordData({34, 8, 129}), 
 ChordData({34, 8, 130}), ChordData({34, 12, 65}), ChordData({34, 12, 129}), ChordData({34, 12, 144}), 
 ChordData({34, 13, 2}), ChordData({34, 13, 64}), ChordData({34, 33, 9}), ChordData({34, 33, 17}), 
 ChordData({34, 33, 65}), ChordData({34, 33, 129}), ChordData({34, 64, 129}), ChordData({34, 65, 1}), 
 ChordData({34, 68, 1}), ChordData({36, 0, 208}), ChordData({36, 4, 80}), ChordData({36, 4, 192}), 
 ChordData({36, 4, 193}), ChordData({36, 5, 80}), ChordData({36, 9, 2}), ChordData({36, 9, 128}), 
 ChordData({38, 0, 9}), ChordData({38, 4, 10}), ChordData({38, 4, 24}), ChordData({38, 4, 64}), 
 ChordData({38, 4, 66}), ChordData({38, 4, 192}), ChordData({48, 0, 65}), ChordData({48, 1, 146}), 
 ChordData({48, 12, 128}), ChordData({48, 44, 64}), ChordData({48, 44, 128}), ChordData({48, 65, 2}), 
 ChordData({50, 65, 0}), ChordData({50, 72, 16}), ChordData({50, 72, 128}), ChordData({52, 5, 8}), 
 ChordData({52, 12, 128}), ChordData({52, 32, 10}), ChordData({52, 36, 2}), ChordData({52, 36, 16}), 
 ChordData({52, 64, 136}), ChordData({52, 68, 16}), ChordData({52, 68, 128}), ChordData({52, 72, 0}), 
 ChordData({54, 1, 8}), ChordData({128, 0, 82}), ChordData({128, 0, 83}), ChordData({128, 0, 152}), 
 ChordData({128, 1, 25}), ChordData({128, 1, 81}), ChordData({128, 1, 144}), ChordData({128, 4, 26}), 
 ChordData({128, 4, 146}), ChordData({128, 5, 129}), ChordData({128, 5, 130}), ChordData({128, 12, 2}), 
 ChordData({128, 40, 9}), ChordData({128, 64, 83}), ChordData({128, 68, 130}), ChordData({128, 96, 18}), 
 ChordData({128, 100, 16}), ChordData({130, 1, 128}), ChordData({130, 64, 16}), ChordData({132, 8, 0}), 
 ChordData({132, 8, 16}), ChordData({132, 32, 1}), ChordData({132, 68, 1}), ChordData({134, 8, 1}), 
 ChordData({144, 8, 26}), ChordData({144, 9, 9}), ChordData({144, 9, 144}), ChordData({144, 72, 10}), 
 ChordData({144, 96, 66}), ChordData({144, 96, 130}), ChordData({148, 64, 18}), ChordData({160, 8, 9}), 
 ChordData({160, 8, 17}), ChordData({160, 12, 130}), ChordData({160, 13, 8}), ChordData({160, 32, 3}), 
 ChordData({160, 32, 65}), ChordData({160, 64, 8}), ChordData({160, 64, 9}), ChordData({160, 64, 24}), 
 ChordData({160, 64, 72}), ChordData({162, 8, 17}), ChordData({162, 32, 8}), ChordData({162, 68, 0}), 
 ChordData({164, 0, 65}), ChordData({164, 4, 10}), ChordData({164, 4, 17}), ChordData({166, 0, 17}), 
 ChordData({176, 9, 128}), ChordData({176, 65, 0}), ChordData({176, 72, 16}), ChordData({178, 8, 0}), 
 ChordData({178, 72, 0}), ChordData({180, 0, 16}), ChordData({180, 8, 16}), 
};

uint8_t const kmap5_Word_len22_anagram0_seqs[526] = {
 252, 242, 221, 239, 
 126, 201, 203, 239, 
 235, 203, 149, 184, 
 223, 93, 252, 67, 
 22, 127, 145, 197, 
 95, 97, 192, 171, 
 62, 31, 249, 16, 
 246, 227, 203, 16, 
 149, 221, 172, 28, 
 255, 50, 63, 218, 
 237, 119, 163, 79, 
 197, 193, 226, 92, 
 129, 114, 192, 200, 
 1, 59, 114, 192, 
 143, 220, 198, 48, 
 251, 33, 206, 125, 
 136, 163, 199, 102, 
 3, 178, 161, 208, 
 126, 63, 222, 126, 
 108, 114, 31, 27, 
 210, 199, 214, 254, 
 144, 9, 251, 109, 
 79, 141, 253, 135, 
 111, 215, 230, 144, 
 237, 183, 9, 107, 
 180, 158, 224, 218, 
 74, 190, 243, 138, 
 239, 200, 98, 50, 
 30, 174, 255, 44, 
 214, 63, 27, 244, 
 120, 6, 221, 126, 
 244, 98, 25, 125, 
 91, 130, 123, 139, 
 72, 222, 98, 183, 
 31, 45, 247, 69, 
 139, 250, 139, 200, 
 108, 241, 49, 119, 
 215, 249, 144, 117, 
 107, 97, 194, 76, 
 93, 48, 249, 220, 
 173, 11, 173, 63, 
 148, 0, 243, 31, 
 192, 158, 108, 189, 
 89, 139, 119, 44, 
 6, 141, 28, 178, 
 113, 87, 142, 41, 
 116, 59, 14, 221, 
 152, 2, 192, 230, 
 12, 176, 33, 55, 
 171, 150, 235, 70, 
 101, 112, 59, 38, 
 192, 52, 119, 84, 
 65, 85, 234, 147, 
 84, 248, 43, 184, 
 53, 118, 21, 139, 
 60, 199, 63, 248, 
 115, 127, 91, 143, 
 81, 85, 100, 133, 
 234, 211, 135, 74, 
 7, 247, 53, 192, 
 58, 116, 220, 200, 
 92, 172, 50, 24, 
 71, 171, 196, 74, 
 55, 56, 220, 16, 
 55, 114, 207, 205, 
 61, 113, 179, 79, 
 241, 225, 160, 12, 
 140, 127, 108, 20, 
 238, 64, 118, 50, 
 144, 29, 13, 100, 
 87, 168, 206, 133, 
 129, 115, 95, 195, 
 156, 80, 221, 214, 
 239, 139, 244, 47, 
 79, 61, 189, 28, 
 220, 151, 214, 87, 
 44, 246, 149, 138, 
 163, 173, 30, 126, 
 63, 218, 239, 143, 
 246, 47, 35, 253, 
 203, 96, 255, 50, 
 196, 95, 181, 172, 
 161, 65, 220, 83, 
 181, 176, 231, 204, 
 158, 56, 3, 14, 
 208, 176, 78, 112, 
 216, 225, 28, 204, 
 13, 245, 134, 175, 
 61, 125, 116, 111, 
 69, 214, 251, 145, 
 173, 217, 247, 61, 
 89, 67, 191, 254, 
 208, 211, 7, 59, 
 246, 14, 189, 225, 
 168, 228, 110, 41, 
 151, 91, 242, 224, 
 169, 221, 166, 94, 
 183, 41, 215, 81, 
 230, 190, 106, 150, 
 79, 148, 101, 71, 
 249, 215, 37, 62, 
 97, 198, 248, 49, 
 245, 24, 144, 43, 
 247, 68, 9, 32, 
 203, 13, 44, 127, 
 67, 151, 52, 25, 
 54, 39, 20, 204, 
 140, 109, 51, 102, 
 99, 121, 249, 33, 
 219, 101, 187, 137, 
 49, 213, 229, 101, 
 209, 10, 158, 69, 
 3, 25, 173, 0, 
 75, 49, 192, 146, 
 220, 18, 240, 198, 
 172, 122, 87, 99, 
 46, 151, 248, 244, 
 49, 21, 94, 86, 
 100, 146, 245, 88, 
 168, 170, 25, 82, 
 235, 109, 86, 13, 
 146, 85, 3, 55, 
 183, 201, 234, 164, 
 126, 13, 147, 125, 
 166, 92, 255, 152, 
 250, 125, 238, 229, 
 246, 115, 144, 146, 
 115, 200, 0, 29, 
 54, 57, 199, 228, 
 198, 220, 4, 103, 
 219, 236, 221, 54, 
 57, 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len22_anagram0 = {
  LengthAndAnagram(22, 0), // seq_bit_len_and_anagram
  191, // num_chords
  kmap5_Word_len22_anagram0_chords, // chords
  kmap5_Word_len22_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len22_anagram1_chords[44] = {
 ChordData({0, 4, 82}), ChordData({0, 5, 129}), ChordData({0, 44, 18}), ChordData({0, 109, 2}), 
 ChordData({2, 0, 146}), ChordData({4, 8, 0}), ChordData({16, 0, 83}), ChordData({16, 4, 131}), 
 ChordData({16, 8, 18}), ChordData({16, 13, 72}), ChordData({16, 33, 192}), ChordData({16, 64, 136}), 
 ChordData({16, 68, 146}), ChordData({16, 96, 19}), ChordData({18, 4, 80}), ChordData({18, 64, 18}), 
 ChordData({32, 33, 0}), ChordData({32, 68, 129}), ChordData({34, 12, 128}), ChordData({34, 33, 1}), 
 ChordData({34, 33, 9}), ChordData({34, 65, 24}), ChordData({36, 4, 18}), ChordData({48, 5, 0}), 
 ChordData({48, 8, 18}), ChordData({48, 13, 16}), ChordData({48, 44, 8}), ChordData({52, 5, 128}), 
 ChordData({52, 12, 16}), ChordData({128, 0, 154}), ChordData({128, 4, 146}), ChordData({128, 64, 26}), 
 ChordData({128, 68, 18}), ChordData({132, 64, 16}), ChordData({144, 0, 81}), ChordData({144, 32, 26}), 
 ChordData({160, 33, 65}), ChordData({160, 64, 130}), ChordData({164, 0, 17}), ChordData({164, 4, 144}), 
 ChordData({176, 1, 16}), ChordData({176, 9, 16}), ChordData({176, 72, 16}), ChordData({180, 1, 128}), 
};

uint8_t const kmap5_Word_len22_anagram1_seqs[121] = {
 130, 191, 101, 247, 
 247, 132, 236, 55, 
 178, 7, 138, 84, 
 238, 32, 223, 248, 
 40, 198, 245, 209, 
 159, 65, 209, 187, 
 165, 232, 23, 221, 
 145, 133, 169, 29, 
 200, 193, 244, 229, 
 177, 53, 224, 151, 
 241, 2, 158, 13, 
 172, 118, 93, 161, 
 250, 199, 13, 209, 
 223, 64, 118, 58, 
 144, 29, 220, 209, 
 208, 127, 95, 194, 
 175, 208, 230, 188, 
 37, 220, 231, 204, 
 158, 179, 246, 15, 
 77, 31, 123, 175, 
 150, 148, 186, 89, 
 62, 225, 38, 160, 
 191, 155, 64, 216, 
 204, 38, 231, 117, 
 178, 84, 151, 144, 
 165, 28, 102, 165, 
 176, 217, 231, 209, 
 247, 185, 93, 46, 
 52, 220, 228, 28, 
 146, 243, 66, 202, 
 222, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len22_anagram1 = {
  LengthAndAnagram(22, 1), // seq_bit_len_and_anagram
  44, // num_chords
  kmap5_Word_len22_anagram1_chords, // chords
  kmap5_Word_len22_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len22_anagram2_chords[12] = {
 ChordData({0, 4, 18}), ChordData({6, 0, 1}), ChordData({16, 0, 27}), ChordData({16, 0, 81}), 
 ChordData({16, 4, 82}), ChordData({16, 4, 138}), ChordData({16, 13, 128}), ChordData({18, 65, 8}), 
 ChordData({48, 8, 18}), ChordData({52, 1, 16}), ChordData({52, 4, 64}), ChordData({160, 64, 130}), 
};

uint8_t const kmap5_Word_len22_anagram2_seqs[33] = {
 248, 187, 101, 155, 
 54, 135, 214, 243, 
 202, 173, 125, 184, 
 126, 241, 171, 26, 
 212, 209, 71, 91, 
 195, 116, 88, 151, 
 115, 131, 235, 246, 
 125, 21, 35, 101, 
 13, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len22_anagram2 = {
  LengthAndAnagram(22, 2), // seq_bit_len_and_anagram
  12, // num_chords
  kmap5_Word_len22_anagram2_chords, // chords
  kmap5_Word_len22_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len22_anagram3_chords[4] = {
 ChordData({16, 4, 18}), ChordData({16, 4, 145}), ChordData({16, 4, 146}), ChordData({36, 1, 0}), 
};

uint8_t const kmap5_Word_len22_anagram3_seqs[11] = {
 248, 107, 239, 154, 
 254, 188, 166, 7, 
 181, 218, 117, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len22_anagram3 = {
  LengthAndAnagram(22, 3), // seq_bit_len_and_anagram
  4, // num_chords
  kmap5_Word_len22_anagram3_chords, // chords
  kmap5_Word_len22_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len22_anagram4_chords[2] = {
 ChordData({16, 4, 65}), ChordData({48, 9, 16}), 
};

uint8_t const kmap5_Word_len22_anagram4_seqs[6] = {
 150, 251, 115, 103, 
 206, 11, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len22_anagram4 = {
  LengthAndAnagram(22, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len22_anagram4_chords, // chords
  kmap5_Word_len22_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len22_anagram6_chords[1] = {
 ChordData({16, 68, 18}), 
};

uint8_t const kmap5_Word_len22_anagram6_seqs[3] = {
 193, 248, 37, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len22_anagram6 = {
  LengthAndAnagram(22, 6), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len22_anagram6_chords, // chords
  kmap5_Word_len22_anagram6_seqs, // sequences
};

ChordData const kmap5_Word_len23_anagram0_chords[162] = {
 ChordData({0, 13, 19}), ChordData({0, 13, 26}), ChordData({0, 13, 67}), ChordData({0, 13, 146}), 
 ChordData({0, 13, 194}), ChordData({0, 32, 91}), ChordData({0, 37, 65}), ChordData({0, 37, 192}), 
 ChordData({0, 69, 16}), ChordData({0, 69, 17}), ChordData({2, 9, 19}), ChordData({2, 9, 67}), 
 ChordData({2, 9, 81}), ChordData({2, 9, 130}), ChordData({2, 9, 192}), ChordData({2, 32, 90}), 
 ChordData({2, 33, 65}), ChordData({2, 36, 1}), ChordData({2, 37, 1}), ChordData({2, 64, 19}), 
 ChordData({2, 68, 82}), ChordData({2, 68, 146}), ChordData({4, 0, 19}), ChordData({4, 4, 19}), 
 ChordData({4, 12, 146}), ChordData({4, 68, 74}), ChordData({6, 0, 82}), ChordData({16, 1, 18}), 
 ChordData({16, 4, 11}), ChordData({16, 4, 26}), ChordData({16, 4, 27}), ChordData({16, 4, 64}), 
 ChordData({16, 4, 75}), ChordData({16, 4, 81}), ChordData({16, 4, 137}), ChordData({16, 4, 195}), 
 ChordData({16, 8, 11}), ChordData({16, 41, 2}), ChordData({16, 45, 64}), ChordData({16, 64, 3}), 
 ChordData({16, 64, 24}), ChordData({16, 77, 8}), ChordData({16, 104, 130}), ChordData({18, 0, 9}), 
 ChordData({18, 0, 75}), ChordData({18, 0, 81}), ChordData({18, 0, 129}), ChordData({18, 0, 139}), 
 ChordData({18, 0, 146}), ChordData({18, 0, 201}), ChordData({18, 4, 17}), ChordData({18, 4, 25}), 
 ChordData({18, 4, 152}), ChordData({18, 4, 200}), ChordData({18, 4, 208}), ChordData({18, 64, 80}), 
 ChordData({18, 64, 138}), ChordData({20, 4, 17}), ChordData({20, 4, 192}), ChordData({20, 8, 19}), 
 ChordData({20, 13, 64}), ChordData({20, 32, 18}), ChordData({20, 32, 82}), ChordData({22, 0, 1}), 
 ChordData({22, 0, 130}), ChordData({22, 9, 64}), ChordData({32, 0, 18}), ChordData({32, 0, 147}), 
 ChordData({32, 1, 19}), ChordData({32, 5, 26}), ChordData({32, 5, 129}), ChordData({32, 13, 0}), 
 ChordData({32, 37, 128}), ChordData({32, 40, 10}), ChordData({32, 44, 8}), ChordData({34, 0, 27}), 
 ChordData({34, 1, 17}), ChordData({34, 8, 80}), ChordData({34, 41, 1}), ChordData({34, 65, 74}), 
 ChordData({34, 76, 64}), ChordData({34, 76, 128}), ChordData({36, 0, 81}), ChordData({36, 4, 24}), 
 ChordData({36, 4, 66}), ChordData({36, 8, 144}), ChordData({36, 36, 3}), ChordData({36, 37, 16}), 
 ChordData({36, 68, 24}), ChordData({38, 0, 2}), ChordData({38, 0, 129}), ChordData({38, 1, 24}), 
 ChordData({38, 8, 130}), ChordData({38, 32, 17}), ChordData({38, 36, 1}), ChordData({38, 64, 136}), 
 ChordData({48, 0, 82}), ChordData({48, 5, 80}), ChordData({48, 8, 136}), ChordData({48, 12, 8}), 
 ChordData({48, 65, 8}), ChordData({48, 65, 16}), ChordData({50, 1, 8}), ChordData({52, 1, 8}), 
 ChordData({52, 12, 16}), ChordData({52, 69, 0}), ChordData({54, 1, 16}), ChordData({128, 9, 67}), 
 ChordData({128, 9, 146}), ChordData({128, 33, 17}), ChordData({128, 64, 82}), ChordData({128, 64, 146}), 
 ChordData({128, 68, 19}), ChordData({128, 76, 2}), ChordData({128, 96, 19}), ChordData({128, 96, 74}), 
 ChordData({130, 0, 131}), ChordData({132, 1, 16}), ChordData({132, 1, 64}), ChordData({132, 40, 2}), 
 ChordData({132, 40, 16}), ChordData({144, 0, 17}), ChordData({144, 0, 83}), ChordData({144, 0, 88}), 
 ChordData({144, 0, 152}), ChordData({144, 0, 200}), ChordData({144, 1, 16}), ChordData({144, 4, 17}), 
 ChordData({144, 4, 72}), ChordData({144, 4, 88}), ChordData({144, 4, 130}), ChordData({144, 4, 131}), 
 ChordData({144, 4, 146}), ChordData({144, 9, 64}), ChordData({144, 41, 2}), ChordData({146, 0, 11}), 
 ChordData({146, 0, 25}), ChordData({146, 0, 129}), ChordData({146, 64, 130}), ChordData({148, 0, 0}), 
 ChordData({148, 9, 64}), ChordData({160, 1, 66}), ChordData({160, 1, 144}), ChordData({160, 1, 146}), 
 ChordData({160, 33, 16}), ChordData({160, 40, 1}), ChordData({160, 40, 16}), ChordData({160, 65, 26}), 
 ChordData({160, 69, 10}), ChordData({162, 76, 0}), ChordData({164, 0, 72}), ChordData({164, 1, 16}), 
 ChordData({164, 4, 1}), ChordData({164, 8, 2}), ChordData({164, 8, 128}), ChordData({164, 64, 16}), 
 ChordData({164, 68, 16}), ChordData({166, 1, 1}), ChordData({166, 1, 8}), ChordData({166, 8, 1}), 
 ChordData({180, 12, 0}), ChordData({180, 64, 130}), 
};

uint8_t const kmap5_Word_len23_anagram0_seqs[466] = {
 183, 143, 69, 220, 
 215, 162, 220, 99, 
 17, 252, 177, 40, 
 244, 88, 148, 82, 
 143, 9, 251, 238, 
 58, 122, 97, 221, 
 239, 135, 176, 223, 
 221, 237, 96, 81, 
 110, 176, 40, 197, 
 217, 67, 26, 44, 
 74, 113, 136, 132, 
 141, 150, 194, 166, 
 59, 254, 216, 79, 
 247, 115, 44, 204, 
 94, 25, 126, 164, 
 12, 63, 84, 226, 
 150, 237, 218, 239, 
 149, 244, 5, 75, 
 105, 15, 168, 224, 
 180, 178, 243, 110, 
 249, 136, 214, 195, 
 87, 244, 222, 190, 
 162, 95, 196, 34, 
 114, 175, 232, 23, 
 241, 30, 253, 89, 
 15, 95, 142, 140, 
 142, 214, 67, 102, 
 44, 10, 251, 162, 
 131, 207, 120, 107, 
 13, 94, 253, 162, 
 3, 192, 76, 113, 
 244, 172, 39, 56, 
 214, 91, 203, 200, 
 209, 220, 145, 145, 
 198, 122, 56, 139, 
 100, 26, 57, 235, 
 223, 205, 122, 125, 
 63, 74, 163, 254, 
 149, 167, 81, 139, 
 119, 158, 130, 101, 
 214, 163, 193, 160, 
 117, 243, 95, 35, 
 191, 216, 177, 93, 
 41, 205, 95, 100, 
 101, 243, 186, 177, 
 82, 154, 111, 206, 
 109, 64, 38, 105, 
 83, 52, 214, 221, 
 242, 182, 82, 137, 
 91, 187, 123, 133, 
 91, 118, 95, 233, 
 224, 199, 248, 244, 
 21, 178, 88, 21, 
 25, 171, 241, 181, 
 234, 92, 217, 109, 
 157, 227, 102, 171, 
 196, 129, 236, 4, 
 24, 133, 31, 184, 
 17, 238, 105, 66, 
 95, 87, 174, 110, 
 255, 42, 88, 251, 
 7, 175, 177, 245, 
 127, 200, 224, 126, 
 99, 253, 190, 6, 
 172, 253, 96, 95, 
 135, 174, 223, 81, 
 136, 52, 177, 239, 
 103, 143, 177, 239, 
 231, 122, 26, 13, 
 98, 172, 107, 184, 
 126, 177, 201, 156, 
 149, 55, 247, 26, 
 220, 85, 13, 134, 
 107, 91, 225, 168, 
 123, 195, 170, 253, 
 62, 231, 254, 3, 
 116, 191, 227, 78, 
 46, 177, 8, 158, 
 88, 236, 114, 143, 
 9, 144, 27, 128, 
 92, 10, 151, 225, 
 75, 224, 49, 227, 
 177, 77, 64, 88, 
 2, 122, 9, 26, 
 108, 155, 217, 73, 
 203, 236, 144, 101, 
 108, 49, 183, 177, 
 243, 110, 174, 24, 
 47, 87, 172, 146, 
 107, 221, 36, 34, 
 139, 164, 102, 215, 
 121, 55, 239, 207, 
 226, 151, 212, 245, 
 75, 42, 37, 62, 
 153, 18, 255, 156, 
 251, 72, 150, 152, 
 69, 35, 203, 162, 
 53, 111, 208, 185, 
 99, 189, 203, 33, 
 95, 130, 38, 152, 
 111, 217, 44, 45, 
 139, 238, 18, 171, 
 116, 148, 117, 147, 
 18, 150, 155, 21, 
 178, 152, 245, 24, 
 171, 49, 23, 216, 
 84, 8, 60, 76, 
 125, 46, 39, 244, 
 169, 85, 224, 102, 
 109, 223, 103, 61, 
 204, 216, 103, 79, 
 153, 177, 109, 214, 
 208, 231, 111, 232, 
 7, 230, 245, 163, 
 48, 219, 112, 121, 
 223, 39, 231, 222, 
 148, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len23_anagram0 = {
  LengthAndAnagram(23, 0), // seq_bit_len_and_anagram
  162, // num_chords
  kmap5_Word_len23_anagram0_chords, // chords
  kmap5_Word_len23_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len23_anagram1_chords[52] = {
 ChordData({0, 12, 1}), ChordData({0, 12, 18}), ChordData({0, 13, 18}), ChordData({0, 36, 19}), 
 ChordData({0, 68, 26}), ChordData({0, 100, 3}), ChordData({2, 68, 18}), ChordData({16, 0, 81}), 
 ChordData({16, 4, 9}), ChordData({16, 4, 66}), ChordData({16, 4, 137}), ChordData({16, 4, 138}), 
 ChordData({16, 64, 11}), ChordData({18, 0, 73}), ChordData({18, 0, 81}), ChordData({18, 0, 89}), 
 ChordData({18, 0, 201}), ChordData({18, 32, 17}), ChordData({18, 64, 80}), ChordData({18, 64, 192}), 
 ChordData({20, 4, 66}), ChordData({22, 0, 18}), ChordData({32, 0, 146}), ChordData({32, 12, 129}), 
 ChordData({34, 65, 128}), ChordData({36, 1, 0}), ChordData({36, 32, 10}), ChordData({38, 0, 128}), 
 ChordData({48, 0, 82}), ChordData({48, 1, 137}), ChordData({48, 8, 80}), ChordData({50, 76, 2}), 
 ChordData({52, 0, 18}), ChordData({54, 0, 128}), ChordData({54, 1, 16}), ChordData({128, 9, 130}), 
 ChordData({128, 65, 128}), ChordData({128, 76, 10}), ChordData({128, 96, 19}), ChordData({128, 104, 2}), 
 ChordData({144, 0, 26}), ChordData({144, 0, 82}), ChordData({144, 0, 83}), ChordData({144, 0, 89}), 
 ChordData({144, 1, 2}), ChordData({144, 8, 17}), ChordData({146, 0, 88}), ChordData({160, 1, 146}), 
 ChordData({164, 32, 1}), ChordData({164, 64, 8}), ChordData({164, 64, 128}), ChordData({164, 68, 16}), 
};

uint8_t const kmap5_Word_len23_anagram1_seqs[150] = {
 124, 252, 59, 62, 
 254, 34, 238, 99, 
 177, 124, 100, 135, 
 175, 161, 4, 254, 
 144, 133, 159, 45, 
 229, 214, 34, 103, 
 125, 189, 71, 180, 
 200, 61, 89, 15, 
 95, 209, 20, 140, 
 214, 59, 171, 142, 
 200, 200, 121, 71, 
 197, 123, 50, 100, 
 61, 207, 49, 239, 
 90, 38, 56, 140, 
 197, 100, 193, 111, 
 94, 227, 52, 131, 
 215, 45, 185, 175, 
 116, 176, 14, 133, 
 190, 118, 93, 171, 
 138, 172, 213, 54, 
 180, 22, 172, 134, 
 214, 35, 139, 57, 
 175, 129, 31, 206, 
 88, 246, 222, 126, 
 122, 114, 55, 189, 
 23, 41, 177, 216, 
 81, 102, 0, 50, 
 190, 2, 185, 199, 
 144, 197, 12, 152, 
 171, 94, 73, 68, 
 175, 5, 115, 239, 
 172, 146, 139, 233, 
 174, 91, 199, 60, 
 139, 117, 114, 33, 
 229, 150, 125, 230, 
 177, 150, 85, 67, 
 79, 153, 161, 223, 
 252, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len23_anagram1 = {
  LengthAndAnagram(23, 1), // seq_bit_len_and_anagram
  52, // num_chords
  kmap5_Word_len23_anagram1_chords, // chords
  kmap5_Word_len23_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len23_anagram2_chords[20] = {
 ChordData({0, 68, 26}), ChordData({2, 68, 18}), ChordData({2, 96, 3}), ChordData({4, 4, 82}), 
 ChordData({16, 4, 81}), ChordData({16, 4, 131}), ChordData({16, 4, 145}), ChordData({18, 0, 25}), 
 ChordData({18, 0, 89}), ChordData({18, 0, 131}), ChordData({18, 4, 145}), ChordData({20, 4, 192}), 
 ChordData({22, 0, 18}), ChordData({32, 68, 128}), ChordData({34, 33, 1}), ChordData({48, 1, 17}), 
 ChordData({48, 8, 192}), ChordData({128, 12, 18}), ChordData({160, 33, 1}), ChordData({164, 0, 17}), 
};

uint8_t const kmap5_Word_len23_anagram2_seqs[58] = {
 251, 26, 202, 48, 
 191, 37, 48, 135, 
 76, 218, 126, 249, 
 187, 150, 195, 191, 
 35, 211, 223, 121, 
 71, 207, 171, 50, 
 122, 94, 211, 224, 
 220, 250, 126, 200, 
 244, 77, 220, 198, 
 139, 46, 84, 63, 
 28, 27, 200, 214, 
 112, 125, 66, 54, 
 231, 143, 185, 101, 
 86, 200, 238, 234, 
 246, 9, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len23_anagram2 = {
  LengthAndAnagram(23, 2), // seq_bit_len_and_anagram
  20, // num_chords
  kmap5_Word_len23_anagram2_chords, // chords
  kmap5_Word_len23_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len23_anagram3_chords[6] = {
 ChordData({20, 0, 19}), ChordData({32, 69, 16}), ChordData({48, 1, 16}), ChordData({48, 9, 16}), 
 ChordData({48, 12, 128}), ChordData({128, 12, 18}), 
};

uint8_t const kmap5_Word_len23_anagram3_seqs[18] = {
 107, 116, 59, 88, 
 127, 3, 15, 215, 
 208, 209, 11, 205, 
 61, 113, 142, 95, 
 230, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len23_anagram3 = {
  LengthAndAnagram(23, 3), // seq_bit_len_and_anagram
  6, // num_chords
  kmap5_Word_len23_anagram3_chords, // chords
  kmap5_Word_len23_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len23_anagram4_chords[2] = {
 ChordData({128, 64, 18}), ChordData({160, 33, 1}), 
};

uint8_t const kmap5_Word_len23_anagram4_seqs[6] = {
 184, 9, 132, 203, 
 10, 25, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len23_anagram4 = {
  LengthAndAnagram(23, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len23_anagram4_chords, // chords
  kmap5_Word_len23_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len23_anagram5_chords[1] = {
 ChordData({16, 4, 146}), 
};

uint8_t const kmap5_Word_len23_anagram5_seqs[3] = {
 124, 249, 100, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len23_anagram5 = {
  LengthAndAnagram(23, 5), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len23_anagram5_chords, // chords
  kmap5_Word_len23_anagram5_seqs, // sequences
};

ChordData const kmap5_Word_len23_anagram6_chords[1] = {
 ChordData({0, 68, 18}), 
};

uint8_t const kmap5_Word_len23_anagram6_seqs[3] = {
 15, 252, 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len23_anagram6 = {
  LengthAndAnagram(23, 6), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len23_anagram6_chords, // chords
  kmap5_Word_len23_anagram6_seqs, // sequences
};

ChordData const kmap5_Word_len24_anagram0_chords[164] = {
 ChordData({0, 5, 26}), ChordData({0, 45, 9}), ChordData({0, 45, 80}), ChordData({0, 68, 3}), 
 ChordData({2, 0, 82}), ChordData({2, 0, 83}), ChordData({2, 0, 138}), ChordData({2, 1, 72}), 
 ChordData({2, 4, 3}), ChordData({2, 4, 11}), ChordData({2, 4, 65}), ChordData({2, 4, 67}), 
 ChordData({2, 4, 131}), ChordData({2, 41, 3}), ChordData({2, 41, 9}), ChordData({2, 65, 67}), 
 ChordData({2, 73, 24}), ChordData({2, 77, 8}), ChordData({2, 96, 2}), ChordData({4, 13, 80}), 
 ChordData({4, 32, 82}), ChordData({6, 8, 146}), ChordData({6, 9, 128}), ChordData({16, 0, 83}), 
 ChordData({16, 0, 91}), ChordData({16, 12, 17}), ChordData({16, 12, 18}), ChordData({16, 12, 24}), 
 ChordData({16, 12, 81}), ChordData({16, 12, 137}), ChordData({16, 36, 10}), ChordData({16, 36, 17}), 
 ChordData({16, 36, 82}), ChordData({16, 36, 192}), ChordData({16, 40, 66}), ChordData({16, 40, 129}), 
 ChordData({16, 64, 146}), ChordData({16, 68, 2}), ChordData({16, 68, 9}), ChordData({16, 68, 137}), 
 ChordData({16, 68, 138}), ChordData({16, 77, 3}), ChordData({18, 1, 144}), ChordData({18, 8, 19}), 
 ChordData({18, 9, 8}), ChordData({18, 12, 24}), ChordData({18, 12, 130}), ChordData({18, 32, 11}), 
 ChordData({18, 32, 65}), ChordData({18, 64, 2}), ChordData({18, 64, 8}), ChordData({18, 64, 9}), 
 ChordData({18, 64, 24}), ChordData({18, 64, 72}), ChordData({18, 68, 129}), ChordData({20, 4, 3}), 
 ChordData({20, 4, 9}), ChordData({20, 4, 19}), ChordData({20, 4, 67}), ChordData({20, 4, 82}), 
 ChordData({20, 4, 137}), ChordData({20, 8, 129}), ChordData({20, 32, 66}), ChordData({20, 32, 80}), 
 ChordData({22, 0, 138}), ChordData({22, 4, 16}), ChordData({22, 4, 17}), ChordData({22, 4, 80}), 
 ChordData({32, 9, 0}), ChordData({32, 9, 19}), ChordData({32, 9, 25}), ChordData({32, 9, 67}), 
 ChordData({32, 9, 152}), ChordData({32, 9, 192}), ChordData({32, 32, 18}), ChordData({32, 33, 192}), 
 ChordData({32, 64, 83}), ChordData({34, 0, 138}), ChordData({34, 8, 19}), ChordData({34, 8, 154}), 
 ChordData({34, 33, 1}), ChordData({34, 65, 128}), ChordData({34, 104, 0}), ChordData({36, 8, 18}), 
 ChordData({36, 12, 128}), ChordData({36, 32, 10}), ChordData({36, 32, 80}), ChordData({38, 64, 128}), 
 ChordData({48, 0, 25}), ChordData({48, 0, 74}), ChordData({48, 0, 137}), ChordData({48, 0, 145}), 
 ChordData({48, 0, 200}), ChordData({48, 0, 209}), ChordData({48, 4, 25}), ChordData({48, 4, 80}), 
 ChordData({48, 4, 152}), ChordData({48, 4, 194}), ChordData({48, 5, 8}), ChordData({48, 5, 138}), 
 ChordData({48, 8, 146}), ChordData({48, 8, 192}), ChordData({48, 44, 18}), ChordData({48, 64, 18}), 
 ChordData({48, 64, 136}), ChordData({48, 64, 144}), ChordData({48, 65, 24}), ChordData({48, 65, 136}), 
 ChordData({48, 76, 0}), ChordData({50, 0, 65}), ChordData({50, 0, 82}), ChordData({50, 0, 88}), 
 ChordData({50, 0, 146}), ChordData({50, 1, 200}), ChordData({50, 8, 80}), ChordData({50, 9, 16}), 
 ChordData({52, 0, 17}), ChordData({52, 4, 136}), ChordData({52, 12, 18}), ChordData({52, 13, 16}), 
 ChordData({52, 65, 0}), ChordData({128, 0, 11}), ChordData({128, 0, 210}), ChordData({128, 4, 1}), 
 ChordData({128, 4, 27}), ChordData({128, 4, 82}), ChordData({128, 4, 210}), ChordData({128, 41, 66}), 
 ChordData({130, 0, 153}), ChordData({130, 4, 25}), ChordData({130, 4, 194}), ChordData({144, 8, 17}), 
 ChordData({144, 8, 25}), ChordData({144, 32, 11}), ChordData({144, 32, 66}), ChordData({144, 32, 73}), 
 ChordData({144, 32, 74}), ChordData({144, 32, 193}), ChordData({144, 64, 18}), ChordData({144, 64, 74}), 
 ChordData({144, 64, 208}), ChordData({144, 68, 9}), ChordData({146, 32, 2}), ChordData({146, 64, 17}), 
 ChordData({148, 0, 17}), ChordData({148, 0, 88}), ChordData({148, 0, 128}), ChordData({150, 0, 130}), 
 ChordData({160, 1, 26}), ChordData({160, 9, 16}), ChordData({160, 13, 16}), ChordData({160, 32, 19}), 
 ChordData({160, 64, 10}), ChordData({160, 64, 130}), ChordData({160, 65, 8}), ChordData({162, 8, 18}), 
 ChordData({164, 64, 1}), ChordData({164, 64, 8}), ChordData({164, 64, 26}), ChordData({176, 0, 82}), 
 ChordData({176, 5, 24}), ChordData({176, 9, 8}), ChordData({178, 1, 24}), ChordData({180, 9, 16}), 
};

uint8_t const kmap5_Word_len24_anagram0_seqs[492] = {
 221, 43, 150, 199, 
 94, 139, 194, 126, 
 139, 60, 240, 119, 
 184, 35, 35, 114, 
 59, 120, 72, 163, 
 131, 162, 211, 117, 
 247, 120, 131, 163, 
 247, 120, 47, 50, 
 114, 114, 127, 131, 
 115, 79, 131, 199, 
 6, 139, 199, 70, 
 139, 2, 76, 119, 
 97, 71, 139, 197, 
 209, 240, 0, 27, 
 100, 210, 126, 139, 
 77, 74, 100, 19, 
 27, 149, 173, 56, 
 68, 165, 229, 188, 
 103, 171, 148, 241, 
 239, 188, 248, 209, 
 251, 241, 85, 189, 
 114, 235, 143, 209, 
 122, 79, 200, 94, 
 209, 251, 199, 188, 
 226, 95, 100, 236, 
 69, 200, 130, 204, 
 209, 204, 20, 125, 
 224, 6, 76, 193, 
 248, 193, 127, 103, 
 13, 193, 122, 79, 
 248, 26, 200, 7, 
 248, 139, 107, 26, 
 119, 209, 183, 131, 
 69, 157, 206, 235, 
 248, 163, 241, 105, 
 208, 62, 166, 131, 
 199, 44, 35, 193, 
 56, 193, 163, 193, 
 14, 19, 172, 55, 
 97, 84, 189, 163, 
 50, 193, 193, 247, 
 67, 143, 232, 118, 
 237, 207, 122, 248, 
 219, 124, 47, 205, 
 120, 130, 251, 205, 
 141, 94, 125, 231, 
 216, 200, 210, 108, 
 100, 210, 152, 215, 
 205, 138, 67, 235, 
 246, 179, 109, 246, 
 207, 109, 127, 196, 
 124, 229, 139, 183, 
 21, 139, 183, 85, 
 139, 114, 21, 139, 
 224, 85, 139, 82, 
 172, 68, 172, 238, 
 150, 29, 85, 97, 
 114, 53, 148, 52, 
 90, 65, 195, 205, 
 149, 220, 104, 73, 
 221, 64, 118, 29, 
 213, 9, 172, 198, 
 9, 184, 53, 246, 
 79, 125, 141, 125, 
 85, 100, 253, 86, 
 97, 125, 29, 10, 
 235, 171, 171, 104, 
 149, 42, 87, 85, 
 77, 87, 247, 200, 
 85, 201, 34, 107, 
 169, 116, 250, 87, 
 215, 47, 82, 215, 
 234, 186, 79, 72, 
 95, 197, 86, 248, 
 208, 144, 94, 209, 
 72, 230, 188, 98, 
 226, 44, 204, 207, 
 149, 235, 80, 209, 
 133, 170, 173, 133, 
 170, 189, 208, 26, 
 188, 100, 104, 13, 
 124, 120, 206, 55, 
 34, 213, 184, 117, 
 196, 163, 82, 215, 
 224, 117, 208, 50, 
 10, 201, 107, 110, 
 196, 107, 56, 209, 
 189, 239, 188, 214, 
 239, 201, 241, 203, 
 222, 253, 250, 139, 
 193, 125, 133, 152, 
 119, 169, 130, 155, 
 68, 247, 119, 153, 
 152, 122, 251, 143, 
 155, 34, 248, 75, 
 41, 194, 18, 139, 
 224, 57, 122, 251, 
 55, 169, 146, 56, 
 79, 183, 142, 185, 
 209, 122, 185, 103, 
 100, 154, 200, 50, 
 197, 44, 213, 114, 
 200, 82, 172, 44, 
 229, 76, 107, 204, 
 13, 98, 76, 13, 
 146, 20, 188, 33, 
 245, 207, 200, 114, 
 208, 14, 115, 185, 
 235, 150, 123, 205, 
 43, 169, 205, 217, 
 200, 45, 105, 208, 
 101, 86, 133, 93, 
 110, 141, 221, 115, 
 185, 101, 214, 99, 
 64, 86, 13, 64, 
 86, 10, 93, 86, 
 13, 195, 229, 150, 
 33, 107, 127, 125, 
 86, 13, 253, 38, 
 160, 146, 117, 209, 
 185, 175, 208, 208, 
 154, 209, 3, 53, 
 215, 253, 102, 209, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len24_anagram0 = {
  LengthAndAnagram(24, 0), // seq_bit_len_and_anagram
  164, // num_chords
  kmap5_Word_len24_anagram0_chords, // chords
  kmap5_Word_len24_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len24_anagram1_chords[36] = {
 ChordData({0, 5, 65}), ChordData({2, 1, 130}), ChordData({2, 4, 81}), ChordData({2, 4, 89}), 
 ChordData({2, 4, 146}), ChordData({2, 96, 3}), ChordData({4, 4, 146}), ChordData({16, 12, 81}), 
 ChordData({16, 68, 82}), ChordData({18, 12, 24}), ChordData({18, 64, 8}), ChordData({18, 64, 9}), 
 ChordData({18, 64, 19}), ChordData({18, 68, 129}), ChordData({18, 68, 136}), ChordData({20, 4, 25}), 
 ChordData({20, 4, 146}), ChordData({22, 0, 81}), ChordData({32, 69, 16}), ChordData({36, 4, 128}), 
 ChordData({48, 4, 66}), ChordData({48, 5, 128}), ChordData({48, 8, 192}), ChordData({48, 12, 144}), 
 ChordData({52, 5, 0}), ChordData({128, 0, 19}), ChordData({128, 4, 11}), ChordData({128, 96, 18}), 
 ChordData({130, 4, 9}), ChordData({130, 4, 11}), ChordData({130, 4, 74}), ChordData({148, 0, 17}), 
 ChordData({148, 8, 8}), ChordData({176, 0, 24}), ChordData({176, 0, 82}), ChordData({178, 1, 24}), 
};

uint8_t const kmap5_Word_len24_anagram1_seqs[108] = {
 114, 223, 117, 72, 
 211, 117, 191, 55, 
 114, 114, 251, 163, 
 251, 56, 79, 192, 
 132, 99, 223, 26, 
 149, 241, 229, 188, 
 242, 184, 14, 241, 
 119, 212, 193, 58, 
 14, 163, 193, 122, 
 184, 14, 115, 97, 
 232, 207, 193, 58, 
 79, 237, 215, 122, 
 237, 23, 77, 114, 
 59, 205, 221, 126, 
 13, 124, 251, 74, 
 143, 88, 197, 228, 
 135, 213, 156, 69, 
 76, 107, 206, 79, 
 60, 252, 222, 252, 
 109, 150, 248, 170, 
 121, 172, 12, 155, 
 250, 55, 169, 143, 
 55, 169, 248, 50, 
 154, 45, 239, 188, 
 89, 48, 213, 234, 
 186, 169, 152, 117, 
 197, 107, 56, 169, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len24_anagram1 = {
  LengthAndAnagram(24, 1), // seq_bit_len_and_anagram
  36, // num_chords
  kmap5_Word_len24_anagram1_chords, // chords
  kmap5_Word_len24_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len24_anagram2_chords[8] = {
 ChordData({2, 0, 19}), ChordData({18, 64, 19}), ChordData({20, 4, 130}), ChordData({22, 0, 81}), 
 ChordData({48, 5, 17}), ChordData({128, 4, 146}), ChordData({128, 64, 18}), ChordData({144, 64, 2}), 
};

uint8_t const kmap5_Word_len24_anagram2_seqs[24] = {
 184, 115, 131, 97, 
 214, 120, 237, 233, 
 209, 109, 199, 114, 
 247, 11, 125, 152, 
 68, 191, 64, 238, 
 150, 193, 152, 193, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len24_anagram2 = {
  LengthAndAnagram(24, 2), // seq_bit_len_and_anagram
  8, // num_chords
  kmap5_Word_len24_anagram2_chords, // chords
  kmap5_Word_len24_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len24_anagram3_chords[2] = {
 ChordData({22, 8, 16}), ChordData({48, 8, 80}), 
};

uint8_t const kmap5_Word_len24_anagram3_seqs[6] = {
 142, 109, 214, 107, 
 169, 209, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len24_anagram3 = {
  LengthAndAnagram(24, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len24_anagram3_chords, // chords
  kmap5_Word_len24_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len24_anagram4_chords[2] = {
 ChordData({16, 68, 18}), ChordData({16, 68, 146}), 
};

uint8_t const kmap5_Word_len24_anagram4_seqs[6] = {
 191, 248, 193, 184, 
 31, 200, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len24_anagram4 = {
  LengthAndAnagram(24, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len24_anagram4_chords, // chords
  kmap5_Word_len24_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len24_anagram5_chords[1] = {
 ChordData({48, 8, 80}), 
};

uint8_t const kmap5_Word_len24_anagram5_seqs[3] = {
 226, 229, 188, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len24_anagram5 = {
  LengthAndAnagram(24, 5), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len24_anagram5_chords, // chords
  kmap5_Word_len24_anagram5_seqs, // sequences
};

ChordData const kmap5_Word_len25_anagram0_chords[179] = {
 ChordData({0, 36, 80}), ChordData({2, 9, 18}), ChordData({2, 12, 136}), ChordData({2, 40, 128}), 
 ChordData({2, 68, 144}), ChordData({2, 68, 193}), ChordData({2, 68, 200}), ChordData({2, 73, 16}), 
 ChordData({2, 96, 128}), ChordData({4, 36, 18}), ChordData({6, 0, 10}), ChordData({6, 0, 83}), 
 ChordData({6, 0, 89}), ChordData({16, 0, 155}), ChordData({16, 0, 194}), ChordData({16, 4, 146}), 
 ChordData({16, 4, 208}), ChordData({16, 5, 26}), ChordData({16, 9, 152}), ChordData({16, 32, 81}), 
 ChordData({16, 32, 136}), ChordData({16, 36, 129}), ChordData({16, 65, 3}), ChordData({16, 68, 90}), 
 ChordData({16, 68, 131}), ChordData({16, 68, 144}), ChordData({16, 69, 1}), ChordData({16, 100, 17}), 
 ChordData({16, 100, 136}), ChordData({16, 100, 144}), ChordData({18, 0, 27}), ChordData({18, 0, 131}), 
 ChordData({18, 1, 9}), ChordData({18, 1, 145}), ChordData({18, 4, 130}), ChordData({18, 9, 0}), 
 ChordData({18, 65, 8}), ChordData({18, 72, 24}), ChordData({18, 76, 8}), ChordData({18, 76, 128}), 
 ChordData({18, 96, 192}), ChordData({20, 1, 16}), ChordData({20, 12, 0}), ChordData({20, 12, 192}), 
 ChordData({20, 64, 8}), ChordData({20, 68, 16}), ChordData({20, 68, 17}), ChordData({20, 68, 80}), 
 ChordData({22, 0, 136}), ChordData({22, 8, 17}), ChordData({22, 8, 192}), ChordData({22, 64, 80}), 
 ChordData({32, 0, 83}), ChordData({32, 1, 26}), ChordData({32, 1, 65}), ChordData({32, 1, 146}), 
 ChordData({32, 4, 65}), ChordData({32, 4, 82}), ChordData({32, 4, 89}), ChordData({32, 4, 131}), 
 ChordData({32, 4, 136}), ChordData({32, 4, 194}), ChordData({32, 40, 82}), ChordData({32, 41, 10}), 
 ChordData({32, 69, 10}), ChordData({32, 69, 130}), ChordData({32, 73, 24}), ChordData({34, 0, 82}), 
 ChordData({34, 1, 26}), ChordData({34, 1, 89}), ChordData({34, 4, 144}), ChordData({34, 5, 72}), 
 ChordData({34, 5, 81}), ChordData({34, 5, 146}), ChordData({34, 5, 200}), ChordData({36, 0, 26}), 
 ChordData({36, 8, 26}), ChordData({36, 8, 128}), ChordData({36, 13, 130}), ChordData({36, 13, 136}), 
 ChordData({36, 40, 1}), ChordData({38, 9, 18}), ChordData({38, 9, 136}), ChordData({48, 0, 81}), 
 ChordData({48, 1, 25}), ChordData({48, 1, 26}), ChordData({48, 8, 194}), ChordData({48, 9, 128}), 
 ChordData({48, 12, 64}), ChordData({48, 12, 145}), ChordData({48, 13, 8}), ChordData({48, 13, 9}), 
 ChordData({48, 13, 136}), ChordData({48, 33, 137}), ChordData({48, 37, 10}), ChordData({48, 37, 17}), 
 ChordData({48, 37, 18}), ChordData({48, 44, 8}), ChordData({48, 64, 128}), ChordData({48, 64, 193}), 
 ChordData({48, 68, 128}), ChordData({48, 69, 8}), ChordData({48, 69, 24}), ChordData({50, 1, 72}), 
 ChordData({50, 5, 8}), ChordData({50, 8, 9}), ChordData({50, 8, 19}), ChordData({50, 8, 208}), 
 ChordData({50, 12, 3}), ChordData({50, 12, 9}), ChordData({50, 12, 16}), ChordData({50, 64, 10}), 
 ChordData({50, 64, 129}), ChordData({50, 65, 65}), ChordData({50, 65, 72}), ChordData({52, 4, 24}), 
 ChordData({52, 4, 73}), ChordData({52, 4, 144}), ChordData({52, 4, 193}), ChordData({52, 5, 128}), 
 ChordData({52, 12, 2}), ChordData({52, 65, 128}), ChordData({54, 64, 64}), ChordData({128, 12, 144}), 
 ChordData({128, 12, 145}), ChordData({128, 12, 152}), ChordData({128, 12, 193}), ChordData({128, 12, 200}), 
 ChordData({128, 32, 16}), ChordData({128, 32, 194}), ChordData({128, 36, 26}), ChordData({128, 64, 19}), 
 ChordData({128, 68, 18}), ChordData({128, 68, 144}), ChordData({128, 68, 208}), ChordData({130, 8, 9}), 
 ChordData({130, 8, 16}), ChordData({130, 12, 3}), ChordData({130, 68, 18}), ChordData({132, 4, 1}), 
 ChordData({132, 4, 81}), ChordData({132, 4, 145}), ChordData({132, 12, 16}), ChordData({134, 0, 9}), 
 ChordData({134, 0, 72}), ChordData({134, 0, 88}), ChordData({144, 0, 146}), ChordData({144, 0, 154}), 
 ChordData({144, 1, 81}), ChordData({144, 8, 9}), ChordData({144, 40, 18}), ChordData({144, 72, 24}), 
 ChordData({144, 76, 8}), ChordData({148, 0, 16}), ChordData({148, 72, 8}), ChordData({150, 64, 16}), 
 ChordData({160, 0, 82}), ChordData({160, 1, 89}), ChordData({162, 0, 72}), ChordData({162, 1, 24}), 
 ChordData({164, 9, 130}), ChordData({176, 1, 9}), ChordData({176, 1, 128}), ChordData({176, 1, 129}), 
 ChordData({176, 1, 136}), ChordData({176, 8, 19}), ChordData({176, 8, 146}), ChordData({176, 64, 129}), 
 ChordData({176, 65, 136}), ChordData({176, 69, 64}), ChordData({176, 72, 1}), ChordData({178, 8, 65}), 
 ChordData({180, 0, 17}), ChordData({180, 0, 81}), ChordData({180, 0, 129}), ChordData({180, 0, 130}), 
 ChordData({180, 1, 72}), ChordData({180, 1, 192}), ChordData({180, 8, 2}), 
};

uint8_t const kmap5_Word_len25_anagram0_seqs[560] = {
 236, 247, 69, 248, 
 29, 44, 190, 78, 
 124, 226, 167, 192, 
 184, 31, 230, 41, 
 140, 220, 211, 8, 
 189, 134, 88, 12, 
 179, 252, 20, 24, 
 216, 183, 86, 182, 
 65, 29, 20, 220, 
 105, 39, 109, 71, 
 207, 160, 243, 170, 
 65, 104, 145, 245, 
 19, 149, 107, 242, 
 139, 187, 125, 69, 
 23, 189, 106, 58, 
 182, 22, 198, 51, 
 147, 149, 249, 233, 
 88, 112, 103, 188, 
 87, 1, 188, 192, 
 19, 249, 232, 67, 
 240, 6, 119, 254, 
 59, 182, 254, 192, 
 94, 3, 153, 121, 
 159, 130, 245, 230, 
 74, 131, 112, 206, 
 221, 232, 156, 187, 
 161, 243, 242, 79, 
 131, 230, 227, 20, 
 29, 220, 141, 122, 
 29, 71, 67, 116, 
 152, 215, 232, 48, 
 79, 194, 198, 20, 
 218, 186, 243, 126, 
 252, 130, 150, 143, 
 141, 28, 220, 172, 
 161, 253, 126, 112, 
 112, 251, 61, 105, 
 235, 15, 58, 173, 
 145, 155, 55, 206, 
 201, 196, 70, 150, 
 54, 193, 43, 183, 
 21, 175, 171, 170, 
 165, 92, 237, 186, 
 174, 18, 149, 114, 
 127, 85, 120, 41, 
 235, 203, 95, 93, 
 125, 188, 250, 244, 
 170, 245, 9, 95, 
 234, 83, 172, 194, 
 74, 100, 85, 139, 
 60, 240, 10, 31, 
 232, 42, 133, 173, 
 90, 196, 89, 172, 
 82, 117, 186, 82, 
 110, 71, 33, 120, 
 165, 249, 23, 25, 
 168, 112, 255, 70, 
 224, 47, 13, 202, 
 64, 125, 234, 171, 
 106, 169, 53, 182, 
 178, 81, 141, 125, 
 79, 143, 197, 158, 
 94, 139, 199, 106, 
 236, 251, 29, 44, 
 246, 52, 90, 148, 
 122, 117, 93, 23, 
 90, 207, 234, 133, 
 101, 172, 130, 100, 
 158, 106, 209, 47, 
 82, 163, 111, 159, 
 51, 197, 215, 135, 
 142, 15, 213, 23, 
 95, 33, 153, 172, 
 240, 24, 178, 87, 
 104, 248, 199, 188, 
 200, 126, 161, 153, 
 159, 179, 22, 170, 
 174, 46, 84, 45, 
 231, 66, 245, 233, 
 161, 53, 124, 120, 
 133, 94, 104, 157, 
 42, 176, 142, 250, 
 227, 104, 61, 115, 
 222, 27, 148, 33, 
 206, 251, 120, 195, 
 89, 255, 134, 243, 
 239, 14, 231, 209, 
 80, 209, 133, 234, 
 156, 195, 64, 203, 
 5, 203, 64, 237, 
 95, 213, 251, 189, 
 88, 175, 255, 93, 
 147, 220, 247, 228, 
 222, 15, 201, 189, 
 241, 163, 27, 57, 
 64, 247, 150, 9, 
 142, 15, 158, 27, 
 115, 239, 73, 115, 
 227, 211, 83, 76, 
 57, 121, 138, 169, 
 44, 119, 115, 5, 
 89, 38, 189, 34, 
 203, 13, 137, 151, 
 251, 136, 185, 33, 
 36, 209, 111, 200, 
 149, 167, 152, 55, 
 169, 113, 118, 115, 
 255, 50, 14, 226, 
 111, 152, 108, 121, 
 127, 217, 94, 46, 
 183, 253, 109, 210, 
 126, 193, 220, 108, 
 55, 169, 45, 71, 
 82, 219, 142, 164, 
 130, 188, 9, 178, 
 130, 103, 217, 229, 
 90, 46, 102, 180, 
 30, 178, 205, 232, 
 152, 193, 171, 225, 
 29, 83, 219, 102, 
 243, 134, 44, 104, 
 109, 222, 201, 128, 
 117, 37, 87, 110, 
 83, 97, 213, 145, 
 212, 220, 129, 163, 
 61, 37, 22, 47, 
 21, 86, 195, 76, 
 72, 190, 132, 144, 
 76, 89, 21, 154, 
 51, 94, 46, 103, 
 194, 205, 66, 53, 
 207, 33, 21, 146, 
 67, 202, 67, 7, 
 115, 121, 150, 228, 
 198, 183, 238, 51, 
 79, 110, 179, 119, 
 159, 119, 100, 204, 
 218, 200, 210, 82, 
 161, 97, 74, 51, 
 245, 198, 140, 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len25_anagram0 = {
  LengthAndAnagram(25, 0), // seq_bit_len_and_anagram
  179, // num_chords
  kmap5_Word_len25_anagram0_chords, // chords
  kmap5_Word_len25_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len25_anagram1_chords[38] = {
 ChordData({0, 68, 89}), ChordData({6, 0, 81}), ChordData({16, 0, 74}), ChordData({16, 13, 128}), 
 ChordData({16, 64, 130}), ChordData({18, 1, 11}), ChordData({18, 64, 17}), ChordData({18, 76, 8}), 
 ChordData({20, 4, 16}), ChordData({20, 36, 80}), ChordData({22, 8, 0}), ChordData({22, 8, 16}), 
 ChordData({32, 5, 26}), ChordData({34, 0, 9}), ChordData({48, 1, 80}), ChordData({48, 8, 17}), 
 ChordData({48, 12, 8}), ChordData({48, 12, 17}), ChordData({48, 69, 16}), ChordData({48, 69, 24}), 
 ChordData({50, 8, 9}), ChordData({50, 8, 73}), ChordData({50, 64, 129}), ChordData({50, 64, 136}), 
 ChordData({50, 72, 2}), ChordData({50, 72, 16}), ChordData({52, 4, 129}), ChordData({52, 68, 1}), 
 ChordData({54, 0, 82}), ChordData({128, 12, 1}), ChordData({128, 73, 10}), ChordData({130, 64, 81}), 
 ChordData({144, 0, 208}), ChordData({144, 1, 81}), ChordData({144, 40, 17}), ChordData({160, 5, 136}), 
 ChordData({176, 8, 16}), ChordData({180, 0, 64}), 
};

uint8_t const kmap5_Word_len25_anagram1_seqs[119] = {
 114, 251, 26, 164, 
 205, 206, 89, 196, 
 138, 238, 28, 159, 
 108, 16, 218, 97, 
 180, 51, 222, 58, 
 132, 185, 248, 19, 
 172, 223, 154, 127, 
 27, 219, 23, 79, 
 156, 130, 110, 59, 
 5, 205, 151, 175, 
 112, 244, 234, 220, 
 186, 171, 226, 88, 
 239, 188, 207, 89, 
 171, 227, 95, 93, 
 175, 225, 111, 128, 
 191, 193, 58, 202, 
 205, 121, 148, 179, 
 92, 161, 58, 190, 
 66, 117, 212, 193, 
 220, 160, 131, 119, 
 56, 223, 247, 228, 
 11, 238, 255, 44, 
 184, 211, 251, 50, 
 254, 101, 81, 19, 
 208, 48, 114, 155, 
 60, 120, 138, 187, 
 148, 243, 198, 60, 
 230, 125, 125, 74, 
 184, 142, 201, 89, 
 90, 86, 49, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len25_anagram1 = {
  LengthAndAnagram(25, 1), // seq_bit_len_and_anagram
  38, // num_chords
  kmap5_Word_len25_anagram1_chords, // chords
  kmap5_Word_len25_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len25_anagram2_chords[8] = {
 ChordData({0, 36, 3}), ChordData({16, 0, 139}), ChordData({16, 4, 136}), ChordData({16, 4, 152}), 
 ChordData({18, 64, 27}), ChordData({20, 4, 128}), ChordData({52, 4, 129}), ChordData({148, 0, 64}), 
};

uint8_t const kmap5_Word_len25_anagram2_seqs[25] = {
 127, 247, 200, 12, 
 58, 235, 241, 79, 
 100, 229, 193, 95, 
 13, 140, 158, 247, 
 91, 243, 83, 255, 
 119, 228, 108, 45, 
 197, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len25_anagram2 = {
  LengthAndAnagram(25, 2), // seq_bit_len_and_anagram
  8, // num_chords
  kmap5_Word_len25_anagram2_chords, // chords
  kmap5_Word_len25_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len25_anagram3_chords[4] = {
 ChordData({0, 12, 18}), ChordData({48, 1, 17}), ChordData({48, 5, 16}), ChordData({160, 65, 0}), 
};

uint8_t const kmap5_Word_len25_anagram3_seqs[13] = {
 124, 252, 45, 215, 
 93, 61, 195, 223, 
 135, 230, 67, 86, 
 8, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len25_anagram3 = {
  LengthAndAnagram(25, 3), // seq_bit_len_and_anagram
  4, // num_chords
  kmap5_Word_len25_anagram3_chords, // chords
  kmap5_Word_len25_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len25_anagram4_chords[2] = {
 ChordData({16, 4, 19}), ChordData({20, 0, 16}), 
};

uint8_t const kmap5_Word_len25_anagram4_seqs[7] = {
 191, 231, 45, 155, 
 91, 243, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len25_anagram4 = {
  LengthAndAnagram(25, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len25_anagram4_chords, // chords
  kmap5_Word_len25_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len26_anagram0_chords[154] = {
 ChordData({0, 4, 210}), ChordData({0, 36, 139}), ChordData({0, 44, 129}), ChordData({0, 72, 16}), 
 ChordData({0, 109, 2}), ChordData({2, 5, 9}), ChordData({2, 5, 80}), ChordData({2, 32, 201}), 
 ChordData({4, 12, 10}), ChordData({4, 12, 192}), ChordData({6, 4, 130}), ChordData({6, 9, 26}), 
 ChordData({6, 12, 3}), ChordData({6, 12, 16}), ChordData({6, 36, 80}), ChordData({16, 0, 147}), 
 ChordData({16, 1, 3}), ChordData({16, 8, 83}), ChordData({16, 8, 137}), ChordData({16, 13, 131}), 
 ChordData({16, 33, 26}), ChordData({16, 36, 72}), ChordData({16, 44, 16}), ChordData({16, 64, 139}), 
 ChordData({16, 72, 18}), ChordData({16, 100, 131}), ChordData({18, 0, 73}), ChordData({18, 0, 90}), 
 ChordData({18, 0, 202}), ChordData({18, 0, 209}), ChordData({18, 4, 144}), ChordData({18, 9, 81}), 
 ChordData({18, 12, 8}), ChordData({18, 13, 72}), ChordData({18, 33, 65}), ChordData({18, 65, 24}), 
 ChordData({18, 72, 128}), ChordData({18, 96, 8}), ChordData({20, 0, 19}), ChordData({20, 0, 131}), 
 ChordData({20, 0, 147}), ChordData({20, 0, 155}), ChordData({20, 36, 8}), ChordData({20, 68, 8}), 
 ChordData({22, 0, 146}), ChordData({32, 12, 11}), ChordData({32, 12, 17}), ChordData({32, 12, 74}), 
 ChordData({32, 12, 136}), ChordData({32, 32, 26}), ChordData({32, 36, 138}), ChordData({32, 68, 137}), 
 ChordData({32, 68, 145}), ChordData({32, 72, 18}), ChordData({34, 5, 17}), ChordData({34, 12, 17}), 
 ChordData({34, 13, 24}), ChordData({34, 33, 131}), ChordData({34, 33, 193}), ChordData({34, 68, 80}), 
 ChordData({36, 0, 195}), ChordData({36, 1, 18}), ChordData({36, 4, 144}), ChordData({38, 1, 88}), 
 ChordData({38, 4, 145}), ChordData({48, 0, 152}), ChordData({48, 0, 194}), ChordData({48, 1, 137}), 
 ChordData({48, 5, 26}), ChordData({48, 5, 146}), ChordData({48, 8, 129}), ChordData({48, 8, 152}), 
 ChordData({48, 12, 144}), ChordData({48, 44, 192}), ChordData({48, 64, 72}), ChordData({48, 65, 144}), 
 ChordData({48, 72, 16}), ChordData({48, 72, 131}), ChordData({48, 77, 0}), ChordData({50, 33, 1}), 
 ChordData({50, 72, 18}), ChordData({50, 76, 2}), ChordData({50, 76, 64}), ChordData({52, 0, 144}), 
 ChordData({52, 0, 193}), ChordData({52, 12, 144}), ChordData({52, 36, 17}), ChordData({52, 36, 18}), 
 ChordData({52, 68, 1}), ChordData({54, 1, 128}), ChordData({54, 8, 17}), ChordData({54, 64, 10}), 
 ChordData({54, 64, 128}), ChordData({54, 68, 8}), ChordData({128, 4, 24}), ChordData({128, 5, 19}), 
 ChordData({128, 5, 144}), ChordData({128, 8, 10}), ChordData({128, 9, 10}), ChordData({128, 40, 65}), 
 ChordData({128, 68, 26}), ChordData({128, 76, 24}), ChordData({130, 1, 192}), ChordData({130, 8, 3}), 
 ChordData({130, 64, 202}), ChordData({130, 76, 8}), ChordData({132, 4, 129}), ChordData({132, 36, 24}), 
 ChordData({134, 8, 17}), ChordData({134, 32, 192}), ChordData({144, 0, 147}), ChordData({144, 1, 2}), 
 ChordData({144, 9, 16}), ChordData({144, 9, 19}), ChordData({144, 9, 67}), ChordData({144, 9, 81}), 
 ChordData({144, 32, 19}), ChordData({144, 64, 26}), ChordData({144, 65, 144}), ChordData({144, 104, 1}), 
 ChordData({146, 0, 131}), ChordData({146, 9, 2}), ChordData({148, 0, 194}), ChordData({148, 68, 10}), 
 ChordData({160, 8, 67}), ChordData({160, 8, 138}), ChordData({160, 12, 9}), ChordData({160, 32, 82}), 
 ChordData({160, 36, 17}), ChordData({160, 37, 3}), ChordData({160, 68, 24}), ChordData({160, 69, 24}), 
 ChordData({162, 8, 72}), ChordData({162, 8, 136}), ChordData({162, 33, 3}), ChordData({162, 64, 65}), 
 ChordData({162, 69, 128}), ChordData({164, 0, 10}), ChordData({164, 0, 82}), ChordData({164, 0, 146}), 
 ChordData({164, 4, 26}), ChordData({166, 1, 64}), ChordData({166, 4, 9}), ChordData({176, 1, 17}), 
 ChordData({176, 9, 24}), ChordData({176, 33, 8}), ChordData({176, 72, 128}), ChordData({180, 0, 10}), 
 ChordData({180, 1, 16}), ChordData({180, 1, 136}), ChordData({180, 32, 17}), ChordData({180, 64, 64}), 
 ChordData({180, 64, 136}), ChordData({182, 8, 128}), 
};

uint8_t const kmap5_Word_len26_anagram0_seqs[501] = {
 242, 244, 91, 226, 
 107, 129, 119, 236, 
 233, 35, 31, 23, 
 12, 0, 123, 44, 
 142, 118, 175, 39, 
 223, 253, 206, 136, 
 22, 120, 237, 49, 
 190, 54, 122, 137, 
 255, 173, 209, 96, 
 27, 45, 150, 19, 
 219, 227, 77, 108, 
 63, 219, 126, 71, 
 216, 26, 220, 120, 
 238, 58, 227, 73, 
 41, 231, 104, 114, 
 180, 222, 61, 22, 
 201, 221, 90, 145, 
 241, 194, 94, 205, 
 62, 70, 175, 65, 
 103, 13, 235, 232, 
 80, 2, 126, 58, 
 54, 122, 86, 177, 
 140, 162, 215, 52, 
 104, 21, 203, 121, 
 135, 236, 95, 26, 
 175, 220, 78, 209, 
 124, 252, 81, 23, 
 71, 95, 220, 249, 
 70, 88, 183, 99, 
 13, 113, 66, 32, 
 179, 9, 193, 218, 
 214, 119, 165, 65, 
 232, 118, 6, 53, 
 239, 53, 178, 94, 
 201, 190, 53, 235, 
 183, 102, 13, 6, 
 53, 239, 112, 143, 
 175, 119, 251, 53, 
 62, 190, 114, 47, 
 241, 181, 62, 225, 
 86, 69, 70, 95, 
 21, 89, 161, 250, 
 122, 133, 234, 239, 
 133, 26, 99, 9, 
 235, 220, 239, 237, 
 112, 243, 241, 23, 
 142, 66, 154, 67, 
 38, 52, 144, 221, 
 126, 152, 42, 130, 
 149, 218, 109, 133, 
 125, 217, 168, 238, 
 147, 180, 29, 133, 
 183, 211, 63, 241, 
 224, 85, 109, 16, 
 86, 113, 71, 213, 
 122, 15, 173, 88, 
 146, 225, 99, 201, 
 153, 56, 31, 87, 
 73, 189, 241, 151, 
 51, 177, 39, 206, 
 34, 53, 4, 43, 
 120, 13, 208, 177, 
 110, 240, 30, 96, 
 226, 28, 62, 62, 
 52, 243, 64, 118, 
 107, 110, 12, 124, 
 224, 6, 253, 129, 
 27, 113, 171, 219, 
 200, 82, 251, 35, 
 199, 223, 158, 220, 
 175, 255, 88, 191, 
 126, 100, 181, 133, 
 63, 247, 166, 113, 
 119, 19, 123, 175, 
 26, 232, 199, 46, 
 84, 167, 5, 247, 
 243, 202, 255, 111, 
 106, 247, 120, 185, 
 29, 229, 62, 97, 
 198, 152, 90, 212, 
 196, 162, 196, 204, 
 99, 250, 187, 9, 
 236, 107, 200, 216, 
 165, 200, 16, 102, 
 140, 115, 192, 144, 
 164, 134, 140, 63, 
 74, 223, 46, 91, 
 110, 99, 175, 19, 
 91, 238, 181, 164, 
 17, 134, 185, 103, 
 16, 102, 215, 217, 
 93, 110, 244, 110, 
 98, 209, 39, 137, 
 69, 159, 220, 102, 
 209, 199, 156, 91, 
 2, 169, 193, 219, 
 37, 5, 111, 244, 
 177, 12, 6, 229, 
 13, 98, 102, 113, 
 108, 80, 75, 49, 
 224, 111, 169, 88, 
 229, 50, 98, 82, 
 141, 250, 49, 171, 
 30, 178, 220, 42, 
 95, 143, 229, 194, 
 60, 100, 255, 155, 
 85, 67, 216, 135, 
 169, 220, 200, 164, 
 114, 147, 52, 10, 
 243, 216, 160, 92, 
 13, 147, 97, 158, 
 18, 98, 214, 150, 
 138, 185, 173, 10, 
 101, 223, 151, 248, 
 219, 167, 194, 20, 
 153, 150, 253, 253, 
 104, 151, 11, 125, 
 48, 57, 175, 90, 
 179, 66, 22, 51, 
 84, 114, 159, 85, 
 209, 189, 187, 92, 
 247, 166, 84, 216, 
 231, 49, 111, 19, 
 215, 144, 61, 165, 
 6, 199, 236, 135, 
 12, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len26_anagram0 = {
  LengthAndAnagram(26, 0), // seq_bit_len_and_anagram
  154, // num_chords
  kmap5_Word_len26_anagram0_chords, // chords
  kmap5_Word_len26_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len26_anagram1_chords[23] = {
 ChordData({0, 13, 10}), ChordData({0, 64, 16}), ChordData({0, 72, 80}), ChordData({2, 68, 3}), 
 ChordData({16, 4, 153}), ChordData({16, 65, 8}), ChordData({16, 68, 18}), ChordData({16, 76, 8}), 
 ChordData({18, 0, 74}), ChordData({18, 0, 202}), ChordData({20, 0, 131}), ChordData({22, 0, 146}), 
 ChordData({32, 12, 17}), ChordData({34, 12, 136}), ChordData({34, 64, 129}), ChordData({48, 8, 65}), 
 ChordData({50, 1, 24}), ChordData({50, 8, 17}), ChordData({52, 0, 80}), ChordData({128, 4, 26}), 
 ChordData({132, 0, 146}), ChordData({144, 8, 16}), ChordData({148, 9, 16}), 
};

uint8_t const kmap5_Word_len26_anagram1_seqs[75] = {
 69, 125, 44, 242, 
 97, 193, 192, 71, 
 1, 195, 135, 48, 
 120, 62, 175, 62, 
 5, 119, 214, 176, 
 6, 126, 67, 112, 
 124, 13, 130, 99, 
 69, 203, 144, 21, 
 109, 80, 51, 158, 
 65, 109, 214, 207, 
 253, 253, 62, 213, 
 168, 83, 168, 14, 
 29, 47, 103, 206, 
 221, 40, 244, 114, 
 179, 87, 221, 234, 
 74, 53, 190, 150, 
 169, 109, 19, 84, 
 242, 49, 115, 221, 
 109, 22, 52, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len26_anagram1 = {
  LengthAndAnagram(26, 1), // seq_bit_len_and_anagram
  23, // num_chords
  kmap5_Word_len26_anagram1_chords, // chords
  kmap5_Word_len26_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len26_anagram2_chords[16] = {
 ChordData({2, 4, 73}), ChordData({4, 12, 128}), ChordData({16, 32, 18}), ChordData({16, 37, 17}), 
 ChordData({16, 96, 19}), ChordData({48, 1, 24}), ChordData({48, 8, 80}), ChordData({48, 13, 64}), 
 ChordData({50, 8, 8}), ChordData({52, 0, 17}), ChordData({52, 0, 129}), ChordData({52, 8, 16}), 
 ChordData({128, 0, 154}), ChordData({128, 4, 26}), ChordData({144, 0, 81}), ChordData({176, 9, 16}), 
};

uint8_t const kmap5_Word_len26_anagram2_seqs[52] = {
 188, 252, 232, 53, 
 250, 130, 143, 204, 
 187, 101, 247, 199, 
 188, 192, 250, 144, 
 193, 173, 10, 205, 
 121, 165, 138, 60, 
 247, 208, 19, 99, 
 85, 247, 245, 206, 
 219, 87, 34, 95, 
 116, 236, 189, 152, 
 148, 90, 226, 126, 
 153, 186, 150, 203, 
 53, 220, 76, 206, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len26_anagram2 = {
  LengthAndAnagram(26, 2), // seq_bit_len_and_anagram
  16, // num_chords
  kmap5_Word_len26_anagram2_chords, // chords
  kmap5_Word_len26_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len26_anagram3_chords[2] = {
 ChordData({36, 0, 18}), ChordData({48, 5, 136}), 
};

uint8_t const kmap5_Word_len26_anagram3_seqs[7] = {
 173, 182, 86, 118, 
 244, 10, 13, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len26_anagram3 = {
  LengthAndAnagram(26, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len26_anagram3_chords, // chords
  kmap5_Word_len26_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len26_anagram4_chords[1] = {
 ChordData({48, 8, 80}), 
};

uint8_t const kmap5_Word_len26_anagram4_seqs[4] = {
 82, 99, 244, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len26_anagram4 = {
  LengthAndAnagram(26, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len26_anagram4_chords, // chords
  kmap5_Word_len26_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len27_anagram0_chords[153] = {
 ChordData({0, 12, 19}), ChordData({0, 13, 3}), ChordData({2, 12, 192}), ChordData({2, 32, 82}), 
 ChordData({2, 33, 72}), ChordData({2, 33, 138}), ChordData({2, 69, 16}), ChordData({2, 96, 67}), 
 ChordData({4, 12, 18}), ChordData({4, 44, 16}), ChordData({4, 72, 0}), ChordData({4, 96, 0}), 
 ChordData({6, 1, 25}), ChordData({6, 4, 72}), ChordData({6, 4, 80}), ChordData({6, 4, 144}), 
 ChordData({16, 4, 9}), ChordData({16, 5, 3}), ChordData({16, 5, 83}), ChordData({16, 13, 17}), 
 ChordData({16, 32, 209}), ChordData({16, 36, 145}), ChordData({16, 64, 27}), ChordData({18, 0, 155}), 
 ChordData({18, 4, 11}), ChordData({18, 4, 27}), ChordData({18, 4, 131}), ChordData({18, 4, 145}), 
 ChordData({18, 4, 147}), ChordData({18, 32, 25}), ChordData({18, 41, 80}), ChordData({18, 68, 64}), 
 ChordData({20, 0, 27}), ChordData({20, 0, 83}), ChordData({20, 0, 89}), ChordData({20, 4, 138}), 
 ChordData({20, 4, 146}), ChordData({20, 8, 131}), ChordData({20, 32, 65}), ChordData({20, 64, 18}), 
 ChordData({22, 0, 19}), ChordData({22, 0, 66}), ChordData({22, 0, 82}), ChordData({32, 0, 211}), 
 ChordData({32, 4, 72}), ChordData({32, 4, 81}), ChordData({32, 4, 144}), ChordData({32, 5, 154}), 
 ChordData({32, 12, 129}), ChordData({32, 37, 1}), ChordData({32, 37, 3}), ChordData({32, 68, 192}), 
 ChordData({34, 8, 3}), ChordData({34, 8, 192}), ChordData({34, 9, 24}), ChordData({34, 12, 192}), 
 ChordData({34, 65, 24}), ChordData({36, 12, 66}), ChordData({36, 12, 129}), ChordData({36, 36, 26}), 
 ChordData({36, 64, 18}), ChordData({38, 32, 72}), ChordData({38, 64, 65}), ChordData({38, 72, 128}), 
 ChordData({48, 0, 147}), ChordData({48, 1, 17}), ChordData({48, 1, 80}), ChordData({48, 5, 137}), 
 ChordData({48, 5, 152}), ChordData({48, 8, 64}), ChordData({48, 8, 147}), ChordData({48, 12, 146}), 
 ChordData({48, 64, 146}), ChordData({50, 0, 208}), ChordData({50, 1, 11}), ChordData({50, 1, 16}), 
 ChordData({50, 1, 25}), ChordData({50, 1, 26}), ChordData({50, 8, 18}), ChordData({50, 33, 128}), 
 ChordData({50, 65, 16}), ChordData({50, 65, 130}), ChordData({50, 72, 0}), ChordData({50, 97, 3}), 
 ChordData({52, 8, 24}), ChordData({52, 13, 128}), ChordData({52, 64, 24}), ChordData({54, 65, 16}), 
 ChordData({54, 96, 8}), ChordData({128, 9, 18}), ChordData({128, 12, 24}), ChordData({128, 13, 17}), 
 ChordData({128, 13, 144}), ChordData({128, 32, 152}), ChordData({128, 32, 208}), ChordData({128, 72, 18}), 
 ChordData({128, 73, 26}), ChordData({128, 96, 130}), ChordData({128, 96, 137}), ChordData({130, 9, 24}), 
 ChordData({130, 12, 16}), ChordData({132, 8, 17}), ChordData({134, 0, 146}), ChordData({134, 1, 17}), 
 ChordData({134, 64, 130}), ChordData({144, 0, 11}), ChordData({144, 0, 19}), ChordData({144, 0, 26}), 
 ChordData({144, 0, 27}), ChordData({144, 0, 75}), ChordData({144, 0, 131}), ChordData({144, 0, 202}), 
 ChordData({144, 1, 17}), ChordData({144, 1, 65}), ChordData({144, 8, 18}), ChordData({144, 64, 88}), 
 ChordData({144, 64, 146}), ChordData({144, 65, 130}), ChordData({144, 65, 146}), ChordData({144, 72, 18}), 
 ChordData({144, 96, 16}), ChordData({146, 0, 72}), ChordData({146, 0, 73}), ChordData({146, 0, 74}), 
 ChordData({146, 0, 75}), ChordData({146, 0, 88}), ChordData({146, 1, 2}), ChordData({148, 4, 17}), 
 ChordData({148, 8, 146}), ChordData({148, 9, 3}), ChordData({148, 64, 146}), ChordData({150, 0, 24}), 
 ChordData({160, 1, 17}), ChordData({160, 4, 19}), ChordData({160, 33, 65}), ChordData({160, 65, 24}), 
 ChordData({160, 72, 128}), ChordData({160, 96, 192}), ChordData({162, 1, 10}), ChordData({162, 1, 72}), 
 ChordData({162, 72, 64}), ChordData({164, 0, 1}), ChordData({164, 0, 9}), ChordData({164, 5, 128}), 
 ChordData({164, 8, 1}), ChordData({164, 12, 3}), ChordData({164, 13, 0}), ChordData({164, 32, 18}), 
 ChordData({164, 36, 16}), ChordData({176, 1, 130}), ChordData({176, 8, 26}), ChordData({180, 64, 82}), 
 ChordData({180, 64, 128}), 
};

uint8_t const kmap5_Word_len27_anagram0_seqs[517] = {
 241, 247, 202, 253, 
 187, 199, 34, 63, 
 66, 31, 121, 100, 
 59, 210, 141, 142, 
 176, 142, 70, 145, 
 125, 183, 63, 65, 
 128, 57, 100, 184, 
 95, 176, 108, 236, 
 55, 62, 223, 248, 
 24, 248, 198, 248, 
 208, 118, 244, 58, 
 94, 218, 143, 242, 
 237, 119, 132, 255, 
 182, 67, 175, 103, 
 213, 255, 174, 51, 
 158, 124, 231, 43, 
 227, 111, 209, 39, 
 204, 116, 94, 242, 
 31, 243, 30, 96, 
 189, 114, 20, 220, 
 120, 175, 56, 214, 
 67, 239, 253, 232, 
 61, 222, 144, 105, 
 206, 251, 244, 123, 
 131, 100, 245, 28, 
 243, 10, 219, 113, 
 49, 140, 248, 197, 
 205, 139, 214, 91, 
 75, 51, 94, 91, 
 139, 245, 12, 106, 
 244, 186, 110, 244, 
 104, 131, 28, 219, 
 241, 114, 110, 172, 
 173, 209, 193, 107, 
 244, 180, 147, 102, 
 28, 75, 91, 227, 
 136, 229, 74, 170, 
 194, 75, 149, 87, 
 94, 254, 234, 242, 
 244, 117, 31, 234, 
 47, 149, 177, 94, 
 125, 186, 175, 144, 
 29, 126, 133, 236, 
 164, 80, 253, 192, 
 13, 222, 196, 88, 
 133, 38, 114, 179, 
 112, 148, 27, 169, 
 79, 161, 238, 40, 
 196, 143, 173, 74, 
 252, 163, 239, 251, 
 125, 69, 214, 215, 
 16, 202, 86, 117, 
 132, 201, 213, 54, 
 161, 80, 157, 130, 
 100, 188, 186, 238, 
 234, 213, 245, 26, 
 174, 69, 76, 134, 
 175, 7, 173, 222, 
 167, 88, 197, 53, 
 114, 222, 51, 136, 
 123, 34, 151, 133, 
 170, 183, 36, 143, 
 212, 53, 180, 250, 
 6, 187, 129, 117, 
 61, 122, 134, 94, 
 104, 245, 14, 174, 
 209, 195, 153, 39, 
 15, 100, 221, 78, 
 128, 6, 6, 66, 
 114, 116, 152, 26, 
 1, 15, 100, 167, 
 53, 246, 94, 248, 
 177, 39, 247, 117, 
 131, 181, 223, 9, 
 208, 189, 217, 104, 
 224, 203, 220, 34, 
 191, 25, 95, 187, 
 220, 248, 215, 229, 
 198, 39, 30, 60, 
 153, 242, 224, 41, 
 44, 230, 110, 2, 
 64, 106, 177, 100, 
 73, 148, 64, 72, 
 45, 240, 70, 187, 
 220, 200, 199, 223, 
 201, 182, 25, 219, 
 181, 164, 193, 178, 
 109, 118, 115, 109, 
 136, 18, 192, 84, 
 53, 30, 230, 174, 
 241, 48, 21, 189, 
 138, 169, 232, 61, 
 76, 21, 235, 97, 
 18, 25, 15, 83, 
 37, 201, 238, 186, 
 220, 203, 174, 19, 
 95, 116, 204, 45, 
 173, 33, 87, 92, 
 154, 40, 129, 206, 
 68, 9, 116, 148, 
 128, 23, 51, 58, 
 148, 252, 178, 12, 
 22, 139, 76, 234, 
 89, 101, 82, 49, 
 21, 71, 44, 198, 
 155, 84, 177, 74, 
 238, 100, 215, 13, 
 58, 155, 247, 207, 
 142, 141, 178, 108, 
 137, 69, 95, 112, 
 163, 44, 219, 164, 
 218, 219, 229, 194, 
 188, 242, 179, 238, 
 73, 86, 200, 14, 
 110, 86, 13, 49, 
 67, 165, 20, 150, 
 149, 2, 166, 118, 
 3, 187, 42, 147, 
 42, 25, 166, 198, 
 172, 215, 234, 245, 
 245, 46, 21, 82, 
 246, 79, 125, 222, 
 101, 196, 140, 253, 
 95, 241, 251, 236, 
 89, 246, 125, 201, 
 126, 251, 92, 76, 
 34, 67, 99, 42, 
 231, 178, 223, 4, 
 196, 33, 107, 79, 
 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len27_anagram0 = {
  LengthAndAnagram(27, 0), // seq_bit_len_and_anagram
  153, // num_chords
  kmap5_Word_len27_anagram0_chords, // chords
  kmap5_Word_len27_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len27_anagram1_chords[25] = {
 ChordData({0, 13, 146}), ChordData({0, 36, 80}), ChordData({2, 36, 10}), ChordData({16, 4, 90}), 
 ChordData({16, 4, 155}), ChordData({16, 13, 16}), ChordData({16, 36, 10}), ChordData({16, 36, 17}), 
 ChordData({16, 36, 129}), ChordData({18, 64, 138}), ChordData({32, 32, 18}), ChordData({34, 8, 65}), 
 ChordData({36, 4, 145}), ChordData({48, 64, 130}), ChordData({50, 72, 0}), ChordData({52, 64, 136}), 
 ChordData({128, 12, 18}), ChordData({128, 68, 19}), ChordData({144, 0, 11}), ChordData({144, 0, 75}), 
 ChordData({144, 64, 26}), ChordData({148, 0, 147}), ChordData({160, 0, 27}), ChordData({164, 0, 81}), 
 ChordData({176, 8, 128}), 
};

uint8_t const kmap5_Word_len27_anagram1_seqs[85] = {
 29, 125, 177, 228, 
 229, 247, 25, 143, 
 108, 244, 5, 95, 
 213, 139, 214, 219, 
 167, 248, 91, 244, 
 90, 217, 43, 250, 
 152, 255, 188, 127, 
 140, 124, 14, 70, 
 26, 53, 178, 186, 
 200, 164, 198, 56, 
 215, 111, 189, 167, 
 96, 170, 32, 135, 
 225, 38, 184, 175, 
 26, 200, 124, 252, 
 197, 188, 4, 126, 
 3, 166, 158, 245, 
 48, 245, 44, 103, 
 197, 12, 94, 131, 
 90, 238, 97, 86, 
 189, 114, 179, 175, 
 114, 92, 82, 141, 
 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len27_anagram1 = {
  LengthAndAnagram(27, 1), // seq_bit_len_and_anagram
  25, // num_chords
  kmap5_Word_len27_anagram1_chords, // chords
  kmap5_Word_len27_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len27_anagram2_chords[7] = {
 ChordData({16, 0, 147}), ChordData({16, 13, 16}), ChordData({16, 68, 146}), ChordData({48, 5, 152}), 
 ChordData({52, 4, 16}), ChordData({148, 64, 18}), ChordData({164, 68, 16}), 
};

uint8_t const kmap5_Word_len27_anagram2_seqs[24] = {
 252, 149, 228, 93, 
 199, 223, 98, 48, 
 210, 175, 173, 244, 
 11, 221, 215, 245, 
 215, 150, 64, 240, 
 126, 191, 249, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len27_anagram2 = {
  LengthAndAnagram(27, 2), // seq_bit_len_and_anagram
  7, // num_chords
  kmap5_Word_len27_anagram2_chords, // chords
  kmap5_Word_len27_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len27_anagram3_chords[2] = {
 ChordData({16, 68, 146}), ChordData({52, 0, 80}), 
};

uint8_t const kmap5_Word_len27_anagram3_seqs[7] = {
 244, 64, 233, 149, 
 218, 188, 61, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len27_anagram3 = {
  LengthAndAnagram(27, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len27_anagram3_chords, // chords
  kmap5_Word_len27_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len27_anagram7_chords[1] = {
 ChordData({48, 8, 80}), 
};

uint8_t const kmap5_Word_len27_anagram7_seqs[4] = {
 107, 206, 43, 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len27_anagram7 = {
  LengthAndAnagram(27, 7), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len27_anagram7_chords, // chords
  kmap5_Word_len27_anagram7_seqs, // sequences
};

ChordData const kmap5_Word_len28_anagram0_chords[134] = {
 ChordData({0, 45, 73}), ChordData({0, 68, 210}), ChordData({0, 72, 210}), ChordData({2, 4, 73}), 
 ChordData({2, 4, 89}), ChordData({2, 4, 137}), ChordData({2, 4, 201}), ChordData({2, 5, 17}), 
 ChordData({2, 12, 147}), ChordData({2, 32, 128}), ChordData({2, 40, 65}), ChordData({6, 13, 8}), 
 ChordData({6, 32, 82}), ChordData({16, 0, 208}), ChordData({16, 1, 147}), ChordData({16, 13, 144}), 
 ChordData({16, 32, 26}), ChordData({16, 32, 83}), ChordData({16, 36, 138}), ChordData({16, 36, 193}), 
 ChordData({16, 64, 74}), ChordData({16, 64, 211}), ChordData({16, 65, 72}), ChordData({16, 68, 66}), 
 ChordData({16, 68, 83}), ChordData({16, 73, 16}), ChordData({18, 12, 9}), ChordData({18, 12, 88}), 
 ChordData({18, 12, 131}), ChordData({18, 12, 146}), ChordData({18, 12, 152}), ChordData({18, 13, 1}), 
 ChordData({18, 64, 73}), ChordData({18, 64, 74}), ChordData({18, 68, 17}), ChordData({18, 68, 73}), 
 ChordData({20, 4, 25}), ChordData({20, 4, 152}), ChordData({20, 9, 16}), ChordData({20, 68, 138}), 
 ChordData({22, 0, 81}), ChordData({22, 4, 9}), ChordData({22, 4, 194}), ChordData({22, 64, 65}), 
 ChordData({32, 9, 26}), ChordData({32, 9, 83}), ChordData({32, 32, 81}), ChordData({36, 76, 128}), 
 ChordData({38, 0, 130}), ChordData({38, 4, 17}), ChordData({38, 4, 26}), ChordData({38, 5, 18}), 
 ChordData({38, 8, 65}), ChordData({38, 33, 17}), ChordData({48, 0, 27}), ChordData({48, 0, 66}), 
 ChordData({48, 0, 211}), ChordData({48, 4, 65}), ChordData({48, 4, 153}), ChordData({48, 4, 154}), 
 ChordData({48, 5, 89}), ChordData({48, 8, 82}), ChordData({48, 9, 24}), ChordData({48, 9, 73}), 
 ChordData({48, 12, 25}), ChordData({48, 12, 80}), ChordData({48, 12, 138}), ChordData({48, 12, 208}), 
 ChordData({48, 13, 64}), ChordData({48, 64, 66}), ChordData({48, 68, 3}), ChordData({48, 69, 128}), 
 ChordData({48, 72, 80}), ChordData({50, 0, 19}), ChordData({50, 0, 74}), ChordData({50, 0, 152}), 
 ChordData({50, 1, 73}), ChordData({50, 4, 65}), ChordData({50, 5, 128}), ChordData({50, 8, 82}), 
 ChordData({50, 9, 9}), ChordData({50, 9, 72}), ChordData({52, 4, 74}), ChordData({52, 13, 65}), 
 ChordData({52, 37, 128}), ChordData({52, 64, 19}), ChordData({52, 65, 1}), ChordData({52, 76, 16}), 
 ChordData({128, 0, 155}), ChordData({128, 4, 11}), ChordData({128, 65, 130}), ChordData({128, 96, 139}), 
 ChordData({128, 100, 66}), ChordData({130, 0, 75}), ChordData({130, 0, 202}), ChordData({130, 1, 27}), 
 ChordData({130, 4, 11}), ChordData({130, 4, 73}), ChordData({130, 64, 130}), ChordData({130, 72, 66}), 
 ChordData({132, 32, 27}), ChordData({134, 32, 82}), ChordData({144, 8, 89}), ChordData({144, 12, 26}), 
 ChordData({144, 36, 25}), ChordData({144, 40, 17}), ChordData({144, 68, 66}), ChordData({146, 8, 9}), 
 ChordData({146, 64, 208}), ChordData({148, 0, 11}), ChordData({148, 0, 81}), ChordData({148, 0, 82}), 
 ChordData({148, 8, 3}), ChordData({148, 8, 17}), ChordData({150, 0, 25}), ChordData({150, 0, 72}), 
 ChordData({150, 0, 200}), ChordData({150, 0, 208}), ChordData({150, 64, 64}), ChordData({160, 13, 64}), 
 ChordData({160, 13, 144}), ChordData({160, 33, 1}), ChordData({164, 1, 192}), ChordData({164, 4, 80}), 
 ChordData({166, 0, 24}), ChordData({166, 64, 2}), ChordData({176, 0, 202}), ChordData({176, 5, 81}), 
 ChordData({178, 0, 25}), ChordData({178, 0, 80}), ChordData({178, 0, 137}), ChordData({180, 1, 128}), 
 ChordData({180, 9, 24}), ChordData({180, 64, 26}), 
};

uint8_t const kmap5_Word_len28_anagram0_seqs[469] = {
 199, 94, 139, 242, 
 4, 124, 41, 177, 
 148, 66, 52, 42, 
 247, 122, 183, 175, 
 50, 55, 58, 55, 
 79, 163, 114, 79, 
 116, 191, 211, 117, 
 241, 111, 7, 196, 
 79, 129, 68, 188, 
 196, 57, 166, 223, 
 138, 163, 141, 149, 
 50, 200, 131, 91, 
 196, 235, 142, 140, 
 199, 131, 127, 209, 
 60, 179, 110, 41, 
 183, 62, 100, 200, 
 94, 213, 36, 231, 
 167, 99, 193, 130, 
 214, 0, 172, 229, 
 200, 193, 157, 85, 
 44, 143, 248, 193, 
 2, 248, 207, 203, 
 7, 175, 139, 175, 
 19, 255, 44, 142, 
 163, 191, 72, 19, 
 255, 28, 103, 31, 
 201, 113, 212, 251, 
 196, 23, 255, 198, 
 193, 122, 35, 55, 
 26, 6, 45, 251, 
 97, 254, 60, 42, 
 231, 15, 237, 239, 
 188, 218, 232, 85, 
 189, 221, 218, 5, 
 109, 80, 123, 13, 
 205, 43, 35, 215, 
 254, 198, 122, 210, 
 140, 243, 20, 44, 
 109, 206, 93, 213, 
 98, 41, 183, 21, 
 139, 252, 177, 186, 
 66, 31, 251, 240, 
 173, 246, 52, 184, 
 223, 247, 115, 253, 
 232, 111, 217, 125, 
 191, 131, 82, 251, 
 56, 215, 239, 64, 
 118, 88, 119, 173, 
 39, 21, 209, 34, 
 72, 85, 206, 43, 
 247, 87, 207, 234, 
 122, 251, 164, 21, 
 201, 191, 114, 251, 
 10, 45, 117, 57, 
 151, 107, 206, 10, 
 45, 134, 209, 122, 
 156, 207, 251, 26, 
 253, 82, 215, 220, 
 147, 21, 45, 230, 
 188, 79, 209, 34, 
 15, 45, 21, 209, 
 14, 14, 21, 255, 
 252, 68, 134, 14, 
 193, 226, 229, 188, 
 198, 173, 115, 88, 
 71, 70, 61, 10, 
 94, 215, 226, 187, 
 81, 40, 115, 245, 
 207, 67, 100, 248, 
 36, 94, 110, 208, 
 209, 190, 81, 88, 
 212, 225, 44, 223, 
 139, 21, 221, 191, 
 20, 125, 189, 217, 
 83, 23, 220, 234, 
 149, 125, 13, 208, 
 247, 129, 243, 246, 
 152, 122, 155, 132, 
 169, 247, 120, 93, 
 18, 37, 0, 164, 
 22, 120, 194, 62, 
 36, 128, 169, 50, 
 114, 50, 52, 152, 
 170, 121, 211, 149, 
 152, 122, 63, 42, 
 247, 55, 169, 192, 
 16, 37, 0, 140, 
 132, 140, 173, 60, 
 150, 218, 88, 41, 
 147, 49, 85, 206, 
 187, 25, 95, 209, 
 175, 121, 204, 123, 
 204, 185, 142, 248, 
 130, 25, 28, 173, 
 55, 169, 146, 20, 
 198, 139, 169, 232, 
 118, 109, 243, 44, 
 215, 54, 209, 34, 
 152, 177, 249, 92, 
 48, 207, 155, 45, 
 71, 207, 219, 172, 
 50, 169, 110, 50, 
 148, 42, 45, 135, 
 188, 110, 35, 25, 
 220, 125, 204, 42, 
 29, 61, 151, 123, 
 44, 43, 100, 144, 
 178, 175, 242, 189, 
 228, 246, 59, 125, 
 159, 138, 181, 207, 
 9, 152, 85, 197, 
 36, 151, 251, 208, 
 155, 245, 70, 45, 
 222, 201, 42, 89, 
 143, 70, 13, 179, 
 239, 201, 253, 102, 
 209, 218, 187, 76, 
 13, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  134, // num_chords
  kmap5_Word_len28_anagram0_chords, // chords
  kmap5_Word_len28_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len28_anagram1_chords[28] = {
 ChordData({2, 4, 194}), ChordData({2, 5, 16}), ChordData({2, 64, 66}), ChordData({16, 4, 195}), 
 ChordData({16, 68, 66}), ChordData({18, 8, 192}), ChordData({18, 12, 18}), ChordData({18, 32, 25}), 
 ChordData({18, 65, 8}), ChordData({18, 68, 3}), ChordData({22, 4, 16}), ChordData({34, 33, 129}), 
 ChordData({48, 5, 24}), ChordData({48, 9, 16}), ChordData({48, 12, 129}), ChordData({50, 0, 65}), 
 ChordData({52, 8, 128}), ChordData({128, 4, 19}), ChordData({130, 4, 17}), ChordData({144, 1, 26}), 
 ChordData({146, 8, 9}), ChordData({148, 0, 19}), ChordData({148, 0, 64}), ChordData({148, 64, 18}), 
 ChordData({150, 0, 25}), ChordData({164, 0, 18}), ChordData({164, 64, 18}), ChordData({176, 8, 18}), 
};

uint8_t const kmap5_Word_len28_anagram1_seqs[98] = {
 72, 47, 50, 248, 
 93, 247, 179, 188, 
 0, 35, 194, 159, 
 65, 47, 248, 130, 
 31, 28, 71, 100, 
 200, 232, 253, 56, 
 56, 202, 188, 115, 
 211, 105, 112, 23, 
 6, 239, 207, 109, 
 127, 118, 220, 209, 
 64, 118, 191, 251, 
 10, 205, 195, 181, 
 139, 142, 149, 254, 
 44, 55, 87, 207, 
 177, 198, 158, 124, 
 251, 120, 185, 183, 
 63, 151, 107, 237, 
 114, 209, 142, 121, 
 147, 218, 54, 207, 
 120, 45, 69, 44, 
 210, 54, 209, 14, 
 109, 243, 60, 154, 
 136, 181, 149, 125, 
 238, 38, 176, 198, 
 228, 188, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len28_anagram1 = {
  LengthAndAnagram(28, 1), // seq_bit_len_and_anagram
  28, // num_chords
  kmap5_Word_len28_anagram1_chords, // chords
  kmap5_Word_len28_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len28_anagram2_chords[11] = {
 ChordData({0, 4, 26}), ChordData({2, 4, 147}), ChordData({20, 0, 19}), ChordData({20, 4, 16}), 
 ChordData({20, 4, 25}), ChordData({22, 8, 16}), ChordData({48, 1, 80}), ChordData({50, 1, 8}), 
 ChordData({52, 0, 16}), ChordData({52, 4, 19}), ChordData({176, 0, 17}), 
};

uint8_t const kmap5_Word_len28_anagram2_seqs[39] = {
 188, 190, 98, 201, 
 207, 61, 149, 205, 
 139, 110, 215, 214, 
 237, 215, 237, 247, 
 212, 219, 214, 113, 
 188, 82, 187, 206, 
 11, 173, 117, 212, 
 91, 251, 222, 219, 
 251, 235, 149, 151, 
 123, 117, 13, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len28_anagram2 = {
  LengthAndAnagram(28, 2), // seq_bit_len_and_anagram
  11, // num_chords
  kmap5_Word_len28_anagram2_chords, // chords
  kmap5_Word_len28_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len28_anagram3_chords[5] = {
 ChordData({0, 4, 19}), ChordData({48, 0, 147}), ChordData({48, 8, 24}), ChordData({48, 13, 64}), 
 ChordData({128, 4, 27}), 
};

uint8_t const kmap5_Word_len28_anagram3_seqs[18] = {
 127, 183, 143, 135, 
 84, 239, 188, 107, 
 206, 90, 205, 115, 
 134, 47, 248, 123, 
 153, 10, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len28_anagram3 = {
  LengthAndAnagram(28, 3), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len28_anagram3_chords, // chords
  kmap5_Word_len28_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len28_anagram4_chords[1] = {
 ChordData({16, 36, 17}), 
};

uint8_t const kmap5_Word_len28_anagram4_seqs[4] = {
 204, 127, 204, 11, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len28_anagram4 = {
  LengthAndAnagram(28, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len28_anagram4_chords, // chords
  kmap5_Word_len28_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len29_anagram0_chords[149] = {
 ChordData({0, 4, 219}), ChordData({0, 36, 83}), ChordData({0, 40, 19}), ChordData({0, 68, 154}), 
 ChordData({0, 72, 146}), ChordData({2, 12, 25}), ChordData({2, 12, 145}), ChordData({2, 12, 208}), 
 ChordData({2, 13, 146}), ChordData({2, 36, 17}), ChordData({2, 36, 66}), ChordData({2, 68, 18}), 
 ChordData({6, 4, 11}), ChordData({6, 4, 131}), ChordData({6, 4, 145}), ChordData({6, 4, 193}), 
 ChordData({6, 4, 195}), ChordData({16, 0, 75}), ChordData({16, 8, 147}), ChordData({16, 36, 153}), 
 ChordData({16, 37, 17}), ChordData({16, 44, 81}), ChordData({16, 44, 145}), ChordData({16, 68, 80}), 
 ChordData({16, 69, 144}), ChordData({16, 100, 19}), ChordData({18, 5, 10}), ChordData({18, 44, 10}), 
 ChordData({18, 73, 2}), ChordData({18, 73, 26}), ChordData({18, 76, 130}), ChordData({20, 0, 202}), 
 ChordData({20, 1, 19}), ChordData({20, 12, 1}), ChordData({20, 68, 9}), ChordData({22, 1, 146}), 
 ChordData({22, 64, 19}), ChordData({32, 0, 146}), ChordData({32, 4, 153}), ChordData({32, 4, 193}), 
 ChordData({32, 12, 2}), ChordData({32, 33, 26}), ChordData({32, 96, 3}), ChordData({34, 0, 19}), 
 ChordData({34, 0, 200}), ChordData({34, 4, 73}), ChordData({34, 4, 146}), ChordData({34, 5, 73}), 
 ChordData({34, 41, 9}), ChordData({34, 73, 130}), ChordData({34, 96, 8}), ChordData({36, 0, 210}), 
 ChordData({36, 8, 2}), ChordData({48, 0, 131}), ChordData({48, 1, 0}), ChordData({48, 1, 152}), 
 ChordData({48, 8, 25}), ChordData({48, 9, 19}), ChordData({48, 12, 17}), ChordData({48, 13, 16}), 
 ChordData({48, 32, 193}), ChordData({48, 64, 73}), ChordData({48, 68, 208}), ChordData({48, 73, 128}), 
 ChordData({50, 1, 17}), ChordData({50, 9, 18}), ChordData({50, 12, 10}), ChordData({50, 13, 8}), 
 ChordData({50, 13, 17}), ChordData({50, 33, 200}), ChordData({50, 40, 128}), ChordData({50, 40, 130}), 
 ChordData({50, 44, 2}), ChordData({50, 64, 66}), ChordData({50, 64, 138}), ChordData({50, 72, 80}), 
 ChordData({50, 72, 144}), ChordData({52, 0, 67}), ChordData({52, 0, 154}), ChordData({52, 4, 66}), 
 ChordData({52, 4, 138}), ChordData({52, 8, 25}), ChordData({52, 36, 9}), ChordData({52, 64, 11}), 
 ChordData({54, 0, 19}), ChordData({54, 4, 11}), ChordData({54, 4, 16}), ChordData({54, 8, 128}), 
 ChordData({128, 32, 146}), ChordData({128, 36, 130}), ChordData({128, 36, 210}), ChordData({128, 69, 16}), 
 ChordData({128, 76, 138}), ChordData({130, 8, 25}), ChordData({130, 8, 72}), ChordData({130, 8, 136}), 
 ChordData({130, 32, 26}), ChordData({130, 64, 10}), ChordData({132, 0, 88}), ChordData({132, 4, 146}), 
 ChordData({134, 0, 8}), ChordData({134, 0, 25}), ChordData({134, 0, 131}), ChordData({134, 4, 72}), 
 ChordData({134, 4, 131}), ChordData({144, 0, 216}), ChordData({144, 8, 11}), ChordData({144, 9, 26}), 
 ChordData({144, 40, 24}), ChordData({144, 64, 145}), ChordData({144, 72, 130}), ChordData({144, 76, 66}), 
 ChordData({146, 0, 83}), ChordData({146, 0, 138}), ChordData({148, 0, 80}), ChordData({148, 8, 66}), 
 ChordData({148, 12, 18}), ChordData({148, 64, 88}), ChordData({150, 8, 80}), ChordData({150, 8, 130}), 
 ChordData({150, 64, 65}), ChordData({160, 0, 203}), ChordData({160, 4, 11}), ChordData({160, 4, 208}), 
 ChordData({160, 5, 131}), ChordData({160, 5, 152}), ChordData({162, 0, 9}), ChordData({162, 0, 138}), 
 ChordData({162, 0, 152}), ChordData({162, 4, 11}), ChordData({162, 5, 26}), ChordData({162, 5, 130}), 
 ChordData({164, 8, 210}), ChordData({164, 33, 1}), ChordData({166, 65, 16}), ChordData({176, 1, 154}), 
 ChordData({176, 1, 194}), ChordData({176, 5, 18}), ChordData({176, 8, 27}), ChordData({176, 8, 67}), 
 ChordData({176, 8, 74}), ChordData({176, 13, 9}), ChordData({178, 8, 24}), ChordData({178, 8, 88}), 
 ChordData({178, 8, 137}), ChordData({178, 64, 65}), ChordData({180, 0, 147}), ChordData({180, 0, 209}), 
 ChordData({180, 4, 136}), 
};

uint8_t const kmap5_Word_len29_anagram0_seqs[541] = {
 82, 234, 61, 72, 
 112, 255, 144, 45, 
 43, 143, 69, 62, 
 148, 244, 202, 71, 
 16, 24, 226, 239, 
 205, 107, 252, 189, 
 121, 146, 137, 67, 
 191, 221, 199, 161, 
 242, 247, 216, 206, 
 35, 123, 145, 17, 
 252, 13, 243, 136, 
 223, 238, 71, 241, 
 219, 220, 83, 251, 
 189, 121, 146, 246, 
 55, 79, 141, 94, 
 110, 80, 172, 103, 
 69, 27, 116, 235, 
 232, 95, 107, 129, 
 215, 249, 143, 121, 
 217, 71, 57, 239, 
 49, 111, 124, 250, 
 16, 214, 34, 157, 
 131, 247, 9, 240, 
 31, 243, 118, 163, 
 175, 232, 248, 200, 
 70, 13, 12, 22, 
 29, 138, 19, 212, 
 101, 116, 24, 124, 
 50, 168, 89, 197, 
 205, 219, 25, 239, 
 239, 28, 219, 53, 
 107, 120, 189, 182, 
 238, 6, 212, 214, 
 97, 240, 120, 240, 
 74, 165, 254, 213, 
 125, 122, 145, 175, 
 116, 220, 99, 173, 
 145, 85, 133, 91, 
 242, 161, 30, 50, 
 156, 197, 58, 55, 
 42, 149, 70, 165, 
 202, 253, 40, 110, 
 197, 121, 122, 248, 
 163, 114, 69, 29, 
 200, 174, 80, 29, 
 44, 242, 108, 52, 
 84, 169, 173, 81, 
 217, 27, 191, 138, 
 13, 50, 214, 51, 
 111, 222, 60, 4, 
 175, 10, 201, 156, 
 245, 234, 250, 234, 
 22, 93, 126, 252, 
 115, 221, 231, 188, 
 15, 45, 172, 222, 
 145, 229, 106, 176, 
 158, 20, 170, 191, 
 46, 82, 13, 208, 
 183, 3, 161, 151, 
 243, 78, 87, 114, 
 143, 56, 234, 137, 
 15, 71, 29, 7, 
 238, 159, 173, 144, 
 70, 24, 63, 5, 
 114, 230, 204, 6, 
 201, 143, 108, 204, 
 89, 234, 224, 4, 
 143, 34, 213, 224, 
 48, 156, 87, 28, 
 76, 195, 121, 165, 
 74, 51, 158, 150, 
 125, 79, 238, 141, 
 95, 197, 253, 211, 
 43, 186, 173, 57, 
 235, 245, 86, 255, 
 177, 222, 7, 216, 
 218, 6, 175, 174, 
 241, 251, 81, 95, 
 255, 187, 227, 237, 
 77, 99, 206, 60, 
 75, 162, 242, 9, 
 147, 37, 9, 178, 
 164, 223, 239, 186, 
 220, 0, 138, 169, 
 31, 98, 234, 92, 
 110, 28, 145, 73, 
 141, 67, 52, 169, 
 200, 54, 117, 16, 
 24, 13, 9, 72, 
 75, 149, 220, 111, 
 109, 19, 148, 109, 
 116, 82, 91, 238, 
 77, 106, 75, 154, 
 27, 108, 47, 50, 
 169, 248, 109, 46, 
 137, 7, 79, 181, 
 96, 198, 104, 189, 
 152, 90, 116, 201, 
 114, 99, 170, 47, 
 67, 32, 47, 96, 
 194, 140, 126, 192, 
 146, 209, 146, 56, 
 190, 146, 215, 193, 
 36, 183, 205, 150, 
 98, 204, 216, 82, 
 140, 25, 219, 175, 
 215, 210, 82, 67, 
 219, 140, 35, 198, 
 140, 109, 200, 193, 
 45, 101, 14, 83, 
 165, 210, 61, 98, 
 86, 189, 223, 172, 
 242, 132, 127, 79, 
 9, 193, 127, 97, 
 234, 213, 185, 73, 
 197, 172, 138, 67, 
 224, 85, 39, 23, 
 191, 222, 164, 230, 
 194, 215, 65, 74, 
 56, 248, 36, 101, 
 236, 147, 250, 172, 
 144, 93, 151, 219, 
 79, 72, 80, 9, 
 173, 144, 42, 166, 
 24, 179, 238, 67, 
 99, 42, 231, 61, 
 76, 185, 26, 141, 
 169, 82, 163, 99, 
 234, 61, 180, 149, 
 155, 77, 229, 188, 
 50, 169, 220, 36, 
 89, 47, 235, 201, 
 4, 103, 15, 110, 
 60, 202, 94, 206, 
 219, 103, 146, 95, 
 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len29_anagram0 = {
  LengthAndAnagram(29, 0), // seq_bit_len_and_anagram
  149, // num_chords
  kmap5_Word_len29_anagram0_chords, // chords
  kmap5_Word_len29_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len29_anagram1_chords[27] = {
 ChordData({2, 36, 19}), ChordData({2, 68, 146}), ChordData({18, 4, 136}), ChordData({18, 4, 208}), 
 ChordData({18, 64, 27}), ChordData({18, 76, 130}), ChordData({20, 4, 144}), ChordData({20, 36, 19}), 
 ChordData({32, 13, 0}), ChordData({36, 0, 9}), ChordData({36, 9, 0}), ChordData({48, 0, 147}), 
 ChordData({48, 5, 17}), ChordData({48, 5, 81}), ChordData({48, 5, 144}), ChordData({48, 12, 153}), 
 ChordData({48, 13, 64}), ChordData({52, 4, 19}), ChordData({54, 4, 144}), ChordData({144, 0, 2}), 
 ChordData({144, 0, 147}), ChordData({148, 8, 17}), ChordData({162, 4, 11}), ChordData({164, 64, 26}), 
 ChordData({178, 12, 129}), ChordData({180, 0, 129}), ChordData({180, 64, 130}), 
};

uint8_t const kmap5_Word_len29_anagram1_seqs[98] = {
 191, 199, 118, 112, 
 63, 12, 62, 241, 
 166, 31, 125, 126, 
 100, 223, 4, 236, 
 220, 89, 131, 113, 
 226, 211, 183, 246, 
 107, 66, 246, 237, 
 188, 207, 121, 31, 
 186, 246, 85, 175, 
 118, 181, 96, 65, 
 172, 116, 117, 221, 
 249, 175, 174, 229, 
 30, 66, 239, 26, 
 86, 250, 229, 172, 
 183, 79, 241, 69, 
 30, 26, 191, 93, 
 93, 211, 244, 222, 
 39, 30, 121, 243, 
 73, 121, 231, 45, 
 219, 102, 204, 243, 
 87, 188, 73, 213, 
 236, 51, 148, 220, 
 36, 253, 185, 37, 
 81, 61, 3, 217, 
 247, 100, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len29_anagram1 = {
  LengthAndAnagram(29, 1), // seq_bit_len_and_anagram
  27, // num_chords
  kmap5_Word_len29_anagram1_chords, // chords
  kmap5_Word_len29_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len29_anagram2_chords[5] = {
 ChordData({16, 4, 153}), ChordData({16, 4, 155}), ChordData({36, 8, 0}), ChordData({48, 1, 16}), 
 ChordData({52, 12, 16}), 
};

uint8_t const kmap5_Word_len29_anagram2_seqs[19] = {
 60, 248, 171, 143, 
 254, 172, 88, 246, 
 181, 96, 193, 117, 
 87, 161, 253, 125, 
 191, 230, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len29_anagram2 = {
  LengthAndAnagram(29, 2), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len29_anagram2_chords, // chords
  kmap5_Word_len29_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len29_anagram3_chords[3] = {
 ChordData({18, 0, 131}), ChordData({18, 64, 19}), ChordData({160, 33, 1}), 
};

uint8_t const kmap5_Word_len29_anagram3_seqs[11] = {
 103, 208, 13, 249, 
 128, 185, 243, 118, 
 89, 33, 59, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len29_anagram3 = {
  LengthAndAnagram(29, 3), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len29_anagram3_chords, // chords
  kmap5_Word_len29_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len30_anagram0_chords[117] = {
 ChordData({0, 0, 73}), ChordData({0, 4, 211}), ChordData({0, 72, 80}), ChordData({2, 4, 146}), 
 ChordData({2, 5, 67}), ChordData({4, 12, 144}), ChordData({6, 12, 137}), ChordData({6, 36, 64}), 
 ChordData({16, 8, 81}), ChordData({16, 12, 208}), ChordData({16, 13, 147}), ChordData({16, 32, 25}), 
 ChordData({16, 68, 82}), ChordData({16, 68, 146}), ChordData({16, 69, 146}), ChordData({16, 96, 19}), 
 ChordData({18, 0, 89}), ChordData({18, 0, 147}), ChordData({18, 4, 90}), ChordData({18, 4, 209}), 
 ChordData({18, 9, 19}), ChordData({18, 12, 138}), ChordData({18, 12, 144}), ChordData({18, 64, 91}), 
 ChordData({18, 65, 3}), ChordData({18, 68, 136}), ChordData({20, 0, 90}), ChordData({20, 0, 210}), 
 ChordData({20, 4, 155}), ChordData({20, 8, 26}), ChordData({20, 36, 80}), ChordData({32, 5, 146}), 
 ChordData({32, 13, 24}), ChordData({32, 68, 209}), ChordData({34, 5, 136}), ChordData({34, 12, 11}), 
 ChordData({34, 12, 24}), ChordData({34, 12, 25}), ChordData({34, 12, 73}), ChordData({34, 64, 66}), 
 ChordData({34, 64, 209}), ChordData({34, 69, 129}), ChordData({34, 76, 0}), ChordData({38, 96, 18}), 
 ChordData({48, 1, 65}), ChordData({48, 5, 25}), ChordData({48, 5, 82}), ChordData({48, 8, 73}), 
 ChordData({48, 44, 81}), ChordData({48, 76, 8}), ChordData({48, 76, 10}), ChordData({50, 1, 24}), 
 ChordData({50, 5, 144}), ChordData({50, 8, 10}), ChordData({50, 12, 64}), ChordData({50, 13, 24}), 
 ChordData({50, 13, 128}), ChordData({50, 33, 26}), ChordData({50, 44, 18}), ChordData({50, 64, 136}), 
 ChordData({50, 73, 16}), ChordData({50, 97, 129}), ChordData({52, 5, 144}), ChordData({52, 64, 72}), 
 ChordData({54, 0, 17}), ChordData({54, 1, 9}), ChordData({54, 8, 9}), ChordData({54, 12, 9}), 
 ChordData({54, 12, 17}), ChordData({54, 12, 64}), ChordData({128, 0, 26}), ChordData({128, 4, 216}), 
 ChordData({128, 44, 67}), ChordData({130, 1, 209}), ChordData({130, 5, 11}), ChordData({130, 68, 24}), 
 ChordData({130, 73, 18}), ChordData({132, 1, 146}), ChordData({132, 12, 3}), ChordData({134, 4, 9}), 
 ChordData({134, 12, 129}), ChordData({144, 0, 139}), ChordData({144, 1, 72}), ChordData({144, 4, 145}), 
 ChordData({144, 64, 83}), ChordData({144, 73, 16}), ChordData({148, 0, 27}), ChordData({148, 0, 146}), 
 ChordData({148, 9, 24}), ChordData({148, 32, 17}), ChordData({150, 1, 144}), ChordData({160, 64, 11}), 
 ChordData({160, 77, 16}), ChordData({162, 0, 82}), ChordData({162, 8, 11}), ChordData({162, 9, 24}), 
 ChordData({162, 32, 74}), ChordData({162, 33, 9}), ChordData({162, 68, 24}), ChordData({164, 4, 3}), 
 ChordData({176, 1, 16}), ChordData({176, 1, 18}), ChordData({176, 1, 25}), ChordData({176, 1, 74}), 
 ChordData({176, 8, 144}), ChordData({176, 9, 16}), ChordData({176, 9, 17}), ChordData({178, 72, 18}), 
 ChordData({180, 0, 64}), ChordData({180, 0, 80}), ChordData({180, 0, 82}), ChordData({180, 0, 145}), 
 ChordData({180, 8, 3}), ChordData({180, 8, 80}), ChordData({180, 64, 18}), ChordData({180, 72, 128}), 
 ChordData({182, 8, 10}), 
};

uint8_t const kmap5_Word_len30_anagram0_seqs[439] = {
 188, 240, 199, 43, 
 110, 41, 247, 196, 
 199, 21, 48, 60, 
 110, 73, 131, 221, 
 11, 142, 28, 248, 
 23, 44, 56, 177, 
 209, 235, 125, 99, 
 47, 243, 226, 104, 
 57, 47, 15, 254, 
 209, 2, 254, 88, 
 244, 249, 152, 87, 
 125, 193, 184, 126, 
 241, 211, 250, 67, 
 9, 152, 186, 95, 
 3, 204, 199, 188, 
 163, 231, 181, 156, 
 201, 120, 59, 56, 
 138, 235, 23, 251, 
 151, 198, 114, 184, 
 131, 69, 159, 65, 
 31, 71, 205, 131, 
 127, 28, 7, 171, 
 204, 149, 193, 221, 
 224, 28, 31, 94, 
 199, 212, 214, 98, 
 69, 27, 212, 214, 
 34, 205, 250, 116, 
 165, 181, 96, 25, 
 221, 188, 236, 155, 
 192, 167, 7, 149, 
 175, 15, 247, 227, 
 7, 240, 42, 7, 
 95, 33, 205, 115, 
 127, 131, 175, 58, 
 203, 189, 62, 247, 
 59, 175, 119, 82, 
 245, 227, 132, 17, 
 172, 34, 82, 168, 
 206, 94, 24, 56, 
 247, 196, 135, 231, 
 38, 176, 178, 223, 
 9, 82, 33, 180, 
 28, 180, 122, 255, 
 44, 117, 187, 71, 
 243, 114, 230, 172, 
 236, 151, 179, 92, 
 172, 26, 94, 253, 
 129, 123, 69, 91, 
 225, 168, 189, 221, 
 62, 28, 50, 207, 
 89, 7, 29, 95, 
 100, 56, 115, 163, 
 134, 191, 220, 16, 
 61, 52, 43, 225, 
 88, 253, 139, 108, 
 56, 87, 157, 66, 
 213, 97, 56, 47, 
 116, 48, 13, 100, 
 247, 4, 221, 239, 
 75, 149, 102, 13, 
 183, 211, 215, 115, 
 111, 117, 55, 215, 
 172, 55, 53, 126, 
 236, 199, 122, 109, 
 135, 251, 115, 123, 
 145, 225, 204, 99, 
 170, 230, 242, 224, 
 47, 169, 114, 25, 
 31, 89, 71, 185, 
 35, 215, 61, 222, 
 164, 190, 134, 205, 
 9, 49, 195, 116, 
 101, 71, 217, 90, 
 137, 25, 219, 227, 
 125, 107, 57, 122, 
 217, 110, 226, 19, 
 166, 158, 65, 151, 
 93, 103, 21, 95, 
 146, 247, 207, 193, 
 114, 155, 101, 183, 
 118, 200, 104, 189, 
 205, 86, 26, 212, 
 40, 215, 221, 102, 
 65, 107, 219, 108, 
 204, 215, 54, 187, 
 33, 99, 106, 168, 
 120, 129, 203, 253, 
 34, 214, 157, 172, 
 130, 169, 220, 224, 
 197, 92, 29, 133, 
 88, 133, 77, 234, 
 165, 14, 100, 247, 
 27, 234, 104, 94, 
 246, 143, 152, 60, 
 116, 46, 52, 220, 
 68, 111, 217, 229, 
 94, 85, 99, 106, 
 87, 197, 107, 46, 
 137, 115, 151, 107, 
 206, 11, 179, 110, 
 244, 133, 225, 114, 
 209, 82, 91, 75, 
 113, 171, 219, 82, 
 156, 189, 96, 93, 
 223, 102, 237, 201, 
 152, 177, 213, 115, 
 246, 226, 229, 220, 
 54, 67, 69, 7, 
 115, 166, 108, 152, 
 177, 31, 53, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len30_anagram0 = {
  LengthAndAnagram(30, 0), // seq_bit_len_and_anagram
  117, // num_chords
  kmap5_Word_len30_anagram0_chords, // chords
  kmap5_Word_len30_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len30_anagram1_chords[26] = {
 ChordData({0, 0, 192}), ChordData({2, 4, 147}), ChordData({16, 4, 27}), ChordData({16, 4, 147}), 
 ChordData({16, 9, 146}), ChordData({16, 37, 17}), ChordData({18, 4, 131}), ChordData({18, 4, 145}), 
 ChordData({18, 64, 0}), ChordData({20, 0, 147}), ChordData({34, 9, 8}), ChordData({48, 0, 27}), 
 ChordData({48, 4, 152}), ChordData({48, 5, 146}), ChordData({48, 5, 152}), ChordData({48, 13, 9}), 
 ChordData({52, 1, 16}), ChordData({52, 4, 130}), ChordData({54, 0, 25}), ChordData({54, 1, 8}), 
 ChordData({130, 68, 18}), ChordData({144, 0, 27}), ChordData({144, 8, 26}), ChordData({148, 1, 80}), 
 ChordData({162, 33, 9}), ChordData({180, 32, 17}), 
};

uint8_t const kmap5_Word_len30_anagram1_seqs[98] = {
 188, 240, 194, 19, 
 210, 239, 92, 105, 
 189, 125, 69, 27, 
 116, 251, 120, 124, 
 209, 68, 101, 247, 
 123, 204, 107, 16, 
 206, 253, 209, 156, 
 247, 207, 252, 240, 
 129, 183, 65, 232, 
 109, 199, 77, 113, 
 20, 162, 245, 234, 
 150, 60, 125, 93, 
 235, 19, 121, 97, 
 217, 85, 245, 62, 
 113, 175, 247, 208, 
 125, 237, 58, 47, 
 126, 251, 158, 124, 
 59, 125, 85, 55, 
 43, 172, 163, 192, 
 239, 78, 46, 166, 
 226, 250, 108, 76, 
 205, 88, 182, 205, 
 206, 34, 154, 199, 
 70, 97, 191, 121, 
 204, 11, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len30_anagram1 = {
  LengthAndAnagram(30, 1), // seq_bit_len_and_anagram
  26, // num_chords
  kmap5_Word_len30_anagram1_chords, // chords
  kmap5_Word_len30_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len30_anagram2_chords[8] = {
 ChordData({34, 12, 136}), ChordData({48, 0, 147}), ChordData({48, 5, 146}), ChordData({50, 13, 9}), 
 ChordData({52, 0, 128}), ChordData({164, 64, 18}), ChordData({178, 1, 24}), ChordData({180, 0, 16}), 
};

uint8_t const kmap5_Word_len30_anagram2_seqs[30] = {
 220, 235, 16, 253, 
 25, 116, 117, 13, 
 159, 200, 91, 114, 
 163, 247, 208, 125, 
 237, 123, 50, 38, 
 208, 103, 217, 229, 
 122, 160, 242, 174, 
 155, 205, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len30_anagram2 = {
  LengthAndAnagram(30, 2), // seq_bit_len_and_anagram
  8, // num_chords
  kmap5_Word_len30_anagram2_chords, // chords
  kmap5_Word_len30_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len31_anagram0_chords[106] = {
 ChordData({0, 64, 72}), ChordData({0, 68, 88}), ChordData({2, 36, 19}), ChordData({2, 69, 130}), 
 ChordData({4, 0, 3}), ChordData({4, 4, 152}), ChordData({4, 40, 0}), ChordData({4, 108, 16}), 
 ChordData({6, 0, 2}), ChordData({6, 0, 64}), ChordData({6, 1, 89}), ChordData({6, 4, 0}), 
 ChordData({16, 68, 147}), ChordData({18, 0, 83}), ChordData({18, 1, 19}), ChordData({18, 4, 19}), 
 ChordData({18, 4, 138}), ChordData({18, 4, 153}), ChordData({18, 12, 65}), ChordData({18, 13, 65}), 
 ChordData({18, 36, 65}), ChordData({18, 41, 11}), ChordData({18, 64, 83}), ChordData({20, 4, 81}), 
 ChordData({20, 12, 130}), ChordData({20, 36, 19}), ChordData({22, 4, 138}), ChordData({22, 12, 144}), 
 ChordData({32, 0, 144}), ChordData({32, 4, 64}), ChordData({32, 13, 25}), ChordData({32, 13, 128}), 
 ChordData({32, 69, 144}), ChordData({34, 0, 16}), ChordData({34, 0, 147}), ChordData({34, 4, 80}), 
 ChordData({34, 5, 18}), ChordData({34, 12, 145}), ChordData({34, 64, 128}), ChordData({34, 76, 65}), 
 ChordData({34, 77, 16}), ChordData({34, 96, 192}), ChordData({36, 4, 145}), ChordData({36, 12, 16}), 
 ChordData({38, 5, 24}), ChordData({38, 32, 9}), ChordData({38, 37, 18}), ChordData({48, 1, 82}), 
 ChordData({48, 4, 81}), ChordData({48, 13, 24}), ChordData({48, 33, 17}), ChordData({48, 64, 130}), 
 ChordData({48, 69, 19}), ChordData({48, 69, 129}), ChordData({48, 96, 24}), ChordData({50, 1, 81}), 
 ChordData({50, 8, 17}), ChordData({50, 33, 17}), ChordData({52, 4, 19}), ChordData({52, 5, 16}), 
 ChordData({52, 9, 16}), ChordData({52, 44, 18}), ChordData({52, 68, 144}), ChordData({54, 0, 147}), 
 ChordData({54, 8, 16}), ChordData({54, 8, 192}), ChordData({54, 12, 16}), ChordData({128, 9, 19}), 
 ChordData({128, 12, 27}), ChordData({128, 36, 88}), ChordData({128, 64, 136}), ChordData({128, 76, 10}), 
 ChordData({128, 100, 194}), ChordData({130, 9, 26}), ChordData({130, 32, 83}), ChordData({130, 37, 72}), 
 ChordData({132, 0, 144}), ChordData({132, 44, 9}), ChordData({144, 4, 9}), ChordData({144, 4, 153}), 
 ChordData({144, 12, 65}), ChordData({144, 68, 19}), ChordData({146, 0, 81}), ChordData({146, 0, 202}), 
 ChordData({146, 4, 17}), ChordData({146, 4, 25}), ChordData({146, 4, 90}), ChordData({146, 4, 153}), 
 ChordData({148, 9, 16}), ChordData({150, 0, 131}), ChordData({160, 0, 27}), ChordData({160, 76, 144}), 
 ChordData({162, 12, 80}), ChordData({164, 0, 81}), ChordData({164, 4, 144}), ChordData({164, 13, 16}), 
 ChordData({164, 64, 19}), ChordData({164, 68, 8}), ChordData({176, 0, 145}), ChordData({178, 8, 136}), 
 ChordData({180, 8, 144}), ChordData({180, 12, 16}), ChordData({180, 64, 144}), ChordData({182, 8, 0}), 
 ChordData({182, 8, 16}), ChordData({182, 72, 16}), 
};

uint8_t const kmap5_Word_len31_anagram0_seqs[411] = {
 124, 224, 149, 23, 
 94, 94, 195, 62, 
 178, 223, 185, 178, 
 163, 71, 156, 192, 
 31, 143, 124, 227, 
 193, 191, 189, 242, 
 145, 103, 5, 217, 
 23, 252, 13, 124, 
 227, 145, 31, 190, 
 241, 194, 143, 180, 
 29, 189, 142, 127, 
 190, 241, 195, 3, 
 79, 231, 93, 203, 
 237, 224, 161, 247, 
 166, 43, 113, 231, 
 188, 243, 79, 52, 
 175, 232, 209, 243, 
 234, 147, 229, 38, 
 254, 57, 142, 220, 
 23, 205, 44, 115, 
 127, 46, 206, 33, 
 179, 134, 17, 92, 
 159, 197, 237, 247, 
 207, 6, 125, 108, 
 228, 99, 222, 111, 
 165, 65, 141, 126, 
 116, 253, 52, 5, 
 205, 87, 126, 121, 
 226, 43, 47, 252, 
 115, 15, 247, 245, 
 62, 62, 193, 143, 
 112, 63, 212, 39, 
 190, 242, 203, 79, 
 189, 161, 185, 146, 
 223, 42, 50, 207, 
 195, 95, 156, 231, 
 102, 175, 62, 209, 
 20, 170, 19, 228, 
 62, 76, 141, 97, 
 30, 238, 71, 41, 
 84, 71, 216, 125, 
 95, 233, 183, 255, 
 130, 255, 219, 255, 
 194, 31, 29, 101, 
 211, 207, 193, 253, 
 198, 6, 165, 46, 
 244, 150, 183, 126, 
 169, 107, 30, 122, 
 227, 107, 87, 247, 
 152, 215, 32, 164, 
 26, 124, 251, 208, 
 161, 12, 238, 190, 
 210, 177, 170, 97, 
 29, 214, 112, 228, 
 188, 235, 219, 49, 
 231, 110, 61, 144, 
 93, 255, 119, 222, 
 18, 254, 246, 15, 
 221, 188, 93, 141, 
 70, 246, 177, 247, 
 246, 244, 33, 120, 
 105, 122, 239, 149, 
 109, 29, 167, 70, 
 110, 100, 122, 50, 
 247, 177, 205, 26, 
 51, 118, 185, 247, 
 250, 151, 177, 228, 
 133, 253, 166, 242, 
 148, 26, 82, 49, 
 99, 124, 13, 194, 
 158, 40, 1, 76, 
 237, 102, 35, 27, 
 185, 220, 178, 123, 
 97, 147, 218, 54, 
 123, 114, 108, 236, 
 245, 50, 190, 106, 
 222, 159, 47, 201, 
 251, 122, 142, 127, 
 103, 201, 96, 204, 
 253, 243, 90, 70, 
 46, 87, 134, 6, 
 83, 61, 231, 253, 
 203, 125, 61, 239, 
 228, 10, 90, 127, 
 39, 215, 244, 55, 
 169, 205, 219, 229, 
 70, 131, 26, 229, 
 28, 102, 213, 219, 
 50, 102, 168, 244, 
 203, 253, 78, 86, 
 145, 218, 90, 238, 
 181, 108, 149, 126, 
 219, 38, 220, 143, 
 109, 51, 84, 188, 
 239, 95, 67, 234, 
 102, 37, 223, 121, 
 148, 75, 226, 220, 
 54, 123, 114, 252, 
 214, 54, 57, 247, 
 89, 41, 120, 11, 
 102, 236, 199, 19, 
 219, 38, 231, 182, 
 201, 77, 48, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len31_anagram0 = {
  LengthAndAnagram(31, 0), // seq_bit_len_and_anagram
  106, // num_chords
  kmap5_Word_len31_anagram0_chords, // chords
  kmap5_Word_len31_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len31_anagram1_chords[22] = {
 ChordData({0, 36, 9}), ChordData({0, 68, 8}), ChordData({6, 0, 64}), ChordData({6, 4, 147}), 
 ChordData({6, 12, 0}), ChordData({16, 36, 82}), ChordData({16, 64, 74}), ChordData({18, 4, 27}), 
 ChordData({22, 4, 11}), ChordData({32, 13, 16}), ChordData({34, 12, 9}), ChordData({48, 4, 19}), 
 ChordData({48, 69, 129}), ChordData({52, 0, 17}), ChordData({128, 9, 19}), ChordData({130, 76, 8}), 
 ChordData({144, 4, 131}), ChordData({146, 0, 11}), ChordData({148, 0, 88}), ChordData({148, 8, 146}), 
 ChordData({180, 0, 17}), ChordData({180, 64, 82}), 
};

uint8_t const kmap5_Word_len31_anagram1_seqs[86] = {
 188, 254, 177, 87, 
 62, 240, 202, 63, 
 63, 188, 240, 237, 
 202, 54, 248, 212, 
 166, 96, 193, 95, 
 139, 127, 145, 241, 
 128, 131, 90, 70, 
 207, 251, 120, 237, 
 111, 172, 104, 184, 
 31, 227, 47, 55, 
 247, 113, 20, 215, 
 127, 117, 29, 76, 
 134, 127, 110, 222, 
 171, 219, 243, 151, 
 197, 50, 195, 124, 
 76, 13, 79, 148, 
 248, 231, 81, 77, 
 180, 222, 90, 90, 
 170, 184, 37, 149, 
 209, 203, 111, 246, 
 222, 235, 55, 1, 
 241, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len31_anagram1 = {
  LengthAndAnagram(31, 1), // seq_bit_len_and_anagram
  22, // num_chords
  kmap5_Word_len31_anagram1_chords, // chords
  kmap5_Word_len31_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len31_anagram2_chords[5] = {
 ChordData({0, 68, 10}), ChordData({16, 0, 146}), ChordData({32, 0, 146}), ChordData({48, 5, 128}), 
 ChordData({54, 8, 192}), 
};

uint8_t const kmap5_Word_len31_anagram2_seqs[20] = {
 60, 190, 126, 120, 
 30, 220, 187, 37, 
 85, 80, 221, 146, 
 42, 132, 15, 45, 
 181, 167, 137, 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len31_anagram2 = {
  LengthAndAnagram(31, 2), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len31_anagram2_chords, // chords
  kmap5_Word_len31_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len31_anagram3_chords[1] = {
 ChordData({48, 8, 18}), 
};

uint8_t const kmap5_Word_len31_anagram3_seqs[4] = {
 209, 139, 117, 75, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len31_anagram3 = {
  LengthAndAnagram(31, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len31_anagram3_chords, // chords
  kmap5_Word_len31_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len32_anagram0_chords[111] = {
 ChordData({0, 0, 26}), ChordData({0, 5, 91}), ChordData({0, 33, 72}), ChordData({0, 45, 19}), 
 ChordData({0, 72, 64}), ChordData({0, 100, 203}), ChordData({2, 4, 147}), ChordData({2, 5, 18}), 
 ChordData({2, 5, 19}), ChordData({2, 5, 83}), ChordData({2, 76, 26}), ChordData({4, 32, 8}), 
 ChordData({6, 12, 18}), ChordData({6, 68, 210}), ChordData({6, 76, 18}), ChordData({16, 68, 154}), 
 ChordData({18, 0, 210}), ChordData({18, 4, 155}), ChordData({18, 8, 89}), ChordData({18, 12, 145}), 
 ChordData({18, 12, 153}), ChordData({18, 33, 80}), ChordData({18, 36, 131}), ChordData({18, 64, 11}), 
 ChordData({18, 64, 25}), ChordData({18, 68, 3}), ChordData({18, 68, 11}), ChordData({18, 68, 75}), 
 ChordData({18, 68, 81}), ChordData({18, 72, 10}), ChordData({18, 76, 17}), ChordData({20, 4, 144}), 
 ChordData({20, 4, 201}), ChordData({20, 12, 129}), ChordData({22, 1, 82}), ChordData({22, 8, 11}), 
 ChordData({32, 4, 210}), ChordData({32, 68, 154}), ChordData({34, 8, 8}), ChordData({34, 33, 88}), 
 ChordData({36, 1, 128}), ChordData({38, 4, 146}), ChordData({38, 40, 17}), ChordData({38, 64, 81}), 
 ChordData({48, 1, 154}), ChordData({48, 4, 19}), ChordData({48, 4, 146}), ChordData({48, 5, 145}), 
 ChordData({48, 12, 153}), ChordData({48, 36, 195}), ChordData({48, 64, 201}), ChordData({48, 64, 209}), 
 ChordData({50, 4, 201}), ChordData({50, 5, 153}), ChordData({50, 8, 83}), ChordData({50, 12, 145}), 
 ChordData({50, 37, 17}), ChordData({50, 64, 144}), ChordData({50, 68, 10}), ChordData({50, 72, 10}), 
 ChordData({52, 0, 145}), ChordData({52, 4, 17}), ChordData({52, 4, 208}), ChordData({52, 8, 80}), 
 ChordData({52, 12, 82}), ChordData({52, 13, 137}), ChordData({54, 0, 145}), ChordData({54, 4, 144}), 
 ChordData({54, 8, 18}), ChordData({128, 1, 2}), ChordData({128, 4, 75}), ChordData({128, 4, 91}), 
 ChordData({128, 44, 26}), ChordData({130, 4, 74}), ChordData({130, 4, 139}), ChordData({130, 4, 147}), 
 ChordData({130, 100, 146}), ChordData({132, 12, 26}), ChordData({134, 8, 146}), ChordData({134, 96, 82}), 
 ChordData({144, 76, 17}), ChordData({146, 8, 67}), ChordData({146, 8, 72}), ChordData({146, 12, 9}), 
 ChordData({146, 64, 74}), ChordData({146, 64, 90}), ChordData({148, 0, 147}), ChordData({148, 4, 194}), 
 ChordData({148, 4, 216}), ChordData({148, 8, 130}), ChordData({148, 8, 131}), ChordData({150, 0, 9}), 
 ChordData({160, 13, 24}), ChordData({160, 33, 17}), ChordData({162, 4, 202}), ChordData({162, 8, 19}), 
 ChordData({162, 96, 3}), ChordData({164, 0, 25}), ChordData({164, 0, 73}), ChordData({164, 0, 147}), 
 ChordData({176, 0, 18}), ChordData({176, 1, 90}), ChordData({176, 4, 10}), ChordData({176, 8, 90}), 
 ChordData({176, 8, 130}), ChordData({176, 32, 146}), ChordData({176, 33, 17}), ChordData({178, 0, 11}), 
 ChordData({178, 1, 25}), ChordData({178, 1, 152}), ChordData({180, 8, 136}), 
};

uint8_t const kmap5_Word_len32_anagram0_seqs[444] = {
 188, 242, 37, 143, 
 221, 235, 189, 148, 
 93, 97, 40, 160, 
 124, 241, 143, 149, 
 188, 240, 145, 15, 
 192, 139, 22, 120, 
 184, 115, 131, 79, 
 252, 119, 59, 248, 
 183, 223, 117, 131, 
 242, 55, 210, 149, 
 161, 212, 143, 131, 
 188, 242, 140, 111, 
 109, 39, 254, 150, 
 97, 164, 209, 151, 
 192, 20, 252, 13, 
 248, 100, 13, 191, 
 6, 121, 113, 196, 
 175, 160, 241, 149, 
 113, 116, 228, 188, 
 241, 207, 59, 79, 
 231, 141, 163, 79, 
 194, 188, 211, 117, 
 127, 140, 124, 131, 
 163, 56, 193, 122, 
 193, 26, 118, 206, 
 193, 97, 240, 207, 
 163, 97, 240, 207, 
 97, 228, 94, 209, 
 97, 228, 229, 188, 
 209, 97, 112, 212, 
 97, 62, 250, 188, 
 237, 247, 137, 76, 
 141, 252, 242, 122, 
 231, 216, 232, 207, 
 210, 140, 211, 149, 
 56, 55, 5, 173, 
 85, 234, 19, 149, 
 244, 85, 195, 150, 
 113, 116, 98, 141, 
 93, 93, 29, 97, 
 60, 228, 27, 79, 
 52, 253, 254, 150, 
 183, 83, 99, 99, 
 97, 228, 234, 246, 
 29, 85, 43, 150, 
 143, 88, 247, 207, 
 104, 162, 74, 191, 
 107, 88, 233, 207, 
 107, 50, 247, 122, 
 6, 177, 175, 114, 
 226, 66, 213, 122, 
 235, 66, 213, 114, 
 163, 82, 233, 207, 
 163, 103, 184, 79, 
 156, 247, 6, 45, 
 107, 250, 27, 206, 
 204, 59, 247, 208, 
 235, 66, 117, 214, 
 95, 195, 88, 209, 
 230, 38, 88, 209, 
 124, 95, 143, 188, 
 223, 188, 87, 215, 
 141, 252, 82, 215, 
 109, 45, 94, 206, 
 142, 253, 139, 148, 
 61, 189, 22, 125, 
 231, 221, 233, 201, 
 107, 154, 239, 201, 
 205, 139, 30, 206, 
 124, 242, 29, 143, 
 152, 42, 247, 122, 
 152, 122, 251, 114, 
 236, 55, 166, 150, 
 137, 248, 50, 169, 
 148, 248, 55, 169, 
 152, 123, 131, 79, 
 44, 105, 194, 151, 
 152, 177, 189, 150, 
 73, 101, 108, 131, 
 64, 174, 176, 105, 
 49, 131, 247, 207, 
 152, 18, 125, 131, 
 142, 35, 50, 169, 
 154, 113, 244, 207, 
 193, 56, 50, 169, 
 152, 42, 19, 188, 
 109, 19, 220, 120, 
 152, 68, 223, 196, 
 205, 43, 169, 79, 
 152, 177, 145, 65, 
 152, 177, 145, 207, 
 205, 55, 55, 169, 
 124, 204, 133, 175, 
 199, 54, 43, 100, 
 175, 160, 201, 42, 
 220, 224, 229, 150, 
 192, 28, 203, 122, 
 124, 159, 123, 169, 
 124, 159, 114, 169, 
 45, 43, 221, 150, 
 101, 214, 2, 215, 
 152, 10, 215, 34, 
 175, 154, 85, 209, 
 152, 42, 94, 206, 
 49, 201, 88, 201, 
 101, 214, 2, 215, 
 151, 208, 199, 188, 
 152, 122, 163, 213, 
 58, 183, 9, 173, 
 107, 26, 56, 169, 
 86, 206, 148, 205, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len32_anagram0 = {
  LengthAndAnagram(32, 0), // seq_bit_len_and_anagram
  111, // num_chords
  kmap5_Word_len32_anagram0_chords, // chords
  kmap5_Word_len32_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len32_anagram1_chords[16] = {
 ChordData({16, 8, 19}), ChordData({16, 8, 83}), ChordData({18, 12, 9}), ChordData({18, 68, 11}), 
 ChordData({22, 4, 19}), ChordData({22, 4, 147}), ChordData({32, 9, 64}), ChordData({34, 1, 0}), 
 ChordData({36, 0, 16}), ChordData({38, 4, 147}), ChordData({50, 5, 153}), ChordData({50, 8, 80}), 
 ChordData({144, 1, 9}), ChordData({160, 13, 144}), ChordData({160, 33, 1}), ChordData({180, 8, 19}), 
};

uint8_t const kmap5_Word_len32_anagram1_seqs[64] = {
 232, 232, 243, 150, 
 177, 148, 243, 150, 
 163, 55, 241, 207, 
 143, 56, 193, 122, 
 109, 31, 111, 208, 
 237, 247, 6, 201, 
 60, 228, 133, 143, 
 60, 228, 43, 63, 
 124, 227, 151, 175, 
 223, 15, 205, 149, 
 183, 243, 10, 201, 
 82, 151, 27, 206, 
 93, 1, 43, 236, 
 93, 110, 172, 244, 
 199, 178, 66, 118, 
 45, 57, 239, 149, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len32_anagram1 = {
  LengthAndAnagram(32, 1), // seq_bit_len_and_anagram
  16, // num_chords
  kmap5_Word_len32_anagram1_chords, // chords
  kmap5_Word_len32_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len32_anagram2_chords[6] = {
 ChordData({16, 12, 81}), ChordData({36, 0, 2}), ChordData({48, 69, 24}), ChordData({128, 4, 27}), 
 ChordData({130, 4, 11}), ChordData({164, 4, 146}), 
};

uint8_t const kmap5_Word_len32_anagram2_seqs[24] = {
 241, 239, 214, 34, 
 60, 242, 141, 175, 
 214, 240, 10, 189, 
 152, 122, 251, 120, 
 56, 247, 55, 169, 
 60, 248, 99, 246, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len32_anagram2 = {
  LengthAndAnagram(32, 2), // seq_bit_len_and_anagram
  6, // num_chords
  kmap5_Word_len32_anagram2_chords, // chords
  kmap5_Word_len32_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len33_anagram0_chords[87] = {
 ChordData({0, 69, 0}), ChordData({0, 69, 18}), ChordData({2, 12, 9}), ChordData({2, 12, 154}), 
 ChordData({2, 64, 18}), ChordData({2, 68, 26}), ChordData({2, 100, 2}), ChordData({4, 1, 2}), 
 ChordData({4, 1, 128}), ChordData({16, 4, 155}), ChordData({16, 5, 89}), ChordData({16, 44, 27}), 
 ChordData({16, 76, 1}), ChordData({18, 32, 74}), ChordData({18, 65, 9}), ChordData({18, 76, 2}), 
 ChordData({22, 64, 83}), ChordData({22, 68, 80}), ChordData({32, 5, 65}), ChordData({32, 5, 147}), 
 ChordData({32, 12, 82}), ChordData({34, 0, 91}), ChordData({34, 13, 19}), ChordData({36, 0, 2}), 
 ChordData({36, 8, 8}), ChordData({36, 64, 64}), ChordData({36, 100, 72}), ChordData({38, 12, 18}), 
 ChordData({38, 32, 192}), ChordData({48, 12, 129}), ChordData({48, 33, 89}), ChordData({48, 64, 83}), 
 ChordData({48, 96, 194}), ChordData({50, 8, 88}), ChordData({50, 12, 26}), ChordData({50, 12, 129}), 
 ChordData({50, 12, 147}), ChordData({50, 12, 193}), ChordData({50, 13, 9}), ChordData({50, 13, 16}), 
 ChordData({50, 65, 64}), ChordData({50, 68, 1}), ChordData({50, 68, 137}), ChordData({50, 68, 146}), 
 ChordData({52, 5, 25}), ChordData({52, 12, 192}), ChordData({52, 96, 18}), ChordData({54, 32, 131}), 
 ChordData({54, 64, 82}), ChordData({54, 68, 65}), ChordData({128, 69, 18}), ChordData({130, 12, 27}), 
 ChordData({132, 0, 147}), ChordData({132, 8, 83}), ChordData({134, 0, 73}), ChordData({134, 4, 17}), 
 ChordData({134, 4, 147}), ChordData({144, 13, 16}), ChordData({146, 0, 147}), ChordData({146, 8, 130}), 
 ChordData({146, 64, 80}), ChordData({148, 0, 9}), ChordData({148, 0, 83}), ChordData({148, 8, 82}), 
 ChordData({148, 12, 145}), ChordData({150, 0, 65}), ChordData({160, 4, 152}), ChordData({160, 96, 72}), 
 ChordData({162, 0, 201}), ChordData({162, 1, 195}), ChordData({162, 4, 67}), ChordData({162, 4, 145}), 
 ChordData({164, 33, 17}), ChordData({166, 1, 72}), ChordData({166, 1, 146}), ChordData({166, 8, 64}), 
 ChordData({176, 8, 88}), ChordData({176, 9, 26}), ChordData({176, 12, 1}), ChordData({176, 64, 138}), 
 ChordData({178, 8, 10}), ChordData({178, 8, 81}), ChordData({178, 12, 9}), ChordData({178, 12, 129}), 
 ChordData({180, 1, 80}), ChordData({182, 0, 80}), ChordData({182, 0, 82}), 
};

uint8_t const kmap5_Word_len33_anagram0_seqs[359] = {
 124, 199, 7, 254, 
 187, 223, 15, 95, 
 198, 31, 189, 31, 
 197, 157, 56, 250, 
 196, 7, 126, 248, 
 146, 15, 191, 192, 
 40, 207, 30, 248, 
 25, 190, 241, 29, 
 143, 60, 241, 29, 
 223, 12, 58, 175, 
 62, 221, 190, 74, 
 231, 141, 94, 100, 
 175, 23, 125, 31, 
 254, 158, 71, 54, 
 106, 113, 112, 55, 
 58, 231, 199, 15, 
 142, 131, 193, 130, 
 59, 237, 218, 239, 
 135, 17, 243, 95, 
 97, 149, 235, 30, 
 43, 93, 41, 53, 
 198, 223, 114, 84, 
 110, 43, 30, 220, 
 231, 230, 74, 190, 
 241, 200, 247, 60, 
 199, 55, 94, 249, 
 192, 247, 188, 176, 
 42, 253, 107, 104, 
 59, 220, 99, 217, 
 106, 79, 35, 204, 
 220, 83, 253, 179, 
 220, 90, 225, 177, 
 96, 185, 173, 120, 
 130, 204, 161, 146, 
 171, 14, 231, 21, 
 115, 191, 243, 138, 
 174, 116, 19, 255, 
 204, 121, 111, 240, 
 73, 38, 86, 250, 
 179, 26, 254, 13, 
 231, 248, 187, 243, 
 208, 97, 186, 174, 
 138, 255, 110, 174, 
 6, 191, 222, 20, 
 170, 126, 44, 84, 
 103, 221, 214, 80, 
 95, 239, 69, 28, 
 123, 50, 207, 220, 
 175, 1, 131, 216, 
 244, 115, 193, 130, 
 59, 189, 195, 124, 
 239, 179, 116, 185, 
 192, 111, 216, 140, 
 175, 55, 216, 54, 
 47, 49, 73, 202, 
 216, 46, 99, 75, 
 153, 155, 212, 150, 
 123, 251, 115, 183, 
 217, 6, 159, 138, 
 191, 159, 69, 27, 
 116, 222, 201, 229, 
 163, 65, 131, 25, 
 70, 114, 131, 55, 
 91, 75, 181, 94, 
 219, 148, 102, 60, 
 204, 216, 214, 34, 
 231, 216, 114, 159, 
 178, 181, 148, 57, 
 131, 103, 93, 125, 
 226, 89, 13, 146, 
 42, 73, 245, 38, 
 149, 18, 142, 220, 
 224, 99, 86, 185, 
 193, 171, 151, 59, 
 79, 253, 102, 133, 
 236, 120, 56, 189, 
 164, 246, 147, 148, 
 176, 204, 158, 155, 
 172, 98, 205, 141, 
 89, 5, 83, 57, 
 47, 244, 215, 203, 
 248, 103, 76, 69, 
 170, 193, 152, 202, 
 141, 162, 99, 142, 
 92, 93, 143, 106, 
 114, 127, 230, 146, 
 254, 134, 220, 54, 
 225, 90, 68, 106, 
 243, 78, 110, 91, 
 227, 100, 21, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len33_anagram0 = {
  LengthAndAnagram(33, 0), // seq_bit_len_and_anagram
  87, // num_chords
  kmap5_Word_len33_anagram0_chords, // chords
  kmap5_Word_len33_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len33_anagram1_chords[15] = {
 ChordData({4, 40, 0}), ChordData({18, 1, 9}), ChordData({18, 44, 10}), ChordData({18, 44, 130}), 
 ChordData({22, 0, 19}), ChordData({22, 4, 80}), ChordData({34, 4, 146}), ChordData({36, 0, 64}), 
 ChordData({36, 8, 2}), ChordData({36, 64, 64}), ChordData({50, 12, 3}), ChordData({50, 12, 153}), 
 ChordData({52, 8, 16}), ChordData({54, 1, 128}), ChordData({144, 0, 154}), 
};

uint8_t const kmap5_Word_len33_anagram1_seqs[62] = {
 124, 228, 27, 207, 
 70, 187, 209, 57, 
 71, 35, 123, 29, 
 68, 230, 56, 248, 
 212, 214, 56, 109, 
 238, 91, 219, 31, 
 49, 206, 98, 165, 
 95, 190, 242, 194, 
 247, 124, 227, 57, 
 30, 249, 158, 23, 
 62, 60, 222, 112, 
 127, 30, 61, 47, 
 247, 180, 142, 142, 
 189, 215, 52, 112, 
 122, 50, 143, 185, 
 106, 34, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len33_anagram1 = {
  LengthAndAnagram(33, 1), // seq_bit_len_and_anagram
  15, // num_chords
  kmap5_Word_len33_anagram1_chords, // chords
  kmap5_Word_len33_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len33_anagram2_chords[2] = {
 ChordData({36, 9, 0}), ChordData({144, 8, 26}), 
};

uint8_t const kmap5_Word_len33_anagram2_seqs[9] = {
 124, 228, 27, 15, 
 209, 235, 152, 90, 
 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len33_anagram2 = {
  LengthAndAnagram(33, 2), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len33_anagram2_chords, // chords
  kmap5_Word_len33_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len33_anagram3_chords[1] = {
 ChordData({20, 4, 25}), 
};

uint8_t const kmap5_Word_len33_anagram3_seqs[5] = {
 223, 218, 175, 245, 
 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len33_anagram3 = {
  LengthAndAnagram(33, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len33_anagram3_chords, // chords
  kmap5_Word_len33_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len34_anagram0_chords[74] = {
 ChordData({0, 68, 89}), ChordData({2, 4, 218}), ChordData({6, 36, 74}), ChordData({16, 1, 26}), 
 ChordData({16, 4, 153}), ChordData({16, 5, 25}), ChordData({16, 64, 90}), ChordData({18, 4, 193}), 
 ChordData({18, 4, 201}), ChordData({18, 12, 18}), ChordData({18, 64, 27}), ChordData({18, 64, 154}), 
 ChordData({20, 12, 154}), ChordData({20, 96, 80}), ChordData({22, 0, 210}), ChordData({22, 1, 66}), 
 ChordData({22, 44, 64}), ChordData({34, 5, 210}), ChordData({34, 12, 9}), ChordData({34, 12, 67}), 
 ChordData({34, 12, 81}), ChordData({34, 37, 81}), ChordData({36, 4, 83}), ChordData({48, 1, 209}), 
 ChordData({48, 5, 83}), ChordData({48, 13, 25}), ChordData({48, 69, 17}), ChordData({50, 0, 83}), 
 ChordData({52, 8, 83}), ChordData({52, 12, 24}), ChordData({52, 36, 82}), ChordData({54, 0, 72}), 
 ChordData({54, 8, 129}), ChordData({128, 44, 25}), ChordData({130, 1, 139}), ChordData({130, 4, 202}), 
 ChordData({130, 5, 27}), ChordData({130, 68, 9}), ChordData({132, 4, 208}), ChordData({134, 12, 128}), 
 ChordData({134, 12, 138}), ChordData({134, 36, 193}), ChordData({134, 40, 24}), ChordData({144, 4, 147}), 
 ChordData({144, 4, 155}), ChordData({144, 32, 26}), ChordData({144, 64, 17}), ChordData({144, 64, 147}), 
 ChordData({144, 96, 201}), ChordData({146, 1, 146}), ChordData({150, 76, 8}), ChordData({162, 12, 9}), 
 ChordData({162, 12, 11}), ChordData({162, 13, 88}), ChordData({162, 64, 75}), ChordData({176, 0, 83}), 
 ChordData({176, 0, 154}), ChordData({176, 1, 2}), ChordData({176, 1, 80}), ChordData({176, 5, 19}), 
 ChordData({176, 8, 9}), ChordData({176, 72, 11}), ChordData({176, 76, 3}), ChordData({176, 76, 129}), 
 ChordData({178, 12, 1}), ChordData({178, 72, 82}), ChordData({180, 4, 129}), ChordData({180, 4, 193}), 
 ChordData({180, 8, 19}), ChordData({182, 0, 192}), ChordData({182, 5, 129}), ChordData({182, 8, 65}), 
 ChordData({182, 32, 144}), ChordData({182, 36, 16}), 
};

uint8_t const kmap5_Word_len34_anagram0_seqs[315] = {
 114, 175, 225, 55, 
 188, 62, 149, 50, 
 194, 70, 218, 235, 
 224, 186, 243, 90, 
 209, 79, 231, 213, 
 63, 127, 215, 121, 
 173, 199, 75, 25, 
 212, 165, 252, 153, 
 104, 206, 22, 177, 
 222, 60, 241, 31, 
 189, 131, 63, 193, 
 122, 115, 37, 150, 
 52, 26, 188, 175, 
 79, 101, 65, 11, 
 115, 99, 222, 224, 
 54, 228, 38, 165, 
 52, 227, 116, 131, 
 142, 141, 189, 140, 
 72, 93, 56, 248, 
 116, 115, 175, 83, 
 227, 227, 13, 55, 
 114, 114, 59, 127, 
 53, 202, 237, 15, 
 100, 247, 189, 220, 
 62, 158, 220, 86, 
 8, 201, 114, 251, 
 103, 88, 254, 194, 
 26, 173, 7, 247, 
 67, 253, 179, 24, 
 235, 206, 149, 210, 
 140, 183, 53, 70, 
 199, 126, 95, 221, 
 234, 34, 123, 113, 
 95, 101, 212, 34, 
 177, 210, 77, 35, 
 199, 223, 63, 150, 
 138, 169, 29, 13, 
 30, 175, 131, 73, 
 47, 221, 62, 222, 
 164, 126, 8, 115, 
 147, 218, 54, 91, 
 202, 83, 204, 130, 
 67, 244, 152, 177, 
 209, 143, 178, 148, 
 54, 247, 196, 114, 
 167, 96, 42, 230, 
 174, 233, 207, 151, 
 228, 125, 69, 99, 
 50, 175, 21, 109, 
 50, 222, 102, 176, 
 201, 120, 155, 193, 
 33, 45, 90, 224, 
 117, 179, 238, 18, 
 20, 178, 125, 28, 
 117, 204, 170, 247, 
 163, 220, 227, 223, 
 164, 230, 194, 215, 
 145, 24, 70, 48, 
 171, 30, 102, 221, 
 179, 148, 224, 89, 
 87, 93, 242, 230, 
 49, 121, 8, 115, 
 161, 179, 10, 254, 
 25, 230, 150, 49, 
 57, 71, 235, 133, 
 196, 26, 173, 247, 
 129, 75, 252, 115, 
 204, 80, 233, 207, 
 49, 111, 184, 63, 
 135, 17, 76, 206, 
 219, 178, 85, 250, 
 243, 247, 146, 84, 
 207, 152, 177, 213, 
 243, 182, 20, 153, 
 158, 156, 61, 13, 
 252, 115, 75, 153, 
 27, 206, 44, 119, 
 167, 39, 187, 54, 
 150, 59, 15, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len34_anagram0 = {
  LengthAndAnagram(34, 0), // seq_bit_len_and_anagram
  74, // num_chords
  kmap5_Word_len34_anagram0_chords, // chords
  kmap5_Word_len34_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len34_anagram1_chords[12] = {
 ChordData({0, 4, 211}), ChordData({2, 5, 19}), ChordData({18, 4, 25}), ChordData({20, 0, 89}), 
 ChordData({48, 44, 18}), ChordData({50, 13, 9}), ChordData({52, 4, 193}), ChordData({52, 13, 16}), 
 ChordData({54, 12, 16}), ChordData({128, 4, 27}), ChordData({130, 1, 27}), ChordData({164, 4, 146}), 
};

uint8_t const kmap5_Word_len34_anagram1_seqs[51] = {
 248, 247, 84, 202, 
 253, 222, 116, 143, 
 103, 61, 239, 253, 
 232, 186, 173, 197, 
 122, 60, 251, 229, 
 92, 234, 115, 3, 
 255, 204, 247, 254, 
 35, 75, 111, 206, 
 251, 208, 253, 20, 
 252, 93, 99, 234, 
 237, 111, 217, 237, 
 224, 77, 42, 223, 
 127, 73, 185, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len34_anagram1 = {
  LengthAndAnagram(34, 1), // seq_bit_len_and_anagram
  12, // num_chords
  kmap5_Word_len34_anagram1_chords, // chords
  kmap5_Word_len34_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len34_anagram2_chords[2] = {
 ChordData({38, 1, 0}), ChordData({48, 5, 136}), 
};

uint8_t const kmap5_Word_len34_anagram2_seqs[9] = {
 124, 199, 247, 252, 
 208, 43, 172, 15, 
 13, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len34_anagram2 = {
  LengthAndAnagram(34, 2), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len34_anagram2_chords, // chords
  kmap5_Word_len34_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len34_anagram4_chords[1] = {
 ChordData({20, 4, 25}), 
};

uint8_t const kmap5_Word_len34_anagram4_seqs[5] = {
 205, 234, 219, 63, 
 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len34_anagram4 = {
  LengthAndAnagram(34, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len34_anagram4_chords, // chords
  kmap5_Word_len34_anagram4_seqs, // sequences
};

ChordData const kmap5_Word_len35_anagram0_chords[67] = {
 ChordData({0, 68, 2}), ChordData({2, 13, 144}), ChordData({6, 4, 19}), ChordData({16, 4, 217}), 
 ChordData({16, 72, 27}), ChordData({18, 4, 89}), ChordData({18, 8, 27}), ChordData({18, 12, 137}), 
 ChordData({18, 44, 130}), ChordData({18, 72, 25}), ChordData({20, 68, 81}), ChordData({22, 0, 25}), 
 ChordData({22, 0, 27}), ChordData({22, 0, 131}), ChordData({22, 4, 147}), ChordData({32, 4, 18}), 
 ChordData({32, 12, 210}), ChordData({32, 44, 193}), ChordData({34, 0, 217}), ChordData({34, 8, 193}), 
 ChordData({38, 12, 137}), ChordData({38, 13, 10}), ChordData({48, 4, 9}), ChordData({48, 5, 155}), 
 ChordData({48, 9, 88}), ChordData({48, 64, 202}), ChordData({48, 69, 136}), ChordData({48, 101, 17}), 
 ChordData({50, 5, 19}), ChordData({50, 5, 25}), ChordData({50, 13, 193}), ChordData({50, 64, 154}), 
 ChordData({52, 4, 147}), ChordData({52, 8, 128}), ChordData({52, 36, 129}), ChordData({52, 68, 136}), 
 ChordData({54, 0, 210}), ChordData({54, 4, 146}), ChordData({54, 12, 144}), ChordData({128, 68, 152}), 
 ChordData({128, 72, 19}), ChordData({130, 68, 26}), ChordData({132, 36, 18}), ChordData({134, 0, 19}), 
 ChordData({134, 0, 90}), ChordData({134, 44, 10}), ChordData({144, 72, 90}), ChordData({146, 4, 9}), 
 ChordData({146, 4, 67}), ChordData({146, 4, 195}), ChordData({148, 0, 19}), ChordData({148, 0, 216}), 
 ChordData({148, 4, 19}), ChordData({148, 32, 208}), ChordData({160, 5, 210}), ChordData({162, 1, 11}), 
 ChordData({162, 5, 9}), ChordData({162, 72, 72}), ChordData({166, 12, 136}), ChordData({178, 5, 9}), 
 ChordData({178, 5, 16}), ChordData({178, 8, 147}), ChordData({178, 13, 17}), ChordData({180, 0, 19}), 
 ChordData({180, 68, 144}), ChordData({182, 8, 80}), ChordData({182, 33, 24}), 
};

uint8_t const kmap5_Word_len35_anagram0_seqs[294] = {
 129, 127, 30, 121, 
 236, 62, 14, 205, 
 47, 126, 123, 156, 
 43, 111, 95, 133, 
 254, 28, 140, 235, 
 104, 189, 219, 87, 
 25, 235, 141, 226, 
 58, 90, 207, 52, 
 113, 244, 207, 124, 
 28, 100, 111, 10, 
 62, 111, 28, 117, 
 176, 52, 239, 159, 
 71, 207, 219, 214, 
 183, 198, 105, 99, 
 61, 131, 26, 13, 
 206, 173, 27, 13, 
 254, 249, 17, 235, 
 62, 150, 220, 11, 
 86, 250, 61, 246, 
 244, 177, 10, 15, 
 94, 229, 70, 229, 
 38, 86, 170, 210, 
 232, 111, 180, 70, 
 252, 216, 126, 160, 
 254, 157, 181, 254, 
 121, 141, 247, 10, 
 201, 209, 34, 86, 
 232, 21, 23, 170, 
 86, 52, 111, 133, 
 244, 26, 194, 87, 
 200, 206, 139, 3, 
 127, 125, 231, 209, 
 51, 220, 63, 119, 
 150, 27, 238, 201, 
 90, 168, 206, 150, 
 104, 114, 191, 127, 
 110, 181, 96, 65, 
 242, 83, 99, 223, 
 251, 90, 13, 214, 
 240, 36, 184, 211, 
 247, 228, 53, 205, 
 247, 84, 114, 191, 
 243, 61, 153, 7, 
 207, 13, 175, 151, 
 49, 119, 19, 200, 
 13, 163, 191, 229, 
 183, 182, 249, 200, 
 218, 78, 238, 92, 
 41, 165, 102, 147, 
 17, 100, 31, 219, 
 164, 74, 169, 97, 
 51, 250, 239, 172, 
 55, 169, 47, 146, 
 56, 127, 78, 193, 
 33, 250, 115, 219, 
 108, 222, 43, 155, 
 87, 82, 213, 132, 
 153, 205, 251, 103, 
 30, 60, 197, 141, 
 65, 74, 145, 223, 
 178, 171, 138, 55, 
 169, 93, 86, 189, 
 31, 13, 195, 141, 
 76, 106, 123, 110, 
 104, 82, 213, 48, 
 111, 254, 204, 67, 
 231, 194, 121, 206, 
 148, 56, 87, 118, 
 207, 229, 206, 153, 
 79, 188, 236, 189, 
 253, 111, 22, 170, 
 110, 107, 110, 178, 
 138, 122, 32, 235, 
 115, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len35_anagram0 = {
  LengthAndAnagram(35, 0), // seq_bit_len_and_anagram
  67, // num_chords
  kmap5_Word_len35_anagram0_chords, // chords
  kmap5_Word_len35_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len35_anagram1_chords[10] = {
 ChordData({2, 12, 147}), ChordData({18, 4, 89}), ChordData({36, 4, 83}), ChordData({48, 5, 145}), 
 ChordData({48, 37, 138}), ChordData({52, 72, 0}), ChordData({134, 0, 72}), ChordData({146, 4, 25}), 
 ChordData({176, 8, 9}), ChordData({180, 64, 64}), 
};

uint8_t const kmap5_Word_len35_anagram1_seqs[44] = {
 113, 104, 238, 183, 
 92, 203, 200, 189, 
 158, 212, 254, 246, 
 241, 224, 254, 185, 
 171, 100, 16, 178, 
 87, 104, 199, 222, 
 33, 56, 240, 45, 
 71, 36, 117, 206, 
 251, 55, 169, 49, 
 163, 245, 106, 148, 
 218, 90, 138, 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len35_anagram1 = {
  LengthAndAnagram(35, 1), // seq_bit_len_and_anagram
  10, // num_chords
  kmap5_Word_len35_anagram1_chords, // chords
  kmap5_Word_len35_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len35_anagram2_chords[1] = {
 ChordData({146, 0, 11}), 
};

uint8_t const kmap5_Word_len35_anagram2_seqs[5] = {
 152, 122, 163, 214, 
 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len35_anagram2 = {
  LengthAndAnagram(35, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len35_anagram2_chords, // chords
  kmap5_Word_len35_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len36_anagram0_chords[54] = {
 ChordData({0, 68, 27}), ChordData({0, 77, 18}), ChordData({2, 5, 210}), ChordData({2, 100, 18}), 
 ChordData({2, 100, 74}), ChordData({6, 36, 210}), ChordData({16, 4, 90}), ChordData({16, 36, 19}), 
 ChordData({16, 68, 155}), ChordData({18, 36, 19}), ChordData({18, 36, 139}), ChordData({18, 65, 27}), 
 ChordData({20, 12, 17}), ChordData({20, 12, 25}), ChordData({20, 64, 9}), ChordData({22, 64, 89}), 
 ChordData({34, 12, 19}), ChordData({34, 12, 136}), ChordData({34, 64, 91}), ChordData({34, 64, 154}), 
 ChordData({34, 68, 147}), ChordData({36, 40, 18}), ChordData({38, 76, 128}), ChordData({48, 4, 131}), 
 ChordData({48, 37, 138}), ChordData({50, 0, 73}), ChordData({50, 8, 73}), ChordData({50, 69, 73}), 
 ChordData({52, 5, 88}), ChordData({52, 72, 192}), ChordData({54, 5, 144}), ChordData({128, 65, 146}), 
 ChordData({130, 4, 138}), ChordData({130, 5, 130}), ChordData({130, 77, 136}), ChordData({132, 12, 8}), 
 ChordData({132, 13, 145}), ChordData({132, 65, 16}), ChordData({144, 36, 83}), ChordData({144, 36, 131}), 
 ChordData({150, 0, 81}), ChordData({150, 4, 137}), ChordData({150, 4, 154}), ChordData({160, 32, 73}), 
 ChordData({160, 37, 129}), ChordData({160, 65, 10}), ChordData({162, 37, 2}), ChordData({164, 12, 144}), 
 ChordData({164, 72, 10}), ChordData({176, 5, 130}), ChordData({176, 8, 25}), ChordData({178, 0, 90}), 
 ChordData({178, 8, 80}), ChordData({182, 44, 16}), 
};

uint8_t const kmap5_Word_len36_anagram0_seqs[243] = {
 192, 239, 190, 94, 
 249, 64, 17, 248, 
 13, 72, 47, 50, 
 93, 201, 239, 32, 
 251, 13, 242, 26, 
 128, 65, 214, 88, 
 41, 131, 79, 106, 
 180, 200, 111, 137, 
 236, 247, 241, 188, 
 31, 192, 31, 173, 
 247, 139, 108, 206, 
 120, 103, 100, 58, 
 248, 52, 193, 122, 
 211, 149, 237, 247, 
 163, 207, 219, 188, 
 241, 213, 122, 193, 
 205, 26, 172, 215, 
 214, 50, 193, 122, 
 143, 55, 220, 92, 
 249, 84, 227, 104, 
 141, 163, 161, 202, 
 109, 57, 90, 168, 
 206, 150, 133, 234, 
 211, 92, 201, 199, 
 186, 141, 149, 237, 
 137, 38, 212, 136, 
 79, 88, 233, 207, 
 200, 158, 200, 10, 
 61, 42, 55, 87, 
 207, 98, 149, 185, 
 225, 28, 44, 3, 
 245, 207, 237, 69, 
 172, 208, 43, 133, 
 170, 93, 208, 60, 
 252, 126, 199, 196, 
 39, 168, 203, 13, 
 248, 154, 58, 248, 
 148, 93, 55, 56, 
 79, 241, 117, 186, 
 164, 192, 127, 252, 
 130, 169, 141, 254, 
 186, 220, 200, 183, 
 205, 14, 12, 185, 
 200, 44, 183, 143, 
 44, 49, 233, 207, 
 45, 229, 188, 147, 
 219, 242, 172, 55, 
 79, 45, 23, 77, 
 63, 202, 179, 172, 
 114, 169, 79, 199, 
 178, 66, 134, 169, 
 93, 86, 13, 60, 
 178, 193, 135, 249, 
 173, 109, 114, 79, 
 152, 177, 101, 213, 
 128, 73, 228, 135, 
 213, 60, 231, 141, 
 169, 183, 198, 186, 
 50, 169, 107, 241, 
 114, 57, 219, 155, 
 61, 55, 185, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len36_anagram0 = {
  LengthAndAnagram(36, 0), // seq_bit_len_and_anagram
  54, // num_chords
  kmap5_Word_len36_anagram0_chords, // chords
  kmap5_Word_len36_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len36_anagram1_chords[9] = {
 ChordData({2, 4, 67}), ChordData({2, 5, 147}), ChordData({16, 0, 139}), ChordData({16, 4, 83}), 
 ChordData({48, 5, 25}), ChordData({50, 12, 9}), ChordData({130, 0, 202}), ChordData({148, 4, 19}), 
 ChordData({148, 8, 11}), 
};

uint8_t const kmap5_Word_len36_anagram1_seqs[41] = {
 114, 127, 35, 55, 
 216, 61, 14, 205, 
 149, 6, 161, 137, 
 172, 39, 198, 245, 
 253, 150, 176, 254, 
 190, 158, 205, 115, 
 227, 211, 143, 152, 
 68, 35, 147, 138, 
 185, 45, 247, 207, 
 152, 177, 249, 172, 
 7, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len36_anagram1 = {
  LengthAndAnagram(36, 1), // seq_bit_len_and_anagram
  9, // num_chords
  kmap5_Word_len36_anagram1_chords, // chords
  kmap5_Word_len36_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len37_anagram0_chords[66] = {
 ChordData({0, 69, 128}), ChordData({2, 8, 65}), ChordData({2, 8, 83}), ChordData({2, 36, 91}), 
 ChordData({2, 76, 130}), ChordData({4, 44, 18}), ChordData({6, 4, 147}), ChordData({6, 5, 2}), 
 ChordData({16, 100, 147}), ChordData({16, 108, 3}), ChordData({18, 4, 210}), ChordData({18, 5, 18}), 
 ChordData({18, 5, 75}), ChordData({18, 5, 82}), ChordData({18, 41, 10}), ChordData({18, 76, 1}), 
 ChordData({20, 12, 66}), ChordData({22, 8, 137}), ChordData({22, 12, 146}), ChordData({22, 36, 65}), 
 ChordData({22, 36, 81}), ChordData({22, 68, 19}), ChordData({22, 68, 138}), ChordData({34, 1, 211}), 
 ChordData({38, 8, 147}), ChordData({48, 0, 83}), ChordData({48, 9, 26}), ChordData({48, 13, 26}), 
 ChordData({48, 68, 129}), ChordData({50, 1, 138}), ChordData({50, 5, 89}), ChordData({50, 8, 152}), 
 ChordData({50, 12, 25}), ChordData({50, 36, 11}), ChordData({50, 36, 26}), ChordData({50, 76, 81}), 
 ChordData({54, 0, 25}), ChordData({54, 1, 130}), ChordData({54, 4, 147}), ChordData({54, 4, 200}), 
 ChordData({128, 32, 154}), ChordData({130, 64, 11}), ChordData({130, 68, 25}), ChordData({130, 69, 144}), 
 ChordData({134, 4, 19}), ChordData({134, 12, 146}), ChordData({144, 4, 82}), ChordData({144, 72, 26}), 
 ChordData({144, 100, 138}), ChordData({146, 0, 19}), ChordData({146, 0, 203}), ChordData({146, 72, 72}), 
 ChordData({148, 8, 11}), ChordData({150, 8, 25}), ChordData({160, 0, 91}), ChordData({160, 69, 192}), 
 ChordData({162, 0, 74}), ChordData({162, 0, 155}), ChordData({166, 0, 210}), ChordData({176, 8, 153}), 
 ChordData({178, 64, 27}), ChordData({178, 64, 194}), ChordData({178, 64, 201}), ChordData({178, 68, 137}), 
 ChordData({180, 8, 145}), ChordData({182, 13, 24}), 
};

uint8_t const kmap5_Word_len37_anagram0_seqs[306] = {
 124, 199, 63, 95, 
 72, 110, 98, 165, 
 63, 227, 206, 13, 
 142, 68, 100, 59, 
 114, 243, 202, 3, 
 67, 52, 31, 27, 
 251, 141, 143, 101, 
 219, 199, 27, 124, 
 226, 219, 227, 116, 
 131, 248, 199, 28, 
 246, 137, 143, 127, 
 199, 12, 240, 224, 
 22, 25, 124, 119, 
 221, 224, 99, 217, 
 189, 224, 232, 159, 
 229, 113, 167, 27, 
 52, 143, 108, 176, 
 104, 157, 24, 29, 
 230, 207, 210, 30, 
 29, 31, 101, 98, 
 35, 71, 235, 57, 
 182, 217, 193, 39, 
 230, 246, 55, 55, 
 114, 204, 251, 109, 
 228, 154, 195, 252, 
 237, 224, 183, 102, 
 13, 3, 2, 175, 
 114, 211, 149, 177, 
 210, 77, 163, 82, 
 110, 43, 94, 93, 
 59, 122, 161, 21, 
 75, 30, 122, 227, 
 107, 249, 193, 133, 
 234, 159, 71, 59, 
 170, 86, 180, 12, 
 212, 191, 186, 6, 
 175, 156, 117, 200, 
 250, 187, 127, 195, 
 249, 235, 49, 235, 
 13, 178, 186, 59, 
 248, 234, 15, 156, 
 247, 70, 60, 122, 
 222, 173, 237, 58, 
 50, 104, 122, 50, 
 62, 77, 191, 127, 
 110, 214, 81, 169, 
 244, 60, 120, 50, 
 213, 18, 83, 195, 
 220, 164, 222, 126, 
 152, 155, 84, 190, 
 163, 220, 9, 143, 
 223, 30, 231, 114, 
 219, 38, 104, 226, 
 211, 35, 90, 36, 
 183, 92, 99, 198, 
 104, 13, 236, 137, 
 18, 176, 245, 188, 
 59, 151, 91, 26, 
 116, 86, 153, 212, 
 48, 209, 42, 147, 
 138, 25, 91, 170, 
 245, 218, 102, 28, 
 181, 30, 166, 202, 
 109, 197, 227, 67, 
 86, 72, 47, 152, 
 42, 56, 89, 5, 
 188, 42, 222, 164, 
 182, 20, 153, 158, 
 74, 46, 169, 234, 
 217, 59, 122, 155, 
 161, 162, 131, 105, 
 112, 178, 74, 161, 
 106, 185, 73, 117, 
 161, 250, 55, 169, 
 205, 183, 73, 174, 
 49, 23, 190, 78, 
 65, 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len37_anagram0 = {
  LengthAndAnagram(37, 0), // seq_bit_len_and_anagram
  66, // num_chords
  kmap5_Word_len37_anagram0_chords, // chords
  kmap5_Word_len37_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len37_anagram1_chords[5] = {
 ChordData({18, 12, 138}), ChordData({22, 0, 154}), ChordData({22, 4, 138}), ChordData({52, 4, 208}), 
 ChordData({180, 64, 18}), 
};

uint8_t const kmap5_Word_len37_anagram1_seqs[24] = {
 124, 52, 104, 240, 
 181, 237, 40, 78, 
 35, 127, 107, 52, 
 175, 104, 113, 251, 
 253, 158, 220, 54, 
 209, 161, 174, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len37_anagram1 = {
  LengthAndAnagram(37, 1), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len37_anagram1_chords, // chords
  kmap5_Word_len37_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len37_anagram2_chords[1] = {
 ChordData({18, 68, 11}), 
};

uint8_t const kmap5_Word_len37_anagram2_seqs[5] = {
 248, 26, 38, 252, 
 25, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len37_anagram2 = {
  LengthAndAnagram(37, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len37_anagram2_chords, // chords
  kmap5_Word_len37_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len37_anagram3_chords[1] = {
 ChordData({48, 5, 17}), 
};

uint8_t const kmap5_Word_len37_anagram3_seqs[5] = {
 15, 225, 26, 254, 
 25, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len37_anagram3 = {
  LengthAndAnagram(37, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len37_anagram3_chords, // chords
  kmap5_Word_len37_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len38_anagram0_chords[38] = {
 ChordData({2, 5, 75}), ChordData({2, 44, 75}), ChordData({2, 44, 83}), ChordData({6, 4, 154}), 
 ChordData({18, 1, 11}), ChordData({18, 12, 26}), ChordData({18, 12, 27}), ChordData({18, 32, 91}), 
 ChordData({18, 37, 90}), ChordData({18, 44, 74}), ChordData({32, 108, 16}), ChordData({38, 4, 153}), 
 ChordData({48, 5, 81}), ChordData({48, 36, 81}), ChordData({48, 65, 153}), ChordData({48, 76, 25}), 
 ChordData({52, 4, 75}), ChordData({52, 13, 129}), ChordData({54, 4, 17}), ChordData({54, 9, 144}), 
 ChordData({54, 36, 193}), ChordData({54, 68, 131}), ChordData({130, 76, 72}), ChordData({134, 12, 10}), 
 ChordData({134, 12, 25}), ChordData({144, 12, 73}), ChordData({144, 96, 209}), ChordData({146, 0, 155}), 
 ChordData({146, 64, 19}), ChordData({146, 65, 11}), ChordData({148, 1, 80}), ChordData({160, 36, 195}), 
 ChordData({162, 12, 3}), ChordData({162, 12, 194}), ChordData({162, 69, 72}), ChordData({164, 1, 17}), 
 ChordData({164, 5, 192}), ChordData({178, 9, 11}), 
};

uint8_t const kmap5_Word_len38_anagram0_seqs[181] = {
 221, 235, 189, 220, 
 96, 124, 100, 163, 
 35, 135, 108, 71, 
 46, 190, 180, 29, 
 197, 105, 79, 238, 
 186, 193, 177, 30, 
 255, 209, 59, 248, 
 26, 255, 188, 58, 
 87, 74, 169, 199, 
 124, 131, 221, 190, 
 34, 27, 113, 52, 
 178, 215, 145, 200, 
 179, 95, 238, 55, 
 244, 59, 68, 243, 
 122, 221, 86, 185, 
 253, 243, 49, 203, 
 215, 173, 210, 173, 
 11, 85, 235, 125, 
 224, 172, 87, 215, 
 82, 123, 185, 87, 
 52, 103, 232, 251, 
 158, 252, 119, 59, 
 125, 61, 183, 29, 
 110, 200, 208, 150, 
 251, 158, 70, 88, 
 168, 141, 6, 255, 
 252, 33, 142, 200, 
 164, 98, 198, 246, 
 58, 169, 19, 91, 
 238, 189, 30, 31, 
 255, 206, 146, 122, 
 108, 45, 44, 41, 
 152, 140, 183, 169, 
 131, 97, 214, 120, 
 185, 37, 166, 118, 
 19, 172, 215, 54, 
 59, 139, 228, 178, 
 164, 196, 175, 114, 
 95, 47, 227, 223, 
 96, 124, 26, 156, 
 172, 18, 230, 161, 
 166, 140, 180, 205, 
 203, 190, 118, 221, 
 247, 149, 178, 10, 
 38, 212, 185, 225, 
 12, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len38_anagram0 = {
  LengthAndAnagram(38, 0), // seq_bit_len_and_anagram
  38, // num_chords
  kmap5_Word_len38_anagram0_chords, // chords
  kmap5_Word_len38_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len38_anagram1_chords[5] = {
 ChordData({18, 32, 91}), ChordData({22, 0, 89}), ChordData({48, 5, 26}), ChordData({54, 0, 147}), 
 ChordData({178, 8, 137}), 
};

uint8_t const kmap5_Word_len38_anagram1_seqs[24] = {
 82, 234, 49, 203, 
 136, 245, 188, 109, 
 71, 220, 237, 195, 
 125, 69, 163, 201, 
 253, 206, 149, 230, 
 146, 234, 77, 42, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len38_anagram1 = {
  LengthAndAnagram(38, 1), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len38_anagram1_chords, // chords
  kmap5_Word_len38_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len38_anagram2_chords[1] = {
 ChordData({50, 8, 9}), 
};

uint8_t const kmap5_Word_len38_anagram2_seqs[5] = {
 163, 87, 231, 134, 
 51, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len38_anagram2 = {
  LengthAndAnagram(38, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len38_anagram2_chords, // chords
  kmap5_Word_len38_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len39_anagram0_chords[35] = {
 ChordData({2, 12, 210}), ChordData({2, 65, 0}), ChordData({4, 44, 83}), ChordData({18, 5, 129}), 
 ChordData({18, 36, 18}), ChordData({18, 40, 83}), ChordData({18, 65, 25}), ChordData({20, 1, 26}), 
 ChordData({22, 0, 89}), ChordData({22, 13, 144}), ChordData({34, 41, 81}), ChordData({36, 4, 81}), 
 ChordData({38, 8, 131}), ChordData({48, 77, 9}), ChordData({50, 4, 145}), ChordData({50, 77, 9}), 
 ChordData({52, 72, 18}), ChordData({54, 5, 19}), ChordData({54, 12, 128}), ChordData({54, 76, 129}), 
 ChordData({128, 12, 91}), ChordData({128, 68, 146}), ChordData({130, 36, 88}), ChordData({132, 4, 16}), 
 ChordData({132, 40, 90}), ChordData({144, 1, 26}), ChordData({144, 76, 18}), ChordData({148, 12, 19}), 
 ChordData({148, 36, 91}), ChordData({150, 0, 202}), ChordData({162, 1, 74}), ChordData({162, 45, 145}), 
 ChordData({164, 4, 146}), ChordData({178, 1, 26}), ChordData({178, 13, 81}), 
};

uint8_t const kmap5_Word_len39_anagram0_seqs[171] = {
 50, 113, 232, 151, 
 202, 48, 93, 231, 
 181, 158, 148, 177, 
 253, 177, 242, 187, 
 110, 104, 254, 204, 
 198, 251, 139, 172, 
 68, 230, 56, 114, 
 91, 134, 233, 58, 
 175, 245, 218, 186, 
 243, 90, 209, 205, 
 43, 35, 103, 189, 
 143, 141, 166, 27, 
 47, 127, 117, 139, 
 35, 236, 91, 251, 
 253, 171, 18, 43, 
 221, 52, 26, 252, 
 192, 189, 222, 67, 
 211, 156, 247, 175, 
 174, 227, 67, 157, 
 171, 193, 124, 48, 
 58, 246, 222, 238, 
 251, 29, 252, 243, 
 115, 63, 244, 61, 
 249, 99, 163, 185, 
 26, 252, 114, 155, 
 154, 177, 228, 49, 
 41, 247, 67, 242, 
 236, 119, 71, 82, 
 219, 102, 255, 61, 
 149, 82, 198, 198, 
 82, 75, 76, 237, 
 188, 86, 116, 112, 
 76, 220, 199, 242, 
 28, 91, 238, 111, 
 217, 94, 175, 100, 
 41, 54, 168, 81, 
 202, 164, 98, 106, 
 87, 101, 82, 159, 
 96, 238, 28, 139, 
 109, 179, 255, 158, 
 74, 76, 237, 6, 
 214, 117, 247, 92, 
 238, 156, 5, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len39_anagram0 = {
  LengthAndAnagram(39, 0), // seq_bit_len_and_anagram
  35, // num_chords
  kmap5_Word_len39_anagram0_chords, // chords
  kmap5_Word_len39_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len39_anagram1_chords[3] = {
 ChordData({16, 68, 83}), ChordData({50, 1, 25}), ChordData({146, 0, 75}), 
};

uint8_t const kmap5_Word_len39_anagram1_seqs[15] = {
 165, 229, 188, 225, 
 203, 174, 174, 206, 
 213, 53, 166, 202, 
 200, 89, 15, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len39_anagram1 = {
  LengthAndAnagram(39, 1), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len39_anagram1_chords, // chords
  kmap5_Word_len39_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len40_anagram0_chords[29] = {
 ChordData({0, 4, 72}), ChordData({6, 12, 146}), ChordData({16, 0, 80}), ChordData({20, 68, 19}), 
 ChordData({22, 0, 154}), ChordData({22, 4, 11}), ChordData({34, 68, 155}), ChordData({36, 77, 18}), 
 ChordData({38, 4, 19}), ChordData({48, 4, 89}), ChordData({50, 4, 209}), ChordData({50, 8, 194}), 
 ChordData({50, 13, 129}), ChordData({50, 65, 25}), ChordData({54, 0, 82}), ChordData({128, 4, 9}), 
 ChordData({130, 4, 89}), ChordData({130, 4, 91}), ChordData({146, 68, 27}), ChordData({146, 68, 67}), 
 ChordData({148, 12, 75}), ChordData({150, 32, 147}), ChordData({150, 64, 88}), ChordData({160, 12, 90}), 
 ChordData({162, 36, 19}), ChordData({178, 0, 75}), ChordData({178, 8, 11}), ChordData({182, 8, 24}), 
 ChordData({182, 9, 26}), 
};

uint8_t const kmap5_Word_len40_anagram0_seqs[145] = {
 188, 242, 207, 11, 
 255, 109, 39, 254, 
 14, 149, 107, 73, 
 170, 55, 169, 193, 
 109, 141, 127, 14, 
 6, 53, 239, 88, 
 209, 175, 55, 56, 
 237, 207, 133, 234, 
 235, 205, 149, 253, 
 99, 17, 248, 13, 
 191, 253, 220, 254, 
 150, 107, 185, 175, 
 251, 122, 67, 84, 
 229, 246, 207, 6, 
 33, 85, 25, 206, 
 100, 56, 55, 241, 
 207, 163, 112, 29, 
 198, 122, 82, 123, 
 193, 157, 222, 188, 
 242, 207, 31, 159, 
 183, 175, 50, 55, 
 169, 152, 42, 183, 
 63, 122, 152, 185, 
 97, 244, 207, 97, 
 68, 18, 231, 207, 
 152, 177, 89, 229, 
 207, 204, 52, 152, 
 237, 188, 193, 109, 
 45, 50, 169, 175, 
 169, 101, 204, 42, 
 95, 143, 229, 206, 
 149, 152, 42, 55, 
 87, 207, 152, 202, 
 89, 199, 122, 60, 
 231, 157, 130, 169, 
 107, 76, 168, 83, 
 208, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len40_anagram0 = {
  LengthAndAnagram(40, 0), // seq_bit_len_and_anagram
  29, // num_chords
  kmap5_Word_len40_anagram0_chords, // chords
  kmap5_Word_len40_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len40_anagram1_chords[2] = {
 ChordData({54, 8, 192}), ChordData({132, 12, 26}), 
};

uint8_t const kmap5_Word_len40_anagram1_seqs[10] = {
 19, 91, 37, 25, 
 206, 143, 152, 177, 
 189, 150, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len40_anagram1 = {
  LengthAndAnagram(40, 1), // seq_bit_len_and_anagram
  2, // num_chords
  kmap5_Word_len40_anagram1_chords, // chords
  kmap5_Word_len40_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len40_anagram2_chords[1] = {
 ChordData({22, 4, 19}), 
};

uint8_t const kmap5_Word_len40_anagram2_seqs[5] = {
 223, 218, 26, 231, 
 207, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len40_anagram2 = {
  LengthAndAnagram(40, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len40_anagram2_chords, // chords
  kmap5_Word_len40_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len41_anagram0_chords[37] = {
 ChordData({6, 76, 146}), ChordData({16, 44, 11}), ChordData({18, 1, 75}), ChordData({18, 76, 210}), 
 ChordData({20, 4, 216}), ChordData({20, 76, 25}), ChordData({22, 4, 210}), ChordData({22, 12, 153}), 
 ChordData({22, 36, 144}), ChordData({22, 64, 202}), ChordData({32, 4, 154}), ChordData({32, 45, 8}), 
 ChordData({50, 8, 89}), ChordData({50, 76, 147}), ChordData({50, 96, 139}), ChordData({54, 5, 129}), 
 ChordData({54, 33, 80}), ChordData({128, 64, 1}), ChordData({128, 69, 89}), ChordData({134, 100, 82}), 
 ChordData({146, 12, 146}), ChordData({148, 8, 139}), ChordData({148, 40, 8}), ChordData({148, 64, 90}), 
 ChordData({150, 8, 88}), ChordData({150, 12, 131}), ChordData({150, 12, 138}), ChordData({150, 72, 9}), 
 ChordData({160, 4, 147}), ChordData({160, 12, 155}), ChordData({162, 0, 202}), ChordData({162, 8, 27}), 
 ChordData({166, 8, 0}), ChordData({176, 72, 89}), ChordData({178, 64, 210}), ChordData({180, 8, 24}), 
 ChordData({182, 4, 25}), 
};

uint8_t const kmap5_Word_len41_anagram0_seqs[190] = {
 173, 220, 143, 19, 
 158, 254, 238, 145, 
 69, 235, 9, 142, 
 245, 166, 27, 12, 
 35, 72, 63, 209, 
 203, 131, 127, 123, 
 181, 56, 184, 253, 
 94, 180, 158, 165, 
 25, 231, 137, 202, 
 246, 75, 243, 209, 
 122, 205, 59, 141, 
 121, 159, 194, 8, 
 78, 163, 81, 243, 
 224, 175, 245, 183, 
 228, 89, 237, 186, 
 248, 58, 42, 183, 
 53, 90, 239, 3, 
 184, 241, 134, 243, 
 25, 153, 78, 161, 
 234, 222, 95, 111, 
 186, 74, 235, 174, 
 110, 63, 194, 248, 
 227, 147, 15, 124, 
 242, 114, 175, 93, 
 110, 8, 165, 52, 
 150, 59, 143, 25, 
 163, 23, 231, 9, 
 51, 54, 114, 180, 
 94, 99, 214, 140, 
 214, 84, 204, 93, 
 75, 75, 13, 205, 
 27, 71, 100, 82, 
 49, 99, 163, 193, 
 63, 99, 198, 70, 
 243, 138, 158, 224, 
 216, 242, 172, 135, 
 79, 88, 233, 47, 
 151, 75, 170, 122, 
 191, 37, 166, 34, 
 85, 153, 84, 204, 
 24, 171, 206, 149, 
 253, 100, 252, 45, 
 122, 111, 29, 173, 
 33, 171, 132, 17, 
 164, 148, 186, 230, 
 53, 57, 199, 222, 
 187, 110, 245, 254, 
 38, 21, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len41_anagram0 = {
  LengthAndAnagram(41, 0), // seq_bit_len_and_anagram
  37, // num_chords
  kmap5_Word_len41_anagram0_chords, // chords
  kmap5_Word_len41_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len41_anagram1_chords[3] = {
 ChordData({34, 13, 24}), ChordData({130, 68, 27}), ChordData({178, 8, 11}), 
};

uint8_t const kmap5_Word_len41_anagram1_seqs[16] = {
 60, 55, 11, 71, 
 231, 49, 245, 246, 
 195, 224, 97, 42, 
 103, 189, 73, 5, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len41_anagram1 = {
  LengthAndAnagram(41, 1), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len41_anagram1_chords, // chords
  kmap5_Word_len41_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len42_anagram0_chords[32] = {
 ChordData({2, 5, 147}), ChordData({2, 65, 2}), ChordData({2, 65, 128}), ChordData({4, 65, 130}), 
 ChordData({18, 44, 3}), ChordData({18, 65, 26}), ChordData({22, 8, 155}), ChordData({22, 36, 73}), 
 ChordData({34, 65, 131}), ChordData({34, 69, 17}), ChordData({36, 1, 72}), ChordData({38, 4, 147}), 
 ChordData({48, 12, 131}), ChordData({48, 13, 129}), ChordData({50, 12, 27}), ChordData({50, 13, 80}), 
 ChordData({52, 8, 201}), ChordData({128, 1, 64}), ChordData({134, 12, 90}), ChordData({144, 4, 27}), 
 ChordData({146, 4, 139}), ChordData({146, 65, 9}), ChordData({150, 0, 27}), ChordData({150, 0, 83}), 
 ChordData({150, 1, 88}), ChordData({150, 8, 82}), ChordData({160, 37, 153}), ChordData({166, 1, 0}), 
 ChordData({166, 8, 82}), ChordData({178, 8, 153}), ChordData({180, 5, 136}), ChordData({182, 0, 27}), 
};

uint8_t const kmap5_Word_len42_anagram0_seqs[168] = {
 191, 55, 221, 224, 
 60, 133, 233, 58, 
 175, 21, 29, 166, 
 235, 6, 43, 93, 
 32, 190, 241, 29, 
 143, 241, 143, 57, 
 254, 13, 134, 233, 
 58, 175, 21, 109, 
 80, 243, 78, 180, 
 30, 47, 231, 198, 
 94, 199, 97, 186, 
 110, 176, 210, 241, 
 31, 190, 219, 58, 
 199, 43, 47, 60, 
 228, 91, 251, 189, 
 193, 74, 191, 143, 
 88, 99, 165, 63, 
 127, 124, 130, 31, 
 255, 204, 249, 188, 
 163, 191, 229, 67, 
 184, 22, 25, 206, 
 82, 91, 35, 71, 
 235, 241, 29, 159, 
 188, 240, 130, 25, 
 219, 239, 72, 42, 
 166, 162, 245, 246, 
 207, 6, 225, 220, 
 223, 164, 6, 119, 
 163, 115, 147, 202, 
 183, 29, 69, 95, 
 234, 186, 165, 204, 
 229, 150, 109, 179, 
 179, 200, 164, 98, 
 198, 182, 25, 71, 
 156, 123, 44, 97, 
 234, 19, 15, 249, 
 198, 15, 159, 82, 
 198, 150, 50, 53, 
 174, 185, 164, 122, 
 147, 218, 251, 33, 
 185, 79, 53, 166, 
 222, 78, 95, 207, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len42_anagram0 = {
  LengthAndAnagram(42, 0), // seq_bit_len_and_anagram
  32, // num_chords
  kmap5_Word_len42_anagram0_chords, // chords
  kmap5_Word_len42_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len42_anagram1_chords[1] = {
 ChordData({134, 0, 25}), 
};

uint8_t const kmap5_Word_len42_anagram1_seqs[6] = {
 109, 179, 229, 222, 
 164, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len42_anagram1 = {
  LengthAndAnagram(42, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len42_anagram1_chords, // chords
  kmap5_Word_len42_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len43_anagram0_chords[25] = {
 ChordData({4, 72, 64}), ChordData({4, 73, 2}), ChordData({18, 12, 11}), ChordData({32, 8, 144}), 
 ChordData({36, 1, 129}), ChordData({36, 9, 130}), ChordData({48, 12, 155}), ChordData({50, 1, 137}), 
 ChordData({52, 8, 81}), ChordData({52, 12, 152}), ChordData({54, 0, 65}), ChordData({54, 4, 130}), 
 ChordData({54, 64, 81}), ChordData({130, 68, 27}), ChordData({134, 4, 90}), ChordData({134, 44, 194}), 
 ChordData({134, 68, 73}), ChordData({144, 32, 211}), ChordData({146, 4, 155}), ChordData({146, 36, 147}), 
 ChordData({166, 4, 137}), ChordData({166, 12, 73}), ChordData({180, 13, 16}), ChordData({182, 12, 131}), 
 ChordData({182, 76, 130}), 
};

uint8_t const kmap5_Word_len43_anagram0_seqs[135] = {
 124, 227, 3, 31, 
 121, 9, 145, 111, 
 124, 199, 99, 252, 
 209, 179, 190, 162, 
 121, 142, 95, 62, 
 242, 196, 19, 15, 
 249, 158, 63, 142, 
 248, 198, 119, 60, 
 154, 179, 94, 125, 
 162, 114, 244, 76, 
 52, 208, 122, 188, 
 184, 157, 99, 239, 
 229, 42, 169, 247, 
 123, 178, 212, 94, 
 110, 174, 158, 191, 
 53, 26, 252, 158, 
 28, 70, 110, 167, 
 175, 231, 48, 120, 
 147, 250, 91, 98, 
 170, 180, 217, 199, 
 242, 17, 51, 54, 
 26, 97, 97, 228, 
 91, 203, 209, 67, 
 150, 100, 57, 111, 
 18, 230, 174, 233, 
 111, 82, 143, 57, 
 215, 55, 248, 212, 
 178, 85, 250, 155, 
 212, 23, 169, 177, 
 221, 164, 182, 77, 
 184, 31, 163, 23, 
 51, 182, 191, 233, 
 201, 253, 100, 116, 
 24, 124, 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len43_anagram0 = {
  LengthAndAnagram(43, 0), // seq_bit_len_and_anagram
  25, // num_chords
  kmap5_Word_len43_anagram0_chords, // chords
  kmap5_Word_len43_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len44_anagram0_chords[18] = {
 ChordData({0, 44, 9}), ChordData({2, 100, 83}), ChordData({18, 5, 19}), ChordData({34, 8, 146}), 
 ChordData({48, 65, 154}), ChordData({50, 1, 75}), ChordData({50, 5, 17}), ChordData({50, 8, 91}), 
 ChordData({50, 12, 131}), ChordData({50, 12, 153}), ChordData({52, 5, 18}), ChordData({52, 12, 17}), 
 ChordData({128, 0, 66}), ChordData({130, 4, 203}), ChordData({144, 76, 89}), ChordData({146, 4, 147}), 
 ChordData({146, 12, 11}), ChordData({146, 68, 73}), 
};

uint8_t const kmap5_Word_len44_anagram0_seqs[99] = {
 124, 124, 101, 127, 
 247, 26, 74, 249, 
 61, 182, 243, 232, 
 189, 233, 6, 255, 
 140, 117, 119, 176, 
 82, 141, 221, 186, 
 80, 181, 98, 41, 
 181, 235, 6, 199, 
 122, 235, 110, 7, 
 122, 255, 92, 117, 
 56, 175, 204, 149, 
 88, 99, 165, 191, 
 225, 252, 116, 94, 
 253, 27, 206, 124, 
 231, 126, 235, 111, 
 121, 142, 205, 251, 
 87, 215, 41, 56, 
 68, 127, 147, 154, 
 130, 67, 244, 55, 
 169, 193, 49, 85, 
 110, 255, 108, 16, 
 206, 253, 229, 150, 
 152, 122, 31, 71, 
 255, 28, 44, 55, 
 250, 55, 169, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len44_anagram0 = {
  LengthAndAnagram(44, 0), // seq_bit_len_and_anagram
  18, // num_chords
  kmap5_Word_len44_anagram0_chords, // chords
  kmap5_Word_len44_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len44_anagram1_chords[1] = {
 ChordData({2, 100, 83}), 
};

uint8_t const kmap5_Word_len44_anagram1_seqs[6] = {
 161, 148, 223, 99, 
 59, 8, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len44_anagram1 = {
  LengthAndAnagram(44, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len44_anagram1_chords, // chords
  kmap5_Word_len44_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len45_anagram0_chords[15] = {
 ChordData({0, 4, 145}), ChordData({18, 108, 90}), ChordData({22, 4, 19}), ChordData({34, 76, 136}), 
 ChordData({50, 8, 8}), ChordData({52, 4, 211}), ChordData({54, 8, 83}), ChordData({144, 0, 89}), 
 ChordData({150, 8, 11}), ChordData({150, 97, 194}), ChordData({178, 8, 25}), ChordData({178, 8, 75}), 
 ChordData({178, 68, 153}), ChordData({180, 4, 147}), ChordData({182, 0, 216}), 
};

uint8_t const kmap5_Word_len45_anagram0_seqs[85] = {
 183, 15, 110, 188, 
 220, 50, 122, 145, 
 189, 134, 17, 183, 
 223, 27, 156, 246, 
 231, 209, 48, 220, 
 132, 250, 100, 229, 
 102, 83, 163, 245, 
 164, 25, 239, 177, 
 210, 111, 243, 74, 
 51, 222, 112, 62, 
 203, 165, 156, 55, 
 213, 152, 177, 249, 
 230, 38, 181, 51, 
 81, 2, 194, 166, 
 89, 185, 217, 212, 
 104, 61, 76, 21, 
 99, 189, 225, 92, 
 168, 254, 121, 117, 
 82, 49, 137, 190, 
 207, 253, 243, 90, 
 90, 170, 76, 79, 
 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len45_anagram0 = {
  LengthAndAnagram(45, 0), // seq_bit_len_and_anagram
  15, // num_chords
  kmap5_Word_len45_anagram0_chords, // chords
  kmap5_Word_len45_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len45_anagram3_chords[1] = {
 ChordData({38, 4, 147}), 
};

uint8_t const kmap5_Word_len45_anagram3_seqs[6] = {
 248, 237, 251, 161, 
 185, 18, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len45_anagram3 = {
  LengthAndAnagram(45, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len45_anagram3_chords, // chords
  kmap5_Word_len45_anagram3_seqs, // sequences
};

ChordData const kmap5_Word_len46_anagram0_chords[16] = {
 ChordData({2, 8, 73}), ChordData({6, 4, 27}), ChordData({6, 36, 83}), ChordData({38, 68, 82}), 
 ChordData({50, 5, 147}), ChordData({50, 76, 137}), ChordData({52, 0, 25}), ChordData({134, 4, 139}), 
 ChordData({134, 32, 210}), ChordData({144, 76, 3}), ChordData({146, 1, 11}), ChordData({148, 13, 26}), 
 ChordData({150, 4, 17}), ChordData({150, 4, 83}), ChordData({160, 8, 2}), ChordData({178, 12, 11}), 
};

uint8_t const kmap5_Word_len46_anagram0_seqs[92] = {
 114, 19, 43, 253, 
 77, 106, 251, 189, 
 193, 105, 175, 215, 
 164, 68, 54, 127, 
 91, 74, 237, 101, 
 194, 252, 150, 15, 
 119, 176, 210, 213, 
 181, 11, 213, 225, 
 158, 172, 103, 189, 
 117, 91, 171, 235, 
 126, 107, 52, 248, 
 55, 169, 141, 13, 
 165, 100, 99, 229, 
 35, 102, 140, 25, 
 254, 140, 233, 174, 
 27, 28, 235, 53, 
 111, 151, 27, 95, 
 209, 223, 218, 102, 
 219, 249, 243, 90, 
 218, 236, 95, 110, 
 137, 25, 99, 213, 
 193, 63, 99, 198, 
 88, 117, 240, 207, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len46_anagram0 = {
  LengthAndAnagram(46, 0), // seq_bit_len_and_anagram
  16, // num_chords
  kmap5_Word_len46_anagram0_chords, // chords
  kmap5_Word_len46_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len46_anagram1_chords[1] = {
 ChordData({32, 8, 18}), 
};

uint8_t const kmap5_Word_len46_anagram1_seqs[6] = {
 124, 201, 71, 62, 
 242, 28, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len46_anagram1 = {
  LengthAndAnagram(46, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len46_anagram1_chords, // chords
  kmap5_Word_len46_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len47_anagram0_chords[13] = {
 ChordData({22, 12, 154}), ChordData({34, 5, 75}), ChordData({38, 4, 201}), ChordData({50, 12, 90}), 
 ChordData({50, 13, 11}), ChordData({52, 64, 201}), ChordData({130, 13, 25}), ChordData({132, 4, 18}), 
 ChordData({150, 4, 19}), ChordData({160, 12, 147}), ChordData({164, 12, 146}), ChordData({176, 8, 91}), 
 ChordData({176, 64, 202}), 
};

uint8_t const kmap5_Word_len47_anagram0_seqs[77] = {
 109, 77, 19, 71, 
 127, 75, 25, 168, 
 211, 13, 190, 158, 
 212, 94, 238, 245, 
 230, 233, 85, 135, 
 243, 202, 111, 25, 
 31, 234, 116, 131, 
 214, 147, 218, 139, 
 11, 85, 235, 141, 
 118, 185, 241, 111, 
 82, 219, 38, 151, 
 248, 55, 169, 109, 
 179, 237, 248, 126, 
 203, 71, 172, 177, 
 210, 95, 46, 151, 
 248, 125, 165, 223, 
 18, 83, 111, 147, 
 243, 74, 137, 169, 
 226, 66, 213, 138, 
 6, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len47_anagram0 = {
  LengthAndAnagram(47, 0), // seq_bit_len_and_anagram
  13, // num_chords
  kmap5_Word_len47_anagram0_chords, // chords
  kmap5_Word_len47_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len48_anagram0_chords[4] = {
 ChordData({48, 13, 27}), ChordData({130, 5, 154}), ChordData({164, 8, 16}), ChordData({182, 72, 26}), 
};

uint8_t const kmap5_Word_len48_anagram0_seqs[24] = {
 241, 181, 118, 143, 
 87, 215, 60, 62, 
 77, 151, 171, 243, 
 124, 219, 228, 38, 
 88, 209, 124, 219, 
 228, 38, 88, 209, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len48_anagram0 = {
  LengthAndAnagram(48, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap5_Word_len48_anagram0_chords, // chords
  kmap5_Word_len48_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len49_anagram0_chords[14] = {
 ChordData({0, 13, 2}), ChordData({4, 4, 82}), ChordData({18, 76, 91}), ChordData({50, 12, 91}), 
 ChordData({54, 1, 137}), ChordData({144, 12, 147}), ChordData({150, 12, 147}), ChordData({150, 36, 67}), 
 ChordData({160, 8, 10}), ChordData({166, 0, 27}), ChordData({166, 0, 211}), ChordData({176, 5, 155}), 
 ChordData({176, 77, 138}), ChordData({178, 12, 91}), 
};

uint8_t const kmap5_Word_len49_anagram0_seqs[86] = {
 143, 69, 77, 128, 
 28, 160, 249, 229, 
 145, 47, 76, 188, 
 132, 17, 220, 137, 
 163, 127, 198, 89, 
 172, 81, 238, 21, 
 61, 122, 38, 26, 
 56, 61, 249, 17, 
 77, 222, 140, 62, 
 239, 183, 182, 9, 
 154, 248, 103, 201, 
 198, 70, 110, 240, 
 207, 152, 202, 121, 
 229, 111, 82, 179, 
 181, 220, 171, 58, 
 87, 182, 20, 153, 
 126, 104, 174, 196, 
 84, 184, 127, 149, 
 254, 252, 88, 212, 
 4, 200, 1, 26, 
 83, 57, 175, 252, 
 77, 42, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len49_anagram0 = {
  LengthAndAnagram(49, 0), // seq_bit_len_and_anagram
  14, // num_chords
  kmap5_Word_len49_anagram0_chords, // chords
  kmap5_Word_len49_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len49_anagram1_chords[1] = {
 ChordData({0, 0, 146}), 
};

uint8_t const kmap5_Word_len49_anagram1_seqs[7] = {
 109, 45, 184, 211, 
 110, 82, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len49_anagram1 = {
  LengthAndAnagram(49, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len49_anagram1_chords, // chords
  kmap5_Word_len49_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len50_anagram0_chords[5] = {
 ChordData({2, 4, 66}), ChordData({4, 4, 66}), ChordData({32, 68, 130}), ChordData({162, 68, 203}), 
 ChordData({178, 12, 201}), 
};

uint8_t const kmap5_Word_len50_anagram0_seqs[32] = {
 252, 243, 194, 35, 
 63, 252, 240, 141, 
 71, 190, 48, 241, 
 242, 88, 168, 142, 
 204, 77, 234, 99, 
 161, 58, 50, 55, 
 169, 50, 177, 210, 
 189, 58, 171, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len50_anagram0 = {
  LengthAndAnagram(50, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len50_anagram0_chords, // chords
  kmap5_Word_len50_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len51_anagram0_chords[3] = {
 ChordData({6, 8, 1}), ChordData({38, 8, 211}), ChordData({164, 0, 17}), 
};

uint8_t const kmap5_Word_len51_anagram0_seqs[20] = {
 19, 91, 37, 25, 
 110, 174, 156, 216, 
 42, 201, 112, 115, 
 101, 219, 236, 191, 
 31, 154, 43, 1, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len51_anagram0 = {
  LengthAndAnagram(51, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len51_anagram0_chords, // chords
  kmap5_Word_len51_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len51_anagram1_chords[1] = {
 ChordData({128, 0, 10}), 
};

uint8_t const kmap5_Word_len51_anagram1_seqs[7] = {
 152, 170, 198, 27, 
 110, 174, 4, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len51_anagram1 = {
  LengthAndAnagram(51, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len51_anagram1_chords, // chords
  kmap5_Word_len51_anagram1_seqs, // sequences
};

ChordData const kmap5_Word_len52_anagram0_chords[5] = {
 ChordData({54, 64, 209}), ChordData({130, 64, 81}), ChordData({150, 32, 83}), ChordData({166, 64, 89}), 
 ChordData({178, 12, 202}), 
};

uint8_t const kmap5_Word_len52_anagram0_seqs[33] = {
 109, 189, 46, 84, 
 71, 230, 28, 70, 
 110, 167, 175, 55, 
 169, 60, 178, 29, 
 185, 108, 204, 27, 
 70, 110, 167, 175, 
 55, 169, 113, 4, 
 77, 244, 234, 172, 
 2, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len52_anagram0 = {
  LengthAndAnagram(52, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap5_Word_len52_anagram0_chords, // chords
  kmap5_Word_len52_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len52_anagram2_chords[1] = {
 ChordData({38, 4, 147}), 
};

uint8_t const kmap5_Word_len52_anagram2_seqs[7] = {
 237, 247, 6, 43, 
 253, 82, 9, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len52_anagram2 = {
  LengthAndAnagram(52, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len52_anagram2_chords, // chords
  kmap5_Word_len52_anagram2_seqs, // sequences
};

ChordData const kmap5_Word_len53_anagram0_chords[1] = {
 ChordData({54, 72, 144}), 
};

uint8_t const kmap5_Word_len53_anagram0_seqs[7] = {
 46, 84, 135, 166, 
 223, 169, 17, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len53_anagram0 = {
  LengthAndAnagram(53, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len53_anagram0_chords, // chords
  kmap5_Word_len53_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len55_anagram0_chords[1] = {
 ChordData({2, 13, 0}), 
};

uint8_t const kmap5_Word_len55_anagram0_seqs[7] = {
 252, 243, 29, 255, 
 252, 240, 69, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len55_anagram0 = {
  LengthAndAnagram(55, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len55_anagram0_chords, // chords
  kmap5_Word_len55_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len57_anagram0_chords[3] = {
 ChordData({22, 76, 219}), ChordData({32, 40, 66}), ChordData({34, 5, 219}), 
};

uint8_t const kmap5_Word_len57_anagram0_seqs[22] = {
 188, 0, 115, 5, 
 189, 244, 26, 120, 
 142, 199, 194, 195, 
 115, 188, 200, 64, 
 157, 110, 240, 245, 
 168, 4, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len57_anagram0 = {
  LengthAndAnagram(57, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap5_Word_len57_anagram0_chords, // chords
  kmap5_Word_len57_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len58_anagram0_chords[1] = {
 ChordData({54, 12, 218}), 
};

uint8_t const kmap5_Word_len58_anagram0_seqs[8] = {
 124, 179, 170, 148, 
 196, 189, 206, 3, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len58_anagram0 = {
  LengthAndAnagram(58, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len58_anagram0_chords, // chords
  kmap5_Word_len58_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len60_anagram0_chords[1] = {
 ChordData({182, 0, 219}), 
};

uint8_t const kmap5_Word_len60_anagram0_seqs[8] = {
 107, 105, 169, 50, 
 253, 208, 92, 9, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len60_anagram0 = {
  LengthAndAnagram(60, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len60_anagram0_chords, // chords
  kmap5_Word_len60_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len71_anagram0_chords[1] = {
 ChordData({164, 36, 9}), 
};

uint8_t const kmap5_Word_len71_anagram0_seqs[9] = {
 124, 207, 43, 159, 
 5, 164, 48, 22, 
 70, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len71_anagram0 = {
  LengthAndAnagram(71, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len71_anagram0_chords, // chords
  kmap5_Word_len71_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len79_anagram0_chords[1] = {
 ChordData({34, 65, 82}), 
};

uint8_t const kmap5_Word_len79_anagram0_seqs[10] = {
 60, 192, 151, 188, 
 240, 195, 3, 124, 
 201, 67, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len79_anagram0 = {
  LengthAndAnagram(79, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len79_anagram0_chords, // chords
  kmap5_Word_len79_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len102_anagram0_chords[1] = {
 ChordData({16, 1, 144}), 
};

uint8_t const kmap5_Word_len102_anagram0_seqs[13] = {
 235, 142, 140, 55, 
 169, 5, 152, 216, 
 42, 201, 112, 115, 
 37, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len102_anagram0 = {
  LengthAndAnagram(102, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len102_anagram0_chords, // chords
  kmap5_Word_len102_anagram0_seqs, // sequences
};

ChordData const kmap5_Word_len105_anagram0_chords[1] = {
 ChordData({2, 5, 0}), 
};

uint8_t const kmap5_Word_len105_anagram0_seqs[14] = {
 47, 5, 232, 126, 
 11, 240, 82, 0, 
 126, 10, 80, 212, 
 4, 0, 
};

LookupKmapTypeLenAnagram const kmap5_Word_len105_anagram0 = {
  LengthAndAnagram(105, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap5_Word_len105_anagram0_chords, // chords
  kmap5_Word_len105_anagram0_seqs, // sequences
};

LookupKmapTypeLenAnagram const* const kmap5_Word_lookups_array[174] = {
 &kmap5_Word_len4_anagram1, &kmap5_Word_len5_anagram1, &kmap5_Word_len7_anagram0, &kmap5_Word_len7_anagram1, 
 &kmap5_Word_len8_anagram0, &kmap5_Word_len8_anagram1, &kmap5_Word_len9_anagram0, &kmap5_Word_len9_anagram1, 
 &kmap5_Word_len9_anagram2, &kmap5_Word_len9_anagram4, &kmap5_Word_len10_anagram0, &kmap5_Word_len10_anagram1, 
 &kmap5_Word_len10_anagram2, &kmap5_Word_len10_anagram3, &kmap5_Word_len11_anagram0, &kmap5_Word_len11_anagram1, 
 &kmap5_Word_len11_anagram2, &kmap5_Word_len11_anagram3, &kmap5_Word_len11_anagram4, &kmap5_Word_len12_anagram0, 
 &kmap5_Word_len12_anagram1, &kmap5_Word_len12_anagram2, &kmap5_Word_len12_anagram3, &kmap5_Word_len13_anagram0, 
 &kmap5_Word_len13_anagram1, &kmap5_Word_len13_anagram2, &kmap5_Word_len13_anagram3, &kmap5_Word_len14_anagram0, 
 &kmap5_Word_len14_anagram1, &kmap5_Word_len14_anagram2, &kmap5_Word_len14_anagram3, &kmap5_Word_len14_anagram4, 
 &kmap5_Word_len14_anagram7, &kmap5_Word_len15_anagram0, &kmap5_Word_len15_anagram1, &kmap5_Word_len15_anagram2, 
 &kmap5_Word_len15_anagram3, &kmap5_Word_len15_anagram5, &kmap5_Word_len16_anagram0, &kmap5_Word_len16_anagram1, 
 &kmap5_Word_len16_anagram2, &kmap5_Word_len16_anagram3, &kmap5_Word_len17_anagram0, &kmap5_Word_len17_anagram1, 
 &kmap5_Word_len17_anagram2, &kmap5_Word_len17_anagram3, &kmap5_Word_len17_anagram5, &kmap5_Word_len18_anagram0, 
 &kmap5_Word_len18_anagram1, &kmap5_Word_len18_anagram2, &kmap5_Word_len18_anagram3, &kmap5_Word_len19_anagram0, 
 &kmap5_Word_len19_anagram1, &kmap5_Word_len19_anagram2, &kmap5_Word_len19_anagram3, &kmap5_Word_len19_anagram4, 
 &kmap5_Word_len20_anagram0, &kmap5_Word_len20_anagram1, &kmap5_Word_len20_anagram2, &kmap5_Word_len20_anagram3, 
 &kmap5_Word_len20_anagram6, &kmap5_Word_len21_anagram0, &kmap5_Word_len21_anagram1, &kmap5_Word_len21_anagram2, 
 &kmap5_Word_len21_anagram3, &kmap5_Word_len21_anagram4, &kmap5_Word_len21_anagram5, &kmap5_Word_len22_anagram0, 
 &kmap5_Word_len22_anagram1, &kmap5_Word_len22_anagram2, &kmap5_Word_len22_anagram3, &kmap5_Word_len22_anagram4, 
 &kmap5_Word_len22_anagram6, &kmap5_Word_len23_anagram0, &kmap5_Word_len23_anagram1, &kmap5_Word_len23_anagram2, 
 &kmap5_Word_len23_anagram3, &kmap5_Word_len23_anagram4, &kmap5_Word_len23_anagram5, &kmap5_Word_len23_anagram6, 
 &kmap5_Word_len24_anagram0, &kmap5_Word_len24_anagram1, &kmap5_Word_len24_anagram2, &kmap5_Word_len24_anagram3, 
 &kmap5_Word_len24_anagram4, &kmap5_Word_len24_anagram5, &kmap5_Word_len25_anagram0, &kmap5_Word_len25_anagram1, 
 &kmap5_Word_len25_anagram2, &kmap5_Word_len25_anagram3, &kmap5_Word_len25_anagram4, &kmap5_Word_len26_anagram0, 
 &kmap5_Word_len26_anagram1, &kmap5_Word_len26_anagram2, &kmap5_Word_len26_anagram3, &kmap5_Word_len26_anagram4, 
 &kmap5_Word_len27_anagram0, &kmap5_Word_len27_anagram1, &kmap5_Word_len27_anagram2, &kmap5_Word_len27_anagram3, 
 &kmap5_Word_len27_anagram7, &kmap5_Word_len28_anagram0, &kmap5_Word_len28_anagram1, &kmap5_Word_len28_anagram2, 
 &kmap5_Word_len28_anagram3, &kmap5_Word_len28_anagram4, &kmap5_Word_len29_anagram0, &kmap5_Word_len29_anagram1, 
 &kmap5_Word_len29_anagram2, &kmap5_Word_len29_anagram3, &kmap5_Word_len30_anagram0, &kmap5_Word_len30_anagram1, 
 &kmap5_Word_len30_anagram2, &kmap5_Word_len31_anagram0, &kmap5_Word_len31_anagram1, &kmap5_Word_len31_anagram2, 
 &kmap5_Word_len31_anagram3, &kmap5_Word_len32_anagram0, &kmap5_Word_len32_anagram1, &kmap5_Word_len32_anagram2, 
 &kmap5_Word_len33_anagram0, &kmap5_Word_len33_anagram1, &kmap5_Word_len33_anagram2, &kmap5_Word_len33_anagram3, 
 &kmap5_Word_len34_anagram0, &kmap5_Word_len34_anagram1, &kmap5_Word_len34_anagram2, &kmap5_Word_len34_anagram4, 
 &kmap5_Word_len35_anagram0, &kmap5_Word_len35_anagram1, &kmap5_Word_len35_anagram2, &kmap5_Word_len36_anagram0, 
 &kmap5_Word_len36_anagram1, &kmap5_Word_len37_anagram0, &kmap5_Word_len37_anagram1, &kmap5_Word_len37_anagram2, 
 &kmap5_Word_len37_anagram3, &kmap5_Word_len38_anagram0, &kmap5_Word_len38_anagram1, &kmap5_Word_len38_anagram2, 
 &kmap5_Word_len39_anagram0, &kmap5_Word_len39_anagram1, &kmap5_Word_len40_anagram0, &kmap5_Word_len40_anagram1, 
 &kmap5_Word_len40_anagram2, &kmap5_Word_len41_anagram0, &kmap5_Word_len41_anagram1, &kmap5_Word_len42_anagram0, 
 &kmap5_Word_len42_anagram1, &kmap5_Word_len43_anagram0, &kmap5_Word_len44_anagram0, &kmap5_Word_len44_anagram1, 
 &kmap5_Word_len45_anagram0, &kmap5_Word_len45_anagram3, &kmap5_Word_len46_anagram0, &kmap5_Word_len46_anagram1, 
 &kmap5_Word_len47_anagram0, &kmap5_Word_len48_anagram0, &kmap5_Word_len49_anagram0, &kmap5_Word_len49_anagram1, 
 &kmap5_Word_len50_anagram0, &kmap5_Word_len51_anagram0, &kmap5_Word_len51_anagram1, &kmap5_Word_len52_anagram0, 
 &kmap5_Word_len52_anagram2, &kmap5_Word_len53_anagram0, &kmap5_Word_len55_anagram0, &kmap5_Word_len57_anagram0, 
 &kmap5_Word_len58_anagram0, &kmap5_Word_len60_anagram0, &kmap5_Word_len71_anagram0, &kmap5_Word_len79_anagram0, 
 &kmap5_Word_len102_anagram0, &kmap5_Word_len105_anagram0, 
};

LookupKmapType const kmap5_Word_lookups = {
  174, // num_lookups
  kmap5_Word_lookups_array, // lookups
};

LookupKmapType const* const kmap5_lookups_array[4] = {
 &kmap5_Plain_lookups, &kmap5_Macro_lookups, &kmap5_Command_lookups, &kmap5_Word_lookups, 
};

KmapStruct const kmap5_lookups = {
  kmap5_lookups_array, // lookups_for_kmap
};

KmapStruct const* const default_mode_kmaps_array[3] = {
 &kmap4_lookups, &kmap5_lookups, &kmap0_lookups, 
};

ChordData const default_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

ChordData const default_mode_anagram_mask = ChordData({8, 128, 0});

ModeStruct const default_mode_struct = {
  0, // is_gaming
  3, // num_kmaps
  default_mode_kmaps_array, // kmaps
  default_mode_mod_chord, // mod_chords
  default_mode_anagram_mask, // anagram_mask
};

KmapStruct const* const gaming_mode_kmaps_array[1] = {
 &kmap1_lookups, 
};

ChordData const gaming_mode_mod_chord[10] = {
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({0, 4, 0}), ChordData({0, 0, 0}), 
};

ChordData const gaming_mode_anagram_mask = ChordData({0, 0, 0});

ModeStruct const gaming_mode_struct = {
  1, // is_gaming
  1, // num_kmaps
  gaming_mode_kmaps_array, // kmaps
  gaming_mode_mod_chord, // mod_chords
  gaming_mode_anagram_mask, // anagram_mask
};

KmapStruct const* const left_hand_mode_kmaps_array[1] = {
 &kmap2_lookups, 
};

ChordData const left_hand_mode_mod_chord[10] = {
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
};

ChordData const left_hand_mode_anagram_mask = ChordData({0, 0, 0});

ModeStruct const left_hand_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  left_hand_mode_kmaps_array, // kmaps
  left_hand_mode_mod_chord, // mod_chords
  left_hand_mode_anagram_mask, // anagram_mask
};

KmapStruct const* const windows_mode_kmaps_array[4] = {
 &kmap3_lookups, &kmap4_lookups, &kmap5_lookups, &kmap0_lookups, 
};

ChordData const windows_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

ChordData const windows_mode_anagram_mask = ChordData({8, 128, 0});

ModeStruct const windows_mode_struct = {
  0, // is_gaming
  4, // num_kmaps
  windows_mode_kmaps_array, // kmaps
  windows_mode_mod_chord, // mod_chords
  windows_mode_anagram_mask, // anagram_mask
};

const std::array<ModeStruct const*,4> mode_structs = {
 &default_mode_struct, &gaming_mode_struct, &left_hand_mode_struct, &windows_mode_struct, 
};

} // end namespace conf
