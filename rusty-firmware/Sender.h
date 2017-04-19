#ifndef SENDER_H_
#define SENDER_H_

#include <Arduino.h>
#include "auto_config.h"
#include "History.h"
#include "Feedback.h"
#include "Chord.h"
#include "Comms.h"


class Sender{
public:
  Sender(Comms* comms);

  bool sendIfEmpty(Chord* chord);
  void sendPlain(const uint8_t* data, uint8_t data_length, Chord* chord);
  void sendMacro(const uint8_t* data, uint8_t data_length, Chord* chord);
  void sendWord(const uint8_t* data, uint8_t data_length, Chord* chord);
  void sendKey(uint8_t key_code, uint8_t mod_byte);

  void deleteLastWord();
  void handleUnknown();

  void setOrAbortStickymod();
  void setOrAbortStickymod(uint8_t key_code);


private:
  bool isSameAsLastSend(uint8_t key_code1, uint8_t key_code2, uint8_t mod_byte);
  void setLastSend(uint8_t key_code1, uint8_t key_code2, uint8_t mod_byte);
  void press(uint8_t key_code1, uint8_t key_code2, uint8_t mod_byte);


  Comms* comms;
  Feedback* feedback;
  History* history;

  uint8_t stickymod = 0; //For programs that use a key like Insert as a fake modifier


  /***** optimized releases *****/
  uint8_t last_sent_keycode1 = 0;
  uint8_t last_sent_keycode2 = 0;
  uint8_t last_sent_mod_byte = 0;


};

#endif
