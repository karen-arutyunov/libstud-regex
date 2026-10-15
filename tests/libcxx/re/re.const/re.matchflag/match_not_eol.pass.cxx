//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// match_not_eol:
//     The last character in the sequence [first,last) shall be treated as
//     though it is not at the end of a line, so the character "$" in
//     the regular expression shall not match [last,last).

#include <libstud/regex.hxx>

#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;

int main(int, char**)
{
    {
    string target = "foo";
    regex re("foo$");
    assert( regex_match(target, re));
    assert(!regex_match(target, re, regex_constants::match_not_eol));
    }

    {
    string target = "foo";
    regex re("foo");
    assert( regex_match(target, re));
    assert( regex_match(target, re, regex_constants::match_not_eol));
    }

    {
    string target = "refoo";
    regex re("foo$");
    assert( regex_search(target, re));
    assert(!regex_search(target, re, regex_constants::match_not_eol));
    }

    {
    string target = "refoo";
    regex re("foo");
    assert( regex_search(target, re));
    assert( regex_search(target, re, regex_constants::match_not_eol));
    }

    {
      string target = "foo";
      regex re("$");
      assert(regex_search(target, re));
      assert(!regex_search(target, re, regex_constants::match_not_eol));

      smatch match;
      assert(regex_search(target, match, re));
      assert(match.position(0) == 3);
      assert(match.length(0) == 0);
      assert(!regex_search(target, match, re, regex_constants::match_not_eol));
      assert(match.length(0) == 0);
    }

    {
      string target = "foo";
      regex re("$", regex::multiline);
      smatch match;
      assert(regex_search(target, match, re));
      assert(match.position(0) == 3);
      assert(match.length(0) == 0);
      assert(!regex_search(target, match, re, regex_constants::match_not_eol));
      assert(match.length(0) == 0);
    }

    {
      string target = "foo";
      regex re("$");
      assert(!regex_match(target, re));
      assert(!regex_match(target, re, regex_constants::match_not_eol));
    }

    {
      string target = "a";
      regex re("^b*$");
      assert(!regex_search(target, re));
      assert(!regex_search(target, re, regex_constants::match_not_eol));
    }

  return 0;
}
