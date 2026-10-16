//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// UNSUPPORTED: c++03

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// match_results& operator=(match_results&& m);

#include <libstud/regex.hxx>

#include <memory>  // allocator, allocator_traits
#include <utility> // move()

#include "test_macros.hxx"
#include "test_allocator.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::allocator;
using std::allocator_traits;
using std::move;

template <class CharT, class Allocator>
void
test(const Allocator& a)
{
    typedef match_results<const CharT*, Allocator> SM;
    SM m0(a);
    SM m1;

    m1 = move(m0);
    assert(m1.size()          == 0);
    assert(!m1.ready());
    if (allocator_traits<Allocator>::propagate_on_container_move_assignment::value)
        assert(m1.get_allocator() == a);
    else
        assert(m1.get_allocator() == Allocator());
}

int main(int, char**)
{
    test<char>   (allocator<sub_match<const char *> >());
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(allocator<sub_match<const wchar_t *> >());
#endif

    // test_allocator has POCMA -> false
    test<char>   (test_allocator<sub_match<const char*> >(3));
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(test_allocator<sub_match<const wchar_t*> >(3));
#endif

    // other_allocator has POCMA -> true
    test<char>   (other_allocator<sub_match<const char*> >(3));
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(other_allocator<sub_match<const wchar_t*> >(3));
#endif

  return 0;
}
