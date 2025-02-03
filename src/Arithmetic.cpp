#include "Arithmetic.h"
template class Arithmetic<char>;
template class Arithmetic<int>;
template class Arithmetic<size_t>;
template class Arithmetic<long>;
template class Arithmetic<long long>;
template class Arithmetic<unsigned long long>;
template class Arithmetic<string>;
template class GCDExtendedEuclideanResult<char>;
template class GCDExtendedEuclideanResult<int>;
template class GCDExtendedEuclideanResult<size_t>;
template class GCDExtendedEuclideanResult<long>;
template class GCDExtendedEuclideanResult<long long>;
template class GCDExtendedEuclideanResult<unsigned long long>;
template <typename T>
GCDExtendedEuclideanResult<T>::GCDExtendedEuclideanResult()
	requires arithmetic_type<T>
	: gcd(0), x(0), y(0)
{
}
template <typename T>
GCDExtendedEuclideanResult<T>::GCDExtendedEuclideanResult(T gcd, T x, T y)
	requires arithmetic_type<T>
	: gcd(gcd), x(x), y(y)
{
}
template <typename T>
bool GCDExtendedEuclideanResult<T>::operator==(GCDExtendedEuclideanResult<T> &rhs)
	requires arithmetic_type<T>
{
	return gcd == rhs.gcd && x == rhs.x && y == rhs.y;
}
/* http://en.wikipedia.org/wiki/Greatest_common_divisor
 * the largest positive integer that divides the numbers without a remainder
 */
template <typename T>
T Arithmetic<T>::gcd_euclidean(T a, T b)
	requires arithmetic_type<T>
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
template <typename T>
GCDExtendedEuclideanResult<T> Arithmetic<T>::gcd_euclidean_extended(T a, T b)
	requires arithmetic_type<T>
{
	if (!(a % b))
	{ // a == b || !a
		return GCDExtendedEuclideanResult<T>(b, 0, 1);
	}
	GCDExtendedEuclideanResult<T> gcd = gcd_euclidean_extended(b, a % b);
	T y = gcd.x - (a / b) * gcd.y;
	T x = gcd.y;
	return GCDExtendedEuclideanResult<T>(gcd.gcd, x, y);
}
template <typename T>
T Arithmetic<T>::gcd(T a, T b)
	requires arithmetic_type<T>
{
	if (!a)
		return b;
	else if (!b)
		return a;
	else
		return a >= b ? gcd_euclidean(a, b) : gcd_euclidean(b, a);
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
template <typename T>
GCDExtendedEuclideanResult<T> Arithmetic<T>::gcd_extended(T a, T b)
	requires arithmetic_type<T>
{
	if (!a)
		return GCDExtendedEuclideanResult<T>(b, 0, 1);
	else if (!b)
		return GCDExtendedEuclideanResult<T>(a, 1, 0);
	else
		return a >= b ? gcd_euclidean_extended(a, b) : gcd_euclidean_extended(b, a);
}
/* http://en.wikipedia.org/wiki/Least_common_multiple */
/* The smallest positive integer that is divisible by both a and b.[1] If either a or b is 0, LCM(a, b) is defined to be zero. */
template <typename T>
T Arithmetic<T>::lcm(T a, T b)
	requires arithmetic_type<T>
{
	return (!a || !b) ? 0 : (a * b) / gcd(a, b);
}
/* https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
 * https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
 * How is Extended Algorithm Useful?
 * The extended Euclidean algorithm is particularly useful when a and b are coprime (or gcd is 1).
 * Since x is the modular multiplicative inverse of “a modulo b”, and y is the modular multiplicative inverse of “b modulo a”.
 * In particular, the computation of the modular multiplicative inverse is an essential step in RSA public-key encryption method.
 */
template <typename T>
T Arithmetic<T>::ModInverse(T num, T mod)
	requires arithmetic_type<T>
{
	GCDExtendedEuclideanResult<T> result = gcd_extended(num, mod);
	if (result.gcd != 1)
		throw invalid_argument("ModInverse does not exist for the input params");
	// m is added to handle negative x
	T modInverse = (result.y % mod + mod) % mod;
	return modInverse;
}
template <typename T>
T Arithmetic<T>::XOR(T n)
	requires arithmetic_type<T>
{
	return (n <= 1) ? n : n ^ XOR(n - 1);
}
template <typename T>
T Arithmetic<T>::ToggleSign(T a)
	requires arithmetic_type<T>
{
	T i, d = a < 0 ? 1 : -1;
	for (i = 0; a; i += d, a += d)
		;
	return i;
}
template <typename T>
T Arithmetic<T>::absolute(T a)
	requires arithmetic_type<T>
{
	return a > 0 ? a : ToggleSign(a);
}
template <typename T>
T Arithmetic<T>::SubtractWithPlusSign(T a, T b)
	requires arithmetic_type<T>
{
	return a + ToggleSign(b);
}
template <typename T>
T Arithmetic<T>::MultiplyWithPlusSign(T a, T b)
	requires arithmetic_type<T>
{
	if (b > a)
		return MultiplyWithPlusSign(b, a); // Just faster doing it the other way round
	T sum = 0;
	for (T i = absolute(b); i > 0; i--, sum += a)
		;
	return b < 0 ? ToggleSign(sum) : sum;
}
template <typename T>
T Arithmetic<T>::DivideWithPlusSign(T a, T b)
	requires arithmetic_type<T>
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
template <typename T>
T Arithmetic<T>::Divide(T dividend, T divisor)
	requires arithmetic_type<T>
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
	for (; dividend >= divisor; quotient++, dividend -= divisor)
		;
	return isNegative ? -quotient : quotient;
}
/*
 * x / y == x * y^(-1) == x * z (where z is multiplicative inverse of y).
 * y_inv = findMMI(y, M);
 * z = (x * y_inv) % M;
 */
template <typename T>
T Arithmetic<T>::Divide(T dividend, T divisor, T modulo)
	requires arithmetic_type<T>
{
	T y_inv = ModInverse(divisor, modulo);
	if (y_inv == -1)
		throw invalid_argument("Undefined divide with modulo operation!");
	return (dividend * y_inv) % modulo;
}
/* https://leetcode.com/problems/sum-of-two-integers/
 * 1 + 1 = 10b, 1 + 0 = 1b, 0 + 0 = 0b
 * Only 1 1 has carry
 * https://stackoverflow.com/questions/55615186/c-left-shift-overflow-for-negative-numbers
 * Left-shifting a negative value results in undefined behaviour. Use unsigned for bit manipulations.
 */
template <typename T>
T Arithmetic<T>::AddWithoutArithmetic(T sum, T carry)
	requires arithmetic_type<T>
{
	return !carry ? sum : AddWithoutArithmetic(sum ^ carry, (unsigned long long)(sum & carry) << 1);
}
template <typename T>
// Function for finding sum of larger numbers
string Arithmetic<T>::NumberStringSum(const string &str1, const string &str2)
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
template <typename T>
string Arithmetic<T>::NumberStringMultiplication(string &num1, string &num2)
{
	if (num1.empty() || num2.empty())
		return "0";
	bool isNegative = (num1[0] == '-' && num2[0] != '-') || (num1[0] != '-' && num2[0] == '-');
	if (num1[0] == '-')
		num1 = num1.substr(1);
	if (num2[0] == '-')
		num2 = num2.substr(1);
	/* Will keep the result number in vector in reverse order.
	 * [LSB,MSB]
	 */
	vector<long> result(num1.size() + num2.size(), 0);
	size_t i_n1 = 0, i_n2 = 0;
	// Go from right to left in num1 (bottom)
	for (int i = num1.size() - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';
		// To shift position to left after every multiplication of a digit in num2 (top)
		i_n2 = 0;
		// Go from right (LSB) to left (MSB) in num2
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
template <typename T>
T Arithmetic<T>::XorSequence(T l, T r)
	requires arithmetic_type<T>
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
template <typename T>
T Arithmetic<T>::SansaXor(vector<T> const &data)
	requires arithmetic_type<T>
{
	T result = 0;
	if (!(data.size() % 2))
		return 0;
	for (size_t i = 0; i < data.size(); i += 2)
		result ^= data[i];
	return result;
}
/* https://leetcode.com/problems/additive-number/
 * 100%
 * i: width of the first operand
 * j: width of the second operand
 * width of sum is max(i, j). So i must be <= half the input string size
 */
template <typename T>
bool Arithmetic<T>::IsAdditiveNumber(string const &str)
{
	for (size_t i = 1; i <= str.size() / 2; i++)
		for (size_t j = 1; max(i, j) <= str.size() - i - j; j++)
			if (CheckIfAdditiveSequence(i, j, str))
				return true;
	return false;
}
/*
 * 123581321
 * 1 2 3
 *   2 3 5
 *     3 5 8
 *       5 8 13
 *         8 13 21
 */
template <typename T>
bool Arithmetic<T>::CheckIfAdditiveSequence(size_t i, size_t j, string const &str)
{
	if ((str[0] == '0' && i > 1) || (str[i] == '0' && j > 1))
		return false;
	unsigned long long first, second;
	string sum;
	istringstream(str.substr(0, i)) >> first;
	istringstream(str.substr(i, j)) >> second;
	for (size_t k = i + j; k < str.size(); k += sum.size())
	{
		second = first + second;
		first = second - first;
		sum = to_string(second);
		if (str.substr(k, sum.size()) != sum)
			return false;
	}
	return true;
}
/*
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/
 * 100%
 */
template <typename T>
T Arithmetic<T>::ReversePolishNotation(vector<string> const &tokens)
	requires arithmetic_type<T>
{
	stack<T> numbers;
	for (size_t i = 0; i < tokens.size(); i++)
	{
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
				throw runtime_error("Invalid operator!");
			}
			numbers.push(num1);
		}
		else
		{
			T num;
			istringstream(tokens[i]) >> num;
			numbers.push(num);
		}
	}
	return !numbers.empty() ? numbers.top() : numeric_limits<T>::max();
}
template <typename T>
void Arithmetic<T>::NumberToVector(T number, vector<T> &digits)
	requires arithmetic_type<T>
{
	digits.clear();
	// Index 0: LSB
	if (!number)
		digits.push_back(0);
	for (; number > 0; number /= 10)
		digits.push_back(number % 10);
}
template <typename T>
T Arithmetic<T>::DigitsVectorToNumber(vector<T> const &digits)
	requires arithmetic_type<T>
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
template <typename T>
string Arithmetic<T>::DigitsVectorToNumberString(vector<T> const &digits)
	requires arithmetic_type<T>
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
	cout << oss.str() << endl;
	return oss.str();
}
template <typename T>
void Arithmetic<T>::NumberVectorsSum(vector<T> const &num1, vector<T> const &num2, vector<T> &result)
	requires arithmetic_type<T>
{
	result.clear();
#if 0
	T carry = 0;
	size_t i = 0, j = 0;
	for (; i < num1.size() && j < num2.size(); i++, j++)
	{
		// if (num1[i] < 0 || num1[i] > 9 || num2[j] < 0 || num2[j] > 9)
		//	throw runtime_error("Vector elements must be numeric digits within the range of [0:9]");
		T tmp = num1[i] + num2[j] + carry;
		carry = tmp / 10;
		result.push_back(tmp % 10);
	}
	for (; i < num1.size(); i++)
	{
		// if (num1[i] < 0 || num1[i] > 9)
		//	throw runtime_error("Vector elements must be numeric digits within the range of [0:9]");
		T tmp = num1[i] + carry;
		carry = tmp / 10;
		result.push_back(tmp % 10);
	}
	for (; j < num2.size(); j++)
	{
		// if (num2[j] < 0 || num2[j] > 9)
		//	throw runtime_error("Vector elements must be numeric digits within the range of [0:9]");
		T tmp = num2[j] + carry;
		carry = tmp / 10;
		result.push_back(tmp % 10);
	}
	if (carry)
		result.push_back(carry);
#endif
	for (size_t i = 0; i < max(num1.size(), num2.size()); i++)
	{
		T sum = 0;
		if (i < num1.size())
			sum += num1[i];
		if (i < num2.size())
			sum += num2[i];
		result.push_back(sum);
	}
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
template <typename T>
void Arithmetic<T>::NumberVectorsMultiplication(vector<T> const &num1, vector<T> const &num2, vector<T> &result)
	requires arithmetic_type<T>
{
	/* Will keep the result number in vector in reverse order.
	 * [LSB,MSB]
	 */
	result.clear();
	result.assign(num1.size() + num2.size(), 0);
	size_t i_n1 = 0, i_n2 = 0;
	// Go from left (LSB) to right (MSB) in num1 (bottom)
	for (size_t i = 0; i < num1.size(); i++)
	{
		T carry = 0;
		T n1 = num1[i];
		// To shift position to left after every multiplication of a digit in num2 (top)
		i_n2 = 0;
		// Go from right to left in num2
		for (size_t j = 0; j < num2.size(); j++)
		{
			// Take current digit of second number
			T n2 = num2[j];

			// Multiply with current digit of first number
			// and add result to previously stored result
			// at current position.
			T sum = n1 * n2 + result[i_n1 + i_n2] + carry;

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
template <typename T>
void Arithmetic<T>::NumberVectorsSquare(vector<T> const &num, vector<T> &result)
	requires arithmetic_type<T>
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