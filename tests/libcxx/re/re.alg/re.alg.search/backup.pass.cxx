//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator, class Allocator, class charT, class traits>
//     bool
//     regex_search(BidirectionalIterator first, BidirectionalIterator last,
//                  match_results<BidirectionalIterator, Allocator>& m,
//                  const basic_regex<charT, traits>& e,
//                  regex_constants::match_flag_type flags = regex_constants::match_default);

#include <libstud/regex.hxx>

#include <list>
#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;
using std::list;

int main(int, char**)
{
    // This regex_iterator uses regex_search(__wrap_iter<_Iter> __first, ...)
    // Test for https://llvm.org/PR16240 fixed in r185273.
    {
        string s("aaaa a");
        regex re("\\ba");
        sregex_iterator it(s.begin(), s.end(), re);
        sregex_iterator end = sregex_iterator();

        assert(it->position(0) == 0);
        assert(it->length(0) == 1);

        ++it;
        assert(it->position(0) == 5);
        assert(it->length(0) == 1);

        ++it;
        assert(it == end);
    }

    // This regex_iterator uses regex_search(_BidirectionalIterator __first, ...)
    {
        string s("aaaa a");
        list<char> l(s.begin(), s.end());
        regex re("\\ba");
        regex_iterator<list<char>::iterator> it(l.begin(), l.end(), re);
        regex_iterator<list<char>::iterator> end = regex_iterator<list<char>::iterator>();

        assert(it->position(0) == 0);
        assert(it->length(0) == 1);

        ++it;
        assert(it->position(0) == 5);
        assert(it->length(0) == 1);

        ++it;
        assert(it == end);
    }

  return 0;
}
