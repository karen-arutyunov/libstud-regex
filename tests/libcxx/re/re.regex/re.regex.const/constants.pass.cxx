//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT, class traits = regex_traits<charT>>
// class basic_regex
// {
// public:
//     // constants:
//     static constexpr regex_constants::syntax_option_type icase = regex_constants::icase;
//     static constexpr regex_constants::syntax_option_type nosubs = regex_constants::nosubs;
//     static constexpr regex_constants::syntax_option_type optimize = regex_constants::optimize;
//     static constexpr regex_constants::syntax_option_type collate = regex_constants::collate;
//     static constexpr regex_constants::syntax_option_type ECMAScript = regex_constants::ECMAScript;
//     static constexpr regex_constants::syntax_option_type basic = regex_constants::basic;
//     static constexpr regex_constants::syntax_option_type extended = regex_constants::extended;
//     static constexpr regex_constants::syntax_option_type awk = regex_constants::awk;
//     static constexpr regex_constants::syntax_option_type grep = regex_constants::grep;
//     static constexpr regex_constants::syntax_option_type egrep = regex_constants::egrep;

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

template <class T>
void where(const T &) {}

template <class CharT>
void
test()
{
    typedef basic_regex<CharT> BR;
    static_assert((BR::icase == regex_constants::icase), "");
    static_assert((BR::nosubs == regex_constants::nosubs), "");
    static_assert((BR::optimize == regex_constants::optimize), "");
    static_assert((BR::collate == regex_constants::collate), "");
    static_assert((BR::ECMAScript == regex_constants::ECMAScript), "");
    static_assert((BR::basic == regex_constants::basic), "");
    static_assert((BR::extended == regex_constants::extended), "");
    static_assert((BR::awk == regex_constants::awk), "");
    static_assert((BR::grep == regex_constants::grep), "");
    static_assert((BR::egrep == regex_constants::egrep), "");
    where(BR::icase);
    where(BR::nosubs);
    where(BR::optimize);
    where(BR::collate);
    where(BR::ECMAScript);
    where(BR::basic);
    where(BR::extended);
    where(BR::awk);
    where(BR::grep);
    where(BR::egrep);
}

int main(int, char**)
{
    test<char>();
#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test<wchar_t>();
#endif

    return 0;
}
