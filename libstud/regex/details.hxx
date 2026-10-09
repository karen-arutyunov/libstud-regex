#pragma once

#include <locale>      // ctype_base
#include <memory>      // pointer_traits
#include <utility>     // declval
#include <cstdint>     // uint16_t
#include <iterator>
#include <type_traits>

#if LIBSTUD_REGEX_STD_VER >= 20
#  include <version>
#endif

#ifdef __cpp_lib_three_way_comparison
#  include <compare>
#endif

#include <libstud/regex/config.hxx>

namespace stud { namespace details { namespace regex {

// libcxx/include/__type_traits/void_t.h
//
template <class...>
using __void_t LIBSTUD_REGEX_NODEBUG = void;

// libcxx/include/__type_traits/enable_if.h
//
template <bool _Bp, class _Tp = void>
using __enable_if_t LIBSTUD_REGEX_NODEBUG = typename std::enable_if<_Bp, _Tp>::type;

// libcxx/include/__type_traits/is_swappable.h
//
template <class _Tp, class _Up, class = void>
constexpr bool __is_swappable_with_v = false;

template <class _Tp>
constexpr bool __is_swappable_v = __is_swappable_with_v<_Tp&, _Tp&>;

template <class _Tp, class _Up, bool = __is_swappable_with_v<_Tp, _Up> >
constexpr bool __is_nothrow_swappable_with_v = false;

template <class _Tp>
constexpr bool __is_nothrow_swappable_v = __is_nothrow_swappable_with_v<_Tp&, _Tp&>;

// libcxx/include/__type_traits/detected_or.h
//
template <class _Default, class _Void, template <class...> class _Op, class... _Args>
struct __detector {
  using type LIBSTUD_REGEX_NODEBUG = _Default;
};

template <class _Default, template <class...> class _Op, class... _Args>
struct __detector<_Default, __void_t<_Op<_Args...> >, _Op, _Args...> {
  using type LIBSTUD_REGEX_NODEBUG = _Op<_Args...>;
};

template <class _Default, template <class...> class _Op, class... _Args>
using __detected_or_t LIBSTUD_REGEX_NODEBUG = typename __detector<_Default, void, _Op, _Args...>::type;

// libcxx/include/__type_traits/integral_constant.h
//
typedef std::integral_constant<bool, true> true_type;
typedef std::integral_constant<bool, false> false_type;

// libcxx/include/__type_traits/conjunction.h
//
template <class...>
using __expand_to_true LIBSTUD_REGEX_NODEBUG = true_type;

template <class... _Pred>
__expand_to_true<__enable_if_t<_Pred::value>...> __and_helper(int);

template <class...>
false_type __and_helper(...);

template <class... _Pred>
using _And LIBSTUD_REGEX_NODEBUG = decltype(__and_helper<_Pred...>(0));

// libcxx/include/__type_traits/disjunction.h
//
template <bool>
struct _OrImpl;

template <>
struct _OrImpl<true> {
  template <class _Res, class _First, class... _Rest>
  using _Result LIBSTUD_REGEX_NODEBUG =
    typename _OrImpl<!bool(_First::value) && sizeof...(_Rest) != 0>::template _Result<_First, _Rest...>;
};

template <>
struct _OrImpl<false> {
  template <class _Res, class...>
  using _Result LIBSTUD_REGEX_NODEBUG = _Res;
};

template <class... _Args>
using _Or LIBSTUD_REGEX_NODEBUG = typename _OrImpl<sizeof...(_Args) != 0>::template _Result<false_type, _Args...>;

// libcxx/include/__type_traits/remove_reference.h
//
template <class _Tp>
using __libcpp_remove_reference_t = typename std::remove_reference<_Tp>::type;

// libcxx/include/__type_traits/make_const_lvalue_ref.h
//
template <class _Tp>
using __make_const_lvalue_ref LIBSTUD_REGEX_NODEBUG = const __libcpp_remove_reference_t<_Tp>&;

// libcxx/include/__type_traits/decay.h
//
template <class _Tp>
using __decay_t LIBSTUD_REGEX_NODEBUG = typename std::decay<_Tp>::type;

// libcxx/include/__memory/pointer_traits.h
//
template <class _Tp>
LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR _Tp* __to_address(_Tp* __p) LIBSTUD_REGEX_NOEXCEPT {
  static_assert(!std::is_function<_Tp>::value, "_Tp is a function type");
  return __p;
}

template <class _Pointer, class = void>
constexpr bool __has_to_address_v = false;

template <class _Pointer>
constexpr bool
    __has_to_address_v<_Pointer,
                       decltype((void)std::pointer_traits<_Pointer>::to_address(std::declval<const _Pointer&>()))> = true;

template <class _Pointer, __enable_if_t<__has_to_address_v<_Pointer>, int> = 0>
LIBSTUD_REGEX_CONSTEXPR __decay_t<decltype(std::pointer_traits<_Pointer>::to_address(std::declval<const _Pointer&>()))>
__to_address(const _Pointer& __p) LIBSTUD_REGEX_NOEXCEPT {
  return std::pointer_traits<_Pointer>::to_address(__p);
}

// libcxx/include/__iterator/iterator_traits.h
//
template <class _Tp>
using __iterator_category LIBSTUD_REGEX_NODEBUG = typename _Tp::iterator_category;

// libcxx/include/__type_traits/nat.h
//
struct __nat {
#ifndef LIBSTUD_REGEX_CXX03_LANG
  __nat()                        = delete;
  __nat(const __nat&)            = delete;
  __nat& operator=(const __nat&) = delete;
  ~__nat()                       = delete;
#endif
};

template <class _Tp, class _Up>
using __has_iterator_category_convertible_to LIBSTUD_REGEX_NODEBUG =
  std::is_convertible<__detected_or_t<__nat, __iterator_category, std::iterator_traits<_Tp> >, _Up>;

template <class _Tp>
using __has_exactly_input_iterator_category LIBSTUD_REGEX_NODEBUG =
  std::integral_constant<bool,
                         __has_iterator_category_convertible_to<_Tp, std::input_iterator_tag>::value &&
                           !__has_iterator_category_convertible_to<_Tp, std::forward_iterator_tag>::value>;

template <class _Tp>
using __has_forward_iterator_category LIBSTUD_REGEX_NODEBUG =
  __has_iterator_category_convertible_to<_Tp, std::forward_iterator_tag>;

template <class _Iter>
using __iterator_reference LIBSTUD_REGEX_NODEBUG = typename std::iterator_traits<_Iter>::reference;

// libcxx/include/__iterator/wrap_iter.h
//
template <class _Iter>
class LIBSTUD_REGEX_WARN_UNUSED __wrap_iter {
public:
  typedef typename std::iterator_traits<_Iter>::value_type value_type;
  typedef typename std::iterator_traits<_Iter>::difference_type difference_type;
  typedef typename std::iterator_traits<_Iter>::pointer pointer;
  typedef typename std::iterator_traits<_Iter>::reference reference;
  typedef typename std::iterator_traits<_Iter>::iterator_category iterator_category;
#if LIBSTUD_REGEX_STD_VER >= 20
  typedef std::contiguous_iterator_tag iterator_concept;
#endif

private:
  _Iter __i_;

public:
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter() LIBSTUD_REGEX_NOEXCEPT : __i_() {}
  template <class _OtherIter,
            __enable_if_t<
              _And<std::is_convertible<const _OtherIter&, _Iter>,
                _Or<std::is_same<reference, __iterator_reference<_OtherIter> >,
                    std::is_same<reference, __make_const_lvalue_ref<__iterator_reference<_OtherIter> > > > >::value,
              int> = 0>
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter(const __wrap_iter<_OtherIter>& __u) LIBSTUD_REGEX_NOEXCEPT
      : __i_(__u.__i_) {}
  LIBSTUD_REGEX_NODISCARD LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 reference operator*() const LIBSTUD_REGEX_NOEXCEPT {
    return *__i_;
  }
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 pointer operator->() const LIBSTUD_REGEX_NOEXCEPT {
    return __to_address(__i_);
  }
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator++() LIBSTUD_REGEX_NOEXCEPT {
    ++__i_;
    return *this;
  }
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter operator++(int) LIBSTUD_REGEX_NOEXCEPT {
    __wrap_iter __tmp(*this);
    ++(*this);
    return __tmp;
  }

  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator--() LIBSTUD_REGEX_NOEXCEPT {
    --__i_;
    return *this;
  }
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter operator--(int) LIBSTUD_REGEX_NOEXCEPT {
    __wrap_iter __tmp(*this);
    --(*this);
    return __tmp;
  }
  LIBSTUD_REGEX_NODISCARD LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter
  operator+(difference_type __n) const LIBSTUD_REGEX_NOEXCEPT {
    __wrap_iter __w(*this);
    __w += __n;
    return __w;
  }
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator+=(difference_type __n) LIBSTUD_REGEX_NOEXCEPT {
    __i_ += __n;
    return *this;
  }
  LIBSTUD_REGEX_NODISCARD LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter
  operator-(difference_type __n) const LIBSTUD_REGEX_NOEXCEPT {
    return *this + (-__n);
  }
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator-=(difference_type __n) LIBSTUD_REGEX_NOEXCEPT {
    *this += -__n;
    return *this;
  }
  LIBSTUD_REGEX_NODISCARD LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 reference
  operator[](difference_type __n) const LIBSTUD_REGEX_NOEXCEPT {
    return __i_[__n];
  }

private:
  LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 explicit __wrap_iter(_Iter __x) LIBSTUD_REGEX_NOEXCEPT : __i_(__x) {}

  template <class _Up>
  friend class __wrap_iter;
#if 0
  template <class _CharT, class _Traits, class _Alloc>
  friend class basic_string;
  template <class _CharT, class _Traits>
  friend class basic_string_view;
  template <class _Tp, class _Alloc>
  friend class vector;
  template <class _Tp, size_t>
  friend class span;
  template <class _Tp, size_t _Size>
  friend struct array;
#endif

#ifndef __cpp_lib_three_way_comparison
  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator==(const __wrap_iter& __x, const __wrap_iter& __y) LIBSTUD_REGEX_NOEXCEPT {
    return __x.__i_ == __y.__i_;
  }

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator==(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT {
    return __x.__i_ == __y.__i_;
  }

  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator<(const __wrap_iter& __x, const __wrap_iter& __y) LIBSTUD_REGEX_NOEXCEPT {
    return __x.__i_ < __y.__i_;
  }

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator<(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT {
    return __x.__i_ < __y.__i_;
  }

  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator!=(const __wrap_iter& __x, const __wrap_iter& __y) LIBSTUD_REGEX_NOEXCEPT {
    return !(__x == __y);
  }

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator!=(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT {
    return !(__x == __y);
  }

  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator>(const __wrap_iter& __x, const __wrap_iter& __y) LIBSTUD_REGEX_NOEXCEPT {
    return __y < __x;
  }

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator>(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT {
    return __y < __x;
  }

  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator>=(const __wrap_iter& __x, const __wrap_iter& __y) LIBSTUD_REGEX_NOEXCEPT {
    return !(__x < __y);
  }

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator>=(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT {
    return !(__x < __y);
  }

  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator<=(const __wrap_iter& __x, const __wrap_iter& __y) LIBSTUD_REGEX_NOEXCEPT {
    return !(__y < __x);
  }

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
  operator<=(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT {
    return !(__y < __x);
  }

#else
  LIBSTUD_REGEX_HIDE_FROM_ABI friend bool operator==(const __wrap_iter&, const __wrap_iter&) = default;

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend constexpr bool
  operator==(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) noexcept {
    return __x.__i_ == __y.__i_;
  }

  template <class _Iter2>
  LIBSTUD_REGEX_HIDE_FROM_ABI friend constexpr std::strong_ordering
  operator<=>(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) noexcept {
    if constexpr (std::three_way_comparable_with<_Iter, _Iter2, std::strong_ordering>) {
      return __x.__i_ <=> __y.__i_;
    } else {
      if (__x.__i_ < __y.__i_)
        return std::strong_ordering::less;

      if (__x.__i_ == __y.__i_)
        return std::strong_ordering::equal;

      return std::strong_ordering::greater;
    }
  }
#endif // LIBSTUD_REGEX_STD_VER >= 20

#ifndef LIBSTUD_REGEX_CXX03_LANG
  template <class _Iter2>
  LIBSTUD_REGEX_NODISCARD LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 auto
  operator-(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT->decltype(__x.__i_ - __y.__i_)
#else
  template <class _Iter2>
  LIBSTUD_REGEX_NODISCARD LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14
  typename __wrap_iter::difference_type operator-(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) LIBSTUD_REGEX_NOEXCEPT
#endif // C++03
  {
    return __x.__i_ - __y.__i_;
  }

  LIBSTUD_REGEX_NODISCARD LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter
  operator+(typename __wrap_iter::difference_type __n, __wrap_iter __x) LIBSTUD_REGEX_NOEXCEPT {
    __x += __n;
    return __x;
  }
};

// Calculate the __regex_word flag by claiming the rightmost not taken bit in
// std::ctype_base::mask.
//
using __regex_word_type = std::make_unsigned_t<std::ctype_base::mask>;

constexpr __regex_word_type ctype_base_mask_all_flags (
  std::ctype_base::space  |
  std::ctype_base::print  |
  std::ctype_base::cntrl  |
  std::ctype_base::upper  |
  std::ctype_base::lower  |
  std::ctype_base::alpha  |
  std::ctype_base::digit  |
  std::ctype_base::punct  |
  std::ctype_base::xdigit |
  std::ctype_base::blank);

constexpr __regex_word_type __regex_word (
  ~ctype_base_mask_all_flags & (ctype_base_mask_all_flags + 1));

// Validate, for good measure.
//
static_assert (ctype_base_mask_all_flags != 0,
               "cannot assign value for regex_traits::__regex_word since no "
               "zero bits left in std::ctype_base::mask");

static_assert (
  __regex_word != std::ctype_base::space  &&
  __regex_word != std::ctype_base::print  &&
  __regex_word != std::ctype_base::cntrl  &&
  __regex_word != std::ctype_base::upper  &&
  __regex_word != std::ctype_base::lower  &&
  __regex_word != std::ctype_base::alpha  &&
  __regex_word != std::ctype_base::digit  &&
  __regex_word != std::ctype_base::punct  &&
  __regex_word != std::ctype_base::xdigit &&
  __regex_word != std::ctype_base::blank,
  "regex_traits::__regex_word clashes with std::ctype_base::* constants");

} } } // namespace stud { namespace details { namespace regex {
