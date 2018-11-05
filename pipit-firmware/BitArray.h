#pragma once

#include <cstdint>

// Undefine these arduino macros that conflict with std::min/std::max, breaking other std lib stuff
#undef max
#undef min
#include <array>
#include <limits>

template<typename T, size_t NumBits>
class BitArray {
  // Calculate the number of blocks required to store this many bits (ceiling)
  using array_t = std::array<T, ((NumBits + std::numeric_limits<T>::digits - 1) / std::numeric_limits<T>::digits)>;

public:

  constexpr BitArray() : blocks() {}
  constexpr BitArray(array_t data_blocks) : blocks(data_blocks) {}

  void reset(){
    std::fill(blocks.begin(), blocks.end(), 0);
  }

  void reset(size_t bit_index){
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

  constexpr size_t size() const{
    return NumBits;
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

  // T get_block(size_t block_index) const;

  array_t blocks;

private:
  static constexpr size_t block_index(size_t bit_index){
    return bit_index / std::numeric_limits<T>::digits;
  }

  static constexpr size_t bit_offset(size_t bit_index){
    return bit_index % std::numeric_limits<T>::digits;
  }

  static constexpr T bit_mask(size_t bit_index){
    return 0x1 << bit_offset(bit_index);
  }
  // constexpr T* block(size_t bit_index) const;

};
