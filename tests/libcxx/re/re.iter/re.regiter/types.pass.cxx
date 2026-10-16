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
// class regex_iterator
// {
// public:
//     typedef basic_regex<charT, traits>           regex_type;
//     typedef match_results<BidirectionalIterator> value_type;
//     typedef ptrdiff_t                            difference_type;
//     typedef const value_type*                    pointer;
//     typedef const value_type&                    reference;
//     typedef forward_iterator_tag                 iterator_category;
//     typedef input_iterator_tag                   iterator_concept; // since C++20

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

#if TEST_STD_VER >= 20 && defined(__cpp_lib_type_trait_variable_templates)
using std::is_same_v;
#endif

template <class CharT>
void
test()
{
    typedef regex_iterator<const CharT*> I;
    static_assert((is_same<typename I::regex_type, basic_regex<CharT> >::value), "");
    static_assert((is_same<typename I::value_type, match_results<const CharT*> >::value), "");
    static_assert((is_same<typename I::difference_type, ptrdiff_t>::value), "");
    static_assert((is_same<typename I::pointer, const match_results<const CharT*>*>::value), "");
    static_assert((is_same<typename I::reference, const match_results<const CharT*>&>::value), "");
    static_assert((is_same<typename I::iterator_category, forward_iterator_tag>::value), "");
#if TEST_STD_VER >= 20 && defined(__cpp_lib_type_trait_variable_templates)
    static_assert(is_same_v<typename I::iterator_concept, input_iterator_tag>);
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
