#pragma once

#include <cstdint>

// Undefine these arduino macros that conflict with std::min/std::max, breaking other std lib stuff
#undef max
#undef min
#include <array>
#include <limits>


template<typename T, size_t NumBits>
class BitArray {
  // Invariant: the unused bits at the end of the last block should always be 0!
  // If the sure initializes them to 1, or manually sets them by indexing out of
  // bounds, things will break. Any method that could change their value (eg.
  // flip()) should call sanitize() afterwards.

  // Calculate the number of blocks required to store this many bits (ceiling)
  using array_t = std::array<T, ((NumBits + std::numeric_limits<T>::digits - 1) / std::numeric_limits<T>::digits)>;

public:

  constexpr BitArray() : blocks() {}
  constexpr BitArray(array_t raw_blocks) : blocks(raw_blocks) {
    // TODO sanitize here?
  }

  void reset() {
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

  void flip() {
    for(size_t i = 0; i < blocks.size(); i++) {
      blocks[i] = ~blocks[i];
    }
    sanitize();
  }

  void flip(size_t bit_index) {
    blocks[block_index(bit_index)] ^= bit_mask(bit_index);
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

  constexpr bool none() const {
    return !any();
  }

  constexpr size_t size() const {
    return NumBits;
  }

  constexpr const array_t& raw() const {
    return blocks;
  }

  constexpr const T* begin() const {
    return blocks.begin();
  }

  constexpr const T* end() const {
    return blocks.end();
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


private:
  array_t blocks;

  /// Set extra unused bits in the last block to zero.
  void sanitize() {
    blocks.back() &= mask_last_block();
  }

  /// Return a mask where each bit is 1 if it used in the last block, and 0 if not.
  static constexpr T mask_last_block() {
    // Make sure this agrees with bit_mask() about bit order!
    return (~static_cast<T>(0)) >>
      (std::numeric_limits<T>::digits - bit_offset(NumBits) - 1);
  }

  static constexpr size_t block_index(size_t bit_index){
    return bit_index / std::numeric_limits<T>::digits;
  }

  static constexpr size_t bit_offset(size_t bit_index){
    return bit_index % std::numeric_limits<T>::digits;
  }

  static constexpr T bit_mask(size_t bit_index){
    return 0x1 << bit_offset(bit_index);
  }
};


/// Compare 2 BitArrays of equal length by comparing the values of their underlying block types.
template<typename T, size_t NumBits>
bool operator<(const BitArray<T, NumBits>& lhs, const BitArray<T, NumBits>& rhs) {
  // We don't need to mask out unused bits because we assume they've already been sanitized to zero.
  for (size_t i = 0; i < lhs.raw().size(); i++) {
    T left = lhs.raw()[i];
    T right = rhs.raw()[i];

    if (left < right) {
      return true;
    }
    if (left > right) {
      return false;
    }
  }
  // equal!
  return false;
}
