#pragma once

#include "Matrix.h"
#include "OneShot.h"
#include "auto_config.h"

class Stopwatch {
 public:
  Stopwatch(uint32_t default_val);
  void restart();
  void tick();
  bool isDone();

 private:
  bool enabled = false;
  uint32_t _count;
  const uint32_t _default;
};

class Stopwatches {
 public:
  void tick();

  // Stopwatch chord = conf::CHORD_DELAY;
  // Stopwatch release = conf::CHORD_DELAY;
  // Stopwatch held = conf::HELD_DELAY;
  Stopwatch chord = 30;
  Stopwatch release = 30;
  Stopwatch held = 200;
};

enum class SwitchStatus : uint8_t {
  NotPressed = 0x0,   // not currently pressed
  Pressed = 0x1,      // pressed and not sent yet
  AlreadySent = 0x2,  // already sent, don't resend in future chords
  Held = 0x3,         // already sent, but ok to resend in future chords
};

class Statuses {
 public:
  SwitchStatus get(size_t index) const;
  void set(size_t index, SwitchStatus status);
  void setHeld(const ChordData& new_held_switches);
  void pressedToAlreadySent();
  void alreadySentToHeld();
  bool anyDown() const;
  void writeSendable(ChordData* chord) const;
  constexpr size_t size() const;

 private:
  bool sendable(size_t index) const;

  ChordData lsb;  // least significant
  ChordData msb;  // most significant
};

class Ring {
 public:
  // TODO config size?
  bool push(ChordData data);
  bool pop(ChordData* data_out);

 private:
  size_t incr(size_t index);

  // TODO which should be volatile?
  volatile size_t _tail = 0;
  volatile size_t _head = 0;
  std::array<ChordData, 16> _ring;
};

class Scanner {
 public:
  void setup();
  bool pop(ChordData* data_out);
  static Scanner* getInstance();

  // TODO separate private/interrupt from public/loop better!
  void scanStep();
  void updateSwitches();
  void detectChords();
  Matrix matrix;

 private:
  ChordData makeChord();

  Statuses statuses;
  Stopwatches stopwatches;
  Ring chords;
  // // Index of last released switch, or NO_SWITCH
  // int16_t last_released_switch = NO_SWITCH;
  // bool was_switch_double_tapped = 0;
};
