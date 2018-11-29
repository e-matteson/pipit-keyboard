#include "Queue.h"

size_t Queue::incr(size_t index) { return (index + 1) % _queue.size(); }

bool Queue::pushInLoop(ChordData data) {
  noInterrupts();
  bool success = pushInInterrupt(data);
  interrupts();
  return success;
}

bool Queue::popInLoop(ChordData* data_out) {
  noInterrupts();
  bool success = popInInterrupt(data_out);
  interrupts();
  return success;
}

bool Queue::pushInInterrupt(ChordData data) {
  /// Call this from the interrupt.
  // TODO should we discard old data instead?
  size_t next_head = incr(_head);
  if (_tail != next_head) {
    // Not full!
    _queue[_head] = data;
    _head = next_head;
    return true;  // success!
  }
  return false;  // fail, new data was not pushed
}

bool Queue::popInInterrupt(ChordData* data_out) {
  /// Call this from the interrupt
  if (_tail != _head) {
    // Not empty!
    *data_out = _queue[_tail];
    _tail = incr(_tail);
    return true;  // success!
  }
  return false;  // fail, nothing to pop
}
