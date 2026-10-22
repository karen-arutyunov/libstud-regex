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
// enum match_flag_type  // bitmask type
// {
//     match_default     = 0,
//     match_not_bol     = unspecified,
//     match_not_eol     = unspecified,
//     match_not_bow     = unspecified,
//     match_not_eow     = unspecified,
//     match_any         = unspecified,
//     match_not_null    = unspecified,
//     match_continuous  = unspecified,
//     match_prev_avail  = unspecified,
//     format_default    = 0,
//     format_sed        = unspecified,
//     format_no_copy    = unspecified,
//     format_first_only = unspecified
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
    assert(regex_constants::match_default == 0);
    assert(regex_constants::match_not_bol != 0);
    assert(regex_constants::match_not_eol != 0);
    assert(regex_constants::match_not_bow != 0);
    assert(regex_constants::match_not_eow != 0);
    assert(regex_constants::match_any != 0);
    assert(regex_constants::match_not_null != 0);
    assert(regex_constants::match_continuous != 0);
    assert(regex_constants::match_prev_avail != 0);
    assert(regex_constants::format_default == 0);
    assert(regex_constants::format_sed != 0);
    assert(regex_constants::format_no_copy != 0);
    assert(regex_constants::format_first_only != 0);

    assert((regex_constants::match_not_bol & regex_constants::match_not_eol) == 0);
    assert((regex_constants::match_not_bol & regex_constants::match_not_bow) == 0);
    assert((regex_constants::match_not_bol & regex_constants::match_not_eow) == 0);
    assert((regex_constants::match_not_bol & regex_constants::match_any) == 0);
    assert((regex_constants::match_not_bol & regex_constants::match_not_null) == 0);
    assert((regex_constants::match_not_bol & regex_constants::match_continuous) == 0);
    assert((regex_constants::match_not_bol & regex_constants::match_prev_avail) == 0);
    assert((regex_constants::match_not_bol & regex_constants::format_sed) == 0);
    assert((regex_constants::match_not_bol & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_not_bol & regex_constants::format_first_only) == 0);

    assert((regex_constants::match_not_eol & regex_constants::match_not_bow) == 0);
    assert((regex_constants::match_not_eol & regex_constants::match_not_eow) == 0);
    assert((regex_constants::match_not_eol & regex_constants::match_any) == 0);
    assert((regex_constants::match_not_eol & regex_constants::match_not_null) == 0);
    assert((regex_constants::match_not_eol & regex_constants::match_continuous) == 0);
    assert((regex_constants::match_not_eol & regex_constants::match_prev_avail) == 0);
    assert((regex_constants::match_not_eol & regex_constants::format_sed) == 0);
    assert((regex_constants::match_not_eol & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_not_eol & regex_constants::format_first_only) == 0);

    assert((regex_constants::match_not_bow & regex_constants::match_not_eow) == 0);
    assert((regex_constants::match_not_bow & regex_constants::match_any) == 0);
    assert((regex_constants::match_not_bow & regex_constants::match_not_null) == 0);
    assert((regex_constants::match_not_bow & regex_constants::match_continuous) == 0);
    assert((regex_constants::match_not_bow & regex_constants::match_prev_avail) == 0);
    assert((regex_constants::match_not_bow & regex_constants::format_sed) == 0);
    assert((regex_constants::match_not_bow & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_not_bow & regex_constants::format_first_only) == 0);

    assert((regex_constants::match_not_eow & regex_constants::match_any) == 0);
    assert((regex_constants::match_not_eow & regex_constants::match_not_null) == 0);
    assert((regex_constants::match_not_eow & regex_constants::match_continuous) == 0);
    assert((regex_constants::match_not_eow & regex_constants::match_prev_avail) == 0);
    assert((regex_constants::match_not_eow & regex_constants::format_sed) == 0);
    assert((regex_constants::match_not_eow & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_not_eow & regex_constants::format_first_only) == 0);

    assert((regex_constants::match_any & regex_constants::match_not_null) == 0);
    assert((regex_constants::match_any & regex_constants::match_continuous) == 0);
    assert((regex_constants::match_any & regex_constants::match_prev_avail) == 0);
    assert((regex_constants::match_any & regex_constants::format_sed) == 0);
    assert((regex_constants::match_any & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_any & regex_constants::format_first_only) == 0);

    assert((regex_constants::match_not_null & regex_constants::match_continuous) == 0);
    assert((regex_constants::match_not_null & regex_constants::match_prev_avail) == 0);
    assert((regex_constants::match_not_null & regex_constants::format_sed) == 0);
    assert((regex_constants::match_not_null & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_not_null & regex_constants::format_first_only) == 0);

    assert((regex_constants::match_continuous & regex_constants::match_prev_avail) == 0);
    assert((regex_constants::match_continuous & regex_constants::format_sed) == 0);
    assert((regex_constants::match_continuous & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_continuous & regex_constants::format_first_only) == 0);

    assert((regex_constants::match_prev_avail & regex_constants::format_sed) == 0);
    assert((regex_constants::match_prev_avail & regex_constants::format_no_copy) == 0);
    assert((regex_constants::match_prev_avail & regex_constants::format_first_only) == 0);

    assert((regex_constants::format_sed & regex_constants::format_no_copy) == 0);
    assert((regex_constants::format_sed & regex_constants::format_first_only) == 0);

    assert((regex_constants::format_no_copy & regex_constants::format_first_only) == 0);

    regex_constants::match_flag_type e1 = regex_constants::match_not_bol;
    regex_constants::match_flag_type e2 = regex_constants::match_not_eol;
    e1 = ~e1;
    e1 = e1 & e2;
    e1 = e1 | e2;
    e1 = e1 ^ e2;
    e1 &= e2;
    e1 |= e2;
    e1 ^= e2;

  return 0;
}
