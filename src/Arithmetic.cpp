#include "pch.h"
#include "Arithmetic.h"
#ifdef __SIZEOF_INT128__
template class Arithmetic<int128_t>;
template class Arithmetic<uint128_t>;
template class GCDExtendedEuclideanResult<int128_t>;
template class GCDExtendedEuclideanResult<uint128_t>;
#endif
#if defined(_MSC_VER)
// The following are duplicates of int64_t on GNUC / GNUG
template class Arithmetic<size_t>;
template class Arithmetic<long>;
template class GCDExtendedEuclideanResult<size_t>;
template class GCDExtendedEuclideanResult<long>;
#endif
template class Arithmetic<char>;
template class Arithmetic<int>;
template class Arithmetic<int64_t>;
template class Arithmetic<uint64_t>;
template class GCDExtendedEuclideanResult<char>;
template class GCDExtendedEuclideanResult<int>;
template class GCDExtendedEuclideanResult<int64_t>;
template class GCDExtendedEuclideanResult<uint64_t>;
template <arithmetic_type T>
GCDExtendedEuclideanResult<T>::GCDExtendedEuclideanResult()
	: gcd(0), x(0), y(0)
{
}
template <arithmetic_type T>
GCDExtendedEuclideanResult<T>::GCDExtendedEuclideanResult(T gcd, T x, T y)
	: gcd(gcd), x(x), y(y)
{
}
template <arithmetic_type T>
bool GCDExtendedEuclideanResult<T>::operator==(GCDExtendedEuclideanResult<T> const &rhs) const
{
	return gcd == rhs.gcd && x == rhs.x && y == rhs.y;
}
template <arithmetic_type T>
T Arithmetic<T>::gcd(T a, T b)

{
	if (!a)
		return b;
	else if (!b)
		return a;
	else
		return a >= b ? gcd_euclidean(a, b) : gcd_euclidean(b, a);
}
/* http://en.wikipedia.org/wiki/Least_common_multiple
 * The smallest positive integer that is divisible by both a and b.[1] If either a or b is 0, LCM(a, b) is defined to be zero.
 */
template <arithmetic_type T>
T Arithmetic<T>::lcm(T a, T b)
{
	return (!a || !b) ? 0 : (a * b) / gcd(a, b);
}
/* http://en.wikipedia.org/wiki/Greatest_common_divisor
 * the largest positive integer that divides the numbers without a remainder
 */
template <arithmetic_type T>
T Arithmetic<T>::gcd_euclidean(T a, T b)
{
	return !(a % b) ? b : gcd_euclidean(b, a % b);
}
/*
https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
Extended Euclidean algorithm also finds integer coefficients x and y such that: ax + by = gcd(a, b)
ax + by = gcd(a, b)
gcd(a, b) = gcd(b, a % b)
gcd(b, a % b) = b*x1 + (a % b)y1
ax + by = b*x1 + (a % b)y1
ax + by = b*x1 + (a - (a/b)*b)y1
ax + by = b(x1 - (a/b) * y1) + a*y1

Comparing LHS and RHS,
y = x1 – (a/b) * y1
x = y1
*/
template <arithmetic_type T>
GCDExtendedEuclideanResult<T> Arithmetic<T>::gcd_euclidean_extended(T a, T b)
{
	if (!(a % b))
		// a == b || !a
		return GCDExtendedEuclideanResult<T>(b, 0, 1);
	GCDExtendedEuclideanResult<T> gcd = gcd_euclidean_extended(b, a % b);
	T y = gcd.x - (a / b) * gcd.y;
	T x = gcd.y;
	return GCDExtendedEuclideanResult<T>(gcd.gcd, x, y);
}
/*
https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
Extended Euclidean algorithm also finds integer coefficients x and y such that: ax + by = gcd(a, b)
ax + by = gcd(a, b)
gcd(a, b) = gcd(b, a % b)
gcd(b, a % b) = b*x1 + (a % b)y1
ax + by = b*x1 + (a % b)y1
ax + by = b*x1 + (a - (a/b)*b)y1
ax + by = b(x1 - (a/b) * y1) + a*y1

Comparing LHS and RHS,
y = x1 – (a/b) * y1
x = y1
*/
template <arithmetic_type T>
GCDExtendedEuclideanResult<T> Arithmetic<T>::gcd_extended(T a, T b)
{
	if (!a)
		return GCDExtendedEuclideanResult<T>(b, 0, 1);
	else if (!b)
		return GCDExtendedEuclideanResult<T>(a, 1, 0);
	else
		return a >= b ? gcd_euclidean_extended(a, b) : gcd_euclidean_extended(b, a);
}
/* https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
 * https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
 * How is Extended Algorithm Useful?
 * The extended Euclidean algorithm is particularly useful when a and b are coprime (or gcd is 1).
 * Since x is the modular multiplicative inverse of “a modulo b”, and y is the modular multiplicative inverse of “b modulo a”.
 * In particular, the computation of the modular multiplicative inverse is an essential step in RSA public-key encryption method.
 */
template <arithmetic_type T>
T Arithmetic<T>::ModInverse(T num, T mod)
{
	GCDExtendedEuclideanResult<T> result = gcd_extended(num, mod);
	if (result.gcd != 1)
		throw invalid_argument("ModInverse does not exist for the input params");
	// m is added to handle negative x. Due to the difference in implementation, the 'x' and 'y' are flipped based on the reference URL.
	T modInverse = (result.y % mod + mod) % mod;
	return modInverse;
}
template <arithmetic_type T>
T Arithmetic<T>::XOR(T n)
{
	return (n <= 1) ? n : n ^ XOR(n - 1);
}
template <arithmetic_type T>
T Arithmetic<T>::ToggleSign(T a)
{
	T i, d = a < 0 ? 1 : -1;
	for (i = 0; a; i += d, a += d)
		;
	return i;
}
template <arithmetic_type T>
T Arithmetic<T>::absolute(T a)
{
	return a > 0 ? a : ToggleSign(a);
}
template <arithmetic_type T>
T Arithmetic<T>::SubtractWithPlusSign(T a, T b)
{
	return a + ToggleSign(b);
}
template <arithmetic_type T>
T Arithmetic<T>::MultiplyWithPlusSign(T a, T b)
{
	if (b > a)
		return MultiplyWithPlusSign(b, a); // Just faster doing it the other way round
	T sum = 0;
	for (T i = absolute(b); i > 0; i--, sum += a)
		;
	return b < 0 ? ToggleSign(sum) : sum;
}
template <arithmetic_type T>
T Arithmetic<T>::DivideWithPlusSign(T a, T b)
{
#ifdef _MSC_VER
#pragma warning(disable : 4146)
#endif
	if (!b)
		throw invalid_argument("Divide by zero exception");
	bool isNegative = (a < 0) ^ (b < 0);
	if (b == 1 || b == -1)
	{
		if (a == numeric_limits<make_signed_t<T>>::min())
#if defined(__GNUC__) || defined(__GNUG__)
			return isNegative ? numeric_limits<make_signed_t<T>>::min() : -a; // ToggleSign of 64-bit value takes very long time
#else
			return numeric_limits<make_signed_t<T>>::min();
#endif
		else if (a == numeric_limits<make_signed_t<T>>::max())
			return isNegative ? numeric_limits<make_signed_t<T>>::min() + 1 : numeric_limits<make_signed_t<T>>::max();
		if (a == numeric_limits<T>::min())
			return numeric_limits<T>::min();
		else if (a == numeric_limits<T>::max())
			return isNegative ? numeric_limits<T>::min() + 1 : numeric_limits<T>::max();
		if (isNegative)			   // result should be < 0
			return a < 0 ? a : -a; // ToggleSign of 64-bit value takes very T time
		return a < 0 ? -a : a;
	}
	T quotient;
	T divisor = ToggleSign(absolute(b)); // * -1
	T dividend = absolute(a);
	for (quotient = 0; dividend >= absolute(divisor); dividend += divisor, quotient++)
		;
	return isNegative ? -quotient : quotient;
}
template <arithmetic_type T>
T Arithmetic<T>::Divide(T dividend, T divisor)
{
#ifdef _MSC_VER
#pragma warning(disable : 4146)
#endif
	if (!divisor)
		throw invalid_argument("Divide by zero exception");
	bool isNegative = (dividend < 0) ^ (divisor < 0);
	if (divisor == 1 || divisor == -1)
	{
		if (dividend == numeric_limits<make_signed_t<T>>::min())
			return isNegative ? numeric_limits<make_signed_t<T>>::min() : -dividend; // ToggleSign of 64-bit value takes very long time
		else if (dividend == numeric_limits<make_signed_t<T>>::max())
			return isNegative ? numeric_limits<make_signed_t<T>>::min() + 1 : numeric_limits<make_signed_t<T>>::max();
		if (dividend == numeric_limits<T>::min())
			return numeric_limits<T>::min();
		else if (dividend == numeric_limits<T>::max())
			return isNegative ? numeric_limits<T>::min() + 1 : numeric_limits<T>::max();
		if (isNegative)
			return dividend < 0 ? dividend : -dividend; // ToggleSign of 64-bit value takes very T time
		return dividend < 0 ? -dividend : dividend;
	}
	if (divisor < 0)
		divisor = -divisor;
	if (dividend < 0)
		dividend = -dividend;
	T quotient = 0;
	for (; dividend >= divisor; quotient++, dividend -= divisor)
		;
	return isNegative ? -quotient : quotient;
}
/* https://www.geeksforgeeks.org/modular-division/
 * x / y == x * y^(-1) == x * z (where z is multiplicative inverse of y).
 * y_inv = findMMI(y, M);
 * z = (x * y_inv) % M;
 *
 * Input  : a  = 8, b = 4, m = 5
Output : 2

Input  : a  = 8, b = 3, m = 5
Output : 1
Note that (1*3)%5 is same as 8%5

Input  : a  = 11, b = 4, m = 5
Output : 4
Note that (4*4)%5 is same as 11%5

Input  : a  = 15, b = 7, m = 11
Output : 10
Note that (10*7)%11 is same as 15%11

Input  : a  = 23, b = 11, m = 17
Output : 16
Note that (16*11)%17=6 is same as 23%17
 */
template <arithmetic_type T>
T Arithmetic<T>::Divide(T dividend, T divisor, T modulo)
{
	T y_inv = ModInverse(divisor, modulo);
	if (y_inv == -1)
		throw runtime_error("Undefined divide with modulo operation!");
	return (dividend * y_inv) % modulo;
}
/* https://leetcode.com/problems/sum-of-two-integers/
 * 1 + 1 = 10b, 1 + 0 = 1b, 0 + 0 = 0b
 * Only 1 1 has carry
 * https://stackoverflow.com/questions/55615186/c-left-shift-overflow-for-negative-numbers
 * Left-shifting a negative value results in undefined behaviour. Use unsigned for bit manipulations.
 *
 * 1+1:
 * sum 1, carry 1
 * sum^carry = 0, (sum & carry) << 1 = 0x10
 *
 * sum 0 carry 0x10
 * sum ^ carry=0x10, (sum & carry) << 1 = 0 => return 0x10
 *
 * 1+0:
 * sum 1, carry 0 => return 1
 *
 * 0+1:
 * sum 0, carry 1
 * sum^carry = 1 (sum & carry) << 1 = 0 => return 1
 */
template <arithmetic_type T>
T Arithmetic<T>::AddWithoutArithmetic(T sum, T carry)
{
	return !carry ? sum : AddWithoutArithmetic(sum ^ carry, (uint64_t)(sum & carry) << 1);
}
/*
 * https://leetcode.com/problems/sqrtx/description/
 * 100%
 */
template <arithmetic_type T>
T Arithmetic<T>::Sqrt(T x)
	requires unsigned_integral<T>
{
	T start = 2, end = x;
	for (; start <= end;)
	{
		uint64_t mid = start + (end - start) / 2 + (end - start) % 2;
		if ((mid * mid) <= x)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return end;
}
/*
 * https://www.hackerrank.com/challenges/xor-se/problem
 * 100%
 * i	data[i]			result(data[i] ^ data[i-1])
 * 0	0(same as i)	0(same as i)
 * 1	1(always 1)		1(same as i)
 * 2	3(always i+1)	2(Always 2)
 * 3	0(always 0)		2(Always 2)
 *
 * 4	4(same as i)	6(Always i+2)
 * 5	1(always 1)		7(Always i+2)
 * 6	7(always i+1)	0(Always 0)
 * 7	0(always 0)		0(Always 0)
 *
 * 8	8(same as i)	8(same as i)
 * 9	1(always 1)		9(same as i)
 * 10	11(always i+1)	2(Always 2)
 * 11	0(always 0)		2(Always 2)
 *
 * 12	12(same as i)	14(Always i+2)
 * 13	1(always 1)		15(Always i+2)
 * 14	15(always i+1)	0(Always 0)
 * 15	0(always 0)		0(Always 0)
 *
 * 16	16(same as i)	16(same as i)
 * 17	1(always 1)		17(same as i)
 * 18	19(always i+1)	2(Always 2)
 * 19	0(always 0)		2(Always 2)
 *
 * 20	20(same as i)	22(Always i+2)
 * 21	1(always 1)		23(Always i+2)
 * 22	23(always i+1)	0(Always 0)
 * 23	0(always 0)		0(Always 0)
 *
 * 24	24(same as i)	24(same as i)
 * 25	1(always 1)		25(same as i)
 * 26	27(always i+1)	2(Always 2)
 * 27	0(always 0)		2(Always 2)
 *
 * Solution: generate result[0, l-1] and result[0, r]
 * final result = data[0, l-1] ^ data[0, r]. It will cancel out the accumulated xor from 0 too l-1
 */
template <arithmetic_type T>
T Arithmetic<T>::XorSequence(T l, T r)
{
	size_t left = 0, right = 0;
	if (l > 0)
		l--;
	switch (l % 8)
	{
	case 0:
	case 1:
		left = l;
		break;
	case 2:
	case 3:
		left = 2;
		break;
	case 4:
	case 5:
		left = l + 2;
		break;
	case 6:
	case 7:
		left = 0;
		break;
	}
	switch (r % 8)
	{
	case 0:
	case 1:
		right = r;
		break;
	case 2:
	case 3:
		right = 2;
		break;
	case 4:
	case 5:
		right = r + 2;
		break;
	case 6:
	case 7:
		right = 0;
		break;
	}
	return left ^ right;
}
/* https://www.hackerrank.com/challenges/sansa-and-xor/problem?isFullScreen=true
If the length of the arr is even the result will always cancel out.
When you get all the sublists you will notice that an element at even position exists odd times in all of the sublists and vice versa, an element at odd position exists even times in all of the subslists.
For example: [1,2,3] has the following sublists = [1],[1,2],[1,2,3],[2],[2,3],[3], the one appears 3 times, the 2 appears 4 times and the 3 appears 3 times.
This means that the elements that are on odd positions will cancel out, and we only need to take into consideration the ones that are on even positions, thus we only need to XOR the elements on the array stepping by 2.
100%
 */
template <arithmetic_type T>
T Arithmetic<T>::SansaXor(vector<T> const &data)
{
	T result = 0;
	if (!(data.size() % 2))
		return 0;
	for (size_t i = 0; i < data.size(); i += 2)
		result ^= data[i];
	return result;
}
/*
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/
 * 100%
 */
template <arithmetic_type T>
T Arithmetic<T>::ReversePolishNotation(vector<string> const &tokens)
{
	stack<T> numbers;
	for (size_t i = 0; i < tokens.size(); i++)
		if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
		{
			T num2 = numbers.top();
			numbers.pop();
			T num1 = numbers.top();
			numbers.pop();
			switch (tokens[i][0])
			{
			case '+':
				num1 += num2;
				break;
			case '-':
				num1 -= num2;
				break;
			case '*':
				num1 *= num2;
				break;
			case '/':
				num1 /= num2;
				break;
			default:
				throw invalid_argument("Invalid operator!");
			}
			numbers.push(num1);
		}
		else
		{
			T num;
			istringstream(tokens[i]) >> num;
			numbers.push(num);
		}
	return !numbers.empty() ? numbers.top() : numeric_limits<T>::max();
}
template <arithmetic_type T>
void Arithmetic<T>::NumberToVector(T number, vector<T> &digits)
{
	digits.clear();
	// Index 0: LSB
	if (!number)
		digits.push_back(0);
	for (; number > 0; number /= 10)
		digits.push_back(number % 10);
}
template <arithmetic_type T>
T Arithmetic<T>::DigitsVectorToNumber(vector<T> const &digits)
{
	T result = 0;
	// Index 0: LSB
	for (typename vector<T>::const_reverse_iterator it = digits.rbegin(); it != digits.rend(); it++)
	{
		result += *it;
		result *= 10;
	}
	result /= 10; // Remove trailing 0
	return result;
}
template <arithmetic_type T>
string Arithmetic<T>::DigitsVectorToNumberString(vector<T> const &digits)
{
	bool skip = true;
	ostringstream oss;
	// Index 0: LSB
	for (typename vector<T>::const_reverse_iterator it = digits.rbegin(); it != digits.rend(); it++)
		if (!skip || *it > 0)
		{
			oss << to_string(*it);
			skip = false;
		}
	return oss.str();
}
template <arithmetic_type T>
void Arithmetic<T>::NumberVectorsSum(vector<T> const &num1, vector<T> const &num2, vector<T> &result)
{
	result.clear();
	T carry = 0;
	size_t i = 0, j = 0;
	for (; i < num1.size() && j < num2.size(); i++, j++)
	{
		if (num1[i] < 0 || num1[i] > 9 || num2[j] < 0 || num2[j] > 9)
			throw runtime_error("Vector elements must be numeric digits within the range of [0:9]");
		T tmp = num1[i] + num2[j] + carry;
		carry = tmp / 10;
		result.push_back(tmp % 10);
	}
	for (; i < num1.size(); i++)
	{
		if (num1[i] < 0 || num1[i] > 9)
			throw runtime_error("Vector elements must be numeric digits within the range of [0:9]");
		T tmp = num1[i] + carry;
		carry = tmp / 10;
		result.push_back(tmp % 10);
	}
	for (; j < num2.size(); j++)
	{
		if (num2[j] < 0 || num2[j] > 9)
			throw runtime_error("Vector elements must be numeric digits within the range of [0:9]");
		T tmp = num2[j] + carry;
		carry = tmp / 10;
		result.push_back(tmp % 10);
	}
	if (carry)
		result.push_back(carry);
}
/*
  456
x 123
-----
 1368
 912
456
-----
56088

   456
x  456
------
  2736
 2280
1824
------
207936

i:0
r: [42 60 48
i:1
r: [42 60 (25+48) 40]
i:2
r: [42 60 73 40 16]

  Multiplies num1 and num2, and prints result.
	  345 (n2)
	 x 76 (n1)
	 ----
	 2070 result: 0(3) 7(2) 0(2) 2(carry) n1: 0, n2: 3
	2415  result:      2(4) 2(3) 6(2)  2(carry) n1: 1, n2: 3
	-----
	26220
*/
template <arithmetic_type T>
void Arithmetic<T>::NumberVectorsMultiplication(vector<T> const &num1, vector<T> const &num2, vector<T> &result)
{
	/* Will keep the result number in vector in reverse order.
	 * [LSB,MSB]
	 */
	vector<T> tmpResult;
	result.clear();
	for (size_t i = 0; i < num1.size(); i++)
	{
		T carry = 0;
		vector<T> tmp;
		for (long k = i; k > 0; k--)
			tmp.push_back(0);
		for (size_t j = 0; j < num2.size(); j++)
		{
			if (num1[i] < 0 || num1[i] > 9 || num2[j] < 0 || num2[j] > 9)
				throw runtime_error("Vector elements must be numeric digits within the range of [0:9]");
			T tmp1 = num1[i] * num2[j] + carry;
			carry = tmp1 / 10;
			tmp.push_back(tmp1 % 10);
		}
		if (carry)
			tmp.push_back(carry);
		NumberVectorsSum(tmp, tmpResult, result);
		tmpResult = result;
	}
}
/*
  Multiplies num1 and num2, and prints result.
	  345 (n2)
	x 345 (n1)
	 ----
	 1725 result: 5(2) 2(2) 7(1) 1(carry) n1: 0, n2: 3
	1380  result:      0(2) 8(1) 3(1)  1(carry) n1: 1, n2: 3
   1035   result:           5(1) 3(1)  0(1)  1(carry) n1: 2, n2: 3
	-----
   119025

num: 345^2 = 119025
i:  0
j:  0 1 2
tmp:25 40 30
r:  [25 40 30]

i:  1
j:  1 2
tmp:16 24
r:  [25 40 46 24]

i:  2
j:  2
tmp:9
r:  [25 40 46 24 9]
*/
#if 0
template <arithmetic_type T>
void Arithmetic<T>::NumberVectorsSquare(vector<T> const &num, vector<T> &result)
	
{
	result.clear();
	result.assign(2 * num.size(), 0);
	T carry - 0;
	for (size_t i = 0; i < num.size(); i++)
		for (size_t j = i; j < num.size(); j++)
		{
			T tmp = num[i] * num[j];
		}
}
#endif