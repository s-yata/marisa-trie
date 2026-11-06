#ifndef MARISA_IOSTREAM_H_
#define MARISA_IOSTREAM_H_

#include <iosfwd>

#include "marisa/export.h"

namespace marisa {

class Trie;

MARISA_API std::istream &read(std::istream &stream, Trie *trie);
MARISA_API std::ostream &write(std::ostream &stream, const Trie &trie);

MARISA_API std::istream &operator>>(std::istream &stream, Trie &trie);
MARISA_API std::ostream &operator<<(std::ostream &stream, const Trie &trie);

}  // namespace marisa

#endif  // MARISA_IOSTREAM_H_
