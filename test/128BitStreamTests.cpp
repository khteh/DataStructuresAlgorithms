#include "pch.h"
using namespace std;
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