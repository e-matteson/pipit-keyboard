#include "conf.h"

class Queue {
 public:
  // TODO config size?
  bool pushInLoop(ChordData data);
  bool pushInInterrupt(ChordData data);
  bool popInLoop(ChordData* data_out);
  bool popInInterrupt(ChordData* data_out);

 private:
  size_t incr(size_t index);

  // TODO which should be volatile?
  volatile size_t _tail = 0;
  volatile size_t _head = 0;
  std::array<ChordData, 16> _queue;
};
