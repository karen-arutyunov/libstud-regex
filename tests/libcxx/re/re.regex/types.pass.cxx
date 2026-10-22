//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>>
// class basic_regex
// {
// public:
//     // types:
//     typedef charT                               value_type;
//     typedef traits                              traits_type;
//     typedef typename traits::string_type        string_type;
//     typedef regex_constants::syntax_option_type flag_type;
//     typedef typename traits::locale_type        locale_type;

#include <libstud/regex/regex.hxx>

#include <string>
#include <locale>
#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::is_same;
using std::basic_string;
using std::locale;

int main(int, char**)
{
    static_assert((is_same<basic_regex<char>::value_type, char>::value), "");
    static_assert((is_same<basic_regex<char>::traits_type, regex_traits<char> >::value), "");
    static_assert((is_same<basic_regex<char>::string_type, basic_string<char> >::value), "");
    static_assert((is_same<basic_regex<char>::flag_type,
                                regex_constants::syntax_option_type>::value), "");
    static_assert((is_same<basic_regex<char>::locale_type, locale>::value), "");

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    static_assert((is_same<basic_regex<wchar_t>::value_type, wchar_t>::value), "");
    static_assert((is_same<basic_regex<wchar_t>::traits_type, regex_traits<wchar_t> >::value), "");
    static_assert((is_same<basic_regex<wchar_t>::string_type, basic_string<wchar_t> >::value), "");
    static_assert((is_same<basic_regex<wchar_t>::flag_type,
                                regex_constants::syntax_option_type>::value), "");
    static_assert((is_same<basic_regex<wchar_t>::locale_type, locale>::value), "");
#endif

    return 0;
}
