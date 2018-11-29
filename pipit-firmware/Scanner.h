#pragma once

#include "Matrix.h"
#include "OneShot.h"
#include "Queue.h"
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
  void pressedToAlreadySent();

  // TODO better hold/reuseable terms, consistent method names
  void alreadySentToHeld();
  void holdSome(ChordData new_held_switches);

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
  // TODO separate private/interrupt from public/loop better!

  ///// For loop:
  void setup();
  bool popToSend(ChordData* data_out);
  bool pushToHold(ChordData data);
  static Scanner* getInstance();

  ///// For interrupt context:
  void scanStep();
  void updateSwitches();
  void detectChords();

  State state = State::Scan;

 private:
  ChordData makeChordData();
  void schedule(uint32_t count);

  Matrix matrix;
  Statuses statuses;
  Stopwatches stopwatches;
  Queue to_send;
  Queue to_hold;

  // Index of last released switch, or NO_SWITCH
  ssize_t last_released_switch = NO_SWITCH;
};
