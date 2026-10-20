//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator,
//           class charT = typename iterator_traits< BidirectionalIterator>::value_type,
//           class traits = regex_traits<charT>>
// class regex_token_iterator
// {
// public:
//     typedef basic_regex<charT, traits>       regex_type;
//     typedef sub_match<BidirectionalIterator> value_type;
//     typedef ptrdiff_t                        difference_type;
//     typedef const value_type*                pointer;
//     typedef const value_type&                reference;
//     typedef forward_iterator_tag             iterator_category;
//     typedef input_iterator_tag               iterator_concept; // since C++20

#include <libstud/regex.hxx>

#include <cstddef>     // ptrdiff_t
#include <iterator>
#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::ptrdiff_t;
using std::is_same;
using std::forward_iterator_tag;
using std::input_iterator_tag;

template <class CharT>
void
test()
{
    typedef regex_token_iterator<const CharT*> I;
    static_assert((is_same<typename I::regex_type, basic_regex<CharT> >::value), "");
    static_assert((is_same<typename I::value_type, sub_match<const CharT*> >::value), "");
    static_assert((is_same<typename I::difference_type, ptrdiff_t>::value), "");
    static_assert((is_same<typename I::pointer, const sub_match<const CharT*>*>::value), "");
    static_assert((is_same<typename I::reference, const sub_match<const CharT*>&>::value), "");
    static_assert((is_same<typename I::iterator_category, forward_iterator_tag>::value), "");
#if TEST_STD_VER >= 20
    static_assert((is_same<typename I::iterator_concept, input_iterator_tag>::value), "");
#endif
}

int main(int, char**)
{
    test<char>();
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>();
#endif

    return 0;
}
