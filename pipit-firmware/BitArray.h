#pragma once

#include <cstdint>
// #include <Arduino.h>

// Undefine these arduino macros that conflict with std::min/std::max, breaking other std lib stuff
#undef max
#undef min
#include <array>
#include <limits>

template<typename T, size_t NumBits>
class BitArray {
  // Invariant: the unused bits at the end of the last block should always be 0! If
  // you initialize them to 1, or manually set them by indexing out of bounds,
  // things will break.

  // Calculate the number of blocks required to store this many bits (ceiling)
  using array_t = std::array<T, ((NumBits + std::numeric_limits<T>::digits - 1) / std::numeric_limits<T>::digits)>;

public:

  constexpr BitArray() : blocks() {}
  constexpr BitArray(array_t data_blocks) : blocks(data_blocks) {
    // TODO sanitize here?
  }

  void reset(){
    std::fill(blocks.begin(), blocks.end(), 0);
  }

  void reset(size_t bit_index) {
    blocks[block_index(bit_index)] &= ~bit_mask(bit_index);
  }

  void set(size_t bit_index) {
    blocks[block_index(bit_index)] |= bit_mask(bit_index);
  }

  void set(size_t bit_index, bool value) {
    if( value) {
      set(bit_index);
    } else {
      reset(bit_index);
    }
  }

  void flip(size_t bit_index) {
    blocks[block_index(bit_index)] ^= bit_mask(bit_index);
  }

  void flip() {
    for(size_t i = 0; i < blocks.size(); i++) {
      blocks[i] = ~blocks[i];
    }
    sanitize();
  }

  bool test(size_t bit_index) const {
    return blocks[block_index(bit_index)] & bit_mask(bit_index);
  }

  bool any() const {
    for(auto b : blocks) {
      if (b != static_cast<T>(0)) {
        return true;
      }
    }
    return false;
  }

  bool none() const {
    return !any();
  }

  constexpr size_t size() const{
    return NumBits;
  }

  // If every high bit in the mask is high in this too, return true.
  // (An empty mask will always return true.)
  bool contains(const BitArray<T, NumBits>& mask) const {
    for(size_t i = 0; i < blocks.size(); i++) {
      if (mask.blocks[i] != (blocks[i] & mask.blocks[i])) {
        return false;
      }
    }
    return true;
  }

  bool operator==(const BitArray<T, NumBits>& rhs) const {
    for(size_t i = 0; i < blocks.size(); i++) {
      if (blocks[i] != rhs.blocks[i]){
        return false;
      }
    }
    return true;
  }

  BitArray<T, NumBits> operator~() const {
    auto result = *this;
    result.flip();
    return result;
  }

  BitArray<T, NumBits>& operator&=(const BitArray<T, NumBits>& rhs){
    for(size_t i = 0; i < blocks.size(); i++) {
      blocks[i] &= rhs.blocks[i];
    }
    return *this;
  }

  BitArray<T, NumBits>& operator|=(const BitArray<T, NumBits>& rhs){
    for(size_t i = 0; i < blocks.size(); i++) {
      blocks[i] |= rhs.blocks[i];
    }
    return *this;
  }

  BitArray<T, NumBits>& operator^=(const BitArray<T, NumBits>& rhs){
    for(size_t i = 0; i < blocks.size(); i++) {
      blocks[i] ^= rhs.blocks[i];
    }
    return *this;
  }

  // void printDebug() const {
  //   Serial.print("chord: ");
  //   for (auto block : blocks) {
  //     Serial.print(block);
  //     Serial.print(" ");
  //   }
  //   Serial.println("");
  // }

  array_t blocks;

private:

  /// Set extra unused bits in the last block to zero.
  void sanitize() {
    blocks.back() &= mask_last_block();
  }

  /// Return a mask where each bit is 1 if it used in the last block, and 0 if not.
  constexpr T mask_last_block() const {
    // Make sure this agrees with bit_mask() about bit order!
    // TODO will this get recomputed every time? Can use template magic instead?
    // return (~static_cast<T>(0)) << bit_offset(NumBits);
    return (~static_cast<T>(0)) >> bit_offset(NumBits);
  }

  static constexpr size_t block_index(size_t bit_index){
    return bit_index / std::numeric_limits<T>::digits;
  }

  static constexpr size_t bit_offset(size_t bit_index){
    return bit_index % std::numeric_limits<T>::digits;
  }

  static constexpr T bit_mask(size_t bit_index){
    // return 0x1 << (std::numeric_limits<T>::digits - bit_offset(bit_index) - 1);
    return 0x1 << bit_offset(bit_index);
  }

};
