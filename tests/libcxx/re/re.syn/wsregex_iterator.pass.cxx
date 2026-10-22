//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// typedef regex_iterator<wstring::const_iterator>   wsregex_iterator;

// XFAIL: no-wide-characters

#include <libstud/regex/regex.hxx>

#include <string>
#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::is_same;
using std::wstring;

int main(int, char**)
{
    static_assert((is_same<regex_iterator<wstring::const_iterator>, wsregex_iterator>::value), "");

  return 0;
}
