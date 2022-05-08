#pragma once

#include "Chord.h"
#include "Matrix.h"
#include "OneShot.h"
#include "Queue.h"
#include "Timer.h"
#include "conf.h"

#define NO_SWITCH -1

enum class State : uint8_t { Scan, UpdateSwitches, DetectChords, Standby };

class Timers {
 public:
  Timers(conf::Mode mode = conf::DEFAULT_MODE);
  void setDefaultsForMode(conf::Mode mode);
  bool isChordOrReleaseDone();

  Timer chord;
  Timer release;
  Timer held;
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

  // Efficiently encode the Status of each switch using 2 bits, one from each
  // ChordData array.
  ChordData lsb;  // least significant
  ChordData msb;  // most significant
};

class Packet {
 public:
  Packet(conf::Mode mode, bool is_partial_release,
         ChordData chord_data = ChordData({0}));
  Packet() = default;

  bool isPress() const;
  bool isPartialRelease() const;
  Chord toChord() const;
  conf::Mode mode() const;

  // Use 1 bit for partial_release flag, and reserve 1 bit for the future.
  static const uint8_t m_num_mode_bits = 6;

 private:
  ChordData m_chord_data;
  uint8_t m_metadata = 0;
};

class Scanner {
 public:
  // TODO separate private/interrupt from public/loop better!

  ///// For use in loop:
  void setup();
  bool popToSend(Packet* packet_out);
  bool pushToHold(ChordData data);
  void setMode(conf::Mode new_mode);

  ///// For use in interrupt context:
  void scanStep();
  void updateSwitches();
  void detectChords();
  void exitStandby();

  volatile State state = State::Scan;

  //// For either:
  static Scanner* getInstance();

 private:
  ChordData makeChordData();
  void schedule_micros(uint32_t micros);

  Matrix matrix;
  Statuses statuses;
  Timers timers;
  volatile conf::Mode mode = conf::DEFAULT_MODE;
  Queue<Packet, 8> to_send;
  Queue<ChordData, 4> to_hold;

  // Index of last released switch, or NO_SWITCH
  ssize_t last_released_switch = NO_SWITCH;
};
