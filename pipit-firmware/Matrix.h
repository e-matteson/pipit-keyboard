#pragma once

#include <stdint.h>

#include "BitArray.h"
#include "Timer.h"
#include "VolatileFlag.h"
#include "auto_config.h"

// Use input without pullup as high-impedance state
#define HI_Z INPUT

class Matrix {
 public:
  Matrix();
  void setup();

  bool isDown(uint8_t index) const;

  bool scanIfChanged();
  bool isSquishedInBackpack();
  void shutdown();

 private:
  void scan();
  void selectColumn(uint8_t column_pin);
  void unselectColumn(uint8_t column_pin);
  bool isRowPressed(uint8_t row_pin);

  bool isInStandby();
  void enterStandby();
  void exitStandby();

  void enablePinChangeInterrupt();
  void disablePinChangeInterrupt();

  void setRowsInput();
  void setColumnsLow();
  void setColumnsHiZ();
  void attachRowPinInterrupts(voidFuncPtr isr);
  void detachRowPinInterrupts();

  static void pinChangeISR();

  Timer standby_timer;
  Timer squished_switch_timer;

  BitArray<uint32_t, NUM_MATRIX_POSITIONS> switches_down;
};
