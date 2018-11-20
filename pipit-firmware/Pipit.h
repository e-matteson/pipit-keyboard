#pragma once

#include <stdint.h>
#include "auto_config.h"

// Verify that the user settings match the board we're compiling for
#if defined(TEENSY_LC)
#if !defined(TEENSYDUINO) || !defined(__MKL26Z64__)
#error "Wrong board_name, the arduino IDE did not expect a teensy_lc"
#endif

#elif defined(FEATHER_M0_BLE) || defined(FEATHER_M0_USB)
#ifndef ARDUINO_SAMD_FEATHER_M0
#error "Wrong board_name, the arduino IDE did not expect a feather_m0"
#endif

#else
#error "Unknown board_name"
#endif

#include "Chord.h"
#include "Feedback.h"
#include "Key.h"
#include "Sender.h"
#include "Switches.h"

#define MAX_PREFIX_LENGTH 3

class Pipit {
 public:
  void loop();
  void setup();

 private:
  void processIfReady();
  void shutdownIfSquished();
  void processChord(Chord* new_chord);
  void processGamingSwitches(Chord gaming_switches[], uint8_t num_switches);

  void doCommand(const Key* keys, uint8_t length);
  void cycleLastWord(CycleType cycle_type);

  uint8_t doIfFound(conf::SeqType type, Chord* chord, Key* keys);
  uint8_t replaceLastIfFound(conf::SeqType type, Chord* chord, Key* keys);
  uint8_t doIfFoundHelper(conf::SeqType type, Chord* chord, Key* keys,
                          bool delete_before_sending);

  Switches switches;
  Feedback feedback;
  Sender sender;

  conf::Mode mode = conf::Mode::default_mode;
  bool is_paused = 0;
};
