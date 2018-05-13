#include "util.h"


uint32_t makeMask32(uint8_t length) {
  // TODO share code with other makeMask
  // The first "length" bits are 1, and the rest are 0
  if(length >= 32) {
    return ~((uint32_t) 0);
  }
  return (1 << length) - 1;
}
uint16_t makeMask16(uint8_t length) {
  // TODO share code with other makeMask
  // The first "length" bits are 1, and the rest are 0
  if(length >= 16) {
    return ~((uint16_t) 0);
  }
  return (1 << length) - 1;
}
