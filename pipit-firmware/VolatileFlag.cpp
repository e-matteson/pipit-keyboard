#include "VolatileFlag.h"

VolatileFlag::VolatileFlag(bool initial_value){
  value = initial_value;
}

bool VolatileFlag::get(){
  bool tmp;
  noInterrupts();
  tmp = value;
  interrupts();
  return tmp;
}

void VolatileFlag::set(){
  noInterrupts();
  value = 1;
  interrupts();
}

void VolatileFlag::unset(){
  noInterrupts();
  value = 0;
  interrupts();
}

bool VolatileFlag::unsafeGet(){
  return value;
}

void VolatileFlag::unsafeSet(){
  value = 1;
}

void VolatileFlag::unsafeUnset(){
  value = 0;
}
