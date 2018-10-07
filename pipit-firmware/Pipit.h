#ifndef PIPIT_H_
#define PIPIT_H_

#include <Arduino.h>
#include "auto_config.h"

// Verify that the user settings match the board we're compiling for
#if defined (TEENSY_LC)
#if !defined (TEENSYDUINO) || !defined(__MKL26Z64__)
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
#include "Key.h"
#include "Switches.h"
#include "lookup.h"
#include "Sender.h"
#include "Feedback.h"

#define MAX_PREFIX_LENGTH 3


class Pipit{

public:

  void loop();
  void setup();

private:
  void sendIfReady();
  void shutdownIfSquished();
  void processChord(Chord* new_chord);
  void processGamingSwitches(Chord gaming_switches[], uint8_t num_switches);

  void doCommand(const Key* data, uint8_t length);
  void cycleLastWord(CycleType cycle_type);

  uint8_t sendIfFoundHelper(conf::SeqType type, Chord* chord, Key* data, bool delete_first);
  uint8_t sendIfFoundForCycling(conf::SeqType type, Chord* chord, Key* data);
  uint8_t sendIfFound(conf::SeqType type, Chord* chord, Key* data);

  Switches switches;
  Feedback feedback;
  Sender sender;

  conf::Mode mode = conf::Mode::default_mode;
  bool is_paused = 0;
};

#endif
