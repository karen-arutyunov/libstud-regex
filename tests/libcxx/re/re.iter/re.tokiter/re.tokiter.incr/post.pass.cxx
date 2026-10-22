//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class regex_token_iterator<BidirectionalIterator, charT, traits>

// regex_token_iterator& operator++(int);

#include <libstud/regex/regex.hxx>

#include <iterator>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::begin;
using std::end;

int main(int, char**)
{
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "start 555-1234, 555-2345, 555-3456 end";
        cregex_token_iterator i(begin(phone_book), end(phone_book)-1,
                                     phone_numbers, -1);
        cregex_token_iterator i2 = i;
        cregex_token_iterator i3;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i->str() == "start ");
        assert(i2->str() == "start ");
        i3 = i++;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i->str() == ", ");
        assert(i2->str() == "start ");
        assert(i3->str() == "start ");
        i3 = i++;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i->str() == ", ");
        assert(i2->str() == "start ");
        assert(i3->str() == ", ");
        i3 = i++;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i->str() == " end");
        assert(i2->str() == "start ");
        assert(i3->str() == ", ");
        i3 = i++;
        assert(i  == cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i2->str() == "start ");
        assert(i3->str() == " end");
    }
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "start 555-1234, 555-2345, 555-3456 end";
        cregex_token_iterator i(begin(phone_book), end(phone_book)-1,
                                     phone_numbers, -1);
        cregex_token_iterator i2 = i;
        cregex_token_iterator i3;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i->str() == "start ");
        assert(i2->str() == "start ");
        i3 = i;
        ++i;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i->str() == ", ");
        assert(i2->str() == "start ");
        assert(i3->str() == "start ");
        i3 = i;
        ++i;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i->str() == ", ");
        assert(i2->str() == "start ");
        assert(i3->str() == ", ");
        i3 = i;
        ++i;
        assert(i  != cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i->str() == " end");
        assert(i2->str() == "start ");
        assert(i3->str() == ", ");
        i3 = i;
        ++i;
        assert(i  == cregex_token_iterator());
        assert(i2 != cregex_token_iterator());
        assert(i3 != cregex_token_iterator());
        assert(i2->str() == "start ");
        assert(i3->str() == " end");
    }
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "start 555-1234, 555-2345, 555-3456 end";
        cregex_token_iterator i(begin(phone_book), end(phone_book)-1,
                                     phone_numbers);
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-1234");
        i++;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-2345");
        i++;
        assert(i != cregex_token_iterator());
        assert(i->str() == "555-3456");
        i++;
        assert(i == cregex_token_iterator());
    }
    {
        regex phone_numbers("\\d{3}-(\\d{4})");
        const char phone_book[] = "start 555-1234, 555-2345, 555-3456 end";
        cregex_token_iterator i(begin(phone_book), end(phone_book)-1,
                                     phone_numbers, 1);
        assert(i != cregex_token_iterator());
        assert(i->str() == "1234");
        i++;
        assert(i != cregex_token_iterator());
        assert(i->str() == "2345");
        i++;
        assert(i != cregex_token_iterator());
        assert(i->str() == "3456");
        i++;
        assert(i == cregex_token_iterator());
    }

  return 0;
}
