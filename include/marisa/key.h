#ifndef MARISA_KEY_H_
#define MARISA_KEY_H_

#include <cstdint>
#include <string_view>

#include "marisa/base.h"

namespace marisa {

class Key {
 public:
  Key() = default;
  Key(const Key &key) = default;
  Key &operator=(const Key &key) = default;

  char operator[](uint32_t i) const {
    MARISA_DEBUG_IF(i >= length_, MARISA_BOUND_ERROR);
    return ptr_[i];
  }

  void set_str(std::string_view str) {
    set_str(str.data(), str.length());
  }
  void set_str(const char *str) {
    MARISA_DEBUG_IF(str == nullptr, MARISA_NULL_ERROR);
    uint32_t length = 0;
    while (str[length] != '\0') {
      ++length;
    }
    ptr_ = str;
    length_ = length;
  }
  void set_str(const char *ptr, uint32_t length) {
    MARISA_DEBUG_IF((ptr == nullptr) && (length != 0), MARISA_NULL_ERROR);
    ptr_ = ptr;
    length_ = length;
  }
  void set_id(uint32_t id) {
    union_.id = static_cast<uint32_t>(id);
  }
  void set_weight(float weight) {
    union_.weight = weight;
  }

  std::string_view str() const {
    return std::string_view(ptr_, length_);
  }
  const char *ptr() const {
    return ptr_;
  }
  uint32_t length() const {
    return length_;
  }
  uint32_t id() const {
    return union_.id;
  }
  float weight() const {
    return union_.weight;
  }

  void clear() noexcept {
    Key().swap(*this);
  }
  void swap(Key &rhs) noexcept {
    std::swap(ptr_, rhs.ptr_);
    std::swap(length_, rhs.length_);
    std::swap(union_.id, rhs.union_.id);
  }

 private:
  const char *ptr_ = nullptr;
  uint32_t length_ = 0;
  union Union {
    uint32_t id = 0;
    float weight;
  } union_;
};

}  // namespace marisa

#endif  // MARISA_KEY_H_
