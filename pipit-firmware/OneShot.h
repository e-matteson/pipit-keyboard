#pragma once

#include "Arduino.h"
#include "auto_config.h"

/// Use a singleton pattern to ensure there's only one OneShot object trying to
/// use the underlying timer hardware, and because we'll need to access it from
/// interrupt context

class OneShot {
 public:
  static OneShot* getInstance();
  void schedule_micros(uint32_t micros);
  void schedule_micros(uint32_t micros, voidFuncPtr callback);

 private:
  OneShot();
  void enableInterrupt();
};
