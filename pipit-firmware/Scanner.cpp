#include "Scanner.h"
#include "conf.h"

// TODO specify as microsecs instead of raw counts
#define CAPACITANCE_COUNT 0x2
#define PAUSE_COUNT 0x2
#define UNTIL_SCAN_COUNT 0x19

void scanRowsISR();

void detectChordsISR() {
  Scanner::getInstance()->detectChords();
  OneShot::getInstance()->schedule(UNTIL_SCAN_COUNT, scanRowsISR);
}

void updateSwitchesISR() {
  Scanner::getInstance()->updateSwitches();
  OneShot::getInstance()->schedule(PAUSE_COUNT, detectChordsISR);
}

void scanRowsISR() {
  Scanner::getInstance()->scanStep();
  // TODO be consistent about where to set OneShot
}

Stopwatch::Stopwatch(uint32_t default_val) : _default(default_val) {}

bool Stopwatch::isDone() {
  if (enabled && _count == 0) {
    enabled = false;
    return true;
  }
  return false;
}

void Stopwatch::tick() {
  if (enabled && _count != 0) {
    _count--;
  }
}

void Stopwatch::restart() {
  _count = _default;
  enabled = true;
}

void Stopwatches::tick() {
  chord.tick();
  release.tick();
  held.tick();
}

void Statuses::set(size_t index, SwitchStatus status) {
  uint8_t val = static_cast<uint8_t>(status);
  lsb.set(index, val & 0x1);
  msb.set(index, val & 0x2);
}

SwitchStatus Statuses::get(size_t index) const {
  return static_cast<SwitchStatus>((msb.test(index) << 1) | lsb.test(index));
}

/// If any switches are AlreadySent, change their status to Held.
void Statuses::setHeld(const ChordData& new_held_switches) {
  lsb |= new_held_switches;
  msb |= new_held_switches;
}

/// If any switches are AlreadySent, change their status to Held.
void Statuses::alreadySentToHeld() { lsb |= msb; }

/// If any switches are Pressed, change their status to AlreadySent.
void Statuses::pressedToAlreadySent() {
  // TODO can we do this in-place instead?
  auto mask(msb);
  mask ^= lsb;
  mask &= lsb;
  msb ^= mask;
  lsb ^= mask;
}

bool Statuses::anyDown() const { return msb.any() | lsb.any(); }

bool Statuses::sendable(size_t index) const { return lsb.test(index); }

constexpr size_t Statuses::size() const { return lsb.size(); }

void Statuses::writeSendable(ChordData* chord) const {
  // If any switches are sendable (Pressed or Held), set them in the chord.
  *chord |= lsb;
}

size_t Ring::incr(size_t index) { return (index + 1) % _ring.size(); }

bool Ring::push(ChordData data) {
  /// Call this from the interrupt.
  // TODO should we discard old data instead?
  bool success = false;
  size_t next_head = incr(_head);
  if (_tail != next_head) {
    // Not full!
    _ring[_head] = data;
    _head = next_head;
    success = true;
  }
  return success;
}

bool Ring::pop(ChordData* data_out) {
  /// Call this from the loop.
  bool success = false;
  noInterrupts();
  if (_tail != _head) {
    // Not empty!
    *data_out = _ring[_tail];
    _tail = incr(_tail);
    success = true;
  }
  interrupts();
  return success;
}

bool Scanner::pop(ChordData* data_out) { return chords.pop(data_out); }

void Scanner::setup() {
  matrix.setup();
  OneShot::getInstance()->schedule(UNTIL_SCAN_COUNT, scanRowsISR);
}

ChordData Scanner::makeChord() {
  // Binary-encode the values of the switch_status array into an array of bytes,
  //  for easy comparison to the bytes in the lookup arrays.
  ChordData data;
  statuses.writeSendable(&data);
  // Modify the status array to record that the switches have been processed.
  statuses.pressedToAlreadySent();
  return data;
}

void Scanner::updateSwitches() {
  // For each switch index, update status based on readings.
  bool was_switch_double_tapped = false;
  for (uint8_t i = 0; i < statuses.size(); i++) {
    // if (matrix.any(i)) {
    //   debug();
    // }
    const SwitchStatus status = statuses.get(i);
    if (status == SwitchStatus::NotPressed && matrix.any(i)) {
      // New press! Accept it immediately without debouncing.
      conf::purple();
      stopwatches.chord.restart();
      stopwatches.held.restart();
      statuses.set(i, SwitchStatus::Pressed);

      // Check if this switch was double tapped.
      was_switch_double_tapped |= (i == last_released_switch);
      last_released_switch = NO_SWITCH;
    } else if (status != SwitchStatus::NotPressed && matrix.none(i)) {
      // Debounced release!
      conf::white();
      stopwatches.release.restart();
      stopwatches.held.restart();
      statuses.set(i, SwitchStatus::NotPressed);
      last_released_switch = i;
      // TODO quick tap (shorter than chord delay)
    }
  }
  if (was_switch_double_tapped) {
    // Ensure that tapping 1 switch in a chord will always resend the full chord
    statuses.alreadySentToHeld();
  }
}

void Scanner::scanStep() {
  static uint8_t col_index = 0;
  if (col_index >= 1) {
    // Not the 1st column, there's something ready to scan.
    matrix.readRows();
    matrix.unselectColumn(col_index - 1);
  }
  if (col_index == conf::column_pins.size()) {
    // Last column, done scanning!
    col_index = 0;
    OneShot::getInstance()->schedule(PAUSE_COUNT, updateSwitchesISR);
  } else {
    // Set next column and then wait for it to take effect before reading.
    matrix.selectColumn(col_index);
    col_index++;
    OneShot::getInstance()->schedule(CAPACITANCE_COUNT, scanRowsISR);
  }
}

void Scanner::detectChords() {
  // TODO releaseNonMods?
  stopwatches.tick();
  if (stopwatches.chord.isDone()) {
    // conf::cyan();
    chords.push(makeChord());
  }
  if (stopwatches.release.isDone()) {
    chords.push(ChordData({0}));
  }
  if (stopwatches.held.isDone()) {
    statuses.alreadySentToHeld();
  }
}

Scanner* Scanner::getInstance() {
  static Scanner s;
  return &s;
}
