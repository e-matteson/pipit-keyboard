#ifndef PROCESSOR_H_
#define PROCESSOR_H_

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


#include "WordHistory.h"
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
  void processChordHelper(Chord* new_chord);

  void resetLastWord();
  void storeLastWord();
  void cycleAnagram();
  int16_t deleteLastWord();
  void handleUnknownDeletion();

  void doSpecialFunction(uint8_t code);


  Switches* switches;
  Lookup* lookup;
  Feedback* feedback;
  Sender* sender;
  WordHistory* wordhistory;
  Chord* chord;
  Chord* saved_chord;
  Comms* comms;

  /***** word anagram cycling *****/
  bool was_last_send_a_word = 0;


  bool is_paused = 0;

  bool is_connected = 0;
  const uint8_t disconnect_readings_threshold = 3;
  uint8_t num_disconnect_readings = disconnect_readings_threshold;
};

#endif
