#pragma once

#include <libstud/regex/export.hxx>

// Note that MSVC 12.0 (VS 2013) added the initial support for C++14 (see the
// "Microsoft C/C++ language conformance by Visual Studio version"
// documentation for details). However, until MSVC 15.7 (VS 2017) the
// __cplusplus value remained at 199711L (C++98 / C++03; see the "MSVC now
// correctly reports __cplusplus" article for details).
//
#ifdef __cplusplus
#  if __cplusplus <= 201103L
#    if defined(_MSC_VER) && _MSC_VER >= 1800 // MSVC >= 12.0
#      define LIBSTUD_REGEX_STD_VER 14
#    else
#      error C++14 compiler required
#    endif
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
#undef LIBSTUD_REGEX_USE_FROZEN_CXX03_HEADERS

#if LIBSTUD_REGEX_STD_VER >= 20
#  if (!defined(__GLIBCXX__) || __has_include(<version>))
#    include <version>
#  endif
#endif

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

// Note that Clang 3.7 doesn't provide complete support for C++17. In
// particular, it doesn't support the nodiscard and fallthrough attributes.
//
#if LIBSTUD_REGEX_STD_VER >= 17
#  ifdef __has_cpp_attribute
#    if __has_cpp_attribute(nodiscard)
#      define LIBSTUD_REGEX_NODISCARD [[nodiscard]]
#    else
#      define LIBSTUD_REGEX_NODISCARD
#    endif
#    if __has_cpp_attribute(fallthrough)
#      define LIBSTUD_REGEX_FALLTHROUGH [[fallthrough]]
#    else
#      define LIBSTUD_REGEX_FALLTHROUGH
#    endif
#  else
#    define LIBSTUD_REGEX_NODISCARD
#    define LIBSTUD_REGEX_FALLTHROUGH
#  endif
#else
#  define LIBSTUD_REGEX_NODISCARD
#  define LIBSTUD_REGEX_FALLTHROUGH
#endif
