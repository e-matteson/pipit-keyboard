#include "Switches.h"


Switches::Switches(){
  chord_timer.setDefaultValue(CHORD_DELAY);
  release_timer.setDefaultValue(CHORD_DELAY);
  held_timer.setDefaultValue(HELD_DELAY);

  for(uint8_t i = 0; i != NUM_MATRIX_POSITIONS; i++){
    debounce_timers[i].setDefaultValue(DEBOUNCE_DELAY);
  }
}

void Switches::update(){
  matrix.scanIfChanged();
  updateSwitchStatuses();
  checkForHeldSwitches();
}

void Switches::setup(){
  matrix.setup();
}

bool Switches::readyToPress(bool is_gaming){
  if(!is_gaming){
    return chord_timer.isDone();
  }

  // If gaming, ignore chord timers and everything else.
  // Just check if anything changed since we last checked.
  if(!chord_timer.isDisabled() || !release_timer.isDisabled()){
    chord_timer.disable();
    release_timer.disable();
    return true; // Changed! Ready.
  }
  return false; // No change.
}

bool Switches::readyToRelease(bool is_gaming){
  if(is_gaming){
    return false; // Gaming mode only uses readyToPress()
  }
  return release_timer.isDone();
}

void Switches::updateSwitchStatuses(){
  for(uint8_t i=0; i!=NUM_MATRIX_POSITIONS; i++){
    if(matrix.getSwitch(i)){ // Switch is physically down now.
      switch(switch_status[i]){ // Old status is:
      case Switches::PRESSED:
      case Switches::ALREADY_SENT:
      case Switches::HELD:
        // If we were debouncing a release, stop, it wasn't real.
        stopDebouncing(i);
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
        // Might be a new release, debounce it first
        debounceRelease(i);
        break;
      case Switches::NOT_PRESSED:
        // If we were debouncing a press, stop, it wasn't real.
        stopDebouncing(i);
        break;
      case Switches::PRESSED:
        if(debounceRelease(i)){
          // Switch was quickly tapped and released, before the chord timer even ran out.
          // Change status back to PRESSED, after debounceRelease set it to NOT_PRESSED.
          // TODO how might this interact with the bouncy-switch grace period?
          switch_status[i] = Switches::PRESSED;
          // Force a send during this loop iteration.
          chord_timer.forceDone();
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
  if(debounce_timers[switch_index].isDisabled()){
    // Start debouncing, don't change status.
    debounce_timers[switch_index].start();
  }
  else if(debounce_timers[switch_index].isDone()){
    // Debounce done, it's a real press!
    switch_status[switch_index] = Switches::PRESSED;
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

bool Switches::debounceRelease(uint8_t switch_index){
  // Maybe it's a new release, debounce it first.
  // Count down from DEBOUNCE_DELAY to 0.
  bool is_debounce_done = false;
  if(debounce_timers[switch_index].isDisabled()){
    // Start debouncing, don't change status.
    debounce_timers[switch_index].start();
  }
  else if(debounce_timers[switch_index].isDone()){
    // Debouncing done, it's a real release.
    debounce_timers[switch_index].disable();
    switch_status[switch_index] = Switches::NOT_PRESSED;
    last_released_switch = switch_index;
    release_timer.start();
    held_timer.start();
    is_debounce_done = true;
  }
  // Else, keep debouncing, don't change status.
  return is_debounce_done;
}

void Switches::stopDebouncing(uint8_t i){
  // It was not a real press/release.
  debounce_timers[i].disable();
}

void Switches::checkForHeldSwitches(){
  // If any switches have been held for a while,
  //  or 1 switch in a chord was released and re-pressed:
  //  let the held switches be reused in future chords.

  // always re-use modifers here?
  if(held_timer.isDone()){
    held_timer.disable();
    reuseHeldSwitches();
  }
  if(was_switch_double_tapped){
    was_switch_double_tapped = false;
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

void Switches::reuseMods(Chord* chord){
  // Let modifiers be immediately re-used in future chords.
  for(uint8_t m = 0; m < NUM_MODIFIERS; m++){
    if(!chord->hasMod((conf::mod_enum) m)){
      continue;
    }
    const uint8_t* mod_chord = conf::getModChord(chord->getMode(), (conf::mod_enum) m);
    uint8_t i = 0;
    for(uint8_t byte_num = 0; byte_num < NUM_BYTES_IN_CHORD; byte_num++){
      for(uint8_t bit_num = 0; bit_num < 8; bit_num++){
        if(1<<bit_num & mod_chord[byte_num]){
          // This switch was included in the modifier chord, let it be re-used.
          switch_status[i] = Switches::HELD;
        }
        i++;
      }
    }
  }
}

bool Switches::anySwitchDown() {
  for(uint8_t index = 0; index < NUM_MATRIX_POSITIONS; index++){
    if(switch_status[index] != NOT_PRESSED) {
      return true;
    }
  }
  return false;
}

void Switches::fillChord(Chord* chord){
  // Binary-encode the values of the switch_status array into an array of bytes,
  //  for easy comparison to the bytes in the lookup arrays.
  // Also, update switch_status values from PRESSED -> ALREADY_SENT.
  for(uint8_t index = 0; index < NUM_MATRIX_POSITIONS; index++){
    if (switch_status[index] == Switches::PRESSED || switch_status[index] == Switches::HELD){
      // Switch is pressed! Record it in the chord.
      chord->setSwitch(index);
    }
    // Modify the status array to record that the switches have been processed.
    if(switch_status[index] == Switches::PRESSED){
      switch_status[index] = Switches::ALREADY_SENT;
    }
  }
}

// Fill up an array of chords, one for each pressed switch, instead of combining them all into 1 chord like fillChord()
uint8_t Switches::fillGamingSwitches(Chord* chords){
  uint8_t num_chords = 0;
  for(uint8_t index = 0; index < NUM_MATRIX_POSITIONS; index++){
    if (switch_status[index] != Switches::NOT_PRESSED){
      // Switch is basically pressed! Other states don't matter in gaming modes.
      chords[num_chords].setSwitch(index);
      num_chords++;
      switch_status[index] = Switches::ALREADY_SENT;
    }
  }
  return num_chords;
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
  // static SwitchStatusEnum old_val = Switches::NOT_PRESSED;

  // TODO avoid implicit casts between enum and uint8_t?
  static uint8_t old_vals[NUM_MATRIX_POSITIONS] = {0};

  SwitchStatusEnum val = switch_status[index];
    if (val != old_vals[index]){
      Serial.print(index);
      Serial.print(": ");
      Serial.println(val);
      old_vals[index] = val;
    }
}

void Switches::printMatrixChange(uint8_t index){
  // Print whether a particular key is physically up or down, every time it changes
  static bool old_vals[NUM_MATRIX_POSITIONS] = {0};
  bool val = matrix.getSwitch(index);
  if (val != old_vals[index]){
    Serial.print(index);
    Serial.print(": ");
    Serial.println(val ? "  d" : "   u");
    old_vals[index] = val;
  }
}

