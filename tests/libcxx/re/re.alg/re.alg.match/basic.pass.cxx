//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//

// <regex>

// template <class BidirectionalIterator, class Allocator, class charT, class traits>
//     bool
//     regex_match(BidirectionalIterator first, BidirectionalIterator last,
//                  match_results<BidirectionalIterator, Allocator>& m,
//                  const basic_regex<charT, traits>& e,
//                  regex_constants::match_flag_type flags = regex_constants::match_default);

#include <libstud/regex/regex.hxx>

#include <string>  // char_traits
#include <cstddef> // size_t, ptrdiff_t

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::size_t;
using std::char_traits;
using std::ptrdiff_t;

int main(int, char**)
{
    {
        cmatch m;
        assert(!regex_match("a", m, regex()));
        assert(m.size() == 0);
        assert(m.empty());
    }
    {
        cmatch m;
        const char s[] = "a";
        assert(regex_match(s, m, regex("a", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.empty());
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+1);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == "a");
    }
    {
        cmatch m;
        const char s[] = "ab";
        assert(regex_match(s, m, regex("ab", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+2);
        assert(m.length(0) == 2);
        assert(m.position(0) == 0);
        assert(m.str(0) == "ab");
    }
    {
        cmatch m;
        const char s[] = "ab";
        assert(!regex_match(s, m, regex("ba", regex_constants::basic)));
        assert(m.size() == 0);
        assert(m.empty());
    }
    {
        cmatch m;
        const char s[] = "aab";
        assert(!regex_match(s, m, regex("ab", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "aab";
        assert(!regex_match(s, m, regex("ab", regex_constants::basic),
                                              regex_constants::match_continuous));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abcd";
        assert(!regex_match(s, m, regex("bc", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abbc";
        assert(regex_match(s, m, regex("ab*c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+4);
        assert(m.length(0) == 4);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "ababc";
        assert(regex_match(s, m, regex("\\(ab\\)*c", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+5);
        assert(m.length(0) == 5);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 2);
        assert(m.position(1) == 2);
        assert(m.str(1) == "ab");
    }
    {
        cmatch m;
        const char s[] = "abcdefghijk";
        assert(!regex_match(s, m, regex("cd\\(\\(e\\)fg\\)hi",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abc";
        assert(regex_match(s, m, regex("^abc", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "abcd";
        assert(!regex_match(s, m, regex("^abc", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "aabc";
        assert(!regex_match(s, m, regex("^abc", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abc";
        assert(regex_match(s, m, regex("abc$", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "efabc";
        assert(!regex_match(s, m, regex("abc$", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "efabcg";
        assert(!regex_match(s, m, regex("abc$", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abc";
        assert(regex_match(s, m, regex("a.c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "acc";
        assert(regex_match(s, m, regex("a.c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "acc";
        assert(regex_match(s, m, regex("a.c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "abcdef";
        assert(regex_match(s, m, regex("\\(.*\\).*", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+6);
        assert(m.length(0) == 6);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 6);
        assert(m.position(1) == 0);
        assert(m.str(1) == s);
    }
    {
        cmatch m;
        const char s[] = "bc";
        assert(!regex_match(s, m, regex("\\(a*\\)*", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abbc";
        assert(!regex_match(s, m, regex("ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abbbc";
        assert(regex_match(s, m, regex("ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == sizeof(s)-1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "abbbbc";
        assert(regex_match(s, m, regex("ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == sizeof(s)-1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "abbbbbc";
        assert(regex_match(s, m, regex("ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == sizeof(s)-1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "adefc";
        assert(!regex_match(s, m, regex("ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "abbbbbbc";
        assert(!regex_match(s, m, regex("ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "adec";
        assert(!regex_match(s, m, regex("a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "adefc";
        assert(regex_match(s, m, regex("a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == sizeof(s)-1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "adefgc";
        assert(regex_match(s, m, regex("a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == sizeof(s)-1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "adefghc";
        assert(regex_match(s, m, regex("a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == sizeof(s)-1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "adefghic";
        assert(!regex_match(s, m, regex("a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "-ab,ab-";
        assert(regex_match(s, m, regex("-\\(.*\\),\\1-", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 2);
        assert(m.position(1) == 1);
        assert(m.str(1) == "ab");
    }
    {
        cmatch m;
        const char s[] = "ababbabb";
        assert(regex_match(s, m, regex("^\\(ab*\\)*\\1$", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == "abb");
    }
    {
        cmatch m;
        const char s[] = "ababbab";
        assert(!regex_match(s, m, regex("^\\(ab*\\)*\\1$", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "aBAbbAbB";
        assert(regex_match(s, m, regex("^\\(Ab*\\)*\\1$",
                                       regex_constants::basic | regex_constants::icase)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == "Abb");
    }
    {
        cmatch m;
        const char s[] = "aBAbbAbB";
        assert(!regex_match(s, m, regex("^\\(Ab*\\)*\\1$",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "a";
        assert(regex_match(s, m, regex("^[a]$",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == "a");
    }
    {
        cmatch m;
        const char s[] = "a";
        assert(regex_match(s, m, regex("^[ab]$",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == "a");
    }
    {
        cmatch m;
        const char s[] = "c";
        assert(regex_match(s, m, regex("^[a-f]$",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "g";
        assert(!regex_match(s, m, regex("^[a-f]$",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "Iraqi";
        assert(!regex_match(s, m, regex("q[^u]",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "Iraq";
        assert(!regex_match(s, m, regex("q[^u]",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "AmB";
        assert(regex_match(s, m, regex("A[[:lower:]]B",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "AMB";
        assert(!regex_match(s, m, regex("A[[:lower:]]B",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "AMB";
        assert(regex_match(s, m, regex("A[^[:lower:]]B",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "AmB";
        assert(!regex_match(s, m, regex("A[^[:lower:]]B",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "A5B";
        assert(!regex_match(s, m, regex("A[^[:lower:]0-9]B",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "A?B";
        assert(regex_match(s, m, regex("A[^[:lower:]0-9]B",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "m";
        assert(regex_match(s, m, regex("[a[=m=]z]",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "m";
        assert(!regex_match(s, m, regex("[a[=M=]z]",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "-";
        assert(regex_match(s, m, regex("[a[.hyphen.]z]",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "z";
        assert(regex_match(s, m, regex("[a[.hyphen.]z]",
                                       regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        cmatch m;
        const char s[] = "m";
        assert(!regex_match(s, m, regex("[a[.hyphen.]z]",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "01a45cef9";
        assert(!regex_match(s, m, regex("[ace1-9]*",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        cmatch m;
        const char s[] = "01a45cef9";
        assert(!regex_match(s, m, regex("[ace1-9]\\{1,\\}",
                                        regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        const char r[] = "^[-+]\\{0,1\\}[0-9]\\{1,\\}[CF]$";
        ptrdiff_t sr = char_traits<char>::length(r);
        typedef forward_iterator<const char*> FI;
        typedef bidirectional_iterator<const char*> BI;
        regex regex(FI(r), FI(r+sr), regex_constants::basic);
        match_results<BI> m;
        const char s[] = "-40C";
        ptrdiff_t ss = char_traits<char>::length(s);
        assert(regex_match(BI(s), BI(s+ss), m, regex));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == BI(s));
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 4);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        wcmatch m;
        assert(!regex_match(L"a", m, wregex()));
        assert(m.size() == 0);
        assert(m.empty());
    }
    {
        wcmatch m;
        const wchar_t s[] = L"a";
        assert(regex_match(s, m, wregex(L"a", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.empty());
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+1);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == L"a");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"ab";
        assert(regex_match(s, m, wregex(L"ab", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+2);
        assert(m.length(0) == 2);
        assert(m.position(0) == 0);
        assert(m.str(0) == L"ab");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"ab";
        assert(!regex_match(s, m, wregex(L"ba", regex_constants::basic)));
        assert(m.size() == 0);
        assert(m.empty());
    }
    {
        wcmatch m;
        const wchar_t s[] = L"aab";
        assert(!regex_match(s, m, wregex(L"ab", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"aab";
        assert(!regex_match(s, m, wregex(L"ab", regex_constants::basic),
                            regex_constants::match_continuous));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abcd";
        assert(!regex_match(s, m, wregex(L"bc", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abbc";
        assert(regex_match(s, m, wregex(L"ab*c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+4);
        assert(m.length(0) == 4);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"ababc";
        assert(regex_match(s, m, wregex(L"\\(ab\\)*c", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+5);
        assert(m.length(0) == 5);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 2);
        assert(m.position(1) == 2);
        assert(m.str(1) == L"ab");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abcdefghijk";
        assert(!regex_match(s, m, wregex(L"cd\\(\\(e\\)fg\\)hi",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abc";
        assert(regex_match(s, m, wregex(L"^abc", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abcd";
        assert(!regex_match(s, m, wregex(L"^abc", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"aabc";
        assert(!regex_match(s, m, wregex(L"^abc", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abc";
        assert(regex_match(s, m, wregex(L"abc$", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"efabc";
        assert(!regex_match(s, m, wregex(L"abc$", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"efabcg";
        assert(!regex_match(s, m, wregex(L"abc$", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abc";
        assert(regex_match(s, m, wregex(L"a.c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"acc";
        assert(regex_match(s, m, wregex(L"a.c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"acc";
        assert(regex_match(s, m, wregex(L"a.c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+3);
        assert(m.length(0) == 3);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abcdef";
        assert(regex_match(s, m, wregex(L"\\(.*\\).*", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s+6);
        assert(m.length(0) == 6);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 6);
        assert(m.position(1) == 0);
        assert(m.str(1) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"bc";
        assert(!regex_match(s, m, wregex(L"\\(a*\\)*", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abbc";
        assert(!regex_match(s, m, wregex(L"ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abbbc";
        assert(regex_match(s, m, wregex(L"ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abbbbc";
        assert(regex_match(s, m, wregex(L"ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abbbbbc";
        assert(regex_match(s, m, wregex(L"ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"adefc";
        assert(!regex_match(s, m, wregex(L"ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"abbbbbbc";
        assert(!regex_match(s, m, wregex(L"ab\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"adec";
        assert(!regex_match(s, m, wregex(L"a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"adefc";
        assert(regex_match(s, m, wregex(L"a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"adefgc";
        assert(regex_match(s, m, wregex(L"a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"adefghc";
        assert(regex_match(s, m, wregex(L"a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"adefghic";
        assert(!regex_match(s, m, wregex(L"a.\\{3,5\\}c", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"-ab,ab-";
        assert(regex_match(s, m, wregex(L"-\\(.*\\),\\1-", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 2);
        assert(m.position(1) == 1);
        assert(m.str(1) == L"ab");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"ababbabb";
        assert(regex_match(s, m, wregex(L"^\\(ab*\\)*\\1$", regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == L"abb");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"ababbab";
        assert(!regex_match(s, m, wregex(L"^\\(ab*\\)*\\1$", regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"aBAbbAbB";
        assert(regex_match(s, m, wregex(L"^\\(Ab*\\)*\\1$",
                   regex_constants::basic | regex_constants::icase)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == L"Abb");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"aBAbbAbB";
        assert(!regex_match(s, m, wregex(L"^\\(Ab*\\)*\\1$",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"a";
        assert(regex_match(s, m, wregex(L"^[a]$",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == L"a");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"a";
        assert(regex_match(s, m, wregex(L"^[ab]$",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == L"a");
    }
    {
        wcmatch m;
        const wchar_t s[] = L"c";
        assert(regex_match(s, m, wregex(L"^[a-f]$",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 1);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"g";
        assert(!regex_match(s, m, wregex(L"^[a-f]$",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"Iraqi";
        assert(!regex_match(s, m, wregex(L"q[^u]",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"Iraq";
        assert(!regex_match(s, m, wregex(L"q[^u]",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"AmB";
        assert(regex_match(s, m, wregex(L"A[[:lower:]]B",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"AMB";
        assert(!regex_match(s, m, wregex(L"A[[:lower:]]B",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"AMB";
        assert(regex_match(s, m, wregex(L"A[^[:lower:]]B",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"AmB";
        assert(!regex_match(s, m, wregex(L"A[^[:lower:]]B",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"A5B";
        assert(!regex_match(s, m, wregex(L"A[^[:lower:]0-9]B",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"A?B";
        assert(regex_match(s, m, wregex(L"A[^[:lower:]0-9]B",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"m";
        assert(regex_match(s, m, wregex(L"[a[=m=]z]",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"m";
        assert(!regex_match(s, m, wregex(L"[a[=M=]z]",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"-";
        assert(regex_match(s, m, wregex(L"[a[.hyphen.]z]",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"z";
        assert(regex_match(s, m, wregex(L"[a[.hyphen.]z]",
                                        regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<size_t>(m.length(0)) == char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"m";
        assert(!regex_match(s, m, wregex(L"[a[.hyphen.]z]",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"01a45cef9";
        assert(!regex_match(s, m, wregex(L"[ace1-9]*",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        wcmatch m;
        const wchar_t s[] = L"01a45cef9";
        assert(!regex_match(s, m, wregex(L"[ace1-9]\\{1,\\}",
                                         regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        const wchar_t r[] = L"^[-+]\\{0,1\\}[0-9]\\{1,\\}[CF]$";
        ptrdiff_t sr = char_traits<wchar_t>::length(r);
        typedef forward_iterator<const wchar_t*> FI;
        typedef bidirectional_iterator<const wchar_t*> BI;
        wregex regex(FI(r), FI(r+sr), regex_constants::basic);
        match_results<BI> m;
        const wchar_t s[] = L"-40C";
        ptrdiff_t ss = char_traits<wchar_t>::length(s);
        assert(regex_match(BI(s), BI(s+ss), m, regex));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == BI(s));
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) == 4);
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
#endif // TEST_HAS_NO_WIDE_CHARACTERS

    { // LWG 2273
        regex re("Foo|FooBar");
        cmatch m;
        {
            assert(regex_match("FooBar", m, re));
            assert(m.size() == 1);
            assert(m[0] == "FooBar");
        }
        {
            assert(regex_match("Foo", m, re));
            assert(m.size() == 1);
            assert(m[0] == "Foo");
        }
        {
            assert(!regex_match("FooBarBaz", m, re));
            assert(m.size() == 0);
            assert(m.empty());
        }
        {
            assert(!regex_match("FooBa", m, re));
            assert(m.size() == 0);
            assert(m.empty());
        }
    }

  return 0;
}
