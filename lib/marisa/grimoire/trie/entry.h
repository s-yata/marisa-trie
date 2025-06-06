#ifndef MARISA_GRIMOIRE_TRIE_ENTRY_H_
#define MARISA_GRIMOIRE_TRIE_ENTRY_H_

#include <cassert>

#include "marisa/base.h"

namespace marisa::grimoire::trie {

class Entry {
 public:
  Entry() = default;
  Entry(const Entry &entry) = default;
  Entry &operator=(const Entry &entry) = default;

  char operator[](std::size_t i) const {
    assert(i < length_);
    return *(ptr_ - i);
  }

  void set_str(const char *ptr, std::size_t length) {
    assert((ptr != nullptr) || (length == 0));
    assert(length <= UINT32_MAX);
    ptr_ = ptr + length - 1;
    length_ = static_cast<UInt32>(length);
  }
  void set_id(std::size_t id) {
    assert(id <= UINT32_MAX);
    id_ = static_cast<UInt32>(id);
  }

  const char *ptr() const {
    return ptr_ - length_ + 1;
  }
  std::size_t length() const {
    return length_;
  }
  std::size_t id() const {
    return id_;
  }

  class StringComparer {
   public:
    bool operator()(const Entry &lhs, const Entry &rhs) const {
      for (std::size_t i = 0; i < lhs.length(); ++i) {
        if (i == rhs.length()) {
          return true;
        }
        if (lhs[i] != rhs[i]) {
          return static_cast<UInt8>(lhs[i]) > static_cast<UInt8>(rhs[i]);
        }
      }
      return lhs.length() > rhs.length();
    }
  };

  class IDComparer {
   public:
    bool operator()(const Entry &lhs, const Entry &rhs) const {
      return lhs.id_ < rhs.id_;
    }
  };

 private:
  const char *ptr_ = nullptr;
  UInt32 length_ = 0;
  UInt32 id_ = 0;
};

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_ENTRY_H_
