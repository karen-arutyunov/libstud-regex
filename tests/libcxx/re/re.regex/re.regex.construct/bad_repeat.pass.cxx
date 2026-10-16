//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: no-exceptions
// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// template <class ST, class SA>
//    basic_regex(const basic_string<charT, ST, SA>& s);

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

static bool error_badrepeat_thrown(const char *pat)
{
    bool result = false;
    try {
        regex re(pat);
    } catch (const regex_error &ex) {
        result = (ex.code() == regex_constants::error_badrepeat);
    }
    return result;
}

int main(int, char**)
{
    assert(error_badrepeat_thrown("?a"));
    assert(error_badrepeat_thrown("*a"));
    assert(error_badrepeat_thrown("+a"));
    assert(error_badrepeat_thrown("{a"));

    assert(error_badrepeat_thrown("?(a+)"));
    assert(error_badrepeat_thrown("*(a+)"));
    assert(error_badrepeat_thrown("+(a+)"));
    assert(error_badrepeat_thrown("{(a+)"));

  return 0;
}
