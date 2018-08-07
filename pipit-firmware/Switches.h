#ifndef SWITCHES_H
#define SWITCHES_H

#include "auto_config.h"
#include <Arduino.h>
#include "Timer.h"
#include "Chord.h"
#include "Matrix.h"

// Possible value of last_released_switch:
// (also all positive values up to NUM_MATRIX_POSITIONS)
#define NO_SWITCH -1

// Possible statuses for the switch_status array:

class Switches{
public:

  Switches();
  void setup();
  void update();
  void fillChord(Chord* chord);
  uint8_t fillGamingSwitches(Chord* chords);
  bool readyToPress(bool is_gaming);
  bool readyToRelease(bool is_gaming);
  bool anySwitchDown();
  void reuseMods(Chord* chord);

  void printStatusArray();

  Matrix matrix;

private:
  enum SwitchStatusEnum{
                        NOT_PRESSED = 0, // not currently pressed
                        PRESSED,         // pressed and not sent yet
                        ALREADY_SENT,    // already sent, don't resend in future chords
                        HELD             // already sent, but ok to resend in future chords
  };

  void checkForHeldSwitches();
  void updateSwitchStatuses();
  bool debouncePress(uint8_t switch_index);
  bool debounceRelease(uint8_t switch_index);
  void stopDebouncing(uint8_t i);
  void resetInactivityTimers();
  void reuseHeldSwitches();

  void printStatusChange(uint8_t index);
  void printMatrixChange(uint8_t index);


  Timer chord_timer;
  Timer release_timer;
  Timer held_timer;

  // We're now using the same timers for both press and release.
  // Will that always work? Why did we decide to have separate ones before?
  Timer debounce_timers[NUM_MATRIX_POSITIONS];
  SwitchStatusEnum switch_status[NUM_MATRIX_POSITIONS] = {Switches::NOT_PRESSED};
  bool was_switch_double_tapped = 0;
  int16_t last_released_switch = NO_SWITCH; // Index of last released switch, or NO_SWITCH

};

#endif
