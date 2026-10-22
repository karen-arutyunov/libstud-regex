//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17

// match_results

#include <libstud/regex/regex.hxx>

#ifdef __cpp_lib_concepts
#  include <concepts>
#endif

#ifdef __cpp_lib_ranges
#  include <ranges>
#endif

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

#ifdef __cpp_lib_concepts
using std::same_as;
#endif

#ifdef __cpp_lib_ranges
namespace ranges = std::ranges;

#  ifdef __cpp_lib_concepts
static_assert(same_as<ranges::iterator_t<cmatch>, cmatch::iterator>);
#  endif

static_assert(ranges::common_range<cmatch>);
static_assert(ranges::random_access_range<cmatch>);
static_assert(ranges::contiguous_range<cmatch>);
static_assert(!ranges::view<cmatch>);
static_assert(ranges::sized_range<cmatch>);
static_assert(!ranges::borrowed_range<cmatch>);

// For libstdc++ 11 and earlier, due to some bugs,
// std::ranges::viewable_range<> can evaluate to false for perfectly valid
// types.
//
// Note: _GLIBCXX_RELEASE macro was introduced in libstdc++ 7.1.
//
#  if defined(_GLIBCXX_RELEASE) && _GLIBCXX_RELEASE >= 12
static_assert(ranges::viewable_range<cmatch>);
#  endif

#  ifdef __cpp_lib_concepts
static_assert(same_as<ranges::iterator_t<cmatch const>, cmatch::const_iterator>);
#  endif

static_assert(ranges::common_range<cmatch const>);
static_assert(ranges::random_access_range<cmatch const>);
static_assert(ranges::contiguous_range<cmatch const>);
static_assert(!ranges::view<cmatch const>);
static_assert(ranges::sized_range<cmatch const>);
static_assert(!ranges::borrowed_range<cmatch const>);
static_assert(!ranges::viewable_range<cmatch const>);
#endif

int main(int, char**)
{
}
