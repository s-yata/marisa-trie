#ifndef MARISA_GRIMOIRE_TRIE_KEY_H_
#define MARISA_GRIMOIRE_TRIE_KEY_H_

#include <cstdint>

#include "marisa/base.h"

namespace marisa::grimoire::trie {

class Key {
 public:
  Key() = default;
  Key(const Key &entry) = default;
  Key &operator=(const Key &entry) = default;

  char operator[](uint32_t i) const {
    MARISA_DEBUG_IF(i >= length_, MARISA_BOUND_ERROR);
    return ptr_[i];
  }

  void substr(uint32_t pos, uint32_t length) {
    MARISA_DEBUG_IF(pos > length_, MARISA_BOUND_ERROR);
    MARISA_DEBUG_IF(length > length_, MARISA_BOUND_ERROR);
    MARISA_DEBUG_IF(pos > (length_ - length), MARISA_BOUND_ERROR);
    ptr_ += pos;
    length_ = length;
  }

  void set_str(const char *ptr, uint32_t length) {
    MARISA_DEBUG_IF((ptr == nullptr) && (length != 0), MARISA_NULL_ERROR);
    ptr_ = ptr;
    length_ = length;
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }
  void set_terminal(uint32_t terminal) {
    union_.terminal = terminal;
  }
  void set_id(uint32_t id) {
    id_ = id;
  }

  const char *ptr() const {
    return ptr_;
  }
  uint32_t length() const {
    return length_;
  }
  float weight() const {
    return union_.weight;
  }
  uint32_t terminal() const {
    return union_.terminal;
  }
  uint32_t id() const {
    return id_;
  }

 private:
  const char *ptr_ = nullptr;
  uint32_t length_ = 0;
  union Union {
    float weight;
    uint32_t terminal = 0;
  } union_;
  uint32_t id_ = 0;
};

inline bool operator==(const Key &lhs, const Key &rhs) {
  if (lhs.length() != rhs.length()) {
    return false;
  }
  for (uint32_t i = 0; i < lhs.length(); ++i) {
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
  for (uint32_t i = 0; i < lhs.length(); ++i) {
    if (i == rhs.length()) {
      return false;
    }
    if (lhs[i] != rhs[i]) {
      return static_cast<uint8_t>(lhs[i]) < static_cast<uint8_t>(rhs[i]);
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

  char operator[](uint32_t i) const {
    MARISA_DEBUG_IF(i >= length_, MARISA_BOUND_ERROR);
    return *(ptr_ - i - 1);
  }

  void substr(uint32_t pos, uint32_t length) {
    MARISA_DEBUG_IF(pos > length_, MARISA_BOUND_ERROR);
    MARISA_DEBUG_IF(length > length_, MARISA_BOUND_ERROR);
    MARISA_DEBUG_IF(pos > (length_ - length), MARISA_BOUND_ERROR);
    ptr_ -= pos;
    length_ = length;
  }

  void set_str(const char *ptr, uint32_t length) {
    MARISA_DEBUG_IF((ptr == nullptr) && (length != 0), MARISA_NULL_ERROR);
    ptr_ = ptr + length;
    length_ = length;
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }
  void set_terminal(uint32_t terminal) {
    union_.terminal = terminal;
  }
  void set_id(uint32_t id) {
    id_ = id;
  }

  const char *ptr() const {
    return ptr_ - length_;
  }
  uint32_t length() const {
    return length_;
  }
  float weight() const {
    return union_.weight;
  }
  uint32_t terminal() const {
    return union_.terminal;
  }
  uint32_t id() const {
    return id_;
  }

 private:
  const char *ptr_ = nullptr;
  uint32_t length_ = 0;
  union Union {
    float weight;
    uint32_t terminal = 0;
  } union_;
  uint32_t id_ = 0;
};

inline bool operator==(const ReverseKey &lhs, const ReverseKey &rhs) {
  if (lhs.length() != rhs.length()) {
    return false;
  }
  for (uint32_t i = 0; i < lhs.length(); ++i) {
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
  for (uint32_t i = 0; i < lhs.length(); ++i) {
    if (i == rhs.length()) {
      return false;
    }
    if (lhs[i] != rhs[i]) {
      return static_cast<uint8_t>(lhs[i]) < static_cast<uint8_t>(rhs[i]);
    }
  }
  return lhs.length() < rhs.length();
}

inline bool operator>(const ReverseKey &lhs, const ReverseKey &rhs) {
  return rhs < lhs;
}

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_KEY_H_
