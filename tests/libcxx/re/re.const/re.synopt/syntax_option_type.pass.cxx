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
// enum syntax_option_type  // bitmask type
// {
//     icase      = unspecified,
//     nosubs     = unspecified,
//     optimize   = unspecified,
//     collate    = unspecified,
//     ECMAScript = unspecified,
//     basic      = unspecified,
//     extended   = unspecified,
//     awk        = unspecified,
//     grep       = unspecified,
//     egrep      = unspecified,
//     multiline  = unspecified
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
    assert(regex_constants::icase != 0);
    assert(regex_constants::nosubs != 0);
    assert(regex_constants::optimize != 0);
    assert(regex_constants::collate != 0);
#if !defined LIBSTUD_REGEX_LIBCPP || defined LIBSTUD_REGEX_ABI_REGEX_CONSTANTS_NONZERO
    // https://llvm.org/PR35967
    assert(regex_constants::ECMAScript != 0);
#else
    assert(regex_constants::ECMAScript == 0);
#endif
    assert(regex_constants::basic != 0);
    assert(regex_constants::extended != 0);
    assert(regex_constants::awk != 0);
    assert(regex_constants::grep != 0);
    assert(regex_constants::egrep != 0);
    assert(regex_constants::multiline != 0);

    assert((regex_constants::icase & regex_constants::nosubs) == 0);
    assert((regex_constants::icase & regex_constants::optimize) == 0);
    assert((regex_constants::icase & regex_constants::collate) == 0);
    assert((regex_constants::icase & regex_constants::ECMAScript) == 0);
    assert((regex_constants::icase & regex_constants::basic) == 0);
    assert((regex_constants::icase & regex_constants::extended) == 0);
    assert((regex_constants::icase & regex_constants::awk) == 0);
    assert((regex_constants::icase & regex_constants::grep) == 0);
    assert((regex_constants::icase & regex_constants::egrep) == 0);
    assert((regex_constants::icase & regex_constants::multiline) == 0);

    assert((regex_constants::nosubs & regex_constants::optimize) == 0);
    assert((regex_constants::nosubs & regex_constants::collate) == 0);
    assert((regex_constants::nosubs & regex_constants::ECMAScript) == 0);
    assert((regex_constants::nosubs & regex_constants::basic) == 0);
    assert((regex_constants::nosubs & regex_constants::extended) == 0);
    assert((regex_constants::nosubs & regex_constants::awk) == 0);
    assert((regex_constants::nosubs & regex_constants::grep) == 0);
    assert((regex_constants::nosubs & regex_constants::egrep) == 0);
    assert((regex_constants::nosubs & regex_constants::multiline) == 0);

    assert((regex_constants::optimize & regex_constants::collate) == 0);
    assert((regex_constants::optimize & regex_constants::ECMAScript) == 0);
    assert((regex_constants::optimize & regex_constants::basic) == 0);
    assert((regex_constants::optimize & regex_constants::extended) == 0);
    assert((regex_constants::optimize & regex_constants::awk) == 0);
    assert((regex_constants::optimize & regex_constants::grep) == 0);
    assert((regex_constants::optimize & regex_constants::egrep) == 0);
    assert((regex_constants::optimize & regex_constants::multiline) == 0);

    assert((regex_constants::collate & regex_constants::ECMAScript) == 0);
    assert((regex_constants::collate & regex_constants::basic) == 0);
    assert((regex_constants::collate & regex_constants::extended) == 0);
    assert((regex_constants::collate & regex_constants::awk) == 0);
    assert((regex_constants::collate & regex_constants::grep) == 0);
    assert((regex_constants::collate & regex_constants::egrep) == 0);
    assert((regex_constants::collate & regex_constants::multiline) == 0);

    assert((regex_constants::ECMAScript & regex_constants::basic) == 0);
    assert((regex_constants::ECMAScript & regex_constants::extended) == 0);
    assert((regex_constants::ECMAScript & regex_constants::awk) == 0);
    assert((regex_constants::ECMAScript & regex_constants::grep) == 0);
    assert((regex_constants::ECMAScript & regex_constants::egrep) == 0);
    assert((regex_constants::ECMAScript & regex_constants::multiline) == 0);

    assert((regex_constants::basic & regex_constants::extended) == 0);
    assert((regex_constants::basic & regex_constants::awk) == 0);
    assert((regex_constants::basic & regex_constants::grep) == 0);
    assert((regex_constants::basic & regex_constants::egrep) == 0);
    assert((regex_constants::basic & regex_constants::multiline) == 0);

    assert((regex_constants::extended & regex_constants::awk) == 0);
    assert((regex_constants::extended & regex_constants::grep) == 0);
    assert((regex_constants::extended & regex_constants::egrep) == 0);
    assert((regex_constants::extended & regex_constants::multiline) == 0);

    assert((regex_constants::awk & regex_constants::grep) == 0);
    assert((regex_constants::awk & regex_constants::egrep) == 0);
    assert((regex_constants::awk & regex_constants::multiline) == 0);

    assert((regex_constants::grep & regex_constants::egrep) == 0);
    assert((regex_constants::grep & regex_constants::multiline) == 0);

    assert((regex_constants::egrep & regex_constants::multiline) == 0);

    assert((regex_constants::icase | regex_constants::nosubs) != 0);
    assert((regex_constants::icase ^ regex_constants::nosubs) != 0);

    regex_constants::syntax_option_type e1 = regex_constants::icase;
    regex_constants::syntax_option_type e2 = regex_constants::nosubs;
    e1 = ~e1;
    e1 = e1 & e2;
    e1 = e1 | e2;
    e1 = e1 ^ e2;
    e1 &= e2;
    e1 |= e2;
    e1 ^= e2;

  return 0;
}
