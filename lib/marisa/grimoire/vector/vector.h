#ifndef MARISA_GRIMOIRE_VECTOR_VECTOR_H_
#define MARISA_GRIMOIRE_VECTOR_VECTOR_H_

#include <cstring>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

#include "marisa/grimoire/io.h"

namespace marisa::grimoire::vector {

template <typename T>
class Vector {
 public:
  // These assertions are repeated for clarity/robustness where the property
  // is used.
  static_assert(std::is_trivially_copyable_v<T>);
  static_assert(std::is_trivially_destructible_v<T>);

  Vector() = default;
  // `T` is trivially destructible, so default destructor is ok.
  ~Vector() = default;

  Vector(const Vector<T> &other)
      : buf_(), objs_(nullptr), const_objs_(nullptr), size_(0), capacity_(0),
        fixed_(other.fixed_) {
    if (other.buf_ == nullptr) {
      objs_ = other.objs_;
      const_objs_ = other.const_objs_;
      size_ = other.size_;
      capacity_ = other.capacity_;
    } else {
      copyInit(other.const_objs_, other.size_, other.capacity_);
    }
  }

  Vector &operator=(const Vector<T> &other) {
    clear();
    fixed_ = other.fixed_;
    if (other.buf_ == nullptr) {
      objs_ = other.objs_;
      const_objs_ = other.const_objs_;
      size_ = other.size_;
      capacity_ = other.capacity_;
    } else {
      copyInit(other.const_objs_, other.size_, other.capacity_);
    }
    return *this;
  }

  Vector(Vector &&) noexcept = default;
  Vector &operator=(Vector<T> &&) noexcept = default;

  void map(Mapper &mapper) {
    Vector temp;
    temp.map_(mapper);
    swap(temp);
  }

  void read(Reader &reader) {
    Vector temp;
    temp.read_(reader);
    swap(temp);
  }

  void write(Writer &writer) const {
    write_(writer);
  }

  void push_back(const T &x) {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    MARISA_DEBUG_IF(size_ == max_size(), MARISA_SIZE_ERROR);
    reserve(size_ + 1);
    new (&objs_[size_]) T(x);
    ++size_;
  }

  void pop_back() {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    MARISA_DEBUG_IF(size_ == 0, MARISA_STATE_ERROR);
    --size_;
    static_assert(std::is_trivially_destructible_v<T>);
  }

  // resize() assumes that T's placement new does not throw an exception.
  void resize(std::size_t size) {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    reserve(size);
    for (std::size_t i = size_; i < size; ++i) {
      new (&objs_[i]) T;
    }
    static_assert(std::is_trivially_destructible_v<T>);
    size_ = size;
  }

  // resize() assumes that T's placement new does not throw an exception.
  void resize(std::size_t size, const T &x) {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    reserve(size);
    if (size > size_) {
      std::fill_n(&objs_[size_], size - size_, x);
    }
    // No need to destroy old elements.
    static_assert(std::is_trivially_destructible_v<T>);
    size_ = size;
  }

  void reserve(std::size_t capacity) {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    if (capacity <= capacity_) {
      return;
    }
    MARISA_DEBUG_IF(capacity > max_size(), MARISA_SIZE_ERROR);
    std::size_t new_capacity = capacity;
    if (capacity_ > (capacity / 2)) {
      if (capacity_ > (max_size() / 2)) {
        new_capacity = max_size();
      } else {
        new_capacity = capacity_ * 2;
      }
    }
    realloc(new_capacity);
  }

  void shrink() {
    MARISA_THROW_IF(fixed_, MARISA_STATE_ERROR);
    if (size_ != capacity_) {
      realloc(size_);
    }
  }

  void fix() {
    MARISA_THROW_IF(fixed_, MARISA_STATE_ERROR);
    fixed_ = true;
  }

  const T *begin() const {
    return const_objs_;
  }
  const T *end() const {
    return const_objs_ + size_;
  }
  const T &operator[](std::size_t i) const {
    MARISA_DEBUG_IF(i >= size_, MARISA_BOUND_ERROR);
    return const_objs_[i];
  }
  const T &front() const {
    MARISA_DEBUG_IF(size_ == 0, MARISA_STATE_ERROR);
    return const_objs_[0];
  }
  const T &back() const {
    MARISA_DEBUG_IF(size_ == 0, MARISA_STATE_ERROR);
    return const_objs_[size_ - 1];
  }

  T *begin() {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    return objs_;
  }
  T *end() {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    return objs_ + size_;
  }
  T &operator[](std::size_t i) {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    MARISA_DEBUG_IF(i >= size_, MARISA_BOUND_ERROR);
    return objs_[i];
  }
  T &front() {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    MARISA_DEBUG_IF(size_ == 0, MARISA_STATE_ERROR);
    return objs_[0];
  }
  T &back() {
    MARISA_DEBUG_IF(fixed_, MARISA_STATE_ERROR);
    MARISA_DEBUG_IF(size_ == 0, MARISA_STATE_ERROR);
    return objs_[size_ - 1];
  }

  std::size_t size() const {
    return size_;
  }
  std::size_t capacity() const {
    return capacity_;
  }
  bool fixed() const {
    return fixed_;
  }

  bool empty() const {
    return size_ == 0;
  }
  std::size_t total_size() const {
    return sizeof(T) * size_;
  }
  std::size_t io_size() const {
    return sizeof(UInt64) + ((total_size() + 7) & ~(std::size_t)0x07);
  }

  void clear() {
    Vector().swap(*this);
  }
  void swap(Vector &rhs) {
    buf_.swap(rhs.buf_);
    marisa::swap(objs_, rhs.objs_);
    marisa::swap(const_objs_, rhs.const_objs_);
    marisa::swap(size_, rhs.size_);
    marisa::swap(capacity_, rhs.capacity_);
    marisa::swap(fixed_, rhs.fixed_);
  }

  static std::size_t max_size() {
    return MARISA_SIZE_MAX / sizeof(T);
  }

 private:
  std::unique_ptr<char[]> buf_;
  T *objs_ = nullptr;
  const T *const_objs_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
  bool fixed_ = false;

  void map_(Mapper &mapper) {
    UInt64 total_size;
    mapper.map(&total_size);
    MARISA_THROW_IF(total_size > MARISA_SIZE_MAX, MARISA_SIZE_ERROR);
    MARISA_THROW_IF((total_size % sizeof(T)) != 0, MARISA_FORMAT_ERROR);
    const std::size_t size = (std::size_t)(total_size / sizeof(T));
    mapper.map(&const_objs_, size);
    mapper.seek((std::size_t)((8 - (total_size % 8)) % 8));
    size_ = size;
    fix();
  }
  void read_(Reader &reader) {
    UInt64 total_size;
    reader.read(&total_size);
    MARISA_THROW_IF(total_size > MARISA_SIZE_MAX, MARISA_SIZE_ERROR);
    MARISA_THROW_IF((total_size % sizeof(T)) != 0, MARISA_FORMAT_ERROR);
    const std::size_t size = (std::size_t)(total_size / sizeof(T));
    resize(size);
    reader.read(objs_, size);
    reader.seek((std::size_t)((8 - (total_size % 8)) % 8));
  }
  void write_(Writer &writer) const {
    writer.write((UInt64)total_size());
    writer.write(const_objs_, size_);
    writer.seek((8 - (total_size() % 8)) % 8);
  }

  // Copies current elements to new buffer of size `new_capacity`.
  // Requires `new_capacity >= size_`.
  void realloc(std::size_t new_capacity) {
    MARISA_DEBUG_IF(new_capacity < size_, MARISA_CODE_ERROR);
    MARISA_DEBUG_IF(new_capacity > max_size(), MARISA_SIZE_ERROR);

    std::unique_ptr<char[]> new_buf(
        new (std::nothrow) char[sizeof(T) * new_capacity]);
    MARISA_DEBUG_IF(new_buf == nullptr, MARISA_MEMORY_ERROR);
    T *new_objs = reinterpret_cast<T *>(new_buf.get());

    static_assert(std::is_trivially_copyable_v<T>);
    std::memcpy(new_objs, objs_, sizeof(T) * size_);

    buf_ = std::move(new_buf);
    objs_ = new_objs;
    const_objs_ = new_objs;
    capacity_ = new_capacity;
  }

  // copyInit() assumes that T's placement new does not throw an exception.
  // Requires the vector to be empty.
  void copyInit(const T *src, std::size_t size, std::size_t capacity) {
    MARISA_DEBUG_IF(size_ > 0, MARISA_CODE_ERROR);

    buf_.reset(new (std::nothrow) char[sizeof(T) * capacity]);
    MARISA_DEBUG_IF(buf_ == nullptr, MARISA_MEMORY_ERROR);
    T *new_objs = reinterpret_cast<T *>(buf_.get());

    static_assert(std::is_trivially_copyable_v<T>);
    std::memcpy(new_objs, src, sizeof(T) * size);

    objs_ = new_objs;
    const_objs_ = new_objs;
    size_ = size;
    capacity_ = capacity;
  }
};

}  // namespace marisa::grimoire::vector

#endif  // MARISA_GRIMOIRE_VECTOR_VECTOR_H_
