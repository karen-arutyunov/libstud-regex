//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class BidirectionalIterator, class Allocator, class charT, class traits>
//     bool
//     regex_search(BidirectionalIterator first, BidirectionalIterator last,
//                  match_results<BidirectionalIterator, Allocator>& m,
//                  const basic_regex<charT, traits>& e,
//                  regex_constants::match_flag_type flags = regex_constants::match_default);

#include <libstud/regex/regex.hxx>

#include <string>
#include <cstddef> // size_t
#include <cstring> // strlen()

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;
using std::size_t;
using std::char_traits;
using std::strlen;

extern "C" void LLVMFuzzerTestOneInput(const char *data)
{
#ifndef TEST_HAS_NO_EXCEPTIONS
    size_t size = strlen(data);
    if (size > 0)
    {
        try
        {
            regex::flag_type flag = regex_constants::grep;
            string s((const char *)data, size);
            regex re(s, flag);
            TEST_IGNORE_NODISCARD regex_match(s, re);
        }
        catch (regex_error &) {}
    }
#else
    ((void)data);
#endif
}


void fuzz_tests()  // patterns that the fuzzer has found
{
// Raw string literals are a C++11 feature.
#if TEST_STD_VER >= 11
    LLVMFuzzerTestOneInput(R"XX(Õ)_%()()((\8'_%()_%()_%()_%(()_%()_%()_%(.t;)()¥f()_%()(.)_%;)()!¥f(((()()XX");
#endif
}

int main(int, char**)
{
    {
        cmatch m;
        const char s[] = "tournament";
        assert(regex_search(s, m, regex("tour\nto\ntournament",
                regex_constants::grep)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(!m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s + char_traits<char>::length(s));
        assert(m.length(0) == 10);
        assert(m.position(0) == 0);
        assert(m.str(0) == "tournament");
    }
    {
        cmatch m;
        const char s[] = "ment";
        assert(regex_search(s, m, regex("tour\n\ntournament",
                regex_constants::grep)));
        assert(m.size() == 1);
        assert(!m.prefix().matched);
        assert(m.prefix().first == s);
        assert(m.prefix().second == m[0].first);
        assert(m.suffix().matched);
        assert(m.suffix().first == m[0].second);
        assert(m.suffix().second == s + char_traits<char>::length(s));
        assert(m.length(0) == 0);
        assert(m.position(0) == 0);
        assert(m.str(0) == "");
    }
    fuzz_tests();

  return 0;
}
