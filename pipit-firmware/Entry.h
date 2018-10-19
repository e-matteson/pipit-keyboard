#ifndef ENTRY_H_
#define ENTRY_H_

#include <stdint.h>
#include "Chord.h"
#include "Key.h"
#include "auto_config.h"

class Entry {
 public:
  Entry(const Chord* _chord, bool _is_anagrammable);
  Entry() = default;

  const Chord* getChord();
  uint8_t getLength();
  void setLength(uint8_t value);
  void increment();
  void decrement();
  void setLastLetter(uint8_t key_code, uint8_t mod_byte);
  Key* getLastLetter();

  bool isClear();
  bool isAnagrammable();
  void setAnagrammable(bool value);

 private:
  Chord chord;
  Key last_key;
  uint8_t length = 0;
  bool is_anagrammable = 0;
};

#endif
