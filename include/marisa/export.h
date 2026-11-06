#ifndef MARISA_EXPORT_H_
#define MARISA_EXPORT_H_

// MARISA_API marks the public interface of the library, so that it can be
// exported from a shared library on Windows and kept visible when compiling
// with hidden visibility on other platforms.
//
// Define MARISA_SHARED when building or consuming Marisa as a shared library.
// The library itself is additionally compiled with MARISA_BUILDING_LIBRARY,
// which selects __declspec(dllexport) instead of __declspec(dllimport).
#if defined(_WIN32) && defined(MARISA_SHARED)
 #ifdef MARISA_BUILDING_LIBRARY
  #define MARISA_API __declspec(dllexport)
 #else
  #define MARISA_API __declspec(dllimport)
 #endif
#elif defined(__GNUC__) || defined(__clang__)
 #define MARISA_API __attribute__((visibility("default")))
#else
 #define MARISA_API
#endif

#endif  // MARISA_EXPORT_H_
