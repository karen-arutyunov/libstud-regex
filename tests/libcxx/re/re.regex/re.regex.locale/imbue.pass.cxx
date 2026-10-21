//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: locale.en_US.UTF-8

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// locale_type imbue(locale_type loc);

#include <libstud/regex.hxx>

#include <locale>

#include "test_macros.hxx"
#include "platform_support.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::locale;

int main(int, char**)
{
#if TEST_HAS_EN_US_UTF8_LOCALE
    regex r;
    locale loc = r.imbue(locale(LOCALE_en_US_UTF_8));
    assert(loc.name() == "C");
    assert(r.getloc().name() == LOCALE_en_US_UTF_8);
    loc = r.imbue(locale("C"));
    assert(loc.name() == LOCALE_en_US_UTF_8);
    assert(r.getloc().name() == "C");
#else
    regex r;
    locale loc = r.imbue(locale("C"));
    assert(loc.name() == "C");
    assert(r.getloc().name() == "C");
    loc = r.imbue(locale("C"));
    assert(loc.name() == "C");
    assert(r.getloc().name() == "C");
#endif

  return 0;
}
