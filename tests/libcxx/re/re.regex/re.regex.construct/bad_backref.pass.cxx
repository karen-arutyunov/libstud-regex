//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: no-exceptions
// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// template <class ST, class SA>
//    basic_regex(const basic_string<charT, ST, SA>& s);

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

static bool error_badbackref_thrown(const char *pat, regex::flag_type f)
{
    bool result = false;
    try {
        regex re(pat, f);
    } catch (const regex_error &ex) {
        result = (ex.code() == regex_constants::error_backref);
    }
    return result;
}

int main(int, char**)
{
//  no references
    assert(error_badbackref_thrown("\\1abc", regex_constants::ECMAScript));
    assert(error_badbackref_thrown("\\1abd", regex::basic));
    assert(error_badbackref_thrown("\\1abd", regex::extended));
    assert(error_badbackref_thrown("\\1abd", regex::awk) == false);
    assert(error_badbackref_thrown("\\1abd", regex::grep));
    assert(error_badbackref_thrown("\\1abd", regex::egrep));

//  only one reference
    assert(error_badbackref_thrown("ab(c)\\2def", regex_constants::ECMAScript));
    assert(error_badbackref_thrown("ab\\(c\\)\\2def", regex_constants::basic));
    assert(error_badbackref_thrown("ab(c)\\2def", regex_constants::extended));
    assert(error_badbackref_thrown("ab\\(c\\)\\2def", regex_constants::awk) == false);
    assert(error_badbackref_thrown("ab(c)\\2def", regex_constants::awk) == false);
    assert(error_badbackref_thrown("ab\\(c\\)\\2def", regex_constants::grep));
    assert(error_badbackref_thrown("ab(c)\\2def", regex_constants::egrep));


    assert(error_badbackref_thrown("\\800000000000000000000000000000", regex_constants::ECMAScript)); // overflows

//  this should NOT throw, because we only should look at the '1'
//  See https://llvm.org/PR31387
    {
    const char *pat1 = "a(b)c\\1234";
    regex re(pat1, pat1 + 7); // extra chars after the end.
    }

//  reference before group
    assert(error_badbackref_thrown("\\1(abc)", regex_constants::ECMAScript));
    assert(error_badbackref_thrown("\\1\\(abd\\)", regex::basic));
    assert(error_badbackref_thrown("\\1(abd)", regex::extended));
    assert(error_badbackref_thrown("\\1(abd)", regex::awk) == false);
    assert(error_badbackref_thrown("\\1\\(abd\\)", regex::awk) == false);
    assert(error_badbackref_thrown("\\1\\(abd\\)", regex::grep));
    assert(error_badbackref_thrown("\\1(abd)", regex::egrep));

//  reference limit
    assert(error_badbackref_thrown("(cat)\\10", regex::ECMAScript));
    assert(error_badbackref_thrown("\\(cat\\)\\10", regex::basic) == false);
    assert(error_badbackref_thrown("(cat)\\10", regex::extended) == false);
    assert(error_badbackref_thrown("\\(cat\\)\\10", regex::awk) == false);
    assert(error_badbackref_thrown("(cat)\\10", regex::awk) == false);
    assert(error_badbackref_thrown("\\(cat\\)\\10", regex::grep) == false);
    assert(error_badbackref_thrown("(cat)\\10", regex::egrep) == false);

//  https://llvm.org/PR34297
    assert(error_badbackref_thrown("(cat)\\1", regex::basic));
    assert(error_badbackref_thrown("\\(cat\\)\\1", regex::basic) == false);
    assert(error_badbackref_thrown("(cat)\\1", regex::extended) == false);
    assert(error_badbackref_thrown("\\(cat\\)\\1", regex::extended));
    assert(error_badbackref_thrown("(cat)\\1", regex::awk) == false);
    assert(error_badbackref_thrown("\\(cat\\)\\1", regex::awk) == false);
    assert(error_badbackref_thrown("(cat)\\1", regex::grep));
    assert(error_badbackref_thrown("\\(cat\\)\\1", regex::grep) == false);
    assert(error_badbackref_thrown("(cat)\\1", regex::egrep) == false);
    assert(error_badbackref_thrown("\\(cat\\)\\1", regex::egrep));

  return 0;
}
