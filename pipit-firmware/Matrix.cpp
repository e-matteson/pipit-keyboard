#include "Matrix.h"
#include <Arduino.h>
#include "conf.h"

Matrix::Matrix() {}

void Matrix::setup() {
  // Initialize pin modes for rows and columns of keyboard matrix. The pin modes
  // shouldn't be set in the constructor, that might be too early and they
  // might fail.
  setRowsInput();   // rows should always stay in input mode
  setColumnsHiZ();  // columns will change, during scanning and during standby
}

uint8_t Matrix::get(uint8_t switch_index) { return readings[switch_index]; }

void Matrix::clear(uint8_t switch_index) { readings[switch_index] = 0; }

bool Matrix::none(uint8_t switch_index) { return readings[switch_index] == 0; }

bool Matrix::any(uint8_t switch_index) { return !none(switch_index); }

void Matrix::readRows() {
  // Since we only read 1 col of the matrix at a time, remember which
  // switch we're at between calls.
  static uint8_t switch_index = 0;

  for (uint8_t row_pin : conf::row_pins) {
    // Shift in the new reading.
    uint8_t is_pressed = (digitalRead(row_pin) == LOW);
    readings[switch_index] = (readings[switch_index] << 1) | is_pressed;
    switch_index = (switch_index + 1) % NUM_MATRIX_POSITIONS;
  }
}

uint8_t Matrix::columnIndexToPin(uint8_t column_index) {
  return conf::column_pins[column_index];
}

void Matrix::selectColumn(uint8_t column_index) {
  uint8_t column_pin = columnIndexToPin(column_index);
  pinMode(column_pin, OUTPUT);
  digitalWrite(column_pin, LOW);
}

void Matrix::unselectColumn(uint8_t column_index) {
  uint8_t column_pin = columnIndexToPin(column_index);
  pinMode(column_pin, HI_Z);
}

void Matrix::setRowsInput() {
  for (uint8_t pin : conf::row_pins) {
    pinMode(pin, INPUT_PULLUP);
  }
}

void Matrix::setColumnsLow() {
  // To prepare for setting pin interrupts, to wake from standby
  for (uint8_t i = 0; i < conf::column_pins.size(); i++) {
    selectColumn(i);
  }
}

void Matrix::setColumnsHiZ() {
  // To prepare for scanning, after waking from standby
  for (uint8_t i = 0; i < conf::column_pins.size(); i++) {
    unselectColumn(i);
  }
}
