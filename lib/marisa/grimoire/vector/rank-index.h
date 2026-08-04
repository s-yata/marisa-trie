#ifndef MARISA_GRIMOIRE_VECTOR_RANK_INDEX_H_
#define MARISA_GRIMOIRE_VECTOR_RANK_INDEX_H_

#include <cassert>

#include "marisa/base.h"

namespace marisa::grimoire::vector {

class RankIndex {
 public:
  RankIndex() = default;

  void set_abs(uint32_t value) {
    abs_ = value;
  }
  void set_rel1(uint32_t value) {
    assert(value <= 64);
    rel_lo_ = (rel_lo_ & ~0x7FU) | (value & 0x7FU);
  }
  void set_rel2(uint32_t value) {
    assert(value <= 128);
    rel_lo_ = (rel_lo_ & ~(0xFFU << 7)) | ((value & 0xFFU) << 7);
  }
  void set_rel3(uint32_t value) {
    assert(value <= 192);
    rel_lo_ = (rel_lo_ & ~(0xFFU << 15)) | ((value & 0xFFU) << 15);
  }
  void set_rel4(uint32_t value) {
    assert(value <= 256);
    rel_lo_ = (rel_lo_ & ~(0x1FFU << 23)) | ((value & 0x1FFU) << 23);
  }
  void set_rel5(uint32_t value) {
    assert(value <= 320);
    rel_hi_ = (rel_hi_ & ~0x1FFU) | (value & 0x1FFU);
  }
  void set_rel6(uint32_t value) {
    assert(value <= 384);
    rel_hi_ = (rel_hi_ & ~(0x1FFU << 9)) | ((value & 0x1FFU) << 9);
  }
  void set_rel7(uint32_t value) {
    assert(value <= 448);
    rel_hi_ = (rel_hi_ & ~(0x1FFU << 18)) | ((value & 0x1FFU) << 18);
  }

  uint32_t abs() const {
    return abs_;
  }
  uint32_t rel1() const {
    return rel_lo_ & 0x7FU;
  }
  uint32_t rel2() const {
    return (rel_lo_ >> 7) & 0xFFU;
  }
  uint32_t rel3() const {
    return (rel_lo_ >> 15) & 0xFFU;
  }
  uint32_t rel4() const {
    return (rel_lo_ >> 23) & 0x1FFU;
  }
  uint32_t rel5() const {
    return rel_hi_ & 0x1FFU;
  }
  uint32_t rel6() const {
    return (rel_hi_ >> 9) & 0x1FFU;
  }
  uint32_t rel7() const {
    return (rel_hi_ >> 18) & 0x1FFU;
  }

 private:
  uint32_t abs_ = 0;
  uint32_t rel_lo_ = 0;
  uint32_t rel_hi_ = 0;
};

}  // namespace marisa::grimoire::vector

#endif  // MARISA_GRIMOIRE_VECTOR_RANK_INDEX_H_
