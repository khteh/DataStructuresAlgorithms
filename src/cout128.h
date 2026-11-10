#pragma once
#include "GenericConstraints.h"
#ifdef __SIZEOF_INT128__
using namespace std;
using int128_t = int128_t;
using uint128_t = uint128_t;
to_chars_result to_chars(char *, char *, uint128_t) noexcept;
to_chars_result to_chars(char *, char *, int128_t) noexcept;
template <typename T>
ostream &operator<<(ostream &, T)
    requires is_128_bits<T>;
template <typename T>
string to_string(T)
    requires is_128_bits<T>;
#endif