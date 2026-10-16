//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// const_reference suffix() const;

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

void
test()
{
    match_results<const char*> m;
    const char s[] = "abcdefghijk";
    assert(regex_search(s, m, regex("cd((e)fg)hi")));

    assert(m.suffix().first == s+9);
    assert(m.suffix().second == s+11);
    assert(m.suffix().matched == true);
}

int main(int, char**)
{
    test();

  return 0;
}
