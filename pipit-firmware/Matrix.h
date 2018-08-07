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
  void setup();

  bool getSwitch(uint8_t index) const;

  bool scanIfChanged();
  bool isSquishedInBackpack();
  void shutdown();

private:
  void setSwitch(uint8_t index);

  void scan();
  void selectColumn(uint8_t hand, uint8_t column);
  void unselectColumn(uint8_t hand, uint8_t column);
  bool isRowPressed(uint8_t hand, uint8_t row);

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

  void printPressedSwitch(uint8_t h, uint8_t c, uint8_t r);

  Timer standby_timer;
  Timer squished_switch_timer;

  // Each bit stores whether one switch is pressed. Make sure 32 bits is enough
  // for all the scanned matrix positions.
#if NUM_MATRIX_POSITIONS > 32
#error "Too many rows and columns, increase `pressed` storage size in Matrix.h"
#endif
  uint32_t switch_states = 0;

};

#endif
