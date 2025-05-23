#pragma once
#if defined(__GNUC__) || defined(__GNUG__)
using namespace std;
using int128_t = __int128;
using uint128_t = unsigned __int128;
to_chars_result to_chars(char *, char *, uint128_t) noexcept;
to_chars_result to_chars(char *, char *, int128_t) noexcept;
ostream &operator<<(ostream &, uint128_t);
ostream &operator<<(ostream &, int128_t);
string to_string(uint128_t);
string to_string(int128_t);
#endif