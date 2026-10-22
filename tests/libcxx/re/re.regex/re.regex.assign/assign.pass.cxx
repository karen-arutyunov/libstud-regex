//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// basic_regex& assign(const basic_regex& that);

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**)
{
    regex r1("(a([bc]))");
    regex r2;
    r2.assign(r1);
    assert(r2.flags() == regex::ECMAScript);
    assert(r2.mark_count() == 2);
    assert(regex_search("ab", r2));

#ifndef TEST_HAS_NO_EXCEPTIONS
    bool caught = false;
    try { r2.assign("(def", regex::extended); }
    catch(regex_error &) { caught = true; }
    assert(caught);
    assert(r2.flags() == regex::ECMAScript);
    assert(r2.mark_count() == 2);
    assert(regex_search("ab", r2));
#endif

  return 0;
}
