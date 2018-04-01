#ifndef ENTRY_H_
#define ENTRY_H_

#include <Arduino.h>
#include "auto_config.h"
#include "Chord.h"
#include "Key.h"

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
  void setLastLetter(uint8_t key_code, uint8_t mod_byte);
  void getLastLetter(Key* key);

  bool isClear();
  bool isAnagrammable();
  void setAnagrammable(bool value);

private:
  //  gotta shrink chord to make it smaller
  Chord chord;
  uint8_t length = 0;
  Key last_key;
  bool is_anagrammable = 0;
};

#endif
