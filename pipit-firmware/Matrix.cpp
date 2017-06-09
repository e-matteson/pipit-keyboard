#include "Matrix.h"

VolatileFlag* change_flag = new VolatileFlag(0);

Matrix::Matrix(){
  // milliseconds to wait after the last keypress before entering standby:
  standby_timer = new Timer(100, 0, Timer::MILLISECONDS);
}

void Matrix::setup(){
  // Initialize pin modes for rows and columns of keyboard matrix. The pin modes
  //  shouldn't be set in the constructor, that's might be too early and they
  //  might fail.
  setRowsInput(); // rows should always stay in input mode
  enablePinChangeInterrupt();
}


bool Matrix::get(uint8_t index){
  return pressed[index];
}


void Matrix::pinChangeISR(){
  change_flag->unsafeSet();
}

void Matrix::enablePinChangeInterrupt(){
  setColumnsLow();
  attachRowPinInterrupts(pinChangeISR);
}

void Matrix::disablePinChangeInterrupt(){
  detachRowPinInterrupts();
  setColumnsHiZ();
}

void Matrix::setRowsInput(){
  for(uint8_t r = 0; r != NUM_ROWS; r++){
    pinMode(conf::row_pins[r], INPUT_PULLUP);
  }
}

void Matrix::setColumnsLow(){
  // To prepare for setting pin interrupts, to wake from standby
  for(uint8_t c = 0; c != NUM_COLUMNS; c++){
    pinMode(conf::column_pins[c], OUTPUT);
    digitalWrite(conf::column_pins[c], LOW);
  }
}

void Matrix::setColumnsHiZ(){
  // To prepare for scanning, after waking from standby
  for(uint8_t c = 0; c != NUM_COLUMNS; c++){
    pinMode(conf::column_pins[c], HI_Z);
  }
}

void Matrix::attachRowPinInterrupts(voidFuncPtr isr){
  // uint32_t wakeup_pins = 0;
  for(uint8_t r = 0; r != NUM_ROWS; r++){
    // Triggering on FALLING/RISING/CHANGE requires some clocks, which could be a problem in deep sleep.
    // But it's fine for normal use. Although it seems to trigger as soon as it's attached, if a switch is already down.
    attachInterrupt(digitalPinToInterrupt(conf::row_pins[r]), isr, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(conf::row_pins[r]), isr, LOW);
  }
}

void Matrix::detachRowPinInterrupts(){
  for(uint8_t r = 0; r != NUM_ROWS; r++){
    detachInterrupt(digitalPinToInterrupt(conf::row_pins[r]));
  }
}


void Matrix::enterStandby(){
  enablePinChangeInterrupt();
}

void Matrix::exitStandby(){
  disablePinChangeInterrupt();
  change_flag->unsafeUnset();
  standby_timer->start();
}

bool Matrix::scanIfChanged(){
  // Return true if we scan. Handle entering and exiting standby.

  if(standby_timer->isDisabled()){
    // in standby
    if(change_flag->get()){
      // an interrupt happened since the last scan
      exitStandby();
      scan();
      return 1;
    }
    // nothing happened, don't scan
    return 0;
  }

  if(standby_timer->isDone()){
    // a bunch of time has passed since a switch was pressed - enter standby
    enterStandby();
    return 0;
  }

  // not much time has passed - keep scanning
  scan();
  return 1;
}

void Matrix::scan(){
  // Scan the matrix for pressed switches.
  bool is_any_switch_down = 0;
  int i = 0;
  for (uint8_t c = 0; c != NUM_COLUMNS; c++){
    pinMode(conf::column_pins[c], OUTPUT);
    digitalWrite(conf::column_pins[c], LOW);
    // Wait for digitalWrite to take effect, to avoid weird ghosting problems.
    // The required length can depend on the properties of the ethernet cable.
    delayMicroseconds(10);
    for(uint8_t r = 0; r != NUM_ROWS; r++){
      // Reading is low if the switch is pressed.
      digitalRead(conf::row_pins[r]);
      pressed[i] = (digitalRead(conf::row_pins[r]) == LOW);
      is_any_switch_down |= pressed[i];

        if(pressed[i]){
          printPressedSwitch(c,r);
        }
        i++;
      }
      pinMode(conf::column_pins[c], HI_Z);
    }
    if (is_any_switch_down) {
      standby_timer->start();
    }
}

void Matrix::printPressedSwitch(uint8_t c, uint8_t r){
  // TODO This should get optimized away if DEBUG_MESSAGES < 2, right?
  DEBUG2("pressed: pins (");
  DEBUG2(conf::column_pins[c]);
  DEBUG2(", ");
  DEBUG2(conf::row_pins[r]);
  DEBUG2("), \tindices (");
  DEBUG2(c);
  DEBUG2(", ");
  DEBUG2(r);
  DEBUG2_LN(")");
}
