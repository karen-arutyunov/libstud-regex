//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>
// UNSUPPORTED: c++03

// Make sure that we correctly match inverted character classes.

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**) {
    assert(regex_match("X", regex("[X]")));
    assert(regex_match("X", regex("[XY]")));
    assert(!regex_match("X", regex("[^X]")));
    assert(!regex_match("X", regex("[^XY]")));

    assert(regex_match("X", regex("[\\S]")));
    assert(!regex_match("X", regex("[^\\S]")));

    assert(!regex_match("X", regex("[\\s]")));
    assert(regex_match("X", regex("[^\\s]")));

    assert(regex_match("X", regex("[\\s\\S]")));
    assert(regex_match("X", regex("[^Y\\s]")));
    assert(!regex_match("X", regex("[^X\\s]")));

    assert(regex_match("X", regex("[\\w]")));
    assert(regex_match("_", regex("[\\w]")));
    assert(!regex_match("X", regex("[^\\w]")));
    assert(!regex_match("_", regex("[^\\w]")));

    assert(!regex_match("X", regex("[\\W]")));
    assert(!regex_match("_", regex("[\\W]")));
    assert(regex_match("X", regex("[^\\W]")));
    assert(regex_match("_", regex("[^\\W]")));

    // Those test cases are taken from PR40904
    assert(regex_match("abZcd", regex("^ab[\\d\\D]cd")));
    assert(regex_match("ab5cd", regex("^ab[\\d\\D]cd")));
    assert(regex_match("abZcd", regex("^ab[\\D]cd")));
    assert(regex_match("abZcd", regex("^ab\\Dcd")));
    assert(regex_match("ab5cd", regex("^ab[\\d]cd")));
    assert(regex_match("ab5cd", regex("^ab\\dcd")));
    assert(!regex_match("abZcd", regex("^ab\\dcd")));
    assert(!regex_match("ab5cd", regex("^ab\\Dcd")));

    assert(regex_match("_xyz_", regex("_(\\s|\\S)+_")));
    assert(regex_match("_xyz_", regex("_[\\s\\S]+_")));

    return 0;
}
