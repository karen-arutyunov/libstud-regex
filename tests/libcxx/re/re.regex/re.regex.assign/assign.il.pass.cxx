//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03

// <regex>

// template <class charT, class traits = regex_traits<charT>> class basic_regex;

// basic_regex&
//    assign(initializer_list<charT> il,
//           flag_type f = regex_constants::ECMAScript);

#include <libstud/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**)
{
    regex r2;
    r2.assign({'(', 'a', '(', '[', 'b', 'c', ']', ')', ')'});
    assert(r2.flags() == regex::ECMAScript);
    assert(r2.mark_count() == 2);

#if (!defined(__GNUC__) || __GNUC__ >= 5)
    r2.assign({'(', 'a', '(', '[', 'b', 'c', ']', ')', ')'}, regex::extended);
#else
    r2.assign(std::initializer_list<char> ({'(', 'a', '(', '[', 'b', 'c', ']', ')', ')'}), regex::extended);
#endif

    assert(r2.flags() == regex::extended);
    assert(r2.mark_count() == 2);

  return 0;
}
