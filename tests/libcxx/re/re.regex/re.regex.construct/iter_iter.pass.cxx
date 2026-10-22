//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// template <class ForwardIterator>
//    basic_regex(ForwardIterator first, ForwardIterator last);

#include <libstud/regex/regex.hxx>

#include <string>
#include <iterator>

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;
using std::iterator_traits;

template <class Iter>
void
test(Iter first, Iter last, unsigned mc)
{
    basic_regex<typename iterator_traits<Iter>::value_type> r(first, last);
    assert(r.flags() == regex_constants::ECMAScript);
    assert(r.mark_count() == mc);
}

int main(int, char**)
{
    typedef forward_iterator<string::const_iterator> F;
    string s1("\\(a\\)");
    string s2("\\(a[bc]\\)");
    string s3("\\(a\\([bc]\\)\\)");
    string s4("(a([bc]))");

    test(F(s1.begin()), F(s1.end()), 0);
    test(F(s2.begin()), F(s2.end()), 0);
    test(F(s3.begin()), F(s3.end()), 0);
    test(F(s4.begin()), F(s4.end()), 2);

  return 0;
}
