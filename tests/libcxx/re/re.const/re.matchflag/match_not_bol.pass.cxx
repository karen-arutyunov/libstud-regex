//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// match_not_bol:
//     The first character in the sequence [first,last) shall be treated as
//     though it is not at the beginning of a line, so the character ^ in the
//     regular expression shall not match [first,first).

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
    regex re("^foo");
    assert( regex_match(target, re));
    assert(!regex_match(target, re, regex_constants::match_not_bol));
    }

    {
    string target = "foo";
    regex re("foo");
    assert( regex_match(target, re));
    assert( regex_match(target, re, regex_constants::match_not_bol));
    }

    {
    string target = "fooby";
    regex re("^foo");
    assert( regex_search(target, re));
    assert(!regex_search(target, re, regex_constants::match_not_bol));
    }

    {
    string target = "fooby";
    regex re("foo");
    assert( regex_search(target, re));
    assert( regex_search(target, re, regex_constants::match_not_bol));
    }

  return 0;
}
