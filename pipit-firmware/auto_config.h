/**
 * Automatically generated by pipit-config on:  Wed May  3 00:02:11 2017
 * Do not make changes here, they will be overwritten.
 */

#ifndef AUTO_CONFIG_H_
#define AUTO_CONFIG_H_

#include <Arduino.h>
#include "keycodes.h"

typedef void (*voidFuncPtr)(void);

#define BY0(X,Y) (( X &0x3F)<<2) | (( Y &0x30)>>4)
#define BY1(X,Y) (( X &0x0F)<<4) | (( Y &0x3C)>>2)
#define BY2(X,Y) (( X &0x03)<<6) | ( Y &0x3F)

extern const uint8_t alt_position[];
extern const uint8_t battery_level_pin;
#define BLANK_MAPPING 0
#define FEATHER_M0_BLE
#define CHORD_DELAY 30
#define COLLAPSE_UNKNOWN_DELETIONS
extern const uint8_t column_pins[];
extern const uint8_t ctrl_position[];
#define DEBOUNCE_DELAY 15
#define DEBUG_MESSAGES 0
#define ENABLE_COLOR_FEEDBACK
#define ENABLE_RGB_LED
extern const uint8_t gui_position[];
#define HAS_BATTERY
#define HELD_DELAY 200
#define NUM_ANAGRAMS 3
#define NUM_BYTES_IN_CHORD 3
#define NUM_COLUMNS 8
#define NUM_MATRIX_POSITIONS 24
#define NUM_RGB_LED_PINS 3
#define NUM_ROWS 3
extern const uint8_t rgb_led_pins[];
extern const uint8_t row_pins[];
extern const uint8_t shift_position[];

enum mode_enum{
  DEFAULT_MODE = 0,
  LEFT_HAND_MODE = 1,
};

extern const uint8_t anagram_mask_chord_bytes[][3];

extern const uint8_t anagram_chord_bytes[][3][3];
extern const uint8_t wordmod_capital_chord_bytes[][3];
extern const uint8_t wordmod_nospace_chord_bytes[][3];

enum command_enum{
  COMMAND_CYCLE_ANAGRAM = 0,
  COMMAND_DEFAULT_MODE = 1,
  COMMAND_DELETE_WORD = 2,
  COMMAND_LED_BATTERY = 3,
  COMMAND_LED_COLORS = 4,
  COMMAND_LED_RAINBOW = 5,
  COMMAND_LEFT_HAND_MODE = 6,
  COMMAND_LEFTRIGHT = 7,
  COMMAND_PAUSE = 8,
  COMMAND_STICKY_ALT = 9,
  COMMAND_STICKY_CTRL = 10,
  COMMAND_STICKY_GUI = 11,
  COMMAND_STICKY_SHIFT = 12,
};

extern const uint8_t** command_chord_lookup[];
extern const uint8_t* command_seq_lookup[];
extern const uint8_t** plain_chord_lookup[];
extern const uint8_t* plain_seq_lookup[];
extern const uint8_t** macro_chord_lookup[];
extern const uint8_t* macro_seq_lookup[];
extern const uint8_t** word_chord_lookup[];
extern const uint8_t* word_seq_lookup[];

#if DEBUG_MESSAGES == 0
#define DEBUG1(msg)
#define DEBUG1_LN(msg)
#define DEBUG2(msg)
#define DEBUG2_LN(msg)
#endif

#if DEBUG_MESSAGES == 1
#define DEBUG1(msg) Serial.print(msg)
#define DEBUG1_LN(msg) Serial.println(msg)
#define DEBUG2(msg)
#define DEBUG2_LN(msg)
#endif

#if DEBUG_MESSAGES == 2
#define DEBUG1(msg) Serial.print(msg)
#define DEBUG1_LN(msg) Serial.println(msg)
#define DEBUG2(msg) Serial.print(msg)
#define DEBUG2_LN(msg) Serial.println(msg)
#endif

 
#endif
