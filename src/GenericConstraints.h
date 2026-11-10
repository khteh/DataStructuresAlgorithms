#pragma once
#include <concepts>
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