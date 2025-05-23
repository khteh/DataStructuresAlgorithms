#include "pch.h"
#include "cout128.h"
template ostream &operator<<(ostream &, __int128);
template ostream &operator<<(ostream &, unsigned __int128);
template string to_string(__int128);
template string to_string(unsigned __int128);
// https://stackoverflow.com/questions/25114597/how-to-print-int128-in-g
to_chars_result to_chars(char *begin, char *end, uint128_t x) noexcept
{
    // if x fits into a 64-bit integer, we delegate to std::to_chars
    if (x <= uint64_t(-1))
        return std::to_chars(begin, end, uint64_t(x));

    /// The greatest power of 10 that fits into a 64-bit integer is 10^19.
    constexpr uint64_t exp10_19 = 10000000000000000000ull;
    constexpr int lower_max_digits = 19;

    // We can shift the result by 19 decimal digits to the right and convert
    // the quotient and remainder separately.
    // Note that even after dividing by 10^19, the quotient may not fit into
    // a 64-bit integer, so this function is recursive.
    auto upper_result = ::to_chars(begin, end, x / exp10_19);
    if (upper_result.ec != std::errc{})
        return upper_result;

    auto lower_result = std::to_chars(upper_result.ptr, end, uint64_t(x % exp10_19));
    if (lower_result.ec != std::errc{})
        return lower_result;

    auto lower_length = lower_result.ptr - upper_result.ptr;

    // The remainder is exactly 19 digits long, and we have to zero-pad
    // to the left if it is shorter.
    char *result_end = upper_result.ptr + lower_max_digits;
    char *result_begin = result_end - lower_length;
    memmove(result_begin, upper_result.ptr, size_t(lower_length));
    memset(upper_result.ptr, '0', size_t(lower_max_digits - lower_length));

    return {result_end, std::errc{}};
}
to_chars_result to_chars(char *begin, char *end, int128_t x) noexcept
{
    // For positive numbers, we delegate to the unsigned function immediately.
    if (x >= 0)
        return ::to_chars(begin, end, uint128_t(x));
    // For negatives, we can check if 64 bits are enough and use std::to_chars.
    if (x >= std::numeric_limits<int64_t>::min())
        return std::to_chars(begin, end, int64_t(x));
    // Otherwise, we simply prepend a '-' sign and delegate to the unsigned function.
    if (end - begin < 2)
        return {begin, std::errc::value_too_large};
    *begin = '-';
    return ::to_chars(begin + 1, end, -uint128_t(x));
}
template <typename T>
ostream &operator<<(ostream &out, T x)
    requires is_128bit<T>
{
    // 40 characters is always enough to fit 128-bit integers.
    char buffer[40];
    to_chars_result result = ::to_chars(buffer, end(buffer), x);
    return out << string_view{buffer, result.ptr};
}
template <typename T>
string to_string(T x)
    requires is_128bit<T>
{
    // 40 characters is always enough to fit 128-bit integers.
    char buffer[40];
    to_chars_result result = ::to_chars(buffer, end(buffer), x);
    return string{buffer, result.ptr};
}