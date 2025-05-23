#pragma once
#include "GenericConstraints.h"
#if defined(__GNUC__) || defined(__GNUG__)
using namespace std;
using int128_t = __int128;
using uint128_t = unsigned __int128;
to_chars_result to_chars(char *, char *, uint128_t) noexcept;
to_chars_result to_chars(char *, char *, int128_t) noexcept;
template <typename T>
ostream &operator<<(ostream &, T)
    requires is_128bit<T>;
template <typename T>
string to_string(T)
    requires is_128bit<T>;
#endif