#pragma once
#include <concepts>
using namespace std;
template <typename T>
concept arithmetic_type = integral<T> || floating_point<T>;
template <typename T>
concept integral_type = integral<T>;
