#include "VolatileFlag.h"

VolatileFlag::VolatileFlag(bool initial_value) { value = initial_value; }

bool VolatileFlag::get() {
  bool tmp;
  noInterrupts();
  tmp = value;
  interrupts();
  return tmp;
}

void VolatileFlag::set() {
  noInterrupts();
  value = true;
  interrupts();
}

void VolatileFlag::unset() {
  noInterrupts();
  value = false;
  interrupts();
}

bool VolatileFlag::unsafeGet() { return value; }

void VolatileFlag::unsafeSet() { value = true; }

void VolatileFlag::unsafeUnset() { value = false; }
