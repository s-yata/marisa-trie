#ifndef MARISA_QUERY_H_
#define MARISA_QUERY_H_

#include <string_view>

#include "marisa/base.h"

namespace marisa {

class Query {
 public:
  Query() = default;
  Query(const Query &query) = default;

  Query &operator=(const Query &query) = default;

  char operator[](std::size_t i) const {
    MARISA_DEBUG_IF(i >= length_, MARISA_BOUND_ERROR);
    return ptr_[i];
  }

  void set_str(std::string_view str) {
    set_str(str.data(), str.length());
  }
  void set_str(const char *str) {
    MARISA_DEBUG_IF(str == nullptr, MARISA_NULL_ERROR);
    std::size_t length = 0;
    while (str[length] != '\0') {
      ++length;
    }
    ptr_ = str;
    length_ = length;
  }
  void set_str(const char *ptr, std::size_t length) {
    MARISA_DEBUG_IF((ptr == nullptr) && (length != 0), MARISA_NULL_ERROR);
    ptr_ = ptr;
    length_ = length;
  }
  void set_id(std::size_t id) {
    id_ = id;
  }

  std::string_view str() const {
    return std::string_view(ptr_, length_);
  }
  const char *ptr() const {
    return ptr_;
  }
  std::size_t length() const {
    return length_;
  }
  std::size_t id() const {
    return id_;
  }

  void clear() {
    Query().swap(*this);
  }
  void swap(Query &rhs) {
    marisa::swap(ptr_, rhs.ptr_);
    marisa::swap(length_, rhs.length_);
    marisa::swap(id_, rhs.id_);
  }

 private:
  const char *ptr_ = nullptr;
  std::size_t length_ = 0;
  std::size_t id_ = 0;
};

}  // namespace marisa

#endif  // MARISA_QUERY_H_
