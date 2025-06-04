#ifndef MARISA_GRIMOIRE_VECTOR_RETHROWING_STD_VECTOR_H_
#define MARISA_GRIMOIRE_VECTOR_RETHROWING_STD_VECTOR_H_

#include <cassert>
#include <new>
#include <stdexcept>
#include <vector>

#include "marisa/base.h"

namespace marisa::grimoire::vector {

// Wraps an std::vector and rethrows all exceptions as marisa::Exception.
template <typename T>
class RethrowingStdVector {
 public:
  using value_type = typename std::vector<T>::value_type;
  using allocator_type = typename std::vector<T>::allocator_type;
  using size_type = typename std::vector<T>::size_type;
  using difference_type = typename std::vector<T>::difference_type;
  using reference = typename std::vector<T>::reference;
  using const_reference = typename std::vector<T>::const_reference;
  using pointer = typename std::vector<T>::pointer;
  using const_pointer = typename std::vector<T>::const_pointer;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  using reverse_iterator = typename std::vector<T>::reverse_iterator;
  using const_reverse_iterator =
      typename std::vector<T>::const_reverse_iterator;

  RethrowingStdVector() = default;
  RethrowingStdVector(const RethrowingStdVector &other) {
    MARISA_TRY {
      vector_ = other.vector_;
    }
    MARISA_CATCH(const std::bad_alloc &e) {
      MARISA_THROW(MARISA_SIZE_ERROR, "std::bad_alloc");
    }
  }
  RethrowingStdVector &operator=(const RethrowingStdVector &other) {
    MARISA_TRY {
      vector_ = other.vector_;
    }
    MARISA_CATCH(const std::bad_alloc &e) {
      MARISA_THROW(MARISA_SIZE_ERROR, "std::bad_alloc");
    }
  }
  RethrowingStdVector(RethrowingStdVector &&other) noexcept = default;
  RethrowingStdVector &operator=(RethrowingStdVector &&other) noexcept =
      default;

  bool empty() const noexcept {
    return vector_.empty();
  }
  size_type size() const noexcept {
    return vector_.size();
  }
  reference operator[](size_type pos) {
    assert(!empty());
    assert(pos < size());
    return vector_[pos];
  }
  const_reference operator[](size_type pos) const {
    assert(!empty());
    assert(pos < size());
    return vector_[pos];
  }
  reference front() {
    assert(!empty());
    return vector_.front();
  }
  const_reference front() const {
    assert(!empty());
    return vector_.front();
  }
  reference back() {
    assert(!empty());
    return vector_.back();
  }
  const_reference back() const {
    assert(!empty());
    return vector_.back();
  }
  T *data() noexcept {
    return vector_.data();
  }
  const T *data() const noexcept {
    return vector_.data();
  }

  iterator begin() noexcept {
    return vector_.begin();
  }
  const_iterator begin() const noexcept {
    return vector_.begin();
  }
  const_iterator cbegin() const noexcept {
    return vector_.cbegin();
  }
  iterator end() noexcept {
    return vector_.end();
  }
  const_iterator end() const noexcept {
    return vector_.end();
  }
  const_iterator cend() const noexcept {
    return vector_.cend();
  }

  void push_back(const T &value) {
    MARISA_TRY {
      vector_.push_back(value);
    }
    MARISA_CATCH(const std::length_error &e) {
      MARISA_THROW(MARISA_SIZE_ERROR, "std::length_error");
    }
    MARISA_CATCH(const std::bad_alloc &e) {
      MARISA_THROW(MARISA_MEMORY_ERROR, "std::bad_alloc");
    }
  }

  void reserve(size_type new_cap) {
    MARISA_TRY {
      vector_.reserve(new_cap);
    }
    MARISA_CATCH(const std::length_error &e) {
      MARISA_THROW(MARISA_SIZE_ERROR, "std::length_error");
    }
    MARISA_CATCH(const std::bad_alloc &e) {
      MARISA_THROW(MARISA_MEMORY_ERROR, "std::bad_alloc");
    }
  }

  void resize(size_type count) {
    MARISA_TRY {
      vector_.resize(count);
    }
    MARISA_CATCH(const std::length_error &e) {
      MARISA_THROW(MARISA_SIZE_ERROR, "std::length_error");
    }
    MARISA_CATCH(const std::bad_alloc &e) {
      MARISA_THROW(MARISA_MEMORY_ERROR, "std::bad_alloc");
    }
  }

 private:
  std::vector<T> vector_;
};

}  // namespace marisa::grimoire::vector

#endif  // MARISA_GRIMOIRE_VECTOR_RETHROWING_STD_VECTOR_H_
