#ifndef VOLATILEFLAG_H
#define VOLATILEFLAG_H

#include "auto_config.h"
#include <Arduino.h>

class VolatileFlag{
public:
  VolatileFlag(bool initial_value);

  bool get();
  bool unsafeGet();
  void set();
  void unsafeSet();
  void unset();
  void unsafeUnset();

private:
  bool value;
};

#endif
