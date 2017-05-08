#include "Timer.h"

Timer::Timer(){
  // For making arrays of Timers.
  // If you use this, you must manually set the default value!
  disable();
}

Timer::Timer(uint32_t new_default_value, bool start_now){
  setDefaultValue(new_default_value);
  disable();
  if(start_now){
    start();
  }
}

void Timer::start(){
  start(default_value);
}

void Timer::start(uint32_t new_value){
  value = new_value;
  is_disabled = 0;
  start_millis = millis();
}

void Timer::forceDone(){
  start(0);
}

void Timer::disable(){
  is_disabled = 1;
}

bool Timer::isDisabled(){
  return is_disabled;
}

bool Timer::peekDone(){
  // Check if done, but don't change anything!
  return !isDisabled() && (value <= (millis() - start_millis));
}

bool Timer::isDone(){
  // Check if done, and disable timer if it is.
  bool is_done = peekDone();
  if(is_done){
    disable();
  }
  return is_done;
}

bool Timer::isRunning(){
  return !isDisabled() && !isDone();
}

void Timer::setDefaultValue(int32_t new_default_value){
  default_value = new_default_value;
}

uint32_t Timer::elapsed(){
  // For use as a stopwatch
  // This can never be negative right? The clock is monotonic, right?
  return  millis() - start_millis;
}

void Timer::jumpAhead(uint32_t millis_ahead){
  start_millis -= millis_ahead;
}
