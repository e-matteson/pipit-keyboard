#include "auto_config-big_test.h"
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
  7141, // bits
  13, // num_bits
  (BLANK_KEY)&0xff, // key_code
  0, // is_mod
}, {
  8855, // bits
  15, // num_bits
  (COMMAND_CYCLE_CAPITAL)&0xff, // key_code
  0, // is_mod
}, {
  25239, // bits
  15, // num_bits
  (COMMAND_CYCLE_NOSPACE)&0xff, // key_code
  0, // is_mod
}, {
  24727, // bits
  15, // num_bits
  (COMMAND_CYCLE_WORD)&0xff, // key_code
  0, // is_mod
}, 
 {
  9189, // bits
  15, // num_bits
  (COMMAND_DEFAULT_MODE)&0xff, // key_code
  0, // is_mod
}, {
  3223, // bits
  15, // num_bits
  (COMMAND_DELETE_WORD)&0xff, // key_code
  0, // is_mod
}, {
  6295, // bits
  15, // num_bits
  (COMMAND_GAMING_MODE)&0xff, // key_code
  0, // is_mod
}, {
  4247, // bits
  15, // num_bits
  (COMMAND_LED_BATTERY)&0xff, // key_code
  0, // is_mod
}, 
 {
  20631, // bits
  15, // num_bits
  (COMMAND_LED_COLORS)&0xff, // key_code
  0, // is_mod
}, {
  16535, // bits
  15, // num_bits
  (COMMAND_LED_RAINBOW)&0xff, // key_code
  0, // is_mod
}, {
  25573, // bits
  15, // num_bits
  (COMMAND_LEFT_HAND_MODE)&0xff, // key_code
  0, // is_mod
}, {
  4759, // bits
  15, // num_bits
  (COMMAND_LEFT_LIMIT)&0xff, // key_code
  0, // is_mod
}, 
 {
  19607, // bits
  15, // num_bits
  (COMMAND_LEFT_WORD)&0xff, // key_code
  0, // is_mod
}, {
  27621, // bits
  15, // num_bits
  (COMMAND_PAUSE)&0xff, // key_code
  0, // is_mod
}, {
  22679, // bits
  15, // num_bits
  (COMMAND_RIGHT_LIMIT)&0xff, // key_code
  0, // is_mod
}, {
  13285, // bits
  15, // num_bits
  (COMMAND_RIGHT_WORD)&0xff, // key_code
  0, // is_mod
}, 
 {
  29669, // bits
  15, // num_bits
  (COMMAND_SHORTEN_LAST_WORD)&0xff, // key_code
  0, // is_mod
}, {
  18405, // bits
  15, // num_bits
  (COMMAND_STICKY_ALT)&0xff, // key_code
  0, // is_mod
}, {
  12439, // bits
  15, // num_bits
  (COMMAND_STICKY_CTRL)&0xff, // key_code
  0, // is_mod
}, {
  5093, // bits
  15, // num_bits
  (COMMAND_STICKY_GUI)&0xff, // key_code
  0, // is_mod
}, 
 {
  10213, // bits
  15, // num_bits
  (COMMAND_STICKY_SHIFT)&0xff, // key_code
  0, // is_mod
}, {
  151, // bits
  15, // num_bits
  (COMMAND_WINDOWS_MODE)&0xff, // key_code
  0, // is_mod
}, {
  322, // bits
  10, // num_bits
  (KEY_0)&0xff, // key_code
  0, // is_mod
}, {
  4069, // bits
  12, // num_bits
  (KEY_1)&0xff, // key_code
  0, // is_mod
}, 
 {
  2711, // bits
  12, // num_bits
  (KEY_2)&0xff, // key_code
  0, // is_mod
}, {
  642, // bits
  11, // num_bits
  (KEY_3)&0xff, // key_code
  0, // is_mod
}, {
  1474, // bits
  12, // num_bits
  (KEY_4)&0xff, // key_code
  0, // is_mod
}, {
  7618, // bits
  13, // num_bits
  (KEY_5)&0xff, // key_code
  0, // is_mod
}, 
 {
  3522, // bits
  13, // num_bits
  (KEY_6)&0xff, // key_code
  0, // is_mod
}, {
  450, // bits
  12, // num_bits
  (KEY_7)&0xff, // key_code
  0, // is_mod
}, {
  663, // bits
  14, // num_bits
  (KEY_8)&0xff, // key_code
  0, // is_mod
}, {
  66, // bits
  10, // num_bits
  (KEY_9)&0xff, // key_code
  0, // is_mod
}, 
 {
  15, // bits
  4, // num_bits
  (KEY_A)&0xff, // key_code
  0, // is_mod
}, {
  39, // bits
  6, // num_bits
  (KEY_B)&0xff, // key_code
  0, // is_mod
}, {
  578, // bits
  11, // num_bits
  (KEY_BACKSLASH)&0xff, // key_code
  0, // is_mod
}, {
  27799, // bits
  15, // num_bits
  (KEY_BACKSPACE)&0xff, // key_code
  0, // is_mod
}, 
 {
  8, // bits
  4, // num_bits
  (KEY_C)&0xff, // key_code
  0, // is_mod
}, {
  2021, // bits
  15, // num_bits
  (KEY_CAPS_LOCK)&0xff, // key_code
  0, // is_mod
}, {
  1687, // bits
  11, // num_bits
  (KEY_COMMA)&0xff, // key_code
  0, // is_mod
}, {
  18, // bits
  5, // num_bits
  (KEY_D)&0xff, // key_code
  0, // is_mod
}, 
 {
  21477, // bits
  15, // num_bits
  (KEY_DELETE)&0xff, // key_code
  0, // is_mod
}, {
  26597, // bits
  15, // num_bits
  (KEY_DOWN)&0xff, // key_code
  0, // is_mod
}, {
  6, // bits
  3, // num_bits
  (KEY_E)&0xff, // key_code
  0, // is_mod
}, {
  1602, // bits
  11, // num_bits
  (KEY_END)&0xff, // key_code
  0, // is_mod
}, 
 {
  962, // bits
  10, // num_bits
  (KEY_ENTER)&0xff, // key_code
  0, // is_mod
}, {
  2498, // bits
  12, // num_bits
  (KEY_EQUAL)&0xff, // key_code
  0, // is_mod
}, {
  3557, // bits
  12, // num_bits
  (KEY_ESC)&0xff, // key_code
  0, // is_mod
}, {
  7, // bits
  6, // num_bits
  (KEY_F)&0xff, // key_code
  0, // is_mod
}, 
 {
  31895, // bits
  15, // num_bits
  (KEY_F1)&0xff, // key_code
  0, // is_mod
}, {
  21143, // bits
  15, // num_bits
  (KEY_F2)&0xff, // key_code
  0, // is_mod
}, {
  15511, // bits
  15, // num_bits
  (KEY_F3)&0xff, // key_code
  0, // is_mod
}, {
  7319, // bits
  15, // num_bits
  (KEY_F4)&0xff, // key_code
  0, // is_mod
}, 
 {
  23703, // bits
  15, // num_bits
  (KEY_F5)&0xff, // key_code
  0, // is_mod
}, {
  12951, // bits
  15, // num_bits
  (KEY_F6)&0xff, // key_code
  0, // is_mod
}, {
  29335, // bits
  15, // num_bits
  (KEY_F7)&0xff, // key_code
  0, // is_mod
}, {
  14487, // bits
  15, // num_bits
  (KEY_F8)&0xff, // key_code
  0, // is_mod
}, 
 {
  30871, // bits
  15, // num_bits
  (KEY_F9)&0xff, // key_code
  0, // is_mod
}, {
  55, // bits
  6, // num_bits
  (KEY_G)&0xff, // key_code
  0, // is_mod
}, {
  16, // bits
  5, // num_bits
  (KEY_H)&0xff, // key_code
  0, // is_mod
}, {
  11237, // bits
  15, // num_bits
  (KEY_HOME)&0xff, // key_code
  0, // is_mod
}, 
 {
  13, // bits
  4, // num_bits
  (KEY_I)&0xff, // key_code
  0, // is_mod
}, {
  2, // bits
  8, // num_bits
  (KEY_J)&0xff, // key_code
  0, // is_mod
}, {
  37, // bits
  7, // num_bits
  (KEY_K)&0xff, // key_code
  0, // is_mod
}, {
  4, // bits
  4, // num_bits
  (KEY_L)&0xff, // key_code
  0, // is_mod
}, 
 {
  407, // bits
  9, // num_bits
  (KEY_LEFT)&0xff, // key_code
  0, // is_mod
}, {
  706, // bits
  10, // num_bits
  (KEY_LEFT_BRACE)&0xff, // key_code
  0, // is_mod
}, {
  9, // bits
  5, // num_bits
  (KEY_M)&0xff, // key_code
  0, // is_mod
}, {
  1666, // bits
  11, // num_bits
  (KEY_MINUS)&0xff, // key_code
  0, // is_mod
}, 
 {
  10, // bits
  4, // num_bits
  (KEY_N)&0xff, // key_code
  0, // is_mod
}, {
  1, // bits
  4, // num_bits
  (KEY_O)&0xff, // key_code
  0, // is_mod
}, {
  21, // bits
  5, // num_bits
  (KEY_P)&0xff, // key_code
  0, // is_mod
}, {
  14309, // bits
  14, // num_bits
  (KEY_PAGE_DOWN)&0xff, // key_code
  0, // is_mod
}, 
 {
  6117, // bits
  14, // num_bits
  (KEY_PAGE_UP)&0xff, // key_code
  0, // is_mod
}, {
  834, // bits
  10, // num_bits
  (KEY_PERIOD)&0xff, // key_code
  0, // is_mod
}, {
  11415, // bits
  15, // num_bits
  (KEY_PRINTSCREEN)&0xff, // key_code
  0, // is_mod
}, {
  101, // bits
  9, // num_bits
  (KEY_Q)&0xff, // key_code
  0, // is_mod
}, 
 {
  386, // bits
  9, // num_bits
  (KEY_QUOTE)&0xff, // key_code
  0, // is_mod
}, {
  3, // bits
  4, // num_bits
  (KEY_R)&0xff, // key_code
  0, // is_mod
}, {
  28823, // bits
  15, // num_bits
  (KEY_RIGHT)&0xff, // key_code
  0, // is_mod
}, {
  194, // bits
  10, // num_bits
  (KEY_RIGHT_BRACE)&0xff, // key_code
  0, // is_mod
}, 
 {
  12, // bits
  4, // num_bits
  (KEY_S)&0xff, // key_code
  0, // is_mod
}, {
  485, // bits
  11, // num_bits
  (KEY_SEMICOLON)&0xff, // key_code
  0, // is_mod
}, {
  1175, // bits
  12, // num_bits
  (KEY_SLASH)&0xff, // key_code
  0, // is_mod
}, {
  229, // bits
  9, // num_bits
  (KEY_SPACE)&0xff, // key_code
  0, // is_mod
}, 
 {
  11, // bits
  4, // num_bits
  (KEY_T)&0xff, // key_code
  0, // is_mod
}, {
  997, // bits
  14, // num_bits
  (KEY_TAB)&0xff, // key_code
  0, // is_mod
}, {
  2199, // bits
  13, // num_bits
  (KEY_TILDE)&0xff, // key_code
  0, // is_mod
}, {
  25, // bits
  5, // num_bits
  (KEY_U)&0xff, // key_code
  0, // is_mod
}, 
 {
  130, // bits
  10, // num_bits
  (KEY_UP)&0xff, // key_code
  0, // is_mod
}, {
  34, // bits
  6, // num_bits
  (KEY_V)&0xff, // key_code
  0, // is_mod
}, {
  87, // bits
  7, // num_bits
  (KEY_W)&0xff, // key_code
  0, // is_mod
}, {
  23, // bits
  8, // num_bits
  (KEY_X)&0xff, // key_code
  0, // is_mod
}, 
 {
  5, // bits
  6, // num_bits
  (KEY_Y)&0xff, // key_code
  0, // is_mod
}, {
  357, // bits
  9, // num_bits
  (KEY_Z)&0xff, // key_code
  0, // is_mod
}, {
  3045, // bits
  14, // num_bits
  (MODIFIERKEY_ALT)&0xff, // key_code
  1, // is_mod
}, {
  1509, // bits
  12, // num_bits
  (MODIFIERKEY_CTRL)&0xff, // key_code
  1, // is_mod
}, 
 {
  8343, // bits
  15, // num_bits
  (MODIFIERKEY_GUI)&0xff, // key_code
  1, // is_mod
}, {
  0, // bits
  5, // num_bits
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

const uint8_t kmap0_plain_len3_anagram0_chords[] = {
 16, 0, 0, 
};

const uint8_t kmap0_plain_len3_anagram0_seqs[] = {
 6, 
};

const LookupOfLength kmap0_plain_len3_anagram0 = {
  48, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_plain_len3_anagram0_chords, // chords
  kmap0_plain_len3_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len4_anagram0_chords[] = {
 0, 4, 0, 0, 
 0, 2, 2, 0, 
 0, 0, 0, 128, 
 0, 0, 8, 128, 
 0, 0, 0, 0, 
 16, 0, 0, 64, 
 0, 0, 1, 
};

const uint8_t kmap0_plain_len4_anagram0_seqs[] = {
 143, 77, 26, 195, 
 11, 
};

const LookupOfLength kmap0_plain_len4_anagram0 = {
  64, // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_plain_len4_anagram0_chords, // chords
  kmap0_plain_len4_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len5_anagram0_chords[] = {
 0, 64, 0, 0, 
 32, 0, 0, 8, 
 0, 4, 0, 0, 
 32, 0, 0, 
};

const uint8_t kmap0_plain_len5_anagram0_seqs[] = {
 18, 166, 154, 1, 
};

const LookupOfLength kmap0_plain_len5_anagram0 = {
  80, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_plain_len5_anagram0_chords, // chords
  kmap0_plain_len5_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len6_anagram0_chords[] = {
 36, 0, 0, 0, 
 1, 0, 32, 1, 
 0, 32, 8, 0, 
 0, 0, 18, 
};

const uint8_t kmap0_plain_len6_anagram0_seqs[] = {
 231, 113, 139, 5, 
};

const LookupOfLength kmap0_plain_len6_anagram0 = {
  96, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_plain_len6_anagram0_chords, // chords
  kmap0_plain_len6_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len7_anagram0_chords[] = {
 0, 9, 0, 0, 
 64, 2, 
};

const uint8_t kmap0_plain_len7_anagram0_seqs[] = {
 165, 43, 
};

const LookupOfLength kmap0_plain_len7_anagram0 = {
  112, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_plain_len7_anagram0_chords, // chords
  kmap0_plain_len7_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len8_anagram0_chords[] = {
 0, 0, 144, 0, 
 0, 130, 
};

const uint8_t kmap0_plain_len8_anagram0_seqs[] = {
 2, 23, 
};

const LookupOfLength kmap0_plain_len8_anagram0 = {
  128, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_plain_len8_anagram0_chords, // chords
  kmap0_plain_len8_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len9_anagram0_chords[] = {
 0, 192, 0, 0, 
 64, 128, 0, 32, 
 128, 0, 128, 0, 
 4, 8, 0, 
};

const uint8_t kmap0_plain_len9_anagram0_seqs[] = {
 151, 203, 8, 46, 
 87, 22, 
};

const LookupOfLength kmap0_plain_len9_anagram0 = {
  144, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_plain_len9_anagram0_chords, // chords
  kmap0_plain_len9_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len10_anagram0_chords[] = {
 0, 32, 1, 16, 
 4, 0, 8, 128, 
 0, 0, 33, 0, 
 0, 64, 16, 0, 
 1, 1, 0, 0, 
 32, 
};

const uint8_t kmap0_plain_len10_anagram0_seqs[] = {
 66, 9, 33, 188, 
 176, 66, 11, 35, 
 8, 
};

const LookupOfLength kmap0_plain_len10_anagram0 = {
  160, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_plain_len10_anagram0_chords, // chords
  kmap0_plain_len10_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len11_anagram0_chords[] = {
 144, 0, 0, 34, 
 0, 0, 4, 1, 
 0, 0, 128, 128, 
 0, 32, 16, 0, 
 64, 8, 
};

const uint8_t kmap0_plain_len11_anagram0_seqs[] = {
 130, 18, 210, 165, 
 133, 44, 232, 242, 
 0, 
};

const LookupOfLength kmap0_plain_len11_anagram0 = {
  176, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_plain_len11_anagram0_chords, // chords
  kmap0_plain_len11_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len12_anagram0_chords[] = {
 18, 0, 0, 0, 
 0, 9, 0, 0, 
 72, 130, 0, 0, 
 0, 64, 64, 16, 
 0, 1, 0, 32, 
 2, 
};

const uint8_t kmap0_plain_len12_anagram0_seqs[] = {
 229, 127, 169, 194, 
 37, 28, 194, 89, 
 222, 151, 4, 
};

const LookupOfLength kmap0_plain_len12_anagram0 = {
  192, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_plain_len12_anagram0_chords, // chords
  kmap0_plain_len12_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len13_anagram0_chords[] = {
 128, 4, 0, 0, 
 32, 8, 0, 0, 
 80, 
};

const uint8_t kmap0_plain_len13_anagram0_seqs[] = {
 194, 93, 184, 93, 
 34, 
};

const LookupOfLength kmap0_plain_len13_anagram0 = {
  208, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_plain_len13_anagram0_chords, // chords
  kmap0_plain_len13_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len14_anagram0_chords[] = {
 0, 0, 65, 2, 
 8, 0, 0, 2, 
 32, 0, 130, 0, 
 128, 8, 0, 
};

const uint8_t kmap0_plain_len14_anagram0_seqs[] = {
 151, 2, 16, 92, 
 126, 151, 95, 229, 
 3, 
};

const LookupOfLength kmap0_plain_len14_anagram0 = {
  224, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_plain_len14_anagram0_chords, // chords
  kmap0_plain_len14_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len15_anagram0_chords[] = {
 8, 0, 0, 0, 
 224, 3, 54, 128, 
 0, 0, 2, 0, 
 18, 129, 0, 0, 
 129, 9, 144, 129, 
 0, 0, 129, 72, 
 128, 133, 0, 0, 
 161, 8, 130, 129, 
 0, 0, 129, 65, 
 16, 133, 0, 0, 
 128, 16, 32, 32, 
 0, 4, 32, 0, 
 0, 128, 216, 0, 
 128, 2, 0, 8, 
 1, 32, 0, 1, 
 4, 0, 1, 
};

const uint8_t kmap0_plain_len15_anagram0_seqs[] = {
 151, 236, 242, 67, 
 249, 180, 252, 124, 
 201, 191, 148, 94, 
 242, 46, 57, 151, 
 220, 75, 217, 165, 
 252, 18, 119, 137, 
 47, 95, 1, 97, 
 129, 16, 151, 172, 
 75, 56, 16, 26, 
 8, 3, 132, 2, 
};

const LookupOfLength kmap0_plain_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  21, // num_chords
  kmap0_plain_len15_anagram0_chords, // chords
  kmap0_plain_len15_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len16_anagram0_chords[] = {
 132, 0, 0, 0, 
 0, 66, 0, 40, 
 0, 16, 1, 0, 
 2, 1, 0, 
};

const uint8_t kmap0_plain_len16_anagram0_seqs[] = {
 160, 60, 64, 80, 
 224, 210, 64, 72, 
 64, 208, 
};

const LookupOfLength kmap0_plain_len16_anagram0 = {
  256, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_plain_len16_anagram0_chords, // chords
  kmap0_plain_len16_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len17_anagram0_chords[] = {
 0, 0, 17, 32, 
 4, 0, 2, 4, 
 0, 0, 64, 1, 
 4, 4, 0, 0, 
 32, 64, 
};

const uint8_t kmap0_plain_len17_anagram0_seqs[] = {
 64, 56, 192, 165, 
 130, 242, 7, 194, 
 5, 132, 19, 92, 
 18, 
};

const LookupOfLength kmap0_plain_len17_anagram0 = {
  272, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_plain_len17_anagram0_chords, // chords
  kmap0_plain_len17_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len18_anagram0_chords[] = {
 20, 0, 0, 0, 
 0, 10, 0, 5, 
 0, 64, 0, 0, 
};

const uint8_t kmap0_plain_len18_anagram0_seqs[] = {
 64, 184, 1, 225, 
 14, 46, 17, 40, 
 223, 
};

const LookupOfLength kmap0_plain_len18_anagram0 = {
  288, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_plain_len18_anagram0_chords, // chords
  kmap0_plain_len18_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len19_anagram0_chords[] = {
 160, 0, 0, 
};

const uint8_t kmap0_plain_len19_anagram0_seqs[] = {
 224, 82, 0, 
};

const LookupOfLength kmap0_plain_len19_anagram0 = {
  304, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_plain_len19_anagram0_chords, // chords
  kmap0_plain_len19_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len25_anagram0_chords[] = {
 1, 0, 0, 
};

const uint8_t kmap0_plain_len25_anagram0_seqs[] = {
 229, 85, 190, 1, 
};

const LookupOfLength kmap0_plain_len25_anagram0 = {
  400, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_plain_len25_anagram0_chords, // chords
  kmap0_plain_len25_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len27_anagram0_chords[] = {
 0, 0, 4, 
};

const uint8_t kmap0_plain_len27_anagram0_seqs[] = {
 229, 75, 249, 6, 
};

const LookupOfLength kmap0_plain_len27_anagram0 = {
  432, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_plain_len27_anagram0_chords, // chords
  kmap0_plain_len27_anagram0_seqs, // sequences
};

const uint8_t kmap0_plain_len28_anagram0_chords[] = {
 0, 16, 0, 
};

const uint8_t kmap0_plain_len28_anagram0_seqs[] = {
 151, 160, 242, 13, 
};

const LookupOfLength kmap0_plain_len28_anagram0 = {
  448, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_plain_len28_anagram0_chords, // chords
  kmap0_plain_len28_anagram0_seqs, // sequences
};

const LookupOfLength* kmap0_plain_lookups_array[] = {
 &kmap0_plain_len3_anagram0, &kmap0_plain_len4_anagram0, &kmap0_plain_len5_anagram0, &kmap0_plain_len6_anagram0, 
 &kmap0_plain_len7_anagram0, &kmap0_plain_len8_anagram0, &kmap0_plain_len9_anagram0, &kmap0_plain_len10_anagram0, 
 &kmap0_plain_len11_anagram0, &kmap0_plain_len12_anagram0, &kmap0_plain_len13_anagram0, &kmap0_plain_len14_anagram0, 
 &kmap0_plain_len15_anagram0, &kmap0_plain_len16_anagram0, &kmap0_plain_len17_anagram0, &kmap0_plain_len18_anagram0, 
 &kmap0_plain_len19_anagram0, &kmap0_plain_len25_anagram0, &kmap0_plain_len27_anagram0, &kmap0_plain_len28_anagram0, 
};

const LookupsOfSeqType kmap0_plain_lookups = {
  20, // num_lookups
  kmap0_plain_lookups_array, // lookups
};

const uint8_t kmap0_macro_len15_anagram0_chords[] = {
 34, 0, 8, 
};

const uint8_t kmap0_macro_len15_anagram0_seqs[] = {
 66, 82, 
};

const LookupOfLength kmap0_macro_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len15_anagram0_chords, // chords
  kmap0_macro_len15_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len16_anagram0_chords[] = {
 16, 128, 8, 0, 
 132, 0, 
};

const uint8_t kmap0_macro_len16_anagram0_seqs[] = {
 229, 172, 229, 245, 
};

const LookupOfLength kmap0_macro_len16_anagram0 = {
  256, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_macro_len16_anagram0_chords, // chords
  kmap0_macro_len16_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len17_anagram0_chords[] = {
 0, 128, 130, 0, 
 160, 1, 80, 128, 
 8, 4, 128, 1, 
 128, 128, 128, 
};

const uint8_t kmap0_macro_len17_anagram0_seqs[] = {
 229, 144, 202, 225, 
 148, 115, 61, 46, 
 93, 46, 8, 
};

const LookupOfLength kmap0_macro_len17_anagram0 = {
  272, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_macro_len17_anagram0_chords, // chords
  kmap0_macro_len17_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len18_anagram0_chords[] = {
 0, 128, 192, 
};

const uint8_t kmap0_macro_len18_anagram0_seqs[] = {
 196, 194, 3, 
};

const LookupOfLength kmap0_macro_len18_anagram0 = {
  288, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len18_anagram0_chords, // chords
  kmap0_macro_len18_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len19_anagram0_chords[] = {
 128, 129, 0, 4, 
 128, 0, 32, 129, 
 64, 36, 128, 64, 
 48, 128, 0, 
};

const uint8_t kmap0_macro_len19_anagram0_seqs[] = {
 229, 226, 40, 55, 
 69, 185, 155, 203, 
 157, 92, 238, 24, 
};

const LookupOfLength kmap0_macro_len19_anagram0 = {
  304, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_macro_len19_anagram0_chords, // chords
  kmap0_macro_len19_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len20_anagram0_chords[] = {
 6, 0, 0, 36, 
 192, 0, 0, 161, 
 1, 0, 128, 3, 
};

const uint8_t kmap0_macro_len20_anagram0_seqs[] = {
 229, 133, 93, 238, 
 148, 194, 10, 83, 
 174, 30, 
};

const LookupOfLength kmap0_macro_len20_anagram0 = {
  320, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_macro_len20_anagram0_chords, // chords
  kmap0_macro_len20_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len21_anagram0_chords[] = {
 0, 0, 3, 48, 
 0, 0, 128, 128, 
 2, 
};

const uint8_t kmap0_macro_len21_anagram0_seqs[] = {
 229, 142, 163, 220, 
 121, 150, 251, 64, 
};

const LookupOfLength kmap0_macro_len21_anagram0 = {
  336, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_macro_len21_anagram0_chords, // chords
  kmap0_macro_len21_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len22_anagram0_chords[] = {
 0, 96, 0, 132, 
 128, 64, 128, 132, 
 16, 128, 128, 0, 
 128, 132, 64, 4, 
 160, 0, 
};

const uint8_t kmap0_macro_len22_anagram0_seqs[] = {
 229, 203, 69, 185, 
 168, 92, 46, 197, 
 148, 75, 209, 229, 
 82, 48, 56, 46, 
 13, 
};

const LookupOfLength kmap0_macro_len22_anagram0 = {
  352, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_macro_len22_anagram0_chords, // chords
  kmap0_macro_len22_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len23_anagram0_chords[] = {
 16, 193, 0, 160, 
 128, 0, 132, 192, 
 0, 132, 128, 0, 
 2, 128, 1, 2, 
 128, 0, 0, 128, 
 18, 
};

const uint8_t kmap0_macro_len23_anagram0_seqs[] = {
 229, 14, 203, 114, 
 81, 115, 185, 168, 
 178, 92, 212, 90, 
 174, 124, 40, 119, 
 189, 22, 64, 184, 
 0, 
};

const LookupOfLength kmap0_macro_len23_anagram0 = {
  368, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_macro_len23_anagram0_chords, // chords
  kmap0_macro_len23_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len24_anagram0_chords[] = {
 36, 192, 2, 
};

const uint8_t kmap0_macro_len24_anagram0_seqs[] = {
 151, 84, 222, 
};

const LookupOfLength kmap0_macro_len24_anagram0 = {
  384, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len24_anagram0_chords, // chords
  kmap0_macro_len24_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len25_anagram0_chords[] = {
 16, 132, 1, 0, 
 128, 1, 6, 128, 
 0, 128, 132, 2, 
};

const uint8_t kmap0_macro_len25_anagram0_seqs[] = {
 95, 174, 188, 203, 
 69, 89, 151, 23, 
 130, 46, 247, 17, 
 8, 
};

const LookupOfLength kmap0_macro_len25_anagram0 = {
  400, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_macro_len25_anagram0_chords, // chords
  kmap0_macro_len25_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len26_anagram0_chords[] = {
 0, 128, 64, 0, 
 128, 8, 16, 36, 
 128, 
};

const uint8_t kmap0_macro_len26_anagram0_seqs[] = {
 229, 85, 126, 151, 
 87, 249, 37, 104, 
 32, 52, 
};

const LookupOfLength kmap0_macro_len26_anagram0 = {
  416, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_macro_len26_anagram0_chords, // chords
  kmap0_macro_len26_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len27_anagram0_chords[] = {
 0, 160, 128, 128, 
 36, 128, 128, 132, 
 1, 16, 129, 192, 
};

const uint8_t kmap0_macro_len27_anagram0_seqs[] = {
 130, 5, 95, 6, 
 151, 22, 116, 185, 
 4, 118, 217, 116, 
 8, 13, 
};

const LookupOfLength kmap0_macro_len27_anagram0 = {
  432, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_macro_len27_anagram0_chords, // chords
  kmap0_macro_len27_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len29_anagram0_chords[] = {
 0, 128, 81, 0, 
 33, 1, 
};

const uint8_t kmap0_macro_len29_anagram0_seqs[] = {
 64, 56, 120, 71, 
 88, 97, 46, 3, 
};

const LookupOfLength kmap0_macro_len29_anagram0 = {
  464, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_macro_len29_anagram0_chords, // chords
  kmap0_macro_len29_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len30_anagram0_chords[] = {
 20, 132, 1, 2, 
 137, 0, 80, 132, 
 1, 32, 160, 1, 
 4, 160, 1, 
};

const uint8_t kmap0_macro_len30_anagram0_seqs[] = {
 95, 174, 188, 43, 
 16, 12, 4, 13, 
 190, 92, 121, 3, 
 97, 129, 48, 64, 
 8, 32, 20, 
};

const LookupOfLength kmap0_macro_len30_anagram0 = {
  480, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_macro_len30_anagram0_chords, // chords
  kmap0_macro_len30_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len31_anagram0_chords[] = {
 0, 168, 1, 
};

const uint8_t kmap0_macro_len31_anagram0_seqs[] = {
 224, 210, 64, 104, 
};

const LookupOfLength kmap0_macro_len31_anagram0 = {
  496, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len31_anagram0_chords, // chords
  kmap0_macro_len31_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len32_anagram0_chords[] = {
 0, 192, 128, 
};

const uint8_t kmap0_macro_len32_anagram0_seqs[] = {
 229, 117, 81, 254, 
};

const LookupOfLength kmap0_macro_len32_anagram0 = {
  512, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len32_anagram0_chords, // chords
  kmap0_macro_len32_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len33_anagram0_chords[] = {
 0, 192, 64, 0, 
 160, 0, 
};

const uint8_t kmap0_macro_len33_anagram0_seqs[] = {
 194, 41, 156, 151, 
 65, 121, 174, 194, 
 3, 
};

const LookupOfLength kmap0_macro_len33_anagram0 = {
  528, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_macro_len33_anagram0_chords, // chords
  kmap0_macro_len33_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len34_anagram0_chords[] = {
 32, 132, 0, 
};

const uint8_t kmap0_macro_len34_anagram0_seqs[] = {
 224, 82, 193, 165, 
 2, 
};

const LookupOfLength kmap0_macro_len34_anagram0 = {
  544, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len34_anagram0_chords, // chords
  kmap0_macro_len34_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len35_anagram0_chords[] = {
 84, 132, 1, 0, 
 128, 80, 146, 164, 
 0, 
};

const uint8_t kmap0_macro_len35_anagram0_seqs[] = {
 224, 203, 149, 119, 
 189, 68, 151, 232, 
 50, 40, 79, 25, 
 225, 1, 
};

const LookupOfLength kmap0_macro_len35_anagram0 = {
  560, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_macro_len35_anagram0_chords, // chords
  kmap0_macro_len35_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len37_anagram0_chords[] = {
 2, 136, 0, 
};

const uint8_t kmap0_macro_len37_anagram0_seqs[] = {
 64, 48, 16, 124, 
 25, 
};

const LookupOfLength kmap0_macro_len37_anagram0 = {
  592, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len37_anagram0_chords, // chords
  kmap0_macro_len37_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len39_anagram0_chords[] = {
 32, 32, 1, 4, 
 32, 1, 2, 160, 
 9, 
};

const uint8_t kmap0_macro_len39_anagram0_seqs[] = {
 64, 88, 32, 204, 
 101, 32, 4, 16, 
 234, 114, 185, 40, 
 123, 10, 10, 
};

const LookupOfLength kmap0_macro_len39_anagram0 = {
  624, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_macro_len39_anagram0_chords, // chords
  kmap0_macro_len39_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len40_anagram0_chords[] = {
 0, 40, 1, 2, 
 160, 1, 2, 160, 
 73, 
};

const uint8_t kmap0_macro_len40_anagram0_seqs[] = {
 224, 210, 64, 232, 
 203, 229, 162, 236, 
 121, 169, 229, 162, 
 236, 41, 92, 
};

const LookupOfLength kmap0_macro_len40_anagram0 = {
  640, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_macro_len40_anagram0_chords, // chords
  kmap0_macro_len40_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len42_anagram0_chords[] = {
 0, 160, 10, 
};

const uint8_t kmap0_macro_len42_anagram0_seqs[] = {
 151, 36, 136, 32, 
 194, 3, 
};

const LookupOfLength kmap0_macro_len42_anagram0 = {
  672, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len42_anagram0_chords, // chords
  kmap0_macro_len42_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len43_anagram0_chords[] = {
 2, 68, 1, 2, 
 160, 65, 
};

const uint8_t kmap0_macro_len43_anagram0_seqs[] = {
 160, 252, 129, 112, 
 149, 91, 216, 44, 
 104, 32, 52, 
};

const LookupOfLength kmap0_macro_len43_anagram0 = {
  688, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_macro_len43_anagram0_chords, // chords
  kmap0_macro_len43_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len44_anagram0_chords[] = {
 0, 132, 130, 0, 
 172, 1, 
};

const uint8_t kmap0_macro_len44_anagram0_seqs[] = {
 229, 117, 81, 222, 
 229, 13, 46, 45, 
 248, 129, 208, 
};

const LookupOfLength kmap0_macro_len44_anagram0 = {
  704, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_macro_len44_anagram0_chords, // chords
  kmap0_macro_len44_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len54_anagram0_chords[] = {
 2, 128, 10, 
};

const uint8_t kmap0_macro_len54_anagram0_seqs[] = {
 64, 80, 173, 72, 
 89, 186, 28, 
};

const LookupOfLength kmap0_macro_len54_anagram0 = {
  864, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len54_anagram0_chords, // chords
  kmap0_macro_len54_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len57_anagram0_chords[] = {
 16, 192, 136, 
};

const uint8_t kmap0_macro_len57_anagram0_seqs[] = {
 224, 210, 224, 210, 
 229, 172, 146, 0, 
};

const LookupOfLength kmap0_macro_len57_anagram0 = {
  912, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len57_anagram0_chords, // chords
  kmap0_macro_len57_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len58_anagram0_chords[] = {
 160, 128, 3, 
};

const uint8_t kmap0_macro_len58_anagram0_seqs[] = {
 24, 121, 203, 129, 
 75, 131, 75, 3, 
};

const LookupOfLength kmap0_macro_len58_anagram0 = {
  928, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len58_anagram0_chords, // chords
  kmap0_macro_len58_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len60_anagram0_chords[] = {
 18, 128, 131, 4, 
 128, 18, 
};

const uint8_t kmap0_macro_len60_anagram0_seqs[] = {
 190, 232, 5, 66, 
 8, 10, 8, 85, 
 167, 117, 129, 16, 
 64, 168, 203, 
};

const LookupOfLength kmap0_macro_len60_anagram0 = {
  960, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_macro_len60_anagram0_chords, // chords
  kmap0_macro_len60_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len65_anagram0_chords[] = {
 16, 128, 18, 
};

const uint8_t kmap0_macro_len65_anagram0_seqs[] = {
 232, 153, 114, 224, 
 210, 224, 210, 229, 
 0, 
};

const LookupOfLength kmap0_macro_len65_anagram0 = {
  1040, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len65_anagram0_chords, // chords
  kmap0_macro_len65_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len70_anagram0_chords[] = {
 4, 128, 130, 
};

const uint8_t kmap0_macro_len70_anagram0_seqs[] = {
 66, 194, 94, 87, 
 32, 44, 16, 230, 
 50, 
};

const LookupOfLength kmap0_macro_len70_anagram0 = {
  1120, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len70_anagram0_chords, // chords
  kmap0_macro_len70_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len74_anagram0_chords[] = {
 16, 128, 2, 
};

const uint8_t kmap0_macro_len74_anagram0_seqs[] = {
 38, 54, 16, 86, 
 120, 225, 129, 48, 
 130, 0, 
};

const LookupOfLength kmap0_macro_len74_anagram0 = {
  1184, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len74_anagram0_chords, // chords
  kmap0_macro_len74_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len76_anagram0_chords[] = {
 16, 192, 10, 
};

const uint8_t kmap0_macro_len76_anagram0_seqs[] = {
 160, 60, 160, 60, 
 234, 43, 16, 2, 
 8, 5, 
};

const LookupOfLength kmap0_macro_len76_anagram0 = {
  1216, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len76_anagram0_chords, // chords
  kmap0_macro_len76_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len88_anagram0_chords[] = {
 18, 132, 0, 
};

const uint8_t kmap0_macro_len88_anagram0_seqs[] = {
 151, 46, 247, 250, 
 247, 124, 2, 229, 
 41, 87, 254, 
};

const LookupOfLength kmap0_macro_len88_anagram0 = {
  1408, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len88_anagram0_chords, // chords
  kmap0_macro_len88_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len90_anagram0_chords[] = {
 2, 132, 66, 
};

const uint8_t kmap0_macro_len90_anagram0_seqs[] = {
 64, 80, 160, 252, 
 47, 233, 108, 189, 
 164, 243, 25, 2, 
};

const LookupOfLength kmap0_macro_len90_anagram0 = {
  1440, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len90_anagram0_chords, // chords
  kmap0_macro_len90_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len109_anagram0_chords[] = {
 36, 160, 1, 
};

const uint8_t kmap0_macro_len109_anagram0_seqs[] = {
 64, 8, 32, 20, 
 16, 86, 120, 32, 
 140, 32, 66, 190, 
 124, 25, 
};

const LookupOfLength kmap0_macro_len109_anagram0 = {
  1744, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len109_anagram0_chords, // chords
  kmap0_macro_len109_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len111_anagram0_chords[] = {
 4, 132, 82, 
};

const uint8_t kmap0_macro_len111_anagram0_seqs[] = {
 64, 48, 16, 12, 
 4, 3, 193, 64, 
 48, 16, 124, 249, 
 242, 101, 
};

const LookupOfLength kmap0_macro_len111_anagram0 = {
  1776, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len111_anagram0_chords, // chords
  kmap0_macro_len111_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len114_anagram0_chords[] = {
 0, 168, 17, 
};

const uint8_t kmap0_macro_len114_anagram0_seqs[] = {
 229, 4, 13, 132, 
 46, 7, 132, 21, 
 30, 8, 35, 136, 
 144, 47, 3, 
};

const LookupOfLength kmap0_macro_len114_anagram0 = {
  1824, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len114_anagram0_chords, // chords
  kmap0_macro_len114_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len118_anagram0_chords[] = {
 4, 128, 64, 
};

const uint8_t kmap0_macro_len118_anagram0_seqs[] = {
 128, 61, 253, 36, 
 116, 157, 214, 5, 
 66, 0, 161, 202, 
 115, 249, 50, 
};

const LookupOfLength kmap0_macro_len118_anagram0 = {
  1888, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len118_anagram0_chords, // chords
  kmap0_macro_len118_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len119_anagram0_chords[] = {
 2, 128, 2, 
};

const uint8_t kmap0_macro_len119_anagram0_seqs[] = {
 125, 0, 33, 128, 
 80, 64, 88, 225, 
 129, 48, 130, 8, 
 249, 242, 101, 
};

const LookupOfLength kmap0_macro_len119_anagram0 = {
  1904, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len119_anagram0_chords, // chords
  kmap0_macro_len119_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len122_anagram0_chords[] = {
 34, 141, 128, 
};

const uint8_t kmap0_macro_len122_anagram0_seqs[] = {
 22, 122, 132, 78, 
 191, 107, 14, 5, 
 151, 122, 167, 111, 
 18, 26, 35, 1, 
};

const LookupOfLength kmap0_macro_len122_anagram0 = {
  1952, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len122_anagram0_chords, // chords
  kmap0_macro_len122_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len126_anagram0_chords[] = {
 4, 128, 192, 
};

const uint8_t kmap0_macro_len126_anagram0_seqs[] = {
 128, 61, 253, 36, 
 116, 157, 214, 37, 
 5, 66, 0, 161, 
 202, 115, 249, 50, 
};

const LookupOfLength kmap0_macro_len126_anagram0 = {
  2016, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len126_anagram0_chords, // chords
  kmap0_macro_len126_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len130_anagram0_chords[] = {
 38, 140, 128, 
};

const uint8_t kmap0_macro_len130_anagram0_seqs[] = {
 22, 95, 129, 160, 
 211, 239, 154, 67, 
 193, 165, 158, 19, 
 87, 21, 218, 50, 
 3, 
};

const LookupOfLength kmap0_macro_len130_anagram0 = {
  2080, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len130_anagram0_chords, // chords
  kmap0_macro_len130_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len132_anagram0_chords[] = {
 18, 224, 130, 
};

const uint8_t kmap0_macro_len132_anagram0_seqs[] = {
 87, 216, 100, 32, 
 4, 16, 10, 8, 
 43, 60, 16, 70, 
 16, 33, 95, 190, 
 12, 
};

const LookupOfLength kmap0_macro_len132_anagram0 = {
  2112, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len132_anagram0_chords, // chords
  kmap0_macro_len132_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len151_anagram0_chords[] = {
 4, 128, 2, 
};

const uint8_t kmap0_macro_len151_anagram0_seqs[] = {
 117, 90, 247, 0, 
 66, 0, 193, 194, 
 3, 193, 64, 168, 
 242, 92, 190, 124, 
 249, 242, 101, 
};

const LookupOfLength kmap0_macro_len151_anagram0 = {
  2416, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len151_anagram0_chords, // chords
  kmap0_macro_len151_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len163_anagram0_chords[] = {
 0, 129, 2, 
};

const uint8_t kmap0_macro_len163_anagram0_seqs[] = {
 71, 12, 16, 162, 
 60, 229, 1, 66, 
 1, 97, 133, 7, 
 194, 8, 34, 228, 
 203, 151, 47, 95, 
 6, 
};

const LookupOfLength kmap0_macro_len163_anagram0 = {
  2608, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len163_anagram0_chords, // chords
  kmap0_macro_len163_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len174_anagram0_chords[] = {
 4, 128, 16, 
};

const uint8_t kmap0_macro_len174_anagram0_seqs[] = {
 117, 90, 151, 20, 
 148, 63, 16, 2, 
 8, 6, 194, 2, 
 97, 128, 224, 75, 
 3, 161, 202, 115, 
 249, 50, 
};

const LookupOfLength kmap0_macro_len174_anagram0 = {
  2784, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len174_anagram0_chords, // chords
  kmap0_macro_len174_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len180_anagram0_chords[] = {
 32, 137, 16, 
};

const uint8_t kmap0_macro_len180_anagram0_seqs[] = {
 135, 150, 3, 66, 
 0, 225, 96, 211, 
 1, 132, 2, 194, 
 10, 15, 132, 17, 
 68, 200, 151, 47, 
 95, 190, 12, 
};

const LookupOfLength kmap0_macro_len180_anagram0 = {
  2880, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len180_anagram0_chords, // chords
  kmap0_macro_len180_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len207_anagram0_chords[] = {
 4, 192, 16, 
};

const uint8_t kmap0_macro_len207_anagram0_seqs[] = {
 117, 90, 151, 20, 
 148, 63, 16, 2, 
 8, 6, 194, 130, 
 242, 128, 75, 2, 
 194, 0, 193, 151, 
 6, 66, 149, 231, 
 242, 101, 
};

const LookupOfLength kmap0_macro_len207_anagram0 = {
  3312, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len207_anagram0_chords, // chords
  kmap0_macro_len207_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len216_anagram0_chords[] = {
 32, 137, 80, 
};

const uint8_t kmap0_macro_len216_anagram0_seqs[] = {
 135, 150, 3, 66, 
 0, 225, 96, 211, 
 1, 132, 2, 194, 
 10, 15, 132, 17, 
 68, 200, 151, 47, 
 95, 190, 124, 249, 
 242, 229, 203, 
};

const LookupOfLength kmap0_macro_len216_anagram0 = {
  3456, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len216_anagram0_chords, // chords
  kmap0_macro_len216_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len217_anagram0_chords[] = {
 0, 129, 16, 
};

const uint8_t kmap0_macro_len217_anagram0_seqs[] = {
 135, 150, 3, 66, 
 0, 161, 202, 9, 
 26, 8, 93, 14, 
 8, 43, 60, 16, 
 70, 16, 33, 95, 
 190, 124, 249, 242, 
 229, 203, 151, 1, 
};

const LookupOfLength kmap0_macro_len217_anagram0 = {
  3472, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len217_anagram0_chords, // chords
  kmap0_macro_len217_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len247_anagram0_chords[] = {
 2, 128, 128, 
};

const uint8_t kmap0_macro_len247_anagram0_seqs[] = {
 66, 58, 125, 183, 
 2, 97, 123, 157, 
 186, 172, 129, 48, 
 194, 11, 47, 36, 
 171, 4, 194, 246, 
 58, 117, 89, 3, 
 97, 4, 17, 82, 
 175, 83, 57, 
};

const LookupOfLength kmap0_macro_len247_anagram0 = {
  3952, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len247_anagram0_chords, // chords
  kmap0_macro_len247_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len253_anagram0_chords[] = {
 16, 128, 128, 
};

const uint8_t kmap0_macro_len253_anagram0_seqs[] = {
 66, 58, 125, 183, 
 2, 97, 173, 57, 
 121, 126, 13, 132, 
 17, 94, 120, 33, 
 89, 37, 16, 214, 
 154, 147, 231, 215, 
 64, 24, 65, 132, 
 212, 235, 84, 14, 
};

const LookupOfLength kmap0_macro_len253_anagram0 = {
  4048, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len253_anagram0_chords, // chords
  kmap0_macro_len253_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len261_anagram0_chords[] = {
 18, 193, 0, 
};

const uint8_t kmap0_macro_len261_anagram0_seqs[] = {
 64, 80, 125, 168, 
 244, 81, 14, 64, 
 225, 129, 160, 164, 
 143, 86, 151, 3, 
 80, 120, 225, 133, 
 7, 130, 178, 202, 
 62, 4, 17, 68, 
 16, 65, 132, 124, 
 25, 
};

const LookupOfLength kmap0_macro_len261_anagram0 = {
  4176, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len261_anagram0_chords, // chords
  kmap0_macro_len261_anagram0_seqs, // sequences
};

const uint8_t kmap0_macro_len296_anagram0_chords[] = {
 0, 129, 80, 
};

const uint8_t kmap0_macro_len296_anagram0_seqs[] = {
 135, 150, 3, 66, 
 0, 225, 96, 211, 
 1, 132, 42, 39, 
 104, 32, 116, 57, 
 32, 172, 240, 64, 
 24, 65, 132, 124, 
 249, 242, 229, 203, 
 151, 47, 95, 190, 
 124, 249, 242, 229, 
 203, 
};

const LookupOfLength kmap0_macro_len296_anagram0 = {
  4736, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_macro_len296_anagram0_chords, // chords
  kmap0_macro_len296_anagram0_seqs, // sequences
};

const LookupOfLength* kmap0_macro_lookups_array[] = {
 &kmap0_macro_len15_anagram0, &kmap0_macro_len16_anagram0, &kmap0_macro_len17_anagram0, &kmap0_macro_len18_anagram0, 
 &kmap0_macro_len19_anagram0, &kmap0_macro_len20_anagram0, &kmap0_macro_len21_anagram0, &kmap0_macro_len22_anagram0, 
 &kmap0_macro_len23_anagram0, &kmap0_macro_len24_anagram0, &kmap0_macro_len25_anagram0, &kmap0_macro_len26_anagram0, 
 &kmap0_macro_len27_anagram0, &kmap0_macro_len29_anagram0, &kmap0_macro_len30_anagram0, &kmap0_macro_len31_anagram0, 
 &kmap0_macro_len32_anagram0, &kmap0_macro_len33_anagram0, &kmap0_macro_len34_anagram0, &kmap0_macro_len35_anagram0, 
 &kmap0_macro_len37_anagram0, &kmap0_macro_len39_anagram0, &kmap0_macro_len40_anagram0, &kmap0_macro_len42_anagram0, 
 &kmap0_macro_len43_anagram0, &kmap0_macro_len44_anagram0, &kmap0_macro_len54_anagram0, &kmap0_macro_len57_anagram0, 
 &kmap0_macro_len58_anagram0, &kmap0_macro_len60_anagram0, &kmap0_macro_len65_anagram0, &kmap0_macro_len70_anagram0, 
 &kmap0_macro_len74_anagram0, &kmap0_macro_len76_anagram0, &kmap0_macro_len88_anagram0, &kmap0_macro_len90_anagram0, 
 &kmap0_macro_len109_anagram0, &kmap0_macro_len111_anagram0, &kmap0_macro_len114_anagram0, &kmap0_macro_len118_anagram0, 
 &kmap0_macro_len119_anagram0, &kmap0_macro_len122_anagram0, &kmap0_macro_len126_anagram0, &kmap0_macro_len130_anagram0, 
 &kmap0_macro_len132_anagram0, &kmap0_macro_len151_anagram0, &kmap0_macro_len163_anagram0, &kmap0_macro_len174_anagram0, 
 &kmap0_macro_len180_anagram0, &kmap0_macro_len207_anagram0, &kmap0_macro_len216_anagram0, &kmap0_macro_len217_anagram0, 
 &kmap0_macro_len247_anagram0, &kmap0_macro_len253_anagram0, &kmap0_macro_len261_anagram0, &kmap0_macro_len296_anagram0, 
};

const LookupsOfSeqType kmap0_macro_lookups = {
  56, // num_lookups
  kmap0_macro_lookups_array, // lookups
};

const uint8_t kmap0_command_len15_anagram0_chords[] = {
 210, 0, 0, 146, 
 0, 4, 146, 0, 
 0, 0, 32, 9, 
 0, 64, 146, 36, 
 169, 0, 36, 137, 
 2, 36, 137, 16, 
 36, 9, 0, 20, 
 128, 0, 36, 128, 
 0, 36, 73, 146, 
 0, 192, 1, 0, 
 192, 2, 146, 16, 
 0, 
};

const uint8_t kmap0_command_len15_anagram0_seqs[] = {
 151, 162, 75, 241, 
 37, 248, 146, 113, 
 137, 185, 132, 92, 
 66, 47, 129, 229, 
 227, 75, 201, 37, 
 179, 124, 125, 137, 
 45, 159, 149, 207, 
 1, 
};

const LookupOfLength kmap0_command_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  15, // num_chords
  kmap0_command_len15_anagram0_chords, // chords
  kmap0_command_len15_anagram0_seqs, // sequences
};

const LookupOfLength* kmap0_command_lookups_array[] = {
 &kmap0_command_len15_anagram0, 
};

const LookupsOfSeqType kmap0_command_lookups = {
  1, // num_lookups
  kmap0_command_lookups_array, // lookups
};

const uint8_t kmap0_word_len4_anagram1_chords[] = {
 0, 4, 0, 0, 
 0, 16, 0, 0, 
 64, 
};

const uint8_t kmap0_word_len4_anagram1_seqs[] = {
 63, 12, 
};

const LookupOfLength kmap0_word_len4_anagram1 = {
  65, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_word_len4_anagram1_chords, // chords
  kmap0_word_len4_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len5_anagram1_chords[] = {
 0, 64, 0, 32, 
 0, 0, 
};

const uint8_t kmap0_word_len5_anagram1_seqs[] = {
 50, 3, 
};

const LookupOfLength kmap0_word_len5_anagram1 = {
  81, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len5_anagram1_chords, // chords
  kmap0_word_len5_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len7_anagram0_chords[] = {
 16, 0, 8, 16, 
 0, 16, 
};

const uint8_t kmap0_word_len7_anagram0_seqs[] = {
 86, 15, 
};

const LookupOfLength kmap0_word_len7_anagram0 = {
  112, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len7_anagram0_chords, // chords
  kmap0_word_len7_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len7_anagram1_chords[] = {
 16, 0, 64, 16, 
 0, 16, 
};

const uint8_t kmap0_word_len7_anagram1_seqs[] = {
 230, 49, 
};

const LookupOfLength kmap0_word_len7_anagram1 = {
  113, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len7_anagram1_chords, // chords
  kmap0_word_len7_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len8_anagram0_chords[] = {
 0, 4, 2, 0, 
 4, 8, 0, 4, 
 64, 0, 4, 1, 
 128, 0, 2, 16, 
 64, 0, 16, 32, 
 0, 2, 0, 2, 
 2, 0, 8, 2, 
 0, 64, 2, 0, 
 1, 0, 0, 136, 
 0, 0, 192, 16, 
 8, 0, 128, 0, 
 8, 128, 0, 16, 
 128, 0, 64, 128, 
 0, 1, 
};

const uint8_t kmap0_word_len8_anagram0_seqs[] = {
 143, 175, 207, 191, 
 24, 150, 208, 141, 
 173, 205, 189, 164, 
 196, 201, 161, 49, 
 28, 27, 
};

const LookupOfLength kmap0_word_len8_anagram0 = {
  128, // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_word_len8_anagram0_chords, // chords
  kmap0_word_len8_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len8_anagram1_chords[] = {
 0, 4, 128, 16, 
 64, 0, 16, 8, 
 0, 128, 0, 8, 
 0, 0, 130, 
};

const uint8_t kmap0_word_len8_anagram1_seqs[] = {
 79, 210, 78, 26, 
 23, 
};

const LookupOfLength kmap0_word_len8_anagram1 = {
  129, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_word_len8_anagram1_chords, // chords
  kmap0_word_len8_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len9_anagram0_chords[] = {
 0, 36, 0, 0, 
 12, 0, 52, 0, 
 0, 128, 64, 0, 
 2, 32, 0, 128, 
 32, 0, 4, 0, 
 64, 0, 8, 16, 
 32, 0, 8, 32, 
 0, 64, 
};

const uint8_t kmap0_word_len9_anagram0_seqs[] = {
 15, 63, 157, 150, 
 1, 59, 96, 229, 
 73, 89, 51, 3, 
};

const LookupOfLength kmap0_word_len9_anagram0 = {
  144, // seq_bit_len_and_anagram
  10, // num_chords
  kmap0_word_len9_anagram0_chords, // chords
  kmap0_word_len9_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len9_anagram1_chords[] = {
 2, 0, 0, 0, 
 64, 2, 0, 36, 
 0, 2, 8, 0, 
 132, 0, 0, 6, 
 0, 0, 
};

const uint8_t kmap0_word_len9_anagram1_seqs[] = {
 160, 81, 194, 239, 
 20, 181, 54, 
};

const LookupOfLength kmap0_word_len9_anagram1 = {
  145, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_word_len9_anagram1_chords, // chords
  kmap0_word_len9_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len9_anagram2_chords[] = {
 4, 4, 0, 6, 
 0, 0, 
};

const uint8_t kmap0_word_len9_anagram2_seqs[] = {
 95, 187, 2, 
};

const LookupOfLength kmap0_word_len9_anagram2 = {
  146, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len9_anagram2_chords, // chords
  kmap0_word_len9_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len10_anagram0_chords[] = {
 38, 0, 0, 0, 
 1, 8, 160, 1, 
 0, 0, 0, 146, 
 128, 1, 0, 16, 
 0, 64, 16, 64, 
 2, 
};

const uint8_t kmap0_word_len10_anagram0_seqs[] = {
 103, 31, 122, 7, 
 21, 113, 176, 125, 
 53, 
};

const LookupOfLength kmap0_word_len10_anagram0 = {
  160, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_word_len10_anagram0_chords, // chords
  kmap0_word_len10_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len10_anagram1_chords[] = {
 2, 1, 0, 32, 
 1, 8, 0, 0, 
 18, 16, 0, 1, 
 32, 8, 1, 36, 
 0, 0, 32, 8, 
 64, 
};

const uint8_t kmap0_word_len10_anagram1_seqs[] = {
 125, 232, 61, 197, 
 218, 43, 230, 42, 
 50, 
};

const LookupOfLength kmap0_word_len10_anagram1 = {
  161, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_word_len10_anagram1_chords, // chords
  kmap0_word_len10_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len10_anagram2_chords[] = {
 32, 8, 0, 
};

const uint8_t kmap0_word_len10_anagram2_seqs[] = {
 57, 1, 
};

const LookupOfLength kmap0_word_len10_anagram2 = {
  162, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len10_anagram2_chords, // chords
  kmap0_word_len10_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len10_anagram3_chords[] = {
 32, 8, 0, 34, 
 8, 0, 
};

const uint8_t kmap0_word_len10_anagram3_seqs[] = {
 41, 139, 13, 
};

const LookupOfLength kmap0_word_len10_anagram3 = {
  163, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len10_anagram3_chords, // chords
  kmap0_word_len10_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len10_anagram4_chords[] = {
 34, 1, 0, 
};

const uint8_t kmap0_word_len10_anagram4_seqs[] = {
 119, 3, 
};

const LookupOfLength kmap0_word_len10_anagram4 = {
  164, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len10_anagram4_chords, // chords
  kmap0_word_len10_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len11_anagram0_chords[] = {
 16, 4, 2, 16, 
 4, 16, 16, 4, 
 1, 144, 0, 2, 
 16, 0, 3, 0, 
 65, 0, 18, 0, 
 2, 18, 0, 16, 
 18, 0, 64, 16, 
 0, 136, 16, 0, 
 129, 18, 0, 128, 
 0, 8, 18, 128, 
 9, 0, 144, 0, 
 8, 16, 0, 144, 
 16, 0, 66, 16, 
 0, 9, 16, 0, 
 17, 18, 0, 1, 
 144, 0, 1, 
};

const uint8_t kmap0_word_len11_anagram0_seqs[] = {
 143, 254, 177, 127, 
 141, 225, 197, 67, 
 54, 186, 61, 109, 
 38, 43, 121, 169, 
 157, 138, 40, 133, 
 122, 76, 108, 92, 
 235, 122, 182, 189, 
 97, 
};

const LookupOfLength kmap0_word_len11_anagram0 = {
  176, // seq_bit_len_and_anagram
  21, // num_chords
  kmap0_word_len11_anagram0_chords, // chords
  kmap0_word_len11_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len11_anagram1_chords[] = {
 16, 4, 1, 16, 
 0, 130, 32, 8, 
 0, 16, 0, 9, 
 20, 0, 0, 16, 
 0, 80, 16, 4, 
 64, 16, 0, 65, 
};

const uint8_t kmap0_word_len11_anagram1_seqs[] = {
 191, 246, 69, 18, 
 213, 91, 237, 49, 
 179, 159, 189, 
};

const LookupOfLength kmap0_word_len11_anagram1 = {
  177, // seq_bit_len_and_anagram
  8, // num_chords
  kmap0_word_len11_anagram1_chords, // chords
  kmap0_word_len11_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len11_anagram2_chords[] = {
 16, 0, 65, 16, 
 4, 1, 
};

const uint8_t kmap0_word_len11_anagram2_seqs[] = {
 230, 93, 63, 
};

const LookupOfLength kmap0_word_len11_anagram2 = {
  178, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len11_anagram2_chords, // chords
  kmap0_word_len11_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len11_anagram3_chords[] = {
 16, 4, 16, 144, 
 0, 8, 
};

const uint8_t kmap0_word_len11_anagram3_seqs[] = {
 158, 87, 7, 
};

const LookupOfLength kmap0_word_len11_anagram3 = {
  179, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len11_anagram3_chords, // chords
  kmap0_word_len11_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len11_anagram4_chords[] = {
 16, 4, 16, 
};

const uint8_t kmap0_word_len11_anagram4_seqs[] = {
 254, 1, 
};

const LookupOfLength kmap0_word_len11_anagram4 = {
  180, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len11_anagram4_chords, // chords
  kmap0_word_len11_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len12_anagram0_chords[] = {
 2, 4, 16, 0, 
 4, 128, 0, 4, 
 9, 20, 4, 0, 
 36, 0, 18, 0, 
 4, 10, 0, 4, 
 3, 2, 0, 66, 
 128, 0, 10, 48, 
 0, 2, 18, 64, 
 0, 16, 64, 8, 
 16, 0, 18, 2, 
 4, 8, 2, 0, 
 128, 2, 0, 9, 
 130, 0, 8, 130, 
 0, 16, 130, 0, 
 64, 2, 0, 65, 
 0, 0, 208, 0, 
 4, 136, 16, 64, 
 128, 2, 0, 129, 
 128, 0, 128, 128, 
 0, 129, 16, 8, 
 8, 2, 0, 136, 
 128, 0, 24, 128, 
 0, 9, 130, 0, 
 128, 20, 0, 8, 
 20, 0, 1, 20, 
 0, 16, 0, 4, 
 24, 16, 64, 16, 
 0, 4, 65, 16, 
 32, 64, 2, 0, 
 72, 0, 0, 82, 
 0, 0, 81, 0, 
 4, 17, 16, 32, 
 1, 2, 0, 17, 
 0, 0, 131, 48, 
 0, 16, 48, 0, 
 64, 0, 72, 2, 
};

const uint8_t kmap0_word_len12_anagram0_seqs[] = {
 223, 243, 68, 175, 
 251, 213, 103, 129, 
 175, 248, 139, 205, 
 24, 138, 217, 178, 
 109, 149, 46, 220, 
 175, 77, 212, 186, 
 29, 218, 49, 205, 
 209, 203, 2, 76, 
 175, 100, 73, 189, 
 20, 68, 177, 201, 
 170, 77, 26, 163, 
 177, 209, 84, 173, 
 213, 91, 199, 243, 
 58, 150, 252, 203, 
 208, 220, 202, 131, 
 188, 179, 63, 11, 
 189, 211, 123, 145, 
 199, 153, 125, 77, 
};

const LookupOfLength kmap0_word_len12_anagram0 = {
  192, // seq_bit_len_and_anagram
  48, // num_chords
  kmap0_word_len12_anagram0_chords, // chords
  kmap0_word_len12_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len12_anagram1_chords[] = {
 0, 4, 3, 0, 
 4, 129, 0, 4, 
 17, 0, 4, 18, 
 128, 0, 130, 144, 
 8, 0, 16, 1, 
 0, 32, 1, 0, 
 16, 32, 16, 2, 
 0, 65, 16, 8, 
 1, 0, 4, 9, 
 20, 0, 16, 22, 
 0, 0, 2, 0, 
 66, 2, 0, 80, 
 128, 0, 72, 48, 
 0, 64, 128, 0, 
 9, 128, 0, 1, 
};

const uint8_t kmap0_word_len12_anagram1_seqs[] = {
 143, 251, 180, 63, 
 139, 63, 24, 228, 
 20, 135, 125, 220, 
 208, 211, 188, 201, 
 171, 191, 213, 83, 
 219, 140, 205, 61, 
 28, 202, 217, 27, 
 186, 17, 
};

const LookupOfLength kmap0_word_len12_anagram1 = {
  193, // seq_bit_len_and_anagram
  20, // num_chords
  kmap0_word_len12_anagram1_chords, // chords
  kmap0_word_len12_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len12_anagram2_chords[] = {
 16, 64, 8, 0, 
 4, 129, 128, 0, 
 8, 0, 4, 17, 
 0, 0, 146, 2, 
 0, 65, 0, 4, 
 65, 0, 4, 9, 
 2, 0, 9, 
};

const uint8_t kmap0_word_len12_anagram2_seqs[] = {
 210, 74, 191, 26, 
 58, 191, 115, 193, 
 189, 188, 191, 175, 
 219, 10, 
};

const LookupOfLength kmap0_word_len12_anagram2 = {
  194, // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_word_len12_anagram2_chords, // chords
  kmap0_word_len12_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len12_anagram3_chords[] = {
 0, 4, 18, 
};

const uint8_t kmap0_word_len12_anagram3_seqs[] = {
 63, 8, 
};

const LookupOfLength kmap0_word_len12_anagram3 = {
  195, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len12_anagram3_chords, // chords
  kmap0_word_len12_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len13_anagram0_chords[] = {
 0, 32, 192, 0, 
 32, 129, 48, 5, 
 0, 2, 68, 0, 
 2, 12, 0, 0, 
 68, 8, 0, 12, 
 16, 48, 12, 0, 
 52, 0, 1, 4, 
 4, 2, 128, 8, 
 2, 132, 0, 2, 
 32, 0, 3, 2, 
 64, 16, 2, 64, 
 64, 48, 64, 0, 
 48, 1, 1, 0, 
 36, 64, 2, 32, 
 64, 2, 32, 1, 
 128, 32, 1, 50, 
 8, 0, 4, 4, 
 128, 0, 64, 130, 
 48, 1, 128, 2, 
 64, 128, 0, 12, 
 2, 0, 12, 128, 
 0, 12, 8, 0, 
 12, 1, 16, 72, 
 0, 16, 40, 0, 
 2, 8, 2, 2, 
 8, 8, 2, 8, 
 1, 32, 0, 9, 
 128, 64, 128, 160, 
 0, 16, 160, 0, 
 64, 160, 0, 1, 
 4, 4, 8, 20, 
 32, 0, 6, 0, 
 8, 4, 0, 129, 
 132, 0, 64, 132, 
 0, 16, 0, 64, 
 129, 2, 8, 16, 
 6, 0, 16, 32, 
 0, 24, 0, 68, 
 64, 0, 64, 65, 
 32, 0, 72, 4, 
 4, 1, 6, 0, 
 1, 132, 0, 1, 
 32, 4, 128, 32, 
 0, 80, 48, 8, 
 2, 4, 0, 130, 
 16, 0, 26, 16, 
 0, 82, 16, 0, 
 19, 
};

const uint8_t kmap0_word_len13_anagram0_seqs[] = {
 130, 89, 240, 254, 
 237, 111, 249, 157, 
 94, 229, 79, 122, 
 209, 167, 23, 191, 
 98, 36, 140, 138, 
 121, 101, 143, 108, 
 150, 217, 183, 23, 
 62, 195, 102, 216, 
 11, 99, 91, 52, 
 125, 37, 148, 228, 
 155, 90, 166, 199, 
 244, 148, 94, 211, 
 111, 178, 76, 134, 
 169, 49, 181, 166, 
 94, 205, 27, 36, 
 35, 79, 100, 142, 
 188, 245, 181, 66, 
 215, 214, 74, 91, 
 131, 235, 68, 153, 
 157, 78, 211, 117, 
 178, 242, 75, 94, 
 201, 89, 247, 235, 
 118, 221, 168, 249, 
 41, 243, 136, 198, 
 139, 90, 88, 11, 
 115, 225, 5, 
};

const LookupOfLength kmap0_word_len13_anagram0 = {
  208, // seq_bit_len_and_anagram
  63, // num_chords
  kmap0_word_len13_anagram0_chords, // chords
  kmap0_word_len13_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len13_anagram1_chords[] = {
 0, 68, 2, 0, 
 12, 2, 128, 64, 
 2, 128, 64, 1, 
 48, 1, 8, 0, 
 36, 1, 2, 32, 
 64, 2, 8, 64, 
 6, 0, 128, 4, 
 4, 2, 4, 4, 
 128, 4, 4, 16, 
 4, 4, 1, 6, 
 0, 2, 6, 0, 
 1, 132, 0, 1, 
 0, 12, 16, 16, 
 1, 16, 48, 1, 
 16, 2, 64, 16, 
 128, 64, 16, 4, 
 4, 64, 0, 32, 
 64, 34, 0, 8, 
 32, 0, 24, 48, 
 8, 16, 
};

const uint8_t kmap0_word_len13_anagram1_seqs[] = {
 248, 18, 63, 201, 
 64, 25, 123, 91, 
 225, 111, 51, 108, 
 78, 212, 181, 62, 
 214, 167, 250, 83, 
 127, 107, 99, 237, 
 173, 177, 243, 105, 
 124, 140, 239, 105, 
 57, 33, 249, 43, 
 51, 204, 218, 121, 
 84, 244, 0, 
};

const LookupOfLength kmap0_word_len13_anagram1 = {
  209, // seq_bit_len_and_anagram
  26, // num_chords
  kmap0_word_len13_anagram1_chords, // chords
  kmap0_word_len13_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len13_anagram2_chords[] = {
 0, 12, 64, 48, 
 1, 128, 16, 8, 
 0, 132, 0, 1, 
 48, 1, 64, 4, 
 4, 64, 
};

const uint8_t kmap0_word_len13_anagram2_seqs[] = {
 207, 233, 54, 37, 
 167, 168, 203, 190, 
 185, 62, 
};

const LookupOfLength kmap0_word_len13_anagram2 = {
  210, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_word_len13_anagram2_chords, // chords
  kmap0_word_len13_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len13_anagram3_chords[] = {
 128, 64, 2, 6, 
 0, 64, 
};

const uint8_t kmap0_word_len13_anagram3_seqs[] = {
 24, 146, 187, 2, 
};

const LookupOfLength kmap0_word_len13_anagram3 = {
  211, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len13_anagram3_chords, // chords
  kmap0_word_len13_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len14_anagram0_chords[] = {
 0, 96, 128, 0, 
 68, 0, 160, 5, 
 0, 0, 4, 26, 
 32, 5, 16, 36, 
 4, 8, 36, 4, 
 16, 52, 64, 0, 
 38, 0, 8, 166, 
 0, 0, 38, 0, 
 1, 36, 4, 2, 
 4, 0, 2, 16, 
 65, 0, 48, 72, 
 0, 2, 64, 0, 
 6, 64, 0, 160, 
 64, 0, 32, 64, 
 16, 16, 0, 192, 
 48, 9, 0, 16, 
 0, 10, 0, 5, 
 8, 0, 5, 16, 
 0, 5, 1, 2, 
 1, 2, 2, 1, 
 1, 128, 1, 16, 
 32, 5, 64, 32, 
 5, 2, 32, 1, 
 2, 34, 1, 1, 
 160, 1, 1, 0, 
 100, 0, 0, 44, 
 0, 16, 32, 18, 
 2, 40, 0, 132, 
 32, 0, 2, 0, 
 146, 2, 1, 8, 
 34, 1, 8, 2, 
 0, 19, 36, 4, 
 128, 32, 5, 128, 
 0, 4, 146, 38, 
 0, 128, 160, 1, 
 128, 0, 76, 0, 
 4, 12, 0, 2, 
 72, 0, 128, 72, 
 0, 4, 8, 2, 
 32, 8, 1, 16, 
 64, 10, 32, 8, 
 8, 128, 0, 18, 
 4, 68, 0, 6, 
 32, 0, 132, 64, 
 0, 4, 8, 16, 
 32, 8, 16, 0, 
 4, 82, 16, 0, 
 72, 34, 1, 64, 
 32, 8, 64, 0, 
 0, 90, 36, 4, 
 1, 32, 5, 1, 
 4, 8, 1, 128, 
 0, 19, 0, 0, 
 19, 32, 12, 128, 
 32, 12, 8, 32, 
 12, 16, 32, 12, 
 1, 34, 12, 0, 
};

const uint8_t kmap0_word_len14_anagram0_seqs[] = {
 130, 229, 75, 249, 
 119, 188, 22, 63, 
 247, 249, 122, 254, 
 156, 150, 103, 235, 
 217, 113, 246, 226, 
 159, 88, 171, 244, 
 33, 45, 202, 150, 
 178, 171, 204, 33, 
 243, 152, 216, 78, 
 183, 21, 125, 188, 
 30, 63, 199, 239, 
 209, 120, 244, 30, 
 49, 247, 243, 141, 
 127, 35, 222, 189, 
 119, 44, 124, 9, 
 63, 65, 23, 176, 
 19, 140, 218, 84, 
 180, 30, 173, 119, 
 111, 65, 127, 210, 
 223, 244, 5, 245, 
 73, 113, 167, 151, 
 233, 107, 106, 153, 
 66, 166, 138, 41, 
 175, 250, 170, 57, 
 197, 20, 245, 101, 
 133, 93, 67, 78, 
 77, 147, 19, 127, 
 193, 182, 114, 223, 
 156, 19, 23, 186, 
 127, 238, 223, 155, 
 234, 70, 177, 83, 
 136, 79, 226, 171, 
 248, 35, 254, 138, 
 253, 
};

const LookupOfLength kmap0_word_len14_anagram0 = {
  224, // seq_bit_len_and_anagram
  76, // num_chords
  kmap0_word_len14_anagram0_chords, // chords
  kmap0_word_len14_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len14_anagram1_chords[] = {
 36, 4, 2, 4, 
 12, 0, 4, 4, 
 0, 32, 12, 16, 
 36, 4, 1, 36, 
 0, 2, 0, 68, 
 0, 2, 72, 0, 
 6, 32, 0, 34, 
 8, 0, 36, 0, 
 192, 48, 9, 0, 
 128, 8, 0, 128, 
 64, 0, 160, 1, 
 16, 144, 64, 2, 
 52, 1, 0, 36, 
 0, 1, 16, 0, 
 144, 0, 0, 82, 
 16, 0, 17, 16, 
 64, 3, 
};

const uint8_t kmap0_word_len14_anagram1_seqs[] = {
 127, 226, 167, 250, 
 181, 190, 56, 231, 
 47, 230, 42, 95, 
 202, 78, 176, 107, 
 231, 68, 39, 39, 
 223, 41, 82, 72, 
 25, 115, 199, 213, 
 213, 119, 205, 59, 
 54, 113, 193, 59, 
 246, 213, 11, 
};

const LookupOfLength kmap0_word_len14_anagram1 = {
  225, // seq_bit_len_and_anagram
  22, // num_chords
  kmap0_word_len14_anagram1_chords, // chords
  kmap0_word_len14_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len14_anagram2_chords[] = {
 164, 0, 1, 0, 
 0, 18, 16, 65, 
 0, 128, 1, 0, 
 48, 9, 0, 32, 
 8, 64, 132, 0, 
 0, 164, 0, 16, 
 16, 0, 9, 16, 
 0, 129, 
};

const uint8_t kmap0_word_len14_anagram2_seqs[] = {
 103, 44, 78, 113, 
 88, 30, 17, 183, 
 83, 202, 92, 163, 
 78, 156, 107, 235, 
 154, 12, 
};

const LookupOfLength kmap0_word_len14_anagram2 = {
  226, // seq_bit_len_and_anagram
  10, // num_chords
  kmap0_word_len14_anagram2_chords, // chords
  kmap0_word_len14_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len14_anagram3_chords[] = {
 164, 0, 16, 
};

const uint8_t kmap0_word_len14_anagram3_seqs[] = {
 103, 12, 
};

const LookupOfLength kmap0_word_len14_anagram3 = {
  227, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len14_anagram3_chords, // chords
  kmap0_word_len14_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len14_anagram4_chords[] = {
 164, 0, 16, 0, 
 4, 18, 
};

const uint8_t kmap0_word_len14_anagram4_seqs[] = {
 231, 196, 124, 1, 
};

const LookupOfLength kmap0_word_len14_anagram4 = {
  228, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len14_anagram4_chords, // chords
  kmap0_word_len14_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len15_anagram0_chords[] = {
 16, 0, 128, 16, 
 4, 10, 0, 13, 
 64, 36, 68, 0, 
 38, 64, 0, 36, 
 0, 1, 52, 0, 
 18, 16, 4, 66, 
 18, 0, 130, 16, 
 0, 130, 16, 0, 
 11, 18, 0, 3, 
 144, 0, 18, 34, 
 65, 0, 0, 64, 
 18, 0, 64, 82, 
 18, 0, 18, 0, 
 9, 1, 4, 1, 
 1, 32, 1, 8, 
 32, 1, 16, 36, 
 1, 64, 16, 32, 
 16, 160, 33, 0, 
 38, 8, 0, 2, 
 9, 8, 16, 73, 
 0, 2, 9, 1, 
 16, 4, 129, 0, 
 68, 130, 16, 4, 
 136, 16, 0, 200, 
 18, 0, 136, 144, 
 0, 136, 144, 0, 
 192, 128, 64, 130, 
 0, 12, 18, 16, 
 8, 1, 16, 8, 
 16, 32, 9, 64, 
 16, 4, 24, 18, 
 0, 10, 18, 0, 
 8, 144, 0, 72, 
 144, 0, 9, 128, 
 64, 10, 128, 13, 
 0, 144, 0, 10, 
 4, 4, 18, 16, 
 4, 17, 16, 4, 
 144, 16, 0, 25, 
 16, 0, 81, 144, 
 0, 144, 144, 0, 
 80, 128, 64, 18, 
 36, 0, 16, 16, 
 4, 192, 16, 0, 
 67, 16, 64, 64, 
 16, 8, 64, 16, 
 0, 73, 18, 0, 
 65, 4, 0, 82, 
 36, 0, 64, 0, 
 8, 82, 16, 0, 
 65, 18, 0, 17, 
 128, 64, 3, 34, 
 8, 0, 0, 68, 
 66, 2, 64, 10, 
 0, 8, 146, 160, 
 0, 18, 
};

const uint8_t kmap0_word_len15_anagram0_seqs[] = {
 128, 236, 87, 244, 
 115, 233, 124, 121, 
 182, 60, 243, 158, 
 133, 241, 217, 232, 
 38, 52, 17, 90, 
 23, 123, 141, 49, 
 150, 125, 203, 41, 
 100, 193, 158, 198, 
 99, 211, 177, 245, 
 200, 122, 228, 185, 
 43, 67, 143, 97, 
 220, 125, 166, 214, 
 82, 73, 186, 212, 
 75, 191, 166, 191, 
 146, 95, 201, 202, 
 212, 106, 10, 53, 
 5, 155, 226, 154, 
 190, 72, 246, 38, 
 143, 19, 223, 234, 
 31, 109, 180, 182, 
 90, 131, 173, 177, 
 214, 184, 198, 151, 
 66, 209, 245, 139, 
 249, 245, 248, 105, 
 172, 59, 230, 157, 
 32, 79, 176, 39, 
 174, 147, 79, 126, 
 50, 27, 151, 109, 
 201, 118, 98, 235, 
 114, 175, 185, 22, 
 156, 79, 46, 210, 
 154, 119, 123, 188, 
 215, 16, 59, 93, 
 159, 175, 173, 69, 
 162, 34, 50, 
};

const LookupOfLength kmap0_word_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  74, // num_chords
  kmap0_word_len15_anagram0_chords, // chords
  kmap0_word_len15_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len15_anagram1_chords[] = {
 0, 13, 2, 16, 
 4, 16, 16, 4, 
 18, 144, 0, 10, 
 0, 68, 18, 160, 
 65, 0, 16, 4, 
 24, 48, 1, 0, 
 0, 69, 0, 32, 
 1, 128, 36, 5, 
 0, 16, 32, 128, 
 32, 32, 0, 16, 
 0, 145, 16, 4, 
 130, 16, 4, 136, 
 16, 0, 192, 4, 
 72, 0, 0, 9, 
 1, 32, 72, 0, 
 16, 64, 8, 144, 
 0, 8, 128, 64, 
 10, 4, 32, 0, 
 38, 1, 0, 16, 
 0, 19, 18, 0, 
 18, 32, 1, 16, 
 0, 68, 66, 16, 
 4, 192, 16, 4, 
 65, 18, 0, 80, 
 16, 0, 194, 18, 
 0, 72, 16, 4, 
 129, 16, 0, 129, 
 16, 0, 131, 18, 
 0, 17, 144, 0, 
 9, 128, 64, 3, 
 16, 64, 2, 2, 
 64, 3, 
};

const uint8_t kmap0_word_len15_anagram1_seqs[] = {
 143, 165, 31, 63, 
 254, 24, 67, 45, 
 191, 144, 113, 251, 
 71, 125, 223, 199, 
 203, 35, 211, 253, 
 21, 218, 4, 51, 
 20, 240, 210, 163, 
 233, 213, 100, 230, 
 84, 101, 218, 35, 
 101, 169, 182, 212, 
 80, 199, 85, 43, 
 172, 181, 239, 49, 
 238, 52, 122, 242, 
 205, 127, 101, 63, 
 177, 127, 217, 211, 
 236, 11, 110, 245, 
 62, 121, 77, 180, 
 190, 216, 246, 108, 
 168, 55, 174, 87, 
 203, 107, 47, 
};

const LookupOfLength kmap0_word_len15_anagram1 = {
  241, // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_word_len15_anagram1_chords, // chords
  kmap0_word_len15_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len15_anagram2_chords[] = {
 36, 0, 64, 16, 
 4, 65, 32, 1, 
 128, 160, 65, 0, 
 32, 1, 8, 0, 
 36, 18, 18, 0, 
 17, 144, 0, 8, 
 16, 0, 72, 16, 
 0, 73, 20, 0, 
 16, 16, 4, 18, 
 16, 4, 16, 0, 
 68, 18, 18, 0, 
 80, 16, 0, 192, 
 2, 9, 64, 144, 
 0, 192, 16, 4, 
 17, 16, 0, 25, 
 16, 32, 1, 18, 
 0, 129, 36, 0, 
 1, 
};

const uint8_t kmap0_word_len15_anagram2_seqs[] = {
 103, 102, 63, 239, 
 65, 249, 14, 121, 
 103, 133, 95, 244, 
 122, 212, 161, 106, 
 102, 53, 111, 181, 
 103, 30, 61, 63, 
 158, 191, 78, 179, 
 217, 68, 92, 106, 
 14, 242, 250, 103, 
 61, 186, 208, 222, 
 38, 111, 62, 1, 
};

const LookupOfLength kmap0_word_len15_anagram2 = {
  242, // seq_bit_len_and_anagram
  23, // num_chords
  kmap0_word_len15_anagram2_chords, // chords
  kmap0_word_len15_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len15_anagram3_chords[] = {
 32, 1, 8, 32, 
 13, 0, 16, 0, 
 9, 128, 64, 10, 
};

const uint8_t kmap0_word_len15_anagram3_seqs[] = {
 183, 230, 244, 247, 
 90, 247, 26, 10, 
};

const LookupOfLength kmap0_word_len15_anagram3 = {
  243, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_word_len15_anagram3_chords, // chords
  kmap0_word_len15_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len15_anagram4_chords[] = {
 128, 64, 2, 
};

const uint8_t kmap0_word_len15_anagram4_seqs[] = {
 24, 87, 
};

const LookupOfLength kmap0_word_len15_anagram4 = {
  244, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len15_anagram4_chords, // chords
  kmap0_word_len15_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len15_anagram5_chords[] = {
 16, 4, 16, 
};

const uint8_t kmap0_word_len15_anagram5_seqs[] = {
 227, 31, 
};

const LookupOfLength kmap0_word_len15_anagram5 = {
  245, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len15_anagram5_chords, // chords
  kmap0_word_len15_anagram5_seqs, // sequences
};

const uint8_t kmap0_word_len15_anagram7_chords[] = {
 0, 68, 18, 
};

const uint8_t kmap0_word_len15_anagram7_seqs[] = {
 215, 31, 
};

const LookupOfLength kmap0_word_len15_anagram7 = {
  247, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len15_anagram7_chords, // chords
  kmap0_word_len15_anagram7_seqs, // sequences
};

const uint8_t kmap0_word_len16_anagram0_chords[] = {
 16, 32, 144, 128, 
 4, 192, 2, 4, 
 9, 36, 5, 0, 
 52, 0, 8, 38, 
 1, 0, 164, 0, 
 18, 0, 4, 130, 
 16, 12, 2, 20, 
 4, 2, 0, 4, 
 19, 0, 4, 67, 
 128, 4, 3, 144, 
 64, 2, 130, 0, 
 130, 144, 8, 2, 
 128, 0, 130, 148, 
 0, 2, 128, 0, 
 67, 0, 0, 147, 
 48, 0, 18, 48, 
 0, 3, 16, 68, 
 1, 16, 68, 128, 
 16, 68, 8, 20, 
 64, 0, 144, 64, 
 64, 144, 64, 8, 
 32, 72, 0, 16, 
 36, 2, 144, 32, 
 2, 18, 64, 1, 
 176, 0, 16, 48, 
 8, 8, 48, 8, 
 16, 20, 0, 130, 
 16, 1, 128, 16, 
 1, 1, 16, 65, 
 2, 34, 1, 0, 
 0, 1, 146, 16, 
 1, 16, 0, 1, 
 18, 32, 5, 0, 
 32, 5, 18, 48, 
 1, 8, 16, 36, 
 16, 16, 36, 1, 
 16, 32, 128, 144, 
 32, 16, 16, 32, 
 130, 18, 32, 16, 
 128, 96, 2, 36, 
 32, 0, 32, 33, 
 0, 130, 0, 10, 
 18, 68, 0, 18, 
 64, 128, 2, 1, 
 18, 2, 0, 80, 
 130, 0, 24, 22, 
 8, 0, 0, 4, 
 144, 16, 9, 18, 
 2, 73, 0, 0, 
 4, 193, 16, 64, 
 136, 2, 0, 137, 
 130, 0, 136, 2, 
 0, 193, 128, 4, 
 136, 128, 0, 192, 
 128, 0, 193, 16, 
 12, 128, 16, 8, 
 129, 16, 8, 9, 
 18, 8, 2, 18, 
 8, 128, 18, 8, 
 8, 144, 8, 16, 
 144, 8, 1, 2, 
 4, 136, 16, 12, 
 8, 128, 4, 8, 
 148, 0, 8, 128, 
 4, 144, 128, 4, 
 18, 20, 4, 128, 
 4, 68, 2, 4, 
 65, 0, 20, 4, 
 64, 20, 0, 144, 
 22, 0, 128, 22, 
 0, 8, 148, 0, 
 1, 148, 0, 64, 
 2, 4, 144, 2, 
 4, 24, 16, 68, 
 16, 18, 64, 16, 
 22, 0, 16, 128, 
 0, 144, 128, 0, 
 17, 48, 0, 144, 
 16, 12, 64, 0, 
 4, 74, 18, 8, 
 64, 16, 64, 72, 
 144, 32, 64, 18, 
 64, 64, 2, 0, 
 192, 130, 0, 72, 
 2, 0, 194, 130, 
 0, 192, 144, 8, 
 64, 128, 0, 72, 
 128, 0, 81, 20, 
 0, 66, 16, 8, 
 65, 20, 0, 65, 
 48, 0, 80, 2, 
 4, 129, 0, 4, 
 129, 20, 4, 1, 
 0, 4, 131, 16, 
 12, 1, 16, 32, 
 3, 16, 64, 9, 
 16, 8, 17, 16, 
 32, 9, 18, 8, 
 1, 130, 0, 9, 
 128, 0, 25, 48, 
 0, 17, 48, 0, 
 9, 52, 64, 2, 
 32, 8, 18, 20, 
 8, 8, 
};

const uint8_t kmap0_word_len16_anagram0_seqs[] = {
 130, 199, 79, 28, 
 175, 219, 231, 223, 
 167, 173, 103, 223, 
 103, 20, 248, 68, 
 248, 201, 248, 213, 
 248, 179, 248, 188, 
 24, 191, 24, 210, 
 24, 77, 24, 201, 
 24, 65, 24, 213, 
 24, 188, 184, 67, 
 152, 199, 152, 215, 
 242, 215, 210, 79, 
 210, 175, 210, 174, 
 50, 204, 50, 212, 
 82, 148, 126, 132, 
 70, 24, 150, 189, 
 206, 19, 22, 173, 
 22, 61, 190, 168, 
 135, 77, 135, 189, 
 135, 175, 71, 223, 
 7, 21, 199, 216, 
 199, 20, 247, 223, 
 247, 23, 183, 213, 
 208, 63, 208, 191, 
 208, 68, 208, 19, 
 208, 23, 176, 199, 
 48, 174, 48, 159, 
 48, 223, 141, 161, 
 45, 253, 45, 201, 
 125, 20, 61, 205, 
 61, 161, 93, 214, 
 2, 63, 37, 23, 
 165, 150, 244, 188, 
 100, 149, 212, 186, 
 212, 161, 212, 188, 
 20, 175, 20, 204, 
 20, 188, 201, 79, 
 201, 180, 201, 186, 
 169, 209, 169, 201, 
 169, 213, 41, 198, 
 41, 214, 250, 77, 
 250, 201, 250, 26, 
 81, 173, 49, 79, 
 49, 248, 245, 201, 
 245, 175, 85, 30, 
 213, 207, 213, 67, 
 181, 201, 181, 213, 
 53, 188, 53, 216, 
 243, 77, 243, 173, 
 227, 151, 211, 210, 
 211, 213, 19, 68, 
 19, 177, 147, 201, 
 252, 201, 140, 175, 
 236, 212, 108, 149, 
 12, 195, 220, 210, 
 220, 68, 220, 161, 
 220, 23, 28, 77, 
 28, 201, 28, 161, 
 28, 179, 92, 141, 
 188, 78, 188, 174, 
 156, 199, 251, 77, 
 251, 68, 251, 213, 
 251, 23, 235, 79, 
 107, 132, 107, 149, 
 235, 73, 11, 173, 
 219, 201, 219, 161, 
 59, 161, 59, 217, 
 155, 213, 87, 159, 
 69, 78, 101, 173, 
};

const LookupOfLength kmap0_word_len16_anagram0 = {
  256, // seq_bit_len_and_anagram
  138, // num_chords
  kmap0_word_len16_anagram0_chords, // chords
  kmap0_word_len16_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len16_anagram1_chords[] = {
 16, 36, 2, 128, 
 4, 129, 52, 0, 
 16, 38, 0, 0, 
 0, 4, 130, 128, 
 4, 130, 130, 0, 
 10, 16, 68, 16, 
 16, 72, 0, 18, 
 64, 1, 144, 64, 
 64, 22, 0, 2, 
 160, 1, 0, 16, 
 36, 1, 144, 32, 
 128, 144, 32, 64, 
 2, 0, 9, 130, 
 0, 9, 18, 8, 
 1, 16, 68, 128, 
 18, 8, 128, 16, 
 12, 128, 16, 12, 
 1, 16, 12, 8, 
 16, 8, 64, 32, 
 9, 0, 16, 64, 
 24, 144, 64, 8, 
 148, 0, 8, 128, 
 1, 0, 148, 0, 
 128, 148, 0, 16, 
 2, 4, 192, 0, 
 4, 193, 128, 0, 
 193, 128, 0, 192, 
 0, 4, 81, 0, 
 4, 65, 2, 4, 
 129, 2, 0, 129, 
 128, 0, 129, 48, 
 0, 80, 128, 96, 
 2, 
};

const uint8_t kmap0_word_len16_anagram1_seqs[] = {
 143, 208, 79, 27, 
 167, 61, 103, 159, 
 248, 132, 24, 79, 
 24, 173, 210, 63, 
 210, 78, 178, 189, 
 50, 216, 174, 141, 
 71, 220, 240, 215, 
 48, 200, 48, 216, 
 173, 189, 173, 27, 
 189, 78, 228, 151, 
 212, 201, 233, 201, 
 233, 215, 201, 175, 
 201, 204, 41, 223, 
 234, 145, 26, 210, 
 26, 213, 113, 28, 
 53, 200, 19, 213, 
 252, 77, 252, 180, 
 76, 177, 28, 20, 
 188, 63, 188, 191, 
 219, 79, 219, 180, 
 27, 65, 153, 61, 
 87, 24, 
};

const LookupOfLength kmap0_word_len16_anagram1 = {
  257, // seq_bit_len_and_anagram
  43, // num_chords
  kmap0_word_len16_anagram1_chords, // chords
  kmap0_word_len16_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len16_anagram2_chords[] = {
 32, 13, 0, 36, 
 4, 18, 16, 68, 
 16, 18, 64, 2, 
 144, 64, 8, 34, 
 1, 0, 16, 12, 
 1, 20, 4, 2, 
 36, 0, 0, 148, 
 0, 16, 2, 0, 
 193, 0, 4, 3, 
 18, 64, 1, 128, 
 0, 129, 
};

const uint8_t kmap0_word_len16_anagram2_seqs[] = {
 47, 222, 231, 23, 
 242, 199, 178, 209, 
 86, 25, 119, 31, 
 201, 191, 245, 209, 
 53, 159, 227, 26, 
 76, 189, 251, 184, 
 219, 210, 27, 68, 
};

const LookupOfLength kmap0_word_len16_anagram2 = {
  258, // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_word_len16_anagram2_chords, // chords
  kmap0_word_len16_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len16_anagram3_chords[] = {
 34, 1, 0, 16, 
 8, 0, 16, 12, 
 1, 128, 0, 8, 
 20, 4, 16, 
};

const uint8_t kmap0_word_len16_anagram3_seqs[] = {
 119, 223, 201, 201, 
 201, 251, 26, 161, 
 227, 175, 
};

const LookupOfLength kmap0_word_len16_anagram3 = {
  259, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_word_len16_anagram3_chords, // chords
  kmap0_word_len16_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len17_anagram0_chords[] = {
 52, 4, 128, 2, 
 68, 2, 128, 12, 
 1, 160, 4, 1, 
 32, 4, 130, 52, 
 4, 16, 52, 4, 
 64, 52, 4, 8, 
 52, 0, 9, 52, 
 0, 65, 52, 4, 
 1, 54, 0, 1, 
 180, 0, 8, 164, 
 64, 2, 36, 1, 
 0, 48, 5, 2, 
 0, 36, 66, 48, 
 12, 2, 0, 36, 
 10, 0, 36, 18, 
 0, 36, 3, 6, 
 0, 130, 32, 0, 
 131, 0, 68, 17, 
 0, 68, 1, 16, 
 68, 0, 18, 72, 
 0, 2, 64, 3, 
 2, 64, 17, 2, 
 64, 66, 2, 64, 
 65, 128, 64, 16, 
 48, 64, 2, 16, 
 4, 82, 48, 65, 
 0, 50, 8, 128, 
 16, 5, 2, 16, 
 5, 16, 16, 5, 
 1, 18, 1, 64, 
 18, 1, 128, 18, 
 1, 8, 18, 1, 
 16, 16, 5, 128, 
 48, 5, 1, 176, 
 1, 64, 176, 1, 
 8, 32, 1, 18, 
 32, 9, 18, 2, 
 36, 16, 0, 36, 
 128, 0, 36, 129, 
 16, 100, 0, 20, 
 36, 0, 16, 96, 
 128, 16, 40, 128, 
 20, 32, 128, 18, 
 96, 0, 2, 32, 
 9, 144, 40, 0, 
 148, 32, 0, 128, 
 32, 65, 54, 0, 
 128, 130, 64, 128, 
 2, 32, 10, 162, 
 0, 64, 16, 9, 
 8, 2, 68, 128, 
 0, 68, 136, 16, 
 1, 129, 6, 0, 
 192, 128, 68, 128, 
 132, 0, 128, 128, 
 64, 144, 176, 8, 
 128, 16, 76, 0, 
 2, 12, 128, 2, 
 12, 8, 0, 12, 
 80, 0, 12, 17, 
 0, 12, 64, 0, 
 12, 130, 16, 40, 
 2, 144, 8, 0, 
 16, 72, 8, 16, 
 40, 64, 2, 8, 
 128, 18, 8, 0, 
 2, 8, 9, 2, 
 8, 66, 2, 8, 
 64, 2, 8, 130, 
 144, 72, 0, 128, 
 8, 1, 128, 8, 
 64, 128, 8, 65, 
 0, 32, 137, 128, 
 8, 24, 160, 0, 
 8, 48, 64, 8, 
 32, 0, 136, 130, 
 8, 1, 176, 8, 
 8, 176, 8, 16, 
 6, 4, 8, 6, 
 4, 16, 4, 4, 
 16, 4, 4, 17, 
 4, 4, 64, 4, 
 4, 65, 6, 0, 
 128, 22, 0, 0, 
 4, 4, 136, 132, 
 0, 129, 148, 8, 
 0, 132, 0, 17, 
 52, 0, 16, 2, 
 68, 16, 0, 68, 
 24, 16, 0, 146, 
 2, 32, 18, 128, 
 68, 16, 128, 8, 
 16, 48, 64, 16, 
 32, 0, 81, 16, 
 5, 64, 48, 5, 
 64, 2, 68, 64, 
 0, 68, 72, 16, 
 9, 64, 16, 1, 
 192, 16, 96, 64, 
 0, 9, 82, 2, 
 64, 192, 2, 8, 
 192, 4, 4, 72, 
 132, 4, 64, 128, 
 64, 192, 160, 0, 
 192, 128, 12, 64, 
 6, 0, 72, 0, 
 64, 192, 132, 0, 
 65, 34, 0, 65, 
 20, 8, 1, 0, 
 36, 9, 0, 36, 
 1, 16, 40, 1, 
 2, 32, 65, 128, 
 64, 129, 128, 8, 
 129, 160, 0, 17, 
 2, 8, 17, 6, 
 0, 17, 32, 0, 
 25, 34, 0, 9, 
 34, 0, 129, 48, 
 8, 17, 48, 8, 
 65, 50, 8, 2, 
 176, 8, 1, 32, 
 76, 2, 0, 68, 
 18, 16, 64, 18, 
 0, 8, 130, 16, 
 4, 18, 
};

const uint8_t kmap0_word_len17_anagram0_seqs[] = {
 127, 146, 31, 91, 
 254, 70, 250, 188, 
 241, 249, 226, 252, 
 241, 249, 236, 211, 
 175, 167, 117, 79, 
 243, 158, 222, 63, 
 123, 125, 134, 250, 
 140, 235, 153, 111, 
 252, 219, 248, 12, 
 241, 69, 35, 124, 
 69, 248, 131, 240, 
 23, 169, 43, 102, 
 90, 249, 179, 242, 
 247, 165, 95, 74, 
 167, 150, 141, 43, 
 123, 86, 54, 163, 
 108, 94, 25, 49, 
 50, 163, 253, 92, 
 88, 222, 182, 216, 
 116, 60, 250, 240, 
 207, 225, 223, 163, 
 205, 71, 147, 143, 
 86, 31, 61, 62, 
 200, 127, 255, 250, 
 14, 243, 29, 234, 
 59, 23, 119, 145, 
 224, 247, 192, 39, 
 130, 79, 11, 253, 
 18, 250, 43, 52, 
 73, 104, 74, 208, 
 84, 97, 75, 195, 
 214, 133, 145, 12, 
 163, 26, 6, 111, 
 159, 228, 150, 65, 
 173, 8, 59, 50, 
 151, 212, 166, 111, 
 73, 175, 146, 124, 
 44, 53, 87, 138, 
 151, 20, 81, 41, 
 70, 82, 136, 78, 
 47, 157, 190, 41, 
 125, 107, 250, 225, 
 244, 179, 233, 153, 
 211, 95, 36, 35, 
 76, 78, 145, 172, 
 50, 153, 97, 106, 
 162, 212, 201, 169, 
 117, 83, 51, 166, 
 102, 78, 125, 145, 
 66, 58, 69, 108, 
 10, 230, 20, 188, 
 42, 120, 53, 38, 
 105, 100, 213, 44, 
 173, 153, 40, 82, 
 111, 136, 214, 16, 
 61, 245, 91, 235, 
 247, 212, 159, 175, 
 63, 91, 159, 185, 
 62, 111, 109, 162, 
 218, 213, 149, 94, 
 43, 197, 214, 112, 
 170, 49, 91, 243, 
 120, 190, 229, 188, 
 202, 49, 21, 211, 
 8, 39, 94, 78, 
 68, 154, 44, 61, 
 153, 151, 255, 48, 
 255, 109, 254, 150, 
 252, 42, 217, 46, 
 177, 233, 96, 104, 
 201, 165, 130, 169, 
 37, 83, 39, 214, 
 175, 28, 95, 57, 
 72, 114, 80, 230, 
 72, 207, 181, 149, 
 203, 16, 111, 84, 
 206, 189, 235, 84, 
 23, 190, 46, 252, 
 93, 232, 180, 176, 
 121, 131, 228, 70, 
 162, 141, 60, 59, 
 157, 118, 186, 110, 
 30, 205, 218, 155, 
 183, 73, 244, 172, 
 104, 94, 177, 209, 
 98, 172, 175, 47, 
 94, 191, 184, 122, 
 124, 145, 168, 240, 
 15, 
};

const LookupOfLength kmap0_word_len17_anagram0 = {
  272, // seq_bit_len_and_anagram
  166, // num_chords
  kmap0_word_len17_anagram0_chords, // chords
  kmap0_word_len17_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len17_anagram1_chords[] = {
 0, 32, 128, 0, 
 36, 18, 52, 4, 
 16, 52, 4, 1, 
 52, 0, 0, 52, 
 0, 128, 52, 0, 
 129, 180, 0, 16, 
 36, 0, 18, 16, 
 5, 2, 0, 12, 
 130, 128, 64, 130, 
 4, 4, 18, 132, 
 0, 18, 144, 72, 
 0, 2, 68, 128, 
 128, 64, 128, 48, 
 8, 8, 16, 5, 
 16, 16, 5, 1, 
 16, 65, 0, 16, 
 1, 128, 16, 1, 
 129, 18, 1, 16, 
 144, 1, 16, 48, 
 5, 16, 128, 36, 
 128, 2, 32, 128, 
 128, 32, 24, 2, 
 12, 128, 0, 12, 
 144, 16, 9, 8, 
 16, 5, 128, 18, 
 1, 128, 50, 8, 
 128, 2, 8, 8, 
 128, 8, 8, 128, 
 8, 24, 132, 0, 
 64, 20, 64, 8, 
 6, 0, 130, 132, 
 0, 128, 132, 0, 
 16, 132, 0, 65, 
 48, 12, 64, 2, 
 32, 65, 128, 32, 
 65, 6, 0, 192, 
 132, 0, 192, 160, 
 0, 192, 4, 4, 
 72, 20, 64, 64, 
 2, 8, 65, 2, 
 32, 9, 50, 8, 
 8, 132, 8, 0, 
};

const uint8_t kmap0_word_len17_anagram1_seqs[] = {
 130, 137, 126, 16, 
 158, 254, 57, 253, 
 123, 218, 245, 52, 
 209, 105, 218, 51, 
 198, 103, 46, 240, 
 15, 227, 83, 194, 
 32, 137, 243, 21, 
 39, 170, 116, 10, 
 217, 79, 50, 136, 
 172, 57, 29, 63, 
 62, 126, 125, 216, 
 242, 48, 209, 97, 
 218, 163, 61, 71, 
 140, 111, 255, 192, 
 167, 128, 77, 4, 
 99, 180, 211, 147, 
 192, 167, 146, 173, 
 228, 63, 168, 15, 
 83, 139, 78, 173, 
 157, 66, 35, 197, 
 104, 68, 229, 106, 
 149, 181, 47, 106, 
 16, 213, 136, 169, 
 193, 203, 47, 154, 
 97, 47, 195, 88, 
 166, 174, 76, 81, 
 57, 50, 113, 125, 
 229, 106, 201, 219, 
 105, 97, 171, 232, 
 214, 178, 17, 
};

const LookupOfLength kmap0_word_len17_anagram1 = {
  273, // seq_bit_len_and_anagram
  56, // num_chords
  kmap0_word_len17_anagram1_chords, // chords
  kmap0_word_len17_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len17_anagram2_chords[] = {
 36, 1, 0, 0, 
 12, 130, 48, 1, 
 8, 48, 12, 128, 
 176, 1, 16, 2, 
 32, 65, 128, 32, 
 1, 48, 8, 8, 
 128, 8, 8, 6, 
 0, 64, 132, 0, 
 128, 132, 0, 18, 
 48, 5, 16, 132, 
 0, 65, 4, 4, 
 17, 
};

const uint8_t kmap0_word_len17_anagram2_seqs[] = {
 103, 62, 144, 62, 
 89, 111, 181, 248, 
 116, 199, 24, 54, 
 47, 140, 216, 100, 
 205, 41, 66, 107, 
 51, 215, 8, 170, 
 19, 56, 127, 155, 
 107, 236, 206, 87, 
};

const LookupOfLength kmap0_word_len17_anagram2 = {
  274, // seq_bit_len_and_anagram
  15, // num_chords
  kmap0_word_len17_anagram2_chords, // chords
  kmap0_word_len17_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len17_anagram3_chords[] = {
 128, 64, 18, 20, 
 0, 16, 
};

const uint8_t kmap0_word_len17_anagram3_seqs[] = {
 24, 35, 235, 184, 
 2, 
};

const LookupOfLength kmap0_word_len17_anagram3 = {
  275, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len17_anagram3_chords, // chords
  kmap0_word_len17_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len17_anagram5_chords[] = {
 0, 68, 18, 
};

const uint8_t kmap0_word_len17_anagram5_seqs[] = {
 248, 35, 1, 
};

const LookupOfLength kmap0_word_len17_anagram5 = {
  277, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len17_anagram5_chords, // chords
  kmap0_word_len17_anagram5_seqs, // sequences
};

const uint8_t kmap0_word_len18_anagram0_chords[] = {
 48, 40, 128, 176, 
 1, 0, 160, 0, 
 128, 128, 8, 8, 
 32, 36, 1, 0, 
 77, 2, 38, 4, 
 128, 36, 4, 64, 
 52, 68, 0, 52, 
 12, 0, 52, 1, 
 0, 52, 64, 8, 
 166, 0, 64, 52, 
 0, 128, 164, 0, 
 129, 164, 0, 128, 
 164, 0, 24, 164, 
 0, 130, 16, 13, 
 2, 4, 12, 2, 
 36, 4, 18, 16, 
 33, 2, 6, 32, 
 2, 132, 8, 2, 
 128, 1, 10, 52, 
 0, 2, 0, 76, 
 8, 0, 100, 64, 
 52, 64, 1, 16, 
 65, 8, 16, 64, 
 26, 2, 96, 64, 
 160, 64, 2, 132, 
 64, 16, 32, 68, 
 16, 32, 64, 65, 
 20, 40, 0, 0, 
 5, 3, 16, 69, 
 0, 2, 5, 128, 
 2, 5, 16, 0, 
 5, 128, 0, 5, 
 65, 0, 5, 130, 
 18, 65, 0, 2, 
 1, 128, 2, 1, 
 65, 2, 1, 130, 
 0, 5, 129, 128, 
 1, 9, 128, 1, 
 128, 128, 1, 1, 
 128, 1, 17, 128, 
 1, 130, 34, 1, 
 128, 34, 1, 144, 
 34, 5, 128, 160, 
 5, 128, 52, 1, 
 16, 0, 100, 8, 
 0, 100, 16, 0, 
 44, 16, 4, 36, 
 16, 48, 44, 0, 
 52, 32, 16, 128, 
 96, 128, 128, 96, 
 0, 160, 32, 16, 
 0, 40, 129, 32, 
 32, 128, 32, 32, 
 9, 6, 12, 0, 
 6, 8, 128, 130, 
 1, 8, 164, 0, 
 144, 20, 9, 0, 
 4, 12, 128, 32, 
 5, 136, 16, 13, 
 128, 2, 1, 129, 
 18, 9, 128, 160, 
 1, 136, 160, 64, 
 128, 0, 44, 64, 
 0, 44, 1, 2, 
 72, 128, 2, 72, 
 8, 128, 72, 128, 
 176, 8, 0, 32, 
 8, 65, 16, 9, 
 10, 160, 12, 8, 
 128, 0, 154, 160, 
 12, 128, 52, 5, 
 0, 6, 68, 0, 
 4, 36, 1, 36, 
 0, 192, 132, 64, 
 8, 52, 8, 16, 
 36, 0, 128, 36, 
 0, 9, 34, 1, 
 24, 32, 32, 80, 
 16, 13, 64, 16, 
 0, 74, 6, 32, 
 64, 132, 32, 64, 
 32, 32, 65, 34, 
 1, 72, 4, 8, 
 65, 128, 5, 64, 
 128, 1, 65, 160, 
 1, 72, 164, 0, 
 64, 4, 12, 64, 
 36, 0, 72, 0, 
 4, 83, 32, 32, 
 66, 160, 64, 64, 
 16, 13, 1, 16, 
 32, 19, 2, 0, 
 27, 16, 9, 17, 
 48, 1, 16, 34, 
 12, 16, 32, 12, 
 65, 48, 72, 8, 
 34, 12, 128, 34, 
 12, 64, 160, 8, 
 129, 20, 64, 2, 
 16, 64, 130, 16, 
 64, 11, 0, 96, 
 18, 18, 64, 10, 
 18, 64, 18, 18, 
 64, 66, 16, 36, 
 18, 6, 8, 0, 
 4, 40, 64, 
};

const uint8_t kmap0_word_len18_anagram0_seqs[] = {
 130, 69, 131, 219, 
 1, 40, 50, 72, 
 161, 159, 23, 254, 
 181, 116, 126, 211, 
 249, 204, 167, 95, 
 158, 254, 116, 218, 
 199, 105, 149, 103, 
 7, 159, 148, 125, 
 6, 237, 25, 65, 
 103, 140, 158, 113, 
 129, 95, 50, 126, 
 170, 248, 115, 34, 
 244, 129, 176, 43, 
 70, 170, 24, 122, 
 96, 62, 45, 63, 
 169, 124, 134, 210, 
 231, 74, 31, 42, 
 173, 133, 108, 134, 
 50, 48, 203, 137, 
 42, 243, 188, 204, 
 188, 78, 21, 30, 
 143, 123, 188, 244, 
 241, 77, 199, 247, 
 28, 79, 116, 60, 
 239, 241, 23, 71, 
 91, 30, 77, 116, 
 52, 239, 209, 23, 
 7, 253, 30, 161, 
 123, 68, 208, 17, 
 177, 71, 204, 30, 
 113, 113, 55, 209, 
 221, 67, 55, 245, 
 223, 241, 116, 143, 
 43, 124, 149, 240, 
 71, 194, 159, 4, 
 127, 42, 124, 209, 
 208, 115, 194, 32, 
 9, 35, 36, 140, 
 60, 112, 19, 193, 
 76, 4, 179, 110, 
 167, 175, 157, 42, 
 181, 30, 33, 16, 
 103, 201, 174, 244, 
 169, 210, 235, 77, 
 254, 18, 245, 177, 
 212, 37, 83, 232, 
 77, 145, 101, 122, 
 134, 233, 23, 166, 
 38, 153, 90, 101, 
 10, 146, 41, 68, 
 167, 204, 171, 198, 
 146, 134, 248, 161, 
 84, 132, 248, 84, 
 255, 118, 253, 150, 
 245, 23, 86, 202, 
 92, 67, 101, 29, 
 139, 53, 19, 213, 
 172, 59, 173, 247, 
 100, 134, 252, 37, 
 51, 90, 205, 176, 
 43, 195, 168, 12, 
 243, 114, 235, 205, 
 105, 43, 199, 241, 
 28, 199, 114, 232, 
 205, 145, 43, 215, 
 79, 92, 179, 242, 
 126, 193, 25, 33, 
 103, 25, 251, 37, 
 47, 116, 177, 173, 
 197, 142, 75, 121, 
 110, 139, 63, 45, 
 62, 175, 104, 149, 
 98, 63, 137, 205, 
 47, 6, 237, 213, 
 174, 87, 19, 93, 
 173, 123, 133, 197, 
 181, 213, 215, 30, 
 95, 155, 93, 248, 
 97, 217, 174, 101, 
 25, 2, 
};

const LookupOfLength kmap0_word_len18_anagram0 = {
  288, // seq_bit_len_and_anagram
  141, // num_chords
  kmap0_word_len18_anagram0_chords, // chords
  kmap0_word_len18_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len18_anagram1_chords[] = {
 52, 0, 8, 0, 
 12, 64, 160, 5, 
 128, 0, 4, 146, 
 36, 4, 24, 38, 
 4, 64, 164, 4, 
 1, 164, 0, 1, 
 164, 0, 64, 0, 
 5, 130, 2, 0, 
 19, 16, 64, 18, 
 16, 69, 0, 32, 
 68, 128, 48, 64, 
 0, 16, 0, 25, 
 48, 1, 64, 34, 
 5, 8, 48, 13, 
 0, 48, 1, 128, 
 160, 5, 1, 160, 
 1, 1, 0, 36, 
 64, 4, 32, 1, 
 32, 32, 17, 16, 
 64, 146, 128, 0, 
 146, 160, 1, 128, 
 128, 72, 0, 164, 
 0, 144, 4, 12, 
 128, 4, 12, 64, 
 20, 9, 0, 164, 
 0, 16, 4, 12, 
 16, 128, 1, 16, 
 16, 0, 72, 34, 
 1, 72, 36, 4, 
 192, 32, 5, 65, 
 16, 0, 193, 32, 
 64, 65, 0, 0, 
 90, 16, 0, 73, 
 32, 32, 65, 52, 
 0, 1, 20, 0, 
 19, 16, 64, 67, 
 0, 4, 26, 
};

const uint8_t kmap0_word_len18_anagram1_seqs[] = {
 224, 180, 2, 254, 
 244, 116, 199, 19, 
 21, 231, 143, 158, 
 253, 124, 198, 239, 
 25, 177, 103, 48, 
 227, 211, 129, 189, 
 5, 142, 175, 210, 
 127, 200, 252, 36, 
 179, 180, 117, 61, 
 71, 102, 223, 223, 
 122, 127, 242, 77, 
 217, 119, 252, 222, 
 177, 1, 159, 33, 
 220, 173, 48, 207, 
 10, 248, 42, 16, 
 5, 197, 29, 41, 
 66, 198, 41, 80, 
 159, 82, 125, 78, 
 213, 46, 213, 200, 
 51, 159, 234, 68, 
 28, 108, 101, 115, 
 223, 202, 244, 39, 
 239, 223, 188, 54, 
 241, 102, 201, 133, 
 226, 90, 217, 11, 
 51, 111, 62, 189, 
 69, 245, 213, 188, 
 197, 143, 2, 
};

const LookupOfLength kmap0_word_len18_anagram1 = {
  289, // seq_bit_len_and_anagram
  49, // num_chords
  kmap0_word_len18_anagram1_chords, // chords
  kmap0_word_len18_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len18_anagram2_chords[] = {
 36, 4, 128, 38, 
 0, 128, 0, 4, 
 146, 50, 72, 0, 
 128, 72, 0, 16, 
 0, 131, 16, 0, 
 130, 16, 13, 0, 
 34, 1, 144, 16, 
 4, 192, 48, 13, 
 0, 32, 8, 1, 
 0, 4, 19, 16, 
 68, 18, 16, 64, 
 2, 128, 64, 2, 
 4, 12, 0, 
};

const uint8_t kmap0_word_len18_anagram2_seqs[] = {
 231, 19, 157, 77, 
 132, 244, 133, 108, 
 209, 50, 34, 153, 
 140, 235, 11, 227, 
 241, 201, 2, 125, 
 147, 159, 157, 124, 
 127, 202, 187, 59, 
 95, 92, 127, 124, 
 181, 229, 53, 174, 
 101, 191, 2, 
};

const LookupOfLength kmap0_word_len18_anagram2 = {
  290, // seq_bit_len_and_anagram
  17, // num_chords
  kmap0_word_len18_anagram2_chords, // chords
  kmap0_word_len18_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len18_anagram3_chords[] = {
 18, 0, 129, 48, 
 1, 128, 0, 4, 
 146, 16, 13, 128, 
 16, 0, 81, 16, 
 68, 18, 
};

const uint8_t kmap0_word_len18_anagram3_seqs[] = {
 166, 94, 31, 217, 
 36, 240, 5, 125, 
 201, 188, 246, 92, 
 253, 3, 
};

const LookupOfLength kmap0_word_len18_anagram3 = {
  291, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_word_len18_anagram3_chords, // chords
  kmap0_word_len18_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len19_anagram0_chords[] = {
 2, 1, 16, 16, 
 4, 130, 18, 4, 
 136, 144, 4, 136, 
 36, 68, 8, 36, 
 36, 64, 36, 36, 
 1, 38, 64, 8, 
 38, 64, 16, 36, 
 36, 128, 36, 0, 
 144, 164, 64, 128, 
 164, 8, 0, 164, 
 32, 1, 36, 0, 
 24, 52, 0, 19, 
 16, 4, 138, 144, 
 0, 138, 144, 0, 
 194, 36, 0, 130, 
 128, 9, 2, 132, 
 0, 18, 20, 0, 
 18, 16, 73, 64, 
 32, 72, 16, 16, 
 64, 144, 144, 0, 
 16, 130, 65, 0, 
 2, 65, 8, 2, 
 9, 16, 2, 33, 
 64, 4, 5, 128, 
 6, 1, 128, 128, 
 65, 128, 128, 65, 
 0, 160, 1, 16, 
 128, 9, 16, 32, 
 1, 128, 32, 1, 
 10, 48, 13, 0, 
 50, 9, 0, 32, 
 69, 128, 160, 65, 
 128, 160, 65, 0, 
 32, 69, 16, 32, 
 13, 16, 48, 1, 
 18, 34, 65, 16, 
 38, 1, 16, 0, 
 37, 128, 32, 37, 
 8, 16, 32, 10, 
 18, 41, 0, 48, 
 33, 0, 18, 0, 
 72, 18, 0, 24, 
 18, 0, 137, 36, 
 1, 144, 20, 9, 
 1, 2, 9, 128, 
 130, 9, 128, 2, 
 9, 9, 0, 13, 
 130, 0, 68, 146, 
 16, 4, 145, 0, 
 68, 138, 16, 4, 
 152, 16, 4, 193, 
 38, 8, 128, 2, 
 9, 136, 128, 9, 
 130, 128, 9, 128, 
 144, 0, 208, 32, 
 1, 136, 16, 13, 
 0, 0, 12, 26, 
 32, 40, 2, 32, 
 40, 64, 0, 13, 
 10, 16, 0, 139, 
 2, 9, 10, 48, 
 9, 8, 144, 4, 
 10, 144, 0, 73, 
 20, 13, 0, 22, 
 0, 2, 22, 9, 
 0, 38, 1, 8, 
 4, 4, 146, 132, 
 0, 146, 164, 0, 
 16, 36, 32, 64, 
 0, 13, 18, 18, 
 4, 80, 0, 13, 
 24, 18, 0, 88, 
 2, 9, 80, 0, 
 13, 66, 16, 4, 
 194, 144, 0, 82, 
 16, 32, 80, 2, 
 9, 66, 18, 0, 
 74, 2, 9, 72, 
 20, 0, 192, 18, 
 0, 194, 128, 64, 
 194, 128, 64, 74, 
 128, 9, 66, 16, 
 4, 65, 144, 0, 
 193, 144, 0, 81, 
 128, 64, 67, 32, 
 1, 80, 0, 13, 
 129, 0, 13, 9, 
 0, 13, 65, 16, 
 0, 131, 16, 32, 
 17, 16, 32, 65, 
 2, 9, 3, 128, 
 9, 1, 128, 64, 
 11, 2, 64, 11, 
 132, 0, 19, 48, 
 8, 18, 162, 72, 
 0, 2, 68, 3, 
 0, 68, 11, 0, 
 68, 26, 16, 96, 
 10, 2, 64, 130, 
 128, 64, 26, 0, 
 12, 146, 32, 0, 
 16, 
};

const uint8_t kmap0_word_len19_anagram0_seqs[] = {
 224, 152, 126, 68, 
 211, 83, 91, 159, 
 66, 125, 190, 202, 
 243, 25, 158, 191, 
 240, 108, 149, 103, 
 143, 60, 233, 225, 
 73, 121, 206, 32, 
 121, 70, 164, 51, 
 22, 158, 121, 244, 
 44, 214, 72, 126, 
 69, 10, 53, 82, 
 176, 145, 242, 137, 
 17, 37, 140, 90, 
 224, 216, 85, 154, 
 75, 114, 114, 50, 
 73, 143, 103, 98, 
 142, 150, 113, 180, 
 202, 163, 39, 29, 
 205, 240, 160, 175, 
 7, 117, 61, 130, 
 228, 17, 33, 143, 
 200, 115, 76, 164, 
 35, 19, 29, 89, 
 241, 126, 209, 119, 
 139, 190, 233, 229, 
 29, 36, 239, 8, 
 121, 207, 203, 123, 
 62, 221, 227, 226, 
 158, 150, 247, 116, 
 133, 79, 7, 124, 
 189, 161, 21, 13, 
 187, 100, 152, 111, 
 183, 154, 185, 85, 
 61, 173, 107, 18, 
 168, 119, 201, 117, 
 75, 77, 84, 106, 
 138, 146, 246, 210, 
 99, 137, 94, 22, 
 244, 235, 161, 191, 
 42, 249, 71, 201, 
 207, 75, 157, 78, 
 106, 45, 81, 96, 
 137, 34, 74, 20, 
 236, 161, 172, 119, 
 250, 146, 211, 107, 
 145, 50, 194, 148, 
 25, 234, 99, 73, 
 125, 177, 218, 88, 
 210, 92, 114, 160, 
 95, 67, 217, 91, 
 253, 165, 218, 70, 
 215, 46, 185, 182, 
 222, 149, 190, 168, 
 65, 69, 157, 56, 
 107, 102, 56, 143, 
 165, 249, 102, 207, 
 107, 105, 204, 173, 
 211, 92, 226, 199, 
 18, 227, 147, 25, 
 99, 204, 208, 30, 
 110, 44, 113, 43, 
 154, 91, 75, 76, 
 118, 101, 106, 52, 
 83, 92, 89, 227, 
 202, 129, 37, 222, 
 95, 243, 6, 153, 
 55, 198, 188, 113, 
 229, 60, 199, 62, 
 149, 246, 181, 180, 
 207, 165, 245, 197, 
 46, 244, 120, 161, 
 217, 219, 88, 218, 
 136, 210, 198, 85, 
 247, 218, 186, 69, 
 13, 209, 83, 136, 
 209, 242, 250, 189, 
 215, 215, 189, 254, 
 232, 21, 90, 175, 
 77, 116, 141, 209, 
 226, 19, 21, 145, 
 7, 
};

const LookupOfLength kmap0_word_len19_anagram0 = {
  304, // seq_bit_len_and_anagram
  135, // num_chords
  kmap0_word_len19_anagram0_chords, // chords
  kmap0_word_len19_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len19_anagram1_chords[] = {
 2, 64, 0, 16, 
 4, 145, 16, 32, 
 18, 16, 73, 2, 
 16, 64, 72, 16, 
 32, 17, 18, 0, 
 131, 0, 13, 16, 
 2, 9, 128, 50, 
 9, 0, 128, 13, 
 0, 128, 9, 16, 
 128, 32, 146, 18, 
 0, 25, 16, 4, 
 152, 16, 0, 147, 
 20, 0, 144, 2, 
 9, 64, 16, 4, 
 208, 16, 32, 130, 
 144, 0, 192, 16, 
 8, 17, 146, 0, 
 72, 20, 4, 2, 
 164, 1, 16, 16, 
 4, 19, 144, 0, 
 17, 128, 9, 18, 
 16, 4, 82, 16, 
 32, 65, 2, 9, 
 192, 2, 9, 72, 
 16, 4, 81, 16, 
 4, 193, 144, 0, 
 73, 0, 13, 3, 
 16, 32, 1, 18, 
 0, 129, 16, 4, 
 17, 0, 68, 130, 
 18, 64, 2, 160, 
 0, 18, 
};

const uint8_t kmap0_word_len19_anagram1_seqs[] = {
 160, 129, 124, 90, 
 15, 66, 123, 164, 
 177, 36, 173, 108, 
 47, 244, 248, 162, 
 247, 248, 73, 71, 
 83, 58, 90, 244, 
 17, 159, 142, 152, 
 4, 131, 138, 214, 
 245, 8, 248, 85, 
 192, 184, 2, 118, 
 45, 53, 51, 61, 
 123, 200, 70, 72, 
 17, 236, 228, 245, 
 104, 52, 187, 250, 
 209, 117, 226, 30, 
 63, 238, 120, 39, 
 38, 176, 196, 248, 
 99, 134, 246, 114, 
 83, 137, 75, 173, 
 188, 63, 230, 245, 
 19, 111, 168, 247, 
 177, 180, 246, 194, 
 237, 37, 239, 248, 
 247, 250, 68, 215, 
 150, 46, 34, 15, 
};

const LookupOfLength kmap0_word_len19_anagram1 = {
  305, // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_word_len19_anagram1_chords, // chords
  kmap0_word_len19_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len19_anagram2_chords[] = {
 16, 4, 24, 164, 
 64, 8, 36, 0, 
 128, 16, 4, 146, 
 128, 9, 18, 32, 
 69, 16, 160, 1, 
 128, 34, 8, 0, 
 4, 4, 18, 144, 
 0, 73, 16, 32, 
 17, 16, 4, 19, 
 0, 68, 130, 16, 
 64, 130, 128, 64, 
 130, 
};

const uint8_t kmap0_word_len19_anagram2_seqs[] = {
 63, 214, 63, 67, 
 229, 153, 137, 144, 
 252, 131, 49, 37, 
 57, 127, 31, 145, 
 169, 83, 78, 117, 
 190, 224, 181, 198, 
 194, 177, 119, 30, 
 125, 253, 139, 171, 
 73, 94, 35, 8, 
};

const LookupOfLength kmap0_word_len19_anagram2 = {
  306, // seq_bit_len_and_anagram
  15, // num_chords
  kmap0_word_len19_anagram2_chords, // chords
  kmap0_word_len19_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len19_anagram3_chords[] = {
 16, 4, 19, 48, 
 9, 0, 16, 4, 
 138, 16, 4, 65, 
 52, 8, 16, 
};

const uint8_t kmap0_word_len19_anagram3_seqs[] = {
 248, 235, 185, 237, 
 18, 189, 162, 247, 
 121, 45, 122, 78, 
};

const LookupOfLength kmap0_word_len19_anagram3 = {
  307, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_word_len19_anagram3_chords, // chords
  kmap0_word_len19_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len19_anagram4_chords[] = {
 16, 4, 145, 
};

const uint8_t kmap0_word_len19_anagram4_seqs[] = {
 79, 158, 5, 
};

const LookupOfLength kmap0_word_len19_anagram4 = {
  308, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len19_anagram4_chords, // chords
  kmap0_word_len19_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len20_anagram0_chords[] = {
 0, 72, 0, 0, 
 1, 16, 32, 12, 
 0, 128, 4, 19, 
 48, 4, 3, 48, 
 5, 16, 2, 4, 
 192, 130, 4, 9, 
 2, 4, 194, 128, 
 4, 138, 52, 13, 
 0, 36, 5, 8, 
 54, 9, 0, 164, 
 1, 128, 0, 4, 
 138, 128, 4, 10, 
 48, 4, 66, 16, 
 36, 66, 16, 32, 
 67, 32, 33, 2, 
 22, 0, 3, 0, 
 4, 194, 128, 4, 
 67, 128, 0, 146, 
 128, 0, 75, 18, 
 8, 18, 16, 68, 
 10, 0, 77, 16, 
 16, 68, 129, 2, 
 73, 64, 128, 73, 
 2, 16, 64, 80, 
 144, 64, 24, 32, 
 65, 16, 36, 72, 
 0, 32, 64, 19, 
 16, 12, 66, 18, 
 12, 128, 18, 32, 
 3, 48, 8, 9, 
 16, 12, 130, 148, 
 0, 130, 16, 1, 
 10, 32, 65, 8, 
 32, 5, 8, 36, 
 5, 16, 48, 1, 
 24, 48, 65, 18, 
 0, 45, 2, 144, 
 32, 128, 144, 32, 
 24, 34, 33, 0, 
 128, 41, 0, 144, 
 32, 129, 32, 33, 
 8, 132, 32, 18, 
 2, 0, 11, 18, 
 68, 128, 2, 4, 
 25, 130, 0, 25, 
 50, 0, 64, 2, 
 0, 67, 130, 0, 
 152, 128, 0, 216, 
 2, 73, 8, 16, 
 68, 136, 144, 8, 
 136, 48, 8, 128, 
 128, 4, 130, 32, 
 9, 130, 32, 9, 
 144, 0, 13, 16, 
 16, 12, 9, 16, 
 12, 129, 144, 8, 
 129, 32, 9, 8, 
 0, 4, 200, 32, 
 12, 26, 16, 36, 
 9, 176, 0, 24, 
 48, 8, 24, 48, 
 0, 88, 130, 4, 
 64, 148, 4, 16, 
 144, 64, 16, 144, 
 32, 17, 4, 13, 
 2, 4, 13, 16, 
 20, 4, 80, 20, 
 4, 65, 6, 9, 
 2, 6, 9, 8, 
 20, 4, 130, 20, 
 4, 136, 20, 4, 
 129, 132, 9, 16, 
 20, 0, 80, 22, 
 0, 18, 36, 8, 
 0, 130, 4, 17, 
 48, 8, 144, 176, 
 0, 17, 128, 4, 
 200, 148, 0, 66, 
 48, 8, 80, 48, 
 8, 72, 16, 36, 
 80, 20, 32, 64, 
 16, 32, 192, 18, 
 32, 72, 144, 32, 
 72, 144, 32, 80, 
 128, 96, 66, 2, 
 4, 72, 22, 8, 
 64, 2, 9, 64, 
 6, 9, 64, 20, 
 0, 193, 18, 64, 
 192, 148, 0, 192, 
 16, 8, 192, 18, 
 8, 192, 2, 4, 
 200, 128, 4, 208, 
 130, 0, 74, 20, 
 4, 66, 20, 0, 
 67, 20, 64, 64, 
 20, 0, 73, 22, 
 0, 72, 22, 0, 
 80, 2, 4, 81, 
 0, 4, 81, 16, 
 68, 65, 16, 12, 
 65, 32, 9, 66, 
 4, 68, 66, 2, 
 72, 66, 16, 36, 
 3, 18, 32, 17, 
 144, 32, 65, 18, 
 8, 17, 128, 4, 
 65, 130, 0, 11, 
 128, 4, 129, 16, 
 68, 17, 2, 4, 
 17, 0, 4, 89, 
 16, 64, 25, 2, 
 4, 145, 18, 64, 
 17, 128, 0, 145, 
 48, 0, 138, 50, 
 0, 9, 32, 12, 
 18, 50, 72, 2, 
 162, 8, 0, 48, 
 69, 2, 0, 76, 
 18, 0, 100, 66, 
 48, 76, 2, 16, 
 73, 2, 0, 100, 
 3, 18, 65, 2, 
 2, 96, 66, 2, 
 96, 3, 128, 100, 
 2, 128, 64, 2, 
 4, 68, 18, 148, 
 8, 16, 148, 8, 
 8, 
};

const uint8_t kmap0_word_len20_anagram0_seqs[] = {
 32, 1, 9, 6, 
 28, 64, 4, 255, 
 184, 49, 143, 121, 
 253, 247, 216, 79, 
 253, 252, 219, 161, 
 127, 209, 252, 23, 
 161, 231, 151, 124, 
 190, 222, 103, 151, 
 124, 82, 220, 248, 
 250, 132, 175, 161, 
 248, 153, 141, 240, 
 217, 8, 205, 139, 
 48, 223, 216, 235, 
 138, 244, 204, 24, 
 207, 139, 65, 49, 
 24, 202, 139, 211, 
 201, 242, 21, 45, 
 127, 74, 210, 180, 
 47, 155, 75, 50, 
 176, 36, 199, 204, 
 114, 66, 45, 39, 
 223, 50, 167, 42, 
 243, 22, 78, 143, 
 236, 244, 77, 94, 
 216, 104, 209, 186, 
 190, 248, 228, 139, 
 26, 135, 21, 125, 
 100, 149, 247, 235, 
 125, 207, 159, 247, 
 216, 122, 143, 175, 
 240, 177, 4, 77, 
 20, 208, 19, 10, 
 251, 134, 48, 162, 
 4, 99, 77, 48, 
 235, 13, 139, 26, 
 125, 169, 216, 210, 
 79, 173, 59, 223, 
 186, 19, 205, 156, 
 221, 188, 141, 2, 
 209, 42, 192, 161, 
 165, 86, 73, 47, 
 173, 228, 20, 74, 
 22, 77, 20, 248, 
 68, 25, 75, 148, 
 167, 148, 126, 74, 
 201, 175, 155, 188, 
 79, 41, 214, 148, 
 178, 222, 250, 252, 
 164, 47, 22, 234, 
 95, 168, 206, 19, 
 106, 209, 163, 121, 
 216, 241, 220, 28, 
 213, 243, 49, 210, 
 19, 11, 61, 245, 
 177, 84, 127, 74, 
 245, 135, 93, 159, 
 215, 181, 177, 84, 
 91, 75, 149, 30, 
 93, 233, 213, 149, 
 126, 93, 99, 74, 
 117, 204, 92, 167, 
 209, 53, 167, 58, 
 191, 29, 99, 209, 
 52, 145, 215, 252, 
 20, 202, 24, 213, 
 236, 17, 205, 22, 
 173, 12, 127, 204, 
 208, 174, 12, 77, 
 196, 176, 213, 12, 
 67, 205, 48, 198, 
 12, 227, 202, 173, 
 223, 220, 101, 205, 
 165, 78, 92, 234, 
 202, 228, 186, 76, 
 45, 205, 20, 213, 
 156, 76, 196, 169, 
 201, 172, 223, 196, 
 65, 63, 28, 218, 
 200, 245, 209, 92, 
 141, 203, 213, 150, 
 92, 173, 203, 181, 
 213, 92, 123, 204, 
 251, 61, 188, 63, 
 203, 235, 151, 188, 
 254, 196, 25, 75, 
 124, 253, 202, 215, 
 78, 235, 71, 184, 
 208, 61, 11, 131, 
 189, 157, 60, 27, 
 207, 187, 161, 141, 
 27, 251, 180, 243, 
 210, 59, 223, 187, 
 243, 202, 59, 86, 
 185, 211, 79, 59, 
 109, 185, 19, 68, 
 89, 145, 156, 181, 
 215, 226, 79, 33, 
 182, 175, 98, 139, 
 113, 253, 219, 215, 
 159, 116, 125, 134, 
 215, 23, 125, 181, 
 75, 87, 248, 123, 
 237, 195, 215, 102, 
 120, 237, 133, 215, 
 120, 120, 141, 144, 
 215, 249, 90, 214, 
 19, 101, 67, 13, 
};

const LookupOfLength kmap0_word_len20_anagram0 = {
  320, // seq_bit_len_and_anagram
  171, // num_chords
  kmap0_word_len20_anagram0_chords, // chords
  kmap0_word_len20_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len20_anagram1_chords[] = {
 144, 0, 144, 4, 
 8, 0, 20, 4, 
 130, 18, 68, 64, 
 36, 5, 16, 36, 
 68, 0, 36, 32, 
 64, 16, 36, 3, 
 16, 32, 66, 144, 
 32, 66, 16, 12, 
 18, 128, 0, 82, 
 0, 68, 10, 50, 
 1, 8, 16, 13, 
 0, 32, 5, 128, 
 48, 1, 24, 34, 
 1, 1, 164, 1, 
 128, 32, 5, 18, 
 48, 1, 17, 144, 
 32, 80, 16, 68, 
 144, 2, 4, 144, 
 20, 4, 192, 2, 
 4, 137, 48, 12, 
 128, 0, 13, 64, 
 18, 8, 17, 0, 
 40, 19, 48, 8, 
 24, 130, 0, 8, 
 160, 33, 0, 176, 
 0, 17, 20, 4, 
 136, 36, 1, 128, 
 16, 36, 18, 52, 
 0, 144, 2, 0, 
 194, 20, 4, 80, 
 20, 0, 192, 22, 
 0, 66, 2, 4, 
 73, 2, 0, 193, 
 2, 4, 131, 16, 
 40, 1, 2, 4, 
 9, 0, 4, 19, 
 2, 4, 145, 2, 
 4, 25, 16, 68, 
 17, 144, 64, 17, 
 4, 68, 18, 2, 
 64, 130, 2, 64, 
 10, 128, 64, 18, 
 128, 72, 18, 160, 
 5, 18, 
};

const uint8_t kmap0_word_len20_anagram1_seqs[] = {
 64, 32, 12, 42, 
 72, 95, 125, 241, 
 220, 210, 231, 207, 
 113, 126, 150, 103, 
 102, 136, 208, 191, 
 8, 205, 140, 48, 
 216, 56, 254, 132, 
 19, 204, 242, 175, 
 234, 190, 173, 199, 
 151, 124, 208, 223, 
 183, 117, 124, 247, 
 177, 55, 197, 121, 
 207, 23, 247, 216, 
 11, 99, 216, 2, 
 47, 45, 240, 77, 
 244, 149, 77, 191, 
 173, 228, 23, 157, 
 158, 75, 201, 211, 
 155, 138, 133, 234, 
 17, 29, 218, 161, 
 145, 111, 24, 121, 
 61, 245, 213, 84, 
 41, 223, 227, 71, 
 56, 62, 77, 140, 
 77, 205, 245, 199, 
 92, 77, 196, 181, 
 209, 188, 223, 202, 
 219, 68, 251, 23, 
 189, 208, 201, 219, 
 251, 186, 243, 184, 
 59, 223, 180, 243, 
 173, 59, 126, 185, 
 19, 210, 215, 159, 
 122, 109, 146, 215, 
 86, 121, 141, 145, 
 215, 152, 84, 196, 
 253, 
};

const LookupOfLength kmap0_word_len20_anagram1 = {
  321, // seq_bit_len_and_anagram
  58, // num_chords
  kmap0_word_len20_anagram1_chords, // chords
  kmap0_word_len20_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len20_anagram2_chords[] = {
 0, 12, 18, 16, 
 36, 2, 18, 64, 
 18, 128, 64, 10, 
 16, 36, 17, 16, 
 1, 129, 160, 1, 
 16, 32, 1, 16, 
 144, 8, 17, 2, 
 9, 128, 180, 0, 
 64, 20, 4, 144, 
 16, 1, 16, 48, 
 4, 66, 20, 4, 
 66, 20, 4, 80, 
 0, 4, 193, 16, 
 36, 1, 
};

const uint8_t kmap0_word_len20_anagram2_seqs[] = {
 224, 83, 129, 143, 
 208, 216, 210, 35, 
 227, 170, 254, 89, 
 120, 144, 189, 199, 
 196, 125, 231, 201, 
 201, 59, 145, 154, 
 74, 113, 154, 93, 
 253, 67, 227, 195, 
 195, 159, 209, 140, 
 95, 205, 174, 63, 
 188, 79, 180, 208, 
 251, 
};

const LookupOfLength kmap0_word_len20_anagram2 = {
  322, // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_word_len20_anagram2_chords, // chords
  kmap0_word_len20_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len20_anagram3_chords[] = {
 0, 68, 18, 48, 
 1, 24, 160, 1, 
 128, 16, 36, 17, 
};

const uint8_t kmap0_word_len20_anagram3_seqs[] = {
 114, 254, 122, 91, 
 61, 119, 208, 1, 
 253, 179, 
};

const LookupOfLength kmap0_word_len20_anagram3 = {
  323, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_word_len20_anagram3_chords, // chords
  kmap0_word_len20_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len20_anagram4_chords[] = {
 0, 68, 18, 
};

const uint8_t kmap0_word_len20_anagram4_seqs[] = {
 215, 31, 9, 
};

const LookupOfLength kmap0_word_len20_anagram4 = {
  324, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len20_anagram4_chords, // chords
  kmap0_word_len20_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len20_anagram6_chords[] = {
 48, 8, 80, 
};

const uint8_t kmap0_word_len20_anagram6_seqs[] = {
 162, 135, 13, 
};

const LookupOfLength kmap0_word_len20_anagram6 = {
  326, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len20_anagram6_chords, // chords
  kmap0_word_len20_anagram6_seqs, // sequences
};

const uint8_t kmap0_word_len21_anagram0_chords[] = {
 2, 4, 64, 128, 
 0, 152, 0, 4, 
 80, 48, 0, 65, 
 16, 5, 17, 48, 
 5, 9, 0, 12, 
 144, 16, 76, 8, 
 48, 5, 136, 36, 
 13, 2, 36, 13, 
 8, 52, 4, 65, 
 52, 64, 128, 164, 
 64, 130, 164, 64, 
 18, 164, 9, 0, 
 52, 64, 16, 36, 
 0, 82, 52, 4, 
 130, 2, 36, 10, 
 2, 36, 18, 128, 
 36, 66, 0, 36, 
 19, 20, 36, 2, 
 130, 32, 18, 2, 
 12, 130, 128, 32, 
 131, 128, 36, 2, 
 130, 8, 2, 160, 
 0, 11, 160, 0, 
 19, 176, 8, 18, 
 0, 36, 82, 16, 
 100, 1, 16, 65, 
 16, 144, 72, 8, 
 146, 64, 0, 130, 
 64, 66, 128, 64, 
 24, 2, 68, 24, 
 16, 76, 16, 2, 
 64, 144, 32, 73, 
 2, 16, 8, 26, 
 148, 32, 2, 16, 
 5, 192, 16, 5, 
 129, 16, 1, 131, 
 16, 1, 130, 144, 
 1, 18, 160, 65, 
 130, 48, 5, 18, 
 48, 5, 17, 160, 
 65, 18, 20, 44, 
 0, 16, 100, 16, 
 128, 32, 24, 176, 
 32, 64, 130, 64, 
 1, 2, 68, 8, 
 2, 32, 193, 32, 
 0, 209, 34, 9, 
 8, 4, 13, 0, 
 16, 73, 10, 164, 
 9, 8, 48, 5, 
 144, 48, 65, 128, 
 48, 5, 128, 54, 
 0, 144, 2, 8, 
 129, 50, 8, 144, 
 128, 12, 18, 2, 
 12, 10, 20, 12, 
 128, 128, 12, 72, 
 16, 76, 128, 18, 
 76, 0, 18, 72, 
 2, 48, 9, 16, 
 130, 8, 18, 130, 
 8, 24, 144, 72, 
 128, 130, 8, 65, 
 128, 8, 17, 176, 
 8, 64, 50, 12, 
 8, 180, 0, 136, 
 128, 32, 25, 176, 
 8, 136, 0, 65, 
 74, 144, 1, 9, 
 128, 13, 18, 178, 
 8, 128, 6, 4, 
 9, 6, 4, 10, 
 4, 4, 73, 20, 
 4, 16, 134, 4, 
 1, 148, 32, 8, 
 134, 4, 8, 134, 
 0, 129, 6, 4, 
 136, 4, 4, 137, 
 132, 4, 144, 22, 
 64, 16, 22, 8, 
 16, 6, 0, 25, 
 134, 0, 16, 52, 
 0, 192, 36, 9, 
 8, 0, 68, 16, 
 130, 68, 16, 0, 
 36, 26, 48, 5, 
 24, 50, 8, 16, 
 128, 36, 18, 0, 
 68, 192, 132, 0, 
 66, 160, 0, 67, 
 16, 100, 64, 0, 
 36, 192, 16, 44, 
 64, 20, 36, 64, 
 2, 32, 81, 128, 
 32, 81, 48, 12, 
 192, 0, 12, 192, 
 0, 12, 81, 130, 
 64, 192, 176, 8, 
 192, 20, 64, 72, 
 20, 8, 80, 6, 
 0, 193, 134, 0, 
 192, 132, 0, 192, 
 132, 0, 81, 0, 
 64, 209, 48, 5, 
 65, 0, 68, 73, 
 130, 64, 65, 128, 
 64, 65, 128, 8, 
 81, 4, 4, 81, 
 6, 0, 81, 16, 
 0, 211, 52, 0, 
 80, 36, 68, 66, 
 16, 64, 67, 52, 
 4, 129, 16, 44, 
 1, 134, 0, 3, 
 0, 36, 81, 52, 
 0, 129, 32, 4, 
 152, 32, 4, 145, 
 48, 64, 24, 162, 
 0, 8, 34, 0, 
 137, 178, 8, 2, 
 16, 77, 2, 128, 
 104, 2, 34, 65, 
 10, 16, 4, 83, 
 6, 8, 10, 
};

const uint8_t kmap0_word_len21_anagram0_seqs[] = {
 224, 185, 31, 8, 
 132, 2, 254, 121, 
 176, 217, 252, 199, 
 122, 254, 182, 238, 
 211, 79, 250, 100, 
 149, 175, 55, 249, 
 124, 44, 157, 175, 
 165, 211, 207, 123, 
 146, 45, 79, 138, 
 235, 25, 178, 56, 
 35, 74, 231, 216, 
 242, 204, 92, 224, 
 159, 100, 132, 223, 
 138, 240, 123, 16, 
 126, 48, 194, 159, 
 69, 232, 175, 8, 
 163, 7, 233, 59, 
 33, 197, 66, 140, 
 71, 136, 145, 26, 
 49, 178, 46, 70, 
 158, 197, 16, 61, 
 56, 207, 80, 250, 
 23, 74, 31, 30, 
 233, 20, 42, 59, 
 164, 101, 51, 134, 
 12, 141, 145, 243, 
 173, 114, 252, 73, 
 78, 19, 201, 140, 
 37, 171, 83, 225, 
 26, 8, 143, 39, 
 246, 65, 191, 62, 
 200, 184, 7, 249, 
 226, 136, 65, 223, 
 20, 215, 123, 30, 
 125, 143, 127, 239, 
 137, 43, 252, 178, 
 134, 254, 145, 48, 
 52, 6, 70, 102, 
 183, 236, 216, 86, 
 217, 223, 43, 152, 
 5, 50, 111, 169, 
 245, 46, 165, 175, 
 37, 245, 181, 164, 
 113, 210, 207, 109, 
 178, 188, 77, 190, 
 159, 168, 207, 49, 
 117, 234, 165, 22, 
 61, 233, 113, 34, 
 189, 54, 166, 175, 
 228, 244, 28, 154, 
 44, 159, 146, 101, 
 127, 178, 108, 76, 
 158, 219, 169, 113, 
 34, 181, 198, 164, 
 144, 166, 20, 205, 
 155, 98, 99, 82, 
 100, 182, 126, 139, 
 214, 56, 201, 26, 
 179, 80, 67, 52, 
 41, 31, 215, 56, 
 214, 26, 165, 47, 
 130, 90, 116, 253, 
 214, 173, 175, 141, 
 245, 117, 185, 126, 
 245, 212, 223, 142, 
 10, 67, 93, 251, 
 53, 106, 83, 108, 
 165, 111, 173, 244, 
 186, 53, 232, 167, 
 78, 75, 215, 233, 
 228, 58, 173, 91, 
 167, 99, 106, 38, 
 118, 205, 90, 154, 
 151, 63, 243, 178, 
 99, 94, 17, 206, 
 235, 237, 105, 209, 
 51, 241, 8, 249, 
 233, 37, 99, 68, 
 101, 140, 188, 12, 
 95, 154, 225, 19, 
 49, 252, 100, 134, 
 95, 205, 176, 103, 
 25, 198, 44, 211, 
 139, 230, 244, 68, 
 156, 126, 150, 131, 
 90, 114, 144, 104, 
 174, 86, 201, 213, 
 147, 184, 82, 47, 
 215, 104, 226, 26, 
 65, 92, 99, 150, 
 203, 204, 242, 254, 
 109, 222, 87, 201, 
 43, 59, 120, 35, 
 36, 111, 76, 226, 
 157, 175, 188, 211, 
 149, 183, 32, 115, 
 174, 30, 190, 254, 
 201, 87, 123, 247, 
 79, 242, 66, 167, 
 223, 168, 141, 59, 
 207, 112, 115, 37, 
 103, 210, 159, 76, 
 59, 159, 85, 122, 
 178, 118, 104, 214, 
 109, 18, 163, 209, 
 215, 47, 249, 10, 
 35, 93, 91, 239, 
 194, 207, 91, 182, 
 21, 1, 
};

const LookupOfLength kmap0_word_len21_anagram0 = {
  336, // seq_bit_len_and_anagram
  165, // num_chords
  kmap0_word_len21_anagram0_chords, // chords
  kmap0_word_len21_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len21_anagram1_chords[] = {
 16, 100, 0, 48, 
 5, 136, 4, 4, 
 17, 20, 4, 128, 
 52, 0, 192, 164, 
 8, 0, 164, 64, 
 130, 36, 0, 128, 
 36, 8, 0, 0, 
 36, 3, 48, 64, 
 18, 32, 1, 2, 
 16, 0, 146, 2, 
 65, 0, 36, 72, 
 0, 16, 4, 146, 
 16, 0, 27, 128, 
 65, 130, 128, 9, 
 128, 176, 1, 64, 
 160, 9, 16, 52, 
 4, 128, 2, 12, 
 8, 128, 12, 144, 
 134, 0, 3, 4, 
 4, 65, 52, 4, 
 64, 20, 36, 64, 
 134, 0, 9, 32, 
 4, 144, 4, 4, 
 82, 52, 0, 65, 
 0, 36, 192, 128, 
 32, 1, 54, 0, 
 17, 132, 0, 17, 
 32, 0, 81, 160, 
 0, 17, 32, 1, 
 146, 34, 0, 138, 
 16, 77, 2, 2, 
 65, 2, 
};

const uint8_t kmap0_word_len21_anagram1_seqs[] = {
 15, 253, 242, 245, 
 54, 125, 253, 217, 
 175, 149, 124, 146, 
 153, 207, 72, 231, 
 25, 87, 58, 51, 
 157, 103, 78, 21, 
 127, 17, 226, 100, 
 105, 204, 199, 129, 
 5, 146, 101, 31, 
 135, 204, 233, 244, 
 15, 21, 214, 157, 
 226, 160, 184, 30, 
 65, 165, 59, 130, 
 125, 79, 148, 232, 
 79, 83, 122, 237, 
 79, 49, 79, 81, 
 183, 177, 62, 239, 
 215, 207, 236, 10, 
 159, 93, 163, 117, 
 39, 207, 19, 227, 
 124, 101, 111, 174, 
 76, 207, 112, 35, 
 22, 238, 244, 233, 
 157, 136, 186, 147, 
 121, 55, 111, 76, 
 190, 169, 200, 218, 
 23, 87, 127, 233, 
 218, 71, 3, 
};

const LookupOfLength kmap0_word_len21_anagram1 = {
  337, // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_word_len21_anagram1_chords, // chords
  kmap0_word_len21_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len21_anagram2_chords[] = {
 48, 5, 24, 128, 
 9, 16, 48, 8, 
 24, 160, 0, 18, 
 132, 0, 17, 52, 
 0, 80, 176, 8, 
 16, 36, 0, 18, 
 128, 32, 65, 6, 
 0, 192, 160, 0, 
 17, 16, 64, 3, 
 128, 65, 130, 0, 
 64, 2, 
};

const uint8_t kmap0_word_len21_anagram2_seqs[] = {
 175, 183, 231, 136, 
 41, 105, 78, 158, 
 64, 204, 83, 39, 
 54, 106, 30, 246, 
 132, 232, 153, 124, 
 22, 12, 35, 150, 
 107, 19, 237, 68, 
 222, 189, 218, 123, 
 13, 58, 174, 215, 
 43, 
};

const LookupOfLength kmap0_word_len21_anagram2 = {
  338, // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_word_len21_anagram2_chords, // chords
  kmap0_word_len21_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len21_anagram3_chords[] = {
 16, 4, 82, 32, 
 1, 128, 48, 8, 
 8, 
};

const uint8_t kmap0_word_len21_anagram3_seqs[] = {
 102, 254, 226, 206, 
 116, 136, 214, 108, 
};

const LookupOfLength kmap0_word_len21_anagram3 = {
  339, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_word_len21_anagram3_chords, // chords
  kmap0_word_len21_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len21_anagram4_chords[] = {
 16, 4, 146, 
};

const uint8_t kmap0_word_len21_anagram4_seqs[] = {
 99, 250, 2, 
};

const LookupOfLength kmap0_word_len21_anagram4 = {
  340, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len21_anagram4_chords, // chords
  kmap0_word_len21_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len21_anagram5_chords[] = {
 128, 64, 2, 128, 
 64, 18, 
};

const uint8_t kmap0_word_len21_anagram5_seqs[] = {
 64, 198, 21, 35, 
 70, 2, 
};

const LookupOfLength kmap0_word_len21_anagram5 = {
  341, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len21_anagram5_chords, // chords
  kmap0_word_len21_anagram5_seqs, // sequences
};

const uint8_t kmap0_word_len22_anagram0_chords[] = {
 48, 12, 8, 148, 
 0, 0, 2, 36, 
 1, 32, 9, 0, 
 164, 4, 17, 4, 
 68, 1, 2, 76, 
 8, 2, 76, 1, 
 132, 68, 1, 32, 
 68, 129, 34, 5, 
 8, 128, 4, 146, 
 160, 5, 136, 4, 
 36, 128, 128, 4, 
 26, 0, 4, 18, 
 162, 68, 0, 34, 
 68, 1, 164, 4, 
 10, 36, 4, 192, 
 38, 4, 66, 38, 
 4, 192, 38, 4, 
 64, 52, 36, 2, 
 52, 32, 10, 52, 
 68, 128, 52, 12, 
 128, 36, 4, 193, 
 52, 64, 136, 164, 
 0, 65, 38, 4, 
 24, 36, 4, 80, 
 52, 68, 16, 36, 
 9, 2, 36, 9, 
 128, 38, 4, 10, 
 160, 5, 18, 16, 
 32, 66, 18, 33, 
 2, 2, 96, 130, 
 128, 96, 18, 34, 
 8, 130, 4, 12, 
 130, 16, 9, 146, 
 128, 12, 2, 0, 
 5, 19, 16, 4, 
 19, 16, 64, 129, 
 20, 96, 1, 50, 
 72, 128, 160, 64, 
 9, 0, 76, 16, 
 50, 72, 16, 130, 
 64, 16, 176, 72, 
 16, 160, 64, 8, 
 52, 72, 0, 18, 
 0, 25, 16, 33, 
 3, 18, 65, 128, 
 2, 5, 136, 2, 
 1, 81, 128, 5, 
 129, 128, 1, 144, 
 128, 5, 130, 130, 
 1, 128, 16, 13, 
 16, 16, 65, 144, 
 16, 33, 80, 18, 
 65, 16, 128, 1, 
 25, 128, 1, 81, 
 32, 9, 2, 34, 
 5, 9, 32, 5, 
 192, 160, 5, 8, 
 160, 5, 1, 48, 
 69, 16, 34, 5, 
 24, 32, 5, 25, 
 160, 1, 80, 48, 
 1, 64, 48, 44, 
 128, 128, 100, 16, 
 162, 32, 8, 50, 
 13, 0, 2, 5, 
 24, 38, 0, 9, 
 32, 12, 144, 16, 
 9, 144, 144, 9, 
 144, 2, 9, 2, 
 128, 73, 10, 16, 
 0, 145, 176, 65, 
 128, 162, 1, 130, 
 162, 1, 136, 32, 
 32, 138, 0, 44, 
 18, 0, 44, 80, 
 0, 44, 3, 16, 
 8, 18, 16, 8, 
 19, 34, 8, 72, 
 144, 8, 26, 128, 
 40, 9, 160, 8, 
 9, 178, 8, 0, 
 34, 8, 129, 34, 
 8, 66, 0, 4, 
 91, 176, 13, 0, 
 134, 8, 1, 166, 
 0, 17, 160, 5, 
 24, 4, 12, 16, 
 4, 36, 3, 20, 
 0, 26, 132, 32, 
 1, 6, 32, 3, 
 180, 0, 16, 132, 
 8, 16, 180, 8, 
 16, 32, 68, 128, 
 34, 64, 129, 6, 
 68, 16, 16, 68, 
 18, 16, 0, 27, 
 52, 36, 16, 20, 
 0, 146, 2, 72, 
 16, 160, 64, 24, 
 16, 0, 90, 16, 
 64, 82, 32, 8, 
 82, 16, 0, 195, 
 16, 4, 73, 18, 
 0, 80, 16, 0, 
 193, 4, 36, 80, 
 48, 44, 64, 16, 
 33, 192, 2, 0, 
 210, 36, 0, 208, 
 16, 13, 72, 128, 
 0, 82, 160, 64, 
 72, 160, 32, 65, 
 16, 13, 65, 4, 
 12, 65, 128, 0, 
 83, 16, 33, 1, 
 2, 96, 17, 144, 
 9, 9, 160, 32, 
 3, 4, 12, 17, 
 32, 32, 17, 160, 
 8, 17, 18, 64, 
 3, 32, 4, 192, 
 48, 12, 128, 48, 
 9, 1, 178, 72, 
 0, 34, 12, 144, 
 34, 8, 65, 34, 
 12, 65, 34, 12, 
 129, 162, 8, 17, 
 160, 12, 130, 0, 
 77, 130, 16, 68, 
 67, 16, 68, 19, 
 16, 96, 130, 16, 
 96, 18, 2, 73, 
 2, 128, 73, 18, 
 144, 64, 82, 18, 
 64, 19, 144, 64, 
 19, 18, 64, 146, 
 132, 8, 0, 
};

const uint8_t kmap0_word_len22_anagram0_seqs[] = {
 192, 226, 43, 168, 
 81, 13, 22, 126, 
 131, 12, 74, 127, 
 198, 236, 203, 175, 
 251, 50, 181, 190, 
 76, 189, 47, 163, 
 238, 203, 76, 251, 
 247, 183, 62, 81, 
 20, 79, 161, 247, 
 83, 133, 255, 170, 
 81, 252, 204, 23, 
 159, 101, 199, 103, 
 217, 123, 62, 134, 
 158, 207, 79, 231, 
 115, 227, 249, 220, 
 116, 62, 55, 159, 
 126, 132, 167, 21, 
 225, 73, 47, 125, 
 210, 39, 159, 244, 
 188, 39, 89, 229, 
 25, 193, 123, 206, 
 183, 158, 243, 204, 
 231, 248, 229, 153, 
 177, 116, 102, 42, 
 225, 159, 173, 248, 
 115, 7, 66, 155, 
 141, 176, 125, 32, 
 108, 146, 8, 99, 
 36, 182, 216, 132, 
 244, 169, 34, 121, 
 74, 24, 41, 61, 
 206, 31, 139, 227, 
 95, 75, 147, 215, 
 210, 117, 161, 180, 
 216, 36, 67, 243, 
 202, 249, 244, 114, 
 90, 180, 156, 104, 
 41, 39, 68, 203, 
 172, 26, 78, 167, 
 165, 117, 123, 124, 
 120, 17, 30, 109, 
 146, 71, 235, 211, 
 209, 195, 123, 80, 
 252, 30, 20, 49, 
 71, 224, 211, 17, 
 212, 113, 204, 39, 
 31, 227, 50, 199, 
 152, 225, 49, 109, 
 121, 76, 232, 30, 
 19, 188, 71, 198, 
 210, 221, 175, 123, 
 211, 51, 223, 161, 
 250, 119, 236, 254, 
 61, 47, 125, 207, 
 183, 222, 243, 186, 
 247, 4, 243, 157, 
 205, 12, 159, 68, 
 195, 248, 145, 48, 
 119, 104, 167, 191, 
 221, 122, 204, 183, 
 214, 188, 2, 47, 
 190, 128, 167, 36, 
 16, 37, 151, 26, 
 75, 37, 141, 43, 
 121, 215, 67, 33, 
 111, 83, 220, 141, 
 20, 119, 43, 101, 
 69, 152, 126, 16, 
 166, 31, 134, 233, 
 23, 97, 242, 96, 
 145, 188, 83, 164, 
 214, 204, 41, 212, 
 69, 10, 93, 152, 
 34, 235, 166, 16, 
 219, 41, 211, 118, 
 202, 220, 168, 207, 
 91, 68, 242, 253, 
 81, 183, 83, 204, 
 217, 27, 115, 191, 
 214, 159, 79, 245, 
 23, 97, 181, 106, 
 81, 97, 108, 212, 
 94, 132, 117, 226, 
 116, 157, 72, 81, 
 39, 68, 151, 201, 
 79, 101, 114, 239, 
 124, 109, 57, 126, 
 89, 140, 209, 186, 
 99, 248, 231, 184, 
 82, 49, 73, 246, 
 76, 100, 149, 140, 
 99, 43, 227, 248, 
 202, 56, 57, 177, 
 201, 184, 108, 253, 
 53, 123, 218, 204, 
 222, 37, 51, 252, 
 169, 12, 95, 52, 
 67, 211, 193, 77, 
 84, 48, 229, 169, 
 172, 254, 18, 199, 
 76, 193, 145, 85, 
 114, 228, 133, 188, 
 95, 50, 239, 167, 
 202, 27, 83, 44, 
 244, 177, 11, 123, 
 228, 70, 201, 186, 
 145, 17, 238, 124, 
 170, 59, 121, 225, 
 230, 20, 179, 215, 
 70, 103, 206, 79, 
 226, 83, 182, 232, 
 219, 43, 182, 116, 
 136, 61, 79, 98, 
 115, 175, 216, 188, 
 47, 246, 62, 137, 
 189, 19, 98, 224, 
 211, 245, 169, 116, 
 125, 94, 95, 127, 
 61, 87, 104, 211, 
 21, 122, 124, 237, 
 82, 95, 99, 74, 
 215, 24, 246, 117, 
 122, 125, 157, 88, 
 23, 109, 146, 101, 
 35, 18, 
};

const LookupOfLength kmap0_word_len22_anagram0 = {
  352, // seq_bit_len_and_anagram
  181, // num_chords
  kmap0_word_len22_anagram0_chords, // chords
  kmap0_word_len22_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len22_anagram1_chords[] = {
 0, 12, 18, 0, 
 12, 1, 34, 5, 
 136, 52, 12, 16, 
 36, 4, 18, 0, 
 44, 18, 160, 64, 
 130, 16, 68, 146, 
 176, 72, 16, 132, 
 64, 16, 18, 4, 
 80, 50, 33, 1, 
 48, 8, 18, 0, 
 5, 129, 16, 33, 
 192, 34, 5, 128, 
 176, 9, 8, 32, 
 5, 80, 34, 1, 
 144, 48, 1, 65, 
 48, 44, 8, 144, 
 32, 26, 32, 33, 
 0, 164, 4, 144, 
 2, 0, 146, 16, 
 8, 18, 16, 64, 
 136, 128, 0, 154, 
 32, 68, 129, 50, 
 65, 16, 164, 0, 
 17, 128, 4, 146, 
 0, 4, 82, 16, 
 0, 83, 16, 13, 
 72, 144, 0, 81, 
 144, 64, 19, 34, 
 12, 128, 
};

const uint8_t kmap0_word_len22_anagram1_seqs[] = {
 32, 253, 32, 72, 
 191, 251, 212, 183, 
 126, 58, 61, 231, 
 159, 5, 194, 159, 
 132, 145, 73, 74, 
 211, 23, 50, 68, 
 143, 156, 136, 234, 
 231, 246, 184, 111, 
 184, 22, 61, 197, 
 241, 251, 116, 144, 
 25, 222, 212, 79, 
 183, 70, 242, 61, 
 207, 124, 79, 19, 
 221, 217, 188, 240, 
 69, 43, 12, 117, 
 1, 243, 113, 208, 
 159, 49, 84, 76, 
 99, 242, 76, 161, 
 182, 36, 107, 65, 
 161, 101, 242, 239, 
 180, 188, 61, 113, 
 198, 78, 20, 79, 
 140, 63, 5, 27, 
 199, 203, 250, 37, 
 243, 122, 28, 27, 
 87, 143, 216, 68, 
 15, 
};

const LookupOfLength kmap0_word_len22_anagram1 = {
  353, // seq_bit_len_and_anagram
  38, // num_chords
  kmap0_word_len22_anagram1_chords, // chords
  kmap0_word_len22_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len22_anagram2_chords[] = {
 52, 4, 64, 0, 
 4, 18, 16, 0, 
 27, 160, 64, 130, 
 16, 4, 82, 48, 
 8, 18, 18, 65, 
 8, 16, 13, 128, 
 6, 0, 1, 16, 
 0, 81, 48, 9, 
 16, 
};

const uint8_t kmap0_word_len22_anagram2_seqs[] = {
 127, 102, 54, 254, 
 76, 129, 214, 245, 
 32, 69, 150, 56, 
 126, 54, 230, 17, 
 109, 149, 125, 28, 
 244, 201, 181, 107, 
 47, 239, 216, 43, 
 122, 110, 3, 
};

const LookupOfLength kmap0_word_len22_anagram2 = {
  354, // seq_bit_len_and_anagram
  11, // num_chords
  kmap0_word_len22_anagram2_chords, // chords
  kmap0_word_len22_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len22_anagram3_chords[] = {
 16, 4, 18, 16, 
 0, 130, 36, 1, 
 0, 16, 4, 145, 
 176, 1, 16, 
};

const uint8_t kmap0_word_len22_anagram3_seqs[] = {
 248, 99, 143, 47, 
 208, 84, 243, 113, 
 140, 233, 215, 19, 
 119, 54, 
};

const LookupOfLength kmap0_word_len22_anagram3 = {
  355, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_word_len22_anagram3_chords, // chords
  kmap0_word_len22_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len22_anagram4_chords[] = {
 16, 4, 65, 48, 
 9, 16, 176, 1, 
 16, 
};

const uint8_t kmap0_word_len22_anagram4_seqs[] = {
 230, 253, 245, 97, 
 209, 51, 145, 111, 
 3, 
};

const LookupOfLength kmap0_word_len22_anagram4 = {
  356, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_word_len22_anagram4_chords, // chords
  kmap0_word_len22_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len22_anagram5_chords[] = {
 16, 4, 146, 16, 
 68, 18, 
};

const uint8_t kmap0_word_len22_anagram5_seqs[] = {
 160, 120, 242, 95, 
 127, 12, 
};

const LookupOfLength kmap0_word_len22_anagram5 = {
  357, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len22_anagram5_chords, // chords
  kmap0_word_len22_anagram5_seqs, // sequences
};

const uint8_t kmap0_word_len22_anagram6_chords[] = {
 16, 68, 18, 
};

const uint8_t kmap0_word_len22_anagram6_seqs[] = {
 210, 248, 5, 
};

const LookupOfLength kmap0_word_len22_anagram6 = {
  358, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len22_anagram6_chords, // chords
  kmap0_word_len22_anagram6_seqs, // sequences
};

const uint8_t kmap0_word_len23_anagram0_chords[] = {
 48, 76, 0, 2, 
 96, 128, 2, 40, 
 128, 164, 4, 1, 
 180, 12, 0, 16, 
 4, 11, 34, 76, 
 64, 128, 68, 130, 
 160, 13, 8, 16, 
 4, 81, 16, 4, 
 64, 18, 4, 17, 
 162, 76, 0, 36, 
 36, 3, 52, 5, 
 8, 54, 1, 8, 
 38, 32, 17, 38, 
 64, 136, 164, 8, 
 128, 164, 68, 16, 
 164, 0, 72, 36, 
 68, 24, 52, 12, 
 16, 54, 1, 16, 
 38, 0, 129, 36, 
 0, 81, 16, 4, 
 26, 16, 4, 195, 
 16, 8, 11, 16, 
 41, 2, 144, 41, 
 2, 132, 40, 2, 
 18, 0, 146, 2, 
 9, 130, 18, 0, 
 139, 38, 8, 130, 
 164, 8, 2, 0, 
 13, 26, 32, 1, 
 19, 4, 0, 19, 
 38, 0, 2, 32, 
 0, 18, 2, 68, 
 146, 2, 68, 82, 
 48, 65, 8, 18, 
 64, 80, 16, 64, 
 3, 34, 65, 1, 
 2, 64, 19, 176, 
 65, 0, 0, 69, 
 17, 48, 8, 136, 
 20, 8, 19, 144, 
 0, 152, 20, 32, 
 82, 16, 4, 131, 
 18, 0, 195, 16, 
 4, 147, 2, 37, 
 1, 0, 69, 16, 
 32, 5, 129, 16, 
 1, 18, 0, 37, 
 192, 160, 1, 144, 
 32, 1, 130, 160, 
 1, 66, 128, 33, 
 17, 34, 1, 17, 
 176, 9, 128, 32, 
 69, 24, 36, 5, 
 80, 50, 65, 0, 
 34, 1, 129, 38, 
 36, 1, 32, 44, 
 8, 160, 40, 16, 
 20, 32, 18, 18, 
 0, 9, 0, 13, 
 146, 128, 9, 146, 
 36, 8, 144, 16, 
 4, 137, 4, 12, 
 146, 144, 0, 200, 
 34, 33, 129, 18, 
 4, 152, 18, 0, 
 201, 18, 0, 129, 
 144, 4, 130, 144, 
 4, 131, 34, 13, 
 2, 132, 40, 16, 
 160, 40, 1, 32, 
 40, 10, 16, 77, 
 8, 146, 0, 11, 
 144, 1, 16, 144, 
 4, 146, 146, 0, 
 25, 4, 4, 19, 
 22, 0, 1, 166, 
 8, 1, 20, 4, 
 192, 148, 64, 18, 
 132, 1, 16, 164, 
 64, 16, 144, 4, 
 88, 16, 64, 24, 
 20, 4, 17, 18, 
 0, 81, 18, 4, 
 25, 34, 33, 17, 
 144, 4, 17, 18, 
 4, 200, 18, 0, 
 75, 6, 0, 82, 
 36, 4, 66, 144, 
 4, 72, 144, 0, 
 83, 48, 0, 82, 
 144, 0, 88, 18, 
 4, 208, 0, 37, 
 65, 16, 45, 64, 
 2, 33, 65, 2, 
 32, 90, 34, 33, 
 65, 34, 13, 64, 
 2, 9, 192, 2, 
 9, 81, 0, 13, 
 194, 144, 9, 64, 
 20, 13, 64, 22, 
 9, 64, 148, 9, 
 64, 132, 1, 64, 
 0, 13, 67, 16, 
 4, 75, 2, 9, 
 67, 128, 9, 67, 
 32, 5, 80, 22, 
 64, 66, 0, 32, 
 91, 144, 0, 17, 
 34, 33, 9, 128, 
 68, 19, 146, 0, 
 129, 0, 13, 19, 
 16, 4, 27, 2, 
 9, 19, 32, 0, 
 147, 2, 64, 67, 
 34, 0, 27, 36, 
 4, 24, 34, 76, 
 128, 34, 8, 80, 
 2, 68, 67, 0, 
 68, 10, 16, 100, 
 130, 16, 100, 3, 
 18, 96, 130, 18, 
 96, 3, 144, 96, 
 130, 144, 96, 66, 
 144, 72, 10, 128, 
 64, 83, 2, 64, 
 83, 
};

const uint8_t kmap0_word_len23_anagram0_seqs[] = {
 64, 190, 104, 208, 
 130, 37, 104, 193, 
 233, 207, 200, 251, 
 103, 136, 126, 68, 
 235, 190, 20, 155, 
 159, 40, 174, 159, 
 66, 239, 103, 246, 
 236, 51, 155, 249, 
 119, 123, 252, 98, 
 180, 60, 127, 17, 
 158, 190, 95, 79, 
 223, 173, 103, 207, 
 194, 147, 90, 229, 
 73, 17, 233, 140, 
 31, 121, 134, 102, 
 62, 231, 85, 158, 
 243, 162, 207, 105, 
 31, 103, 110, 218, 
 51, 15, 47, 190, 
 162, 7, 159, 151, 
 140, 78, 214, 69, 
 104, 44, 33, 140, 
 146, 17, 70, 170, 
 216, 131, 100, 164, 
 198, 18, 82, 91, 
 23, 169, 211, 137, 
 145, 206, 192, 121, 
 45, 225, 228, 99, 
 113, 138, 186, 152, 
 207, 70, 204, 51, 
 133, 252, 166, 66, 
 126, 115, 33, 125, 
 100, 149, 230, 30, 
 75, 175, 113, 101, 
 223, 189, 178, 103, 
 11, 25, 242, 182, 
 156, 63, 214, 100, 
 209, 234, 84, 183, 
 176, 78, 16, 185, 
 194, 130, 125, 241, 
 184, 190, 104, 94, 
 95, 236, 252, 241, 
 189, 240, 248, 121, 
 121, 124, 166, 61, 
 60, 83, 28, 244, 
 12, 15, 138, 60, 
 7, 229, 139, 35, 
 48, 243, 17, 179, 
 240, 152, 220, 123, 
 83, 136, 190, 231, 
 85, 222, 243, 92, 
 239, 220, 210, 119, 
 110, 90, 248, 103, 
 47, 204, 233, 21, 
 230, 20, 3, 139, 
 234, 105, 93, 235, 
 10, 60, 150, 4, 
 2, 75, 2, 57, 
 85, 250, 181, 46, 
 125, 217, 130, 204, 
 28, 74, 125, 195, 
 165, 86, 255, 80, 
 243, 90, 169, 119, 
 201, 20, 248, 100, 
 10, 252, 117, 250, 
 187, 49, 197, 84, 
 152, 34, 47, 76, 
 89, 17, 234, 151, 
 44, 53, 182, 209, 
 113, 28, 158, 152, 
 71, 114, 76, 91, 
 183, 254, 108, 81, 
 189, 189, 174, 45, 
 198, 86, 242, 179, 
 107, 92, 61, 117, 
 34, 142, 58, 145, 
 229, 248, 57, 116, 
 172, 210, 51, 174, 
 254, 29, 115, 243, 
 142, 247, 91, 167, 
 111, 184, 19, 251, 
 107, 126, 106, 53, 
 99, 91, 151, 177, 
 107, 193, 152, 207, 
 103, 63, 135, 178, 
 113, 99, 216, 152, 
 199, 108, 229, 24, 
 246, 244, 19, 195, 
 63, 150, 225, 151, 
 204, 176, 143, 101, 
 216, 90, 112, 223, 
 112, 185, 239, 244, 
 92, 106, 34, 46, 
 245, 44, 211, 99, 
 137, 83, 148, 204, 
 213, 95, 226, 218, 
 37, 115, 141, 146, 
 185, 70, 28, 188, 
 143, 37, 222, 87, 
 52, 111, 99, 137, 
 55, 176, 196, 249, 
 254, 225, 107, 87, 
 115, 161, 11, 215, 
 51, 49, 11, 91, 
 239, 13, 249, 197, 
 70, 147, 119, 231, 
 177, 180, 243, 138, 
 222, 105, 44, 237, 
 100, 42, 246, 218, 
 188, 89, 123, 139, 
 60, 231, 171, 248, 
 212, 82, 236, 201, 
 124, 253, 230, 189, 
 190, 234, 95, 225, 
 147, 175, 208, 191, 
 87, 216, 228, 43, 
 236, 245, 21, 6, 
 249, 10, 131, 125, 
 141, 100, 189, 198, 
 240, 94, 167, 121, 
 1, 
};

const LookupOfLength kmap0_word_len23_anagram0 = {
  368, // seq_bit_len_and_anagram
  167, // num_chords
  kmap0_word_len23_anagram0_chords, // chords
  kmap0_word_len23_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len23_anagram1_chords[] = {
 36, 4, 128, 128, 
 0, 19, 16, 4, 
 66, 128, 68, 18, 
 52, 5, 128, 54, 
 0, 128, 164, 64, 
 128, 164, 32, 1, 
 164, 68, 16, 36, 
 1, 0, 16, 4, 
 138, 0, 68, 26, 
 128, 104, 2, 128, 
 9, 130, 144, 1, 
 2, 144, 0, 26, 
 0, 13, 18, 128, 
 64, 26, 52, 0, 
 18, 2, 68, 18, 
 16, 64, 11, 18, 
 64, 192, 18, 32, 
 17, 20, 4, 66, 
 144, 0, 83, 54, 
 1, 16, 128, 65, 
 128, 176, 1, 16, 
 160, 33, 65, 180, 
 1, 128, 48, 13, 
 16, 34, 65, 24, 
 176, 9, 16, 0, 
 109, 2, 18, 0, 
 89, 32, 0, 146, 
 16, 4, 131, 34, 
 33, 9, 164, 64, 
 8, 36, 32, 10, 
 38, 0, 128, 22, 
 0, 18, 144, 8, 
 17, 48, 0, 82, 
 18, 64, 80, 146, 
 0, 88, 48, 8, 
 80, 18, 0, 201, 
 18, 0, 81, 144, 
 0, 82, 16, 0, 
 81, 16, 4, 137, 
 16, 4, 9, 18, 
 0, 73, 144, 0, 
 89, 16, 96, 19, 
 34, 33, 1, 32, 
 12, 129, 18, 64, 
 18, 0, 36, 19, 
};

const uint8_t kmap0_word_len23_anagram1_seqs[] = {
 160, 126, 38, 176, 
 19, 197, 35, 154, 
 249, 103, 226, 122, 
 254, 109, 58, 251, 
 36, 159, 20, 33, 
 207, 136, 133, 231, 
 196, 203, 51, 31, 
 7, 190, 162, 9, 
 95, 101, 129, 48, 
 133, 68, 10, 44, 
 97, 248, 56, 48, 
 70, 61, 56, 143, 
 37, 156, 184, 42, 
 22, 167, 71, 126, 
 79, 33, 141, 214, 
 149, 109, 54, 185, 
 23, 122, 204, 248, 
 213, 102, 140, 217, 
 163, 79, 207, 65, 
 17, 242, 136, 185, 
 125, 195, 224, 189, 
 41, 78, 223, 243, 
 162, 239, 105, 149, 
 247, 132, 104, 248, 
 215, 82, 43, 123, 
 86, 32, 79, 65, 
 191, 190, 208, 190, 
 225, 214, 200, 42, 
 107, 86, 132, 53, 
 215, 166, 49, 118, 
 245, 56, 197, 122, 
 204, 152, 61, 230, 
 150, 102, 107, 199, 
 176, 69, 143, 185, 
 201, 186, 220, 188, 
 30, 14, 68, 15, 
 239, 152, 121, 159, 
 172, 187, 214, 215, 
 93, 171, 54, 175, 
 149, 99, 22, 142, 
 175, 219, 55, 92, 
 241, 51, 237, 213, 
 61, 178, 120, 132, 
 11, 
};

const LookupOfLength kmap0_word_len23_anagram1 = {
  369, // seq_bit_len_and_anagram
  60, // num_chords
  kmap0_word_len23_anagram1_chords, // chords
  kmap0_word_len23_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len23_anagram2_chords[] = {
 128, 12, 18, 16, 
 4, 138, 16, 4, 
 81, 16, 4, 131, 
 2, 68, 18, 20, 
 4, 192, 18, 0, 
 131, 18, 0, 25, 
 16, 4, 145, 52, 
 1, 16, 22, 0, 
 18, 32, 68, 128, 
 0, 68, 26, 18, 
 4, 145, 18, 0, 
 89, 48, 8, 192, 
 4, 4, 82, 164, 
 0, 17, 
};

const uint8_t kmap0_word_len23_anagram2_seqs[] = {
 159, 98, 138, 87, 
 245, 197, 207, 152, 
 23, 127, 151, 44, 
 251, 167, 48, 125, 
 101, 155, 26, 123, 
 91, 215, 163, 244, 
 187, 158, 122, 143, 
 107, 109, 15, 186, 
 76, 126, 57, 175, 
 178, 24, 239, 55, 
 113, 235, 122, 152, 
 108, 209, 92, 231, 
 139, 205, 115, 6, 
};

const LookupOfLength kmap0_word_len23_anagram2 = {
  370, // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_word_len23_anagram2_chords, // chords
  kmap0_word_len23_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len23_anagram3_chords[] = {
 128, 12, 18, 20, 
 0, 19, 16, 4, 
 146, 48, 12, 128, 
};

const uint8_t kmap0_word_len23_anagram3_seqs[] = {
 233, 139, 152, 49, 
 186, 238, 152, 254, 
 66, 124, 18, 13, 
};

const LookupOfLength kmap0_word_len23_anagram3 = {
  371, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_word_len23_anagram3_chords, // chords
  kmap0_word_len23_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len24_anagram0_chords[] = {
 18, 4, 130, 16, 
 32, 136, 48, 9, 
 128, 18, 9, 0, 
 0, 72, 16, 2, 
 9, 18, 32, 4, 
 82, 0, 68, 3, 
 20, 4, 3, 128, 
 4, 82, 36, 12, 
 128, 32, 5, 26, 
 20, 4, 67, 2, 
 4, 65, 48, 4, 
 80, 16, 68, 9, 
 52, 69, 0, 52, 
 1, 8, 180, 64, 
 130, 52, 0, 17, 
 166, 1, 1, 166, 
 1, 8, 164, 64, 
 8, 52, 13, 16, 
 38, 1, 24, 180, 
 9, 16, 36, 32, 
 80, 38, 64, 128, 
 36, 32, 10, 16, 
 12, 18, 16, 68, 
 138, 128, 4, 210, 
 20, 4, 19, 48, 
 0, 74, 16, 36, 
 10, 146, 32, 2, 
 144, 32, 66, 144, 
 32, 74, 48, 4, 
 194, 48, 8, 146, 
 2, 0, 138, 128, 
 4, 27, 128, 0, 
 11, 2, 0, 82, 
 50, 0, 82, 36, 
 8, 18, 16, 68, 
 2, 18, 64, 2, 
 48, 65, 16, 16, 
 68, 137, 18, 68, 
 129, 18, 64, 24, 
 144, 68, 9, 164, 
 64, 1, 2, 73, 
 24, 146, 64, 17, 
 52, 4, 136, 50, 
 1, 8, 18, 32, 
 11, 0, 5, 26, 
 160, 13, 16, 34, 
 65, 128, 32, 33, 
 192, 160, 9, 16, 
 160, 65, 8, 32, 
 13, 0, 36, 37, 
 16, 48, 5, 80, 
 164, 1, 16, 16, 
 36, 192, 48, 44, 
 18, 16, 40, 129, 
 144, 32, 73, 144, 
 32, 193, 34, 104, 
 0, 32, 32, 18, 
 18, 64, 9, 6, 
 8, 146, 18, 64, 
 8, 18, 64, 138, 
 18, 64, 72, 50, 
 0, 88, 2, 4, 
 11, 2, 4, 131, 
 34, 8, 19, 162, 
 8, 18, 130, 0, 
 153, 50, 0, 146, 
 32, 9, 152, 2, 
 77, 8, 18, 9, 
 8, 32, 37, 128, 
 18, 12, 130, 16, 
 12, 24, 16, 12, 
 17, 52, 12, 18, 
 16, 12, 137, 144, 
 8, 25, 18, 8, 
 19, 34, 41, 1, 
 48, 4, 25, 48, 
 4, 152, 160, 1, 
 146, 146, 64, 130, 
 20, 4, 9, 22, 
 0, 138, 148, 0, 
 128, 148, 0, 88, 
 22, 4, 17, 22, 
 0, 130, 6, 9, 
 128, 20, 4, 137, 
 150, 0, 130, 22, 
 4, 80, 4, 32, 
 82, 48, 64, 136, 
 48, 64, 144, 16, 
 36, 17, 130, 4, 
 25, 144, 64, 18, 
 48, 64, 18, 48, 
 1, 146, 18, 1, 
 144, 18, 12, 24, 
 22, 4, 16, 148, 
 0, 17, 48, 0, 
 209, 48, 0, 25, 
 50, 8, 80, 160, 
 33, 16, 16, 40, 
 66, 20, 4, 82, 
 128, 0, 210, 16, 
 36, 82, 144, 64, 
 74, 48, 8, 192, 
 0, 45, 80, 128, 
 41, 66, 128, 96, 
 74, 32, 9, 192, 
 2, 1, 72, 130, 
 4, 194, 144, 64, 
 208, 176, 0, 82, 
 4, 13, 80, 4, 
 68, 74, 20, 32, 
 66, 20, 32, 80, 
 2, 4, 67, 16, 
 12, 81, 2, 0, 
 83, 32, 9, 67, 
 32, 64, 83, 128, 
 64, 82, 2, 4, 
 3, 128, 4, 1, 
 144, 32, 11, 16, 
 0, 91, 20, 8, 
 129, 0, 45, 9, 
 18, 32, 65, 2, 
 41, 3, 2, 41, 
 9, 128, 96, 19, 
 50, 0, 65, 130, 
 0, 131, 144, 8, 
 17, 32, 9, 19, 
 32, 9, 25, 48, 
 0, 137, 48, 0, 
 145, 48, 0, 200, 
 34, 8, 154, 128, 
 76, 2, 48, 65, 
 2, 16, 104, 130, 
 128, 64, 146, 16, 
 0, 83, 160, 32, 
 19, 
};

const uint8_t kmap0_word_len24_anagram0_seqs[] = {
 224, 169, 209, 0, 
 154, 172, 128, 114, 
 201, 32, 117, 201, 
 32, 141, 208, 96, 
 26, 75, 128, 139, 
 252, 224, 250, 187, 
 143, 232, 186, 143, 
 19, 204, 79, 103, 
 78, 175, 247, 20, 
 207, 213, 184, 207, 
 220, 188, 207, 156, 
 199, 191, 107, 149, 
 231, 203, 219, 167, 
 239, 172, 167, 41, 
 174, 167, 119, 61, 
 103, 223, 177, 103, 
 235, 29, 103, 100, 
 149, 231, 248, 75, 
 231, 180, 222, 231, 
 68, 201, 231, 100, 
 134, 103, 110, 146, 
 103, 86, 132, 248, 
 201, 243, 248, 42, 
 201, 248, 67, 193, 
 248, 83, 189, 104, 
 229, 204, 8, 95, 
 209, 8, 163, 209, 
 8, 35, 216, 8, 
 131, 173, 72, 159, 
 217, 72, 22, 61, 
 72, 173, 141, 24, 
 186, 243, 24, 187, 
 161, 56, 205, 205, 
 56, 185, 217, 56, 
 57, 157, 210, 248, 
 210, 210, 216, 210, 
 210, 247, 216, 210, 
 186, 79, 210, 251, 
 77, 178, 85, 61, 
 50, 244, 215, 50, 
 242, 185, 114, 90, 
 75, 150, 189, 49, 
 214, 63, 201, 214, 
 187, 213, 94, 168, 
 141, 199, 43, 22, 
 199, 139, 49, 7, 
 229, 150, 7, 101, 
 134, 71, 76, 78, 
 71, 100, 149, 247, 
 167, 244, 247, 124, 
 133, 247, 248, 217, 
 247, 68, 174, 240, 
 153, 201, 208, 47, 
 22, 208, 148, 188, 
 48, 212, 188, 48, 
 120, 77, 48, 167, 
 150, 48, 207, 20, 
 45, 173, 219, 157, 
 42, 21, 173, 210, 
 150, 173, 210, 23, 
 173, 220, 210, 173, 
 156, 199, 173, 251, 
 184, 189, 79, 141, 
 45, 246, 22, 45, 
 198, 20, 2, 209, 
 186, 2, 185, 209, 
 2, 89, 75, 165, 
 86, 249, 37, 237, 
 195, 244, 249, 134, 
 233, 169, 209, 233, 
 85, 61, 233, 119, 
 61, 233, 139, 211, 
 201, 186, 79, 201, 
 186, 49, 201, 59, 
 141, 169, 111, 184, 
 250, 155, 199, 234, 
 60, 79, 65, 113, 
 23, 113, 209, 210, 
 245, 215, 186, 213, 
 138, 77, 213, 81, 
 201, 213, 195, 161, 
 181, 231, 215, 181, 
 47, 76, 181, 212, 
 68, 149, 94, 189, 
 53, 168, 209, 117, 
 190, 217, 149, 11, 
 132, 101, 178, 173, 
 101, 178, 61, 243, 
 11, 61, 243, 219, 
 161, 99, 140, 145, 
 99, 153, 209, 227, 
 219, 23, 99, 106, 
 31, 227, 244, 173, 
 227, 250, 61, 227, 
 26, 179, 99, 206, 
 180, 227, 205, 163, 
 99, 177, 217, 19, 
 249, 134, 140, 208, 
 201, 140, 243, 213, 
 140, 19, 68, 236, 
 31, 132, 108, 12, 
 149, 108, 18, 205, 
 12, 127, 74, 12, 
 3, 75, 12, 227, 
 170, 92, 202, 68, 
 172, 125, 28, 28, 
 216, 79, 28, 36, 
 61, 28, 121, 208, 
 92, 127, 74, 92, 
 255, 170, 92, 109, 
 132, 92, 161, 199, 
 188, 191, 141, 188, 
 227, 79, 188, 211, 
 184, 188, 25, 75, 
 188, 89, 22, 124, 
 141, 145, 251, 184, 
 141, 251, 187, 17, 
 107, 132, 26, 107, 
 43, 23, 235, 84, 
 201, 11, 95, 75, 
 11, 205, 205, 11, 
 27, 75, 11, 91, 
 75, 11, 39, 174, 
 219, 204, 217, 27, 
 23, 141, 59, 78, 
 49, 59, 25, 75, 
 59, 89, 75, 155, 
 85, 77, 155, 103, 
 201, 89, 201, 204, 
 98, 107, 65, 215, 
 199, 72, 87, 203, 
 219, 87, 104, 74, 
 215, 24, 146, 133, 
 121, 61, 69, 228, 
 133, 
};

const LookupOfLength kmap0_word_len24_anagram0 = {
  384, // seq_bit_len_and_anagram
  179, // num_chords
  kmap0_word_len24_anagram0_chords, // chords
  kmap0_word_len24_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len24_anagram1_chords[] = {
 0, 64, 16, 52, 
 5, 0, 144, 0, 
 208, 0, 72, 80, 
 48, 4, 66, 130, 
 4, 11, 4, 4, 
 146, 2, 4, 81, 
 128, 4, 11, 130, 
 4, 74, 2, 1, 
 130, 176, 0, 82, 
 18, 64, 19, 18, 
 68, 136, 18, 64, 
 8, 18, 68, 129, 
 32, 69, 16, 48, 
 5, 0, 48, 1, 
 137, 160, 1, 146, 
 34, 65, 128, 128, 
 96, 18, 18, 64, 
 9, 18, 12, 24, 
 16, 12, 81, 130, 
 4, 9, 176, 0, 
 24, 148, 8, 8, 
 20, 4, 146, 20, 
 4, 25, 148, 0, 
 17, 2, 4, 146, 
 48, 12, 144, 16, 
 68, 82, 0, 5, 
 65, 2, 4, 89, 
 22, 0, 81, 48, 
 8, 192, 50, 76, 
 2, 0, 100, 3, 
 128, 76, 10, 128, 
 96, 19, 
};

const uint8_t kmap0_word_len24_anagram1_seqs[] = {
 64, 142, 208, 224, 
 254, 211, 64, 32, 
 216, 32, 177, 208, 
 143, 152, 217, 143, 
 219, 161, 95, 43, 
 21, 63, 219, 188, 
 248, 170, 177, 248, 
 220, 26, 72, 125, 
 28, 24, 121, 216, 
 56, 150, 189, 210, 
 218, 79, 210, 218, 
 150, 178, 233, 215, 
 199, 124, 150, 247, 
 231, 219, 183, 117, 
 201, 55, 197, 20, 
 119, 110, 146, 176, 
 144, 19, 173, 210, 
 186, 233, 167, 213, 
 233, 121, 61, 250, 
 219, 161, 234, 60, 
 161, 81, 54, 212, 
 245, 7, 77, 245, 
 199, 186, 53, 118, 
 61, 243, 216, 79, 
 99, 209, 79, 252, 
 56, 150, 188, 127, 
 28, 188, 243, 173, 
 188, 211, 213, 162, 
 153, 77, 215, 111, 
 209, 215, 95, 132, 
 215, 72, 175, 215, 
 152, 133, 
};

const LookupOfLength kmap0_word_len24_anagram1 = {
  385, // seq_bit_len_and_anagram
  42, // num_chords
  kmap0_word_len24_anagram1_chords, // chords
  kmap0_word_len24_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len24_anagram2_chords[] = {
 16, 4, 136, 16, 
 4, 152, 128, 4, 
 146, 2, 0, 19, 
 144, 64, 2, 18, 
 64, 19, 160, 33, 
 1, 20, 4, 130, 
 22, 0, 81, 48, 
 1, 17, 34, 33, 
 1, 2, 96, 3, 
};

const uint8_t kmap0_word_len24_anagram2_seqs[] = {
 224, 137, 172, 64, 
 224, 213, 24, 68, 
 63, 56, 189, 141, 
 210, 24, 210, 178, 
 199, 184, 145, 111, 
 184, 245, 233, 209, 
 117, 218, 188, 227, 
 123, 188, 11, 251, 
 134, 215, 94, 132, 
};

const LookupOfLength kmap0_word_len24_anagram2 = {
  386, // seq_bit_len_and_anagram
  12, // num_chords
  kmap0_word_len24_anagram2_chords, // chords
  kmap0_word_len24_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len24_anagram3_chords[] = {
 48, 1, 16, 0, 
 12, 18, 48, 9, 
 16, 22, 8, 16, 
 32, 69, 16, 48, 
 8, 80, 
};

const uint8_t kmap0_word_len24_anagram3_seqs[] = {
 224, 30, 223, 32, 
 253, 20, 78, 158, 
 219, 78, 181, 199, 
 119, 254, 145, 99, 
 206, 201, 
};

const LookupOfLength kmap0_word_len24_anagram3 = {
  387, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_word_len24_anagram3_chords, // chords
  kmap0_word_len24_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len24_anagram4_chords[] = {
 16, 68, 18, 16, 
 68, 146, 128, 64, 
 18, 160, 33, 1, 
};

const uint8_t kmap0_word_len24_anagram4_seqs[] = {
 63, 248, 210, 56, 
 47, 201, 56, 113, 
 149, 27, 249, 134, 
};

const LookupOfLength kmap0_word_len24_anagram4 = {
  388, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_word_len24_anagram4_chords, // chords
  kmap0_word_len24_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len24_anagram5_chords[] = {
 48, 8, 80, 
};

const uint8_t kmap0_word_len24_anagram5_seqs[] = {
 236, 17, 61, 
};

const LookupOfLength kmap0_word_len24_anagram5 = {
  389, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len24_anagram5_chords, // chords
  kmap0_word_len24_anagram5_seqs, // sequences
};

const uint8_t kmap0_word_len24_anagram6_chords[] = {
 0, 68, 18, 
};

const uint8_t kmap0_word_len24_anagram6_seqs[] = {
 127, 253, 145, 
};

const LookupOfLength kmap0_word_len24_anagram6 = {
  390, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len24_anagram6_chords, // chords
  kmap0_word_len24_anagram6_seqs, // sequences
};

const uint8_t kmap0_word_len25_anagram0_chords[] = {
 128, 4, 24, 48, 
 0, 152, 18, 12, 
 8, 4, 72, 0, 
 4, 96, 0, 16, 
 36, 72, 52, 4, 
 73, 128, 68, 18, 
 50, 12, 3, 32, 
 4, 131, 128, 12, 
 193, 20, 12, 0, 
 128, 36, 26, 2, 
 12, 136, 32, 4, 
 136, 50, 12, 16, 
 48, 12, 64, 130, 
 12, 3, 52, 4, 
 24, 52, 4, 144, 
 52, 12, 2, 180, 
 8, 2, 54, 64, 
 64, 36, 13, 130, 
 36, 13, 136, 38, 
 9, 136, 164, 9, 
 130, 180, 0, 129, 
 38, 9, 18, 164, 
 64, 26, 36, 0, 
 26, 0, 36, 139, 
 130, 68, 18, 32, 
 4, 194, 144, 40, 
 18, 32, 41, 10, 
 34, 0, 82, 180, 
 0, 130, 160, 0, 
 82, 144, 76, 8, 
 52, 65, 0, 16, 
 69, 1, 16, 65, 
 3, 18, 65, 8, 
 20, 68, 17, 20, 
 64, 8, 176, 72, 
 1, 2, 68, 193, 
 128, 64, 19, 128, 
 68, 144, 128, 68, 
 208, 148, 72, 8, 
 32, 73, 24, 144, 
 0, 154, 18, 0, 
 27, 48, 68, 128, 
 34, 33, 1, 18, 
 1, 145, 18, 1, 
 9, 144, 1, 81, 
 16, 5, 26, 32, 
 1, 146, 32, 1, 
 26, 48, 65, 24, 
 176, 9, 8, 48, 
 5, 138, 16, 100, 
 136, 4, 36, 18, 
 0, 36, 80, 16, 
 36, 129, 48, 44, 
 8, 16, 100, 144, 
 128, 32, 16, 178, 
 1, 24, 50, 64, 
 10, 2, 68, 200, 
 2, 32, 201, 16, 
 64, 146, 34, 4, 
 144, 16, 9, 152, 
 16, 68, 144, 48, 
 65, 136, 34, 0, 
 138, 128, 12, 144, 
 18, 76, 128, 18, 
 76, 8, 50, 8, 
 9, 130, 8, 16, 
 2, 73, 16, 144, 
 72, 24, 144, 8, 
 9, 128, 12, 145, 
 130, 8, 9, 48, 
 8, 194, 32, 40, 
 82, 50, 12, 9, 
 22, 0, 136, 128, 
 12, 152, 36, 8, 
 26, 134, 0, 9, 
 176, 5, 24, 20, 
 68, 16, 132, 4, 
 81, 132, 4, 145, 
 150, 64, 16, 22, 
 8, 17, 6, 0, 
 10, 36, 8, 128, 
 134, 0, 72, 132, 
 4, 1, 20, 1, 
 16, 134, 0, 88, 
 148, 0, 16, 48, 
 64, 193, 48, 64, 
 128, 50, 64, 129, 
 176, 64, 129, 2, 
 68, 144, 132, 12, 
 16, 16, 4, 146, 
 180, 0, 17, 50, 
 9, 16, 16, 4, 
 208, 18, 72, 24, 
 128, 12, 200, 20, 
 12, 192, 32, 4, 
 89, 128, 32, 194, 
 6, 0, 83, 18, 
 96, 192, 50, 8, 
 208, 22, 8, 192, 
 50, 1, 200, 178, 
 8, 65, 22, 64, 
 80, 20, 68, 80, 
 6, 0, 89, 52, 
 4, 193, 32, 4, 
 65, 180, 0, 81, 
 32, 0, 83, 32, 
 1, 65, 48, 0, 
 81, 2, 65, 67, 
 34, 65, 74, 16, 
 100, 17, 16, 32, 
 81, 36, 40, 1, 
 48, 12, 145, 16, 
 77, 3, 34, 1, 
 26, 162, 0, 72, 
 176, 8, 19, 176, 
 8, 146, 50, 8, 
 19, 160, 69, 10, 
 2, 96, 2, 160, 
 64, 130, 160, 64, 
 10, 160, 65, 26, 
 160, 1, 26, 
};

const uint8_t kmap0_word_len25_anagram0_seqs[] = {
 224, 127, 66, 129, 
 64, 86, 131, 244, 
 173, 6, 21, 36, 
 9, 42, 4, 18, 
 48, 124, 245, 159, 
 108, 221, 71, 140, 
 145, 143, 219, 162, 
 31, 55, 63, 61, 
 165, 224, 253, 244, 
 101, 253, 138, 48, 
 230, 181, 211, 211, 
 171, 230, 167, 159, 
 105, 209, 207, 156, 
 147, 127, 35, 53, 
 158, 175, 234, 57, 
 127, 198, 116, 26, 
 63, 249, 52, 70, 
 242, 105, 110, 233, 
 147, 30, 75, 39, 
 189, 150, 78, 106, 
 45, 157, 20, 88, 
 58, 99, 151, 124, 
 78, 99, 233, 156, 
 184, 234, 153, 85, 
 11, 124, 21, 188, 
 248, 35, 59, 240, 
 57, 63, 33, 156, 
 72, 70, 152, 181, 
 132, 61, 152, 25, 
 35, 87, 50, 230, 
 225, 24, 249, 78, 
 161, 210, 103, 190, 
 165, 15, 255, 74, 
 31, 198, 149, 62, 
 90, 45, 93, 127, 
 86, 186, 90, 165, 
 180, 24, 107, 217, 
 188, 79, 50, 112, 
 99, 100, 16, 253, 
 200, 24, 126, 146, 
 81, 214, 42, 39, 
 107, 201, 42, 16, 
 133, 117, 123, 11, 
 151, 201, 79, 71, 
 223, 112, 143, 166, 
 245, 28, 173, 189, 
 62, 98, 204, 123, 
 204, 43, 250, 200, 
 68, 197, 145, 85, 
 139, 219, 42, 61, 
 183, 53, 146, 111, 
 122, 69, 195, 87, 
 73, 134, 95, 107, 
 1, 127, 158, 25, 
 250, 105, 33, 244, 
 139, 86, 232, 121, 
 146, 48, 102, 98, 
 250, 214, 24, 183, 
 202, 140, 110, 166, 
 87, 217, 172, 130, 
 87, 192, 87, 147, 
 64, 166, 254, 146, 
 71, 77, 244, 82, 
 122, 200, 183, 85, 
 82, 107, 190, 72, 
 47, 16, 147, 44, 
 251, 41, 89, 246, 
 107, 106, 205, 235, 
 212, 51, 49, 169, 
 36, 123, 82, 72, 
 143, 166, 72, 214, 
 77, 49, 251, 148, 
 98, 59, 52, 101, 
 70, 114, 202, 12, 
 11, 253, 109, 209, 
 218, 181, 146, 53, 
 38, 61, 105, 78, 
 181, 136, 186, 29, 
 26, 243, 122, 187, 
 254, 188, 116, 125, 
 222, 152, 250, 59, 
 65, 213, 211, 33, 
 171, 39, 245, 214, 
 70, 109, 172, 148, 
 211, 89, 163, 57, 
 180, 198, 254, 70, 
 29, 31, 158, 58, 
 205, 161, 117, 162, 
 122, 202, 100, 243, 
 150, 201, 206, 46, 
 147, 123, 93, 38, 
 199, 122, 94, 246, 
 211, 124, 217, 152, 
 241, 19, 21, 227, 
 51, 98, 199, 119, 
 39, 143, 201, 207, 
 30, 167, 86, 201, 
 79, 41, 148, 63, 
 85, 50, 255, 230, 
 81, 70, 24, 65, 
 140, 211, 117, 25, 
 182, 73, 114, 147, 
 232, 225, 78, 149, 
 204, 173, 55, 153, 
 67, 108, 47, 215, 
 150, 30, 174, 227, 
 151, 92, 167, 117, 
 121, 255, 36, 243, 
 254, 102, 230, 157, 
 56, 205, 59, 25, 
 151, 55, 31, 7, 
 231, 205, 99, 190, 
 246, 177, 124, 109, 
 189, 23, 142, 95, 
 46, 28, 51, 92, 
 152, 211, 185, 243, 
 162, 105, 175, 254, 
 82, 214, 62, 138, 
 172, 205, 161, 162, 
 113, 99, 68, 19, 
 78, 136, 158, 109, 
 188, 254, 29, 122, 
 133, 141, 240, 26, 
 153, 228, 53, 178, 
 202, 235, 132, 222, 
 69, 100, 189, 1, 
};

const LookupOfLength kmap0_word_len25_anagram0 = {
  400, // seq_bit_len_and_anagram
  161, // num_chords
  kmap0_word_len25_anagram0_chords, // chords
  kmap0_word_len25_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len25_anagram1_chords[] = {
 144, 8, 16, 48, 
 8, 65, 32, 5, 
 26, 20, 4, 16, 
 48, 12, 8, 52, 
 68, 1, 50, 72, 
 16, 50, 72, 2, 
 130, 64, 81, 16, 
 0, 74, 16, 13, 
 128, 144, 1, 81, 
 22, 8, 0, 18, 
 1, 11, 34, 0, 
 9, 50, 8, 73, 
 50, 8, 9, 48, 
 5, 128, 18, 76, 
 8, 48, 12, 17, 
 144, 40, 17, 48, 
 8, 17, 20, 36, 
 80, 22, 8, 16, 
 50, 64, 129, 50, 
 64, 136, 18, 64, 
 17, 48, 1, 80, 
 178, 1, 24, 176, 
 8, 16, 54, 0, 
 82, 6, 0, 81, 
 180, 0, 64, 0, 
 68, 89, 52, 4, 
 129, 128, 12, 1, 
 2, 96, 3, 
};

const uint8_t kmap0_word_len25_anagram1_seqs[] = {
 32, 69, 140, 1, 
 175, 69, 131, 226, 
 245, 254, 90, 253, 
 243, 162, 53, 91, 
 250, 252, 181, 244, 
 180, 104, 105, 177, 
 209, 178, 121, 39, 
 204, 108, 69, 31, 
 78, 79, 62, 130, 
 215, 211, 169, 203, 
 186, 245, 48, 110, 
 235, 230, 222, 86, 
 209, 188, 173, 98, 
 175, 201, 127, 103, 
 167, 111, 105, 77, 
 191, 121, 156, 98, 
 161, 39, 229, 93, 
 79, 133, 243, 236, 
 58, 93, 214, 101, 
 114, 123, 203, 228, 
 86, 143, 165, 236, 
 29, 31, 153, 61, 
 190, 59, 116, 156, 
 66, 52, 227, 244, 
 105, 174, 61, 189, 
 92, 35, 179, 121, 
 231, 85, 238, 159, 
 228, 221, 72, 191, 
 113, 109, 185, 16, 
};

const LookupOfLength kmap0_word_len25_anagram1 = {
  401, // seq_bit_len_and_anagram
  37, // num_chords
  kmap0_word_len25_anagram1_chords, // chords
  kmap0_word_len25_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len25_anagram2_chords[] = {
 2, 4, 73, 20, 
 4, 128, 0, 36, 
 3, 52, 4, 129, 
 148, 0, 64, 48, 
 5, 17, 128, 64, 
 18, 
};

const uint8_t kmap0_word_len25_anagram2_seqs[] = {
 128, 191, 117, 191, 
 86, 63, 253, 238, 
 35, 60, 127, 151, 
 28, 181, 6, 123, 
 127, 110, 239, 53, 
 102, 10, 
};

const LookupOfLength kmap0_word_len25_anagram2 = {
  402, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_word_len25_anagram2_chords, // chords
  kmap0_word_len25_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len25_anagram3_chords[] = {
 160, 65, 0, 48, 
 1, 17, 
};

const uint8_t kmap0_word_len25_anagram3_seqs[] = {
 64, 70, 190, 199, 
 71, 94, 3, 
};

const LookupOfLength kmap0_word_len25_anagram3 = {
  403, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len25_anagram3_chords, // chords
  kmap0_word_len25_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len25_anagram4_chords[] = {
 16, 4, 19, 20, 
 0, 16, 
};

const uint8_t kmap0_word_len25_anagram4_seqs[] = {
 63, 235, 41, 170, 
 107, 245, 0, 
};

const LookupOfLength kmap0_word_len25_anagram4 = {
  404, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len25_anagram4_chords, // chords
  kmap0_word_len25_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len26_anagram0_chords[] = {
 6, 4, 144, 2, 
 32, 82, 2, 32, 
 128, 2, 12, 192, 
 128, 32, 152, 128, 
 32, 208, 32, 4, 
 144, 130, 12, 16, 
 6, 4, 80, 144, 
 96, 16, 128, 12, 
 24, 32, 4, 81, 
 6, 4, 72, 20, 
 32, 65, 32, 4, 
 72, 32, 69, 10, 
 128, 9, 18, 50, 
 76, 2, 50, 76, 
 64, 48, 69, 8, 
 160, 12, 9, 16, 
 68, 90, 20, 68, 
 8, 6, 4, 130, 
 160, 68, 24, 34, 
 5, 72, 160, 36, 
 17, 32, 69, 130, 
 52, 5, 128, 180, 
 1, 16, 54, 1, 
 128, 180, 64, 136, 
 180, 32, 17, 180, 
 0, 10, 52, 36, 
 18, 52, 36, 17, 
 32, 12, 74, 164, 
 4, 26, 48, 37, 
 10, 48, 37, 18, 
 160, 32, 82, 144, 
 1, 2, 160, 8, 
 138, 130, 8, 3, 
 128, 8, 10, 146, 
 9, 2, 164, 0, 
 82, 164, 0, 10, 
 32, 32, 26, 160, 
 8, 67, 48, 69, 
 24, 54, 68, 8, 
 50, 65, 72, 50, 
 65, 65, 130, 76, 
 8, 128, 96, 137, 
 176, 65, 136, 176, 
 69, 64, 32, 72, 
 18, 18, 4, 144, 
 16, 1, 3, 16, 
 8, 137, 48, 1, 
 26, 48, 5, 8, 
 54, 64, 128, 16, 
 0, 194, 18, 0, 
 131, 16, 0, 155, 
 128, 5, 19, 18, 
 33, 65, 128, 5, 
 144, 48, 1, 137, 
 144, 65, 144, 144, 
 9, 16, 130, 1, 
 192, 16, 33, 26, 
 18, 65, 24, 34, 
 5, 146, 48, 37, 
 17, 50, 1, 72, 
 180, 1, 192, 34, 
 5, 81, 50, 5, 
 8, 48, 44, 192, 
 16, 44, 16, 20, 
 36, 8, 18, 96, 
 8, 6, 12, 3, 
 6, 12, 16, 134, 
 8, 17, 2, 5, 
 9, 18, 0, 73, 
 18, 13, 72, 128, 
 9, 10, 132, 4, 
 129, 32, 36, 138, 
 48, 33, 137, 18, 
 0, 202, 164, 0, 
 146, 176, 1, 136, 
 48, 13, 9, 48, 
 13, 8, 48, 13, 
 136, 32, 12, 136, 
 52, 12, 144, 48, 
 12, 144, 144, 104, 
 1, 18, 72, 128, 
 182, 8, 128, 176, 
 72, 128, 48, 72, 
 16, 166, 4, 9, 
 162, 1, 24, 132, 
 36, 24, 4, 12, 
 10, 6, 36, 80, 
 6, 9, 26, 4, 
 12, 192, 52, 65, 
 128, 20, 0, 155, 
 36, 4, 144, 134, 
 32, 192, 20, 0, 
 19, 180, 64, 64, 
 52, 0, 144, 32, 
 68, 137, 32, 68, 
 145, 34, 68, 80, 
 128, 76, 24, 16, 
 0, 147, 16, 72, 
 18, 144, 9, 19, 
 2, 5, 80, 0, 
 4, 210, 36, 0, 
 195, 34, 5, 200, 
 18, 0, 90, 128, 
 40, 65, 144, 9, 
 67, 180, 1, 72, 
 18, 0, 209, 18, 
 9, 81, 34, 1, 
 89, 144, 9, 81, 
 160, 1, 89, 162, 
 64, 65, 52, 0, 
 193, 48, 64, 72, 
 16, 8, 83, 16, 
 13, 131, 0, 44, 
 129, 144, 32, 19, 
 54, 8, 17, 176, 
 1, 9, 32, 12, 
 17, 38, 4, 145, 
 34, 12, 17, 52, 
 68, 1, 48, 1, 
 25, 32, 12, 11, 
 48, 8, 129, 162, 
 8, 136, 162, 8, 
 72, 48, 8, 152, 
 16, 68, 131, 
};

const uint8_t kmap0_word_len26_anagram0_seqs[] = {
 224, 235, 52, 1, 
 132, 211, 12, 90, 
 48, 17, 104, 166, 
 79, 64, 32, 160, 
 2, 129, 96, 8, 
 232, 243, 60, 72, 
 63, 29, 160, 254, 
 52, 131, 129, 33, 
 13, 38, 210, 43, 
 224, 223, 60, 128, 
 235, 183, 2, 94, 
 87, 8, 56, 243, 
 43, 184, 190, 222, 
 160, 136, 41, 189, 
 20, 27, 253, 82, 
 108, 246, 223, 86, 
 249, 159, 34, 235, 
 190, 242, 213, 243, 
 181, 90, 229, 215, 
 74, 141, 63, 145, 
 85, 62, 115, 223, 
 250, 121, 97, 204, 
 95, 143, 76, 167, 
 255, 38, 159, 62, 
 98, 124, 154, 218, 
 199, 73, 161, 210, 
 103, 44, 244, 156, 
 145, 21, 125, 142, 
 31, 225, 57, 254, 
 133, 248, 42, 62, 
 227, 207, 25, 138, 
 240, 245, 54, 194, 
 159, 219, 8, 99, 
 50, 99, 28, 135, 
 141, 65, 57, 41, 
 70, 74, 189, 24, 
 41, 133, 98, 68, 
 169, 141, 49, 53, 
 51, 70, 174, 161, 
 56, 89, 17, 98, 
 230, 141, 36, 95, 
 111, 143, 244, 217, 
 175, 210, 220, 183, 
 202, 190, 205, 43, 
 35, 125, 171, 12, 
 21, 188, 50, 244, 
 38, 203, 224, 191, 
 45, 115, 74, 133, 
 127, 168, 61, 62, 
 14, 227, 154, 156, 
 172, 107, 245, 220, 
 133, 245, 254, 219, 
 46, 147, 187, 250, 
 2, 205, 236, 11, 
 236, 181, 47, 214, 
 163, 199, 227, 198, 
 28, 222, 102, 120, 
 80, 204, 211, 65, 
 217, 186, 71, 144, 
 244, 28, 49, 201, 
 115, 4, 115, 211, 
 49, 86, 132, 199, 
 180, 85, 222, 63, 
 212, 120, 255, 66, 
 207, 109, 237, 204, 
 119, 112, 53, 221, 
 243, 219, 124, 231, 
 86, 63, 124, 18, 
 205, 240, 83, 242, 
 192, 175, 213, 10, 
 91, 74, 107, 167, 
 250, 184, 157, 234, 
 247, 116, 170, 49, 
 219, 122, 188, 110, 
 235, 90, 217, 165, 
 214, 103, 151, 52, 
 176, 68, 95, 55, 
 42, 125, 86, 132, 
 100, 189, 23, 82, 
 163, 149, 77, 113, 
 158, 5, 69, 214, 
 219, 233, 111, 245, 
 166, 215, 191, 157, 
 94, 111, 114, 122, 
 205, 79, 233, 231, 
 36, 167, 31, 209, 
 148, 188, 48, 100, 
 106, 41, 201, 41, 
 206, 38, 167, 144, 
 153, 156, 242, 72, 
 79, 156, 251, 173, 
 49, 125, 183, 198, 
 84, 248, 90, 31, 
 211, 107, 253, 105, 
 134, 181, 181, 84, 
 84, 122, 78, 95, 
 201, 242, 118, 37, 
 235, 22, 149, 242, 
 60, 213, 160, 102, 
 88, 199, 187, 69, 
 101, 103, 25, 53, 
 79, 37, 151, 201, 
 175, 91, 38, 255, 
 236, 188, 236, 204, 
 243, 42, 35, 141, 
 5, 140, 59, 78, 
 150, 197, 4, 150, 
 188, 252, 199, 79, 
 243, 211, 79, 193, 
 152, 169, 46, 247, 
 173, 79, 220, 138, 
 30, 115, 138, 88, 
 200, 129, 37, 47, 
 215, 208, 219, 188, 
 158, 38, 243, 78, 
 151, 204, 59, 173, 
 55, 239, 68, 201, 
 188, 19, 122, 243, 
 102, 217, 193, 249, 
 92, 50, 103, 41, 
 173, 92, 240, 58, 
 237, 99, 137, 188, 
 240, 233, 211, 66, 
 199, 20, 219, 233, 
 244, 108, 232, 157, 
 189, 243, 57, 253, 
 78, 159, 79, 59, 
 45, 246, 231, 42, 
 127, 157, 231, 182, 
 174, 248, 248, 186, 
 162, 73, 244, 138, 
 29, 212, 42, 54, 
 119, 168, 152, 73, 
 61, 215, 39, 242, 
 2, 
};

const LookupOfLength kmap0_word_len26_anagram0 = {
  416, // seq_bit_len_and_anagram
  165, // num_chords
  kmap0_word_len26_anagram0_chords, // chords
  kmap0_word_len26_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len26_anagram1_chords[] = {
 144, 0, 2, 2, 
 36, 10, 128, 12, 
 18, 0, 36, 80, 
 2, 68, 3, 34, 
 12, 136, 160, 5, 
 136, 32, 12, 17, 
 128, 4, 26, 16, 
 65, 8, 16, 76, 
 8, 16, 4, 153, 
 16, 64, 130, 148, 
 9, 16, 48, 69, 
 24, 0, 13, 10, 
 128, 73, 10, 52, 
 0, 80, 34, 64, 
 129, 48, 69, 16, 
 18, 0, 74, 18, 
 0, 202, 50, 8, 
 17, 
};

const uint8_t kmap0_word_len26_anagram1_seqs[] = {
 0, 129, 65, 0, 
 132, 173, 15, 210, 
 15, 6, 224, 159, 
 135, 47, 101, 227, 
 62, 229, 164, 253, 
 250, 20, 247, 139, 
 191, 63, 248, 90, 
 132, 74, 31, 86, 
 41, 157, 94, 165, 
 215, 163, 79, 190, 
 64, 91, 30, 19, 
 101, 125, 255, 72, 
 107, 73, 31, 75, 
 37, 141, 171, 214, 
 60, 156, 93, 38, 
 55, 237, 248, 254, 
 145, 140, 109, 69, 
 115, 147, 21, 45, 
 246, 108, 54, 
};

const LookupOfLength kmap0_word_len26_anagram1 = {
  417, // seq_bit_len_and_anagram
  23, // num_chords
  kmap0_word_len26_anagram1_chords, // chords
  kmap0_word_len26_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len26_anagram2_chords[] = {
 16, 0, 147, 52, 
 0, 129, 52, 0, 
 17, 16, 32, 18, 
 128, 0, 154, 128, 
 4, 26, 16, 0, 
 139, 16, 37, 17, 
 50, 8, 8, 52, 
 8, 16, 4, 12, 
 128, 144, 0, 81, 
 48, 8, 80, 18, 
 64, 27, 
};

const uint8_t kmap0_word_len26_anagram2_seqs[] = {
 96, 11, 242, 156, 
 153, 200, 123, 230, 
 93, 15, 66, 207, 
 20, 24, 20, 90, 
 224, 124, 17, 234, 
 139, 181, 238, 241, 
 11, 61, 157, 82, 
 86, 39, 167, 211, 
 83, 233, 203, 254, 
 152, 55, 198, 162, 
 135, 51, 95, 91, 
 215, 3, 
};

const LookupOfLength kmap0_word_len26_anagram2 = {
  418, // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_word_len26_anagram2_chords, // chords
  kmap0_word_len26_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len26_anagram3_chords[] = {
 36, 0, 18, 
};

const uint8_t kmap0_word_len26_anagram3_seqs[] = {
 53, 215, 90, 0, 
};

const LookupOfLength kmap0_word_len26_anagram3 = {
  419, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len26_anagram3_chords, // chords
  kmap0_word_len26_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len26_anagram4_chords[] = {
 48, 8, 80, 
};

const uint8_t kmap0_word_len26_anagram4_seqs[] = {
 156, 83, 242, 0, 
};

const LookupOfLength kmap0_word_len26_anagram4 = {
  420, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len26_anagram4_chords, // chords
  kmap0_word_len26_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len27_anagram0_chords[] = {
 16, 73, 16, 48, 
 1, 0, 16, 32, 
 26, 50, 40, 128, 
 16, 13, 144, 16, 
 0, 208, 18, 13, 
 1, 50, 33, 128, 
 0, 0, 73, 2, 
 40, 65, 32, 32, 
 81, 16, 5, 3, 
 2, 69, 16, 48, 
 5, 26, 18, 4, 
 11, 16, 4, 9, 
 18, 4, 147, 0, 
 13, 3, 54, 96, 
 8, 180, 1, 136, 
 164, 8, 1, 36, 
 36, 26, 36, 64, 
 18, 52, 64, 24, 
 164, 0, 9, 36, 
 12, 66, 18, 4, 
 27, 144, 0, 131, 
 164, 12, 3, 144, 
 72, 18, 144, 0, 
 26, 144, 0, 27, 
 146, 0, 74, 144, 
 0, 11, 144, 0, 
 75, 144, 0, 202, 
 176, 8, 26, 144, 
 0, 19, 144, 0, 
 147, 4, 12, 18, 
 48, 77, 0, 148, 
 64, 146, 162, 69, 
 128, 18, 68, 64, 
 180, 64, 128, 160, 
 69, 24, 144, 1, 
 17, 148, 8, 146, 
 144, 64, 88, 176, 
 33, 8, 20, 0, 
 131, 48, 0, 194, 
 146, 0, 131, 22, 
 0, 146, 20, 0, 
 147, 148, 0, 194, 
 16, 64, 139, 2, 
 33, 72, 2, 33, 
 138, 176, 1, 17, 
 128, 13, 144, 128, 
 13, 17, 162, 1, 
 72, 48, 1, 17, 
 34, 33, 131, 176, 
 1, 128, 166, 1, 
 64, 160, 37, 3, 
 162, 33, 3, 176, 
 9, 24, 34, 5, 
 17, 164, 36, 16, 
 50, 33, 1, 164, 
 32, 18, 130, 9, 
 24, 18, 0, 155, 
 48, 65, 144, 164, 
 13, 0, 16, 36, 
 145, 48, 0, 147, 
 48, 5, 146, 50, 
 0, 208, 18, 4, 
 145, 34, 13, 24, 
 16, 13, 17, 0, 
 12, 19, 36, 12, 
 129, 50, 72, 0, 
 144, 8, 18, 160, 
 72, 128, 48, 8, 
 64, 34, 8, 192, 
 32, 12, 129, 128, 
 68, 26, 18, 32, 
 25, 54, 64, 10, 
 52, 8, 24, 146, 
 1, 2, 144, 1, 
 65, 148, 4, 17, 
 164, 0, 1, 20, 
 0, 27, 4, 44, 
 16, 150, 0, 24, 
 148, 9, 3, 134, 
 0, 146, 20, 64, 
 18, 22, 0, 82, 
 20, 0, 89, 6, 
 1, 25, 134, 1, 
 17, 132, 8, 17, 
 38, 32, 72, 48, 
 64, 146, 38, 72, 
 128, 22, 0, 19, 
 50, 8, 18, 20, 
 4, 146, 20, 0, 
 83, 50, 72, 18, 
 36, 1, 18, 16, 
 5, 83, 146, 0, 
 75, 146, 0, 88, 
 146, 0, 72, 16, 
 32, 209, 160, 96, 
 192, 18, 41, 80, 
 34, 33, 193, 162, 
 72, 64, 22, 0, 
 66, 38, 1, 88, 
 32, 68, 192, 38, 
 64, 65, 32, 0, 
 211, 18, 4, 131, 
 146, 0, 73, 176, 
 1, 129, 48, 72, 
 131, 48, 12, 146, 
 34, 8, 3, 34, 
 12, 192, 16, 100, 
 131, 148, 68, 10, 
 0, 109, 2, 130, 
 64, 202, 144, 64, 
 26, 144, 0, 146, 
 160, 4, 19, 
};

const uint8_t kmap0_word_len27_anagram0_seqs[] = {
 64, 122, 92, 2, 
 6, 6, 55, 128, 
 214, 41, 64, 11, 
 22, 13, 4, 190, 
 100, 32, 96, 102, 
 131, 210, 111, 27, 
 144, 251, 134, 128, 
 193, 2, 5, 156, 
 122, 33, 88, 152, 
 135, 255, 56, 140, 
 251, 199, 124, 203, 
 191, 173, 88, 188, 
 98, 91, 247, 117, 
 173, 250, 63, 219, 
 72, 254, 221, 199, 
 210, 105, 216, 42, 
 79, 83, 232, 125, 
 198, 110, 164, 115, 
 94, 17, 158, 89, 
 202, 226, 204, 35, 
 173, 103, 222, 13, 
 197, 79, 53, 51, 
 122, 246, 91, 49, 
 136, 140, 139, 145, 
 206, 95, 140, 100, 
 89, 96, 40, 122, 
 20, 67, 209, 179, 
 24, 138, 205, 198, 
 80, 53, 46, 134, 
 178, 117, 49, 148, 
 131, 140, 161, 162, 
 11, 140, 25, 227, 
 98, 204, 250, 2, 
 231, 203, 22, 242, 
 211, 223, 150, 174, 
 20, 133, 236, 167, 
 184, 101, 179, 159, 
 45, 35, 159, 100, 
 57, 127, 135, 250, 
 56, 98, 214, 169, 
 82, 20, 86, 25, 
 195, 182, 70, 190, 
 161, 47, 208, 117, 
 125, 129, 153, 237, 
 139, 216, 70, 95, 
 84, 79, 251, 162, 
 122, 214, 23, 53, 
 216, 190, 88, 171, 
 60, 90, 155, 225, 
 65, 173, 8, 143, 
 152, 219, 123, 196, 
 164, 167, 35, 38, 
 253, 30, 153, 59, 
 244, 200, 155, 199, 
 55, 245, 34, 188, 
 35, 110, 242, 29, 
 204, 93, 239, 88, 
 132, 127, 199, 194, 
 198, 59, 68, 143, 
 222, 185, 247, 7, 
 254, 156, 49, 208, 
 125, 195, 133, 113, 
 158, 69, 235, 17, 
 147, 90, 5, 140, 
 43, 144, 229, 237, 
 210, 159, 113, 146, 
 127, 161, 135, 140, 
 155, 199, 228, 251, 
 177, 32, 55, 231, 
 49, 245, 122, 158, 
 210, 207, 221, 154, 
 126, 74, 222, 244, 
 179, 197, 164, 95, 
 250, 51, 89, 118, 
 78, 201, 41, 166, 
 72, 33, 51, 69, 
 202, 236, 156, 82, 
 102, 234, 148, 242, 
 230, 39, 253, 153, 
 184, 170, 123, 161, 
 71, 125, 61, 219, 
 154, 211, 233, 137, 
 227, 104, 116, 28, 
 7, 123, 163, 122, 
 126, 29, 121, 107, 
 222, 234, 65, 235, 
 86, 248, 147, 190, 
 118, 168, 61, 53, 
 176, 228, 173, 65, 
 141, 69, 29, 163, 
 165, 235, 24, 155, 
 93, 199, 108, 221, 
 58, 173, 123, 212, 
 137, 163, 183, 78, 
 164, 186, 53, 107, 
 51, 44, 147, 61, 
 69, 153, 220, 101, 
 199, 232, 174, 59, 
 70, 183, 232, 113, 
 165, 71, 143, 185, 
 26, 119, 44, 182, 
 175, 147, 239, 179, 
 224, 63, 188, 5, 
 27, 183, 67, 217, 
 202, 49, 205, 102, 
 238, 80, 134, 166, 
 245, 48, 140, 76, 
 146, 225, 180, 75, 
 76, 125, 195, 229, 
 144, 157, 19, 87, 
 99, 155, 185, 78, 
 235, 205, 101, 242, 
 75, 222, 92, 91, 
 242, 22, 148, 121, 
 31, 183, 201, 107, 
 229, 14, 221, 184, 
 111, 242, 94, 77, 
 162, 197, 39, 114, 
 33, 54, 110, 39, 
 177, 57, 63, 93, 
 253, 180, 240, 234, 
 175, 161, 87, 248, 
 88, 186, 54, 113, 
 232, 53, 84, 122, 
 46, 60, 113, 81, 
 124, 228, 89, 
};

const LookupOfLength kmap0_word_len27_anagram0 = {
  432, // seq_bit_len_and_anagram
  149, // num_chords
  kmap0_word_len27_anagram0_chords, // chords
  kmap0_word_len27_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len27_anagram1_chords[] = {
 18, 64, 0, 0, 
 0, 192, 16, 36, 
 129, 36, 4, 145, 
 52, 64, 136, 16, 
 4, 155, 32, 32, 
 18, 144, 0, 11, 
 144, 0, 75, 160, 
 0, 27, 18, 64, 
 138, 50, 72, 0, 
 144, 64, 26, 16, 
 36, 10, 20, 0, 
 131, 22, 0, 146, 
 50, 1, 24, 0, 
 13, 146, 16, 13, 
 16, 132, 0, 146, 
 16, 68, 18, 164, 
 0, 81, 16, 4, 
 90, 34, 8, 65, 
 16, 36, 17, 176, 
 8, 128, 
};

const uint8_t kmap0_word_len27_anagram1_seqs[] = {
 160, 129, 4, 6, 
 12, 24, 208, 47, 
 36, 175, 207, 201, 
 251, 116, 102, 149, 
 100, 180, 238, 60, 
 33, 204, 131, 16, 
 67, 215, 186, 24, 
 186, 230, 197, 200, 
 186, 133, 52, 82, 
 171, 101, 139, 45, 
 109, 197, 144, 30, 
 43, 124, 69, 251, 
 162, 26, 215, 23, 
 181, 199, 71, 235, 
 237, 57, 232, 75, 
 69, 250, 41, 121, 
 234, 196, 69, 49, 
 190, 254, 200, 137, 
 51, 243, 50, 190, 
 170, 135, 115, 74, 
 189, 11, 253, 235, 
 17, 131, 114, 50, 
};

const LookupOfLength kmap0_word_len27_anagram1 = {
  433, // seq_bit_len_and_anagram
  26, // num_chords
  kmap0_word_len27_anagram1_chords, // chords
  kmap0_word_len27_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len27_anagram2_chords[] = {
 2, 4, 147, 0, 
 4, 26, 164, 68, 
 16, 52, 4, 16, 
 16, 68, 146, 176, 
 9, 16, 16, 13, 
 16, 48, 13, 64, 
 16, 96, 19, 
};

const uint8_t kmap0_word_len27_anagram2_seqs[] = {
 160, 247, 169, 0, 
 250, 138, 197, 159, 
 19, 47, 207, 60, 
 254, 44, 141, 244, 
 227, 123, 34, 68, 
 143, 211, 79, 137, 
 95, 252, 219, 215, 
 241, 34, 4, 
};

const LookupOfLength kmap0_word_len27_anagram2 = {
  434, // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_word_len27_anagram2_chords, // chords
  kmap0_word_len27_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len27_anagram3_chords[] = {
 48, 5, 136, 48, 
 5, 16, 52, 0, 
 80, 
};

const uint8_t kmap0_word_len27_anagram3_seqs[] = {
 7, 189, 222, 190, 
 127, 254, 54, 231, 
 234, 57, 1, 
};

const LookupOfLength kmap0_word_len27_anagram3 = {
  435, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_word_len27_anagram3_chords, // chords
  kmap0_word_len27_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len27_anagram7_chords[] = {
 48, 8, 80, 
};

const uint8_t kmap0_word_len27_anagram7_seqs[] = {
 99, 209, 195, 6, 
};

const LookupOfLength kmap0_word_len27_anagram7 = {
  439, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len27_anagram7_chords, // chords
  kmap0_word_len27_anagram7_seqs, // sequences
};

const uint8_t kmap0_word_len28_anagram0_chords[] = {
 6, 4, 0, 0, 
 64, 72, 32, 96, 
 3, 0, 68, 154, 
 34, 96, 8, 128, 
 32, 146, 144, 0, 
 216, 32, 0, 146, 
 0, 72, 80, 0, 
 72, 146, 146, 0, 
 138, 6, 0, 2, 
 6, 0, 64, 4, 
 0, 3, 34, 0, 
 16, 32, 0, 144, 
 32, 4, 64, 52, 
 4, 74, 164, 4, 
 80, 52, 76, 16, 
 18, 12, 9, 144, 
 36, 25, 16, 36, 
 153, 52, 13, 65, 
 52, 37, 128, 180, 
 64, 26, 38, 4, 
 26, 54, 65, 16, 
 180, 9, 24, 180, 
 64, 82, 144, 68, 
 66, 32, 37, 3, 
 16, 36, 138, 18, 
 12, 131, 48, 0, 
 211, 176, 1, 130, 
 148, 8, 3, 148, 
 0, 11, 162, 1, 
 10, 130, 0, 75, 
 128, 4, 11, 130, 
 4, 11, 128, 0, 
 155, 176, 0, 202, 
 166, 64, 2, 50, 
 0, 74, 48, 0, 
 27, 16, 65, 72, 
 18, 64, 73, 52, 
 64, 19, 16, 64, 
 74, 48, 72, 80, 
 22, 64, 65, 34, 
 65, 24, 48, 68, 
 3, 48, 5, 137, 
 150, 64, 64, 150, 
 0, 200, 20, 8, 
 131, 20, 4, 138, 
 38, 5, 18, 160, 
 13, 64, 144, 65, 
 130, 50, 1, 16, 
 160, 13, 144, 144, 
 65, 146, 160, 1, 
 17, 20, 9, 16, 
 50, 65, 16, 32, 
 9, 26, 52, 13, 
 128, 48, 5, 152, 
 50, 1, 26, 50, 
 1, 11, 164, 5, 
 128, 32, 5, 154, 
 160, 65, 24, 128, 
 96, 130, 18, 64, 
 74, 2, 4, 137, 
 50, 0, 152, 2, 
 4, 201, 2, 4, 
 73, 18, 68, 73, 
 50, 1, 25, 50, 
 9, 72, 36, 76, 
 128, 48, 12, 80, 
 146, 8, 9, 18, 
 12, 152, 18, 12, 
 146, 144, 8, 89, 
 128, 72, 18, 0, 
 72, 210, 6, 13, 
 8, 48, 4, 153, 
 130, 1, 27, 48, 
 4, 154, 178, 0, 
 137, 22, 4, 9, 
 20, 4, 25, 150, 
 0, 72, 22, 0, 
 81, 6, 32, 82, 
 134, 32, 82, 134, 
 64, 130, 20, 4, 
 152, 150, 0, 25, 
 148, 0, 82, 148, 
 0, 81, 38, 0, 
 130, 132, 32, 27, 
 38, 4, 17, 18, 
 68, 17, 50, 0, 
 19, 16, 1, 147, 
 48, 1, 80, 166, 
 0, 24, 144, 12, 
 26, 178, 0, 25, 
 16, 68, 66, 18, 
 12, 88, 178, 0, 
 80, 50, 8, 82, 
 48, 12, 208, 130, 
 0, 202, 50, 4, 
 65, 146, 64, 208, 
 160, 33, 65, 22, 
 4, 194, 150, 0, 
 208, 130, 4, 73, 
 48, 4, 65, 16, 
 36, 193, 16, 32, 
 83, 32, 9, 83, 
 38, 8, 65, 48, 
 64, 66, 48, 0, 
 66, 48, 8, 82, 
 2, 96, 67, 2, 
 5, 17, 32, 37, 
 1, 0, 45, 73, 
 144, 40, 17, 2, 
 4, 89, 16, 64, 
 27, 48, 12, 138, 
 48, 8, 147, 48, 
 12, 25, 34, 9, 
 24, 128, 96, 139, 
 128, 73, 26, 144, 
 64, 146, 148, 8, 
 17, 
};

const uint8_t kmap0_word_len28_anagram0_seqs[] = {
 224, 65, 5, 13, 
 36, 80, 192, 64, 
 230, 69, 8, 100, 
 65, 175, 0, 182, 
 202, 12, 96, 16, 
 21, 64, 32, 212, 
 12, 4, 50, 21, 
 32, 13, 11, 13, 
 210, 133, 208, 64, 
 27, 131, 12, 42, 
 64, 208, 160, 2, 
 6, 13, 22, 32, 
 168, 32, 131, 1, 
 13, 50, 24, 64, 
 32, 3, 6, 255, 
 39, 91, 209, 127, 
 114, 204, 249, 82, 
 244, 156, 175, 157, 
 126, 253, 26, 11, 
 61, 63, 86, 193, 
 123, 62, 151, 188, 
 167, 225, 211, 113, 
 186, 8, 149, 103, 
 235, 79, 113, 78, 
 203, 219, 231, 68, 
 201, 122, 78, 92, 
 217, 248, 140, 33, 
 141, 159, 111, 184, 
 8, 95, 213, 132, 
 212, 233, 215, 72, 
 153, 215, 131, 65, 
 228, 219, 24, 169, 
 122, 141, 161, 232, 
 186, 24, 122, 244, 
 141, 161, 220, 188, 
 24, 186, 143, 139, 
 161, 251, 173, 24, 
 186, 19, 132, 145, 
 149, 77, 152, 207, 
 104, 137, 185, 185, 
 213, 152, 103, 172, 
 43, 125, 88, 217, 
 210, 186, 205, 43, 
 93, 243, 22, 210, 
 140, 86, 41, 205, 
 30, 209, 210, 92, 
 123, 45, 243, 180, 
 222, 150, 25, 127, 
 109, 242, 253, 186, 
 174, 205, 33, 237, 
 202, 77, 161, 190, 
 112, 170, 235, 139, 
 74, 175, 199, 159, 
 211, 120, 124, 138, 
 204, 135, 137, 226, 
 122, 244, 157, 199, 
 7, 189, 24, 115, 
 80, 92, 61, 71, 
 204, 29, 123, 140, 
 93, 214, 199, 180, 
 188, 125, 100, 45, 
 21, 247, 167, 147, 
 124, 91, 61, 79, 
 183, 213, 211, 120, 
 91, 189, 141, 55, 
 197, 249, 116, 235, 
 15, 21, 247, 68, 
 86, 9, 131, 40, 
 174, 173, 178, 209, 
 220, 218, 219, 79, 
 173, 2, 121, 220, 
 202, 251, 68, 173, 
 188, 175, 219, 202, 
 235, 151, 173, 235, 
 219, 83, 210, 22, 
 205, 244, 233, 148, 
 159, 252, 156, 199, 
 201, 186, 29, 154, 
 90, 61, 79, 169, 
 231, 145, 156, 66, 
 121, 61, 41, 102, 
 226, 154, 10, 46, 
 67, 250, 181, 212, 
 170, 206, 59, 79, 
 26, 219, 71, 161, 
 25, 201, 63, 145, 
 151, 90, 93, 127, 
 219, 186, 245, 119, 
 61, 90, 173, 220, 
 161, 213, 195, 205, 
 91, 97, 193, 141, 
 21, 22, 220, 81, 
 155, 40, 174, 149, 
 94, 213, 83, 163, 
 117, 61, 117, 2, 
 205, 92, 39, 214, 
 188, 53, 159, 212, 
 88, 139, 133, 161, 
 243, 231, 217, 59, 
 47, 251, 215, 99, 
 156, 220, 59, 62, 
 200, 184, 227, 123, 
 204, 60, 125, 158, 
 161, 19, 233, 21, 
 61, 145, 183, 213, 
 252, 136, 47, 205, 
 78, 173, 63, 236, 
 233, 200, 204, 30, 
 177, 209, 108, 209, 
 243, 196, 77, 141, 
 161, 220, 155, 127, 
 205, 65, 178, 61, 
 28, 249, 134, 203, 
 213, 216, 79, 92, 
 163, 201, 195, 251, 
 219, 161, 188, 191, 
 121, 205, 235, 167, 
 133, 188, 227, 69, 
 200, 59, 25, 75, 
 156, 207, 212, 203, 
 25, 209, 150, 156, 
 17, 205, 204, 121, 
 68, 23, 124, 237, 
 69, 184, 63, 125, 
 28, 251, 249, 134, 
 187, 240, 181, 196, 
 11, 29, 227, 180, 
 243, 202, 189, 123, 
 181, 110, 33, 62, 
 89, 209, 162, 103, 
 125, 33, 122, 61, 
 175, 98, 207, 221, 
 122, 13, 21, 188, 
 215, 208, 82, 81, 
 152, 40, 174, 101, 
 99, 61, 1, 
};

const LookupOfLength kmap0_word_len28_anagram0 = {
  448, // seq_bit_len_and_anagram
  155, // num_chords
  kmap0_word_len28_anagram0_chords, // chords
  kmap0_word_len28_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len28_anagram1_chords[] = {
 0, 68, 8, 18, 
 4, 136, 48, 9, 
 16, 6, 0, 64, 
 18, 4, 208, 2, 
 64, 66, 16, 4, 
 195, 2, 5, 16, 
 16, 68, 66, 18, 
 12, 18, 2, 4, 
 194, 48, 64, 130, 
 18, 68, 3, 146, 
 8, 9, 48, 12, 
 129, 144, 1, 26, 
 148, 0, 147, 18, 
 65, 8, 18, 32, 
 25, 18, 8, 192, 
 52, 8, 128, 164, 
 0, 18, 148, 0, 
 64, 22, 4, 16, 
 148, 64, 18, 148, 
 0, 19, 150, 0, 
 25, 176, 8, 18, 
 50, 0, 65, 128, 
 68, 19, 128, 4, 
 19, 130, 4, 17, 
};

const uint8_t kmap0_word_len28_anagram1_seqs[] = {
 64, 2, 5, 15, 
 76, 223, 250, 224, 
 30, 187, 4, 26, 
 48, 168, 160, 121, 
 222, 4, 248, 218, 
 204, 96, 125, 241, 
 252, 199, 241, 61, 
 248, 140, 47, 141, 
 158, 79, 141, 72, 
 207, 220, 40, 77, 
 249, 194, 178, 113, 
 127, 237, 20, 219, 
 161, 78, 153, 126, 
 109, 61, 98, 208, 
 190, 168, 49, 219, 
 135, 74, 31, 173, 
 208, 211, 155, 154, 
 185, 201, 41, 167, 
 147, 28, 136, 185, 
 22, 53, 152, 205, 
 92, 231, 123, 218, 
 117, 2, 109, 89, 
 39, 214, 184, 117, 
 98, 221, 58, 198, 
 16, 61, 188, 189, 
 121, 189, 113, 253, 
 145, 59, 143, 27, 
 179, 243, 189, 49, 
};

const LookupOfLength kmap0_word_len28_anagram1 = {
  449, // seq_bit_len_and_anagram
  32, // num_chords
  kmap0_word_len28_anagram1_chords, // chords
  kmap0_word_len28_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len28_anagram2_chords[] = {
 16, 4, 153, 52, 
 4, 19, 48, 5, 
 152, 48, 1, 24, 
 20, 4, 25, 20, 
 0, 19, 148, 64, 
 18, 22, 8, 16, 
 20, 4, 16, 52, 
 0, 16, 48, 1, 
 80, 176, 0, 17, 
};

const uint8_t kmap0_word_len28_anagram2_seqs[] = {
 64, 224, 213, 123, 
 250, 243, 22, 86, 
 250, 185, 125, 79, 
 214, 219, 245, 103, 
 213, 83, 61, 232, 
 186, 53, 174, 210, 
 83, 199, 169, 61, 
 117, 92, 127, 60, 
 249, 60, 61, 156, 
 143, 195, 179, 49, 
 155, 199, 
};

const LookupOfLength kmap0_word_len28_anagram2 = {
  450, // seq_bit_len_and_anagram
  12, // num_chords
  kmap0_word_len28_anagram2_chords, // chords
  kmap0_word_len28_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len28_anagram3_chords[] = {
 48, 13, 64, 0, 
 4, 19, 128, 4, 
 27, 48, 0, 147, 
 16, 68, 146, 48, 
 8, 24, 
};

const uint8_t kmap0_word_len28_anagram3_seqs[] = {
 64, 244, 253, 252, 
 187, 243, 184, 248, 
 179, 17, 138, 148, 
 119, 61, 244, 215, 
 194, 51, 22, 173, 
 217, 
};

const LookupOfLength kmap0_word_len28_anagram3 = {
  451, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_word_len28_anagram3_chords, // chords
  kmap0_word_len28_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len28_anagram4_chords[] = {
 16, 36, 17, 
};

const uint8_t kmap0_word_len28_anagram4_seqs[] = {
 208, 191, 208, 3, 
};

const LookupOfLength kmap0_word_len28_anagram4 = {
  452, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len28_anagram4_chords, // chords
  kmap0_word_len28_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len29_anagram0_chords[] = {
 128, 0, 26, 18, 
 68, 136, 34, 76, 
 0, 16, 12, 208, 
 18, 12, 144, 128, 
 4, 216, 4, 40, 
 0, 4, 32, 8, 
 0, 0, 26, 128, 
 1, 2, 0, 72, 
 64, 48, 8, 73, 
 50, 8, 10, 160, 
 4, 11, 50, 44, 
 2, 16, 68, 80, 
 128, 69, 16, 128, 
 36, 130, 48, 69, 
 128, 0, 68, 210, 
 48, 12, 17, 160, 
 4, 208, 2, 36, 
 17, 32, 4, 193, 
 20, 12, 1, 52, 
 4, 138, 54, 4, 
 16, 52, 4, 66, 
 36, 8, 2, 54, 
 8, 128, 52, 36, 
 9, 180, 4, 136, 
 38, 33, 17, 52, 
 65, 1, 54, 4, 
 11, 6, 4, 131, 
 134, 4, 131, 6, 
 4, 11, 2, 68, 
 18, 162, 4, 11, 
 2, 36, 66, 130, 
 32, 26, 34, 0, 
 19, 144, 8, 11, 
 148, 12, 18, 150, 
 8, 130, 148, 8, 
 66, 160, 0, 203, 
 176, 8, 74, 176, 
 8, 27, 176, 8, 
 67, 162, 0, 138, 
 34, 4, 146, 50, 
 72, 144, 150, 64, 
 65, 50, 72, 80, 
 178, 8, 24, 20, 
 68, 138, 2, 13, 
 146, 16, 37, 17, 
 16, 69, 144, 18, 
 5, 10, 128, 65, 
 130, 166, 65, 16, 
 164, 1, 192, 180, 
 1, 128, 16, 44, 
 81, 144, 40, 24, 
 50, 5, 128, 50, 
 64, 138, 34, 0, 
 200, 162, 0, 152, 
 18, 73, 26, 180, 
 0, 209, 18, 44, 
 10, 2, 12, 145, 
 2, 12, 25, 2, 
 12, 147, 18, 76, 
 130, 50, 9, 9, 
 48, 13, 64, 130, 
 8, 136, 130, 8, 
 72, 130, 8, 25, 
 144, 9, 26, 32, 
 4, 153, 52, 0, 
 154, 180, 0, 147, 
 134, 0, 8, 178, 
 64, 65, 6, 4, 
 145, 134, 4, 72, 
 20, 68, 9, 20, 
 1, 19, 54, 0, 
 19, 6, 4, 195, 
 134, 0, 131, 134, 
 0, 25, 22, 64, 
 19, 52, 8, 25, 
 150, 8, 80, 148, 
 0, 80, 34, 73, 
 130, 148, 64, 88, 
 48, 9, 24, 0, 
 40, 19, 128, 36, 
 210, 0, 36, 83, 
 48, 9, 73, 16, 
 0, 75, 50, 1, 
 73, 128, 100, 66, 
 48, 32, 193, 2, 
 12, 208, 146, 0, 
 83, 6, 4, 193, 
 132, 0, 88, 48, 
 68, 208, 176, 5, 
 81, 48, 5, 89, 
 48, 64, 73, 50, 
 64, 66, 36, 0, 
 210, 52, 0, 67, 
 34, 4, 73, 16, 
 68, 83, 164, 8, 
 210, 16, 44, 145, 
 160, 33, 1, 144, 
 64, 145, 162, 0, 
 9, 48, 9, 19, 
 50, 12, 10, 32, 
 12, 2, 50, 40, 
 130, 48, 8, 25, 
 50, 9, 18, 178, 
 8, 88, 178, 8, 
 137, 50, 97, 3, 
 130, 72, 66, 16, 
 64, 211, 
};

const uint8_t kmap0_word_len29_anagram0_seqs[] = {
 0, 67, 53, 6, 
 200, 215, 54, 1, 
 249, 98, 75, 32, 
 240, 201, 12, 4, 
 62, 181, 129, 192, 
 115, 40, 72, 0, 
 150, 5, 10, 32, 
 168, 64, 65, 1, 
 16, 4, 56, 0, 
 2, 6, 9, 72, 
 192, 107, 209, 10, 
 68, 107, 163, 31, 
 49, 178, 238, 35, 
 108, 139, 126, 41, 
 199, 204, 127, 28, 
 49, 242, 9, 3, 
 6, 61, 145, 111, 
 203, 167, 235, 23, 
 252, 233, 215, 121, 
 126, 34, 243, 211, 
 207, 194, 233, 127, 
 230, 207, 180, 191, 
 235, 84, 247, 124, 
 122, 69, 159, 63, 
 211, 158, 211, 248, 
 153, 125, 26, 63, 
 179, 79, 83, 91, 
 244, 105, 245, 47, 
 60, 35, 200, 175, 
 231, 244, 13, 247, 
 204, 242, 246, 226, 
 159, 173, 94, 252, 
 218, 251, 132, 95, 
 123, 131, 240, 235, 
 126, 43, 254, 200, 
 126, 196, 207, 219, 
 161, 8, 159, 185, 
 25, 225, 132, 54, 
 98, 15, 230, 94, 
 140, 148, 172, 139, 
 145, 234, 143, 49, 
 82, 109, 50, 70, 
 170, 193, 198, 80, 
 206, 180, 24, 202, 
 57, 25, 67, 69, 
 207, 98, 240, 230, 
 100, 140, 172, 216, 
 132, 147, 177, 159, 
 164, 169, 69, 143, 
 116, 13, 238, 149, 
 45, 122, 216, 86, 
 177, 39, 212, 23, 
 245, 85, 30, 159, 
 154, 138, 195, 191, 
 208, 115, 88, 122, 
 158, 142, 214, 87, 
 244, 17, 68, 113, 
 61, 98, 206, 150, 
 55, 197, 153, 249, 
 142, 243, 36, 195, 
 79, 188, 30, 24, 
 147, 66, 221, 68, 
 190, 159, 90, 145, 
 178, 116, 43, 103, 
 106, 21, 200, 218, 
 49, 165, 150, 234, 
 130, 226, 228, 245, 
 164, 71, 216, 234, 
 244, 179, 253, 148, 
 126, 182, 95, 211, 
 239, 244, 69, 178, 
 108, 124, 74, 246, 
 182, 222, 201, 204, 
 127, 59, 53, 81, 
 135, 166, 102, 238, 
 208, 20, 218, 27, 
 147, 66, 75, 46, 
 244, 55, 207, 147, 
 22, 231, 73, 142, 
 83, 192, 184, 81, 
 91, 59, 52, 242, 
 114, 75, 215, 159, 
 237, 167, 250, 204, 
 29, 90, 173, 242, 
 117, 171, 231, 48, 
 110, 109, 220, 60, 
 174, 244, 188, 141, 
 53, 168, 183, 177, 
 198, 108, 135, 214, 
 177, 108, 220, 58, 
 22, 173, 91, 39, 
 82, 179, 235, 68, 
 13, 118, 153, 220, 
 88, 26, 115, 13, 
 149, 99, 209, 122, 
 123, 96, 177, 48, 
 49, 194, 160, 31, 
 198, 249, 69, 200, 
 190, 147, 117, 217, 
 186, 86, 52, 123, 
 183, 245, 102, 248, 
 50, 174, 12, 243, 
 46, 153, 59, 53, 
 253, 112, 96, 123, 
 11, 174, 191, 253, 
 196, 53, 148, 99, 
 184, 76, 254, 49, 
 111, 204, 223, 230, 
 157, 215, 219, 188, 
 89, 90, 151, 115, 
 99, 75, 115, 174, 
 149, 10, 206, 92, 
 141, 203, 153, 247, 
 91, 249, 234, 95, 
 15, 23, 233, 12, 
 90, 232, 73, 79, 
 11, 35, 223, 112, 
 67, 74, 242, 108, 
 238, 237, 208, 205, 
 83, 114, 33, 62, 
 98, 171, 197, 199, 
 156, 147, 104, 216, 
 72, 22, 173, 155, 
 199, 162, 167, 143, 
 66, 244, 112, 135, 
 138, 29, 100, 221, 
 171, 251, 134, 123, 
 109, 150, 145, 174, 
 99, 94, 50, 
};

const LookupOfLength kmap0_word_len29_anagram0 = {
  464, // seq_bit_len_and_anagram
  142, // num_chords
  kmap0_word_len29_anagram0_chords, // chords
  kmap0_word_len29_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len29_anagram1_chords[] = {
 16, 9, 146, 48, 
 4, 152, 36, 0, 
 16, 20, 4, 144, 
 48, 5, 24, 2, 
 36, 19, 162, 4, 
 11, 164, 64, 18, 
 52, 4, 19, 20, 
 36, 19, 48, 0, 
 147, 18, 76, 130, 
 144, 1, 9, 48, 
 5, 17, 34, 33, 
 129, 36, 9, 0, 
 54, 4, 144, 144, 
 0, 147, 164, 64, 
 26, 180, 0, 129, 
 148, 8, 17, 2, 
 68, 146, 36, 0, 
 9, 48, 12, 153, 
 178, 12, 129, 
};

const uint8_t kmap0_word_len29_anagram1_seqs[] = {
 160, 100, 162, 2, 
 208, 231, 177, 130, 
 10, 6, 228, 175, 
 245, 199, 244, 51, 
 175, 183, 127, 22, 
 78, 227, 103, 220, 
 14, 61, 99, 38, 
 174, 248, 117, 243, 
 24, 225, 215, 245, 
 96, 166, 205, 99, 
 105, 236, 244, 116, 
 8, 234, 82, 15, 
 255, 230, 241, 65, 
 125, 195, 61, 114, 
 217, 178, 212, 167, 
 231, 137, 98, 215, 
 83, 104, 156, 33, 
 139, 26, 68, 121, 
 93, 39, 82, 172, 
 231, 101, 227, 83, 
 62, 179, 110, 22, 
 173, 59, 79, 98, 
 7, 253, 26, 
};

const LookupOfLength kmap0_word_len29_anagram1 = {
  465, // seq_bit_len_and_anagram
  25, // num_chords
  kmap0_word_len29_anagram1_chords, // chords
  kmap0_word_len29_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len29_anagram2_chords[] = {
 36, 0, 2, 180, 
 0, 16, 52, 12, 
 16, 36, 8, 0, 
 50, 1, 8, 16, 
 4, 155, 
};

const uint8_t kmap0_word_len29_anagram2_seqs[] = {
 0, 65, 5, 25, 
 56, 79, 84, 255, 
 121, 142, 197, 51, 
 151, 45, 123, 91, 
 115, 171, 233, 215, 
 138, 5, 
};

const LookupOfLength kmap0_word_len29_anagram2 = {
  466, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_word_len29_anagram2_chords, // chords
  kmap0_word_len29_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len30_anagram0_chords[] = {
 36, 64, 64, 2, 
 64, 18, 0, 69, 
 0, 36, 1, 128, 
 4, 4, 152, 4, 
 1, 128, 128, 64, 
 136, 36, 0, 2, 
 4, 1, 2, 34, 
 4, 80, 0, 68, 
 88, 128, 36, 88, 
 36, 8, 8, 2, 
 4, 146, 32, 68, 
 209, 48, 76, 10, 
 34, 5, 73, 16, 
 68, 146, 54, 12, 
 9, 130, 68, 24, 
 6, 36, 64, 134, 
 4, 9, 132, 4, 
 146, 50, 44, 18, 
 162, 68, 24, 48, 
 13, 16, 144, 76, 
 66, 54, 1, 9, 
 52, 64, 11, 164, 
 33, 1, 160, 5, 
 131, 182, 8, 10, 
 132, 12, 3, 180, 
 8, 3, 160, 64, 
 11, 176, 1, 74, 
 162, 8, 11, 176, 
 5, 18, 18, 9, 
 19, 0, 4, 211, 
 162, 0, 82, 162, 
 32, 74, 16, 68, 
 82, 18, 65, 3, 
 18, 64, 91, 144, 
 64, 83, 180, 72, 
 128, 34, 64, 66, 
 178, 72, 18, 160, 
 77, 16, 18, 4, 
 209, 18, 0, 147, 
 50, 33, 200, 148, 
 0, 27, 20, 8, 
 26, 16, 32, 25, 
 48, 0, 131, 20, 
 0, 202, 16, 8, 
 147, 130, 5, 11, 
 2, 5, 67, 132, 
 1, 146, 130, 1, 
 209, 176, 9, 16, 
 176, 1, 25, 144, 
 73, 16, 148, 9, 
 24, 176, 1, 194, 
 48, 44, 81, 32, 
 33, 26, 38, 96, 
 18, 50, 13, 8, 
 6, 12, 137, 18, 
 4, 90, 18, 0, 
 89, 16, 13, 147, 
 160, 5, 152, 4, 
 12, 144, 48, 1, 
 152, 48, 73, 128, 
 34, 41, 9, 162, 
 5, 130, 50, 12, 
 64, 50, 13, 17, 
 130, 73, 18, 176, 
 13, 9, 48, 76, 
 8, 34, 12, 24, 
 180, 0, 82, 180, 
 8, 80, 144, 1, 
 72, 134, 12, 129, 
 162, 5, 26, 54, 
 12, 64, 20, 4, 
 155, 54, 8, 9, 
 20, 36, 80, 22, 
 1, 146, 20, 0, 
 90, 54, 12, 17, 
 180, 64, 18, 150, 
 1, 144, 148, 32, 
 17, 180, 0, 80, 
 176, 8, 144, 16, 
 8, 81, 34, 64, 
 209, 128, 44, 67, 
 180, 0, 64, 48, 
 5, 82, 52, 64, 
 72, 0, 4, 219, 
 164, 4, 3, 144, 
 4, 145, 54, 0, 
 17, 180, 0, 145, 
 34, 12, 73, 50, 
 64, 136, 34, 12, 
 25, 34, 12, 11, 
 16, 100, 19, 144, 
 72, 130, 18, 73, 
 2, 50, 65, 130, 
 130, 64, 130, 128, 
 76, 138, 
};

const uint8_t kmap0_word_len30_anagram0_seqs[] = {
 64, 130, 19, 48, 
 144, 160, 65, 1, 
 14, 32, 193, 131, 
 27, 84, 64, 64, 
 224, 235, 43, 32, 
 112, 128, 10, 40, 
 84, 134, 130, 10, 
 16, 156, 160, 130, 
 3, 32, 152, 204, 
 220, 15, 248, 85, 
 206, 3, 134, 63, 
 161, 64, 4, 21, 
 232, 227, 20, 212, 
 248, 82, 32, 243, 
 190, 20, 95, 209, 
 127, 127, 43, 239, 
 211, 248, 101, 241, 
 233, 108, 235, 190, 
 202, 137, 150, 95, 
 225, 115, 255, 215, 
 26, 173, 251, 181, 
 78, 92, 252, 32, 
 108, 209, 63, 50, 
 183, 198, 139, 158, 
 191, 253, 87, 115, 
 36, 159, 86, 31, 
 189, 167, 247, 106, 
 235, 25, 249, 134, 
 139, 191, 79, 113, 
 99, 164, 179, 213, 
 24, 169, 62, 46, 
 70, 170, 121, 141, 
 161, 50, 227, 98, 
 232, 145, 217, 24, 
 42, 54, 46, 70, 
 158, 191, 141, 211, 
 88, 242, 226, 20, 
 188, 79, 152, 167, 
 35, 51, 102, 134, 
 29, 42, 141, 227, 
 103, 75, 31, 141, 
 189, 210, 202, 189, 
 133, 52, 239, 68, 
 33, 45, 154, 162, 
 202, 102, 204, 204, 
 178, 197, 24, 180, 
 20, 99, 190, 228, 
 31, 106, 243, 154, 
 140, 59, 141, 214, 
 155, 154, 161, 117, 
 39, 106, 97, 45, 
 91, 36, 123, 161, 
 71, 189, 190, 48, 
 230, 181, 47, 170, 
 149, 237, 139, 29, 
 39, 31, 143, 219, 
 161, 199, 51, 54, 
 239, 65, 81, 107, 
 113, 80, 76, 243, 
 30, 49, 22, 61, 
 71, 204, 102, 245, 
 49, 182, 140, 116, 
 76, 148, 181, 222, 
 148, 49, 216, 240, 
 71, 52, 47, 204, 
 122, 79, 1, 139, 
 115, 90, 118, 250, 
 187, 213, 157, 42, 
 189, 110, 43, 142, 
 159, 221, 186, 30, 
 243, 10, 60, 150, 
 188, 2, 63, 119, 
 168, 192, 151, 45, 
 43, 144, 245, 38, 
 151, 40, 203, 219, 
 37, 237, 27, 46, 
 197, 221, 248, 148, 
 158, 185, 69, 167, 
 190, 231, 215, 41, 
 100, 31, 69, 10, 
 221, 191, 157, 178, 
 202, 87, 107, 143, 
 248, 250, 113, 50, 
 230, 113, 156, 236, 
 17, 29, 199, 97, 
 101, 71, 221, 78, 
 79, 49, 247, 107, 
 99, 125, 230, 22, 
 93, 173, 79, 91, 
 84, 235, 118, 78, 
 213, 3, 191, 114, 
 29, 31, 125, 81, 
 199, 108, 69, 215, 
 105, 241, 215, 117, 
 66, 102, 116, 157, 
 56, 154, 92, 39, 
 42, 244, 214, 60, 
 53, 216, 99, 49, 
 72, 52, 59, 153, 
 215, 195, 101, 114, 
 207, 242, 70, 122, 
 132, 156, 107, 13, 
 54, 231, 57, 30, 
 205, 153, 171, 85, 
 114, 161, 251, 23, 
 27, 231, 35, 198, 
 6, 121, 126, 189, 
 211, 103, 94, 239, 
 68, 62, 201, 203, 
 89, 63, 117, 214, 
 46, 147, 45, 254, 
 244, 235, 138, 191, 
 141, 175, 87, 255, 
 66, 207, 213, 132, 
 145, 124, 109, 44, 
 89, 94, 251, 190, 
 201, 215, 38, 138, 
 235, 69, 10, 125, 
 9, 
};

const LookupOfLength kmap0_word_len30_anagram0 = {
  480, // seq_bit_len_and_anagram
  126, // num_chords
  kmap0_word_len30_anagram0_chords, // chords
  kmap0_word_len30_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len30_anagram1_chords[] = {
 36, 64, 64, 32, 
 9, 64, 34, 1, 
 0, 4, 40, 0, 
 0, 36, 9, 36, 
 8, 2, 180, 0, 
 17, 128, 9, 19, 
 36, 0, 64, 32, 
 13, 0, 180, 32, 
 17, 52, 1, 16, 
 52, 4, 130, 48, 
 0, 27, 2, 4, 
 147, 144, 0, 27, 
 144, 8, 26, 16, 
 4, 27, 16, 37, 
 17, 48, 5, 152, 
 18, 4, 145, 48, 
 13, 64, 148, 1, 
 80, 48, 5, 144, 
 54, 0, 25, 180, 
 64, 130, 18, 64, 
 27, 
};

const uint8_t kmap0_word_len30_anagram1_seqs[] = {
 224, 4, 12, 36, 
 184, 1, 131, 4, 
 110, 144, 65, 131, 
 4, 42, 128, 64, 
 127, 225, 43, 168, 
 64, 4, 8, 38, 
 78, 207, 130, 141, 
 82, 17, 32, 3, 
 6, 231, 139, 158, 
 191, 125, 78, 44, 
 244, 156, 249, 56, 
 60, 248, 245, 79, 
 50, 90, 55, 79, 
 129, 244, 211, 91, 
 96, 40, 142, 215, 
 198, 208, 72, 133, 
 117, 231, 21, 125, 
 252, 44, 244, 28, 
 89, 61, 79, 212, 
 235, 249, 117, 122, 
 230, 191, 93, 39, 
 14, 51, 143, 239, 
 76, 63, 59, 125, 
 102, 245, 53, 206, 
 147, 124, 157, 222, 
 181, 2, 
};

const LookupOfLength kmap0_word_len30_anagram1 = {
  481, // seq_bit_len_and_anagram
  27, // num_chords
  kmap0_word_len30_anagram1_chords, // chords
  kmap0_word_len30_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len30_anagram2_chords[] = {
 0, 68, 10, 16, 
 0, 146, 52, 0, 
 128, 48, 1, 16, 
 34, 12, 136, 
};

const uint8_t kmap0_word_len30_anagram2_seqs[] = {
 0, 95, 95, 62, 
 16, 240, 76, 113, 
 230, 243, 36, 143, 
 143, 124, 219, 226, 
 107, 19, 61, 
};

const LookupOfLength kmap0_word_len30_anagram2 = {
  482, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_word_len30_anagram2_chords, // chords
  kmap0_word_len30_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len30_anagram3_chords[] = {
 160, 33, 1, 18, 
 0, 131, 18, 64, 
 19, 
};

const uint8_t kmap0_word_len30_anagram3_seqs[] = {
 71, 228, 27, 238, 
 250, 98, 155, 188, 
 215, 222, 245, 0, 
};

const LookupOfLength kmap0_word_len30_anagram3 = {
  483, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_word_len30_anagram3_chords, // chords
  kmap0_word_len30_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len31_anagram0_chords[] = {
 2, 5, 18, 164, 
 0, 25, 164, 0, 
 73, 52, 0, 145, 
 34, 5, 18, 176, 
 1, 16, 48, 13, 
 24, 0, 45, 19, 
 16, 68, 147, 164, 
 68, 8, 52, 5, 
 144, 18, 4, 138, 
 32, 13, 24, 128, 
 12, 27, 144, 4, 
 9, 146, 4, 25, 
 180, 12, 16, 52, 
 4, 19, 36, 12, 
 16, 52, 68, 144, 
 180, 64, 144, 18, 
 1, 19, 52, 44, 
 18, 2, 36, 19, 
 128, 9, 19, 128, 
 76, 10, 130, 9, 
 26, 144, 0, 139, 
 160, 0, 27, 18, 
 4, 19, 144, 68, 
 19, 48, 69, 129, 
 50, 97, 129, 34, 
 69, 129, 18, 64, 
 83, 50, 73, 16, 
 144, 12, 65, 50, 
 1, 24, 18, 12, 
 65, 18, 12, 138, 
 148, 0, 146, 20, 
 0, 210, 0, 33, 
 72, 130, 37, 72, 
 2, 69, 130, 50, 
 5, 144, 48, 33, 
 17, 48, 5, 25, 
 176, 9, 17, 176, 
 1, 18, 4, 108, 
 16, 18, 36, 65, 
 130, 32, 83, 48, 
 96, 24, 50, 33, 
 26, 182, 8, 16, 
 38, 32, 9, 18, 
 4, 153, 178, 8, 
 136, 146, 4, 17, 
 18, 41, 11, 54, 
 0, 147, 34, 64, 
 128, 18, 13, 65, 
 160, 76, 144, 162, 
 9, 24, 176, 1, 
 154, 148, 9, 16, 
 52, 9, 16, 132, 
 44, 9, 164, 4, 
 144, 54, 8, 16, 
 180, 8, 144, 132, 
 0, 144, 164, 64, 
 19, 182, 72, 16, 
 22, 12, 144, 146, 
 4, 153, 146, 0, 
 81, 18, 0, 83, 
 50, 8, 17, 176, 
 0, 145, 146, 4, 
 90, 20, 4, 81, 
 146, 0, 202, 6, 
 1, 89, 34, 96, 
 192, 34, 76, 65, 
 164, 0, 81, 36, 
 4, 145, 20, 36, 
 19, 144, 4, 153, 
 162, 33, 9, 48, 
 4, 81, 50, 1, 
 17, 34, 0, 147, 
 54, 12, 16, 162, 
 12, 80, 50, 13, 
 128, 50, 13, 24, 
 34, 12, 145, 54, 
 8, 192, 16, 69, 
 146, 16, 96, 19, 
 130, 64, 10, 176, 
 32, 146, 176, 0, 
 18, 182, 8, 0, 
};

const uint8_t kmap0_word_len31_anagram0_seqs[] = {
 224, 143, 105, 124, 
 112, 198, 108, 40, 
 56, 131, 55, 20, 
 156, 121, 201, 3, 
 238, 31, 236, 7, 
 183, 99, 110, 131, 
 219, 147, 94, 65, 
 233, 23, 22, 224, 
 250, 180, 158, 63, 
 95, 101, 232, 211, 
 237, 115, 254, 137, 
 250, 21, 253, 250, 
 247, 124, 122, 253, 
 141, 84, 188, 106, 
 236, 175, 95, 215, 
 211, 49, 95, 235, 
 132, 232, 243, 119, 
 61, 197, 249, 101, 
 255, 231, 164, 151, 
 210, 115, 70, 38, 
 233, 65, 207, 246, 
 81, 32, 252, 116, 
 122, 16, 254, 244, 
 22, 24, 233, 136, 
 89, 140, 148, 94, 
 37, 134, 30, 61, 
 9, 67, 215, 23, 
 139, 145, 117, 167, 
 192, 233, 245, 244, 
 75, 99, 204, 175, 
 165, 143, 207, 180, 
 210, 212, 55, 92, 
 217, 119, 239, 147, 
 108, 198, 241, 90, 
 182, 232, 185, 237, 
 244, 187, 230, 176, 
 222, 173, 246, 152, 
 183, 211, 175, 125, 
 241, 169, 213, 190, 
 168, 20, 99, 95, 
 212, 49, 243, 33, 
 220, 132, 235, 120, 
 134, 29, 122, 208, 
 35, 182, 60, 230, 
 239, 38, 31, 121, 
 22, 122, 110, 171, 
 231, 215, 119, 228, 
 73, 222, 123, 2, 
 61, 5, 252, 178, 
 63, 18, 154, 123, 
 127, 13, 155, 55, 
 166, 128, 89, 229, 
 88, 194, 226, 110, 
 171, 59, 213, 9, 
 209, 173, 176, 207, 
 222, 214, 245, 232, 
 83, 171, 24, 36, 
 186, 215, 243, 27, 
 83, 234, 69, 104, 
 165, 62, 61, 91, 
 80, 151, 201, 45, 
 83, 243, 126, 201, 
 41, 100, 166, 159, 
 20, 163, 173, 119, 
 92, 20, 183, 181, 
 122, 142, 152, 84, 
 61, 71, 78, 174, 
 240, 117, 35, 213, 
 168, 153, 126, 234, 
 56, 117, 78, 117, 
 226, 36, 167, 58, 
 113, 146, 83, 157, 
 144, 25, 183, 78, 
 136, 45, 61, 126, 
 234, 178, 30, 211, 
 111, 135, 142, 185, 
 121, 99, 198, 188, 
 211, 184, 227, 157, 
 182, 232, 137, 76, 
 222, 53, 163, 245, 
 167, 131, 93, 127, 
 126, 205, 77, 141, 
 161, 230, 58, 173, 
 123, 112, 153, 220, 
 12, 121, 95, 118, 
 78, 156, 107, 141, 
 217, 253, 51, 211, 
 207, 66, 207, 215, 
 98, 131, 60, 175, 
 187, 161, 125, 195, 
 221, 241, 115, 30, 
 239, 244, 125, 123, 
 242, 54, 245, 22, 
 226, 167, 218, 99, 
 241, 167, 35, 179, 
 216, 68, 127, 91, 
 108, 245, 253, 35, 
 246, 108, 126, 18, 
 155, 251, 36, 95, 
 77, 199, 143, 175, 
 208, 11, 61, 215, 
 86, 25, 215, 34, 
 178, 224, 113, 17, 
 89, 240, 184, 108, 
 164, 179, 13, 
};

const LookupOfLength kmap0_word_len31_anagram0 = {
  496, // seq_bit_len_and_anagram
  108, // num_chords
  kmap0_word_len31_anagram0_chords, // chords
  kmap0_word_len31_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len31_anagram1_chords[] = {
 16, 64, 74, 48, 
 5, 146, 144, 4, 
 131, 48, 4, 19, 
 130, 76, 8, 20, 
 0, 147, 18, 4, 
 131, 16, 4, 147, 
 146, 0, 11, 18, 
 4, 27, 162, 33, 
 9, 22, 4, 11, 
 54, 1, 8, 52, 
 0, 17, 6, 12, 
 0, 148, 8, 146, 
 16, 36, 82, 148, 
 0, 88, 48, 5, 
 81, 6, 4, 147, 
 48, 13, 9, 34, 
 9, 8, 34, 12, 
 9, 130, 68, 18, 
};

const uint8_t kmap0_word_len31_anagram1_seqs[] = {
 224, 106, 169, 230, 
 39, 242, 220, 197, 
 19, 5, 254, 26, 
 199, 191, 121, 44, 
 251, 83, 168, 244, 
 5, 122, 234, 250, 
 2, 123, 127, 125, 
 177, 243, 184, 173, 
 26, 104, 221, 214, 
 245, 60, 174, 198, 
 194, 214, 187, 254, 
 182, 21, 93, 173, 
 119, 110, 173, 158, 
 205, 115, 214, 46, 
 91, 246, 107, 80, 
 145, 60, 99, 246, 
 15, 194, 49, 215, 
 80, 54, 239, 223, 
 183, 103, 139, 218, 
 248, 36, 190, 238, 
 223, 22, 187, 212, 
 122, 139, 189, 159, 
 90, 175, 63, 211, 
 49, 
};

const LookupOfLength kmap0_word_len31_anagram1 = {
  497, // seq_bit_len_and_anagram
  24, // num_chords
  kmap0_word_len31_anagram1_chords, // chords
  kmap0_word_len31_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len31_anagram2_chords[] = {
 38, 1, 0, 164, 
 4, 146, 36, 9, 
 0, 164, 64, 18, 
 178, 1, 24, 48, 
 5, 146, 54, 8, 
 192, 48, 0, 147, 
 50, 13, 9, 
};

const uint8_t kmap0_word_len31_anagram2_seqs[] = {
 224, 0, 39, 104, 
 32, 240, 24, 39, 
 72, 160, 130, 27, 
 227, 122, 70, 113, 
 196, 184, 111, 189, 
 159, 200, 83, 112, 
 62, 169, 147, 215, 
 23, 155, 199, 98, 
 235, 254, 109, 
};

const LookupOfLength kmap0_word_len31_anagram2 = {
  498, // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_word_len31_anagram2_chords, // chords
  kmap0_word_len31_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len31_anagram3_chords[] = {
 48, 8, 18, 
};

const uint8_t kmap0_word_len31_anagram3_seqs[] = {
 201, 131, 121, 10, 
};

const LookupOfLength kmap0_word_len31_anagram3 = {
  499, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len31_anagram3_chords, // chords
  kmap0_word_len31_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len32_anagram0_chords[] = {
 18, 32, 74, 176, 
 1, 2, 160, 96, 
 72, 160, 13, 24, 
 48, 4, 19, 32, 
 13, 128, 176, 4, 
 10, 52, 4, 17, 
 18, 36, 131, 50, 
 68, 10, 38, 5, 
 24, 52, 13, 137, 
 16, 68, 154, 48, 
 4, 146, 22, 8, 
 11, 148, 4, 194, 
 132, 12, 26, 148, 
 8, 131, 176, 8, 
 90, 146, 64, 90, 
 128, 4, 75, 178, 
 0, 11, 128, 4, 
 91, 130, 4, 147, 
 146, 8, 67, 2, 
 4, 147, 0, 68, 
 2, 146, 64, 74, 
 18, 68, 3, 18, 
 64, 25, 34, 77, 
 16, 18, 76, 17, 
 18, 68, 81, 6, 
 68, 210, 18, 68, 
 75, 38, 64, 81, 
 2, 76, 26, 52, 
 12, 82, 146, 8, 
 72, 180, 8, 136, 
 50, 72, 10, 20, 
 12, 130, 48, 64, 
 130, 22, 4, 138, 
 150, 0, 131, 0, 
 5, 91, 48, 1, 
 154, 50, 33, 17, 
 34, 33, 88, 32, 
 5, 146, 34, 5, 
 136, 32, 69, 144, 
 38, 37, 18, 128, 
 44, 26, 130, 100, 
 146, 18, 64, 11, 
 18, 68, 11, 50, 
 4, 201, 32, 68, 
 154, 38, 4, 146, 
 130, 4, 139, 18, 
 12, 145, 18, 72, 
 10, 34, 8, 8, 
 18, 8, 89, 144, 
 76, 17, 176, 8, 
 130, 146, 12, 9, 
 130, 4, 74, 134, 
 8, 146, 20, 4, 
 144, 54, 8, 18, 
 148, 4, 216, 150, 
 0, 9, 20, 4, 
 201, 52, 4, 208, 
 164, 0, 147, 52, 
 8, 80, 6, 12, 
 18, 164, 13, 16, 
 148, 0, 147, 50, 
 1, 81, 50, 12, 
 145, 48, 12, 153, 
 54, 4, 144, 48, 
 64, 209, 50, 64, 
 144, 2, 5, 83, 
 48, 64, 201, 128, 
 100, 194, 18, 33, 
 80, 22, 1, 82, 
 48, 1, 65, 48, 
 1, 82, 20, 12, 
 129, 18, 12, 153, 
 54, 0, 145, 2, 
 5, 19, 48, 69, 
 19, 38, 40, 17, 
 32, 4, 210, 32, 
 13, 25, 50, 8, 
 83, 162, 8, 19, 
 0, 100, 203, 
};

const uint8_t kmap0_word_len32_anagram0_seqs[] = {
 0, 97, 171, 217, 
 192, 0, 3, 220, 
 0, 102, 201, 161, 
 32, 197, 220, 175, 
 143, 152, 231, 215, 
 159, 158, 238, 79, 
 175, 26, 89, 209, 
 95, 61, 155, 199, 
 191, 144, 188, 141, 
 159, 101, 91, 209, 
 231, 207, 253, 173, 
 39, 189, 150, 188, 
 248, 100, 149, 63, 
 104, 162, 76, 63, 
 216, 219, 101, 173, 
 24, 68, 95, 217, 
 24, 169, 190, 22, 
 24, 169, 146, 215, 
 24, 202, 30, 209, 
 24, 202, 45, 61, 
 24, 202, 251, 186, 
 24, 186, 173, 217, 
 24, 186, 243, 188, 
 24, 179, 141, 79, 
 24, 156, 188, 141, 
 56, 189, 141, 79, 
 18, 60, 64, 128, 
 210, 216, 220, 161, 
 210, 178, 241, 215, 
 210, 42, 167, 215, 
 178, 255, 158, 79, 
 178, 63, 121, 61, 
 178, 249, 121, 61, 
 178, 185, 210, 23, 
 178, 121, 95, 209, 
 178, 121, 243, 156, 
 178, 208, 79, 141, 
 78, 231, 51, 23, 
 78, 205, 220, 161, 
 86, 209, 20, 213, 
 22, 91, 90, 209, 
 190, 248, 84, 201, 
 190, 64, 202, 210, 
 190, 168, 244, 173, 
 190, 168, 20, 189, 
 199, 235, 62, 23, 
 7, 101, 43, 22, 
 199, 184, 111, 184, 
 71, 30, 109, 134, 
 247, 211, 95, 20, 
 247, 235, 77, 253, 
 247, 188, 204, 79, 
 247, 124, 133, 141, 
 240, 39, 133, 22, 
 48, 168, 229, 23, 
 173, 216, 210, 186, 
 173, 178, 241, 215, 
 173, 156, 233, 215, 
 244, 89, 229, 20, 
 212, 231, 252, 20, 
 20, 248, 219, 161, 
 233, 215, 211, 79, 
 201, 178, 177, 213, 
 169, 181, 83, 78, 
 169, 181, 121, 61, 
 41, 164, 231, 215, 
 41, 200, 152, 201, 
 26, 169, 245, 215, 
 129, 248, 220, 161, 
 65, 69, 170, 141, 
 245, 231, 137, 76, 
 213, 131, 110, 209, 
 213, 195, 161, 79, 
 213, 219, 219, 161, 
 149, 252, 252, 186, 
 149, 252, 156, 199, 
 53, 50, 237, 20, 
 117, 204, 30, 209, 
 117, 58, 253, 20, 
 117, 226, 158, 79, 
 117, 66, 192, 184, 
 227, 187, 121, 61, 
 99, 250, 109, 209, 
 99, 178, 248, 186, 
 99, 234, 63, 201, 
 227, 50, 217, 188, 
 227, 50, 185, 199, 
 252, 219, 124, 20, 
 236, 50, 217, 186, 
 12, 159, 40, 174, 
 12, 61, 125, 28, 
 92, 141, 125, 20, 
 156, 239, 219, 188, 
 156, 231, 246, 20, 
 235, 84, 233, 215, 
 235, 73, 173, 79, 
 235, 153, 62, 201, 
 59, 127, 28, 141, 
 59, 127, 91, 22, 
 59, 157, 83, 133, 
 153, 243, 19, 21, 
 226, 223, 243, 186, 
 162, 103, 27, 205, 
 98, 227, 198, 20, 
 215, 103, 21, 188, 
};

const LookupOfLength kmap0_word_len32_anagram0 = {
  512, // seq_bit_len_and_anagram
  105, // num_chords
  kmap0_word_len32_anagram0_chords, // chords
  kmap0_word_len32_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len32_anagram1_chords[] = {
 144, 0, 154, 38, 
 4, 147, 18, 68, 
 11, 180, 64, 82, 
 16, 8, 19, 48, 
 69, 129, 160, 13, 
 144, 32, 13, 16, 
 18, 12, 9, 16, 
 8, 83, 22, 4, 
 147, 180, 8, 19, 
 22, 4, 19, 50, 
 8, 80, 
};

const uint8_t kmap0_word_len32_anagram1_seqs[] = {
 0, 99, 212, 68, 
 127, 54, 245, 22, 
 143, 216, 210, 186, 
 231, 196, 149, 61, 
 232, 228, 245, 20, 
 210, 228, 251, 215, 
 71, 76, 202, 244, 
 247, 124, 74, 63, 
 173, 219, 233, 215, 
 169, 224, 245, 20, 
 245, 103, 27, 201, 
 53, 68, 207, 22, 
 117, 30, 183, 209, 
 156, 71, 108, 209, 
};

const LookupOfLength kmap0_word_len32_anagram1 = {
  513, // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_word_len32_anagram1_chords, // chords
  kmap0_word_len32_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len32_anagram2_chords[] = {
 130, 4, 11, 128, 
 4, 27, 32, 0, 
 146, 16, 12, 81, 
};

const uint8_t kmap0_word_len32_anagram2_seqs[] = {
 216, 251, 219, 161, 
 24, 186, 243, 184, 
 148, 47, 242, 20, 
 233, 119, 199, 204, 
};

const LookupOfLength kmap0_word_len32_anagram2 = {
  514, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_word_len32_anagram2_chords, // chords
  kmap0_word_len32_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len33_anagram0_chords[] = {
 18, 12, 18, 32, 
 5, 65, 2, 68, 
 26, 166, 1, 72, 
 2, 100, 2, 52, 
 96, 18, 146, 8, 
 130, 130, 4, 202, 
 16, 64, 90, 18, 
 76, 2, 162, 4, 
 67, 50, 68, 146, 
 50, 68, 137, 18, 
 4, 155, 162, 4, 
 202, 52, 12, 192, 
 50, 68, 1, 176, 
 12, 1, 148, 8, 
 130, 148, 8, 82, 
 176, 64, 138, 176, 
 1, 90, 178, 8, 
 10, 2, 12, 154, 
 18, 65, 9, 54, 
 64, 82, 22, 64, 
 83, 48, 64, 83, 
 54, 68, 65, 50, 
 65, 64, 146, 64, 
 80, 144, 96, 201, 
 176, 8, 88, 48, 
 12, 129, 18, 0, 
 210, 48, 36, 195, 
 32, 5, 147, 0, 
 69, 18, 52, 5, 
 16, 50, 37, 17, 
 36, 100, 72, 178, 
 12, 9, 34, 0, 
 91, 50, 5, 153, 
 160, 4, 152, 144, 
 13, 16, 2, 12, 
 9, 16, 44, 27, 
 16, 76, 1, 178, 
 8, 81, 178, 1, 
 25, 166, 8, 64, 
 148, 0, 9, 150, 
 0, 65, 22, 68, 
 80, 134, 4, 17, 
 134, 0, 73, 182, 
 0, 82, 38, 12, 
 18, 148, 0, 83, 
 132, 0, 147, 38, 
 32, 192, 48, 5, 
 145, 178, 1, 152, 
 130, 12, 27, 48, 
 96, 194, 50, 12, 
 193, 162, 0, 201, 
 32, 12, 82, 182, 
 0, 80, 132, 8, 
 83, 148, 12, 145, 
 160, 33, 17, 176, 
 33, 17, 16, 5, 
 89, 134, 4, 147, 
 162, 4, 145, 50, 
 12, 129, 50, 8, 
 88, 50, 12, 26, 
 50, 12, 147, 178, 
 12, 129, 162, 96, 
 3, 6, 76, 18, 
 134, 96, 82, 
};

const uint8_t kmap0_word_len33_anagram0_seqs[] = {
 224, 147, 167, 241, 
 193, 231, 59, 243, 
 2, 249, 115, 109, 
 5, 119, 159, 28, 
 10, 224, 95, 191, 
 27, 64, 159, 227, 
 43, 72, 190, 104, 
 12, 160, 141, 65, 
 207, 128, 11, 169, 
 46, 30, 95, 58, 
 53, 62, 70, 230, 
 109, 124, 44, 147, 
 123, 252, 186, 93, 
 38, 251, 245, 162, 
 189, 197, 235, 69, 
 71, 230, 103, 118, 
 58, 201, 191, 219, 
 155, 165, 63, 111, 
 164, 95, 99, 164, 
 74, 190, 192, 72, 
 117, 204, 140, 161, 
 72, 89, 26, 67, 
 239, 49, 51, 134, 
 138, 173, 104, 156, 
 78, 173, 79, 210, 
 71, 107, 175, 165, 
 25, 167, 79, 75, 
 51, 78, 215, 149, 
 230, 157, 140, 43, 
 251, 79, 175, 89, 
 246, 113, 100, 182, 
 108, 142, 145, 30, 
 25, 102, 21, 188, 
 214, 152, 20, 153, 
 45, 62, 229, 95, 
 251, 194, 131, 205, 
 246, 5, 252, 204, 
 123, 60, 102, 218, 
 226, 248, 121, 249, 
 197, 253, 115, 254, 
 109, 232, 233, 253, 
 219, 48, 243, 249, 
 42, 91, 53, 196, 
 95, 183, 242, 78, 
 198, 109, 93, 223, 
 243, 36, 16, 121, 
 244, 169, 244, 243, 
 81, 114, 250, 214, 
 253, 214, 228, 65, 
 248, 186, 201, 251, 
 242, 247, 83, 52, 
 111, 30, 107, 239, 
 196, 109, 141, 83, 
 236, 200, 28, 181, 
 134, 90, 55, 106, 
 13, 238, 117, 253, 
 121, 217, 236, 26, 
 179, 243, 189, 53, 
 184, 183, 67, 235, 
 24, 59, 50, 215, 
 105, 241, 177, 168, 
 19, 92, 141, 91, 
 39, 54, 48, 168, 
 230, 147, 154, 225, 
 248, 206, 244, 235, 
 49, 245, 221, 161, 
 19, 233, 117, 27, 
 25, 161, 101, 38, 
 115, 167, 76, 191, 
 230, 160, 188, 29, 
 202, 57, 165, 159, 
 130, 115, 245, 116, 
 12, 23, 169, 110, 
 164, 117, 170, 49, 
 79, 11, 39, 242, 
 13, 55, 110, 47, 
 244, 236, 188, 242, 
 225, 217, 137, 218, 
 248, 180, 121, 99, 
 250, 41, 211, 118, 
 250, 117, 214, 22, 
 61, 108, 241, 167, 
 95, 209, 162, 103, 
 27, 159, 196, 160, 
 223, 38, 95, 123, 
 97, 228, 189, 118, 
 217, 31, 121, 141, 
 97, 216, 21, 
};

const LookupOfLength kmap0_word_len33_anagram0 = {
  528, // seq_bit_len_and_anagram
  85, // num_chords
  kmap0_word_len33_anagram0_chords, // chords
  kmap0_word_len33_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len33_anagram1_chords[] = {
 164, 4, 146, 52, 
 4, 193, 48, 44, 
 18, 50, 12, 3, 
 22, 4, 80, 18, 
 44, 130, 34, 4, 
 146, 18, 1, 9, 
 50, 12, 153, 18, 
 44, 10, 22, 0, 
 19, 52, 8, 16, 
 160, 33, 1, 50, 
 5, 153, 
};

const uint8_t kmap0_word_len33_anagram1_seqs[] = {
 224, 252, 130, 98, 
 192, 233, 95, 50, 
 3, 248, 35, 186, 
 120, 220, 22, 127, 
 253, 181, 206, 55, 
 27, 161, 83, 227, 
 19, 246, 96, 166, 
 159, 214, 163, 181, 
 215, 173, 235, 17, 
 159, 146, 17, 190, 
 54, 214, 49, 118, 
 237, 29, 39, 167, 
 211, 179, 48, 242, 
 13, 119, 167, 95, 
 111, 50, 
};

const LookupOfLength kmap0_word_len33_anagram1 = {
  529, // seq_bit_len_and_anagram
  14, // num_chords
  kmap0_word_len33_anagram1_chords, // chords
  kmap0_word_len33_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len33_anagram2_chords[] = {
 144, 8, 26, 48, 
 69, 24, 
};

const uint8_t kmap0_word_len33_anagram2_seqs[] = {
 232, 113, 10, 45, 
 172, 242, 245, 246, 
 0, 
};

const LookupOfLength kmap0_word_len33_anagram2 = {
  530, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len33_anagram2_chords, // chords
  kmap0_word_len33_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len33_anagram3_chords[] = {
 20, 4, 25, 
};

const uint8_t kmap0_word_len33_anagram3_seqs[] = {
 95, 235, 143, 117, 
 1, 
};

const LookupOfLength kmap0_word_len33_anagram3 = {
  531, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len33_anagram3_chords, // chords
  kmap0_word_len33_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len34_anagram0_chords[] = {
 0, 69, 128, 128, 
 68, 152, 148, 32, 
 208, 34, 0, 217, 
 18, 44, 130, 180, 
 0, 19, 132, 65, 
 16, 180, 4, 193, 
 36, 4, 83, 34, 
 12, 67, 130, 68, 
 9, 176, 76, 3, 
 16, 5, 25, 16, 
 4, 153, 2, 4, 
 218, 20, 12, 154, 
 166, 1, 146, 164, 
 33, 17, 54, 0, 
 72, 144, 32, 26, 
 134, 12, 138, 180, 
 8, 19, 130, 1, 
 139, 176, 9, 26, 
 144, 4, 147, 176, 
 0, 83, 18, 64, 
 154, 162, 64, 75, 
 178, 72, 82, 176, 
 72, 11, 150, 76, 
 8, 144, 64, 147, 
 144, 64, 17, 22, 
 44, 64, 22, 0, 
 210, 18, 4, 201, 
 182, 36, 16, 54, 
 32, 131, 146, 0, 
 147, 16, 4, 155, 
 128, 69, 18, 130, 
 5, 27, 34, 13, 
 19, 6, 36, 74, 
 134, 40, 24, 182, 
 32, 144, 134, 36, 
 193, 18, 64, 27, 
 176, 0, 154, 162, 
 1, 195, 128, 44, 
 25, 50, 13, 16, 
 52, 12, 24, 176, 
 76, 129, 178, 12, 
 1, 162, 12, 9, 
 176, 8, 9, 134, 
 12, 128, 54, 8, 
 129, 50, 13, 9, 
 180, 4, 129, 182, 
 8, 65, 182, 0, 
 192, 52, 5, 25, 
 180, 1, 80, 132, 
 4, 208, 52, 36, 
 82, 16, 1, 26, 
 18, 4, 193, 50, 
 0, 83, 20, 96, 
 80, 22, 1, 66, 
 52, 8, 83, 0, 
 68, 89, 48, 33, 
 89, 34, 12, 81, 
 34, 12, 9, 144, 
 4, 155, 162, 12, 
 11, 
};

const uint8_t kmap0_word_len34_anagram0_seqs[] = {
 224, 0, 15, 202, 
 0, 129, 24, 249, 
 10, 4, 130, 93, 
 33, 16, 200, 188, 
 173, 32, 53, 194, 
 55, 129, 192, 141, 
 211, 3, 234, 196, 
 33, 244, 159, 28, 
 148, 215, 127, 242, 
 206, 227, 62, 110, 
 139, 205, 251, 82, 
 246, 118, 232, 75, 
 49, 240, 215, 127, 
 28, 30, 235, 62, 
 173, 71, 127, 253, 
 250, 84, 112, 243, 
 235, 83, 81, 214, 
 103, 7, 197, 93, 
 156, 19, 249, 134, 
 123, 102, 110, 53, 
 51, 6, 244, 88, 
 209, 24, 169, 210, 
 183, 98, 164, 154, 
 215, 131, 161, 7, 
 53, 46, 134, 138, 
 158, 219, 24, 51, 
 166, 95, 99, 228, 
 89, 115, 129, 5, 
 181, 74, 143, 108, 
 198, 200, 186, 178, 
 25, 67, 244, 200, 
 192, 156, 172, 43, 
 163, 126, 106, 181, 
 201, 184, 19, 210, 
 38, 227, 78, 72, 
 59, 85, 248, 220, 
 236, 218, 228, 202, 
 133, 153, 173, 219, 
 79, 206, 21, 198, 
 244, 251, 2, 246, 
 217, 235, 139, 245, 
 116, 140, 47, 214, 
 163, 79, 71, 204, 
 245, 71, 30, 243, 
 184, 29, 122, 207, 
 139, 189, 5, 108, 
 174, 175, 141, 48, 
 166, 203, 134, 194, 
 152, 233, 147, 12, 
 131, 107, 239, 83, 
 75, 235, 246, 22, 
 2, 145, 71, 93, 
 80, 220, 205, 219, 
 152, 126, 126, 97, 
 104, 250, 153, 254, 
 219, 201, 233, 156, 
 87, 167, 144, 153, 
 126, 157, 98, 91, 
 252, 117, 138, 172, 
 251, 173, 41, 68, 
 39, 235, 166, 40, 
 219, 68, 159, 50, 
 109, 87, 178, 250, 
 254, 109, 209, 53, 
 106, 166, 95, 215, 
 224, 222, 22, 93, 
 131, 185, 79, 114, 
 29, 223, 250, 186, 
 117, 226, 30, 51, 
 215, 137, 26, 252, 
 84, 243, 32, 124, 
 246, 248, 240, 88, 
 209, 252, 107, 162, 
 94, 179, 49, 79, 
 111, 193, 208, 21, 
 122, 36, 87, 99, 
 31, 141, 92, 141, 
 59, 57, 241, 190, 
 202, 31, 201, 59, 
 214, 123, 33, 239, 
 244, 111, 78, 219, 
 251, 218, 57, 109, 
 144, 231, 21, 45, 
 62, 254, 118, 40, 
};

const LookupOfLength kmap0_word_len34_anagram0 = {
  544, // seq_bit_len_and_anagram
  79, // num_chords
  kmap0_word_len34_anagram0_chords, // chords
  kmap0_word_len34_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len34_anagram1_chords[] = {
 134, 0, 72, 2, 
 5, 19, 54, 12, 
 16, 0, 4, 211, 
 128, 4, 27, 54, 
 1, 128, 18, 4, 
 25, 130, 1, 27, 
 20, 0, 89, 
};

const uint8_t kmap0_word_len34_anagram1_seqs[] = {
 160, 70, 51, 135, 
 254, 108, 31, 143, 
 123, 118, 217, 159, 
 49, 254, 62, 21, 
 188, 24, 186, 243, 
 83, 152, 250, 238, 
 147, 108, 93, 207, 
 126, 235, 49, 141, 
 219, 161, 227, 58, 
 102, 235, 2, 
};

const LookupOfLength kmap0_word_len34_anagram1 = {
  545, // seq_bit_len_and_anagram
  9, // num_chords
  kmap0_word_len34_anagram1_chords, // chords
  kmap0_word_len34_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len34_anagram2_chords[] = {
 48, 5, 128, 
};

const uint8_t kmap0_word_len34_anagram2_seqs[] = {
 148, 239, 251, 111, 
 3, 
};

const LookupOfLength kmap0_word_len34_anagram2 = {
  546, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len34_anagram2_chords, // chords
  kmap0_word_len34_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len34_anagram4_chords[] = {
 20, 4, 25, 
};

const uint8_t kmap0_word_len34_anagram4_seqs[] = {
 213, 234, 157, 95, 
 3, 
};

const LookupOfLength kmap0_word_len34_anagram4 = {
  548, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len34_anagram4_chords, // chords
  kmap0_word_len34_anagram4_seqs, // sequences
};

const uint8_t kmap0_word_len35_anagram0_chords[] = {
 132, 12, 8, 48, 
 69, 136, 160, 32, 
 73, 36, 40, 18, 
 2, 100, 18, 176, 
 8, 25, 32, 4, 
 18, 52, 36, 129, 
 132, 36, 18, 48, 
 13, 25, 146, 4, 
 67, 146, 4, 9, 
 48, 4, 9, 180, 
 68, 144, 6, 4, 
 19, 176, 5, 19, 
 52, 4, 147, 134, 
 44, 10, 148, 4, 
 19, 16, 72, 27, 
 20, 68, 81, 18, 
 72, 25, 162, 72, 
 72, 18, 12, 137, 
 50, 64, 154, 2, 
 13, 144, 178, 13, 
 17, 50, 13, 193, 
 146, 1, 146, 162, 
 5, 9, 162, 1, 
 11, 48, 69, 17, 
 18, 8, 27, 22, 
 0, 25, 182, 5, 
 129, 130, 68, 26, 
 162, 13, 88, 146, 
 4, 195, 166, 12, 
 136, 148, 0, 216, 
 38, 12, 137, 182, 
 8, 80, 134, 0, 
 19, 148, 0, 19, 
 52, 68, 136, 52, 
 8, 128, 22, 0, 
 27, 54, 4, 146, 
 22, 4, 147, 54, 
 0, 210, 48, 64, 
 202, 34, 8, 193, 
 34, 37, 81, 48, 
 5, 83, 34, 5, 
 210, 144, 72, 90, 
 134, 0, 90, 32, 
 44, 193, 18, 4, 
 89, 16, 4, 217, 
 54, 12, 144, 32, 
 12, 210, 178, 8, 
 147, 
};

const uint8_t kmap0_word_len35_anagram0_seqs[] = {
 224, 211, 151, 13, 
 5, 214, 155, 94, 
 37, 128, 145, 121, 
 67, 65, 202, 83, 
 97, 1, 166, 17, 
 254, 72, 32, 122, 
 82, 232, 62, 98, 
 158, 199, 226, 169, 
 194, 63, 189, 95, 
 235, 196, 35, 252, 
 185, 115, 178, 238, 
 51, 7, 246, 175, 
 127, 215, 186, 29, 
 250, 187, 214, 252, 
 235, 243, 39, 202, 
 100, 227, 215, 199, 
 222, 2, 127, 125, 
 199, 20, 104, 242, 
 57, 191, 70, 248, 
 169, 118, 40, 70, 
 84, 207, 175, 165, 
 113, 156, 172, 43, 
 205, 213, 243, 107, 
 233, 245, 164, 86, 
 203, 22, 155, 59, 
 212, 212, 169, 245, 
 215, 214, 50, 185, 
 167, 56, 62, 53, 
 245, 207, 241, 98, 
 76, 175, 15, 243, 
 182, 248, 116, 244, 
 248, 136, 139, 35, 
 178, 238, 183, 30, 
 89, 113, 59, 244, 
 158, 151, 249, 215, 
 173, 56, 78, 214, 
 109, 93, 79, 29, 
 111, 156, 212, 247, 
 175, 99, 100, 235, 
 79, 17, 115, 191, 
 54, 167, 96, 108, 
 162, 95, 215, 23, 
 155, 58, 180, 122, 
 56, 84, 77, 149, 
 126, 91, 115, 170, 
 99, 177, 35, 115, 
 157, 142, 233, 45, 
 234, 68, 245, 108, 
 81, 179, 180, 202, 
 167, 154, 203, 150, 
 37, 143, 177, 107, 
 91, 119, 76, 253, 
 39, 21, 227, 74, 
 141, 191, 102, 156, 
 62, 79, 50, 187, 
 76, 182, 162, 121, 
 59, 101, 202, 204, 
 59, 223, 55, 92, 
 222, 249, 245, 93, 
 112, 158, 187, 241, 
 137, 11, 149, 19, 
 201, 92, 104, 84, 
 110, 94, 248, 244, 
 41, 243, 206, 43, 
 183, 117, 119, 94, 
 153, 126, 45, 254, 
 244, 159, 100, 241, 
 25, 51, 253, 136, 
 166, 192, 222, 2, 
};

const LookupOfLength kmap0_word_len35_anagram0 = {
  560, // seq_bit_len_and_anagram
  63, // num_chords
  kmap0_word_len35_anagram0_chords, // chords
  kmap0_word_len35_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len35_anagram1_chords[] = {
 50, 12, 9, 52, 
 13, 16, 52, 72, 
 0, 146, 4, 25, 
 2, 12, 147, 176, 
 8, 9, 50, 13, 
 9, 18, 4, 89, 
 36, 4, 83, 180, 
 64, 64, 
};

const uint8_t kmap0_word_len35_anagram1_seqs[] = {
 64, 108, 175, 126, 
 58, 45, 122, 254, 
 182, 211, 105, 41, 
 45, 123, 61, 191, 
 29, 154, 154, 122, 
 127, 138, 20, 201, 
 186, 57, 233, 139, 
 125, 255, 122, 204, 
 205, 251, 186, 156, 
 207, 157, 199, 229, 
 92, 107, 176, 37, 
};

const LookupOfLength kmap0_word_len35_anagram1 = {
  561, // seq_bit_len_and_anagram
  10, // num_chords
  kmap0_word_len35_anagram1_chords, // chords
  kmap0_word_len35_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len35_anagram2_chords[] = {
 146, 0, 11, 
};

const uint8_t kmap0_word_len35_anagram2_seqs[] = {
 24, 186, 173, 214, 
 5, 
};

const LookupOfLength kmap0_word_len35_anagram2 = {
  562, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len35_anagram2_chords, // chords
  kmap0_word_len35_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len36_anagram0_chords[] = {
 162, 37, 2, 18, 
 41, 10, 130, 69, 
 144, 54, 5, 144, 
 178, 5, 16, 18, 
 4, 210, 128, 32, 
 154, 0, 4, 72, 
 128, 4, 9, 128, 
 65, 146, 6, 5, 
 2, 34, 12, 19, 
 16, 68, 155, 34, 
 12, 136, 164, 12, 
 144, 18, 36, 19, 
 182, 44, 16, 48, 
 4, 131, 38, 13, 
 10, 130, 4, 138, 
 16, 36, 19, 144, 
 36, 131, 50, 5, 
 19, 2, 5, 210, 
 164, 72, 10, 160, 
 65, 10, 48, 101, 
 17, 20, 64, 9, 
 22, 0, 131, 160, 
 5, 210, 176, 1, 
 80, 18, 65, 27, 
 34, 64, 91, 34, 
 64, 154, 50, 0, 
 73, 50, 5, 25, 
 130, 77, 136, 48, 
 9, 88, 16, 4, 
 90, 178, 5, 9, 
 182, 33, 24, 130, 
 5, 130, 144, 36, 
 83, 38, 76, 128, 
 20, 12, 17, 20, 
 12, 25, 6, 36, 
 210, 132, 13, 145, 
 150, 4, 154, 150, 
 0, 81, 150, 4, 
 137, 22, 64, 89, 
 34, 68, 147, 48, 
 5, 155, 178, 0, 
 90, 178, 8, 80, 
 50, 8, 73, 52, 
 72, 192, 48, 1, 
 209, 18, 36, 139, 
 128, 72, 19, 
};

const uint8_t kmap0_word_len36_anagram0_seqs[] = {
 0, 97, 227, 223, 
 1, 16, 54, 150, 
 172, 224, 160, 152, 
 150, 15, 238, 63, 
 167, 77, 224, 118, 
 204, 221, 15, 4, 
 204, 220, 248, 64, 
 32, 160, 106, 1, 
 20, 60, 96, 240, 
 64, 193, 131, 5, 
 1, 226, 226, 136, 
 145, 160, 62, 246, 
 209, 248, 184, 45, 
 246, 22, 47, 5, 
 30, 173, 251, 148, 
 83, 107, 78, 95, 
 235, 132, 248, 244, 
 131, 176, 215, 184, 
 167, 225, 139, 29, 
 131, 79, 152, 233, 
 215, 248, 169, 126, 
 223, 138, 175, 161, 
 141, 79, 8, 127, 
 30, 215, 131, 48, 
 48, 232, 215, 216, 
 247, 143, 119, 141, 
 244, 204, 125, 20, 
 24, 169, 70, 86, 
 137, 161, 71, 100, 
 149, 242, 243, 13, 
 215, 35, 93, 173, 
 210, 186, 190, 168, 
 212, 216, 123, 83, 
 48, 255, 20, 119, 
 204, 237, 200, 220, 
 210, 186, 125, 20, 
 173, 50, 243, 78, 
 209, 90, 38, 247, 
 20, 173, 188, 189, 
 121, 221, 186, 190, 
 231, 215, 233, 181, 
 143, 32, 153, 204, 
 108, 189, 61, 106, 
 52, 243, 79, 161, 
 190, 99, 251, 215, 
 234, 190, 225, 25, 
 19, 199, 209, 216, 
 79, 49, 8, 205, 
 59, 95, 159, 168, 
 101, 78, 245, 231, 
 147, 215, 83, 61, 
 233, 213, 186, 21, 
 22, 220, 248, 84, 
 233, 247, 136, 73, 
 53, 6, 77, 223, 
 90, 131, 215, 211, 
 49, 53, 214, 186, 
 253, 84, 199, 220, 
 210, 186, 101, 242, 
 83, 111, 49, 198, 
 125, 189, 201, 99, 
 204, 195, 29, 58, 
 102, 143, 24, 61, 
 108, 229, 222, 22, 
 205, 101, 178, 93, 
 214, 188, 147, 239, 
 155, 188, 70, 168, 
 141, 79, 27, 41, 
 102, 226, 10, 
};

const LookupOfLength kmap0_word_len36_anagram0 = {
  576, // seq_bit_len_and_anagram
  61, // num_chords
  kmap0_word_len36_anagram0_chords, // chords
  kmap0_word_len36_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len36_anagram1_chords[] = {
 130, 0, 202, 148, 
 8, 11, 148, 4, 
 19, 2, 5, 147, 
 48, 5, 145, 16, 
 4, 83, 2, 4, 
 67, 
};

const uint8_t kmap0_word_len36_anagram1_seqs[] = {
 24, 68, 205, 29, 
 138, 145, 170, 215, 
 186, 24, 83, 99, 
 126, 125, 60, 54, 
 245, 22, 247, 252, 
 250, 200, 196, 198, 
 241, 254, 20, 188, 
 191, 205, 219, 8, 
};

const LookupOfLength kmap0_word_len36_anagram1 = {
  577, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_word_len36_anagram1_chords, // chords
  kmap0_word_len36_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len36_anagram2_chords[] = {
 48, 5, 136, 
};

const uint8_t kmap0_word_len36_anagram2_seqs[] = {
 244, 122, 231, 191, 
 13, 
};

const LookupOfLength kmap0_word_len36_anagram2 = {
  578, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len36_anagram2_chords, // chords
  kmap0_word_len36_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len37_anagram0_chords[] = {
 18, 12, 26, 160, 
 69, 192, 48, 13, 
 26, 32, 108, 16, 
 144, 12, 73, 16, 
 108, 3, 128, 64, 
 1, 2, 76, 130, 
 144, 4, 82, 48, 
 68, 129, 50, 76, 
 81, 160, 37, 129, 
 50, 36, 11, 54, 
 4, 147, 134, 4, 
 19, 16, 100, 147, 
 48, 37, 138, 2, 
 36, 91, 176, 5, 
 130, 148, 8, 11, 
 130, 64, 11, 162, 
 0, 74, 160, 0, 
 91, 2, 8, 83, 
 178, 64, 194, 50, 
 69, 73, 146, 72, 
 72, 18, 5, 18, 
 22, 12, 146, 178, 
 68, 137, 18, 5, 
 75, 22, 36, 65, 
 50, 36, 26, 18, 
 76, 1, 22, 8, 
 137, 50, 1, 138, 
 54, 0, 25, 178, 
 64, 27, 162, 0, 
 155, 34, 1, 211, 
 50, 8, 152, 38, 
 8, 147, 50, 12, 
 25, 52, 5, 88, 
 22, 68, 19, 54, 
 4, 200, 180, 8, 
 145, 4, 44, 18, 
 166, 0, 210, 6, 
 4, 147, 150, 8, 
 25, 178, 64, 201, 
 144, 72, 26, 18, 
 5, 82, 2, 100, 
 74, 20, 12, 66, 
 2, 8, 65, 48, 
 0, 83, 146, 0, 
 19, 22, 36, 81, 
 130, 68, 25, 176, 
 8, 153, 0, 68, 
 27, 
};

const uint8_t kmap0_word_len37_anagram0_seqs[] = {
 224, 147, 167, 241, 
 21, 200, 200, 55, 
 61, 131, 219, 147, 
 94, 11, 0, 127, 
 196, 31, 9, 210, 
 239, 154, 67, 65, 
 250, 93, 232, 43, 
 88, 16, 64, 130, 
 0, 215, 38, 234, 
 79, 143, 104, 230, 
 152, 226, 165, 203, 
 228, 95, 191, 20, 
 61, 219, 236, 167, 
 133, 145, 111, 248, 
 121, 161, 117, 27, 
 241, 169, 207, 249, 
 53, 126, 125, 236, 
 141, 193, 95, 104, 
 57, 79, 8, 159, 
 200, 122, 27, 225, 
 52, 111, 191, 98, 
 16, 249, 239, 108, 
 140, 84, 67, 173, 
 139, 161, 178, 183, 
 67, 49, 148, 177, 
 35, 51, 134, 242, 
 78, 198, 197, 233, 
 109, 108, 78, 210, 
 212, 216, 145, 89, 
 154, 251, 214, 95, 
 203, 78, 86, 238, 
 80, 31, 71, 227, 
 99, 225, 84, 123, 
 26, 159, 92, 38, 
 255, 118, 232, 241, 
 140, 173, 191, 134, 
 174, 191, 189, 205, 
 48, 207, 52, 190, 
 186, 83, 178, 236, 
 95, 119, 170, 228, 
 100, 221, 214, 131, 
 178, 21, 221, 186, 
 158, 201, 117, 91, 
 119, 66, 102, 180, 
 64, 86, 220, 14, 
 21, 200, 188, 125, 
 20, 2, 89, 180, 
 54, 57, 101, 218, 
 174, 84, 232, 207, 
 252, 182, 232, 250, 
 204, 214, 219, 83, 
 45, 251, 119, 26, 
 171, 181, 149, 51, 
 125, 245, 78, 144, 
 115, 170, 240, 39, 
 61, 22, 53, 152, 
 251, 164, 162, 206, 
 227, 54, 62, 213, 
 137, 212, 106, 221, 
 50, 217, 188, 29, 
 58, 198, 72, 201, 
 42, 249, 113, 250, 
 104, 52, 191, 202, 
 107, 35, 228, 250, 
 232, 244, 200, 188, 
 157, 50, 253, 154, 
 119, 50, 110, 30, 
 175, 103, 122, 99, 
 138, 133, 158, 175, 
 205, 187, 243, 178, 
 183, 67, 197, 160, 
 172, 107, 207, 245, 
 103, 94, 183, 0, 
};

const LookupOfLength kmap0_word_len37_anagram0 = {
  592, // seq_bit_len_and_anagram
  63, // num_chords
  kmap0_word_len37_anagram0_chords, // chords
  kmap0_word_len37_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len37_anagram1_chords[] = {
 18, 12, 138, 22, 
 4, 138, 16, 0, 
 139, 48, 37, 138, 
 48, 5, 25, 22, 
 0, 154, 180, 64, 
 18, 52, 4, 208, 
};

const uint8_t kmap0_word_len37_anagram1_seqs[] = {
 32, 249, 162, 241, 
 245, 107, 165, 126, 
 69, 251, 2, 77, 
 100, 93, 95, 32, 
 124, 189, 125, 231, 
 159, 215, 181, 235, 
 180, 98, 87, 114, 
 157, 64, 203, 60, 
 102, 215, 159, 63, 
 201, 
};

const LookupOfLength kmap0_word_len37_anagram1 = {
  593, // seq_bit_len_and_anagram
  8, // num_chords
  kmap0_word_len37_anagram1_chords, // chords
  kmap0_word_len37_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len37_anagram2_chords[] = {
 18, 68, 11, 
};

const uint8_t kmap0_word_len37_anagram2_seqs[] = {
 248, 42, 91, 254, 
 26, 
};

const LookupOfLength kmap0_word_len37_anagram2 = {
  594, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len37_anagram2_chords, // chords
  kmap0_word_len37_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len38_anagram0_chords[] = {
 128, 68, 146, 52, 
 72, 18, 128, 1, 
 64, 130, 36, 88, 
 34, 41, 81, 130, 
 76, 72, 48, 76, 
 25, 22, 68, 138, 
 54, 4, 17, 162, 
 12, 3, 0, 77, 
 18, 38, 4, 153, 
 2, 44, 83, 134, 
 12, 10, 146, 65, 
 11, 146, 64, 19, 
 54, 68, 131, 18, 
 1, 11, 146, 0, 
 155, 48, 9, 26, 
 54, 36, 193, 146, 
 0, 203, 164, 5, 
 192, 2, 5, 75, 
 54, 1, 130, 18, 
 37, 90, 48, 65, 
 153, 48, 5, 81, 
 144, 100, 138, 160, 
 36, 195, 134, 12, 
 25, 2, 44, 75, 
 162, 12, 194, 18, 
 12, 27, 18, 44, 
 74, 182, 13, 24, 
 6, 4, 154, 148, 
 1, 80, 164, 1, 
 17, 134, 12, 146, 
 50, 5, 89, 52, 
 4, 75, 18, 32, 
 91, 48, 36, 81, 
 144, 96, 209, 
};

const uint8_t kmap0_word_len38_anagram0_seqs[] = {
 0, 131, 98, 94, 
 6, 144, 70, 167, 
 211, 3, 14, 16, 
 128, 1, 3, 248, 
 51, 205, 161, 96, 
 243, 148, 154, 225, 
 203, 212, 204, 29, 
 250, 82, 180, 110, 
 30, 127, 173, 86, 
 217, 23, 191, 59, 
 125, 230, 245, 231, 
 141, 244, 219, 248, 
 215, 210, 245, 71, 
 158, 211, 68, 253, 
 186, 8, 167, 121, 
 211, 51, 70, 170, 
 175, 29, 138, 161, 
 71, 75, 235, 202, 
 30, 227, 198, 20, 
 50, 87, 106, 252, 
 181, 143, 163, 177, 
 173, 107, 50, 238, 
 132, 54, 58, 121, 
 110, 43, 22, 230, 
 253, 147, 154, 161, 
 47, 214, 202, 29, 
 122, 252, 153, 41, 
 50, 31, 175, 251, 
 188, 141, 7, 249, 
 162, 79, 242, 49, 
 175, 8, 155, 125, 
 140, 203, 100, 235, 
 30, 147, 121, 231, 
 215, 240, 137, 226, 
 106, 43, 12, 10, 
 252, 204, 219, 169, 
 198, 236, 235, 166, 
 71, 216, 218, 188, 
 233, 169, 177, 35, 
 115, 250, 245, 104, 
 111, 145, 140, 240, 
 181, 57, 197, 220, 
 175, 93, 214, 117, 
 90, 177, 235, 83, 
 157, 56, 204, 28, 
 83, 39, 54, 206, 
 124, 212, 137, 139, 
 78, 79, 220, 183, 
 254, 230, 49, 231, 
 147, 247, 21, 205, 
 133, 46, 244, 54, 
 46, 52, 127, 158, 
 204, 11, 199, 12, 
 131, 36, 
};

const LookupOfLength kmap0_word_len38_anagram0 = {
  608, // seq_bit_len_and_anagram
  45, // num_chords
  kmap0_word_len38_anagram0_chords, // chords
  kmap0_word_len38_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len38_anagram1_chords[] = {
 54, 0, 147, 22, 
 0, 89, 178, 8, 
 137, 18, 32, 91, 
};

const uint8_t kmap0_word_len38_anagram1_seqs[] = {
 104, 242, 57, 189, 
 133, 117, 61, 117, 
 154, 109, 49, 40, 
 111, 135, 114, 161, 
 11, 205, 205, 
};

const LookupOfLength kmap0_word_len38_anagram1 = {
  609, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_word_len38_anagram1_chords, // chords
  kmap0_word_len38_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len38_anagram2_chords[] = {
 50, 8, 9, 
};

const uint8_t kmap0_word_len38_anagram2_seqs[] = {
 173, 155, 123, 91, 
 52, 
};

const LookupOfLength kmap0_word_len38_anagram2 = {
  610, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len38_anagram2_chords, // chords
  kmap0_word_len38_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len39_anagram0_chords[] = {
 166, 1, 0, 36, 
 1, 72, 4, 72, 
 64, 32, 8, 144, 
 182, 8, 24, 18, 
 5, 129, 22, 13, 
 144, 54, 76, 129, 
 36, 4, 81, 128, 
 12, 91, 54, 12, 
 128, 18, 40, 83, 
 178, 9, 11, 144, 
 1, 26, 162, 1, 
 74, 144, 76, 18, 
 162, 69, 72, 18, 
 65, 25, 2, 65, 
 0, 4, 65, 130, 
 54, 5, 19, 178, 
 13, 81, 18, 36, 
 18, 50, 4, 145, 
 38, 8, 131, 148, 
 36, 91, 22, 0, 
 89, 20, 1, 26, 
 54, 9, 144, 164, 
 4, 146, 132, 4, 
 16, 2, 12, 210, 
 4, 44, 83, 132, 
 40, 90, 148, 12, 
 19, 52, 13, 129, 
};

const uint8_t kmap0_word_len39_anagram0_seqs[] = {
 224, 6, 21, 52, 
 8, 160, 128, 193, 
 13, 42, 168, 64, 
 130, 4, 24, 136, 
 96, 64, 2, 4, 
 68, 79, 151, 13, 
 253, 227, 104, 234, 
 95, 127, 170, 212, 
 71, 123, 62, 85, 
 234, 205, 210, 95, 
 235, 207, 111, 230, 
 231, 157, 208, 72, 
 197, 139, 223, 244, 
 39, 25, 161, 83, 
 243, 78, 129, 113, 
 107, 111, 139, 198, 
 208, 195, 99, 69, 
 99, 232, 145, 185, 
 67, 165, 83, 224, 
 60, 22, 178, 255, 
 214, 224, 102, 217, 
 199, 225, 177, 174, 
 236, 227, 240, 88, 
 87, 18, 168, 224, 
 0, 120, 252, 57, 
 141, 191, 62, 94, 
 140, 233, 53, 195, 
 246, 252, 32, 44, 
 168, 215, 243, 155, 
 199, 41, 211, 118, 
 165, 198, 250, 186, 
 5, 12, 118, 245, 
 112, 243, 90, 183, 
 142, 15, 143, 21, 
 93, 167, 197, 38, 
 223, 174, 19, 231, 
 159, 84, 212, 137, 
 243, 79, 42, 184, 
 83, 211, 15, 21, 
 92, 164, 250, 11, 
 11, 46, 82, 133, 
 161, 197, 58, 213, 
 152, 159, 66, 244, 
 237, 253, 147, 12, 
};

const LookupOfLength kmap0_word_len39_anagram0 = {
  624, // seq_bit_len_and_anagram
  36, // num_chords
  kmap0_word_len39_anagram0_chords, // chords
  kmap0_word_len39_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len39_anagram1_chords[] = {
 146, 0, 75, 48, 
 5, 26, 50, 1, 
 25, 16, 68, 83, 
};

const uint8_t kmap0_word_len39_anagram1_seqs[] = {
 24, 202, 205, 107, 
 221, 99, 254, 158, 
 87, 244, 145, 71, 
 123, 243, 184, 48, 
 175, 71, 126, 1, 
};

const LookupOfLength kmap0_word_len39_anagram1 = {
  625, // seq_bit_len_and_anagram
  4, // num_chords
  kmap0_word_len39_anagram1_chords, // chords
  kmap0_word_len39_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len40_anagram0_chords[] = {
 32, 45, 8, 32, 
 4, 154, 20, 4, 
 216, 36, 1, 129, 
 180, 8, 24, 128, 
 69, 89, 48, 77, 
 9, 162, 45, 145, 
 160, 12, 90, 22, 
 4, 11, 38, 4, 
 19, 162, 36, 19, 
 148, 12, 75, 178, 
 1, 26, 178, 0, 
 75, 130, 4, 91, 
 178, 8, 11, 146, 
 68, 27, 20, 68, 
 19, 150, 64, 88, 
 146, 68, 67, 4, 
 73, 2, 150, 0, 
 202, 150, 32, 147, 
 50, 4, 209, 50, 
 77, 9, 6, 12, 
 146, 34, 68, 155, 
 16, 0, 80, 48, 
 4, 89, 54, 0, 
 82, 130, 4, 89, 
 36, 9, 130, 
};

const uint8_t kmap0_word_len40_anagram0_seqs[] = {
 0, 230, 227, 72, 
 175, 64, 224, 53, 
 255, 20, 64, 224, 
 235, 171, 217, 128, 
 192, 13, 78, 176, 
 64, 67, 116, 58, 
 61, 128, 247, 245, 
 136, 145, 47, 197, 
 215, 253, 219, 79, 
 119, 76, 47, 76, 
 175, 161, 69, 138, 
 204, 175, 219, 216, 
 245, 215, 63, 103, 
 239, 252, 20, 159, 
 23, 198, 244, 22, 
 24, 169, 90, 249, 
 215, 24, 122, 244, 
 157, 199, 24, 202, 
 219, 155, 215, 24, 
 202, 59, 223, 186, 
 24, 42, 90, 219, 
 186, 24, 49, 178, 
 245, 215, 210, 117, 
 140, 191, 150, 210, 
 117, 204, 220, 161, 
 178, 153, 3, 251, 
 215, 50, 129, 10, 
 14, 128, 190, 168, 
 20, 220, 161, 208, 
 212, 24, 117, 61, 
 77, 148, 121, 231, 
 215, 233, 111, 237, 
 205, 210, 117, 58, 
 253, 52, 21, 101, 
 242, 235, 246, 22, 
 99, 14, 202, 219, 
 161, 99, 222, 207, 
 243, 186, 156, 79, 
 198, 233, 211, 59, 
 175, 220, 219, 161, 
 34, 129, 10, 14, 
 128, 
};

const LookupOfLength kmap0_word_len40_anagram0 = {
  640, // seq_bit_len_and_anagram
  33, // num_chords
  kmap0_word_len40_anagram0_chords, // chords
  kmap0_word_len40_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len40_anagram1_chords[] = {
 132, 12, 26, 54, 
 8, 192, 
};

const uint8_t kmap0_word_len40_anagram1_seqs[] = {
 143, 24, 169, 190, 
 22, 157, 106, 38, 
 110, 209, 
};

const LookupOfLength kmap0_word_len40_anagram1 = {
  641, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len40_anagram1_chords, // chords
  kmap0_word_len40_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len40_anagram2_chords[] = {
 22, 4, 19, 
};

const uint8_t kmap0_word_len40_anagram2_seqs[] = {
 95, 235, 24, 251, 
 215, 
};

const LookupOfLength kmap0_word_len40_anagram2 = {
  642, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len40_anagram2_chords, // chords
  kmap0_word_len40_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len40_anagram3_chords[] = {
 48, 5, 17, 
};

const uint8_t kmap0_word_len40_anagram3_seqs[] = {
 127, 223, 227, 251, 
 215, 
};

const LookupOfLength kmap0_word_len40_anagram3 = {
  643, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len40_anagram3_chords, // chords
  kmap0_word_len40_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len41_anagram0_chords[] = {
 34, 69, 17, 150, 
 0, 27, 22, 36, 
 73, 50, 76, 147, 
 16, 44, 11, 36, 
 77, 18, 54, 5, 
 129, 166, 8, 0, 
 160, 4, 147, 146, 
 12, 146, 162, 8, 
 27, 148, 8, 139, 
 150, 12, 138, 150, 
 12, 131, 162, 0, 
 202, 148, 64, 90, 
 20, 76, 25, 22, 
 64, 202, 18, 76, 
 210, 178, 64, 210, 
 134, 100, 82, 22, 
 4, 210, 50, 8, 
 194, 22, 0, 154, 
 150, 72, 9, 50, 
 65, 25, 50, 8, 
 89, 50, 13, 129, 
 22, 12, 153, 22, 
 36, 144, 150, 8, 
 88, 148, 40, 8, 
 6, 76, 146, 182, 
 9, 26, 54, 33, 
 80, 182, 4, 25, 
 18, 1, 75, 50, 
 96, 139, 176, 72, 
 89, 160, 12, 155, 
};

const uint8_t kmap0_word_len41_anagram0_seqs[] = {
 224, 229, 31, 147, 
 123, 65, 157, 86, 
 244, 134, 2, 94, 
 87, 248, 218, 126, 
 41, 96, 220, 22, 
 253, 187, 143, 48, 
 89, 247, 124, 44, 
 93, 127, 228, 233, 
 207, 219, 71, 166, 
 179, 35, 253, 148, 
 60, 248, 132, 153, 
 126, 99, 48, 82, 
 242, 96, 63, 97, 
 164, 148, 181, 183, 
 192, 72, 149, 156, 
 172, 139, 145, 42, 
 245, 43, 26, 35, 
 85, 106, 252, 53, 
 134, 34, 101, 238, 
 80, 140, 25, 115, 
 13, 149, 210, 245, 
 103, 147, 117, 101, 
 51, 118, 165, 86, 
 203, 102, 164, 239, 
 228, 145, 205, 72, 
 193, 121, 44, 11, 
 174, 48, 166, 223, 
 92, 141, 253, 68, 
 133, 47, 144, 50, 
 183, 104, 95, 84, 
 79, 91, 209, 45, 
 157, 106, 172, 117, 
 91, 239, 177, 108, 
 235, 182, 242, 78, 
 78, 214, 37, 223, 
 189, 157, 126, 93, 
 127, 168, 63, 89, 
 183, 122, 186, 66, 
 207, 83, 245, 164, 
 102, 238, 208, 10, 
 173, 145, 172, 161, 
 181, 152, 79, 45, 
 159, 198, 24, 183, 
 118, 89, 143, 143, 
 60, 103, 51, 28, 
 215, 188, 191, 29, 
 202, 216, 214, 237, 
 163, 113, 141, 80, 
 187, 76, 246, 142, 
 147, 85, 70, 102, 
 49, 40, 235, 254, 
 20, 
};

const LookupOfLength kmap0_word_len41_anagram0 = {
  656, // seq_bit_len_and_anagram
  40, // num_chords
  kmap0_word_len41_anagram0_chords, // chords
  kmap0_word_len41_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len41_anagram1_chords[] = {
 34, 13, 24, 130, 
 68, 27, 178, 8, 
 11, 
};

const uint8_t kmap0_word_len41_anagram1_seqs[] = {
 64, 236, 185, 91, 
 251, 49, 116, 231, 
 101, 227, 98, 168, 
 104, 221, 14, 5, 
};

const LookupOfLength kmap0_word_len41_anagram1 = {
  657, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_word_len41_anagram1_chords, // chords
  kmap0_word_len41_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len42_anagram0_chords[] = {
 52, 8, 81, 48, 
 12, 131, 2, 5, 
 147, 134, 12, 90, 
 150, 8, 82, 144, 
 4, 27, 182, 0, 
 27, 146, 65, 9, 
 18, 65, 26, 2, 
 65, 2, 34, 65, 
 131, 2, 65, 128, 
 18, 44, 3, 38, 
 4, 147, 150, 1, 
 88, 150, 0, 83, 
 178, 8, 153, 52, 
 8, 201, 166, 8, 
 82, 50, 12, 27, 
};

const uint8_t kmap0_word_len42_anagram0_seqs[] = {
 128, 93, 215, 233, 
 244, 60, 98, 78, 
 153, 126, 253, 179, 
 125, 52, 246, 19, 
 70, 170, 63, 205, 
 161, 24, 169, 78, 
 164, 102, 99, 40, 
 90, 119, 126, 141, 
 161, 59, 125, 230, 
 181, 244, 209, 218, 
 219, 161, 178, 143, 
 195, 99, 69, 203, 
 62, 14, 143, 21, 
 45, 251, 56, 26, 
 51, 173, 236, 227, 
 104, 204, 180, 233, 
 23, 58, 253, 54, 
 214, 159, 109, 204, 
 244, 83, 39, 14, 
 51, 119, 232, 184, 
 6, 247, 198, 20, 
 99, 49, 40, 111, 
 135, 114, 174, 149, 
 156, 172, 203, 69, 
 170, 193, 157, 147, 
 232, 245, 180, 254, 
 20, 
};

const LookupOfLength kmap0_word_len42_anagram0 = {
  672, // seq_bit_len_and_anagram
  20, // num_chords
  kmap0_word_len42_anagram0_chords, // chords
  kmap0_word_len42_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len42_anagram1_chords[] = {
 32, 8, 18, 134, 
 0, 25, 
};

const uint8_t kmap0_word_len42_anagram1_seqs[] = {
 160, 0, 9, 36, 
 32, 214, 137, 26, 
 179, 29, 10, 
};

const LookupOfLength kmap0_word_len42_anagram1 = {
  673, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len42_anagram1_chords, // chords
  kmap0_word_len42_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len43_anagram0_chords[] = {
 52, 5, 18, 0, 
 44, 9, 134, 44, 
 194, 48, 13, 129, 
 54, 4, 130, 166, 
 12, 73, 180, 5, 
 136, 182, 76, 130, 
 144, 32, 211, 182, 
 12, 131, 134, 4, 
 90, 146, 4, 155, 
 130, 68, 27, 134, 
 68, 73, 54, 64, 
 81, 48, 12, 155, 
 146, 4, 139, 22, 
 8, 155, 18, 12, 
 11, 160, 37, 153, 
 166, 4, 137, 54, 
 0, 65, 146, 36, 
 147, 52, 12, 152, 
};

const uint8_t kmap0_word_len43_anagram0_seqs[] = {
 224, 240, 57, 249, 
 167, 0, 233, 21, 
 254, 238, 235, 35, 
 70, 170, 212, 12, 
 63, 61, 221, 159, 
 126, 253, 181, 82, 
 227, 159, 228, 103, 
 206, 169, 110, 135, 
 158, 254, 155, 124, 
 134, 250, 236, 72, 
 150, 141, 79, 8, 
 131, 204, 235, 9, 
 194, 72, 245, 183, 
 79, 50, 134, 114, 
 237, 121, 44, 48, 
 102, 76, 191, 29, 
 42, 27, 183, 67, 
 127, 10, 217, 252, 
 181, 70, 235, 202, 
 230, 157, 62, 243, 
 218, 162, 117, 243, 
 19, 21, 190, 192, 
 222, 223, 14, 245, 
 69, 245, 116, 178, 
 110, 250, 214, 181, 
 190, 162, 99, 22, 
 198, 29, 250, 84, 
 163, 102, 250, 237, 
 80, 206, 39, 111, 
 111, 94, 47, 116, 
 140, 183, 241, 73, 
 204, 164, 158, 63, 
 201, 
};

const LookupOfLength kmap0_word_len43_anagram0 = {
  688, // seq_bit_len_and_anagram
  24, // num_chords
  kmap0_word_len43_anagram0_chords, // chords
  kmap0_word_len43_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len44_anagram0_chords[] = {
 4, 4, 82, 50, 
 13, 80, 50, 12, 
 153, 18, 5, 19, 
 146, 12, 11, 50, 
 12, 131, 34, 8, 
 146, 144, 76, 89, 
 146, 68, 73, 2, 
 100, 83, 48, 65, 
 154, 50, 1, 137, 
 130, 4, 203, 128, 
 0, 66, 180, 13, 
 16, 50, 1, 75, 
 52, 12, 17, 50, 
 8, 91, 
};

const uint8_t kmap0_word_len44_anagram0_seqs[] = {
 96, 0, 2, 225, 
 4, 252, 247, 61, 
 102, 110, 209, 79, 
 235, 209, 223, 22, 
 141, 158, 237, 163, 
 241, 215, 24, 186, 
 159, 90, 127, 141, 
 57, 101, 250, 109, 
 209, 152, 103, 26, 
 51, 229, 36, 157, 
 66, 121, 231, 215, 
 210, 188, 173, 191, 
 29, 42, 11, 254, 
 89, 56, 253, 199, 
 184, 76, 182, 98, 
 209, 186, 38, 234, 
 219, 186, 193, 216, 
 68, 191, 29, 26, 
 140, 77, 244, 219, 
 161, 117, 226, 158, 
 79, 201, 195, 249, 
 56, 26, 219, 186, 
 235, 84, 61, 191, 
 121, 156, 181, 69, 
 15, 247, 22, 
};

const LookupOfLength kmap0_word_len44_anagram0 = {
  704, // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_word_len44_anagram0_chords, // chords
  kmap0_word_len44_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len44_anagram1_chords[] = {
 2, 100, 83, 
};

const uint8_t kmap0_word_len44_anagram1_seqs[] = {
 178, 224, 159, 133, 
 211, 8, 
};

const LookupOfLength kmap0_word_len44_anagram1 = {
  705, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len44_anagram1_chords, // chords
  kmap0_word_len44_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len45_anagram0_chords[] = {
 2, 4, 66, 4, 
 4, 66, 180, 4, 
 147, 150, 8, 11, 
 178, 8, 75, 178, 
 8, 25, 50, 8, 
 8, 146, 4, 147, 
 34, 76, 136, 18, 
 108, 90, 22, 4, 
 19, 54, 8, 83, 
 178, 68, 153, 50, 
 5, 17, 182, 0, 
 216, 52, 4, 211, 
 144, 0, 89, 0, 
 4, 145, 
};

const uint8_t kmap0_word_len45_anagram0_seqs[] = {
 224, 1, 3, 4, 
 13, 26, 84, 128, 
 64, 56, 1, 99, 
 16, 253, 25, 243, 
 107, 140, 84, 189, 
 189, 29, 138, 161, 
 108, 204, 219, 162, 
 173, 98, 79, 104, 
 178, 174, 85, 236, 
 9, 77, 214, 245, 
 5, 246, 254, 198, 
 20, 173, 178, 197, 
 150, 249, 41, 121, 
 16, 190, 202, 102, 
 215, 159, 109, 236, 
 250, 235, 234, 225, 
 106, 220, 22, 93, 
 38, 255, 122, 180, 
 67, 199, 199, 244, 
 237, 249, 245, 152, 
 107, 40, 247, 73, 
 230, 106, 220, 199, 
 76, 63, 107, 222, 
 224, 245, 132, 122, 
 231, 5, 140, 27, 
 83, 0, 
};

const LookupOfLength kmap0_word_len45_anagram0 = {
  720, // seq_bit_len_and_anagram
  18, // num_chords
  kmap0_word_len45_anagram0_chords, // chords
  kmap0_word_len45_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len45_anagram3_chords[] = {
 38, 4, 147, 
};

const uint8_t kmap0_word_len45_anagram3_seqs[] = {
 248, 245, 207, 166, 
 222, 2, 
};

const LookupOfLength kmap0_word_len45_anagram3 = {
  723, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len45_anagram3_chords, // chords
  kmap0_word_len45_anagram3_seqs, // sequences
};

const uint8_t kmap0_word_len46_anagram0_chords[] = {
 144, 76, 3, 134, 
 4, 139, 150, 4, 
 17, 146, 1, 11, 
 178, 12, 11, 160, 
 8, 2, 52, 0, 
 25, 50, 76, 137, 
 150, 97, 194, 6, 
 4, 27, 148, 13, 
 26, 134, 32, 210, 
 6, 36, 83, 150, 
 4, 83, 2, 8, 
 73, 38, 68, 82, 
};

const uint8_t kmap0_word_len46_anagram0_seqs[] = {
 143, 24, 41, 133, 
 252, 245, 215, 74, 
 141, 191, 29, 250, 
 181, 78, 212, 233, 
 95, 99, 248, 56, 
 26, 219, 186, 24, 
 41, 101, 109, 252, 
 53, 70, 74, 89, 
 27, 127, 109, 221, 
 113, 29, 171, 243, 
 184, 76, 110, 241, 
 201, 186, 135, 137, 
 226, 202, 176, 107, 
 253, 217, 198, 174, 
 175, 91, 61, 71, 
 76, 122, 69, 87, 
 216, 20, 28, 21, 
 22, 149, 11, 132, 
 253, 59, 197, 152, 
 107, 207, 111, 76, 
 193, 219, 41, 211, 
 111, 135, 114, 62, 
 185, 101, 255, 20, 
};

const LookupOfLength kmap0_word_len46_anagram0 = {
  736, // seq_bit_len_and_anagram
  16, // num_chords
  kmap0_word_len46_anagram0_chords, // chords
  kmap0_word_len46_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len47_anagram0_chords[] = {
 130, 5, 154, 182, 
 72, 26, 164, 8, 
 16, 160, 12, 147, 
 50, 5, 147, 50, 
 12, 90, 176, 64, 
 202, 176, 8, 91, 
 130, 13, 25, 22, 
 12, 154, 150, 4, 
 19, 132, 4, 18, 
 52, 64, 201, 38, 
 4, 201, 164, 12, 
 146, 
};

const uint8_t kmap0_word_len47_anagram0_seqs[] = {
 0, 159, 250, 136, 
 209, 126, 80, 39, 
 196, 150, 86, 52, 
 168, 19, 98, 75, 
 43, 250, 17, 115, 
 202, 244, 27, 243, 
 247, 52, 102, 218, 
 60, 126, 213, 22, 
 61, 252, 83, 96, 
 40, 187, 76, 182, 
 162, 49, 116, 39, 
 68, 15, 23, 173, 
 71, 76, 250, 237, 
 208, 58, 166, 78, 
 173, 63, 69, 157, 
 168, 211, 222, 159, 
 162, 78, 136, 129, 
 191, 29, 202, 249, 
 100, 151, 201, 214, 
 229, 124, 242, 190, 
 110, 63, 137, 129, 
 127, 102, 250, 41, 
 0, 
};

const LookupOfLength kmap0_word_len47_anagram0 = {
  752, // seq_bit_len_and_anagram
  15, // num_chords
  kmap0_word_len47_anagram0_chords, // chords
  kmap0_word_len47_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len48_anagram0_chords[] = {
 50, 13, 11, 48, 
 13, 27, 34, 5, 
 75, 
};

const uint8_t kmap0_word_len48_anagram0_seqs[] = {
 233, 111, 237, 163, 
 209, 186, 233, 53, 
 31, 143, 155, 199, 
 220, 183, 246, 209, 
 248, 186, 
};

const LookupOfLength kmap0_word_len48_anagram0 = {
  768, // seq_bit_len_and_anagram
  3, // num_chords
  kmap0_word_len48_anagram0_chords, // chords
  kmap0_word_len48_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len49_anagram0_chords[] = {
 144, 12, 147, 50, 
 12, 91, 178, 12, 
 91, 160, 8, 10, 
 18, 76, 91, 166, 
 0, 27, 166, 0, 
 211, 150, 36, 67, 
};

const uint8_t kmap0_word_len49_anagram0_seqs[] = {
 143, 104, 242, 68, 
 242, 122, 176, 7, 
 115, 226, 125, 69, 
 99, 168, 232, 225, 
 223, 14, 197, 80, 
 209, 195, 191, 29, 
 42, 155, 113, 58, 
 181, 254, 58, 106, 
 141, 217, 172, 189, 
 69, 13, 230, 62, 
 155, 122, 11, 142, 
 10, 155, 183, 241, 
 215, 
};

const LookupOfLength kmap0_word_len49_anagram0 = {
  784, // seq_bit_len_and_anagram
  8, // num_chords
  kmap0_word_len49_anagram0_chords, // chords
  kmap0_word_len49_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len49_anagram1_chords[] = {
 0, 0, 146, 
};

const uint8_t kmap0_word_len49_anagram1_seqs[] = {
 117, 204, 56, 93, 
 183, 67, 1, 
};

const LookupOfLength kmap0_word_len49_anagram1 = {
  785, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len49_anagram1_chords, // chords
  kmap0_word_len49_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len50_anagram0_chords[] = {
 2, 13, 0, 162, 
 68, 203, 32, 68, 
 130, 150, 12, 147, 
 176, 5, 155, 54, 
 1, 137, 178, 12, 
 201, 
};

const uint8_t kmap0_word_len50_anagram0_seqs[] = {
 224, 193, 1, 30, 
 52, 40, 61, 150, 
 201, 205, 189, 29, 
 250, 88, 38, 55, 
 247, 118, 232, 215, 
 58, 113, 209, 233, 
 215, 24, 122, 207, 
 111, 166, 95, 183, 
 174, 137, 250, 238, 
 147, 204, 157, 50, 
 237, 171, 35, 51, 
};

const LookupOfLength kmap0_word_len50_anagram0 = {
  800, // seq_bit_len_and_anagram
  7, // num_chords
  kmap0_word_len50_anagram0_chords, // chords
  kmap0_word_len50_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len51_anagram0_chords[] = {
 150, 32, 83, 176, 
 77, 138, 0, 13, 
 2, 38, 8, 211, 
 6, 8, 1, 164, 
 0, 17, 
};

const uint8_t kmap0_word_len51_anagram0_seqs[] = {
 0, 225, 52, 111, 
 84, 232, 121, 44, 
 105, 92, 201, 242, 
 246, 99, 73, 227, 
 74, 150, 183, 59, 
 213, 76, 220, 98, 
 111, 209, 169, 102, 
 226, 22, 123, 139, 
 58, 113, 254, 217, 
 212, 91, 0, 
};

const LookupOfLength kmap0_word_len51_anagram0 = {
  816, // seq_bit_len_and_anagram
  6, // num_chords
  kmap0_word_len51_anagram0_chords, // chords
  kmap0_word_len51_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len51_anagram1_chords[] = {
 128, 0, 10, 
};

const uint8_t kmap0_word_len51_anagram1_seqs[] = {
 24, 170, 198, 109, 
 177, 183, 0, 
};

const LookupOfLength kmap0_word_len51_anagram1 = {
  817, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len51_anagram1_chords, // chords
  kmap0_word_len51_anagram1_seqs, // sequences
};

const uint8_t kmap0_word_len52_anagram0_chords[] = {
 32, 40, 66, 166, 
 64, 89, 130, 64, 
 81, 178, 12, 202, 
 54, 64, 209, 
};

const uint8_t kmap0_word_len52_anagram0_seqs[] = {
 64, 4, 120, 73, 
 64, 4, 44, 155, 
 119, 250, 204, 219, 
 161, 178, 121, 167, 
 207, 188, 29, 154, 
 154, 209, 68, 175, 
 142, 204, 117, 60, 
 46, 147, 155, 123, 
 13, 
};

const LookupOfLength kmap0_word_len52_anagram0 = {
  832, // seq_bit_len_and_anagram
  5, // num_chords
  kmap0_word_len52_anagram0_chords, // chords
  kmap0_word_len52_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len52_anagram2_chords[] = {
 38, 4, 147, 
};

const uint8_t kmap0_word_len52_anagram2_seqs[] = {
 245, 103, 27, 51, 
 253, 80, 1, 
};

const LookupOfLength kmap0_word_len52_anagram2 = {
  834, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len52_anagram2_chords, // chords
  kmap0_word_len52_anagram2_seqs, // sequences
};

const uint8_t kmap0_word_len53_anagram0_chords[] = {
 54, 72, 144, 
};

const uint8_t kmap0_word_len53_anagram0_seqs[] = {
 46, 147, 155, 250, 
 156, 206, 9, 
};

const LookupOfLength kmap0_word_len53_anagram0 = {
  848, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len53_anagram0_chords, // chords
  kmap0_word_len53_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len57_anagram0_chords[] = {
 54, 12, 218, 22, 
 76, 219, 
};

const uint8_t kmap0_word_len57_anagram0_seqs[] = {
 160, 90, 149, 11, 
 18, 95, 251, 1, 
 95, 123, 203, 122, 
 232, 85, 2, 
};

const LookupOfLength kmap0_word_len57_anagram0 = {
  912, // seq_bit_len_and_anagram
  2, // num_chords
  kmap0_word_len57_anagram0_chords, // chords
  kmap0_word_len57_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len58_anagram0_chords[] = {
 34, 5, 219, 
};

const uint8_t kmap0_word_len58_anagram0_seqs[] = {
 220, 183, 246, 209, 
 248, 186, 84, 0, 
};

const LookupOfLength kmap0_word_len58_anagram0 = {
  928, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len58_anagram0_chords, // chords
  kmap0_word_len58_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len60_anagram0_chords[] = {
 182, 0, 219, 
};

const uint8_t kmap0_word_len60_anagram0_seqs[] = {
 99, 174, 161, 220, 
 103, 83, 111, 1, 
};

const LookupOfLength kmap0_word_len60_anagram0 = {
  960, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len60_anagram0_chords, // chords
  kmap0_word_len60_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len65_anagram0_chords[] = {
 164, 36, 9, 
};

const uint8_t kmap0_word_len65_anagram0_seqs[] = {
 224, 4, 10, 66, 
 40, 225, 46, 220, 
 1, 
};

const LookupOfLength kmap0_word_len65_anagram0 = {
  1040, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len65_anagram0_chords, // chords
  kmap0_word_len65_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len75_anagram0_chords[] = {
 34, 65, 82, 
};

const uint8_t kmap0_word_len75_anagram0_seqs[] = {
 224, 10, 10, 192, 
 160, 193, 21, 20, 
 224, 6, 
};

const LookupOfLength kmap0_word_len75_anagram0 = {
  1200, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len75_anagram0_chords, // chords
  kmap0_word_len75_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len97_anagram0_chords[] = {
 2, 5, 0, 
};

const uint8_t kmap0_word_len97_anagram0_seqs[] = {
 207, 229, 142, 159, 
 114, 207, 229, 64, 
 151, 43, 105, 92, 
 1, 
};

const LookupOfLength kmap0_word_len97_anagram0 = {
  1552, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len97_anagram0_chords, // chords
  kmap0_word_len97_anagram0_seqs, // sequences
};

const uint8_t kmap0_word_len100_anagram0_chords[] = {
 16, 1, 144, 
};

const uint8_t kmap0_word_len100_anagram0_seqs[] = {
 227, 131, 140, 219, 
 161, 229, 58, 213, 
 76, 220, 98, 111, 
 1, 
};

const LookupOfLength kmap0_word_len100_anagram0 = {
  1600, // seq_bit_len_and_anagram
  1, // num_chords
  kmap0_word_len100_anagram0_chords, // chords
  kmap0_word_len100_anagram0_seqs, // sequences
};

const LookupOfLength* kmap0_word_lookups_array[] = {
 &kmap0_word_len4_anagram1, &kmap0_word_len5_anagram1, &kmap0_word_len7_anagram0, &kmap0_word_len7_anagram1, 
 &kmap0_word_len8_anagram0, &kmap0_word_len8_anagram1, &kmap0_word_len9_anagram0, &kmap0_word_len9_anagram1, 
 &kmap0_word_len9_anagram2, &kmap0_word_len10_anagram0, &kmap0_word_len10_anagram1, &kmap0_word_len10_anagram2, 
 &kmap0_word_len10_anagram3, &kmap0_word_len10_anagram4, &kmap0_word_len11_anagram0, &kmap0_word_len11_anagram1, 
 &kmap0_word_len11_anagram2, &kmap0_word_len11_anagram3, &kmap0_word_len11_anagram4, &kmap0_word_len12_anagram0, 
 &kmap0_word_len12_anagram1, &kmap0_word_len12_anagram2, &kmap0_word_len12_anagram3, &kmap0_word_len13_anagram0, 
 &kmap0_word_len13_anagram1, &kmap0_word_len13_anagram2, &kmap0_word_len13_anagram3, &kmap0_word_len14_anagram0, 
 &kmap0_word_len14_anagram1, &kmap0_word_len14_anagram2, &kmap0_word_len14_anagram3, &kmap0_word_len14_anagram4, 
 &kmap0_word_len15_anagram0, &kmap0_word_len15_anagram1, &kmap0_word_len15_anagram2, &kmap0_word_len15_anagram3, 
 &kmap0_word_len15_anagram4, &kmap0_word_len15_anagram5, &kmap0_word_len15_anagram7, &kmap0_word_len16_anagram0, 
 &kmap0_word_len16_anagram1, &kmap0_word_len16_anagram2, &kmap0_word_len16_anagram3, &kmap0_word_len17_anagram0, 
 &kmap0_word_len17_anagram1, &kmap0_word_len17_anagram2, &kmap0_word_len17_anagram3, &kmap0_word_len17_anagram5, 
 &kmap0_word_len18_anagram0, &kmap0_word_len18_anagram1, &kmap0_word_len18_anagram2, &kmap0_word_len18_anagram3, 
 &kmap0_word_len19_anagram0, &kmap0_word_len19_anagram1, &kmap0_word_len19_anagram2, &kmap0_word_len19_anagram3, 
 &kmap0_word_len19_anagram4, &kmap0_word_len20_anagram0, &kmap0_word_len20_anagram1, &kmap0_word_len20_anagram2, 
 &kmap0_word_len20_anagram3, &kmap0_word_len20_anagram4, &kmap0_word_len20_anagram6, &kmap0_word_len21_anagram0, 
 &kmap0_word_len21_anagram1, &kmap0_word_len21_anagram2, &kmap0_word_len21_anagram3, &kmap0_word_len21_anagram4, 
 &kmap0_word_len21_anagram5, &kmap0_word_len22_anagram0, &kmap0_word_len22_anagram1, &kmap0_word_len22_anagram2, 
 &kmap0_word_len22_anagram3, &kmap0_word_len22_anagram4, &kmap0_word_len22_anagram5, &kmap0_word_len22_anagram6, 
 &kmap0_word_len23_anagram0, &kmap0_word_len23_anagram1, &kmap0_word_len23_anagram2, &kmap0_word_len23_anagram3, 
 &kmap0_word_len24_anagram0, &kmap0_word_len24_anagram1, &kmap0_word_len24_anagram2, &kmap0_word_len24_anagram3, 
 &kmap0_word_len24_anagram4, &kmap0_word_len24_anagram5, &kmap0_word_len24_anagram6, &kmap0_word_len25_anagram0, 
 &kmap0_word_len25_anagram1, &kmap0_word_len25_anagram2, &kmap0_word_len25_anagram3, &kmap0_word_len25_anagram4, 
 &kmap0_word_len26_anagram0, &kmap0_word_len26_anagram1, &kmap0_word_len26_anagram2, &kmap0_word_len26_anagram3, 
 &kmap0_word_len26_anagram4, &kmap0_word_len27_anagram0, &kmap0_word_len27_anagram1, &kmap0_word_len27_anagram2, 
 &kmap0_word_len27_anagram3, &kmap0_word_len27_anagram7, &kmap0_word_len28_anagram0, &kmap0_word_len28_anagram1, 
 &kmap0_word_len28_anagram2, &kmap0_word_len28_anagram3, &kmap0_word_len28_anagram4, &kmap0_word_len29_anagram0, 
 &kmap0_word_len29_anagram1, &kmap0_word_len29_anagram2, &kmap0_word_len30_anagram0, &kmap0_word_len30_anagram1, 
 &kmap0_word_len30_anagram2, &kmap0_word_len30_anagram3, &kmap0_word_len31_anagram0, &kmap0_word_len31_anagram1, 
 &kmap0_word_len31_anagram2, &kmap0_word_len31_anagram3, &kmap0_word_len32_anagram0, &kmap0_word_len32_anagram1, 
 &kmap0_word_len32_anagram2, &kmap0_word_len33_anagram0, &kmap0_word_len33_anagram1, &kmap0_word_len33_anagram2, 
 &kmap0_word_len33_anagram3, &kmap0_word_len34_anagram0, &kmap0_word_len34_anagram1, &kmap0_word_len34_anagram2, 
 &kmap0_word_len34_anagram4, &kmap0_word_len35_anagram0, &kmap0_word_len35_anagram1, &kmap0_word_len35_anagram2, 
 &kmap0_word_len36_anagram0, &kmap0_word_len36_anagram1, &kmap0_word_len36_anagram2, &kmap0_word_len37_anagram0, 
 &kmap0_word_len37_anagram1, &kmap0_word_len37_anagram2, &kmap0_word_len38_anagram0, &kmap0_word_len38_anagram1, 
 &kmap0_word_len38_anagram2, &kmap0_word_len39_anagram0, &kmap0_word_len39_anagram1, &kmap0_word_len40_anagram0, 
 &kmap0_word_len40_anagram1, &kmap0_word_len40_anagram2, &kmap0_word_len40_anagram3, &kmap0_word_len41_anagram0, 
 &kmap0_word_len41_anagram1, &kmap0_word_len42_anagram0, &kmap0_word_len42_anagram1, &kmap0_word_len43_anagram0, 
 &kmap0_word_len44_anagram0, &kmap0_word_len44_anagram1, &kmap0_word_len45_anagram0, &kmap0_word_len45_anagram3, 
 &kmap0_word_len46_anagram0, &kmap0_word_len47_anagram0, &kmap0_word_len48_anagram0, &kmap0_word_len49_anagram0, 
 &kmap0_word_len49_anagram1, &kmap0_word_len50_anagram0, &kmap0_word_len51_anagram0, &kmap0_word_len51_anagram1, 
 &kmap0_word_len52_anagram0, &kmap0_word_len52_anagram2, &kmap0_word_len53_anagram0, &kmap0_word_len57_anagram0, 
 &kmap0_word_len58_anagram0, &kmap0_word_len60_anagram0, &kmap0_word_len65_anagram0, &kmap0_word_len75_anagram0, 
 &kmap0_word_len97_anagram0, &kmap0_word_len100_anagram0, 
};

const LookupsOfSeqType kmap0_word_lookups = {
  174, // num_lookups
  kmap0_word_lookups_array, // lookups
};

const LookupsOfSeqType* kmap0_lookups_array[] = {
 &kmap0_plain_lookups, &kmap0_macro_lookups, &kmap0_command_lookups, &kmap0_word_lookups, 
};

const KmapStruct kmap0_lookups = {
  kmap0_lookups_array, // lookups_by_seq_type
};

const uint8_t kmap1_plain_len3_anagram0_chords[] = {
 4, 0, 0, 
};

const uint8_t kmap1_plain_len3_anagram0_seqs[] = {
 6, 
};

const LookupOfLength kmap1_plain_len3_anagram0 = {
  48, // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_plain_len3_anagram0_chords, // chords
  kmap1_plain_len3_anagram0_seqs, // sequences
};

const uint8_t kmap1_plain_len4_anagram0_chords[] = {
 128, 0, 0, 16, 
 0, 0, 
};

const uint8_t kmap1_plain_len4_anagram0_seqs[] = {
 207, 
};

const LookupOfLength kmap1_plain_len4_anagram0 = {
  64, // seq_bit_len_and_anagram
  2, // num_chords
  kmap1_plain_len4_anagram0_chords, // chords
  kmap1_plain_len4_anagram0_seqs, // sequences
};

const uint8_t kmap1_plain_len5_anagram0_chords[] = {
 2, 0, 0, 
};

const uint8_t kmap1_plain_len5_anagram0_seqs[] = {
 18, 
};

const LookupOfLength kmap1_plain_len5_anagram0 = {
  80, // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_plain_len5_anagram0_chords, // chords
  kmap1_plain_len5_anagram0_seqs, // sequences
};

const uint8_t kmap1_plain_len7_anagram0_chords[] = {
 32, 0, 0, 
};

const uint8_t kmap1_plain_len7_anagram0_seqs[] = {
 87, 
};

const LookupOfLength kmap1_plain_len7_anagram0 = {
  112, // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_plain_len7_anagram0_chords, // chords
  kmap1_plain_len7_anagram0_seqs, // sequences
};

const uint8_t kmap1_plain_len9_anagram0_chords[] = {
 0, 1, 0, 8, 
 0, 0, 
};

const uint8_t kmap1_plain_len9_anagram0_seqs[] = {
 101, 202, 1, 
};

const LookupOfLength kmap1_plain_len9_anagram0 = {
  144, // seq_bit_len_and_anagram
  2, // num_chords
  kmap1_plain_len9_anagram0_chords, // chords
  kmap1_plain_len9_anagram0_seqs, // sequences
};

const uint8_t kmap1_plain_len14_anagram0_chords[] = {
 0, 8, 0, 
};

const uint8_t kmap1_plain_len14_anagram0_seqs[] = {
 229, 3, 
};

const LookupOfLength kmap1_plain_len14_anagram0 = {
  224, // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_plain_len14_anagram0_chords, // chords
  kmap1_plain_len14_anagram0_seqs, // sequences
};

const uint8_t kmap1_plain_len18_anagram0_chords[] = {
 0, 4, 0, 
};

const uint8_t kmap1_plain_len18_anagram0_seqs[] = {
 160, 124, 3, 
};

const LookupOfLength kmap1_plain_len18_anagram0 = {
  288, // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_plain_len18_anagram0_chords, // chords
  kmap1_plain_len18_anagram0_seqs, // sequences
};

const uint8_t kmap1_plain_len25_anagram0_chords[] = {
 1, 0, 0, 
};

const uint8_t kmap1_plain_len25_anagram0_seqs[] = {
 229, 85, 190, 1, 
};

const LookupOfLength kmap1_plain_len25_anagram0 = {
  400, // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_plain_len25_anagram0_chords, // chords
  kmap1_plain_len25_anagram0_seqs, // sequences
};

const LookupOfLength* kmap1_plain_lookups_array[] = {
 &kmap1_plain_len3_anagram0, &kmap1_plain_len4_anagram0, &kmap1_plain_len5_anagram0, &kmap1_plain_len7_anagram0, 
 &kmap1_plain_len9_anagram0, &kmap1_plain_len14_anagram0, &kmap1_plain_len18_anagram0, &kmap1_plain_len25_anagram0, 
};

const LookupsOfSeqType kmap1_plain_lookups = {
  8, // num_lookups
  kmap1_plain_lookups_array, // lookups
};

const LookupOfLength* kmap1_macro_lookups_array[] = {
};

const LookupsOfSeqType kmap1_macro_lookups = {
  0, // num_lookups
  kmap1_macro_lookups_array, // lookups
};

const uint8_t kmap1_command_len15_anagram0_chords[] = {
 0, 0, 1, 
};

const uint8_t kmap1_command_len15_anagram0_seqs[] = {
 229, 35, 
};

const LookupOfLength kmap1_command_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  1, // num_chords
  kmap1_command_len15_anagram0_chords, // chords
  kmap1_command_len15_anagram0_seqs, // sequences
};

const LookupOfLength* kmap1_command_lookups_array[] = {
 &kmap1_command_len15_anagram0, 
};

const LookupsOfSeqType kmap1_command_lookups = {
  1, // num_lookups
  kmap1_command_lookups_array, // lookups
};

const LookupOfLength* kmap1_word_lookups_array[] = {
};

const LookupsOfSeqType kmap1_word_lookups = {
  0, // num_lookups
  kmap1_word_lookups_array, // lookups
};

const LookupsOfSeqType* kmap1_lookups_array[] = {
 &kmap1_plain_lookups, &kmap1_macro_lookups, &kmap1_command_lookups, &kmap1_word_lookups, 
};

const KmapStruct kmap1_lookups = {
  kmap1_lookups_array, // lookups_by_seq_type
};

const uint8_t kmap2_plain_len3_anagram0_chords[] = {
 16, 0, 0, 
};

const uint8_t kmap2_plain_len3_anagram0_seqs[] = {
 6, 
};

const LookupOfLength kmap2_plain_len3_anagram0 = {
  48, // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_plain_len3_anagram0_chords, // chords
  kmap2_plain_len3_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len4_anagram0_chords[] = {
 0, 4, 0, 96, 
 0, 0, 2, 0, 
 0, 64, 8, 0, 
 192, 0, 0, 128, 
 0, 0, 64, 1, 
 0, 64, 4, 0, 
 80, 0, 0, 
};

const uint8_t kmap2_plain_len4_anagram0_seqs[] = {
 143, 77, 26, 195, 
 11, 
};

const LookupOfLength kmap2_plain_len4_anagram0 = {
  64, // seq_bit_len_and_anagram
  9, // num_chords
  kmap2_plain_len4_anagram0_chords, // chords
  kmap2_plain_len4_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len5_anagram0_chords[] = {
 68, 0, 0, 66, 
 0, 0, 0, 8, 
 0, 4, 0, 0, 
 32, 0, 0, 
};

const uint8_t kmap2_plain_len5_anagram0_seqs[] = {
 18, 166, 154, 1, 
};

const LookupOfLength kmap2_plain_len5_anagram0 = {
  80, // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_plain_len5_anagram0_chords, // chords
  kmap2_plain_len5_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len6_anagram0_chords[] = {
 36, 0, 0, 0, 
 1, 0, 32, 1, 
 0, 32, 8, 0, 
 96, 1, 0, 
};

const uint8_t kmap2_plain_len6_anagram0_seqs[] = {
 231, 113, 139, 5, 
};

const LookupOfLength kmap2_plain_len6_anagram0 = {
  96, // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_plain_len6_anagram0_chords, // chords
  kmap2_plain_len6_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len7_anagram0_chords[] = {
 0, 9, 0, 100, 
 0, 0, 
};

const uint8_t kmap2_plain_len7_anagram0_seqs[] = {
 165, 43, 
};

const LookupOfLength kmap2_plain_len7_anagram0 = {
  112, // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_plain_len7_anagram0_chords, // chords
  kmap2_plain_len7_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len8_anagram0_chords[] = {
 64, 9, 0, 96, 
 8, 0, 
};

const uint8_t kmap2_plain_len8_anagram0_seqs[] = {
 2, 23, 
};

const LookupOfLength kmap2_plain_len8_anagram0 = {
  128, // seq_bit_len_and_anagram
  2, // num_chords
  kmap2_plain_len8_anagram0_chords, // chords
  kmap2_plain_len8_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len9_anagram0_chords[] = {
 33, 0, 0, 68, 
 8, 0, 66, 8, 
 0, 64, 0, 0, 
 4, 8, 0, 
};

const uint8_t kmap2_plain_len9_anagram0_seqs[] = {
 151, 203, 8, 46, 
 87, 22, 
};

const LookupOfLength kmap2_plain_len9_anagram0 = {
  144, // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_plain_len9_anagram0_chords, // chords
  kmap2_plain_len9_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len10_anagram0_chords[] = {
 82, 0, 0, 16, 
 4, 0, 1, 0, 
 0, 68, 1, 0, 
 64, 2, 0, 
};

const uint8_t kmap2_plain_len10_anagram0_seqs[] = {
 66, 9, 33, 188, 
 208, 130, 0, 
};

const LookupOfLength kmap2_plain_len10_anagram0 = {
  160, // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_plain_len10_anagram0_chords, // chords
  kmap2_plain_len10_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len11_anagram0_chords[] = {
 144, 0, 0, 34, 
 0, 0, 4, 1, 
 0, 1, 1, 0, 
 66, 1, 0, 196, 
 0, 0, 
};

const uint8_t kmap2_plain_len11_anagram0_seqs[] = {
 130, 18, 210, 165, 
 133, 44, 232, 242, 
 0, 
};

const LookupOfLength kmap2_plain_len11_anagram0 = {
  176, // seq_bit_len_and_anagram
  6, // num_chords
  kmap2_plain_len11_anagram0_chords, // chords
  kmap2_plain_len11_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len12_anagram0_chords[] = {
 18, 0, 0, 208, 
 0, 0, 192, 4, 
 0, 130, 0, 0, 
 68, 4, 0, 19, 
 0, 0, 98, 0, 
 0, 
};

const uint8_t kmap2_plain_len12_anagram0_seqs[] = {
 229, 127, 169, 194, 
 37, 28, 194, 89, 
 222, 151, 4, 
};

const LookupOfLength kmap2_plain_len12_anagram0 = {
  192, // seq_bit_len_and_anagram
  7, // num_chords
  kmap2_plain_len12_anagram0_chords, // chords
  kmap2_plain_len12_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len13_anagram0_chords[] = {
 128, 4, 0, 194, 
 0, 0, 64, 5, 
 0, 
};

const uint8_t kmap2_plain_len13_anagram0_seqs[] = {
 194, 93, 184, 93, 
 34, 
};

const LookupOfLength kmap2_plain_len13_anagram0 = {
  208, // seq_bit_len_and_anagram
  3, // num_chords
  kmap2_plain_len13_anagram0_chords, // chords
  kmap2_plain_len13_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len14_anagram0_chords[] = {
 80, 4, 0, 2, 
 8, 0, 48, 0, 
 0, 6, 0, 0, 
 128, 8, 0, 
};

const uint8_t kmap2_plain_len14_anagram0_seqs[] = {
 151, 2, 16, 92, 
 126, 151, 95, 229, 
 3, 
};

const LookupOfLength kmap2_plain_len14_anagram0 = {
  224, // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_plain_len14_anagram0_chords, // chords
  kmap2_plain_len14_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len15_anagram0_chords[] = {
 8, 0, 0, 128, 
 13, 0, 54, 0, 
 0, 0, 2, 0, 
 18, 1, 0, 208, 
 1, 0, 144, 1, 
 0, 192, 5, 0, 
 128, 5, 0, 194, 
 1, 0, 130, 1, 
 0, 80, 5, 0, 
 16, 5, 0, 1, 
 8, 0, 5, 0, 
 0, 
};

const uint8_t kmap2_plain_len15_anagram0_seqs[] = {
 151, 236, 242, 67, 
 249, 180, 252, 124, 
 201, 191, 148, 94, 
 242, 46, 57, 151, 
 220, 75, 217, 165, 
 252, 18, 119, 137, 
 47, 95, 93, 194, 
 1, 
};

const LookupOfLength kmap2_plain_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  15, // num_chords
  kmap2_plain_len15_anagram0_chords, // chords
  kmap2_plain_len15_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len16_anagram0_chords[] = {
 132, 0, 0, 96, 
 4, 0, 16, 1, 
 0, 2, 1, 0, 
};

const uint8_t kmap2_plain_len16_anagram0_seqs[] = {
 160, 60, 64, 80, 
 64, 72, 64, 208, 
};

const LookupOfLength kmap2_plain_len16_anagram0 = {
  256, // seq_bit_len_and_anagram
  4, // num_chords
  kmap2_plain_len16_anagram0_chords, // chords
  kmap2_plain_len16_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len17_anagram0_chords[] = {
 80, 1, 0, 32, 
 4, 0, 2, 4, 
 0, 84, 0, 0, 
 4, 4, 0, 66, 
 4, 0, 
};

const uint8_t kmap2_plain_len17_anagram0_seqs[] = {
 64, 56, 192, 165, 
 130, 242, 7, 194, 
 5, 132, 19, 92, 
 18, 
};

const LookupOfLength kmap2_plain_len17_anagram0 = {
  272, // seq_bit_len_and_anagram
  6, // num_chords
  kmap2_plain_len17_anagram0_chords, // chords
  kmap2_plain_len17_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len18_anagram0_chords[] = {
 20, 0, 0, 224, 
 0, 0, 0, 5, 
 0, 
};

const uint8_t kmap2_plain_len18_anagram0_seqs[] = {
 64, 184, 1, 225, 
 14, 46, 17, 
};

const LookupOfLength kmap2_plain_len18_anagram0 = {
  288, // seq_bit_len_and_anagram
  3, // num_chords
  kmap2_plain_len18_anagram0_chords, // chords
  kmap2_plain_len18_anagram0_seqs, // sequences
};

const uint8_t kmap2_plain_len19_anagram0_chords[] = {
 160, 0, 0, 
};

const uint8_t kmap2_plain_len19_anagram0_seqs[] = {
 224, 82, 0, 
};

const LookupOfLength kmap2_plain_len19_anagram0 = {
  304, // seq_bit_len_and_anagram
  1, // num_chords
  kmap2_plain_len19_anagram0_chords, // chords
  kmap2_plain_len19_anagram0_seqs, // sequences
};

const LookupOfLength* kmap2_plain_lookups_array[] = {
 &kmap2_plain_len3_anagram0, &kmap2_plain_len4_anagram0, &kmap2_plain_len5_anagram0, &kmap2_plain_len6_anagram0, 
 &kmap2_plain_len7_anagram0, &kmap2_plain_len8_anagram0, &kmap2_plain_len9_anagram0, &kmap2_plain_len10_anagram0, 
 &kmap2_plain_len11_anagram0, &kmap2_plain_len12_anagram0, &kmap2_plain_len13_anagram0, &kmap2_plain_len14_anagram0, 
 &kmap2_plain_len15_anagram0, &kmap2_plain_len16_anagram0, &kmap2_plain_len17_anagram0, &kmap2_plain_len18_anagram0, 
 &kmap2_plain_len19_anagram0, 
};

const LookupsOfSeqType kmap2_plain_lookups = {
  17, // num_lookups
  kmap2_plain_lookups_array, // lookups
};

const LookupOfLength* kmap2_macro_lookups_array[] = {
};

const LookupsOfSeqType kmap2_macro_lookups = {
  0, // num_lookups
  kmap2_macro_lookups_array, // lookups
};

const uint8_t kmap2_command_len15_anagram0_chords[] = {
 16, 0, 1, 1, 
 4, 0, 3, 0, 
 0, 17, 0, 0, 
 129, 0, 0, 
};

const uint8_t kmap2_command_len15_anagram0_seqs[] = {
 229, 163, 242, 227, 
 37, 172, 124, 82, 
 126, 2, 
};

const LookupOfLength kmap2_command_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  5, // num_chords
  kmap2_command_len15_anagram0_chords, // chords
  kmap2_command_len15_anagram0_seqs, // sequences
};

const LookupOfLength* kmap2_command_lookups_array[] = {
 &kmap2_command_len15_anagram0, 
};

const LookupsOfSeqType kmap2_command_lookups = {
  1, // num_lookups
  kmap2_command_lookups_array, // lookups
};

const LookupOfLength* kmap2_word_lookups_array[] = {
};

const LookupsOfSeqType kmap2_word_lookups = {
  0, // num_lookups
  kmap2_word_lookups_array, // lookups
};

const LookupsOfSeqType* kmap2_lookups_array[] = {
 &kmap2_plain_lookups, &kmap2_macro_lookups, &kmap2_command_lookups, &kmap2_word_lookups, 
};

const KmapStruct kmap2_lookups = {
  kmap2_lookups_array, // lookups_by_seq_type
};

const LookupOfLength* kmap3_plain_lookups_array[] = {
};

const LookupsOfSeqType kmap3_plain_lookups = {
  0, // num_lookups
  kmap3_plain_lookups_array, // lookups
};

const LookupOfLength* kmap3_macro_lookups_array[] = {
};

const LookupsOfSeqType kmap3_macro_lookups = {
  0, // num_lookups
  kmap3_macro_lookups_array, // lookups
};

const uint8_t kmap3_command_len15_anagram0_chords[] = {
 36, 9, 0, 
};

const uint8_t kmap3_command_len15_anagram0_seqs[] = {
 229, 35, 
};

const LookupOfLength kmap3_command_len15_anagram0 = {
  240, // seq_bit_len_and_anagram
  1, // num_chords
  kmap3_command_len15_anagram0_chords, // chords
  kmap3_command_len15_anagram0_seqs, // sequences
};

const LookupOfLength* kmap3_command_lookups_array[] = {
 &kmap3_command_len15_anagram0, 
};

const LookupsOfSeqType kmap3_command_lookups = {
  1, // num_lookups
  kmap3_command_lookups_array, // lookups
};

const LookupOfLength* kmap3_word_lookups_array[] = {
};

const LookupsOfSeqType kmap3_word_lookups = {
  0, // num_lookups
  kmap3_word_lookups_array, // lookups
};

const LookupsOfSeqType* kmap3_lookups_array[] = {
 &kmap3_plain_lookups, &kmap3_macro_lookups, &kmap3_command_lookups, &kmap3_word_lookups, 
};

const KmapStruct kmap3_lookups = {
  kmap3_lookups_array, // lookups_by_seq_type
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
 &kmap1_lookups, 
};

const uint8_t gaming_mode_mod_chord_0[] = {
 0, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_1[] = {
 0, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_2[] = {
 0, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_3[] = {
 0, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_4[] = {
 1, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_5[] = {
 0, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_6[] = {
 0, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_7[] = {
 0, 0, 0, 
};

const uint8_t gaming_mode_mod_chord_8[] = {
 0, 4, 0, 
};

const uint8_t gaming_mode_mod_chord_9[] = {
 0, 0, 0, 
};

const uint8_t* gaming_mode_mod_chord[] = {
 gaming_mode_mod_chord_0, gaming_mode_mod_chord_1, gaming_mode_mod_chord_2, gaming_mode_mod_chord_3, 
 gaming_mode_mod_chord_4, gaming_mode_mod_chord_5, gaming_mode_mod_chord_6, gaming_mode_mod_chord_7, 
 gaming_mode_mod_chord_8, gaming_mode_mod_chord_9, 
};

const uint8_t gaming_mode_anagram_mask[] = {
 0, 0, 0, 
};

const ModeStruct gaming_mode_struct = {
  1, // is_gaming
  1, // num_kmaps
  gaming_mode_kmaps_array, // kmaps
  gaming_mode_mod_chord, // mod_chords
  gaming_mode_anagram_mask, // anagram_mask
};

const KmapStruct* left_hand_mode_kmaps_array[] = {
 &kmap2_lookups, 
};

const uint8_t left_hand_mode_mod_chord_0[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_1[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_2[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_3[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_4[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_5[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_6[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_7[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_8[] = {
 0, 0, 0, 
};

const uint8_t left_hand_mode_mod_chord_9[] = {
 0, 0, 0, 
};

const uint8_t* left_hand_mode_mod_chord[] = {
 left_hand_mode_mod_chord_0, left_hand_mode_mod_chord_1, left_hand_mode_mod_chord_2, left_hand_mode_mod_chord_3, 
 left_hand_mode_mod_chord_4, left_hand_mode_mod_chord_5, left_hand_mode_mod_chord_6, left_hand_mode_mod_chord_7, 
 left_hand_mode_mod_chord_8, left_hand_mode_mod_chord_9, 
};

const uint8_t left_hand_mode_anagram_mask[] = {
 0, 0, 0, 
};

const ModeStruct left_hand_mode_struct = {
  0, // is_gaming
  1, // num_kmaps
  left_hand_mode_kmaps_array, // kmaps
  left_hand_mode_mod_chord, // mod_chords
  left_hand_mode_anagram_mask, // anagram_mask
};

const KmapStruct* windows_mode_kmaps_array[] = {
 &kmap3_lookups, &kmap0_lookups, 
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
  2, // num_kmaps
  windows_mode_kmaps_array, // kmaps
  windows_mode_mod_chord, // mod_chords
  windows_mode_anagram_mask, // anagram_mask
};

const ModeStruct* mode_structs[] = {
 &default_mode_struct, &gaming_mode_struct, &left_hand_mode_struct, &windows_mode_struct, 
};


} // end namespace conf
