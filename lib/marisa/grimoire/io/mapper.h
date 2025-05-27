#ifndef MARISA_GRIMOIRE_IO_MAPPER_H_
#define MARISA_GRIMOIRE_IO_MAPPER_H_

#include <cstdio>

#include "marisa/base.h"

namespace marisa::grimoire::io {

class Mapper {
 public:
  Mapper();
  ~Mapper();

  Mapper(const Mapper &) = delete;
  Mapper &operator=(const Mapper &) = delete;

  void open(const char *filename, int flags = 0);
  void open(const void *ptr, std::size_t size);

  template <typename T>
  void map(T *obj) {
    MARISA_THROW_IF(obj == nullptr, MARISA_NULL_ERROR);
    *obj = *static_cast<const T *>(map_data(sizeof(T)));
  }

  template <typename T>
  void map(const T **objs, std::size_t num_objs) {
    MARISA_THROW_IF((objs == nullptr) && (num_objs != 0), MARISA_NULL_ERROR);
    MARISA_THROW_IF(num_objs > (SIZE_MAX / sizeof(T)), MARISA_SIZE_ERROR);
    *objs = static_cast<const T *>(map_data(sizeof(T) * num_objs));
  }

  void seek(std::size_t size);

  bool is_open() const;

  void clear();
  void swap(Mapper &rhs);

 private:
  const void *ptr_ = nullptr;
  void *origin_ = nullptr;
  std::size_t avail_ = 0;
  std::size_t size_ = 0;
#if (defined _WIN32) || (defined _WIN64)
  void *file_ = nullptr;
  void *map_ = nullptr;
#else   // (defined _WIN32) || (defined _WIN64)
  int fd_ = -1;
#endif  // (defined _WIN32) || (defined _WIN64)

  void open_(const char *filename, int flags);
  void open_(const void *ptr, std::size_t size);

  const void *map_data(std::size_t size);
};

}  // namespace marisa::grimoire::io

#endif  // MARISA_GRIMOIRE_IO_MAPPER_H_
