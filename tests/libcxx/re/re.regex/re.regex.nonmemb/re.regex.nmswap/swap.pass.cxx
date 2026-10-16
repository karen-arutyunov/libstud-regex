//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// template <class charT, class traits>
//   void swap(basic_regex<charT, traits>& lhs, basic_regex<charT, traits>& rhs);

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**)
{
    regex r1("(a([bc]))");
    regex r2;
    swap(r2, r1);
    assert(r1.flags() == regex::ECMAScript);
    assert(r1.mark_count() == 0);
    assert(r2.flags() == regex::ECMAScript);
    assert(r2.mark_count() == 2);

  return 0;
}
