#pragma once

#include <iosfwd>
#include <string>

#include <libstud/regex/export.hxx>

namespace stud_regex
{
  // Print a greeting for the specified name into the specified
  // stream. Throw std::invalid_argument if the name is empty.
  //
  LIBSTUD_REGEX_SYMEXPORT void
  say_hello (std::ostream&, const std::string& name);
}
