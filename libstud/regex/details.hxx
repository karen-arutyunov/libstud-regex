#pragma once

#include <iterator>
#include <type_traits>

#include <libstud/regex/config.hxx>

namespace stud
{
  namespace details
  {
    namespace regex
    {
      template <class...>
      using __void_t = void;

      template <bool _Bp, class _Tp = void>
      using __enable_if_t = typename std::enable_if<_Bp, _Tp>::type;

      template <class _Tp, class _Up, class = void>
      constexpr bool __is_swappable_with_v = false;

      template <class _Tp>
      constexpr bool __is_swappable_v = __is_swappable_with_v<_Tp&, _Tp&>;

      template <class _Tp, class _Up, bool = __is_swappable_with_v<_Tp, _Up> >
      constexpr bool __is_nothrow_swappable_with_v = false;

      template <class _Tp>
      constexpr bool __is_nothrow_swappable_v = __is_nothrow_swappable_with_v<_Tp&, _Tp&>;

      template <class _Default, class _Void, template <class...> class _Op, class... _Args>
      struct __detector {
        using type = _Default;
      };

      template <class _Default, template <class...> class _Op, class... _Args>
      struct __detector<_Default, __void_t<_Op<_Args...> >, _Op, _Args...> {
        using type = _Op<_Args...>;
      };

      template <class _Default, template <class...> class _Op, class... _Args>
      using __detected_or_t = typename __detector<_Default, void, _Op, _Args...>::type;

      template <class _Tp>
      using __iterator_category = typename _Tp::iterator_category;

      struct __nat {
        __nat()                        = delete;
        __nat(const __nat&)            = delete;
        __nat& operator=(const __nat&) = delete;
        ~__nat()                       = delete;
      };

      template <class _Tp, class _Up>
      using __has_iterator_category_convertible_to =
        std::is_convertible<__detected_or_t<__nat,
                                            __iterator_category,
                                            std::iterator_traits<_Tp> >, _Up>;

      template <class _Tp>
      using __has_exactly_input_iterator_category =
        std::integral_constant<
          bool,
        __has_iterator_category_convertible_to<_Tp, std::input_iterator_tag>::value &&
          !__has_iterator_category_convertible_to<_Tp, std::forward_iterator_tag>::value>;

      template <class _Tp>
      using __has_forward_iterator_category =
        __has_iterator_category_convertible_to<_Tp, std::forward_iterator_tag>;

      typedef std::integral_constant<bool, true> true_type;
      typedef std::integral_constant<bool, false> false_type;

      template <class...>
      using __expand_to_true = true_type;

      template <class... _Pred>
      __expand_to_true<__enable_if_t<_Pred::value>...> __and_helper(int);

      template <class...>
      false_type __and_helper(...);

      template <class... _Pred>
      using _And = decltype(__and_helper<_Pred...>(0));

      template <bool>
      struct _OrImpl;

      template <>
      struct _OrImpl<true> {
        template <class _Res, class _First, class... _Rest>
        using _Result =
          typename _OrImpl<!bool(_First::value) && sizeof...(_Rest) != 0>::template _Result<_First, _Rest...>;
      };

      template <>
      struct _OrImpl<false> {
        template <class _Res, class...>
        using _Result = _Res;
      };

      template <class... _Args>
      using _Or = typename _OrImpl<sizeof...(_Args) != 0>::template _Result<false_type, _Args...>;

      template <class _Iter>
      using __iterator_reference = typename std::iterator_traits<_Iter>::reference;

      template <class _Tp>
      using __libcpp_remove_reference_t = std::remove_reference<_Tp>;

      template <class _Tp>
      using __make_const_lvalue_ref = const __libcpp_remove_reference_t<_Tp>&;

      template <class _Iter>
      class LIBSTUD_REGEX_WARN_UNUSED __wrap_iter {
        public:
        typedef typename std::iterator_traits<_Iter>::value_type value_type;
        typedef typename std::iterator_traits<_Iter>::difference_type difference_type;
        typedef typename std::iterator_traits<_Iter>::pointer pointer;
        typedef typename std::iterator_traits<_Iter>::reference reference;
        typedef typename std::iterator_traits<_Iter>::iterator_category iterator_category;
#if LIBSTUD_REGEX_STD_VER >= 20
        typedef contiguous_iterator_tag iterator_concept;
#endif

        private:
        _Iter __i_;

        public:
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter() _NOEXCEPT : __i_() {}
        template <class _OtherIter,
                  __enable_if_t<
                    _And<std::is_convertible<const _OtherIter&, _Iter>,
                         _Or<std::is_same<reference, __iterator_reference<_OtherIter> >,
                             std::is_same<reference, __make_const_lvalue_ref<__iterator_reference<_OtherIter> > > > >::value,
                    int> = 0>
          LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter(const __wrap_iter<_OtherIter>& __u) _NOEXCEPT
          : __i_(__u.__i_) {}
        [[__nodiscard__]] LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 reference operator*() const _NOEXCEPT {
          return *__i_;
        }
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 pointer operator->() const _NOEXCEPT {
          return std::__to_address(__i_);
        }
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator++() _NOEXCEPT {
          ++__i_;
          return *this;
        }
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter operator++(int) _NOEXCEPT {
          __wrap_iter __tmp(*this);
          ++(*this);
          return __tmp;
        }

        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator--() _NOEXCEPT {
          --__i_;
          return *this;
        }
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter operator--(int) _NOEXCEPT {
          __wrap_iter __tmp(*this);
          --(*this);
          return __tmp;
        }
        [[__nodiscard__]] LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter
          operator+(difference_type __n) const _NOEXCEPT {
          __wrap_iter __w(*this);
          __w += __n;
          return __w;
        }
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator+=(difference_type __n) _NOEXCEPT {
          __i_ += __n;
          return *this;
        }
        [[__nodiscard__]] LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter
          operator-(difference_type __n) const _NOEXCEPT {
          return *this + (-__n);
        }
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter& operator-=(difference_type __n) _NOEXCEPT {
          *this += -__n;
          return *this;
        }
        [[__nodiscard__]] LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 reference
          operator[](difference_type __n) const _NOEXCEPT {
          return __i_[__n];
        }

        private:
        LIBSTUD_REGEX_HIDE_FROM_ABI LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 explicit __wrap_iter(_Iter __x) _NOEXCEPT : __i_(__x) {}

        template <class _Up>
          friend class __wrap_iter;
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

#if LIBSTUD_REGEX_STD_VER <= 17
        LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator==(const __wrap_iter& __x, const __wrap_iter& __y) _NOEXCEPT {
          return __x.__i_ == __y.__i_;
        }

        template <class _Iter2>
          LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator==(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT {
          return __x.__i_ == __y.__i_;
        }

        LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator<(const __wrap_iter& __x, const __wrap_iter& __y) _NOEXCEPT {
          return __x.__i_ < __y.__i_;
        }

        template <class _Iter2>
          LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator<(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT {
          return __x.__i_ < __y.__i_;
        }

        LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator!=(const __wrap_iter& __x, const __wrap_iter& __y) _NOEXCEPT {
          return !(__x == __y);
        }

        template <class _Iter2>
          LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator!=(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT {
          return !(__x == __y);
        }

        LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator>(const __wrap_iter& __x, const __wrap_iter& __y) _NOEXCEPT {
          return __y < __x;
        }

        template <class _Iter2>
          LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator>(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT {
          return __y < __x;
        }

        LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator>=(const __wrap_iter& __x, const __wrap_iter& __y) _NOEXCEPT {
          return !(__x < __y);
        }

        template <class _Iter2>
          LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator>=(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT {
          return !(__x < __y);
        }

        LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator<=(const __wrap_iter& __x, const __wrap_iter& __y) _NOEXCEPT {
          return !(__y < __x);
        }

        template <class _Iter2>
          LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR bool
          operator<=(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT {
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
          LIBSTUD_REGEX_HIDE_FROM_ABI friend constexpr strong_ordering
          operator<=>(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) noexcept {
          if constexpr (three_way_comparable_with<_Iter, _Iter2, strong_ordering>) {
              return __x.__i_ <=> __y.__i_;
            } else {
            if (__x.__i_ < __y.__i_)
              return strong_ordering::less;

            if (__x.__i_ == __y.__i_)
              return strong_ordering::equal;

            return strong_ordering::greater;
          }
        }
#endif // LIBSTUD_REGEX_STD_VER >= 20

#ifndef LIBSTUD_REGEX_CXX03_LANG
        template <class _Iter2>
          [[__nodiscard__]] LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 auto
          operator-(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT->decltype(__x.__i_ - __y.__i_)
#else
          template <class _Iter2>
          [[__nodiscard__]] LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14
          typename __wrap_iter::difference_type operator-(const __wrap_iter& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT
#endif // C++03
        {
          return __x.__i_ - __y.__i_;
        }

        [[__nodiscard__]] LIBSTUD_REGEX_HIDE_FROM_ABI friend LIBSTUD_REGEX_CONSTEXPR_SINCE_CXX14 __wrap_iter
          operator+(typename __wrap_iter::difference_type __n, __wrap_iter __x) _NOEXCEPT {
          __x += __n;
          return __x;
        }
      };
    }
  }
}
