//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class OutputIterator, class BidirectionalIterator,
//           class traits, class charT, class ST, class SA>
//     OutputIterator
//     regex_replace(OutputIterator out,
//                   BidirectionalIterator first, BidirectionalIterator last,
//                   const basic_regex<charT, traits>& e,
//                   const basic_string<charT, ST, SA>& fmt,
//                   regex_constants::match_flag_type flags =
//                                              regex_constants::match_default);

#include <libstud/regex.hxx>

#include <string>
#include <iterator>

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;
using std::begin;
using std::end;

int main(int, char**)
{
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "555-1234, 555-2345, 555-3456";
        typedef cpp17_output_iterator<char*> Out;
        typedef bidirectional_iterator<const char*> Bi;
        char buf[100] = {0};
        Out r = regex_replace(Out(buf), Bi(begin(phone_book)),
                                    Bi(end(phone_book)-1), phone_numbers,
                                    string("123-$&"));
        assert(base(r) == buf+40);
        assert(buf == string("123-555-1234, 123-555-2345, 123-555-3456"));
    }
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "555-1234, 555-2345, 555-3456";
        typedef cpp17_output_iterator<char*> Out;
        typedef bidirectional_iterator<const char*> Bi;
        char buf[100] = {0};
        Out r = regex_replace(Out(buf), Bi(begin(phone_book)),
                                    Bi(end(phone_book)-1), phone_numbers,
                                    string("123-$&"),
                                    regex_constants::format_sed);
        assert(base(r) == buf+43);
        assert(buf == string("123-$555-1234, 123-$555-2345, 123-$555-3456"));
    }
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "555-1234, 555-2345, 555-3456";
        typedef cpp17_output_iterator<char*> Out;
        typedef bidirectional_iterator<const char*> Bi;
        char buf[100] = {0};
        Out r = regex_replace(Out(buf), Bi(begin(phone_book)),
                                    Bi(end(phone_book)-1), phone_numbers,
                                    string("123-&"),
                                    regex_constants::format_sed);
        assert(base(r) == buf+40);
        assert(buf == string("123-555-1234, 123-555-2345, 123-555-3456"));
    }
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "555-1234, 555-2345, 555-3456";
        typedef cpp17_output_iterator<char*> Out;
        typedef bidirectional_iterator<const char*> Bi;
        char buf[100] = {0};
        Out r = regex_replace(Out(buf), Bi(begin(phone_book)),
                                    Bi(end(phone_book)-1), phone_numbers,
                                    string("123-$&"),
                                    regex_constants::format_no_copy);
        assert(base(r) == buf+36);
        assert(buf == string("123-555-1234123-555-2345123-555-3456"));
    }
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "555-1234, 555-2345, 555-3456";
        typedef cpp17_output_iterator<char*> Out;
        typedef bidirectional_iterator<const char*> Bi;
        char buf[100] = {0};
        Out r = regex_replace(Out(buf), Bi(begin(phone_book)),
                                    Bi(end(phone_book)-1), phone_numbers,
                                    string("123-$&"),
                                    regex_constants::format_first_only);
        assert(base(r) == buf+32);
        assert(buf == string("123-555-1234, 555-2345, 555-3456"));
    }
    {
        regex phone_numbers("\\d{3}-\\d{4}");
        const char phone_book[] = "555-1234, 555-2345, 555-3456";
        typedef cpp17_output_iterator<char*> Out;
        typedef bidirectional_iterator<const char*> Bi;
        char buf[100] = {0};
        Out r = regex_replace(Out(buf), Bi(begin(phone_book)),
                                    Bi(end(phone_book)-1), phone_numbers,
                                    string("123-$&"),
                                    regex_constants::format_first_only |
                                    regex_constants::format_no_copy);
        assert(base(r) == buf+12);
        assert(buf == string("123-555-1234"));
    }

  return 0;
}
