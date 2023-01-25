#include "marisa/exception.h"

namespace marisa {

/**
 * This is defined here for the following reasons.
 *
 * 1. Virtual destructors are best not defined in a header to be included in many compilation units.
 * Defining it here in a single compilation unit prevents multiple vtables from being generated and causing
 * a compiler to be confused as to which is the true vtable, like with full link time optimization.
 * By reducing the number of vtable instances, you also reduce the size of your library or application.
 * You can see warnings around this with the -Wweak-vtables compiler option. Such issues may not be seen till runtime.
 * Using the default keyword on the destructor is the same as defining it in the header.
 *
 * 2. Exceptions can not be thrown from destructors. When an exception is thrown from a destructor
 * while the stack is unwinding from another thrown exception, then the program will crash instead
 * of throwing the exception. See https://isocpp.org/wiki/faq/exceptions#ctor-exceptions
 */
Exception::~Exception() noexcept {}

}
