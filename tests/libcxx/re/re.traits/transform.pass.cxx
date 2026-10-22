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

#include <libstud/regex.hxx>

#include <locale>

#include "test_macros.hxx"
#include "test_iterators.hxx"
#include "platform_support.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::locale;

int main(int, char**)
{
    {
        regex_traits<char> t;
        const char a[] = "a";
        const char B[] = "B";
        typedef forward_iterator<const char*> F;
        assert(t.transform(F(a), F(a+1)) > t.transform(F(B), F(B+1)));
#if !TEST_HAS_C_LOCALE_ONLY && TEST_HAS_CS_CZ_ISO8859_2_LOCALE
        t.imbue(locale(LOCALE_cs_CZ_ISO8859_2));
        assert(t.transform(F(a), F(a+1)) < t.transform(F(B), F(B+1)));
#endif
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        regex_traits<wchar_t> t;
        const wchar_t a[] = L"a";
        const wchar_t B[] = L"B";
        typedef forward_iterator<const wchar_t*> F;
        assert(t.transform(F(a), F(a+1)) > t.transform(F(B), F(B+1)));
#if !TEST_HAS_C_LOCALE_ONLY && TEST_HAS_CS_CZ_ISO8859_2_LOCALE
        t.imbue(locale(LOCALE_cs_CZ_ISO8859_2));
        assert(t.transform(F(a), F(a+1)) < t.transform(F(B), F(B+1)));
#endif
    }
#endif

  return 0;
}
