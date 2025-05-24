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
// Write the 128-bit integer val to out, with a minus sign if decimal and neg
// is true. Obey all of the ostream settings of out for integer display: octal
// or hexadecimal, upper case letters, plus sign, fill character and width, and
// fill placement.
void out128(ostream &out, uint128_t val, int neg)
{
    // Note if the number is zero. (No hex or octal prefix in this case.)
    auto zero = val == 0;

    // Note if upper-case letters requested.
    auto state = out.flags();
    auto upper = (state & ios_base::uppercase) != 0;

    // Set base for digits.
    unsigned base = state & ios_base::hex ? 16 : state & ios_base::oct ? 8
                                                                       : 10;

    // Space for digits and prefix. Generate digits starting at the end of the
    // string, going backwards. num will be the digit string. Terminate it.
    char str[47];
    auto end = str + sizeof(str), num = end;
    *--num = 0;

    // Compute and place digits in base base.
    do
    {
        char dig = val % base;
        val /= base;
        dig += dig < 10 ? '0' : (upper ? 'A' : 'a') - 10;
        *--num = dig;
    } while (val);

    // Prepend octal number with a zero if requested.
    if (state & ios_base::showbase && base == 8 && !zero)
        *--num = '0';

    // pre will be the prefix string. Terminate it.
    auto pre = num;
    *--pre = 0;

    // Put a plus or minus sign in the prefix as appropriate.
    if (base == 10)
    {
        if (neg)
            *--pre = '-';
        else if (state & ios_base::showpos)
            *--pre = '+';
    }

    // Prefix a hexadecimal number if requested.
    else if (state & ios_base::showbase && base == 16 && !zero)
    {
        *--pre = upper ? 'X' : 'x';
        *--pre = '0';
    }

    // Compute the number of pad characters and get the fill character.
    auto len = (num - pre) + (end - num) - 2;
    auto pad = out.width();
    out.width(0);
    pad = pad > len ? pad - len : 0;
    char fill = out.fill();

    // Put the padding before prefix if neither left nor internal requested.
    if (!(state & (ios_base::internal | ios_base::left)))
        while (pad)
        {
            out << fill;
            pad--;
        }

    // Write prefix.
    out << pre;

    // Put the padding between the prefix and the digits if requested.
    if (state & ios_base::internal)
        while (pad)
        {
            out << fill;
            pad--;
        }

    // Write digits.
    out << num;

    // Put number to the left of padding, if requested.
    if (state & ios_base::left)
        while (pad)
        {
            out << fill;
            pad--;
        }
}
template <typename T>
ostream &operator<<(ostream &out, T val)
    requires is_128_bits<T>
{
#if 0
    // 40 characters is always enough to fit 128-bit integers.
    char buffer[40];
    to_chars_result result = ::to_chars(buffer, end(buffer), val);
    return out << string_view{buffer, result.ptr};
#endif
    if constexpr (is_same_v<T, uint128_t>)
        out128(out, val, 0);
    else if constexpr (is_same_v<T, int128_t>)
    {
        // Overload << for a signed 128-bit integer. Negation of the most negative
        // signed value gives the correct unsigned absolute value.
        auto state = out.flags();
        if (val < 0 && !(state & (ios_base::hex | ios_base::oct)))
            out128(out, -(uint128_t)val, 1);
        else
            out128(out, (uint128_t)val, 0);
    }
    else
        throw invalid_argument("Invalid template paramater type!");
    return out;
}
template <typename T>
string to_string(T x)
    requires is_128_bits<T>
{
    // 40 characters is always enough to fit 128-bit integers.
    char buffer[40];
    to_chars_result result = ::to_chars(buffer, end(buffer), x);
    return string{buffer, result.ptr};
}