//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator>
// class sub_match
//     : public pair<BidirectionalIterator, BidirectionalIterator>
// {
// public:
//     typedef BidirectionalIterator                               iterator;
//     typedef typename iterator_traits<iterator>::value_type      value_type;
//     typedef typename iterator_traits<iterator>::difference_type difference_type;
//     typedef basic_string<value_type>                            string_type;
//
//     bool matched;
//     ...
// };

#include <libstud/regex/regex.hxx>

#include <string>
#include <cstddef>     // ptrdiff_t
#include <utility>     // pair
#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::is_same;
using std::is_convertible;
using std::string;
using std::wstring;
using std::ptrdiff_t;
using std::pair;

int main(int, char**)
{
    {
        typedef sub_match<char*> SM;
        static_assert((is_same<SM::iterator, char*>::value), "");
        static_assert((is_same<SM::value_type, char>::value), "");
        static_assert((is_same<SM::difference_type, ptrdiff_t>::value), "");
        static_assert((is_same<SM::string_type, string>::value), "");
        static_assert((is_convertible<SM*, pair<char*, char*>*>::value), "");

        static_assert((is_same<csub_match, sub_match<const char*> >::value), "");
        static_assert((is_same<ssub_match, sub_match<string::const_iterator> >::value), "");

        SM sm;
        sm.first = nullptr;
        sm.second = nullptr;
        sm.matched = false;
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        typedef sub_match<wchar_t*> SM;
        static_assert((is_same<SM::iterator, wchar_t*>::value), "");
        static_assert((is_same<SM::value_type, wchar_t>::value), "");
        static_assert((is_same<SM::difference_type, ptrdiff_t>::value), "");
        static_assert((is_same<SM::string_type, wstring>::value), "");
        static_assert((is_convertible<SM*, pair<wchar_t*, wchar_t*>*>::value), "");

        static_assert((is_same<wcsub_match, sub_match<const wchar_t*> >::value), "");
        static_assert((is_same<wssub_match, sub_match<wstring::const_iterator> >::value), "");

        SM sm;
        sm.first = nullptr;
        sm.second = nullptr;
        sm.matched = false;
    }
#endif

  return 0;
}
