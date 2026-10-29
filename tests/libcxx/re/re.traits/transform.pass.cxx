//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// NetBSD does not support LC_COLLATE at the moment
// XFAIL: netbsd

// REQUIRES: locale.cs_CZ.ISO8859-2

// <regex>

// template <class charT> struct regex_traits;

// template <class ForwardIterator>
//   string_type transform(ForwardIterator first, ForwardIterator last) const;

#include <libstud/regex/regex.hxx>

#include <locale>
#include <stdexcept>

#include "test_macros.hxx"
#include "test_iterators.hxx"
#include "platform_support.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::locale;
using std::runtime_error;

int main(int, char**)
{
    // Load the LOCALE_cs_CZ_ISO8859_2 locale, if present.
    //
    // Note that if it is not, then cz_loc stays "C", in which case it is
    // equal to locale::classic().
    //
    locale cz_loc;

    try
    {
      cz_loc = locale (LOCALE_cs_CZ_ISO8859_2);
    }
    catch (const runtime_error&) {}

    {
        regex_traits<char> t;
        const char a[] = "a";
        const char B[] = "B";
        typedef forward_iterator<const char*> F;
        assert(t.transform(F(a), F(a+1)) > t.transform(F(B), F(B+1)));

        if (cz_loc != locale::classic ()) // Not "C" locale?
        {
          t.imbue(cz_loc);
          assert(t.transform(F(a), F(a+1)) < t.transform(F(B), F(B+1)));
        }
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        regex_traits<wchar_t> t;
        const wchar_t a[] = L"a";
        const wchar_t B[] = L"B";
        typedef forward_iterator<const wchar_t*> F;
        assert(t.transform(F(a), F(a+1)) > t.transform(F(B), F(B+1)));

        if (cz_loc != locale::classic ()) // Not "C" locale?
        {
          t.imbue(cz_loc);
          assert(t.transform(F(a), F(a+1)) < t.transform(F(B), F(B+1)));
        }
    }
#endif

  return 0;
}
