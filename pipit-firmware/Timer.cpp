#include "Timer.h"
#include <Arduino.h>


Timer::Timer() {
  // For making arrays of Timers.
  // If you use this, you must manually set the default value later!
}

Timer::Timer(uint32_t _default_value) { setDefaultValue(_default_value); }

void Timer::start() {
  if (!default_value) {
    DEBUG1_LN("WARNING: starting timer with default value of 0");
  }
  start(default_value);
}

void Timer::start(uint32_t new_value) {
  value = new_value;
  is_disabled = 0;
  start_time = getSystemTime();
}

void Timer::forceDone() { start(0); }

void Timer::disable() { is_disabled = 1; }

bool Timer::isDisabled() { return is_disabled; }

bool Timer::peekDone() {
  // Check if done, but don't change anything!
  return !isDisabled() && (remaining() == 0);
}

bool Timer::isDone() {
  // Check if done, and disable timer if it is.
  bool is_done = peekDone();
  if (is_done) {
    disable();
  }
  return is_done;
}

bool Timer::isRunning() { return !isDisabled() && !isDone(); }

void Timer::setDefaultValue(int32_t new_default_value) {
  default_value = new_default_value;
}

uint32_t Timer::remaining() {
  uint32_t elapsed_time = elapsed();
  if (elapsed_time > value) {
    // Done!
    return 0;
  }
  return value - elapsed_time;
}

uint32_t Timer::elapsed() {
  // This works even if the clock overflowed, because modular arithmetic
  return getSystemTime() - start_time;
}

void Timer::jumpAhead(uint32_t units_ahead) { start_time -= units_ahead; }

uint32_t Timer::getSystemTime() { return millis(); }
