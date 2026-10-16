//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// bool ready() const;

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

void
test1()
{
    match_results<const char*> m;
    const char s[] = "abcdefghijk";
    assert(m.ready() == false);
    regex_search(s, m, regex("cd((e)fg)hi"));
    assert(m.ready() == true);
}

void
test2()
{
    match_results<const char*> m;
    const char s[] = "abcdefghijk";
    assert(m.ready() == false);
    regex_search(s, m, regex("z"));
    assert(m.ready() == true);
}

int main(int, char**)
{
    test1();
    test2();

  return 0;
}
