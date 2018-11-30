#include "Scanner.h"
#include "conf.h"

// TODO specify as microsecs instead of raw counts
#define CAPACITANCE_COUNT 0x2
#define YIELD_COUNT 0x2
#define UNTIL_SCAN_COUNT 0x19

void scannerISR() {
  Scanner* s = Scanner::getInstance();
  switch (s->state) {
    case State::Scan:
      s->scanStep();
      break;
    case State::UpdateSwitches:
      s->updateSwitches();
      break;
    case State::DetectChords:
      s->detectChords();
      break;
  }
}

Stopwatch::Stopwatch(uint32_t default_val)
    : _default(default_val), _count(0), _enabled(false) {}

void Stopwatch::setDefault(uint32_t new_default) { _default = new_default; }

bool Stopwatch::isDone() {
  if (_enabled && _count == 0) {
    _enabled = false;
    return true;
  }
  return false;
}

void Stopwatch::tick() {
  if (_enabled && _count != 0) {
    _count--;
  }
}

void Stopwatch::restart() {
  _count = _default;
  _enabled = true;
}

Stopwatches::Stopwatches(conf::Mode mode) : chord(0), release(0), held(0) {
  setDefaultsForMode(mode);
}

void Stopwatches::setDefaultsForMode(conf::Mode mode) {
  if (conf::isGaming(mode)) {
    chord = 0;
    release = 0;
    held = 0;
  } else {
    chord = conf::CHORD_DELAY;
    release = conf::CHORD_DELAY;
    held = conf::HELD_DELAY;
  }
}

bool Stopwatches::isChordOrReleaseDone() {
  if (chord.isDone() || release.isDone()) {
    // Ensure we always check the release counter and disable it if it's done,
    // even if the 'or' short-circuits.
    release.isDone();
    return true;
  }
  return false;
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

/// If any of the switches in the given chord are not NotPressed, change their
/// statuses to Held.
void Statuses::holdSome(ChordData new_held_switches) {
  // Because I haven't bothered to implement non-assigning bitwise ops...
  ChordData mask;
  mask |= lsb;
  mask |= msb;
  mask &= new_held_switches;
  msb |= mask;
  lsb |= mask;
}

/// If any switches are AlreadySent, change their status to Held.
void Statuses::alreadySentToHeld() { lsb |= msb; }

/// If any switches are Pressed, change their status to Held.
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

bool Scanner::popToSend(Packet* packet_out) {
  return to_send.popInLoop(packet_out);
}

bool Scanner::pushToHold(ChordData data) { return to_hold.pushInLoop(data); }

void Scanner::setup() {
  matrix.setup();
  OneShot::getInstance()->schedule(UNTIL_SCAN_COUNT, scannerISR);
}

ChordData Scanner::makeChordData() {
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
    const SwitchStatus status = statuses.get(i);
    if (status == SwitchStatus::NotPressed && matrix.any(i)) {
      // New press! Accept it immediately without debouncing.
      stopwatches.chord.restart();
      stopwatches.held.restart();
      statuses.set(i, SwitchStatus::Pressed);

      // Check if this switch was double tapped.
      was_switch_double_tapped |= (i == last_released_switch);
      last_released_switch = NO_SWITCH;
    } else if (status != SwitchStatus::NotPressed && matrix.none(i)) {
      // Debounced release!
      stopwatches.release.restart();
      stopwatches.held.restart();
      statuses.set(i, SwitchStatus::NotPressed);
      last_released_switch = i;
      // TODO detect quick taps (pressed and released before chord delay is up)
      // Or is it better not to? Protects against bounces, and fine when the
      // chord delay is very short.
    }
  }
  if (was_switch_double_tapped) {
    // Ensure that tapping 1 switch in a chord will always resend the full chord
    statuses.alreadySentToHeld();
  }
  state = State::DetectChords;
  schedule(YIELD_COUNT);
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
    state = State::UpdateSwitches;
    schedule(YIELD_COUNT);
  } else {
    // Set next column and then wait for it to take effect before reading.
    matrix.selectColumn(col_index);
    col_index++;
    schedule(CAPACITANCE_COUNT);
  }
}

void Scanner::detectChords() {
  if (stopwatches.held.isDone()) {
    statuses.alreadySentToHeld();
  }

  static ChordData switches_to_hold;
  if (to_hold.popInInterrupt(&switches_to_hold)) {
    statuses.holdSome(switches_to_hold);
  }

  if ((conf::isGaming(mode) && stopwatches.isChordOrReleaseDone()) ||
      stopwatches.chord.isDone()) {
    to_send.pushInInterrupt(Packet(mode, false, makeChordData()));
  } else if (stopwatches.release.isDone()) {
    to_send.pushInInterrupt(Packet(mode, statuses.anyDown(), ChordData({0})));
  }

  stopwatches.tick();
  state = State::Scan;
  schedule(UNTIL_SCAN_COUNT);
}

void Scanner::setMode(conf::Mode new_mode) {
  noInterrupts();
  mode = new_mode;
  stopwatches.setDefaultsForMode(new_mode);
  interrupts();
}

void Scanner::schedule(uint32_t count) {
  OneShot::getInstance()->schedule(count);
}

Scanner* Scanner::getInstance() {
  static Scanner s;
  return &s;
}

static_assert(conf::mode_structs.size() <= (1 << Packet::m_num_mode_bits),
              "too many modes, can't fit in packet");

Packet::Packet(conf::Mode mode, bool is_partial_release, ChordData chord_data)
    : m_chord_data(chord_data) {
  m_metadata = conf::to_index(mode);
  m_metadata |= (is_partial_release << m_num_mode_bits);
}

bool Packet::isPartialRelease() const { return m_metadata >> m_num_mode_bits; }

bool Packet::isPress() const { return m_chord_data.any(); }

conf::Mode Packet::mode() const {
  return static_cast<conf::Mode>(m_metadata & ~(1 << m_num_mode_bits));
}

Chord Packet::toChord() const {
  Chord chord(mode(), m_chord_data);
  return chord;
}
