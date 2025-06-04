#ifndef MARISA_GRIMOIRE_TRIE_KEY_H_
#define MARISA_GRIMOIRE_TRIE_KEY_H_

#include <cassert>

#include "marisa/base.h"

namespace marisa::grimoire::trie {

class Key {
 public:
  Key() = default;
  Key(const Key &entry) = default;
  Key &operator=(const Key &entry) = default;

  char operator[](std::size_t i) const {
    assert(i < length_);
    return ptr_[i];
  }

  void substr(std::size_t pos, std::size_t length) {
    assert(pos <= length_);
    assert(length <= length_);
    assert(pos <= (length_ - length));
    ptr_ += pos;
    length_ = static_cast<UInt32>(length);
  }

  void set_str(const char *ptr, std::size_t length) {
    assert((ptr != nullptr) || (length == 0));
    assert(length <= UINT32_MAX);
    ptr_ = ptr;
    length_ = static_cast<UInt32>(length);
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }
  void set_terminal(std::size_t terminal) {
    assert(terminal <= UINT32_MAX);
    union_.terminal = static_cast<UInt32>(terminal);
  }
  void set_id(std::size_t id) {
    assert(id <= UINT32_MAX);
    id_ = static_cast<UInt32>(id);
  }

  const char *ptr() const {
    return ptr_;
  }
  std::size_t length() const {
    return length_;
  }
  float weight() const {
    return union_.weight;
  }
  std::size_t terminal() const {
    return union_.terminal;
  }
  std::size_t id() const {
    return id_;
  }

 private:
  const char *ptr_ = nullptr;
  UInt32 length_ = 0;
  union Union {
    float weight;
    UInt32 terminal = 0;
  } union_;
  UInt32 id_ = 0;
};

inline bool operator==(const Key &lhs, const Key &rhs) {
  if (lhs.length() != rhs.length()) {
    return false;
  }
  for (std::size_t i = 0; i < lhs.length(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

inline bool operator!=(const Key &lhs, const Key &rhs) {
  return !(lhs == rhs);
}

inline bool operator<(const Key &lhs, const Key &rhs) {
  for (std::size_t i = 0; i < lhs.length(); ++i) {
    if (i == rhs.length()) {
      return false;
    }
    if (lhs[i] != rhs[i]) {
      return static_cast<UInt8>(lhs[i]) < static_cast<UInt8>(rhs[i]);
    }
  }
  return lhs.length() < rhs.length();
}

inline bool operator>(const Key &lhs, const Key &rhs) {
  return rhs < lhs;
}

class ReverseKey {
 public:
  ReverseKey() = default;
  ReverseKey(const ReverseKey &entry) = default;
  ReverseKey &operator=(const ReverseKey &entry) = default;

  char operator[](std::size_t i) const {
    assert(i < length_);
    return *(ptr_ - i - 1);
  }

  void substr(std::size_t pos, std::size_t length) {
    assert(pos <= length_);
    assert(length <= length_);
    assert(pos <= (length_ - length));
    ptr_ -= pos;
    length_ = static_cast<UInt32>(length);
  }

  void set_str(const char *ptr, std::size_t length) {
    assert((ptr != nullptr) || (length == 0));
    assert(length <= UINT32_MAX);
    ptr_ = ptr + length;
    length_ = static_cast<UInt32>(length);
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }
  void set_terminal(std::size_t terminal) {
    assert(terminal <= UINT32_MAX);
    union_.terminal = static_cast<UInt32>(terminal);
  }
  void set_id(std::size_t id) {
    assert(id <= UINT32_MAX);
    id_ = static_cast<UInt32>(id);
  }

  const char *ptr() const {
    return ptr_ - length_;
  }
  std::size_t length() const {
    return length_;
  }
  float weight() const {
    return union_.weight;
  }
  std::size_t terminal() const {
    return union_.terminal;
  }
  std::size_t id() const {
    return id_;
  }

 private:
  const char *ptr_ = nullptr;
  UInt32 length_ = 0;
  union Union {
    float weight;
    UInt32 terminal = 0;
  } union_;
  UInt32 id_ = 0;
};

inline bool operator==(const ReverseKey &lhs, const ReverseKey &rhs) {
  if (lhs.length() != rhs.length()) {
    return false;
  }
  for (std::size_t i = 0; i < lhs.length(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

inline bool operator!=(const ReverseKey &lhs, const ReverseKey &rhs) {
  return !(lhs == rhs);
}

inline bool operator<(const ReverseKey &lhs, const ReverseKey &rhs) {
  for (std::size_t i = 0; i < lhs.length(); ++i) {
    if (i == rhs.length()) {
      return false;
    }
    if (lhs[i] != rhs[i]) {
      return static_cast<UInt8>(lhs[i]) < static_cast<UInt8>(rhs[i]);
    }
  }
  return lhs.length() < rhs.length();
}

inline bool operator>(const ReverseKey &lhs, const ReverseKey &rhs) {
  return rhs < lhs;
}

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_KEY_H_
