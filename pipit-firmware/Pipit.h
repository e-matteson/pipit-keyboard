#ifndef PIPIT_H_
#define PIPIT_H_

#include <Arduino.h>
#include "auto_config.h"

// Verify that the user settings match the board we're compiling for

#if defined (TEENSY_LC)
#if !defined (TEENSYDUINO) || !defined(__MKL26Z64__)
#error "Wrong board_name, this is not a teensy_lc"
#endif

#elif defined(FEATHER_M0_BLE)
#ifndef ARDUINO_SAMD_FEATHER_M0
#error "Wrong board_name, this is not a feather_m0_ble"
#endif

#else
#error "Unknown board_name"
#endif


#include "Switches.h"
#include "Lookup.h"
#include "Sender.h"
#include "Feedback.h"

#include "Comms.h"

#define MAX_PREFIX_LENGTH 3

class Pipit{

public:
  Pipit();

  void loop();
  void setup();

private:
  void sendIfReady();
  // void updateConnection();

  void processChord(Chord* new_chord);

  void doCommand(uint8_t code);

  void cycleLastWord();
  void deleteLastWord();
  void move(Motion motion, Direction direction);

  Switches* switches;
  Lookup* lookup;
  Feedback* feedback;
  Sender* sender;
  Comms* comms;


  conf::mode_enum mode = conf::mode_enum::DEFAULT_MODE;

  bool is_paused = 0;

  Timer* connection_timer;
  bool is_connected = 0;
  const uint8_t disconnect_readings_threshold = 3;
  uint8_t num_disconnect_readings = disconnect_readings_threshold;
};

#endif
