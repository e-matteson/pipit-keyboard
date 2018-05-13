#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

uint32_t makeMask32(uint8_t length);
uint16_t makeMask16(uint8_t length);
uint32_t getUnalignedBits(uint32_t bit_offset, uint8_t length, const uint8_t* array);
bool areBitsEqual(const uint32_t a, const uint32_t b, uint32_t mask);
bool isByteMaskSet(const uint8_t mask, const uint8_t byte);


#endif
