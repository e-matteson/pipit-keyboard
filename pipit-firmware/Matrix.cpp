#include "Matrix.h"
#include <Arduino.h>

VolatileFlag change_flag(0);

Matrix::Matrix() {
  // milliseconds to wait since the last keypress before entering standby:
  standby_timer.setDefaultValue(100);
  // milliseconds to wait before deciding that a switch is probably squished
  // down inside a backpack:
  squished_switch_timer.setDefaultValue(60000);
}

void Matrix::setup() {
  // Initialize pin modes for rows and columns of keyboard matrix. The pin modes
  // shouldn't be set in the constructor, that might be too early and they
  // might fail.
  setRowsInput();   // rows should always stay in input mode
  setColumnsHiZ();  // columns will change, during scanning and during standby

  if (conf::USE_STANDBY_INTERRUPTS){
    enterStandby();
  }
}

bool Matrix::scanIfChanged() {
  // Return true if we scan. Handle entering and exiting standby.

  if (conf::USE_STANDBY_INTERRUPTS){
    if (standby_timer.isDone()) {
      // A bunch of time has passed since a switch was pressed
      enterStandby();
      return false;
    }
    if (isInStandby()) {
      if (!change_flag.get()) {
        // Nothing happened, don't scan
        return false;
      }
      // A pin-change interrupt happened since the last scan!
      exitStandby();
    }
  }

  // If not using standby interrupts, we don't know when there was a change, so
  // always scan.
  scan();
  return true;
}

void Matrix::scan() {
  // Scan the matrix for pressed switches.
  // TODO is it more efficient to set LSB then <<=1 on every iteration?
  switch_states = 0;
  bool is_any_switch_down = false;
  uint8_t switch_index = 0;
  for(uint8_t col_pin : conf::column_pins) {
    selectColumn(col_pin);
    for(uint8_t row_pin : conf::row_pins) {
      if (isRowPressed(row_pin)) {
        setSwitch(switch_index);
        is_any_switch_down = true;
      }
      switch_index++;
    }
    unselectColumn(col_pin);
  }

  if (conf::USE_STANDBY_INTERRUPTS && is_any_switch_down) {
    standby_timer.start();
  }
}

bool Matrix::isRowPressed(uint8_t row_pin) {
  // Reading is low if the switch is pressed.
  return (digitalRead(row_pin) == LOW);
}

void Matrix::selectColumn(uint8_t column_pin) {
  pinMode(column_pin, OUTPUT);
  digitalWrite(column_pin, LOW);

  // Wait for digitalWrite to take effect, to avoid weird ghosting problems.
  // The required length can depend on the properties of the ethernet cable.
  delayMicroseconds(10);
}

void Matrix::unselectColumn(uint8_t column_pin) {
  pinMode(column_pin, HI_Z);
}

bool Matrix::isDown(uint8_t index) const {
  return 0x1 & (switch_states >> index);
}

void Matrix::setSwitch(uint8_t index) { switch_states |= (0x1 << index); }

void Matrix::setRowsInput() {
  for (uint8_t pin : conf::row_pins) {
    pinMode(pin, INPUT_PULLUP);
  }
}

void Matrix::setColumnsLow() {
  // To prepare for setting pin interrupts, to wake from standby
  for(uint8_t pin : conf::column_pins) {
    selectColumn(pin);
  }
}

void Matrix::setColumnsHiZ() {
  // To prepare for scanning, after waking from standby
  for(uint8_t pin : conf::column_pins) {
    unselectColumn(pin);
  }
}

void Matrix::attachRowPinInterrupts(voidFuncPtr isr) {
  for (uint8_t pin : conf::row_pins) {
      // Triggering on FALLING/RISING/CHANGE requires some clocks, which could
      // be a problem in deep sleep. But it's fine for normal use. Although it
      // seems to trigger as soon as it's attached, if a switch is already down.
      attachInterrupt(digitalPinToInterrupt(pin), isr, CHANGE);
    }
}

void Matrix::detachRowPinInterrupts() {
  for (uint8_t pin : conf::row_pins) {
    detachInterrupt(digitalPinToInterrupt(pin));
  }
}

void Matrix::pinChangeISR() { change_flag.unsafeSet(); }

void Matrix::enablePinChangeInterrupt() {
  setColumnsLow();
  attachRowPinInterrupts(pinChangeISR);
}

void Matrix::disablePinChangeInterrupt() {
  detachRowPinInterrupts();
  setColumnsHiZ();
}

void Matrix::enterStandby() {
  squished_switch_timer.disable();
  enablePinChangeInterrupt();
}

void Matrix::exitStandby() {
  disablePinChangeInterrupt();
  change_flag.unsafeUnset();
  standby_timer.start();
  squished_switch_timer.start();
}

bool Matrix::isInStandby() {
  if (conf::USE_STANDBY_INTERRUPTS) {
    return standby_timer.isDisabled();
  }
  return false;
}

bool Matrix::isSquishedInBackpack() { return squished_switch_timer.isDone(); }

void Matrix::shutdown() { setColumnsHiZ(); }

// void Matrix::printPressedSwitch(uint8_t hand, uint8_t column, uint8_t row) {
//   DEBUG2("pressed: pins (");
//   DEBUG2(conf::column_pins[hand][column]);
//   DEBUG2(", ");
//   DEBUG2(conf::row_pins[hand][row]);
//   DEBUG2("), \tindices (");
//   DEBUG2(column);
//   DEBUG2(", ");
//   DEBUG2(row);
//   DEBUG2_LN(")");
// }
