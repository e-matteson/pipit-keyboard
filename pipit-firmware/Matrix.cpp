#include "Matrix.h"

VolatileFlag change_flag(0);

Matrix::Matrix(){
  // milliseconds to wait since the last keypress before entering standby:
  standby_timer.setDefaultValue(100);
  // milliseconds to wait before deciding that a switch is probably squished down inside a backpack:
  squished_switch_timer.setDefaultValue(60000);
}

void Matrix::setup(){
  // Initialize pin modes for rows and columns of keyboard matrix. The pin modes
  // shouldn't be set in the constructor, that might be too early and they
  // might fail.
  setRowsInput(); // rows should always stay in input mode
  setColumnsHiZ(); // columns will change, during scanning and during standby

#ifdef USE_STANDBY_INTERRUPTS
  enterStandby();
#endif
}

bool Matrix::scanIfChanged(){
  // Return true if we scan. Handle entering and exiting standby.

#ifdef USE_STANDBY_INTERRUPTS
  if(standby_timer.isDone()){
    // A bunch of time has passed since a switch was pressed
    enterStandby();
    return false;
  }
  if(isInStandby()){
    if(!change_flag.get()){
      // Nothing happened, don't scan
      return false;
    }
    // A pin-change interrupt happened since the last scan!
    exitStandby();
  }
#endif

  // If not using standby interrupts, we don't know when there was a change, so
  // always scan.
  scan();
  return true;
}

void Matrix::scan(){
  // Scan the matrix for pressed switches.
  switch_states = 0;
  bool is_any_switch_down = false;
  uint8_t switch_index = 0;
  for(uint8_t h = 0; h != NUM_HANDS; h++){
    for (uint8_t c = 0; c != NUM_COLUMNS; c++){
      selectColumn(h, c);
      for(uint8_t r = 0; r != NUM_ROWS; r++){
        if(isRowPressed(h, r)){
          setSwitch(switch_index);
          is_any_switch_down = true;
          printPressedSwitch(h, c, r);
        }
        switch_index++;
      }
      unselectColumn(h,c);
    }
  }

#ifdef USE_STANDBY_INTERRUPTS
  if (is_any_switch_down) {
    standby_timer.start();
  }
#endif
}

bool Matrix::isRowPressed(uint8_t hand, uint8_t row){
  // Reading is low if the switch is pressed.
  return (digitalRead(conf::row_pins[hand][row]) == LOW);
}

void Matrix::selectColumn(uint8_t hand, uint8_t column){
  pinMode(conf::column_pins[hand][column], OUTPUT);
  digitalWrite(conf::column_pins[hand][column], LOW);

  // Wait for digitalWrite to take effect, to avoid weird ghosting problems.
  // The required length can depend on the properties of the ethernet cable.
  delayMicroseconds(10);
}

void Matrix::unselectColumn(uint8_t hand, uint8_t column){
  pinMode(conf::column_pins[hand][column], HI_Z);
}

bool Matrix::getSwitch(uint8_t index) const{
  return 0x1 & (switch_states >> index);
}

void Matrix::setSwitch(uint8_t index) {
  switch_states |= (0x1 << index);
}


void Matrix::setRowsInput(){
  for(uint8_t h = 0; h != NUM_HANDS; h++){
    for(uint8_t r = 0; r != NUM_ROWS; r++){
      pinMode(conf::row_pins[h][r], INPUT_PULLUP);
    }
  }
}

void Matrix::setColumnsLow(){
  // To prepare for setting pin interrupts, to wake from standby
  for(uint8_t h = 0; h != NUM_HANDS; h++){
    for(uint8_t c = 0; c != NUM_COLUMNS; c++){
      selectColumn(h,c);
    }
  }
}

void Matrix::setColumnsHiZ(){
  // To prepare for scanning, after waking from standby
  for(uint8_t h = 0; h != NUM_HANDS; h++){
    for(uint8_t c = 0; c != NUM_COLUMNS; c++){
      unselectColumn(h, c);
    }
  }

}

void Matrix::attachRowPinInterrupts(voidFuncPtr isr){
  for(uint8_t h = 0; h != NUM_HANDS; h++){
    for(uint8_t r = 0; r != NUM_ROWS; r++){
      // Triggering on FALLING/RISING/CHANGE requires some clocks, which could be a problem in deep sleep.
      // But it's fine for normal use. Although it seems to trigger as soon as it's attached, if a switch is already down.
      attachInterrupt(digitalPinToInterrupt(conf::row_pins[h][r]), isr, CHANGE);
      // attachInterrupt(digitalPinToInterrupt(conf::row_pins[h][r]), isr, LOW);
    }
  }
}

void Matrix::detachRowPinInterrupts(){
  for(uint8_t h = 0; h != NUM_HANDS; h++){
    for(uint8_t r = 0; r != NUM_ROWS; r++){
      detachInterrupt(digitalPinToInterrupt(conf::row_pins[h][r]));
    }
  }
}

void Matrix::pinChangeISR(){
  change_flag.unsafeSet();
}

void Matrix::enablePinChangeInterrupt(){
  setColumnsLow();
  attachRowPinInterrupts(pinChangeISR);
}

void Matrix::disablePinChangeInterrupt(){
  detachRowPinInterrupts();
  setColumnsHiZ();
}

void Matrix::enterStandby(){
  squished_switch_timer.disable();
  enablePinChangeInterrupt();
}

void Matrix::exitStandby(){
  disablePinChangeInterrupt();
  change_flag.unsafeUnset();
  standby_timer.start();
  squished_switch_timer.start();
}

bool Matrix::isInStandby(){
#ifdef USE_STANDBY_INTERRUPTS
  return standby_timer.isDisabled();
#endif

  return false;
}

bool Matrix::isSquishedInBackpack(){
  return squished_switch_timer.isDone();
}

void Matrix::shutdown(){
  setColumnsHiZ();
}

void Matrix::printPressedSwitch(uint8_t hand, uint8_t column, uint8_t row){
  DEBUG2("pressed: pins (");
  DEBUG2(conf::column_pins[hand][column]);
  DEBUG2(", ");
  DEBUG2(conf::row_pins[hand][row]);
  DEBUG2("), \tindices (");
  DEBUG2(column);
  DEBUG2(", ");
  DEBUG2(row);
  DEBUG2_LN(")");
}
