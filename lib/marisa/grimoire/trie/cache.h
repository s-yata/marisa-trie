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

  void set_parent(std::size_t parent) {
    assert(parent <= UINT32_MAX);
    parent_ = static_cast<UInt32>(parent);
  }
  void set_child(std::size_t child) {
    assert(child <= UINT32_MAX);
    child_ = static_cast<UInt32>(child);
  }
  void set_base(UInt8 base) {
    union_.link = (union_.link & ~0xFFU) | base;
  }
  void set_extra(std::size_t extra) {
    assert(extra <= (UINT32_MAX >> 8));
    union_.link = static_cast<UInt32>((union_.link & 0xFFU) | (extra << 8));
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }

  std::size_t parent() const {
    return parent_;
  }
  std::size_t child() const {
    return child_;
  }
  UInt8 base() const {
    return static_cast<UInt8>(union_.link & 0xFFU);
  }
  std::size_t extra() const {
    return union_.link >> 8;
  }
  char label() const {
    return static_cast<char>(base());
  }
  std::size_t link() const {
    return union_.link;
  }
  float weight() const {
    return union_.weight;
  }

 private:
  UInt32 parent_ = 0;
  UInt32 child_ = 0;
  union Union {
    UInt32 link;
    float weight = FLT_MIN;
  } union_;
};

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_CACHE_H_
