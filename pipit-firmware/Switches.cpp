#include "Switches.h"

Switches::Switches() {
  chord_timer.setDefaultValue(CHORD_DELAY);
  release_timer.setDefaultValue(CHORD_DELAY);
  held_timer.setDefaultValue(HELD_DELAY);

  for (uint8_t i = 0; i != NUM_MATRIX_POSITIONS; i++) {
    debounce_timers[i].setDefaultValue(DEBOUNCE_DELAY);
  }
}

void Switches::update() {
  matrix.scanIfChanged();
  updateSwitchStatuses();
  checkForHeldSwitches();
}

void Switches::setup() { matrix.setup(); }

bool Switches::readyToPress(bool is_gaming) {
  if (!is_gaming) {
    return chord_timer.isDone();
  }

  // If gaming, ignore chord timers and everything else.
  // Just check if anything changed since we last checked.
  if (!chord_timer.isDisabled() || !release_timer.isDisabled()) {
    chord_timer.disable();
    release_timer.disable();
    return true;  // Changed! Ready.
  }
  return false;  // No change.
}

bool Switches::readyToRelease() {
  // Gaming modes never needs to call this, they don't respond to releases.
  return release_timer.isDone();
}

void Switches::updateSwitchStatuses() {
  for (uint8_t i = 0; i != NUM_MATRIX_POSITIONS; i++) {
    if (matrix.getSwitch(i)) {     // Switch is physically down now.
      switch (switch_status[i]) {  // Old status is:
        case SwitchStatus::Pressed:
        case SwitchStatus::AlreadySent:
        case SwitchStatus::Held:
          // If we were debouncing a release, stop, it wasn't real.
          stopDebouncing(i);
          break;
        case SwitchStatus::NotPressed:
          // Might be a new press, debounce it first
          debouncePress(i);
          break;
      }
    } else {                       // Switch is physically up now.
      switch (switch_status[i]) {  // Old status is:
        case SwitchStatus::AlreadySent:
        case SwitchStatus::Held:
          // Might be a new release, debounce it first
          debounceRelease(i);
          break;
        case SwitchStatus::NotPressed:
          // If we were debouncing a press, stop, it wasn't real.
          stopDebouncing(i);
          break;
        case SwitchStatus::Pressed:
          if (debounceRelease(i)) {
            // Switch was quickly tapped and released, before the chord timer
            // even ran out. Change status back to Pressed, after
            // debounceRelease set it to NotPressed.
            // TODO how might this interact with the bouncy-switch grace period?
            switch_status[i] = SwitchStatus::Pressed;
            // Force a send during this loop iteration.
            chord_timer.forceDone();
          }
          break;
      }
    }
  }
}

bool Switches::debouncePress(uint8_t switch_index) {
  // Maybe it's a new press, debounce it first.
  // Count down from DEBOUNCE_DELAY to 0.
  bool is_debounce_done = 0;
  if (debounce_timers[switch_index].isDisabled()) {
    // Start debouncing, don't change status.
    debounce_timers[switch_index].start();
  } else if (debounce_timers[switch_index].isDone()) {
    // Debounce done, it's a real press!
    switch_status[switch_index] = SwitchStatus::Pressed;
    debounce_timers[switch_index].disable();

    chord_timer.start();
    held_timer.start();

    // Check if the switch was double tapped.
    was_switch_double_tapped |= (switch_index == last_released_switch);
    last_released_switch = NO_SWITCH;

    is_debounce_done = 1;
  }
  // Else, keep debouncing, don't change status.
  return is_debounce_done;
}

bool Switches::debounceRelease(uint8_t switch_index) {
  // Maybe it's a new release, debounce it first.
  // Count down from DEBOUNCE_DELAY to 0.
  bool is_debounce_done = false;
  if (debounce_timers[switch_index].isDisabled()) {
    // Start debouncing, don't change status.
    debounce_timers[switch_index].start();
  } else if (debounce_timers[switch_index].isDone()) {
    // Debouncing done, it's a real release.
    debounce_timers[switch_index].disable();
    switch_status[switch_index] = SwitchStatus::NotPressed;
    last_released_switch = switch_index;
    release_timer.start();
    held_timer.start();
    is_debounce_done = true;
  }
  // Else, keep debouncing, don't change status.
  return is_debounce_done;
}

void Switches::stopDebouncing(uint8_t i) {
  // It was not a real press/release.
  debounce_timers[i].disable();
}

void Switches::checkForHeldSwitches() {
  // If any switches have been held for a while,
  //  or 1 switch in a chord was released and re-pressed:
  //  let the held switches be reused in future chords.

  // always re-use modifers here?
  if (held_timer.isDone()) {
    held_timer.disable();
    reuseHeldSwitches();
  }
  if (was_switch_double_tapped) {
    was_switch_double_tapped = false;
    reuseHeldSwitches();
  }
}

void Switches::reuseHeldSwitches() {
  // If any switches have been held down for a while, let them be re-used
  //  in future chords.
  for (uint8_t i = 0; i != NUM_MATRIX_POSITIONS; i++) {
    if (switch_status[i] == SwitchStatus::AlreadySent) {
      switch_status[i] = SwitchStatus::Held;
    }
  }
}

void Switches::reuseMods(Chord* chord) {
  // Let modifiers be immediately re-used in future chords.
  for (uint8_t m = 0; m < NUM_MODIFIERS; m++) {
    if (!chord->hasMod((conf::Mod)m)) {
      continue;
    }
    const ChordData* mod_chord = conf::getModChord(chord->getMode(), (conf::Mod)m);
    uint8_t i = 0;
    for (uint8_t byte : *mod_chord) {
      for (uint8_t bit_num = 0; bit_num < 8; bit_num++) {
        if (1 << bit_num & byte) {
          // This switch was included in the modifier chord, let it be re-used.
          switch_status[i] = SwitchStatus::Held;
        }
        i++;
      }
    }
  }
}

bool Switches::anyDown() {
  for (uint8_t index = 0; index < NUM_MATRIX_POSITIONS; index++) {
    if (switch_status[index] != SwitchStatus::NotPressed) {
      return true;
    }
  }
  return false;
}

void Switches::fillChord(Chord* chord) {
  // Binary-encode the values of the switch_status array into an array of bytes,
  //  for easy comparison to the bytes in the lookup arrays.
  // Also, update switch_status values from Pressed -> AlreadySent.
  for (uint8_t index = 0; index < NUM_MATRIX_POSITIONS; index++) {
    if (switch_status[index] == SwitchStatus::Pressed ||
        switch_status[index] == SwitchStatus::Held) {
      // Switch is pressed! Record it in the chord.
      chord->setSwitch(index);
    }
    // Modify the status array to record that the switches have been processed.
    if (switch_status[index] == SwitchStatus::Pressed) {
      switch_status[index] = SwitchStatus::AlreadySent;
    }
  }
}

// Fill up an array of chords, one for each pressed switch, instead of combining
// them all into 1 chord like fillChord()
uint8_t Switches::fillGamingSwitches(Chord* chords) {
  uint8_t num_pressed = 0;
  for (uint8_t index = 0; index < NUM_MATRIX_POSITIONS; index++) {
    if (switch_status[index] != SwitchStatus::NotPressed) {
      // Switch is basically pressed! Other states don't matter in gaming modes.
      chords[num_pressed].setSwitch(index);
      num_pressed++;
      switch_status[index] = SwitchStatus::AlreadySent;
    }
  }
  return num_pressed;
}

void Switches::printStatusArray() {
  // for debugging
  Serial.print("status: ");
  for (uint8_t i = 0; i != NUM_MATRIX_POSITIONS; i++) {
    Serial.print(static_cast<uint8_t>(switch_status[i]));
    Serial.print(" ");
  }
  Serial.println("");
}

void Switches::printStatusChange(uint8_t index) {
  // Print the new status of a particular key every time it changes
  // TODO avoid implicit casts between enum and uint8_t?
  static SwitchStatus old_vals[NUM_MATRIX_POSITIONS] = {
      SwitchStatus::NotPressed};

  SwitchStatus val = switch_status[index];

  if (val != old_vals[index]) {
    Serial.print(index);
    Serial.print(": ");
    Serial.println(static_cast<uint8_t>(val));
    old_vals[index] = val;
  }
}

void Switches::printMatrixChange(uint8_t index) {
  // Print whether a particular key is physically up or down, every time it
  // changes
  static bool old_vals[NUM_MATRIX_POSITIONS] = {0};
  bool val = matrix.getSwitch(index);
  if (val != old_vals[index]) {
    Serial.print(index);
    Serial.print(": ");
    Serial.println(val ? "  d" : "   u");
    old_vals[index] = val;
  }
}
