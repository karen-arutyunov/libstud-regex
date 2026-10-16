//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class match_results<BidirectionalIterator, Allocator>

// template <class OutputIter, class ST, class SA>
//   OutputIter
//   format(OutputIter out, const basic_string<char_type, ST, SA>& fmt,
//          regex_constants::match_flag_type flags = regex_constants::format_default) const;

#include <libstud/regex.hxx>

#include <string>

#include "test_macros.hxx"
#include "test_iterators.hxx"
#include "test_allocator.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;
using std::wstring;
using std::basic_string;
using std::char_traits;

int main(int, char**)
{
    typedef basic_string<char, char_traits<char>, test_allocator<char> > nstr;
    {
        match_results<const char*> m;
        const char s[] = "abcdefghijk";
        assert(regex_search(s, m, regex("cd((e)fg)hi")));

        char out[100] = {0};
        nstr fmt("prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        auto r = m.format(cpp17_output_iterator<char*>(out), fmt);
        assert(base(r) == out + 58);
        assert(string(out) == "prefix: ab, match: cdefghi, suffix: jk, m[1]: efg, m[2]: e");
    }
    {
        match_results<const char*> m;
        const char s[] = "abcdefghijk";
        assert(regex_search(s, m, regex("cd((e)fg)hi")));

        char out[100] = {0};
        nstr fmt("prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        auto r = m.format(cpp17_output_iterator<char*>(out), fmt, regex_constants::format_sed);
        assert(base(r) == out + 59);
        assert(string(out) == "prefix: $`, match: $cdefghi, suffix: $', m[1]: $1, m[2]: $2");
    }
    {
        match_results<const char*> m;
        const char s[] = "abcdefghijk";
        assert(regex_search(s, m, regex("cd((e)fg)hi")));

        char out[100] = {0};
        nstr fmt("match: &, m[1]: \\1, m[2]: \\2");
        auto r = m.format(cpp17_output_iterator<char*>(out), fmt, regex_constants::format_sed);
        assert(base(r) == out + 34);
        assert(string(out) == "match: cdefghi, m[1]: efg, m[2]: e");
    }

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    typedef basic_string<wchar_t, char_traits<wchar_t>, test_allocator<wchar_t> > wstr;
    {
        match_results<const wchar_t*> m;
        const wchar_t s[] = L"abcdefghijk";
        assert(regex_search(s, m, wregex(L"cd((e)fg)hi")));

        wchar_t out[100] = {0};
        wstr fmt(L"prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        auto r = m.format(cpp17_output_iterator<wchar_t*>(out), fmt);
        assert(base(r) == out + 58);
        assert(wstring(out) == L"prefix: ab, match: cdefghi, suffix: jk, m[1]: efg, m[2]: e");
    }
    {
        match_results<const wchar_t*> m;
        const wchar_t s[] = L"abcdefghijk";
        assert(regex_search(s, m, wregex(L"cd((e)fg)hi")));

        wchar_t out[100] = {0};
        wstr fmt(L"prefix: $`, match: $&, suffix: $', m[1]: $1, m[2]: $2");
        auto r = m.format(cpp17_output_iterator<wchar_t*>(out), fmt, regex_constants::format_sed);
        assert(base(r) == out + 59);
        assert(wstring(out) == L"prefix: $`, match: $cdefghi, suffix: $', m[1]: $1, m[2]: $2");
    }
    {
        match_results<const wchar_t*> m;
        const wchar_t s[] = L"abcdefghijk";
        assert(regex_search(s, m, wregex(L"cd((e)fg)hi")));

        wchar_t out[100] = {0};
        wstr fmt(L"match: &, m[1]: \\1, m[2]: \\2");
        auto r = m.format(cpp17_output_iterator<wchar_t*>(out), fmt, regex_constants::format_sed);
        assert(base(r) == out + 34);
        assert(wstring(out) == L"match: cdefghi, m[1]: efg, m[2]: e");
    }
#endif // TEST_HAS_NO_WIDE_CHARACTERS

  return 0;
}
