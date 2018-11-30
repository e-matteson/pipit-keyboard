#include "conf.h"

template <typename T, size_t N>
class Queue {
 public:
  bool pushInLoop(T data) {
    noInterrupts();
    bool success = pushInInterrupt(data);
    interrupts();
    return success;
  }

  bool popInLoop(T* data_out) {
    noInterrupts();
    bool success = popInInterrupt(data_out);
    interrupts();
    return success;
  }

  bool pushInInterrupt(T data) {
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

  bool popInInterrupt(T* data_out) {
    /// Call this from the interrupt
    if (_tail != _head) {
      // Not empty!
      *data_out = _queue[_tail];
      _tail = incr(_tail);
      return true;  // success!
    }
    return false;  // fail, nothing to pop
  }

 private:
  size_t incr(size_t index) { return (index + 1) % N; }

  // TODO which should be volatile?
  volatile size_t _tail = 0;
  volatile size_t _head = 0;
  std::array<T, N> _queue;
};
