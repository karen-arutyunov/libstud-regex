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

// template <class BidirectionalIterator, class Allocator, class charT, class traits>
//     bool
//     regex_match(BidirectionalIterator first, BidirectionalIterator last,
//                  match_results<BidirectionalIterator, Allocator>& m,
//                  const basic_regex<charT, traits>& e,
//                  regex_constants::match_flag_type flags = regex_constants::match_default);

// Throw exception after spent too many cycles with respect to the length of the input string.

#include <libstud/regex.hxx>

#include <string>

#undef NDEBUG
#include <cassert>

int main(int, char**) {
  for (stud::regex_constants::syntax_option_type op :
       {stud::regex::ECMAScript, stud::regex::extended, stud::regex::egrep,
        stud::regex::awk}) {
    try {
      bool b = stud::regex_match(
          "aaaaaaaaaaaaaaaaaaaa",
          stud::regex(
              "a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?aaaaaaaaaaaaaaaaaaaa",
              op));
      assert(false);
      assert(b);
    } catch (const stud::regex_error &e) {
      assert(e.code() == stud::regex_constants::error_complexity);
    }
  }
  std::string s(100000, 'a');
  for (stud::regex_constants::syntax_option_type op :
       {stud::regex::ECMAScript, stud::regex::extended, stud::regex::egrep,
        stud::regex::awk}) {
    assert(stud::regex_match(s, stud::regex("a*", op)));
  }
  return 0;
}
