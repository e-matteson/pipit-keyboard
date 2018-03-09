#ifndef PIPIT_H_
#define PIPIT_H_

#include <Arduino.h>
#include "auto_config.h"
#include "structs.h"
#include "Chord.h"
#include "Key.h"

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
  void updateConnection();
  void shutdownIfSquished();

  void processChord(Chord* new_chord);
  void processGamingSwitches(Chord gaming_switches[], uint8_t num_switches);

  void doCommand(uint8_t code);

  void cycleLastWordAnagram();
  void cycleLastWordCapital();
  void cycleLastWordNospace();
  void deleteLastWord();
  void move(Motion motion, Direction direction);

  uint8_t sendIfFoundHelper(conf::seq_type_enum type, Chord* chord, Key* data, bool delete_first);
  uint8_t sendIfFoundForCycling(conf::seq_type_enum type, Chord* chord, Key* data);
  uint8_t sendIfFound(conf::seq_type_enum type, Chord* chord, Key* data);

  Switches* switches;
  Lookup* lookup;
  Feedback* feedback;
  Sender* sender;
  Comms* comms;


  conf::mode_enum mode = conf::mode_enum::DEFAULT_MODE;


  // Chord* gaming_chords[NUM_MATRIX_POSITIONS] = {0};

  bool is_paused = 0;

  Timer* loop_timer;
  const uint32_t loop_delay_micros = 500;

  Timer* connection_timer;
  bool is_connected = 0;
  const uint8_t disconnect_readings_threshold = 3;
  uint8_t num_disconnect_readings = disconnect_readings_threshold;

  const uint16_t connection_check_delay_short = 3000;
  const uint16_t connection_check_delay_long = 6000;

};

#endif
