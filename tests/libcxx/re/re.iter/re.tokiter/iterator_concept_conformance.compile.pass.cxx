//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17

// regex_token_iterator

#include <libstud/regex.hxx>

#include <iterator>

using namespace stud::regex;

#ifdef __cpp_lib_ranges
static_assert(std::input_iterator<cregex_token_iterator>);
static_assert(!std::forward_iterator<cregex_token_iterator>);
static_assert(!std::indirectly_writable<cregex_token_iterator, char>);
static_assert(std::sentinel_for<cregex_token_iterator, cregex_token_iterator>);
static_assert(!std::sized_sentinel_for<cregex_token_iterator, cregex_token_iterator>);
static_assert(!std::indirectly_movable<cregex_token_iterator, cregex_token_iterator>);
static_assert(!std::indirectly_movable_storable<cregex_token_iterator, cregex_token_iterator>);
static_assert(!std::indirectly_copyable<cregex_token_iterator, cregex_token_iterator>);
static_assert(!std::indirectly_copyable_storable<cregex_token_iterator, cregex_token_iterator>);
static_assert(!std::indirectly_swappable<cregex_token_iterator, cregex_token_iterator>);
#endif

int main(int, char**)
{
}
