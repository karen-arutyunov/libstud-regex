//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>
// UNSUPPORTED: no-exceptions

// template <class OutputIterator, class BidirectionalIterator,
//           class traits, class charT, class ST, class SA>
//     OutputIterator
//     regex_replace(OutputIterator out,
//                   BidirectionalIterator first, BidirectionalIterator last,
//                   const basic_regex<charT, traits>& e,
//                   const basic_string<charT, ST, SA>& fmt,
//                   regex_constants::match_flag_type flags =
//                                              regex_constants::match_default);

#include <libstud/regex/regex.hxx>

#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;

int main(int, char**)
{
    try {
        regex re("a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?a?aaaaaaaaaaaaaaaaaaaa");
        const char s[] = "aaaaaaaaaaaaaaaaaaaa";
        string r = regex_replace(s, re, "123-&", regex_constants::format_sed);
        LIBCPP_ASSERT(false);
        assert(r == "123-aaaaaaaaaaaaaaaaaaaa");
    } catch (const regex_error &e) {
      assert(e.code() == regex_constants::error_complexity);
    }
    return 0;
}
