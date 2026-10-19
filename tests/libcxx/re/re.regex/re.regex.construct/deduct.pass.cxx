//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>
// UNSUPPORTED: c++03, c++11, c++14

// template<class ForwardIterator>
// basic_regex(ForwardIterator, ForwardIterator,
//             regex_constants::syntax_option_type = regex_constants::ECMAScript)
// -> basic_regex<typename iterator_traits<ForwardIterator>::value_type>;

#include <libstud/regex.hxx>

#include <string>
#include <type_traits> // is_same

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using namespace std::literals;

using std::is_same;
using std::string;
using std::wstring;

struct A {};

int main(int, char**)
{

//  Test the explicit deduction guides
    {
//  basic_regex(ForwardIterator, ForwardIterator)
    string s1("\\(a\\)");
    basic_regex re(s1.begin(), s1.end());

    static_assert(is_same<decltype(re), basic_regex<char>>::value, "");
    assert(re.flags() == regex_constants::ECMAScript);
    assert(re.mark_count() == 0);
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
    wstring s1(L"\\(a\\)");
    basic_regex re(s1.begin(), s1.end(), regex_constants::basic);

    static_assert(is_same<decltype(re), basic_regex<wchar_t>>::value, "");
    assert(re.flags() == regex_constants::basic);
    assert(re.mark_count() == 1);
    }
#endif

//  Test the implicit deduction guides
    {
//  basic_regex(string);
    basic_regex re("(a([bc]))"s);
    static_assert(is_same<decltype(re), basic_regex<char>>::value, "");
    assert(re.flags() == regex_constants::ECMAScript);
    assert(re.mark_count() == 2);
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
//  basic_regex(string, flag_type);
    basic_regex re(L"(a([bc]))"s, regex_constants::awk);
    static_assert(is_same<decltype(re), basic_regex<wchar_t>>::value, "");
    assert(re.flags() == regex_constants::awk);
    assert(re.mark_count() == 2);
    }
#endif

    {
//  basic_regex(const charT*);
    basic_regex re("ABCDE");
    static_assert(is_same<decltype(re), basic_regex<char>>::value, "");
    assert(re.flags() == regex_constants::ECMAScript);
    assert(re.mark_count() == 0);
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
//  basic_regex(const charT*, flag_type);
    basic_regex re(L"ABCDE", regex_constants::grep);
    static_assert(is_same<decltype(re), basic_regex<wchar_t>>::value, "");
    assert(re.flags() == regex_constants::grep);
    assert(re.mark_count() == 0);
    }
#endif

    {
//  basic_regex(const charT*, size_t);
    basic_regex re("ABCDEDEF", 7);
    static_assert(is_same<decltype(re), basic_regex<char>>::value, "");
    assert(re.flags() == regex_constants::ECMAScript);
    assert(re.mark_count() == 0);
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
//  basic_regex(const charT*, size_t, flag_type);
    basic_regex re(L"ABCDEDEF", 8, regex_constants::awk);
    static_assert(is_same<decltype(re), basic_regex<wchar_t>>::value, "");
    assert(re.flags() == regex_constants::awk);
    assert(re.mark_count() == 0);
    }
#endif

    {
//  basic_regex(const basic_regex &);
    basic_regex<char> source;
    basic_regex re(source);
    static_assert(is_same<decltype(re), basic_regex<char>>::value, "");
    assert(re.flags() == source.flags());
    assert(re.mark_count() == source.mark_count());
    }

    {
//  template<class ST, class SA>
//         explicit basic_regex(const basic_string<charT, ST, SA>& p,
//                              flag_type f = regex_constants::ECMAScript);
    }

    {
//  basic_regex(initializer_list);
    basic_regex re({'A', 'B', 'F', 'E', 'D'});
    static_assert(is_same<decltype(re), basic_regex<char>>::value, "");
    assert(re.flags() == regex_constants::ECMAScript);
    assert(re.mark_count() == 0);
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
//  basic_regex(initializer_list, flag_type);
    basic_regex re({L'A', L'B', L'F', L'E', L'D'}, regex_constants::grep);
    static_assert(is_same<decltype(re), basic_regex<wchar_t>>::value, "");
    assert(re.flags() == regex_constants::grep);
    assert(re.mark_count() == 0);
    }
#endif

  return 0;
}
