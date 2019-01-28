#pragma once

#include <stdint.h>
#include "auto_config.h"

// Verify that the user settings match the board we're compiling for
#if defined(TEENSY_LC)
#if !defined(TEENSYDUINO) || !defined(__MKL26Z64__)
#error "Wrong board_name, the arduino IDE did not expect a teensy_lc"
#endif

#else
#error "Unknown board_name"
#endif

#include "Chord.h"
#include "Feedback.h"
#include "Key.h"
#include "Sender.h"
// #include "Switches.h"

class Pipit {
 public:
  void loop();
  void setup();

 private:
  void processIfReady();
  // void shutdownIfSquished();
  void processPress(Chord* new_chord);
  void processGamingSwitches(Chord* switches);

  void doCommand(const Key* keys, uint8_t length);
  void cycleLastWord(CycleType cycle_type);

  uint8_t doIfFound(conf::SeqType type, Chord* chord, Key* keys);
  uint8_t replaceLastIfFound(conf::SeqType type, Chord* chord, Key* keys);
  uint8_t doIfFoundHelper(conf::SeqType type, Chord* chord, Key* keys,
                          bool is_replacement);

  void reuseMods(Chord* chord);

  // Switches switches;
  Feedback feedback;
  Sender sender;

  bool is_paused = 0;
};
