#include "Ring.h"

size_t Ring::incr(size_t index) { return (index + 1) % _ring.size(); }

bool Ring::push_loop(ChordData data) {
  noInterrupts();
  bool success = push_interrupt(data);
  interrupts();
  return success;
}

bool Ring::pop_loop(ChordData* data_out) {
  noInterrupts();
  bool success = pop_interrupt(data_out);
  interrupts();
  return success;
}

bool Ring::push_interrupt(ChordData data) {
  /// Call this from the interrupt.
  // TODO should we discard old data instead?
  size_t next_head = incr(_head);
  if (_tail != next_head) {
    // Not full!
    _ring[_head] = data;
    _head = next_head;
    return true;  // success!
  }
  return false;  // fail, new data was not pushed
}

bool Ring::pop_interrupt(ChordData* data_out) {
  /// Call this from the interrupt
  if (_tail != _head) {
    // Not empty!
    *data_out = _ring[_tail];
    _tail = incr(_tail);
    return true;  // success!
  }
  return false;  // fail, nothing to pop
}
