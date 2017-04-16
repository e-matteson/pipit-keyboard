#ifndef WORDLENGTH_H_
#define WORDLENGTH_H_

#include <Arduino.h>
#include "auto_config.h"
#include "keycodes.h"

// The number of recent words that can be deleted
#define WORD_LENGTH_HISTORY_SIZE 20

class WordHistory{

public:
  WordHistory();
  void update(uint8_t key_code, uint8_t mod_byte);
  int16_t peek();
  int16_t pop();
  void handleUnknown();
  void startWord();
  void endWord();

private:
  bool shouldKeyResetDeletion(uint8_t key_code, uint8_t mod_byte);
  void clear();
  void push(int16_t value);

  int16_t word_length_stack[WORD_LENGTH_HISTORY_SIZE] = {0};
  int16_t current_word_length = 0;
};


#endif
