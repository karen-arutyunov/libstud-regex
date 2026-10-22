//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class regex_token_iterator<BidirectionalIterator, charT, traits>

// regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b,
//                      const regex_type& re,
//                      const std::vector<int>& submatches,
//                      regex_constants::match_flag_type m =
//                                              regex_constants::match_default);

#include <libstud/regex/regex.hxx>

#include <vector>
#include <iterator>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::vector;
using std::begin;
using std::end;

int main(int, char**)
{
    {
        regex phone_numbers("\\d{3}-(\\d{4})");
        const char phone_book[] = "start 555-1234, 555-2345, 555-3456 end";
        vector<int> v;
        v.push_back(-1);
        v.push_back(-1);
        cregex_token_iterator i(begin(phone_book), end(phone_book)-1,
                                     phone_numbers, v);
        assert(i != cregex_token_iterator());
        assert(i->str() == "start ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "start ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == " end");
        ++i;
        assert(i == cregex_token_iterator());
    }
    {
        regex phone_numbers("\\d{3}-(\\d{4})");
        const char phone_book[] = "start 555-1234, 555-2345, 555-3456 end";
        vector<int> v;
        v.push_back(-1);
        v.push_back(0);
        cregex_token_iterator i(begin(phone_book), end(phone_book)-1,
                                     phone_numbers, v);
        assert(i != cregex_token_iterator());
        assert(i->str() == "start ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-1234");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-2345");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-3456");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == " end");
        ++i;
        assert(i == cregex_token_iterator());
    }
    {
        regex phone_numbers("\\d{3}-(\\d{4})");
        const char phone_book[] = "start 555-1234, 555-2345, 555-3456 end";
        vector<int> v;
        v.push_back(-1);
        v.push_back(0);
        v.push_back(1);
        cregex_token_iterator i(begin(phone_book), end(phone_book)-1,
                                     phone_numbers, v);
        assert(i != cregex_token_iterator());
        assert(i->str() == "start ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-1234");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "1234");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-2345");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "2345");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == ", ");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-3456");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == "3456");
        ++i;
        assert(i != cregex_token_iterator());
        assert(i->str() == " end");
        ++i;
        assert(i == cregex_token_iterator());
    }

  return 0;
}
