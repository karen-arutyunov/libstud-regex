//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// match_results& operator=(const match_results& m);

#include <libstud/regex.hxx>

#include <memory> // allocator, allocator_traits

#include "test_macros.hxx"
#include "test_allocator.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::allocator;
using std::allocator_traits;

template <class CharT, class Allocator>
void
test(const Allocator& a)
{
    typedef match_results<const CharT*, Allocator> SM;
    SM m0(a);
    SM m1;

    m1 = m0;
    assert(m1.size()          == m0.size());
    assert(m1.ready()         == m0.ready());
    if (allocator_traits<Allocator>::propagate_on_container_copy_assignment::value)
        assert(m1.get_allocator() == m0.get_allocator());
    else
        assert(m1.get_allocator() == Allocator());
}

int main(int, char**)
{
    test<char>   (allocator<sub_match<const char *> >());
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(allocator<sub_match<const wchar_t *> >());
#endif

    // test_allocator has POCCA -> false
    test<char>   (test_allocator<sub_match<const char*> >(3));
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(test_allocator<sub_match<const wchar_t*> >(3));
#endif

    // other_allocator has POCCA -> true
    test<char>   (other_allocator<sub_match<const char*> >(3));
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(other_allocator<sub_match<const wchar_t*> >(3));
#endif

  return 0;
}
