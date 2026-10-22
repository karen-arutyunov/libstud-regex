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

// std::regex in ECMAScript mode should not ignore capture groups inside lookahead assertions.
// For example, matching /(?=(a))(a)/ to "a" should yield two captures: \1 = "a", \2 = "a"

#include <libstud/regex/regex.hxx>

#include <string>

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;

int main(int, char**)
{
    {
        regex re("^(?=(.))a$");
        assert(re.mark_count() == 1);

        string s("a");
        smatch m;
        assert(regex_match(s, m, re));
        assert(m.size() == 2);
        assert(m[0] == "a");
        assert(m[1] == "a");
    }

    {
        regex re("^(a)(?=(.))(b)$");
        assert(re.mark_count() == 3);

        string s("ab");
        smatch m;
        assert(regex_match(s, m, re));
        assert(m.size() == 4);
        assert(m[0] == "ab");
        assert(m[1] == "a");
        assert(m[2] == "b");
        assert(m[3] == "b");
    }

    {
        regex re("^(.)(?=(.)(?=.(.)))(...)$");
        assert(re.mark_count() == 4);

        string s("abcd");
        smatch m;
        assert(regex_match(s, m, re));
        assert(m.size() == 5);
        assert(m[0] == "abcd");
        assert(m[1] == "a");
        assert(m[2] == "b");
        assert(m[3] == "d");
        assert(m[4] == "bcd");
    }

    {
        regex re("^(a)(?!([^b]))(.c)$");
        assert(re.mark_count() == 3);

        string s("abc");
        smatch m;
        assert(regex_match(s, m, re));
        assert(m.size() == 4);
        assert(m[0] == "abc");
        assert(m[1] == "a");
        assert(m[2] == "");
        assert(m[3] == "bc");
    }

    {
        regex re("^(?!((b)))(?=(.))(?!(abc)).b$");
        assert(re.mark_count() == 4);

        string s("ab");
        smatch m;
        assert(regex_match(s, m, re));
        assert(m.size() == 5);
        assert(m[0] == "ab");
        assert(m[1] == "");
        assert(m[2] == "");
        assert(m[3] == "a");
        assert(m[4] == "");
    }

  return 0;
}
