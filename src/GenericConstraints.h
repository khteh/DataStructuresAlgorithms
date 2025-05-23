#pragma once
#include <concepts>
#include <type_traits>
using namespace std;
template <typename T>
concept arithmetic_type = integral<T> || floating_point<T>;
template <typename T>
concept integral_type = integral<T>;
template <typename T>
concept signed_integral_type = signed_integral<T>;
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