//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// const_reference operator[](size_type n) const;

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

void
test(regex_constants::syntax_option_type syntax)
{
    match_results<const char*> m;
    const char s[] = "abcdefghijk";
    assert(regex_search(s, m, regex("cd((e)fg)hi|(z)", syntax)));

    assert(m.size() == 4);

    assert(m[0].first == s+2);
    assert(m[0].second == s+9);
    assert(m[0].matched == true);

    assert(m[1].first == s+4);
    assert(m[1].second == s+7);
    assert(m[1].matched == true);

    assert(m[2].first == s+4);
    assert(m[2].second == s+5);
    assert(m[2].matched == true);

    assert(m[3].first == s+11);
    assert(m[3].second == s+11);
    assert(m[3].matched == false);

    assert(m[4].first == s+11);
    assert(m[4].second == s+11);
    assert(m[4].matched == false);
}

int main(int, char**)
{
    test(regex_constants::ECMAScript);
    test(regex_constants::extended);

  return 0;
}
