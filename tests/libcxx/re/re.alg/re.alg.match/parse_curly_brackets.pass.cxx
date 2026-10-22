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
//     regex_match(BidirectionalIterator first, BidirectionalIterator last,
//                  match_results<BidirectionalIterator, Allocator>& m,
//                  const basic_regex<charT, traits>& e,
//                  regex_constants::match_flag_type flags = regex_constants::match_default);

// https://llvm.org/PR16135

#include <libstud/regex/regex.hxx>

#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;

void
test1()
{
    string re("\\{a\\}");
    string target("{a}");
    regex regex(re);
    smatch smatch;
    assert((regex_match(target, smatch, regex)));
}

void
test2()
{
    string re("\\{a\\}");
    string target("{a}");
    regex regex(re, regex::extended);
    smatch smatch;
    assert((regex_match(target, smatch, regex)));
}

void
test3()
{
    string re("\\{a\\}");
    string target("{a}");
    regex regex(re, regex::awk);
    smatch smatch;
    assert((regex_match(target, smatch, regex)));
}

void
test4()
{
    string re("\\{a\\}");
    string target("{a}");
    regex regex(re, regex::egrep);
    smatch smatch;
    assert((regex_match(target, smatch, regex)));
}

int main(int, char**)
{
    test1();
    test2();
    test3();
    test4();

  return 0;
}
