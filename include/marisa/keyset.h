#ifndef MARISA_KEYSET_H_
#define MARISA_KEYSET_H_

#include <cstdint>
#include <memory>
#include <string_view>

#include "marisa/key.h"

namespace marisa {

class Keyset {
 public:
  enum {
    BASE_BLOCK_SIZE = 4096,
    EXTRA_BLOCK_SIZE = 1024,
    KEY_BLOCK_SIZE = 256
  };

  Keyset();

  Keyset(const Keyset &) = delete;
  Keyset &operator=(const Keyset &) = delete;

  void push_back(const Key &key);
  void push_back(const Key &key, char end_marker);

  void push_back(std::string_view str, float weight = 1.0) {
    push_back(str.data(), str.length(), weight);
  }
  void push_back(const char *str);
  void push_back(const char *ptr, uint32_t length, float weight = 1.0);

  const Key &operator[](uint32_t i) const {
    MARISA_DEBUG_IF(i >= size_, MARISA_BOUND_ERROR);
    return key_blocks_[i / KEY_BLOCK_SIZE][i % KEY_BLOCK_SIZE];
  }
  Key &operator[](uint32_t i) {
    MARISA_DEBUG_IF(i >= size_, MARISA_BOUND_ERROR);
    return key_blocks_[i / KEY_BLOCK_SIZE][i % KEY_BLOCK_SIZE];
  }

  uint32_t num_keys() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }
  uint32_t size() const {
    return size_;
  }
  uint32_t total_length() const {
    return total_length_;
  }

  void reset();

  void clear() noexcept;
  void swap(Keyset &rhs) noexcept;

 private:
  std::unique_ptr<std::unique_ptr<char[]>[]> base_blocks_;
  uint32_t base_blocks_size_ = 0;
  uint32_t base_blocks_capacity_ = 0;
  std::unique_ptr<std::unique_ptr<char[]>[]> extra_blocks_;
  uint32_t extra_blocks_size_ = 0;
  uint32_t extra_blocks_capacity_ = 0;
  std::unique_ptr<std::unique_ptr<Key[]>[]> key_blocks_;
  uint32_t key_blocks_size_ = 0;
  uint32_t key_blocks_capacity_ = 0;
  char *ptr_ = nullptr;
  uint32_t avail_ = 0;
  uint32_t size_ = 0;
  uint32_t total_length_ = 0;

  char *reserve(uint32_t size);

  void append_base_block();
  void append_extra_block(uint32_t size);
  void append_key_block();
};

}  // namespace marisa

#endif  // MARISA_KEYSET_H_
