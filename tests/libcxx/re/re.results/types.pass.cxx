//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator,
//           class Allocator = allocator<sub_match<BidirectionalIterator>>>
// class match_results
// {
// public:
//     typedef sub_match<BidirectionalIterator>                  value_type;
//     typedef const value_type&                                 const_reference;
//     typedef const_reference                                   reference;
//     typedef /implementation-defined/                          const_iterator;
//     typedef const_iterator                                    iterator;
//     typedef typename iterator_traits<BidirectionalIterator>::difference_type difference_type;
//     typedef typename allocator_traits<Allocator>::size_type   size_type;
//     typedef Allocator                                         allocator_type;
//     typedef typename iterator_traits<BidirectionalIterator>::value_type char_type;
//     typedef basic_string<char_type>                           string_type;

#include <libstud/regex.hxx>

#include <string>
#include <memory>      // allocator
#include <cstddef>     // size_t, ptrdiff_t
#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::is_same;
using std::basic_string;
using std::allocator;
using std::size_t;
using std::ptrdiff_t;

template <class CharT>
void
test()
{
    typedef match_results<CharT*> MR;
    static_assert((is_same<typename MR::value_type, sub_match<CharT*> >::value), "");
    static_assert((is_same<typename MR::const_reference, const sub_match<CharT*>& >::value), "");
    static_assert((is_same<typename MR::reference, sub_match<CharT*>& >::value), "");
    static_assert((!is_same<typename MR::const_iterator, void>::value), "");
    static_assert((is_same<typename MR::difference_type, ptrdiff_t>::value), "");
    static_assert((is_same<typename MR::size_type, size_t>::value), "");
    static_assert((is_same<typename MR::allocator_type, allocator<sub_match<CharT*> > >::value), "");
    static_assert((is_same<typename MR::char_type, CharT>::value), "");
    static_assert((is_same<typename MR::string_type, basic_string<CharT> >::value), "");
}

int main(int, char**)
{
    test<char>();
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>();
#endif

    return 0;
}
