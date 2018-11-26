// #pragma once

// #include <stdint.h>
// #include "Chord.h"
// #include "Matrix.h"
// #include "Timer.h"

// // Possible value of last_released_switch:
// // (also all positive values up to NUM_MATRIX_POSITIONS)
// #define NO_SWITCH -1

// // Possible statuses for the switch_status array:

// class Switches {
//  public:
//   Switches();
//   void setup();
//   void update();
//   void fillChord(Chord* chord);
//   uint8_t fillGamingSwitches(Chord* chords);
//   bool readyToPress(bool is_gaming);
//   bool readyToRelease();
//   bool anyDown();
//   void reuseMods(Chord* chord);

//   Matrix matrix;

//  private:
//   // The values of the variants matter! We use bitwise operations to
//   efficiently
//   // change the status of multiple switches at once.
//   enum class SwitchStatus : uint8_t {
//     NotPressed = 0x0,   // not currently pressed
//     Pressed = 0x1,      // pressed and not sent yet
//     AlreadySent = 0x2,  // already sent, don't resend in future chords
//     Held = 0x3,         // already sent, but ok to resend in future chords
//   };

//   // Represent the status of each switch with 2 bits, 1 from each array.
//   struct Statuses {
//     ChordData lsb;  // least significant
//     ChordData msb;  // most significant

//     Switches::SwitchStatus get(size_t index) const;
//     void set(size_t index, Switches::SwitchStatus status);
//     void setHeld(const ChordData& new_held_switches);
//     bool sendable(size_t index) const;
//     void pressedToAlreadySent();
//     void alreadySentToHeld();
//     bool anyDown() const;
//     void writeSendable(ChordData* chord) const;
//     constexpr size_t size() const;
//   };

//   void updateSwitchStatuses();
//   bool debouncePress(uint8_t switch_index);
//   bool debounceRelease(uint8_t switch_index);
//   void stopDebouncing(uint8_t i);
//   void resetInactivityTimers();

//   Timer chord_timer;
//   Timer release_timer;
//   Timer held_timer;

//   // We're now using the same timers for both press and release.
//   // Will that always work? Why did we decide to have separate ones before?
//   Timer debounce_timers[NUM_MATRIX_POSITIONS];
//   Statuses statuses;
//   bool was_switch_double_tapped = 0;

//   // Index of last released switch, or NO_SWITCH
//   int16_t last_released_switch = NO_SWITCH;
// };
