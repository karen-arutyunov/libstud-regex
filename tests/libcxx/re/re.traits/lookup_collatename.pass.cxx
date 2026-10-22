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
//   string_type
//   lookup_collatename(ForwardIterator first, ForwardIterator last) const;

#include <libstud/regex/regex.hxx>

#include <string>
#include <iterator>

#include "test_macros.hxx"
#include "test_iterators.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::basic_string;
using std::string;
using std::wstring;

template <class char_type>
void
test(const char_type* A, const basic_string<char_type>& expected)
{
    regex_traits<char_type> t;
    typedef forward_iterator<const char_type*> F;
    assert(t.lookup_collatename(F(A), F(A + t.length(A))) == expected);
}

int main(int, char**)
{
    test("NUL", string("\x00", 1));
    test("alert", string("\x07"));
    test("backspace", string("\x08"));
    test("tab", string("\x09"));
    test("carriage-return", string("\x0D"));
    test("newline", string("\x0A"));
    test("vertical-tab", string("\x0B"));
    test("form-feed", string("\x0C"));
    test("space", string(" "));
    test("exclamation-mark", string("!"));
    test("quotation-mark", string("\""));
    test("number-sign", string("#"));
    test("dollar-sign", string("$"));
    test("percent-sign", string("%"));
    test("ampersand", string("&"));
    test("apostrophe", string("\'"));
    test("left-parenthesis", string("("));
    test("right-parenthesis", string(")"));
    test("asterisk", string("*"));
    test("plus-sign", string("+"));
    test("comma", string(","));
    test("hyphen-minus", string("-"));
    test("hyphen", string("-"));
    test("full-stop", string("."));
    test("period", string("."));
    test("slash", string("/"));
    test("solidus", string("/"));
    test("zero", string("0"));
    test("one", string("1"));
    test("two", string("2"));
    test("three", string("3"));
    test("four", string("4"));
    test("five", string("5"));
    test("six", string("6"));
    test("seven", string("7"));
    test("eight", string("8"));
    test("nine", string("9"));
    test("colon", string(":"));
    test("semicolon", string(";"));
    test("less-than-sign", string("<"));
    test("equals-sign", string("="));
    test("greater-than-sign", string(">"));
    test("question-mark", string("?"));
    test("commercial-at", string("@"));
    for (char c = 'A'; c <= 'Z'; ++c)
    {
        const char a[2] = {c};
        test(a, string(a));
    }
    test("left-square-bracket", string("["));
    test("backslash", string("\\"));
    test("reverse-solidus", string("\\"));
    test("right-square-bracket", string("]"));
    test("circumflex-accent", string("^"));
    test("circumflex", string("^"));
    test("low-line", string("_"));
    test("underscore", string("_"));
    test("grave-accent", string("`"));
    for (char c = 'a'; c <= 'z'; ++c)
    {
        const char a[2] = {c};
        test(a, string(a));
    }
    test("left-brace", string("{"));
    test("left-curly-bracket", string("{"));
    test("vertical-line", string("|"));
    test("right-brace", string("}"));
    test("right-curly-bracket", string("}"));
    test("tilde", string("~"));

    test("tild", string(""));
    test("ch", string(""));

#ifndef TEST_HAS_NO_WIDE_CHARACTERS
    test(L"NUL", wstring(L"\x00", 1));
    test(L"alert", wstring(L"\x07"));
    test(L"backspace", wstring(L"\x08"));
    test(L"tab", wstring(L"\x09"));
    test(L"carriage-return", wstring(L"\x0D"));
    test(L"newline", wstring(L"\x0A"));
    test(L"vertical-tab", wstring(L"\x0B"));
    test(L"form-feed", wstring(L"\x0C"));
    test(L"space", wstring(L" "));
    test(L"exclamation-mark", wstring(L"!"));
    test(L"quotation-mark", wstring(L"\""));
    test(L"number-sign", wstring(L"#"));
    test(L"dollar-sign", wstring(L"$"));
    test(L"percent-sign", wstring(L"%"));
    test(L"ampersand", wstring(L"&"));
    test(L"apostrophe", wstring(L"\'"));
    test(L"left-parenthesis", wstring(L"("));
    test(L"right-parenthesis", wstring(L")"));
    test(L"asterisk", wstring(L"*"));
    test(L"plus-sign", wstring(L"+"));
    test(L"comma", wstring(L","));
    test(L"hyphen-minus", wstring(L"-"));
    test(L"hyphen", wstring(L"-"));
    test(L"full-stop", wstring(L"."));
    test(L"period", wstring(L"."));
    test(L"slash", wstring(L"/"));
    test(L"solidus", wstring(L"/"));
    test(L"zero", wstring(L"0"));
    test(L"one", wstring(L"1"));
    test(L"two", wstring(L"2"));
    test(L"three", wstring(L"3"));
    test(L"four", wstring(L"4"));
    test(L"five", wstring(L"5"));
    test(L"six", wstring(L"6"));
    test(L"seven", wstring(L"7"));
    test(L"eight", wstring(L"8"));
    test(L"nine", wstring(L"9"));
    test(L"colon", wstring(L":"));
    test(L"semicolon", wstring(L";"));
    test(L"less-than-sign", wstring(L"<"));
    test(L"equals-sign", wstring(L"="));
    test(L"greater-than-sign", wstring(L">"));
    test(L"question-mark", wstring(L"?"));
    test(L"commercial-at", wstring(L"@"));
    for (wchar_t c = L'A'; c <= L'Z'; ++c)
    {
        const wchar_t a[2] = {c};
        test(a, wstring(a));
    }
    test(L"left-square-bracket", wstring(L"["));
    test(L"backslash", wstring(L"\\"));
    test(L"reverse-solidus", wstring(L"\\"));
    test(L"right-square-bracket", wstring(L"]"));
    test(L"circumflex-accent", wstring(L"^"));
    test(L"circumflex", wstring(L"^"));
    test(L"low-line", wstring(L"_"));
    test(L"underscore", wstring(L"_"));
    test(L"grave-accent", wstring(L"`"));
    for (wchar_t c = L'a'; c <= L'z'; ++c)
    {
        const wchar_t a[2] = {c};
        test(a, wstring(a));
    }
    test(L"left-brace", wstring(L"{"));
    test(L"left-curly-bracket", wstring(L"{"));
    test(L"vertical-line", wstring(L"|"));
    test(L"right-brace", wstring(L"}"));
    test(L"right-curly-bracket", wstring(L"}"));
    test(L"tilde", wstring(L"~"));

    test(L"tild", wstring(L""));
    test(L"ch", wstring(L""));
#endif // TEST_HAS_NO_WIDE_CHARACTERS

  return 0;
}
