#pragma once

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
