//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// typedef basic_regex<wchar_t> wregex;

// XFAIL: no-wide-characters

#include <libstud/regex.hxx>

#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::is_same;

int main(int, char**)
{
    static_assert((is_same<basic_regex<wchar_t>, wregex>::value), "");

  return 0;
}
