#include "pch.h"
#include "BigNumber.h"
using namespace std;
namespace
{
	// Remove leading zero limbs, keeping at least one limb
	void Trim(BigNumber &number)
	{
		while (number.size() > 1 && !number.back())
			number.pop_back();
	}
	// number * factor, for 0 <= factor < BigNumberBase. The result may have a leading zero limb.
	BigNumber MultiplySmall(BigNumber const &number, uint64_t factor)
	{
		BigNumber result;
		result.reserve(number.size() + 1);
		uint64_t carry = 0;
		for (uint32_t limb : number)
		{
			uint64_t current = limb * factor + carry;
			result.push_back(static_cast<uint32_t>(current % BigNumberBase));
			carry = current / BigNumberBase;
		}
		result.push_back(static_cast<uint32_t>(carry));
		return result;
	}
	// {number / divisor, number % divisor}, for 0 < divisor < BigNumberBase
	pair<BigNumber, uint64_t> DivideSmall(BigNumber const &number, uint64_t divisor)
	{
		BigNumber quotient(number.size(), 0);
		uint64_t remainder = 0;
		for (size_t i = number.size(); i-- > 0;) // Most significant limb first, as in long division by hand
		{
			uint64_t current = remainder * BigNumberBase + number[i]; // < divisor * BigNumberBase <= 10^18
			quotient[i] = static_cast<uint32_t>(current / divisor);
			remainder = current % divisor;
		}
		Trim(quotient);
		return {quotient, remainder};
	}
}
/*
 * Throws std::invalid_argument unless number is a valid BigNumber: non-empty, every limb < BigNumberBase,
 * and no leading zero limbs.
 */
void BigValidate(BigNumber const &number)
{
	if (number.empty())
		throw invalid_argument("BigNumber: empty: zero is {0}");
	for (size_t i = 0; i < number.size(); i++)
		if (number[i] >= BigNumberBase)
			throw invalid_argument("BigNumber: limb " + to_string(i) + " is " + to_string(number[i]) + ", must be < " + to_string(BigNumberBase));
	if (number.size() > 1 && !number.back())
		throw invalid_argument("BigNumber: leading zero limb");
}
BigNumber BigFromNumber(uint64_t number)
{
	BigNumber result;
	do
	{
		result.push_back(static_cast<uint32_t>(number % BigNumberBase));
		number /= BigNumberBase;
	} while (number);
	return result;
}
/*
 * From a decimal string: one or more digits '0'-'9', nothing else. Leading zeros are allowed.
 * Throws std::invalid_argument otherwise.
 */
BigNumber BigFromString(string_view decimal)
{
	if (decimal.empty())
		throw invalid_argument("BigFromString: empty string");
	for (char c : decimal)
		if (c < '0' || c > '9')
			throw invalid_argument("BigFromString: invalid character '" + string(1, c) + "' in \"" + string(decimal) + "\"");
	BigNumber result;
	result.reserve(decimal.size() / BigNumberLimbDigits + 1);
	// Groups of 9 digits from the right: each group is one limb
	for (size_t end = decimal.size(); end > 0;)
	{
		size_t begin = end > BigNumberLimbDigits ? end - BigNumberLimbDigits : 0;
		uint32_t limb = 0;
		for (size_t i = begin; i < end; i++)
			limb = limb * 10 + static_cast<uint32_t>(decimal[i] - '0');
		result.push_back(limb);
		end = begin;
	}
	Trim(result);
	return result;
}
string BigToString(BigNumber const &number)
{
	BigValidate(number);
	string result = to_string(number.back()); // Most significant limb: no leading zeros
	char limb[BigNumberLimbDigits + 1];
	for (size_t i = number.size() - 1; i-- > 0;)
	{
		snprintf(limb, sizeof limb, "%09u", number[i]); // Every other limb: exactly 9 digits, e.g. 5 -> 000000005
		result += limb;
	}
	return result;
}
strong_ordering BigCompare(BigNumber const &a, BigNumber const &b)
{
	BigValidate(a);
	BigValidate(b);
	if (a.size() != b.size()) // No leading zero limbs: more limbs means a larger number
		return a.size() <=> b.size();
	for (size_t i = a.size(); i-- > 0;)
		if (a[i] != b[i])
			return a[i] <=> b[i];
	return strong_ordering::equal;
}
BigNumber BigAdd(BigNumber const &a, BigNumber const &b)
{
	BigValidate(a);
	BigValidate(b);
	BigNumber result;
	result.reserve(max(a.size(), b.size()) + 1);
	uint64_t carry = 0;
	for (size_t i = 0; i < max(a.size(), b.size()) || carry; i++)
	{
		uint64_t current = carry + (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
		result.push_back(static_cast<uint32_t>(current % BigNumberBase));
		carry = current / BigNumberBase;
	}
	return result;
}
/*
 * a - b. Throws std::domain_error if a < b: a BigNumber is unsigned, so the result can't be negative.
 */
BigNumber BigSubtract(BigNumber const &a, BigNumber const &b)
{
	if (BigCompare(a, b) == strong_ordering::less) // BigCompare also validates a and b
		throw domain_error("BigSubtract: a < b, the result would be negative");
	BigNumber result(a.size());
	int64_t borrow = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		int64_t difference = (int64_t)a[i] - (i < b.size() ? (int64_t)b[i] : 0) - borrow;
		borrow = difference < 0;
		result[i] = static_cast<uint32_t>(difference + (borrow ? (int64_t)BigNumberBase : 0)); // Borrow 10^9 from the next limb
	}
	Trim(result);
	return result;
}
/*
 * Schoolbook multiplication: every limb of a times every limb of b, O(|a| x |b|).
 * Each product is added straight into its place in the result, with no temporary rows.
 */
BigNumber BigMultiply(BigNumber const &a, BigNumber const &b)
{
	BigValidate(a);
	BigValidate(b);
	BigNumber result(a.size() + b.size(), 0);
	for (size_t i = 0; i < a.size(); i++)
	{
		uint64_t carry = 0, ai = a[i];
		for (size_t j = 0; j < b.size(); j++)
		{
			uint64_t current = result[i + j] + ai * b[j] + carry; // <= (10^9 - 1)^2 + 2 (10^9 - 1): fits in uint64_t
			result[i + j] = static_cast<uint32_t>(current % BigNumberBase);
			carry = current / BigNumberBase;
		}
		result[i + b.size()] = static_cast<uint32_t>(carry); // Not written by any earlier row
	}
	Trim(result);
	return result;
}
/*
 * {dividend / divisor, dividend % divisor}. Throws std::domain_error if divisor is 0.
 * Long division, one quotient limb at a time: Knuth, The Art of Computer Programming Vol. 2, 4.3.1, Algorithm D.
 * 1. Normalize: multiply both numbers by d = Base / (top limb of divisor + 1), so the divisor's top limb is
 *    >= Base / 2. That makes the estimate in step 2 at most 2 too large. The quotient doesn't change,
 *    and the remainder is divided by d at the end.
 * 2. Estimate each quotient limb from the top two limbs of the remainder and the top limb of the divisor,
 *    then correct it with the divisor's second limb. After that it is exact, or 1 too large (rare).
 * 3. Subtract estimate x divisor from the remainder. If that goes negative, the estimate was 1 too large:
 *    decrease it and add the divisor back.
 * O(|dividend| x |divisor|)
 */
pair<BigNumber, BigNumber> BigDivide(BigNumber const &dividend, BigNumber const &divisor)
{
	BigValidate(dividend);
	BigValidate(divisor);
	if (divisor.size() == 1 && !divisor[0])
		throw domain_error("BigDivide: division by zero");
	if (BigCompare(dividend, divisor) == strong_ordering::less)
		return {BigNumber{0}, dividend};
	if (divisor.size() == 1) // Single-limb divisor: short division
	{
		auto [quotient, remainder] = DivideSmall(dividend, divisor[0]);
		return {quotient, BigFromNumber(remainder)};
	}
	size_t n = divisor.size(), m = dividend.size() - n;
	uint64_t d = BigNumberBase / (divisor.back() + 1);
	BigNumber u = MultiplySmall(dividend, d), v = MultiplySmall(divisor, d); // u: m + n + 1 limbs
	v.pop_back();															 // v keeps n limbs: d was chosen so it doesn't grow
	BigNumber quotient(m + 1, 0);
	for (size_t j = m + 1; j-- > 0;)
	{
		// Step 2: estimate this quotient limb
		uint64_t top = u[j + n] * BigNumberBase + u[j + n - 1]; // < 10^18
		uint64_t qhat = top / v[n - 1], rhat = top % v[n - 1];
		while (qhat >= BigNumberBase || qhat * v[n - 2] > rhat * BigNumberBase + u[j + n - 2])
		{
			qhat--;
			rhat += v[n - 1];
			if (rhat >= BigNumberBase)
				break;
		}
		// Step 3: u[j .. j+n] -= qhat * v
		int64_t borrow = 0;
		uint64_t carry = 0;
		for (size_t i = 0; i < n; i++)
		{
			uint64_t product = qhat * v[i] + carry;
			carry = product / BigNumberBase;
			int64_t difference = (int64_t)u[i + j] - (int64_t)(product % BigNumberBase) - borrow;
			borrow = difference < 0;
			u[i + j] = static_cast<uint32_t>(difference + (borrow ? (int64_t)BigNumberBase : 0));
		}
		int64_t top_difference = (int64_t)u[j + n] - (int64_t)carry - borrow;
		if (top_difference < 0) // qhat was 1 too large: add v back
		{
			qhat--;
			carry = 0;
			for (size_t i = 0; i < n; i++)
			{
				uint64_t sum = (uint64_t)u[i + j] + v[i] + carry;
				u[i + j] = static_cast<uint32_t>(sum % BigNumberBase);
				carry = sum / BigNumberBase;
			}
			top_difference += static_cast<int64_t>(carry); // Back to 0: the remainder is now < v
		}
		u[j + n] = static_cast<uint32_t>(top_difference);
		quotient[j] = static_cast<uint32_t>(qhat);
	}
	Trim(quotient);
	u.resize(n); // The remainder is in the low n limbs, still multiplied by d
	Trim(u);
	return {quotient, DivideSmall(u, d).first};
}
