#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "config_types.h"
/*
Hacky way to be able to write the type of C-style arrays as `c_array_t<int,42>`, in which the type is entirely before the variable name. Otherwise it'sharder to auto-generate the code because the type information is splitacross either side of the variable name.
*/

#include <type_traits>
template<class T, size_t N>
using c_array_t = T[N];

typedef void (*voidFuncPtr)(void);
namespace conf {
uint32_t const CHORD_DELAY = 30;

uint32_t const HELD_DELAY = 200;

WordSpacePosition const SPACE_POS = WordSpacePosition::Before;

#define TEENSY_LC
std::array<uint8_t, 3> const row_pins = {1, 0, 19};

std::array<uint8_t, 8> const column_pins = {15, 16, 17, 18,
  20, 21, 5, 6};

#define ENABLE_LED_TYPING_FEEDBACK
bool const USE_STANDBY_INTERRUPTS = true;

std::array<uint8_t, 3> const rgb_led_pins = {10, 11, 12};

#define ENABLE_RGB_LED
enum class Command : uint8_t {
  command_cycle_capital = 0,
  command_cycle_nospace = 1,
  command_cycle_word = 2,
  command_delete_word = 3,
  command_led_battery = 4,
  command_led_colors = 5,
  command_led_rainbow = 6,
  command_left_limit = 7,
  command_left_word = 8,
  command_pan_left = 9,
  command_pan_right = 10,
  command_pause = 11,
  command_right_limit = 12,
  command_right_word = 13,
  command_scroll_down = 14,
  command_scroll_up = 15,
  command_shorten_last_word = 16,
  command_sticky_alt = 17,
  command_sticky_ctrl = 18,
  command_sticky_gui = 19,
  command_sticky_shift = 20,
  command_switch_to = 21,
  command_toggle_wireless = 22,
  command_windows_mode = 23,
};

uint8_t const BLANK_KEY = 0;

uint8_t const MIN_HUFFMAN_CODE_BIT_LEN = 4;

c_array_t<HuffmanChar, 73> const huffman_lookup = {HuffmanChar {HuffmanBits {{2}},
  4,
  static_cast<uint8_t>(BLANK_KEY),
  false}, HuffmanChar {HuffmanBits {{0}},
  4,
  static_cast<uint8_t>(KEY_T),
  false}, HuffmanChar {HuffmanBits {{27}},
  5,
  static_cast<uint8_t>(Command::command_switch_to),
  false}, HuffmanChar {HuffmanBits {{17}},
  5,
  static_cast<uint8_t>(KEY_3),
  false},
  HuffmanChar {HuffmanBits {{25}},
  5,
  static_cast<uint8_t>(KEY_E),
  false}, HuffmanChar {HuffmanBits {{9}},
  5,
  static_cast<uint8_t>(KEY_H),
  false}, HuffmanChar {HuffmanBits {{10}},
  5,
  static_cast<uint8_t>(KEY_S),
  false}, HuffmanChar {HuffmanBits {{12}},
  6,
  static_cast<uint8_t>(Command::command_delete_word),
  false},
  HuffmanChar {HuffmanBits {{22}},
  6,
  static_cast<uint8_t>(Command::command_led_colors),
  false}, HuffmanChar {HuffmanBits {{8}},
  6,
  static_cast<uint8_t>(Command::command_led_rainbow),
  false}, HuffmanChar {HuffmanBits {{40}},
  6,
  static_cast<uint8_t>(Command::command_left_limit),
  false}, HuffmanChar {HuffmanBits {{4}},
  6,
  static_cast<uint8_t>(Command::command_left_word),
  false},
  HuffmanChar {HuffmanBits {{44}},
  6,
  static_cast<uint8_t>(Command::command_pan_left),
  false}, HuffmanChar {HuffmanBits {{54}},
  6,
  static_cast<uint8_t>(Command::command_right_word),
  false}, HuffmanChar {HuffmanBits {{56}},
  6,
  static_cast<uint8_t>(Command::command_shorten_last_word),
  false}, HuffmanChar {HuffmanBits {{36}},
  6,
  static_cast<uint8_t>(Command::command_sticky_gui),
  false},
  HuffmanChar {HuffmanBits {{30}},
  6,
  static_cast<uint8_t>(KEY_0),
  false}, HuffmanChar {HuffmanBits {{3}},
  6,
  static_cast<uint8_t>(KEY_1),
  false}, HuffmanChar {HuffmanBits {{6}},
  6,
  static_cast<uint8_t>(KEY_5),
  false}, HuffmanChar {HuffmanBits {{26}},
  6,
  static_cast<uint8_t>(KEY_6),
  false},
  HuffmanChar {HuffmanBits {{43}},
  6,
  static_cast<uint8_t>(KEY_7),
  false}, HuffmanChar {HuffmanBits {{52}},
  6,
  static_cast<uint8_t>(KEY_A),
  false}, HuffmanChar {HuffmanBits {{20}},
  6,
  static_cast<uint8_t>(KEY_B),
  false}, HuffmanChar {HuffmanBits {{24}},
  6,
  static_cast<uint8_t>(KEY_BACKSPACE),
  false},
  HuffmanChar {HuffmanBits {{28}},
  6,
  static_cast<uint8_t>(KEY_I),
  false}, HuffmanChar {HuffmanBits {{60}},
  6,
  static_cast<uint8_t>(KEY_J),
  false}, HuffmanChar {HuffmanBits {{15}},
  6,
  static_cast<uint8_t>(KEY_L),
  false}, HuffmanChar {HuffmanBits {{62}},
  6,
  static_cast<uint8_t>(KEY_P),
  false},
  HuffmanChar {HuffmanBits {{14}},
  6,
  static_cast<uint8_t>(KEY_Q),
  false}, HuffmanChar {HuffmanBits {{46}},
  6,
  static_cast<uint8_t>(KEY_R),
  false}, HuffmanChar {HuffmanBits {{38}},
  6,
  static_cast<uint8_t>(KEY_X),
  false}, HuffmanChar {HuffmanBits {{1}},
  6,
  static_cast<uint8_t>(KEY_Y),
  false},
  HuffmanChar {HuffmanBits {{58}},
  6,
  static_cast<uint8_t>(MODIFIERKEY_ALT),
  true}, HuffmanChar {HuffmanBits {{33}},
  7,
  static_cast<uint8_t>(Command::command_cycle_capital),
  false}, HuffmanChar {HuffmanBits {{97}},
  7,
  static_cast<uint8_t>(Command::command_cycle_nospace),
  false}, HuffmanChar {HuffmanBits {{99}},
  7,
  static_cast<uint8_t>(Command::command_cycle_word),
  false},
  HuffmanChar {HuffmanBits {{7}},
  7,
  static_cast<uint8_t>(Command::command_led_battery),
  false}, HuffmanChar {HuffmanBits {{115}},
  7,
  static_cast<uint8_t>(Command::command_pan_right),
  false}, HuffmanChar {HuffmanBits {{71}},
  7,
  static_cast<uint8_t>(Command::command_pause),
  false}, HuffmanChar {HuffmanBits {{85}},
  7,
  static_cast<uint8_t>(Command::command_right_limit),
  false},
  HuffmanChar {HuffmanBits {{47}},
  7,
  static_cast<uint8_t>(Command::command_scroll_down),
  false}, HuffmanChar {HuffmanBits {{111}},
  7,
  static_cast<uint8_t>(Command::command_scroll_up),
  false}, HuffmanChar {HuffmanBits {{55}},
  7,
  static_cast<uint8_t>(Command::command_sticky_alt),
  false}, HuffmanChar {HuffmanBits {{23}},
  7,
  static_cast<uint8_t>(Command::command_sticky_ctrl),
  false},
  HuffmanChar {HuffmanBits {{29}},
  7,
  static_cast<uint8_t>(Command::command_sticky_shift),
  false}, HuffmanChar {HuffmanBits {{95}},
  7,
  static_cast<uint8_t>(Command::command_toggle_wireless),
  false}, HuffmanChar {HuffmanBits {{63}},
  7,
  static_cast<uint8_t>(Command::command_windows_mode),
  false}, HuffmanChar {HuffmanBits {{75}},
  7,
  static_cast<uint8_t>(KEY_2),
  false},
  HuffmanChar {HuffmanBits {{103}},
  7,
  static_cast<uint8_t>(KEY_4),
  false}, HuffmanChar {HuffmanBits {{83}},
  7,
  static_cast<uint8_t>(KEY_8),
  false}, HuffmanChar {HuffmanBits {{19}},
  7,
  static_cast<uint8_t>(KEY_9),
  false}, HuffmanChar {HuffmanBits {{119}},
  7,
  static_cast<uint8_t>(KEY_C),
  false},
  HuffmanChar {HuffmanBits {{87}},
  7,
  static_cast<uint8_t>(KEY_D),
  false}, HuffmanChar {HuffmanBits {{125}},
  7,
  static_cast<uint8_t>(KEY_ENTER),
  false}, HuffmanChar {HuffmanBits {{61}},
  7,
  static_cast<uint8_t>(KEY_F),
  false}, HuffmanChar {HuffmanBits {{93}},
  7,
  static_cast<uint8_t>(KEY_G),
  false},
  HuffmanChar {HuffmanBits {{35}},
  7,
  static_cast<uint8_t>(KEY_K),
  false}, HuffmanChar {HuffmanBits {{31}},
  7,
  static_cast<uint8_t>(KEY_M),
  false}, HuffmanChar {HuffmanBits {{127}},
  7,
  static_cast<uint8_t>(KEY_N),
  false}, HuffmanChar {HuffmanBits {{51}},
  7,
  static_cast<uint8_t>(KEY_O),
  false},
  HuffmanChar {HuffmanBits {{45}},
  7,
  static_cast<uint8_t>(KEY_SPACE),
  false}, HuffmanChar {HuffmanBits {{11}},
  7,
  static_cast<uint8_t>(KEY_TAB),
  false}, HuffmanChar {HuffmanBits {{53}},
  7,
  static_cast<uint8_t>(KEY_U),
  false}, HuffmanChar {HuffmanBits {{37}},
  7,
  static_cast<uint8_t>(KEY_V),
  false},
  HuffmanChar {HuffmanBits {{13}},
  7,
  static_cast<uint8_t>(KEY_W),
  false}, HuffmanChar {HuffmanBits {{109}},
  7,
  static_cast<uint8_t>(KEY_Z),
  false}, HuffmanChar {HuffmanBits {{21}},
  7,
  static_cast<uint8_t>(MODIFIERKEY_CTRL),
  true}, HuffmanChar {HuffmanBits {{117}},
  7,
  static_cast<uint8_t>(MODIFIERKEY_GUI),
  true},
  HuffmanChar {HuffmanBits {{101}},
  7,
  static_cast<uint8_t>(MODIFIERKEY_SHIFT),
  true}, HuffmanChar {HuffmanBits {{39}},
  7,
  static_cast<uint8_t>(Mode::default_mode),
  false}, HuffmanChar {HuffmanBits {{77}},
  7,
  static_cast<uint8_t>(Mode::gaming_mode),
  false}, HuffmanChar {HuffmanBits {{69}},
  7,
  static_cast<uint8_t>(Mode::left_hand_mode),
  false},
  HuffmanChar {HuffmanBits {{5}},
  7,
  static_cast<uint8_t>(Mode::windows_mode),
  false}};

uint8_t const MAX_ANAGRAM_NUM = 1;

std::array<Mod, 4> const word_mods = {Mod::mod_capital, Mod::mod_nospace, Mod::mod_double, Mod::mod_shorten};

std::array<Mod, 4> const plain_mods = {Mod::mod_alt, Mod::mod_ctrl, Mod::mod_gui, Mod::mod_shift};

std::array<Mod, 2> const anagram_mods = {Mod::mod_anagram_1, Mod::mod_anagram_2};

std::array<uint8_t, 2> const anagram_mod_numbers = {1, 2};

std::array<uint8_t, 4> const plain_mod_keys = {static_cast<uint8_t>(MODIFIERKEY_ALT), static_cast<uint8_t>(MODIFIERKEY_CTRL), static_cast<uint8_t>(MODIFIERKEY_GUI), static_cast<uint8_t>(MODIFIERKEY_SHIFT)};

uint8_t const MAX_KEYS_IN_SEQUENCE = 5;

c_array_t<ChordData, 1> const kmap0_Plain_len4_anagram0_chords = {ChordData {{0, 0, 1}}};

c_array_t<uint8_t, 1> const kmap0_Plain_len4_anagram0_seqs = {0};

LookupKmapTypeLenAnagram const kmap0_Plain_len4_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {4,
  0},
  1,
  kmap0_Plain_len4_anagram0_chords,
  kmap0_Plain_len4_anagram0_seqs};

c_array_t<ChordData, 4> const kmap0_Plain_len5_anagram0_chords = {ChordData {{0, 0, 64}}, ChordData {{0, 32, 0}}, ChordData {{16, 0, 0}}, ChordData {{144, 0, 0}}};

c_array_t<uint8_t, 3> const kmap0_Plain_len5_anagram0_seqs = {42, 229, 8};

LookupKmapTypeLenAnagram const kmap0_Plain_len5_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {5,
  0},
  4,
  kmap0_Plain_len5_anagram0_chords,
  kmap0_Plain_len5_anagram0_seqs};

c_array_t<ChordData, 16> const kmap0_Plain_len6_anagram0_chords = {ChordData {{0, 0, 16}}, ChordData {{0, 0, 18}}, ChordData {{0, 0, 128}}, ChordData {{0, 0, 130}},
  ChordData {{0, 0, 144}}, ChordData {{0, 4, 0}}, ChordData {{0, 32, 1}}, ChordData {{0, 32, 8}},
  ChordData {{0, 64, 128}}, ChordData {{2, 0, 0}}, ChordData {{4, 0, 0}}, ChordData {{8, 0, 0}},
  ChordData {{18, 0, 0}}, ChordData {{36, 0, 0}}, ChordData {{128, 4, 0}}, ChordData {{130, 0, 0}}};

c_array_t<uint8_t, 12> const kmap0_Plain_len6_anagram0_seqs = {110, 240, 152, 60,
  237, 105, 14, 231,
  99, 3, 101, 172};

LookupKmapTypeLenAnagram const kmap0_Plain_len6_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {6,
  0},
  16,
  kmap0_Plain_len6_anagram0_chords,
  kmap0_Plain_len6_anagram0_seqs};

c_array_t<ChordData, 17> const kmap0_Plain_len7_anagram0_chords = {ChordData {{0, 0, 2}}, ChordData {{0, 0, 8}}, ChordData {{0, 0, 9}}, ChordData {{0, 0, 65}},
  ChordData {{0, 0, 72}}, ChordData {{0, 1, 0}}, ChordData {{0, 8, 0}}, ChordData {{0, 9, 0}},
  ChordData {{0, 64, 0}}, ChordData {{0, 64, 2}}, ChordData {{0, 128, 0}}, ChordData {{4, 8, 0}},
  ChordData {{16, 4, 0}}, ChordData {{32, 0, 0}}, ChordData {{32, 1, 0}}, ChordData {{32, 8, 0}},
  ChordData {{128, 0, 0}}};

c_array_t<uint8_t, 15> const kmap0_Plain_len7_anagram0_seqs = {247, 255, 114, 122,
  238, 125, 70, 215,
  70, 171, 61, 169,
  117, 75, 51};

LookupKmapTypeLenAnagram const kmap0_Plain_len7_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {7,
  0},
  17,
  kmap0_Plain_len7_anagram0_chords,
  kmap0_Plain_len7_anagram0_seqs};

c_array_t<ChordData, 1> const kmap0_Plain_len10_anagram0_chords = {ChordData {{0, 0, 4}}};

c_array_t<uint8_t, 2> const kmap0_Plain_len10_anagram0_seqs = {186, 0};

LookupKmapTypeLenAnagram const kmap0_Plain_len10_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {10,
  0},
  1,
  kmap0_Plain_len10_anagram0_chords,
  kmap0_Plain_len10_anagram0_seqs};

c_array_t<ChordData, 3> const kmap0_Plain_len11_anagram0_chords = {ChordData {{0, 16, 0}}, ChordData {{1, 0, 0}}, ChordData {{64, 0, 0}}};

c_array_t<uint8_t, 5> const kmap0_Plain_len11_anagram0_seqs = {117, 169, 72, 89,
  0};

LookupKmapTypeLenAnagram const kmap0_Plain_len11_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {11,
  0},
  3,
  kmap0_Plain_len11_anagram0_chords,
  kmap0_Plain_len11_anagram0_seqs};

c_array_t<LookupKmapTypeLenAnagram const*, 6> const kmap0_Plain_lookups_array = {&kmap0_Plain_len4_anagram0, &kmap0_Plain_len5_anagram0, &kmap0_Plain_len6_anagram0, &kmap0_Plain_len7_anagram0,
  &kmap0_Plain_len10_anagram0, &kmap0_Plain_len11_anagram0};

LookupKmapType const kmap0_Plain_lookups = LookupKmapType {6,
  kmap0_Plain_lookups_array};

c_array_t<ChordData, 1> const kmap0_Macro_len18_anagram0_chords = {ChordData {{0, 128, 192}}};

c_array_t<uint8_t, 3> const kmap0_Macro_len18_anagram0_seqs = {143, 234, 3};

LookupKmapTypeLenAnagram const kmap0_Macro_len18_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {18,
  0},
  1,
  kmap0_Macro_len18_anagram0_chords,
  kmap0_Macro_len18_anagram0_seqs};

c_array_t<LookupKmapTypeLenAnagram const*, 1> const kmap0_Macro_lookups_array = {&kmap0_Macro_len18_anagram0};

LookupKmapType const kmap0_Macro_lookups = LookupKmapType {1,
  kmap0_Macro_lookups_array};

c_array_t<LookupKmapTypeLenAnagram const*, 0> const kmap0_Command_lookups_array = {};

LookupKmapType const kmap0_Command_lookups = LookupKmapType {0,
  kmap0_Command_lookups_array};

c_array_t<LookupKmapTypeLenAnagram const*, 0> const kmap0_Word_lookups_array = {};

LookupKmapType const kmap0_Word_lookups = LookupKmapType {0,
  kmap0_Word_lookups_array};

c_array_t<LookupKmapType const*, 4> const kmap0_lookups_array = {&kmap0_Plain_lookups, &kmap0_Macro_lookups, &kmap0_Command_lookups, &kmap0_Word_lookups};

KmapStruct const kmap0_lookups = KmapStruct {kmap0_lookups_array};

c_array_t<LookupKmapTypeLenAnagram const*, 0> const kmap1_Plain_lookups_array = {};

LookupKmapType const kmap1_Plain_lookups = LookupKmapType {0,
  kmap1_Plain_lookups_array};

c_array_t<LookupKmapTypeLenAnagram const*, 0> const kmap1_Macro_lookups_array = {};

LookupKmapType const kmap1_Macro_lookups = LookupKmapType {0,
  kmap1_Macro_lookups_array};

c_array_t<LookupKmapTypeLenAnagram const*, 0> const kmap1_Command_lookups_array = {};

LookupKmapType const kmap1_Command_lookups = LookupKmapType {0,
  kmap1_Command_lookups_array};

c_array_t<ChordData, 1> const kmap1_Word_len14_anagram0_chords = {ChordData {{16, 32, 1}}};

c_array_t<uint8_t, 2> const kmap1_Word_len14_anagram0_seqs = {144, 50};

LookupKmapTypeLenAnagram const kmap1_Word_len14_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {14,
  0},
  1,
  kmap1_Word_len14_anagram0_chords,
  kmap1_Word_len14_anagram0_seqs};

c_array_t<ChordData, 1> const kmap1_Word_len22_anagram0_chords = {ChordData {{146, 0, 0}}};

c_array_t<uint8_t, 3> const kmap1_Word_len22_anagram0_seqs = {67, 140, 43};

LookupKmapTypeLenAnagram const kmap1_Word_len22_anagram0 = LookupKmapTypeLenAnagram {LengthAndAnagram {22,
  0},
  1,
  kmap1_Word_len22_anagram0_chords,
  kmap1_Word_len22_anagram0_seqs};

c_array_t<ChordData, 1> const kmap1_Word_len23_anagram1_chords = {ChordData {{16, 32, 1}}};

c_array_t<uint8_t, 3> const kmap1_Word_len23_anagram1_seqs = {144, 51, 36};

LookupKmapTypeLenAnagram const kmap1_Word_len23_anagram1 = LookupKmapTypeLenAnagram {LengthAndAnagram {23,
  1},
  1,
  kmap1_Word_len23_anagram1_chords,
  kmap1_Word_len23_anagram1_seqs};

c_array_t<LookupKmapTypeLenAnagram const*, 3> const kmap1_Word_lookups_array = {&kmap1_Word_len14_anagram0, &kmap1_Word_len22_anagram0, &kmap1_Word_len23_anagram1};

LookupKmapType const kmap1_Word_lookups = LookupKmapType {3,
  kmap1_Word_lookups_array};

c_array_t<LookupKmapType const*, 4> const kmap1_lookups_array = {&kmap1_Plain_lookups, &kmap1_Macro_lookups, &kmap1_Command_lookups, &kmap1_Word_lookups};

KmapStruct const kmap1_lookups = KmapStruct {kmap1_lookups_array};

c_array_t<KmapStruct const*, 2> const default_mode_kmaps_array = {&kmap1_lookups, &kmap0_lookups};

c_array_t<ChordData, 10> const default_mode_mod_chord = {ChordData {{0, 0, 4}}, ChordData {{8, 0, 0}}, ChordData {{8, 128, 0}}, ChordData {{64, 0, 0}},
  ChordData {{1, 0, 0}}, ChordData {{1, 0, 0}}, ChordData {{0, 16, 0}}, ChordData {{0, 0, 4}},
  ChordData {{64, 0, 0}}, ChordData {{0, 16, 0}}};

ChordData const default_mode_anagram_mask = ChordData {{8, 128, 0}};

ModeStruct const default_mode_struct = ModeStruct {false,
  2,
  default_mode_kmaps_array,
  default_mode_mod_chord,
  default_mode_anagram_mask};

c_array_t<KmapStruct const*, 1> const gaming_mode_kmaps_array = {&kmap0_lookups};

c_array_t<ChordData, 10> const gaming_mode_mod_chord = {ChordData {{0, 0, 4}}, ChordData {{8, 0, 0}}, ChordData {{8, 128, 0}}, ChordData {{64, 0, 0}},
  ChordData {{1, 0, 0}}, ChordData {{1, 0, 0}}, ChordData {{0, 16, 0}}, ChordData {{0, 0, 4}},
  ChordData {{64, 0, 0}}, ChordData {{0, 16, 0}}};

ChordData const gaming_mode_anagram_mask = ChordData {{8, 128, 0}};

ModeStruct const gaming_mode_struct = ModeStruct {false,
  1,
  gaming_mode_kmaps_array,
  gaming_mode_mod_chord,
  gaming_mode_anagram_mask};

c_array_t<KmapStruct const*, 1> const left_hand_mode_kmaps_array = {&kmap0_lookups};

c_array_t<ChordData, 10> const left_hand_mode_mod_chord = {ChordData {{0, 0, 4}}, ChordData {{8, 0, 0}}, ChordData {{8, 128, 0}}, ChordData {{64, 0, 0}},
  ChordData {{1, 0, 0}}, ChordData {{1, 0, 0}}, ChordData {{0, 16, 0}}, ChordData {{0, 0, 4}},
  ChordData {{64, 0, 0}}, ChordData {{0, 16, 0}}};

ChordData const left_hand_mode_anagram_mask = ChordData {{8, 128, 0}};

ModeStruct const left_hand_mode_struct = ModeStruct {false,
  1,
  left_hand_mode_kmaps_array,
  left_hand_mode_mod_chord,
  left_hand_mode_anagram_mask};

c_array_t<KmapStruct const*, 1> const windows_mode_kmaps_array = {&kmap0_lookups};

c_array_t<ChordData, 10> const windows_mode_mod_chord = {ChordData {{0, 0, 4}}, ChordData {{8, 0, 0}}, ChordData {{8, 128, 0}}, ChordData {{64, 0, 0}},
  ChordData {{1, 0, 0}}, ChordData {{1, 0, 0}}, ChordData {{0, 16, 0}}, ChordData {{0, 0, 4}},
  ChordData {{64, 0, 0}}, ChordData {{0, 16, 0}}};

ChordData const windows_mode_anagram_mask = ChordData {{8, 128, 0}};

ModeStruct const windows_mode_struct = ModeStruct {false,
  1,
  windows_mode_kmaps_array,
  windows_mode_mod_chord,
  windows_mode_anagram_mask};

std::array<ModeStruct const*, 4> const mode_structs = {&default_mode_struct, &gaming_mode_struct, &left_hand_mode_struct, &windows_mode_struct};


} // end namespace conf

#ifdef DEBUG_MESSAGES
   #define ENABLE_SERIAL_DEBUG
   #include <Arduino.h>
   #define DEBUG1(msg) Serial.print(msg)
   #define DEBUG1_LN(msg) Serial.println(msg)
#else
    #define DEBUG1(msg)
    #define DEBUG1_LN(msg)
#endif

