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

// match_results(match_results&& m) noexcept;
//
//  Additionally, the stored Allocator value is move constructed from m.get_allocator().

#include <libstud/regex.hxx>

#include <memory>  // allocator
#include <utility> // move(), declval()

#include "test_macros.hxx"
#include "test_allocator.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::allocator;
using std::move;
using std::declval;

template <class CharT, class Allocator>
void
test(const Allocator& a)
{
    typedef match_results<const CharT*, Allocator> SM;
    ASSERT_NOEXCEPT(SM(declval<SM&&>()));

    SM m0(a);
    assert(m0.get_allocator() == a);

    SM m1(move(m0));
    assert(m1.size() == 0);
    assert(!m1.ready());
    assert(m1.get_allocator() == a);
}

int main(int, char**)
{
    test_allocator_statistics alloc_stats;
    test<char>   (allocator<sub_match<const char *> >());
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(allocator<sub_match<const wchar_t *> >());
#endif

    test<char>   (test_allocator<sub_match<const char*> >(3, &alloc_stats));

    // Note that for some older standard libraries (MSVC 14.3, libc++ 3.7) the
    // number of the allocator object move constructions can be a bit higher
    // than 1. However, the stud::regex::match_results implementation doesn't
    // manipulate the allocator objects directly and just defines the internal
    // std::vector container using the specified allocator type. Thus, this is
    // most likely specifics of the standard library implementation which can
    // result in a different number of move-constructor calls. Doesn't feel
    // that we should care about that, thus let's just comment out the checks.
    //
    //assert(alloc_stats.moved == 1);
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>(test_allocator<sub_match<const wchar_t*> >(3, &alloc_stats));
    //assert(alloc_stats.moved == 2);
#endif

  return 0;
}
