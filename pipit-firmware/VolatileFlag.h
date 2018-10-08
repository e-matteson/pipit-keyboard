#ifndef VOLATILEFLAG_H
#define VOLATILEFLAG_H

#include <Arduino.h>
#include "auto_config.h"

class VolatileFlag {
 public:
  VolatileFlag(bool initial_value);

  bool get();
  bool unsafeGet();
  void set();
  void unsafeSet();
  void unset();
  void unsafeUnset();

 private:
  volatile bool value = false;
};

#endif
