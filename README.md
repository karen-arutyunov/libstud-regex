# libstud-regex - `std::regex`-like library with extensions

This library is a fork of the [`libc++`][libc++] implementation of the regular
expressions library with a few extensions.

The primary goal of this library is to provide a high-quality C++14-conforming
`std::regex` implementation compatible with all the major compilers and
standard libraries. In particular, the library is supposed to stay free from
all the existing and future restrictions on the user-defined character
types. It is also supposed to eliminate the need to write and maintain the
various hacks required to instantiate `std::basic_regex` template with a
nontrivial character type for different standard library implementations.

The library additionally provides:

- Non-standard replacement functions, which extend the standard `ECMA-262`
  substitution escape sequences with a subset of `Perl` sequences:

  `\\`, `\n`, `\u`, `\l`, `\U`, `\L`, `\E`, `\1`, ..., `\9`

- `line_regex` - the `basic_regex<line_char>` specialization intended for
  matching text line sequences (in a sense a 2D regex).

Supported compilers are GCC >= 4.9, Clang >= 3.7, and MSVC >= 14.3.

[libc++]: https://github.com/llvm/llvm-project/tree/main/libcxx
