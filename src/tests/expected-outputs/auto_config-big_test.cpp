#include "auto_config-big_test.h"
namespace conf {
const uint32_t CHORD_DELAY = 30;

const uint32_t HELD_DELAY = 200;

const uint32_t DEBOUNCE_DELAY = 10;

const WordSpacePosition SPACE_POS = WordSpacePosition::Before;

const std::array<uint8_t,3> row_pins = {
 1, 0, 19, 
};
const std::array<uint8_t,8> column_pins = {
 15, 16, 17, 18, 
 20, 21, 5, 6, 
};
const bool USE_STANDBY_INTERRUPTS = 1;

const std::array<uint8_t,3> rgb_led_pins = {
 10, 11, 12, 
};
const uint8_t battery_level_pin = 9;

const uint8_t MIN_HUFFMAN_CODE_BIT_LEN = 3;

const HuffmanChar huffman_lookup[105] = {
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
  HuffmanBits({13}), // bits
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
  HuffmanBits({1}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_O), // key_code
  0, // is_mod
}, {
  HuffmanBits({3}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_R), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({12}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_S), // key_code
  0, // is_mod
}, {
  HuffmanBits({11}), // bits
  4, // num_bits
  static_cast<uint8_t>(KEY_T), // key_code
  0, // is_mod
}, {
  HuffmanBits({18}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_D), // key_code
  0, // is_mod
}, {
  HuffmanBits({16}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_H), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({9}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_M), // key_code
  0, // is_mod
}, {
  HuffmanBits({21}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_P), // key_code
  0, // is_mod
}, {
  HuffmanBits({25}), // bits
  5, // num_bits
  static_cast<uint8_t>(KEY_U), // key_code
  0, // is_mod
}, {
  HuffmanBits({0}), // bits
  5, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_SHIFT), // key_code
  1, // is_mod
}, 
 {
  HuffmanBits({39}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_B), // key_code
  0, // is_mod
}, {
  HuffmanBits({7}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_F), // key_code
  0, // is_mod
}, {
  HuffmanBits({55}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_G), // key_code
  0, // is_mod
}, {
  HuffmanBits({34}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_V), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({5}), // bits
  6, // num_bits
  static_cast<uint8_t>(KEY_Y), // key_code
  0, // is_mod
}, {
  HuffmanBits({37}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_K), // key_code
  0, // is_mod
}, {
  HuffmanBits({23}), // bits
  7, // num_bits
  static_cast<uint8_t>(KEY_W), // key_code
  0, // is_mod
}, {
  HuffmanBits({2}), // bits
  8, // num_bits
  static_cast<uint8_t>(KEY_J), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({87}), // bits
  8, // num_bits
  static_cast<uint8_t>(KEY_X), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 1}), // bits
  9, // num_bits
  static_cast<uint8_t>(KEY_LEFT), // key_code
  0, // is_mod
}, {
  HuffmanBits({101, 0}), // bits
  9, // num_bits
  static_cast<uint8_t>(KEY_Q), // key_code
  0, // is_mod
}, {
  HuffmanBits({130, 1}), // bits
  9, // num_bits
  static_cast<uint8_t>(KEY_QUOTE), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({229, 0}), // bits
  9, // num_bits
  static_cast<uint8_t>(KEY_SPACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({101, 1}), // bits
  9, // num_bits
  static_cast<uint8_t>(KEY_Z), // key_code
  0, // is_mod
}, {
  HuffmanBits({66, 2}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_0), // key_code
  0, // is_mod
}, {
  HuffmanBits({66, 0}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_9), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({194, 1}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_ENTER), // key_code
  0, // is_mod
}, {
  HuffmanBits({194, 2}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_LEFT_BRACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({194, 0}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_PERIOD), // key_code
  0, // is_mod
}, {
  HuffmanBits({66, 3}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_RIGHT_BRACE), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({130, 0}), // bits
  10, // num_bits
  static_cast<uint8_t>(KEY_UP), // key_code
  0, // is_mod
}, {
  HuffmanBits({130, 2}), // bits
  11, // num_bits
  static_cast<uint8_t>(KEY_BACKSLASH), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 2}), // bits
  11, // num_bits
  static_cast<uint8_t>(KEY_COMMA), // key_code
  0, // is_mod
}, {
  HuffmanBits({66, 1}), // bits
  11, // num_bits
  static_cast<uint8_t>(KEY_END), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({130, 6}), // bits
  11, // num_bits
  static_cast<uint8_t>(KEY_MINUS), // key_code
  0, // is_mod
}, {
  HuffmanBits({194, 7}), // bits
  11, // num_bits
  static_cast<uint8_t>(KEY_SEMICOLON), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 11}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_1), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 6}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_2), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 14}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_3), // key_code
  0, // is_mod
}, {
  HuffmanBits({66, 5}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_4), // key_code
  0, // is_mod
}, {
  HuffmanBits({194, 3}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_7), // key_code
  0, // is_mod
}, {
  HuffmanBits({66, 13}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_EQUAL), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({229, 9}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_ESC), // key_code
  0, // is_mod
}, {
  HuffmanBits({194, 11}), // bits
  12, // num_bits
  static_cast<uint8_t>(KEY_SLASH), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 3}), // bits
  12, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_CTRL), // key_code
  1, // is_mod
}, {
  HuffmanBits({215, 12}), // bits
  13, // num_bits
  static_cast<uint8_t>(0 /* blank key, when a keypress contains only modifiers and no key */), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 0}), // bits
  13, // num_bits
  static_cast<uint8_t>(Command::command_switch_to), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 5}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_5), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 7}), // bits
  13, // num_bits
  static_cast<uint8_t>(KEY_TILDE), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 60}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_6), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 28}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_8), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 49}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_PAGE_DOWN), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 17}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_PAGE_UP), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 4}), // bits
  14, // num_bits
  static_cast<uint8_t>(KEY_TAB), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 8}), // bits
  14, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_ALT), // key_code
  1, // is_mod
}, {
  HuffmanBits({229, 21}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_cycle_capital), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 85}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_cycle_nospace), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 95}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_cycle_word), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 36}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_delete_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 87}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_led_battery), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 53}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_led_colors), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 52}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_led_rainbow), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 116}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_left_limit), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 109}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_left_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 100}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_pan_left), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 61}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_pan_right), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 40}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_pause), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 15}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_right_limit), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 117}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_right_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 1}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_scroll_down), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({229, 65}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_scroll_up), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 120}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_shorten_last_word), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 13}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_sticky_alt), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 97}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_sticky_ctrl), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({229, 33}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_sticky_gui), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 63}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_sticky_shift), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 31}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_toggle_wireless), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 125}), // bits
  15, // num_bits
  static_cast<uint8_t>(Command::command_windows_mode), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({229, 77}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_BACKSPACE), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 20}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_CAPS_LOCK), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 45}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_DELETE), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 127}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_DOWN), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({229, 119}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F1), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 29}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F2), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 104}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F3), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 55}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F4), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 112}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F5), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 23}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F6), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 79}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F7), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 48}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F8), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 16}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_F9), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 47}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_HOME), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 56}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_PRINTSCREEN), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 84}), // bits
  15, // num_bits
  static_cast<uint8_t>(KEY_RIGHT), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({215, 88}), // bits
  15, // num_bits
  static_cast<uint8_t>(MODIFIERKEY_GUI), // key_code
  1, // is_mod
}, {
  HuffmanBits({215, 24}), // bits
  15, // num_bits
  static_cast<uint8_t>(Mode::default_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({215, 80}), // bits
  15, // num_bits
  static_cast<uint8_t>(Mode::gaming_mode), // key_code
  0, // is_mod
}, {
  HuffmanBits({229, 93}), // bits
  15, // num_bits
  static_cast<uint8_t>(Mode::left_hand_mode), // key_code
  0, // is_mod
}, 
 {
  HuffmanBits({229, 111}), // bits
  15, // num_bits
  static_cast<uint8_t>(Mode::windows_mode), // key_code
  0, // is_mod
}, 
};

const uint8_t MAX_ANAGRAM_NUM = 7;

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
const uint8_t MAX_KEYS_IN_SEQUENCE = 41;

const ChordData kmap0_Plain_len3_anagram0_chords[1] = {
 ChordData({16, 0, 0}), 
};

const uint8_t kmap0_Plain_len3_anagram0_seqs[1] = {
 6, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len3_anagram0 = {
  LengthAndAnagram(3, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len3_anagram0_chords, // chords
  kmap0_Plain_len3_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len4_anagram0_chords[9] = {
 ChordData({0, 0, 1}), ChordData({0, 0, 2}), ChordData({0, 0, 8}), ChordData({0, 0, 16}), 
 ChordData({0, 0, 64}), ChordData({0, 0, 128}), ChordData({0, 4, 0}), ChordData({2, 0, 0}), 
 ChordData({128, 0, 0}), 
};

const uint8_t kmap0_Plain_len4_anagram0_seqs[5] = {
 139, 58, 76, 223, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len4_anagram0 = {
  LengthAndAnagram(4, 0), // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_Plain_len4_anagram0_chords, // chords
  kmap0_Plain_len4_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len5_anagram0_chords[5] = {
 ChordData({0, 8, 0}), ChordData({0, 32, 0}), ChordData({0, 64, 0}), ChordData({4, 0, 0}), 
 ChordData({32, 0, 0}), 
};

const uint8_t kmap0_Plain_len5_anagram0_seqs[4] = {
 9, 202, 154, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len5_anagram0 = {
  LengthAndAnagram(5, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Plain_len5_anagram0_chords, // chords
  kmap0_Plain_len5_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len6_anagram0_chords[5] = {
 ChordData({0, 0, 18}), ChordData({0, 1, 0}), ChordData({32, 1, 0}), ChordData({32, 8, 0}), 
 ChordData({36, 0, 0}), 
};

const uint8_t kmap0_Plain_len6_anagram0_seqs[4] = {
 197, 113, 139, 39, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len6_anagram0 = {
  LengthAndAnagram(6, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Plain_len6_anagram0_chords, // chords
  kmap0_Plain_len6_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len7_anagram0_chords[2] = {
 ChordData({0, 9, 0}), ChordData({0, 64, 2}), 
};

const uint8_t kmap0_Plain_len7_anagram0_seqs[2] = {
 165, 11, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len7_anagram0_chords, // chords
  kmap0_Plain_len7_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len8_anagram0_chords[2] = {
 ChordData({0, 0, 130}), ChordData({0, 0, 144}), 
};

const uint8_t kmap0_Plain_len8_anagram0_seqs[2] = {
 87, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len8_anagram0 = {
  LengthAndAnagram(8, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len8_anagram0_chords, // chords
  kmap0_Plain_len8_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len9_anagram0_chords[5] = {
 ChordData({0, 32, 128}), ChordData({0, 64, 128}), ChordData({0, 128, 0}), ChordData({0, 192, 0}), 
 ChordData({4, 8, 0}), 
};

const uint8_t kmap0_Plain_len9_anagram0_seqs[6] = {
 130, 203, 148, 187, 
 94, 22, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Plain_len9_anagram0_chords, // chords
  kmap0_Plain_len9_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len10_anagram0_chords[7] = {
 ChordData({0, 0, 32}), ChordData({0, 1, 1}), ChordData({0, 32, 1}), ChordData({0, 33, 0}), 
 ChordData({0, 64, 16}), ChordData({8, 128, 0}), ChordData({16, 4, 0}), 
};

const uint8_t kmap0_Plain_len10_anagram0_seqs[9] = {
 130, 8, 45, 164, 
 176, 194, 8, 39, 
 4, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len10_anagram0 = {
  LengthAndAnagram(10, 0), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Plain_len10_anagram0_chords, // chords
  kmap0_Plain_len10_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len11_anagram0_chords[5] = {
 ChordData({0, 32, 16}), ChordData({0, 64, 8}), ChordData({0, 128, 128}), ChordData({4, 1, 0}), 
 ChordData({34, 0, 0}), 
};

const uint8_t kmap0_Plain_len11_anagram0_seqs[7] = {
 130, 22, 190, 80, 
 174, 37, 40, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Plain_len11_anagram0_chords, // chords
  kmap0_Plain_len11_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len12_anagram0_chords[8] = {
 ChordData({0, 0, 9}), ChordData({0, 0, 72}), ChordData({0, 32, 2}), ChordData({0, 64, 64}), 
 ChordData({16, 0, 1}), ChordData({18, 0, 0}), ChordData({130, 0, 0}), ChordData({144, 0, 0}), 
};

const uint8_t kmap0_Plain_len12_anagram0_seqs[12] = {
 215, 38, 84, 194, 
 43, 212, 229, 89, 
 190, 194, 115, 237, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len12_anagram0 = {
  LengthAndAnagram(12, 0), // seq_bit_len_and_anagram
  8, // num_chords
  kmap0_Plain_len12_anagram0_chords, // chords
  kmap0_Plain_len12_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len13_anagram0_chords[2] = {
 ChordData({0, 0, 80}), ChordData({128, 4, 0}), 
};

const uint8_t kmap0_Plain_len13_anagram0_seqs[4] = {
 229, 167, 188, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len13_anagram0 = {
  LengthAndAnagram(13, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len13_anagram0_chords, // chords
  kmap0_Plain_len13_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len14_anagram0_chords[6] = {
 ChordData({0, 0, 65}), ChordData({0, 2, 32}), ChordData({0, 32, 8}), ChordData({0, 130, 0}), 
 ChordData({2, 8, 0}), ChordData({128, 8, 0}), 
};

const uint8_t kmap0_Plain_len14_anagram0_seqs[11] = {
 215, 92, 121, 124, 
 205, 151, 71, 64, 
 240, 53, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Plain_len14_anagram0_chords, // chords
  kmap0_Plain_len14_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len15_anagram0_chords[21] = {
 ChordData({0, 2, 0}), ChordData({0, 8, 1}), ChordData({0, 128, 2}), ChordData({0, 128, 16}), 
 ChordData({0, 128, 216}), ChordData({0, 129, 9}), ChordData({0, 129, 65}), ChordData({0, 129, 72}), 
 ChordData({0, 161, 8}), ChordData({0, 224, 3}), ChordData({4, 0, 1}), ChordData({4, 32, 0}), 
 ChordData({8, 0, 0}), ChordData({16, 133, 0}), ChordData({18, 129, 0}), ChordData({32, 0, 1}), 
 ChordData({32, 32, 0}), ChordData({54, 128, 0}), ChordData({128, 133, 0}), ChordData({130, 129, 0}), 
 ChordData({144, 129, 0}), 
};

const uint8_t kmap0_Plain_len15_anagram0_seqs[40] = {
 229, 127, 32, 204, 
 53, 181, 252, 117, 
 141, 43, 239, 92, 
 195, 202, 111, 229, 
 151, 107, 10, 16, 
 18, 8, 81, 222, 
 188, 134, 148, 223, 
 129, 208, 64, 216, 
 242, 214, 53, 188, 
 252, 121, 141, 6, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  21, // num_chords
  kmap0_Plain_len15_anagram0_chords, // chords
  kmap0_Plain_len15_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len16_anagram0_chords[4] = {
 ChordData({0, 40, 0}), ChordData({2, 1, 0}), ChordData({16, 1, 0}), ChordData({132, 0, 0}), 
};

const uint8_t kmap0_Plain_len16_anagram0_seqs[8] = {
 224, 90, 64, 208, 
 64, 80, 64, 248, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Plain_len16_anagram0_chords, // chords
  kmap0_Plain_len16_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len17_anagram0_chords[7] = {
 ChordData({0, 0, 17}), ChordData({0, 0, 66}), ChordData({0, 32, 64}), ChordData({0, 64, 1}), 
 ChordData({2, 4, 0}), ChordData({4, 4, 0}), ChordData({32, 4, 0}), 
};

const uint8_t kmap0_Plain_len17_anagram0_seqs[15] = {
 64, 120, 192, 181, 
 3, 225, 5, 66, 
 5, 202, 23, 8, 
 53, 184, 54, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len17_anagram0 = {
  LengthAndAnagram(17, 0), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Plain_len17_anagram0_chords, // chords
  kmap0_Plain_len17_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len18_anagram0_chords[3] = {
 ChordData({0, 0, 10}), ChordData({0, 5, 0}), ChordData({64, 0, 0}), 
};

const uint8_t kmap0_Plain_len18_anagram0_seqs[7] = {
 160, 188, 128, 242, 
 3, 174, 25, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Plain_len18_anagram0_chords, // chords
  kmap0_Plain_len18_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len19_anagram0_chords[2] = {
 ChordData({20, 0, 0}), ChordData({160, 0, 0}), 
};

const uint8_t kmap0_Plain_len19_anagram0_seqs[5] = {
 224, 154, 7, 215, 
 28, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len19_anagram0 = {
  LengthAndAnagram(19, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Plain_len19_anagram0_chords, // chords
  kmap0_Plain_len19_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len25_anagram0_chords[1] = {
 ChordData({1, 0, 0}), 
};

const uint8_t kmap0_Plain_len25_anagram0_seqs[4] = {
 229, 115, 205, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len25_anagram0 = {
  LengthAndAnagram(25, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len25_anagram0_chords, // chords
  kmap0_Plain_len25_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len27_anagram0_chords[1] = {
 ChordData({0, 0, 4}), 
};

const uint8_t kmap0_Plain_len27_anagram0_seqs[4] = {
 215, 200, 53, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len27_anagram0 = {
  LengthAndAnagram(27, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len27_anagram0_chords, // chords
  kmap0_Plain_len27_anagram0_seqs, // sequences
};

const ChordData kmap0_Plain_len28_anagram0_chords[1] = {
 ChordData({0, 16, 0}), 
};

const uint8_t kmap0_Plain_len28_anagram0_seqs[4] = {
 215, 216, 107, 6, 
};

const LookupKmapTypeLenAnagram kmap0_Plain_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Plain_len28_anagram0_chords, // chords
  kmap0_Plain_len28_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap0_Plain_lookups_array[20] = {
 &kmap0_Plain_len3_anagram0, &kmap0_Plain_len4_anagram0, &kmap0_Plain_len5_anagram0, &kmap0_Plain_len6_anagram0, 
 &kmap0_Plain_len7_anagram0, &kmap0_Plain_len8_anagram0, &kmap0_Plain_len9_anagram0, &kmap0_Plain_len10_anagram0, 
 &kmap0_Plain_len11_anagram0, &kmap0_Plain_len12_anagram0, &kmap0_Plain_len13_anagram0, &kmap0_Plain_len14_anagram0, 
 &kmap0_Plain_len15_anagram0, &kmap0_Plain_len16_anagram0, &kmap0_Plain_len17_anagram0, &kmap0_Plain_len18_anagram0, 
 &kmap0_Plain_len19_anagram0, &kmap0_Plain_len25_anagram0, &kmap0_Plain_len27_anagram0, &kmap0_Plain_len28_anagram0, 
};

const LookupKmapType kmap0_Plain_lookups = {
  20, // num_lookups
  kmap0_Plain_lookups_array, // lookups
};

const ChordData kmap0_Macro_len15_anagram0_chords[1] = {
 ChordData({34, 0, 8}), 
};

const uint8_t kmap0_Macro_len15_anagram0_seqs[2] = {
 130, 82, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len15_anagram0_chords, // chords
  kmap0_Macro_len15_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len16_anagram0_chords[2] = {
 ChordData({0, 132, 0}), ChordData({16, 128, 8}), 
};

const uint8_t kmap0_Macro_len16_anagram0_seqs[4] = {
 229, 243, 229, 172, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len16_anagram0_chords, // chords
  kmap0_Macro_len16_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len17_anagram0_chords[5] = {
 ChordData({0, 128, 130}), ChordData({0, 160, 1}), ChordData({4, 128, 1}), ChordData({80, 128, 8}), 
 ChordData({128, 128, 128}), 
};

const uint8_t kmap0_Macro_len17_anagram0_seqs[11] = {
 229, 144, 202, 225, 
 28, 215, 42, 231, 
 90, 46, 8, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len17_anagram0 = {
  LengthAndAnagram(17, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Macro_len17_anagram0_chords, // chords
  kmap0_Macro_len17_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len18_anagram0_chords[1] = {
 ChordData({0, 128, 192}), 
};

const uint8_t kmap0_Macro_len18_anagram0_seqs[3] = {
 196, 194, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len18_anagram0_chords, // chords
  kmap0_Macro_len18_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len19_anagram0_chords[5] = {
 ChordData({4, 128, 0}), ChordData({32, 129, 64}), ChordData({36, 128, 64}), ChordData({48, 128, 0}), 
 ChordData({128, 129, 0}), 
};

const uint8_t kmap0_Macro_len19_anagram0_seqs[12] = {
 229, 166, 40, 119, 
 115, 185, 147, 203, 
 29, 83, 46, 14, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len19_anagram0 = {
  LengthAndAnagram(19, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Macro_len19_anagram0_chords, // chords
  kmap0_Macro_len19_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len20_anagram0_chords[4] = {
 ChordData({0, 128, 3}), ChordData({0, 161, 1}), ChordData({6, 0, 0}), ChordData({36, 192, 0}), 
};

const uint8_t kmap0_Macro_len20_anagram0_seqs[10] = {
 229, 234, 33, 172, 
 208, 229, 131, 93, 
 238, 148, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len20_anagram0 = {
  LengthAndAnagram(20, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Macro_len20_anagram0_chords, // chords
  kmap0_Macro_len20_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len21_anagram0_chords[3] = {
 ChordData({0, 0, 3}), ChordData({48, 0, 0}), ChordData({128, 128, 2}), 
};

const uint8_t kmap0_Macro_len21_anagram0_seqs[8] = {
 229, 142, 163, 220, 
 121, 150, 251, 64, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len21_anagram0 = {
  LengthAndAnagram(21, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Macro_len21_anagram0_chords, // chords
  kmap0_Macro_len21_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len22_anagram0_chords[6] = {
 ChordData({0, 96, 0}), ChordData({4, 160, 0}), ChordData({128, 128, 0}), ChordData({128, 132, 16}), 
 ChordData({128, 132, 64}), ChordData({132, 128, 64}), 
};

const uint8_t kmap0_Macro_len22_anagram0_seqs[17] = {
 215, 200, 21, 56, 
 174, 85, 46, 69, 
 151, 75, 49, 229, 
 82, 112, 185, 168, 
 12, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len22_anagram0 = {
  LengthAndAnagram(22, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Macro_len22_anagram0_chords, // chords
  kmap0_Macro_len22_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len23_anagram0_chords[7] = {
 ChordData({0, 128, 18}), ChordData({2, 128, 0}), ChordData({2, 128, 1}), ChordData({16, 193, 0}), 
 ChordData({132, 128, 0}), ChordData({132, 192, 0}), ChordData({160, 128, 0}), 
};

const uint8_t kmap0_Macro_len23_anagram0_seqs[21] = {
 5, 16, 170, 114, 
 151, 75, 185, 107, 
 162, 220, 97, 89, 
 46, 106, 45, 23, 
 85, 150, 139, 154, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len23_anagram0 = {
  LengthAndAnagram(23, 0), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Macro_len23_anagram0_chords, // chords
  kmap0_Macro_len23_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len24_anagram0_chords[1] = {
 ChordData({36, 192, 2}), 
};

const uint8_t kmap0_Macro_len24_anagram0_seqs[3] = {
 194, 91, 158, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len24_anagram0 = {
  LengthAndAnagram(24, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len24_anagram0_chords, // chords
  kmap0_Macro_len24_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len25_anagram0_chords[4] = {
 ChordData({0, 128, 1}), ChordData({6, 128, 0}), ChordData({16, 132, 1}), ChordData({128, 132, 2}), 
};

const uint8_t kmap0_Macro_len25_anagram0_seqs[13] = {
 229, 162, 172, 203, 
 7, 65, 127, 185, 
 242, 44, 247, 17, 
 8, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len25_anagram0 = {
  LengthAndAnagram(25, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Macro_len25_anagram0_chords, // chords
  kmap0_Macro_len25_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len26_anagram0_chords[3] = {
 ChordData({0, 128, 8}), ChordData({0, 128, 64}), ChordData({16, 36, 128}), 
};

const uint8_t kmap0_Macro_len26_anagram0_seqs[10] = {
 229, 83, 30, 149, 
 79, 121, 44, 104, 
 32, 12, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len26_anagram0 = {
  LengthAndAnagram(26, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Macro_len26_anagram0_chords, // chords
  kmap0_Macro_len26_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len27_anagram0_chords[4] = {
 ChordData({0, 160, 128}), ChordData({16, 129, 192}), ChordData({128, 36, 128}), ChordData({128, 132, 1}), 
};

const uint8_t kmap0_Macro_len27_anagram0_seqs[14] = {
 130, 5, 95, 103, 
 211, 33, 12, 184, 
 150, 160, 203, 37, 
 176, 11, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len27_anagram0 = {
  LengthAndAnagram(27, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Macro_len27_anagram0_chords, // chords
  kmap0_Macro_len27_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len29_anagram0_chords[2] = {
 ChordData({0, 33, 1}), ChordData({0, 128, 81}), 
};

const uint8_t kmap0_Macro_len29_anagram0_seqs[8] = {
 194, 10, 125, 29, 
 8, 15, 239, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len29_anagram0 = {
  LengthAndAnagram(29, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len29_anagram0_chords, // chords
  kmap0_Macro_len29_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len30_anagram0_chords[5] = {
 ChordData({2, 137, 0}), ChordData({4, 160, 1}), ChordData({20, 132, 1}), ChordData({32, 160, 1}), 
 ChordData({80, 132, 1}), 
};

const uint8_t kmap0_Macro_len30_anagram0_seqs[19] = {
 64, 48, 16, 52, 
 16, 2, 8, 249, 
 229, 202, 179, 2, 
 97, 129, 208, 224, 
 203, 149, 39, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len30_anagram0 = {
  LengthAndAnagram(30, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Macro_len30_anagram0_chords, // chords
  kmap0_Macro_len30_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len31_anagram0_chords[1] = {
 ChordData({0, 168, 1}), 
};

const uint8_t kmap0_Macro_len31_anagram0_seqs[4] = {
 224, 90, 64, 24, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len31_anagram0 = {
  LengthAndAnagram(31, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len31_anagram0_chords, // chords
  kmap0_Macro_len31_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len32_anagram0_chords[1] = {
 ChordData({0, 192, 128}), 
};

const uint8_t kmap0_Macro_len32_anagram0_seqs[4] = {
 229, 115, 85, 190, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len32_anagram0 = {
  LengthAndAnagram(32, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len32_anagram0_chords, // chords
  kmap0_Macro_len32_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len33_anagram0_chords[2] = {
 ChordData({0, 160, 0}), ChordData({0, 192, 64}), 
};

const uint8_t kmap0_Macro_len33_anagram0_seqs[9] = {
 64, 248, 23, 225, 
 132, 90, 168, 175, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len33_anagram0 = {
  LengthAndAnagram(33, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len33_anagram0_chords, // chords
  kmap0_Macro_len33_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len34_anagram0_chords[1] = {
 ChordData({32, 132, 0}), 
};

const uint8_t kmap0_Macro_len34_anagram0_seqs[5] = {
 224, 218, 192, 181, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len34_anagram0 = {
  LengthAndAnagram(34, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len34_anagram0_chords, // chords
  kmap0_Macro_len34_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len35_anagram0_chords[3] = {
 ChordData({0, 128, 80}), ChordData({84, 132, 1}), ChordData({146, 164, 0}), 
};

const uint8_t kmap0_Macro_len35_anagram0_seqs[14] = {
 229, 167, 252, 92, 
 7, 95, 174, 60, 
 43, 16, 126, 25, 
 225, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len35_anagram0 = {
  LengthAndAnagram(35, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Macro_len35_anagram0_chords, // chords
  kmap0_Macro_len35_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len37_anagram0_chords[1] = {
 ChordData({2, 136, 0}), 
};

const uint8_t kmap0_Macro_len37_anagram0_seqs[5] = {
 64, 48, 16, 124, 
 29, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len37_anagram0 = {
  LengthAndAnagram(37, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len37_anagram0_chords, // chords
  kmap0_Macro_len37_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len39_anagram0_chords[2] = {
 ChordData({4, 32, 1}), ChordData({32, 32, 1}), 
};

const uint8_t kmap0_Macro_len39_anagram0_seqs[10] = {
 64, 8, 32, 228, 
 117, 32, 44, 16, 
 250, 58, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len39_anagram0 = {
  LengthAndAnagram(39, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len39_anagram0_chords, // chords
  kmap0_Macro_len39_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len40_anagram0_chords[4] = {
 ChordData({0, 40, 1}), ChordData({2, 160, 1}), ChordData({2, 160, 9}), ChordData({2, 160, 73}), 
};

const uint8_t kmap0_Macro_len40_anagram0_seqs[20] = {
 224, 90, 64, 152, 
 235, 229, 162, 236, 
 121, 109, 229, 162, 
 236, 121, 237, 229, 
 162, 236, 41, 84, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len40_anagram0 = {
  LengthAndAnagram(40, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Macro_len40_anagram0_chords, // chords
  kmap0_Macro_len40_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len42_anagram0_chords[1] = {
 ChordData({0, 160, 10}), 
};

const uint8_t kmap0_Macro_len42_anagram0_seqs[6] = {
 194, 43, 136, 32, 
 194, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len42_anagram0 = {
  LengthAndAnagram(42, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len42_anagram0_chords, // chords
  kmap0_Macro_len42_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len43_anagram0_chords[2] = {
 ChordData({2, 68, 1}), ChordData({2, 160, 65}), 
};

const uint8_t kmap0_Macro_len43_anagram0_seqs[11] = {
 160, 124, 129, 80, 
 149, 91, 216, 44, 
 104, 32, 12, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len43_anagram0 = {
  LengthAndAnagram(43, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len43_anagram0_chords, // chords
  kmap0_Macro_len43_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len44_anagram0_chords[2] = {
 ChordData({0, 132, 130}), ChordData({0, 172, 1}), 
};

const uint8_t kmap0_Macro_len44_anagram0_seqs[11] = {
 229, 115, 85, 158, 
 229, 9, 174, 37, 
 248, 129, 48, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len44_anagram0 = {
  LengthAndAnagram(44, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Macro_len44_anagram0_chords, // chords
  kmap0_Macro_len44_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len55_anagram0_chords[1] = {
 ChordData({2, 128, 10}), 
};

const uint8_t kmap0_Macro_len55_anagram0_seqs[7] = {
 224, 218, 91, 145, 
 178, 116, 57, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len55_anagram0 = {
  LengthAndAnagram(55, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len55_anagram0_chords, // chords
  kmap0_Macro_len55_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len57_anagram0_chords[1] = {
 ChordData({16, 192, 136}), 
};

const uint8_t kmap0_Macro_len57_anagram0_seqs[8] = {
 224, 90, 224, 90, 
 229, 172, 146, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len57_anagram0 = {
  LengthAndAnagram(57, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len57_anagram0_chords, // chords
  kmap0_Macro_len57_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len58_anagram0_chords[1] = {
 ChordData({160, 128, 3}), 
};

const uint8_t kmap0_Macro_len58_anagram0_seqs[8] = {
 24, 121, 203, 129, 
 107, 129, 107, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len58_anagram0 = {
  LengthAndAnagram(58, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len58_anagram0_chords, // chords
  kmap0_Macro_len58_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len60_anagram0_chords[1] = {
 ChordData({4, 128, 18}), 
};

const uint8_t kmap0_Macro_len60_anagram0_seqs[8] = {
 117, 90, 23, 8, 
 1, 132, 188, 14, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len60_anagram0 = {
  LengthAndAnagram(60, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len60_anagram0_chords, // chords
  kmap0_Macro_len60_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len61_anagram0_chords[1] = {
 ChordData({18, 128, 131}), 
};

const uint8_t kmap0_Macro_len61_anagram0_seqs[8] = {
 190, 234, 5, 66, 
 92, 59, 16, 18, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len61_anagram0 = {
  LengthAndAnagram(61, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len61_anagram0_chords, // chords
  kmap0_Macro_len61_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len65_anagram0_chords[1] = {
 ChordData({16, 128, 18}), 
};

const uint8_t kmap0_Macro_len65_anagram0_seqs[9] = {
 232, 153, 114, 224, 
 90, 224, 90, 229, 
 0, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len65_anagram0 = {
  LengthAndAnagram(65, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len65_anagram0_chords, // chords
  kmap0_Macro_len65_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len70_anagram0_chords[1] = {
 ChordData({4, 128, 130}), 
};

const uint8_t kmap0_Macro_len70_anagram0_seqs[9] = {
 130, 194, 94, 87, 
 32, 44, 16, 250, 
 58, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len70_anagram0 = {
  LengthAndAnagram(70, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len70_anagram0_chords, // chords
  kmap0_Macro_len70_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len74_anagram0_chords[1] = {
 ChordData({16, 128, 2}), 
};

const uint8_t kmap0_Macro_len74_anagram0_seqs[10] = {
 38, 54, 16, 86, 
 56, 225, 128, 208, 
 130, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len74_anagram0 = {
  LengthAndAnagram(74, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len74_anagram0_chords, // chords
  kmap0_Macro_len74_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len76_anagram0_chords[1] = {
 ChordData({16, 192, 10}), 
};

const uint8_t kmap0_Macro_len76_anagram0_seqs[10] = {
 64, 248, 64, 248, 
 234, 11, 16, 2, 
 8, 9, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len76_anagram0 = {
  LengthAndAnagram(76, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len76_anagram0_chords, // chords
  kmap0_Macro_len76_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len88_anagram0_chords[1] = {
 ChordData({18, 132, 0}), 
};

const uint8_t kmap0_Macro_len88_anagram0_seqs[11] = {
 215, 42, 247, 250, 
 247, 124, 2, 194, 
 47, 87, 190, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len88_anagram0 = {
  LengthAndAnagram(88, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len88_anagram0_chords, // chords
  kmap0_Macro_len88_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len91_anagram0_chords[1] = {
 ChordData({2, 132, 66}), 
};

const uint8_t kmap0_Macro_len91_anagram0_seqs[12] = {
 224, 218, 65, 249, 
 10, 239, 217, 42, 
 188, 231, 51, 4, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len91_anagram0 = {
  LengthAndAnagram(91, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len91_anagram0_chords, // chords
  kmap0_Macro_len91_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len109_anagram0_chords[1] = {
 ChordData({36, 160, 1}), 
};

const uint8_t kmap0_Macro_len109_anagram0_seqs[14] = {
 64, 8, 32, 36, 
 16, 86, 56, 32, 
 180, 32, 66, 185, 
 126, 29, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len109_anagram0 = {
  LengthAndAnagram(109, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len109_anagram0_chords, // chords
  kmap0_Macro_len109_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len111_anagram0_chords[1] = {
 ChordData({4, 132, 82}), 
};

const uint8_t kmap0_Macro_len111_anagram0_seqs[14] = {
 64, 48, 16, 12, 
 4, 3, 193, 64, 
 48, 16, 124, 253, 
 250, 117, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len111_anagram0 = {
  LengthAndAnagram(111, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len111_anagram0_chords, // chords
  kmap0_Macro_len111_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len114_anagram0_chords[1] = {
 ChordData({0, 168, 17}), 
};

const uint8_t kmap0_Macro_len114_anagram0_seqs[15] = {
 229, 4, 13, 132, 
 41, 7, 132, 21, 
 14, 8, 45, 136, 
 80, 174, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len114_anagram0 = {
  LengthAndAnagram(114, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len114_anagram0_chords, // chords
  kmap0_Macro_len114_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len118_anagram0_chords[1] = {
 ChordData({4, 128, 64}), 
};

const uint8_t kmap0_Macro_len118_anagram0_seqs[15] = {
 128, 61, 253, 36, 
 76, 157, 214, 5, 
 66, 0, 33, 133, 
 127, 253, 58, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len118_anagram0 = {
  LengthAndAnagram(118, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len118_anagram0_chords, // chords
  kmap0_Macro_len118_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len119_anagram0_chords[1] = {
 ChordData({2, 128, 2}), 
};

const uint8_t kmap0_Macro_len119_anagram0_seqs[15] = {
 125, 0, 33, 128, 
 144, 64, 88, 225, 
 128, 208, 130, 8, 
 229, 250, 117, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len119_anagram0 = {
  LengthAndAnagram(119, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len119_anagram0_chords, // chords
  kmap0_Macro_len119_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len122_anagram0_chords[1] = {
 ChordData({34, 141, 128}), 
};

const uint8_t kmap0_Macro_len122_anagram0_seqs[16] = {
 22, 102, 132, 73, 
 191, 107, 14, 5, 
 215, 118, 167, 111, 
 18, 6, 35, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len122_anagram0 = {
  LengthAndAnagram(122, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len122_anagram0_chords, // chords
  kmap0_Macro_len122_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len126_anagram0_chords[1] = {
 ChordData({4, 128, 192}), 
};

const uint8_t kmap0_Macro_len126_anagram0_seqs[16] = {
 128, 61, 253, 36, 
 76, 157, 214, 37, 
 5, 66, 0, 33, 
 133, 127, 253, 58, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len126_anagram0 = {
  LengthAndAnagram(126, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len126_anagram0_chords, // chords
  kmap0_Macro_len126_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len130_anagram0_chords[1] = {
 ChordData({38, 140, 128}), 
};

const uint8_t kmap0_Macro_len130_anagram0_seqs[17] = {
 22, 95, 129, 160, 
 211, 239, 154, 67, 
 193, 181, 157, 19, 
 23, 21, 198, 50, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len130_anagram0 = {
  LengthAndAnagram(130, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len130_anagram0_chords, // chords
  kmap0_Macro_len130_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len132_anagram0_chords[1] = {
 ChordData({18, 224, 130}), 
};

const uint8_t kmap0_Macro_len132_anagram0_seqs[17] = {
 23, 216, 100, 32, 
 4, 16, 18, 8, 
 43, 28, 16, 90, 
 16, 161, 92, 191, 
 14, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len132_anagram0 = {
  LengthAndAnagram(132, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len132_anagram0_chords, // chords
  kmap0_Macro_len132_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len151_anagram0_chords[1] = {
 ChordData({4, 128, 2}), 
};

const uint8_t kmap0_Macro_len151_anagram0_seqs[19] = {
 117, 90, 247, 0, 
 66, 0, 193, 194, 
 1, 193, 64, 72, 
 225, 95, 191, 126, 
 253, 250, 117, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len151_anagram0 = {
  LengthAndAnagram(151, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len151_anagram0_chords, // chords
  kmap0_Macro_len151_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len163_anagram0_chords[1] = {
 ChordData({0, 129, 2}), 
};

const uint8_t kmap0_Macro_len163_anagram0_seqs[21] = {
 71, 12, 16, 66, 
 248, 194, 7, 66, 
 2, 97, 133, 3, 
 66, 11, 34, 148, 
 235, 215, 175, 95, 
 7, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len163_anagram0 = {
  LengthAndAnagram(163, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len163_anagram0_chords, // chords
  kmap0_Macro_len163_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len174_anagram0_chords[1] = {
 ChordData({4, 128, 16}), 
};

const uint8_t kmap0_Macro_len174_anagram0_seqs[22] = {
 117, 90, 151, 20, 
 148, 47, 16, 2, 
 8, 6, 194, 2, 
 161, 129, 224, 107, 
 1, 33, 133, 127, 
 253, 58, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len174_anagram0 = {
  LengthAndAnagram(174, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len174_anagram0_chords, // chords
  kmap0_Macro_len174_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len180_anagram0_chords[1] = {
 ChordData({32, 137, 16}), 
};

const uint8_t kmap0_Macro_len180_anagram0_seqs[23] = {
 135, 150, 3, 66, 
 0, 225, 97, 211, 
 1, 132, 4, 194, 
 10, 7, 132, 22, 
 68, 40, 215, 175, 
 95, 191, 14, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len180_anagram0 = {
  LengthAndAnagram(180, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len180_anagram0_chords, // chords
  kmap0_Macro_len180_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len207_anagram0_chords[1] = {
 ChordData({4, 192, 16}), 
};

const uint8_t kmap0_Macro_len207_anagram0_seqs[26] = {
 117, 90, 151, 20, 
 148, 47, 16, 2, 
 8, 6, 194, 2, 
 225, 3, 225, 5, 
 66, 3, 193, 215, 
 2, 66, 10, 255, 
 250, 117, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len207_anagram0 = {
  LengthAndAnagram(207, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len207_anagram0_chords, // chords
  kmap0_Macro_len207_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len216_anagram0_chords[1] = {
 ChordData({32, 137, 80}), 
};

const uint8_t kmap0_Macro_len216_anagram0_seqs[27] = {
 135, 150, 3, 66, 
 0, 225, 97, 211, 
 1, 132, 4, 194, 
 10, 7, 132, 22, 
 68, 40, 215, 175, 
 95, 191, 126, 253, 
 250, 245, 235, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len216_anagram0 = {
  LengthAndAnagram(216, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len216_anagram0_chords, // chords
  kmap0_Macro_len216_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len217_anagram0_chords[1] = {
 ChordData({0, 129, 16}), 
};

const uint8_t kmap0_Macro_len217_anagram0_seqs[28] = {
 135, 150, 3, 66, 
 0, 33, 203, 9, 
 26, 8, 83, 14, 
 8, 43, 28, 16, 
 90, 16, 161, 92, 
 191, 126, 253, 250, 
 245, 235, 215, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len217_anagram0 = {
  LengthAndAnagram(217, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len217_anagram0_chords, // chords
  kmap0_Macro_len217_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len247_anagram0_chords[1] = {
 ChordData({2, 128, 128}), 
};

const uint8_t kmap0_Macro_len247_anagram0_seqs[31] = {
 130, 58, 125, 183, 
 2, 97, 123, 157, 
 186, 172, 129, 208, 
 194, 9, 39, 40, 
 171, 4, 194, 246, 
 58, 117, 89, 3, 
 161, 5, 17, 84, 
 175, 83, 57, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len247_anagram0 = {
  LengthAndAnagram(247, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len247_anagram0_chords, // chords
  kmap0_Macro_len247_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len253_anagram0_chords[1] = {
 ChordData({16, 128, 128}), 
};

const uint8_t kmap0_Macro_len253_anagram0_seqs[32] = {
 130, 58, 125, 183, 
 2, 97, 173, 57, 
 121, 126, 13, 132, 
 22, 78, 56, 65, 
 89, 37, 16, 214, 
 154, 147, 231, 215, 
 64, 104, 65, 4, 
 213, 235, 84, 14, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len253_anagram0 = {
  LengthAndAnagram(253, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len253_anagram0_chords, // chords
  kmap0_Macro_len253_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len264_anagram0_chords[1] = {
 ChordData({18, 193, 0}), 
};

const uint8_t kmap0_Macro_len264_anagram0_seqs[33] = {
 224, 218, 251, 80, 
 233, 163, 28, 128, 
 194, 129, 107, 151, 
 62, 90, 93, 14, 
 64, 225, 132, 19, 
 14, 92, 187, 85, 
 246, 33, 136, 32, 
 130, 8, 34, 148, 
 235, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len264_anagram0 = {
  LengthAndAnagram(264, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len264_anagram0_chords, // chords
  kmap0_Macro_len264_anagram0_seqs, // sequences
};

const ChordData kmap0_Macro_len296_anagram0_chords[1] = {
 ChordData({0, 129, 80}), 
};

const uint8_t kmap0_Macro_len296_anagram0_seqs[37] = {
 135, 150, 3, 66, 
 0, 225, 97, 211, 
 1, 132, 44, 39, 
 104, 32, 76, 57, 
 32, 172, 112, 64, 
 104, 65, 132, 114, 
 253, 250, 245, 235, 
 215, 175, 95, 191, 
 126, 253, 250, 245, 
 235, 
};

const LookupKmapTypeLenAnagram kmap0_Macro_len296_anagram0 = {
  LengthAndAnagram(296, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Macro_len296_anagram0_chords, // chords
  kmap0_Macro_len296_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap0_Macro_lookups_array[57] = {
 &kmap0_Macro_len15_anagram0, &kmap0_Macro_len16_anagram0, &kmap0_Macro_len17_anagram0, &kmap0_Macro_len18_anagram0, 
 &kmap0_Macro_len19_anagram0, &kmap0_Macro_len20_anagram0, &kmap0_Macro_len21_anagram0, &kmap0_Macro_len22_anagram0, 
 &kmap0_Macro_len23_anagram0, &kmap0_Macro_len24_anagram0, &kmap0_Macro_len25_anagram0, &kmap0_Macro_len26_anagram0, 
 &kmap0_Macro_len27_anagram0, &kmap0_Macro_len29_anagram0, &kmap0_Macro_len30_anagram0, &kmap0_Macro_len31_anagram0, 
 &kmap0_Macro_len32_anagram0, &kmap0_Macro_len33_anagram0, &kmap0_Macro_len34_anagram0, &kmap0_Macro_len35_anagram0, 
 &kmap0_Macro_len37_anagram0, &kmap0_Macro_len39_anagram0, &kmap0_Macro_len40_anagram0, &kmap0_Macro_len42_anagram0, 
 &kmap0_Macro_len43_anagram0, &kmap0_Macro_len44_anagram0, &kmap0_Macro_len55_anagram0, &kmap0_Macro_len57_anagram0, 
 &kmap0_Macro_len58_anagram0, &kmap0_Macro_len60_anagram0, &kmap0_Macro_len61_anagram0, &kmap0_Macro_len65_anagram0, 
 &kmap0_Macro_len70_anagram0, &kmap0_Macro_len74_anagram0, &kmap0_Macro_len76_anagram0, &kmap0_Macro_len88_anagram0, 
 &kmap0_Macro_len91_anagram0, &kmap0_Macro_len109_anagram0, &kmap0_Macro_len111_anagram0, &kmap0_Macro_len114_anagram0, 
 &kmap0_Macro_len118_anagram0, &kmap0_Macro_len119_anagram0, &kmap0_Macro_len122_anagram0, &kmap0_Macro_len126_anagram0, 
 &kmap0_Macro_len130_anagram0, &kmap0_Macro_len132_anagram0, &kmap0_Macro_len151_anagram0, &kmap0_Macro_len163_anagram0, 
 &kmap0_Macro_len174_anagram0, &kmap0_Macro_len180_anagram0, &kmap0_Macro_len207_anagram0, &kmap0_Macro_len216_anagram0, 
 &kmap0_Macro_len217_anagram0, &kmap0_Macro_len247_anagram0, &kmap0_Macro_len253_anagram0, &kmap0_Macro_len264_anagram0, 
 &kmap0_Macro_len296_anagram0, 
};

const LookupKmapType kmap0_Macro_lookups = {
  57, // num_lookups
  kmap0_Macro_lookups_array, // lookups
};

const ChordData kmap0_Command_len15_anagram0_chords[13] = {
 ChordData({0, 32, 9}), ChordData({0, 192, 1}), ChordData({0, 192, 2}), ChordData({20, 128, 0}), 
 ChordData({36, 73, 146}), ChordData({36, 128, 0}), ChordData({36, 137, 2}), ChordData({36, 137, 16}), 
 ChordData({36, 169, 0}), ChordData({146, 0, 0}), ChordData({146, 0, 4}), ChordData({146, 16, 0}), 
 ChordData({210, 0, 0}), 
};

const uint8_t kmap0_Command_len15_anagram0_seqs[25] = {
 215, 164, 242, 71, 
 121, 253, 154, 126, 
 141, 42, 111, 151, 
 215, 174, 105, 229, 
 215, 242, 111, 121, 
 245, 26, 95, 94, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Command_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  13, // num_chords
  kmap0_Command_len15_anagram0_chords, // chords
  kmap0_Command_len15_anagram0_seqs, // sequences
};

const ChordData kmap0_Command_len28_anagram0_chords[2] = {
 ChordData({0, 64, 146}), ChordData({36, 9, 0}), 
};

const uint8_t kmap0_Command_len28_anagram0_seqs[7] = {
 215, 224, 26, 122, 
 13, 202, 187, 
};

const LookupKmapTypeLenAnagram kmap0_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Command_len28_anagram0_chords, // chords
  kmap0_Command_len28_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap0_Command_lookups_array[2] = {
 &kmap0_Command_len15_anagram0, &kmap0_Command_len28_anagram0, 
};

const LookupKmapType kmap0_Command_lookups = {
  2, // num_lookups
  kmap0_Command_lookups_array, // lookups
};

const ChordData kmap0_Word_len4_anagram1_chords[3] = {
 ChordData({0, 0, 16}), ChordData({0, 0, 64}), ChordData({0, 4, 0}), 
};

const uint8_t kmap0_Word_len4_anagram1_seqs[2] = {
 195, 15, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len4_anagram1 = {
  LengthAndAnagram(4, 1), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Word_len4_anagram1_chords, // chords
  kmap0_Word_len4_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len5_anagram1_chords[2] = {
 ChordData({0, 64, 0}), ChordData({32, 0, 0}), 
};

const uint8_t kmap0_Word_len5_anagram1_seqs[2] = {
 50, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len5_anagram1 = {
  LengthAndAnagram(5, 1), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len5_anagram1_chords, // chords
  kmap0_Word_len5_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len7_anagram0_chords[2] = {
 ChordData({16, 0, 8}), ChordData({16, 0, 16}), 
};

const uint8_t kmap0_Word_len7_anagram0_seqs[2] = {
 86, 15, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len7_anagram0_chords, // chords
  kmap0_Word_len7_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len7_anagram1_chords[2] = {
 ChordData({16, 0, 16}), ChordData({16, 0, 64}), 
};

const uint8_t kmap0_Word_len7_anagram1_seqs[2] = {
 99, 51, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len7_anagram1 = {
  LengthAndAnagram(7, 1), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len7_anagram1_chords, // chords
  kmap0_Word_len7_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len8_anagram0_chords[18] = {
 ChordData({0, 0, 136}), ChordData({0, 0, 192}), ChordData({0, 4, 1}), ChordData({0, 4, 2}), 
 ChordData({0, 4, 8}), ChordData({0, 4, 64}), ChordData({2, 0, 1}), ChordData({2, 0, 2}), 
 ChordData({2, 0, 8}), ChordData({2, 0, 64}), ChordData({16, 8, 0}), ChordData({16, 32, 0}), 
 ChordData({16, 64, 0}), ChordData({128, 0, 1}), ChordData({128, 0, 2}), ChordData({128, 0, 8}), 
 ChordData({128, 0, 16}), ChordData({128, 0, 64}), 
};

const uint8_t kmap0_Word_len8_anagram0_seqs[18] = {
 164, 196, 191, 143, 
 175, 207, 189, 141, 
 173, 205, 201, 208, 
 150, 27, 24, 161, 
 49, 28, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len8_anagram0 = {
  LengthAndAnagram(8, 0), // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_Word_len8_anagram0_chords, // chords
  kmap0_Word_len8_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len8_anagram1_chords[5] = {
 ChordData({0, 0, 130}), ChordData({0, 4, 128}), ChordData({16, 8, 0}), ChordData({16, 64, 0}), 
 ChordData({128, 0, 8}), 
};

const uint8_t kmap0_Word_len8_anagram1_seqs[5] = {
 87, 79, 78, 210, 
 26, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len8_anagram1 = {
  LengthAndAnagram(8, 1), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Word_len8_anagram1_chords, // chords
  kmap0_Word_len8_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len9_anagram0_chords[10] = {
 ChordData({0, 8, 16}), ChordData({0, 12, 0}), ChordData({0, 36, 0}), ChordData({2, 32, 0}), 
 ChordData({4, 0, 64}), ChordData({32, 0, 8}), ChordData({32, 0, 64}), ChordData({52, 0, 0}), 
 ChordData({128, 32, 0}), ChordData({128, 64, 0}), 
};

const uint8_t kmap0_Word_len9_anagram0_seqs[12] = {
 147, 62, 61, 132, 
 93, 57, 107, 230, 
 211, 1, 101, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  10, // num_chords
  kmap0_Word_len9_anagram0_chords, // chords
  kmap0_Word_len9_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len9_anagram1_chords[6] = {
 ChordData({0, 36, 0}), ChordData({0, 64, 2}), ChordData({2, 0, 0}), ChordData({2, 8, 0}), 
 ChordData({6, 0, 0}), ChordData({132, 0, 0}), 
};

const uint8_t kmap0_Word_len9_anagram1_seqs[7] = {
 240, 81, 130, 238, 
 84, 59, 42, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len9_anagram1 = {
  LengthAndAnagram(9, 1), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Word_len9_anagram1_chords, // chords
  kmap0_Word_len9_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len9_anagram2_chords[2] = {
 ChordData({4, 4, 0}), ChordData({6, 0, 0}), 
};

const uint8_t kmap0_Word_len9_anagram2_seqs[3] = {
 95, 187, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len9_anagram2 = {
  LengthAndAnagram(9, 2), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len9_anagram2_chords, // chords
  kmap0_Word_len9_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len10_anagram0_chords[7] = {
 ChordData({0, 0, 146}), ChordData({0, 1, 8}), ChordData({16, 0, 64}), ChordData({16, 64, 2}), 
 ChordData({38, 0, 0}), ChordData({128, 1, 0}), ChordData({160, 1, 0}), 
};

const uint8_t kmap0_Word_len10_anagram0_seqs[9] = {
 84, 28, 202, 246, 
 197, 103, 199, 113, 
 7, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len10_anagram0 = {
  LengthAndAnagram(10, 0), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Word_len10_anagram0_chords, // chords
  kmap0_Word_len10_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len10_anagram1_chords[7] = {
 ChordData({0, 0, 18}), ChordData({2, 1, 0}), ChordData({16, 0, 1}), ChordData({32, 1, 8}), 
 ChordData({32, 8, 1}), ChordData({32, 8, 64}), ChordData({36, 0, 0}), 
};

const uint8_t kmap0_Word_len10_anagram1_seqs[9] = {
 83, 244, 177, 182, 
 222, 43, 138, 156, 
 43, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len10_anagram1 = {
  LengthAndAnagram(10, 1), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Word_len10_anagram1_chords, // chords
  kmap0_Word_len10_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len10_anagram2_chords[1] = {
 ChordData({32, 8, 0}), 
};

const uint8_t kmap0_Word_len10_anagram2_seqs[2] = {
 57, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len10_anagram2 = {
  LengthAndAnagram(10, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len10_anagram2_chords, // chords
  kmap0_Word_len10_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len10_anagram3_chords[2] = {
 ChordData({32, 8, 0}), ChordData({34, 8, 0}), 
};

const uint8_t kmap0_Word_len10_anagram3_seqs[3] = {
 41, 139, 13, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len10_anagram3 = {
  LengthAndAnagram(10, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len10_anagram3_chords, // chords
  kmap0_Word_len10_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len10_anagram4_chords[1] = {
 ChordData({34, 1, 0}), 
};

const uint8_t kmap0_Word_len10_anagram4_seqs[2] = {
 119, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len10_anagram4 = {
  LengthAndAnagram(10, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len10_anagram4_chords, // chords
  kmap0_Word_len10_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len11_anagram0_chords[21] = {
 ChordData({0, 8, 18}), ChordData({0, 65, 0}), ChordData({16, 0, 3}), ChordData({16, 0, 9}), 
 ChordData({16, 0, 17}), ChordData({16, 0, 66}), ChordData({16, 0, 129}), ChordData({16, 0, 136}), 
 ChordData({16, 0, 144}), ChordData({16, 4, 1}), ChordData({16, 4, 2}), ChordData({16, 4, 16}), 
 ChordData({18, 0, 1}), ChordData({18, 0, 2}), ChordData({18, 0, 16}), ChordData({18, 0, 64}), 
 ChordData({18, 0, 128}), ChordData({128, 9, 0}), ChordData({144, 0, 1}), ChordData({144, 0, 2}), 
 ChordData({144, 0, 8}), 
};

const uint8_t kmap0_Word_len11_anagram0_seqs[29] = {
 169, 56, 164, 23, 
 215, 186, 30, 54, 
 146, 151, 172, 99, 
 242, 239, 163, 127, 
 188, 237, 70, 183, 
 167, 205, 212, 142, 
 210, 134, 141, 17, 
 106, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  21, // num_chords
  kmap0_Word_len11_anagram0_chords, // chords
  kmap0_Word_len11_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len11_anagram1_chords[8] = {
 ChordData({16, 0, 9}), ChordData({16, 0, 65}), ChordData({16, 0, 80}), ChordData({16, 0, 130}), 
 ChordData({16, 4, 1}), ChordData({16, 4, 64}), ChordData({20, 0, 0}), ChordData({32, 8, 0}), 
};

const uint8_t kmap0_Word_len11_anagram1_seqs[11] = {
 234, 101, 239, 152, 
 125, 245, 107, 246, 
 87, 59, 137, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len11_anagram1 = {
  LengthAndAnagram(11, 1), // seq_bit_len_and_anagram
  8, // num_chords
  kmap0_Word_len11_anagram1_chords, // chords
  kmap0_Word_len11_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len11_anagram2_chords[2] = {
 ChordData({16, 0, 65}), ChordData({16, 4, 1}), 
};

const uint8_t kmap0_Word_len11_anagram2_seqs[3] = {
 230, 93, 63, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len11_anagram2 = {
  LengthAndAnagram(11, 2), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len11_anagram2_chords, // chords
  kmap0_Word_len11_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len11_anagram3_chords[2] = {
 ChordData({16, 4, 16}), ChordData({144, 0, 8}), 
};

const uint8_t kmap0_Word_len11_anagram3_seqs[3] = {
 158, 87, 7, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len11_anagram3 = {
  LengthAndAnagram(11, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len11_anagram3_chords, // chords
  kmap0_Word_len11_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len11_anagram4_chords[1] = {
 ChordData({16, 4, 16}), 
};

const uint8_t kmap0_Word_len11_anagram4_seqs[2] = {
 254, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len11_anagram4 = {
  LengthAndAnagram(11, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len11_anagram4_chords, // chords
  kmap0_Word_len11_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len12_anagram0_chords[48] = {
 ChordData({0, 0, 81}), ChordData({0, 0, 82}), ChordData({0, 0, 131}), ChordData({0, 0, 208}), 
 ChordData({0, 4, 3}), ChordData({0, 4, 9}), ChordData({0, 4, 10}), ChordData({0, 4, 17}), 
 ChordData({0, 4, 24}), ChordData({0, 4, 65}), ChordData({0, 4, 128}), ChordData({0, 4, 136}), 
 ChordData({0, 72, 2}), ChordData({2, 0, 9}), ChordData({2, 0, 17}), ChordData({2, 0, 65}), 
 ChordData({2, 0, 66}), ChordData({2, 0, 72}), ChordData({2, 0, 128}), ChordData({2, 0, 129}), 
 ChordData({2, 0, 136}), ChordData({2, 4, 8}), ChordData({2, 4, 16}), ChordData({16, 0, 18}), 
 ChordData({16, 8, 8}), ChordData({16, 32, 1}), ChordData({16, 32, 64}), ChordData({16, 64, 8}), 
 ChordData({16, 64, 16}), ChordData({16, 64, 128}), ChordData({18, 64, 0}), ChordData({20, 0, 1}), 
 ChordData({20, 0, 8}), ChordData({20, 0, 16}), ChordData({20, 4, 0}), ChordData({36, 0, 18}), 
 ChordData({48, 0, 2}), ChordData({48, 0, 16}), ChordData({48, 0, 64}), ChordData({128, 0, 9}), 
 ChordData({128, 0, 10}), ChordData({128, 0, 24}), ChordData({128, 0, 128}), ChordData({128, 0, 129}), 
 ChordData({130, 0, 8}), ChordData({130, 0, 16}), ChordData({130, 0, 64}), ChordData({130, 0, 128}), 
};

const uint8_t kmap0_Word_len12_anagram0_seqs[72] = {
 188, 195, 131, 123, 
 37, 192, 248, 251, 
 186, 248, 186, 63, 
 243, 202, 191, 79, 
 68, 175, 151, 212, 
 186, 59, 221, 203, 
 216, 204, 173, 77, 
 68, 189, 218, 212, 
 175, 223, 227, 194, 
 201, 186, 208, 12, 
 109, 149, 99, 73, 
 150, 178, 93, 189, 
 213, 90, 199, 95, 
 125, 22, 152, 157, 
 199, 153, 173, 177, 
 24, 170, 49, 20, 
 68, 177, 29, 218, 
 49, 205, 17, 77, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len12_anagram0 = {
  LengthAndAnagram(12, 0), // seq_bit_len_and_anagram
  48, // num_chords
  kmap0_Word_len12_anagram0_chords, // chords
  kmap0_Word_len12_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len12_anagram1_chords[20] = {
 ChordData({0, 4, 3}), ChordData({0, 4, 9}), ChordData({0, 4, 17}), ChordData({0, 4, 18}), 
 ChordData({0, 4, 129}), ChordData({2, 0, 65}), ChordData({2, 0, 66}), ChordData({2, 0, 80}), 
 ChordData({16, 1, 0}), ChordData({16, 8, 1}), ChordData({16, 32, 16}), ChordData({20, 0, 16}), 
 ChordData({22, 0, 0}), ChordData({32, 1, 0}), ChordData({48, 0, 64}), ChordData({128, 0, 1}), 
 ChordData({128, 0, 9}), ChordData({128, 0, 72}), ChordData({128, 0, 130}), ChordData({144, 8, 0}), 
};

const uint8_t kmap0_Word_len12_anagram1_seqs[30] = {
 143, 171, 191, 63, 
 139, 63, 79, 219, 
 188, 140, 205, 61, 
 135, 157, 188, 208, 
 83, 61, 181, 125, 
 220, 156, 189, 17, 
 27, 202, 161, 24, 
 228, 20, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len12_anagram1 = {
  LengthAndAnagram(12, 1), // seq_bit_len_and_anagram
  20, // num_chords
  kmap0_Word_len12_anagram1_chords, // chords
  kmap0_Word_len12_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len12_anagram2_chords[9] = {
 ChordData({0, 0, 146}), ChordData({0, 4, 9}), ChordData({0, 4, 17}), ChordData({0, 4, 65}), 
 ChordData({0, 4, 129}), ChordData({2, 0, 9}), ChordData({2, 0, 65}), ChordData({16, 64, 8}), 
 ChordData({128, 0, 8}), 
};

const uint8_t kmap0_Word_len12_anagram2_seqs[14] = {
 115, 181, 175, 243, 
 203, 251, 244, 187, 
 173, 220, 43, 173, 
 26, 10, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len12_anagram2 = {
  LengthAndAnagram(12, 2), // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_Word_len12_anagram2_chords, // chords
  kmap0_Word_len12_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len12_anagram3_chords[1] = {
 ChordData({0, 4, 18}), 
};

const uint8_t kmap0_Word_len12_anagram3_seqs[2] = {
 63, 8, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len12_anagram3 = {
  LengthAndAnagram(12, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len12_anagram3_chords, // chords
  kmap0_Word_len12_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len13_anagram0_chords[63] = {
 ChordData({0, 12, 1}), ChordData({0, 12, 2}), ChordData({0, 12, 8}), ChordData({0, 12, 16}), 
 ChordData({0, 12, 128}), ChordData({0, 32, 129}), ChordData({0, 32, 192}), ChordData({0, 36, 64}), 
 ChordData({0, 64, 65}), ChordData({0, 64, 129}), ChordData({0, 64, 130}), ChordData({0, 68, 8}), 
 ChordData({0, 68, 64}), ChordData({2, 8, 1}), ChordData({2, 8, 2}), ChordData({2, 8, 8}), 
 ChordData({2, 8, 16}), ChordData({2, 12, 0}), ChordData({2, 32, 1}), ChordData({2, 32, 64}), 
 ChordData({2, 64, 16}), ChordData({2, 64, 64}), ChordData({2, 64, 128}), ChordData({2, 68, 0}), 
 ChordData({4, 0, 129}), ChordData({4, 0, 130}), ChordData({4, 4, 1}), ChordData({4, 4, 2}), 
 ChordData({4, 4, 8}), ChordData({4, 4, 128}), ChordData({6, 0, 1}), ChordData({6, 0, 8}), 
 ChordData({6, 0, 16}), ChordData({16, 0, 19}), ChordData({16, 0, 26}), ChordData({16, 0, 82}), 
 ChordData({16, 40, 0}), ChordData({16, 72, 0}), ChordData({20, 32, 0}), ChordData({32, 0, 3}), 
 ChordData({32, 0, 9}), ChordData({32, 0, 24}), ChordData({32, 0, 72}), ChordData({32, 0, 80}), 
 ChordData({32, 4, 128}), ChordData({48, 1, 1}), ChordData({48, 1, 128}), ChordData({48, 5, 0}), 
 ChordData({48, 8, 2}), ChordData({48, 12, 0}), ChordData({48, 64, 0}), ChordData({50, 8, 0}), 
 ChordData({52, 0, 1}), ChordData({128, 8, 2}), ChordData({128, 32, 1}), ChordData({128, 64, 128}), 
 ChordData({132, 0, 1}), ChordData({132, 0, 2}), ChordData({132, 0, 16}), ChordData({132, 0, 64}), 
 ChordData({160, 0, 1}), ChordData({160, 0, 16}), ChordData({160, 0, 64}), 
};

const uint8_t kmap0_Word_len13_anagram0_seqs[103] = {
 233, 55, 61, 166, 
 215, 159, 148, 158, 
 4, 175, 96, 134, 
 207, 188, 178, 204, 
 18, 202, 87, 201, 
 47, 83, 111, 106, 
 76, 173, 211, 233, 
 59, 193, 94, 216, 
 44, 123, 100, 51, 
 181, 252, 150, 149, 
 246, 170, 238, 87, 
 252, 90, 95, 233, 
 235, 118, 173, 173, 
 211, 181, 240, 22, 
 214, 194, 156, 12, 
 147, 101, 133, 198, 
 188, 154, 119, 178, 
 114, 214, 204, 147, 
 159, 110, 47, 249, 
 254, 219, 162, 241, 
 69, 203, 236, 22, 
 125, 122, 49, 18, 
 140, 13, 146, 27, 
 21, 163, 214, 137, 
 26, 28, 121, 35, 
 79, 100, 6, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len13_anagram0 = {
  LengthAndAnagram(13, 0), // seq_bit_len_and_anagram
  63, // num_chords
  kmap0_Word_len13_anagram0_chords, // chords
  kmap0_Word_len13_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len13_anagram1_chords[26] = {
 ChordData({0, 12, 2}), ChordData({0, 12, 16}), ChordData({0, 32, 64}), ChordData({0, 36, 1}), 
 ChordData({0, 68, 2}), ChordData({2, 8, 64}), ChordData({2, 32, 64}), ChordData({2, 64, 16}), 
 ChordData({4, 4, 1}), ChordData({4, 4, 2}), ChordData({4, 4, 16}), ChordData({4, 4, 64}), 
 ChordData({4, 4, 128}), ChordData({6, 0, 1}), ChordData({6, 0, 2}), ChordData({6, 0, 128}), 
 ChordData({16, 1, 16}), ChordData({32, 0, 24}), ChordData({34, 0, 8}), ChordData({48, 1, 8}), 
 ChordData({48, 1, 16}), ChordData({48, 8, 16}), ChordData({128, 64, 1}), ChordData({128, 64, 2}), 
 ChordData({128, 64, 16}), ChordData({132, 0, 1}), 
};

const uint8_t kmap0_Word_len13_anagram1_seqs[43] = {
 248, 105, 62, 49, 
 67, 248, 139, 47, 
 155, 83, 51, 156, 
 150, 245, 183, 62, 
 214, 31, 254, 90, 
 159, 106, 111, 109, 
 164, 174, 227, 35, 
 143, 102, 237, 219, 
 58, 190, 69, 143, 
 140, 149, 129, 19, 
 178, 198, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len13_anagram1 = {
  LengthAndAnagram(13, 1), // seq_bit_len_and_anagram
  26, // num_chords
  kmap0_Word_len13_anagram1_chords, // chords
  kmap0_Word_len13_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len13_anagram2_chords[6] = {
 ChordData({0, 12, 64}), ChordData({4, 4, 64}), ChordData({16, 8, 0}), ChordData({48, 1, 64}), 
 ChordData({48, 1, 128}), ChordData({132, 0, 1}), 
};

const uint8_t kmap0_Word_len13_anagram2_seqs[10] = {
 207, 137, 235, 39, 
 39, 246, 125, 155, 
 162, 46, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len13_anagram2 = {
  LengthAndAnagram(13, 2), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Word_len13_anagram2_chords, // chords
  kmap0_Word_len13_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len13_anagram3_chords[2] = {
 ChordData({6, 0, 64}), ChordData({128, 64, 2}), 
};

const uint8_t kmap0_Word_len13_anagram3_seqs[4] = {
 220, 21, 67, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len13_anagram3 = {
  LengthAndAnagram(13, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len13_anagram3_chords, // chords
  kmap0_Word_len13_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len14_anagram0_chords[76] = {
 ChordData({0, 0, 19}), ChordData({0, 0, 90}), ChordData({0, 4, 26}), ChordData({0, 4, 82}), 
 ChordData({0, 4, 146}), ChordData({0, 5, 1}), ChordData({0, 5, 8}), ChordData({0, 5, 16}), 
 ChordData({0, 44, 0}), ChordData({0, 68, 0}), ChordData({0, 76, 0}), ChordData({0, 96, 128}), 
 ChordData({0, 100, 0}), ChordData({2, 0, 19}), ChordData({2, 0, 146}), ChordData({2, 1, 1}), 
 ChordData({2, 1, 2}), ChordData({2, 1, 8}), ChordData({2, 40, 0}), ChordData({2, 64, 0}), 
 ChordData({2, 72, 0}), ChordData({4, 0, 2}), ChordData({4, 8, 1}), ChordData({4, 8, 2}), 
 ChordData({4, 8, 16}), ChordData({4, 12, 0}), ChordData({4, 68, 0}), ChordData({6, 32, 0}), 
 ChordData({6, 64, 0}), ChordData({16, 0, 10}), ChordData({16, 0, 72}), ChordData({16, 0, 192}), 
 ChordData({16, 32, 18}), ChordData({16, 64, 10}), ChordData({16, 65, 0}), ChordData({32, 1, 2}), 
 ChordData({32, 5, 1}), ChordData({32, 5, 2}), ChordData({32, 5, 16}), ChordData({32, 5, 64}), 
 ChordData({32, 5, 128}), ChordData({32, 8, 1}), ChordData({32, 8, 8}), ChordData({32, 8, 16}), 
 ChordData({32, 8, 64}), ChordData({32, 12, 1}), ChordData({32, 12, 8}), ChordData({32, 12, 16}), 
 ChordData({32, 12, 128}), ChordData({32, 64, 16}), ChordData({34, 1, 1}), ChordData({34, 1, 8}), 
 ChordData({34, 1, 64}), ChordData({34, 12, 0}), ChordData({36, 4, 1}), ChordData({36, 4, 2}), 
 ChordData({36, 4, 8}), ChordData({36, 4, 16}), ChordData({36, 4, 128}), ChordData({38, 0, 1}), 
 ChordData({38, 0, 8}), ChordData({38, 0, 128}), ChordData({48, 9, 0}), ChordData({48, 72, 0}), 
 ChordData({52, 64, 0}), ChordData({128, 0, 18}), ChordData({128, 0, 19}), ChordData({128, 1, 16}), 
 ChordData({128, 72, 0}), ChordData({132, 32, 0}), ChordData({132, 64, 0}), ChordData({160, 1, 1}), 
 ChordData({160, 1, 128}), ChordData({160, 5, 0}), ChordData({160, 64, 0}), ChordData({166, 0, 0}), 
};

const uint8_t kmap0_Word_len14_anagram0_seqs[133] = {
 59, 5, 23, 250, 
 90, 240, 23, 244, 
 197, 241, 123, 188, 
 30, 63, 240, 211, 
 75, 153, 94, 10, 
 150, 240, 101, 111, 
 209, 84, 28, 189, 
 71, 99, 235, 1, 
 59, 201, 150, 169, 
 37, 214, 186, 169, 
 166, 138, 83, 83, 
 250, 90, 95, 86, 
 216, 178, 171, 21, 
 205, 182, 154, 216, 
 208, 133, 250, 34, 
 125, 220, 136, 251, 
 247, 141, 255, 115, 
 223, 207, 244, 119, 
 202, 171, 57, 77, 
 78, 156, 147, 248, 
 43, 190, 138, 63, 
 226, 147, 204, 115, 
 247, 182, 222, 220, 
 183, 216, 191, 127, 
 226, 159, 231, 235, 
 249, 67, 127, 158, 
 189, 103, 43, 245, 
 233, 116, 75, 139, 
 167, 101, 76, 177, 
 81, 28, 49, 41, 
 36, 140, 90, 67, 
 222, 177, 20, 247, 
 223, 33, 115, 156, 
 29, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  76, // num_chords
  kmap0_Word_len14_anagram0_chords, // chords
  kmap0_Word_len14_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len14_anagram1_chords[22] = {
 ChordData({0, 0, 82}), ChordData({0, 68, 0}), ChordData({2, 72, 0}), ChordData({4, 4, 0}), 
 ChordData({4, 12, 0}), ChordData({6, 32, 0}), ChordData({16, 0, 17}), ChordData({16, 0, 144}), 
 ChordData({16, 64, 3}), ChordData({32, 12, 16}), ChordData({34, 8, 0}), ChordData({36, 0, 1}), 
 ChordData({36, 0, 2}), ChordData({36, 0, 192}), ChordData({36, 4, 1}), ChordData({36, 4, 2}), 
 ChordData({48, 9, 0}), ChordData({52, 1, 0}), ChordData({128, 8, 0}), ChordData({128, 64, 0}), 
 ChordData({144, 64, 2}), ChordData({160, 1, 16}), 
};

const uint8_t kmap0_Word_len14_anagram1_seqs[39] = {
 92, 176, 124, 41, 
 59, 125, 173, 159, 
 42, 236, 186, 99, 
 143, 77, 23, 239, 
 139, 211, 57, 213, 
 188, 152, 43, 157, 
 124, 254, 254, 137, 
 201, 119, 245, 157, 
 34, 133, 148, 113, 
 113, 204, 13, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len14_anagram1 = {
  LengthAndAnagram(14, 1), // seq_bit_len_and_anagram
  22, // num_chords
  kmap0_Word_len14_anagram1_chords, // chords
  kmap0_Word_len14_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len14_anagram2_chords[10] = {
 ChordData({0, 0, 18}), ChordData({16, 0, 9}), ChordData({16, 0, 129}), ChordData({16, 65, 0}), 
 ChordData({32, 8, 64}), ChordData({48, 9, 0}), ChordData({128, 1, 0}), ChordData({132, 0, 0}), 
 ChordData({164, 0, 1}), ChordData({164, 0, 16}), 
};

const uint8_t kmap0_Word_len14_anagram2_seqs[18] = {
 56, 197, 218, 186, 
 38, 31, 150, 41, 
 243, 237, 116, 68, 
 212, 168, 103, 236, 
 196, 9, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len14_anagram2 = {
  LengthAndAnagram(14, 2), // seq_bit_len_and_anagram
  10, // num_chords
  kmap0_Word_len14_anagram2_chords, // chords
  kmap0_Word_len14_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len14_anagram3_chords[1] = {
 ChordData({164, 0, 16}), 
};

const uint8_t kmap0_Word_len14_anagram3_seqs[2] = {
 103, 12, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len14_anagram3 = {
  LengthAndAnagram(14, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len14_anagram3_chords, // chords
  kmap0_Word_len14_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len14_anagram4_chords[2] = {
 ChordData({0, 4, 18}), ChordData({164, 0, 16}), 
};

const uint8_t kmap0_Word_len14_anagram4_seqs[4] = {
 243, 197, 57, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len14_anagram4 = {
  LengthAndAnagram(14, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len14_anagram4_chords, // chords
  kmap0_Word_len14_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len15_anagram0_chords[74] = {
 ChordData({0, 8, 82}), ChordData({0, 8, 146}), ChordData({0, 9, 1}), ChordData({0, 12, 18}), 
 ChordData({0, 13, 64}), ChordData({0, 64, 18}), ChordData({0, 64, 82}), ChordData({0, 68, 66}), 
 ChordData({0, 68, 130}), ChordData({2, 9, 1}), ChordData({2, 9, 8}), ChordData({2, 64, 10}), 
 ChordData({4, 0, 82}), ChordData({4, 1, 1}), ChordData({4, 4, 18}), ChordData({16, 0, 11}), 
 ChordData({16, 0, 25}), ChordData({16, 0, 65}), ChordData({16, 0, 67}), ChordData({16, 0, 73}), 
 ChordData({16, 0, 81}), ChordData({16, 0, 128}), ChordData({16, 0, 130}), ChordData({16, 0, 200}), 
 ChordData({16, 4, 10}), ChordData({16, 4, 17}), ChordData({16, 4, 24}), ChordData({16, 4, 66}), 
 ChordData({16, 4, 129}), ChordData({16, 4, 136}), ChordData({16, 4, 144}), ChordData({16, 4, 192}), 
 ChordData({16, 8, 1}), ChordData({16, 8, 16}), ChordData({16, 8, 64}), ChordData({16, 32, 16}), 
 ChordData({16, 64, 64}), ChordData({16, 73, 0}), ChordData({18, 0, 3}), ChordData({18, 0, 8}), 
 ChordData({18, 0, 10}), ChordData({18, 0, 17}), ChordData({18, 0, 18}), ChordData({18, 0, 65}), 
 ChordData({18, 0, 130}), ChordData({18, 0, 136}), ChordData({32, 1, 8}), ChordData({32, 1, 16}), 
 ChordData({32, 9, 64}), ChordData({34, 8, 0}), ChordData({34, 65, 0}), ChordData({36, 0, 1}), 
 ChordData({36, 0, 16}), ChordData({36, 0, 64}), ChordData({36, 1, 64}), ChordData({36, 68, 0}), 
 ChordData({38, 8, 0}), ChordData({38, 64, 0}), ChordData({52, 0, 18}), ChordData({128, 13, 0}), 
 ChordData({128, 64, 3}), ChordData({128, 64, 10}), ChordData({128, 64, 18}), ChordData({128, 64, 130}), 
 ChordData({144, 0, 9}), ChordData({144, 0, 10}), ChordData({144, 0, 18}), ChordData({144, 0, 72}), 
 ChordData({144, 0, 80}), ChordData({144, 0, 136}), ChordData({144, 0, 144}), ChordData({144, 0, 192}), 
 ChordData({160, 0, 18}), ChordData({160, 33, 0}), 
};

const uint8_t kmap0_Word_len15_anagram0_seqs[139] = {
 92, 164, 34, 209, 
 177, 41, 125, 241, 
 92, 146, 83, 200, 
 130, 47, 207, 244, 
 151, 82, 111, 107, 
 233, 210, 202, 181, 
 56, 182, 214, 47, 
 208, 186, 99, 221, 
 53, 47, 27, 151, 
 173, 59, 230, 5, 
 100, 163, 137, 200, 
 202, 175, 232, 249, 
 181, 250, 7, 159, 
 77, 191, 38, 191, 
 142, 159, 248, 201, 
 201, 222, 228, 49, 
 219, 9, 122, 204, 
 182, 44, 73, 99, 
 175, 181, 213, 218, 
 232, 237, 177, 167, 
 145, 123, 141, 110, 
 162, 86, 31, 89, 
 143, 60, 137, 111, 
 177, 147, 236, 251, 
 204, 59, 249, 228, 
 124, 222, 149, 207, 
 151, 125, 166, 179, 
 229, 89, 56, 190, 
 180, 151, 208, 184, 
 76, 92, 40, 46, 
 26, 235, 80, 52, 
 198, 88, 131, 61, 
 193, 166, 80, 79, 
 144, 41, 216, 69, 
 100, 24, 55, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  74, // num_chords
  kmap0_Word_len15_anagram0_chords, // chords
  kmap0_Word_len15_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len15_anagram1_chords[42] = {
 ChordData({0, 9, 1}), ChordData({0, 13, 2}), ChordData({0, 68, 18}), ChordData({0, 68, 66}), 
 ChordData({0, 69, 0}), ChordData({2, 64, 3}), ChordData({4, 32, 0}), ChordData({4, 72, 0}), 
 ChordData({16, 0, 19}), ChordData({16, 0, 129}), ChordData({16, 0, 131}), ChordData({16, 0, 145}), 
 ChordData({16, 0, 192}), ChordData({16, 0, 194}), ChordData({16, 4, 16}), ChordData({16, 4, 18}), 
 ChordData({16, 4, 24}), ChordData({16, 4, 65}), ChordData({16, 4, 129}), ChordData({16, 4, 130}), 
 ChordData({16, 4, 136}), ChordData({16, 4, 192}), ChordData({16, 32, 128}), ChordData({16, 64, 2}), 
 ChordData({16, 64, 8}), ChordData({18, 0, 17}), ChordData({18, 0, 18}), ChordData({18, 0, 72}), 
 ChordData({18, 0, 80}), ChordData({32, 1, 16}), ChordData({32, 1, 128}), ChordData({32, 32, 0}), 
 ChordData({32, 72, 0}), ChordData({36, 5, 0}), ChordData({38, 1, 0}), ChordData({48, 1, 0}), 
 ChordData({128, 64, 3}), ChordData({128, 64, 10}), ChordData({144, 0, 8}), ChordData({144, 0, 9}), 
 ChordData({144, 0, 10}), ChordData({160, 65, 0}), 
};

const uint8_t kmap0_Word_len15_anagram1_seqs[79] = {
 105, 143, 199, 146, 
 252, 130, 255, 114, 
 188, 188, 244, 86, 
 88, 83, 149, 99, 
 220, 53, 209, 250, 
 74, 192, 75, 102, 
 102, 95, 253, 248, 
 241, 199, 254, 81, 
 246, 239, 62, 153, 
 30, 77, 175, 102, 
 63, 65, 155, 46, 
 150, 106, 203, 109, 
 207, 52, 154, 91, 
 205, 158, 158, 124, 
 31, 153, 96, 134, 
 41, 203, 251, 107, 
 237, 219, 247, 189, 
 113, 137, 139, 106, 
 168, 55, 212, 24, 
 106, 25, 55, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len15_anagram1 = {
  LengthAndAnagram(15, 1), // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_Word_len15_anagram1_chords, // chords
  kmap0_Word_len15_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len15_anagram2_chords[23] = {
 ChordData({0, 36, 18}), ChordData({0, 68, 18}), ChordData({2, 9, 64}), ChordData({16, 0, 25}), 
 ChordData({16, 0, 72}), ChordData({16, 0, 73}), ChordData({16, 0, 192}), ChordData({16, 4, 16}), 
 ChordData({16, 4, 17}), ChordData({16, 4, 18}), ChordData({16, 4, 65}), ChordData({16, 32, 1}), 
 ChordData({18, 0, 17}), ChordData({18, 0, 80}), ChordData({18, 0, 129}), ChordData({20, 0, 16}), 
 ChordData({32, 1, 8}), ChordData({32, 1, 128}), ChordData({36, 0, 1}), ChordData({36, 0, 64}), 
 ChordData({144, 0, 8}), ChordData({144, 0, 192}), ChordData({160, 65, 0}), 
};

const uint8_t kmap0_Word_len15_anagram2_seqs[44] = {
 240, 139, 249, 11, 
 151, 122, 61, 170, 
 102, 86, 243, 178, 
 137, 230, 199, 235, 
 159, 121, 180, 159, 
 119, 161, 221, 235, 
 153, 102, 111, 147, 
 171, 61, 119, 214, 
 131, 242, 230, 243, 
 204, 172, 14, 229, 
 32, 223, 33, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len15_anagram2 = {
  LengthAndAnagram(15, 2), // seq_bit_len_and_anagram
  23, // num_chords
  kmap0_Word_len15_anagram2_chords, // chords
  kmap0_Word_len15_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len15_anagram3_chords[4] = {
 ChordData({16, 0, 9}), ChordData({32, 1, 8}), ChordData({32, 13, 0}), ChordData({128, 64, 10}), 
};

const uint8_t kmap0_Word_len15_anagram3_seqs[8] = {
 107, 221, 91, 115, 
 250, 251, 18, 10, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len15_anagram3 = {
  LengthAndAnagram(15, 3), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Word_len15_anagram3_chords, // chords
  kmap0_Word_len15_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len15_anagram4_chords[1] = {
 ChordData({128, 64, 2}), 
};

const uint8_t kmap0_Word_len15_anagram4_seqs[2] = {
 24, 23, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len15_anagram4 = {
  LengthAndAnagram(15, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len15_anagram4_chords, // chords
  kmap0_Word_len15_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len15_anagram5_chords[1] = {
 ChordData({16, 4, 16}), 
};

const uint8_t kmap0_Word_len15_anagram5_seqs[2] = {
 227, 31, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len15_anagram5 = {
  LengthAndAnagram(15, 5), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len15_anagram5_chords, // chords
  kmap0_Word_len15_anagram5_seqs, // sequences
};

const ChordData kmap0_Word_len15_anagram7_chords[1] = {
 ChordData({0, 68, 18}), 
};

const uint8_t kmap0_Word_len15_anagram7_seqs[2] = {
 151, 31, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len15_anagram7 = {
  LengthAndAnagram(15, 7), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len15_anagram7_chords, // chords
  kmap0_Word_len15_anagram7_seqs, // sequences
};

const ChordData kmap0_Word_len16_anagram0_chords[138] = {
 ChordData({0, 0, 147}), ChordData({0, 1, 18}), ChordData({0, 1, 146}), ChordData({0, 4, 19}), 
 ChordData({0, 4, 67}), ChordData({0, 4, 74}), ChordData({0, 4, 129}), ChordData({0, 4, 130}), 
 ChordData({0, 4, 131}), ChordData({0, 4, 144}), ChordData({0, 4, 193}), ChordData({2, 0, 80}), 
 ChordData({2, 0, 137}), ChordData({2, 0, 192}), ChordData({2, 0, 193}), ChordData({2, 0, 194}), 
 ChordData({2, 1, 18}), ChordData({2, 4, 9}), ChordData({2, 4, 24}), ChordData({2, 4, 129}), 
 ChordData({2, 4, 136}), ChordData({2, 4, 144}), ChordData({2, 73, 0}), ChordData({4, 65, 0}), 
 ChordData({4, 68, 2}), ChordData({16, 1, 1}), ChordData({16, 1, 16}), ChordData({16, 1, 128}), 
 ChordData({16, 8, 9}), ChordData({16, 8, 17}), ChordData({16, 8, 65}), ChordData({16, 8, 129}), 
 ChordData({16, 9, 18}), ChordData({16, 12, 1}), ChordData({16, 12, 2}), ChordData({16, 12, 8}), 
 ChordData({16, 12, 64}), ChordData({16, 12, 128}), ChordData({16, 32, 3}), ChordData({16, 32, 9}), 
 ChordData({16, 32, 128}), ChordData({16, 32, 130}), ChordData({16, 32, 144}), ChordData({16, 36, 1}), 
 ChordData({16, 36, 2}), ChordData({16, 36, 16}), ChordData({16, 64, 9}), ChordData({16, 64, 72}), 
 ChordData({16, 64, 136}), ChordData({16, 65, 2}), ChordData({16, 68, 1}), ChordData({16, 68, 8}), 
 ChordData({16, 68, 16}), ChordData({16, 68, 128}), ChordData({18, 8, 1}), ChordData({18, 8, 2}), 
 ChordData({18, 8, 8}), ChordData({18, 8, 64}), ChordData({18, 8, 128}), ChordData({18, 32, 16}), 
 ChordData({18, 64, 1}), ChordData({18, 64, 16}), ChordData({18, 64, 64}), ChordData({18, 64, 128}), 
 ChordData({18, 68, 0}), ChordData({20, 0, 65}), ChordData({20, 0, 66}), ChordData({20, 0, 130}), 
 ChordData({20, 0, 144}), ChordData({20, 4, 1}), ChordData({20, 4, 2}), ChordData({20, 4, 64}), 
 ChordData({20, 4, 128}), ChordData({20, 8, 8}), ChordData({20, 64, 0}), ChordData({22, 0, 8}), 
 ChordData({22, 0, 16}), ChordData({22, 0, 128}), ChordData({22, 8, 0}), ChordData({32, 5, 0}), 
 ChordData({32, 5, 18}), ChordData({32, 8, 18}), ChordData({32, 33, 0}), ChordData({32, 72, 0}), 
 ChordData({34, 1, 0}), ChordData({36, 5, 0}), ChordData({36, 32, 0}), ChordData({38, 1, 0}), 
 ChordData({48, 0, 3}), ChordData({48, 0, 9}), ChordData({48, 0, 17}), ChordData({48, 0, 18}), 
 ChordData({48, 0, 80}), ChordData({48, 0, 144}), ChordData({48, 1, 8}), ChordData({48, 8, 8}), 
 ChordData({48, 8, 16}), ChordData({52, 0, 8}), ChordData({52, 64, 2}), ChordData({128, 0, 17}), 
 ChordData({128, 0, 25}), ChordData({128, 0, 67}), ChordData({128, 0, 72}), ChordData({128, 0, 81}), 
 ChordData({128, 0, 130}), ChordData({128, 0, 144}), ChordData({128, 0, 192}), ChordData({128, 0, 193}), 
 ChordData({128, 4, 3}), ChordData({128, 4, 8}), ChordData({128, 4, 18}), ChordData({128, 4, 136}), 
 ChordData({128, 4, 144}), ChordData({128, 4, 192}), ChordData({128, 96, 2}), ChordData({130, 0, 9}), 
 ChordData({130, 0, 10}), ChordData({130, 0, 24}), ChordData({130, 0, 72}), ChordData({130, 0, 130}), 
 ChordData({130, 0, 136}), ChordData({130, 0, 192}), ChordData({144, 8, 1}), ChordData({144, 8, 2}), 
 ChordData({144, 8, 16}), ChordData({144, 8, 64}), ChordData({144, 32, 2}), ChordData({144, 32, 16}), 
 ChordData({144, 32, 64}), ChordData({144, 64, 2}), ChordData({144, 64, 8}), ChordData({144, 64, 64}), 
 ChordData({148, 0, 1}), ChordData({148, 0, 2}), ChordData({148, 0, 8}), ChordData({148, 0, 64}), 
 ChordData({164, 0, 18}), ChordData({176, 0, 16}), 
};

const uint8_t kmap0_Word_len16_anagram0_seqs[276] = {
 184, 67, 199, 20, 
 7, 21, 248, 179, 
 248, 188, 140, 175, 
 251, 68, 248, 68, 
 251, 87, 2, 63, 
 244, 188, 61, 205, 
 212, 186, 220, 68, 
 212, 188, 220, 87, 
 125, 20, 175, 219, 
 243, 173, 251, 77, 
 250, 77, 243, 77, 
 165, 150, 85, 30, 
 245, 47, 135, 189, 
 199, 216, 135, 77, 
 201, 186, 235, 73, 
 188, 78, 201, 180, 
 37, 23, 235, 79, 
 248, 201, 250, 201, 
 252, 201, 201, 79, 
 107, 132, 11, 173, 
 208, 68, 208, 87, 
 130, 199, 208, 191, 
 126, 132, 208, 63, 
 107, 149, 108, 149, 
 100, 149, 135, 47, 
 242, 215, 210, 175, 
 227, 151, 210, 79, 
 219, 201, 169, 209, 
 169, 213, 236, 212, 
 169, 201, 176, 199, 
 150, 189, 211, 210, 
 220, 210, 45, 201, 
 45, 253, 188, 174, 
 92, 141, 190, 170, 
 213, 67, 251, 213, 
 248, 213, 213, 207, 
 245, 201, 101, 173, 
 210, 174, 181, 213, 
 211, 213, 181, 201, 
 93, 214, 247, 223, 
 247, 23, 69, 78, 
 48, 223, 82, 148, 
 71, 223, 231, 223, 
 48, 159, 103, 223, 
 152, 215, 155, 213, 
 59, 217, 152, 199, 
 156, 199, 147, 201, 
 183, 213, 22, 173, 
 22, 61, 167, 173, 
 23, 159, 19, 177, 
 59, 161, 24, 188, 
 28, 161, 28, 179, 
 24, 65, 19, 68, 
 20, 204, 20, 188, 
 24, 191, 250, 26, 
 49, 248, 20, 175, 
 49, 79, 79, 28, 
 48, 46, 219, 161, 
 141, 161, 61, 161, 
 220, 161, 24, 77, 
 212, 161, 28, 77, 
 41, 214, 24, 201, 
 41, 198, 28, 201, 
 70, 24, 208, 19, 
 12, 195, 24, 210, 
 50, 212, 50, 204, 
 53, 188, 24, 213, 
 81, 173, 53, 216, 
 103, 20, 206, 19, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  138, // num_chords
  kmap0_Word_len16_anagram0_chords, // chords
  kmap0_Word_len16_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len16_anagram1_chords[43] = {
 ChordData({0, 4, 65}), ChordData({0, 4, 81}), ChordData({0, 4, 130}), ChordData({0, 4, 193}), 
 ChordData({2, 0, 9}), ChordData({2, 0, 129}), ChordData({2, 4, 129}), ChordData({2, 4, 192}), 
 ChordData({16, 8, 64}), ChordData({16, 12, 1}), ChordData({16, 12, 8}), ChordData({16, 12, 128}), 
 ChordData({16, 36, 1}), ChordData({16, 36, 2}), ChordData({16, 64, 24}), ChordData({16, 68, 16}), 
 ChordData({16, 68, 128}), ChordData({16, 72, 0}), ChordData({18, 8, 1}), ChordData({18, 8, 128}), 
 ChordData({18, 64, 1}), ChordData({22, 0, 2}), ChordData({32, 9, 0}), ChordData({38, 0, 0}), 
 ChordData({48, 0, 80}), ChordData({52, 0, 16}), ChordData({128, 0, 129}), ChordData({128, 0, 192}), 
 ChordData({128, 0, 193}), ChordData({128, 1, 0}), ChordData({128, 4, 129}), ChordData({128, 4, 130}), 
 ChordData({128, 96, 2}), ChordData({130, 0, 9}), ChordData({130, 0, 10}), ChordData({144, 32, 64}), 
 ChordData({144, 32, 128}), ChordData({144, 64, 8}), ChordData({144, 64, 64}), ChordData({148, 0, 8}), 
 ChordData({148, 0, 16}), ChordData({148, 0, 128}), ChordData({160, 1, 0}), 
};

const uint8_t kmap0_Word_len16_anagram1_seqs[86] = {
 188, 191, 188, 63, 
 248, 132, 252, 180, 
 173, 189, 219, 180, 
 219, 79, 252, 77, 
 201, 204, 233, 215, 
 201, 175, 233, 201, 
 240, 215, 143, 208, 
 234, 145, 210, 63, 
 228, 151, 210, 78, 
 189, 78, 212, 201, 
 178, 189, 174, 141, 
 41, 223, 103, 159, 
 153, 61, 167, 61, 
 27, 65, 28, 20, 
 76, 177, 113, 28, 
 79, 27, 24, 79, 
 23, 24, 173, 27, 
 24, 173, 48, 216, 
 48, 200, 26, 210, 
 50, 216, 26, 213, 
 19, 213, 53, 200, 
 71, 220, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len16_anagram1 = {
  LengthAndAnagram(16, 1), // seq_bit_len_and_anagram
  43, // num_chords
  kmap0_Word_len16_anagram1_chords, // chords
  kmap0_Word_len16_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len16_anagram2_chords[14] = {
 ChordData({0, 4, 3}), ChordData({2, 0, 193}), ChordData({16, 12, 1}), ChordData({16, 68, 16}), 
 ChordData({18, 64, 1}), ChordData({18, 64, 2}), ChordData({20, 4, 2}), ChordData({32, 13, 0}), 
 ChordData({34, 1, 0}), ChordData({36, 0, 0}), ChordData({36, 4, 18}), ChordData({128, 0, 129}), 
 ChordData({144, 64, 8}), ChordData({148, 0, 16}), 
};

const uint8_t kmap0_Word_len16_anagram2_seqs[28] = {
 251, 184, 76, 189, 
 201, 191, 242, 199, 
 219, 210, 178, 209, 
 245, 209, 47, 222, 
 119, 31, 53, 159, 
 231, 23, 27, 68, 
 86, 25, 227, 26, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len16_anagram2 = {
  LengthAndAnagram(16, 2), // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_Word_len16_anagram2_chords, // chords
  kmap0_Word_len16_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len16_anagram3_chords[5] = {
 ChordData({16, 8, 0}), ChordData({16, 12, 1}), ChordData({20, 4, 16}), ChordData({34, 1, 0}), 
 ChordData({128, 0, 8}), 
};

const uint8_t kmap0_Word_len16_anagram3_seqs[10] = {
 201, 201, 201, 251, 
 227, 175, 119, 223, 
 26, 161, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len16_anagram3 = {
  LengthAndAnagram(16, 3), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Word_len16_anagram3_chords, // chords
  kmap0_Word_len16_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len17_anagram0_chords[166] = {
 ChordData({0, 8, 130}), ChordData({0, 9, 82}), ChordData({0, 12, 17}), ChordData({0, 12, 64}), 
 ChordData({0, 12, 80}), ChordData({0, 12, 130}), ChordData({0, 32, 137}), ChordData({0, 36, 1}), 
 ChordData({0, 36, 3}), ChordData({0, 36, 9}), ChordData({0, 36, 10}), ChordData({0, 36, 18}), 
 ChordData({0, 36, 66}), ChordData({0, 36, 128}), ChordData({0, 36, 129}), ChordData({0, 64, 192}), 
 ChordData({0, 68, 1}), ChordData({0, 68, 17}), ChordData({0, 68, 18}), ChordData({0, 68, 24}), 
 ChordData({0, 68, 72}), ChordData({0, 68, 136}), ChordData({2, 8, 9}), ChordData({2, 8, 17}), 
 ChordData({2, 8, 64}), ChordData({2, 8, 66}), ChordData({2, 8, 128}), ChordData({2, 8, 130}), 
 ChordData({2, 8, 192}), ChordData({2, 12, 8}), ChordData({2, 12, 128}), ChordData({2, 32, 9}), 
 ChordData({2, 32, 10}), ChordData({2, 32, 18}), ChordData({2, 32, 65}), ChordData({2, 36, 16}), 
 ChordData({2, 64, 3}), ChordData({2, 64, 17}), ChordData({2, 64, 65}), ChordData({2, 64, 66}), 
 ChordData({2, 64, 192}), ChordData({2, 68, 2}), ChordData({2, 68, 16}), ChordData({2, 68, 64}), 
 ChordData({2, 68, 128}), ChordData({4, 4, 16}), ChordData({4, 4, 17}), ChordData({4, 4, 64}), 
 ChordData({4, 4, 65}), ChordData({4, 4, 72}), ChordData({4, 4, 136}), ChordData({6, 0, 17}), 
 ChordData({6, 0, 72}), ChordData({6, 0, 128}), ChordData({6, 0, 130}), ChordData({6, 0, 192}), 
 ChordData({6, 4, 8}), ChordData({6, 4, 16}), ChordData({16, 0, 146}), ChordData({16, 1, 129}), 
 ChordData({16, 1, 192}), ChordData({16, 4, 18}), ChordData({16, 4, 82}), ChordData({16, 5, 1}), 
 ChordData({16, 5, 2}), ChordData({16, 5, 16}), ChordData({16, 5, 64}), ChordData({16, 5, 128}), 
 ChordData({16, 9, 8}), ChordData({16, 9, 64}), ChordData({16, 40, 1}), ChordData({16, 40, 2}), 
 ChordData({16, 40, 64}), ChordData({16, 40, 128}), ChordData({16, 64, 18}), ChordData({16, 68, 0}), 
 ChordData({16, 72, 8}), ChordData({16, 76, 0}), ChordData({16, 96, 64}), ChordData({16, 96, 128}), 
 ChordData({16, 100, 0}), ChordData({18, 1, 8}), ChordData({18, 1, 16}), ChordData({18, 1, 64}), 
 ChordData({18, 1, 128}), ChordData({18, 8, 0}), ChordData({18, 72, 0}), ChordData({18, 96, 0}), 
 ChordData({20, 8, 1}), ChordData({20, 32, 128}), ChordData({20, 36, 0}), ChordData({22, 0, 0}), 
 ChordData({32, 0, 25}), ChordData({32, 0, 81}), ChordData({32, 0, 131}), ChordData({32, 0, 136}), 
 ChordData({32, 1, 18}), ChordData({32, 4, 130}), ChordData({32, 9, 18}), ChordData({32, 76, 2}), 
 ChordData({34, 0, 9}), ChordData({34, 0, 65}), ChordData({34, 0, 129}), ChordData({36, 1, 0}), 
 ChordData({48, 5, 1}), ChordData({48, 5, 2}), ChordData({48, 5, 64}), ChordData({48, 8, 17}), 
 ChordData({48, 8, 65}), ChordData({48, 12, 2}), ChordData({48, 64, 2}), ChordData({48, 64, 8}), 
 ChordData({48, 64, 16}), ChordData({48, 65, 0}), ChordData({50, 8, 2}), ChordData({50, 8, 128}), 
 ChordData({52, 0, 9}), ChordData({52, 0, 16}), ChordData({52, 0, 65}), ChordData({52, 4, 1}), 
 ChordData({52, 4, 8}), ChordData({52, 4, 16}), ChordData({52, 4, 64}), ChordData({52, 4, 128}), 
 ChordData({54, 0, 1}), ChordData({54, 0, 128}), ChordData({128, 8, 1}), ChordData({128, 8, 16}), 
 ChordData({128, 8, 24}), ChordData({128, 8, 64}), ChordData({128, 8, 65}), ChordData({128, 8, 129}), 
 ChordData({128, 12, 1}), ChordData({128, 12, 64}), ChordData({128, 32, 65}), ChordData({128, 64, 16}), 
 ChordData({128, 64, 129}), ChordData({128, 64, 144}), ChordData({128, 64, 192}), ChordData({128, 68, 16}), 
 ChordData({128, 68, 128}), ChordData({130, 8, 1}), ChordData({130, 64, 128}), ChordData({132, 0, 17}), 
 ChordData({132, 0, 65}), ChordData({132, 0, 128}), ChordData({132, 0, 129}), ChordData({132, 4, 64}), 
 ChordData({144, 8, 0}), ChordData({144, 40, 0}), ChordData({144, 72, 0}), ChordData({148, 8, 0}), 
 ChordData({148, 32, 0}), ChordData({160, 0, 8}), ChordData({160, 0, 17}), ChordData({160, 0, 192}), 
 ChordData({160, 4, 1}), ChordData({162, 0, 64}), ChordData({164, 64, 2}), ChordData({176, 1, 8}), 
 ChordData({176, 1, 64}), ChordData({176, 8, 1}), ChordData({176, 8, 8}), ChordData({176, 8, 16}), 
 ChordData({176, 8, 128}), ChordData({180, 0, 8}), 
};

const uint8_t kmap0_Word_len17_anagram0_seqs[353] = {
 87, 137, 184, 84, 
 164, 159, 77, 207, 
 156, 126, 56, 253, 
 149, 10, 222, 133, 
 191, 8, 127, 23, 
 190, 34, 124, 69, 
 248, 131, 207, 16, 
 62, 17, 124, 90, 
 46, 67, 242, 247, 
 229, 207, 94, 190, 
 152, 87, 201, 175, 
 146, 94, 101, 106, 
 221, 157, 78, 169, 
 153, 83, 51, 166, 
 38, 74, 125, 197, 
 212, 41, 125, 107, 
 250, 38, 216, 186, 
 173, 8, 167, 17, 
 46, 108, 134, 223, 
 35, 27, 87, 246, 
 172, 108, 94, 217, 
 140, 76, 45, 31, 
 91, 206, 183, 228, 
 111, 73, 223, 178, 
 254, 124, 253, 217, 
 250, 204, 245, 121, 
 89, 191, 86, 122, 
 221, 233, 202, 181, 
 181, 54, 17, 82, 
 87, 106, 174, 245, 
 91, 235, 247, 140, 
 169, 32, 31, 203, 
 166, 163, 240, 143, 
 159, 139, 195, 191, 
 199, 163, 15, 255, 
 240, 31, 62, 200, 
 95, 82, 155, 237, 
 210, 66, 167, 100, 
 132, 201, 12, 161, 
 41, 93, 60, 150, 
 126, 153, 172, 50, 
 189, 52, 67, 75, 
 104, 146, 208, 47, 
 143, 86, 31, 61, 
 62, 218, 124, 52, 
 57, 117, 178, 116, 
 106, 216, 210, 235, 
 84, 161, 169, 66, 
 127, 173, 93, 189, 
 121, 116, 50, 47, 
 102, 90, 205, 68, 
 119, 46, 62, 95, 
 221, 69, 186, 188, 
 152, 181, 151, 115, 
 111, 222, 166, 51, 
 223, 247, 175, 241, 
 111, 243, 223, 22, 
 61, 43, 154, 23, 
 95, 180, 204, 104, 
 205, 210, 147, 165, 
 45, 111, 139, 141, 
 182, 216, 116, 90, 
 183, 230, 241, 105, 
 222, 211, 251, 167, 
 95, 207, 31, 159, 
 207, 254, 147, 124, 
 246, 186, 79, 114, 
 138, 216, 137, 72, 
 26, 147, 82, 48, 
 167, 224, 221, 72, 
 244, 27, 137, 35, 
 61, 12, 94, 25, 
 49, 27, 36, 41, 
 70, 114, 144, 156, 
 120, 73, 241, 50, 
 82, 111, 203, 160, 
 26, 179, 188, 81, 
 41, 162, 86, 138, 
 229, 248, 154, 156, 
 2, 70, 114, 10, 
 233, 26, 78, 48, 
 170, 53, 178, 110, 
 228, 225, 160, 252, 
 121, 163, 35, 243, 
 25, 151, 59, 212, 
 119, 152, 197, 88, 
 135, 104, 13, 209, 
 67, 33, 250, 12, 
 53, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len17_anagram0 = {
  LengthAndAnagram(17, 0), // seq_bit_len_and_anagram
  166, // num_chords
  kmap0_Word_len17_anagram0_chords, // chords
  kmap0_Word_len17_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len17_anagram1_chords[56] = {
 ChordData({0, 12, 130}), ChordData({0, 12, 144}), ChordData({0, 32, 128}), ChordData({0, 36, 18}), 
 ChordData({2, 8, 8}), ChordData({2, 8, 65}), ChordData({2, 12, 128}), ChordData({2, 32, 9}), 
 ChordData({2, 32, 65}), ChordData({2, 32, 128}), ChordData({2, 68, 128}), ChordData({4, 4, 18}), 
 ChordData({4, 4, 72}), ChordData({6, 0, 130}), ChordData({6, 0, 192}), ChordData({16, 1, 128}), 
 ChordData({16, 1, 129}), ChordData({16, 5, 1}), ChordData({16, 5, 2}), ChordData({16, 5, 16}), 
 ChordData({16, 5, 128}), ChordData({16, 9, 8}), ChordData({16, 65, 0}), ChordData({18, 1, 16}), 
 ChordData({18, 1, 128}), ChordData({20, 64, 8}), ChordData({20, 64, 64}), ChordData({36, 0, 18}), 
 ChordData({48, 5, 16}), ChordData({48, 8, 8}), ChordData({48, 12, 64}), ChordData({50, 8, 8}), 
 ChordData({50, 8, 128}), ChordData({52, 0, 0}), ChordData({52, 0, 128}), ChordData({52, 0, 129}), 
 ChordData({52, 4, 1}), ChordData({52, 4, 16}), ChordData({128, 8, 8}), ChordData({128, 8, 24}), 
 ChordData({128, 32, 24}), ChordData({128, 32, 65}), ChordData({128, 36, 128}), ChordData({128, 64, 128}), 
 ChordData({128, 64, 130}), ChordData({132, 0, 16}), ChordData({132, 0, 18}), ChordData({132, 0, 64}), 
 ChordData({132, 0, 65}), ChordData({132, 0, 128}), ChordData({132, 0, 192}), ChordData({132, 8, 0}), 
 ChordData({144, 1, 16}), ChordData({144, 72, 0}), ChordData({160, 0, 192}), ChordData({180, 0, 16}), 
};

const uint8_t kmap0_Word_len17_anagram1_seqs[119] = {
 248, 148, 4, 62, 
 9, 38, 250, 65, 
 152, 90, 155, 183, 
 83, 167, 167, 133, 
 173, 12, 123, 97, 
 19, 201, 126, 194, 
 249, 202, 245, 181, 
 246, 21, 83, 215, 
 195, 68, 135, 105, 
 143, 95, 227, 31, 
 62, 126, 76, 254, 
 163, 100, 235, 97, 
 203, 163, 61, 212, 
 135, 171, 85, 114, 
 181, 60, 115, 113, 
 251, 199, 154, 19, 
 191, 104, 209, 173, 
 212, 162, 79, 187, 
 158, 38, 58, 77, 
 123, 250, 247, 244, 
 79, 10, 141, 20, 
 163, 48, 70, 25, 
 198, 194, 167, 144, 
 65, 132, 65, 178, 
 70, 12, 78, 212, 
 136, 202, 53, 120, 
 107, 16, 49, 69, 
 45, 27, 113, 196, 
 88, 58, 5, 71, 
 166, 51, 198, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len17_anagram1 = {
  LengthAndAnagram(17, 1), // seq_bit_len_and_anagram
  56, // num_chords
  kmap0_Word_len17_anagram1_chords, // chords
  kmap0_Word_len17_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len17_anagram2_chords[15] = {
 ChordData({0, 12, 130}), ChordData({2, 32, 65}), ChordData({4, 4, 17}), ChordData({6, 0, 64}), 
 ChordData({36, 1, 0}), ChordData({48, 1, 8}), ChordData({48, 5, 16}), ChordData({48, 8, 8}), 
 ChordData({48, 12, 128}), ChordData({128, 8, 8}), ChordData({128, 32, 1}), ChordData({132, 0, 18}), 
 ChordData({132, 0, 65}), ChordData({132, 0, 128}), ChordData({176, 1, 16}), 
};

const uint8_t kmap0_Word_len17_anagram2_seqs[32] = {
 72, 159, 96, 243, 
 238, 124, 173, 205, 
 124, 230, 195, 122, 
 235, 252, 237, 100, 
 205, 22, 159, 82, 
 132, 194, 136, 173, 
 19, 200, 53, 182, 
 70, 208, 29, 99, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len17_anagram2 = {
  LengthAndAnagram(17, 2), // seq_bit_len_and_anagram
  15, // num_chords
  kmap0_Word_len17_anagram2_chords, // chords
  kmap0_Word_len17_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len17_anagram3_chords[2] = {
 ChordData({20, 0, 16}), ChordData({128, 64, 18}), 
};

const uint8_t kmap0_Word_len17_anagram3_seqs[5] = {
 117, 92, 49, 70, 
 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len17_anagram3 = {
  LengthAndAnagram(17, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len17_anagram3_chords, // chords
  kmap0_Word_len17_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len17_anagram5_chords[1] = {
 ChordData({0, 68, 18}), 
};

const uint8_t kmap0_Word_len17_anagram5_seqs[3] = {
 248, 35, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len17_anagram5 = {
  LengthAndAnagram(17, 5), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len17_anagram5_chords, // chords
  kmap0_Word_len17_anagram5_seqs, // sequences
};

const ChordData kmap0_Word_len18_anagram0_chords[141] = {
 ChordData({0, 4, 83}), ChordData({0, 5, 3}), ChordData({0, 5, 65}), ChordData({0, 5, 128}), 
 ChordData({0, 5, 129}), ChordData({0, 5, 130}), ChordData({0, 40, 129}), ChordData({0, 44, 1}), 
 ChordData({0, 44, 16}), ChordData({0, 44, 64}), ChordData({0, 76, 8}), ChordData({0, 77, 2}), 
 ChordData({0, 96, 18}), ChordData({0, 100, 8}), ChordData({0, 100, 16}), ChordData({0, 100, 64}), 
 ChordData({2, 0, 27}), ChordData({2, 1, 65}), ChordData({2, 1, 128}), ChordData({2, 1, 129}), 
 ChordData({2, 1, 130}), ChordData({2, 5, 16}), ChordData({2, 5, 128}), ChordData({2, 72, 8}), 
 ChordData({2, 72, 128}), ChordData({2, 96, 64}), ChordData({4, 8, 65}), ChordData({4, 12, 2}), 
 ChordData({4, 12, 64}), ChordData({4, 12, 128}), ChordData({4, 36, 1}), ChordData({4, 36, 16}), 
 ChordData({4, 40, 64}), ChordData({6, 8, 0}), ChordData({6, 8, 128}), ChordData({6, 12, 0}), 
 ChordData({6, 32, 2}), ChordData({6, 32, 64}), ChordData({6, 68, 0}), ChordData({16, 0, 74}), 
 ChordData({16, 9, 10}), ChordData({16, 9, 17}), ChordData({16, 13, 1}), ChordData({16, 13, 2}), 
 ChordData({16, 13, 64}), ChordData({16, 13, 128}), ChordData({16, 32, 19}), ChordData({16, 33, 2}), 
 ChordData({16, 36, 18}), ChordData({16, 64, 11}), ChordData({16, 64, 26}), ChordData({16, 64, 130}), 
 ChordData({16, 65, 8}), ChordData({16, 69, 0}), ChordData({18, 9, 128}), ChordData({18, 64, 10}), 
 ChordData({18, 64, 18}), ChordData({18, 64, 66}), ChordData({18, 65, 0}), ChordData({20, 9, 0}), 
 ChordData({20, 40, 0}), ChordData({20, 64, 2}), ChordData({32, 5, 136}), ChordData({32, 8, 65}), 
 ChordData({32, 12, 65}), ChordData({32, 32, 9}), ChordData({32, 32, 65}), ChordData({32, 32, 66}), 
 ChordData({32, 32, 80}), ChordData({32, 32, 128}), ChordData({32, 36, 1}), ChordData({32, 64, 65}), 
 ChordData({32, 68, 16}), ChordData({34, 1, 24}), ChordData({34, 1, 72}), ChordData({34, 1, 128}), 
 ChordData({34, 1, 144}), ChordData({34, 5, 128}), ChordData({34, 12, 16}), ChordData({34, 12, 64}), 
 ChordData({34, 12, 128}), ChordData({36, 0, 9}), ChordData({36, 0, 72}), ChordData({36, 0, 128}), 
 ChordData({36, 0, 192}), ChordData({36, 4, 18}), ChordData({36, 4, 64}), ChordData({38, 4, 128}), 
 ChordData({48, 1, 16}), ChordData({48, 40, 128}), ChordData({48, 44, 0}), ChordData({48, 72, 8}), 
 ChordData({52, 0, 2}), ChordData({52, 0, 128}), ChordData({52, 1, 0}), ChordData({52, 1, 16}), 
 ChordData({52, 5, 0}), ChordData({52, 8, 16}), ChordData({52, 12, 0}), ChordData({52, 32, 16}), 
 ChordData({52, 64, 1}), ChordData({52, 64, 8}), ChordData({52, 68, 0}), ChordData({128, 0, 154}), 
 ChordData({128, 1, 1}), ChordData({128, 1, 9}), ChordData({128, 1, 10}), ChordData({128, 1, 17}), 
 ChordData({128, 1, 65}), ChordData({128, 1, 128}), ChordData({128, 1, 130}), ChordData({128, 5, 64}), 
 ChordData({128, 8, 8}), ChordData({128, 72, 128}), ChordData({128, 96, 0}), ChordData({128, 96, 128}), 
 ChordData({130, 1, 8}), ChordData({132, 8, 2}), ChordData({132, 32, 64}), ChordData({132, 64, 8}), 
 ChordData({132, 64, 16}), ChordData({160, 0, 128}), ChordData({160, 1, 72}), ChordData({160, 1, 136}), 
 ChordData({160, 5, 128}), ChordData({160, 8, 129}), ChordData({160, 12, 8}), ChordData({160, 12, 128}), 
 ChordData({160, 32, 16}), ChordData({160, 64, 2}), ChordData({160, 64, 64}), ChordData({160, 64, 128}), 
 ChordData({164, 0, 24}), ChordData({164, 0, 64}), ChordData({164, 0, 128}), ChordData({164, 0, 129}), 
 ChordData({164, 0, 130}), ChordData({164, 0, 144}), ChordData({166, 0, 64}), ChordData({176, 1, 0}), 
 ChordData({176, 8, 0}), 
};

const uint8_t kmap0_Word_len18_anagram0_seqs[318] = {
 188, 95, 28, 143, 
 123, 60, 239, 241, 
 68, 7, 253, 30, 
 127, 5, 55, 81, 
 250, 133, 240, 39, 
 165, 103, 40, 63, 
 233, 95, 74, 23, 
 88, 192, 87, 9, 
 127, 164, 124, 134, 
 219, 90, 28, 205, 
 123, 52, 17, 245, 
 177, 71, 95, 29, 
 223, 115, 124, 83, 
 106, 149, 169, 73, 
 202, 102, 200, 105, 
 43, 126, 170, 92, 
 63, 209, 167, 90, 
 127, 33, 252, 169, 
 101, 25, 150, 237, 
 218, 169, 82, 167, 
 175, 8, 187, 50, 
 236, 90, 191, 37, 
 163, 213, 106, 44, 
 237, 184, 180, 95, 
 50, 126, 201, 252, 
 37, 147, 191, 180, 
 208, 5, 66, 31, 
 133, 31, 94, 172, 
 43, 173, 197, 197, 
 68, 210, 135, 30, 
 47, 77, 93, 242, 
 165, 213, 151, 30, 
 95, 154, 125, 180, 
 101, 201, 174, 78, 
 21, 94, 236, 74, 
 175, 119, 202, 188, 
 226, 243, 194, 172, 
 203, 48, 47, 103, 
 132, 147, 25, 194, 
 76, 244, 121, 161, 
 204, 188, 50, 207, 
 79, 235, 205, 173, 
 247, 221, 68, 119, 
 15, 221, 212, 47, 
 254, 180, 216, 252, 
 98, 63, 213, 172, 
 203, 53, 107, 205, 
 68, 149, 50, 227, 
 207, 121, 62, 243, 
 249, 77, 121, 110, 
 11, 22, 13, 95, 
 180, 104, 149, 152, 
 79, 159, 148, 125, 
 218, 199, 61, 174, 
 245, 111, 215, 177, 
 120, 250, 19, 244, 
 156, 210, 231, 158, 
 86, 121, 250, 101, 
 40, 21, 71, 196, 
 30, 161, 139, 161, 
 199, 17, 179, 28, 
 199, 30, 17, 116, 
 196, 21, 199, 241, 
 32, 133, 166, 32, 
 9, 35, 36, 12, 
 146, 173, 71, 96, 
 164, 202, 48, 106, 
 13, 149, 114, 162, 
 2, 138, 204, 161, 
 55, 133, 222, 119, 
 60, 137, 65, 171, 
 33, 126, 136, 79, 
 48, 242, 200, 192, 
 204, 89, 6, 69, 
 150, 103, 140, 114, 
 228, 122, 70, 208, 
 25, 180, 103, 92, 
 9, 196, 121, 118, 
 48, 184, 29, 41, 
 68, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  141, // num_chords
  kmap0_Word_len18_anagram0_chords, // chords
  kmap0_Word_len18_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len18_anagram1_chords[49] = {
 ChordData({0, 0, 90}), ChordData({0, 4, 26}), ChordData({0, 4, 146}), ChordData({0, 5, 130}), 
 ChordData({0, 12, 64}), ChordData({0, 36, 64}), ChordData({2, 0, 19}), ChordData({4, 12, 16}), 
 ChordData({4, 12, 64}), ChordData({4, 12, 128}), ChordData({4, 32, 1}), ChordData({16, 0, 25}), 
 ChordData({16, 0, 72}), ChordData({16, 0, 73}), ChordData({16, 0, 193}), ChordData({16, 64, 18}), 
 ChordData({16, 64, 67}), ChordData({16, 64, 146}), ChordData({16, 69, 0}), ChordData({20, 0, 19}), 
 ChordData({20, 9, 0}), ChordData({32, 5, 65}), ChordData({32, 32, 17}), ChordData({32, 32, 65}), 
 ChordData({32, 64, 65}), ChordData({32, 68, 128}), ChordData({34, 1, 72}), ChordData({34, 5, 8}), 
 ChordData({36, 4, 24}), ChordData({36, 4, 192}), ChordData({38, 4, 64}), ChordData({48, 1, 64}), 
 ChordData({48, 1, 128}), ChordData({48, 13, 0}), ChordData({48, 64, 0}), ChordData({52, 0, 1}), 
 ChordData({52, 0, 8}), ChordData({128, 0, 146}), ChordData({128, 1, 16}), ChordData({128, 72, 0}), 
 ChordData({160, 1, 1}), ChordData({160, 1, 128}), ChordData({160, 5, 1}), ChordData({160, 5, 128}), 
 ChordData({164, 0, 1}), ChordData({164, 0, 16}), ChordData({164, 0, 64}), ChordData({164, 0, 144}), 
 ChordData({164, 4, 1}), 
};

const uint8_t kmap0_Word_len18_anagram1_seqs[111] = {
 92, 40, 22, 63, 
 250, 68, 5, 62, 
 29, 128, 63, 193, 
 103, 136, 189, 197, 
 124, 170, 245, 57, 
 213, 167, 4, 119, 
 171, 117, 61, 108, 
 101, 175, 149, 205, 
 107, 19, 142, 47, 
 23, 243, 10, 248, 
 34, 253, 199, 22, 
 213, 213, 46, 241, 
 254, 13, 243, 236, 
 194, 204, 188, 89, 
 202, 252, 196, 125, 
 235, 253, 173, 231, 
 143, 50, 253, 121, 
 246, 243, 145, 217, 
 55, 101, 223, 159, 
 44, 179, 244, 230, 
 211, 224, 180, 10, 
 68, 49, 17, 71, 
 138, 144, 119, 108, 
 80, 220, 113, 199, 
 239, 211, 29, 103, 
 196, 214, 200, 115, 
 6, 115, 156, 2, 
 103, 252, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len18_anagram1 = {
  LengthAndAnagram(18, 1), // seq_bit_len_and_anagram
  49, // num_chords
  kmap0_Word_len18_anagram1_chords, // chords
  kmap0_Word_len18_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len18_anagram2_chords[17] = {
 ChordData({0, 4, 19}), ChordData({0, 4, 146}), ChordData({4, 12, 0}), ChordData({16, 0, 130}), 
 ChordData({16, 0, 131}), ChordData({16, 4, 192}), ChordData({16, 13, 0}), ChordData({16, 64, 2}), 
 ChordData({16, 68, 18}), ChordData({32, 8, 1}), ChordData({34, 1, 144}), ChordData({36, 4, 128}), 
 ChordData({38, 0, 128}), ChordData({48, 13, 0}), ChordData({50, 72, 0}), ChordData({128, 64, 2}), 
 ChordData({128, 72, 0}), 
};

const uint8_t kmap0_Word_len18_anagram2_seqs[39] = {
 59, 95, 32, 125, 
 81, 246, 171, 175, 
 140, 38, 227, 146, 
 159, 125, 124, 242, 
 197, 150, 151, 31, 
 167, 188, 43, 208, 
 247, 249, 68, 103, 
 19, 37, 223, 47, 
 91, 244, 37, 46, 
 50, 34, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len18_anagram2 = {
  LengthAndAnagram(18, 2), // seq_bit_len_and_anagram
  17, // num_chords
  kmap0_Word_len18_anagram2_chords, // chords
  kmap0_Word_len18_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len18_anagram3_chords[6] = {
 ChordData({0, 4, 146}), ChordData({16, 0, 81}), ChordData({16, 13, 128}), ChordData({16, 68, 18}), 
 ChordData({18, 0, 129}), ChordData({48, 1, 128}), 
};

const uint8_t kmap0_Word_len18_anagram3_seqs[14] = {
 2, 95, 240, 218, 
 67, 95, 242, 197, 
 63, 166, 94, 31, 
 217, 4, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len18_anagram3 = {
  LengthAndAnagram(18, 3), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Word_len18_anagram3_chords, // chords
  kmap0_Word_len18_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len19_anagram0_chords[135] = {
 ChordData({0, 12, 26}), ChordData({0, 12, 146}), ChordData({0, 13, 9}), ChordData({0, 13, 10}), 
 ChordData({0, 13, 18}), ChordData({0, 13, 24}), ChordData({0, 13, 65}), ChordData({0, 13, 66}), 
 ChordData({0, 13, 129}), ChordData({0, 13, 130}), ChordData({0, 37, 128}), ChordData({0, 68, 11}), 
 ChordData({0, 68, 26}), ChordData({0, 68, 138}), ChordData({0, 68, 146}), ChordData({2, 1, 16}), 
 ChordData({2, 9, 3}), ChordData({2, 9, 9}), ChordData({2, 9, 10}), ChordData({2, 9, 16}), 
 ChordData({2, 9, 66}), ChordData({2, 9, 72}), ChordData({2, 9, 80}), ChordData({2, 9, 128}), 
 ChordData({2, 9, 136}), ChordData({2, 33, 64}), ChordData({2, 64, 11}), ChordData({2, 64, 130}), 
 ChordData({2, 65, 8}), ChordData({2, 68, 3}), ChordData({4, 4, 146}), ChordData({4, 5, 128}), 
 ChordData({6, 1, 128}), ChordData({16, 0, 131}), ChordData({16, 0, 139}), ChordData({16, 4, 65}), 
 ChordData({16, 4, 130}), ChordData({16, 4, 138}), ChordData({16, 4, 145}), ChordData({16, 4, 152}), 
 ChordData({16, 4, 193}), ChordData({16, 4, 194}), ChordData({16, 13, 0}), ChordData({16, 32, 10}), 
 ChordData({16, 32, 17}), ChordData({16, 32, 65}), ChordData({16, 32, 80}), ChordData({16, 64, 144}), 
 ChordData({16, 73, 64}), ChordData({16, 96, 10}), ChordData({18, 0, 24}), ChordData({18, 0, 72}), 
 ChordData({18, 0, 74}), ChordData({18, 0, 88}), ChordData({18, 0, 137}), ChordData({18, 0, 194}), 
 ChordData({18, 4, 80}), ChordData({18, 4, 136}), ChordData({18, 41, 0}), ChordData({20, 0, 18}), 
 ChordData({20, 0, 192}), ChordData({20, 9, 1}), ChordData({20, 13, 0}), ChordData({22, 0, 2}), 
 ChordData({22, 9, 0}), ChordData({32, 0, 16}), ChordData({32, 1, 10}), ChordData({32, 1, 80}), 
 ChordData({32, 1, 128}), ChordData({32, 1, 136}), ChordData({32, 13, 16}), ChordData({32, 37, 8}), 
 ChordData({32, 40, 2}), ChordData({32, 40, 64}), ChordData({32, 69, 16}), ChordData({32, 69, 128}), 
 ChordData({32, 72, 16}), ChordData({34, 65, 16}), ChordData({36, 0, 24}), ChordData({36, 0, 130}), 
 ChordData({36, 0, 144}), ChordData({36, 1, 144}), ChordData({36, 32, 64}), ChordData({36, 36, 1}), 
 ChordData({36, 36, 64}), ChordData({36, 36, 128}), ChordData({36, 68, 8}), ChordData({38, 1, 8}), 
 ChordData({38, 1, 16}), ChordData({38, 8, 128}), ChordData({38, 64, 8}), ChordData({38, 64, 16}), 
 ChordData({48, 1, 18}), ChordData({48, 8, 18}), ChordData({48, 9, 8}), ChordData({48, 13, 0}), 
 ChordData({48, 33, 0}), ChordData({50, 9, 0}), ChordData({52, 0, 19}), ChordData({128, 9, 1}), 
 ChordData({128, 9, 2}), ChordData({128, 9, 16}), ChordData({128, 9, 66}), ChordData({128, 9, 128}), 
 ChordData({128, 9, 130}), ChordData({128, 64, 11}), ChordData({128, 64, 26}), ChordData({128, 64, 67}), 
 ChordData({128, 64, 74}), ChordData({128, 64, 194}), ChordData({128, 65, 0}), ChordData({128, 65, 128}), 
 ChordData({130, 9, 128}), ChordData({130, 65, 0}), ChordData({132, 0, 18}), ChordData({132, 0, 19}), 
 ChordData({132, 0, 146}), ChordData({144, 0, 16}), ChordData({144, 0, 73}), ChordData({144, 0, 81}), 
 ChordData({144, 0, 82}), ChordData({144, 0, 138}), ChordData({144, 0, 193}), ChordData({144, 0, 194}), 
 ChordData({144, 0, 208}), ChordData({144, 4, 10}), ChordData({144, 4, 136}), ChordData({160, 1, 16}), 
 ChordData({160, 65, 0}), ChordData({160, 65, 128}), ChordData({162, 72, 0}), ChordData({164, 0, 16}), 
 ChordData({164, 8, 0}), ChordData({164, 32, 1}), ChordData({164, 64, 128}), 
};

const uint8_t kmap0_Word_len19_anagram0_seqs[321] = {
 233, 181, 40, 62, 
 209, 190, 150, 244, 
 177, 52, 143, 165, 
 121, 45, 237, 115, 
 137, 31, 75, 251, 
 84, 162, 199, 18, 
 124, 58, 46, 175, 
 123, 249, 81, 250, 
 139, 210, 203, 2, 
 28, 211, 219, 88, 
 42, 105, 175, 54, 
 150, 142, 158, 196, 
 141, 37, 110, 45, 
 77, 115, 169, 212, 
 68, 212, 90, 58, 
 154, 225, 94, 90, 
 47, 77, 116, 180, 
 202, 203, 247, 86, 
 250, 226, 160, 175, 
 7, 117, 93, 95, 
 173, 250, 106, 121, 
 127, 253, 136, 38, 
 36, 191, 210, 175, 
 135, 252, 163, 228, 
 231, 101, 124, 114, 
 250, 146, 161, 21, 
 189, 208, 227, 133, 
 102, 51, 180, 199, 
 36, 61, 210, 92, 
 186, 64, 107, 171, 
 122, 90, 205, 204, 
 173, 232, 49, 183, 
 182, 174, 137, 169, 
 209, 243, 205, 126, 
 106, 43, 236, 146, 
 113, 236, 202, 100, 
 215, 146, 235, 86, 
 127, 169, 182, 209, 
 181, 75, 46, 34, 
 207, 145, 21, 57, 
 207, 113, 100, 34, 
 202, 122, 223, 243, 
 9, 190, 222, 41, 
 35, 76, 153, 225, 
 61, 47, 111, 122, 
 41, 39, 167, 123, 
 90, 158, 121, 20, 
 41, 159, 39, 229, 
 17, 168, 119, 205, 
 12, 207, 95, 120, 
 62, 195, 147, 30, 
 158, 175, 178, 182, 
 222, 247, 116, 165, 
 78, 231, 217, 42, 
 207, 30, 121, 143, 
 11, 209, 83, 104, 
 46, 249, 126, 209, 
 48, 223, 190, 91, 
 244, 89, 172, 55, 
 162, 132, 17, 165, 
 99, 34, 113, 96, 
 137, 34, 74, 20, 
 88, 218, 184, 232, 
 37, 70, 121, 227, 
 194, 26, 23, 166, 
 184, 28, 17, 242, 
 8, 146, 165, 166, 
 56, 90, 6, 70, 
 45, 182, 168, 81, 
 131, 10, 207, 196, 
 132, 178, 151, 55, 
 198, 140, 49, 70, 
 10, 53, 111, 144, 
 145, 130, 77, 193, 
 158, 64, 191, 62, 
 133, 250, 136, 60, 
 119, 132, 188, 131, 
 164, 24, 45, 235, 
 196, 121, 70, 164, 
 51, 22, 158, 65, 
 18, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len19_anagram0 = {
  LengthAndAnagram(19, 0), // seq_bit_len_and_anagram
  135, // num_chords
  kmap0_Word_len19_anagram0_chords, // chords
  kmap0_Word_len19_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len19_anagram1_chords[42] = {
 ChordData({0, 13, 3}), ChordData({0, 13, 16}), ChordData({0, 68, 130}), ChordData({2, 9, 64}), 
 ChordData({2, 9, 72}), ChordData({2, 9, 128}), ChordData({2, 9, 192}), ChordData({2, 64, 0}), 
 ChordData({16, 0, 147}), ChordData({16, 4, 17}), ChordData({16, 4, 19}), ChordData({16, 4, 81}), 
 ChordData({16, 4, 82}), ChordData({16, 4, 145}), ChordData({16, 4, 152}), ChordData({16, 4, 193}), 
 ChordData({16, 4, 208}), ChordData({16, 8, 17}), ChordData({16, 32, 1}), ChordData({16, 32, 17}), 
 ChordData({16, 32, 18}), ChordData({16, 32, 65}), ChordData({16, 32, 130}), ChordData({16, 64, 72}), 
 ChordData({16, 73, 2}), ChordData({18, 0, 25}), ChordData({18, 0, 129}), ChordData({18, 0, 131}), 
 ChordData({18, 64, 2}), ChordData({20, 0, 144}), ChordData({20, 4, 2}), ChordData({50, 9, 0}), 
 ChordData({128, 9, 16}), ChordData({128, 9, 18}), ChordData({128, 13, 0}), ChordData({128, 32, 146}), 
 ChordData({144, 0, 17}), ChordData({144, 0, 73}), ChordData({144, 0, 192}), ChordData({146, 0, 72}), 
 ChordData({160, 0, 18}), ChordData({164, 1, 16}), 
};

const uint8_t kmap0_Word_len19_anagram1_seqs[100] = {
 251, 88, 58, 126, 
 210, 229, 137, 74, 
 205, 204, 165, 214, 
 163, 41, 113, 83, 
 9, 52, 144, 2, 
 198, 221, 241, 239, 
 248, 113, 121, 127, 
 204, 248, 227, 167, 
 245, 8, 248, 149, 
 215, 79, 244, 236, 
 73, 94, 207, 218, 
 11, 189, 208, 131, 
 208, 30, 134, 246, 
 146, 141, 80, 90, 
 217, 210, 88, 106, 
 93, 207, 246, 146, 
 125, 213, 123, 105, 
 105, 1, 187, 86, 
 63, 250, 104, 209, 
 71, 76, 154, 192, 
 210, 17, 159, 96, 
 80, 49, 222, 9, 
 222, 80, 83, 4, 
 91, 163, 217, 69, 
 228, 169, 19, 55, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len19_anagram1 = {
  LengthAndAnagram(19, 1), // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_Word_len19_anagram1_chords, // chords
  kmap0_Word_len19_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len19_anagram2_chords[15] = {
 ChordData({0, 68, 130}), ChordData({4, 4, 18}), ChordData({16, 4, 19}), ChordData({16, 4, 24}), 
 ChordData({16, 4, 146}), ChordData({16, 32, 17}), ChordData({16, 64, 130}), ChordData({32, 69, 16}), 
 ChordData({34, 8, 0}), ChordData({36, 0, 128}), ChordData({128, 9, 18}), ChordData({128, 64, 130}), 
 ChordData({144, 0, 73}), ChordData({160, 1, 128}), ChordData({164, 64, 8}), 
};

const uint8_t kmap0_Word_len19_anagram2_seqs[36] = {
 151, 191, 170, 243, 
 197, 206, 163, 127, 
 172, 143, 228, 159, 
 133, 99, 95, 76, 
 82, 206, 223, 157, 
 114, 58, 51, 17, 
 198, 148, 46, 17, 
 196, 107, 141, 35, 
 50, 157, 161, 18, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len19_anagram2 = {
  LengthAndAnagram(19, 2), // seq_bit_len_and_anagram
  15, // num_chords
  kmap0_Word_len19_anagram2_chords, // chords
  kmap0_Word_len19_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len19_anagram3_chords[5] = {
 ChordData({16, 4, 19}), ChordData({16, 4, 65}), ChordData({16, 4, 138}), ChordData({48, 9, 0}), 
 ChordData({52, 8, 16}), 
};

const uint8_t kmap0_Word_len19_anagram3_seqs[12] = {
 248, 235, 217, 231, 
 53, 189, 162, 111, 
 187, 36, 122, 78, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len19_anagram3 = {
  LengthAndAnagram(19, 3), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Word_len19_anagram3_chords, // chords
  kmap0_Word_len19_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len19_anagram4_chords[1] = {
 ChordData({16, 4, 145}), 
};

const uint8_t kmap0_Word_len19_anagram4_seqs[3] = {
 79, 158, 5, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len19_anagram4 = {
  LengthAndAnagram(19, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len19_anagram4_chords, // chords
  kmap0_Word_len19_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len20_anagram0_chords[171] = {
 ChordData({0, 1, 16}), ChordData({0, 4, 81}), ChordData({0, 4, 89}), ChordData({0, 4, 138}), 
 ChordData({0, 4, 194}), ChordData({0, 4, 200}), ChordData({0, 13, 16}), ChordData({0, 45, 2}), 
 ChordData({0, 72, 0}), ChordData({0, 76, 18}), ChordData({0, 77, 16}), ChordData({0, 100, 3}), 
 ChordData({0, 100, 66}), ChordData({2, 0, 11}), ChordData({2, 0, 67}), ChordData({2, 4, 17}), 
 ChordData({2, 4, 25}), ChordData({2, 4, 72}), ChordData({2, 4, 81}), ChordData({2, 4, 145}), 
 ChordData({2, 4, 192}), ChordData({2, 4, 194}), ChordData({2, 4, 200}), ChordData({2, 9, 64}), 
 ChordData({2, 72, 66}), ChordData({2, 73, 8}), ChordData({2, 73, 64}), ChordData({2, 96, 3}), 
 ChordData({2, 96, 66}), ChordData({4, 13, 2}), ChordData({4, 13, 16}), ChordData({4, 68, 18}), 
 ChordData({4, 68, 66}), ChordData({6, 9, 2}), ChordData({6, 9, 8}), ChordData({6, 9, 64}), 
 ChordData({16, 1, 10}), ChordData({16, 8, 192}), ChordData({16, 12, 9}), ChordData({16, 12, 65}), 
 ChordData({16, 12, 66}), ChordData({16, 12, 129}), ChordData({16, 12, 130}), ChordData({16, 32, 67}), 
 ChordData({16, 32, 192}), ChordData({16, 36, 3}), ChordData({16, 36, 9}), ChordData({16, 36, 66}), 
 ChordData({16, 36, 80}), ChordData({16, 64, 25}), ChordData({16, 64, 80}), ChordData({16, 68, 10}), 
 ChordData({16, 68, 17}), ChordData({16, 68, 65}), ChordData({16, 68, 129}), ChordData({16, 68, 136}), 
 ChordData({16, 73, 2}), ChordData({18, 8, 17}), ChordData({18, 8, 18}), ChordData({18, 8, 192}), 
 ChordData({18, 12, 128}), ChordData({18, 32, 3}), ChordData({18, 32, 17}), ChordData({18, 32, 72}), 
 ChordData({18, 64, 17}), ChordData({18, 64, 192}), ChordData({18, 65, 2}), ChordData({18, 68, 128}), 
 ChordData({20, 0, 67}), ChordData({20, 0, 73}), ChordData({20, 0, 80}), ChordData({20, 0, 193}), 
 ChordData({20, 4, 65}), ChordData({20, 4, 66}), ChordData({20, 4, 80}), ChordData({20, 4, 129}), 
 ChordData({20, 4, 130}), ChordData({20, 4, 136}), ChordData({20, 32, 64}), ChordData({20, 64, 64}), 
 ChordData({22, 0, 3}), ChordData({22, 0, 18}), ChordData({22, 0, 72}), ChordData({22, 0, 80}), 
 ChordData({22, 8, 64}), ChordData({32, 5, 8}), ChordData({32, 9, 8}), ChordData({32, 9, 66}), 
 ChordData({32, 9, 130}), ChordData({32, 9, 144}), ChordData({32, 12, 0}), ChordData({32, 12, 18}), 
 ChordData({32, 12, 26}), ChordData({32, 33, 2}), ChordData({32, 33, 8}), ChordData({32, 64, 19}), 
 ChordData({32, 65, 8}), ChordData({32, 65, 16}), ChordData({34, 33, 0}), ChordData({36, 5, 8}), 
 ChordData({36, 5, 16}), ChordData({36, 8, 0}), ChordData({36, 72, 0}), ChordData({48, 0, 88}), 
 ChordData({48, 0, 138}), ChordData({48, 1, 24}), ChordData({48, 4, 3}), ChordData({48, 4, 66}), 
 ChordData({48, 5, 16}), ChordData({48, 8, 9}), ChordData({48, 8, 24}), ChordData({48, 8, 72}), 
 ChordData({48, 8, 80}), ChordData({48, 8, 128}), ChordData({48, 8, 144}), ChordData({48, 65, 18}), 
 ChordData({48, 69, 2}), ChordData({48, 76, 2}), ChordData({50, 0, 9}), ChordData({50, 0, 64}), 
 ChordData({50, 72, 2}), ChordData({52, 13, 0}), ChordData({54, 9, 0}), ChordData({128, 0, 75}), 
 ChordData({128, 0, 145}), ChordData({128, 0, 146}), ChordData({128, 0, 216}), ChordData({128, 4, 10}), 
 ChordData({128, 4, 19}), ChordData({128, 4, 65}), ChordData({128, 4, 67}), ChordData({128, 4, 129}), 
 ChordData({128, 4, 130}), ChordData({128, 4, 138}), ChordData({128, 4, 200}), ChordData({128, 4, 208}), 
 ChordData({128, 41, 0}), ChordData({128, 64, 2}), ChordData({128, 73, 2}), ChordData({128, 96, 66}), 
 ChordData({128, 100, 2}), ChordData({130, 0, 11}), ChordData({130, 0, 25}), ChordData({130, 0, 74}), 
 ChordData({130, 0, 152}), ChordData({130, 4, 9}), ChordData({130, 4, 17}), ChordData({130, 4, 64}), 
 ChordData({132, 9, 16}), ChordData({132, 32, 18}), ChordData({144, 8, 129}), ChordData({144, 8, 136}), 
 ChordData({144, 32, 17}), ChordData({144, 32, 24}), ChordData({144, 32, 65}), ChordData({144, 32, 72}), 
 ChordData({144, 32, 80}), ChordData({144, 32, 128}), ChordData({144, 32, 129}), ChordData({144, 64, 16}), 
 ChordData({144, 64, 24}), ChordData({148, 0, 66}), ChordData({148, 0, 130}), ChordData({148, 0, 192}), 
 ChordData({148, 4, 16}), ChordData({148, 8, 8}), ChordData({148, 8, 16}), ChordData({162, 8, 0}), 
 ChordData({164, 1, 128}), ChordData({176, 0, 17}), ChordData({176, 0, 24}), 
};

const uint8_t kmap0_Word_len20_anagram0_seqs[428] = {
 96, 192, 193, 251, 
 179, 59, 175, 140, 
 175, 79, 72, 207, 
 172, 207, 79, 233, 
 167, 4, 31, 75, 
 32, 1, 121, 249, 
 73, 242, 167, 116, 
 129, 191, 151, 103, 
 216, 215, 134, 205, 
 219, 184, 243, 189, 
 173, 59, 207, 173, 
 223, 188, 223, 179, 
 211, 79, 79, 253, 
 252, 87, 205, 172, 
 223, 196, 165, 78, 
 124, 233, 84, 106, 
 149, 178, 185, 116, 
 233, 133, 151, 102, 
 88, 31, 75, 245, 
 167, 116, 153, 175, 
 124, 249, 90, 27, 
 75, 181, 181, 196, 
 165, 174, 135, 21, 
 205, 201, 68, 201, 
 175, 203, 235, 79, 
 78, 143, 156, 188, 
 79, 190, 250, 132, 
 208, 188, 12, 77, 
 180, 126, 132, 234, 
 95, 136, 240, 217, 
 12, 127, 188, 99, 
 149, 114, 204, 44, 
 95, 209, 59, 47, 
 205, 235, 151, 210, 
 180, 79, 47, 173, 
 23, 187, 180, 157, 
 60, 56, 157, 204, 
 169, 201, 78, 223, 
 228, 133, 141, 11, 
 221, 195, 176, 213, 
 59, 109, 201, 212, 
 210, 151, 62, 220, 
 210, 79, 92, 141, 
 203, 213, 186, 117, 
 204, 204, 228, 186, 
 245, 121, 205, 245, 
 209, 245, 135, 93, 
 233, 215, 149, 30, 
 93, 233, 213, 12, 
 237, 202, 213, 150, 
 216, 235, 90, 167, 
 209, 92, 91, 205, 
 181, 199, 220, 101, 
 125, 191, 222, 41, 
 235, 205, 25, 75, 
 148, 177, 68, 121, 
 74, 64, 4, 47, 
 254, 20, 250, 98, 
 129, 48, 223, 48, 
 235, 45, 243, 22, 
 71, 86, 41, 39, 
 223, 176, 111, 120, 
 190, 222, 247, 252, 
 89, 115, 170, 50, 
 167, 170, 121, 216, 
 89, 145, 124, 143, 
 173, 143, 121, 141, 
 159, 217, 127, 143, 
 109, 209, 186, 106, 
 209, 195, 22, 173, 
 236, 17, 77, 22, 
 77, 99, 209, 116, 
 143, 47, 151, 191, 
 125, 121, 209, 89, 
 123, 221, 204, 217, 
 98, 251, 114, 126, 
 201, 103, 151, 140, 
 161, 188, 59, 65, 
 132, 65, 49, 2, 
 28, 138, 175, 161, 
 143, 27, 179, 241, 
 188, 24, 207, 187, 
 177, 79, 20, 248, 
 244, 87, 161, 252, 
 20, 202, 65, 63, 
 48, 162, 116, 137, 
 144, 50, 176, 196, 
 48, 46, 151, 120, 
 184, 161, 141, 173, 
 59, 193, 161, 141, 
 2, 209, 250, 219, 
 161, 243, 219, 17, 
 207, 205, 53, 166, 
 4, 139, 26, 41, 
 214, 68, 78, 161, 
 177, 208, 3, 61, 
 161, 11, 131, 205, 
 48, 212, 12, 99, 
 12, 77, 20, 48, 
 214, 20, 35, 61, 
 114, 66, 205, 24, 
 213, 190, 170, 193, 
 20, 213, 81, 61, 
 95, 54, 212, 101, 
 61, 33, 182, 24, 
 39, 197, 61, 145, 
 215, 234, 60, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len20_anagram0 = {
  LengthAndAnagram(20, 0), // seq_bit_len_and_anagram
  171, // num_chords
  kmap0_Word_len20_anagram0_chords, // chords
  kmap0_Word_len20_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len20_anagram1_chords[58] = {
 ChordData({0, 4, 19}), ChordData({0, 13, 64}), ChordData({0, 40, 19}), ChordData({0, 68, 10}), 
 ChordData({2, 0, 193}), ChordData({2, 0, 194}), ChordData({2, 4, 9}), ChordData({2, 4, 25}), 
 ChordData({2, 4, 73}), ChordData({2, 4, 131}), ChordData({2, 4, 137}), ChordData({2, 4, 144}), 
 ChordData({2, 4, 145}), ChordData({2, 64, 10}), ChordData({2, 64, 130}), ChordData({4, 8, 0}), 
 ChordData({4, 68, 18}), ChordData({16, 12, 18}), ChordData({16, 13, 0}), ChordData({16, 32, 66}), 
 ChordData({16, 36, 3}), ChordData({16, 36, 18}), ChordData({16, 40, 1}), ChordData({16, 68, 17}), 
 ChordData({16, 68, 144}), ChordData({18, 8, 17}), ChordData({18, 68, 64}), ChordData({20, 0, 192}), 
 ChordData({20, 4, 80}), ChordData({20, 4, 130}), ChordData({20, 4, 136}), ChordData({20, 4, 192}), 
 ChordData({22, 0, 66}), ChordData({32, 5, 18}), ChordData({32, 5, 128}), ChordData({34, 1, 1}), 
 ChordData({36, 1, 128}), ChordData({36, 5, 16}), ChordData({36, 32, 64}), ChordData({36, 68, 0}), 
 ChordData({48, 1, 17}), ChordData({48, 1, 24}), ChordData({48, 8, 24}), ChordData({48, 12, 128}), 
 ChordData({50, 1, 8}), ChordData({52, 0, 144}), ChordData({128, 0, 82}), ChordData({128, 64, 18}), 
 ChordData({128, 72, 18}), ChordData({130, 0, 8}), ChordData({144, 0, 144}), ChordData({144, 32, 66}), 
 ChordData({144, 32, 80}), ChordData({144, 64, 17}), ChordData({160, 5, 18}), ChordData({160, 33, 0}), 
 ChordData({164, 1, 128}), ChordData({176, 0, 17}), 
};

const uint8_t kmap0_Word_len20_anagram1_seqs[145] = {
 59, 143, 155, 158, 
 75, 169, 88, 40, 
 255, 162, 188, 77, 
 196, 216, 212, 219, 
 251, 186, 243, 173, 
 188, 223, 186, 127, 
 213, 244, 219, 42, 
 240, 77, 59, 223, 
 116, 105, 149, 151, 
 38, 9, 42, 72, 
 151, 159, 138, 227, 
 79, 199, 151, 140, 
 208, 204, 8, 253, 
 59, 126, 132, 11, 
 157, 188, 227, 151, 
 2, 47, 157, 60, 
 189, 207, 45, 205, 
 213, 68, 92, 127, 
 252, 213, 87, 245, 
 213, 68, 95, 217, 
 92, 27, 125, 207, 
 23, 7, 253, 125, 
 247, 177, 149, 242, 
 125, 254, 28, 103, 
 102, 120, 126, 150, 
 247, 216, 123, 91, 
 199, 234, 17, 77, 
 126, 209, 238, 219, 
 58, 62, 77, 56, 
 193, 124, 137, 145, 
 151, 152, 20, 218, 
 161, 64, 32, 140, 
 48, 216, 48, 134, 
 189, 19, 210, 69, 
 220, 31, 249, 134, 
 55, 197, 25, 121, 
 61, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len20_anagram1 = {
  LengthAndAnagram(20, 1), // seq_bit_len_and_anagram
  58, // num_chords
  kmap0_Word_len20_anagram1_chords, // chords
  kmap0_Word_len20_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len20_anagram2_chords[18] = {
 ChordData({0, 4, 193}), ChordData({0, 12, 18}), ChordData({2, 9, 128}), ChordData({16, 1, 16}), 
 ChordData({16, 1, 129}), ChordData({16, 36, 1}), ChordData({16, 36, 2}), ChordData({16, 36, 17}), 
 ChordData({18, 64, 18}), ChordData({20, 4, 66}), ChordData({20, 4, 80}), ChordData({20, 4, 144}), 
 ChordData({32, 1, 16}), ChordData({48, 4, 66}), ChordData({128, 64, 10}), ChordData({144, 8, 17}), 
 ChordData({160, 1, 16}), ChordData({180, 0, 64}), 
};

const uint8_t kmap0_Word_len20_anagram2_seqs[45] = {
 188, 79, 4, 62, 
 21, 169, 169, 52, 
 62, 60, 7, 217, 
 187, 208, 251, 248, 
 8, 237, 159, 133, 
 216, 210, 195, 248, 
 213, 236, 250, 83, 
 253, 67, 119, 158, 
 204, 159, 209, 50, 
 46, 154, 188, 19, 
 199, 196, 29, 167, 
 217, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len20_anagram2 = {
  LengthAndAnagram(20, 2), // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_Word_len20_anagram2_chords, // chords
  kmap0_Word_len20_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len20_anagram3_chords[4] = {
 ChordData({0, 68, 18}), ChordData({16, 36, 17}), ChordData({48, 1, 24}), ChordData({160, 1, 128}), 
};

const uint8_t kmap0_Word_len20_anagram3_seqs[10] = {
 114, 254, 2, 253, 
 179, 183, 213, 115, 
 7, 29, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len20_anagram3 = {
  LengthAndAnagram(20, 3), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Word_len20_anagram3_chords, // chords
  kmap0_Word_len20_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len20_anagram4_chords[1] = {
 ChordData({0, 68, 18}), 
};

const uint8_t kmap0_Word_len20_anagram4_seqs[3] = {
 151, 31, 9, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len20_anagram4 = {
  LengthAndAnagram(20, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len20_anagram4_chords, // chords
  kmap0_Word_len20_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len20_anagram6_chords[1] = {
 ChordData({48, 8, 80}), 
};

const uint8_t kmap0_Word_len20_anagram6_seqs[3] = {
 162, 135, 13, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len20_anagram6 = {
  LengthAndAnagram(20, 6), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len20_anagram6_chords, // chords
  kmap0_Word_len20_anagram6_seqs, // sequences
};

const ChordData kmap0_Word_len21_anagram0_chords[165] = {
 ChordData({0, 4, 80}), ChordData({0, 12, 81}), ChordData({0, 12, 144}), ChordData({0, 12, 192}), 
 ChordData({0, 36, 19}), ChordData({0, 36, 26}), ChordData({0, 36, 81}), ChordData({0, 36, 82}), 
 ChordData({0, 36, 192}), ChordData({0, 64, 209}), ChordData({0, 65, 74}), ChordData({0, 68, 16}), 
 ChordData({0, 68, 73}), ChordData({0, 68, 192}), ChordData({2, 4, 64}), ChordData({2, 8, 129}), 
 ChordData({2, 12, 10}), ChordData({2, 12, 130}), ChordData({2, 32, 81}), ChordData({2, 32, 193}), 
 ChordData({2, 36, 10}), ChordData({2, 36, 18}), ChordData({2, 64, 144}), ChordData({2, 68, 8}), 
 ChordData({2, 68, 24}), ChordData({4, 4, 73}), ChordData({4, 4, 81}), ChordData({4, 4, 137}), 
 ChordData({4, 13, 0}), ChordData({6, 0, 25}), ChordData({6, 0, 81}), ChordData({6, 0, 193}), 
 ChordData({6, 4, 9}), ChordData({6, 4, 10}), ChordData({6, 4, 136}), ChordData({6, 8, 10}), 
 ChordData({16, 0, 211}), ChordData({16, 1, 130}), ChordData({16, 1, 131}), ChordData({16, 4, 83}), 
 ChordData({16, 5, 17}), ChordData({16, 5, 129}), ChordData({16, 5, 192}), ChordData({16, 8, 26}), 
 ChordData({16, 44, 1}), ChordData({16, 44, 64}), ChordData({16, 64, 67}), ChordData({16, 65, 16}), 
 ChordData({16, 73, 10}), ChordData({16, 76, 8}), ChordData({16, 76, 16}), ChordData({16, 76, 128}), 
 ChordData({16, 77, 2}), ChordData({16, 100, 1}), ChordData({16, 100, 16}), ChordData({16, 100, 64}), 
 ChordData({18, 72, 2}), ChordData({18, 76, 0}), ChordData({20, 4, 16}), ChordData({20, 8, 80}), 
 ChordData({20, 12, 128}), ChordData({20, 36, 2}), ChordData({20, 36, 64}), ChordData({20, 44, 0}), 
 ChordData({20, 64, 72}), ChordData({22, 8, 16}), ChordData({22, 64, 16}), ChordData({32, 0, 209}), 
 ChordData({32, 4, 145}), ChordData({32, 4, 152}), ChordData({32, 73, 2}), ChordData({34, 0, 137}), 
 ChordData({34, 9, 8}), ChordData({34, 65, 10}), ChordData({36, 0, 82}), ChordData({36, 9, 8}), 
 ChordData({36, 13, 2}), ChordData({36, 13, 8}), ChordData({36, 68, 66}), ChordData({48, 0, 65}), 
 ChordData({48, 5, 9}), ChordData({48, 5, 17}), ChordData({48, 5, 18}), ChordData({48, 5, 24}), 
 ChordData({48, 5, 65}), ChordData({48, 5, 128}), ChordData({48, 5, 136}), ChordData({48, 5, 144}), 
 ChordData({48, 9, 16}), ChordData({48, 12, 192}), ChordData({48, 64, 24}), ChordData({48, 65, 128}), 
 ChordData({50, 8, 16}), ChordData({50, 8, 144}), ChordData({50, 12, 8}), ChordData({52, 0, 80}), 
 ChordData({52, 0, 129}), ChordData({52, 0, 192}), ChordData({52, 4, 65}), ChordData({52, 4, 129}), 
 ChordData({52, 4, 130}), ChordData({52, 64, 16}), ChordData({52, 64, 128}), ChordData({54, 0, 144}), 
 ChordData({128, 0, 152}), ChordData({128, 8, 17}), ChordData({128, 8, 81}), ChordData({128, 12, 18}), 
 ChordData({128, 12, 72}), ChordData({128, 13, 18}), ChordData({128, 32, 24}), ChordData({128, 32, 25}), 
 ChordData({128, 32, 81}), ChordData({128, 32, 131}), ChordData({128, 36, 2}), ChordData({128, 36, 18}), 
 ChordData({128, 36, 66}), ChordData({128, 64, 24}), ChordData({128, 64, 65}), ChordData({128, 104, 2}), 
 ChordData({130, 8, 2}), ChordData({130, 8, 18}), ChordData({130, 8, 24}), ChordData({130, 8, 65}), 
 ChordData({130, 32, 18}), ChordData({130, 64, 1}), ChordData({130, 64, 65}), ChordData({130, 64, 66}), 
 ChordData({130, 64, 192}), ChordData({130, 68, 16}), ChordData({132, 0, 66}), ChordData({132, 0, 81}), 
 ChordData({132, 0, 192}), ChordData({132, 4, 144}), ChordData({134, 0, 3}), ChordData({134, 0, 16}), 
 ChordData({134, 0, 129}), ChordData({134, 0, 192}), ChordData({134, 4, 1}), ChordData({134, 4, 8}), 
 ChordData({144, 1, 9}), ChordData({144, 1, 18}), ChordData({144, 72, 8}), ChordData({144, 72, 128}), 
 ChordData({146, 64, 0}), ChordData({148, 32, 2}), ChordData({148, 32, 8}), ChordData({160, 0, 11}), 
 ChordData({160, 0, 19}), ChordData({160, 0, 67}), ChordData({160, 65, 18}), ChordData({160, 65, 130}), 
 ChordData({162, 0, 8}), ChordData({164, 9, 0}), ChordData({164, 9, 8}), ChordData({164, 64, 18}), 
 ChordData({164, 64, 130}), ChordData({176, 8, 18}), ChordData({176, 8, 64}), ChordData({176, 8, 136}), 
 ChordData({176, 8, 192}), ChordData({176, 32, 64}), ChordData({178, 8, 2}), ChordData({178, 8, 128}), 
 ChordData({180, 0, 136}), 
};

const uint8_t kmap0_Word_len21_anagram0_seqs[434] = {
 128, 127, 158, 211, 
 207, 62, 253, 36, 
 78, 79, 132, 240, 
 103, 231, 21, 225, 
 206, 51, 196, 121, 
 134, 12, 159, 136, 
 203, 204, 42, 31, 
 151, 121, 249, 195, 
 251, 42, 249, 233, 
 37, 120, 238, 167, 
 78, 189, 233, 181, 
 17, 233, 59, 49, 
 236, 217, 94, 193, 
 140, 240, 91, 17, 
 126, 143, 156, 38, 
 106, 149, 253, 114, 
 190, 181, 190, 46, 
 243, 206, 215, 74, 
 175, 91, 74, 95, 
 235, 180, 46, 239, 
 116, 229, 74, 189, 
 245, 91, 183, 190, 
 54, 86, 250, 214, 
 178, 173, 200, 91, 
 144, 15, 242, 213, 
 65, 198, 45, 252, 
 188, 127, 172, 231, 
 160, 95, 31, 79, 
 108, 171, 83, 177, 
 208, 233, 25, 126, 
 50, 95, 236, 149, 
 62, 60, 37, 245, 
 229, 147, 85, 202, 
 241, 167, 100, 249, 
 116, 249, 146, 165, 
 127, 33, 244, 143, 
 100, 248, 210, 201, 
 178, 49, 89, 246, 
 215, 175, 30, 174, 
 158, 148, 190, 146, 
 17, 250, 43, 195, 
 175, 134, 95, 214, 
 92, 173, 178, 78, 
 39, 215, 105, 105, 
 129, 204, 155, 105, 
 231, 51, 233, 143, 
 204, 88, 202, 186, 
 77, 165, 214, 251, 
 210, 122, 159, 153, 
 139, 154, 181, 116, 
 62, 150, 206, 215, 
 18, 95, 254, 4, 
 155, 205, 127, 91, 
 247, 30, 255, 222, 
 243, 232, 121, 189, 
 205, 251, 183, 201, 
 247, 211, 235, 77, 
 166, 159, 219, 201, 
 115, 155, 233, 69, 
 103, 149, 30, 178, 
 188, 61, 45, 122, 
 168, 69, 143, 126, 
 139, 230, 92, 61, 
 155, 43, 185, 102, 
 98, 159, 126, 222, 
 253, 147, 140, 127, 
 146, 207, 177, 229, 
 73, 182, 164, 62, 
 199, 64, 32, 52, 
 197, 198, 240, 198, 
 164, 244, 56, 145, 
 158, 67, 163, 244, 
 5, 12, 141, 209, 
 152, 133, 12, 99, 
 22, 41, 22, 98, 
 60, 194, 137, 71, 
 136, 240, 131, 101, 
 104, 12, 111, 132, 
 188, 192, 72, 24, 
 169, 49, 53, 78, 
 164, 214, 152, 20, 
 205, 139, 48, 122, 
 90, 118, 44, 175, 
 236, 144, 205, 24, 
 28, 212, 114, 94, 
 118, 48, 70, 84, 
 174, 49, 203, 53, 
 130, 106, 208, 207, 
 70, 109, 172, 211, 
 49, 181, 41, 150, 
 107, 52, 213, 223, 
 142, 218, 175, 17, 
 199, 90, 143, 24, 
 180, 116, 10, 77, 
 33, 77, 178, 67, 
 218, 53, 16, 86, 
 24, 106, 140, 172, 
 139, 145, 103, 25, 
 35, 239, 61, 113, 
 185, 41, 46, 89, 
 59, 244, 140, 40, 
 149, 52, 206, 51, 
 100, 113, 82, 92, 
 48, 68, 79, 138, 
 204, 214, 16, 77, 
 28, 36, 26, 70, 
 102, 139, 209, 232, 
 160, 22, 173, 113, 
 146, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len21_anagram0 = {
  LengthAndAnagram(21, 0), // seq_bit_len_and_anagram
  165, // num_chords
  kmap0_Word_len21_anagram0_chords, // chords
  kmap0_Word_len21_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len21_anagram1_chords[42] = {
 ChordData({0, 36, 3}), ChordData({0, 36, 192}), ChordData({2, 12, 8}), ChordData({2, 65, 0}), 
 ChordData({2, 65, 2}), ChordData({4, 4, 17}), ChordData({4, 4, 65}), ChordData({4, 4, 82}), 
 ChordData({16, 0, 27}), ChordData({16, 0, 146}), ChordData({16, 4, 146}), ChordData({16, 77, 2}), 
 ChordData({16, 100, 0}), ChordData({20, 4, 128}), ChordData({20, 36, 64}), ChordData({32, 0, 81}), 
 ChordData({32, 1, 2}), ChordData({32, 1, 146}), ChordData({32, 4, 144}), ChordData({34, 0, 138}), 
 ChordData({36, 0, 128}), ChordData({36, 8, 0}), ChordData({36, 72, 0}), ChordData({48, 5, 136}), 
 ChordData({48, 64, 18}), ChordData({52, 0, 65}), ChordData({52, 0, 192}), ChordData({52, 4, 64}), 
 ChordData({52, 4, 128}), ChordData({54, 0, 17}), ChordData({128, 9, 128}), ChordData({128, 12, 144}), 
 ChordData({128, 32, 1}), ChordData({128, 65, 130}), ChordData({132, 0, 17}), ChordData({134, 0, 3}), 
 ChordData({134, 0, 9}), ChordData({160, 0, 17}), ChordData({160, 9, 16}), ChordData({164, 8, 0}), 
 ChordData({164, 64, 130}), ChordData({176, 1, 64}), 
};

const uint8_t kmap0_Word_len21_anagram1_seqs[111] = {
 248, 139, 144, 233, 
 25, 166, 215, 126, 
 217, 199, 113, 233, 
 163, 191, 254, 108, 
 125, 222, 103, 156, 
 175, 214, 157, 2, 
 11, 36, 251, 135, 
 138, 139, 191, 244, 
 208, 47, 191, 86, 
 114, 133, 207, 222, 
 201, 188, 152, 143, 
 35, 223, 84, 76, 
 158, 167, 172, 125, 
 117, 102, 58, 207, 
 156, 170, 204, 233, 
 124, 189, 77, 56, 
 89, 154, 189, 185, 
 158, 100, 230, 250, 
 153, 77, 127, 154, 
 118, 250, 244, 17, 
 84, 74, 49, 79, 
 27, 177, 240, 160, 
 184, 236, 68, 212, 
 168, 219, 88, 163, 
 117, 55, 111, 204, 
 61, 81, 58, 35, 
 157, 103, 92, 232, 
 142, 96, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len21_anagram1 = {
  LengthAndAnagram(21, 1), // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_Word_len21_anagram1_chords, // chords
  kmap0_Word_len21_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len21_anagram2_chords[14] = {
 ChordData({0, 64, 2}), ChordData({6, 0, 192}), ChordData({16, 64, 3}), ChordData({36, 0, 18}), 
 ChordData({48, 5, 24}), ChordData({48, 8, 24}), ChordData({52, 0, 80}), ChordData({128, 9, 16}), 
 ChordData({128, 32, 65}), ChordData({128, 65, 130}), ChordData({132, 0, 17}), ChordData({160, 0, 17}), 
 ChordData({160, 0, 18}), ChordData({176, 8, 16}), 
};

const uint8_t kmap0_Word_len21_anagram2_seqs[37] = {
 151, 203, 133, 107, 
 19, 237, 197, 222, 
 201, 103, 241, 122, 
 123, 52, 39, 79, 
 205, 195, 62, 98, 
 74, 12, 35, 246, 
 18, 116, 212, 137, 
 141, 157, 200, 27, 
 136, 121, 38, 68, 
 15, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len21_anagram2 = {
  LengthAndAnagram(21, 2), // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_Word_len21_anagram2_chords, // chords
  kmap0_Word_len21_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len21_anagram3_chords[3] = {
 ChordData({16, 4, 82}), ChordData({32, 1, 128}), ChordData({48, 8, 8}), 
};

const uint8_t kmap0_Word_len21_anagram3_seqs[8] = {
 102, 254, 226, 206, 
 116, 136, 214, 108, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len21_anagram3 = {
  LengthAndAnagram(21, 3), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Word_len21_anagram3_chords, // chords
  kmap0_Word_len21_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len21_anagram4_chords[1] = {
 ChordData({16, 4, 146}), 
};

const uint8_t kmap0_Word_len21_anagram4_seqs[3] = {
 99, 250, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len21_anagram4 = {
  LengthAndAnagram(21, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len21_anagram4_chords, // chords
  kmap0_Word_len21_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len21_anagram5_chords[2] = {
 ChordData({128, 64, 2}), ChordData({128, 64, 18}), 
};

const uint8_t kmap0_Word_len21_anagram5_seqs[6] = {
 64, 198, 5, 35, 
 70, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len21_anagram5 = {
  LengthAndAnagram(21, 5), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len21_anagram5_chords, // chords
  kmap0_Word_len21_anagram5_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram0_chords[181] = {
 ChordData({0, 4, 18}), ChordData({0, 4, 91}), ChordData({0, 5, 19}), ChordData({0, 44, 3}), 
 ChordData({0, 44, 18}), ChordData({0, 44, 80}), ChordData({0, 76, 16}), ChordData({0, 77, 130}), 
 ChordData({2, 0, 210}), ChordData({2, 1, 81}), ChordData({2, 5, 24}), ChordData({2, 5, 136}), 
 ChordData({2, 9, 2}), ChordData({2, 36, 1}), ChordData({2, 72, 16}), ChordData({2, 73, 2}), 
 ChordData({2, 76, 1}), ChordData({2, 76, 8}), ChordData({2, 96, 17}), ChordData({2, 96, 130}), 
 ChordData({4, 12, 16}), ChordData({4, 12, 17}), ChordData({4, 12, 65}), ChordData({4, 12, 130}), 
 ChordData({4, 36, 3}), ChordData({4, 36, 80}), ChordData({4, 36, 128}), ChordData({4, 68, 1}), 
 ChordData({6, 32, 3}), ChordData({6, 68, 16}), ChordData({16, 0, 27}), ChordData({16, 0, 90}), 
 ChordData({16, 0, 145}), ChordData({16, 0, 193}), ChordData({16, 0, 195}), ChordData({16, 4, 19}), 
 ChordData({16, 4, 73}), ChordData({16, 8, 18}), ChordData({16, 8, 19}), ChordData({16, 9, 144}), 
 ChordData({16, 9, 146}), ChordData({16, 13, 16}), ChordData({16, 13, 65}), ChordData({16, 13, 72}), 
 ChordData({16, 32, 66}), ChordData({16, 33, 1}), ChordData({16, 33, 3}), ChordData({16, 33, 80}), 
 ChordData({16, 33, 192}), ChordData({16, 64, 82}), ChordData({16, 64, 129}), ChordData({16, 65, 144}), 
 ChordData({16, 68, 18}), ChordData({16, 68, 19}), ChordData({16, 68, 67}), ChordData({16, 96, 18}), 
 ChordData({16, 96, 130}), ChordData({18, 0, 25}), ChordData({18, 0, 80}), ChordData({18, 33, 2}), 
 ChordData({18, 64, 3}), ChordData({18, 64, 19}), ChordData({18, 64, 146}), ChordData({18, 65, 16}), 
 ChordData({18, 65, 128}), ChordData({20, 0, 26}), ChordData({20, 0, 146}), ChordData({20, 96, 1}), 
 ChordData({32, 4, 192}), ChordData({32, 5, 25}), ChordData({32, 5, 192}), ChordData({32, 8, 82}), 
 ChordData({32, 9, 0}), ChordData({32, 9, 2}), ChordData({32, 12, 144}), ChordData({32, 32, 17}), 
 ChordData({32, 32, 138}), ChordData({32, 68, 128}), ChordData({32, 68, 129}), ChordData({34, 5, 8}), 
 ChordData({34, 5, 9}), ChordData({34, 5, 24}), ChordData({34, 8, 65}), ChordData({34, 8, 66}), 
 ChordData({34, 8, 72}), ChordData({34, 8, 129}), ChordData({34, 8, 130}), ChordData({34, 12, 65}), 
 ChordData({34, 12, 129}), ChordData({34, 12, 144}), ChordData({34, 64, 129}), ChordData({34, 68, 1}), 
 ChordData({36, 0, 208}), ChordData({36, 4, 80}), ChordData({36, 4, 192}), ChordData({36, 4, 193}), 
 ChordData({36, 9, 2}), ChordData({36, 9, 128}), ChordData({38, 0, 9}), ChordData({38, 4, 10}), 
 ChordData({38, 4, 24}), ChordData({38, 4, 64}), ChordData({38, 4, 66}), ChordData({38, 4, 192}), 
 ChordData({48, 1, 64}), ChordData({48, 9, 1}), ChordData({48, 12, 8}), ChordData({48, 12, 128}), 
 ChordData({48, 44, 64}), ChordData({48, 44, 128}), ChordData({48, 69, 16}), ChordData({50, 13, 0}), 
 ChordData({50, 72, 16}), ChordData({50, 72, 128}), ChordData({52, 12, 128}), ChordData({52, 32, 10}), 
 ChordData({52, 36, 2}), ChordData({52, 36, 16}), ChordData({52, 64, 136}), ChordData({52, 68, 16}), 
 ChordData({52, 68, 128}), ChordData({52, 72, 0}), ChordData({128, 0, 82}), ChordData({128, 0, 83}), 
 ChordData({128, 1, 25}), ChordData({128, 1, 81}), ChordData({128, 1, 144}), ChordData({128, 4, 26}), 
 ChordData({128, 4, 146}), ChordData({128, 5, 129}), ChordData({128, 5, 130}), ChordData({128, 12, 2}), 
 ChordData({128, 40, 9}), ChordData({128, 73, 10}), ChordData({128, 73, 18}), ChordData({128, 96, 18}), 
 ChordData({128, 100, 16}), ChordData({130, 1, 128}), ChordData({130, 64, 16}), ChordData({132, 8, 0}), 
 ChordData({132, 8, 16}), ChordData({132, 32, 1}), ChordData({132, 68, 1}), ChordData({134, 8, 1}), 
 ChordData({144, 8, 26}), ChordData({144, 9, 9}), ChordData({144, 9, 144}), ChordData({144, 64, 19}), 
 ChordData({144, 64, 82}), ChordData({148, 0, 0}), ChordData({160, 1, 80}), ChordData({160, 5, 1}), 
 ChordData({160, 5, 8}), ChordData({160, 5, 18}), ChordData({160, 5, 24}), ChordData({160, 5, 136}), 
 ChordData({160, 8, 9}), ChordData({160, 8, 17}), ChordData({160, 12, 130}), ChordData({160, 32, 3}), 
 ChordData({160, 32, 65}), ChordData({160, 64, 8}), ChordData({160, 64, 9}), ChordData({160, 64, 24}), 
 ChordData({160, 64, 72}), ChordData({162, 1, 130}), ChordData({162, 1, 136}), ChordData({162, 8, 17}), 
 ChordData({162, 32, 8}), ChordData({162, 68, 0}), ChordData({164, 0, 65}), ChordData({164, 4, 10}), 
 ChordData({164, 4, 17}), ChordData({166, 0, 17}), ChordData({176, 13, 0}), ChordData({176, 65, 128}), 
 ChordData({176, 72, 16}), ChordData({178, 8, 0}), ChordData({178, 72, 0}), ChordData({180, 0, 16}), 
 ChordData({180, 8, 16}), 
};

const uint8_t kmap0_Word_len22_anagram0_seqs[498] = {
 63, 243, 133, 62, 
 111, 129, 243, 199, 
 166, 95, 132, 233, 
 7, 97, 250, 97, 
 40, 231, 211, 95, 
 158, 74, 220, 68, 
 197, 209, 195, 219, 
 122, 204, 31, 173, 
 79, 165, 198, 18, 
 88, 248, 61, 73, 
 246, 92, 186, 212, 
 47, 83, 239, 203, 
 212, 186, 176, 71, 
 34, 108, 146, 245, 
 231, 211, 206, 167, 
 202, 251, 169, 34, 
 125, 170, 245, 23, 
 33, 195, 159, 250, 
 84, 225, 191, 252, 
 186, 181, 23, 225, 
 124, 109, 57, 70, 
 235, 50, 142, 173, 
 228, 93, 15, 123, 
 151, 204, 38, 227, 
 226, 248, 215, 108, 
 253, 117, 242, 96, 
 145, 188, 83, 8, 
 120, 74, 72, 158, 
 210, 49, 159, 204, 
 251, 37, 179, 250, 
 75, 8, 109, 246, 
 66, 31, 123, 120, 
 17, 30, 99, 134, 
 12, 77, 7, 227, 
 248, 34, 77, 94, 
 31, 227, 50, 227, 
 151, 197, 229, 215, 
 115, 121, 94, 95, 
 160, 199, 23, 104, 
 147, 117, 123, 204, 
 158, 54, 35, 108, 
 31, 123, 105, 244, 
 101, 122, 93, 180, 
 73, 30, 211, 150, 
 71, 155, 100, 181, 
 106, 49, 174, 84, 
 72, 215, 133, 153, 
 243, 211, 61, 175, 
 123, 211, 51, 51, 
 78, 78, 32, 131, 
 210, 145, 177, 36, 
 240, 226, 239, 228, 
 133, 148, 21, 97, 
 153, 252, 244, 50, 
 211, 254, 253, 173, 
 119, 191, 238, 61, 
 223, 42, 54, 247, 
 166, 204, 141, 169, 
 53, 115, 202, 180, 
 141, 45, 54, 137, 
 205, 251, 98, 239, 
 147, 216, 243, 84, 
 38, 247, 126, 150, 
 189, 76, 121, 234, 
 57, 207, 124, 62, 
 63, 157, 244, 188, 
 103, 198, 210, 153, 
 169, 212, 90, 243, 
 226, 159, 173, 231, 
 124, 235, 249, 220, 
 124, 62, 55, 158, 
 207, 77, 119, 54, 
 179, 232, 219, 11, 
 44, 190, 138, 79, 
 217, 12, 95, 52, 
 124, 18, 125, 207, 
 75, 119, 250, 219, 
 114, 90, 180, 180, 
 216, 116, 210, 39, 
 159, 86, 132, 167, 
 31, 225, 24, 254, 
 121, 146, 85, 158, 
 227, 151, 39, 189, 
 180, 211, 105, 201, 
 49, 83, 240, 198, 
 20, 199, 132, 238, 
 49, 193, 123, 80, 
 196, 188, 106, 20, 
 79, 20, 197, 65, 
 241, 123, 4, 62, 
 97, 164, 244, 41, 
 116, 97, 73, 227, 
 114, 137, 41, 33, 
 140, 145, 48, 126, 
 228, 17, 212, 33, 
 39, 90, 150, 141, 
 72, 117, 34, 69, 
 133, 177, 241, 50, 
 234, 70, 221, 78, 
 41, 212, 197, 70, 
 201, 42, 16, 37, 
 95, 38, 214, 151, 
 24, 54, 168, 81, 
 125, 79, 48, 223, 
 177, 251, 119, 168, 
 62, 254, 220, 17, 
 115, 191, 62, 133, 
 222, 41, 178, 238, 
 230, 20, 35, 6, 
 62, 109, 100, 132, 
 28, 121, 161, 204, 
 170, 33, 67, 243, 
 78, 100, 149, 28, 
 89, 37, 197, 221, 
 72, 113, 183, 138, 
 189, 19, 48, 119, 
 232, 103, 217, 113, 
 70, 240, 158, 143, 
 161, 127, 198, 108, 
 204, 217, 27, 201, 
 247, 83, 200, 219, 
 114, 66, 116, 10, 
 177, 45, 182, 116, 
 212, 137, 211, 117, 
 66, 52, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram0 = {
  LengthAndAnagram(22, 0), // seq_bit_len_and_anagram
  181, // num_chords
  kmap0_Word_len22_anagram0_chords, // chords
  kmap0_Word_len22_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram1_chords[38] = {
 ChordData({0, 4, 82}), ChordData({0, 5, 129}), ChordData({0, 12, 1}), ChordData({0, 12, 18}), 
 ChordData({0, 44, 18}), ChordData({2, 0, 146}), ChordData({16, 0, 83}), ChordData({16, 8, 18}), 
 ChordData({16, 13, 72}), ChordData({16, 33, 192}), ChordData({16, 64, 136}), ChordData({16, 68, 146}), 
 ChordData({18, 4, 80}), ChordData({32, 5, 80}), ChordData({32, 33, 0}), ChordData({32, 68, 129}), 
 ChordData({34, 1, 144}), ChordData({34, 5, 128}), ChordData({34, 5, 136}), ChordData({34, 12, 128}), 
 ChordData({36, 4, 18}), ChordData({48, 1, 65}), ChordData({48, 8, 18}), ChordData({48, 44, 8}), 
 ChordData({50, 33, 1}), ChordData({50, 65, 16}), ChordData({52, 12, 16}), ChordData({128, 0, 154}), 
 ChordData({128, 4, 146}), ChordData({132, 64, 16}), ChordData({144, 0, 81}), ChordData({144, 32, 26}), 
 ChordData({144, 64, 19}), ChordData({160, 64, 130}), ChordData({164, 0, 17}), ChordData({164, 4, 144}), 
 ChordData({176, 9, 8}), ChordData({176, 72, 16}), 
};

const uint8_t kmap0_Word_len22_anagram1_seqs[105] = {
 140, 63, 197, 241, 
 251, 4, 210, 239, 
 130, 244, 131, 8, 
 127, 18, 21, 211, 
 200, 198, 241, 38, 
 207, 20, 172, 95, 
 242, 65, 102, 168, 
 182, 36, 75, 211, 
 23, 126, 110, 207, 
 61, 207, 12, 243, 
 113, 148, 201, 191, 
 247, 52, 209, 77, 
 253, 244, 212, 183, 
 138, 77, 244, 231, 
 159, 197, 157, 205, 
 107, 209, 83, 192, 
 23, 173, 238, 27, 
 238, 180, 188, 253, 
 233, 244, 104, 65, 
 161, 19, 197, 147, 
 156, 136, 202, 235, 
 113, 192, 80, 23, 
 27, 23, 15, 70, 
 38, 57, 113, 198, 
 210, 159, 49, 183, 
 70, 178, 12, 209, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram1 = {
  LengthAndAnagram(22, 1), // seq_bit_len_and_anagram
  38, // num_chords
  kmap0_Word_len22_anagram1_chords, // chords
  kmap0_Word_len22_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram2_chords[11] = {
 ChordData({0, 4, 18}), ChordData({6, 0, 1}), ChordData({16, 0, 27}), ChordData({16, 0, 81}), 
 ChordData({16, 4, 82}), ChordData({16, 13, 128}), ChordData({18, 65, 8}), ChordData({48, 8, 18}), 
 ChordData({48, 9, 16}), ChordData({52, 4, 64}), ChordData({160, 64, 130}), 
};

const uint8_t kmap0_Word_len22_anagram2_seqs[31] = {
 248, 51, 69, 237, 
 218, 139, 214, 245, 
 240, 142, 189, 56, 
 126, 246, 65, 159, 
 108, 149, 125, 96, 
 30, 209, 162, 231, 
 246, 159, 153, 141, 
 20, 89, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram2 = {
  LengthAndAnagram(22, 2), // seq_bit_len_and_anagram
  11, // num_chords
  kmap0_Word_len22_anagram2_chords, // chords
  kmap0_Word_len22_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram3_chords[5] = {
 ChordData({16, 0, 130}), ChordData({16, 4, 18}), ChordData({16, 4, 145}), ChordData({36, 1, 0}), 
 ChordData({176, 1, 16}), 
};

const uint8_t kmap0_Word_len22_anagram3_seqs[14] = {
 190, 66, 19, 254, 
 216, 51, 166, 95, 
 215, 124, 28, 19, 
 119, 54, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram3 = {
  LengthAndAnagram(22, 3), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Word_len22_anagram3_chords, // chords
  kmap0_Word_len22_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram4_chords[3] = {
 ChordData({16, 4, 65}), ChordData({48, 9, 16}), ChordData({176, 1, 16}), 
};

const uint8_t kmap0_Word_len22_anagram4_seqs[9] = {
 230, 253, 245, 97, 
 209, 51, 145, 111, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram4 = {
  LengthAndAnagram(22, 4), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Word_len22_anagram4_chords, // chords
  kmap0_Word_len22_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram5_chords[2] = {
 ChordData({16, 4, 146}), ChordData({16, 68, 18}), 
};

const uint8_t kmap0_Word_len22_anagram5_seqs[6] = {
 160, 120, 242, 95, 
 126, 12, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram5 = {
  LengthAndAnagram(22, 5), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len22_anagram5_chords, // chords
  kmap0_Word_len22_anagram5_seqs, // sequences
};

const ChordData kmap0_Word_len22_anagram6_chords[1] = {
 ChordData({16, 68, 18}), 
};

const uint8_t kmap0_Word_len22_anagram6_seqs[3] = {
 210, 248, 5, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len22_anagram6 = {
  LengthAndAnagram(22, 6), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len22_anagram6_chords, // chords
  kmap0_Word_len22_anagram6_seqs, // sequences
};

const ChordData kmap0_Word_len23_anagram0_chords[167] = {
 ChordData({0, 13, 19}), ChordData({0, 13, 26}), ChordData({0, 13, 67}), ChordData({0, 13, 146}), 
 ChordData({0, 13, 194}), ChordData({0, 32, 91}), ChordData({0, 37, 65}), ChordData({0, 37, 192}), 
 ChordData({0, 68, 10}), ChordData({0, 69, 16}), ChordData({0, 69, 17}), ChordData({2, 9, 19}), 
 ChordData({2, 9, 67}), ChordData({2, 9, 81}), ChordData({2, 9, 130}), ChordData({2, 9, 192}), 
 ChordData({2, 32, 90}), ChordData({2, 33, 65}), ChordData({2, 37, 1}), ChordData({2, 40, 128}), 
 ChordData({2, 64, 19}), ChordData({2, 64, 67}), ChordData({2, 64, 83}), ChordData({2, 68, 67}), 
 ChordData({2, 68, 82}), ChordData({2, 68, 146}), ChordData({2, 96, 128}), ChordData({4, 0, 19}), 
 ChordData({4, 4, 19}), ChordData({4, 12, 146}), ChordData({6, 0, 82}), ChordData({16, 1, 18}), 
 ChordData({16, 4, 11}), ChordData({16, 4, 26}), ChordData({16, 4, 27}), ChordData({16, 4, 64}), 
 ChordData({16, 4, 75}), ChordData({16, 4, 81}), ChordData({16, 4, 131}), ChordData({16, 4, 137}), 
 ChordData({16, 4, 147}), ChordData({16, 4, 195}), ChordData({16, 8, 11}), ChordData({16, 41, 2}), 
 ChordData({16, 45, 64}), ChordData({16, 64, 3}), ChordData({16, 64, 24}), ChordData({16, 77, 8}), 
 ChordData({16, 100, 3}), ChordData({16, 100, 130}), ChordData({18, 0, 9}), ChordData({18, 0, 75}), 
 ChordData({18, 0, 81}), ChordData({18, 0, 129}), ChordData({18, 0, 139}), ChordData({18, 0, 146}), 
 ChordData({18, 0, 195}), ChordData({18, 0, 201}), ChordData({18, 4, 17}), ChordData({18, 4, 25}), 
 ChordData({18, 4, 152}), ChordData({18, 4, 200}), ChordData({18, 4, 208}), ChordData({18, 64, 80}), 
 ChordData({18, 96, 3}), ChordData({18, 96, 130}), ChordData({20, 4, 17}), ChordData({20, 4, 192}), 
 ChordData({20, 8, 19}), ChordData({20, 13, 64}), ChordData({20, 32, 18}), ChordData({20, 32, 82}), 
 ChordData({22, 0, 1}), ChordData({22, 9, 64}), ChordData({22, 64, 66}), ChordData({32, 0, 18}), 
 ChordData({32, 0, 147}), ChordData({32, 1, 19}), ChordData({32, 1, 130}), ChordData({32, 5, 80}), 
 ChordData({32, 5, 129}), ChordData({32, 40, 10}), ChordData({32, 44, 8}), ChordData({32, 69, 24}), 
 ChordData({34, 0, 27}), ChordData({34, 1, 17}), ChordData({34, 1, 129}), ChordData({34, 8, 80}), 
 ChordData({34, 13, 2}), ChordData({34, 13, 64}), ChordData({34, 33, 9}), ChordData({34, 33, 17}), 
 ChordData({34, 33, 65}), ChordData({34, 33, 129}), ChordData({34, 65, 1}), ChordData({34, 76, 64}), 
 ChordData({34, 76, 128}), ChordData({36, 0, 81}), ChordData({36, 4, 24}), ChordData({36, 4, 66}), 
 ChordData({36, 5, 80}), ChordData({36, 8, 144}), ChordData({36, 36, 3}), ChordData({36, 68, 24}), 
 ChordData({38, 0, 2}), ChordData({38, 0, 129}), ChordData({38, 8, 130}), ChordData({38, 32, 17}), 
 ChordData({38, 36, 1}), ChordData({38, 64, 136}), ChordData({48, 0, 82}), ChordData({48, 8, 136}), 
 ChordData({48, 65, 8}), ChordData({48, 76, 0}), ChordData({50, 65, 0}), ChordData({52, 5, 8}), 
 ChordData({52, 12, 16}), ChordData({54, 1, 8}), ChordData({54, 1, 16}), ChordData({128, 9, 67}), 
 ChordData({128, 9, 146}), ChordData({128, 33, 17}), ChordData({128, 64, 83}), ChordData({128, 68, 19}), 
 ChordData({128, 68, 130}), ChordData({132, 1, 16}), ChordData({132, 1, 64}), ChordData({132, 40, 2}), 
 ChordData({132, 40, 16}), ChordData({144, 0, 17}), ChordData({144, 0, 83}), ChordData({144, 0, 88}), 
 ChordData({144, 0, 152}), ChordData({144, 0, 200}), ChordData({144, 1, 16}), ChordData({144, 4, 17}), 
 ChordData({144, 4, 72}), ChordData({144, 4, 88}), ChordData({144, 4, 130}), ChordData({144, 4, 131}), 
 ChordData({144, 4, 146}), ChordData({144, 9, 64}), ChordData({144, 41, 2}), ChordData({144, 72, 10}), 
 ChordData({144, 96, 66}), ChordData({144, 96, 130}), ChordData({146, 0, 11}), ChordData({146, 0, 25}), 
 ChordData({146, 0, 129}), ChordData({148, 9, 64}), ChordData({148, 64, 18}), ChordData({160, 1, 66}), 
 ChordData({160, 1, 144}), ChordData({160, 13, 8}), ChordData({160, 40, 1}), ChordData({160, 40, 16}), 
 ChordData({162, 76, 0}), ChordData({164, 0, 72}), ChordData({164, 4, 1}), ChordData({164, 8, 2}), 
 ChordData({164, 8, 128}), ChordData({164, 64, 16}), ChordData({164, 68, 16}), ChordData({166, 8, 1}), 
 ChordData({176, 9, 128}), ChordData({176, 65, 0}), ChordData({180, 12, 0}), 
};

const uint8_t kmap0_Word_len23_anagram0_seqs[481] = {
 59, 143, 37, 156, 
 215, 18, 239, 99, 
 73, 224, 177, 196, 
 244, 88, 226, 66, 
 23, 50, 252, 99, 
 15, 122, 134, 151, 
 87, 253, 227, 231, 
 165, 156, 63, 118, 
 167, 177, 196, 219, 
 88, 226, 82, 207, 
 34, 53, 150, 184, 
 212, 68, 12, 91, 
 11, 134, 125, 236, 
 241, 189, 16, 180, 
 224, 36, 123, 182, 
 216, 75, 243, 94, 
 166, 121, 47, 223, 
 188, 242, 155, 11, 
 249, 77, 5, 104, 
 193, 18, 167, 168, 
 91, 127, 182, 160, 
 47, 91, 48, 118, 
 45, 14, 207, 20, 
 143, 104, 93, 124, 
 69, 207, 206, 43, 
 250, 153, 205, 204, 
 251, 138, 126, 102, 
 207, 250, 234, 113, 
 233, 215, 186, 190, 
 218, 121, 124, 94, 
 50, 58, 89, 23, 
 161, 177, 196, 240, 
 75, 150, 94, 227, 
 142, 85, 122, 244, 
 75, 150, 23, 232, 
 223, 11, 124, 114, 
 235, 90, 151, 177, 
 173, 59, 230, 230, 
 165, 222, 37, 35, 
 181, 117, 177, 7, 
 201, 190, 106, 94, 
 106, 94, 235, 239, 
 246, 120, 188, 223, 
 74, 173, 254, 225, 
 167, 86, 179, 167, 
 159, 164, 185, 199, 
 23, 216, 235, 11, 
 108, 242, 184, 250, 
 183, 146, 159, 237, 
 84, 183, 224, 234, 
 47, 193, 162, 122, 
 92, 97, 193, 213, 
 219, 107, 174, 93, 
 50, 95, 186, 26, 
 243, 76, 177, 147, 
 169, 192, 201, 199, 
 30, 148, 175, 56, 
 223, 63, 199, 103, 
 218, 148, 21, 33, 
 204, 233, 245, 158, 
 87, 153, 181, 183, 
 56, 38, 247, 222, 
 185, 105, 197, 158, 
 204, 233, 239, 70, 
 238, 59, 253, 194, 
 214, 123, 250, 134, 
 203, 125, 195, 165, 
 190, 225, 202, 190, 
 123, 95, 138, 205, 
 226, 83, 203, 51, 
 15, 111, 158, 243, 
 149, 49, 159, 127, 
 207, 115, 21, 200, 
 169, 158, 191, 8, 
 207, 121, 149, 152, 
 207, 198, 51, 55, 
 45, 82, 167, 243, 
 236, 89, 8, 255, 
 236, 61, 169, 85, 
 178, 49, 143, 77, 
 22, 173, 210, 71, 
 86, 32, 95, 244, 
 157, 91, 250, 244, 
 253, 122, 206, 139, 
 62, 125, 183, 158, 
 211, 62, 120, 3, 
 75, 2, 129, 165, 
 35, 102, 225, 37, 
 134, 119, 67, 126, 
 241, 68, 113, 169, 
 19, 113, 112, 141, 
 56, 16, 70, 170, 
 41, 166, 194, 245, 
 76, 12, 27, 55, 
 134, 173, 28, 99, 
 157, 32, 34, 51, 
 135, 198, 113, 120, 
 38, 246, 215, 236, 
 231, 208, 241, 115, 
 40, 5, 62, 153, 
 2, 127, 29, 243, 
 72, 230, 20, 37, 
 35, 140, 146, 47, 
 145, 172, 23, 24, 
 236, 11, 12, 178, 
 198, 54, 58, 166, 
 173, 187, 209, 228, 
 229, 26, 37, 215, 
 184, 120, 142, 192, 
 204, 7, 69, 158, 
 79, 161, 119, 138, 
 188, 16, 230, 20, 
 243, 98, 180, 60, 
 67, 51, 255, 25, 
 121, 49, 210, 25, 
 39, 69, 164, 58, 
 145, 229, 25, 63, 
 178, 182, 24, 123, 
 83, 136, 150, 33, 
 111, 255, 25, 162, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len23_anagram0 = {
  LengthAndAnagram(23, 0), // seq_bit_len_and_anagram
  167, // num_chords
  kmap0_Word_len23_anagram0_chords, // chords
  kmap0_Word_len23_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len23_anagram1_chords[60] = {
 ChordData({0, 13, 18}), ChordData({0, 36, 19}), ChordData({0, 68, 26}), ChordData({0, 109, 2}), 
 ChordData({2, 68, 18}), ChordData({16, 0, 81}), ChordData({16, 4, 9}), ChordData({16, 4, 66}), 
 ChordData({16, 4, 131}), ChordData({16, 4, 137}), ChordData({16, 4, 138}), ChordData({16, 64, 11}), 
 ChordData({16, 96, 19}), ChordData({18, 0, 73}), ChordData({18, 0, 81}), ChordData({18, 0, 89}), 
 ChordData({18, 0, 201}), ChordData({18, 32, 17}), ChordData({18, 64, 18}), ChordData({18, 64, 80}), 
 ChordData({18, 64, 192}), ChordData({20, 4, 66}), ChordData({22, 0, 18}), ChordData({32, 0, 146}), 
 ChordData({32, 12, 129}), ChordData({34, 33, 1}), ChordData({34, 33, 9}), ChordData({34, 65, 24}), 
 ChordData({36, 1, 0}), ChordData({36, 4, 128}), ChordData({36, 32, 10}), ChordData({38, 0, 128}), 
 ChordData({48, 0, 82}), ChordData({48, 8, 80}), ChordData({48, 13, 16}), ChordData({52, 0, 18}), 
 ChordData({52, 5, 128}), ChordData({54, 0, 128}), ChordData({54, 1, 16}), ChordData({128, 0, 19}), 
 ChordData({128, 9, 130}), ChordData({128, 64, 26}), ChordData({128, 65, 128}), ChordData({128, 68, 18}), 
 ChordData({128, 104, 2}), ChordData({144, 0, 26}), ChordData({144, 0, 82}), ChordData({144, 0, 83}), 
 ChordData({144, 0, 89}), ChordData({144, 1, 2}), ChordData({144, 8, 17}), ChordData({146, 0, 88}), 
 ChordData({160, 33, 65}), ChordData({164, 32, 1}), ChordData({164, 64, 8}), ChordData({164, 64, 128}), 
 ChordData({164, 68, 16}), ChordData({176, 1, 16}), ChordData({176, 9, 16}), ChordData({180, 1, 128}), 
};

const uint8_t kmap0_Word_len23_anagram1_seqs[173] = {
 56, 143, 165, 226, 
 17, 46, 190, 202, 
 2, 254, 165, 36, 
 191, 167, 224, 29, 
 51, 175, 245, 117, 
 31, 209, 204, 244, 
 235, 171, 125, 178, 
 46, 190, 162, 73, 
 26, 173, 187, 112, 
 124, 89, 171, 54, 
 115, 243, 122, 90, 
 217, 179, 220, 100, 
 93, 247, 66, 207, 
 197, 61, 114, 204, 
 45, 45, 219, 108, 
 50, 227, 87, 143, 
 177, 171, 5, 242, 
 20, 226, 103, 218, 
 237, 27, 174, 246, 
 13, 247, 158, 86, 
 121, 230, 227, 0, 
 245, 51, 213, 172, 
 8, 107, 174, 77, 
 99, 198, 108, 182, 
 232, 241, 61, 47, 
 26, 139, 211, 115, 
 254, 109, 58, 251, 
 36, 31, 125, 122, 
 192, 78, 20, 72, 
 129, 37, 156, 184, 
 232, 65, 17, 242, 
 103, 226, 130, 48, 
 133, 196, 24, 245, 
 112, 32, 122, 204, 
 24, 179, 107, 229, 
 24, 12, 31, 199, 
 56, 197, 154, 173, 
 29, 115, 195, 224, 
 61, 35, 22, 214, 
 200, 42, 79, 138, 
 144, 231, 196, 203, 
 35, 230, 246, 61, 
 33, 250, 166, 56, 
 13, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len23_anagram1 = {
  LengthAndAnagram(23, 1), // seq_bit_len_and_anagram
  60, // num_chords
  kmap0_Word_len23_anagram1_chords, // chords
  kmap0_Word_len23_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len23_anagram2_chords[18] = {
 ChordData({0, 68, 26}), ChordData({2, 68, 18}), ChordData({4, 4, 82}), ChordData({16, 4, 81}), 
 ChordData({16, 4, 131}), ChordData({16, 4, 138}), ChordData({16, 4, 145}), ChordData({18, 0, 25}), 
 ChordData({18, 0, 89}), ChordData({18, 0, 131}), ChordData({18, 4, 145}), ChordData({20, 4, 192}), 
 ChordData({22, 0, 18}), ChordData({32, 68, 128}), ChordData({48, 8, 192}), ChordData({52, 1, 16}), 
 ChordData({128, 12, 18}), ChordData({164, 0, 17}), 
};

const uint8_t kmap0_Word_len23_anagram2_seqs[52] = {
 243, 42, 11, 217, 
 63, 5, 215, 249, 
 226, 103, 204, 139, 
 191, 75, 126, 85, 
 95, 209, 239, 122, 
 90, 215, 163, 220, 
 186, 30, 83, 99, 
 239, 120, 191, 201, 
 244, 149, 93, 219, 
 131, 46, 147, 95, 
 50, 217, 162, 235, 
 61, 174, 159, 98, 
 138, 205, 115, 6, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len23_anagram2 = {
  LengthAndAnagram(23, 2), // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_Word_len23_anagram2_chords, // chords
  kmap0_Word_len23_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len23_anagram3_chords[4] = {
 ChordData({16, 4, 146}), ChordData({20, 0, 19}), ChordData({48, 12, 128}), ChordData({128, 12, 18}), 
};

const uint8_t kmap0_Word_len23_anagram3_seqs[12] = {
 99, 250, 171, 49, 
 186, 174, 248, 36, 
 58, 125, 17, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len23_anagram3 = {
  LengthAndAnagram(23, 3), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Word_len23_anagram3_chords, // chords
  kmap0_Word_len23_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len24_anagram0_chords[179] = {
 ChordData({0, 5, 26}), ChordData({0, 45, 9}), ChordData({0, 45, 80}), ChordData({0, 68, 3}), 
 ChordData({0, 72, 16}), ChordData({2, 0, 82}), ChordData({2, 0, 83}), ChordData({2, 0, 138}), 
 ChordData({2, 1, 72}), ChordData({2, 4, 3}), ChordData({2, 4, 11}), ChordData({2, 4, 65}), 
 ChordData({2, 4, 67}), ChordData({2, 4, 131}), ChordData({2, 9, 18}), ChordData({2, 41, 3}), 
 ChordData({2, 41, 9}), ChordData({2, 73, 24}), ChordData({2, 77, 8}), ChordData({4, 13, 80}), 
 ChordData({4, 32, 82}), ChordData({4, 68, 74}), ChordData({6, 8, 146}), ChordData({6, 9, 128}), 
 ChordData({16, 0, 83}), ChordData({16, 0, 91}), ChordData({16, 12, 17}), ChordData({16, 12, 18}), 
 ChordData({16, 12, 24}), ChordData({16, 12, 81}), ChordData({16, 12, 137}), ChordData({16, 32, 136}), 
 ChordData({16, 36, 10}), ChordData({16, 36, 17}), ChordData({16, 36, 82}), ChordData({16, 36, 192}), 
 ChordData({16, 40, 66}), ChordData({16, 40, 129}), ChordData({16, 68, 2}), ChordData({16, 68, 9}), 
 ChordData({16, 68, 137}), ChordData({16, 68, 138}), ChordData({16, 104, 130}), ChordData({18, 1, 144}), 
 ChordData({18, 4, 130}), ChordData({18, 8, 19}), ChordData({18, 9, 0}), ChordData({18, 9, 8}), 
 ChordData({18, 12, 24}), ChordData({18, 12, 130}), ChordData({18, 32, 11}), ChordData({18, 32, 65}), 
 ChordData({18, 64, 2}), ChordData({18, 64, 8}), ChordData({18, 64, 9}), ChordData({18, 64, 24}), 
 ChordData({18, 64, 72}), ChordData({18, 64, 138}), ChordData({18, 68, 129}), ChordData({20, 4, 3}), 
 ChordData({20, 4, 9}), ChordData({20, 4, 19}), ChordData({20, 4, 67}), ChordData({20, 4, 82}), 
 ChordData({20, 4, 137}), ChordData({20, 8, 129}), ChordData({20, 32, 66}), ChordData({20, 32, 80}), 
 ChordData({22, 0, 130}), ChordData({22, 0, 138}), ChordData({22, 4, 16}), ChordData({22, 4, 17}), 
 ChordData({22, 4, 80}), ChordData({32, 4, 82}), ChordData({32, 5, 26}), ChordData({32, 9, 19}), 
 ChordData({32, 9, 25}), ChordData({32, 9, 67}), ChordData({32, 9, 152}), ChordData({32, 9, 192}), 
 ChordData({32, 13, 0}), ChordData({32, 32, 18}), ChordData({32, 33, 192}), ChordData({32, 37, 128}), 
 ChordData({32, 64, 83}), ChordData({34, 8, 19}), ChordData({34, 8, 154}), ChordData({34, 41, 1}), 
 ChordData({34, 65, 128}), ChordData({34, 104, 0}), ChordData({36, 8, 18}), ChordData({36, 12, 128}), 
 ChordData({36, 32, 10}), ChordData({36, 32, 80}), ChordData({36, 37, 16}), ChordData({38, 1, 24}), 
 ChordData({38, 64, 128}), ChordData({48, 0, 25}), ChordData({48, 0, 74}), ChordData({48, 0, 137}), 
 ChordData({48, 0, 145}), ChordData({48, 0, 200}), ChordData({48, 0, 209}), ChordData({48, 1, 146}), 
 ChordData({48, 4, 25}), ChordData({48, 4, 80}), ChordData({48, 4, 152}), ChordData({48, 4, 194}), 
 ChordData({48, 5, 80}), ChordData({48, 8, 146}), ChordData({48, 8, 192}), ChordData({48, 9, 128}), 
 ChordData({48, 44, 18}), ChordData({48, 64, 18}), ChordData({48, 64, 136}), ChordData({48, 64, 144}), 
 ChordData({48, 65, 2}), ChordData({48, 65, 16}), ChordData({50, 0, 65}), ChordData({50, 0, 82}), 
 ChordData({50, 0, 88}), ChordData({50, 0, 146}), ChordData({50, 1, 8}), ChordData({50, 8, 80}), 
 ChordData({52, 0, 17}), ChordData({52, 1, 8}), ChordData({52, 4, 136}), ChordData({52, 12, 18}), 
 ChordData({52, 13, 16}), ChordData({52, 69, 0}), ChordData({128, 0, 11}), ChordData({128, 0, 210}), 
 ChordData({128, 4, 1}), ChordData({128, 4, 27}), ChordData({128, 4, 82}), ChordData({128, 4, 210}), 
 ChordData({128, 41, 66}), ChordData({128, 64, 82}), ChordData({128, 64, 146}), ChordData({128, 76, 2}), 
 ChordData({128, 96, 19}), ChordData({128, 96, 74}), ChordData({130, 0, 131}), ChordData({130, 0, 153}), 
 ChordData({130, 4, 25}), ChordData({130, 4, 194}), ChordData({144, 8, 17}), ChordData({144, 8, 25}), 
 ChordData({144, 32, 11}), ChordData({144, 32, 66}), ChordData({144, 32, 73}), ChordData({144, 32, 74}), 
 ChordData({144, 32, 193}), ChordData({144, 64, 18}), ChordData({144, 64, 74}), ChordData({144, 64, 208}), 
 ChordData({144, 68, 9}), ChordData({146, 32, 2}), ChordData({146, 64, 17}), ChordData({146, 64, 130}), 
 ChordData({148, 0, 17}), ChordData({148, 0, 88}), ChordData({148, 0, 128}), ChordData({150, 0, 130}), 
 ChordData({160, 1, 146}), ChordData({160, 9, 16}), ChordData({160, 13, 16}), ChordData({160, 32, 19}), 
 ChordData({160, 33, 16}), ChordData({160, 65, 8}), ChordData({162, 8, 18}), ChordData({164, 1, 16}), 
 ChordData({164, 64, 1}), ChordData({164, 64, 8}), ChordData({166, 1, 1}), ChordData({166, 1, 8}), 
 ChordData({176, 0, 82}), ChordData({180, 9, 16}), ChordData({180, 64, 130}), 
};

const uint8_t kmap0_Word_len24_anagram0_seqs[537] = {
 199, 43, 22, 11, 
 95, 75, 12, 127, 
 74, 224, 242, 187, 
 32, 141, 48, 56, 
 205, 205, 188, 211, 
 184, 72, 173, 141, 
 172, 125, 28, 251, 
 184, 141, 173, 251, 
 184, 207, 220, 188, 
 188, 191, 141, 189, 
 79, 141, 96, 26, 
 75, 11, 27, 75, 
 11, 91, 75, 114, 
 90, 75, 165, 86, 
 249, 92, 127, 74, 
 149, 11, 132, 92, 
 255, 162, 157, 42, 
 21, 181, 212, 68, 
 133, 121, 61, 107, 
 43, 23, 233, 119, 
 61, 248, 201, 243, 
 233, 85, 61, 188, 
 227, 79, 201, 186, 
 79, 0, 154, 172, 
 8, 95, 209, 243, 
 11, 61, 236, 31, 
 132, 240, 153, 201, 
 140, 208, 201, 208, 
 148, 188, 210, 248, 
 210, 191, 107, 149, 
 210, 186, 79, 248, 
 42, 201, 23, 104, 
 74, 99, 106, 31, 
 224, 169, 209, 201, 
 59, 141, 32, 117, 
 201, 37, 237, 195, 
 227, 244, 173, 233, 
 169, 209, 94, 168, 
 141, 11, 205, 205, 
 210, 216, 210, 173, 
 210, 150, 45, 173, 
 219, 178, 85, 61, 
 173, 220, 210, 173, 
 210, 87, 210, 251, 
 77, 143, 232, 186, 
 245, 215, 186, 248, 
 83, 189, 207, 213, 
 184, 140, 243, 213, 
 149, 94, 189, 235, 
 84, 201, 92, 109, 
 132, 92, 161, 199, 
 181, 175, 76, 213, 
 138, 77, 227, 250, 
 61, 181, 231, 215, 
 117, 190, 217, 128, 
 139, 252, 175, 247, 
 20, 59, 25, 75, 
 59, 89, 75, 188, 
 25, 75, 2, 89, 
 75, 92, 202, 68, 
 247, 167, 244, 48, 
 207, 20, 7, 101, 
 134, 244, 249, 134, 
 188, 89, 22, 45, 
 246, 22, 98, 107, 
 65, 169, 111, 184, 
 7, 229, 150, 48, 
 167, 150, 56, 57, 
 157, 79, 103, 78, 
 103, 86, 132, 231, 
 100, 134, 247, 124, 
 133, 231, 180, 222, 
 103, 110, 146, 227, 
 205, 163, 104, 229, 
 204, 155, 85, 77, 
 155, 103, 201, 89, 
 201, 204, 99, 206, 
 180, 227, 219, 87, 
 250, 155, 199, 207, 
 156, 199, 234, 60, 
 79, 72, 159, 217, 
 247, 248, 217, 72, 
 22, 61, 108, 18, 
 205, 128, 114, 201, 
 208, 47, 22, 99, 
 153, 209, 101, 178, 
 173, 101, 178, 61, 
 23, 203, 219, 210, 
 247, 216, 219, 204, 
 217, 56, 185, 217, 
 173, 156, 199, 2, 
 185, 209, 214, 187, 
 213, 99, 177, 217, 
 167, 119, 61, 167, 
 239, 172, 214, 63, 
 201, 233, 139, 211, 
 231, 248, 75, 231, 
 203, 219, 24, 187, 
 161, 140, 19, 68, 
 251, 187, 17, 24, 
 186, 243, 143, 19, 
 204, 248, 67, 193, 
 12, 3, 75, 124, 
 137, 145, 151, 24, 
 146, 151, 199, 72, 
 11, 39, 46, 12, 
 227, 162, 27, 87, 
 141, 2, 209, 186, 
 243, 219, 161, 28, 
 216, 79, 59, 78, 
 49, 201, 186, 49, 
 107, 132, 26, 8, 
 35, 216, 48, 212, 
 188, 8, 131, 173, 
 48, 120, 77, 99, 
 140, 145, 108, 12, 
 149, 28, 36, 61, 
 50, 244, 215, 8, 
 163, 209, 150, 189, 
 49, 113, 213, 210, 
 227, 26, 179, 213, 
 195, 161, 213, 81, 
 201, 53, 168, 209, 
 65, 113, 23, 71, 
 76, 78, 199, 139, 
 49, 69, 228, 133, 
 19, 249, 134, 71, 
 100, 149, 45, 198, 
 20, 247, 68, 174, 
 50, 242, 185, 103, 
 100, 149, 103, 223, 
 177, 103, 235, 29, 
 28, 121, 208, 231, 
 68, 201, 167, 41, 
 46, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len24_anagram0 = {
  LengthAndAnagram(24, 0), // seq_bit_len_and_anagram
  179, // num_chords
  kmap0_Word_len24_anagram0_chords, // chords
  kmap0_Word_len24_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len24_anagram1_chords[42] = {
 ChordData({0, 5, 65}), ChordData({0, 64, 16}), ChordData({0, 72, 80}), ChordData({0, 100, 3}), 
 ChordData({2, 1, 130}), ChordData({2, 4, 81}), ChordData({2, 4, 89}), ChordData({2, 4, 146}), 
 ChordData({4, 4, 146}), ChordData({16, 12, 81}), ChordData({16, 68, 82}), ChordData({18, 12, 24}), 
 ChordData({18, 64, 8}), ChordData({18, 64, 9}), ChordData({18, 64, 19}), ChordData({18, 68, 129}), 
 ChordData({18, 68, 136}), ChordData({20, 4, 25}), ChordData({20, 4, 146}), ChordData({22, 0, 81}), 
 ChordData({32, 69, 16}), ChordData({34, 65, 128}), ChordData({48, 1, 137}), ChordData({48, 4, 66}), 
 ChordData({48, 5, 0}), ChordData({48, 8, 192}), ChordData({48, 12, 144}), ChordData({50, 76, 2}), 
 ChordData({52, 5, 0}), ChordData({128, 4, 11}), ChordData({128, 76, 10}), ChordData({128, 96, 18}), 
 ChordData({128, 96, 19}), ChordData({130, 4, 9}), ChordData({130, 4, 11}), ChordData({130, 4, 74}), 
 ChordData({144, 0, 208}), ChordData({148, 0, 17}), ChordData({148, 8, 8}), ChordData({160, 1, 146}), 
 ChordData({176, 0, 24}), ChordData({176, 0, 82}), 
};

const uint8_t kmap0_Word_len24_anagram1_seqs[126] = {
 188, 127, 28, 64, 
 142, 48, 32, 177, 
 48, 151, 95, 132, 
 72, 125, 28, 63, 
 219, 188, 188, 243, 
 173, 243, 216, 79, 
 95, 43, 21, 233, 
 121, 61, 252, 56, 
 150, 233, 167, 213, 
 210, 218, 150, 173, 
 210, 186, 56, 150, 
 189, 178, 233, 215, 
 210, 218, 79, 245, 
 199, 186, 245, 7, 
 77, 188, 211, 213, 
 199, 124, 150, 119, 
 110, 146, 183, 117, 
 201, 143, 152, 217, 
 247, 231, 219, 162, 
 153, 77, 99, 209, 
 79, 151, 111, 209, 
 224, 254, 211, 248, 
 170, 177, 151, 72, 
 175, 176, 144, 19, 
 151, 152, 133, 250, 
 219, 161, 143, 219, 
 161, 248, 220, 26, 
 64, 32, 216, 53, 
 118, 61, 81, 54, 
 212, 55, 197, 20, 
 234, 60, 161, 24, 
 121, 216, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len24_anagram1 = {
  LengthAndAnagram(24, 1), // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_Word_len24_anagram1_chords, // chords
  kmap0_Word_len24_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len24_anagram2_chords[12] = {
 ChordData({2, 0, 19}), ChordData({2, 96, 3}), ChordData({16, 4, 136}), ChordData({16, 4, 152}), 
 ChordData({18, 64, 19}), ChordData({20, 4, 130}), ChordData({22, 0, 81}), ChordData({34, 33, 1}), 
 ChordData({48, 1, 17}), ChordData({128, 4, 146}), ChordData({144, 64, 2}), ChordData({160, 33, 1}), 
};

const uint8_t kmap0_Word_len24_anagram2_seqs[36] = {
 56, 189, 141, 151, 
 94, 132, 224, 137, 
 172, 64, 224, 213, 
 178, 199, 184, 245, 
 233, 209, 117, 218, 
 188, 11, 251, 134, 
 227, 123, 188, 24, 
 68, 63, 210, 24, 
 210, 145, 111, 184, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len24_anagram2 = {
  LengthAndAnagram(24, 2), // seq_bit_len_and_anagram
  12, // num_chords
  kmap0_Word_len24_anagram2_chords, // chords
  kmap0_Word_len24_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len24_anagram3_chords[6] = {
 ChordData({0, 12, 18}), ChordData({22, 8, 16}), ChordData({32, 69, 16}), ChordData({48, 1, 16}), 
 ChordData({48, 8, 80}), ChordData({48, 9, 16}), 
};

const uint8_t kmap0_Word_len24_anagram3_seqs[18] = {
 32, 253, 20, 78, 
 181, 199, 119, 254, 
 145, 224, 30, 223, 
 99, 206, 201, 78, 
 158, 219, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len24_anagram3 = {
  LengthAndAnagram(24, 3), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Word_len24_anagram3_chords, // chords
  kmap0_Word_len24_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len24_anagram4_chords[4] = {
 ChordData({16, 68, 18}), ChordData({16, 68, 146}), ChordData({128, 64, 18}), ChordData({160, 33, 1}), 
};

const uint8_t kmap0_Word_len24_anagram4_seqs[12] = {
 63, 248, 210, 56, 
 47, 201, 56, 113, 
 145, 27, 249, 134, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len24_anagram4 = {
  LengthAndAnagram(24, 4), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Word_len24_anagram4_chords, // chords
  kmap0_Word_len24_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len24_anagram5_chords[1] = {
 ChordData({48, 8, 80}), 
};

const uint8_t kmap0_Word_len24_anagram5_seqs[3] = {
 236, 17, 61, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len24_anagram5 = {
  LengthAndAnagram(24, 5), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len24_anagram5_chords, // chords
  kmap0_Word_len24_anagram5_seqs, // sequences
};

const ChordData kmap0_Word_len24_anagram6_chords[1] = {
 ChordData({0, 68, 18}), 
};

const uint8_t kmap0_Word_len24_anagram6_seqs[3] = {
 127, 249, 145, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len24_anagram6 = {
  LengthAndAnagram(24, 6), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len24_anagram6_chords, // chords
  kmap0_Word_len24_anagram6_seqs, // sequences
};

const ChordData kmap0_Word_len25_anagram0_chords[161] = {
 ChordData({0, 36, 80}), ChordData({0, 36, 139}), ChordData({2, 12, 136}), ChordData({2, 32, 201}), 
 ChordData({2, 65, 67}), ChordData({2, 68, 144}), ChordData({2, 68, 193}), ChordData({2, 68, 200}), 
 ChordData({2, 73, 16}), ChordData({2, 96, 2}), ChordData({4, 36, 18}), ChordData({4, 72, 0}), 
 ChordData({4, 96, 0}), ChordData({6, 0, 10}), ChordData({6, 0, 83}), ChordData({6, 0, 89}), 
 ChordData({16, 4, 146}), ChordData({16, 4, 208}), ChordData({16, 5, 26}), ChordData({16, 9, 152}), 
 ChordData({16, 32, 81}), ChordData({16, 36, 72}), ChordData({16, 36, 129}), ChordData({16, 64, 146}), 
 ChordData({16, 65, 3}), ChordData({16, 68, 144}), ChordData({16, 69, 1}), ChordData({16, 77, 3}), 
 ChordData({16, 100, 17}), ChordData({16, 100, 136}), ChordData({16, 100, 144}), ChordData({18, 0, 27}), 
 ChordData({18, 1, 9}), ChordData({18, 1, 145}), ChordData({18, 12, 8}), ChordData({18, 65, 8}), 
 ChordData({18, 72, 24}), ChordData({18, 76, 8}), ChordData({18, 76, 128}), ChordData({18, 96, 192}), 
 ChordData({20, 1, 16}), ChordData({20, 12, 0}), ChordData({20, 12, 192}), ChordData({20, 64, 8}), 
 ChordData({20, 68, 16}), ChordData({20, 68, 17}), ChordData({20, 68, 80}), ChordData({22, 0, 136}), 
 ChordData({22, 8, 17}), ChordData({22, 8, 192}), ChordData({22, 64, 80}), ChordData({32, 0, 83}), 
 ChordData({32, 1, 26}), ChordData({32, 1, 65}), ChordData({32, 1, 146}), ChordData({32, 4, 65}), 
 ChordData({32, 4, 89}), ChordData({32, 4, 131}), ChordData({32, 4, 136}), ChordData({32, 4, 194}), 
 ChordData({32, 40, 82}), ChordData({32, 41, 10}), ChordData({32, 73, 24}), ChordData({34, 0, 82}), 
 ChordData({34, 0, 138}), ChordData({34, 1, 26}), ChordData({34, 4, 144}), ChordData({34, 33, 1}), 
 ChordData({34, 65, 74}), ChordData({36, 0, 26}), ChordData({36, 8, 26}), ChordData({36, 8, 128}), 
 ChordData({36, 13, 130}), ChordData({36, 13, 136}), ChordData({36, 40, 1}), ChordData({38, 9, 18}), 
 ChordData({38, 9, 136}), ChordData({48, 0, 81}), ChordData({48, 0, 152}), ChordData({48, 5, 138}), 
 ChordData({48, 8, 194}), ChordData({48, 12, 64}), ChordData({48, 12, 145}), ChordData({48, 44, 8}), 
 ChordData({48, 64, 128}), ChordData({48, 64, 193}), ChordData({48, 65, 24}), ChordData({48, 65, 136}), 
 ChordData({48, 68, 128}), ChordData({50, 1, 200}), ChordData({50, 8, 9}), ChordData({50, 8, 19}), 
 ChordData({50, 8, 208}), ChordData({50, 9, 16}), ChordData({50, 12, 3}), ChordData({50, 12, 9}), 
 ChordData({50, 12, 16}), ChordData({50, 64, 10}), ChordData({50, 64, 129}), ChordData({52, 4, 24}), 
 ChordData({52, 4, 73}), ChordData({52, 4, 144}), ChordData({52, 4, 193}), ChordData({52, 12, 2}), 
 ChordData({52, 65, 0}), ChordData({54, 64, 64}), ChordData({128, 4, 24}), ChordData({128, 12, 144}), 
 ChordData({128, 12, 145}), ChordData({128, 12, 152}), ChordData({128, 12, 193}), ChordData({128, 12, 200}), 
 ChordData({128, 32, 16}), ChordData({128, 32, 194}), ChordData({128, 36, 26}), ChordData({128, 64, 19}), 
 ChordData({128, 68, 18}), ChordData({128, 68, 144}), ChordData({128, 68, 208}), ChordData({130, 8, 9}), 
 ChordData({130, 8, 16}), ChordData({130, 12, 3}), ChordData({130, 68, 18}), ChordData({132, 4, 1}), 
 ChordData({132, 4, 81}), ChordData({132, 4, 145}), ChordData({132, 12, 16}), ChordData({134, 0, 9}), 
 ChordData({134, 0, 72}), ChordData({134, 0, 88}), ChordData({144, 0, 154}), ChordData({144, 1, 81}), 
 ChordData({144, 8, 9}), ChordData({144, 40, 18}), ChordData({144, 72, 24}), ChordData({144, 76, 8}), 
 ChordData({148, 0, 16}), ChordData({148, 72, 8}), ChordData({150, 64, 16}), ChordData({160, 0, 82}), 
 ChordData({160, 1, 26}), ChordData({160, 64, 10}), ChordData({160, 64, 130}), ChordData({160, 65, 26}), 
 ChordData({160, 69, 10}), ChordData({162, 0, 72}), ChordData({164, 9, 130}), ChordData({164, 64, 26}), 
 ChordData({176, 5, 24}), ChordData({176, 8, 19}), ChordData({176, 8, 146}), ChordData({176, 9, 8}), 
 ChordData({176, 64, 129}), ChordData({176, 72, 1}), ChordData({178, 1, 24}), ChordData({178, 8, 65}), 
 ChordData({180, 0, 17}), ChordData({180, 0, 81}), ChordData({180, 0, 129}), ChordData({180, 0, 130}), 
 ChordData({180, 8, 2}), 
};

const uint8_t kmap0_Word_len25_anagram0_seqs[504] = {
 240, 231, 153, 241, 
 85, 240, 190, 118, 
 122, 106, 86, 193, 
 203, 151, 62, 118, 
 94, 246, 147, 108, 
 222, 167, 102, 122, 
 149, 169, 36, 123, 
 46, 176, 17, 194, 
 175, 181, 0, 21, 
 36, 9, 42, 4, 
 178, 54, 106, 35, 
 227, 116, 93, 174, 
 211, 186, 227, 39, 
 42, 198, 228, 103, 
 31, 243, 138, 46, 
 121, 212, 180, 112, 
 204, 16, 48, 124, 
 53, 244, 211, 66, 
 1, 95, 76, 210, 
 135, 113, 233, 165, 
 244, 72, 31, 254, 
 221, 139, 191, 180, 
 112, 252, 18, 190, 
 74, 50, 244, 60, 
 73, 235, 246, 22, 
 71, 107, 175, 143, 
 166, 245, 128, 244, 
 173, 150, 62, 90, 
 61, 78, 173, 50, 
 89, 246, 107, 178, 
 236, 39, 134, 109, 
 146, 117, 124, 120, 
 62, 125, 89, 243, 
 167, 74, 150, 174, 
 86, 89, 127, 94, 
 90, 186, 254, 44, 
 215, 241, 75, 237, 
 90, 201, 213, 147, 
 122, 185, 83, 37, 
 115, 109, 233, 225, 
 157, 140, 123, 100, 
 213, 130, 55, 31, 
 199, 145, 137, 10, 
 222, 223, 204, 252, 
 155, 71, 31, 55, 
 63, 189, 106, 126, 
 194, 231, 252, 148, 
 50, 195, 2, 97, 
 214, 146, 156, 172, 
 37, 236, 193, 204, 
 212, 154, 175, 178, 
 246, 81, 8, 100, 
 234, 63, 250, 134, 
 203, 151, 214, 251, 
 204, 170, 133, 230, 
 84, 139, 74, 57, 
 157, 39, 61, 150, 
 78, 122, 45, 45, 
 204, 233, 60, 167, 
 177, 116, 82, 107, 
 137, 243, 230, 49, 
 16, 200, 234, 155, 
 94, 209, 41, 51, 
 146, 159, 57, 39, 
 239, 188, 104, 130, 
 126, 209, 90, 38, 
 59, 187, 76, 54, 
 239, 109, 149, 30, 
 242, 109, 149, 46, 
 147, 159, 184, 245, 
 38, 167, 214, 188, 
 22, 61, 219, 200, 
 77, 162, 103, 124, 
 119, 242, 227, 182, 
 104, 253, 109, 209, 
 63, 211, 162, 91, 
 101, 70, 151, 201, 
 189, 62, 95, 213, 
 243, 39, 91, 247, 
 252, 25, 19, 239, 
 159, 228, 211, 248, 
 201, 210, 103, 190, 
 79, 115, 75, 131, 
 255, 9, 77, 47, 
 16, 147, 98, 246, 
 73, 99, 210, 211, 
 83, 10, 94, 126, 
 74, 161, 48, 102, 
 98, 24, 97, 4, 
 189, 34, 140, 145, 
 129, 27, 243, 136, 
 49, 82, 6, 209, 
 143, 140, 225, 167, 
 20, 219, 161, 169, 
 103, 98, 126, 35, 
 53, 226, 143, 236, 
 168, 177, 191, 81, 
 159, 55, 166, 254, 
 78, 208, 124, 217, 
 152, 168, 219, 161, 
 53, 154, 67, 235, 
 52, 135, 90, 5, 
 162, 56, 98, 204, 
 155, 34, 89, 23, 
 225, 68, 114, 10, 
 233, 81, 249, 78, 
 161, 117, 162, 122, 
 100, 148, 181, 86, 
 79, 135, 196, 60, 
 28, 83, 68, 214, 
 251, 18, 89, 229, 
 37, 50, 201, 203, 
 132, 222, 151, 191, 
 67, 179, 54, 135, 
 158, 20, 88, 58, 
 39, 46, 26, 243, 
 122, 91, 52, 110, 
 140, 104, 194, 137, 
 219, 26, 201, 101, 
 114, 172, 165, 197, 
 88, 247, 173, 49, 
 230, 16, 219, 59, 
 62, 35, 150, 119, 
 226, 244, 25, 187, 
 100, 140, 92, 201, 
 167, 49, 146, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len25_anagram0 = {
  LengthAndAnagram(25, 0), // seq_bit_len_and_anagram
  161, // num_chords
  kmap0_Word_len25_anagram0_chords, // chords
  kmap0_Word_len25_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len25_anagram1_chords[37] = {
 ChordData({0, 68, 89}), ChordData({2, 96, 3}), ChordData({6, 0, 81}), ChordData({16, 0, 74}), 
 ChordData({16, 13, 128}), ChordData({18, 1, 11}), ChordData({18, 64, 17}), ChordData({18, 76, 8}), 
 ChordData({20, 4, 16}), ChordData({20, 36, 80}), ChordData({22, 8, 0}), ChordData({22, 8, 16}), 
 ChordData({32, 5, 26}), ChordData({34, 0, 9}), ChordData({48, 1, 80}), ChordData({48, 5, 128}), 
 ChordData({48, 8, 17}), ChordData({48, 8, 65}), ChordData({48, 12, 8}), ChordData({48, 12, 17}), 
 ChordData({50, 8, 9}), ChordData({50, 8, 73}), ChordData({50, 64, 129}), ChordData({50, 64, 136}), 
 ChordData({50, 72, 2}), ChordData({50, 72, 16}), ChordData({52, 4, 129}), ChordData({52, 68, 1}), 
 ChordData({54, 0, 82}), ChordData({128, 12, 1}), ChordData({130, 64, 81}), ChordData({144, 1, 81}), 
 ChordData({144, 8, 16}), ChordData({144, 40, 17}), ChordData({176, 8, 16}), ChordData({178, 1, 24}), 
 ChordData({180, 0, 64}), 
};

const uint8_t kmap0_Word_len25_anagram1_seqs[116] = {
 188, 243, 42, 47, 
 45, 23, 114, 237, 
 233, 53, 179, 21, 
 125, 56, 61, 185, 
 245, 48, 238, 88, 
 202, 222, 244, 45, 
 173, 95, 171, 127, 
 42, 156, 103, 119, 
 234, 178, 174, 211, 
 101, 13, 138, 215, 
 187, 117, 115, 239, 
 248, 200, 108, 242, 
 223, 217, 41, 239, 
 122, 0, 175, 69, 
 191, 104, 205, 78, 
 191, 121, 220, 42, 
 246, 186, 85, 52, 
 111, 153, 220, 222, 
 50, 185, 213, 210, 
 98, 163, 165, 167, 
 69, 239, 159, 228, 
 149, 62, 127, 205, 
 56, 125, 122, 35, 
 253, 134, 108, 222, 
 137, 35, 120, 61, 
 32, 69, 140, 83, 
 44, 244, 140, 83, 
 136, 30, 223, 29, 
 202, 53, 50, 27, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len25_anagram1 = {
  LengthAndAnagram(25, 1), // seq_bit_len_and_anagram
  37, // num_chords
  kmap0_Word_len25_anagram1_chords, // chords
  kmap0_Word_len25_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len25_anagram2_chords[7] = {
 ChordData({0, 36, 3}), ChordData({2, 4, 73}), ChordData({20, 4, 128}), ChordData({48, 5, 17}), 
 ChordData({52, 4, 129}), ChordData({128, 64, 18}), ChordData({148, 0, 64}), 
};

const uint8_t kmap0_Word_len25_anagram2_seqs[22] = {
 191, 251, 8, 1, 
 127, 235, 126, 173, 
 126, 218, 159, 219, 
 123, 254, 46, 249, 
 18, 51, 69, 212, 
 26, 108, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len25_anagram2 = {
  LengthAndAnagram(25, 2), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Word_len25_anagram2_chords, // chords
  kmap0_Word_len25_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len25_anagram3_chords[2] = {
 ChordData({48, 1, 17}), ChordData({160, 65, 0}), 
};

const uint8_t kmap0_Word_len25_anagram3_seqs[7] = {
 227, 35, 175, 129, 
 140, 124, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len25_anagram3 = {
  LengthAndAnagram(25, 3), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len25_anagram3_chords, // chords
  kmap0_Word_len25_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len25_anagram4_chords[2] = {
 ChordData({16, 4, 19}), ChordData({20, 0, 16}), 
};

const uint8_t kmap0_Word_len25_anagram4_seqs[7] = {
 63, 235, 41, 170, 
 107, 245, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len25_anagram4 = {
  LengthAndAnagram(25, 4), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len25_anagram4_chords, // chords
  kmap0_Word_len25_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len26_anagram0_chords[165] = {
 ChordData({0, 4, 210}), ChordData({0, 44, 129}), ChordData({2, 5, 9}), ChordData({2, 5, 80}), 
 ChordData({2, 12, 192}), ChordData({2, 32, 82}), ChordData({2, 32, 128}), ChordData({4, 12, 10}), 
 ChordData({4, 12, 192}), ChordData({6, 4, 72}), ChordData({6, 4, 80}), ChordData({6, 4, 130}), 
 ChordData({6, 4, 144}), ChordData({6, 9, 26}), ChordData({6, 12, 3}), ChordData({6, 12, 16}), 
 ChordData({6, 36, 80}), ChordData({16, 0, 147}), ChordData({16, 0, 155}), ChordData({16, 0, 194}), 
 ChordData({16, 1, 3}), ChordData({16, 8, 83}), ChordData({16, 8, 137}), ChordData({16, 13, 131}), 
 ChordData({16, 33, 26}), ChordData({16, 44, 16}), ChordData({16, 68, 90}), ChordData({16, 68, 131}), 
 ChordData({16, 72, 18}), ChordData({18, 0, 73}), ChordData({18, 0, 90}), ChordData({18, 0, 131}), 
 ChordData({18, 0, 202}), ChordData({18, 0, 209}), ChordData({18, 4, 144}), ChordData({18, 9, 81}), 
 ChordData({18, 13, 72}), ChordData({18, 33, 65}), ChordData({18, 65, 24}), ChordData({18, 72, 128}), 
 ChordData({18, 96, 8}), ChordData({20, 0, 19}), ChordData({20, 0, 155}), ChordData({20, 32, 65}), 
 ChordData({20, 36, 8}), ChordData({20, 68, 8}), ChordData({32, 4, 72}), ChordData({32, 4, 81}), 
 ChordData({32, 4, 144}), ChordData({32, 12, 11}), ChordData({32, 12, 17}), ChordData({32, 12, 74}), 
 ChordData({32, 12, 136}), ChordData({32, 32, 26}), ChordData({32, 36, 138}), ChordData({32, 68, 137}), 
 ChordData({32, 68, 145}), ChordData({32, 69, 10}), ChordData({32, 69, 130}), ChordData({32, 72, 18}), 
 ChordData({34, 1, 89}), ChordData({34, 5, 72}), ChordData({34, 5, 81}), ChordData({34, 5, 146}), 
 ChordData({34, 5, 200}), ChordData({34, 12, 17}), ChordData({34, 68, 80}), ChordData({36, 0, 195}), 
 ChordData({36, 4, 144}), ChordData({38, 4, 145}), ChordData({48, 1, 25}), ChordData({48, 1, 26}), 
 ChordData({48, 1, 137}), ChordData({48, 5, 8}), ChordData({48, 8, 129}), ChordData({48, 8, 152}), 
 ChordData({48, 12, 144}), ChordData({48, 13, 8}), ChordData({48, 13, 9}), ChordData({48, 13, 136}), 
 ChordData({48, 33, 137}), ChordData({48, 37, 10}), ChordData({48, 37, 17}), ChordData({48, 37, 18}), 
 ChordData({48, 44, 192}), ChordData({48, 64, 72}), ChordData({48, 69, 8}), ChordData({48, 69, 24}), 
 ChordData({48, 72, 16}), ChordData({50, 1, 72}), ChordData({50, 5, 8}), ChordData({50, 65, 65}), 
 ChordData({50, 65, 72}), ChordData({50, 76, 2}), ChordData({50, 76, 64}), ChordData({52, 0, 144}), 
 ChordData({52, 0, 193}), ChordData({52, 5, 128}), ChordData({52, 12, 144}), ChordData({52, 36, 17}), 
 ChordData({52, 36, 18}), ChordData({52, 65, 128}), ChordData({52, 68, 1}), ChordData({54, 1, 128}), 
 ChordData({54, 8, 17}), ChordData({54, 64, 128}), ChordData({54, 68, 8}), ChordData({128, 5, 19}), 
 ChordData({128, 5, 144}), ChordData({128, 8, 10}), ChordData({128, 9, 10}), ChordData({128, 9, 18}), 
 ChordData({128, 12, 24}), ChordData({128, 32, 152}), ChordData({128, 32, 208}), ChordData({128, 40, 65}), 
 ChordData({128, 76, 24}), ChordData({128, 96, 137}), ChordData({130, 1, 192}), ChordData({130, 8, 3}), 
 ChordData({130, 12, 16}), ChordData({130, 76, 8}), ChordData({132, 4, 129}), ChordData({132, 36, 24}), 
 ChordData({134, 8, 17}), ChordData({134, 32, 192}), ChordData({144, 1, 2}), ChordData({144, 9, 16}), 
 ChordData({144, 9, 19}), ChordData({144, 9, 67}), ChordData({144, 9, 81}), ChordData({144, 32, 19}), 
 ChordData({144, 65, 144}), ChordData({144, 96, 16}), ChordData({144, 104, 1}), ChordData({146, 9, 2}), 
 ChordData({160, 1, 89}), ChordData({160, 8, 67}), ChordData({160, 8, 138}), ChordData({160, 12, 9}), 
 ChordData({160, 32, 82}), ChordData({160, 36, 17}), ChordData({160, 68, 24}), ChordData({162, 1, 24}), 
 ChordData({162, 8, 72}), ChordData({162, 8, 136}), ChordData({162, 64, 65}), ChordData({164, 0, 10}), 
 ChordData({164, 0, 82}), ChordData({164, 0, 146}), ChordData({164, 4, 26}), ChordData({166, 4, 9}), 
 ChordData({176, 1, 9}), ChordData({176, 1, 136}), ChordData({176, 65, 136}), ChordData({176, 69, 64}), 
 ChordData({176, 72, 128}), ChordData({180, 0, 10}), ChordData({180, 1, 16}), ChordData({180, 1, 72}), 
 ChordData({180, 1, 192}), ChordData({180, 32, 17}), ChordData({180, 64, 64}), ChordData({180, 64, 136}), 
 ChordData({182, 8, 128}), 
};

const uint8_t kmap0_Word_len26_anagram0_seqs[537] = {
 252, 244, 83, 44, 
 124, 250, 212, 122, 
 188, 46, 255, 241, 
 211, 160, 153, 62, 
 1, 132, 211, 12, 
 90, 48, 81, 125, 
 76, 175, 149, 158, 
 211, 3, 174, 223, 
 10, 234, 79, 243, 
 215, 74, 141, 224, 
 235, 52, 213, 214, 
 82, 209, 169, 62, 
 110, 167, 250, 61, 
 245, 167, 25, 142, 
 5, 140, 235, 171, 
 245, 168, 175, 208, 
 204, 62, 14, 227, 
 114, 193, 235, 100, 
 114, 178, 238, 62, 
 150, 200, 199, 88, 
 17, 194, 79, 201, 
 243, 202, 23, 207, 
 229, 137, 188, 227, 
 100, 89, 180, 174, 
 149, 205, 173, 232, 
 177, 175, 176, 215, 
 212, 104, 101, 243, 
 122, 154, 236, 31, 
 106, 15, 239, 116, 
 201, 165, 214, 103, 
 31, 222, 102, 120, 
 76, 91, 101, 106, 
 41, 201, 176, 165, 
 180, 214, 241, 110, 
 81, 201, 186, 5, 
 224, 117, 133, 240, 
 107, 181, 126, 173, 
 86, 9, 56, 243, 
 43, 224, 223, 60, 
 128, 62, 207, 139, 
 143, 175, 187, 243, 
 57, 61, 190, 138, 
 207, 233, 53, 63, 
 225, 100, 69, 72, 
 159, 21, 97, 153, 
 252, 186, 101, 242, 
 207, 130, 203, 235, 
 253, 151, 35, 147, 
 204, 41, 21, 188, 
 211, 122, 63, 115, 
 223, 122, 207, 111, 
 243, 253, 67, 141, 
 220, 183, 62, 237, 
 180, 216, 63, 47, 
 59, 51, 99, 166, 
 186, 149, 242, 60, 
 237, 244, 249, 148, 
 231, 182, 174, 213, 
 115, 23, 7, 101, 
 235, 90, 239, 191, 
 45, 154, 68, 175, 
 152, 73, 61, 233, 
 71, 52, 165, 215, 
 191, 157, 254, 86, 
 111, 122, 189, 201, 
 100, 189, 23, 34, 
 124, 189, 125, 255, 
 66, 15, 194, 159, 
 219, 240, 73, 52, 
 115, 150, 210, 250, 
 183, 85, 190, 124, 
 189, 61, 41, 143, 
 244, 220, 214, 206, 
 124, 231, 86, 191, 
 236, 219, 188, 210, 
 220, 183, 190, 20, 
 27, 253, 82, 108, 
 118, 205, 83, 201, 
 156, 207, 37, 159, 
 254, 155, 156, 126, 
 78, 242, 57, 254, 
 133, 231, 248, 17, 
 86, 178, 188, 157, 
 171, 252, 245, 105, 
 106, 31, 219, 233, 
 244, 184, 76, 238, 
 42, 125, 246, 235, 
 241, 184, 49, 7, 
 197, 60, 97, 164, 
 20, 90, 210, 192, 
 18, 40, 98, 74, 
 96, 34, 189, 2, 
 129, 128, 10, 4, 
 130, 33, 167, 136, 
 133, 243, 42, 35, 
 201, 80, 193, 123, 
 4, 115, 19, 70, 
 74, 189, 32, 253, 
 116, 200, 72, 223, 
 74, 95, 55, 106, 
 76, 133, 175, 157, 
 106, 204, 214, 160, 
 102, 136, 113, 28, 
 246, 17, 147, 60, 
 19, 88, 242, 114, 
 96, 201, 203, 59, 
 81, 242, 66, 199, 
 20, 71, 144, 244, 
 128, 129, 33, 157, 
 188, 48, 36, 70, 
 148, 218, 188, 19, 
 122, 99, 230, 141, 
 132, 65, 57, 233, 
 167, 200, 186, 8, 
 99, 50, 127, 94, 
 24, 243, 19, 89, 
 101, 76, 223, 173, 
 98, 115, 135, 138, 
 29, 212, 202, 155, 
 101, 7, 70, 174, 
 161, 24, 83, 51, 
 83, 156, 103, 129, 
 63, 103, 104, 156, 
 251, 173, 27, 122, 
 103, 83, 100, 189, 
 45, 67, 111, 178, 
 12, 254, 219, 41, 
 100, 38, 159, 145, 
 21, 125, 250, 136, 
 49, 215, 208, 219, 
 119, 112, 53, 157, 
 177, 208, 83, 217, 
 89, 198, 73, 161, 
 210, 41, 206, 38, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len26_anagram0 = {
  LengthAndAnagram(26, 0), // seq_bit_len_and_anagram
  165, // num_chords
  kmap0_Word_len26_anagram0_chords, // chords
  kmap0_Word_len26_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len26_anagram1_chords[23] = {
 ChordData({0, 13, 10}), ChordData({0, 36, 80}), ChordData({2, 36, 10}), ChordData({2, 68, 3}), 
 ChordData({16, 4, 153}), ChordData({16, 64, 130}), ChordData({16, 65, 8}), ChordData({16, 76, 8}), 
 ChordData({18, 0, 74}), ChordData({18, 0, 202}), ChordData({32, 12, 17}), ChordData({34, 12, 136}), 
 ChordData({34, 64, 129}), ChordData({48, 69, 16}), ChordData({48, 69, 24}), ChordData({50, 8, 17}), 
 ChordData({52, 0, 80}), ChordData({128, 4, 26}), ChordData({128, 12, 18}), ChordData({128, 73, 10}), 
 ChordData({144, 0, 2}), ChordData({148, 9, 16}), ChordData({160, 5, 136}), 
};

const uint8_t kmap0_Word_len26_anagram1_seqs[75] = {
 37, 125, 44, 1, 
 254, 121, 8, 16, 
 182, 254, 75, 217, 
 184, 94, 143, 62, 
 249, 10, 109, 41, 
 125, 88, 165, 116, 
 122, 149, 140, 109, 
 69, 115, 147, 21, 
 253, 226, 239, 207, 
 83, 78, 218, 101, 
 114, 211, 142, 239, 
 31, 121, 255, 72, 
 171, 216, 179, 217, 
 53, 15, 103, 227, 
 107, 17, 10, 210, 
 15, 70, 73, 227, 
 162, 0, 129, 65, 
 28, 19, 101, 253, 
 250, 20, 55, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len26_anagram1 = {
  LengthAndAnagram(26, 1), // seq_bit_len_and_anagram
  23, // num_chords
  kmap0_Word_len26_anagram1_chords, // chords
  kmap0_Word_len26_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len26_anagram2_chords[14] = {
 ChordData({4, 12, 128}), ChordData({16, 0, 139}), ChordData({16, 0, 147}), ChordData({16, 32, 18}), 
 ChordData({16, 37, 17}), ChordData({18, 64, 27}), ChordData({48, 8, 80}), ChordData({50, 8, 8}), 
 ChordData({52, 0, 17}), ChordData({52, 0, 129}), ChordData({52, 8, 16}), ChordData({128, 0, 154}), 
 ChordData({128, 4, 26}), ChordData({144, 0, 81}), 
};

const uint8_t kmap0_Word_len26_anagram2_seqs[46] = {
 149, 190, 236, 251, 
 106, 173, 11, 182, 
 32, 15, 66, 207, 
 20, 199, 47, 244, 
 92, 90, 215, 35, 
 122, 56, 115, 167, 
 148, 213, 103, 222, 
 245, 156, 153, 200, 
 155, 156, 78, 15, 
 6, 133, 22, 56, 
 95, 132, 142, 121, 
 99, 12, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len26_anagram2 = {
  LengthAndAnagram(26, 2), // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_Word_len26_anagram2_chords, // chords
  kmap0_Word_len26_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len26_anagram3_chords[1] = {
 ChordData({36, 0, 18}), 
};

const uint8_t kmap0_Word_len26_anagram3_seqs[4] = {
 53, 215, 90, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len26_anagram3 = {
  LengthAndAnagram(26, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len26_anagram3_chords, // chords
  kmap0_Word_len26_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len26_anagram4_chords[1] = {
 ChordData({48, 8, 80}), 
};

const uint8_t kmap0_Word_len26_anagram4_seqs[4] = {
 156, 83, 242, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len26_anagram4 = {
  LengthAndAnagram(26, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len26_anagram4_chords, // chords
  kmap0_Word_len26_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len27_anagram0_chords[149] = {
 ChordData({0, 0, 73}), ChordData({0, 12, 19}), ChordData({0, 13, 3}), ChordData({0, 109, 2}), 
 ChordData({2, 33, 72}), ChordData({2, 33, 138}), ChordData({2, 40, 65}), ChordData({2, 69, 16}), 
 ChordData({4, 12, 18}), ChordData({4, 44, 16}), ChordData({6, 1, 25}), ChordData({16, 0, 208}), 
 ChordData({16, 4, 9}), ChordData({16, 5, 3}), ChordData({16, 5, 83}), ChordData({16, 13, 17}), 
 ChordData({16, 13, 144}), ChordData({16, 32, 26}), ChordData({16, 32, 209}), ChordData({16, 36, 145}), 
 ChordData({16, 64, 139}), ChordData({16, 73, 16}), ChordData({16, 100, 131}), ChordData({18, 0, 155}), 
 ChordData({18, 4, 11}), ChordData({18, 4, 27}), ChordData({18, 4, 131}), ChordData({18, 4, 145}), 
 ChordData({18, 4, 147}), ChordData({18, 13, 1}), ChordData({18, 32, 25}), ChordData({18, 41, 80}), 
 ChordData({18, 68, 64}), ChordData({20, 0, 27}), ChordData({20, 0, 83}), ChordData({20, 0, 89}), 
 ChordData({20, 0, 131}), ChordData({20, 0, 147}), ChordData({20, 4, 146}), ChordData({20, 64, 18}), 
 ChordData({22, 0, 19}), ChordData({22, 0, 66}), ChordData({22, 0, 82}), ChordData({22, 0, 146}), 
 ChordData({32, 0, 211}), ChordData({32, 12, 129}), ChordData({32, 32, 81}), ChordData({32, 68, 192}), 
 ChordData({34, 5, 17}), ChordData({34, 8, 3}), ChordData({34, 8, 192}), ChordData({34, 12, 192}), 
 ChordData({34, 13, 24}), ChordData({34, 33, 131}), ChordData({34, 33, 193}), ChordData({36, 1, 18}), 
 ChordData({36, 12, 66}), ChordData({36, 12, 129}), ChordData({36, 36, 26}), ChordData({36, 64, 18}), 
 ChordData({38, 1, 88}), ChordData({38, 32, 72}), ChordData({38, 64, 65}), ChordData({38, 72, 128}), 
 ChordData({48, 0, 147}), ChordData({48, 0, 194}), ChordData({48, 1, 0}), ChordData({48, 1, 17}), 
 ChordData({48, 5, 26}), ChordData({48, 5, 146}), ChordData({48, 8, 64}), ChordData({48, 12, 146}), 
 ChordData({48, 64, 146}), ChordData({48, 65, 144}), ChordData({48, 72, 131}), ChordData({48, 77, 0}), 
 ChordData({50, 0, 208}), ChordData({50, 8, 18}), ChordData({50, 33, 1}), ChordData({50, 33, 128}), 
 ChordData({50, 40, 128}), ChordData({50, 72, 0}), ChordData({50, 72, 18}), ChordData({52, 8, 24}), 
 ChordData({52, 64, 24}), ChordData({54, 64, 10}), ChordData({54, 96, 8}), ChordData({128, 13, 17}), 
 ChordData({128, 13, 144}), ChordData({128, 68, 26}), ChordData({130, 9, 24}), ChordData({130, 64, 202}), 
 ChordData({132, 8, 17}), ChordData({134, 0, 146}), ChordData({134, 1, 17}), ChordData({144, 0, 11}), 
 ChordData({144, 0, 19}), ChordData({144, 0, 26}), ChordData({144, 0, 27}), ChordData({144, 0, 75}), 
 ChordData({144, 0, 131}), ChordData({144, 0, 146}), ChordData({144, 0, 147}), ChordData({144, 0, 202}), 
 ChordData({144, 1, 17}), ChordData({144, 1, 65}), ChordData({144, 8, 18}), ChordData({144, 64, 26}), 
 ChordData({144, 64, 88}), ChordData({144, 72, 18}), ChordData({146, 0, 72}), ChordData({146, 0, 73}), 
 ChordData({146, 0, 74}), ChordData({146, 0, 75}), ChordData({146, 0, 88}), ChordData({146, 0, 131}), 
 ChordData({146, 1, 2}), ChordData({148, 0, 194}), ChordData({148, 4, 17}), ChordData({148, 8, 146}), 
 ChordData({148, 9, 3}), ChordData({148, 64, 146}), ChordData({148, 68, 10}), ChordData({150, 0, 24}), 
 ChordData({160, 4, 19}), ChordData({160, 37, 3}), ChordData({160, 69, 24}), ChordData({160, 72, 128}), 
 ChordData({160, 96, 192}), ChordData({162, 1, 72}), ChordData({162, 33, 3}), ChordData({162, 69, 128}), 
 ChordData({162, 72, 64}), ChordData({164, 0, 1}), ChordData({164, 0, 9}), ChordData({164, 8, 1}), 
 ChordData({164, 12, 3}), ChordData({164, 13, 0}), ChordData({164, 32, 18}), ChordData({164, 36, 16}), 
 ChordData({166, 1, 64}), ChordData({176, 1, 17}), ChordData({176, 1, 128}), ChordData({176, 1, 129}), 
 ChordData({176, 8, 26}), ChordData({176, 9, 24}), ChordData({176, 33, 8}), ChordData({180, 1, 136}), 
 ChordData({180, 64, 128}), 
};

const uint8_t kmap0_Word_len27_anagram0_seqs[503] = {
 128, 193, 2, 77, 
 63, 91, 204, 239, 
 62, 150, 46, 240, 
 177, 116, 180, 54, 
 195, 131, 90, 17, 
 2, 78, 189, 240, 
 143, 249, 150, 56, 
 95, 182, 168, 240, 
 39, 125, 157, 214, 
 61, 128, 128, 153, 
 253, 186, 86, 253, 
 63, 14, 227, 242, 
 31, 222, 34, 253, 
 148, 188, 64, 224, 
 75, 6, 208, 58, 
 5, 67, 211, 122, 
 200, 191, 208, 227, 
 171, 181, 74, 32, 
 61, 46, 93, 252, 
 180, 176, 85, 192, 
 184, 175, 216, 214, 
 69, 207, 126, 235, 
 62, 110, 147, 169, 
 215, 243, 244, 179, 
 141, 100, 80, 250, 
 109, 171, 123, 161, 
 135, 225, 180, 75, 
 178, 217, 207, 174, 
 30, 180, 238, 152, 
 171, 113, 235, 152, 
 173, 235, 43, 116, 
 93, 95, 85, 207, 
 142, 43, 61, 186, 
 142, 209, 210, 99, 
 116, 215, 229, 106, 
 108, 115, 29, 99, 
 179, 125, 85, 61, 
 205, 91, 80, 230, 
 148, 55, 63, 129, 
 133, 121, 152, 203, 
 228, 151, 119, 238, 
 253, 17, 27, 183, 
 83, 202, 76, 157, 
 196, 230, 252, 148, 
 126, 238, 214, 155, 
 122, 17, 50, 245, 
 13, 119, 242, 125, 
 22, 248, 169, 102, 
 78, 191, 244, 231, 
 57, 175, 8, 207, 
 44, 101, 193, 117, 
 90, 239, 154, 181, 
 25, 242, 230, 218, 
 178, 76, 238, 178, 
 100, 220, 60, 246, 
 21, 102, 54, 48, 
 48, 184, 143, 188, 
 121, 252, 183, 21, 
 11, 242, 253, 88, 
 164, 204, 206, 73, 
 124, 34, 23, 101, 
 178, 167, 16, 200, 
 242, 246, 94, 76, 
 162, 229, 167, 191, 
 77, 110, 206, 227, 
 49, 186, 69, 67, 
 247, 13, 23, 144, 
 251, 134, 160, 5, 
 139, 78, 150, 157, 
 211, 88, 108, 95, 
 52, 167, 211, 115, 
 230, 145, 86, 245, 
 229, 108, 159, 134, 
 173, 242, 136, 73, 
 191, 71, 76, 122, 
 210, 159, 137, 75, 
 235, 17, 147, 46, 
 77, 28, 90, 39, 
 82, 221, 26, 212, 
 88, 212, 137, 163, 
 23, 67, 213, 184, 
 24, 51, 198, 197, 
 80, 244, 40, 134, 
 162, 103, 49, 148, 
 173, 139, 65, 100, 
 220, 43, 79, 92, 
 97, 204, 250, 10, 
 67, 57, 200, 62, 
 142, 152, 141, 227, 
 96, 111, 114, 138, 
 41, 46, 161, 210, 
 99, 149, 49, 108, 
 140, 100, 89, 176, 
 153, 59, 116, 173, 
 220, 161, 24, 138, 
 205, 102, 227, 118, 
 40, 91, 57, 166, 
 125, 21, 219, 24, 
 199, 209, 104, 95, 
 213, 96, 71, 245, 
 252, 218, 169, 82, 
 20, 53, 176, 228, 
 149, 174, 20, 197, 
 197, 95, 67, 107, 
 135, 218, 83, 124, 
 228, 217, 59, 22, 
 225, 203, 249, 59, 
 52, 133, 204, 20, 
 12, 35, 147, 60, 
 50, 119, 232, 29, 
 11, 27, 101, 63, 
 197, 205, 33, 59, 
 167, 200, 91, 243, 
 158, 121, 55, 244, 
 140, 221, 72, 24, 
 233, 252, 45, 253, 
 25, 39, 140, 243, 
 44, 224, 207, 25, 
 115, 7, 115, 215, 
 35, 230, 246, 222, 
 17, 55, 121, 227, 
 190, 201, 24, 42, 
 186, 184, 67, 244, 
 168, 53, 242, 13, 
 79, 83, 232, 45, 
 35, 159, 100, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len27_anagram0 = {
  LengthAndAnagram(27, 0), // seq_bit_len_and_anagram
  149, // num_chords
  kmap0_Word_len27_anagram0_chords, // chords
  kmap0_Word_len27_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len27_anagram1_chords[26] = {
 ChordData({0, 0, 192}), ChordData({0, 13, 146}), ChordData({16, 4, 90}), ChordData({16, 4, 155}), 
 ChordData({16, 13, 16}), ChordData({16, 36, 10}), ChordData({16, 36, 17}), ChordData({16, 36, 129}), 
 ChordData({16, 68, 18}), ChordData({18, 64, 0}), ChordData({18, 64, 138}), ChordData({20, 0, 131}), 
 ChordData({22, 0, 146}), ChordData({32, 32, 18}), ChordData({34, 8, 65}), ChordData({36, 4, 145}), 
 ChordData({50, 1, 24}), ChordData({50, 72, 0}), ChordData({52, 64, 136}), ChordData({132, 0, 146}), 
 ChordData({144, 0, 11}), ChordData({144, 0, 75}), ChordData({144, 64, 26}), ChordData({160, 0, 27}), 
 ChordData({164, 0, 81}), ChordData({176, 8, 128}), 
};

const uint8_t kmap0_Word_len27_anagram1_seqs[88] = {
 128, 1, 3, 58, 
 232, 75, 5, 227, 
 171, 122, 208, 186, 
 243, 148, 126, 74, 
 30, 43, 124, 69, 
 47, 244, 175, 231, 
 23, 146, 215, 227, 
 203, 143, 4, 13, 
 36, 176, 52, 82, 
 171, 125, 85, 141, 
 235, 171, 218, 99, 
 132, 121, 16, 114, 
 78, 169, 247, 156, 
 188, 79, 71, 235, 
 237, 145, 45, 182, 
 244, 153, 85, 146, 
 235, 196, 85, 129, 
 161, 107, 93, 12, 
 93, 243, 90, 49, 
 164, 7, 35, 235, 
 22, 19, 103, 230, 
 21, 131, 114, 50, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len27_anagram1 = {
  LengthAndAnagram(27, 1), // seq_bit_len_and_anagram
  26, // num_chords
  kmap0_Word_len27_anagram1_chords, // chords
  kmap0_Word_len27_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len27_anagram2_chords[9] = {
 ChordData({0, 4, 26}), ChordData({2, 4, 147}), ChordData({16, 13, 16}), ChordData({16, 68, 146}), 
 ChordData({16, 96, 19}), ChordData({48, 13, 64}), ChordData({52, 4, 16}), ChordData({164, 68, 16}), 
 ChordData({176, 9, 16}), 
};

const uint8_t kmap0_Word_len27_anagram2_seqs[31] = {
 64, 95, 177, 0, 
 189, 79, 197, 56, 
 253, 148, 164, 145, 
 126, 124, 25, 47, 
 66, 126, 241, 111, 
 159, 121, 252, 249, 
 207, 137, 151, 247, 
 68, 136, 6, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len27_anagram2 = {
  LengthAndAnagram(27, 2), // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_Word_len27_anagram2_chords, // chords
  kmap0_Word_len27_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len27_anagram3_chords[3] = {
 ChordData({48, 5, 16}), ChordData({48, 5, 136}), ChordData({52, 0, 80}), 
};

const uint8_t kmap0_Word_len27_anagram3_seqs[11] = {
 247, 207, 223, 62, 
 232, 245, 54, 231, 
 234, 57, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len27_anagram3 = {
  LengthAndAnagram(27, 3), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Word_len27_anagram3_chords, // chords
  kmap0_Word_len27_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len27_anagram7_chords[1] = {
 ChordData({48, 8, 80}), 
};

const uint8_t kmap0_Word_len27_anagram7_seqs[4] = {
 99, 209, 195, 6, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len27_anagram7 = {
  LengthAndAnagram(27, 7), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len27_anagram7_chords, // chords
  kmap0_Word_len27_anagram7_seqs, // sequences
};

const ChordData kmap0_Word_len28_anagram0_chords[155] = {
 ChordData({0, 45, 73}), ChordData({0, 64, 72}), ChordData({0, 68, 154}), ChordData({0, 72, 80}), 
 ChordData({0, 72, 146}), ChordData({0, 72, 210}), ChordData({2, 4, 73}), ChordData({2, 4, 89}), 
 ChordData({2, 4, 137}), ChordData({2, 4, 201}), ChordData({2, 5, 17}), ChordData({2, 96, 67}), 
 ChordData({4, 0, 3}), ChordData({6, 0, 2}), ChordData({6, 0, 64}), ChordData({6, 4, 0}), 
 ChordData({6, 13, 8}), ChordData({6, 32, 82}), ChordData({16, 1, 147}), ChordData({16, 32, 83}), 
 ChordData({16, 36, 138}), ChordData({16, 36, 153}), ChordData({16, 36, 193}), ChordData({16, 64, 27}), 
 ChordData({16, 64, 74}), ChordData({16, 65, 72}), ChordData({16, 68, 66}), ChordData({18, 12, 9}), 
 ChordData({18, 12, 88}), ChordData({18, 12, 131}), ChordData({18, 12, 146}), ChordData({18, 12, 152}), 
 ChordData({18, 64, 73}), ChordData({18, 64, 74}), ChordData({18, 68, 17}), ChordData({18, 68, 73}), 
 ChordData({20, 4, 25}), ChordData({20, 4, 138}), ChordData({20, 4, 152}), ChordData({20, 8, 131}), 
 ChordData({20, 9, 16}), ChordData({22, 0, 81}), ChordData({22, 4, 9}), ChordData({22, 4, 194}), 
 ChordData({22, 64, 65}), ChordData({32, 0, 144}), ChordData({32, 0, 146}), ChordData({32, 4, 64}), 
 ChordData({32, 5, 154}), ChordData({32, 9, 26}), ChordData({32, 9, 83}), ChordData({32, 37, 1}), 
 ChordData({32, 37, 3}), ChordData({32, 96, 3}), ChordData({34, 0, 16}), ChordData({34, 9, 24}), 
 ChordData({34, 65, 24}), ChordData({34, 96, 8}), ChordData({36, 76, 128}), ChordData({38, 0, 130}), 
 ChordData({38, 4, 17}), ChordData({38, 4, 26}), ChordData({38, 5, 18}), ChordData({38, 8, 65}), 
 ChordData({48, 0, 27}), ChordData({48, 0, 66}), ChordData({48, 0, 211}), ChordData({48, 1, 80}), 
 ChordData({48, 4, 65}), ChordData({48, 4, 153}), ChordData({48, 4, 154}), ChordData({48, 5, 137}), 
 ChordData({48, 5, 152}), ChordData({48, 8, 82}), ChordData({48, 8, 147}), ChordData({48, 12, 25}), 
 ChordData({48, 12, 80}), ChordData({48, 12, 138}), ChordData({48, 12, 208}), ChordData({48, 64, 66}), 
 ChordData({48, 68, 3}), ChordData({48, 72, 80}), ChordData({50, 0, 19}), ChordData({50, 0, 74}), 
 ChordData({50, 0, 152}), ChordData({50, 1, 11}), ChordData({50, 1, 16}), ChordData({50, 1, 25}), 
 ChordData({50, 1, 26}), ChordData({50, 4, 65}), ChordData({50, 8, 82}), ChordData({50, 9, 72}), 
 ChordData({50, 65, 16}), ChordData({52, 4, 74}), ChordData({52, 13, 65}), ChordData({52, 13, 128}), 
 ChordData({52, 37, 128}), ChordData({52, 64, 19}), ChordData({52, 76, 16}), ChordData({54, 65, 16}), 
 ChordData({128, 0, 155}), ChordData({128, 4, 11}), ChordData({128, 32, 146}), ChordData({128, 72, 18}), 
 ChordData({128, 73, 26}), ChordData({128, 96, 130}), ChordData({128, 96, 139}), ChordData({130, 0, 75}), 
 ChordData({130, 0, 202}), ChordData({130, 1, 27}), ChordData({130, 4, 11}), ChordData({130, 4, 73}), 
 ChordData({132, 32, 27}), ChordData({134, 32, 82}), ChordData({134, 64, 130}), ChordData({144, 0, 216}), 
 ChordData({144, 8, 89}), ChordData({144, 12, 26}), ChordData({144, 36, 25}), ChordData({144, 40, 17}), 
 ChordData({144, 64, 146}), ChordData({144, 65, 130}), ChordData({144, 65, 146}), ChordData({144, 68, 66}), 
 ChordData({146, 0, 138}), ChordData({146, 8, 9}), ChordData({146, 64, 208}), ChordData({148, 0, 11}), 
 ChordData({148, 0, 81}), ChordData({148, 0, 82}), ChordData({148, 8, 3}), ChordData({148, 8, 17}), 
 ChordData({150, 0, 25}), ChordData({150, 0, 72}), ChordData({150, 0, 200}), ChordData({150, 0, 208}), 
 ChordData({150, 64, 64}), ChordData({160, 1, 17}), ChordData({160, 13, 64}), ChordData({160, 13, 144}), 
 ChordData({160, 33, 65}), ChordData({160, 65, 24}), ChordData({162, 1, 10}), ChordData({164, 4, 80}), 
 ChordData({164, 5, 128}), ChordData({166, 0, 24}), ChordData({166, 64, 2}), ChordData({176, 0, 202}), 
 ChordData({176, 1, 130}), ChordData({178, 0, 25}), ChordData({178, 0, 80}), ChordData({178, 0, 137}), 
 ChordData({180, 9, 24}), ChordData({180, 64, 26}), ChordData({180, 64, 82}), 
};

const uint8_t kmap0_Word_len28_anagram0_seqs[543] = {
 11, 95, 75, 12, 
 36, 80, 192, 64, 
 22, 244, 10, 210, 
 176, 48, 32, 93, 
 9, 147, 10, 46, 
 67, 173, 188, 175, 
 187, 243, 202, 189, 
 173, 189, 253, 212, 
 202, 251, 68, 251, 
 211, 199, 193, 151, 
 94, 132, 96, 1, 
 130, 10, 42, 64, 
 208, 160, 2, 6, 
 13, 30, 84, 208, 
 250, 181, 212, 90, 
 97, 193, 141, 227, 
 131, 140, 203, 59, 
 94, 132, 8, 95, 
 213, 244, 99, 21, 
 188, 188, 126, 90, 
 184, 23, 235, 22, 
 210, 140, 86, 41, 
 125, 88, 217, 252, 
 136, 47, 253, 218, 
 233, 215, 236, 212, 
 250, 131, 212, 233, 
 215, 169, 231, 145, 
 156, 90, 61, 79, 
 210, 186, 205, 219, 
 42, 27, 205, 243, 
 178, 127, 221, 202, 
 235, 151, 245, 119, 
 61, 234, 171, 74, 
 175, 149, 94, 213, 
 227, 43, 167, 186, 
 199, 216, 101, 93, 
 61, 220, 188, 245, 
 183, 173, 203, 213, 
 216, 79, 210, 92, 
 123, 13, 50, 24, 
 64, 64, 32, 83, 
 1, 50, 96, 240, 
 183, 254, 80, 113, 
 100, 45, 21, 188, 
 147, 177, 180, 159, 
 111, 184, 248, 249, 
 134, 11, 100, 94, 
 132, 32, 131, 1, 
 45, 246, 220, 173, 
 50, 79, 235, 13, 
 96, 171, 204, 244, 
 233, 148, 95, 243, 
 73, 141, 243, 231, 
 217, 123, 182, 254, 
 20, 199, 159, 211, 
 200, 249, 76, 189, 
 152, 103, 172, 203, 
 25, 209, 204, 72, 
 153, 215, 51, 190, 
 199, 204, 188, 191, 
 121, 173, 206, 59, 
 79, 154, 145, 252, 
 99, 242, 253, 186, 
 183, 213, 243, 196, 
 121, 68, 23, 162, 
 103, 125, 37, 122, 
 61, 175, 201, 207, 
 121, 44, 62, 89, 
 209, 108, 209, 243, 
 196, 25, 209, 150, 
 150, 25, 127, 45, 
 205, 30, 209, 99, 
 156, 220, 139, 185, 
 185, 213, 173, 2, 
 121, 124, 91, 189, 
 141, 71, 223, 121, 
 220, 186, 190, 61, 
 183, 213, 211, 200, 
 189, 249, 215, 236, 
 17, 27, 93, 210, 
 22, 205, 199, 180, 
 188, 253, 39, 91, 
 209, 231, 115, 201, 
 123, 127, 58, 201, 
 167, 225, 211, 33, 
 93, 243, 22, 47, 
 69, 207, 121, 78, 
 203, 219, 24, 186, 
 19, 132, 161, 251, 
 184, 0, 6, 81, 
 145, 98, 38, 46, 
 151, 208, 82, 1, 
 131, 40, 46, 151, 
 80, 193, 139, 161, 
 220, 188, 220, 212, 
 24, 170, 177, 125, 
 20, 24, 186, 223, 
 202, 251, 219, 161, 
 181, 88, 24, 90, 
 97, 193, 29, 181, 
 137, 226, 2, 4, 
 66, 205, 41, 148, 
 215, 51, 145, 94, 
 209, 175, 177, 208, 
 179, 208, 49, 78, 
 133, 137, 226, 114, 
 152, 40, 46, 7, 
 197, 197, 131, 207, 
 24, 210, 64, 27, 
 131, 156, 172, 219, 
 161, 28, 36, 219, 
 131, 161, 232, 186, 
 117, 98, 205, 91, 
 39, 208, 204, 24, 
 169, 122, 93, 54, 
 214, 19, 53, 90, 
 215, 83, 173, 220, 
 161, 174, 220, 20, 
 202, 53, 154, 60, 
 174, 205, 33, 125, 
 196, 220, 177, 199, 
 167, 200, 124, 208, 
 139, 49, 28, 249, 
 134, 123, 79, 100, 
 149, 24, 122, 244, 
 253, 39, 199, 156, 
 55, 197, 249, 52, 
 125, 158, 161, 152, 
 207, 104, 137, 145, 
 149, 77, 24, 68, 
 190, 61, 145, 183, 
 213, 236, 233, 200, 
 28, 121, 169, 213, 
 231, 68, 201, 122, 
 186, 8, 149, 231, 
 196, 133, 13, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  155, // num_chords
  kmap0_Word_len28_anagram0_chords, // chords
  kmap0_Word_len28_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len28_anagram1_chords[32] = {
 ChordData({0, 68, 8}), ChordData({2, 4, 194}), ChordData({2, 5, 16}), ChordData({2, 64, 66}), 
 ChordData({6, 0, 64}), ChordData({16, 4, 195}), ChordData({16, 68, 66}), ChordData({18, 4, 136}), 
 ChordData({18, 4, 208}), ChordData({18, 8, 192}), ChordData({18, 12, 18}), ChordData({18, 32, 25}), 
 ChordData({18, 65, 8}), ChordData({18, 68, 3}), ChordData({22, 4, 16}), ChordData({48, 9, 16}), 
 ChordData({48, 12, 129}), ChordData({48, 64, 130}), ChordData({50, 0, 65}), ChordData({52, 8, 128}), 
 ChordData({128, 4, 19}), ChordData({128, 68, 19}), ChordData({130, 4, 17}), ChordData({144, 1, 26}), 
 ChordData({146, 8, 9}), ChordData({148, 0, 19}), ChordData({148, 0, 64}), ChordData({148, 0, 147}), 
 ChordData({148, 64, 18}), ChordData({150, 0, 25}), ChordData({164, 0, 18}), ChordData({176, 8, 18}), 
};

const uint8_t kmap0_Word_len28_anagram1_seqs[112] = {
 64, 2, 5, 143, 
 244, 204, 141, 127, 
 28, 223, 3, 248, 
 210, 204, 160, 1, 
 131, 10, 214, 87, 
 207, 248, 140, 47, 
 13, 76, 223, 250, 
 160, 121, 222, 148, 
 154, 185, 201, 232, 
 249, 212, 216, 10, 
 61, 189, 125, 168, 
 244, 33, 27, 247, 
 215, 117, 190, 167, 
 13, 238, 177, 75, 
 78, 153, 126, 45, 
 77, 249, 202, 188, 
 189, 121, 157, 114, 
 58, 201, 59, 143, 
 27, 179, 113, 249, 
 145, 59, 223, 27, 
 99, 61, 98, 208, 
 78, 177, 29, 90, 
 39, 214, 184, 53, 
 152, 205, 236, 171, 
 26, 179, 117, 2, 
 109, 89, 39, 214, 
 173, 129, 152, 107, 
 49, 198, 16, 61, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len28_anagram1 = {
  LengthAndAnagram(28, 1), // seq_bit_len_and_anagram
  32, // num_chords
  kmap0_Word_len28_anagram1_chords, // chords
  kmap0_Word_len28_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len28_anagram2_chords[12] = {
 ChordData({16, 4, 153}), ChordData({20, 0, 19}), ChordData({20, 4, 16}), ChordData({20, 4, 25}), 
 ChordData({22, 8, 16}), ChordData({48, 1, 24}), ChordData({48, 1, 80}), ChordData({48, 5, 152}), 
 ChordData({52, 0, 16}), ChordData({52, 4, 19}), ChordData({148, 64, 18}), ChordData({176, 0, 17}), 
};

const uint8_t kmap0_Word_len28_anagram2_seqs[42] = {
 64, 224, 213, 91, 
 61, 232, 186, 117, 
 92, 127, 92, 127, 
 86, 61, 117, 156, 
 218, 115, 79, 214, 
 219, 156, 143, 195, 
 99, 165, 159, 219, 
 147, 207, 211, 115, 
 250, 243, 22, 53, 
 46, 210, 179, 49, 
 155, 199, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len28_anagram2 = {
  LengthAndAnagram(28, 2), // seq_bit_len_and_anagram
  12, // num_chords
  kmap0_Word_len28_anagram2_chords, // chords
  kmap0_Word_len28_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len28_anagram3_chords[6] = {
 ChordData({0, 4, 19}), ChordData({16, 68, 146}), ChordData({48, 0, 147}), ChordData({48, 8, 24}), 
 ChordData({48, 13, 64}), ChordData({128, 4, 27}), 
};

const uint8_t kmap0_Word_len28_anagram3_seqs[21] = {
 191, 59, 143, 75, 
 127, 41, 60, 72, 
 121, 215, 51, 22, 
 173, 217, 64, 244, 
 253, 140, 63, 27, 
 161, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len28_anagram3 = {
  LengthAndAnagram(28, 3), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Word_len28_anagram3_chords, // chords
  kmap0_Word_len28_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len28_anagram4_chords[1] = {
 ChordData({16, 36, 17}), 
};

const uint8_t kmap0_Word_len28_anagram4_seqs[4] = {
 208, 191, 208, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len28_anagram4 = {
  LengthAndAnagram(28, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len28_anagram4_chords, // chords
  kmap0_Word_len28_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len29_anagram0_chords[142] = {
 ChordData({0, 0, 26}), ChordData({0, 36, 83}), ChordData({0, 40, 19}), ChordData({0, 68, 210}), 
 ChordData({0, 72, 64}), ChordData({2, 12, 25}), ChordData({2, 12, 145}), ChordData({2, 12, 147}), 
 ChordData({2, 12, 208}), ChordData({2, 13, 146}), ChordData({2, 36, 17}), ChordData({2, 36, 66}), 
 ChordData({2, 68, 18}), ChordData({4, 32, 8}), ChordData({4, 40, 0}), ChordData({6, 4, 11}), 
 ChordData({6, 4, 131}), ChordData({6, 4, 145}), ChordData({6, 4, 193}), ChordData({6, 4, 195}), 
 ChordData({16, 0, 75}), ChordData({16, 12, 208}), ChordData({16, 37, 17}), ChordData({16, 44, 81}), 
 ChordData({16, 44, 145}), ChordData({16, 64, 211}), ChordData({16, 68, 80}), ChordData({16, 68, 83}), 
 ChordData({16, 69, 144}), ChordData({18, 5, 10}), ChordData({18, 12, 144}), ChordData({18, 44, 10}), 
 ChordData({18, 68, 136}), ChordData({18, 73, 26}), ChordData({18, 76, 130}), ChordData({20, 1, 19}), 
 ChordData({20, 12, 1}), ChordData({20, 68, 9}), ChordData({20, 68, 138}), ChordData({22, 64, 19}), 
 ChordData({32, 4, 153}), ChordData({32, 4, 193}), ChordData({32, 12, 2}), ChordData({34, 0, 19}), 
 ChordData({34, 0, 200}), ChordData({34, 4, 73}), ChordData({34, 4, 146}), ChordData({34, 73, 130}), 
 ChordData({34, 76, 0}), ChordData({36, 0, 210}), ChordData({36, 8, 2}), ChordData({38, 33, 17}), 
 ChordData({48, 5, 89}), ChordData({48, 8, 25}), ChordData({48, 8, 73}), ChordData({48, 9, 19}), 
 ChordData({48, 9, 24}), ChordData({48, 9, 73}), ChordData({48, 12, 17}), ChordData({48, 13, 64}), 
 ChordData({48, 32, 193}), ChordData({48, 64, 73}), ChordData({48, 68, 208}), ChordData({48, 69, 128}), 
 ChordData({50, 1, 73}), ChordData({50, 5, 128}), ChordData({50, 8, 10}), ChordData({50, 9, 9}), 
 ChordData({50, 9, 18}), ChordData({50, 12, 10}), ChordData({50, 40, 130}), ChordData({50, 44, 2}), 
 ChordData({50, 64, 66}), ChordData({50, 64, 138}), ChordData({50, 72, 80}), ChordData({50, 72, 144}), 
 ChordData({50, 97, 3}), ChordData({52, 0, 67}), ChordData({52, 0, 154}), ChordData({52, 4, 66}), 
 ChordData({52, 4, 138}), ChordData({52, 8, 25}), ChordData({52, 36, 9}), ChordData({52, 65, 1}), 
 ChordData({54, 0, 19}), ChordData({54, 4, 11}), ChordData({54, 4, 16}), ChordData({54, 8, 128}), 
 ChordData({128, 0, 26}), ChordData({128, 1, 2}), ChordData({128, 4, 216}), ChordData({128, 36, 130}), 
 ChordData({128, 36, 210}), ChordData({128, 65, 130}), ChordData({128, 69, 16}), ChordData({128, 100, 66}), 
 ChordData({130, 8, 25}), ChordData({130, 8, 72}), ChordData({130, 8, 136}), ChordData({130, 32, 26}), 
 ChordData({130, 72, 66}), ChordData({132, 0, 88}), ChordData({134, 0, 8}), ChordData({134, 0, 25}), 
 ChordData({134, 0, 131}), ChordData({134, 4, 72}), ChordData({134, 4, 131}), ChordData({144, 8, 11}), 
 ChordData({144, 9, 26}), ChordData({144, 40, 24}), ChordData({144, 64, 145}), ChordData({146, 0, 83}), 
 ChordData({148, 0, 80}), ChordData({148, 8, 66}), ChordData({148, 12, 18}), ChordData({148, 64, 88}), 
 ChordData({150, 8, 80}), ChordData({150, 8, 130}), ChordData({150, 64, 65}), ChordData({160, 0, 203}), 
 ChordData({160, 4, 11}), ChordData({160, 4, 208}), ChordData({160, 33, 1}), ChordData({162, 0, 9}), 
 ChordData({162, 0, 138}), ChordData({162, 0, 152}), ChordData({162, 4, 11}), ChordData({164, 1, 192}), 
 ChordData({164, 8, 210}), ChordData({166, 65, 16}), ChordData({176, 5, 81}), ChordData({176, 8, 27}), 
 ChordData({176, 8, 67}), ChordData({176, 8, 74}), ChordData({178, 8, 24}), ChordData({178, 8, 88}), 
 ChordData({178, 8, 137}), ChordData({178, 64, 65}), ChordData({180, 0, 147}), ChordData({180, 0, 209}), 
 ChordData({180, 1, 128}), ChordData({180, 4, 136}), 
};

const uint8_t kmap0_Word_len29_anagram0_seqs[515] = {
 64, 65, 1, 144, 
 113, 126, 17, 14, 
 44, 22, 166, 167, 
 203, 23, 12, 24, 
 36, 32, 211, 207, 
 246, 107, 250, 217, 
 126, 74, 191, 211, 
 87, 220, 169, 233, 
 231, 248, 212, 84, 
 252, 44, 156, 126, 
 132, 207, 220, 140, 
 63, 178, 31, 129, 
 2, 8, 42, 72, 
 0, 150, 197, 175, 
 251, 173, 248, 181, 
 247, 169, 254, 108, 
 63, 113, 253, 237, 
 167, 74, 207, 219, 
 200, 214, 181, 162, 
 129, 192, 39, 243, 
 225, 95, 232, 129, 
 159, 120, 61, 11, 
 61, 233, 233, 50, 
 230, 37, 191, 148, 
 99, 102, 190, 248, 
 215, 115, 88, 122, 
 158, 142, 214, 87, 
 52, 16, 248, 212, 
 78, 143, 176, 213, 
 64, 190, 182, 169, 
 212, 82, 93, 36, 
 203, 198, 167, 234, 
 57, 140, 251, 187, 
 78, 117, 171, 85, 
 190, 174, 175, 234, 
 171, 172, 99, 217, 
 184, 250, 155, 231, 
 233, 153, 63, 211, 
 138, 143, 57, 39, 
 236, 193, 220, 219, 
 202, 153, 90, 57, 
 243, 126, 43, 78, 
 198, 126, 42, 147, 
 27, 75, 64, 190, 
 216, 146, 115, 173, 
 84, 156, 198, 207, 
 236, 115, 250, 134, 
 203, 59, 175, 183, 
 69, 235, 230, 49, 
 224, 181, 104, 221, 
 60, 37, 23, 99, 
 209, 122, 155, 125, 
 39, 235, 126, 250, 
 117, 158, 100, 230, 
 191, 205, 48, 239, 
 146, 121, 179, 180, 
 46, 151, 201, 63, 
 126, 34, 223, 150, 
 236, 221, 214, 187, 
 137, 124, 63, 1, 
 209, 218, 232, 100, 
 111, 235, 45, 122, 
 250, 40, 196, 71, 
 108, 181, 104, 216, 
 72, 126, 132, 109, 
 209, 156, 27, 91, 
 186, 21, 41, 75, 
 203, 22, 61, 108, 
 105, 106, 209, 115, 
 113, 223, 112, 57, 
 115, 53, 174, 22, 
 231, 73, 62, 141, 
 159, 217, 231, 211, 
 43, 186, 142, 69, 
 235, 158, 86, 255, 
 194, 51, 203, 219, 
 91, 27, 55, 143, 
 241, 207, 86, 239, 
 249, 51, 237, 57, 
 77, 109, 209, 0, 
 67, 53, 6, 4, 
 56, 0, 2, 129, 
 231, 208, 39, 12, 
 24, 196, 8, 131, 
 126, 142, 32, 138, 
 203, 31, 71, 140, 
 100, 248, 50, 46, 
 41, 180, 55, 38, 
 53, 115, 135, 166, 
 38, 234, 80, 132, 
 19, 218, 120, 105, 
 150, 145, 184, 134, 
 114, 76, 212, 214, 
 14, 173, 49, 219, 
 161, 53, 168, 183, 
 177, 62, 115, 135, 
 226, 215, 222, 32, 
 140, 148, 172, 155, 
 66, 75, 46, 96, 
 76, 10, 245, 134, 
 148, 228, 225, 192, 
 246, 22, 117, 162, 
 6, 27, 35, 213, 
 96, 99, 164, 250, 
 227, 49, 215, 80, 
 89, 39, 82, 179, 
 49, 82, 109, 178, 
 116, 13, 238, 197, 
 80, 206, 180, 143, 
 24, 89, 247, 39, 
 50, 63, 45, 140, 
 124, 195, 205, 189, 
 29, 138, 145, 21, 
 155, 4, 178, 118, 
 12, 126, 222, 14, 
 189, 41, 206, 204, 
 92, 164, 51, 232, 
 136, 57, 91, 242, 
 198, 252, 109, 12, 
 21, 61, 139, 193, 
 155, 147, 49, 148, 
 115, 178, 85, 236, 
 9, 21, 61, 220, 
 161, 98, 7, 89, 
 55, 242, 114, 75, 
 199, 41, 96, 92, 
 138, 147, 215, 115, 
 199, 121, 146, 207, 
 8, 242, 43, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len29_anagram0 = {
  LengthAndAnagram(29, 0), // seq_bit_len_and_anagram
  142, // num_chords
  kmap0_Word_len29_anagram0_chords, // chords
  kmap0_Word_len29_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len29_anagram1_chords[24] = {
 ChordData({2, 36, 19}), ChordData({2, 68, 146}), ChordData({16, 9, 146}), ChordData({18, 76, 130}), 
 ChordData({20, 4, 144}), ChordData({20, 36, 19}), ChordData({34, 33, 129}), ChordData({36, 0, 9}), 
 ChordData({36, 0, 16}), ChordData({36, 9, 0}), ChordData({48, 0, 147}), ChordData({48, 4, 152}), 
 ChordData({48, 5, 17}), ChordData({48, 5, 24}), ChordData({48, 12, 153}), ChordData({52, 4, 19}), 
 ChordData({54, 4, 144}), ChordData({144, 0, 147}), ChordData({148, 8, 17}), ChordData({162, 4, 11}), 
 ChordData({164, 64, 18}), ChordData({164, 64, 26}), ChordData({178, 12, 129}), ChordData({180, 0, 129}), 
};

const uint8_t kmap0_Word_len29_anagram1_seqs[87] = {
 63, 11, 167, 113, 
 94, 54, 62, 129, 
 146, 137, 10, 105, 
 236, 244, 244, 181, 
 254, 152, 16, 126, 
 93, 207, 65, 125, 
 195, 205, 103, 214, 
 205, 160, 130, 1, 
 249, 200, 101, 203, 
 98, 166, 205, 99, 
 64, 159, 199, 122, 
 248, 55, 143, 127, 
 230, 245, 182, 104, 
 221, 121, 194, 175, 
 155, 199, 212, 167, 
 231, 137, 98, 215, 
 83, 212, 137, 20, 
 235, 207, 184, 29, 
 122, 198, 76, 92, 
 52, 206, 144, 133, 
 216, 65, 191, 174, 
 65, 148, 215, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len29_anagram1 = {
  LengthAndAnagram(29, 1), // seq_bit_len_and_anagram
  24, // num_chords
  kmap0_Word_len29_anagram1_chords, // chords
  kmap0_Word_len29_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len29_anagram2_chords[6] = {
 ChordData({16, 4, 155}), ChordData({36, 0, 2}), ChordData({36, 8, 0}), ChordData({50, 1, 8}), 
 ChordData({52, 12, 16}), ChordData({180, 0, 16}), 
};

const uint8_t kmap0_Word_len29_anagram2_seqs[22] = {
 244, 107, 197, 2, 
 32, 168, 32, 159, 
 185, 108, 217, 219, 
 154, 91, 253, 231, 
 57, 22, 129, 243, 
 68, 53, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len29_anagram2 = {
  LengthAndAnagram(29, 2), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Word_len29_anagram2_chords, // chords
  kmap0_Word_len29_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len30_anagram0_chords[126] = {
 ChordData({0, 4, 211}), ChordData({0, 4, 219}), ChordData({0, 68, 88}), ChordData({0, 69, 0}), 
 ChordData({2, 4, 146}), ChordData({2, 5, 67}), ChordData({2, 64, 18}), ChordData({4, 1, 2}), 
 ChordData({4, 1, 128}), ChordData({4, 4, 152}), ChordData({4, 12, 144}), ChordData({6, 12, 137}), 
 ChordData({6, 36, 64}), ChordData({16, 8, 81}), ChordData({16, 8, 147}), ChordData({16, 13, 147}), 
 ChordData({16, 32, 25}), ChordData({16, 68, 82}), ChordData({16, 68, 146}), ChordData({16, 100, 19}), 
 ChordData({18, 0, 89}), ChordData({18, 0, 147}), ChordData({18, 4, 90}), ChordData({18, 4, 209}), 
 ChordData({18, 9, 19}), ChordData({18, 64, 91}), ChordData({18, 65, 3}), ChordData({18, 73, 2}), 
 ChordData({20, 0, 90}), ChordData({20, 0, 202}), ChordData({20, 4, 155}), ChordData({20, 8, 26}), 
 ChordData({20, 36, 80}), ChordData({22, 1, 146}), ChordData({32, 33, 26}), ChordData({32, 68, 209}), 
 ChordData({34, 4, 80}), ChordData({34, 5, 73}), ChordData({34, 12, 11}), ChordData({34, 12, 24}), 
 ChordData({34, 12, 25}), ChordData({34, 12, 73}), ChordData({34, 41, 9}), ChordData({34, 64, 66}), 
 ChordData({34, 64, 209}), ChordData({36, 0, 2}), ChordData({36, 1, 128}), ChordData({36, 8, 8}), 
 ChordData({36, 64, 64}), ChordData({38, 96, 18}), ChordData({48, 0, 131}), ChordData({48, 1, 152}), 
 ChordData({48, 5, 82}), ChordData({48, 13, 16}), ChordData({48, 44, 81}), ChordData({48, 73, 128}), 
 ChordData({48, 76, 8}), ChordData({48, 76, 10}), ChordData({50, 12, 64}), ChordData({50, 13, 8}), 
 ChordData({50, 13, 17}), ChordData({50, 33, 200}), ChordData({50, 44, 18}), ChordData({50, 64, 136}), 
 ChordData({50, 65, 130}), ChordData({52, 64, 11}), ChordData({52, 64, 72}), ChordData({54, 0, 17}), 
 ChordData({54, 1, 9}), ChordData({54, 8, 9}), ChordData({54, 12, 9}), ChordData({54, 12, 17}), 
 ChordData({54, 12, 64}), ChordData({128, 36, 88}), ChordData({128, 44, 67}), ChordData({128, 64, 136}), 
 ChordData({128, 76, 138}), ChordData({130, 1, 209}), ChordData({130, 5, 11}), ChordData({130, 64, 130}), 
 ChordData({130, 68, 24}), ChordData({130, 73, 18}), ChordData({132, 1, 146}), ChordData({132, 4, 146}), 
 ChordData({132, 12, 3}), ChordData({134, 4, 9}), ChordData({134, 12, 129}), ChordData({144, 1, 72}), 
 ChordData({144, 4, 145}), ChordData({144, 64, 83}), ChordData({144, 72, 130}), ChordData({144, 73, 16}), 
 ChordData({144, 76, 66}), ChordData({148, 0, 27}), ChordData({148, 9, 24}), ChordData({148, 32, 17}), 
 ChordData({150, 1, 144}), ChordData({160, 5, 131}), ChordData({160, 5, 152}), ChordData({160, 64, 11}), 
 ChordData({160, 77, 16}), ChordData({162, 0, 82}), ChordData({162, 5, 26}), ChordData({162, 5, 130}), 
 ChordData({162, 8, 11}), ChordData({162, 32, 74}), ChordData({162, 68, 24}), ChordData({164, 4, 3}), 
 ChordData({164, 33, 1}), ChordData({176, 1, 25}), ChordData({176, 1, 74}), ChordData({176, 1, 194}), 
 ChordData({176, 5, 18}), ChordData({176, 8, 144}), ChordData({176, 9, 16}), ChordData({176, 13, 9}), 
 ChordData({178, 72, 18}), ChordData({180, 0, 64}), ChordData({180, 0, 80}), ChordData({180, 0, 82}), 
 ChordData({180, 0, 145}), ChordData({180, 8, 3}), ChordData({180, 8, 80}), ChordData({180, 64, 18}), 
 ChordData({180, 72, 128}), ChordData({182, 8, 10}), 
};

const uint8_t kmap0_Word_len30_anagram0_seqs[473] = {
 56, 5, 239, 19, 
 23, 186, 127, 5, 
 248, 85, 206, 131, 
 3, 72, 240, 143, 
 83, 80, 227, 241, 
 140, 205, 11, 36, 
 104, 80, 128, 10, 
 14, 128, 128, 192, 
 1, 42, 16, 248, 
 250, 42, 240, 101, 
 203, 118, 170, 244, 
 186, 95, 225, 115, 
 63, 59, 153, 215, 
 227, 171, 29, 39, 
 11, 60, 150, 188, 
 94, 232, 81, 175, 
 52, 142, 159, 253, 
 52, 126, 89, 92, 
 252, 11, 61, 173, 
 235, 49, 175, 201, 
 184, 211, 216, 138, 
 227, 103, 251, 135, 
 218, 188, 56, 141, 
 37, 175, 180, 114, 
 111, 33, 125, 52, 
 246, 94, 26, 75, 
 150, 117, 204, 86, 
 180, 175, 170, 149, 
 93, 173, 79, 91, 
 88, 203, 22, 201, 
 213, 3, 191, 114, 
 29, 31, 125, 5, 
 179, 222, 83, 188, 
 20, 200, 188, 96, 
 50, 115, 255, 223, 
 223, 202, 43, 254, 
 54, 190, 106, 143, 
 248, 250, 226, 79, 
 191, 238, 114, 214, 
 79, 93, 210, 190, 
 225, 202, 102, 204, 
 204, 92, 38, 247, 
 44, 168, 0, 193, 
 9, 110, 80, 1, 
 1, 17, 84, 160, 
 64, 130, 19, 48, 
 44, 206, 105, 233, 
 43, 99, 94, 11, 
 100, 189, 201, 156, 
 231, 120, 244, 139, 
 158, 191, 13, 127, 
 68, 243, 150, 40, 
 203, 219, 41, 171, 
 124, 245, 75, 241, 
 21, 157, 158, 185, 
 69, 119, 250, 187, 
 213, 169, 239, 249, 
 181, 245, 166, 102, 
 248, 131, 176, 69, 
 103, 237, 50, 217, 
 151, 190, 111, 242, 
 233, 189, 216, 202, 
 153, 171, 85, 238, 
 244, 153, 215, 167, 
 213, 71, 111, 181, 
 110, 231, 244, 233, 
 108, 235, 214, 105, 
 241, 215, 245, 153, 
 91, 52, 96, 248, 
 19, 202, 27, 233, 
 17, 2, 10, 149, 
 161, 87, 41, 244, 
 229, 65, 49, 205, 
 123, 60, 110, 135, 
 94, 154, 40, 46, 
 175, 114, 162, 101, 
 10, 217, 71, 113, 
 80, 212, 90, 124, 
 173, 19, 87, 24, 
 169, 62, 238, 215, 
 26, 173, 27, 117, 
 59, 61, 197, 113, 
 88, 217, 27, 228, 
 249, 181, 52, 239, 
 68, 113, 49, 97, 
 36, 31, 99, 203, 
 72, 127, 49, 71, 
 178, 117, 39, 106, 
 113, 76, 148, 181, 
 214, 137, 10, 189, 
 117, 226, 104, 50, 
 254, 62, 197, 45, 
 240, 115, 135, 98, 
 168, 204, 184, 82, 
 140, 249, 18, 230, 
 233, 200, 28, 115, 
 191, 54, 82, 220, 
 141, 79, 24, 42, 
 54, 46, 102, 134, 
 29, 250, 35, 115, 
 107, 108, 156, 143, 
 24, 103, 228, 27, 
 238, 17, 179, 89, 
 141, 161, 71, 102, 
 223, 148, 49, 216, 
 24, 121, 254, 246, 
 88, 12, 18, 125, 
 196, 88, 244, 164, 
 208, 253, 219, 178, 
 197, 24, 52, 231, 
 90, 131, 93, 243, 
 212, 96, 199, 201, 
 152, 199, 59, 145, 
 79, 50, 70, 170, 
 121, 29, 39, 123, 
 68, 215, 9, 153, 
 209, 210, 162, 41, 
 42, 70, 58, 91, 
 13, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len30_anagram0 = {
  LengthAndAnagram(30, 0), // seq_bit_len_and_anagram
  126, // num_chords
  kmap0_Word_len30_anagram0_chords, // chords
  kmap0_Word_len30_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len30_anagram1_chords[28] = {
 ChordData({0, 36, 9}), ChordData({2, 4, 147}), ChordData({4, 40, 0}), ChordData({16, 4, 27}), 
 ChordData({16, 37, 17}), ChordData({18, 4, 145}), ChordData({18, 64, 27}), ChordData({32, 9, 64}), 
 ChordData({32, 13, 0}), ChordData({34, 1, 0}), ChordData({36, 0, 64}), ChordData({36, 8, 2}), 
 ChordData({36, 64, 64}), ChordData({48, 0, 27}), ChordData({48, 5, 144}), ChordData({48, 5, 152}), 
 ChordData({48, 13, 64}), ChordData({52, 1, 16}), ChordData({52, 4, 130}), ChordData({54, 0, 25}), 
 ChordData({128, 9, 19}), ChordData({144, 0, 27}), ChordData({144, 1, 9}), ChordData({144, 8, 26}), 
 ChordData({148, 1, 80}), ChordData({180, 0, 17}), ChordData({180, 32, 17}), ChordData({180, 64, 130}), 
};

const uint8_t kmap0_Word_len30_anagram1_seqs[105] = {
 64, 127, 225, 43, 
 210, 79, 111, 1, 
 18, 168, 0, 90, 
 119, 94, 209, 199, 
 207, 66, 15, 245, 
 122, 126, 125, 153, 
 222, 181, 130, 27, 
 48, 72, 47, 122, 
 254, 54, 184, 65, 
 6, 13, 50, 96, 
 112, 130, 10, 68, 
 128, 224, 4, 12, 
 36, 90, 55, 79, 
 49, 190, 51, 253, 
 28, 89, 61, 79, 
 233, 153, 255, 246, 
 153, 143, 195, 131, 
 95, 255, 36, 239, 
 244, 153, 213, 96, 
 163, 84, 4, 134, 
 226, 120, 125, 92, 
 251, 181, 25, 67, 
 35, 21, 117, 226, 
 48, 51, 152, 56, 
 61, 123, 78, 44, 
 244, 92, 226, 60, 
 201, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len30_anagram1 = {
  LengthAndAnagram(30, 1), // seq_bit_len_and_anagram
  28, // num_chords
  kmap0_Word_len30_anagram1_chords, // chords
  kmap0_Word_len30_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len30_anagram2_chords[5] = {
 ChordData({0, 68, 10}), ChordData({16, 0, 146}), ChordData({34, 12, 136}), ChordData({48, 1, 16}), 
 ChordData({52, 0, 128}), 
};

const uint8_t kmap0_Word_len30_anagram2_seqs[19] = {
 0, 95, 95, 62, 
 16, 240, 76, 33, 
 190, 54, 209, 143, 
 143, 124, 219, 103, 
 62, 79, 50, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len30_anagram2 = {
  LengthAndAnagram(30, 2), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Word_len30_anagram2_chords, // chords
  kmap0_Word_len30_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len30_anagram3_chords[3] = {
 ChordData({18, 0, 131}), ChordData({18, 64, 19}), ChordData({160, 33, 1}), 
};

const uint8_t kmap0_Word_len30_anagram3_seqs[12] = {
 235, 171, 109, 242, 
 94, 122, 215, 115, 
 68, 190, 225, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len30_anagram3 = {
  LengthAndAnagram(30, 3), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Word_len30_anagram3_chords, // chords
  kmap0_Word_len30_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len31_anagram0_chords[107] = {
 ChordData({0, 45, 19}), ChordData({2, 5, 18}), ChordData({2, 36, 19}), ChordData({2, 69, 130}), 
 ChordData({4, 108, 16}), ChordData({6, 1, 89}), ChordData({16, 68, 147}), ChordData({16, 69, 146}), 
 ChordData({16, 96, 19}), ChordData({18, 0, 83}), ChordData({18, 1, 19}), ChordData({18, 4, 19}), 
 ChordData({18, 4, 138}), ChordData({18, 4, 153}), ChordData({18, 12, 65}), ChordData({18, 12, 138}), 
 ChordData({18, 13, 65}), ChordData({18, 36, 65}), ChordData({18, 41, 11}), ChordData({18, 64, 83}), 
 ChordData({20, 0, 210}), ChordData({20, 4, 81}), ChordData({20, 36, 19}), ChordData({22, 12, 144}), 
 ChordData({32, 13, 24}), ChordData({34, 0, 147}), ChordData({34, 5, 18}), ChordData({34, 12, 145}), 
 ChordData({34, 64, 128}), ChordData({34, 69, 129}), ChordData({34, 76, 65}), ChordData({34, 96, 192}), 
 ChordData({36, 4, 145}), ChordData({36, 12, 16}), ChordData({38, 32, 9}), ChordData({48, 4, 81}), 
 ChordData({48, 5, 25}), ChordData({48, 13, 24}), ChordData({48, 33, 17}), ChordData({48, 69, 129}), 
 ChordData({48, 96, 24}), ChordData({50, 1, 17}), ChordData({50, 1, 24}), ChordData({50, 5, 144}), 
 ChordData({50, 8, 17}), ChordData({50, 13, 24}), ChordData({50, 13, 128}), ChordData({50, 33, 26}), 
 ChordData({50, 73, 16}), ChordData({50, 97, 129}), ChordData({52, 0, 145}), ChordData({52, 4, 19}), 
 ChordData({52, 5, 144}), ChordData({52, 9, 16}), ChordData({52, 44, 18}), ChordData({52, 68, 144}), 
 ChordData({54, 0, 147}), ChordData({54, 8, 16}), ChordData({54, 8, 192}), ChordData({54, 12, 16}), 
 ChordData({128, 9, 19}), ChordData({128, 12, 27}), ChordData({128, 76, 10}), ChordData({130, 9, 26}), 
 ChordData({130, 32, 83}), ChordData({130, 37, 72}), ChordData({130, 64, 10}), ChordData({132, 0, 144}), 
 ChordData({132, 44, 9}), ChordData({144, 0, 139}), ChordData({144, 4, 9}), ChordData({144, 4, 153}), 
 ChordData({144, 12, 65}), ChordData({144, 68, 19}), ChordData({146, 0, 81}), ChordData({146, 0, 202}), 
 ChordData({146, 4, 17}), ChordData({146, 4, 25}), ChordData({146, 4, 90}), ChordData({146, 4, 153}), 
 ChordData({148, 0, 146}), ChordData({148, 9, 16}), ChordData({160, 0, 27}), ChordData({160, 76, 144}), 
 ChordData({162, 9, 24}), ChordData({162, 12, 80}), ChordData({162, 33, 9}), ChordData({164, 0, 25}), 
 ChordData({164, 0, 73}), ChordData({164, 0, 81}), ChordData({164, 4, 144}), ChordData({164, 64, 19}), 
 ChordData({164, 68, 8}), ChordData({176, 0, 18}), ChordData({176, 0, 145}), ChordData({176, 1, 16}), 
 ChordData({176, 1, 18}), ChordData({176, 1, 154}), ChordData({176, 9, 17}), ChordData({176, 32, 146}), 
 ChordData({178, 8, 136}), ChordData({180, 8, 144}), ChordData({180, 12, 16}), ChordData({180, 64, 144}), 
 ChordData({182, 8, 0}), ChordData({182, 8, 16}), ChordData({182, 72, 16}), 
};

const uint8_t kmap0_Word_len31_anagram0_seqs[415] = {
 160, 244, 11, 11, 
 240, 199, 52, 62, 
 194, 159, 222, 226, 
 160, 71, 108, 9, 
 191, 236, 143, 228, 
 58, 173, 123, 128, 
 203, 211, 122, 46, 
 166, 227, 199, 23, 
 232, 133, 158, 49, 
 239, 52, 46, 122, 
 182, 143, 2, 167, 
 215, 211, 255, 68, 
 253, 138, 110, 93, 
 143, 62, 153, 183, 
 211, 175, 125, 245, 
 169, 213, 169, 121, 
 191, 100, 104, 238, 
 253, 117, 169, 23, 
 161, 85, 54, 227, 
 120, 237, 171, 58, 
 102, 102, 215, 159, 
 95, 47, 244, 124, 
 45, 198, 79, 93, 
 214, 175, 127, 207, 
 167, 188, 77, 189, 
 5, 184, 127, 176, 
 95, 236, 217, 252, 
 68, 93, 38, 183, 
 148, 125, 247, 62, 
 241, 190, 236, 156, 
 184, 76, 110, 134, 
 251, 103, 166, 159, 
 243, 203, 254, 79, 
 43, 236, 179, 119, 
 199, 207, 121, 124, 
 91, 61, 191, 6, 
 183, 39, 189, 30, 
 121, 22, 122, 164, 
 143, 207, 180, 48, 
 171, 28, 203, 157, 
 190, 111, 143, 245, 
 110, 181, 231, 152, 
 191, 155, 60, 222, 
 105, 139, 22, 91, 
 125, 255, 136, 77, 
 244, 183, 97, 113, 
 183, 213, 178, 69, 
 207, 109, 105, 234, 
 27, 46, 56, 243, 
 146, 231, 252, 93, 
 79, 241, 116, 251, 
 156, 175, 158, 35, 
 39, 35, 252, 116, 
 122, 78, 122, 41, 
 61, 212, 167, 103, 
 139, 58, 78, 157, 
 147, 216, 220, 39, 
 89, 252, 84, 123, 
 140, 145, 142, 152, 
 125, 253, 141, 84, 
 96, 164, 244, 42, 
 49, 244, 232, 73, 
 176, 121, 99, 138, 
 227, 25, 118, 232, 
 165, 85, 198, 165, 
 78, 156, 228, 84, 
 225, 235, 70, 194, 
 208, 245, 213, 190, 
 106, 236, 175, 55, 
 200, 243, 186, 78, 
 191, 107, 14, 105, 
 140, 249, 245, 152, 
 155, 55, 134, 155, 
 26, 67, 221, 235, 
 249, 141, 121, 93, 
 79, 199, 48, 90, 
 127, 58, 198, 244, 
 219, 161, 190, 170, 
 20, 227, 234, 57, 
 98, 18, 70, 214, 
 157, 34, 133, 204, 
 244, 147, 98, 180, 
 245, 22, 127, 58, 
 50, 111, 104, 223, 
 112, 193, 25, 179, 
 161, 224, 12, 222, 
 80, 206, 181, 198, 
 108, 141, 154, 233, 
 167, 78, 200, 140, 
 251, 231, 171, 12, 
 45, 34, 11, 30, 
 79, 100, 242, 174, 
 193, 237, 152, 219, 
 247, 4, 122, 138, 
 184, 42, 110, 235, 
 29, 121, 146, 183, 
 136, 44, 120, 220, 
 42, 6, 137, 174, 
 19, 39, 57, 125, 
 173, 19, 162, 207, 
 200, 36, 61, 101, 
 35, 157, 237, 78, 
 117, 66, 116, 157, 
 16, 91, 26, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len31_anagram0 = {
  LengthAndAnagram(31, 0), // seq_bit_len_and_anagram
  107, // num_chords
  kmap0_Word_len31_anagram0_chords, // chords
  kmap0_Word_len31_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len31_anagram1_chords[24] = {
 ChordData({6, 4, 147}), ChordData({6, 12, 0}), ChordData({16, 4, 147}), ChordData({16, 36, 82}), 
 ChordData({16, 64, 74}), ChordData({18, 4, 27}), ChordData({18, 4, 131}), ChordData({20, 0, 147}), 
 ChordData({22, 4, 11}), ChordData({34, 9, 8}), ChordData({34, 12, 9}), ChordData({48, 4, 19}), 
 ChordData({48, 5, 81}), ChordData({48, 5, 146}), ChordData({48, 13, 9}), ChordData({52, 0, 17}), 
 ChordData({54, 1, 8}), ChordData({130, 68, 18}), ChordData({130, 76, 8}), ChordData({144, 4, 131}), 
 ChordData({146, 0, 11}), ChordData({148, 0, 88}), ChordData({148, 8, 146}), ChordData({162, 33, 9}), 
};

const uint8_t kmap0_Word_len31_anagram1_seqs[93] = {
 91, 212, 198, 167, 
 218, 101, 203, 190, 
 175, 118, 30, 119, 
 204, 254, 65, 8, 
 46, 150, 106, 110, 
 93, 207, 227, 250, 
 10, 123, 127, 125, 
 133, 158, 186, 245, 
 183, 173, 104, 177, 
 75, 173, 183, 216, 
 251, 169, 21, 199, 
 191, 121, 204, 251, 
 247, 237, 121, 34, 
 207, 93, 136, 175, 
 251, 183, 171, 103, 
 243, 156, 213, 122, 
 231, 214, 203, 207, 
 116, 140, 236, 79, 
 161, 242, 137, 2, 
 127, 221, 170, 129, 
 214, 29, 115, 13, 
 101, 215, 160, 34, 
 121, 52, 22, 182, 
 222, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len31_anagram1 = {
  LengthAndAnagram(31, 1), // seq_bit_len_and_anagram
  24, // num_chords
  kmap0_Word_len31_anagram1_chords, // chords
  kmap0_Word_len31_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len31_anagram2_chords[9] = {
 ChordData({36, 9, 0}), ChordData({38, 1, 0}), ChordData({48, 0, 147}), ChordData({48, 5, 146}), 
 ChordData({50, 13, 9}), ChordData({54, 8, 192}), ChordData({164, 4, 146}), ChordData({164, 64, 18}), 
 ChordData({178, 1, 24}), 
};

const uint8_t kmap0_Word_len31_anagram2_seqs[35] = {
 32, 129, 10, 110, 
 112, 128, 19, 244, 
 250, 106, 243, 248, 
 126, 34, 79, 33, 
 182, 238, 223, 230, 
 124, 82, 39, 3, 
 129, 199, 56, 49, 
 46, 103, 20, 71, 
 140, 251, 86, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len31_anagram2 = {
  LengthAndAnagram(31, 2), // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_Word_len31_anagram2_chords, // chords
  kmap0_Word_len31_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len31_anagram3_chords[1] = {
 ChordData({48, 8, 18}), 
};

const uint8_t kmap0_Word_len31_anagram3_seqs[4] = {
 201, 131, 121, 10, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len31_anagram3 = {
  LengthAndAnagram(31, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len31_anagram3_chords, // chords
  kmap0_Word_len31_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len32_anagram0_chords[106] = {
 ChordData({0, 5, 91}), ChordData({0, 33, 72}), ChordData({0, 68, 2}), ChordData({0, 100, 203}), 
 ChordData({2, 4, 147}), ChordData({2, 5, 19}), ChordData({2, 5, 83}), ChordData({2, 76, 26}), 
 ChordData({6, 12, 18}), ChordData({6, 68, 210}), ChordData({16, 68, 154}), ChordData({18, 8, 89}), 
 ChordData({18, 12, 145}), ChordData({18, 12, 153}), ChordData({18, 32, 74}), ChordData({18, 33, 80}), 
 ChordData({18, 36, 131}), ChordData({18, 64, 11}), ChordData({18, 64, 25}), ChordData({18, 68, 3}), 
 ChordData({18, 68, 11}), ChordData({18, 68, 75}), ChordData({18, 68, 81}), ChordData({18, 72, 10}), 
 ChordData({18, 76, 17}), ChordData({20, 4, 144}), ChordData({20, 4, 201}), ChordData({20, 12, 129}), 
 ChordData({20, 12, 130}), ChordData({22, 1, 82}), ChordData({22, 4, 138}), ChordData({22, 8, 11}), 
 ChordData({32, 4, 210}), ChordData({32, 5, 146}), ChordData({32, 13, 25}), ChordData({32, 13, 128}), 
 ChordData({32, 68, 154}), ChordData({32, 69, 144}), ChordData({34, 5, 136}), ChordData({34, 8, 8}), 
 ChordData({34, 33, 88}), ChordData({34, 77, 16}), ChordData({38, 4, 146}), ChordData({38, 5, 24}), 
 ChordData({38, 37, 18}), ChordData({38, 40, 17}), ChordData({38, 64, 81}), ChordData({48, 1, 65}), 
 ChordData({48, 1, 82}), ChordData({48, 1, 154}), ChordData({48, 4, 19}), ChordData({48, 4, 146}), 
 ChordData({48, 12, 153}), ChordData({48, 64, 130}), ChordData({48, 64, 201}), ChordData({48, 64, 209}), 
 ChordData({48, 69, 19}), ChordData({50, 1, 81}), ChordData({50, 4, 201}), ChordData({50, 8, 83}), 
 ChordData({50, 12, 145}), ChordData({50, 33, 17}), ChordData({50, 64, 144}), ChordData({50, 68, 10}), 
 ChordData({50, 72, 10}), ChordData({52, 4, 17}), ChordData({52, 4, 208}), ChordData({52, 8, 80}), 
 ChordData({52, 12, 82}), ChordData({52, 13, 137}), ChordData({54, 0, 145}), ChordData({54, 4, 144}), 
 ChordData({54, 8, 18}), ChordData({128, 4, 75}), ChordData({128, 4, 91}), ChordData({128, 44, 26}), 
 ChordData({128, 100, 194}), ChordData({130, 4, 74}), ChordData({130, 4, 139}), ChordData({130, 4, 147}), 
 ChordData({130, 100, 146}), ChordData({132, 12, 26}), ChordData({134, 8, 146}), ChordData({144, 76, 17}), 
 ChordData({146, 8, 67}), ChordData({146, 8, 72}), ChordData({146, 12, 9}), ChordData({146, 64, 74}), 
 ChordData({146, 64, 90}), ChordData({148, 0, 147}), ChordData({148, 4, 194}), ChordData({148, 4, 216}), 
 ChordData({148, 8, 131}), ChordData({150, 0, 9}), ChordData({150, 0, 131}), ChordData({160, 13, 24}), 
 ChordData({160, 96, 72}), ChordData({162, 8, 19}), ChordData({164, 0, 147}), ChordData({164, 13, 16}), 
 ChordData({176, 1, 2}), ChordData({176, 4, 10}), ChordData({176, 8, 90}), ChordData({176, 8, 130}), 
 ChordData({178, 0, 11}), ChordData({180, 8, 136}), 
};

const uint8_t kmap0_Word_len32_anagram0_seqs[424] = {
 199, 235, 62, 23, 
 199, 53, 47, 84, 
 18, 60, 64, 128, 
 151, 103, 21, 188, 
 56, 189, 141, 79, 
 59, 127, 28, 141, 
 252, 219, 124, 20, 
 178, 208, 79, 141, 
 117, 58, 253, 20, 
 178, 185, 210, 23, 
 248, 100, 149, 63, 
 169, 181, 121, 61, 
 233, 215, 211, 79, 
 235, 73, 173, 79, 
 0, 97, 171, 217, 
 12, 61, 125, 28, 
 191, 144, 188, 141, 
 173, 216, 210, 186, 
 210, 42, 167, 215, 
 210, 178, 241, 215, 
 173, 178, 241, 215, 
 178, 121, 95, 209, 
 178, 249, 121, 61, 
 201, 178, 177, 213, 
 178, 63, 121, 61, 
 245, 231, 137, 76, 
 149, 252, 252, 186, 
 235, 84, 233, 215, 
 190, 250, 84, 201, 
 92, 141, 125, 20, 
 190, 170, 244, 173, 
 216, 219, 101, 173, 
 153, 243, 19, 21, 
 247, 211, 95, 21, 
 226, 223, 243, 186, 
 159, 158, 238, 79, 
 244, 89, 229, 20, 
 247, 188, 204, 79, 
 247, 235, 77, 253, 
 169, 181, 83, 78, 
 71, 30, 109, 134, 
 178, 255, 158, 79, 
 212, 231, 252, 20, 
 231, 207, 253, 173, 
 247, 124, 133, 141, 
 59, 157, 83, 133, 
 178, 121, 243, 156, 
 156, 239, 219, 188, 
 156, 231, 246, 20, 
 7, 101, 43, 22, 
 143, 152, 231, 215, 
 104, 162, 76, 63, 
 99, 178, 248, 186, 
 190, 66, 202, 210, 
 236, 50, 217, 186, 
 227, 50, 217, 188, 
 59, 127, 91, 22, 
 227, 187, 121, 61, 
 173, 156, 233, 215, 
 162, 103, 27, 205, 
 99, 250, 109, 209, 
 199, 184, 111, 184, 
 227, 50, 185, 199, 
 159, 101, 91, 209, 
 22, 91, 90, 209, 
 95, 61, 155, 199, 
 149, 252, 156, 199, 
 117, 204, 30, 209, 
 78, 231, 51, 23, 
 39, 189, 150, 188, 
 235, 153, 62, 201, 
 99, 234, 63, 201, 
 213, 131, 110, 209, 
 24, 202, 251, 186, 
 24, 186, 243, 188, 
 240, 39, 133, 22, 
 12, 159, 40, 46, 
 129, 248, 220, 161, 
 20, 248, 219, 161, 
 24, 179, 141, 79, 
 48, 168, 229, 23, 
 24, 169, 190, 22, 
 65, 69, 170, 141, 
 41, 164, 231, 215, 
 24, 156, 188, 141, 
 78, 205, 220, 161, 
 26, 169, 245, 215, 
 210, 216, 220, 161, 
 24, 202, 45, 61, 
 117, 66, 192, 184, 
 24, 68, 95, 217, 
 213, 195, 161, 79, 
 24, 169, 146, 215, 
 213, 219, 219, 161, 
 190, 170, 20, 189, 
 32, 197, 220, 175, 
 0, 102, 201, 161, 
 98, 227, 198, 20, 
 53, 50, 237, 20, 
 117, 226, 158, 79, 
 192, 0, 3, 220, 
 175, 26, 89, 209, 
 24, 202, 30, 209, 
 41, 200, 152, 201, 
 24, 186, 173, 217, 
 86, 209, 20, 213, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len32_anagram0 = {
  LengthAndAnagram(32, 0), // seq_bit_len_and_anagram
  106, // num_chords
  kmap0_Word_len32_anagram0_chords, // chords
  kmap0_Word_len32_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len32_anagram1_chords[14] = {
 ChordData({16, 8, 19}), ChordData({16, 8, 83}), ChordData({18, 12, 9}), ChordData({18, 68, 11}), 
 ChordData({22, 4, 19}), ChordData({22, 4, 147}), ChordData({32, 13, 16}), ChordData({38, 4, 147}), 
 ChordData({48, 69, 129}), ChordData({50, 8, 80}), ChordData({144, 0, 154}), ChordData({160, 13, 144}), 
 ChordData({180, 8, 19}), ChordData({180, 64, 82}), 
};

const uint8_t kmap0_Word_len32_anagram1_seqs[56] = {
 232, 228, 245, 20, 
 169, 224, 245, 20, 
 173, 219, 233, 215, 
 143, 216, 210, 186, 
 117, 30, 183, 209, 
 245, 103, 27, 201, 
 247, 124, 74, 63, 
 127, 54, 245, 22, 
 210, 228, 251, 215, 
 156, 71, 108, 209, 
 0, 99, 212, 68, 
 71, 76, 202, 244, 
 53, 68, 207, 22, 
 231, 196, 133, 61, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len32_anagram1 = {
  LengthAndAnagram(32, 1), // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_Word_len32_anagram1_chords, // chords
  kmap0_Word_len32_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len32_anagram2_chords[4] = {
 ChordData({16, 12, 81}), ChordData({32, 0, 146}), ChordData({128, 4, 27}), ChordData({130, 4, 11}), 
};

const uint8_t kmap0_Word_len32_anagram2_seqs[16] = {
 233, 119, 199, 204, 
 148, 175, 242, 20, 
 24, 186, 243, 184, 
 216, 251, 219, 161, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len32_anagram2 = {
  LengthAndAnagram(32, 2), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Word_len32_anagram2_chords, // chords
  kmap0_Word_len32_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len33_anagram0_chords[85] = {
 ChordData({0, 69, 18}), ChordData({2, 12, 9}), ChordData({2, 12, 154}), ChordData({2, 68, 26}), 
 ChordData({2, 100, 2}), ChordData({6, 76, 18}), ChordData({16, 5, 89}), ChordData({16, 44, 27}), 
 ChordData({16, 64, 90}), ChordData({16, 76, 1}), ChordData({18, 0, 210}), ChordData({18, 4, 155}), 
 ChordData({18, 12, 18}), ChordData({18, 65, 9}), ChordData({18, 76, 2}), ChordData({22, 64, 83}), 
 ChordData({22, 68, 80}), ChordData({32, 5, 65}), ChordData({32, 5, 147}), ChordData({32, 12, 82}), 
 ChordData({34, 0, 91}), ChordData({36, 100, 72}), ChordData({38, 12, 18}), ChordData({38, 32, 192}), 
 ChordData({48, 5, 145}), ChordData({48, 12, 129}), ChordData({48, 36, 195}), ChordData({48, 64, 83}), 
 ChordData({48, 96, 194}), ChordData({50, 5, 153}), ChordData({50, 8, 88}), ChordData({50, 12, 26}), 
 ChordData({50, 12, 129}), ChordData({50, 12, 147}), ChordData({50, 12, 193}), ChordData({50, 37, 17}), 
 ChordData({50, 65, 64}), ChordData({50, 68, 1}), ChordData({50, 68, 137}), ChordData({50, 68, 146}), 
 ChordData({52, 5, 16}), ChordData({52, 12, 192}), ChordData({52, 96, 18}), ChordData({54, 64, 82}), 
 ChordData({54, 68, 65}), ChordData({130, 4, 202}), ChordData({130, 12, 27}), ChordData({132, 0, 147}), 
 ChordData({132, 8, 83}), ChordData({134, 0, 73}), ChordData({134, 4, 17}), ChordData({134, 4, 147}), 
 ChordData({134, 96, 82}), ChordData({144, 13, 16}), ChordData({144, 96, 201}), ChordData({146, 8, 130}), 
 ChordData({146, 64, 80}), ChordData({148, 0, 9}), ChordData({148, 0, 83}), ChordData({148, 8, 82}), 
 ChordData({148, 8, 130}), ChordData({148, 12, 145}), ChordData({150, 0, 65}), ChordData({160, 4, 152}), 
 ChordData({160, 33, 17}), ChordData({162, 0, 201}), ChordData({162, 4, 67}), ChordData({162, 4, 145}), 
 ChordData({162, 4, 202}), ChordData({162, 96, 3}), ChordData({166, 1, 72}), ChordData({166, 8, 64}), 
 ChordData({176, 1, 90}), ChordData({176, 8, 88}), ChordData({176, 12, 1}), ChordData({176, 33, 17}), 
 ChordData({176, 64, 138}), ChordData({178, 1, 25}), ChordData({178, 1, 152}), ChordData({178, 8, 10}), 
 ChordData({178, 8, 81}), ChordData({178, 12, 9}), ChordData({178, 12, 129}), ChordData({182, 0, 80}), 
 ChordData({182, 0, 82}), 
};

const uint8_t kmap0_Word_len33_anagram0_seqs[351] = {
 199, 207, 203, 47, 
 210, 183, 238, 183, 
 226, 116, 106, 125, 
 2, 242, 231, 210, 
 10, 224, 95, 190, 
 251, 210, 101, 127, 
 228, 206, 43, 31, 
 158, 228, 65, 248, 
 186, 128, 11, 169, 
 46, 146, 247, 229, 
 239, 251, 202, 131, 
 205, 126, 189, 106, 
 111, 1, 62, 121, 
 26, 95, 250, 104, 
 237, 245, 227, 75, 
 167, 70, 105, 198, 
 233, 186, 245, 231, 
 101, 179, 193, 231, 
 59, 243, 30, 143, 
 153, 182, 224, 156, 
 210, 79, 209, 202, 
 59, 25, 23, 102, 
 62, 95, 101, 157, 
 22, 31, 139, 154, 
 79, 106, 134, 227, 
 59, 211, 175, 45, 
 62, 229, 95, 251, 
 10, 126, 230, 149, 
 230, 157, 140, 203, 
 8, 45, 51, 185, 
 117, 125, 207, 83, 
 214, 22, 61, 108, 
 241, 167, 95, 209, 
 153, 182, 211, 175, 
 69, 207, 54, 62, 
 113, 167, 76, 191, 
 134, 158, 222, 191, 
 45, 251, 56, 50, 
 251, 119, 123, 179, 
 244, 235, 118, 153, 
 236, 199, 50, 185, 
 199, 247, 207, 249, 
 183, 159, 217, 233, 
 36, 3, 232, 115, 
 124, 145, 102, 156, 
 62, 45, 251, 79, 
 175, 25, 104, 99, 
 208, 243, 68, 122, 
 221, 198, 58, 177, 
 129, 65, 92, 164, 
 186, 145, 106, 112, 
 111, 135, 214, 152, 
 157, 239, 221, 137, 
 218, 248, 116, 137, 
 97, 216, 181, 244, 
 243, 81, 178, 12, 
 179, 10, 94, 144, 
 124, 213, 24, 178, 
 57, 70, 122, 162, 
 214, 80, 235, 214, 
 9, 174, 198, 197, 
 72, 117, 204, 140, 
 145, 42, 249, 106, 
 157, 106, 204, 83, 
 212, 26, 220, 107, 
 129, 200, 163, 79, 
 11, 39, 242, 13, 
 57, 40, 111, 135, 
 62, 70, 230, 109, 
 220, 188, 49, 253, 
 244, 122, 213, 145, 
 249, 210, 11, 35, 
 47, 184, 251, 228, 
 208, 56, 197, 142, 
 204, 24, 122, 143, 
 153, 173, 49, 41, 
 50, 127, 222, 72, 
 191, 222, 184, 189, 
 208, 131, 161, 72, 
 89, 90, 123, 39, 
 110, 235, 152, 250, 
 238, 80, 12, 21, 
 91, 209, 41, 154, 
 55, 143, 91, 53, 
 196, 95, 139, 65, 
 191, 77, 230, 92, 
 61, 29, 83, 199, 
 216, 145, 25, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len33_anagram0 = {
  LengthAndAnagram(33, 0), // seq_bit_len_and_anagram
  85, // num_chords
  kmap0_Word_len33_anagram0_chords, // chords
  kmap0_Word_len33_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len33_anagram1_chords[14] = {
 ChordData({18, 1, 9}), ChordData({18, 44, 10}), ChordData({18, 44, 130}), ChordData({22, 0, 19}), 
 ChordData({22, 4, 80}), ChordData({34, 4, 146}), ChordData({48, 44, 18}), ChordData({50, 5, 153}), 
 ChordData({50, 12, 3}), ChordData({50, 12, 153}), ChordData({52, 4, 193}), ChordData({52, 8, 16}), 
 ChordData({160, 33, 1}), ChordData({164, 4, 146}), 
};

const uint8_t kmap0_Word_len33_anagram1_seqs[58] = {
 173, 71, 107, 175, 
 147, 17, 190, 54, 
 34, 116, 106, 124, 
 170, 99, 236, 218, 
 251, 181, 206, 55, 
 27, 123, 48, 211, 
 15, 128, 63, 162, 
 139, 157, 126, 189, 
 201, 143, 219, 226, 
 175, 91, 215, 35, 
 62, 129, 211, 191, 
 100, 30, 39, 167, 
 211, 179, 48, 242, 
 13, 23, 156, 95, 
 80, 12, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len33_anagram1 = {
  LengthAndAnagram(33, 1), // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_Word_len33_anagram1_chords, // chords
  kmap0_Word_len33_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len33_anagram2_chords[2] = {
 ChordData({48, 69, 24}), ChordData({144, 8, 26}), 
};

const uint8_t kmap0_Word_len33_anagram2_seqs[9] = {
 86, 249, 122, 123, 
 208, 227, 20, 90, 
 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len33_anagram2 = {
  LengthAndAnagram(33, 2), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len33_anagram2_chords, // chords
  kmap0_Word_len33_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len33_anagram3_chords[1] = {
 ChordData({20, 4, 25}), 
};

const uint8_t kmap0_Word_len33_anagram3_seqs[5] = {
 95, 235, 143, 117, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len33_anagram3 = {
  LengthAndAnagram(33, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len33_anagram3_chords, // chords
  kmap0_Word_len33_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len34_anagram0_chords[79] = {
 ChordData({0, 68, 89}), ChordData({0, 69, 128}), ChordData({2, 4, 218}), ChordData({6, 36, 74}), 
 ChordData({16, 1, 26}), ChordData({16, 4, 153}), ChordData({16, 4, 155}), ChordData({16, 5, 25}), 
 ChordData({18, 4, 193}), ChordData({18, 4, 201}), ChordData({18, 44, 130}), ChordData({18, 64, 27}), 
 ChordData({18, 64, 154}), ChordData({20, 12, 154}), ChordData({20, 96, 80}), ChordData({22, 0, 210}), 
 ChordData({22, 1, 66}), ChordData({22, 44, 64}), ChordData({34, 0, 217}), ChordData({34, 12, 9}), 
 ChordData({34, 12, 67}), ChordData({34, 12, 81}), ChordData({34, 13, 19}), ChordData({36, 4, 83}), 
 ChordData({48, 33, 89}), ChordData({50, 0, 83}), ChordData({50, 13, 9}), ChordData({50, 13, 16}), 
 ChordData({52, 5, 25}), ChordData({52, 8, 83}), ChordData({52, 12, 24}), ChordData({52, 36, 82}), 
 ChordData({54, 0, 72}), ChordData({54, 8, 129}), ChordData({54, 32, 131}), ChordData({128, 44, 25}), 
 ChordData({128, 68, 152}), ChordData({128, 69, 18}), ChordData({130, 1, 139}), ChordData({130, 5, 27}), 
 ChordData({130, 68, 9}), ChordData({132, 4, 208}), ChordData({132, 65, 16}), ChordData({134, 12, 128}), 
 ChordData({134, 12, 138}), ChordData({134, 36, 193}), ChordData({134, 40, 24}), ChordData({144, 4, 147}), 
 ChordData({144, 4, 155}), ChordData({144, 32, 26}), ChordData({144, 64, 17}), ChordData({144, 64, 147}), 
 ChordData({146, 0, 147}), ChordData({148, 32, 208}), ChordData({150, 76, 8}), ChordData({162, 1, 195}), 
 ChordData({162, 12, 9}), ChordData({162, 12, 11}), ChordData({162, 64, 75}), ChordData({164, 33, 17}), 
 ChordData({166, 1, 146}), ChordData({176, 0, 83}), ChordData({176, 0, 154}), ChordData({176, 8, 9}), 
 ChordData({176, 9, 26}), ChordData({176, 72, 11}), ChordData({176, 76, 3}), ChordData({176, 76, 129}), 
 ChordData({178, 12, 1}), ChordData({178, 72, 82}), ChordData({180, 0, 19}), ChordData({180, 1, 80}), 
 ChordData({180, 4, 129}), ChordData({180, 4, 193}), ChordData({180, 8, 19}), ChordData({182, 0, 192}), 
 ChordData({182, 8, 65}), ChordData({182, 32, 144}), ChordData({182, 36, 16}), 
};

const uint8_t kmap0_Word_len34_anagram0_seqs[336] = {
 188, 175, 242, 71, 
 130, 3, 60, 40, 
 243, 250, 84, 112, 
 51, 108, 174, 175, 
 141, 227, 195, 99, 
 69, 63, 173, 71, 
 127, 237, 171, 245, 
 232, 211, 31, 135, 
 199, 186, 252, 107, 
 162, 94, 155, 217, 
 186, 253, 4, 82, 
 35, 124, 83, 75, 
 235, 246, 22, 88, 
 80, 171, 244, 188, 
 62, 21, 101, 205, 
 208, 21, 122, 164, 
 107, 147, 43, 23, 
 92, 141, 125, 52, 
 58, 85, 248, 220, 
 12, 4, 50, 111, 
 235, 246, 190, 118, 
 78, 143, 219, 98, 
 243, 242, 78, 255, 
 230, 116, 207, 139, 
 189, 197, 159, 188, 
 243, 184, 188, 99, 
 189, 23, 178, 49, 
 79, 111, 161, 190, 
 127, 91, 116, 250, 
 153, 254, 219, 117, 
 124, 235, 235, 114, 
 53, 238, 228, 148, 
 156, 206, 121, 117, 
 205, 131, 240, 217, 
 103, 230, 86, 51, 
 167, 76, 219, 149, 
 236, 43, 216, 103, 
 111, 250, 249, 133, 
 161, 64, 32, 70, 
 190, 30, 49, 151, 
 31, 137, 161, 7, 
 53, 238, 49, 143, 
 219, 161, 47, 101, 
 111, 135, 214, 137, 
 26, 252, 4, 234, 
 196, 33, 76, 138, 
 178, 77, 244, 24, 
 169, 210, 183, 194, 
 224, 218, 251, 4, 
 99, 186, 108, 40, 
 198, 140, 233, 215, 
 27, 228, 121, 69, 
 99, 64, 143, 21, 
 109, 50, 238, 132, 
 180, 201, 184, 19, 
 210, 190, 90, 79, 
 199, 0, 129, 96, 
 87, 40, 163, 126, 
 106, 53, 197, 221, 
 188, 141, 41, 178, 
 238, 183, 138, 143, 
 191, 29, 42, 155, 
 49, 178, 238, 57, 
 145, 111, 184, 103, 
 7, 197, 93, 96, 
 228, 89, 115, 33, 
 16, 121, 212, 69, 
 10, 209, 201, 186, 
 24, 42, 122, 110, 
 203, 192, 156, 172, 
 251, 82, 12, 252, 
 117, 10, 153, 233, 
 215, 41, 182, 197, 
 95, 203, 102, 12, 
 209, 3, 2, 55, 
 78, 79, 157, 184, 
 199, 204, 53, 106, 
 166, 95, 255, 201, 
 65, 121, 141, 145, 
 106, 94, 79, 13, 
 230, 62, 201, 53, 
 184, 183, 69, 195, 
 152, 233, 147, 236, 
 92, 97, 76, 63, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len34_anagram0 = {
  LengthAndAnagram(34, 0), // seq_bit_len_and_anagram
  79, // num_chords
  kmap0_Word_len34_anagram0_chords, // chords
  kmap0_Word_len34_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len34_anagram1_chords[9] = {
 ChordData({0, 4, 211}), ChordData({2, 5, 19}), ChordData({18, 4, 25}), ChordData({20, 0, 89}), 
 ChordData({54, 1, 128}), ChordData({54, 12, 16}), ChordData({128, 4, 27}), ChordData({130, 1, 27}), 
 ChordData({134, 0, 72}), 
};

const uint8_t kmap0_Word_len34_anagram1_seqs[39] = {
 248, 251, 84, 240, 
 254, 108, 31, 143, 
 107, 93, 207, 126, 
 235, 184, 142, 217, 
 186, 166, 190, 251, 
 36, 159, 93, 246, 
 103, 140, 161, 59, 
 63, 197, 49, 141, 
 219, 161, 160, 70, 
 51, 135, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len34_anagram1 = {
  LengthAndAnagram(34, 1), // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_Word_len34_anagram1_chords, // chords
  kmap0_Word_len34_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len34_anagram2_chords[1] = {
 ChordData({48, 5, 128}), 
};

const uint8_t kmap0_Word_len34_anagram2_seqs[5] = {
 148, 239, 251, 111, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len34_anagram2 = {
  LengthAndAnagram(34, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len34_anagram2_chords, // chords
  kmap0_Word_len34_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len34_anagram4_chords[1] = {
 ChordData({20, 4, 25}), 
};

const uint8_t kmap0_Word_len34_anagram4_seqs[5] = {
 213, 234, 157, 95, 
 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len34_anagram4 = {
  LengthAndAnagram(34, 4), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len34_anagram4_chords, // chords
  kmap0_Word_len34_anagram4_seqs, // sequences
};

const ChordData kmap0_Word_len35_anagram0_chords[63] = {
 ChordData({2, 13, 144}), ChordData({2, 100, 18}), ChordData({6, 4, 19}), ChordData({16, 4, 217}), 
 ChordData({16, 72, 27}), ChordData({18, 4, 89}), ChordData({18, 8, 27}), ChordData({18, 12, 137}), 
 ChordData({18, 72, 25}), ChordData({20, 68, 81}), ChordData({22, 0, 25}), ChordData({22, 0, 27}), 
 ChordData({22, 4, 147}), ChordData({32, 4, 18}), ChordData({32, 12, 210}), ChordData({32, 44, 193}), 
 ChordData({34, 5, 210}), ChordData({34, 8, 193}), ChordData({34, 37, 81}), ChordData({36, 40, 18}), 
 ChordData({38, 12, 137}), ChordData({48, 4, 9}), ChordData({48, 5, 83}), ChordData({48, 13, 25}), 
 ChordData({48, 64, 202}), ChordData({48, 69, 17}), ChordData({48, 69, 136}), ChordData({50, 13, 193}), 
 ChordData({50, 64, 154}), ChordData({52, 4, 147}), ChordData({52, 8, 128}), ChordData({52, 36, 129}), 
 ChordData({52, 68, 136}), ChordData({54, 0, 210}), ChordData({54, 4, 146}), ChordData({54, 12, 144}), 
 ChordData({130, 68, 26}), ChordData({132, 12, 8}), ChordData({132, 36, 18}), ChordData({134, 0, 19}), 
 ChordData({134, 0, 90}), ChordData({134, 44, 10}), ChordData({144, 72, 90}), ChordData({146, 1, 146}), 
 ChordData({146, 4, 9}), ChordData({146, 4, 67}), ChordData({146, 4, 195}), ChordData({148, 0, 19}), 
 ChordData({148, 0, 216}), ChordData({148, 4, 19}), ChordData({160, 32, 73}), ChordData({162, 1, 11}), 
 ChordData({162, 5, 9}), ChordData({162, 13, 88}), ChordData({162, 72, 72}), ChordData({166, 12, 136}), 
 ChordData({176, 5, 19}), ChordData({176, 8, 25}), ChordData({178, 8, 147}), ChordData({178, 13, 17}), 
 ChordData({180, 68, 144}), ChordData({182, 5, 129}), ChordData({182, 8, 80}), 
};

const uint8_t kmap0_Word_len35_anagram0_seqs[276] = {
 199, 167, 166, 254, 
 1, 211, 8, 127, 
 36, 126, 125, 236, 
 45, 118, 94, 153, 
 126, 45, 141, 227, 
 100, 221, 157, 87, 
 110, 235, 182, 226, 
 56, 89, 215, 212, 
 169, 245, 215, 210, 
 235, 73, 173, 150, 
 230, 234, 249, 117, 
 235, 122, 234, 120, 
 199, 216, 181, 173, 
 59, 174, 212, 248, 
 235, 71, 204, 243, 
 88, 136, 207, 152, 
 233, 103, 225, 211, 
 167, 204, 156, 231, 
 110, 124, 226, 237, 
 148, 41, 51, 239, 
 124, 223, 112, 65, 
 202, 83, 97, 81, 
 233, 183, 53, 167, 
 223, 181, 230, 95, 
 243, 206, 175, 239, 
 226, 231, 206, 201, 
 186, 236, 50, 217, 
 138, 190, 231, 101, 
 254, 53, 176, 222, 
 244, 42, 15, 243, 
 182, 248, 100, 45, 
 147, 123, 10, 52, 
 249, 156, 95, 215, 
 92, 182, 44, 249, 
 169, 194, 63, 189, 
 53, 75, 171, 124, 
 98, 156, 62, 79, 
 242, 152, 250, 79, 
 42, 196, 159, 254, 
 147, 28, 35, 91, 
 127, 10, 240, 233, 
 203, 134, 126, 173, 
 19, 143, 176, 78, 
 199, 244, 22, 92, 
 104, 84, 110, 70, 
 248, 169, 118, 40, 
 23, 42, 39, 146, 
 143, 30, 31, 113, 
 245, 187, 214, 237, 
 208, 103, 14, 236, 
 95, 7, 99, 19, 
 253, 186, 78, 84, 
 207, 22, 213, 195, 
 161, 106, 194, 136, 
 234, 249, 53, 128, 
 145, 121, 67, 143, 
 172, 184, 29, 122, 
 68, 214, 253, 214, 
 152, 251, 181, 57, 
 201, 22, 155, 59, 
 180, 190, 216, 212, 
 161, 248, 235, 59, 
 166, 0, 162, 39, 
 133, 174, 104, 10, 
 236, 45, 142, 23, 
 99, 122, 125, 254, 
 68, 153, 236, 56, 
 169, 239, 95, 215, 
 177, 216, 145, 25, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len35_anagram0 = {
  LengthAndAnagram(35, 0), // seq_bit_len_and_anagram
  63, // num_chords
  kmap0_Word_len35_anagram0_chords, // chords
  kmap0_Word_len35_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len35_anagram1_chords[10] = {
 ChordData({2, 12, 147}), ChordData({18, 4, 89}), ChordData({36, 4, 83}), ChordData({50, 12, 9}), 
 ChordData({50, 13, 9}), ChordData({52, 13, 16}), ChordData({52, 72, 0}), ChordData({146, 4, 25}), 
 ChordData({176, 8, 9}), ChordData({180, 64, 64}), 
};

const uint8_t kmap0_Word_len35_anagram1_seqs[44] = {
 169, 169, 247, 167, 
 24, 115, 243, 190, 
 46, 231, 115, 231, 
 113, 129, 216, 94, 
 253, 164, 47, 246, 
 253, 235, 211, 162, 
 231, 111, 59, 157, 
 150, 210, 178, 215, 
 243, 219, 161, 41, 
 146, 117, 115, 226, 
 92, 107, 176, 37, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len35_anagram1 = {
  LengthAndAnagram(35, 1), // seq_bit_len_and_anagram
  10, // num_chords
  kmap0_Word_len35_anagram1_chords, // chords
  kmap0_Word_len35_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len35_anagram2_chords[1] = {
 ChordData({146, 0, 11}), 
};

const uint8_t kmap0_Word_len35_anagram2_seqs[5] = {
 24, 186, 173, 214, 
 5, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len35_anagram2 = {
  LengthAndAnagram(35, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len35_anagram2_chords, // chords
  kmap0_Word_len35_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len36_anagram0_chords[61] = {
 ChordData({0, 4, 72}), ChordData({2, 5, 210}), ChordData({6, 5, 2}), ChordData({6, 36, 210}), 
 ChordData({16, 4, 90}), ChordData({16, 36, 19}), ChordData({16, 68, 155}), ChordData({18, 4, 210}), 
 ChordData({18, 36, 19}), ChordData({18, 36, 139}), ChordData({18, 41, 10}), ChordData({18, 65, 27}), 
 ChordData({20, 12, 17}), ChordData({20, 12, 25}), ChordData({20, 64, 9}), ChordData({22, 0, 131}), 
 ChordData({22, 64, 89}), ChordData({34, 12, 19}), ChordData({34, 12, 136}), ChordData({34, 64, 91}), 
 ChordData({34, 64, 154}), ChordData({34, 68, 147}), ChordData({38, 13, 10}), ChordData({38, 76, 128}), 
 ChordData({48, 1, 209}), ChordData({48, 4, 131}), ChordData({48, 5, 155}), ChordData({48, 9, 88}), 
 ChordData({48, 101, 17}), ChordData({50, 0, 73}), ChordData({50, 5, 19}), ChordData({50, 5, 25}), 
 ChordData({50, 8, 73}), ChordData({52, 72, 192}), ChordData({54, 5, 144}), ChordData({128, 4, 9}), 
 ChordData({128, 32, 154}), ChordData({128, 65, 146}), ChordData({128, 72, 19}), ChordData({130, 4, 138}), 
 ChordData({130, 5, 130}), ChordData({130, 69, 144}), ChordData({130, 77, 136}), ChordData({132, 13, 145}), 
 ChordData({144, 36, 83}), ChordData({144, 36, 131}), ChordData({150, 0, 81}), ChordData({150, 4, 137}), 
 ChordData({150, 4, 154}), ChordData({160, 5, 210}), ChordData({160, 65, 10}), ChordData({162, 37, 2}), 
 ChordData({164, 12, 144}), ChordData({164, 72, 10}), ChordData({176, 1, 80}), ChordData({178, 0, 90}), 
 ChordData({178, 5, 9}), ChordData({178, 5, 16}), ChordData({178, 8, 80}), ChordData({182, 33, 24}), 
 ChordData({182, 44, 16}), 
};

const uint8_t kmap0_Word_len36_anagram0_seqs[275] = {
 64, 193, 3, 6, 
 143, 244, 204, 125, 
 20, 160, 62, 246, 
 209, 88, 97, 193, 
 141, 79, 106, 52, 
 243, 79, 129, 240, 
 231, 113, 61, 47, 
 5, 30, 173, 11, 
 4, 204, 220, 248, 
 63, 8, 123, 141, 
 187, 70, 168, 141, 
 79, 0, 97, 99, 
 201, 218, 210, 186, 
 125, 20, 245, 231, 
 147, 215, 83, 61, 
 233, 213, 186, 210, 
 213, 42, 173, 235, 
 171, 74, 141, 189, 
 117, 204, 45, 173, 
 251, 184, 45, 246, 
 22, 79, 57, 181, 
 230, 212, 42, 51, 
 239, 20, 173, 101, 
 114, 79, 81, 38, 
 63, 245, 22, 248, 
 169, 126, 223, 90, 
 159, 168, 101, 78, 
 188, 147, 239, 155, 
 140, 79, 152, 233, 
 215, 99, 220, 215, 
 155, 156, 204, 108, 
 189, 61, 242, 243, 
 13, 215, 211, 202, 
 219, 155, 215, 216, 
 247, 143, 119, 221, 
 186, 190, 231, 215, 
 108, 229, 222, 22, 
 205, 101, 178, 93, 
 214, 224, 254, 115, 
 218, 4, 20, 60, 
 88, 16, 64, 32, 
 160, 106, 1, 226, 
 234, 136, 145, 27, 
 41, 102, 226, 130, 
 175, 161, 141, 79, 
 113, 28, 141, 253, 
 4, 14, 138, 105, 
 249, 233, 181, 143, 
 32, 89, 233, 247, 
 136, 73, 49, 8, 
 205, 59, 143, 48, 
 48, 232, 215, 53, 
 120, 61, 29, 83, 
 99, 173, 219, 79, 
 53, 6, 77, 223, 
 122, 83, 48, 255, 
 20, 24, 122, 68, 
 86, 9, 16, 54, 
 254, 29, 95, 235, 
 132, 248, 132, 145, 
 106, 100, 149, 119, 
 204, 237, 200, 60, 
 198, 60, 220, 161, 
 234, 59, 182, 127, 
 13, 110, 199, 220, 
 253, 99, 246, 136, 
 209, 163, 238, 27, 
 158, 49, 167, 225, 
 139, 29, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len36_anagram0 = {
  LengthAndAnagram(36, 0), // seq_bit_len_and_anagram
  61, // num_chords
  kmap0_Word_len36_anagram0_chords, // chords
  kmap0_Word_len36_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len36_anagram1_chords[7] = {
 ChordData({2, 4, 67}), ChordData({2, 5, 147}), ChordData({16, 4, 83}), ChordData({48, 5, 145}), 
 ChordData({130, 0, 202}), ChordData({148, 4, 19}), ChordData({148, 8, 11}), 
};

const uint8_t kmap0_Word_len36_anagram1_seqs[32] = {
 188, 191, 205, 219, 
 120, 60, 54, 245, 
 22, 108, 28, 239, 
 79, 113, 207, 175, 
 143, 76, 24, 68, 
 205, 29, 138, 49, 
 53, 230, 215, 24, 
 169, 122, 173, 11, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len36_anagram1 = {
  LengthAndAnagram(36, 1), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Word_len36_anagram1_chords, // chords
  kmap0_Word_len36_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len36_anagram2_chords[1] = {
 ChordData({48, 5, 136}), 
};

const uint8_t kmap0_Word_len36_anagram2_seqs[5] = {
 244, 122, 231, 191, 
 13, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len36_anagram2 = {
  LengthAndAnagram(36, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len36_anagram2_chords, // chords
  kmap0_Word_len36_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len37_anagram0_chords[63] = {
 ChordData({0, 68, 27}), ChordData({2, 8, 65}), ChordData({2, 8, 83}), ChordData({2, 36, 91}), 
 ChordData({2, 76, 130}), ChordData({2, 100, 74}), ChordData({4, 44, 18}), ChordData({6, 4, 147}), 
 ChordData({16, 100, 147}), ChordData({16, 108, 3}), ChordData({18, 5, 18}), ChordData({18, 5, 75}), 
 ChordData({18, 5, 82}), ChordData({18, 12, 26}), ChordData({18, 76, 1}), ChordData({20, 12, 66}), 
 ChordData({22, 8, 137}), ChordData({22, 12, 146}), ChordData({22, 36, 65}), ChordData({22, 36, 81}), 
 ChordData({22, 68, 19}), ChordData({32, 108, 16}), ChordData({34, 1, 211}), ChordData({38, 8, 147}), 
 ChordData({48, 0, 83}), ChordData({48, 13, 26}), ChordData({48, 37, 138}), ChordData({48, 68, 129}), 
 ChordData({50, 1, 138}), ChordData({50, 8, 152}), ChordData({50, 12, 25}), ChordData({50, 36, 11}), 
 ChordData({50, 36, 26}), ChordData({50, 69, 73}), ChordData({50, 76, 81}), ChordData({52, 5, 88}), 
 ChordData({54, 0, 25}), ChordData({54, 4, 147}), ChordData({54, 4, 200}), ChordData({128, 64, 1}), 
 ChordData({130, 64, 11}), ChordData({130, 68, 25}), ChordData({134, 4, 19}), ChordData({144, 4, 82}), 
 ChordData({144, 12, 73}), ChordData({144, 72, 26}), ChordData({146, 0, 19}), ChordData({146, 72, 72}), 
 ChordData({148, 8, 11}), ChordData({150, 8, 25}), ChordData({160, 0, 91}), ChordData({160, 37, 129}), 
 ChordData({160, 69, 192}), ChordData({162, 0, 74}), ChordData({162, 0, 155}), ChordData({166, 0, 210}), 
 ChordData({176, 5, 130}), ChordData({176, 8, 153}), ChordData({178, 64, 27}), ChordData({178, 64, 194}), 
 ChordData({178, 64, 201}), ChordData({178, 68, 137}), ChordData({180, 8, 145}), 
};

const uint8_t kmap0_Word_len37_anagram0_seqs[292] = {
 151, 159, 121, 221, 
 130, 183, 83, 166, 
 95, 227, 244, 54, 
 54, 39, 132, 211, 
 188, 253, 10, 46, 
 77, 212, 159, 248, 
 85, 94, 26, 97, 
 133, 63, 233, 177, 
 168, 243, 184, 141, 
 79, 248, 11, 45, 
 231, 9, 164, 223, 
 133, 190, 248, 56, 
 26, 31, 139, 227, 
 25, 91, 127, 205, 
 143, 211, 71, 163, 
 193, 39, 79, 227, 
 107, 167, 100, 217, 
 191, 230, 250, 232, 
 244, 200, 157, 42, 
 57, 89, 215, 169, 
 246, 52, 62, 65, 
 215, 223, 222, 230, 
 133, 158, 175, 205, 
 91, 45, 251, 119, 
 26, 1, 252, 17, 
 127, 164, 64, 230, 
 237, 163, 72, 153, 
 182, 43, 21, 188, 
 147, 113, 243, 24, 
 220, 158, 244, 90, 
 32, 124, 34, 235, 
 237, 151, 46, 147, 
 127, 221, 122, 80, 
 182, 162, 5, 178, 
 104, 109, 178, 254, 
 204, 111, 139, 254, 
 188, 208, 186, 141, 
 48, 207, 52, 190, 
 90, 154, 251, 214, 
 95, 191, 20, 61, 
 219, 236, 250, 204, 
 214, 219, 211, 186, 
 158, 201, 117, 241, 
 169, 207, 249, 117, 
 181, 182, 114, 166, 
 7, 11, 2, 72, 
 16, 24, 42, 123, 
 59, 116, 231, 101, 
 111, 135, 226, 215, 
 199, 222, 152, 71, 
 52, 115, 76, 1, 
 210, 239, 154, 67, 
 199, 24, 41, 89, 
 229, 122, 166, 55, 
 166, 144, 157, 172, 
 220, 161, 24, 169, 
 134, 90, 183, 78, 
 164, 86, 235, 98, 
 40, 239, 100, 220, 
 167, 133, 145, 111, 
 8, 100, 228, 155, 
 158, 49, 148, 177, 
 35, 179, 64, 86, 
 220, 14, 173, 193, 
 220, 39, 21, 24, 
 68, 254, 59, 91, 
 12, 202, 186, 246, 
 180, 238, 132, 204, 
 104, 105, 106, 236, 
 200, 92, 38, 155, 
 183, 67, 93, 38, 
 255, 118, 104, 245, 
 78, 144, 115, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len37_anagram0 = {
  LengthAndAnagram(37, 0), // seq_bit_len_and_anagram
  63, // num_chords
  kmap0_Word_len37_anagram0_chords, // chords
  kmap0_Word_len37_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len37_anagram1_chords[8] = {
 ChordData({16, 0, 139}), ChordData({18, 12, 138}), ChordData({22, 0, 154}), ChordData({22, 4, 138}), 
 ChordData({48, 5, 25}), ChordData({48, 37, 138}), ChordData({52, 4, 208}), ChordData({180, 64, 18}), 
};

const uint8_t kmap0_Word_len37_anagram1_seqs[37] = {
 190, 66, 19, 89, 
 23, 36, 95, 53, 
 190, 214, 105, 197, 
 174, 228, 175, 149, 
 250, 21, 125, 231, 
 159, 215, 181, 125, 
 133, 240, 245, 54, 
 187, 254, 252, 73, 
 174, 19, 104, 153, 
 199, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len37_anagram1 = {
  LengthAndAnagram(37, 1), // seq_bit_len_and_anagram
  8, // num_chords
  kmap0_Word_len37_anagram1_chords, // chords
  kmap0_Word_len37_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len37_anagram2_chords[1] = {
 ChordData({18, 68, 11}), 
};

const uint8_t kmap0_Word_len37_anagram2_seqs[5] = {
 248, 42, 91, 254, 
 26, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len37_anagram2 = {
  LengthAndAnagram(37, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len37_anagram2_chords, // chords
  kmap0_Word_len37_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len38_anagram0_chords[45] = {
 ChordData({0, 77, 18}), ChordData({2, 5, 75}), ChordData({2, 44, 75}), ChordData({2, 44, 83}), 
 ChordData({6, 4, 154}), ChordData({18, 1, 11}), ChordData({18, 12, 27}), ChordData({18, 32, 91}), 
 ChordData({18, 37, 90}), ChordData({18, 44, 74}), ChordData({22, 68, 138}), ChordData({34, 41, 81}), 
 ChordData({38, 4, 153}), ChordData({48, 5, 81}), ChordData({48, 9, 26}), ChordData({48, 36, 81}), 
 ChordData({48, 65, 153}), ChordData({48, 76, 25}), ChordData({50, 5, 89}), ChordData({52, 4, 75}), 
 ChordData({52, 72, 18}), ChordData({54, 1, 130}), ChordData({54, 4, 17}), ChordData({54, 36, 193}), 
 ChordData({54, 68, 131}), ChordData({128, 1, 64}), ChordData({128, 68, 146}), ChordData({130, 36, 88}), 
 ChordData({130, 76, 72}), ChordData({134, 12, 10}), ChordData({134, 12, 25}), ChordData({134, 12, 146}), 
 ChordData({144, 96, 209}), ChordData({144, 100, 138}), ChordData({146, 0, 155}), ChordData({146, 0, 203}), 
 ChordData({146, 64, 19}), ChordData({146, 65, 11}), ChordData({148, 1, 80}), ChordData({160, 36, 195}), 
 ChordData({162, 12, 3}), ChordData({162, 12, 194}), ChordData({164, 1, 17}), ChordData({164, 5, 192}), 
 ChordData({182, 13, 24}), 
};

const uint8_t kmap0_Word_len38_anagram0_seqs[214] = {
 127, 41, 93, 126, 
 228, 241, 186, 207, 
 219, 152, 30, 97, 
 107, 243, 34, 156, 
 230, 77, 207, 117, 
 90, 177, 235, 147, 
 143, 163, 177, 173, 
 155, 126, 61, 218, 
 91, 112, 161, 11, 
 189, 141, 199, 188, 
 34, 108, 118, 50, 
 194, 215, 230, 244, 
 181, 90, 101, 95, 
 129, 205, 83, 106, 
 134, 231, 52, 81, 
 191, 238, 49, 153, 
 119, 126, 237, 228, 
 185, 173, 88, 44, 
 52, 127, 158, 204, 
 199, 184, 76, 182, 
 238, 75, 209, 186, 
 121, 204, 125, 235, 
 111, 30, 115, 62, 
 121, 95, 209, 64, 
 26, 157, 78, 207, 
 65, 190, 234, 147, 
 252, 187, 211, 103, 
 94, 155, 247, 79, 
 106, 134, 50, 87, 
 106, 252, 53, 56, 
 64, 0, 6, 12, 
 48, 40, 230, 101, 
 0, 248, 51, 205, 
 161, 47, 83, 51, 
 119, 40, 70, 170, 
 175, 29, 218, 169, 
 198, 236, 235, 214, 
 137, 171, 78, 79, 
 11, 199, 12, 131, 
 36, 124, 162, 184, 
 216, 106, 50, 238, 
 132, 54, 250, 106, 
 173, 220, 161, 178, 
 199, 184, 49, 5, 
 134, 30, 45, 173, 
 91, 39, 14, 51, 
 199, 192, 160, 192, 
 207, 188, 159, 55, 
 210, 111, 99, 122, 
 106, 236, 200, 92, 
 39, 54, 206, 124, 
 28, 127, 102, 138, 
 204, 49, 247, 107, 
 151, 53, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len38_anagram0 = {
  LengthAndAnagram(38, 0), // seq_bit_len_and_anagram
  45, // num_chords
  kmap0_Word_len38_anagram0_chords, // chords
  kmap0_Word_len38_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len38_anagram1_chords[4] = {
 ChordData({18, 32, 91}), ChordData({22, 0, 89}), ChordData({54, 0, 147}), ChordData({178, 8, 137}), 
};

const uint8_t kmap0_Word_len38_anagram1_seqs[19] = {
 92, 232, 66, 115, 
 179, 117, 61, 117, 
 154, 141, 38, 159, 
 211, 91, 88, 12, 
 202, 219, 161, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len38_anagram1 = {
  LengthAndAnagram(38, 1), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Word_len38_anagram1_chords, // chords
  kmap0_Word_len38_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len38_anagram2_chords[1] = {
 ChordData({50, 8, 9}), 
};

const uint8_t kmap0_Word_len38_anagram2_seqs[5] = {
 173, 155, 123, 91, 
 52, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len38_anagram2 = {
  LengthAndAnagram(38, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len38_anagram2_chords, // chords
  kmap0_Word_len38_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len39_anagram0_chords[36] = {
 ChordData({2, 12, 210}), ChordData({2, 65, 0}), ChordData({4, 44, 83}), ChordData({4, 65, 130}), 
 ChordData({4, 72, 64}), ChordData({18, 5, 129}), ChordData({18, 36, 18}), ChordData({18, 40, 83}), 
 ChordData({18, 65, 25}), ChordData({20, 1, 26}), ChordData({22, 0, 89}), ChordData({22, 13, 144}), 
 ChordData({32, 8, 144}), ChordData({36, 1, 72}), ChordData({36, 4, 81}), ChordData({38, 8, 131}), 
 ChordData({50, 4, 145}), ChordData({52, 13, 129}), ChordData({54, 5, 19}), ChordData({54, 9, 144}), 
 ChordData({54, 12, 128}), ChordData({54, 76, 129}), ChordData({128, 12, 91}), ChordData({132, 4, 16}), 
 ChordData({132, 40, 90}), ChordData({144, 1, 26}), ChordData({144, 76, 18}), ChordData({148, 12, 19}), 
 ChordData({148, 36, 91}), ChordData({162, 1, 74}), ChordData({162, 69, 72}), ChordData({164, 4, 146}), 
 ChordData({166, 1, 0}), ChordData({178, 9, 11}), ChordData({178, 13, 81}), ChordData({182, 8, 24}), 
};

const uint8_t kmap0_Word_len39_anagram0_seqs[176] = {
 220, 169, 233, 135, 
 10, 217, 199, 225, 
 177, 46, 23, 169, 
 254, 194, 66, 18, 
 168, 224, 0, 8, 
 42, 144, 32, 1, 
 254, 227, 104, 234, 
 95, 195, 246, 252, 
 32, 44, 16, 58, 
 53, 239, 20, 178, 
 143, 195, 99, 221, 
 58, 62, 60, 86, 
 116, 245, 112, 243, 
 90, 247, 83, 165, 
 62, 218, 3, 68, 
 48, 32, 1, 2, 
 10, 24, 220, 160, 
 126, 173, 63, 191, 
 153, 83, 166, 237, 
 74, 141, 212, 235, 
 249, 205, 99, 209, 
 183, 247, 79, 242, 
 241, 231, 52, 254, 
 186, 78, 139, 77, 
 190, 253, 226, 55, 
 253, 73, 254, 84, 
 169, 55, 75, 63, 
 239, 132, 70, 42, 
 234, 196, 249, 39, 
 21, 92, 164, 10, 
 67, 11, 12, 61, 
 60, 86, 180, 116, 
 10, 156, 199, 98, 
 157, 106, 204, 79, 
 81, 95, 183, 128, 
 193, 198, 208, 35, 
 115, 135, 202, 254, 
 91, 131, 155, 235, 
 196, 249, 39, 21, 
 224, 6, 21, 52, 
 8, 140, 91, 123, 
 91, 244, 241, 98, 
 76, 175, 25, 136, 
 158, 46, 27, 10, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len39_anagram0 = {
  LengthAndAnagram(39, 0), // seq_bit_len_and_anagram
  36, // num_chords
  kmap0_Word_len39_anagram0_chords, // chords
  kmap0_Word_len39_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len39_anagram1_chords[4] = {
 ChordData({16, 68, 83}), ChordData({48, 5, 26}), ChordData({50, 1, 25}), ChordData({146, 0, 75}), 
};

const uint8_t kmap0_Word_len39_anagram1_seqs[20] = {
 133, 121, 61, 242, 
 139, 99, 254, 158, 
 87, 244, 145, 71, 
 123, 243, 24, 67, 
 185, 121, 173, 11, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len39_anagram1 = {
  LengthAndAnagram(39, 1), // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_Word_len39_anagram1_chords, // chords
  kmap0_Word_len39_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len40_anagram0_chords[33] = {
 ChordData({4, 73, 2}), ChordData({6, 12, 146}), ChordData({16, 0, 80}), ChordData({20, 4, 216}), 
 ChordData({20, 68, 19}), ChordData({22, 4, 11}), ChordData({32, 4, 154}), ChordData({32, 45, 8}), 
 ChordData({34, 68, 155}), ChordData({36, 1, 129}), ChordData({36, 9, 130}), ChordData({38, 4, 19}), 
 ChordData({48, 4, 89}), ChordData({48, 77, 9}), ChordData({50, 4, 209}), ChordData({50, 77, 9}), 
 ChordData({54, 0, 82}), ChordData({128, 69, 89}), ChordData({130, 4, 89}), ChordData({130, 4, 91}), 
 ChordData({146, 68, 27}), ChordData({146, 68, 67}), ChordData({148, 12, 75}), ChordData({150, 0, 202}), 
 ChordData({150, 32, 147}), ChordData({150, 64, 88}), ChordData({160, 12, 90}), ChordData({162, 36, 19}), 
 ChordData({162, 45, 145}), ChordData({178, 0, 75}), ChordData({178, 1, 26}), ChordData({178, 8, 11}), 
 ChordData({180, 8, 24}), 
};

const uint8_t kmap0_Word_len40_anagram0_seqs[165] = {
 50, 129, 10, 14, 
 128, 117, 58, 253, 
 52, 21, 99, 14, 
 202, 219, 161, 64, 
 224, 235, 171, 217, 
 210, 117, 140, 191, 
 150, 175, 219, 216, 
 245, 215, 64, 224, 
 53, 255, 20, 0, 
 230, 227, 72, 175, 
 101, 242, 235, 246, 
 22, 128, 192, 13, 
 78, 176, 34, 129, 
 10, 14, 128, 63, 
 103, 239, 252, 20, 
 99, 222, 207, 243, 
 186, 47, 197, 215, 
 253, 219, 77, 148, 
 121, 231, 215, 233, 
 111, 237, 205, 210, 
 156, 79, 198, 233, 
 211, 128, 247, 245, 
 136, 145, 59, 175, 
 220, 219, 161, 24, 
 202, 59, 223, 186, 
 24, 49, 178, 245, 
 215, 178, 153, 3, 
 251, 215, 24, 169, 
 90, 249, 215, 190, 
 170, 20, 220, 161, 
 208, 212, 24, 117, 
 61, 210, 117, 204, 
 220, 161, 175, 161, 
 69, 138, 204, 159, 
 23, 198, 244, 22, 
 79, 119, 76, 47, 
 76, 24, 202, 219, 
 155, 215, 24, 122, 
 244, 157, 199, 24, 
 42, 90, 219, 186, 
 64, 67, 116, 58, 
 61, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len40_anagram0 = {
  LengthAndAnagram(40, 0), // seq_bit_len_and_anagram
  33, // num_chords
  kmap0_Word_len40_anagram0_chords, // chords
  kmap0_Word_len40_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len40_anagram1_chords[2] = {
 ChordData({54, 8, 192}), ChordData({132, 12, 26}), 
};

const uint8_t kmap0_Word_len40_anagram1_seqs[10] = {
 157, 106, 38, 110, 
 209, 143, 24, 169, 
 190, 22, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len40_anagram1 = {
  LengthAndAnagram(40, 1), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len40_anagram1_chords, // chords
  kmap0_Word_len40_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len40_anagram2_chords[1] = {
 ChordData({22, 4, 19}), 
};

const uint8_t kmap0_Word_len40_anagram2_seqs[5] = {
 95, 235, 24, 251, 
 215, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len40_anagram2 = {
  LengthAndAnagram(40, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len40_anagram2_chords, // chords
  kmap0_Word_len40_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len40_anagram3_chords[1] = {
 ChordData({48, 5, 17}), 
};

const uint8_t kmap0_Word_len40_anagram3_seqs[5] = {
 127, 223, 227, 251, 
 215, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len40_anagram3 = {
  LengthAndAnagram(40, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len40_anagram3_chords, // chords
  kmap0_Word_len40_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len41_anagram0_chords[40] = {
 ChordData({6, 76, 146}), ChordData({16, 44, 11}), ChordData({18, 1, 75}), ChordData({18, 76, 210}), 
 ChordData({20, 76, 25}), ChordData({22, 0, 154}), ChordData({22, 4, 210}), ChordData({22, 12, 153}), 
 ChordData({22, 36, 73}), ChordData({22, 36, 144}), ChordData({22, 64, 202}), ChordData({34, 69, 17}), 
 ChordData({36, 77, 18}), ChordData({50, 8, 89}), ChordData({50, 8, 194}), ChordData({50, 13, 129}), 
 ChordData({50, 65, 25}), ChordData({50, 76, 147}), ChordData({50, 96, 139}), ChordData({54, 5, 129}), 
 ChordData({54, 33, 80}), ChordData({134, 100, 82}), ChordData({146, 12, 146}), ChordData({148, 8, 139}), 
 ChordData({148, 40, 8}), ChordData({148, 64, 90}), ChordData({150, 0, 27}), ChordData({150, 8, 88}), 
 ChordData({150, 12, 131}), ChordData({150, 12, 138}), ChordData({150, 72, 9}), ChordData({160, 4, 147}), 
 ChordData({160, 12, 155}), ChordData({162, 0, 202}), ChordData({162, 8, 27}), ChordData({166, 8, 0}), 
 ChordData({176, 72, 89}), ChordData({178, 64, 210}), ChordData({182, 4, 25}), ChordData({182, 9, 26}), 
};

const uint8_t kmap0_Word_len41_anagram0_seqs[205] = {
 181, 152, 79, 45, 
 159, 126, 247, 17, 
 38, 235, 50, 182, 
 117, 251, 104, 148, 
 205, 72, 223, 201, 
 35, 93, 127, 54, 
 89, 215, 87, 213, 
 211, 86, 180, 185, 
 26, 251, 137, 138, 
 250, 67, 253, 201, 
 186, 128, 215, 21, 
 190, 182, 171, 167, 
 43, 244, 60, 201, 
 102, 236, 74, 173, 
 6, 47, 255, 152, 
 220, 123, 62, 150, 
 46, 63, 178, 149, 
 119, 114, 178, 174, 
 175, 144, 50, 183, 
 104, 242, 221, 219, 
 233, 215, 173, 247, 
 88, 182, 117, 95, 
 10, 24, 183, 69, 
 175, 17, 106, 151, 
 201, 62, 253, 121, 
 251, 200, 52, 62, 
 242, 156, 205, 80, 
 22, 92, 97, 76, 
 63, 70, 74, 30, 
 236, 39, 140, 84, 
 201, 201, 186, 21, 
 90, 35, 89, 67, 
 49, 102, 204, 53, 
 84, 130, 58, 173, 
 232, 13, 173, 158, 
 212, 204, 29, 138, 
 145, 42, 53, 254, 
 26, 35, 85, 234, 
 87, 116, 75, 167, 
 26, 107, 93, 124, 
 194, 76, 191, 49, 
 98, 80, 214, 253, 
 41, 48, 20, 41, 
 115, 135, 98, 164, 
 148, 181, 183, 56, 
 59, 210, 79, 201, 
 179, 227, 100, 149, 
 145, 89, 54, 35, 
 5, 231, 241, 184, 
 230, 253, 237, 208, 
 49, 198, 173, 93, 
 214, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len41_anagram0 = {
  LengthAndAnagram(41, 0), // seq_bit_len_and_anagram
  40, // num_chords
  kmap0_Word_len41_anagram0_chords, // chords
  kmap0_Word_len41_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len41_anagram1_chords[3] = {
 ChordData({34, 13, 24}), ChordData({130, 68, 27}), ChordData({178, 8, 11}), 
};

const uint8_t kmap0_Word_len41_anagram1_seqs[16] = {
 64, 236, 185, 91, 
 251, 49, 116, 231, 
 101, 227, 98, 168, 
 104, 221, 14, 5, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len41_anagram1 = {
  LengthAndAnagram(41, 1), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Word_len41_anagram1_chords, // chords
  kmap0_Word_len41_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len42_anagram0_chords[20] = {
 ChordData({2, 5, 147}), ChordData({2, 65, 2}), ChordData({2, 65, 128}), ChordData({18, 44, 3}), 
 ChordData({18, 65, 26}), ChordData({34, 65, 131}), ChordData({38, 4, 147}), ChordData({48, 12, 131}), 
 ChordData({50, 12, 27}), ChordData({52, 8, 81}), ChordData({52, 8, 201}), ChordData({134, 12, 90}), 
 ChordData({144, 4, 27}), ChordData({146, 65, 9}), ChordData({150, 0, 83}), ChordData({150, 1, 88}), 
 ChordData({150, 8, 82}), ChordData({166, 8, 82}), ChordData({178, 8, 153}), ChordData({182, 0, 27}), 
};

const uint8_t kmap0_Word_len42_anagram0_seqs[105] = {
 63, 219, 71, 99, 
 63, 201, 62, 14, 
 143, 21, 45, 251, 
 56, 26, 51, 109, 
 250, 133, 78, 191, 
 141, 178, 143, 195, 
 99, 69, 203, 62, 
 142, 198, 76, 91, 
 127, 182, 49, 211, 
 207, 35, 230, 148, 
 233, 215, 162, 215, 
 211, 250, 83, 0, 
 118, 93, 167, 211, 
 195, 185, 86, 114, 
 178, 46, 70, 170, 
 63, 205, 161, 24, 
 138, 214, 157, 95, 
 75, 31, 173, 189, 
 29, 58, 174, 193, 
 189, 49, 69, 157, 
 56, 204, 220, 161, 
 24, 169, 78, 164, 
 102, 115, 145, 106, 
 112, 231, 52, 22, 
 131, 242, 118, 40, 
 134, 238, 244, 153, 
 215, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len42_anagram0 = {
  LengthAndAnagram(42, 0), // seq_bit_len_and_anagram
  20, // num_chords
  kmap0_Word_len42_anagram0_chords, // chords
  kmap0_Word_len42_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len42_anagram1_chords[2] = {
 ChordData({32, 8, 18}), ChordData({134, 0, 25}), 
};

const uint8_t kmap0_Word_len42_anagram1_seqs[11] = {
 160, 0, 9, 36, 
 32, 214, 137, 26, 
 179, 29, 10, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len42_anagram1 = {
  LengthAndAnagram(42, 1), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len42_anagram1_chords, // chords
  kmap0_Word_len42_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len43_anagram0_chords[24] = {
 ChordData({0, 44, 9}), ChordData({18, 12, 11}), ChordData({22, 8, 155}), ChordData({48, 12, 155}), 
 ChordData({48, 13, 129}), ChordData({52, 5, 18}), ChordData({52, 12, 152}), ChordData({54, 0, 65}), 
 ChordData({54, 4, 130}), ChordData({54, 64, 81}), ChordData({130, 68, 27}), ChordData({134, 4, 90}), 
 ChordData({134, 44, 194}), ChordData({134, 68, 73}), ChordData({144, 32, 211}), ChordData({146, 4, 139}), 
 ChordData({146, 4, 155}), ChordData({146, 36, 147}), ChordData({160, 37, 153}), ChordData({166, 4, 137}), 
 ChordData({166, 12, 73}), ChordData({180, 5, 136}), ChordData({182, 12, 131}), ChordData({182, 76, 130}), 
};

const uint8_t kmap0_Word_len43_anagram0_seqs[129] = {
 32, 189, 194, 223, 
 125, 77, 223, 186, 
 214, 87, 180, 175, 
 170, 167, 147, 117, 
 45, 90, 55, 63, 
 81, 241, 233, 233, 
 254, 244, 107, 112, 
 248, 156, 252, 83, 
 136, 153, 212, 243, 
 39, 153, 243, 201, 
 219, 155, 215, 95, 
 43, 53, 254, 73, 
 150, 205, 59, 125, 
 230, 181, 108, 220, 
 14, 253, 41, 48, 
 148, 107, 207, 99, 
 241, 136, 145, 42, 
 53, 67, 217, 252, 
 181, 70, 235, 34, 
 12, 50, 175, 39, 
 200, 87, 216, 251, 
 219, 161, 24, 51, 
 166, 223, 14, 93, 
 232, 24, 111, 227, 
 83, 204, 194, 184, 
 67, 159, 106, 212, 
 76, 191, 29, 250, 
 204, 57, 213, 237, 
 208, 211, 127, 147, 
 207, 80, 99, 164, 
 250, 219, 39, 249, 
 236, 72, 150, 141, 
 79, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len43_anagram0 = {
  LengthAndAnagram(43, 0), // seq_bit_len_and_anagram
  24, // num_chords
  kmap0_Word_len43_anagram0_chords, // chords
  kmap0_Word_len43_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len44_anagram0_chords[18] = {
 ChordData({2, 100, 83}), ChordData({4, 4, 82}), ChordData({18, 5, 19}), ChordData({34, 8, 146}), 
 ChordData({48, 65, 154}), ChordData({50, 1, 75}), ChordData({50, 1, 137}), ChordData({50, 8, 91}), 
 ChordData({50, 12, 131}), ChordData({50, 12, 153}), ChordData({50, 13, 80}), ChordData({52, 12, 17}), 
 ChordData({128, 0, 66}), ChordData({130, 4, 203}), ChordData({144, 76, 89}), ChordData({146, 12, 11}), 
 ChordData({146, 68, 73}), ChordData({180, 13, 16}), 
};

const uint8_t kmap0_Word_len44_anagram0_seqs[99] = {
 178, 224, 159, 133, 
 211, 15, 6, 32, 
 16, 106, 192, 232, 
 217, 62, 26, 127, 
 141, 121, 166, 49, 
 83, 78, 199, 184, 
 76, 182, 98, 193, 
 249, 56, 26, 219, 
 186, 173, 107, 162, 
 190, 173, 155, 181, 
 69, 15, 247, 22, 
 152, 83, 166, 223, 
 22, 253, 180, 30, 
 253, 109, 209, 127, 
 223, 99, 230, 22, 
 189, 78, 213, 243, 
 155, 199, 193, 216, 
 68, 191, 29, 26, 
 140, 77, 244, 219, 
 161, 210, 41, 148, 
 119, 126, 141, 161, 
 251, 169, 245, 215, 
 210, 188, 173, 191, 
 29, 90, 39, 238, 
 249, 148, 60, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len44_anagram0 = {
  LengthAndAnagram(44, 0), // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_Word_len44_anagram0_chords, // chords
  kmap0_Word_len44_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len44_anagram1_chords[1] = {
 ChordData({2, 100, 83}), 
};

const uint8_t kmap0_Word_len44_anagram1_seqs[6] = {
 178, 224, 159, 133, 
 211, 8, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len44_anagram1 = {
  LengthAndAnagram(44, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len44_anagram1_chords, // chords
  kmap0_Word_len44_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len45_anagram0_chords[18] = {
 ChordData({0, 4, 145}), ChordData({2, 4, 66}), ChordData({4, 4, 66}), ChordData({18, 108, 90}), 
 ChordData({22, 4, 19}), ChordData({34, 76, 136}), ChordData({50, 5, 17}), ChordData({50, 8, 8}), 
 ChordData({52, 4, 211}), ChordData({54, 8, 83}), ChordData({144, 0, 89}), ChordData({146, 4, 147}), 
 ChordData({150, 8, 11}), ChordData({178, 8, 25}), ChordData({178, 8, 75}), ChordData({178, 68, 153}), 
 ChordData({180, 4, 147}), ChordData({182, 0, 216}), 
};

const uint8_t kmap0_Word_len45_anagram0_seqs[102] = {
 59, 47, 96, 220, 
 152, 2, 60, 96, 
 128, 160, 65, 131, 
 10, 16, 8, 53, 
 224, 228, 65, 248, 
 42, 155, 93, 127, 
 182, 177, 235, 175, 
 91, 101, 139, 45, 
 243, 211, 248, 152, 
 190, 61, 191, 182, 
 138, 61, 161, 201, 
 186, 92, 141, 251, 
 152, 233, 167, 122, 
 184, 26, 183, 69, 
 175, 121, 131, 215, 
 19, 106, 95, 97, 
 239, 111, 76, 129, 
 145, 170, 183, 183, 
 67, 173, 98, 79, 
 104, 178, 46, 134, 
 178, 49, 111, 139, 
 46, 147, 127, 61, 
 218, 161, 24, 68, 
 127, 198, 252, 122, 
 204, 53, 148, 251, 
 36, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len45_anagram0 = {
  LengthAndAnagram(45, 0), // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_Word_len45_anagram0_chords, // chords
  kmap0_Word_len45_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len45_anagram3_chords[1] = {
 ChordData({38, 4, 147}), 
};

const uint8_t kmap0_Word_len45_anagram3_seqs[6] = {
 248, 245, 207, 166, 
 222, 2, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len45_anagram3 = {
  LengthAndAnagram(45, 3), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len45_anagram3_chords, // chords
  kmap0_Word_len45_anagram3_seqs, // sequences
};

const ChordData kmap0_Word_len46_anagram0_chords[16] = {
 ChordData({2, 8, 73}), ChordData({6, 4, 27}), ChordData({6, 36, 83}), ChordData({38, 68, 82}), 
 ChordData({50, 76, 137}), ChordData({52, 0, 25}), ChordData({134, 4, 139}), ChordData({134, 32, 210}), 
 ChordData({144, 76, 3}), ChordData({146, 1, 11}), ChordData({148, 13, 26}), ChordData({150, 4, 17}), 
 ChordData({150, 4, 83}), ChordData({150, 97, 194}), ChordData({160, 8, 2}), ChordData({178, 12, 11}), 
};

const uint8_t kmap0_Word_len46_anagram0_seqs[92] = {
 188, 157, 50, 253, 
 118, 104, 253, 217, 
 198, 174, 175, 91, 
 185, 64, 216, 191, 
 83, 112, 62, 185, 
 101, 255, 20, 46, 
 147, 91, 124, 178, 
 174, 117, 199, 117, 
 172, 206, 243, 181, 
 82, 227, 111, 135, 
 86, 216, 20, 28, 
 21, 22, 143, 24, 
 41, 133, 252, 53, 
 134, 143, 163, 177, 
 173, 91, 61, 71, 
 76, 122, 69, 127, 
 173, 19, 117, 250, 
 215, 99, 174, 61, 
 191, 49, 197, 97, 
 162, 184, 48, 236, 
 138, 145, 82, 214, 
 198, 95, 99, 164, 
 148, 181, 241, 215, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len46_anagram0 = {
  LengthAndAnagram(46, 0), // seq_bit_len_and_anagram
  16, // num_chords
  kmap0_Word_len46_anagram0_chords, // chords
  kmap0_Word_len46_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len47_anagram0_chords[15] = {
 ChordData({22, 12, 154}), ChordData({38, 4, 201}), ChordData({50, 5, 147}), ChordData({50, 12, 90}), 
 ChordData({52, 64, 201}), ChordData({130, 5, 154}), ChordData({130, 13, 25}), ChordData({132, 4, 18}), 
 ChordData({150, 4, 19}), ChordData({160, 12, 147}), ChordData({164, 8, 16}), ChordData({164, 12, 146}), 
 ChordData({176, 8, 91}), ChordData({176, 64, 202}), ChordData({182, 72, 26}), 
};

const uint8_t kmap0_Word_len47_anagram0_seqs[89] = {
 117, 76, 157, 90, 
 127, 10, 206, 39, 
 239, 235, 246, 211, 
 223, 211, 152, 105, 
 243, 248, 85, 91, 
 244, 240, 79, 193, 
 249, 100, 151, 201, 
 214, 5, 248, 212, 
 71, 140, 246, 183, 
 30, 49, 233, 183, 
 67, 235, 132, 24, 
 248, 219, 161, 117, 
 162, 78, 123, 127, 
 138, 71, 204, 41, 
 211, 111, 12, 168, 
 19, 98, 75, 43, 
 90, 12, 252, 51, 
 211, 79, 129, 161, 
 59, 33, 122, 184, 
 192, 80, 118, 153, 
 108, 69, 131, 58, 
 33, 182, 180, 162, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len47_anagram0 = {
  LengthAndAnagram(47, 0), // seq_bit_len_and_anagram
  15, // num_chords
  kmap0_Word_len47_anagram0_chords, // chords
  kmap0_Word_len47_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len48_anagram0_chords[3] = {
 ChordData({34, 5, 75}), ChordData({48, 13, 27}), ChordData({50, 13, 11}), 
};

const uint8_t kmap0_Word_len48_anagram0_seqs[18] = {
 220, 183, 246, 209, 
 248, 186, 233, 53, 
 31, 143, 155, 199, 
 233, 111, 237, 163, 
 209, 186, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len48_anagram0 = {
  LengthAndAnagram(48, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_Word_len48_anagram0_chords, // chords
  kmap0_Word_len48_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len49_anagram0_chords[8] = {
 ChordData({18, 76, 91}), ChordData({50, 12, 91}), ChordData({144, 12, 147}), ChordData({150, 36, 67}), 
 ChordData({160, 8, 10}), ChordData({166, 0, 27}), ChordData({166, 0, 211}), ChordData({178, 12, 91}), 
};

const uint8_t kmap0_Word_len49_anagram0_seqs[49] = {
 178, 25, 167, 83, 
 235, 175, 177, 7, 
 115, 226, 125, 69, 
 63, 162, 201, 19, 
 201, 235, 225, 168, 
 176, 121, 27, 127, 
 141, 161, 162, 135, 
 127, 59, 52, 106, 
 141, 217, 172, 189, 
 69, 13, 230, 62, 
 155, 122, 11, 12, 
 21, 61, 252, 219, 
 161, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len49_anagram0 = {
  LengthAndAnagram(49, 0), // seq_bit_len_and_anagram
  8, // num_chords
  kmap0_Word_len49_anagram0_chords, // chords
  kmap0_Word_len49_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len49_anagram1_chords[1] = {
 ChordData({0, 0, 146}), 
};

const uint8_t kmap0_Word_len49_anagram1_seqs[7] = {
 117, 204, 56, 93, 
 183, 67, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len49_anagram1 = {
  LengthAndAnagram(49, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len49_anagram1_chords, // chords
  kmap0_Word_len49_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len50_anagram0_chords[7] = {
 ChordData({2, 13, 0}), ChordData({32, 68, 130}), ChordData({54, 1, 137}), ChordData({150, 12, 147}), 
 ChordData({162, 68, 203}), ChordData({176, 5, 155}), ChordData({178, 12, 201}), 
};

const uint8_t kmap0_Word_len50_anagram0_seqs[44] = {
 224, 193, 1, 30, 
 52, 40, 61, 150, 
 201, 205, 189, 29, 
 218, 186, 38, 234, 
 187, 79, 242, 215, 
 58, 113, 213, 233, 
 215, 143, 101, 114, 
 115, 111, 135, 98, 
 232, 61, 191, 153, 
 126, 205, 157, 50, 
 237, 171, 35, 51, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len50_anagram0 = {
  LengthAndAnagram(50, 0), // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_Word_len50_anagram0_chords, // chords
  kmap0_Word_len50_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len51_anagram0_chords[6] = {
 ChordData({0, 13, 2}), ChordData({6, 8, 1}), ChordData({38, 8, 211}), ChordData({150, 32, 83}), 
 ChordData({164, 0, 17}), ChordData({176, 77, 138}), 
};

const uint8_t kmap0_Word_len51_anagram0_seqs[39] = {
 143, 37, 141, 11, 
 89, 222, 238, 84, 
 51, 113, 139, 189, 
 69, 167, 154, 137, 
 91, 236, 45, 0, 
 194, 105, 222, 168, 
 208, 83, 39, 206, 
 63, 155, 122, 139, 
 199, 146, 198, 133, 
 44, 111, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len51_anagram0 = {
  LengthAndAnagram(51, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_Word_len51_anagram0_chords, // chords
  kmap0_Word_len51_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len51_anagram1_chords[1] = {
 ChordData({128, 0, 10}), 
};

const uint8_t kmap0_Word_len51_anagram1_seqs[7] = {
 24, 170, 198, 109, 
 177, 183, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len51_anagram1 = {
  LengthAndAnagram(51, 1), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len51_anagram1_chords, // chords
  kmap0_Word_len51_anagram1_seqs, // sequences
};

const ChordData kmap0_Word_len52_anagram0_chords[5] = {
 ChordData({32, 40, 66}), ChordData({54, 64, 209}), ChordData({130, 64, 81}), ChordData({166, 64, 89}), 
 ChordData({178, 12, 202}), 
};

const uint8_t kmap0_Word_len52_anagram0_seqs[33] = {
 64, 4, 40, 188, 
 64, 4, 92, 199, 
 227, 50, 185, 185, 
 215, 178, 121, 167, 
 207, 188, 29, 42, 
 155, 119, 250, 204, 
 219, 161, 169, 25, 
 77, 244, 234, 200, 
 12, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len52_anagram0 = {
  LengthAndAnagram(52, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_Word_len52_anagram0_chords, // chords
  kmap0_Word_len52_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len52_anagram2_chords[1] = {
 ChordData({38, 4, 147}), 
};

const uint8_t kmap0_Word_len52_anagram2_seqs[7] = {
 245, 103, 27, 51, 
 253, 80, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len52_anagram2 = {
  LengthAndAnagram(52, 2), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len52_anagram2_chords, // chords
  kmap0_Word_len52_anagram2_seqs, // sequences
};

const ChordData kmap0_Word_len53_anagram0_chords[1] = {
 ChordData({54, 72, 144}), 
};

const uint8_t kmap0_Word_len53_anagram0_seqs[7] = {
 46, 147, 155, 250, 
 156, 206, 9, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len53_anagram0 = {
  LengthAndAnagram(53, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len53_anagram0_chords, // chords
  kmap0_Word_len53_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len57_anagram0_chords[2] = {
 ChordData({22, 76, 219}), ChordData({54, 12, 218}), 
};

const uint8_t kmap0_Word_len57_anagram0_seqs[15] = {
 128, 47, 189, 101, 
 61, 244, 42, 65, 
 181, 42, 23, 36, 
 190, 246, 3, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len57_anagram0 = {
  LengthAndAnagram(57, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_Word_len57_anagram0_chords, // chords
  kmap0_Word_len57_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len58_anagram0_chords[1] = {
 ChordData({34, 5, 219}), 
};

const uint8_t kmap0_Word_len58_anagram0_seqs[8] = {
 220, 183, 246, 209, 
 248, 186, 84, 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len58_anagram0 = {
  LengthAndAnagram(58, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len58_anagram0_chords, // chords
  kmap0_Word_len58_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len60_anagram0_chords[1] = {
 ChordData({182, 0, 219}), 
};

const uint8_t kmap0_Word_len60_anagram0_seqs[8] = {
 99, 174, 161, 220, 
 103, 83, 111, 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len60_anagram0 = {
  LengthAndAnagram(60, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len60_anagram0_chords, // chords
  kmap0_Word_len60_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len65_anagram0_chords[1] = {
 ChordData({164, 36, 9}), 
};

const uint8_t kmap0_Word_len65_anagram0_seqs[9] = {
 224, 4, 10, 66, 
 200, 242, 82, 94, 
 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len65_anagram0 = {
  LengthAndAnagram(65, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len65_anagram0_chords, // chords
  kmap0_Word_len65_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len75_anagram0_chords[1] = {
 ChordData({34, 65, 82}), 
};

const uint8_t kmap0_Word_len75_anagram0_seqs[10] = {
 224, 2, 10, 192, 
 160, 193, 5, 20, 
 224, 6, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len75_anagram0 = {
  LengthAndAnagram(75, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len75_anagram0_chords, // chords
  kmap0_Word_len75_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len97_anagram0_chords[1] = {
 ChordData({2, 5, 0}), 
};

const uint8_t kmap0_Word_len97_anagram0_seqs[13] = {
 207, 229, 142, 159, 
 114, 207, 229, 64, 
 151, 43, 105, 92, 
 0, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len97_anagram0 = {
  LengthAndAnagram(97, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len97_anagram0_chords, // chords
  kmap0_Word_len97_anagram0_seqs, // sequences
};

const ChordData kmap0_Word_len100_anagram0_chords[1] = {
 ChordData({16, 1, 144}), 
};

const uint8_t kmap0_Word_len100_anagram0_seqs[13] = {
 227, 131, 140, 219, 
 161, 229, 58, 213, 
 76, 220, 98, 111, 
 1, 
};

const LookupKmapTypeLenAnagram kmap0_Word_len100_anagram0 = {
  LengthAndAnagram(100, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_Word_len100_anagram0_chords, // chords
  kmap0_Word_len100_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap0_Word_lookups_array[174] = {
 &kmap0_Word_len4_anagram1, &kmap0_Word_len5_anagram1, &kmap0_Word_len7_anagram0, &kmap0_Word_len7_anagram1, 
 &kmap0_Word_len8_anagram0, &kmap0_Word_len8_anagram1, &kmap0_Word_len9_anagram0, &kmap0_Word_len9_anagram1, 
 &kmap0_Word_len9_anagram2, &kmap0_Word_len10_anagram0, &kmap0_Word_len10_anagram1, &kmap0_Word_len10_anagram2, 
 &kmap0_Word_len10_anagram3, &kmap0_Word_len10_anagram4, &kmap0_Word_len11_anagram0, &kmap0_Word_len11_anagram1, 
 &kmap0_Word_len11_anagram2, &kmap0_Word_len11_anagram3, &kmap0_Word_len11_anagram4, &kmap0_Word_len12_anagram0, 
 &kmap0_Word_len12_anagram1, &kmap0_Word_len12_anagram2, &kmap0_Word_len12_anagram3, &kmap0_Word_len13_anagram0, 
 &kmap0_Word_len13_anagram1, &kmap0_Word_len13_anagram2, &kmap0_Word_len13_anagram3, &kmap0_Word_len14_anagram0, 
 &kmap0_Word_len14_anagram1, &kmap0_Word_len14_anagram2, &kmap0_Word_len14_anagram3, &kmap0_Word_len14_anagram4, 
 &kmap0_Word_len15_anagram0, &kmap0_Word_len15_anagram1, &kmap0_Word_len15_anagram2, &kmap0_Word_len15_anagram3, 
 &kmap0_Word_len15_anagram4, &kmap0_Word_len15_anagram5, &kmap0_Word_len15_anagram7, &kmap0_Word_len16_anagram0, 
 &kmap0_Word_len16_anagram1, &kmap0_Word_len16_anagram2, &kmap0_Word_len16_anagram3, &kmap0_Word_len17_anagram0, 
 &kmap0_Word_len17_anagram1, &kmap0_Word_len17_anagram2, &kmap0_Word_len17_anagram3, &kmap0_Word_len17_anagram5, 
 &kmap0_Word_len18_anagram0, &kmap0_Word_len18_anagram1, &kmap0_Word_len18_anagram2, &kmap0_Word_len18_anagram3, 
 &kmap0_Word_len19_anagram0, &kmap0_Word_len19_anagram1, &kmap0_Word_len19_anagram2, &kmap0_Word_len19_anagram3, 
 &kmap0_Word_len19_anagram4, &kmap0_Word_len20_anagram0, &kmap0_Word_len20_anagram1, &kmap0_Word_len20_anagram2, 
 &kmap0_Word_len20_anagram3, &kmap0_Word_len20_anagram4, &kmap0_Word_len20_anagram6, &kmap0_Word_len21_anagram0, 
 &kmap0_Word_len21_anagram1, &kmap0_Word_len21_anagram2, &kmap0_Word_len21_anagram3, &kmap0_Word_len21_anagram4, 
 &kmap0_Word_len21_anagram5, &kmap0_Word_len22_anagram0, &kmap0_Word_len22_anagram1, &kmap0_Word_len22_anagram2, 
 &kmap0_Word_len22_anagram3, &kmap0_Word_len22_anagram4, &kmap0_Word_len22_anagram5, &kmap0_Word_len22_anagram6, 
 &kmap0_Word_len23_anagram0, &kmap0_Word_len23_anagram1, &kmap0_Word_len23_anagram2, &kmap0_Word_len23_anagram3, 
 &kmap0_Word_len24_anagram0, &kmap0_Word_len24_anagram1, &kmap0_Word_len24_anagram2, &kmap0_Word_len24_anagram3, 
 &kmap0_Word_len24_anagram4, &kmap0_Word_len24_anagram5, &kmap0_Word_len24_anagram6, &kmap0_Word_len25_anagram0, 
 &kmap0_Word_len25_anagram1, &kmap0_Word_len25_anagram2, &kmap0_Word_len25_anagram3, &kmap0_Word_len25_anagram4, 
 &kmap0_Word_len26_anagram0, &kmap0_Word_len26_anagram1, &kmap0_Word_len26_anagram2, &kmap0_Word_len26_anagram3, 
 &kmap0_Word_len26_anagram4, &kmap0_Word_len27_anagram0, &kmap0_Word_len27_anagram1, &kmap0_Word_len27_anagram2, 
 &kmap0_Word_len27_anagram3, &kmap0_Word_len27_anagram7, &kmap0_Word_len28_anagram0, &kmap0_Word_len28_anagram1, 
 &kmap0_Word_len28_anagram2, &kmap0_Word_len28_anagram3, &kmap0_Word_len28_anagram4, &kmap0_Word_len29_anagram0, 
 &kmap0_Word_len29_anagram1, &kmap0_Word_len29_anagram2, &kmap0_Word_len30_anagram0, &kmap0_Word_len30_anagram1, 
 &kmap0_Word_len30_anagram2, &kmap0_Word_len30_anagram3, &kmap0_Word_len31_anagram0, &kmap0_Word_len31_anagram1, 
 &kmap0_Word_len31_anagram2, &kmap0_Word_len31_anagram3, &kmap0_Word_len32_anagram0, &kmap0_Word_len32_anagram1, 
 &kmap0_Word_len32_anagram2, &kmap0_Word_len33_anagram0, &kmap0_Word_len33_anagram1, &kmap0_Word_len33_anagram2, 
 &kmap0_Word_len33_anagram3, &kmap0_Word_len34_anagram0, &kmap0_Word_len34_anagram1, &kmap0_Word_len34_anagram2, 
 &kmap0_Word_len34_anagram4, &kmap0_Word_len35_anagram0, &kmap0_Word_len35_anagram1, &kmap0_Word_len35_anagram2, 
 &kmap0_Word_len36_anagram0, &kmap0_Word_len36_anagram1, &kmap0_Word_len36_anagram2, &kmap0_Word_len37_anagram0, 
 &kmap0_Word_len37_anagram1, &kmap0_Word_len37_anagram2, &kmap0_Word_len38_anagram0, &kmap0_Word_len38_anagram1, 
 &kmap0_Word_len38_anagram2, &kmap0_Word_len39_anagram0, &kmap0_Word_len39_anagram1, &kmap0_Word_len40_anagram0, 
 &kmap0_Word_len40_anagram1, &kmap0_Word_len40_anagram2, &kmap0_Word_len40_anagram3, &kmap0_Word_len41_anagram0, 
 &kmap0_Word_len41_anagram1, &kmap0_Word_len42_anagram0, &kmap0_Word_len42_anagram1, &kmap0_Word_len43_anagram0, 
 &kmap0_Word_len44_anagram0, &kmap0_Word_len44_anagram1, &kmap0_Word_len45_anagram0, &kmap0_Word_len45_anagram3, 
 &kmap0_Word_len46_anagram0, &kmap0_Word_len47_anagram0, &kmap0_Word_len48_anagram0, &kmap0_Word_len49_anagram0, 
 &kmap0_Word_len49_anagram1, &kmap0_Word_len50_anagram0, &kmap0_Word_len51_anagram0, &kmap0_Word_len51_anagram1, 
 &kmap0_Word_len52_anagram0, &kmap0_Word_len52_anagram2, &kmap0_Word_len53_anagram0, &kmap0_Word_len57_anagram0, 
 &kmap0_Word_len58_anagram0, &kmap0_Word_len60_anagram0, &kmap0_Word_len65_anagram0, &kmap0_Word_len75_anagram0, 
 &kmap0_Word_len97_anagram0, &kmap0_Word_len100_anagram0, 
};

const LookupKmapType kmap0_Word_lookups = {
  174, // num_lookups
  kmap0_Word_lookups_array, // lookups
};

const LookupKmapType* kmap0_lookups_array[4] = {
 &kmap0_Plain_lookups, &kmap0_Macro_lookups, &kmap0_Command_lookups, &kmap0_Word_lookups, 
};

const KmapStruct kmap0_lookups = {
  kmap0_lookups_array, // lookups_for_kmap
};

const ChordData kmap1_Plain_len3_anagram0_chords[1] = {
 ChordData({4, 0, 0}), 
};

const uint8_t kmap1_Plain_len3_anagram0_seqs[1] = {
 6, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len3_anagram0 = {
  LengthAndAnagram(3, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len3_anagram0_chords, // chords
  kmap1_Plain_len3_anagram0_seqs, // sequences
};

const ChordData kmap1_Plain_len4_anagram0_chords[2] = {
 ChordData({16, 0, 0}), ChordData({128, 0, 0}), 
};

const uint8_t kmap1_Plain_len4_anagram0_seqs[1] = {
 252, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len4_anagram0 = {
  LengthAndAnagram(4, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap1_Plain_len4_anagram0_chords, // chords
  kmap1_Plain_len4_anagram0_seqs, // sequences
};

const ChordData kmap1_Plain_len5_anagram0_chords[1] = {
 ChordData({2, 0, 0}), 
};

const uint8_t kmap1_Plain_len5_anagram0_seqs[1] = {
 18, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len5_anagram0 = {
  LengthAndAnagram(5, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len5_anagram0_chords, // chords
  kmap1_Plain_len5_anagram0_seqs, // sequences
};

const ChordData kmap1_Plain_len7_anagram0_chords[1] = {
 ChordData({32, 0, 0}), 
};

const uint8_t kmap1_Plain_len7_anagram0_seqs[1] = {
 23, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len7_anagram0_chords, // chords
  kmap1_Plain_len7_anagram0_seqs, // sequences
};

const ChordData kmap1_Plain_len9_anagram0_chords[2] = {
 ChordData({0, 1, 0}), ChordData({8, 0, 0}), 
};

const uint8_t kmap1_Plain_len9_anagram0_seqs[3] = {
 101, 202, 1, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap1_Plain_len9_anagram0_chords, // chords
  kmap1_Plain_len9_anagram0_seqs, // sequences
};

const ChordData kmap1_Plain_len14_anagram0_chords[1] = {
 ChordData({0, 8, 0}), 
};

const uint8_t kmap1_Plain_len14_anagram0_seqs[2] = {
 215, 4, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len14_anagram0_chords, // chords
  kmap1_Plain_len14_anagram0_seqs, // sequences
};

const ChordData kmap1_Plain_len18_anagram0_chords[1] = {
 ChordData({0, 4, 0}), 
};

const uint8_t kmap1_Plain_len18_anagram0_seqs[3] = {
 224, 154, 1, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len18_anagram0_chords, // chords
  kmap1_Plain_len18_anagram0_seqs, // sequences
};

const ChordData kmap1_Plain_len25_anagram0_chords[1] = {
 ChordData({1, 0, 0}), 
};

const uint8_t kmap1_Plain_len25_anagram0_seqs[4] = {
 229, 115, 205, 0, 
};

const LookupKmapTypeLenAnagram kmap1_Plain_len25_anagram0 = {
  LengthAndAnagram(25, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Plain_len25_anagram0_chords, // chords
  kmap1_Plain_len25_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap1_Plain_lookups_array[8] = {
 &kmap1_Plain_len3_anagram0, &kmap1_Plain_len4_anagram0, &kmap1_Plain_len5_anagram0, &kmap1_Plain_len7_anagram0, 
 &kmap1_Plain_len9_anagram0, &kmap1_Plain_len14_anagram0, &kmap1_Plain_len18_anagram0, &kmap1_Plain_len25_anagram0, 
};

const LookupKmapType kmap1_Plain_lookups = {
  8, // num_lookups
  kmap1_Plain_lookups_array, // lookups
};

const LookupKmapTypeLenAnagram* kmap1_Macro_lookups_array[0] = {
};

const LookupKmapType kmap1_Macro_lookups = {
  0, // num_lookups
  kmap1_Macro_lookups_array, // lookups
};

const ChordData kmap1_Command_len28_anagram0_chords[1] = {
 ChordData({0, 0, 1}), 
};

const uint8_t kmap1_Command_len28_anagram0_seqs[4] = {
 215, 224, 26, 3, 
};

const LookupKmapTypeLenAnagram kmap1_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_Command_len28_anagram0_chords, // chords
  kmap1_Command_len28_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap1_Command_lookups_array[1] = {
 &kmap1_Command_len28_anagram0, 
};

const LookupKmapType kmap1_Command_lookups = {
  1, // num_lookups
  kmap1_Command_lookups_array, // lookups
};

const LookupKmapTypeLenAnagram* kmap1_Word_lookups_array[0] = {
};

const LookupKmapType kmap1_Word_lookups = {
  0, // num_lookups
  kmap1_Word_lookups_array, // lookups
};

const LookupKmapType* kmap1_lookups_array[4] = {
 &kmap1_Plain_lookups, &kmap1_Macro_lookups, &kmap1_Command_lookups, &kmap1_Word_lookups, 
};

const KmapStruct kmap1_lookups = {
  kmap1_lookups_array, // lookups_for_kmap
};

const ChordData kmap2_Plain_len3_anagram0_chords[1] = {
 ChordData({16, 0, 0}), 
};

const uint8_t kmap2_Plain_len3_anagram0_seqs[1] = {
 6, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len3_anagram0 = {
  LengthAndAnagram(3, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Plain_len3_anagram0_chords, // chords
  kmap2_Plain_len3_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len4_anagram0_chords[9] = {
 ChordData({0, 4, 0}), ChordData({2, 0, 0}), ChordData({64, 1, 0}), ChordData({64, 4, 0}), 
 ChordData({64, 8, 0}), ChordData({80, 0, 0}), ChordData({96, 0, 0}), ChordData({128, 0, 0}), 
 ChordData({192, 0, 0}), 
};

const uint8_t kmap2_Plain_len4_anagram0_seqs[5] = {
 223, 195, 180, 24, 
 10, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len4_anagram0 = {
  LengthAndAnagram(4, 0), // seq_bit_len_and_anagram
  9, // num_chords
  kmap2_Plain_len4_anagram0_chords, // chords
  kmap2_Plain_len4_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len5_anagram0_chords[5] = {
 ChordData({0, 8, 0}), ChordData({4, 0, 0}), ChordData({32, 0, 0}), ChordData({66, 0, 0}), 
 ChordData({68, 0, 0}), 
};

const uint8_t kmap2_Plain_len5_anagram0_seqs[4] = {
 169, 102, 40, 1, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len5_anagram0 = {
  LengthAndAnagram(5, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_Plain_len5_anagram0_chords, // chords
  kmap2_Plain_len5_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len6_anagram0_chords[5] = {
 ChordData({0, 1, 0}), ChordData({32, 1, 0}), ChordData({32, 8, 0}), ChordData({36, 0, 0}), 
 ChordData({96, 1, 0}), 
};

const uint8_t kmap2_Plain_len6_anagram0_seqs[4] = {
 199, 45, 158, 5, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len6_anagram0 = {
  LengthAndAnagram(6, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_Plain_len6_anagram0_chords, // chords
  kmap2_Plain_len6_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len7_anagram0_chords[2] = {
 ChordData({0, 9, 0}), ChordData({100, 0, 0}), 
};

const uint8_t kmap2_Plain_len7_anagram0_seqs[2] = {
 165, 11, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len7_anagram0 = {
  LengthAndAnagram(7, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len7_anagram0_chords, // chords
  kmap2_Plain_len7_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len8_anagram0_chords[2] = {
 ChordData({64, 9, 0}), ChordData({96, 8, 0}), 
};

const uint8_t kmap2_Plain_len8_anagram0_seqs[2] = {
 2, 87, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len8_anagram0 = {
  LengthAndAnagram(8, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len8_anagram0_chords, // chords
  kmap2_Plain_len8_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len9_anagram0_chords[5] = {
 ChordData({4, 8, 0}), ChordData({33, 0, 0}), ChordData({64, 0, 0}), ChordData({66, 8, 0}), 
 ChordData({68, 8, 0}), 
};

const uint8_t kmap2_Plain_len9_anagram0_seqs[6] = {
 101, 175, 151, 19, 
 92, 6, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len9_anagram0 = {
  LengthAndAnagram(9, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_Plain_len9_anagram0_chords, // chords
  kmap2_Plain_len9_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len10_anagram0_chords[5] = {
 ChordData({1, 0, 0}), ChordData({16, 4, 0}), ChordData({64, 2, 0}), ChordData({68, 1, 0}), 
 ChordData({82, 0, 0}), 
};

const uint8_t kmap2_Plain_len10_anagram0_seqs[7] = {
 194, 9, 33, 136, 
 48, 66, 2, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len10_anagram0 = {
  LengthAndAnagram(10, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_Plain_len10_anagram0_chords, // chords
  kmap2_Plain_len10_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len11_anagram0_chords[5] = {
 ChordData({1, 1, 0}), ChordData({4, 1, 0}), ChordData({34, 0, 0}), ChordData({66, 1, 0}), 
 ChordData({196, 0, 0}), 
};

const uint8_t kmap2_Plain_len11_anagram0_seqs[7] = {
 66, 185, 150, 160, 
 4, 45, 124, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len11_anagram0 = {
  LengthAndAnagram(11, 0), // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_Plain_len11_anagram0_chords, // chords
  kmap2_Plain_len11_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len12_anagram0_chords[8] = {
 ChordData({18, 0, 0}), ChordData({19, 0, 0}), ChordData({68, 4, 0}), ChordData({98, 0, 0}), 
 ChordData({130, 0, 0}), ChordData({144, 0, 0}), ChordData({192, 4, 0}), ChordData({208, 0, 0}), 
};

const uint8_t kmap2_Plain_len12_anagram0_seqs[12] = {
 229, 91, 158, 66, 
 45, 188, 194, 115, 
 237, 66, 117, 109, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len12_anagram0 = {
  LengthAndAnagram(12, 0), // seq_bit_len_and_anagram
  8, // num_chords
  kmap2_Plain_len12_anagram0_chords, // chords
  kmap2_Plain_len12_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len13_anagram0_chords[2] = {
 ChordData({64, 5, 0}), ChordData({128, 4, 0}), 
};

const uint8_t kmap2_Plain_len13_anagram0_seqs[4] = {
 229, 167, 188, 0, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len13_anagram0 = {
  LengthAndAnagram(13, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len13_anagram0_chords, // chords
  kmap2_Plain_len13_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len14_anagram0_chords[6] = {
 ChordData({2, 8, 0}), ChordData({6, 0, 0}), ChordData({48, 0, 0}), ChordData({80, 4, 0}), 
 ChordData({128, 8, 0}), ChordData({194, 0, 0}), 
};

const uint8_t kmap2_Plain_len14_anagram0_seqs[11] = {
 64, 112, 121, 84, 
 30, 95, 115, 215, 
 196, 53, 15, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len14_anagram0 = {
  LengthAndAnagram(14, 0), // seq_bit_len_and_anagram
  6, // num_chords
  kmap2_Plain_len14_anagram0_chords, // chords
  kmap2_Plain_len14_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len15_anagram0_chords[15] = {
 ChordData({0, 2, 0}), ChordData({1, 8, 0}), ChordData({5, 0, 0}), ChordData({8, 0, 0}), 
 ChordData({16, 5, 0}), ChordData({18, 1, 0}), ChordData({54, 0, 0}), ChordData({80, 5, 0}), 
 ChordData({128, 5, 0}), ChordData({128, 13, 0}), ChordData({130, 1, 0}), ChordData({144, 1, 0}), 
 ChordData({192, 5, 0}), ChordData({194, 1, 0}), ChordData({208, 1, 0}), 
};

const uint8_t kmap2_Plain_len15_anagram0_seqs[29] = {
 229, 255, 242, 215, 
 53, 181, 188, 121, 
 13, 41, 191, 151, 
 183, 174, 97, 215, 
 240, 107, 74, 249, 
 243, 26, 93, 126, 
 43, 191, 148, 119, 
 0, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  15, // num_chords
  kmap2_Plain_len15_anagram0_chords, // chords
  kmap2_Plain_len15_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len16_anagram0_chords[3] = {
 ChordData({2, 1, 0}), ChordData({16, 1, 0}), ChordData({132, 0, 0}), 
};

const uint8_t kmap2_Plain_len16_anagram0_seqs[6] = {
 64, 208, 64, 80, 
 64, 248, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len16_anagram0 = {
  LengthAndAnagram(16, 0), // seq_bit_len_and_anagram
  3, // num_chords
  kmap2_Plain_len16_anagram0_chords, // chords
  kmap2_Plain_len16_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len17_anagram0_chords[7] = {
 ChordData({2, 4, 0}), ChordData({4, 4, 0}), ChordData({32, 4, 0}), ChordData({66, 4, 0}), 
 ChordData({80, 1, 0}), ChordData({84, 0, 0}), ChordData({96, 4, 0}), 
};

const uint8_t kmap2_Plain_len17_anagram0_seqs[15] = {
 160, 124, 129, 80, 
 131, 107, 3, 194, 
 11, 132, 7, 8, 
 21, 184, 118, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len17_anagram0 = {
  LengthAndAnagram(17, 0), // seq_bit_len_and_anagram
  7, // num_chords
  kmap2_Plain_len17_anagram0_chords, // chords
  kmap2_Plain_len17_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len18_anagram0_chords[2] = {
 ChordData({0, 5, 0}), ChordData({224, 0, 0}), 
};

const uint8_t kmap2_Plain_len18_anagram0_seqs[5] = {
 160, 252, 128, 242, 
 2, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len18_anagram0 = {
  LengthAndAnagram(18, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len18_anagram0_chords, // chords
  kmap2_Plain_len18_anagram0_seqs, // sequences
};

const ChordData kmap2_Plain_len19_anagram0_chords[2] = {
 ChordData({20, 0, 0}), ChordData({160, 0, 0}), 
};

const uint8_t kmap2_Plain_len19_anagram0_seqs[5] = {
 224, 154, 7, 215, 
 28, 
};

const LookupKmapTypeLenAnagram kmap2_Plain_len19_anagram0 = {
  LengthAndAnagram(19, 0), // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_Plain_len19_anagram0_chords, // chords
  kmap2_Plain_len19_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap2_Plain_lookups_array[17] = {
 &kmap2_Plain_len3_anagram0, &kmap2_Plain_len4_anagram0, &kmap2_Plain_len5_anagram0, &kmap2_Plain_len6_anagram0, 
 &kmap2_Plain_len7_anagram0, &kmap2_Plain_len8_anagram0, &kmap2_Plain_len9_anagram0, &kmap2_Plain_len10_anagram0, 
 &kmap2_Plain_len11_anagram0, &kmap2_Plain_len12_anagram0, &kmap2_Plain_len13_anagram0, &kmap2_Plain_len14_anagram0, 
 &kmap2_Plain_len15_anagram0, &kmap2_Plain_len16_anagram0, &kmap2_Plain_len17_anagram0, &kmap2_Plain_len18_anagram0, 
 &kmap2_Plain_len19_anagram0, 
};

const LookupKmapType kmap2_Plain_lookups = {
  17, // num_lookups
  kmap2_Plain_lookups_array, // lookups
};

const LookupKmapTypeLenAnagram* kmap2_Macro_lookups_array[0] = {
};

const LookupKmapType kmap2_Macro_lookups = {
  0, // num_lookups
  kmap2_Macro_lookups_array, // lookups
};

const ChordData kmap2_Command_len15_anagram0_chords[4] = {
 ChordData({1, 4, 0}), ChordData({3, 0, 0}), ChordData({17, 0, 0}), ChordData({129, 0, 0}), 
};

const uint8_t kmap2_Command_len15_anagram0_seqs[8] = {
 229, 141, 242, 112, 
 121, 168, 252, 7, 
};

const LookupKmapTypeLenAnagram kmap2_Command_len15_anagram0 = {
  LengthAndAnagram(15, 0), // seq_bit_len_and_anagram
  4, // num_chords
  kmap2_Command_len15_anagram0_chords, // chords
  kmap2_Command_len15_anagram0_seqs, // sequences
};

const ChordData kmap2_Command_len28_anagram0_chords[1] = {
 ChordData({16, 0, 1}), 
};

const uint8_t kmap2_Command_len28_anagram0_seqs[4] = {
 215, 224, 26, 3, 
};

const LookupKmapTypeLenAnagram kmap2_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_Command_len28_anagram0_chords, // chords
  kmap2_Command_len28_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap2_Command_lookups_array[2] = {
 &kmap2_Command_len15_anagram0, &kmap2_Command_len28_anagram0, 
};

const LookupKmapType kmap2_Command_lookups = {
  2, // num_lookups
  kmap2_Command_lookups_array, // lookups
};

const LookupKmapTypeLenAnagram* kmap2_Word_lookups_array[0] = {
};

const LookupKmapType kmap2_Word_lookups = {
  0, // num_lookups
  kmap2_Word_lookups_array, // lookups
};

const LookupKmapType* kmap2_lookups_array[4] = {
 &kmap2_Plain_lookups, &kmap2_Macro_lookups, &kmap2_Command_lookups, &kmap2_Word_lookups, 
};

const KmapStruct kmap2_lookups = {
  kmap2_lookups_array, // lookups_for_kmap
};

const LookupKmapTypeLenAnagram* kmap3_Plain_lookups_array[0] = {
};

const LookupKmapType kmap3_Plain_lookups = {
  0, // num_lookups
  kmap3_Plain_lookups_array, // lookups
};

const LookupKmapTypeLenAnagram* kmap3_Macro_lookups_array[0] = {
};

const LookupKmapType kmap3_Macro_lookups = {
  0, // num_lookups
  kmap3_Macro_lookups_array, // lookups
};

const ChordData kmap3_Command_len28_anagram0_chords[1] = {
 ChordData({36, 9, 0}), 
};

const uint8_t kmap3_Command_len28_anagram0_seqs[4] = {
 215, 224, 26, 3, 
};

const LookupKmapTypeLenAnagram kmap3_Command_len28_anagram0 = {
  LengthAndAnagram(28, 0), // seq_bit_len_and_anagram
  1, // num_chords
  kmap3_Command_len28_anagram0_chords, // chords
  kmap3_Command_len28_anagram0_seqs, // sequences
};

const LookupKmapTypeLenAnagram* kmap3_Command_lookups_array[1] = {
 &kmap3_Command_len28_anagram0, 
};

const LookupKmapType kmap3_Command_lookups = {
  1, // num_lookups
  kmap3_Command_lookups_array, // lookups
};

const LookupKmapTypeLenAnagram* kmap3_Word_lookups_array[0] = {
};

const LookupKmapType kmap3_Word_lookups = {
  0, // num_lookups
  kmap3_Word_lookups_array, // lookups
};

const LookupKmapType* kmap3_lookups_array[4] = {
 &kmap3_Plain_lookups, &kmap3_Macro_lookups, &kmap3_Command_lookups, &kmap3_Word_lookups, 
};

const KmapStruct kmap3_lookups = {
  kmap3_lookups_array, // lookups_for_kmap
};

const KmapStruct* default_mode_kmaps_array[1] = {
 &kmap0_lookups, 
};

const ChordData default_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

const ChordData default_mode_anagram_mask = ChordData({8, 128, 0});

const ModeStruct default_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  default_mode_kmaps_array, // kmaps
  default_mode_mod_chord, // mod_chords
  default_mode_anagram_mask, // anagram_mask
};

const KmapStruct* gaming_mode_kmaps_array[1] = {
 &kmap1_lookups, 
};

const ChordData gaming_mode_mod_chord[10] = {
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({0, 4, 0}), ChordData({0, 0, 0}), 
};

const ChordData gaming_mode_anagram_mask = ChordData({0, 0, 0});

const ModeStruct gaming_mode_struct = {
  1, // is_gaming
  1, // num_kmaps
  gaming_mode_kmaps_array, // kmaps
  gaming_mode_mod_chord, // mod_chords
  gaming_mode_anagram_mask, // anagram_mask
};

const KmapStruct* left_hand_mode_kmaps_array[1] = {
 &kmap2_lookups, 
};

const ChordData left_hand_mode_mod_chord[10] = {
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
 ChordData({0, 0, 0}), ChordData({0, 0, 0}), 
};

const ChordData left_hand_mode_anagram_mask = ChordData({0, 0, 0});

const ModeStruct left_hand_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  left_hand_mode_kmaps_array, // kmaps
  left_hand_mode_mod_chord, // mod_chords
  left_hand_mode_anagram_mask, // anagram_mask
};

const KmapStruct* windows_mode_kmaps_array[2] = {
 &kmap3_lookups, &kmap0_lookups, 
};

const ChordData windows_mode_mod_chord[10] = {
 ChordData({0, 0, 4}), ChordData({8, 0, 0}), ChordData({8, 128, 0}), ChordData({64, 0, 0}), 
 ChordData({1, 0, 0}), ChordData({1, 0, 0}), ChordData({0, 16, 0}), ChordData({0, 0, 4}), 
 ChordData({64, 0, 0}), ChordData({0, 16, 0}), 
};

const ChordData windows_mode_anagram_mask = ChordData({8, 128, 0});

const ModeStruct windows_mode_struct = {
  0, // is_gaming
  2, // num_kmaps
  windows_mode_kmaps_array, // kmaps
  windows_mode_mod_chord, // mod_chords
  windows_mode_anagram_mask, // anagram_mask
};

const ModeStruct* mode_structs[4] = {
 &default_mode_struct, &gaming_mode_struct, &left_hand_mode_struct, &windows_mode_struct, 
};


} // end namespace conf
