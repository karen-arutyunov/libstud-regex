#include <string>
#include <locale>  // std::ctype_base
#include <sstream>
#include <cstddef> // size_t

#include <libstud/regex/regex.hxx>
#include <libstud/regex/regex-io.hxx>

#undef NDEBUG
#include <cassert>

int main ()
{
  using namespace stud::regex;

  using std::ctype_base;
  using std::string;
  using std::size_t;

  // Test matching the space character with the space and blank character
  // classes.
  //
  {
    // While at it, test 2 regex_match() overloads.
    //
    smatch m;
    string s ("A B");
    assert (regex_match (s, m, regex ("A[[:space:]]B")));
    assert (regex_match (s,    regex ("A[[:blank:]]B")));
  }

  // Test matching the newline character with the space and blank character
  // classes.
  //
  {
    cmatch m;
    const char s[] = "A\nB";

    // While at it, test 2 regex_match() overloads.
    //
    assert (regex_match (s, m, regex ("A[[:space:]]B")));

    // Note that for GCC 4.9 '\n' is recognized as a 'blank' character (see
    // libstud/regex/details.hxx for details).
    //
    if (details::ctype_base_blank != ctype_base::space)
      assert (!regex_match (s, regex ("A[[:blank:]]B")));
  }

  // Test matching various characters with the word character class.
  //
  {
    regex re ("[[:w:]]");
    assert (regex_match ("A", re));
    assert (regex_match ("a", re));
    assert (regex_match ("1", re));
    assert (regex_match ("_", re));
    assert (!regex_match (" ", re));
    assert (!regex_match ("\n", re));
    assert (!regex_match ("\t", re));
    assert (!regex_match ("-", re));
    assert (!regex_match (",", re));
  }

  // Test regex_error class.
  //
  {
    try
    {
      regex r ("(");
      assert (false);
    }
    catch (const regex_error& e1)
    {
      regex_error e2 (e1);

      assert (e2.code () == e1.code ());
      assert (string (e2.what ()) == e1.what ());

      std::ostringstream o;
      o << e1;

      assert (o.str () == "the expression contained mismatched ( and )");
    }

    // Test that regex is capable of matching very long strings.
    //
    {
      size_t n (1024 * 1024 * 10);

      string s;
      s.reserve (n);

      const char cs[] = "abc";

      for (size_t i (0); i != n; ++i)
        s.push_back (cs[i % 3]);

      assert (regex_match (s, regex ("[a-c]+")));
    }
  }
}
