//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// namespace regex_constants
// {
//
// enum error_type
// {
//     error_collate    = unspecified,
//     error_ctype      = unspecified,
//     error_escape     = unspecified,
//     error_backref    = unspecified,
//     error_brack      = unspecified,
//     error_paren      = unspecified,
//     error_brace      = unspecified,
//     error_badbrace   = unspecified,
//     error_range      = unspecified,
//     error_space      = unspecified,
//     error_badrepeat  = unspecified,
//     error_complexity = unspecified,
//     error_stack      = unspecified
// };
//
// }

#include <libstud/regex/regex.hxx>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

int main(int, char**)
{
    LIBCPP_ASSERT(regex_constants::error_collate != 0);
    LIBCPP_ASSERT(regex_constants::error_ctype != 0);
    LIBCPP_ASSERT(regex_constants::error_escape != 0);
    LIBCPP_ASSERT(regex_constants::error_backref != 0);
    LIBCPP_ASSERT(regex_constants::error_brack != 0);
    LIBCPP_ASSERT(regex_constants::error_paren != 0);
    LIBCPP_ASSERT(regex_constants::error_brace != 0);
    LIBCPP_ASSERT(regex_constants::error_badbrace != 0);
    LIBCPP_ASSERT(regex_constants::error_range != 0);
    LIBCPP_ASSERT(regex_constants::error_space != 0);
    LIBCPP_ASSERT(regex_constants::error_badrepeat != 0);
    LIBCPP_ASSERT(regex_constants::error_complexity != 0);
    LIBCPP_ASSERT(regex_constants::error_stack != 0);

    assert(regex_constants::error_collate != regex_constants::error_ctype);
    assert(regex_constants::error_collate != regex_constants::error_escape);
    assert(regex_constants::error_collate != regex_constants::error_backref);
    assert(regex_constants::error_collate != regex_constants::error_brack);
    assert(regex_constants::error_collate != regex_constants::error_paren);
    assert(regex_constants::error_collate != regex_constants::error_brace);
    assert(regex_constants::error_collate != regex_constants::error_badbrace);
    assert(regex_constants::error_collate != regex_constants::error_range);
    assert(regex_constants::error_collate != regex_constants::error_space);
    assert(regex_constants::error_collate != regex_constants::error_badrepeat);
    assert(regex_constants::error_collate != regex_constants::error_complexity);
    assert(regex_constants::error_collate != regex_constants::error_stack);

    assert(regex_constants::error_ctype != regex_constants::error_escape);
    assert(regex_constants::error_ctype != regex_constants::error_backref);
    assert(regex_constants::error_ctype != regex_constants::error_brack);
    assert(regex_constants::error_ctype != regex_constants::error_paren);
    assert(regex_constants::error_ctype != regex_constants::error_brace);
    assert(regex_constants::error_ctype != regex_constants::error_badbrace);
    assert(regex_constants::error_ctype != regex_constants::error_range);
    assert(regex_constants::error_ctype != regex_constants::error_space);
    assert(regex_constants::error_ctype != regex_constants::error_badrepeat);
    assert(regex_constants::error_ctype != regex_constants::error_complexity);
    assert(regex_constants::error_ctype != regex_constants::error_stack);

    assert(regex_constants::error_escape != regex_constants::error_backref);
    assert(regex_constants::error_escape != regex_constants::error_brack);
    assert(regex_constants::error_escape != regex_constants::error_paren);
    assert(regex_constants::error_escape != regex_constants::error_brace);
    assert(regex_constants::error_escape != regex_constants::error_badbrace);
    assert(regex_constants::error_escape != regex_constants::error_range);
    assert(regex_constants::error_escape != regex_constants::error_space);
    assert(regex_constants::error_escape != regex_constants::error_badrepeat);
    assert(regex_constants::error_escape != regex_constants::error_complexity);
    assert(regex_constants::error_escape != regex_constants::error_stack);

    assert(regex_constants::error_backref != regex_constants::error_brack);
    assert(regex_constants::error_backref != regex_constants::error_paren);
    assert(regex_constants::error_backref != regex_constants::error_brace);
    assert(regex_constants::error_backref != regex_constants::error_badbrace);
    assert(regex_constants::error_backref != regex_constants::error_range);
    assert(regex_constants::error_backref != regex_constants::error_space);
    assert(regex_constants::error_backref != regex_constants::error_badrepeat);
    assert(regex_constants::error_backref != regex_constants::error_complexity);
    assert(regex_constants::error_backref != regex_constants::error_stack);

    assert(regex_constants::error_brack != regex_constants::error_paren);
    assert(regex_constants::error_brack != regex_constants::error_brace);
    assert(regex_constants::error_brack != regex_constants::error_badbrace);
    assert(regex_constants::error_brack != regex_constants::error_range);
    assert(regex_constants::error_brack != regex_constants::error_space);
    assert(regex_constants::error_brack != regex_constants::error_badrepeat);
    assert(regex_constants::error_brack != regex_constants::error_complexity);
    assert(regex_constants::error_brack != regex_constants::error_stack);

    assert(regex_constants::error_paren != regex_constants::error_brace);
    assert(regex_constants::error_paren != regex_constants::error_badbrace);
    assert(regex_constants::error_paren != regex_constants::error_range);
    assert(regex_constants::error_paren != regex_constants::error_space);
    assert(regex_constants::error_paren != regex_constants::error_badrepeat);
    assert(regex_constants::error_paren != regex_constants::error_complexity);
    assert(regex_constants::error_paren != regex_constants::error_stack);

    assert(regex_constants::error_brace != regex_constants::error_badbrace);
    assert(regex_constants::error_brace != regex_constants::error_range);
    assert(regex_constants::error_brace != regex_constants::error_space);
    assert(regex_constants::error_brace != regex_constants::error_badrepeat);
    assert(regex_constants::error_brace != regex_constants::error_complexity);
    assert(regex_constants::error_brace != regex_constants::error_stack);

    assert(regex_constants::error_badbrace != regex_constants::error_range);
    assert(regex_constants::error_badbrace != regex_constants::error_space);
    assert(regex_constants::error_badbrace != regex_constants::error_badrepeat);
    assert(regex_constants::error_badbrace != regex_constants::error_complexity);
    assert(regex_constants::error_badbrace != regex_constants::error_stack);

    assert(regex_constants::error_range != regex_constants::error_space);
    assert(regex_constants::error_range != regex_constants::error_badrepeat);
    assert(regex_constants::error_range != regex_constants::error_complexity);
    assert(regex_constants::error_range != regex_constants::error_stack);

    assert(regex_constants::error_space != regex_constants::error_badrepeat);
    assert(regex_constants::error_space != regex_constants::error_complexity);
    assert(regex_constants::error_space != regex_constants::error_stack);

    assert(regex_constants::error_badrepeat != regex_constants::error_complexity);
    assert(regex_constants::error_badrepeat != regex_constants::error_stack);

    assert(regex_constants::error_complexity != regex_constants::error_stack);

  return 0;
}
