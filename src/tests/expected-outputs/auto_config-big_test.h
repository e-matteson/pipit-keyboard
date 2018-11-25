#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "config_types.h"
typedef void (*voidFuncPtr)(void);

#ifndef KEYPAD_0
#define KEYPAD_0 98
#define KEYPAD_1 89
#define KEYPAD_2 90
#define KEYPAD_3 91
#define KEYPAD_4 92
#define KEYPAD_5 93
#define KEYPAD_6 94
#define KEYPAD_7 95
#define KEYPAD_8 96
#define KEYPAD_9 97
#define KEYPAD_ASTERIX 85
#define KEYPAD_ENTER 88
#define KEYPAD_MINUS 86
#define KEYPAD_PERIOD 99
#define KEYPAD_PLUS 87
#define KEYPAD_SLASH 84
#define KEY_0 39
#define KEY_1 30
#define KEY_2 31
#define KEY_3 32
#define KEY_4 33
#define KEY_5 34
#define KEY_6 35
#define KEY_7 36
#define KEY_8 37
#define KEY_9 38
#define KEY_A 4
#define KEY_B 5
#define KEY_BACKSLASH 49
#define KEY_BACKSPACE 42
#define KEY_C 6
#define KEY_CAPS_LOCK 57
#define KEY_COMMA 54
#define KEY_D 7
#define KEY_DELETE 76
#define KEY_DOWN 81
#define KEY_E 8
#define KEY_END 77
#define KEY_ENTER 40
#define KEY_EQUAL 46
#define KEY_ESC 41
#define KEY_F 9
#define KEY_F1 58
#define KEY_F10 67
#define KEY_F11 68
#define KEY_F12 69
#define KEY_F13 104
#define KEY_F14 105
#define KEY_F15 106
#define KEY_F16 107
#define KEY_F17 108
#define KEY_F18 109
#define KEY_F19 110
#define KEY_F2 59
#define KEY_F20 111
#define KEY_F21 112
#define KEY_F22 113
#define KEY_F23 114
#define KEY_F24 115
#define KEY_F3 60
#define KEY_F4 61
#define KEY_F5 62
#define KEY_F6 63
#define KEY_F7 64
#define KEY_F8 65
#define KEY_F9 66
#define KEY_G 10
#define KEY_H 11
#define KEY_HOME 74
#define KEY_I 12
#define KEY_INSERT 73
#define KEY_J 13
#define KEY_K 14
#define KEY_L 15
#define KEY_LEFT 80
#define KEY_LEFT_BRACE 47
#define KEY_M 16
#define KEY_MENU 101
#define KEY_MINUS 45
#define KEY_N 17
#define KEY_NON_US_NUM 50
#define KEY_NUM_LOCK 83
#define KEY_O 18
#define KEY_P 19
#define KEY_PAGE_DOWN 78
#define KEY_PAGE_UP 75
#define KEY_PAUSE 72
#define KEY_PERIOD 55
#define KEY_PRINTSCREEN 70
#define KEY_Q 20
#define KEY_QUOTE 52
#define KEY_R 21
#define KEY_RIGHT 79
#define KEY_RIGHT_BRACE 48
#define KEY_S 22
#define KEY_SCROLL_LOCK 71
#define KEY_SEMICOLON 51
#define KEY_SLASH 56
#define KEY_SPACE 44
#define KEY_T 23
#define KEY_TAB 43
#define KEY_TILDE 53
#define KEY_U 24
#define KEY_UP 82
#define KEY_V 25
#define KEY_W 26
#define KEY_X 27
#define KEY_Y 28
#define KEY_Z 29
#define MODIFIERKEY_ALT 4
#define MODIFIERKEY_CTRL 1
#define MODIFIERKEY_GUI 8
#define MODIFIERKEY_LEFT_ALT 4
#define MODIFIERKEY_LEFT_CTRL 1
#define MODIFIERKEY_LEFT_GUI 8
#define MODIFIERKEY_LEFT_SHIFT 2
#define MODIFIERKEY_RIGHT_ALT 64
#define MODIFIERKEY_RIGHT_CTRL 16
#define MODIFIERKEY_RIGHT_GUI 128
#define MODIFIERKEY_RIGHT_SHIFT 32
#define MODIFIERKEY_SHIFT 2
#endif // ifndef KEYPAD_0

namespace conf {
extern const uint32_t CHORD_DELAY;
extern const uint32_t HELD_DELAY;
extern const uint32_t DEBOUNCE_DELAY;
#define DEBUG_MESSAGES 0
extern const WordSpacePosition SPACE_POS;
#define FEATHER_M0_BLE 
extern const std::array<uint8_t,3> row_pins;
extern const std::array<uint8_t,8> column_pins;
#define ENABLE_LED_TYPING_FEEDBACK 
extern const bool USE_STANDBY_INTERRUPTS;
extern const std::array<uint8_t,3> rgb_led_pins;
extern const uint8_t battery_level_pin;
#define ENABLE_RGB_LED 
#define HAS_BATTERY 
extern const uint8_t MIN_HUFFMAN_CODE_BIT_LEN;
extern const HuffmanChar huffman_lookup[105];
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
extern const ModeStruct* mode_structs[4];

} // end namespace conf

#if DEBUG_MESSAGES == 0
    #define DEBUG1(msg)
    #define DEBUG1_LN(msg)
    #define DEBUG2(msg)
    #define DEBUG2_LN(msg)
#else
   #define ENABLE_SERIAL_DEBUG
   #include <Arduino.h>
   #define DEBUG1(msg) Serial.print(msg)
   #define DEBUG1_LN(msg) Serial.println(msg)
   #if DEBUG_MESSAGES == 1
       #define DEBUG2(msg)
       #define DEBUG2_LN(msg)
   #else
       #define DEBUG2(msg) Serial.print(msg)
       #define DEBUG2_LN(msg) Serial.println(msg)
   #endif

#endif

