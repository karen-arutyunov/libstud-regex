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
//     regex_match(BidirectionalIterator first, BidirectionalIterator last,
//                  match_results<BidirectionalIterator, Allocator>& m,
//                  const basic_regex<charT, traits>& e,
//                  regex_constants::match_flag_type flags = regex_constants::match_default);

#include <libstud/regex.hxx>

#include <string> // char_traits

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::char_traits;

int main(int, char**)
{
    {
        cmatch m;
        const char s[] = "tournament";
        assert(regex_match(s, m, regex("tour\nto\ntournament",
                regex_constants::egrep)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s + char_traits<char>::length(s));
        assert(m.length(0) == 10);
        assert(m.position(0) == 0);
        assert(m.str(0) == "tournament");
    }
    {
        cmatch m;
        const char s[] = "ment";
        assert(!regex_match(s, m, regex("tour\n\ntournament",
                regex_constants::egrep)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "tournament";
        assert(regex_match(s, m, regex("(tour|to|tournament)+\ntourna",
                regex_constants::egrep)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s + char_traits<char>::length(s));
        assert(m.length(0) == 10);
        assert(m.position(0) == 0);
        assert(m.str(0) == "tournament");
    }
    {
        cmatch m;
        const char s[] = "tourna";
        assert(regex_match(s, m, regex("(tour|to|tournament)+\ntourna",
                regex_constants::egrep)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s + char_traits<char>::length(s));
        assert(m.length(0) == 6);
        assert(m.position(0) == 0);
        assert(m.str(0) == "tourna");
    }

  return 0;
}
