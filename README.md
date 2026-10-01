# libstud-regex - `std::regex` library for C++14.

Fork of the [`libc++`][libc++] implementation of the regular expressions
library.

The goal of this library is to provide a fairly high-quality C++14-conforming
`std::regex` implementation, buildable by a wide version range of the major
compilers against the major standard library implementations. The library is
supposed to stay free from all the upcoming restrictions on the user-defined
character types. It is also supposed to eliminate the need to write and
maintain the various hacks required to instantiate `std::basic_regex` template
with a nontrivial character type for different standard library
implementations.

Supported compilers are GCC >= 4.9, Clang >= 3.7, and MSVC >= 14.3.

Note that this is a fork of the commit
6b4cd9965e354e4411cde79cc0ebcd522ce26b1f (13/10/2026).

[libc++]: https://github.com/llvm/llvm-project/tree/main/libcxx
