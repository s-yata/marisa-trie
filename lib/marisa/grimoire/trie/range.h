#ifndef MARISA_GRIMOIRE_TRIE_RANGE_H_
#define MARISA_GRIMOIRE_TRIE_RANGE_H_

#include <cassert>

#include "marisa/base.h"

namespace marisa::grimoire::trie {

class Range {
 public:
  Range() = default;

  void set_begin(uint32_t begin) {
    begin_ = begin;
  }
  void set_end(uint32_t end) {
    end_ = end;
  }
  void set_key_pos(uint32_t key_pos) {
    key_pos_ = key_pos;
  }

  uint32_t begin() const {
    return begin_;
  }
  uint32_t end() const {
    return end_;
  }
  uint32_t key_pos() const {
    return key_pos_;
  }

 private:
  uint32_t begin_ = 0;
  uint32_t end_ = 0;
  uint32_t key_pos_ = 0;
};

inline Range make_range(uint32_t begin, uint32_t end, uint32_t key_pos) {
  Range range;
  range.set_begin(begin);
  range.set_end(end);
  range.set_key_pos(key_pos);
  return range;
}

class WeightedRange {
 public:
  WeightedRange() = default;

  void set_range(const Range &range) {
    range_ = range;
  }
  void set_begin(uint32_t begin) {
    range_.set_begin(begin);
  }
  void set_end(uint32_t end) {
    range_.set_end(end);
  }
  void set_key_pos(uint32_t key_pos) {
    range_.set_key_pos(key_pos);
  }
  void set_weight(float weight) {
    weight_ = weight;
  }

  const Range &range() const {
    return range_;
  }
  uint32_t begin() const {
    return range_.begin();
  }
  uint32_t end() const {
    return range_.end();
  }
  uint32_t key_pos() const {
    return range_.key_pos();
  }
  float weight() const {
    return weight_;
  }

 private:
  Range range_;
  float weight_ = 0.0F;
};

inline bool operator<(const WeightedRange &lhs, const WeightedRange &rhs) {
  return lhs.weight() < rhs.weight();
}

inline bool operator>(const WeightedRange &lhs, const WeightedRange &rhs) {
  return lhs.weight() > rhs.weight();
}

inline WeightedRange make_weighted_range(uint32_t begin, uint32_t end,
                                         uint32_t key_pos, float weight) {
  WeightedRange range;
  range.set_begin(begin);
  range.set_end(end);
  range.set_key_pos(key_pos);
  range.set_weight(weight);
  return range;
}

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_RANGE_H_
