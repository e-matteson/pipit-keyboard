#pragma once

#include "Arduino.h"
#include "auto_config.h"

/// Use a singleton pattern to ensure there's only one OneShot object trying to
/// use the underlying timer hardware. getInstance() will get a subclass of
/// OneShot, depending on which board we're compiling the firmware for.

class OneShot {
 public:
  static OneShot* getInstance();
  virtual void schedule(uint32_t count);
  virtual void schedule(uint32_t count, voidFuncPtr callback);
};

#if defined(TEENSY_LC)
#error "OneShot not yet implemented for TEENSY_LC"

#elif defined(FEATHER_M0_BLE)

class FeatherOneShot : public OneShot {
 public:
  FeatherOneShot();
  void schedule(uint32_t count);
  void schedule(uint32_t count, voidFuncPtr callback);

 private:
  void init();
  void initClocks();
  void enableInterrupt();
  void setCount(uint32_t count);
  void sync();

  // const uint32_t _prescaler = TC_CTRLA_PRESCALER_DIV16;
  const uint32_t _prescaler = TC_CTRLA_PRESCALER_DIV1024;
  TcCount32* const _timer = &TC4->COUNT32;
};

#else
#error "OneShot not implemented for unknown board"
#endif
