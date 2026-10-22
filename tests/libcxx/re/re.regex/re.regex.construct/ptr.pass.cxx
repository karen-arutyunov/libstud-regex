//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// basic_regex(const charT* p);

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

template <class CharT>
void
test(const CharT* p, unsigned mc)
{
    basic_regex<CharT> r(p);
    assert(r.flags() == regex_constants::ECMAScript);
    assert(r.mark_count() == mc);
}

int main(int, char**)
{
    test("\\(a\\)", 0);
    test("\\(a[bc]\\)", 0);
    test("\\(a\\([bc]\\)\\)", 0);
    test("(a([bc]))", 2);

  return 0;
}
