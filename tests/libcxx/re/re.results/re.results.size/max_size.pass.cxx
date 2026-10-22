//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// size_type max_size() const;

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

template <class CharT>
void
test()
{
    match_results<const CharT*> m;
    assert(m.max_size() > 0);
}

int main(int, char**)
{
    test<char>();
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>();
#endif

    return 0;
}
