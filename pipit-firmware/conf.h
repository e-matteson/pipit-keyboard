#ifndef CONF_H_
#define CONF_H_

#include <Arduino.h>
#include "structs.h"
#include "auto_config.h"

namespace conf {

  const ModeStruct* getMode(mode_enum mode);
  const KmapStruct* getKmap(mode_enum mode, seq_type_enum seq_type, uint8_t kmap_num);
  uint8_t getNumKmaps(mode_enum mode);

  const uint8_t* getAnagramMask(mode_enum mode);
  const uint8_t* getAnagram(mode_enum mode, uint8_t num);

  const uint8_t* getModifier(mode_enum mode, mod_enum modifier);
  const uint8_t* getNospace(mode_enum mode);
  const uint8_t* getCapital(mode_enum mode);
  const uint8_t* getCtrl(mode_enum mode);
  const uint8_t* getShift(mode_enum mode);
  const uint8_t* getAlt(mode_enum mode);
  const uint8_t* getGUI(mode_enum mode);

}

#endif
