//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// Test that replacing zero-length matches works correctly.

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**) {
  // Various patterns that produce zero-length matches.
  assert(regex_replace("abc", regex(""), "!") == "!a!b!c!");
  assert(regex_replace("abc", regex("X*"), "!") == "!a!b!c!");
  assert(regex_replace("abc", regex("X{0,3}"), "!") == "!a!b!c!");

  // Replacement string has several characters.
  assert(regex_replace("abc", regex(""), "[!]") == "[!]a[!]b[!]c[!]");

  // Empty replacement string.
  assert(regex_replace("abc", regex(""), "") == "abc");

  // Empty input.
  assert(regex_replace("", regex(""), "!") == "!");

  // Not all matches are zero-length.
  assert(regex_replace("abCabCa", regex("C*"), "!") == "!a!b!!a!b!!a!");

  return 0;
}
