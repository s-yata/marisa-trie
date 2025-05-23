#ifndef MARISA_GRIMOIRE_VECTOR_POP_COUNT_H_
#define MARISA_GRIMOIRE_VECTOR_POP_COUNT_H_

#if __cplusplus >= 202002L
 #include <bit>
#endif

#include "marisa/grimoire/intrin.h"

namespace marisa::grimoire::vector {

#ifdef __has_builtin
 #define MARISA_HAS_BUILTIN(x) __has_builtin(x)
#else
 #define MARISA_HAS_BUILTIN(x) 0
#endif

#if MARISA_WORD_SIZE == 64

class PopCount {
 public:
  explicit PopCount(UInt64 x) : value_() {
    x = (x & 0x5555555555555555ULL) + ((x & 0xAAAAAAAAAAAAAAAAULL) >> 1);
    x = (x & 0x3333333333333333ULL) + ((x & 0xCCCCCCCCCCCCCCCCULL) >> 2);
    x = (x & 0x0F0F0F0F0F0F0F0FULL) + ((x & 0xF0F0F0F0F0F0F0F0ULL) >> 4);
    x *= 0x0101010101010101ULL;
    value_ = x;
  }

  std::size_t lo8() const {
    return (std::size_t)(value_ & 0xFFU);
  }
  std::size_t lo16() const {
    return (std::size_t)((value_ >> 8) & 0xFFU);
  }
  std::size_t lo24() const {
    return (std::size_t)((value_ >> 16) & 0xFFU);
  }
  std::size_t lo32() const {
    return (std::size_t)((value_ >> 24) & 0xFFU);
  }
  std::size_t lo40() const {
    return (std::size_t)((value_ >> 32) & 0xFFU);
  }
  std::size_t lo48() const {
    return (std::size_t)((value_ >> 40) & 0xFFU);
  }
  std::size_t lo56() const {
    return (std::size_t)((value_ >> 48) & 0xFFU);
  }
  std::size_t lo64() const {
    return (std::size_t)((value_ >> 56) & 0xFFU);
  }

  static std::size_t count(UInt64 x) {
 #if defined(__cpp_lib_bitops) && __cpp_lib_bitops >= 201907L
    return std::popcount(x);
 #elif MARISA_HAS_BUILTIN(__builtin_popcountll)
    static_assert(sizeof(x) == sizeof(unsigned long long),
                  "__builtin_popcountll does not take 64-bit arg");
    return __builtin_popcountll(x);
 #elif defined(MARISA_X64) && defined(MARISA_USE_POPCNT)
  #ifdef _MSC_VER
    return __popcnt64(x);
  #else   // _MSC_VER
    return static_cast<std::size_t>(_mm_popcnt_u64(x));
  #endif  // _MSC_VER
 #elif defined(MARISA_AARCH64)
    // Byte-wise popcount followed by horizontal add.
    return vaddv_u8(vcnt_u8(vcreate_u8(x)));
 #else   // defined(MARISA_AARCH64)
    return PopCount(x).lo64();
 #endif  // defined(MARISA_AARCH64)
  }

 private:
  UInt64 value_;
};

#else  // MARISA_WORD_SIZE == 64

class PopCount {
 public:
  explicit PopCount(UInt32 x) : value_() {
    x = (x & 0x55555555U) + ((x & 0xAAAAAAAAU) >> 1);
    x = (x & 0x33333333U) + ((x & 0xCCCCCCCCU) >> 2);
    x = (x & 0x0F0F0F0FU) + ((x & 0xF0F0F0F0U) >> 4);
    x *= 0x01010101U;
    value_ = x;
  }

  std::size_t lo8() const {
    return value_ & 0xFFU;
  }
  std::size_t lo16() const {
    return (value_ >> 8) & 0xFFU;
  }
  std::size_t lo24() const {
    return (value_ >> 16) & 0xFFU;
  }
  std::size_t lo32() const {
    return (value_ >> 24) & 0xFFU;
  }

  static std::size_t count(UInt32 x) {
 #if defined(__cpp_lib_bitops) && __cpp_lib_bitops >= 201907L
    return std::popcount(x);
 #elif MARISA_HAS_BUILTIN(__builtin_popcount)
    static_assert(sizeof(x) == sizeof(unsigned int),
                  "__builtin_popcount does not take 32-bit arg");
    return __builtin_popcount(x);
 #elif defined(MARISA_USE_POPCNT)
  #ifdef _MSC_VER
    return __popcnt(x);
  #else   // _MSC_VER
    return _mm_popcnt_u32(x);
  #endif  // _MSC_VER
 #else    // MARISA_USE_POPCNT
    return PopCount(x).lo32();
 #endif   // MARISA_USE_POPCNT
  }

 private:
  UInt32 value_;
};

#endif  // MARISA_WORD_SIZE == 64

#undef MARISA_HAS_BUILTIN

}  // namespace marisa::grimoire::vector

#endif  // MARISA_GRIMOIRE_VECTOR_POP_COUNT_H_
