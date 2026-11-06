#ifndef MARISA_MYSTDIO_H_
#define MARISA_MYSTDIO_H_

#include <cstdio>

#include "marisa/export.h"

namespace marisa {

class Trie;

MARISA_API void fread(std::FILE *file, Trie *trie);
MARISA_API void fwrite(std::FILE *file, const Trie &trie);

}  // namespace marisa

#endif  // MARISA_MYSTDIO_H_
