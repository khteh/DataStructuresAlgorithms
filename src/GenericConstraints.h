#pragma once
#include <concepts>
#include <functional>
#include <type_traits>
using namespace std;
#ifdef __SIZEOF_INT128__
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
#endif
// int128_t / uint128_t are GCC/Clang extensions. std::integral accepts them only in gnu++ modes,
// so list them explicitly: these concepts then behave the same with -std=c++XX, -std=gnu++XX and IntelliSense.
template <typename T>
concept int128_type =
#ifdef __SIZEOF_INT128__
    same_as<remove_cv_t<T>, int128_t> || same_as<remove_cv_t<T>, uint128_t>;
#else
    false;
#endif
template <typename T>
concept integral_type = integral<T> || int128_type<T>;
template <typename T>
concept signed_integral_type = signed_integral<T>
#ifdef __SIZEOF_INT128__
                               || same_as<remove_cv_t<T>, int128_t>
#endif
    ;
template <typename T>
concept arithmetic_type = integral<T> || floating_point<T>;
template <typename T>
concept floating_point_type = floating_point<T>;
template <class T, class U>
concept Derived = is_base_of<U, T>::value;

// https://stackoverflow.com/questions/79634906/c-23-generic-constraints-of-specific-types
// A generic size concept:
template <typename T, size_t num_bits>
concept is_num_bits = is_integral_v<T> && ((sizeof(T) * 8) == num_bits);

// A size concept for 128 bit:
template <typename T>
concept is_128_bits = is_num_bits<T, 128>;

// You can add more sizes, e.g. 64 bits:
template <typename T>
concept is_64_bits = is_num_bits<T, 64>;

/*
 * A comparator that is a strict weak ordering of T: Compare(a, b) is true when a is strictly before / better than b.
 * strict_weak_order only checks that Compare can be called with two Ts and returns something usable as bool. The rest
 * (Compare(a, a) is false, Compare(a, b) and Compare(b, a) are never both true, ...) are semantic requirements no compiler can check.
 * So the standard comparators known not to be strict are rejected by name: they return true for Compare(a, a).
 * Callers that take other comparators should still check Compare(a, a) is false at runtime, as SparseTable does.
 */
template <typename Compare>
inline constexpr bool NonStrictComparator = false;
template <typename T>
inline constexpr bool NonStrictComparator<less_equal<T>> = true; // Including less_equal<> (T = void)
template <typename T>
inline constexpr bool NonStrictComparator<greater_equal<T>> = true;
template <>
inline constexpr bool NonStrictComparator<ranges::less_equal> = true;
template <>
inline constexpr bool NonStrictComparator<ranges::greater_equal> = true;
template <typename Compare, typename T>
concept StrictComparator = strict_weak_order<Compare, T const&, T const&> && !NonStrictComparator<remove_cvref_t<Compare>>;
