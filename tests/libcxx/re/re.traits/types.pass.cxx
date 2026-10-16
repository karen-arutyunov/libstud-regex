//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT>
// struct regex_traits
// {
// public:
//     typedef charT                   char_type;
//     typedef basic_string<char_type> string_type;
//     typedef locale                  locale_type;

#include <libstud/regex.hxx>

#include <locale>
#include <string>
#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::is_same;
using std::string;
using std::wstring;
using std::locale;

int main(int, char**)
{
    static_assert((is_same<regex_traits<char>::char_type, char>::value), "");
    static_assert((is_same<regex_traits<char>::string_type, string>::value), "");
    static_assert((is_same<regex_traits<char>::locale_type, locale>::value), "");
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    static_assert((is_same<regex_traits<wchar_t>::char_type, wchar_t>::value), "");
    static_assert((is_same<regex_traits<wchar_t>::string_type, wstring>::value), "");
    static_assert((is_same<regex_traits<wchar_t>::locale_type, locale>::value), "");
#endif

  return 0;
}
