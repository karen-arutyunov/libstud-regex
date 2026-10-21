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

// XFAIL: LIBCXX-AIX-FIXME

// REQUIRES: locale.cs_CZ.ISO8859-2

// <regex>

// template <class charT> struct regex_traits;

// template <class ForwardIterator>
//   string_type
//   transform_primary(ForwardIterator first, ForwardIterator last) const;

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
        const char A[] = "A";
        const char AA[]      = "AA";
        const char B[]       = "B";
        const char BB[]      = "BB";
        const char Aacute[]  = "\xC1";
        const char AAacute[] = "\xC1\xC1";
        typedef forward_iterator<const char*> F;
        assert(t.transform_primary(F(A), F(A+1)) !=
               t.transform_primary(F(Aacute), F(Aacute+1)));
        assert(t.transform_primary(F(B), F(B + 1)) != t.transform_primary(F(Aacute), F(Aacute + 1)));
        assert(t.transform_primary(F(A), F(A + 1)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(BB), F(BB + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(BB), F(BB + 2)));

        // Note that on MinGW only the "C" locale can be created (see
        // support/platform_support.hxx for details).
        //
#ifndef __MINGW32__
        t.imbue(locale(LOCALE_cs_CZ_ISO8859_2));

        // Note that regex_traits::transform_primary() always works as if the
        // "C" locale is imbued (see regex_traits::__transform_primary() for
        // details).
        //
#if !defined(_WIN32) || (defined(_MSVC_STL_VERSION) && _MSVC_STL_VERSION >= 145)
        assert(t.transform_primary(F(A), F(A+1)) ==
               t.transform_primary(F(Aacute), F(Aacute+1)));
#else
        assert(t.transform_primary(F(A), F(A+1)) !=
               t.transform_primary(F(Aacute), F(Aacute+1)));
#endif
        assert(t.transform_primary(F(B), F(B + 1)) != t.transform_primary(F(Aacute), F(Aacute + 1)));
        assert(t.transform_primary(F(A), F(A + 1)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
#if !defined(_WIN32) || (defined(_MSVC_STL_VERSION) && _MSVC_STL_VERSION >= 145)
        assert(t.transform_primary(F(AA), F(AA + 2)) == t.transform_primary(F(AAacute), F(AAacute + 2)));
#else
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
#endif
        assert(t.transform_primary(F(BB), F(BB + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(BB), F(BB + 2)));
#endif // __MINGW32__
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        regex_traits<wchar_t> t;
        const wchar_t A[] = L"A";
        const wchar_t AA[]      = L"AA";
        const wchar_t B[]       = L"B";
        const wchar_t BB[]      = L"BB";
        const wchar_t Aacute[] = L"\xC1";
        const wchar_t AAacute[] = L"\xC1\xC1";
        typedef forward_iterator<const wchar_t*> F;
        assert(t.transform_primary(F(A), F(A+1)) !=
               t.transform_primary(F(Aacute), F(Aacute+1)));
        assert(t.transform_primary(F(B), F(B + 1)) != t.transform_primary(F(Aacute), F(Aacute + 1)));
        assert(t.transform_primary(F(A), F(A + 1)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(BB), F(BB + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(BB), F(BB + 2)));
#ifndef __MINGW32__
        t.imbue(locale(LOCALE_cs_CZ_ISO8859_2));
#if !defined(_WIN32) || (defined(_MSVC_STL_VERSION) && _MSVC_STL_VERSION >= 145)
        assert(t.transform_primary(F(A), F(A+1)) ==
               t.transform_primary(F(Aacute), F(Aacute+1)));
#else
        assert(t.transform_primary(F(A), F(A+1)) !=
               t.transform_primary(F(Aacute), F(Aacute+1)));
#endif
        assert(t.transform_primary(F(B), F(B + 1)) != t.transform_primary(F(Aacute), F(Aacute + 1)));
        assert(t.transform_primary(F(A), F(A + 1)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
#if !defined(_WIN32) || (defined(_MSVC_STL_VERSION) && _MSVC_STL_VERSION >= 145)
        assert(t.transform_primary(F(AA), F(AA + 2)) == t.transform_primary(F(AAacute), F(AAacute + 2)));
#else
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
#endif
        assert(t.transform_primary(F(BB), F(BB + 2)) != t.transform_primary(F(AAacute), F(AAacute + 2)));
        assert(t.transform_primary(F(AA), F(AA + 2)) != t.transform_primary(F(BB), F(BB + 2)));
#endif // __MINGW32__
    }
#endif

  return 0;
}
