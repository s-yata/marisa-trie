#ifndef MARISA_GRIMOIRE_VECTOR_H_
#define MARISA_GRIMOIRE_VECTOR_H_

#include "marisa/grimoire/vector/bit-vector.h"
#include "marisa/grimoire/vector/flat-vector.h"
#include "marisa/grimoire/vector/vector.h"

namespace marisa::grimoire {

using vector::Vector;
typedef vector::FlatVector FlatVector;
typedef vector::BitVector BitVector;

}  // namespace marisa::grimoire

#endif  // MARISA_GRIMOIRE_VECTOR_H_
