//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// template <class ST, class SA>
//   basic_string<char_type, ST, SA>
//   format(const basic_string<char_type, ST, SA>& fmt,
//          regex_constants::match_flag_type flags = regex_constants::format_default) const;

#include <libstud/regex/regex.hxx>

#include <string>

#include "test_macros.hxx"
#include "test_allocator.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::basic_string;
using std::char_traits;

int main(int, char**)
{
    typedef basic_string<char, char_traits<char>, test_allocator<char> > nstr;
    {
        match_results<const char*> m;
        const char s[] = "abcdefghijk";
        assert(regex_search(s, m, regex("cd((e)fg)hi")));

        nstr fmt("prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        nstr out = m.format(fmt);
        assert(out == "prefix: ab, match: cdefghi, suffix: jk, m[1]: efg, m[2]: e");
    }
    {
        match_results<const char*> m;
        const char s[] = "abcdefghijk";
        assert(regex_search(s, m, regex("cd((e)fg)hi")));

        nstr fmt("prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        nstr out = m.format(fmt, regex_constants::format_sed);
        assert(out == "prefix: $`, match: $cdefghi, suffix: $', m[1]: $1, m[2]: $2");
    }
    {
        match_results<const char*> m;
        const char s[] = "abcdefghijk";
        assert(regex_search(s, m, regex("cd((e)fg)hi")));

        nstr fmt("match: &, m[1]: \\1, m[2]: \\2");
        nstr out = m.format(fmt, regex_constants::format_sed);
        assert(out == "match: cdefghi, m[1]: efg, m[2]: e");
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    typedef basic_string<wchar_t, char_traits<wchar_t>, test_allocator<wchar_t> > wstr;
    {
        match_results<const wchar_t*> m;
        const wchar_t s[] = L"abcdefghijk";
        assert(regex_search(s, m, wregex(L"cd((e)fg)hi")));

        wstr fmt(L"prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        wstr out = m.format(fmt);
        assert(out == L"prefix: ab, match: cdefghi, suffix: jk, m[1]: efg, m[2]: e");
    }
    {
        match_results<const wchar_t*> m;
        const wchar_t s[] = L"abcdefghijk";
        assert(regex_search(s, m, wregex(L"cd((e)fg)hi")));

        wstr fmt(L"prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        wstr out = m.format(fmt, regex_constants::format_sed);
        assert(out == L"prefix: $`, match: $cdefghi, suffix: $', m[1]: $1, m[2]: $2");
    }
    {
        match_results<const wchar_t*> m;
        const wchar_t s[] = L"abcdefghijk";
        assert(regex_search(s, m, wregex(L"cd((e)fg)hi")));

        wstr fmt(L"match: &, m[1]: \\1, m[2]: \\2");
        wstr out = m.format(fmt, regex_constants::format_sed);
        assert(out == L"match: cdefghi, m[1]: efg, m[2]: e");
    }
#endif // TEST_HAS_NO_WIDE_CHARACTERS

  return 0;
}
