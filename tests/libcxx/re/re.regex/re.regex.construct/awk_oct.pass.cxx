//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// template <class ST, class SA>
//    basic_regex(const basic_string<charT, ST, SA>& s);

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**)
{
    using regex_constants::awk;

    assert(regex_match("\4", regex("\\4", awk)));
    assert(regex_match("\41", regex("\\41", awk)));
    assert(regex_match("\141", regex("\\141", awk)));
    assert(regex_match("\141" "1", regex("\\1411", awk)));

  return 0;
}
