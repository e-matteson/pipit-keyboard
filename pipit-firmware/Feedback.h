#ifndef FEEDBACK_H_
#define FEEDBACK_H_

#include <stdint.h>

#include "auto_config.h"

#include "Battery.h"
#include "Timer.h"

// Possible routines for the rgb led:
enum class LEDRoutine {
  None = 0,
  Battery,
  Boot,
  BleNoConnection,
  BleTxpower,
  BleRssi,
  Flymacro,
  FlashGreen,
  FlashRed,
  PlainFeedback,
  MacroFeedback,
  WordFeedback,
  UnknownFeedback,
  NoAnagramFeedback,
  CommandFeedback,
  Warning,
  ToggleWireless,
  Test,
  AllColors,
  Rainbow,
};

class Feedback {
 public:
  void setup();
  void trigger(conf::SeqType type);
  void triggerUnknown();
  void triggerCyclingFailed();
  void updateLED();
  void startRoutine(LEDRoutine routine);
  void endRoutine();

 private:
  // Pre-defined colors for the rgb led
  // TODO make private?
  // The all_colors_routine relies on the fact that these are numbered in order
  // starting at zero, and BLACK is the last color.
  enum class LEDColor {
    Red = 0,
    Orange,
    Yellow,
    Green,
    Teal,
    Blue,
    DimBlue,
    Purple,
    Magenta,
    White,
    Black,
    NumColors,  // this should always come last
  };

  void triggerFeedback(char feedback_code);
  void triggerAudioFeedback(char feedback_code);
  void triggerLEDFeedback(LEDRoutine routine);
  void setLEDColor(LEDColor color);
  void setLEDRGB(uint8_t red, uint8_t green, uint8_t blue);

  Battery battery;
  Timer led_timer;

  LEDRoutine led_routine = LEDRoutine::None;  // The active LED routine
  uint16_t led_subroutine = 0;                // The active LED subroutine
};

#endif
