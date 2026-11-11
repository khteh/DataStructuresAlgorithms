#include "pch.h"
#include "cout128.h"
template ostream &operator<<(ostream &, int128_t);
template ostream &operator<<(ostream &, uint128_t);
template string to_string(int128_t);
template string to_string(uint128_t);
template istream &operator>>(istream &, int128_t &);
template istream &operator>>(istream &, uint128_t &);
template istream &operator>>(istream &&, int128_t &);
template istream &operator>>(istream &&, uint128_t &);
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
template <is_128_bits T>
ostream &operator<<(ostream &out, T val)
{
    if constexpr (is_same_v<T, uint128_t>)
        out128(out, val, 0);
    else if constexpr (is_same_v<T, int128_t>)
    {
        /*
         * Overload << for a signed 128-bit integer. Negation of the most negative
         * signed value gives the correct unsigned absolute value.

        When C++ writes a signed integer in hex or octal, it doesn’t write -1f. It writes the number’s bit pattern, the two’s complement representation, as if the value were unsigned:

        long long -1 in hex:  ffffffffffffffff                    (16 f's: all 64 bits set)
        int128_t  -1 in hex:  ffffffffffffffffffffffffffffffff    (32 f's: all 128 bits set)
        Reading that back doesn’t give −1

        When operator>> reads ffff…ff, it sees a positive number, 2¹²⁸ − 1. That’s far bigger than the largest int128_t (2¹²⁷ − 1), so it reports “out of range”: it stores the maximum and sets the fail flag. The standard library does the same with long long:

        read back into long long:  9223372036854775807, fail = 1
        read back into int128_t:   170141183460469231731687303715884105727, fail = 1

        So for negative signed values, “write in hex, then read back in hex” doesn’t give you the original number, for every signed integer type in C++.
        If you need hex round trips of negative values, read the bit pattern into the unsigned type, then convert:

        uint128_t bits;
        iss >> hex >> bits;
        int128_t value = (int128_t)bits;   // ffff…ff → -1
        */
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
template <is_128_bits T>
string to_string(T x)
{
    // 40 characters is always enough to fit 128-bit integers.
    char buffer[40];
    to_chars_result result = ::to_chars(buffer, end(buffer), x);
    return string{buffer, result.ptr};
}
/* Read a 128-bit integer from in. Follows the same rules as the standard operator>> for
 * long long / unsigned long long (std::num_get), so the two behave the same way:
 * - Leading whitespace is skipped if skipws is set (the default).
 * - An optional '+' or '-' sign. For uint128_t, '-' negates the value modulo 2^128, like strtoull: "-1" -> max.
 * - The base comes from the basefield flags: dec (default), hex or oct. A "0x" / "0X" prefix is accepted in hex.
 *   With no basefield flag set, the base is taken from the prefix: "0x" / "0X" -> hex, "0" -> octal, otherwise decimal.
 * - Reading stops at the first character that is not a digit in that base. That character stays in the stream.
 * - No digits: val = 0 and failbit.
 * - Out of range: val = max (min for a negative int128_t) and failbit.
 * - Reaching the end of the input sets eofbit.
 * - Empty input or only whitespace: val is unchanged, failbit and eofbit (set by the sentry).
 */
template <is_128_bits T>
istream &operator>>(istream &in, T &val)
{
    istream::sentry sentry(in); // Skips leading whitespace if skipws is set
    if (!sentry)
        return in;
    streambuf *buf = in.rdbuf();
    ios_base::iostate state = ios_base::goodbit;
    int c = buf->sgetc(); // Peek at the next character without consuming it

    // Optional sign
    bool negative = false;
    if (c == '+' || c == '-')
    {
        negative = c == '-';
        buf->sbumpc();
        c = buf->sgetc();
    }

    // Base. 0: detect from the prefix
    unsigned base;
    switch (in.flags() & ios_base::basefield)
    {
    case ios_base::hex:
        base = 16;
        break;
    case ios_base::oct:
        base = 8;
        break;
    case ios_base::dec:
        base = 10;
        break;
    default:
        base = 0;
    }
    bool digits = false; // At least one digit read
    if (c == '0' && base != 10)
    {
        buf->sbumpc();
        c = buf->sgetc();
        digits = true; // The '0' itself is a valid number if nothing follows
        if ((c == 'x' || c == 'X') && (base == 16 || base == 0))
        {
            buf->sbumpc(); // "0x" prefix: hex digits must follow
            c = buf->sgetc();
            base = 16;
            digits = false;
        }
        else if (!base)
            base = 8; // Leading '0': octal
    }
    if (!base)
        base = 10;

    // Largest magnitude that fits: 2^127 - 1 (2^127 if negative) for int128_t, 2^128 - 1 for uint128_t
    uint128_t limit;
    if constexpr (is_same_v<T, int128_t>)
        limit = negative ? uint128_t(1) << 127 : (uint128_t(1) << 127) - 1;
    else
        limit = numeric_limits<uint128_t>::max();

    // Digits. Keep consuming them after an overflow, as the standard does, so they don't stay in the stream.
    uint128_t magnitude = 0;
    bool overflow = false;
    for (; c != istream::traits_type::eof(); buf->sbumpc(), c = buf->sgetc())
    {
        unsigned digit;
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (c >= 'a' && c <= 'f')
            digit = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            digit = c - 'A' + 10;
        else
            break;
        if (digit >= base)
            break;
        digits = true;
        if (overflow || magnitude > (limit - digit) / base) // magnitude * base + digit > limit
            overflow = true;
        else
            magnitude = magnitude * base + digit;
    }
    if (c == istream::traits_type::eof())
        state |= ios_base::eofbit;

    if (!digits)
    {
        val = 0;
        state |= ios_base::failbit;
    }
    else if (overflow)
    {
        if constexpr (is_same_v<T, int128_t>)
            val = negative ? numeric_limits<int128_t>::min() : numeric_limits<int128_t>::max();
        else
            val = numeric_limits<uint128_t>::max();
        state |= ios_base::failbit;
    }
    else if constexpr (is_same_v<T, int128_t>)
        val = negative ? int128_t(-magnitude) : int128_t(magnitude); // -2^127 -> min: two's complement, well-defined since C++20
    else
        val = negative ? -magnitude : magnitude;
    in.setstate(state);
    return in;
}
/* For a temporary stream, e.g. istringstream(s) >> value. A temporary can't bind to istream &,
 * and the standard library's own rvalue-stream overload can't find the one above from inside namespace std.
It’s about where C++ looks when it sees >> inside a function. The inner >> code in std library implementation is looked up from inside std.
When the compiler sees __is >> x inside that function, it has to find a matching operator>>. It searches in two ways:
(1) From where the code is written, outwards. The code is inside namespace std, so it searches std first. std contains plenty of operator>> functions, so it finds some and stops there.
    It never continues out to the global namespace, where our operator>> lives.
(2) Argument-dependent lookup (ADL). It also searches the namespaces that the argument types belong to. istringstream belongs to std, already searched.
    __int128 is a built-in type like int, so it belongs to no namespace and adds nothing.
Neither search reaches the global namespace, so our operator>> is never considered. The __rvalue_stream_extraction_t in the return type is a check that __is >> x would compile.
Since it wouldn’t, this standard overload removes itself from the candidates, and you get “no match for operator>>”.

Why our own code could see it:
When you write iss >> num in your code, which is in the global namespace, step 1 starts in the global namespace and finds our operator>>.
The only problem with istringstream(tokens[i]) >> num was the temporary. This istream && overload fixes that, and because it’s also in the global namespace, its inner in >> val finds our real implementation.
The same applies to anything in std that uses >> or << internally, such as std::istream_iterator<int128_t> or std::ostream_iterator<int128_t>.
They can’t see your global 128-bit operators for the same reason, so they won’t work with them.
 */
template <is_128_bits T>
istream &operator>>(istream &&in, T &val)
{
    return in >> val; // in has a name, so it's an lvalue here: calls the overload above
}