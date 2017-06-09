#ifndef TIMER_H_
#define TIMER_H_

#include "auto_config.h"
#include <Arduino.h>

class Timer{
public:
  enum time_units_enum {
    MILLISECONDS,
    MICROSECONDS,
  };

  Timer(time_units_enum _units);
  Timer(uint32_t new_default_value, bool start_now, time_units_enum _units);
  void start();
  void start(uint32_t new_value);
  void disable();
  bool isDisabled();
  bool isDone();
  bool peekDone();
  bool isRunning();
  void forceDone();
  void setDefaultValue(int32_t new_default_value);
  uint32_t elapsed();
  uint32_t remaining();
  void jumpAhead(uint32_t units_ahead);

private:
  uint32_t getSystemTime();

  bool is_disabled = 1;
  uint32_t start_time = 0;
  uint32_t value = 0;
  uint32_t default_value = 0;
  time_units_enum units;
  const time_units_enum default_units = MILLISECONDS;
};





#endif
