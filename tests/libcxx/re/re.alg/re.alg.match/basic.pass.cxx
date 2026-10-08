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

#include <libstud/regex.hxx>

#include <string>  // char_traits
#include <cstddef> // size_t, ptrdiff_t

#undef NDEBUG
#include <cassert>

int main(int, char**)
{
    {
        stud::cmatch m;
        assert(!stud::regex_match("a", m, stud::regex()));
        assert(m.size() == 0);
        assert(m.empty());
    }
    {
        stud::cmatch m;
        const char s[] = "a";
        assert(stud::regex_match(s, m, stud::regex("a", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "ab";
        assert(stud::regex_match(s, m, stud::regex("ab", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "ab";
        assert(!stud::regex_match(s, m, stud::regex("ba", stud::regex_constants::basic)));
        assert(m.size() == 0);
        assert(m.empty());
    }
    {
        stud::cmatch m;
        const char s[] = "aab";
        assert(!stud::regex_match(s, m, stud::regex("ab", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "aab";
        assert(!stud::regex_match(s, m, stud::regex("ab", stud::regex_constants::basic),
                                            stud::regex_constants::match_continuous));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abcd";
        assert(!stud::regex_match(s, m, stud::regex("bc", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abbc";
        assert(stud::regex_match(s, m, stud::regex("ab*c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "ababc";
        assert(stud::regex_match(s, m, stud::regex("\\(ab\\)*c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "abcdefghijk";
        assert(!stud::regex_match(s, m, stud::regex("cd\\(\\(e\\)fg\\)hi",
                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abc";
        assert(stud::regex_match(s, m, stud::regex("^abc", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "abcd";
        assert(!stud::regex_match(s, m, stud::regex("^abc", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "aabc";
        assert(!stud::regex_match(s, m, stud::regex("^abc", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abc";
        assert(stud::regex_match(s, m, stud::regex("abc$", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "efabc";
        assert(!stud::regex_match(s, m, stud::regex("abc$", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "efabcg";
        assert(!stud::regex_match(s, m, stud::regex("abc$", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abc";
        assert(stud::regex_match(s, m, stud::regex("a.c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "acc";
        assert(stud::regex_match(s, m, stud::regex("a.c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "acc";
        assert(stud::regex_match(s, m, stud::regex("a.c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "abcdef";
        assert(stud::regex_match(s, m, stud::regex("\\(.*\\).*", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "bc";
        assert(!stud::regex_match(s, m, stud::regex("\\(a*\\)*", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abbc";
        assert(!stud::regex_match(s, m, stud::regex("ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abbbc";
        assert(stud::regex_match(s, m, stud::regex("ab\\{3,5\\}c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "abbbbc";
        assert(stud::regex_match(s, m, stud::regex("ab\\{3,5\\}c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "abbbbbc";
        assert(stud::regex_match(s, m, stud::regex("ab\\{3,5\\}c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "adefc";
        assert(!stud::regex_match(s, m, stud::regex("ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "abbbbbbc";
        assert(!stud::regex_match(s, m, stud::regex("ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "adec";
        assert(!stud::regex_match(s, m, stud::regex("a.\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "adefc";
        assert(stud::regex_match(s, m, stud::regex("a.\\{3,5\\}c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "adefgc";
        assert(stud::regex_match(s, m, stud::regex("a.\\{3,5\\}c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "adefghc";
        assert(stud::regex_match(s, m, stud::regex("a.\\{3,5\\}c", stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "adefghic";
        assert(!stud::regex_match(s, m, stud::regex("a.\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "-ab,ab-";
        assert(stud::regex_match(s, m, stud::regex("-\\(.*\\),\\1-", stud::regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 2);
        assert(m.position(1) == 1);
        assert(m.str(1) == "ab");
    }
    {
        stud::cmatch m;
        const char s[] = "ababbabb";
        assert(stud::regex_match(s, m, stud::regex("^\\(ab*\\)*\\1$", stud::regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == "abb");
    }
    {
        stud::cmatch m;
        const char s[] = "ababbab";
        assert(!stud::regex_match(s, m, stud::regex("^\\(ab*\\)*\\1$", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "aBAbbAbB";
        assert(stud::regex_match(s, m, stud::regex("^\\(Ab*\\)*\\1$",
                   stud::regex_constants::basic | stud::regex_constants::icase)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == "Abb");
    }
    {
        stud::cmatch m;
        const char s[] = "aBAbbAbB";
        assert(!stud::regex_match(s, m, stud::regex("^\\(Ab*\\)*\\1$",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "a";
        assert(stud::regex_match(s, m, stud::regex("^[a]$",
                                                 stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "a";
        assert(stud::regex_match(s, m, stud::regex("^[ab]$",
                                                 stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "c";
        assert(stud::regex_match(s, m, stud::regex("^[a-f]$",
                                                 stud::regex_constants::basic)));
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
        stud::cmatch m;
        const char s[] = "g";
        assert(!stud::regex_match(s, m, stud::regex("^[a-f]$",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "Iraqi";
        assert(!stud::regex_match(s, m, stud::regex("q[^u]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "Iraq";
        assert(!stud::regex_match(s, m, stud::regex("q[^u]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "AmB";
        assert(stud::regex_match(s, m, stud::regex("A[[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::cmatch m;
        const char s[] = "AMB";
        assert(!stud::regex_match(s, m, stud::regex("A[[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "AMB";
        assert(stud::regex_match(s, m, stud::regex("A[^[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::cmatch m;
        const char s[] = "AmB";
        assert(!stud::regex_match(s, m, stud::regex("A[^[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "A5B";
        assert(!stud::regex_match(s, m, stud::regex("A[^[:lower:]0-9]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "A?B";
        assert(stud::regex_match(s, m, stud::regex("A[^[:lower:]0-9]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::cmatch m;
        const char s[] = "m";
        assert(stud::regex_match(s, m, stud::regex("[a[=m=]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::cmatch m;
        const char s[] = "m";
        assert(!stud::regex_match(s, m, stud::regex("[a[=M=]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "-";
        assert(stud::regex_match(s, m, stud::regex("[a[.hyphen.]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::cmatch m;
        const char s[] = "z";
        assert(stud::regex_match(s, m, stud::regex("[a[.hyphen.]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<char>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::cmatch m;
        const char s[] = "m";
        assert(!stud::regex_match(s, m, stud::regex("[a[.hyphen.]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "01a45cef9";
        assert(!stud::regex_match(s, m, stud::regex("[ace1-9]*",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::cmatch m;
        const char s[] = "01a45cef9";
        assert(!stud::regex_match(s, m, stud::regex("[ace1-9]\\{1,\\}",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
#if 0
    {
        const char r[] = "^[-+]\\{0,1\\}[0-9]\\{1,\\}[CF]$";
        std::ptrdiff_t sr = std::char_traits<char>::length(r);
        typedef forward_iterator<const char*> FI;
        typedef bidirectional_iterator<const char*> BI;
        stud::regex regex(FI(r), FI(r+sr), stud::regex_constants::basic);
        stud::match_results<BI> m;
        const char s[] = "-40C";
        std::ptrdiff_t ss = std::char_traits<char>::length(s);
        assert(stud::regex_match(BI(s), BI(s+ss), m, regex));
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
#endif
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    {
        stud::wcmatch m;
        assert(!stud::regex_match(L"a", m, stud::wregex()));
        assert(m.size() == 0);
        assert(m.empty());
    }
#if 0
    {
        stud::wcmatch m;
        const wchar_t s[] = L"a";
        assert(stud::regex_match(s, m, stud::wregex(L"a", stud::regex_constants::basic)));
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
#endif
    {
        stud::wcmatch m;
        const wchar_t s[] = L"ab";
        assert(stud::regex_match(s, m, stud::wregex(L"ab", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"ab";
        assert(!stud::regex_match(s, m, stud::wregex(L"ba", stud::regex_constants::basic)));
        assert(m.size() == 0);
        assert(m.empty());
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"aab";
        assert(!stud::regex_match(s, m, stud::wregex(L"ab", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"aab";
        assert(!stud::regex_match(s, m, stud::wregex(L"ab", stud::regex_constants::basic),
                                            stud::regex_constants::match_continuous));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abcd";
        assert(!stud::regex_match(s, m, stud::wregex(L"bc", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abbc";
        assert(stud::regex_match(s, m, stud::wregex(L"ab*c", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"ababc";
        assert(stud::regex_match(s, m, stud::wregex(L"\\(ab\\)*c", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"abcdefghijk";
        assert(!stud::regex_match(s, m, stud::wregex(L"cd\\(\\(e\\)fg\\)hi",
                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abc";
        assert(stud::regex_match(s, m, stud::wregex(L"^abc", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"abcd";
        assert(!stud::regex_match(s, m, stud::wregex(L"^abc", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"aabc";
        assert(!stud::regex_match(s, m, stud::wregex(L"^abc", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abc";
        assert(stud::regex_match(s, m, stud::wregex(L"abc$", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"efabc";
        assert(!stud::regex_match(s, m, stud::wregex(L"abc$", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"efabcg";
        assert(!stud::regex_match(s, m, stud::wregex(L"abc$", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abc";
        assert(stud::regex_match(s, m, stud::wregex(L"a.c", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"acc";
        assert(stud::regex_match(s, m, stud::wregex(L"a.c", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"acc";
        assert(stud::regex_match(s, m, stud::wregex(L"a.c", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"abcdef";
        assert(stud::regex_match(s, m, stud::wregex(L"\\(.*\\).*", stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"bc";
        assert(!stud::regex_match(s, m, stud::wregex(L"\\(a*\\)*", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abbc";
        assert(!stud::regex_match(s, m, stud::wregex(L"ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abbbc";
        assert(stud::regex_match(s, m, stud::wregex(L"ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abbbbc";
        assert(stud::regex_match(s, m, stud::wregex(L"ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abbbbbc";
        assert(stud::regex_match(s, m, stud::wregex(L"ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"adefc";
        assert(!stud::regex_match(s, m, stud::wregex(L"ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"abbbbbbc";
        assert(!stud::regex_match(s, m, stud::wregex(L"ab\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"adec";
        assert(!stud::regex_match(s, m, stud::wregex(L"a.\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"adefc";
        assert(stud::regex_match(s, m, stud::wregex(L"a.\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"adefgc";
        assert(stud::regex_match(s, m, stud::wregex(L"a.\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"adefghc";
        assert(stud::regex_match(s, m, stud::wregex(L"a.\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"adefghic";
        assert(!stud::regex_match(s, m, stud::wregex(L"a.\\{3,5\\}c", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"-ab,ab-";
        assert(stud::regex_match(s, m, stud::wregex(L"-\\(.*\\),\\1-", stud::regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 2);
        assert(m.position(1) == 1);
        assert(m.str(1) == L"ab");
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"ababbabb";
        assert(stud::regex_match(s, m, stud::wregex(L"^\\(ab*\\)*\\1$", stud::regex_constants::basic)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == L"abb");
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"ababbab";
        assert(!stud::regex_match(s, m, stud::wregex(L"^\\(ab*\\)*\\1$", stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"aBAbbAbB";
        assert(stud::regex_match(s, m, stud::wregex(L"^\\(Ab*\\)*\\1$",
                   stud::regex_constants::basic | stud::regex_constants::icase)));
        assert(m.size() == 2);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
        assert(m.length(1) == 3);
        assert(m.position(1) == 2);
        assert(m.str(1) == L"Abb");
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"aBAbbAbB";
        assert(!stud::regex_match(s, m, stud::wregex(L"^\\(Ab*\\)*\\1$",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"a";
        assert(stud::regex_match(s, m, stud::wregex(L"^[a]$",
                                                 stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"a";
        assert(stud::regex_match(s, m, stud::wregex(L"^[ab]$",
                                                 stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"c";
        assert(stud::regex_match(s, m, stud::wregex(L"^[a-f]$",
                                                 stud::regex_constants::basic)));
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
        stud::wcmatch m;
        const wchar_t s[] = L"g";
        assert(!stud::regex_match(s, m, stud::wregex(L"^[a-f]$",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"Iraqi";
        assert(!stud::regex_match(s, m, stud::wregex(L"q[^u]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"Iraq";
        assert(!stud::regex_match(s, m, stud::wregex(L"q[^u]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"AmB";
        assert(stud::regex_match(s, m, stud::wregex(L"A[[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"AMB";
        assert(!stud::regex_match(s, m, stud::wregex(L"A[[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"AMB";
        assert(stud::regex_match(s, m, stud::wregex(L"A[^[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"AmB";
        assert(!stud::regex_match(s, m, stud::wregex(L"A[^[:lower:]]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"A5B";
        assert(!stud::regex_match(s, m, stud::wregex(L"A[^[:lower:]0-9]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"A?B";
        assert(stud::regex_match(s, m, stud::wregex(L"A[^[:lower:]0-9]B",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"m";
        assert(stud::regex_match(s, m, stud::wregex(L"[a[=m=]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"m";
        assert(!stud::regex_match(s, m, stud::wregex(L"[a[=M=]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"-";
        assert(stud::regex_match(s, m, stud::wregex(L"[a[.hyphen.]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"z";
        assert(stud::regex_match(s, m, stud::wregex(L"[a[.hyphen.]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == m[0].second);
        assert(m.length(0) >= 0 && static_cast<std::size_t>(m.length(0)) == std::char_traits<wchar_t>::length(s));
        assert(m.position(0) == 0);
        assert(m.str(0) == s);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"m";
        assert(!stud::regex_match(s, m, stud::wregex(L"[a[.hyphen.]z]",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"01a45cef9";
        assert(!stud::regex_match(s, m, stud::wregex(L"[ace1-9]*",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
    {
        stud::wcmatch m;
        const wchar_t s[] = L"01a45cef9";
        assert(!stud::regex_match(s, m, stud::wregex(L"[ace1-9]\\{1,\\}",
                                                 stud::regex_constants::basic)));
        assert(m.size() == 0);
    }
#if 0
    {
        const wchar_t r[] = L"^[-+]\\{0,1\\}[0-9]\\{1,\\}[CF]$";
        std::ptrdiff_t sr = std::char_traits<wchar_t>::length(r);
        typedef forward_iterator<const wchar_t*> FI;
        typedef bidirectional_iterator<const wchar_t*> BI;
        stud::wregex regex(FI(r), FI(r+sr), stud::regex_constants::basic);
        stud::match_results<BI> m;
        const wchar_t s[] = L"-40C";
        std::ptrdiff_t ss = std::char_traits<wchar_t>::length(s);
        assert(stud::regex_match(BI(s), BI(s+ss), m, regex));
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
#endif
#endif // TEST_HAS_NO_WIDE_CHARACTERS

    { // LWG 2273
        stud::regex re("Foo|FooBar");
        stud::cmatch m;
        {
            assert(stud::regex_match("FooBar", m, re));
            assert(m.size() == 1);
            assert(m[0] == "FooBar");
        }
        {
            assert(stud::regex_match("Foo", m, re));
            assert(m.size() == 1);
            assert(m[0] == "Foo");
        }
        {
            assert(!stud::regex_match("FooBarBaz", m, re));
            assert(m.size() == 0);
            assert(m.empty());
        }
        {
            assert(!stud::regex_match("FooBa", m, re));
            assert(m.size() == 0);
            assert(m.empty());
        }
    }

  return 0;
}
