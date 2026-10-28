#include <locale> // std::ctype_base

#include <libstud/regex/regex.hxx>

#undef NDEBUG
#include <cassert>

int main ()
{
  using namespace stud::regex;

  using std::ctype_base;

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
    if (details::ctype_base_blank != ctype_base::space)
      assert (!regex_match (s, m, regex ("A[[:blank:]]B")));
  }

  {
    cmatch m;
    regex re ("[[:w:]]");
    assert (regex_match ("A", m, re));
    assert (regex_match ("a", m, re));
    assert (regex_match ("1", m, re));
    assert (regex_match ("_", m, re));
    assert (!regex_match (" ", m, re));
    assert (!regex_match ("\n", m, re));
    assert (!regex_match ("\t", m, re));
    assert (!regex_match ("-", m, re));
    assert (!regex_match (",", m, re));
  }
}
