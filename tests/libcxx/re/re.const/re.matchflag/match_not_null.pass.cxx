//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// match_not_null:
//     The regular expression shall not match an empty sequence.

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**)
{
  // When match_not_null is on, the regex engine should reject empty matches and
  // move on to try other solutions.
  cmatch m;
  assert(!regex_search("a", m, regex("b*"),
                            regex_constants::match_not_null));
  assert(regex_search("aa", m, regex("a*?"),
                           regex_constants::match_not_null));
  assert(m[0].length() == 1);
  assert(!regex_search("a", m, regex("b*", regex::extended),
                            regex_constants::match_not_null));
  assert(!regex_search(
      "a", m,
      regex("b*", regex::extended | regex_constants::nosubs),
      regex_constants::match_not_null));

  assert(!regex_match("", m, regex("a*"),
                           regex_constants::match_not_null));
  assert(!regex_match("", m, regex("a*", regex::extended),
                           regex_constants::match_not_null));
  assert(!regex_match(
      "", m,
      regex("a*", regex::extended | regex_constants::nosubs),
      regex_constants::match_not_null));

  return 0;
}
