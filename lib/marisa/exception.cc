#include "marisa/base.h"

namespace marisa {

// This is defined here for the following reason.
//
// Virtual destructors are best not defined in a header to be included in many
// compilation units.
// Defining it here in a single compilation unit prevents multiple vtables
// from being generated and causing a compiler to be confused as to which is
// the true vtable, like with full link time optimization.
// By reducing the number of vtable instances, you also reduce the size of
// your library or application.
//
// You can see warnings around this with the -Wweak-vtables compiler option.
// Such issues may not be seen till runtime.
Exception::~Exception() noexcept = default;

}  // namespace marisa