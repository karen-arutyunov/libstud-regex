#include <libstud/regex.hxx>

#include <locale> // std::ctype_base

#if 0
#include <bitset>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#endif

#undef NDEBUG
#include <cassert>

int main ()
{
  using namespace stud::regex;

  using std::ctype_base;

#if 0
  using std::cerr;
  using std::endl;
  using std::pair;
  using std::bitset;
  using std::vector;
  using std::string;
  using std::ctype;
#endif

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

#if 0
  {
    cerr << "sizeof (regex_traits<char>::char_class_type) "
         << sizeof (regex_traits<char>::char_class_type) << endl
         << "sizeof (regex_traits<wchar_t>::char_class_type) "
         << sizeof (regex_traits<wchar_t>::char_class_type) << endl
         << "sizeof (std::ctype_base::mask) "
         << sizeof (ctype_base::mask) << endl;

    using named_flag = pair<string, ctype_base::mask>;

    vector<named_flag> flags ({
        named_flag ("space ", ctype_base::space),
        named_flag ("print ", ctype_base::print),
        named_flag ("cntrl ", ctype_base::cntrl),
        named_flag ("upper ", ctype_base::upper),
        named_flag ("lower ", ctype_base::lower),
        named_flag ("alpha ", ctype_base::alpha),
        named_flag ("digit ", ctype_base::digit),
        named_flag ("punct ", ctype_base::punct),
        named_flag ("xdigit", ctype_base::xdigit),
        named_flag ("blank ", stud::regex::details::ctype_base_blank),
        named_flag ("w(ord)", regex_traits<char>::__regex_word)});

    for (const named_flag& f: flags)
      cerr << f.first << ": "
           << bitset<sizeof (ctype_base::mask) * 8> (f.second) << endl;

    {
      regex_traits<char> t;

      cerr << "' ' is a:" << endl;
      for (const named_flag& f: flags)
        cerr << "  " << f.first << ": " << t.isctype (' ', f.second) << endl;
    }

    {
      regex_traits<wchar_t> t;

      cerr << "L' ' is a:" << endl;
      for (const named_flag& f: flags)
        cerr << "  " << f.first << ": " << t.isctype (L' ', f.second) << endl;
    }
  }
#endif
}
