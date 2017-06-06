#ifndef ENTRY_H_
#define ENTRY_H_

#include <Arduino.h>
#include "auto_config.h"
#include "Chord.h"

class Entry{
public:
  // Entry(Chord* chord, bool is_anagrammable);
  Entry();

  void init(const Chord* _chord, bool _is_anagrammable);
  void copy(const Entry* other);
  void clear();
  Chord* getChord();
  uint8_t getLength();
  void setLength(uint8_t value);
  void increment();
  void decrement();

  bool isClear();
  bool isAnagrammable();
  void setAnagrammable(bool value);

private:
  Chord chord;
  // bool is_clear = 1;
  uint8_t length = 0;
  bool is_anagrammable = 0; // TODO should this be in Entry or Chord?
};

#endif
