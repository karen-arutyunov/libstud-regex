//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator> class sub_match;

// template <class charT, class ST, class BiIter>
//     basic_ostream<charT, ST>&
//     operator<<(basic_ostream<charT, ST>& os, const sub_match<BiIter>& m);

#include <libstud/regex.hxx>

#include <string>
#include <sstream>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;
using std::wstring;
using std::basic_string;
using std::basic_ostringstream;

template <class CharT>
void
test(const std::basic_string<CharT>& s)
{
    typedef basic_string<CharT> string;
    typedef sub_match<typename string::const_iterator> SM;
    typedef basic_ostringstream<CharT> ostringstream;
    SM sm;
    sm.first = s.begin();
    sm.second = s.end();
    sm.matched = true;
    ostringstream os;
    os << sm;
    assert(os.str() == s);
}

int main(int, char**)
{
    test(string("123"));
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test(wstring(L"123"));
#endif

  return 0;
}
