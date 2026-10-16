//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// size_type size() const;
// bool empty() const;

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

template <class CharT>
void
test()
{
    match_results<const CharT*> m;
    assert(m.empty());
    assert(m.size() == 0);
    const char s[] = "abcdefghijk";
    assert(regex_search(s, m, regex("cd((e)fg)hi")));
    assert(!m.empty());
    assert(m.size() == 3);
}

int main(int, char**)
{
    test<char>();

  return 0;
}
