//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>
// bool empty() const;

// UNSUPPORTED: c++03, c++11, c++14, c++17

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

void f() {
    match_results<const char*> c;
    TEST_IGNORE_NODISCARD c.empty(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
}
int main(int, char**)
{
  f();
}
