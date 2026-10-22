//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>
// UNSUPPORTED: no-exceptions
// UNSUPPORTED: c++03

// the "n" and "m" in `a{n,m}` should be within the numeric limits.
// requirement "m >= n" should be checked.

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**) {
  // test that `n <= m`
  for (regex_constants::syntax_option_type op :
       {regex::basic}) {
    try {
      TEST_IGNORE_NODISCARD regex("a\\{3,2\\}", op);
      assert(false);
    } catch (const regex_error &e) {
      assert(e.code() == regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == regex_constants::error_badbrace);
    }
  }
  for (regex_constants::syntax_option_type op :
       {regex::ECMAScript, regex::extended, regex::egrep,
        regex::awk}) {
    try {
      TEST_IGNORE_NODISCARD regex("a{3,2}", op);
      assert(false);
    } catch (const regex_error &e) {
      assert(e.code() == regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == regex_constants::error_badbrace);
    }
  }

  // test that both bounds are within the limit
  for (regex_constants::syntax_option_type op :
       {regex::basic}) {
    try {
      TEST_IGNORE_NODISCARD regex("a\\{100000000000000000000,10000000000000000000\\}", op);
      assert(false);
    } catch (const regex_error &e) {
      assert(e.code() == regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == regex_constants::error_badbrace);
    }
  }
  for (regex_constants::syntax_option_type op :
       {regex::ECMAScript, regex::extended, regex::egrep,
        regex::awk}) {
    try {
      TEST_IGNORE_NODISCARD regex("a{100000000000000000000,10000000000000000000}", op);
      assert(false);
    } catch (const regex_error &e) {
      assert(e.code() == regex_constants::error_badbrace);
      LIBCPP_ASSERT(e.code() == regex_constants::error_badbrace);
    }
  }
  return 0;
}
