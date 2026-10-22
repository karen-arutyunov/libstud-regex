//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// template <class ST, class SA>
//    basic_regex(const basic_string<charT, ST, SA>& s);

#include <libstud/regex/regex.hxx>

#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;

template <class String>
void
test(const String& p, unsigned mc)
{
    basic_regex<typename String::value_type> r(p);
    assert(r.flags() == regex_constants::ECMAScript);
    assert(r.mark_count() == mc);
}

int main(int, char**)
{
    test(string("\\(a\\)"), 0);
    test(string("\\(a[bc]\\)"), 0);
    test(string("\\(a\\([bc]\\)\\)"), 0);
    test(string("(a([bc]))"), 2);

  return 0;
}
