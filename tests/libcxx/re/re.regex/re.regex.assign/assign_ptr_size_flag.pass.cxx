//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// basic_regex& assign(const charT* ptr, size_t len, flag_type f);

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**)
{
    regex r0;
    r0.assign("(a([bc]))", 9);
    assert(r0.flags() == regex::ECMAScript);
    assert(r0.mark_count() == 2);

    regex r1;
    r1.assign("(a([bc]))", 9, regex::ECMAScript);
    assert(r1.flags() == regex::ECMAScript);
    assert(r1.mark_count() == 2);

    regex r2;
    r2.assign("(a([bc]))", 9, regex::extended);
    assert(r2.flags() == regex::extended);
    assert(r2.mark_count() == 2);

  return 0;
}
