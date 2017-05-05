#include "Switches.h"

Switches::Switches(){
  matrix = new Matrix();

  chord_timer = new Timer(CHORD_DELAY, 0);
  release_timer = new Timer(CHORD_DELAY, 0);
  held_timer = new Timer(HELD_DELAY, 0);

  for(uint8_t i = 0; i != NUM_MATRIX_POSITIONS; i++){
    switch_status[i] = Switches::NOT_PRESSED;
    debounce_press_timers[i] = new Timer(DEBOUNCE_DELAY, 0);
    debounce_release_timers[i] = new Timer(DEBOUNCE_DELAY, 0);
  }
}

void Switches::update(){
  matrix->scanIfChanged();
  updateSwitchStatuses();
  checkForHeldSwitches();
}

void Switches::setup(){
  matrix->setup();
}


bool Switches::readyToPress(){
  return chord_timer->isDone();
}

bool Switches::readyToRelease(){
  return release_timer->isDone();
}

void Switches::updateSwitchStatuses(){

  // printStatusArray();
  // printStatusChange(16);

  is_any_switch_down = 0;
  for(uint8_t i=0; i!=NUM_MATRIX_POSITIONS; i++){
    if(matrix->get(i)){ // Switch is physically down now.
      is_any_switch_down = 1;

      switch(switch_status[i]){ // Old status is:
      case Switches::PRESSED:
      case Switches::ALREADY_SENT:
      case Switches::HELD:
        stopDebouncingRelease(i);
        break;
      case Switches::NOT_PRESSED:
        // Might be a new press, debounce it first
        debouncePress(i);
        break;
      }
    }
    else{ // Switch is physically up now.
      switch(switch_status[i]){ //Old status is:
      case Switches::ALREADY_SENT:
      case Switches::HELD:
        debounceRelease(i);
        break;
      case Switches::NOT_PRESSED:
        stopDebouncingPress(i);
        break;
      case Switches::PRESSED:
        if(debounceRelease(i)){
          // Switch was quickly tapped and released, before the chord timer even ran out.
          // Change status back to PRESSED, after debounceRelease set it to NOT_PRESSED.
          switch_status[i] = Switches::PRESSED;
          // Force a send during this loop iteration.
          chord_timer->forceDone();
        }
        break;
      }
    }
  }
}

bool Switches::debouncePress(uint8_t switch_index){
  // Maybe it's a new press, debounce it first.
  // Count down from DEBOUNCE_DELAY to 0.
  bool is_debounce_done = 0;
  if(debounce_press_timers[switch_index]->isDisabled()){
    // Start debouncing, don't change status.
    debounce_press_timers[switch_index]->start();
  }
  else if(debounce_press_timers[switch_index]->isDone()){
    // Debounce done, it's a real press!
    switch_status[switch_index] = Switches::PRESSED;
    debounce_press_timers[switch_index]->disable();
    chord_timer->start();
    held_timer->start();
    // Check if the switch was double tapped.
    was_switch_double_tapped |= (switch_index == last_released_switch);
    last_released_switch = NO_SWITCH;

    is_debounce_done = 1;
  }
  // Else, keep debdownouncing, don't change status.
  return is_debounce_done;
}

bool Switches::debounceRelease(uint8_t switch_index){
  // Maybe it's a new release, debounce it first.
  // Count down from DEBOUNCE_DELAY to 0.
  bool is_debounce_done = 0;
  if(debounce_release_timers[switch_index]->isDisabled()){
    // Start debouncing, don't change status.
    debounce_release_timers[switch_index]->start();
  }
  else if(debounce_release_timers[switch_index]->isDone()){
    // Debouncing done, it's a real release.
    debounce_release_timers[switch_index]->disable();
    switch_status[switch_index] = Switches::NOT_PRESSED;
    last_released_switch = switch_index;
    release_timer->start();
    held_timer->start();
    is_debounce_done = 1;
  }
  // Else, keep debouncing, don't change status.
  return is_debounce_done;
}

void Switches::stopDebouncingPress(uint8_t i){
  // It was not a real press.
  debounce_press_timers[i]->disable();
}

void Switches::stopDebouncingRelease(uint8_t i){
  // It was not a real release.
  debounce_release_timers[i]->disable();
}

// void Switches::resetInactivityTimers(){
//   // Call this when something changes, to reset all the timers that care about changes.
//   timers->setHeld(HELD_DELAY);
//   // timers->setDoze(DOZE_DELAY);
// }

void Switches::checkForHeldSwitches(){
  // If any switches have been held for a while,
  //  or 1 switch in a chord was released and re-pressed:
  //  let the held switches be reused in future chords.

  // always re-use modifers here?
  if(held_timer->isDone()){
    held_timer->disable();
    reuseHeldSwitches();
  }
  if(was_switch_double_tapped){
    was_switch_double_tapped = 0;
    reuseHeldSwitches();
  }
}

void Switches::reuseHeldSwitches(){
  // If any switches have been held down for a while, let them be re-used
  //  in future chords.
  for(uint8_t i = 0; i!= NUM_MATRIX_POSITIONS; i++){
    if(switch_status[i] == Switches::ALREADY_SENT){
      switch_status[i] = Switches::HELD;
    }
  }
}

void Switches::makeChordBytes(Chord* chord){
  // Binary-encode the values of the switch_status array into an array of bytes,
  //  for easy comparison to the bytes in the lookup arrays.
  // Also, update switch_status values from PRESSED -> ALREADY_SENT or HELD.
  uint8_t index = 0;
  uint8_t chord_bytes [NUM_BYTES_IN_CHORD] = {0};
  for(uint8_t byte_num = 0; byte_num != NUM_BYTES_IN_CHORD; byte_num++){
    // For each byte:
    for(uint8_t bit_num = 0; bit_num != 8; bit_num++){
      // For each bit/switch:
      if (switch_status[index] == Switches::PRESSED || switch_status[index] == Switches::HELD){
        // Switch is pressed! Set bit high.
        chord_bytes[byte_num] |= 1<<bit_num;
        // Modify the status array to record that the switches have been processed.
        if(switch_status[index] == Switches::PRESSED){
          // Let modifiers be immediately re-used in future chords.
          // TODO document this special case
          // TODO multi-switch mods? what if those switches are also used in macros? trigger this from pipit, after plain-key recognition?
          switch_status[index] = isModifier(index, chord->getMode()) ?
            Switches::HELD : Switches::ALREADY_SENT;
        }
      }
      index++;
      if(index == NUM_MATRIX_POSITIONS){
        chord->setChordArray(chord_bytes);
        return;
      }
    }
  }
}

bool Switches::isModifier(uint8_t switch_index, mode_enum mode){
  return ((switch_index == shift_position[mode]) ||
          (switch_index == alt_position[mode])  ||
          (switch_index == ctrl_position[mode])  ||
          (switch_index == gui_position[mode]));
}

void Switches::printStatusArray(){
  //for debugging
  Serial.print("status: ");
  for(uint8_t i = 0; i != NUM_MATRIX_POSITIONS; i++){
    Serial.print(switch_status[i]);
    Serial.print(" ");
  }
  Serial.println("");
}


void Switches::printStatusChange(uint8_t index){
  // Print the new status of a particular key every time it changes
  static switch_status_enum old_val = Switches::NOT_PRESSED;
  switch_status_enum val = switch_status[index];
    if (val != old_val){
      Serial.println(val);
      old_val = val;
    }
}

void Switches::printMatrixChange(uint8_t index){
  // Print whether a particular key is physically up or down, every time it changes
  static bool old_val = 0;
  bool val = matrix->get(index);
  if (val != old_val){
    Serial.println(val);
    old_val = val;
  }
}

bool Switches::isActive(){
  return is_any_switch_down;
}

// void Switches::attachPinInterrupts(voidFuncPtr isr){
//   matrix->setAllColumnsLow();
//   matrix->attachRowPinInterrupts(isr);
// }

// void Switches::detachPinInterrupts(){
//   matrix->detachRowPinInterrupts();
//   matrix->setAllColumnsHiZ();
// }

