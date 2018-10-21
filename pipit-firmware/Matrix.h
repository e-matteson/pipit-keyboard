#pragma once

#include <stdint.h>

#include "Timer.h"
#include "VolatileFlag.h"
#include "auto_config.h"

// Use input without pullup as high-impedance state
#define HI_Z INPUT

class Matrix {
 public:
  Matrix();
  void setup();

  bool getSwitch(uint8_t index) const;

  bool scanIfChanged();
  bool isSquishedInBackpack();
  void shutdown();

 private:
  void setSwitch(uint8_t index);

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

  // Each bit stores whether one switch is pressed. Make sure 32 bits is enough
  // for all the scanned matrix positions.
  // TODO automatically use uint64_t when necessary? what are the implications for a 32bit mcu?
#if NUM_MATRIX_POSITIONS > 32
#error "Too many rows and columns, increase `switch_states` storage size in Matrix.h"
#endif
  uint32_t switch_states = 0;
};
