#pragma once
#include <concepts>
using namespace std;
template <typename T>
concept arithmetic_type = integral<T> || floating_point<T>;
template <typename T>
concept integral_type = integral<T>;
template <typename T>
concept signed_integral_type = signed_integral<T>;
template <class T, class U>
concept Derived = is_base_of<U, T>::value;