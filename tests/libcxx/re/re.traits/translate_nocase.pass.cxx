//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT> struct regex_traits;

// charT translate_nocase(charT c) const;

// REQUIRES: locale.en_US.UTF-8
// XFAIL: win32-broken-utf8-wchar-ctype

// Prior to Android O (API 26), in the "en_US.UTF-8" locale, towlower(L'\xDA')
// returned 0xDA instead of 0xFA.
// XFAIL: LIBCXX-ANDROID-FIXME && android-device-api={{21|22|23|24|25}}

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
        assert(t.translate_nocase(' ') == ' ');
        assert(t.translate_nocase('A') == 'a');
        assert(t.translate_nocase('\x07') == '\x07');
        assert(t.translate_nocase('.') == '.');
        assert(t.translate_nocase('a') == 'a');
        assert(t.translate_nocase('1') == '1');
        assert(t.translate_nocase('\xDA') == '\xDA');
        assert(t.translate_nocase('\xFA') == '\xFA');
#if TEST_HAS_EN_US_UTF8_LOCALE
        t.imbue(locale(LOCALE_en_US_UTF_8));
#else
        t.imbue(locale("C"));
#endif
        assert(t.translate_nocase(' ') == ' ');
        assert(t.translate_nocase('A') == 'a');
        assert(t.translate_nocase('\x07') == '\x07');
        assert(t.translate_nocase('.') == '.');
        assert(t.translate_nocase('a') == 'a');
        assert(t.translate_nocase('1') == '1');
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        regex_traits<wchar_t> t;
        assert(t.translate_nocase(L' ') == L' ');
        assert(t.translate_nocase(L'A') == L'a');
        assert(t.translate_nocase(L'\x07') == L'\x07');
        assert(t.translate_nocase(L'.') == L'.');
        assert(t.translate_nocase(L'a') == L'a');
        assert(t.translate_nocase(L'1') == L'1');
        assert(t.translate_nocase(L'\xDA') == L'\xDA');
        assert(t.translate_nocase(L'\xFA') == L'\xFA');
#if TEST_HAS_EN_US_UTF8_LOCALE
        t.imbue(locale(LOCALE_en_US_UTF_8));
#else
        t.imbue(locale("C"));
#endif
        assert(t.translate_nocase(L' ') == L' ');
        assert(t.translate_nocase(L'A') == L'a');
        assert(t.translate_nocase(L'\x07') == L'\x07');
        assert(t.translate_nocase(L'.') == L'.');
        assert(t.translate_nocase(L'a') == L'a');
        assert(t.translate_nocase(L'1') == L'1');
#if TEST_HAS_EN_US_UTF8_LOCALE
        assert(t.translate_nocase(L'\xDA') == L'\xFA');
        assert(t.translate_nocase(L'\xFA') == L'\xFA');
#endif
    }
#endif

  return 0;
}
