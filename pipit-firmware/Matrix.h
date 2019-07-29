#pragma once

#include <stdint.h>

#include "BitArray.h"
#include "VolatileFlag.h"
#include "auto_config.h"

// Use input without pullup as high-impedance state
#define HI_Z INPUT

class Matrix {
 public:
  Matrix();
  void setup();

  void readRows();
  void selectColumn(uint8_t column_index);
  void unselectColumn(uint8_t column_index);
  uint8_t get(uint8_t switch_index);
  bool any(uint8_t switch_index);
  bool none(uint8_t switch_index);
  void clear(uint8_t switch_index);

  void enterStandby(voidFuncPtr isr);
  void exitStandby();

 private:
  uint8_t columnIndexToPin(uint8_t column_index);
  void setRowsInput();
  void setColumnsLow();
  void setColumnsHiZ();
  void attachRowPinInterrupts(voidFuncPtr isr);
  void detachRowPinInterrupts();

  volatile uint8_t readings[NUM_MATRIX_POSITIONS] = {0};
};
