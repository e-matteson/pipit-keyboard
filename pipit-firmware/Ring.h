#include "conf.h"

class Ring {
 public:
  // TODO config size?
  bool push_loop(ChordData data);
  bool push_interrupt(ChordData data);
  bool pop_loop(ChordData* data_out);
  bool pop_interrupt(ChordData* data_out);

 private:
  size_t incr(size_t index);

  // TODO which should be volatile?
  volatile size_t _tail = 0;
  volatile size_t _head = 0;
  std::array<ChordData, 16> _ring;
};
