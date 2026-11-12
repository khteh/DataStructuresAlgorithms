#pragma once
#if 0
#include <compare>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#endif
using namespace std;
/*
 * Arbitrary-size unsigned integers, stored as base 10^9 "limbs", least significant first.
 * A limb is one element of the number: a uint32_t holding 0 .. 999,999,999, i.e. 9 decimal digits.
 * 10^9 is the largest power of 10 for which every limb value fits in a uint32_t (max 4,294,967,295),
 * and a limb product plus two limbs, (10^9 - 1)^2 + 2 (10^9 - 1) ~ 10^18, fits in a uint64_t (max ~1.8 x 10^19).
 *
 * Example: 123456789012345678901 = 123 x 10^18 + 456789012 x 10^9 + 345678901 -> {345678901, 456789012, 123}
 *
 * A valid BigNumber is non-empty, every limb is < BigNumberBase, and there are no leading zero limbs
 * (zero is {0}). Every function validates its BigNumber arguments and throws std::invalid_argument
 * if one is not valid, and every function returns a valid BigNumber.
 *
 * Functions:
 * 1. Conversions and comparison: BigFromNumber, BigFromString, BigToString and BigCompare.
 *    BigNumber is just a vector<uint32_t> alias, so it can’t have its own operators; that’s why it has a separate BigCompare function.
 *    vector’s built-in <=> compares element by element from index 0, which is the least significant limb, so it would give the wrong order for numbers.
 *    For example,124 <=> 223. Using vector's built-in <=> would return 124 > 223 as it compares index-0 (LSB) first. BigCompare compares from .size() - 1 and returns the right result 223 > 124.
 * 2. BigAdd.
 * 3. BigSubtract: throws std::domain_error if the result would be negative, since the numbers are unsigned.
 * 4. BigMultiply: works for any two numbers, so BigMultiply(b, b) replaces the earlier BigSquare.
 * 5. BigDivide: returns {quotient, remainder}, and throws std::domain_error when dividing by zero. Single-limb divisors use short division; longer ones use Knuth’s long-division algorithm, which works one quotient limb at a time.
 * 6. Validation: every function first checks its inputs with BigValidate and throws std::invalid_argument if a number is empty, has a limb of 10⁹ or more, or has leading zero limbs.
 *                BigFromString rejects anything other than the digits 0–9.
 */
using BigNumber = vector<uint32_t>; // BigNumber is just a vector<uint32_t> alias
inline constexpr uint64_t BigNumberBase = 1'000'000'000;
inline constexpr size_t BigNumberLimbDigits = 9;

void BigValidate(BigNumber const &);
BigNumber BigFromNumber(uint64_t);
BigNumber BigFromString(string_view);
string BigToString(BigNumber const &);
strong_ordering BigCompare(BigNumber const &, BigNumber const &);
BigNumber BigAdd(BigNumber const &, BigNumber const &);
BigNumber BigSubtract(BigNumber const &, BigNumber const &);
BigNumber BigMultiply(BigNumber const &, BigNumber const &);
pair<BigNumber, BigNumber> BigDivide(BigNumber const &, BigNumber const &);