#pragma once

#include "Matrix.h"
#include "OneShot.h"
#include "Ring.h"
#include "auto_config.h"

#define NO_SWITCH -1

enum class State : uint8_t { Scan, UpdateSwitches, DetectChords };

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

  Stopwatch chord = conf::CHORD_DELAY;
  Stopwatch release = conf::CHORD_DELAY;
  Stopwatch held = conf::HELD_DELAY;
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

class Scanner {
 public:
  void setup();
  bool pop(ChordData* data_out);
  static Scanner* getInstance();

  // TODO separate private/interrupt from public/loop better!
  void scanStep();
  void updateSwitches();
  void detectChords();

  // TODO getter
  State state = State::Scan;

 private:
  ChordData makeChordData();
  void schedule(uint32_t count);

  Matrix matrix;
  Statuses statuses;
  Stopwatches stopwatches;
  Ring chords;

  // Index of last released switch, or NO_SWITCH
  ssize_t last_released_switch = NO_SWITCH;
};
