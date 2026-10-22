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
//    basic_regex(const basic_string<charT, ST, SA>& s,
//                flag_type f = regex_constants::ECMAScript);

#include <libstud/regex/regex.hxx>

#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;

template <class String>
void
test(const String& p, regex_constants::syntax_option_type f, unsigned mc)
{
    basic_regex<typename String::value_type> r(p, f);
    assert(r.flags() == f);
    assert(r.mark_count() == mc);
}

int main(int, char**)
{
    test(string("\\(a\\)"), regex_constants::basic, 1);
    test(string("\\(a[bc]\\)"), regex_constants::basic, 1);
    test(string("\\(a\\([bc]\\)\\)"), regex_constants::basic, 2);
    test(string("(a([bc]))"), regex_constants::basic, 0);

    test(string("\\(a\\)"), regex_constants::extended, 0);
    test(string("\\(a[bc]\\)"), regex_constants::extended, 0);
    test(string("\\(a\\([bc]\\)\\)"), regex_constants::extended, 0);
    test(string("(a([bc]))"), regex_constants::extended, 2);

    test(string("\\(a\\)"), regex_constants::ECMAScript, 0);
    test(string("\\(a[bc]\\)"), regex_constants::ECMAScript, 0);
    test(string("\\(a\\([bc]\\)\\)"), regex_constants::ECMAScript, 0);
    test(string("(a([bc]))"), regex_constants::ECMAScript, 2);

    test(string("\\(a\\)"), regex_constants::awk, 0);
    test(string("\\(a[bc]\\)"), regex_constants::awk, 0);
    test(string("\\(a\\([bc]\\)\\)"), regex_constants::awk, 0);
    test(string("(a([bc]))"), regex_constants::awk, 2);

    test(string("\\(a\\)"), regex_constants::grep, 1);
    test(string("\\(a[bc]\\)"), regex_constants::grep, 1);
    test(string("\\(a\\([bc]\\)\\)"), regex_constants::grep, 2);
    test(string("(a([bc]))"), regex_constants::grep, 0);

    test(string("\\(a\\)"), regex_constants::egrep, 0);
    test(string("\\(a[bc]\\)"), regex_constants::egrep, 0);
    test(string("\\(a\\([bc]\\)\\)"), regex_constants::egrep, 0);
    test(string("(a([bc]))"), regex_constants::egrep, 2);

  return 0;
}
