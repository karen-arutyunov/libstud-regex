//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// difference_type position(size_type sub = 0) const;

#include <libstud/regex/regex.hxx>

#include <iterator>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::distance;

void
test()
{
    match_results<const char*> m;
    const char s[] = "abcdefghijk";
    assert(regex_search(s, m, regex("cd((e)fg)hi")));
    assert(m.position() == distance(s, m[0].first));
    assert(m.position(0) == distance(s, m[0].first));
    assert(m.position(1) == distance(s, m[1].first));
    assert(m.position(2) == distance(s, m[2].first));
    assert(m.position(3) == distance(s, m[3].first));
    assert(m.position(4) == distance(s, m[4].first));
}

int main(int, char**)
{
    test();

  return 0;
}
