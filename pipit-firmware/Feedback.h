#ifndef FEEDBACK_H_
#define FEEDBACK_H_

#include <Arduino.h>
#include "auto_config.h"

#include "Battery.h"
#include "Timer.h"

// Possible routines for the rgb led:
enum led_routine_enum{
  NO_ROUTINE = 0,
  BATTERY_ROUTINE,
  BOOT_ROUTINE,
  BLE_NO_CONNECTION_ROUTINE,
  BLE_TXPOWER_ROUTINE,
  BLE_RSSI_ROUTINE,
  FLYMACRO_ROUTINE,
  FLASH_GREEN_ROUTINE,
  FLASH_RED_ROUTINE,
  PLAIN_FEEDBACK_ROUTINE,
  MACRO_FEEDBACK_ROUTINE,
  WORD_FEEDBACK_ROUTINE,
  UNKNOWN_FEEDBACK_ROUTINE,
  NO_ANAGRAM_FEEDBACK_ROUTINE,
  COMMAND_FEEDBACK_ROUTINE,
  WARNING_ROUTINE,
  SHUTDOWN_ROUTINE,
  TEST_ROUTINE,
  ALL_COLORS_ROUTINE,
  RAINBOW_ROUTINE,
};

// Pre-defined colors for the rgb led
// TODO make private?
// The all_colors_routine relies on the fact that these are numbered in order starting at zero, and BLACK is the last color.
enum led_color_enum{
  RED = 0,
  ORANGE,
  YELLOW,
  GREEN,
  TEAL,
  BLUE,
  DIM_BLUE,
  PURPLE,
  MAGENTA,
  WHITE,
  BLACK,
};



class Feedback{

public:

  Feedback();

  void triggerPlain();
  void triggerMacro();
  void triggerWord();
  void triggerCommand();
  void triggerUnknown();
  void triggerNoAnagram();
  void updateLED();
  void startRoutine(led_routine_enum routine);
  void endRoutine();
  void setLEDColor(led_color_enum color);

private:
  void triggerFeedback(char feedback_code);
  void triggerAudioFeedback(char feedback_code);
  void triggerLEDFeedback(led_routine_enum routine);
  void setLEDRGB(uint8_t red, uint8_t green, uint8_t blue);

  Battery* battery;
  Timer* led_timer;
  // Timer led_timer(1000, 0);
  led_routine_enum led_routine = NO_ROUTINE; // The active LED routine
  uint16_t led_subroutine = 0; // The active LED subroutine
  uint8_t battery_pin;

};

#endif
