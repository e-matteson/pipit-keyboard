#include "Switches.h"
#include <Arduino.h>

Switches::Switches() {
  chord_timer.setDefaultValue(conf::CHORD_DELAY);
  release_timer.setDefaultValue(conf::CHORD_DELAY);
  held_timer.setDefaultValue(conf::HELD_DELAY);

  for (Timer& timer : debounce_timers) {
    timer.setDefaultValue(conf::DEBOUNCE_DELAY);
  }
}

void Switches::update() {
  matrix.scanIfChanged();
  updateSwitchStatuses();

  // If any switches have been held for a while,
  // or 1 switch in a chord was released and re-pressed,
  // let the held switches be reused in future chords.
  // TODO always re-use modifers here?
  if (held_timer.isDone() || was_switch_double_tapped) {
    statuses.alreadySentToHeld();
  }
}

void Switches::setup() { matrix.setup(); }

bool Switches::readyToPress(bool is_gaming) {
  if (!is_gaming) {
    return chord_timer.isDone();
  }

  // If gaming, ignore chord timers and everything else.
  // Just check if anything changed since we last checked.
  if (!chord_timer.isDisabled() || !release_timer.isDisabled()) {
    chord_timer.disable();
    release_timer.disable();
    return true;  // Changed! Ready.
  }
  return false;  // No change.
}

bool Switches::readyToRelease() {
  // Gaming modes never needs to call this, they don't respond to releases.
  return release_timer.isDone();
}

void Switches::updateSwitchStatuses() {
  // TODO use bitwise ops somehow?
  was_switch_double_tapped = false;
  for (uint8_t i = 0; i < statuses.size(); i++) {
    const SwitchStatus status = statuses.get(i);
    if (matrix.isDown(i)) {   // Switch is physically down now.
      switch (status) {   // Old status is:
        case SwitchStatus::Pressed:
        case SwitchStatus::AlreadySent:
        case SwitchStatus::Held:
          // If we were debouncing a release, stop, it wasn't real.
          stopDebouncing(i);
          break;
        case SwitchStatus::NotPressed:
          // Might be a new press, debounce it first
          debouncePress(i);
          break;
      }
    } else {  // Switch is physically up now.
      switch (status) {  // Old status is:
        case SwitchStatus::AlreadySent:
        case SwitchStatus::Held:
          // Might be a new release, debounce it first
          debounceRelease(i);
          break;
        case SwitchStatus::NotPressed:
          // If we were debouncing a press, stop, it wasn't real.
          stopDebouncing(i);
          break;
        case SwitchStatus::Pressed:
          if (debounceRelease(i)) {
            // Switch was quickly tapped and released, before the chord timer
            // even ran out. Change status back to Pressed, after
            // debounceRelease set it to NotPressed.
            // TODO how might this interact with the bouncy-switch grace period?
            statuses.set(i, SwitchStatus::Pressed);
            // Force a send during this loop iteration.
            chord_timer.forceDone();
          }
          break;
      }
    }
  }
}

bool Switches::debouncePress(uint8_t switch_index) {
  // Maybe it's a new press, debounce it first.
  // Count down from DEBOUNCE_DELAY to 0.
  bool is_debounce_done = 0;
  /* if (debounce_timers[switch_index].isDisabled()) { */
  /*   // Start debouncing, don't change status. */
  /*   debounce_timers[switch_index].start(); */
  /* } else if (debounce_timers[switch_index].isDone()) { */
  /*   // Debounce done, it's a real press! */
    statuses.set(switch_index, SwitchStatus::Pressed);
    debounce_timers[switch_index].disable();

    chord_timer.start();
    held_timer.start();

    // Check if the switch was double tapped.
    // TODO why `|=` and not `=`?
    was_switch_double_tapped |= (switch_index == last_released_switch);
    last_released_switch = NO_SWITCH;

    is_debounce_done = 1;
  /* } */
  // Else, keep debouncing, don't change status.
  return is_debounce_done;
}

bool Switches::debounceRelease(uint8_t switch_index) {
  // Maybe it's a new release, debounce it first.
  // Count down from DEBOUNCE_DELAY to 0.
  bool is_debounce_done = false;
  if (debounce_timers[switch_index].isDisabled()) {
    // Start debouncing, don't change status.
    debounce_timers[switch_index].start();
  } else if (debounce_timers[switch_index].isDone()) {
    // Debouncing done, it's a real release.
    debounce_timers[switch_index].disable();
    statuses.set(switch_index, SwitchStatus::NotPressed);

    last_released_switch = switch_index;
    release_timer.start();
    held_timer.start();
    is_debounce_done = true;
  }
  // Else, keep debouncing, don't change status.
  return is_debounce_done;
}

void Switches::stopDebouncing(uint8_t i) {
  // It was not a real press/release.
  debounce_timers[i].disable();
}


/// Let modifiers be immediately re-used in future chords.
// Not currently called in gaming mode, which simplifies things
// TODO could this ever set an unpressed switch to Held?
// TODO how does this distinguish between implicit and explicit mods?
void Switches::reuseMods(Chord* chord) {
  for (uint8_t i = 0; i < NUM_MODIFIERS; i++) {
    conf::Mod mod = (conf::Mod) i;
    if (!chord->hasMod(mod)) {
      continue;
    }
    statuses.setHeld(*conf::getModChord(chord->getModeName(), mod));
  }
}

bool Switches::anyDown() {
  return statuses.anyDown();
}

void Switches::fillChord(Chord* chord) {
  // Binary-encode the values of the switch_status array into an array of bytes,
  //  for easy comparison to the bytes in the lookup arrays.
  statuses.writeSendable(chord->getDataMut());
  // Modify the status array to record that the switches have been processed.
  statuses.pressedToAlreadySent();
}

// Fill up an array of chords, one for each pressed switch, instead of combining
// them all into 1 chord like fillChord()
uint8_t Switches::fillGamingSwitches(Chord* chords) {
  // TODO use bitwise ops, count()
  uint8_t num_pressed = 0;

  for (uint8_t index = 0; index < statuses.size(); index++) {
    // TODO write statuses.gaming_sendable()
    if (statuses.get(index) != SwitchStatus::NotPressed) {
      // Switch is basically pressed! Other states don't matter in gaming modes.
      chords[num_pressed].setSwitch(index);
      num_pressed++;
      statuses.set(index, SwitchStatus::AlreadySent);
    }
    index++;
  }
  return num_pressed;
}


void Switches::Statuses::set(size_t index, Switches::SwitchStatus status){
  uint8_t val = static_cast<uint8_t>(status);
  lsb.set(index, val & 0x1);
  msb.set(index, val & 0x2);
}

Switches::SwitchStatus Switches::Statuses::get(size_t index) const {
  return static_cast<Switches::SwitchStatus>((msb.test(index) << 1) | lsb.test(index));
}

/// If any switches are AlreadySent, change their status to Held.
void Switches::Statuses::setHeld(const ChordData& new_held_switches) {
  lsb |= new_held_switches;
  msb |= new_held_switches;
}

/// If any switches are AlreadySent, change their status to Held.
void Switches::Statuses::alreadySentToHeld(){
  lsb |= msb;
}

/// If any switches are Pressed, change their status to AlreadySent.
void Switches::Statuses::pressedToAlreadySent(){
  // TODO can we do this in-place instead?
  auto mask (msb);
  mask ^= lsb;
  mask &= lsb;
  msb ^= mask;
  lsb ^= mask;
}

bool Switches::Statuses::anyDown() const {
  return msb.any() | lsb.any();
}

bool Switches::Statuses::sendable(size_t index) const {
  return lsb.test(index);
}

constexpr size_t Switches::Statuses::size() const {
  return lsb.size();
}

void Switches::Statuses::writeSendable(ChordData* chord) const {
  // If any switches are sendable (Pressed or Held), set them in the chord.
  *chord |= lsb;
}
