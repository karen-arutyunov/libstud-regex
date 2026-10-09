#pragma once

#include <libstud/regex/export.hxx>

#ifdef __cplusplus
#  if __cplusplus <= 201103L
#    error C++14 compiler required
#  elif __cplusplus <= 201402L
#    define LIBSTUD_REGEX_STD_VER 14
#  elif __cplusplus <= 201703L
#    define LIBSTUD_REGEX_STD_VER 17
#  elif __cplusplus <= 202002L
#    define LIBSTUD_REGEX_STD_VER 20
#  elif __cplusplus <= 202302L
#    define LIBSTUD_REGEX_STD_VER 23
#  elif __cplusplus <= 202603L
#    define LIBSTUD_REGEX_STD_VER 26
#  else
// Expected release year of the next C++ standard
#    define LIBSTUD_REGEX_STD_VER 29
#  endif
#else
#  error C++14 compiler required
#endif // __cplusplus

#undef LIBSTUD_REGEX_CXX03_LANG

// Avoid using `#pragma GCC system_header` which reduces noise, disabling
// warnings, etc.
//
#define LIBSTUD_REGEX_HAS_NO_PRAGMA_SYSTEM_HEADER    1

#define LIBSTUD_REGEX_BEGIN_NAMESPACE_STD            namespace stud {
#define LIBSTUD_REGEX_BEGIN_EXPLICIT_ABI_ANNOTATIONS
#define LIBSTUD_REGEX_END_EXPLICIT_ABI_ANNOTATIONS
#define LIBSTUD_REGEX_END_NAMESPACE_STD              }

#define LIBSTUD_REGEX_PUSH_MACROS
#define LIBSTUD_REGEX_POP_MACROS

#define LIBSTUD_REGEX_HIDE_FROM_ABI
#define LIBSTUD_REGEX_HIDE_FROM_ABI_VIRTUAL
#define LIBSTUD_REGEX_EXPORTED_FROM_ABI              LIBSTUD_REGEX_SYMEXPORT

#define LIBSTUD_REGEX_CONSTEXPR                      constexpr
#define LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14          constexpr

#define LIBSTUD_REGEX_HAS_EXCEPTIONS                 1
#define LIBSTUD_REGEX_HAS_LOCALIZATION               1
#define LIBSTUD_REGEX_ABI_REGEX_CONSTANTS_NONZERO    1
#define LIBSTUD_REGEX_HAS_WIDE_CHARACTERS            1

#define LIBSTUD_REGEX_AVAILABILITY_PMR

#define LIBSTUD_REGEX_VERBOSE_ABORT(x)               std::abort ()
#define LIBSTUD_REGEX_PREFERRED_NAME(x)
#define LIBSTUD_REGEX_IF_WIDE_CHARACTERS(x)

#define LIBSTUD_REGEX_NODEBUG
#define LIBSTUD_REGEX_ASSERT_PEDANTIC(e, m)             assert (e)
#define LIBSTUD_REGEX_ASSERT_VALID_ELEMENT_ACCESS(e, m) assert (e)

#define LIBSTUD_REGEX_WARN_UNUSED

#define LIBSTUD_REGEX_NOEXCEPT       noexcept
#define LIBSTUD_REGEX_NOEXCEPT_(...) noexcept(__VA_ARGS__)

#if defined(__NEWLIB__) || defined(_NEWLIB_VERSION)
#  define LIBSTUD_REGEX_LIBC_NEWLIB                  1
#endif
