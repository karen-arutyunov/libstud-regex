//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class regex_error
//     : public runtime_error
// {
// public:
//     explicit regex_error(regex_constants::error_type ecode);
//     regex_constants::error_type code() const;
// };

#include <libstud/regex.hxx>

#include <string>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::string;

int main(int, char**)
{
    {
        regex_error e(regex_constants::error_collate);
        assert(e.code() == regex_constants::error_collate);
        LIBCPP_ASSERT(e.what() == string("The expression contained an invalid collating element name."));
    }
    {
        regex_error e(regex_constants::error_ctype);
        assert(e.code() == regex_constants::error_ctype);
        LIBCPP_ASSERT(e.what() == string("The expression contained an invalid character class name."));
    }
    {
        regex_error e(regex_constants::error_escape);
        assert(e.code() == regex_constants::error_escape);
        LIBCPP_ASSERT(e.what() == string("The expression contained an invalid escaped character, or a "
               "trailing escape."));
    }
    {
        regex_error e(regex_constants::error_backref);
        assert(e.code() == regex_constants::error_backref);
        LIBCPP_ASSERT(e.what() == string("The expression contained an invalid back reference."));
    }
    {
        regex_error e(regex_constants::error_brack);
        assert(e.code() == regex_constants::error_brack);
        LIBCPP_ASSERT(e.what() == string("The expression contained mismatched [ and ]."));
    }
    {
        regex_error e(regex_constants::error_paren);
        assert(e.code() == regex_constants::error_paren);
        LIBCPP_ASSERT(e.what() == string("The expression contained mismatched ( and )."));
    }
    {
        regex_error e(regex_constants::error_brace);
        assert(e.code() == regex_constants::error_brace);
        LIBCPP_ASSERT(e.what() == string("The expression contained mismatched { and }."));
    }
    {
        regex_error e(regex_constants::error_badbrace);
        assert(e.code() == regex_constants::error_badbrace);
        LIBCPP_ASSERT(e.what() == string("The expression contained an invalid range in a {} expression."));
    }
    {
        regex_error e(regex_constants::error_range);
        assert(e.code() == regex_constants::error_range);
        LIBCPP_ASSERT(e.what() == string("The expression contained an invalid character range, "
               "such as [b-a] in most encodings."));
    }
    {
        regex_error e(regex_constants::error_space);
        assert(e.code() == regex_constants::error_space);
        LIBCPP_ASSERT(e.what() == string("There was insufficient memory to convert the expression into "
               "a finite state machine."));
    }
    {
        regex_error e(regex_constants::error_badrepeat);
        assert(e.code() == regex_constants::error_badrepeat);
        LIBCPP_ASSERT(e.what() == string("One of *?+{ was not preceded by a valid regular expression."));
    }
    {
        regex_error e(regex_constants::error_complexity);
        assert(e.code() == regex_constants::error_complexity);
        LIBCPP_ASSERT(e.what() == string("The complexity of an attempted match against a regular "
               "expression exceeded a pre-set level."));
    }
    {
        regex_error e(regex_constants::error_stack);
        assert(e.code() == regex_constants::error_stack);
        LIBCPP_ASSERT(e.what() == string("There was insufficient memory to determine whether the regular "
               "expression could match the specified character sequence."));
    }

  return 0;
}
