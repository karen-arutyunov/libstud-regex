//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <regex>

// class regex_iterator<BidirectionalIterator, charT, traits>

// regex_iterator operator++(int);

#include <libstud/regex.hxx>

#include <iterator>

#include "test_macros.hxx"

#undef NDEBUG
#include <cassert>

using namespace stud::regex;

using std::begin;
using std::end;

void validate_prefixes(const regex& empty_matching_pattern) {
  const char source[] = "abc";

  cregex_iterator i(source, source + 3, empty_matching_pattern);
  assert(!i->prefix().matched);
  assert(i->prefix().length() == 0);
  assert(i->prefix().first == source);
  assert(i->prefix().second == source);

  ++i;
  assert(i->prefix().matched);
  assert(i->prefix().length() == 1);
  assert(i->prefix().first == source);
  assert(i->prefix().second == source + 1);
  assert(i->prefix().str() == "a");

  ++i;
  assert(i->prefix().matched);
  assert(i->prefix().length() == 1);
  assert(i->prefix().first == source + 1);
  assert(i->prefix().second == source + 2);
  assert(i->prefix().str() == "b");

  ++i;
  assert(i->prefix().matched);
  assert(i->prefix().length() == 1);
  assert(i->prefix().first == source + 2);
  assert(i->prefix().second == source + 3);
  assert(i->prefix().str() == "c");

  ++i;
  assert(i == cregex_iterator());
}

void test_prefix_adjustment() {
  // Check that we correctly adjust the match prefix when dealing with zero-length matches -- this is explicitly
  // required by the Standard ([re.regiter.incr]: "In all cases in which the call to `regex_search` returns true,
  // `match.prefix().first` shall be equal to the previous value of `match[0].second`"). For a pattern that matches
  // empty sequences, there is an implicit zero-length match between every character in a string -- make sure the
  // prefix of each of these matches (except the first one) is the preceding character.

  // An empty pattern produces zero-length matches.
  validate_prefixes(regex(""));
  // Any character repeated zero or more times can produce zero-length matches.
  validate_prefixes(regex("X*"));
  validate_prefixes(regex("X{0,3}"));
}

int main(int, char**) {
  {
    regex phone_numbers("\\d{3}-\\d{4}");
    const char phone_book[] = "555-1234, 555-2345, 555-3456";
    cregex_iterator i(begin(phone_book), end(phone_book), phone_numbers);
    cregex_iterator i2 = i;
    assert(i != cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i).size() == 1);
    assert((*i).position() == 0);
    assert((*i).str() == "555-1234");
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
    i++;
    assert(i != cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i).size() == 1);
    assert((*i).position() == 10);
    assert((*i).str() == "555-2345");
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
    i++;
    assert(i != cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i).size() == 1);
    assert((*i).position() == 20);
    assert((*i).str() == "555-3456");
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
    i++;
    assert(i == cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
  }
  {
    regex phone_numbers("\\d{3}-\\d{4}");
    const char phone_book[] = "555-1234, 555-2345, 555-3456";
    cregex_iterator i(begin(phone_book), end(phone_book), phone_numbers);
    cregex_iterator i2 = i;
    assert(i != cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i).size() == 1);
    assert((*i).position() == 0);
    assert((*i).str() == "555-1234");
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
    ++i;
    assert(i != cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i).size() == 1);
    assert((*i).position() == 10);
    assert((*i).str() == "555-2345");
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
    ++i;
    assert(i != cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i).size() == 1);
    assert((*i).position() == 20);
    assert((*i).str() == "555-3456");
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
    ++i;
    assert(i == cregex_iterator());
    assert(i2 != cregex_iterator());
    assert((*i2).size() == 1);
    assert((*i2).position() == 0);
    assert((*i2).str() == "555-1234");
  }
  { // https://llvm.org/PR33681
    regex rex(".*");
    const char foo[] = "foo";
    //  The -1 is because we don't want the implicit null from the array.
    cregex_iterator i(begin(foo), end(foo) - 1, rex);
    cregex_iterator e;
    assert(i != e);
    assert((*i).size() == 1);
    assert((*i).str() == "foo");

    ++i;
    assert(i != e);
    assert((*i).size() == 1);
    assert((*i).str() == "");

    ++i;
    assert(i == e);
  }

  test_prefix_adjustment();

  return 0;
}
