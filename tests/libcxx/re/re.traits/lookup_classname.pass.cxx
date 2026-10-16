//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// template <class charT> struct regex_traits;

// template <class ForwardIterator>
//   char_class_type
//   lookup_classname(ForwardIterator first, ForwardIterator last,
//                    bool icase = false) const;

#include <libstud/regex.hxx>

#include <locale>

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::ctype_base;

template <class char_type>
void
test(const char_type* A,
     typename regex_traits<char_type>::char_class_type expected,
     bool icase = false)
{
    typedef typename regex_traits<char_type>::char_class_type char_class_type;
    regex_traits<char_type> t;
    typedef forward_iterator<const char_type*> F;
    char_class_type result = t.lookup_classname(F(A), F(A + t.length(A)), icase);
    assert(result == expected);
}

template <class char_type>
void
test_w(const char_type* A,
       typename regex_traits<char_type>::char_class_type expected,
        bool icase = false)
{
    typedef typename regex_traits<char_type>::char_class_type char_class_type;
    regex_traits<char_type> t;
    typedef forward_iterator<const char_type*> F;
    char_class_type result = t.lookup_classname(F(A), F(A + t.length(A)), icase);
    assert((result & expected) == expected);
    LIBCPP_ASSERT((expected | regex_traits<char_type>::__regex_word) == result);

    const bool matches_underscore = t.isctype('_', result);
    if (result != expected)
      assert(matches_underscore && "expected to match underscore");
    else
      assert(!matches_underscore && "should not match underscore");
}

int main(int, char**)
{
//  if __regex_word is not distinct from all the classes, bad things happen
//  See https://llvm.org/PR26476 for an example.
    LIBCPP_ASSERT((ctype_base::space  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::print  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::cntrl  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::upper  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::lower  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::alpha  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::digit  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::punct  & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((ctype_base::xdigit & regex_traits<char>::__regex_word) == 0);
    LIBCPP_ASSERT((details::ctype_base_blank  & regex_traits<char>::__regex_word) == 0);

    test("d", ctype_base::digit);
    test("D", ctype_base::digit);
    test("d", ctype_base::digit, true);
    test("D", ctype_base::digit, true);

    test_w("w", ctype_base::alnum
              | ctype_base::upper | ctype_base::lower);
    test_w("W", ctype_base::alnum
              | ctype_base::upper | ctype_base::lower);
    test_w("w", ctype_base::alnum
              | ctype_base::upper | ctype_base::lower, true);
    test_w("W", ctype_base::alnum
              | ctype_base::upper | ctype_base::lower, true);

    test("s", ctype_base::space);
    test("S", ctype_base::space);
    test("s", ctype_base::space, true);
    test("S", ctype_base::space, true);

    test("alnum", ctype_base::alnum);
    test("AlNum", ctype_base::alnum);
    test("alnum", ctype_base::alnum, true);
    test("AlNum", ctype_base::alnum, true);

    test("alpha", ctype_base::alpha);
    test("Alpha", ctype_base::alpha);
    test("alpha", ctype_base::alpha, true);
    test("Alpha", ctype_base::alpha, true);

    test("blank", details::ctype_base_blank);
    test("Blank", details::ctype_base_blank);
    test("blank", details::ctype_base_blank, true);
    test("Blank", details::ctype_base_blank, true);

    test("cntrl", ctype_base::cntrl);
    test("Cntrl", ctype_base::cntrl);
    test("cntrl", ctype_base::cntrl, true);
    test("Cntrl", ctype_base::cntrl, true);

    test("digit", ctype_base::digit);
    test("Digit", ctype_base::digit);
    test("digit", ctype_base::digit, true);
    test("Digit", ctype_base::digit, true);

    test("digit", ctype_base::digit);
    test("DIGIT", ctype_base::digit);
    test("digit", ctype_base::digit, true);
    test("Digit", ctype_base::digit, true);

    test("graph", ctype_base::graph);
    test("GRAPH", ctype_base::graph);
    test("graph", ctype_base::graph, true);
    test("Graph", ctype_base::graph, true);

    test("lower", ctype_base::lower);
    test("LOWER", ctype_base::lower);
    test("lower", ctype_base::lower | ctype_base::alpha, true);
    test("Lower", ctype_base::lower | ctype_base::alpha, true);

    test("print", ctype_base::print);
    test("PRINT", ctype_base::print);
    test("print", ctype_base::print, true);
    test("Print", ctype_base::print, true);

    test("punct", ctype_base::punct);
    test("PUNCT", ctype_base::punct);
    test("punct", ctype_base::punct, true);
    test("Punct", ctype_base::punct, true);

    test("space", ctype_base::space);
    test("SPACE", ctype_base::space);
    test("space", ctype_base::space, true);
    test("Space", ctype_base::space, true);

    test("upper", ctype_base::upper);
    test("UPPER", ctype_base::upper);
    test("upper", ctype_base::upper | ctype_base::alpha, true);
    test("Upper", ctype_base::upper | ctype_base::alpha, true);

    test("xdigit", ctype_base::xdigit);
    test("XDIGIT", ctype_base::xdigit);
    test("xdigit", ctype_base::xdigit, true);
    test("Xdigit", ctype_base::xdigit, true);

    test("dig", ctype_base::mask());
    test("", ctype_base::mask());
    test("digits", ctype_base::mask());

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test(L"d", ctype_base::digit);
    test(L"D", ctype_base::digit);
    test(L"d", ctype_base::digit, true);
    test(L"D", ctype_base::digit, true);

    test_w(L"w", ctype_base::alnum
                      | ctype_base::upper | ctype_base::lower);
    test_w(L"W", ctype_base::alnum
                      | ctype_base::upper | ctype_base::lower);
    test_w(L"w", ctype_base::alnum
                      | ctype_base::upper | ctype_base::lower, true);
    test_w(L"W", ctype_base::alnum
                      | ctype_base::upper | ctype_base::lower, true);

    test(L"s", ctype_base::space);
    test(L"S", ctype_base::space);
    test(L"s", ctype_base::space, true);
    test(L"S", ctype_base::space, true);

    test(L"alnum", ctype_base::alnum);
    test(L"AlNum", ctype_base::alnum);
    test(L"alnum", ctype_base::alnum, true);
    test(L"AlNum", ctype_base::alnum, true);

    test(L"alpha", ctype_base::alpha);
    test(L"Alpha", ctype_base::alpha);
    test(L"alpha", ctype_base::alpha, true);
    test(L"Alpha", ctype_base::alpha, true);

    test(L"blank", details::ctype_base_blank);
    test(L"Blank", details::ctype_base_blank);
    test(L"blank", details::ctype_base_blank, true);
    test(L"Blank", details::ctype_base_blank, true);

    test(L"cntrl", ctype_base::cntrl);
    test(L"Cntrl", ctype_base::cntrl);
    test(L"cntrl", ctype_base::cntrl, true);
    test(L"Cntrl", ctype_base::cntrl, true);

    test(L"digit", ctype_base::digit);
    test(L"Digit", ctype_base::digit);
    test(L"digit", ctype_base::digit, true);
    test(L"Digit", ctype_base::digit, true);

    test(L"digit", ctype_base::digit);
    test(L"DIGIT", ctype_base::digit);
    test(L"digit", ctype_base::digit, true);
    test(L"Digit", ctype_base::digit, true);

    test(L"graph", ctype_base::graph);
    test(L"GRAPH", ctype_base::graph);
    test(L"graph", ctype_base::graph, true);
    test(L"Graph", ctype_base::graph, true);

    test(L"lower", ctype_base::lower);
    test(L"LOWER", ctype_base::lower);
    test(L"lower", ctype_base::lower | ctype_base::alpha, true);
    test(L"Lower", ctype_base::lower | ctype_base::alpha, true);

    test(L"print", ctype_base::print);
    test(L"PRINT", ctype_base::print);
    test(L"print", ctype_base::print, true);
    test(L"Print", ctype_base::print, true);

    test(L"punct", ctype_base::punct);
    test(L"PUNCT", ctype_base::punct);
    test(L"punct", ctype_base::punct, true);
    test(L"Punct", ctype_base::punct, true);

    test(L"space", ctype_base::space);
    test(L"SPACE", ctype_base::space);
    test(L"space", ctype_base::space, true);
    test(L"Space", ctype_base::space, true);

    test(L"upper", ctype_base::upper);
    test(L"UPPER", ctype_base::upper);
    test(L"upper", ctype_base::upper | ctype_base::alpha, true);
    test(L"Upper", ctype_base::upper | ctype_base::alpha, true);

    test(L"xdigit", ctype_base::xdigit);
    test(L"XDIGIT", ctype_base::xdigit);
    test(L"xdigit", ctype_base::xdigit, true);
    test(L"Xdigit", ctype_base::xdigit, true);

    test(L"dig", ctype_base::mask());
    test(L"", ctype_base::mask());
    test(L"digits", ctype_base::mask());
#endif

  return 0;
}
