//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// typedef regex_token_iterator<string::const_iterator>   sregex_token_iterator;

#include <libstud/regex.hxx>

#include <string>
#include <type_traits>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::is_same;
using std::string;

int main(int, char**)
{
    static_assert((is_same<regex_token_iterator<string::const_iterator>, sregex_token_iterator>::value), "");

  return 0;
}
