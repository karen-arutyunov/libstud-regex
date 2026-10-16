//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// const_iterator cbegin() const;
// const_iterator cend() const;

#include <libstud/regex.hxx>

#include <cstddef> // size_t

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::size_t;

void
test()
{
    match_results<const char*> m;
    const char s[] = "abcdefghijk";
    assert(regex_search(s, m, regex("cd((e)fg)hi")));

    match_results<const char*>::const_iterator i = m.cbegin();
    match_results<const char*>::const_iterator e = m.cend();

    assert(static_cast<size_t>(e - i) == m.size());
    for (int j = 0; i != e; ++i, ++j)
        assert(*i == m[j]);
}

int main(int, char**)
{
    test();

  return 0;
}
