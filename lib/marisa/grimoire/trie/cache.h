#ifndef MARISA_GRIMOIRE_TRIE_CACHE_H_
#define MARISA_GRIMOIRE_TRIE_CACHE_H_

#include <cassert>
#include <cfloat>

#include "marisa/base.h"

namespace marisa::grimoire::trie {

class Cache {
 public:
  Cache() = default;
  Cache(const Cache &cache) = default;
  Cache &operator=(const Cache &cache) = default;

  void set_parent(uint32_t parent) {
    parent_ = parent;
  }
  void set_child(uint32_t child) {
    child_ = child;
  }
  void set_base(uint8_t base) {
    union_.link = (union_.link & ~0xFFU) | base;
  }
  void set_extra(uint32_t extra) {
    assert(extra <= (UINT32_MAX >> 8));
    union_.link = static_cast<uint32_t>((union_.link & 0xFFU) | (extra << 8));
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }

  uint32_t parent() const {
    return parent_;
  }
  uint32_t child() const {
    return child_;
  }
  uint8_t base() const {
    return static_cast<uint8_t>(union_.link & 0xFFU);
  }
  uint32_t extra() const {
    return union_.link >> 8;
  }
  char label() const {
    return static_cast<char>(base());
  }
  uint32_t link() const {
    return union_.link;
  }
  float weight() const {
    return union_.weight;
  }

 private:
  uint32_t parent_ = 0;
  uint32_t child_ = 0;
  union Union {
    uint32_t link;
    float weight = FLT_MIN;
  } union_;
};

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_CACHE_H_
