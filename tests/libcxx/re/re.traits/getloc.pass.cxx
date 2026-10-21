//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: locale.en_US.UTF-8

// <regex>

// template <class charT> struct regex_traits;

// locale_type getloc()const;

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
    {
        regex_traits<char> t;
        assert(t.getloc().name() == "C");
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        regex_traits<wchar_t> t;
        assert(t.getloc().name() == "C");
    }
#endif
#if TEST_HAS_EN_US_UTF8_LOCALE
    {
        locale::global(locale(LOCALE_en_US_UTF_8));
        regex_traits<char> t;
        assert(t.getloc().name() == LOCALE_en_US_UTF_8);
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        locale::global(locale(LOCALE_en_US_UTF_8));
        regex_traits<wchar_t> t;
        assert(t.getloc().name() == LOCALE_en_US_UTF_8);
    }
#endif
#else
    {
        locale::global(locale("C"));
        regex_traits<char> t;
        assert(t.getloc().name() == "C");
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        locale::global(locale("C"));
        regex_traits<wchar_t> t;
        assert(t.getloc().name() == "C");
    }
#endif
#endif

  return 0;
}
