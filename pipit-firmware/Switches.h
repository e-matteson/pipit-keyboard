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

  enum switch_status_enum{
    NOT_PRESSED = 0, // not currently pressed
    PRESSED,         // pressed and not sent yet
    ALREADY_SENT,    // already sent, don't resend in future chords
    HELD             // already sent, but ok to resend in future chords
  };

  Switches();
  void setup();
  void update();
  void makeChordBytes(Chord* chord);
  void printStatusArray();
  bool isActive();
  bool readyToPress();
  bool readyToRelease();

  void reuseMods(Chord* chord);
  Matrix* matrix;

private:
  void checkForHeldSwitches();
  void updateSwitchStatuses();
  bool debouncePress(uint8_t switch_index);
  bool debounceRelease(uint8_t switch_index);
  void stopDebouncingPress(uint8_t i);
  void stopDebouncingRelease(uint8_t i);
  void resetInactivityTimers();
  void reuseHeldSwitches();
  bool isAnySwitchStillBouncing();
  int32_t maximum(int32_t x, int32_t y);

  void printStatusChange(uint8_t index);
  void printMatrixChange(uint8_t index);


  Timer* chord_timer;
  Timer* release_timer;
  Timer* held_timer;
  Timer* debounce_press_timers[NUM_MATRIX_POSITIONS];
  Timer* debounce_release_timers[NUM_MATRIX_POSITIONS];

  Timer* first_contact_timers[NUM_MATRIX_POSITIONS];

  switch_status_enum switch_status[NUM_MATRIX_POSITIONS] = {(switch_status_enum)0};
  bool was_switch_double_tapped = 0;
  int16_t last_released_switch = NO_SWITCH; // Index of last released switch, or NO_SWITCH
  bool is_any_switch_down = 0;

};

#endif
