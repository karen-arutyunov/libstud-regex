#include <libstud/regex.hxx>

#include <string>
#include <locale> // std::ctype_base

#undef NDEBUG
#include <cassert>

int main ()
{
  using namespace stud::regex;

  {
    cmatch m;
    const char s[] = "A B";
    assert (regex_match (s, m, regex ("A[[:space:]]B")));
    assert (regex_match (s, m, regex ("A[[:blank:]]B")));
  }

  {
    cmatch m;
    const char s[] = "A\nB";

    assert (regex_match (s, m, regex ("A[[:space:]]B")));

    // Note for GCC 4.9 '\n' is recognized as a 'blank' character (see
    // libstud/regex/details.hxx for details).
    //
    if (details::ctype_base_blank != std::ctype_base::space)
      assert (!regex_match (s, m, regex ("A[[:blank:]]B")));
  }
}
