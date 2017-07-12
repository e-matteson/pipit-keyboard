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

  bool sendIfEmpty(const Chord* chord);
  void sendPlain(const Key* data, uint8_t data_length, const Chord* chord);
  void sendMacro(const Key* data, uint8_t data_length, const Chord* chord);
  void sendWord(const Key* data, uint8_t data_length, const Chord* chord);
  // void sendGaming(const Key* data, uint8_t data_length, Chord* chord);

  void sendKey(const Key* key);
  void sendKey(uint8_t key_code, uint8_t mod_byte);
  void sendKeys(SixKeys* keys);

  void sendRelease();

  void setStickymod(uint8_t mod_byte);

  History* history;

private:
  bool isSameAsLastSend(const SixKeys* keys);
  void setLastSend(const SixKeys* keys);
  void press(const SixKeys* keys);


  Comms* comms;
  Feedback* feedback;
  SixKeys last_keys;

  uint8_t stickymod = 0; //For programs that use a key like Insert as a fake modifier
  // TODO store stickymod as a Chord?

  /***** optimized releases *****/
  uint8_t last_sent_keycode = 0;
  uint8_t last_sent_mod_byte = 0;
};

#endif
