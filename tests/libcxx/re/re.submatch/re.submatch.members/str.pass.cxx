//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator> class sub_match;

// string_type str() const;

#include <libstud/regex/regex.hxx>

#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;
using std::wstring;

int main(int, char**)
{
    {
        typedef char CharT;
        typedef sub_match<const CharT*> SM;
        SM sm = SM();
        SM::string_type str = sm.str();
        assert(str.empty());
        const CharT s[] = {'1', '2', '3', 0};
        sm.first = s;
        sm.second = s + 3;
        sm.matched = true;
        str = sm.str();
        assert(str == string("123"));
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        typedef wchar_t CharT;
        typedef sub_match<const CharT*> SM;
        SM sm = SM();
        SM::string_type str = sm.str();
        assert(str.empty());
        const CharT s[] = {'1', '2', '3', 0};
        sm.first = s;
        sm.second = s + 3;
        sm.matched = true;
        str = sm.str();
        assert(str == wstring(L"123"));
    }
#endif

  return 0;
}
