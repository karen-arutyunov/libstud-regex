//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17

// <regex>

// class regex_token_iterator<BidirectionalIterator, charT, traits>

// bool operator==(default_sentinel_t) const { return *this == regex_iterator(); } // since C++20

#include <libstud/regex/regex.hxx>

#include <iterator>

#include "test_comparisons.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

#ifdef __cpp_lib_ranges
using std::default_sentinel;
#endif

int main(int, char**) {
  AssertEqualityReturnBool<cregex_iterator>();

#ifdef __cpp_lib_ranges
  {
    cregex_iterator i;
    assert(testEquality(i, default_sentinel, true));
  }
#endif

  AssertEqualityReturnBool<sregex_token_iterator>();

#ifdef __cpp_lib_ranges
  {
    sregex_token_iterator i;
    assert(testEquality(i, default_sentinel, true));
  }
#endif

  return 0;
}
