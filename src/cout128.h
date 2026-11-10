#pragma once
#include "GenericConstraints.h"
using namespace std;

#ifdef __SIZEOF_INT128__
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

to_chars_result to_chars(char *, char *, uint128_t) noexcept;
to_chars_result to_chars(char *, char *, int128_t) noexcept;

template <is_128_bits T>
ostream &operator<<(ostream &, T);

template <is_128_bits T>
string to_string(T);

template <is_128_bits T>
istream &operator>>(istream &, T &);

// For a temporary stream, e.g. istringstream(s) >> value. A temporary can't bind to istream &,
// and the standard library's own rvalue-stream overload can't find the one above from inside namespace std.
template <is_128_bits T>
istream &operator>>(istream &&, T &);
#endif