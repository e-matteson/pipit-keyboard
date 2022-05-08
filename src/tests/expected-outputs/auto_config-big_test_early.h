#pragma once
namespace conf {
const uint8_t NUM_MATRIX_POSITIONS = 24;

const uint8_t MAX_ALLOWED_ANAGRAM = 15;

const uint16_t MAX_ALLOWED_SEQUENCE_BIT_LENGTH = 4095;

const uint8_t MAX_HUFFMAN_CODE_BIT_LEN = 15;

enum class Mode : uint8_t {
  default_mode = 0,
  gaming_mode = 1,
  left_hand_mode = 2,
  windows_mode = 3,
};

const Mode DEFAULT_MODE = Mode::default_mode;

enum class Mod : uint8_t {
  mod_alt = 0,
  mod_anagram_1 = 1,
  mod_anagram_2 = 2,
  mod_capital = 3,
  mod_ctrl = 4,
  mod_double = 5,
  mod_gui = 6,
  mod_nospace = 7,
  mod_shift = 8,
  mod_shorten = 9,
};

const uint8_t NUM_MODIFIERS = 10;

enum class SeqType : uint8_t {
  Plain = 0,
  Macro = 1,
  Command = 2,
  Word = 3,
};


} // end namespace conf
