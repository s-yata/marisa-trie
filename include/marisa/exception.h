#ifndef MARISA_EXCEPTION_H_
#define MARISA_EXCEPTION_H_

#include <exception>

// Please don't #include this header directly.
// This header is #included from "marisa/base.h".

namespace marisa {

// An exception object keeps a filename, a line number, an error code and an
// error message. The message format is as follows:
//  "__FILE__:__LINE__: error_code: error_message"
class Exception : public std::exception {
 public:
  Exception(const char *filename, int line, ErrorCode error_code,
            const char *error_message) noexcept
      : std::exception(), filename_(filename), line_(line),
        error_code_(error_code), error_message_(error_message) {}
  Exception(const Exception &ex) noexcept = default;
  ~Exception() noexcept override;

  Exception &operator=(const Exception &rhs) noexcept;

  const char *filename() const noexcept {
    return filename_;
  }
  int line() const noexcept {
    return line_;
  }
  ErrorCode error_code() const noexcept {
    return error_code_;
  }
  const char *error_message() const noexcept {
    return error_message_;
  }

  const char *what() const noexcept override {
    return error_message_;
  }

 private:
  const char *filename_;
  int line_;
  ErrorCode error_code_;
  const char *error_message_;
};

// These macros are used to convert a line number to a string constant.
#define MARISA_INT_TO_STR(value) #value
#define MARISA_LINE_TO_STR(line) MARISA_INT_TO_STR(line)
#define MARISA_LINE_STR          MARISA_LINE_TO_STR(__LINE__)

// MARISA_THROW throws an exception with a filename, a line number, an error
// code and an error message. The message format is as follows:
//  "__FILE__:__LINE__: error_code: error_message"
#define MARISA_THROW(error_code, error_message)                          \
  (throw marisa::Exception(__FILE__, __LINE__, error_code,               \
                           __FILE__ ":" MARISA_LINE_STR ": " #error_code \
                                    ": " error_message))

// MARISA_THROW_IF throws an exception if `condition' is true.
#define MARISA_THROW_IF(condition, error_code) \
  (void)((!(condition)) || (MARISA_THROW(error_code, #condition), 0))

// MARISA_DEBUG_IF is ignored if _DEBUG is undefined. So, it is useful for
// debugging time-critical codes.
#ifdef _DEBUG
 #define MARISA_DEBUG_IF(cond, error_code) MARISA_THROW_IF(cond, error_code)
#else
 #define MARISA_DEBUG_IF(cond, error_code)
#endif

#ifndef MARISA_USE_EXCEPTIONS
 #if defined(__GNUC__) && !defined(__EXCEPTIONS)
  #define MARISA_USE_EXCEPTIONS 0
 #elif defined(__clang__) && !defined(__cpp_exceptions)
  #define MARISA_USE_EXCEPTIONS 0
 #elif defined(_MSC_VER) && !_HAS_EXCEPTIONS
  #define MARISA_USE_EXCEPTIONS 0
 #else
  #define MARISA_USE_EXCEPTIONS 1
 #endif
#endif

#if MARISA_USE_EXCEPTIONS
 #define MARISA_TRY      try
 #define MARISA_CATCH(x) catch (x)
#else
 #define MARISA_TRY      if (true)
 #define MARISA_CATCH(x) if (false)
#endif

}  // namespace marisa

#endif  // MARISA_EXCEPTION_H_
