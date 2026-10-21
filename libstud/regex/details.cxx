#include <libstud/regex/details.hxx>

#if LIBSTUD_REGEX_DELEGATE_TO_STD_TRANSFORM_PRIMARY
#  include <regex>
#  include <string>
#  include <memory> // make_unique()
#endif

namespace stud { namespace regex { namespace details {

#if LIBSTUD_REGEX_DELEGATE_TO_STD_TRANSFORM_PRIMARY
using std::string;
using std::wstring;
using std::locale;
using std::make_unique;

// regex_traits_impl<char>
//
struct regex_traits_impl<char>::traits_wrapper
{
  std::regex_traits<char> traits;
};

regex_traits_impl<char>::regex_traits_impl ()
    : wrapper_ (make_unique<traits_wrapper> ())
{
}

regex_traits_impl<char>::~regex_traits_impl () = default;

regex_traits_impl<char>::
regex_traits_impl (const regex_traits_impl& x)
    : wrapper_ (make_unique<traits_wrapper> (*x.wrapper_))
{
}

regex_traits_impl<char>::regex_traits_impl (regex_traits_impl&&) = default;

regex_traits_impl<char>& regex_traits_impl<char>::
operator= (const regex_traits_impl& x)
{
  wrapper_ = make_unique<traits_wrapper> (*x.wrapper_);
  return *this;
}

regex_traits_impl<char>&
regex_traits_impl<char>::operator= (regex_traits_impl&&) = default;

void
regex_traits_impl<char>::imbue (const locale& l)
{
  wrapper_->traits.imbue (l);
}

string
regex_traits_impl<char>::transform_primary(const string& s) const
{
  return wrapper_->traits.transform_primary (s.begin (), s.end ());
}

// regex_traits_impl<wchar_t>
//
struct regex_traits_impl<wchar_t>::traits_wrapper
{
  std::regex_traits<wchar_t> traits;
};

regex_traits_impl<wchar_t>::regex_traits_impl ()
    : wrapper_ (make_unique<traits_wrapper> ())
{
}

regex_traits_impl<wchar_t>::~regex_traits_impl () = default;

regex_traits_impl<wchar_t>::
regex_traits_impl (const regex_traits_impl& x)
    : wrapper_ (make_unique<traits_wrapper> (*x.wrapper_))
{
}

regex_traits_impl<wchar_t>::regex_traits_impl (regex_traits_impl&&) = default;

regex_traits_impl<wchar_t>& regex_traits_impl<wchar_t>::
operator= (const regex_traits_impl& x)
{
  wrapper_ = make_unique<traits_wrapper> (*x.wrapper_);
  return *this;
}

regex_traits_impl<wchar_t>&
regex_traits_impl<wchar_t>::operator= (regex_traits_impl&&) = default;

void
regex_traits_impl<wchar_t>::imbue (const locale& l)
{
  wrapper_->traits.imbue (l);
}

wstring
regex_traits_impl<wchar_t>::transform_primary(const wstring& s) const
{
  return wrapper_->traits.transform_primary (s.begin (), s.end ());
}
#else
int dummy; // Suppress the 'no symbols' warning.
#endif
} } } // namespace stud { namespace regex { namespace details {
