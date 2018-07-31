#ifndef AUTO_CONFIG_BIG_TEST_H_
#define AUTO_CONFIG_BIG_TEST_H_
#include <Arduino.h>
#include "structs.h"
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
#define CHORD_DELAY 30
#define HELD_DELAY 200
#define DEBOUNCE_DELAY 10
#define DEBUG_MESSAGES 0
#define WORD_SPACE_POSITION 0
#define FEATHER_M0_BLE 
extern const uint8_t* row_pins[];
extern const uint8_t* column_pins[];
#define ENABLE_LED_TYPING_FEEDBACK 
#define USE_STANDBY_INTERRUPTS 
extern const uint8_t rgb_led_pins[];
extern const uint8_t battery_level_pin;
#define NUM_ROWS 3
#define NUM_COLUMNS 8
#define NUM_HANDS 1
#define NUM_MATRIX_POSITIONS 24
#define NUM_RGB_LED_PINS 3
#define ENABLE_RGB_LED 
#define HAS_BATTERY 
#define NUM_BYTES_IN_CHORD 3
#define BLANK_KEY 0
#define NUM_HUFFMAN_CODES 98
#define MIN_HUFFMAN_CODE_BIT_LEN 3
extern const HuffmanChar huffman_lookup[];
enum mod_enum : uint8_t {
  MOD_ALT_ENUM = 0,
  MOD_ANAGRAM_1_ENUM = 1,
  MOD_ANAGRAM_2_ENUM = 2,
  MOD_CAPITAL_ENUM = 3,
  MOD_CTRL_ENUM = 4,
  MOD_DOUBLE_ENUM = 5,
  MOD_GUI_ENUM = 6,
  MOD_NOSPACE_ENUM = 7,
  MOD_SHIFT_ENUM = 8,
  MOD_SHORTEN_ENUM = 9,
};

#define NUM_MODIFIERS 10
#define NUM_WORD_MODS 4
#define NUM_ANAGRAM_MODS 2
#define NUM_ANAGRAMS 8
#define NUM_PLAIN_MODS 4
extern const mod_enum word_mod_indices[];
extern const mod_enum plain_mod_indices[];
extern const mod_enum anagram_mod_indices[];
extern const uint8_t plain_mod_keys[];
enum command_enum : uint8_t {
  COMMAND_CYCLE_CAPITAL = 0,
  COMMAND_CYCLE_NOSPACE = 1,
  COMMAND_CYCLE_WORD = 2,
  COMMAND_DEFAULT_MODE = 3,
  COMMAND_DELETE_WORD = 4,
  COMMAND_GAMING_MODE = 5,
  COMMAND_LED_BATTERY = 6,
  COMMAND_LED_COLORS = 7,
  COMMAND_LED_RAINBOW = 8,
  COMMAND_LEFT_HAND_MODE = 9,
  COMMAND_LEFT_LIMIT = 10,
  COMMAND_LEFT_WORD = 11,
  COMMAND_PAUSE = 12,
  COMMAND_RIGHT_LIMIT = 13,
  COMMAND_RIGHT_WORD = 14,
  COMMAND_SHORTEN_LAST_WORD = 15,
  COMMAND_STICKY_ALT = 16,
  COMMAND_STICKY_CTRL = 17,
  COMMAND_STICKY_GUI = 18,
  COMMAND_STICKY_SHIFT = 19,
  COMMAND_WINDOWS_MODE = 20,
};

enum seq_type_enum : uint8_t {
  PLAIN = 0,
  MACRO = 1,
  COMMAND = 2,
  WORD = 3,
};

enum mode_enum : uint8_t {
  DEFAULT_MODE = 0,
  GAMING_MODE = 1,
  LEFT_HAND_MODE = 2,
  WINDOWS_MODE = 3,
};

#define MAX_KEYS_IN_SEQUENCE 41
extern const ModeStruct* mode_structs[];

} // end namespace conf

#if DEBUG_MESSAGES == 0
#define DEBUG1(msg)
#define DEBUG1_LN(msg)
#define DEBUG2(msg)
#define DEBUG2_LN(msg)
#endif

#if DEBUG_MESSAGES == 1
#define ENABLE_SERIAL_DEBUG
#define DEBUG1(msg) Serial.print(msg)
#define DEBUG1_LN(msg) Serial.println(msg)
#define DEBUG2(msg)
#define DEBUG2_LN(msg)
#endif

#if DEBUG_MESSAGES == 2
#define ENABLE_SERIAL_DEBUG
#define DEBUG1(msg) Serial.print(msg)
#define DEBUG1_LN(msg) Serial.println(msg)
#define DEBUG2(msg) Serial.print(msg)
#define DEBUG2_LN(msg) Serial.println(msg)
#endif

#endif // AUTO_CONFIG_BIG_TEST_H_
