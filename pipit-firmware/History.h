#ifndef HISTORY_H_
#define HISTORY_H_

#include <Arduino.h>
#include "auto_config.h"
#include "keycodes.h"
#include "Chord.h"
#include "Entry.h"

// The number of recent words/sends that can be deleted
#define HISTORY_SIZE 20

class History{

public:
  History();
  void update(uint8_t key_code, uint8_t mod_byte);
  Entry* peek();
  int16_t pop();
  void startGroup(const Chord* new_chord, bool is_anagrammable);
  void endGroup();
  void printStack();

private:

  // void insertCurrentAtCursor();
  void pushCurrent();
  // void push(const Chord* new_chord);
  bool shouldKeyResetDeletion(uint8_t key_code, uint8_t mod_byte);
  void clear();

  // int16_t length_stack[HISTORY_SIZE] = {0};
  Entry* stack[HISTORY_SIZE] = {0}; //TODO deal with null pointers
  Entry current;
  // int16_t current_group_length = 0;
};


#endif
