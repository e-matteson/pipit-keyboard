#ifndef SCANNER_H_
#define SCANNER_H_

#include <Arduino.h>
#include "auto_config.h"
#include "VolatileFlag.h"
#include "Timer.h"


// Use input without pullup as high-impedance state
#define HI_Z INPUT


class Matrix{
public:
  Matrix();
  bool get(uint8_t index);
  void setup();

  bool scanIfChanged();


private:

  void scan();
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

  void printPressedSwitch(uint8_t c, uint8_t r);

  Timer* standby_timer;

  bool pressed [NUM_MATRIX_POSITIONS] = {0};

};

#endif
