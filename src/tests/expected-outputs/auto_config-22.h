#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "config_types.h"
typedef void (*voidFuncPtr)(void);
namespace conf {
extern const uint32_t CHORD_DELAY;
extern const uint32_t HELD_DELAY;
extern const WordSpacePosition SPACE_POS;
#define TEENSY_LC 
extern const std::array<uint8_t,3> row_pins;
extern const std::array<uint8_t,8> column_pins;
#define ENABLE_LED_TYPING_FEEDBACK 
extern const bool USE_STANDBY_INTERRUPTS;
extern const std::array<uint8_t,3> rgb_led_pins;
#define ENABLE_RGB_LED 
extern const uint8_t MIN_HUFFMAN_CODE_BIT_LEN;
extern const HuffmanChar huffman_lookup[73];
extern const uint8_t MAX_ANAGRAM_NUM;
extern const std::array<Mod,4> word_mods;
extern const std::array<Mod,4> plain_mods;
extern const std::array<Mod,2> anagram_mods;
extern const std::array<uint8_t,2> anagram_mod_numbers;
extern const std::array<uint8_t,4> plain_mod_keys;
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

extern const uint8_t MAX_KEYS_IN_SEQUENCE;
extern const std::array<const ModeStruct*,4> mode_structs;

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

