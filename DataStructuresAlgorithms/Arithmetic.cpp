#include "Arithmetic.h"
unsigned long long Arithmetic::XOR(unsigned long long n)
{
	return (n <= 1) ? n : n ^ XOR(n - 1);
}
long Arithmetic::ToggleSign(long a)
{
	long i, d = a < 0 ? 1 : -1;
	for (i = 0; a != 0; i += d, a += d)
		;
	return i;
}
long Arithmetic::absolute(long a)
{
	return a > 0 ? a : ToggleSign(a);
}
long Arithmetic::SubtractWithPlusSign(long a, long b)
{
	return a + ToggleSign(b);
}
long Arithmetic::MultiplyWithPlusSign(long a, long b)
{
	if (b > a)
		return MultiplyWithPlusSign(b, a); // Just faster doing it the other way round
	long sum = 0;
	for (long i = absolute(b); i > 0; i--, sum += a)
		;
	return b < 0 ? ToggleSign(sum) : sum;
}
long Arithmetic::DivideWithPlusSign(long a, long b)
{
	if (!b)
		throw runtime_error("Divide by zero exception");
	bool isNegative = (a < 0) ^ (b < 0);
	if (b == 1 || b == -1)
	{
		if (a == numeric_limits<int>::min())
#if defined(__GNUC__) || defined(__GNUG__)
			return isNegative ? numeric_limits<int>::min() : -a; // ToggleSign of 64-bit value takes very long time
#else
			return numeric_limits<int>::min();
#endif
		else if (a == numeric_limits<int>::max())
			return isNegative ? numeric_limits<int>::min() + 1 : numeric_limits<int>::max();
		if (a == numeric_limits<long>::min())
			return numeric_limits<long>::min();
		else if (a == numeric_limits<long>::max())
			return isNegative ? numeric_limits<long>::min() + 1 : numeric_limits<long>::max();
		if (isNegative)			   // result should be < 0
			return a < 0 ? a : -a; // ToggleSign of 64-bit value takes very long time
		return a < 0 ? -a : a;
	}
	long quotient;
	long divisor = ToggleSign(absolute(b)); // * -1
	long dividend = absolute(a);
	for (quotient = 0; dividend >= absolute(divisor); dividend += divisor, quotient++)
		;
	return isNegative ? -quotient : quotient;
}
long Arithmetic::divide(long dividend, long divisor)
{
	if (!divisor)
		throw runtime_error("Divide by zero exception");
	int quotient = 0;
	bool isNegative = (dividend < 0) ^ (divisor < 0);
	if (divisor == 1 || divisor == -1)
	{
		if (dividend == numeric_limits<int>::min())
			return isNegative ? numeric_limits<int>::min() : -dividend; // ToggleSign of 64-bit value takes very long time
		else if (dividend == numeric_limits<int>::max())
			return isNegative ? numeric_limits<int>::min() + 1 : numeric_limits<int>::max();
		if (dividend == numeric_limits<long>::min())
			return numeric_limits<long>::min();
		else if (dividend == numeric_limits<long>::max())
			return isNegative ? numeric_limits<long>::min() + 1 : numeric_limits<long>::max();
		if (isNegative)
			return dividend < 0 ? dividend : -dividend; // ToggleSign of 64-bit value takes very long time
		return dividend < 0 ? -dividend : dividend;
	}
	if (divisor < 0)
		divisor = -divisor;
	if (dividend < 0)
		dividend = -dividend;
	for (; dividend >= divisor; quotient++, dividend -= divisor)
		;
	return isNegative ? -quotient : quotient;
}
/* https://leetcode.com/problems/sum-of-two-integers/			   1
 * 1 + 1 = 10b, 1 + 0 = 1b, 0 + 0 = 0b
 * Only 1 1 has carry
 * https://stackoverflow.com/questions/55615186/c-left-shift-overflow-for-negative-numbers
 * Left-shifting a negative value results in undefined behaviour. Use unsigned for bit manipulations.
 */
long long Arithmetic::AddWithoutArithmetic(long long sum, long long carry)
{
	return !carry ? sum : AddWithoutArithmetic(sum ^ carry, (unsigned long long)(sum & carry) << 1);
}
// Function for finding sum of larger numbers
string Arithmetic::NumberStringSum(const string &str1, const string &str2)
{
	if (str1.empty() && !str2.empty())
		return str2;
	else if (!str1.empty() && str2.empty())
		return str1;
	else if (str1.empty() && str2.empty())
		return "";
	// Initially take carry zero
	int carry = 0;
	string::const_reverse_iterator it1 = str1.rbegin();
	string::const_reverse_iterator it2 = str2.rbegin();
	vector<char> result(max(str1.size(), str2.size()) + 1, '0');
	vector<char>::reverse_iterator it3 = result.rbegin();
	for (; !(it1 == str1.rend() && it2 == str2.rend());)
	{
		// Do school mathematics, compute sum of current digits and carry
		int sum = carry;
		if (it1 != str1.rend())
			sum += *it1 - '0';
		if (it2 != str2.rend())
			sum += *it2 - '0';
		*it3++ = (sum % 10) + '0';
		carry = sum / 10;
		if (it1 != str1.rend())
			it1++;
		if (it2 != str2.rend())
			it2++;
	}
	// Add remaining carry
	if (carry)
		*it3 = carry + '0';
	string str(result.begin(), result.end());
	return carry ? str : str.substr(1);
}
/*
  Multiplies str1 and str2, and prints result.
	  345 (n2)
	 x 76 (n1)
	 ----
	 2070 result: 0(3) 7(2) 0(2) 2(carry) n1: 0, n2: 3
	2415  result:      2(4) 2(3) 6(2)  2(carry) n1: 1, n2: 3
	-----
	26220
*/
string Arithmetic::NumberStringMultiplication(string &num1, string &num2)
{
	if (num1.empty() || num2.empty())
		return "0";
	bool isNegative = (num1[0] == '-' && num2[0] != '-') || (num1[0] != '-' && num2[0] == '-');
	if (num1[0] == '-')
		num1 = num1.substr(1);
	if (num2[0] == '-')
		num2 = num2.substr(1);

	// will keep the result number in vector in reverse order
	vector<long> result(num1.size() + num2.size(), 0);

	size_t i_n1 = 0, i_n2 = 0;
	// Go from right to left in num1 (bottom)
	for (int i = num1.size() - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';
		// To shift position to left after every multiplication of a digit in num2 (top)
		i_n2 = 0;
		// Go from right to left in num2
		for (int j = num2.size() - 1; j >= 0; j--)
		{
			// Take current digit of second number
			int n2 = num2[j] - '0';

			// Multiply with current digit of first number
			// and add result to previously stored result
			// at current position.
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

			// Carry for next iteration
			carry = sum / 10;

			// Store result
			result[i_n1 + i_n2] = sum % 10;

			i_n2++;
		}

		// store carry in next cell
		if (carry)
			result[i_n1 + i_n2] += carry;

		// To shift position to left after every multiplication of a digit in num1.
		i_n1++;
	}
	// Ignore '0's from the right (MSBs in reversed order)
	int i = result.size() - 1;
	for (; i >= 0 && !result[i]; i--)
		;
	// If all were '0's - means either both or one of num1 or num2 were '0'
	if (i < 0)
		return "0";
	// generate the result string
	ostringstream oss;
	if (isNegative)
		oss << '-';
	while (i >= 0)
		oss << result[i--];
	return oss.str();
}