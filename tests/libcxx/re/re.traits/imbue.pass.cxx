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

// locale_type imbue(locale_type l);

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
#if !defined(__MINGW32__) && (!defined(_MSC_VER) || _MSC_VER >= 1929)
        locale loc = t.imbue(locale(LOCALE_en_US_UTF_8));
        assert(loc.name() == "C");
        assert(t.getloc().name() == LOCALE_en_US_UTF_8);
#else
        locale loc = t.imbue(locale("C"));
        assert(loc.name() == "C");
        assert(t.getloc().name() == "C");
#endif
    }

  return 0;
}
