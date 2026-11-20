#pragma once
#include <climits> // CHAR_BIT
#include <concepts>
#include <cstdint>
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
/*
 * At least 64 bits: int64_t, uint64_t, long long, and int128_t / uint128_t where the compiler has them. Not int, and not a 32-bit long (MSVC).
 * Built on integral_type, not integral, so that the 128-bit types count in strict -std=c++XX too, and sized with sizeof rather than
 * numeric_limits<T>::digits, which strict modes don't define for __int128.
 */
template <typename T>
concept wide_integral_type = integral_type<T> && sizeof(T) * CHAR_BIT >= 64;
template <typename T>
concept wide_signed_integral_type = signed_integral_type<T> && sizeof(T) * CHAR_BIT >= 64;
// The widest integers the compiler offers: 128 bits if it has int128_t, otherwise 64
#ifdef __SIZEOF_INT128__
using widest_signed_int = int128_t;
using widest_unsigned_int = uint128_t;
#else
using widest_signed_int = int64_t;
using widest_unsigned_int = uint64_t;
#endif
inline constexpr size_t widest_integral_bits = sizeof(widest_signed_int) * CHAR_BIT;
// The widest integer the compiler offers, and nothing narrower: a concept checks a type, while widest_signed_int / widest_unsigned_int pick one
template <typename T>
concept widest_integral_type = integral_type<T> && sizeof(T) * CHAR_BIT >= widest_integral_bits;
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
