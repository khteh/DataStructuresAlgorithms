#include "pch.h"
using namespace std;
template <typename T>
class Int128InsertionTestFixtureBase
{
public:
    void SetUp(string const &expected, T value, ios_base::fmtflags flags, streamsize width, char fill)
    {
        _expected = expected;
        _value = value;
        _flags = flags;
        _width = width;
        _fill = fill;
    }
    void InsertionTest()
    {
        ostringstream oss;
        oss.flags(_flags); // Replaces all the flags: base, showbase, showpos, uppercase and adjustment
        oss.width(_width);
        oss.fill(_fill);
        oss << _value << '|'; // '|' shows the padding and that the width is reset to 0 after the value
        ASSERT_EQ(_expected + "|", oss.str());
    }

protected:
    string _expected;
    T _value;
    ios_base::fmtflags _flags;
    streamsize _width;
    char _fill;
};
class Int128InsertionTestFixture : public Int128InsertionTestFixtureBase<int128_t>, public testing::TestWithParam<tuple<string, int128_t, ios_base::fmtflags, streamsize, char>>
{
public:
    void SetUp() override
    {
        Int128InsertionTestFixtureBase::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()), get<3>(GetParam()), get<4>(GetParam()));
    }
};
TEST_P(Int128InsertionTestFixture, Int128InsertionTests)
{
    this->InsertionTest();
}
// Columns: expected output, value, flags, width, fill
INSTANTIATE_TEST_SUITE_P(
    Int128InsertionTests,
    Int128InsertionTestFixture,
    ::testing::Values(
        // Decimal
        make_tuple("0", 0, ios_base::dec, 0, ' '),
        make_tuple("42", 42, ios_base::dec, 0, ' '),
        make_tuple("-42", -42, ios_base::dec, 0, ' '),
        make_tuple("123456789012345678901234567890", (int128_t)12345678901234567890ULL * 10000000000LL + 1234567890, ios_base::dec, 0, ' '),
        make_tuple("-123456789012345678901234567890", -((int128_t)12345678901234567890ULL * 10000000000LL + 1234567890), ios_base::dec, 0, ' '),
        make_tuple("170141183460469231731687303715884105727", numeric_limits<int128_t>::max(), ios_base::dec, 0, ' '),
        make_tuple("-170141183460469231731687303715884105728", numeric_limits<int128_t>::min(), ios_base::dec, 0, ' '),
        make_tuple("42", 42, ios_base::fmtflags(0), 0, ' '), // No basefield flag: decimal
        // showpos: '+' for zero and positive values, in decimal only
        make_tuple("+42", 42, ios_base::dec | ios_base::showpos, 0, ' '),
        make_tuple("+0", 0, ios_base::dec | ios_base::showpos, 0, ' '),
        make_tuple("-42", -42, ios_base::dec | ios_base::showpos, 0, ' '),
        make_tuple("2a", 42, ios_base::hex | ios_base::showpos, 0, ' '),
        // Hexadecimal
        make_tuple("2a", 42, ios_base::hex, 0, ' '),
        make_tuple("2A", 42, ios_base::hex | ios_base::uppercase, 0, ' '),
        make_tuple("0x2a", 42, ios_base::hex | ios_base::showbase, 0, ' '),
        make_tuple("0X2A", 42, ios_base::hex | ios_base::showbase | ios_base::uppercase, 0, ' '),
        make_tuple("0", 0, ios_base::hex | ios_base::showbase, 0, ' '), // No prefix for zero
        make_tuple("7fffffffffffffffffffffffffffffff", numeric_limits<int128_t>::max(), ios_base::hex, 0, ' '),
        // Negative values in hex / oct: the two's complement bit pattern, no minus sign
        make_tuple("80000000000000000000000000000000", numeric_limits<int128_t>::min(), ios_base::hex, 0, ' '),
        make_tuple("ffffffffffffffffffffffffffffffff", -1, ios_base::hex, 0, ' '),
        make_tuple("ffffffffffffffffffffffffffffffd6", -42, ios_base::hex, 0, ' '),
        // Octal
        make_tuple("52", 42, ios_base::oct, 0, ' '),
        make_tuple("052", 42, ios_base::oct | ios_base::showbase, 0, ' '),
        make_tuple("0", 0, ios_base::oct | ios_base::showbase, 0, ' '), // Not "00"
        make_tuple("1777777777777777777777777777777777777777777", numeric_limits<int128_t>::max(), ios_base::oct, 0, ' '),
        make_tuple("3777777777777777777777777777777777777777777", -1, ios_base::oct, 0, ' '),
        // Width, fill and adjustment
        make_tuple("   42", 42, ios_base::dec, 5, ' '), // Right by default
        make_tuple("***42", 42, ios_base::dec | ios_base::right, 5, '*'),
        make_tuple("42***", 42, ios_base::dec | ios_base::left, 5, '*'),
        make_tuple("**-42", -42, ios_base::dec | ios_base::right, 5, '*'),
        make_tuple("-42**", -42, ios_base::dec | ios_base::left, 5, '*'),
        make_tuple("-**42", -42, ios_base::dec | ios_base::internal, 5, '*'), // Fill between the sign and the digits
        make_tuple("+**42", 42, ios_base::dec | ios_base::showpos | ios_base::internal, 5, '*'),
        make_tuple("0x**2a", 42, ios_base::hex | ios_base::showbase | ios_base::internal, 6, '*'), // Fill between the prefix and the digits
        make_tuple("**0x2a", 42, ios_base::hex | ios_base::showbase | ios_base::right, 6, '*'),
        make_tuple("123456", 123456, ios_base::dec, 3, '*'), // Width smaller than the number: no padding
        make_tuple("-00170141183460469231731687303715884105728", numeric_limits<int128_t>::min(), ios_base::dec | ios_base::internal, 42, '0')));
class UInt128InsertionTestFixture : public Int128InsertionTestFixtureBase<uint128_t>, public testing::TestWithParam<tuple<string, uint128_t, ios_base::fmtflags, streamsize, char>>
{
public:
    void SetUp() override
    {
        Int128InsertionTestFixtureBase::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()), get<3>(GetParam()), get<4>(GetParam()));
    }
};
TEST_P(UInt128InsertionTestFixture, UInt128InsertionTests)
{
    this->InsertionTest();
}
INSTANTIATE_TEST_SUITE_P(
    UInt128InsertionTests,
    UInt128InsertionTestFixture,
    ::testing::Values(
        make_tuple("0", 0, ios_base::dec, 0, ' '),
        make_tuple("42", 42, ios_base::dec, 0, ' '),
        make_tuple("18446744073709551616", (uint128_t)1 << 64, ios_base::dec, 0, ' '), // 2^64: beyond unsigned long long
        make_tuple("340282366920938463463374607431768211455", numeric_limits<uint128_t>::max(), ios_base::dec, 0, ' '),
        make_tuple("ffffffffffffffffffffffffffffffff", numeric_limits<uint128_t>::max(), ios_base::hex, 0, ' '),
        make_tuple("0XFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", numeric_limits<uint128_t>::max(), ios_base::hex | ios_base::showbase | ios_base::uppercase, 0, ' '),
        make_tuple("0x10000000000000000", (uint128_t)1 << 64, ios_base::hex | ios_base::showbase, 0, ' '),
        make_tuple("3777777777777777777777777777777777777777777", numeric_limits<uint128_t>::max(), ios_base::oct, 0, ' '),
        make_tuple("042", 34, ios_base::oct | ios_base::showbase, 0, ' '),
        make_tuple("42", 42, ios_base::dec | ios_base::showpos, 0, ' '), // Like unsigned long long: no '+' for unsigned types
        make_tuple("42   ", 42, ios_base::dec | ios_base::left, 5, ' '),
        make_tuple("0000000042", 42, ios_base::dec | ios_base::internal, 10, '0')));
// Several values and other types in one stream; setw only applies to the next value
TEST(Int128InsertionTests, Int128ChainedInsertionTest)
{
    ostringstream oss;
    oss << numeric_limits<int128_t>::min() << ' ' << setw(5) << (int128_t)42 << ' ' << 7 << ' ' << hex << showbase << numeric_limits<uint128_t>::max() << ' ' << 255;
    ASSERT_EQ("-170141183460469231731687303715884105728    42 7 0xffffffffffffffffffffffffffffffff 0xff", oss.str());
}
// For values that fit in 64 bits, the output must match long long / unsigned long long for every combination of flags
TEST(Int128InsertionTests, Int128MatchesStandardFormattingTest)
{
    mt19937_64 generator(12345); // Fixed seed: reproducible failures
    vector<long long> values{0, 1, -1, 42, -42, numeric_limits<long long>::max(), numeric_limits<long long>::min()};
    for (size_t i = 0; i < 50; i++)
        values.push_back((long long)(generator() >> (generator() % 64)) * (generator() % 2 ? 1 : -1)); // Mix of lengths and signs
    auto format = [](auto value, ios_base::fmtflags flags, streamsize width)
    {
        ostringstream oss;
        oss.flags(flags);
        oss.width(width);
        oss.fill('*');
        oss << value << '|';
        return oss.str();
    };
    for (ios_base::fmtflags base : {ios_base::dec, ios_base::hex, ios_base::oct, ios_base::fmtflags(0)})
        for (ios_base::fmtflags adjust : {ios_base::fmtflags(0), ios_base::left, ios_base::right, ios_base::internal})
            for (ios_base::fmtflags extra : {ios_base::fmtflags(0), ios_base::showbase, ios_base::showpos, ios_base::uppercase, ios_base::showbase | ios_base::showpos | ios_base::uppercase})
                for (streamsize width : {0, 1, 5, 30})
                    for (long long value : values)
                    {
                        ios_base::fmtflags flags = base | adjust | extra;
                        // Negative values in hex / oct print the bit pattern: 64 bits for long long, 128 bits for int128_t
                        if (value >= 0 || base == ios_base::dec || base == ios_base::fmtflags(0))
                        {
                            ASSERT_EQ(format(value, flags, width), format((int128_t)value, flags, width)) << value << ", flags " << flags << ", width " << width;
                        }
                        ASSERT_EQ(format((unsigned long long)value, flags, width), format((uint128_t)(unsigned long long)value, flags, width)) << (unsigned long long)value << ", flags " << flags << ", width " << width;
                    }
}
TEST(Int128InsertionTests, Int128ToStringTest)
{
    ASSERT_EQ("0", to_string((int128_t)0));
    ASSERT_EQ("-1", to_string((int128_t)-1));
    ASSERT_EQ("-9223372036854775809", to_string((int128_t)numeric_limits<long long>::min() - 1)); // Just below the 64-bit range
    ASSERT_EQ("170141183460469231731687303715884105727", to_string(numeric_limits<int128_t>::max()));
    ASSERT_EQ("-170141183460469231731687303715884105728", to_string(numeric_limits<int128_t>::min()));
    ASSERT_EQ("0", to_string((uint128_t)0));
    ASSERT_EQ("10000000000000000000", to_string((uint128_t)10000000000000000000ULL)); // 10^19: the split point in to_chars
    ASSERT_EQ("100000000000000000000", to_string((uint128_t)10000000000000000000ULL * 10));
    ASSERT_EQ("340282366920938463463374607431768211455", to_string(numeric_limits<uint128_t>::max()));
}
TEST(Int128InsertionTests, Int128ToCharsBufferTooSmallTest)
{
    char buffer[10];
    ASSERT_EQ(errc::value_too_large, ::to_chars(buffer, end(buffer), numeric_limits<uint128_t>::max()).ec);
    ASSERT_EQ(errc::value_too_large, ::to_chars(buffer, end(buffer), numeric_limits<int128_t>::min()).ec);
    to_chars_result result = ::to_chars(buffer, end(buffer), (int128_t)-123456789);
    ASSERT_EQ(errc{}, result.ec);
    ASSERT_EQ("-123456789", string(buffer, result.ptr));
}
template <typename T>
class Int128ExtractionTestFixtureBase
{
public:
    void SetUp(string const &input, ios_base::fmtflags base, T expected, bool fail, bool eof)
    {
        _input = input;
        _base = base;
        _expected = expected;
        _fail = fail;
        _eof = eof;
    }
    void ExtractionTest()
    {
        istringstream iss(_input);
        iss.setf(_base, ios_base::basefield); // fmtflags(0): base from the prefix
        T value = 7;                          // Stays 7 when the sentry fails (empty input or only whitespace)
        iss >> value;
        ASSERT_EQ(to_string(_expected), to_string(value)) << "Input: \"" << _input << "\"";
        ASSERT_EQ(_fail, iss.fail()) << "Input: \"" << _input << "\"";
        ASSERT_EQ(_eof, iss.eof()) << "Input: \"" << _input << "\"";
    }

protected:
    string _input;
    ios_base::fmtflags _base;
    T _expected;
    bool _fail, _eof;
};
class Int128ExtractionTestFixture : public Int128ExtractionTestFixtureBase<int128_t>, public testing::TestWithParam<tuple<string, ios_base::fmtflags, int128_t, bool, bool>>
{
public:
    void SetUp() override
    {
        Int128ExtractionTestFixtureBase::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()), get<3>(GetParam()), get<4>(GetParam()));
    }
};
TEST_P(Int128ExtractionTestFixture, Int128ExtractionTests)
{
    this->ExtractionTest();
}
// Columns: input, base, expected value, failbit, eofbit
INSTANTIATE_TEST_SUITE_P(
    Int128ExtractionTests,
    Int128ExtractionTestFixture,
    ::testing::Values(
        // Decimal
        make_tuple("0", ios_base::dec, 0, false, true),
        make_tuple("42", ios_base::dec, 42, false, true),
        make_tuple(" \t+42", ios_base::dec, 42, false, true), // Leading whitespace skipped
        make_tuple("-42", ios_base::dec, -42, false, true),
        make_tuple("-0", ios_base::dec, 0, false, true),
        make_tuple("017", ios_base::dec, 17, false, true),    // Leading 0 is not octal in dec
        make_tuple("42abc", ios_base::dec, 42, false, false), // Stops at the first non-digit
        make_tuple("0x1f", ios_base::dec, 0, false, false),   // 'x' is not a decimal digit
        make_tuple("123456789012345678901234567890", ios_base::dec, (int128_t)12345678901234567890ULL * 10000000000LL + 1234567890, false, true),
        make_tuple("-123456789012345678901234567890", ios_base::dec, -((int128_t)12345678901234567890ULL * 10000000000LL + 1234567890), false, true),
        make_tuple("170141183460469231731687303715884105727", ios_base::dec, numeric_limits<int128_t>::max(), false, true),
        make_tuple("-170141183460469231731687303715884105728", ios_base::dec, numeric_limits<int128_t>::min(), false, true),
        // Out of range: max / min and failbit
        make_tuple("170141183460469231731687303715884105728", ios_base::dec, numeric_limits<int128_t>::max(), true, true),
        make_tuple("-170141183460469231731687303715884105729", ios_base::dec, numeric_limits<int128_t>::min(), true, true),
        make_tuple("99999999999999999999999999999999999999999 1", ios_base::dec, numeric_limits<int128_t>::max(), true, false),
        // No digits: 0 and failbit
        make_tuple("-", ios_base::dec, 0, true, true),
        make_tuple("+", ios_base::dec, 0, true, true),
        make_tuple("abc", ios_base::dec, 0, true, false),
        // Nothing to read: value unchanged, failbit and eofbit
        make_tuple("", ios_base::dec, 7, true, true),
        make_tuple("   ", ios_base::dec, 7, true, true),
        // Hexadecimal
        make_tuple("1f", ios_base::hex, 31, false, true),
        make_tuple("0x1F", ios_base::hex, 31, false, true),
        make_tuple("-0X1f", ios_base::hex, -31, false, true),
        make_tuple("7fffffffffffffffffffffffffffffff", ios_base::hex, numeric_limits<int128_t>::max(), false, true),
        make_tuple("-80000000000000000000000000000000", ios_base::hex, numeric_limits<int128_t>::min(), false, true),
        make_tuple("80000000000000000000000000000000", ios_base::hex, numeric_limits<int128_t>::max(), true, true),
        make_tuple("0x", ios_base::hex, 0, true, true), // Prefix without digits
        make_tuple("1g", ios_base::hex, 1, false, false),
        // Octal
        make_tuple("17", ios_base::oct, 15, false, true),
        make_tuple("-017", ios_base::oct, -15, false, true),
        make_tuple("1777777777777777777777777777777777777777777", ios_base::oct, numeric_limits<int128_t>::max(), false, true),
        make_tuple("2000000000000000000000000000000000000000000", ios_base::oct, numeric_limits<int128_t>::max(), true, true),
        make_tuple("8", ios_base::oct, 0, true, false),
        // No basefield flag: base from the prefix
        make_tuple("0x1f", ios_base::fmtflags(0), 31, false, true),
        make_tuple("017", ios_base::fmtflags(0), 15, false, true),
        make_tuple("17", ios_base::fmtflags(0), 17, false, true),
        make_tuple("-0x10", ios_base::fmtflags(0), -16, false, true),
        make_tuple("08", ios_base::fmtflags(0), 0, false, false))); // Octal "0", stops at '8'
class UInt128ExtractionTestFixture : public Int128ExtractionTestFixtureBase<uint128_t>, public testing::TestWithParam<tuple<string, ios_base::fmtflags, uint128_t, bool, bool>>
{
public:
    void SetUp() override
    {
        Int128ExtractionTestFixtureBase::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()), get<3>(GetParam()), get<4>(GetParam()));
    }
};
TEST_P(UInt128ExtractionTestFixture, UInt128ExtractionTests)
{
    this->ExtractionTest();
}
INSTANTIATE_TEST_SUITE_P(
    UInt128ExtractionTests,
    UInt128ExtractionTestFixture,
    ::testing::Values(
        make_tuple("0", ios_base::dec, 0, false, true),
        make_tuple("+42", ios_base::dec, 42, false, true),
        make_tuple("18446744073709551616", ios_base::dec, (uint128_t)1 << 64, false, true), // 2^64: beyond unsigned long long
        make_tuple("340282366920938463463374607431768211455", ios_base::dec, numeric_limits<uint128_t>::max(), false, true),
        make_tuple("340282366920938463463374607431768211456", ios_base::dec, numeric_limits<uint128_t>::max(), true, true),
        make_tuple("-1", ios_base::dec, numeric_limits<uint128_t>::max(), false, true), // Negated modulo 2^128, like strtoull
        make_tuple("-42", ios_base::dec, numeric_limits<uint128_t>::max() - 41, false, true),
        make_tuple("ffffffffffffffffffffffffffffffff", ios_base::hex, numeric_limits<uint128_t>::max(), false, true),
        make_tuple("0XFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", ios_base::hex, numeric_limits<uint128_t>::max(), false, true),
        make_tuple("100000000000000000000000000000000", ios_base::hex, numeric_limits<uint128_t>::max(), true, true),
        make_tuple("3777777777777777777777777777777777777777777", ios_base::oct, numeric_limits<uint128_t>::max(), false, true),
        make_tuple("4000000000000000000000000000000000000000000", ios_base::oct, numeric_limits<uint128_t>::max(), true, true),
        make_tuple("0x10000000000000000", ios_base::fmtflags(0), (uint128_t)1 << 64, false, true),
        make_tuple("abc", ios_base::dec, 0, true, false),
        make_tuple("", ios_base::dec, 7, true, true)));
// Several values from one stream, and the character that stopped the read stays in the stream
TEST(Int128ExtractionTests, Int128ChainedExtractionTest)
{
    istringstream iss("170141183460469231731687303715884105727 -42  340282366920938463463374607431768211455 99xyz");
    int128_t a, b;
    uint128_t c, d;
    iss >> a >> b >> c >> d;
    ASSERT_FALSE(iss.fail());
    ASSERT_EQ(to_string(numeric_limits<int128_t>::max()), to_string(a));
    ASSERT_EQ(to_string((int128_t)-42), to_string(b));
    ASSERT_EQ(to_string(numeric_limits<uint128_t>::max()), to_string(c));
    ASSERT_EQ(to_string((uint128_t)99), to_string(d));
    string rest;
    iss >> rest;
    ASSERT_EQ("xyz", rest);
}
// Values written with operator<< read back to the same value, in every base
TEST(Int128ExtractionTests, Int128RoundTripTest)
{
    mt19937_64 generator(12345); // Fixed seed: reproducible failures
    vector<uint128_t> unsignedValues{0, 1, numeric_limits<uint128_t>::max(), (uint128_t)numeric_limits<uint64_t>::max() + 1};
    vector<int128_t> signedValues{0, -1, numeric_limits<int128_t>::max(), numeric_limits<int128_t>::min()};
    for (size_t i = 0; i < 1000; i++)
    {
        uint128_t value = ((uint128_t)generator() << 64) | generator();
        unsignedValues.push_back(value >> (generator() % 128)); // Mix of lengths
        signedValues.push_back((int128_t)unsignedValues.back());
    }
    for (ios_base::fmtflags base : {ios_base::dec, ios_base::hex, ios_base::oct})
        for (bool withBase : {false, true}) // With and without a "0x" / "0" prefix
        {
            for (uint128_t expected : unsignedValues)
            {
                ostringstream oss;
                oss.setf(base, ios_base::basefield);
                if (withBase)
                    oss.setf(ios_base::showbase);
                oss << expected;
                istringstream iss(oss.str());
                iss.setf(base, ios_base::basefield);
                uint128_t value = 0;
                iss >> value;
                ASSERT_FALSE(iss.fail()) << oss.str();
                ASSERT_EQ(to_string(expected), to_string(value)) << oss.str();
            }
            for (int128_t expected : signedValues)
            {
                // Like long long, operator<< writes negative values in hex / oct as their two's complement bit pattern,
                // which operator>> reads as an out-of-range positive value. Round-trip negatives in decimal only.
                if (expected < 0 && base != ios_base::dec)
                    continue;
                ostringstream oss;
                oss.setf(base, ios_base::basefield);
                if (withBase)
                    oss.setf(ios_base::showbase);
                oss << expected;
                istringstream iss(oss.str());
                iss.setf(base, ios_base::basefield);
                int128_t value = 0;
                iss >> value;
                ASSERT_FALSE(iss.fail()) << oss.str();
                ASSERT_EQ(to_string(expected), to_string(value)) << oss.str();
            }
        }
}
/* A temporary stream, as in Arithmetic<T>::ReversePolishNotation: istringstream(token) >> value
istringstream(tokens[i]) is a temporary object, and operator>> takes istream &, a non-const reference.
C++ doesn’t let a temporary bind to a non-const reference, so the usual overload can’t be used.
The same line works for int or long because their operator>> is a member function of the stream, and member functions can be called on temporaries.
The standard library also has an overload for temporary streams, but it’s in namespace std and passes the call on from there.
It can’t see our operator>>, which is in the global namespace, so it doesn’t help either.
This overload fixes the temporary object problem as seen in Arithmetic<T>::ReversePolishNotation: istringstream(token) >> value
It takes the stream as istream &&, which does bind to a temporary, and passes it to the existing one.
 */
TEST(Int128ExtractionTests, Int128TemporaryStreamTest)
{
    int128_t a = 0;
    uint128_t b = 0;
    istringstream("-170141183460469231731687303715884105728") >> a;
    istringstream("340282366920938463463374607431768211455") >> b;
    ASSERT_EQ(to_string(numeric_limits<int128_t>::min()), to_string(a));
    ASSERT_EQ(to_string(numeric_limits<uint128_t>::max()), to_string(b));
}