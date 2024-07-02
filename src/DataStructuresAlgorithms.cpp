#include "stdafx.h"
#include "DataStructuresAlgorithms.h"
namespace ranges = std::ranges;
using namespace oneapi::tbb;
long **my2DAlloc(long rows, long cols)
{
	size_t header = rows * sizeof(long *);			// Store the row pointers [i]
	size_t data = rows * cols * sizeof(long);		// Store the data
	long **rowptr = (long **)malloc(header + data); // row pointers + data buffers
	long *dataptr = (long *)(rowptr + rows);		// Pointer arithmetic to get the first location of data buffer
	for (int i = 0; i < rows; i++)
		rowptr[i] = dataptr + i * cols;
	return rowptr;
}
long ***my3DAlloc(long rows, long cols, long heights)
{
	size_t header = rows * sizeof(long *) + rows * cols * sizeof(long *); // Store the row pointers [i] and every cell of the 2D-plane is pointer to the Z-buffer [i][j]
	size_t data = rows * cols * heights * sizeof(long);					  // data
	long ***ptrs = (long ***)malloc(header + data);						  // row pointers + 2-D plane of pointers to Z-plane data
	long **columns = (long **)(ptrs + rows);							  // Pointer arithmetic to get the first location of 2D plane of Z-plane pointers [i][j]
	long *dataPtr = (long *)(ptrs + rows + rows * cols);				  // Pointer arithmetic to get the first location of data buffer
	for (long i = 0; i < rows; i++)
	{
		ptrs[i] = columns + i * cols;
		for (long j = 0; j < cols; j++)
			ptrs[i][j] = dataPtr + i * cols * heights + j * heights;
	}
	return ptrs;
}
void testPointerReference(int *&ptr)
{
	free(ptr);
	ptr = (int *)malloc(101 * sizeof(int));
	memset(ptr, 0xabababab, 101 * sizeof(int)); // XXX: sizeof(int*) is 8 bytes on x64!!!
}
long Min(long a, long b)
{
	long delta = b - a;
	long sign = (delta >> 31) & 1;
	// b > a: sign = 0: returns a
	// b < a: sign = 1: returns a - (a - b) = b
	return a - sign * (a - b);
}
long Max(long a, long b)
{
	long delta = a - b;
	long sign = (delta >> 31) & 1;
	// a > b: sign = 0 => return a
	// a < b: sign = 1 => return a - (a - b) = b
	return a - sign * (a - b);
}
float MachineEpsilon(float value)
{
	thirty_two_bit f;
	f.f = value;
	f.l++;
	return f.f - value;
}
double MachineEpsilon(double value)
{
	sixty_four_bit d;
	d.d = value;
	d.ll++;
	return d.d - value;
}
float FloatMachineEpsilonApproximation()
{
	float e = 1.0;
	while ((1 + 0.5 * e) != 1.0)
		e *= 0.5;
	return e;
}
double MachineEpsilonApproximation()
{
	double e = 1.0;
	while ((1 + 0.5 * e) != 1.0)
		e *= 0.5;
	return e;
}
/* Assume ASCII character set */
bool isUniqueString(string const &str)
{
	size_t i;
	bool char_set[256];
	for (i = 0; i < 256; i++)
		char_set[i] = false;
	for (i = 0; i < str.length(); i++)
	{
		if (char_set[str[i]])
			return false;
		char_set[str[i]] = true;
	}
	return true;
}
vector<string> findUnique(vector<string> const &a, vector<string> const &b)
{
	vector<string> result;
	vector<string> c(a);
	c.insert(c.end(), b.begin(), b.end());
	ranges::sort(c);
	for (vector<string>::const_iterator it = c.begin(); it != c.end(); it++)
	{
		if (it != (c.end() - 1))
		{
			if (*it != *(it + 1))
				result.push_back(*it);
			else
			{
				while (it != (c.end() - 1) && *it == *(it + 1))
					it++;
			}
		}
		else
			result.push_back(*it);
	}
	return result;
}
bool CanShuffleWithoutRepeat(string &str)
{
	map<char, size_t> repeats;
	size_t maxCount = 0;
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		repeats[*it]++;
		maxCount = max(maxCount, repeats[*it]);
	}
	return str.size() - maxCount >= maxCount - 1;
}
size_t CountDistinctSlices1(long m, vector<long> &data)
{
	size_t slices = 0;
	set<string> uniqueslices;
	set<long> unique;
	size_t j;
	for (size_t i = 0; i < data.size();)
	{
		unique.clear();
		unique.emplace(data[i]);
		for (j = i + 1; j < data.size() && unique.find(data[j]) == unique.end(); j++)
			unique.emplace(data[j]);
		for (size_t k = (j - i); k > 0; k--)
			slices += k;
		i = j;
	}
	return slices;
}
// a.push_back(3); // 3
// a.push_back(4); // 2
// a.push_back(5); // 1
// a.push_back(5); // 2
// a.push_back(2); // 1
// XXX: I don't know what this function is doing. May remove this function!
size_t CountDistinctSlices(vector<long> &data)
{
	size_t slices = 0, start = 0;
	set<long> unique;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (unique.find(data[i]) == unique.end())
			unique.emplace(data[i]); // {3, 4, 5}, {5, 2}
		else
		{
			slices += SequenceSum(i - start); // f(3) = 1+2+3 = 6
			start = i;						  // 3
			unique.clear();
			unique.emplace(data[i]); // 5
		}
	}
	return slices + SequenceSum(data.size() - start); // 6 + f(2) = 6 + 3 = 9
}
// "Hello World!!!" -> "!!!dlroW olleH"
void reverse(string &str)
{
	char tmp;
	size_t pivot = str.size() / 2 + str.size() % 2;
	for (size_t i = 0, tail = str.size() - 1; i < pivot; i++, tail--)
	{
		tmp = str[tail];
		str[tail] = str[i];
		str[i] = tmp;
	}
}
/*
 * "Hello World!!!" -> "World!!! Hello"
 * 1: "Hello World!!!" -> "!!!dlroW olleH"
 * 2: "!!!dlroW olleH" -> "World!!! Hello"
 */
void reverseWords(string &str)
{
	reverse(str);
	for (size_t i = 0, j = 0; i != string::npos; j = i + 1)
	{
		i = str.find(" ", j);
		if (i != string::npos)
		{
			string tmp = str.substr(j, i - j);
			reverse(tmp);
			str.replace(j, i - j, tmp);
		}
		else
		{
			string tmp = str.substr(j);
			reverse(tmp);
			str.replace(j, str.size() - j, tmp);
		}
	}
}
/* "  Hello World!!!  " -> "World!!! Hello"
 * 1: "Hello World!!!" -> "!!!dlroW olleH"
 * 2: "!!!dlroW olleH" -> World!!! Hello"
 */
void reverseWordsTrimmed(string &str)
{
	reverse(str);
	for (size_t i = 0, j = 0; i != string::npos && j < str.size();)
	{
		i = str.find(' ', j);
		if (i != string::npos)
		{
			size_t k = i;
			for (; str[k] == ' '; k++)
				;
			if (!i)
			{ // If str is prefixed with spaces
				str = str.substr(k);
				continue;
			}
			else if (k == str.size()) // if str ends with spaces
				str.erase(i, k - i);
			else if ((k - i) > 1) // More than one space in between words
				str.erase(i, k - i - 1);
			string tmp = str.substr(j, i - j);
			reverse(tmp);
			str.replace(j, i - j, tmp);
		}
		else
		{
			string tmp = str.substr(j);
			reverse(tmp);
			str.replace(j, str.size() - j, tmp);
		}
		j = i + 1;
	}
}
/* 0 1   2   3
 *  a b   b   c
 *    i,t
 *    j
 *  a b   b   c
 *        i,t
 *    j
 *  a b   b   c
 *        t   i
 *        j
 *  a b   c
 */
void RemoveDuplicateCharacters(string &str)
{
	if (str.size() > 1)
	{
		size_t tail = 1, j;
		for (size_t i = tail; i < str.size(); i++)
		{
			for (j = 0; j < tail && str[j] != str[i]; j++)
				;
			if (j == tail) // str[i] is not a duplicate character. So copy it to str[tail]
				str[tail++] = str[i];
		}
		str[tail] = 0;
		str.resize(tail);
	}
}
/* https://leetcode.com/problems/remove-duplicate-letters/
* 100%
bcabc
bc
  abc

abacb
ab
  acb <= abc

cbacdcbc
c
 b
  acd c b
  acdb

cbacdbcd
c
 b
  acd b -> acb -> ab
	abcd

cbaidbcj
c
 b
  aidbcj
WITHOUT reorder the original character sequence!
*/
void RemoveDuplicateCharactersLexicographicalOrder(string &str)
{
	string result;
	map<char, long> counts;
	for (size_t i = 0; i < str.size(); i++)
		counts[str[i]]++;
	for (size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		for (; !result.empty() && c < result.back() && counts[result.back()] && result.find(c) == string::npos; result.pop_back())
			;
		if (result.find(c) == string::npos)
			result.push_back(c);
		counts[c]--;
	}
	str = result;
}
/* https://leetcode.com/problems/additive-number/
 * 100%
 * i: width of the first operand
 * j: width of the second operand
 * width of sum is max(i, j). So i must be <= half the input string size
 */
bool isAdditiveNumber(string const &str)
{
	for (size_t i = 1; i <= str.size() / 2; i++)
		for (size_t j = 1; max(i, j) <= str.size() - i - j; j++)
			if (checkIfAdditiveSequence(i, j, str))
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
bool checkIfAdditiveSequence(size_t i, size_t j, string const &str)
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
bool AreAnagrams(string const &s1, string const &s2)
{
	if (s1.size() == s2.size())
	{
		string str1(s1), str2(s2);
		ranges::sort(str1);
		ranges::sort(str2);
		return str1 == str2;
	}
	else
		return false;
}
size_t FindAnagrams(vector<string> const &s, vector<vector<string>> &result)
{
	map<string, vector<string>> anagrams;
	for (vector<string>::const_iterator it = s.begin(); it != s.end(); it++)
	{
		string s1(*it);
		ranges::sort(s1);
		anagrams[s1].push_back(*it);
	}
	size_t count = 0;
	for (map<string, vector<string>>::const_iterator it = anagrams.begin(); it != anagrams.end(); it++)
	{
		/*
			2 elements: a a = [0,1] 1 pair of anagrams
			3 elements: a a a = [0,1],[1,2],[0,2] 3 pairs of anagrams
			4 elements: a a a a = [0,1],[1,2],[2,3],[0,2],[0,3] 5 pairs of anagrams
			(n+1)*n/2 - n = ((n+1)*n - 2n) / 2 = (n^2 + n - 2n) / 2 = (n^2 - n) / 2 = (n * (n - 1)) / 2 (Note: Multiply BEFORE divide!)
		*/
		if (it->second.size() > 1)
			result.push_back(it->second);
		count += ((it->second.size() - 1) * it->second.size()) / 2;
	}
	return count;
}
// https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem
// 100%
size_t SherlockAndAnagrams(string const &s)
{
	vector<string> strings;
	vector<vector<string>> anagrams;
	for (size_t i = 0; i < s.size(); i++)
		for (size_t len = 1; len <= s.size() - i; len++)
			strings.push_back(s.substr(i, len));
	return FindAnagrams(strings, anagrams);
}
/*
 * https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
 * adapt from IsPalindrome()
 * 100%
 */
bool SherlockValidString(string const &s)
{
	size_t odd = 0;
	size_t length = s.length();
	map<char, size_t> counts;
	for (string::const_iterator it = s.begin(); it != s.end(); it++)
		counts[*it]++;
	size_t min = numeric_limits<size_t>::max(), max = 0;
	bool result = true;
	map<size_t, size_t> countsCounts;
	for (map<char, size_t>::const_iterator it = counts.begin(); it != counts.end(); it++)
	{
		if (it->second % 2 && (!(length % 2) || ++odd > 1))
			result = false;
		if (it->second > max)
			max = it->second;
		if (it->second < min)
			min = it->second;
		countsCounts[it->second]++;
	}
	if (countsCounts.size() == 2 && countsCounts.find(1) != countsCounts.end() && countsCounts[1] == 1)
		return true;
	return max - min > 1 ? false : result;
}
// Write a code to test whether string s2 is obtained by rotating the string s1 by n places.
bool AreRotatedStrings(string const &s1, string const &s2, size_t n)
{
	string str(s1);
	ranges::rotate(str, str.begin() + n);
	return (str == s2);
}
// Return occurrance of any anagram of s2 in s1
vector<size_t> FindSubString(string const &s1, string const s2)
{
	vector<size_t> result;
	if (s1.size() >= s2.size())
		for (size_t i = 0; i < s1.size(); i++)
		{
			if (AreAnagrams(s1.substr(i, s2.size()), s2))
				result.push_back(i);
		}
	return result;
}
void copy_on_write_string()
{
	const char *cptr, *cptr1;
	string s1("Hello World!!!");
	string s2 = s1;
	cptr = s1.c_str();
	cptr1 = s1.c_str();
	cout << hex << "s1 @ " << (void *)(cptr) << endl;
	cout << "s2 @ " << (void *)(cptr1) << endl;
	s2 += " Hello World!!!";
	cptr = s1.c_str();
	cptr1 = s1.c_str();
	cout << hex << "s1 @ " << (void *)(cptr) << endl;
	cout << "s2 @ " << (void *)(cptr1) << endl;
}
long double Fibonacci(long n)
{
	// {0 1 1 2 ...}
	return (n <= 1) ? n : Fibonacci(n - 2) + Fibonacci(n - 1);
}
/* Bottom-up Dynamic Programming
 */
long double FibonacciDynamicProgramming(long n)
{
	/* 0 1 2 3
	 * {0 1 1 2 3 5 8}
	 * {0, 1}, {1, 1}, {1, 2}, {3, 2}, {3, 5}
	 */
	vector<long double> result = {0, 1};
	if (n <= 1)
		return n;
	for (size_t i = 2; i <= (size_t)n; i++)
		result[i % 2] = result[(i - 2) % 2] + result[(i - 1) % 2];
	return result[n % 2];
}
/* https://www.hackerrank.com/challenges/fibonacci-modified/problem
 * Timeout for n >= 20
 */
string FibonacciModified(long t1, long t2, long n)
{
	// Index: 0 1 2 3 4 5  6   7	  8
	// Value: 0 1 1 2 5 27 734 538783 ...
	if (!n)
		return to_string(t1);
	else if (n == 1)
		return to_string(t2);
	Arithmetic arithmetic;
	string s1 = FibonacciModified(t1, t2, n - 2);
	string s2 = FibonacciModified(t1, t2, n - 1);
	string s3 = arithmetic.NumberStringMultiplication(s2, s2);
	return arithmetic.NumberStringSum(s1, s3);
}
string FibonacciModifiedDynamicProgramming(long t1, long t2, long n)
{
	// Index: 0 1 2 3 4 5  6   7	  8
	// Value: 0 1 1 2 5 27 734 538783 ...
	if (!n)
		return to_string(t1);
	else if (n == 1)
		return to_string(t2);
	Arithmetic arithmetic;
	vector<string> result = {to_string(t1), to_string(t2)};
	for (size_t i = 2; i <= (size_t)n; i++)
		result[i % 2] = arithmetic.NumberStringSum(result[(i - 2) % 2], arithmetic.NumberStringMultiplication(result[(i - 1) % 2], result[(i - 1) % 2]));
	return result[n % 2];
}
// http://web2.0calc.com/
// 64-bit max is 18446744073709551615
// Overflow happens at 21!
long double Factorial(long n)
{
	return (n <= 0) ? 1 : n * Factorial(n - 1);
}
long double FactorialDynamicProgramming(long n)
{
	/* 0 1 2 3 4
	 * {1 1 2 6 24 ...}
	 * result = 1,
	 */
	long double result = 1;
	if (n <= 0)
		return 1;
	for (size_t i = 1; i <= (size_t)n; result *= i++)
		;
	return result;
}
/*
 * https://en.wikipedia.org/wiki/Binomial_coefficient
 */
long double BinomialCoefficients(size_t n, size_t k)
{
	return Factorial(n) / (Factorial(k) * Factorial(n - k));
}
/*
 * https://en.wikipedia.org/wiki/Multinomial_theorem
 * Permutations of length-nword with n1 a's, n2 b's, ..., nk z's = n! / (n1! * n2! * ... * nk!)
 */
long double MultinomialCoefficients(size_t n, vector<size_t> const &k)
{
	long double divisor = 1;
	for (vector<size_t>::const_iterator it = k.begin(); it != k.end(); it++)
		divisor *= Factorial(*it);
	return Factorial(n) / divisor;
}

long SequenceSum(long n)
{
	// return (n <= 0) ? 0 : n + SequenceSum(n - 1);
	return (n + 1) * (n) / 2;
}

/*
 Trailing zeros are contributed by pairs of 5 and 2, because 5*2 = 10.
 To count the number of pairs, we just have to count the number of multiples of 5.
 Note that while 5 contributes to one multiple of 10, 25 contributes two (because 25 = 5*5).
 Examples:
 25(5*5) 24 23 22 21 20(5*4) 19 18 17 16 15(5*3) 14 13 12 11 10(5*2) 9 8 7 6 5 4 3 2 1 => 6 zeroes
 10(5*2) 9 8 7 6 5 4 3 2 1 => 2 zeroes
 */
long FactorialTrailingZeroesCount(long n)
{
	long count = 0;
	if (n < 0)
		return 0;
	for (long i = 5; (n / i) > 0; i *= 5)
		count += (n / i);
	return count;
}
void MultiplesCount(int dividend, long &twos, long &fives)
{
	long div = dividend;
	if (dividend > 0)
	{
		for (; (dividend / 5) > 0 && !(dividend % 5); dividend /= 5)
			fives++;
		dividend = div;
		for (; (dividend >> 1) > 0 && !(dividend % 2); dividend >>= 1)
			twos++;
	}
}
// given an array of N positive integers, returns the maximum number of trailing zeros of the number obtained by multiplying three different elements from the array.
// Numbers are considered different if they are at different positions in the array
// 100% correctness However, performance is bad with O(N**3).
long MaxZeroProductBruteForce(vector<int> const &data)
{
	long result = 0;
	map<int, ZeroFactors> multipleMap;
	map<int, ZeroFactors>::const_iterator it;
	vector<ZeroFactors> factors;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (!(data[i] % 10 && data[i] % 2 && data[i] % 5))
		{
			it = multipleMap.find(data[i]);
			ZeroFactors factor;
			if (it == multipleMap.end())
			{
				long two = 0, five = 0;
				MultiplesCount(data[i], two, five);
				factor.two = two;
				factor.five = five;
				multipleMap.emplace(data[i], factor);
				factors.push_back(factor);
			}
			else
			{
				factor.two = it->second.two;
				factor.five = it->second.five;
				;
				factors.push_back(factor);
			}
		}
	}
	if (factors.size() == 1)
		result = min(factors[0].two, factors[0].five);
	else if (factors.size() == 2)
		result = min(factors[0].two + factors[1].two, factors[0].five + factors[1].five);
	else if (factors.size() > 2)
	{
		for (size_t i = 0; i < factors.size() - 2; i++)
		{
			for (size_t j = i + 1; j < factors.size() - 1; j++)
			{
				for (size_t k = j + 1; k < factors.size(); k++)
				{
					long twofactor = factors[i].two + factors[j].two + factors[k].two;
					long fivefactor = factors[i].five + factors[j].five + factors[k].five;
					if (min(twofactor, fivefactor) > result)
						result = min(twofactor, fivefactor);
				}
			}
		}
	}
	return result;
}
// XXX: WIP
long MaxZeroProduct(vector<int> const &data, size_t count)
{
	long result = 0;
	map<int, ZeroFactors> multipleMap;
	map<int, ZeroFactors>::const_iterator it;
	vector<ZeroFactors> factors;
	// Initializing each value with -1;
#define MAX5 100
	// vector<vector<long>> subset(count, vector<long>(100, -1));
	// map<long, long> twos, fives;
	set<long> twos, fives;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (!(data[i] % 10 && data[i] % 2 && data[i] % 5))
		{
			it = multipleMap.find(data[i]);
			ZeroFactors factor;
			if (it == multipleMap.end())
			{
				long two = 0, five = 0;
				MultiplesCount(data[i], two, five);
				factor.two = two;
				factor.five = five;
				multipleMap.emplace(data[i], factor);
				factors.push_back(factor);
			}
			else
			{
				factor.two = it->second.two;
				factor.five = it->second.five;
				;
				factors.push_back(factor);
			}
			// twos[factor.two] = max(twos[factor.two], factor.five);
			// fives[factor.five] = max(fives[factor.five], factor.two);
			twos.emplace(factor.two);
			fives.emplace(factor.five);
#if 0
			// Calculating subset[i][j] for maximum amount of twos we can collect by checking first i numbers and taking 
			// j of them with total power of five. 
			//for (int i = count - 1; i >= 0; i--)
			for (size_t j = 0; j < count; j++)
				for (int k = 0; k < subset[j].size(); k++)
				//for (size_t k = 0; k < 100; k++)
					// If subset[j][k] is not calculated. 
					//if (subset[j][k] != -1)
					//subset[j][k + factor.five] = max(subset[j][k + factor.five], subset[j][k] + factor.two);
					subset[j][k] = max(subset[j][k], subset[j][k] + factor.two);
#endif
		}
	}
	// for (map<long, long>::const_iterator it = subset.begin(); it != subset.end(); it++)
	//	result = max(result, min(it->))
	return 0;
}
long ConsecutiveMaximumSumOfFactors(vector<zerofactors_t> &data, vector<zerofactors_t> &result, int value)
{
	long max_ending_here = 0, max_so_far = 0, count = 0;
	vector<zerofactors_t>::iterator start = data.end(), end = data.end();
	for (vector<zerofactors_t>::iterator it = data.begin(); it != data.end(); it++)
	{
		max_ending_here += (value == 2) ? it->two : it->five;
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			start = end = data.end();
		}
		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			if (start == data.end())
				start = it;
			end = it;
		}
		if (++count >= 3)
		{
			max_ending_here = 0;
			count = 0;
		}
	}
	if (start != data.end() && end != data.end())
		result.assign(start, end + 1);
	return max_so_far;
}
set<string> permute(string const &str)
{
	set<string> permutations;
	if (str.empty())
		return permutations;
	else if (str.size() == 1)
	{
		permutations.insert(str);
		return permutations;
	}
	char toInsert = str[0];
	set<string> words = permute(str.substr(1));
	for (set<string>::iterator it = words.begin(); it != words.end(); it++)
	{
		for (size_t i = 0; i <= it->size(); i++)
			permutations.insert(insertCharAt(toInsert, *it, i));
	}
	return permutations;
}
// O(n!)
set<vector<long>> permute(vector<long> &data)
{
	set<vector<long>> permutations;
	if (data.empty())
		return permutations;
	else if (data.size() == 1)
	{
		permutations.insert(vector<long>{data[0]});
		return permutations;
	}
	long toInsert = data[0];
	vector<long> subset(data.begin() + 1, data.end());
	set<vector<long>> combinations = permute(subset);
	for (set<vector<long>>::iterator it = combinations.begin(); it != combinations.end(); it++)
	{
		vector<long> tmp = *it;
		for (size_t offset = 0; offset <= tmp.size(); offset++)
			permutations.insert(insertItemAt(toInsert, tmp, offset));
	}
	return permutations;
}
string insertCharAt(char toInsert, string str, size_t offset)
{
	string start = str.substr(0, offset);
	string end = str.substr(offset);
	return start + toInsert + end;
}
vector<long> insertItemAt(long toInsert, vector<long> &items, size_t offset)
{
	vector<long> result(items.begin(), items.begin() + offset);
	result.push_back(toInsert);
	result.insert(result.end(), items.begin() + offset, items.end());
	return result;
}
void Parentheses(vector<string> &result, string &str, size_t index, long left, long right)
{
	if (!left && !right)
		result.push_back(str);
	else
	{
		if (left > 0)
		{
			str[index] = '(';
			Parentheses(result, str, index + 1, left - 1, right);
		}
		if (right > left)
		{
			str[index] = ')';
			Parentheses(result, str, index + 1, left, right - 1);
		}
	}
}
void Parentheses(vector<string> &result, size_t count)
{
	string str;
	str.resize(count * 2);
	Parentheses(result, str, 0, count, count);
}
/*
 * i - stack.peek()
 * ()
 * 0: -1, 0
 * 1 : -1, result = 2
 *
 * (()
 * 0: -1, 0
 * 1 : -1, 0, 1
 * 2 : -1, 0 result = 2
 *
 * ((
 * 0: -1, 0
 * 1 : -1, 1
 * result = 0
 *
 * ((()
 * 0: -1, 0
 * 1 : -1, 0, 1
 * 2 : -1, 0, 1, 2
 * 3 : -1, 0, 1 result = 2
 *
 * ((())
 * 0: -1, 0
 * 1 : -1, 0, 1
 * 2 : -1, 0, 1, 2
 * 3 : -1, 0, 1 result = 2
 * 4 : -1, 0 result = 4
 *
 * ())()
 * 0: -1, 0
 * 1: -1 result = 2
 * 2: 2			<= extra ')'
 * 3: 2, 3
 * 4: 2 result = 2
 */
long LongestValidParentheses(string const &str)
{
	MyStack<long> stack;
	stack.push(-1); // The first element of stack is used to provide base for next valid string
	long result = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			stack.push(i);
		else if (str[i] == ')')
		{
			stack.pop(); // Remove the last matching opening bracket or -1
			if (!stack.isEmpty() && (long)(i - stack.peek()) > result)
				result = i - stack.peek();
			else if (stack.isEmpty())
				stack.push(i); // This marks the next invalid extra ')' as base case
		}
	}
	return result;
}
// https://app.codility.com/programmers/task/brackets_rotation/
// Unfinished work!
long LongestValidParenthesesWithFixes(string const &str, size_t k)
{
	stack<long> stack;
	long start = -1, end = -1;
	stack.push(-1); // The first element of stack is used to provide base for next valid string
	long result = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			stack.push(i);
		else if (str[i] == ')')
		{
			stack.pop(); // Remove the last matching opening bracket or -1
			if (!stack.empty() && (long)(i - stack.top()) > result)
			{
				result = i - stack.top();
				start = stack.top() + 1;
				end = i;
			}
			else if (stack.empty())
				stack.push(i);
		}
	}
	long *stackEnd = &stack.top() + 1;
	long *stackBegin = stackEnd - stack.size();
	vector<long> list(stackBegin, stackEnd);
	// The algorithm implemented is based on reverse-engineering of the result sets obtained from the remaining stack elements after the for loop above.
	if (k == 0 || list.empty() || (list.size() == 1 && list[0] == -1))
		return result;
	if (result == 0)
	{
		if (list[0] == -1 || list.size() == 1)
		{
			result = !(list[0] % 2) ? list[0] : list[0] + 1;
			result = list.size() == str.size() + 1 && str.size() > 1 ? 2 : min((long)k, result / 2) * 2;
		}
		else
		{
			size_t size = list.size();
			if (list[0] == -1)
				size--; // remove -1
						// if (list[0] != 0) {
			result = !(size % 2) ? size : size - 1;
			if ((list[0] == 0 && (long)k > (result / 2)) || (list[0] != 0 && (long)k >= (result / 2)))
				result = min((long)(k * 2), result);
			else
				result = 0;
			//}
		}
	}
	else if (list.size() == 1 && list[0] != -1)
	{
		if ((list[0] > end && start > 0) || (list[0] < start && list[0] > 0))
		{
			k--;
			result += 2;
		}
	}
	else
	{
		size_t size = list.size();
		if (list[0] == -1)
			size--;
		result += min(k, size / 2 + size % 2) * 2;
	}
	return result;
}
bool JSONValidation(string json)
{
	size_t keyCount = 0, valueCount = 0, leftBraceCount = 0, rightBraceCount = 0;
	ostringstream oss;
	string key = "", value = "";
	for (string::const_iterator it = json.begin(); it != json.end(); it++)
	{
		if (*it == '{')
		{
			leftBraceCount++;
			key = "";
			value = "";
			oss.str("");
		}
		else if (*it == '}' || *it == ' ' || *it == ',')
		{
			value = oss.str();
			oss.str("");
			if (value != "")
				valueCount++;
			if (*it == '}')
				rightBraceCount++;
			if (leftBraceCount > rightBraceCount && keyCount > valueCount)
				valueCount++;
		}
		else if (*it == ':')
		{
			key = oss.str();
			oss.str("");
			if (key != "")
				keyCount++;
		}
		else
			oss << *it;
	}
	return leftBraceCount == rightBraceCount && keyCount == valueCount;
}
// 0 1 2 3 4 5 6 7 8 9 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
void findDistinct(vector<long> &input, vector<long> &output)
{
	for (vector<long>::const_iterator it = input.begin(); it != input.end(); it++)
	{
		vector<long>::const_iterator it1 = it + 1;
		for (; it1 != input.end() && (*it ^ *it1); it1++)
			;
		if (it1 == input.end())
			output.push_back(*it);
	}
}
// http://en.wikipedia.org/wiki/Prime_number - Trial division implementation
void findPrimes(unsigned long n, vector<long> &result)
{
	if (n <= 3)
		result = {2, 3};
	else
	{
		long double j;
		result = {2, 3};
		for (unsigned long i = 4; i <= n; i++)
		{
			long double sqrtI = sqrt(i);
			for (j = 2; j <= sqrtI && (i % (long)j); j++)
				;
			if (j > sqrtI)
				result.push_back(i);
		}
	}
}
// https://en.wikipedia.org/wiki/Primality_test
bool isPrime(unsigned long n)
{
	if (n <= 3)
		return n > 1;
	else if (!(n % 2) || !(n % 3))
		return false;
	for (size_t i = 5; (i * i) <= n; i += 6) // 5 7 11
		if (!(n % i) || !(n % (i + 2)))
			return false;
	return true;
}
// https://app.codility.com/programmers/lessons/12-euclidean_algorithm/common_prime_divisors/
// Correctness: 100%
// 61% due to timeout
size_t CommonPrimeDivisors(vector<long> &data1, vector<long> &data2)
{
	vector<size_t> indices;
	vector<long> a(data1), b(data2);
	ranges::sort(a);
	ranges::sort(b);
	long maxNum = max(a.back(), b.back());
	vector<long> primes;
	findPrimes(maxNum, primes);
	if (data1.size() == 1 && data2.size() == 1 && data1[0] == 1 && data2[0] == 1)
		return 1;
	for (size_t i = 0; i < data1.size(); i++)
	{
		maxNum = max(data1[i], data2[i]);
		bool flag = true;
		for (vector<long>::const_iterator it = primes.begin(); it < primes.end() && *it <= maxNum; it++)
		{
			if (!(data1[i] % *it) ^ !(data2[i] % *it))
				flag = false;
		}
		if (flag)
			indices.push_back(i);
	}
	return indices.size();
}
// 2 1 1 2 => (2+1)*(2+1) = 9
// 2 3 3 2 :
// (1) 2 + 3 + 3 + 2 = 10
// (2) 2 * 3 * 3 * 2 = 36
// (3) (2 + 3) * (3 + 2) = 25
// (4) 2 + (3 * 3) + 2 = 11
unsigned long long findMax(vector<unsigned long long> const &data)
{
	vector<unsigned long long> result;
	if (data.size() == 1)
		return data[0];
	else if (data.size() == 2)
		return (data[0] * data[1] > data[0] + data[1]) ? data[0] * data[1] : data[0] + data[1];
	else
	{
		for (vector<unsigned long long>::const_iterator it = data.begin(); it != data.end(); it += 2)
		{
			if (it <= data.end() - 2)
				result.push_back((*it + *(it + 1)) > (*it * *(it + 1)) ? (*it + *(it + 1)) : (*it * *(it + 1)));
			else
				result.push_back(*it);
		}
	}
	return findMax(result);
}

string uncompress(string const &str)
{
	ostringstream oss;
	for (size_t i = 0; i < str.size();)
	{
		if (isalpha(str[i]))
			oss << str[i++];
		else if (isdigit(str[i]))
		{
			char *end(nullptr);
			errno = 0;
			unsigned long repeat = strtoul(&str[i], &end, 10);
			if (!errno && repeat > 0 && repeat < numeric_limits<unsigned long>::max())
			{
				if (*end)
					while (str[i] != end[0])
						i++;
				else
					i++;
				ostringstream oss1;
				for (size_t k = 0; k < repeat; k++)
					oss1 << oss.str();
				oss.str("");
				oss << oss1.str();
			}
			else
				i++;
		}
	}
	return oss.str();
}
/*
 "0010110100" => Length: 4
 "0010110110" => Length: 5
 */
size_t findLongestContiguousPattern(string &str, char c)
{
	size_t max = 0;
	int index = -1;
	size_t count = 0;
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == c)
			count++;
		else
		{
			if (max < count)
			{
				max = count;
				if (i > 0 && str[i - 1] == c && str[i + 1] == c)
				{
					count = (index != -1) ? i - index : count + 1;
					index = i;
				}
			}
			else
				count = 0;
		}
	if (index > 0)
		str[index] = c;
	return max;
}
/*
 * dest:  {1,3,5,7,9,11,13,15}
 * source:{6,8,10,12,14}
 * dest:  {1,3,5,[6],7,8,9,10,11 ,12 ,13 ,14 ,15 }
 *
 * dest:  {6,8,10,12,14,16,18}
 * source:{1,3,5,7,9,11}
 * dest:  {1,3,5,[6],7,8,9,10 ,11 ,12 ,14 ,16 ,18 }
 */
void Merge(vector<long> &dest, vector<long> &source)
{
	int k = dest.size() + source.size() - 1;
	int i = dest.size() - 1;
	int j = source.size() - 1;
	dest.resize(k + 1);
	while (i >= 0 && j >= 0)
		dest[k--] = dest[i] > source[j] ? dest[i--] : source[j--];
	while (j >= 0)
		dest[k--] = source[j--];
}
// http://cpluspluslearning-petert.blogspot.co.uk/2014/10/data-structure-and-algorithm-order.html
void OrderArrayIntoNegativePositiveSeries(vector<long> &arr)
{
	if (arr.empty() || arr.size() < 3)
		return;
	// if first value is negative, then find a positive value next
	bool positiveValToFind = arr[0] < 0;
	long nextValue;
	for (size_t outOfOrderPos = 1, curIndex = 1; curIndex < arr.size(); curIndex++)
	{
		if ((positiveValToFind && arr[curIndex] > 0) || (!positiveValToFind && arr[curIndex] < 0))
		{
			if (outOfOrderPos == curIndex)
			{
				// Scenario 1: curIndex is increment by the for loop
				positiveValToFind = !positiveValToFind;
				outOfOrderPos++;
			}
			else
			{
				// Scenario 2: curIndex is increment by the for loop
				nextValue = arr[curIndex];
				memcpy(&arr[outOfOrderPos + 1], /* destination */
					   &arr[outOfOrderPos],		/* source */
					   (curIndex - outOfOrderPos) * sizeof(long));
				arr[outOfOrderPos] = nextValue;
				outOfOrderPos += 2;
			}
		}
	}
}

/* https://en.wikipedia.org/wiki/Dutch_national_flag_problem
* https://leetcode.com/problems/sort-colors/
* 100%
* Entries from 0 up to (but NOT including) i are values less than mid,
* entries from i up to (but NOT including) j are values equal to mid,
* entries from j up to (and including) k are values not yet sorted, and
* entries from k + 1 to the end of the array are values greater than mid.
0  i   j   k  n-1
<mid mid ??? >mid

2 1 0 1 2 0 1 2
i,j           k (>mid)

2 1 0 1 2 0 1 2
i,j         k   (>mid)

1 1 0 1 2 0 2 2
i,j       k     (==mid)

1 1 0 1 2 0 2 2
i j       k    (==mid)

1 1 0 1 2 0 2 2
i   j     k    (<mid)

0 1 1 1 2 0 2 2
  i   j   k    (==mid)

0 1 1 1 2 0 2 2
  i     j k    (>mid)

0 1 1 1 0 2 2 2
  i     j,k    (>mid)

0 1 1 1 0 2 2 2
  i     j,k    (<mid)

0 0 1 1 1 2 2 2
	i   k j		<= j > k base case
*/
void DutchPartitioning(vector<long> &data, long mid)
{
	for (int i = 0, j = 0, k = data.size() - 1; !data.empty() && j <= k;)
	{
		if (data[j] < mid)
			swap(data[i++], data[j++]);
		else if (data[j] > mid)
			swap(data[j], data[k--]);
		else // if (data[j] == mid)
			j++;
	}
}
/* http://www.cplusplus.com/reference/cstdlib/rand/
 * A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use
 * the modulo of the returned value by the range span and add the initial value of the range:
 * v1 = rand() % 100;         // v1 in the range 0 to 99
 * v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
 * v3 = rand() % 30 + 1985;   // v3 in the range 1985 to 2014
 */
void shuffleCards(vector<long> &cards)
{
	unsigned long long mask = 0; // bitmask of 52 cards.
	int tmp, index;
	random_device device;
	vector<unsigned int> seeds(mt19937_64::state_size);
	ranges::generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	if (!cards.empty() && cards.size() <= 52)
	{
		for (size_t i = 0; i < 52; i++)
		{
			/* index = (rand() % (52 - i)) + i;
			 * i: n  random from n to 51
			 * i: 0  (rand() % 52) + 0  = 0  to 51
			 * i: 1  (rand() % 51) + 1  = 1  to 51
			 * i: 2  (rand() % 50) + 2  = 2  to 51
			 * i: 10 (rand() % 42) + 10 = 10 to 51
			 * i: 26 (rand() % 26) + 26 = 26 to 51
			 * i: 50 (rand() % 2) + 50  = 50 to 51
			 * i: 51 (rand() % 1) + 51  = 51 (Last card left)
			 */
			uniform_int_distribution<int> dist(i, 51);
			index = dist(engine);
			assert(!(mask & ((unsigned long long)1 << cards[index])));
			mask |= ((unsigned long long)1 << cards[index]);
			tmp = cards[i];
			cards[i] = cards[index];
			cards[index] = tmp;
		}
	}
}
void randomSubset(vector<long> &source, size_t count, vector<long> &result)
{
	set<long> masks;
	long index, tmp;
	if (count > source.size())
		return;
	random_device device;
	vector<unsigned int> seeds(mt19937_64::state_size);
	ranges::generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	for (size_t i = 0; i < count; i++)
	{
		// index = (rand() % (source.size() - i)) + i;
		uniform_int_distribution<long> dist(i, source.size() - 1);
		index = dist(engine);
		// cout << "source[" << index << "]: " << source[index] << endl;
		assert(masks.find(source[index]) == masks.end());
		masks.emplace(source[index]);
		result.push_back(source[index]);
		tmp = source[i];
		source[i] = source[index];
		source[index] = tmp;
	}
}
/*
 *  0  1  2  3  4  5  6  7  8  9
 * 10 11 12 13 14 15 16 17 18 19
 * 20 21 22 23 24 25 26 27 28 29
 * 30 31 32 33 34 35 36 37 38 39
 * ...
 * 100 101 102 103 104 105 106 107 108 109
 * 110 111 112 113 114 115 116 117 118 119
 *
 * The last digit will repeat every 10 numbers, the last two digits will repeat every 10^2 numbers, the last 3 digits will repeat every 10^3 numbers, etc.
 *
 * So, if there are X 3s between 0 and 9, then we know there are 2x '3' between 0 and 19.
 * Between 0 and 39, we have 4x '3' from the last digit, and another 10 '3's from the first digit.
 *
 * sequence of last m digits (power-1) repeats n/power times.
 *
 * n: 235 digit: 3
 *
 * f(9):
 * power=1
 * repeats (last digit): 1 {3}
 *
 * f(99):	The last digit will repeat every 10 numbers
 * power=10
 * repeats (last digit): 99/10=9: 13,23,33,43,53,63,73,83,93 (within the power of 10)
 * MSBs: 10
 *
 * f(235):  The last two digits will repeat every 10^2 numbers
 * power:100
 * repeats (last 2 digits): 235/100=2 Example: 134, 234
 *
 * repeats = n / power
 * Total(n=235, digit=3) = n/power * f(power-1) + f(n % power) + MSBs
 *
 * MSBs: n / power > digit ? power : (n % power) == digit ? (n % power) + 1 : 0
 *
 * Example:
 * digit:3, n: 35
 * {3,13,23},{30,31,32,3{3},34,35}
 * first digit repeats n/10= 3 times => 3 * f(power - 1) : {3,13,23}
 * + MSBs = 6 {30,31,32,33,34,35}
 * + f(5) {3'3'}
 *
 * So, if there are X 2s between 0 and 99, then we know there are 2x twos between 0 and 199.
 * Between 0 and 299, we have 3x twos from the last two digits, and another 100 2s from the first digit.
 */
size_t CountDigits(char digit, size_t n)
{
	unsigned long power = 1, MSBs = 0;
	if (digit < 0 || digit > 9)
		throw runtime_error("digit must be between 0 and 9!");
	if (!n)
		return 0;
	for (; (power * 10) < n; power *= 10)
		;
	/* Count MSB digits in the number
	 * 123: power = 100. '1' appears in 100-123
	 * 223: power = 100. '1' appears in 100-199
	 */
	if ((char)(n / power) > digit)
		MSBs = power;
	else if ((n / power) == digit)
		MSBs = (n % power) + 1;

	// Count digit from all other digits
	return (n / power) * CountDigits(digit, power - 1) + CountDigits(digit, n % power) + MSBs;
}
/* https://leetcode.com/problems/count-numbers-with-unique-digits/
 * 100%
 * Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n. 0 <= n <= 8
 *
 * MSB: 1-9 count:9 (MSB cannot have '0' digit)
 * next: 0-9 exclude MSB count:9
 * next: 0-9 count:10 - 2 = 8
 * count: 9,9,8,7,6,5,4,3,2,1,0
 *
 * i:		 0 1 2 3 4 5 6 7 8 9 10
 * lastCount: 9 9 8 7 6 5 4 3 2 1 0(-1)
 *
 * n: 1 [0,10) 0-9
 * 10
 *
 * n: 2 [0,100) 0-99
 * Start from LSB:
 * LSB: 10 numbers
 * next: 10 - LSB's digit - '0' = 8 => 80 numbers
 *
 * Start from MSB:
 * MSB: 10 - '0' = 9
 * next: 10 - MSB's digit = 9 => 81 numbers
 *
 * n: 3 [0,1000) 0-999
 * Start from LSB:
 * LSB: 10 numbers
 * next: 10 - LSB's digit = 9
 * next: 10 - 1 ('0') - 2 = 7 => 7 * 9 * 10 = 630
 *
 * Start from MSB:
 * MSB: 10 - '0' = 9 digits
 * next: 10 - MSB's digit = 9
 * next: 8 => 8 * 9 * 9 = 648
 *
 * Starting from MSB will give more unique numbers
 */
size_t CountNumbersWithUniqueDigits(size_t n)
{
	size_t count = 1;
	if (n >= 0 && n <= 1)
		return pow(10, n);
	else if (n <= 10)
	{
		long lastCount = 9;
		for (size_t i = 0; i < n; i++)
		{
			count *= lastCount;
			if (i >= 1)
				lastCount--;
		}
		return count + CountNumbersWithUniqueDigits(n - 1);
	}
	return 0;
}
/* http://en.wikipedia.org/wiki/Greatest_common_divisor
 * the largest positive integer that divides the numbers without a remainder
 */
long gcd_euclidean(long a, long b)
{
	return !(a % b) ? b : gcd_euclidean(b, a % b);
}
long gcd(long a, long b)
{
	if (!a)
		return b;
	else if (!b)
		return a;
	else
		return a >= b ? gcd_euclidean(a, b) : gcd_euclidean(b, a);
}
/* http://en.wikipedia.org/wiki/Least_common_multiple */
/* The smallest positive integer that is divisible by both a and b.[1] If either a or b is 0, LCM(a, b) is defined to be zero. */
long lcm(long a, long b)
{
	return (!a || !b) ? 0 : (a * b) / gcd(a, b);
}
unsigned long long _atoull(string str, char base)
{
	size_t i = 0;
	unsigned long long result = 0;
	if ((str.length() > 2) && str[0] == '0' && str[1] == 'x')
	{
		base = 16;
		i = 2;
	}
	for (; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if ((str[i] - '0') >= base)
				break;
			result *= base;
			result += str[i] - '0';
		}
		else if (base == 16 && ((str[i] >= 'a' && str[i] <= 'f') || str[i] >= 'A' && str[i] <= 'F'))
		{
			result *= base;
			if (str[i] >= 'a' && str[i] <= 'f')
				result += str[i] - 'a';
			else
				result += str[i] - 'A';
			result += 10;
		}
		else
			break;
	}
	return result;
}
double _atod(string str, char base)
{
	size_t i = 0;
	bool isRemainder = false;
	double quotient = 0;
	double remainder = 0;
	unsigned long long qCount = 1;
	if ((str.length() > 2) && str[0] == '0' && str[1] == 'x')
	{
		base = 16;
		i = 2;
	}
	for (; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if ((str[i] - '0') >= base)
				break;
			if (isRemainder)
			{
				qCount *= base;
				remainder *= base;
				remainder += (double)str[i] - '0';
			}
			else
			{
				quotient *= base;
				quotient += (double)str[i] - '0';
			}
		}
		else if (base == 16 && ((str[i] >= 'a' && str[i] <= 'f') || str[i] >= 'A' && str[i] <= 'F'))
		{
			if (isRemainder)
			{
				qCount *= base;
				remainder *= base;
				if (str[i] >= 'a' && str[i] <= 'f')
					remainder += (double)str[i] - 'a';
				else
					remainder += (double)str[i] - 'A';
				remainder += 10;
			}
			else
			{
				quotient *= base;
				if (str[i] >= 'a' && str[i] <= 'f')
					quotient += (double)str[i] - 'a';
				else
					quotient += (double)str[i] - 'A';
				quotient += 10;
			}
		}
		else if (str[i] == '.')
			isRemainder = true;
		else
			break;
	}
	if (remainder)
	{
		remainder /= qCount;
		return quotient + remainder;
	}
	else
		return quotient;
}
/*
 * https://leetcode.com/problems/string-to-integer-atoi/
 * 100%
 */
long _atoi(string str)
{
	int result = 0;
	bool isNegative = false, isPositive = false, foundNumber = false;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '-')
		{
			if (!isNegative && !isPositive && !foundNumber)
				isNegative = true;
			else if (foundNumber)
				return isNegative ? result * -1 : result;
			else
				return 0;
		}
		else if (str[i] == '+')
		{
			if (!isPositive && !isNegative && !foundNumber)
				isPositive = true;
			else if (foundNumber)
				return isNegative ? result * -1 : result;
			else
				return 0;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			long r = (long)result * 10;
			r += str[i] - '0';
			if (isNegative)
				r *= -1;
			if (r >= numeric_limits<int>::max())
				return numeric_limits<int>::max();
			else if (r <= numeric_limits<int>::min())
				return numeric_limits<int>::min();
			result *= 10;
			result += str[i] - '0';
			foundNumber = true;
		}
		else if (foundNumber || isNegative || isPositive)
		{
			if (foundNumber)
				return isNegative ? result * -1 : result;
			else
				return 0;
		}
		else if (str[i] != ' ')
			return 0;
	}
	if (isNegative)
		result *= -1;
	return result;
}
// 1234.5678
double round(double num, int n)
{
	unsigned long long tmp, tmp1;
	tmp = num * pow(10, n + 1);
	tmp1 = num * pow(10, n);
	if (tmp % 10 >= 5)
		tmp1++;
	return tmp1 / pow(10, n);
}
long KthNumberWith357PrimeFactors(long n)
{
	long value = 1;
	if (n > 0)
	{
		queue<long> three, five, seven;
		three.push(3);
		five.push(5);
		seven.push(7);
		for (--n; n > 0; n--)
		{
			value = Min(three.front(), Min(five.front(), seven.front()));
			if (value == seven.front())
				seven.pop();
			else
			{
				if (value == five.front())
					five.pop();
				else
				{
					three.pop();
					three.push(value * 3);
				}
				five.push(value * 5);
			}
			seven.push(value * 7);
		}
	}
	return value;
}
void GetPermutations(string &w, set<string> &dictionary, set<string> &result)
{
	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		if (it->size() == w.size() && *it != w)
		{
			size_t count = 0;
			for (size_t i = 0; i < it->size() && count < 2; i++)
				if ((*it)[i] != w[i])
					count++;
			if (count < 2)
				result.insert(*it);
		}
	}
}
// DAMP -> LAMP -> LIMP -> LIME -> LIKE
void WordsLadder(string const &start, string const &stop, set<string> &dictionary, vector<string> &result)
{
	queue<string> actionQ;
	set<string> visited;
	map<string, string> backtrack;
	actionQ.push(start);
	visited.emplace(start);
	while (!actionQ.empty())
	{
		string w = actionQ.front(); // DAMP
		actionQ.pop();
		set<string> permutations;
		dictionary.erase(w);
		GetPermutations(w, dictionary, permutations);
		for (set<string>::const_iterator it = permutations.begin(); it != permutations.end(); it++)
		{
			if (*it == stop)
			{ // LIKE
				// Found our word! Now backtrack to record all the single-character change from 'start' to 'stop'
				result.push_back(*it);
				result.push_back(w);
				while (backtrack.find(w) != backtrack.end())
				{
					w = backtrack[w];
					result.push_back(w);
				}
				return;
			}
			else if (visited.find(*it) == visited.end())
			{
				actionQ.push(*it);
				visited.insert(*it);
				backtrack[*it] = w; // Key: later; Value: earlier
			}
		}
	}
}
void KDTreeTests()
{
	vector<vector<long>> coordinates{{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
	KDTree<long> kdTree(coordinates);
	kdTree.PrintTree();
}
/*
 * Perform a down-heap or heapify-down operation for a max-heap
 * Index start from 0
 */
void MaxHeapifyDown(vector<long> &data, size_t start)
{
	size_t left = 2 * start + 1;
	size_t right = 2 * start + 2;
	size_t max = start;
	if (left < data.size() && data[left] > data[max])
		max = left;
	if (right < data.size() && data[right] > data[max])
		max = right;
	if (max != start)
	{
		long tmp = data[start];
		data[start] = data[max];
		data[max] = tmp;
		MaxHeapifyDown(data, max);
	}
}
/*
 * Perform a down-heap or heapify-down operation for a min-heap
 * Index start from 0
 */
void MinHeapifyDown(vector<long> &data, size_t start)
{
	size_t left = 2 * start + 1;
	size_t right = 2 * start + 2;
	size_t min = start;
	if (left < data.size() && data[left] < data[min])
		min = left;
	if (right < data.size() && data[right] < data[min])
		min = right;
	if (min != start)
	{
		long tmp = data[start];
		data[start] = data[min];
		data[min] = tmp;
		MinHeapifyDown(data, min);
	}
}
void trim(string &str)
{
	size_t i = 0, j = 0;
	for (i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			if (i > 0 && str[i - 1] != ' ')
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
	}
	for (; j < str.size(); j++)
		str[j] = ' ';
}
size_t minDiffPairs(vector<long> &numbers, long diff)
{
	set<long> pairs;
	size_t count = 0;
	ranges::sort(numbers);
	if (numbers.size() < 2)
		return 0;
	size_t offset = 1;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (pairs.find(i) == pairs.end())
		{
			int num = numbers[i];
			for (size_t j = offset; j < numbers.size(); j++)
			{
				if (pairs.find(j) == pairs.end() && abs(numbers[i] - numbers[j]) >= diff)
				{
					offset = j + 1;
					pairs.insert(i);
					pairs.insert(j);
					break;
				}
			}
		}
	}
	return pairs.size() / 2;
}
vector<char> AddVectors(vector<char> &a, vector<char> &b)
{
	char carry = 0;
	vector<char> result;
	vector<char>::reverse_iterator aIt = a.rbegin();
	vector<char>::reverse_iterator bIt = b.rbegin();
	for (; aIt != a.rend() && bIt != b.rend(); aIt++, bIt++)
	{
		result.push_back((*aIt + *bIt + carry) % 10);
		carry = (*aIt + *bIt + carry) / 10;
	}
	if (aIt != a.rend())
	{
		result.push_back((*aIt + carry) % 10);
		carry = (*aIt + carry) / 10;
	}
	if (bIt != b.rend())
	{
		result.push_back((*bIt + carry) % 10);
		carry = (*bIt + carry) / 10;
	}
	if (carry > 0)
		result.push_back(carry);
	reverse(result.begin(), result.end());
	return result;
}
/* Given a 2-dimensional array with arbitrary sizes and contains random positive values, you are required to move from the first element [0][0] to the last
 * element [n][n] using the path which will yield the maximum sum of all the elements traversed. You can only move right and down; NOT left and up.
 * 1 2
 */
pathResult_t FindMaxPath(vector<vector<size_t>> &grid, size_t r, size_t c)
{
	ostringstream oss;
	pathResult_t result;
	if (r < grid.size() && c < grid[r].size())
	{
		if (r == grid.size() - 1 && c == grid[r].size() - 1)
		{
			result.sum = grid[r][c];
			oss << "[" << r << "][" << c << "]";
			result.path = oss.str();
			return result;
		}
		pathResult_t path1 = FindMaxPath(grid, r, c + 1);
		pathResult_t path2 = FindMaxPath(grid, r + 1, c);
		oss << "[" << r << "][" << c << "] " << ((path1.sum >= path2.sum) ? path1.path : path2.path);
		result.sum = grid[r][c] + max(path1.sum, path2.sum);
		result.path = oss.str();
	}
	return result;
}
// S: Start; X: Obstacle E: Destination
// 1 1 1 1 1
// S 1 X 1 1
// 1 1 1 1 1
// X 1 1 E 1
// 1 1 1 1 X
bool FindShortestPath(vector<vector<char>> &grid, size_t r, size_t c, queue<string> &result, char dest, char obstacle)
{
	string pos, origin;
	ostringstream oss, oss1;
	set<string> visited;
	map<string, string> routes;
	vector<position_t> positions;
	positions.push_back(position_t(r, c));
	oss << r << c;
	origin = oss.str();
	oss.str("");
	while (!positions.empty())
	{
		vector<position_t> nextHops(positions);
		positions.clear();
		for (vector<position_t>::const_iterator it = nextHops.begin(); it != nextHops.end(); it++)
		{
			oss1.str("");
			oss1 << it->row << it->col;
			// Go Down
			if (it->row + 1 < grid.size())
				if (grid[it->row + 1][it->col] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row + 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row + 1][it->col] != obstacle)
				{ // Obstacle. Cancel this route
					oss.str("");
					oss << it->row + 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row + 1, it->col));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Right
			if (it->col + 1 < grid[it->row].size())
				if (grid[it->row][it->col + 1] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col + 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col + 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col + 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col + 1));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Up
			if (it->row > 0)
				if (grid[it->row - 1][it->col] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row - 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row - 1][it->col] != obstacle)
				{
					oss.str("");
					oss << it->row - 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row - 1, it->col));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Left
			if (it->col > 0)
				if (grid[it->row][it->col - 1] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col - 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col - 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col - 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col - 1));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
		}
	}
	return false;
}
template <typename A, typename B>
pair<B, A> flip_pair(const pair<A, B> &p)
{
	return pair<B, A>(p.second, p.first);
}

template <typename A, typename B, typename Compare = std::less<typename iterator_traits<B>::value_type>>
multimap<B, A, Compare> flip_map(const map<A, B> &src)
{
	multimap<B, A, Compare> dst;
	ranges::transform(src, inserter(dst, dst.begin()), flip_pair<A, B>);
	return dst;
}
/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 * This is more useful to check matching grids compared to using DisJointSet
 */
size_t ConnectedCellsInAGridLinkedList(vector<vector<long>> &grid)
{
	map<string, shared_ptr<Node<string>>> nodes;
	set<shared_ptr<LinkedList<string>>> clusters;
	ostringstream location, oss;
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == 1)
			{
				location.str("");
				location << i << "," << j;
				// Node<string>* node = new Node<string>(location.str());
				shared_ptr<Node<string>> node(make_shared<Node<string>>(location.str()));
				// nodes[location.str()] = shared_ptr<Node<string>>(node);
				nodes[location.str()] = node;
				shared_ptr<Node<string>> parent = nullptr;
				set<shared_ptr<LinkedList<string>>> joins;
				bool skip = false;
				// Upper Left
				if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1)
				{
					oss.str("");
					oss << i - 1 << "," << j - 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Up
				if (i > 0 && grid[i - 1][j] == 1)
				{
					oss.str("");
					oss << i - 1 << "," << j;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Upper Right
				if (i > 0 && j < grid[0].size() - 1 && grid[i - 1][j + 1] == 1)
				{
					oss.str("");
					oss << i - 1 << "," << j + 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Left
				if (j > 0 && grid[i][j - 1] == 1)
				{
					oss.str("");
					oss << i << "," << j - 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Right
				if (j < grid[0].size() - 1 && grid[i][j + 1] == 1)
				{
					oss.str("");
					oss << i << "," << j + 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Join the overlapping clusters
				if (!joins.empty() && joins.size() > 1)
				{
					set<shared_ptr<LinkedList<string>>>::iterator it = joins.begin();
					set<shared_ptr<LinkedList<string>>>::iterator joinTo = clusters.find(*it++); // Get the first cluster from "clusters" and join the others to it
					for (; it != joins.end(); it++)
					{
						set<shared_ptr<LinkedList<string>>>::iterator it1 = clusters.find(*it);
						(*joinTo)->Join(**it1);
						clusters.erase(*it1);
					}
				}
				if (!skip)
					clusters.emplace(make_shared<LinkedList<string>>(node));
				joins.clear();
			} // if (grid[i][j] == 1) {
		}
	cout << clusters.size() << " clusters" << endl;
	size_t max = 0;
	for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end(); it++)
	{
		vector<string> d;
		(*it)->ToVector(d); // This is useful to find matching grids
		//(*it)->Print();
		cout << "vector: ";
		ranges::copy(d, ostream_iterator<string>(cout, " "));
		cout << endl;
		// cout << "Length: " << (*it)->Length() << endl;
		if ((*it)->Length() > max)
			max = (*it)->Length();
	}
	nodes.clear();
	clusters.clear();
	return max;
}
/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 */
size_t ConnectedCellsInAGrid(vector<vector<long>> &grid)
{
	vector<long> data(grid.size() * grid[0].size());
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	DisJointSet<long> disjointSet(data);
	size_t width = grid[0].size();
	map<long, size_t> counts;
	size_t max = 0;
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == 1)
			{
				max = 1;
				long node = i * width + j + 1;
				long currentRoot = disjointSet.Find(node);
				// Upper Left
				if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1)
				{
					long neighbour = (i - 1) * width + j;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Up
				if (i > 0 && grid[i - 1][j] == 1)
				{
					long neighbour = (i - 1) * width + j + 1;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Upper Right
				if (i > 0 && j < grid[0].size() - 1 && grid[i - 1][j + 1] == 1)
				{
					long neighbour = (i - 1) * width + j + 2;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Left
				if (j > 0 && grid[i][j - 1] == 1)
				{
					long neighbour = i * width + j;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Right
				if (j < grid[0].size() - 1 && grid[i][j + 1] == 1)
				{
					long neighbour = i * width + j + 2;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
			} // if (grid[i][j] == 1) {
		} // for (size_t j = 0; j < grid[0].size(); j++) {
	for (map<long, size_t>::iterator it = counts.begin(); it != counts.end(); it++)
	{
		// cout << "Length: " << it->second << endl;
		if (it->second > max)
			max = it->second;
	}
	disjointSet.Print(data, grid[0].size());
	map<long, vector<long>> sets;
	disjointSet.GetSets(data, sets);
	for (map<long, vector<long>>::const_iterator it = sets.begin(); it != sets.end(); it++)
	{
		cout << it->first << ": ";
		ranges::copy(it->second, ostream_iterator<long>(cout, " "));
		cout << endl;
	}
	return max;
}
/* https://leetcode.com/problems/word-search/
 * 100%
 */
bool WordExistsInGrid(vector<vector<char>> &board, string const &word)
{
	for (size_t i = 0; i < board.size(); i++)
		for (size_t j = 0; j < board[i].size(); j++)
			if (WordExistsInGrid(board, word, i, j, 0))
				return true;
	return false;
}
bool WordExistsInGrid(vector<vector<char>> &board, string const &word, long row, long col, size_t offset)
{
	if (row < 0 || col < 0 || row >= (long)board.size() || col >= (long)board[row].size() || offset >= word.size() || word[offset] != board[row][col])
		return false;
	if (offset == word.size() - 1)
		return true;
	board[row][col] ^= 0x80; // "visited" mark
	bool flag = WordExistsInGrid(board, word, row, col + 1, offset + 1) ||
				WordExistsInGrid(board, word, row + 1, col, offset + 1) ||
				WordExistsInGrid(board, word, row, col - 1, offset + 1) ||
				WordExistsInGrid(board, word, row - 1, col, offset + 1);
	board[row][col] ^= 0x80; //
	return flag;
}
// 0 0 1 0 1
// 0 0 0 0 0
// 0 1 1 1 1
// 0 1 1 0 0
// Start: y:1 x:4 End: y: 0 x: 3=> true

// 0 0 1 1 1
// 0 1 0 0 0
// 1 1 1 1 1
// 0 0 0 0 1
// Start: y:0 x:0 End: y: 2 x: 1  => false
bool PathExists(vector<vector<char>> &grid, size_t r, size_t c, size_t y, size_t x, queue<string> &result, char obstacle)
{
	string pos, origin;
	ostringstream oss, oss1;
	set<string> visited;
	map<string, string> routes;
	vector<position_t> positions;
	positions.push_back(position_t(r, c));
	oss << r << c;
	origin = oss.str();
	oss.str("");
	while (!positions.empty())
	{
		vector<position_t> nextHops(positions);
		positions.clear();
		for (vector<position_t>::const_iterator it = nextHops.begin(); it != nextHops.end(); it++)
		{
			oss1.str("");
			oss1 << it->row << it->col;
			// Go Down
			if (it->row + 1 < grid.size())
				if (it->row + 1 == y && it->col == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row + 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row + 1][it->col] != obstacle)
				{ // Obstacle. Cancel this route
					oss.str("");
					oss << it->row + 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row + 1, it->col));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Right
			if (it->col + 1 < grid[it->row].size())
				if (it->row == y && it->col + 1 == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col + 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col + 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col + 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col + 1));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Up
			if (it->row > 0)
				if (it->row - 1 == y && it->col == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row - 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row - 1][it->col] != obstacle)
				{
					oss.str("");
					oss << it->row - 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row - 1, it->col));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Left
			if (it->col > 0)
				if (it->row == y && it->col - 1 == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col - 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && routes.find(pos) != routes.end())
					{
						pos = routes[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col - 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col - 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col - 1));
						routes.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
		}
	}
	return false;
}
// Divide the array(+ve and -ve numbers) into two parts such that the average of both the parts is equal.
//
// Assume that such splitting exists.
//
// Let then N be array length, Sum - sum of entire array, P - sum of one part of items, K - count of numbers in that part.
// Let's write equations for averages in both parts of array:
//
// P / K = (Sum - P) / (N - K)
// P * (N - K) = K * (Sum - P)
// P * N - P * K = K * Sum - K * P
// P * N = K * Sum
// P = K * Sum / N
void EqualAverageDivide(vector<long> &data, vector<long> &left)
{
	long sum = 0, P = 0;
	size_t N = data.size(), K;
	// Sort the data
	ranges::sort(data);
	sum = parallel_reduce(
		blocked_range<size_t>(0, data.size()), 0,
		[&](tbb::blocked_range<size_t> const &r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); ++i)
				running_total += data[i];
			return running_total;
		},
		std::plus<long>());
	for (K = 1; K < (N - K); K++)
	{
		if (((K * sum) % N)) //  check if such P can be integer (we operate with array of integers).
			continue;
		// picking K integers with sum of P from sorted array of integers
		P = K * sum / N;
		if (GetSum(data, K, P, 0, left))
			break;
	}
}
bool GetSum(vector<long> &data, size_t K, long P, size_t index, vector<long> &left)
{
	if (!P)
		return K == 0;
	else if (!K)
		return P == 0;
	else if (index >= data.size())
		return false;
	for (size_t i = index; i < data.size(); i++)
	{
		if (GetSum(data, K - 1, P - data[i], i + 1, left))
		{
			left.push_back(data[i]);
			return true;
		}
	}
	return false;
}
// Question was "Given a pattern and a string input - find if the string follows the same pattern and return 0 or 1.
// Examples:
// 1) Pattern: "abba" (.+)(.+)\\2\\1 input : "redbluebluered" should return 1.
// 2) Pattern: "aaaa" (.+)\\1\\1\\1  input : "asdasdasdasd" should return 1.
// 3) Pattern: "aabb" (.+)\\1(.+)\\2 input : "xyzabcxyzabc" should return 0.
// 3) Pattern: "abab" (.+)(.+)\\1\\2 input : "xyzabcxyzabc" should return 1.
bool match(string const &pattern, string const &input)
{
	map<char, long> patternCount;
	ostringstream regexStr;
	long captureGroup = 0;
	for (string::const_iterator it = pattern.begin(); it != pattern.end(); it++)
	{
		if (patternCount.find(*it) != patternCount.end())
			regexStr << "\\" << patternCount[*it];
		else
		{
			patternCount.emplace(*it, ++captureGroup);
			regexStr << "(.+)";
		}
	}
	return regex_match(input.begin(), input.end(), regex(regexStr.str()));
}
string EncodeString(string str)
{
	ostringstream oss;
	map<char, long> codes;
	long code = 0;
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (codes.find(*it) == codes.end())
			codes.emplace(*it, code++);
		oss << codes[*it];
	}
	return oss.str();
}
// Given a pattern and a dictionary, print out all the strings which match the pattern
// where a char in the pattern maps uniquely to a char in the dictionary.
// Eg: 'abc' <'cdf', 'too', 'hgfdt', 'paa'> => 'cdf'
// Eg: 'acc' <'cdf', 'too', 'hgfdt', 'paa'> => 'too', 'paa'
void FindPattern(string pattern, set<string> &dictionary, set<string> &result)
{
	string encodedPattern = EncodeString(pattern);
	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
		if (it->size() == pattern.size() && !encodedPattern.compare(EncodeString(*it)))
			result.insert(*it);
}
string GetRange(vector<long> &input)
{
	ostringstream oss;
	vector<long> numbers(input);
	ranges::sort(numbers);
	if (!numbers.empty())
	{
		size_t first = 0;
		for (size_t i = 1; i < numbers.size(); i++)
			if ((numbers[i] - numbers[i - 1]) > 1)
			{
				oss << numbers[first];
				if (first != i - 1)
					oss << " - " << numbers[i - 1] << ", ";
				else
					oss << ", ";
				first = i;
			}
		oss << numbers[first];
		if (first != numbers.size() - 1)
			oss << " - " << numbers.back();
	}
	return oss.str();
}
/* https://leetcode.com/problems/merge-intervals/
 * 100%
 */
vector<vector<long>> MergeIntervals(vector<vector<long>> &intervals)
{
	vector<vector<long>> result;
	// Sort the 2D vector in ascending order of the first element.
	ranges::sort(intervals, [](const vector<long> &a, const vector<long> &b)
				 { return a[0] < b[0]; });
	for (size_t i = 0; i < intervals.size(); i++)
	{
		if (!i)
			result.push_back(intervals[i]);
		else if (intervals[i][1] < result.back()[0] || intervals[i][0] > result.back()[1])
			result.push_back(intervals[i]);
		else if (intervals[i][0] <= result.back()[0])
		{
			result.back()[0] = intervals[i][0];
			if (intervals[i][1] >= result.back()[1])
				result.back()[1] = intervals[i][1];
		}
		else if (intervals[i][0] <= result.back()[1] && intervals[i][1] > result.back()[1])
			result.back()[1] = intervals[i][1];
	}
	return result;
}
bool isSparseNumber(long i)
{
	long previous2digits = 0;
	for (; i > 0; i = i >> 2)
	{
		if (((i & 3) == 1 && previous2digits == 2) || (i & 3) == 3)
			return false;
		previous2digits = i & 3;
	}
	return true;
}
long NextSparseNumber(long number)
{
	long i = number;
	long shift;
	for (shift = 0; i > 0; shift++, i = i >> 1)
	{
		if (!(i & 3))
			return i + (1 << shift);
		else if ((i & 7) == 1)
			return 1 << (shift + 1) > number ? 1 << (shift + 1) : number - (1 << shift) + (1 << (shift + 1));
	}
	return number == 0 ? 1 : 1 << (shift + 1);
}
// a and b are streams of integer from LSB to MSB
// Assume a >= b
string subtract(istream &a, istream &b)
{
	ostringstream oss;
	char i, j;
	while (b.read(&j, 1))
	{
		a.read(&i, 1);
		oss << i - j;
	}
	cout << "Result : " << oss.str() << endl;
	return oss.str();
}
void split(string const &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		elems.push_back(item);
}
// file: "This is a dog"
// 0: This is a
// 1: is a dog
set<string> process(string const &str, int n)
{
	vector<string> words;
	set<string> ngrams;
	::split(str, ' ', words);
	for (size_t i = 0; i <= words.size() - n; i++) // i: 0, 1
	{
		string s;
		for (size_t j = i; j < (i + n); j++)
		{ // j: [0,2] [1,3]: "This is a", "is a dog"
			s.append(words[j]);
			if (j != i + n - 1)
				s.append(" ");
		}
		ngrams.emplace(s);
	}
	return ngrams;
}
set<string> intersectionNgram(string const &str1, string const &str2, int n)
{
	set<string> result;
	set<string> ngrams1 = process(str1, n);
	if (ngrams1.empty())
		return result;
	cout << "str1 " << n << "-grams: ";
	for (set<string>::const_iterator it = ngrams1.begin(); it != ngrams1.end(); it++)
		cout << quoted(*it) << ", ";
	cout << endl;
	set<string> ngrams2 = process(str2, n);
	cout << "str2 " << n << "-grams: ";
	for (set<string>::const_iterator it = ngrams2.begin(); it != ngrams2.end(); it++)
		cout << quoted(*it) << ", ";
	cout << endl;
	set_intersection(ngrams1.begin(), ngrams1.end(), ngrams2.begin(), ngrams2.end(), inserter(result, result.begin()));
	return result;
}
vector<int> Increment(vector<int> &data)
{
	int j = 1;
	vector<int> result;
	for (vector<int>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
	{
		j += *it;
		if (j < 10)
		{
			result.push_back(j);
			j = 0;
		}
		else
		{
			result.push_back(j - 10);
			j = 1;
		}
	}
	if (j == 1)
		result.push_back(j);
	reverse(result.begin(), result.end());
	return result;
}
vector<string> numbersegments(vector<long> &data)
{
	ostringstream oss;
	vector<string> result;
	oss << data.front();
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++)
		if (it == (data.end() - 1) || *it != (*(it + 1) - 1))
		{
			if (!oss.str().empty())
				oss << '-';
			oss << *it;
			result.push_back(oss.str());
			oss.str("");
		}
		else if (oss.str().empty())
			oss << *it;
	return result;
}
/*
sizeof(void*) = 4
Align 4: alignment - 1 = 3
1 : 1 + 3 = 4 / 4 = 1
2 : 2 + 3 = 5 / 4 = 1
3 : 3 + 3 = 6 / 4 = 1
4 : 4 + 3 = 7 / 4 = 1

5 : 5 + 3 = 8 / 4 = 2
6 : 6 + 3 = 9 / 4 = 2
7 : 7 + 3 = 10 / 4 = 2
8 : 8 + 3 = 11 / 4 = 2

9 : 9 + 3 = 12 / 4 = 3
10 : 10 + 3 = 13 / 4 = 3
*/
void *alignedMalloc(size_t size, size_t alignment)
{
	size_t bytes = alignment / 8;
	return malloc(size + (size % bytes) / bytes);
}
void alignedFree(void **p)
{
	free(*p);
	*p = nullptr;
}
template <typename URNG>
void TestURNG(URNG &urng)
{
	// Uniform distribution used with vector
	// Distribution is [-5, 5] inclusive
	uniform_int_distribution<long> dist(-5, 5);
	vector<long> v(20);
	ranges::generate(v, [&]
					 { return dist(urng); });
	cout << "Randomized vector: ";
	ranges::copy(v, ostream_iterator<long>(cout, " "));
	cout << endl;

	// Shuffle an array.
	// Notice that shuffle() takes an URNG, not a distribution
	vector<string> strings = {{"H", "He", "Li", "Be", "B", "C", "N", "O", "F",
							   "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc",
							   "Ti", "V", "Cr", "Mn", "Fe"}};
	shuffle(strings.begin(), strings.end(), urng);
	cout << "Randomized vector<string>: ";
	ranges::copy(strings, ostream_iterator<string>(cout, " "));
	cout << endl;
}
void TestRandom()
{
	// First run: non-seedable, non-deterministic URNG random_device
	// Slower but crypto-secure and non-repeatable.
	random_device device;
	cout << "Using random_device URNG:" << endl;
	uniform_int_distribution<long> dist(-5, 5);
	vector<long> v(20);
	ranges::generate(v, [&]
					 { return dist(device); });
	TestURNG(device);

	// Second run: simple integer seed. Repeatable results
	cout << "Using constant-seed mersene twister engine URNG:" << endl;
	mt19937_64 constant_seed_mersene_twister_engine{12345};
	TestURNG(constant_seed_mersene_twister_engine);

	// Third run: random_device as seed; different each run.
	// Desirable for most purposes
	cout << "Using non-deterministic-seed mersene twister engine URNG:" << endl;
	mt19937_64 non_deterministic_seed_mersene_twister_engine{device()};
	TestURNG(non_deterministic_seed_mersene_twister_engine);

	// Fourth run: "warm-up" sequence as as seed; different each run.
	// Advanced uses. Allows more than 32 bits of randomness.
	cout << "Using non-deterministic-seed \"warm-up\" sequence mersene twister engine URNG" << endl;
	vector<unsigned int> seeds(mt19937_64::state_size);
	cout << "mt19937_64::state_size: " << mt19937_64::state_size << endl;
	ranges::generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 non_deterministic_seed_sequence_mersene_twister_engine{sequence};
	TestURNG(non_deterministic_seed_sequence_mersene_twister_engine);
}
long concat(vector<long> &data)
{
	ostringstream oss;
	ranges::sort(data, [](long i, long j) -> bool
				 {
		ostringstream a, b;
		a << i << j;
		b << j << i;
		return a.str() < b.str(); });
	for (vector<long>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
		oss << *it;
	long result;
	istringstream(oss.str()) >> result;
	return result;
}
/* https://leetcode.com/problems/largest-number/
 * {10, 2} => 210
 * {3,30,34,5,9} => 9534330
 *
 * Use string comparator to decide which goes before the other:
 * lhs: 12
 * rhs: 10
 * lhsrhs = 1210
 * rhslhs = 1012
 *
 * lhsrhs < rhslhs : lhs goes after rhs
 * lhsrhs > rhslhs : lhs goes before rhs
 *
 * 100%
 */
string buildmax(vector<size_t> &a)
{
	bool nonZero = false;
	multiset<string, buildmax_comparator_t> data;
	for (vector<size_t>::iterator it = a.begin(); it != a.end(); it++)
	{
		if (*it > 0)
			nonZero = true;
		data.insert(to_string(*it));
	}
	ostringstream oss;
	for (multiset<string, buildmax_comparator_t>::iterator it = data.begin(); it != data.end(); it++)
		oss << *it;
	return oss.str().empty() || !nonZero ? "0" : oss.str();
}
long MaxLengths(vector<string> &data)
{
	ranges::sort(data, [](string a, string b)
				 { return a.size() > b.size(); });
	for (vector<string>::const_iterator it = data.begin(); it != data.end(); it++)
		for (vector<string>::const_iterator it1 = it + 1; it1 != data.end(); it1++)
		{
			size_t i = 0;
			for (; i < it1->size(); i++)
				if (it->find(it1[i]) != string::npos) // Check if *it has it1[i] character
					break;
			if (i != it1->size() - 1)
				return it->size() * it1->size();
		}
	return 0;
}
void ExceptionTest()
{
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw..." << endl;
			throw; // Throw the original e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw..." << endl;
			e.msg_ = "Second Throw";
			throw; // throw the original e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw e..." << endl;
			throw e; // Throw the new e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw e..." << endl;
			e.msg_ = "Second throw";
			throw e; // Throw the new e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
}
// Count number of '1' bits
size_t Count1Bits(long a)
{
	size_t count = 0;
	for (long i = 1; i <= a; i <<= 1)
		if (i & a)
			count++;
	return count;
}
/* Returns a sequence of bit patterns with increasing number of '1' bits
 * k: total number of bits in the bit patterns
 */
void BitCombinations(size_t k, vector<long> &result)
{
	for (size_t i = 0; i <= k; i++)
		for (long j = (1 << i) - 1; j < (1 << k); j++)
			if (Count1Bits(j) == i)
				result.push_back(j);
}
/* https://leetcode.com/problems/gray-code/
 * 100%
 */
vector<size_t> grayCode(size_t n)
{
	// 00, 01
	// 10, 10
	// 00 01 11 10

	// 000, 001
	// 010, 010
	// 100, 100
	// 000 001 011 010 110 111
	size_t i = 1;
	vector<size_t> result;
	result.push_back(0);
	for (; n > 0; n--, i <<= 1)
		for (int j = result.size() - 1; j >= 0; j--)
			result.push_back(result[j] | i);
	return result;
}
void OrderedMergedCombinations(set<string> &result, string const &s1, string const &s2, string cur)
{
	if (s1.empty() && s2.empty())
	{
		result.insert(cur);
		return;
	}
	else if (s1.empty() || s2.empty())
	{
		result.insert(s1.empty() ? cur + s2 : cur + s1);
		return;
	}
	/*
	 * s1: Hey, ey,    y,  ""
	 * s2: Bob, Bob, Bob, Bob
	 * cur: "",  H,   He, Hey  => HeyBob
	 *                     ""
	 *                     ob
	 *                    HeBy => HeByob
	 *                     ""
	 *                      b
	 *                  HeBoy  => HeBoyb
	 *                     ""
	 *                     ""
	 *                  HeBoby => HeBoby
	 */
	for (size_t i = 0; i <= s2.size(); i++) // Same result as below
		OrderedMergedCombinations(result, s1.substr(1, s1.size() - 1), s2.substr(i, s2.size() - i), cur + s2.substr(0, i) + s1[0]);
	// for (size_t i = 0; i <= s1.size(); i++) // Same result as above
	//	OrderedMergedCombinations(result, s1.substr(i, s1.size() - i), s2.substr(1, s2.size() - 1), cur + s1.substr(0, i) + s2[0]);
}
/*
k: 2
i: 1
comb: 1

k: 1
i: 2
comb: 1,2 combs: {{1,2}}
comb: 1
i: 3
comb: 1,3 combs: {{1,2}, {1,3}}
comb: 1
i: 4
comb: 1,4 combs: {{1,2}, {1,3}, {1,4}}
comb: 1

k: 2
i: 2
comb: 2

k: 1
i: 3
comb: 2,3 combs: {{1,2}, {1,3}, {1,4}, {2,3}}
comb: 2
i: 4
comb: 2,4 combs: {{1,2}, {1,3}, {1,4}, {2,3}, {2,4}}
comb: 2

k: 2
i: 3
comb: 3

k: 1
i: 4
comb: 3,4 combs: {{1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4}}
comb: 3

k: 2
i: 4
comb: 4

k: 1
i: 4
comb: 4 combs: {{1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4}}
comb: {}
* C=1, L: O(count), Other: O(n) n: end-start
* #nodes = O(count).
* TC = O(count * n)
*/
void numberCombinations1(size_t start, size_t end, size_t count, vector<size_t> &comb, vector<vector<size_t>> &result)
{
	if (!count)
		result.push_back(comb);
	else
	{
		for (size_t i = start; i <= end; i++)
		{
			comb.push_back(i);
			numberCombinations1(i + 1, end, count - 1, comb, result);
			comb.pop_back();
		}
	}
}
/* https://leetcode.com/problems/combinations/
 * 100%
 */
void numberCombinations(size_t n, size_t k, vector<vector<size_t>> &result)
{
	vector<size_t> comb;
	numberCombinations1(1, n, k, comb, result);
}
/*A zero-indexed array A consisting of N integers is given. A triplet(P, Q, R) is triangular if it is possible to build a triangle with sides of lengths A[P], A[Q] and A[R].
 * In other words, triplet(P, Q, R) is triangular if 0 ≤ P < Q < R < N and:
 *
 * A[P] + A[Q] > A[R],
 * A[Q] + A[R] > A[P],
 * A[R] + A[P] > A[Q].
 *
 * For example, consider array A such that :
 * A[0] = 10    A[1] = 2    A[2] = 5
 * A[3] = 1     A[4] = 8    A[5] = 12
 * There are four triangular triplets that can be constructed from elements of this array, namely(0, 2, 4), (0, 2, 5), (0, 4, 5), and (2, 4, 5).
 */
size_t CountTriangles(vector<long> &data)
{
	size_t result = 0;
	if (data.size() < 3)
		return 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = i + 1; j < data.size(); j++)
		{
			for (size_t k = j + 1; k < data.size(); k++)
			{
				if (data[i] + data[j] > data[k] &&
					data[j] + data[k] > data[i] &&
					data[k] + data[i] > data[j])
					result++;
			}
		}
	}
	return result;
}
string decimal_to_binary(long decimal)
{
	if (decimal > 0)
	{
		ostringstream oss;
		long remainder = decimal % 2;
		oss << decimal_to_binary(decimal / 2);
		oss << remainder;
		return oss.str();
	}
	return "0";
}
long binary_to_decimal(string const &binary)
{
	long result = 0;
	size_t shift = 0;
	for (long i = binary.size() - 1; i >= 0; i--)
	{
		if (binary[i] == '1')
			result += (1 << shift);
		if (binary[i] == '0' || binary[i] == '1')
			shift++;
	}
	return result;
}
void decimal_to_binary(long decimal, vector<bool> &binary, size_t width)
{
	binary.resize(width, false);
	for (long i = width - 1; i >= 0 && decimal; i--)
	{
		binary[i] = decimal & 1;
		decimal >>= 1;
	}
}
// Find longest sequence of zeros in binary representation of an integer.
// 9: 1001 => 2
// 529: 1000010001  => 4
// 32: 100000 => 0
size_t binary_gap(long n)
{
	bool start = false;
	int count = 0, max = 0;
	bitset<32> x(n);
	for (size_t i = 0; i < x.size(); i++)
	{
		if (start && x[i] == 0)
			count++;
		else if (x[i] == 1)
		{
			if (count > max)
				max = count;
			count = 0;
			start = true;
		}
	}
	return max;
}
/*
 * For a given array A of N integers and a sequence S of N integers from the set{ −1, 1 }, we define val(A, S) as follows:
 * val(A, S) = | sum{ A[i] * S[i] for i = 0..N−1 } |
 * (Assume that the sum of zero elements equals zero.)
 * For a given array A, we are looking for such a sequence S that minimizes val(A, S).
 * Write a function that, given an array A of N integers, computes the minimum value of val(A, S) from all possible values of val(A, S) for all possible sequences S of N integers from the set{ −1, 1 }.
 * For example, given array:
 * A = { 1,5, 2,-2}
 * S = {-1,1,-1, 1}
 * val:{-1,5, 2, 0}
 * your function should return 0, since for S = [−1, 1, −1, 1], val(A, S) = 0, which is the minimum possible value.
 */
long MinAbsSum(vector<long> &data)
{
	long sum = 0;
	long min = numeric_limits<long>::max();
	for (size_t i = 0; i < ((size_t)1 << data.size()); i++)
	{
		vector<bool> binary;
		decimal_to_binary(i, binary, data.size()); // Permutations of {-1,1} for all the bit patterns
		for (size_t j = 0; j < binary.size(); j++)
			sum += (binary[j] ? -1 : 1) * data[j];
		if (abs(sum) < min)
			min = abs(sum);
		sum = 0;
	}
	return min;
}
/*
 * You are a game developer working on a game that randomly generates levels. A level is an undirected graph of rooms, each connected by doors.
 * The player starts in one room, and there is a treasure in another room. Some doors are locked, and each lock is opened by a unique key.
 * A room may contain one of those unique keys, or the treasure, or nothing. Implement a representation for a level and write code that,
 * given a level and starting room, returns true if the treasure can be reached by the player—likely requiring them to find certain other keys first—or
 * false if there is no solution.
 */
void PlayTreasureGame()
{
	TreasureGame game;
	Room a(false), b(1), c(3), d(-1), e(2), f(true);
	a.addDoor(&b);
	b.addDoor(&c, 6);
	a.addDoor(&c, 1);
	a.addDoor(&d, 1);
	d.addDoor(&e, 3);
	e.addDoor(&f, 7);
	// cout << "Start with room a " << game.hasTreasure(&a) << endl;
	assert(!game.hasTreasure(&a));
	c.addDoor(&f, 2);
	// cout << "Start with room a " << game.hasTreasure(&a) << endl;
	assert(game.hasTreasure(&a));
}
// Given a matrix of N * M, given the coordinates(x, y) present in a matrix,
// Find the number of paths that can reach(0, 0) from the(x, y) points with k steps(requires exactly k, k> = 0)
// From each point you can go up, down, left and right in four directions.
//  https://www.geeksforgeeks.org/check-if-it-is-possible-to-move-from-0-0-to-x-y-in-exactly-k-steps/
// For example, the following matrix :
//----------
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
//(x, y) = (1, 1), k = 2, the output is 2
const long moves[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
size_t countPaths(size_t m, size_t n, size_t x, size_t y, size_t k)
{
	// It is clear that the shortest path to reach (0, 0) from (x, y) will be minMoves = (|x| + |y|)
	// if K ≥ minMoves then after reaching (0, 0) in minMoves number of moves the remaining (K – minMoves) number of moves have to be even in order to
	// remain at that point for the rest of the moves.
	size_t minMoves = x + y;
	if (k >= minMoves && !((k - minMoves) % 2) && x < m && y < n)
	{
		if (k == 0 && x == 0 && y == 0)
			return 1;
		size_t sum = 0;
		// cout << "sizeof(moves): " << sizeof(moves) << ", sizeof(decltype(moves[0])): " << sizeof(decltype(moves[0])) << endl;
		for (size_t i = 0; i < sizeof(moves) / sizeof(decltype(moves[0])); i++)
			sum += countPaths(m, n, x + moves[i][0], y + moves[i][1], k - 1);
		return sum;
	}
	return 0;
}
vector<shared_ptr<Node<string>>> shortest_cycle_path(shared_ptr<Node<string>> node)
{
	map<shared_ptr<Node<string>>, shared_ptr<Node<string>>> parents;
	deque<shared_ptr<Node<string>>> q(1, node);
	while (!q.empty())
	{
		shared_ptr<Node<string>> n = q.front();
		q.pop_front();
		for (set<shared_ptr<Node<string>>>::iterator i = n->m_adjacents.begin(); i != n->m_adjacents.end(); i++)
		{
			if (parents.find(*i) == parents.end())
			{
				parents.emplace(*i, n);
				if (*i == node)
				{
					q.clear();
					break;
				}
				else
					q.push_back(*i);
			}
		}
	}
	// Build path
	vector<shared_ptr<Node<string>>> path;
	shared_ptr<Node<string>> current = node;
	do
	{
		path.push_back(current);
		current = parents[current];
	} while (current && current != node);
	if (path.size() == 1 && !current) // current == nullptr : no cycle
		path.clear();
	reverse(path.begin(), path.end());
	return path;
}
// given a binary array, you can flip 0 -> 1 or 1 -> 0 to make all the 1
// are in the left part and all the 0 to the right part, return the minimun flip required
// example 1
// 1011000  -> 1111000 only need one flip 0 -> 1
// example 2
// 00001 -> 10000 require 2 flips
int findMinFlip(vector<int> &binary)
{
	size_t count = 0, last_left = -1, last_right = -1;
	size_t left = 0, right = binary.size() - 1;
	for (; left < right;)
	{
		if (binary[left] == 0)
			last_left = left;
		else if (last_left != -1 && last_left != left)
		{
			count += left - last_left;
			last_left = -1;
		}
		if (binary[right] == 1)
			last_right = right;
		else if (last_right != -1 && last_right != right)
		{
			count += last_right - right;
			last_right = -1;
		}
		left++;
		right--;
	}
	if (last_left != -1 && last_left != left)
		count += left - last_left;
	if (last_right != -1 && last_right != right)
		count += last_right - right;
	return count;
}
// The matrix is valid if there is no consecutive 3 elements with the same value.
bool IsValidMatrix(vector<vector<char>> const &data)
{
	for (size_t row = 0; row < data.size(); row++)
		for (size_t col = 0; col < data[row].size(); col++)
		{
			if (row <= (data.size() - 3) && data[row][col] == data[row + 1][col] && data[row][col] == data[row + 2][col])
				return false;
			if (col <= (data[row].size() - 3) && data[row][col] == data[row][col + 1] && data[row][col] == data[row][col + 2])
				return false;
		}
	return true;
}
// https://app.codility.com/programmers/task/zig_zag_escape/
// Given a sequence S of integers, find a number of increasing sequences I such that every two consecutive elements in I appear in S, but on the opposite sides of the first element of I.
// Unfinished work!
// Task Score: 18 %
// Correctness: 44 %
// Performance: 0 %
size_t ZigZagEscape(vector<long> &data)
{
	vector<zigzag_t> zigzag;
	set<set<int>> result;
	for (size_t i = 0; i < data.size(); i++)
	{
		zigzag_t zz(i, data[i]);
		zigzag.push_back(zz);
	}
	ranges::sort(zigzag, {}, &zigzag_t::value);
	for (size_t i = 0; i < zigzag.size(); i++)
	{
		bool wasSmaller = false;
		bool isFirst = true;
		set<int> r;
		r.emplace(zigzag[i].value);
		result.emplace(r);
		for (size_t k = 1; k < (zigzag.size() - i); k++)
		{
			r.clear();
			r.emplace(zigzag[i].value);
			for (size_t j = i + k, isFirst = true; j < zigzag.size(); j++)
			{
				// cout << "i: " << i << ", j: " << j << ", k: " << k << endl;
				if (isFirst)
				{
					isFirst = false;
					wasSmaller = zigzag[j].index < zigzag[i].index;
					r.emplace(zigzag[j].value);
					// ranges::copy(r, ostream_iterator<size_t>(cout, " "));
					// cout << endl;
					result.emplace(r);
				}
				else if (wasSmaller && zigzag[j].index > zigzag[i].index)
				{
					wasSmaller = !wasSmaller;
					r.emplace(zigzag[j].value);
					// ranges::copy(r, ostream_iterator<size_t>(cout, " "));
					// cout << endl;
					result.emplace(r);
				}
				else if (!wasSmaller && zigzag[j].index < zigzag[i].index)
				{
					wasSmaller = !wasSmaller;
					r.emplace(zigzag[j].value);
					// ranges::copy(r, ostream_iterator<size_t>(cout, " "));
					// cout << endl;
					result.emplace(r);
				}
				else
				{
					set<int> tmp(r);
					tmp.erase(zigzag[j - 1].value);
					tmp.emplace(zigzag[j].value);
					result.emplace(tmp);
					// cout << "No result! i:" << zigzag[i].index << " " << zigzag[i].value << ", j: " << zigzag[j].index << " " << zigzag[j].value << endl;
				}
			}
		}
	}
#if 0
	cout << "Final: " << endl;
	for (set<set<int>>::const_iterator it = result.begin(); it != result.end(); it++) {
		ranges::copy(*it, ostream_iterator<size_t>(cout, " "));
		cout << endl;
	}
#endif
	return result.size();
}
size_t ZigZagEscape(vector<long> &data, set<string> &strResult)
{
	long current;
	vector<string> tmp;
	ostringstream oss;
	vector<long> left, right;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (i > 0)
			left.assign(data.begin(), data.begin() + i);
		if (i != data.size() - 1)
			right.assign(data.begin() + i + 1, data.end());
		ranges::sort(left);
		ranges::sort(right);
		current = data[i];
		strResult.insert(to_string(current));
		// Start with left
		for (size_t j = 0; j < left.size(); j++)
		{
			if (left[j] > current)
			{
				if (right.empty())
				{
					oss << current << " " << left[j];
					strResult.insert(oss.str());
					oss.str("");
				}
				else
				{
					tmp = ZigZagEscape(left, right, j, 0, current, true);
					ranges::copy(tmp, inserter(strResult, strResult.end()));
				}
			}
		}
		// Start with right
		for (size_t j = 0; j < right.size(); j++)
		{
			if (right[j] > current)
			{
				if (left.empty())
				{
					oss << current << " " << right[j];
					strResult.insert(oss.str());
					oss.str("");
				}
				else
				{
					tmp = ZigZagEscape(left, right, 0, j, current, false);
					ranges::copy(tmp, inserter(strResult, strResult.end()));
				}
			}
		}
		// Clean up
		left.clear();
		right.clear();
	}
	return strResult.size();
}
vector<string> ZigZagEscape(vector<long> &left, vector<long> &right, size_t lIndex, size_t rIndex, long current, bool dir)
{ // 4, 6, 2, 1, 5
	long next;
	vector<string> result, tmp;
	ostringstream oss;
	if (dir && left.size())
	{ // left
		for (; lIndex < left.size(); lIndex++)
		{
			if (left[lIndex] > current)
			{
				next = left[lIndex];
				result.push_back(to_string(current));
				tmp = ZigZagEscape(left, right, lIndex, rIndex, next, !dir);
				if (!tmp.empty())
				{
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						oss << current << " " << *it;
						result.push_back(oss.str());
						oss.str("");
					}
				}
				else
				{
					// Only take current value if the other side is empty.
					oss << current << " " << next;
					result.push_back(oss.str());
				}
				oss.str("");
			}
		}
	}
	else if (right.size())
		for (; rIndex < right.size(); rIndex++)
			if (right[rIndex] > current)
			{
				next = right[rIndex];
				result.push_back(to_string(current));
				tmp = ZigZagEscape(left, right, lIndex, rIndex, next, !dir);
				if (!tmp.empty())
				{
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						oss << current << " " << *it;
						result.push_back(oss.str());
						oss.str("");
					}
				}
				else
				{
					oss << current << " " << next;
					result.push_back(oss.str());
				}
				oss.str("");
			}
	return result;
}
/* https://app.codility.com/demo/results/trainingCP4NRT-FE4/
 * https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/discuss/119835/Java-O(n)-DP-Solution
 * 100%
 * index               0    1    2    3    4
 * A                   1    3    5    4    9
 * B                   1    2    3    7    10
 * swapRecord          0    1    2    1    2
 * fixRecord           0    0    0    2    1	(swap = 1)
 *
 * index               0    1    2    3    4
 * A                   1    3    5    4    9 (Impossible)
 * B                   1    2    3    10   8
 * swapRecord          0    1    2    1    2
 * fixRecord           0    0    0    2    2
 *
 * index               0    1    2    3    4
 * A                   1    3    5    10   9
 * B                   1    2    3    8    7 (Impossible)
 * swapRecord          0    1    2    1    2
 * fixRecord           0    0    0    0    0
 *
 * index               0    1    2
 * A                   1    3    5
 * B                   1    2    3
 * swapRecord          0    1    2
 * fixRecord           0    0    0 (swap = 0)
 *
 */
size_t IncreasingSequences(vector<long> &a, vector<long> &b)
{
	bool outOfSequence = false, isSwap = false;
	// swapRecord[i]: min swaps to make A[0:i] and B[0:i] increasing if we swap A[i] and B[i]
	// fixRecord[i] : min swaps to make A[0:i] and B[0:i] increasing if we do not swap A[i] and B[i]
	size_t swapRecord = 0, fixRecord = 0;
	if (a.size() != b.size())
		return -1;
	if (a.size() == 1)
		return 0;
	vector<long> A, B;
	A.push_back(a[0]);
	B.push_back(b[0]);
	for (size_t i = 1; i < a.size(); i++)
	{
		if (a[i - 1] >= b[i] || b[i - 1] >= a[i])
			// In this case, the ith manipulation should be same as the i-1th manipulation
			swapRecord++;
		else if (a[i - 1] >= a[i] || b[i - 1] >= b[i])
		{
			// In this case, the ith manipulation should be the opposite of the i-1th manipulation
			size_t temp = swapRecord;
			swapRecord = fixRecord + 1;
			fixRecord = temp;
			isSwap = !isSwap; // Because "opposite"
		}
		else
		{
			// Either swap or fix is OK. Let's keep the minimum one
			isSwap = swapRecord > fixRecord;
			size_t minimum = min(swapRecord, fixRecord);
			swapRecord = minimum + 1;
			fixRecord = minimum;
		}
		A.push_back(isSwap ? b[i] : a[i]);
		B.push_back(isSwap ? a[i] : b[i]);
		outOfSequence |= A[i] <= A[i - 1] || B[i] <= B[i - 1];
	}
	return outOfSequence ? -1 : min(swapRecord, fixRecord);
}
/*
   https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem
   100%
   https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
1. If A[i] is smallest among all end candidates of active lists, we will start
   new active list of length 1.
2. If A[i] is largest among all end candidates of active lists, we will clone the largest active
   list, and extend it by A[i].
3. If A[i] is in between, we will find a list with largest end element that is smaller than A[i].
   Clone and extend this list by A[i]. We will discard all other lists of same length as this modified list.
[1 2 5 3]
[1]
[1 2] <- Rule (2)
[1 2 5] <- Rule (2)
[1 2 3] <- Rule (3) Discard [1 2 5]

[1 2 5 6 3 4]
[1]
[1 2] 		<- Rule (2)
[1 2 5 6]	<- Rule (2)
[1 2 3]		<- Rule (3)
[1 2 3 4]   <- Rule (2)

[1 2 3 6]   <- Rule (3) Discard [1 2 5 6]
[1 2 3 4] 	<- Rule (3) Discard [1 2 5 6]

3, 2, 4, 1, 5
[3]
[2]
[2 4] or [3 4] => [2 4 5] or [3 4 5]
[1]
[1 4]
[1 4 5]

0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 => 0 2 6 9 13 15
[0]
[0 8]
[0 4]
[0 4 12]
[0 2 12]
[0 2 10]
[0 2 6]
[0 2 6 14]
[0 1 6 14]
[0 1 6 9]
[0 1 5 9]
[0 1 5 9 13]
[0 1 3 9 13]
[0 1 3 9 11]
[0 1 3 7 11]
[0 1 3 7 11 15]
*/
size_t LongestIncreasingSubsequenceNlogN(vector<size_t> &data)
{
	vector<size_t> tails; // Note: This records the tails of the subsequences. Not the actual longest increasing subsequence!
	if (!data.empty())
	{
		tails.push_back(data[0]);
		for (vector<size_t>::iterator it = data.begin(); it != data.end(); it++)
		{
			vector<size_t>::iterator it1 = lower_bound(tails.begin(), tails.end(), *it); // Look for element >= data[i]
			if (it1 != tails.end())														 // *it1 >= data[i]
				*it1 = *it;																 // *it1 = data[i]
			else
				tails.push_back(*it);
		}
	}
	return tails.size();
}
/*
[1 2 5 3]
[1]
[2]
[5]
[5 3]

[1 2 5 6 3 4]
[1]
[2]
[5]
[6]
[6 3]
[6 4]

3, 2, 4, 1, 5 => 3 2 1
[3]
[3 2]
[4 2]
[4 2 1]
[5 2 1]

0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 => 12 10 9 5 3
[0]
[8]
[8 4]
[12 4]
[12 4 2]
[12 10 2]
[12 10 6]
[14 10 6]
[14 10 6 1]
[14 10 9 1]
[14 10 9 5]
[14 13 9 5]
[14 13 9 5 3]
[14 13 11 5 3]
[14 13 11 7 3]
[15 13 11 7 3]
*/
size_t LongestDecreasingSubsequenceNlogN(vector<size_t> &data)
{
	vector<size_t> tails; // Note: This records the tails of the subsequences. Not the actual longest decreasing subsequence!
	if (!data.empty())
	{
		tails.push_back(data[0]);
		for (vector<size_t>::iterator it = data.begin(); it != data.end(); it++)
		{
			vector<size_t>::iterator it1 = ranges::find_if(tails, [it](const auto &value)
														   { return value <= *it; }); // Look for element <= data[i]
			if (it1 != tails.end())													  // *it1 <= data[i]
				*it1 = *it;
			else
				tails.push_back(*it);
		}
	}
	return tails.size();
}

bool IncreasingTriplet(vector<size_t> &data)
{
	vector<size_t> tails;
	if (!data.empty())
	{
		for (vector<size_t>::iterator it = data.begin(); it != data.end(); it++)
		{
			vector<size_t>::iterator it1 = lower_bound(tails.begin(), tails.end(), *it); // Look for element >= data[i]
			if (it1 != tails.end())														 // *it1 > data[i]
				*it1 = *it;																 // *it1 = data[i]
			else
				tails.push_back(*it);
		}
	}
	return tails.size() >= 3;
}
// https://stackoverflow.com/questions/6877249/find-the-number-of-occurrences-of-a-subsequence-in-a-string
size_t FindSubsequenceRecursive(string const &str, string const &tomatch)
{
	size_t result = 0;
	if (tomatch.empty())
		return 1;
	else if (str.empty())
		return 0;
	if (str[0] == tomatch[0])
		result += FindSubsequenceRecursive(str.substr(1), tomatch.substr(1)) + FindSubsequenceRecursive(str.substr(1), tomatch);
	else
		result += FindSubsequenceRecursive(str.substr(1), tomatch);
	return result;
}
/*
* s: "1221", tomatch: "12"
* s1 is tomatch1
* 				j:0	j:1(s1=2)	j:2(s1=12)
				0	1			2
i:0			0	1	0			0
i:1(s=1)	1	1	0			0
i:2(s=21)	2	1	1			0
i:3(s=221)	2	1	2			0
i:4(s=1221)	1	1	2			2
*
* https://en.wikipedia.org/wiki/Binomial_coefficient: (n!)/k!(n - k)!
* s: kkkkkk s1: kkkk = 6 choose 4 = 6! / 4! * 2! = 15
* s: kkkkkk s1: kkkkk = 6 choose 5 = 6! / 5! = 6
* s: DeadBeef s1: FeedBeef
* 				j:0	j:1(s1=f)	j:2(s1=ef)	j:3(s1=eef)	j:4(s1=Beef) j:5(s1=dBeef)	j:6(s1=edBeef)	j:7(s1=eedBeef)	j:8(s1=FeedBeef)
i:0				1	0			0			0			0			 0				0				0				0
i:1(s=f)		1   1			0			0			0			 0				0				0				0
i:2(s=ef)		1   1			1			1			0			 0				0				0				0
i:3(s=eef)		1	1			2			2			0			 0				0				0				0
i:4(s=Beef)		1	1			2			2			1			 0				0				0				0
i:5(s=dBeef)	1	1			2			2			1			 1				0				0				0
i:6(s=adBeef)	1	1			2			2			1			 1				0				0				0
i:7(s=eadBeef)	1	1			3			3			1			 1				1				0				0
i:8(s=DeadBeef)	1	1			3			3			1			 1				1				0				0
*/
size_t FindSubsequenceDynamicProgramming(string const &str, string const &tomatch)
{
	if (tomatch.empty())
		return 1;
	else if (str.empty())
		return 0;
	vector<vector<size_t>> counts(str.size() + 1, vector<size_t>(tomatch.size() + 1)); // Add one dimension for the empty element which is the base case
	for (size_t i = 0; i <= str.size(); i++)
	{
		string s = str.substr(str.size() - i, i);
		for (size_t j = 0; j <= tomatch.size(); j++)
		{
			string tomatch1 = tomatch.substr(tomatch.size() - j, j);
			if (tomatch1.empty())
				counts[i][j] = 1;
			else if (s.empty())
				counts[i][j] = 0;
			else if (i > 0 && j > 0)
			{
				counts[i][j] = counts[i - 1][j]; // Preserve previously matched character
				if (s[0] == tomatch1[0])
					counts[i][j] += counts[i - 1][j - 1]; // It's a match! Increment from last match count.
			}
		}
	}
	return counts[str.size()][tomatch.size()];
}
void cpluplus17()
{
	map<int, string> mymap;
	// Structured bindings
	// Return compound objects
	auto [it, success] = mymap.emplace(1, "Hello World!!!");
	assert(success);
	assert(it->first == 1);
	assert(it->second == "Hello World!!!");
	// Compound object iterations
	for (const auto &[key, value] : mymap)
		cout << key << ": " << value << endl;
	// Direct Initialization
	for (auto [i, ch] = pair(0U, ' '); i < 10; i++, ch++)
		cout << "[" << i << ": '" << ch << "'] ";
	cout << endl;
}
long MaxProductOfThree(vector<long> &data)
{
	ranges::sort(data);
	long tmp1 = data[0] * data[1];
	long tmp2 = data[data.size() - 2] * data[data.size() - 3];
	if (data.back() > 0)
		return data.back() * (tmp1 > tmp2 ? tmp1 : tmp2);
	else
		return data.back() * (tmp1 < tmp2 ? tmp1 : tmp2);
}
/*
 * 1 2 3 4 5, n = 2
 * 5 4 3 2 1, reverse the whole vector
 * 4 5 3 2 1, reverse [0,n-1]
 * 4 5 1 2 3, reverse [n,data.size()-1]
 *
 * https://www.hackerrank.com/challenges/circular-array-rotation/problem
 * 100%
 */
void RotateRightArray(vector<int> &data, int n)
{
	n %= data.size();
	reverse(data.begin(), data.end());
	reverse(data.begin(), data.begin() + n);
	reverse(data.begin() + n, data.end());
}
/*
 * https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem?
 * 100%
 */
vector<int> RotateLeftArray(vector<int> &a, int d)
{
	vector<int> result;
	for (size_t i = 0; i < a.size(); i++)
		result.push_back(a[(i + d) % a.size()]);
	return result;
}

/*
 * https://app.codility.com/programmers/lessons/5-prefix_sums/count_div/
 * Pending. Only 87%
 */
size_t CountDiv(size_t a, size_t b, size_t k)
{
	if (b < a || k > b)
		return 0;
	else if (b == a)
		return !(a % k) ? 1 : 0;
	else if (k == 1)
		return b - a + 1;
	else if (!a && k == b)
		return 2;
	else
	{
		// size_t multiples = (b - a + 1) / k;
		//  n * k >= a => n >= a / k
		// size_t first = round(a / k);
		// size_t last = first + k * multiples;
		// return (last + multiples <= b) ? multiples++ : multiples;
		double result = ((double)b - (double)a + (double)1) / (double)k;
		return !(k % 10) ? floor(result) : round(result);
	}
}
/*
 * https://app.codility.com/programmers/lessons/12-euclidean_algorithm/chocolates_by_numbers/
 * Correctness: 100%
 * 87% due to timeout. For example: ChocolatesByNumbers(415633212, 234332);
 */
long ChocolatesByNumbers(long n, long m)
{
	long count = 0;
	if (n <= 0 || m <= 0)
		return 0;
	else if (n == 1 && m > n)
		return 1;
	else if (m == 1)
		return n;
	else if (m == 2)
		return n / 2;
	long greatestCommonDivisor = gcd(n, m);
	long N = n / greatestCommonDivisor;
	long M = m / greatestCommonDivisor;
	for (long i = 0; i < N;)
	{
		count++;
		i += M;
		i %= N;
		if (!i)
			break;
	}
	return count;
}
/*
 * https://www.hackerrank.com/challenges/frequency-queries/problem
 * 5/15 failed
 * Test case 5 data included in solution as queryFrequencyInput.txt
 */
vector<int> freqQuery(vector<vector<int>> &queries)
{
	unordered_map<int, int> frequency;	 // frequency of data
	unordered_map<int, int> frequencies; // frequeny of frequency
	vector<int> result;
	for (size_t i = 0; i < queries.size(); i++)
	{
		switch (queries[i][0])
		{
		case 1: // Insert
		{
			frequency[queries[i][1]]++;
			frequencies[frequency[queries[i][1]]]++;
		}
		break;
		case 2: // Remove
			if (frequency.find(queries[i][1]) != frequency.end())
			{
				if (--frequencies[frequency[queries[i][1]]] <= 0)
					frequencies.erase(frequency[queries[i][1]]);
				frequency[queries[i][1]]--;
			}
			break;
		case 3: // Find frequency
		{
			int j = frequencies.find(queries[i][1]) != frequencies.end() ? 1 : 0;
			result.push_back(frequencies.find(queries[i][1]) != frequencies.end() ? 1 : 0);
		}
		break;
		default:
			break;
		}
	}
	return result;
}
/*
 * https://www.hackerrank.com/challenges/encryption/problem
 * 100%
 */
string encryption(string &s)
{
	vector<vector<char>> result;
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	size_t row = floor(sqrt(s.size()));
	size_t col = ceil(sqrt(s.size()));
	for (; col * row < s.size();)
		if (row < col)
			row++;
		else
			col++;
	for (size_t i = 0; i < row; i++)
	{
		string str = s.substr(i * col, col);
		vector<char> chars(str.begin(), str.end());
		for (size_t j = str.size(); j < (size_t)col; j++)
			chars.push_back('\0');
		result.push_back(chars);
	}
	ostringstream oss;
	for (size_t i = 0; i < col; i++)
	{
		for (size_t j = 0; j < row && result[j][i] != '\0'; j++)
			oss << result[j][i];
		if (i < col - 1)
			oss << ' ';
	}
	return oss.str();
}
/*
 * https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem
 * 100%
 */
vector<size_t> ClimbLeaderBoard(vector<long> &scores, vector<long> &alice)
{
	vector<size_t> result;
	ranges::sort(scores);
	auto unique = ranges::unique(scores);
	scores.erase(unique.begin(), unique.end());
	for (size_t i = 0; i < alice.size(); i++)
	{
		vector<long>::iterator it = upper_bound(scores.begin(), scores.end(), alice[i]); // Look for element > alice[i]
		result.push_back(distance(it, scores.end()) + 1);
		scores.insert(it, alice[i]);
	}
	return result;
}
long CalculateMedian(vector<long> &data)
{
	const auto middleItr = data.begin() + data.size() / 2; // +data.size() % 2;
	nth_element(data.begin(), middleItr, data.end());
	if (!(data.size() % 2))
	{
		const auto leftMiddleItr = ranges::max_element(data.begin(), middleItr);
		return (*leftMiddleItr + *middleItr) / 2;
	}
	return *middleItr;
}
string TimeInWords(size_t h, size_t m)
{
	static map<int, string> numbers = {
		{1, "one"},
		{2, "two"},
		{3, "three"},
		{4, "four"},
		{5, "five"},
		{6, "six"},
		{7, "seven"},
		{8, "eight"},
		{9, "nine"},
		{10, "ten"},
		{11, "eleven"},
		{12, "twelve"},
		{13, "thirteen"},
		{14, "fourteen"},
		{15, "fifteen"},
		{16, "sixteen"},
		{17, "seventeen"},
		{18, "eighteen"},
		{19, "nineteen"},
		{20, "twenty"}};
	ostringstream str, hour;
	if (m == 0)
	{
		str << numbers[h] << " o' clock";
		return str.str();
	}
	else if (m == 15)
	{
		str << "quarter past " << numbers[h];
		return str.str();
	}
	else if (m == 30)
	{
		str << "half past " << numbers[h];
		return str.str();
	}
	else if (m == 45)
	{
		str << "quarter to " << numbers[h + 1];
		return str.str();
	}
	if (m > 30)
	{
		m -= 30;
		m = 30 - m;
		hour << " to " << numbers[h + 1];
	}
	else
		hour << " past " << numbers[h];
	if (m > 20)
		str << "twenty " << numbers[m % 20] << " minutes";
	else
		str << numbers[m] << (m > 1 ? " minutes" : " minute");
	str << hour.str();
	return str.str();
}
/* https://www.hackerrank.com/challenges/xor-quadruples/problem
 * WIP
 * 100% Functionality. However, time out as it is O(N^3)
 */
size_t BeautifulQuadruples(long a, long b, long c, long d)
{
	/*
		if a^b^c^d = 0 then a^b = c^d, therefore sort values to avoid duplications
	*/
	vector<long> abcd{a, b, c, d};
	ranges::sort(abcd);
	set<multiset<long>> quadruples;
	for (long i = 1; i <= abcd[0]; i++)
		for (long j = 1; j <= abcd[1]; j++)
			for (long k = 1; k <= abcd[2]; k++)
				for (long l = 1; l <= abcd[3]; l++)
					if ((i ^ j ^ k ^ l) != 0)
						quadruples.emplace(multiset<long>{i, j, k, l});
	return quadruples.size();
}
// https://www.hackerrank.com/challenges/red-knights-shortest-path/problem
// 100%
vector<string> findShortestPath(int n, int i_start, int j_start, int i_end, int j_end)
{
	vector<string> result;
	ostringstream oss;
	// Print the distance along with the sequence of moves.
	// UL, UR, R, LR, LL, L.
	size_t diff_i = abs(i_end - i_start), diff_j = abs(j_end - j_start);
	// Upper Left
	if (i_end < i_start && j_end < j_start)
	{
		if ((i_start - i_end) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		long uls = (i_start - i_end) / 2; // 6 / 2 = 3
		long dest_j = j_start - uls;	  // 6 - 3 = 3
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		long L = (dest_j - j_end) / 2;
		oss << uls + L;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < (size_t)uls; i++)
		{
			oss << "UL";
			if (i != uls - 1)
				oss << " ";
		}
		if (L)
			oss << " ";
		for (size_t i = 0; i < (size_t)L; i++)
		{
			oss << "L";
			if ((long)i < L - 1)
				oss << " ";
		}
	}
	// Upper Right
	else if (i_end < i_start && j_end > j_start)
	{
		if ((i_start - i_end) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int urs = (i_start - i_end) / 2; // 4 / 2 = 2
		int dest_j = j_start + urs;		 // 2 - 1 = 1
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int R = (j_end - dest_j) / 2; // (3 -
		oss << urs + R;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < (size_t)urs; i++)
		{
			oss << "UR";
			if ((long)i != urs - 1)
				oss << " ";
		}
		if (R)
			oss << " ";
		for (size_t i = 0; i < (size_t)R; i++)
		{
			oss << "R";
			if ((long)i < R - 1)
				oss << " ";
		}
	}
	// Lower Left
	else if (i_end > i_start && j_end < j_start)
	{
		if ((i_end - i_start) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int lls = (i_end - i_start) / 2;
		int dest_j = j_start - lls;
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int L = (dest_j - j_end) / 2;
		if (L >= 0)
		{
			oss << lls + L;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)lls; i++)
			{
				oss << "LL";
				if ((long)i != lls - 1)
					oss << " ";
			}
			if (L)
				oss << " ";
			for (size_t i = 0; i < (size_t)L; i++)
			{
				oss << "L";
				if ((long)i < L - 1)
					oss << " ";
			}
		}
		else
		{ // L < 0
			oss << lls;
			result.push_back(oss.str());
			oss.str("");
			for (int i = L; i < 0; i++)
			{
				oss << "LR";
				if (i < -1)
					oss << " ";
			}
			if (lls + L)
				oss << " ";
			for (size_t i = 0; i < (size_t)(lls + L); i++)
			{
				oss << "LL";
				if ((long)i != (lls + L - 1))
					oss << " ";
			}
		}
	}
	// Lower Right
	else if (i_end > i_start && j_end > j_start)
	{
		if ((i_end - i_start) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int lrs = (i_end - i_start) / 2;
		int dest_j = j_start + lrs;
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int R = (j_end - dest_j) / 2;
		if (R >= 0)
		{
			oss << lrs + R;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)R; i++)
			{
				oss << "R";
				if ((long)i < R - 1)
					oss << " ";
			}
			if (lrs)
				oss << " ";
			for (size_t i = 0; i < (size_t)lrs; i++)
			{
				oss << "LR";
				if ((long)i != lrs - 1)
					oss << " ";
			}
		}
		else
		{ // R < 0
			oss << lrs;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)(lrs + R); i++)
			{
				oss << "LR";
				if (i != (lrs + R - 1))
					oss << " ";
			}
			if (R < 0)
				oss << " ";
			for (int i = R; i < 0; i++)
			{
				oss << "LL";
				if (i < -1)
					oss << " ";
			}
		}
	}
	// UP
	else if (j_end == j_start && i_end < i_start)
	{
		size_t diff = i_start - i_end;
		if (diff % 4)
		{
			result.push_back("Impossible");
			return result;
		}
		else
		{
			oss << diff / 2;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (diff / 4); i++)
			{
				oss << "UL UR";
				if (i != (diff / 4) - 1)
					oss << " ";
			}
		}
	}
	// DOWN
	else if (j_end == j_start && i_end > i_start)
	{
		size_t diff = i_end - i_start;
		if (diff % 4)
		{
			result.push_back("Impossible");
			return result;
		}
		else
		{
			oss << diff / 2;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (diff / 4); i++)
			{
				oss << "LR LL";
				if (i != (diff / 4) - 1)
					oss << " ";
			}
		}
	}
	// Left
	else if (i_end == i_start && j_end < j_start)
	{
		if ((j_start - j_end) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		size_t L = (j_start - j_end) / 2;
		oss << L;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < L; i++)
		{
			oss << "L";
			if (i != L - 1)
				oss << " ";
		}
	}
	// Right
	else if (i_end == i_start && j_end > j_start)
	{
		if ((j_end - j_start) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		size_t R = (j_end - j_start) / 2;
		oss << R;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < R; i++)
		{
			oss << "R";
			if (i != R - 1)
				oss << " ";
		}
	}
	else
	{
		// Destination = start?
		oss << 0 << endl;
	}
	result.push_back(oss.str());
	return result;
}
/* https://www.hackerrank.com/challenges/kruskalmstrsub/problem
   https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
   https://stackoverflow.com/questions/1195872/when-should-i-use-kruskal-as-opposed-to-prim-and-vice-versa
   Kruskal can have better performance if the edges can be sorted in linear time, or are already sorted
   100%
*/
long kruskals(int nodes, vector<long> &from, vector<long> &to, vector<long> &weight)
{
	multiset<Edge> edges; // Sorted edges based on weights
	long sum = 0;
	for (size_t i = 0; i < weight.size(); i++)
		edges.emplace(Edge(weight[i], from[i], to[i]));
	DisJointSet<long> disjointSet(from); // Every vertex is a disjoint set
	disjointSet.MakeSet(to);
	for (multiset<Edge>::iterator it = edges.begin(); it != edges.end(); it++)
	{
		if (disjointSet.Find(it->node1) != disjointSet.Find(it->node2))
		{
			sum += it->weight;
			disjointSet.Union(it->node1, it->node2);
		}
	}
	return sum;
}
/* https://www.hackerrank.com/challenges/cut-the-tree/problem
 * Segmentation fault. Maybe due to recursion
 */
size_t MinSubGraphsDifference(vector<size_t> &vertices, vector<vector<size_t>> &edges)
{
	Graph<size_t, size_t> graph(vertices);
	for (vector<vector<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
	{
		shared_ptr<Vertex<size_t, size_t>> v1 = graph.GetVertex(vertices[(*it)[0] - 1]);
		shared_ptr<Vertex<size_t, size_t>> v2 = graph.GetVertex(vertices[(*it)[1] - 1]);
		assert(v1);
		assert(v2);
		graph.AddUndirectedEdge(v1, v2, 0);
	}
	shared_ptr<Vertex<size_t, size_t>> v = graph.GetVertex(650);
	if (v)
		graph.Print(v);
	size_t sum = parallel_reduce(
		blocked_range<size_t>(0, vertices.size()), 0,
		[&](tbb::blocked_range<size_t> const &r, size_t running_total)
		{
			for (int i = r.begin(); i < r.end(); ++i)
				running_total += vertices[i];
			return running_total;
		},
		std::plus<size_t>());
	size_t result = graph.MinSubGraphsDifference(vertices[0], sum);
	return result;
}
// https://www.hackerrank.com/challenges/jeanies-route/problem
// Times out for more than 100 nodes! ;)
long PostmanProblem(vector<long> &k, vector<vector<long>> &roads)
{
	Graph<long, long> graph;
	for (size_t i = 0; i < roads.size(); i++)
	{
		shared_ptr<Vertex<long, long>> v1 = graph.AddVertex(roads[i][0]);
		shared_ptr<Vertex<long, long>> v2 = graph.AddVertex(roads[i][1]);
		graph.AddUndirectedEdge(v1, v2, roads[i][2]);
	}
	set<vector<long>> paths;
	paths = permute(k);
	multimap<long, string> costs;
	ostringstream oss, oss1, oss2;
	map<string, long> costCache;
	for (set<vector<long>>::iterator it = paths.begin(); it != paths.end(); it++)
	{
		vector<long> path = *it;
		long totalCost = 0;
		bool isValidPath = true;
		for (size_t i = 0; i < path.size() - 1 && isValidPath; i++)
		{
			long cost = -1;
			oss1.str("");
			oss2.str("");
			oss1 << path[i] << "-" << path[i + 1];
			oss2 << path[i + 1] << "-" << path[i];
			if (costCache.find(oss1.str()) != costCache.end())
				cost = costCache[oss1.str()];
			else if (costCache.find(oss2.str()) != costCache.end())
				cost = costCache[oss2.str()];
			else
			{
				cost = graph.Dijkstra(path[i], path[i + 1]);
				costCache[oss1.str()] = cost;
				costCache[oss2.str()] = cost;
			}
			// cout << path[i] << " - " << path[i + 1] << ": " << cost << endl;
			if (cost >= 0)
				totalCost += cost;
			else
				isValidPath = false;
			oss << path[i] << "," << path[i + 1] << ",";
		}
		if (isValidPath)
		{
			costs.emplace(totalCost, oss.str());
			oss.str("");
		}
	}
	return costs.empty() ? -1 : costs.begin()->first;
}
/*
  https://www.hackerrank.com/challenges/cipher/problem
1001 011     shift 0
0100 1011    shift 1
0010 01011   shift 2
0001 001011  shift 3
-----------
1110 101001  <- XORed/encoded string s

1111 010     shift 0
0111 1010    shift 1
0011 11010   shift 2
0001 111010  shift 3
-----------
1010 110110  <- XORed/encoded string s

1101 101     shift 0
0110 1101    shift 1
0011 01101   shift 2
0001 101101  shift 3
-----------
1001 101001  <- XORed/encoded string s

0111 000     shift 0
0011 1001    shift 1
0001 11001   shift 2
0000 111001  shift 3
-----------
0101 101001  <- XORed/encoded string s

1010	  shift 0
0101 0	  shift 1
0010 10	  shift 2
0001 010  shift 3
0000 1010 shift 4
-----------
1100 0110

Observation:
	Result is derived from the encoded string s and the computed result so far. Intermediate shifted strings are distractions.
	result[0] = s[0]
	For i < k, result[i] = s[i - 1] == s[i] ? '0' : '1'
	For i >= k, result[i] = s[i - 1] == s[i] ? result[i - k] : result[i - k] == '1' ? '0' : '1'
100%
*/
string Cipher(size_t n, size_t k, string const &s)
{
	string result;
	if (!s.empty() && k <= s.size() && s.size() >= n)
	{
		result = s[0];
		for (size_t i = 1; i < n; i++)
		{
			if (i < k)
				result.push_back(s[i - 1] == s[i] ? '0' : '1');
			else
				result.push_back(s[i - 1] == s[i] ? result[i - k] : result[i - k] == '1' ? '0'
																						 : '1');
		}
	}
	return result;
}
// Encryption scheme:
// If s[i] is lowercase and s[i+1] is uppercase, swap them and add an asterik '*' after them
// If s[i] is a number, replace it with 0 and place the original number at the beginning.
// 100%
string DecryptPassword(string const &s)
{
	string result;
	long numbers = -1;
	for (size_t i = 0; i < s.size() && isdigit(s[i]) && s[i] != '0'; i++)
	{
		if (isdigit(s[i]) && s[i] != '0')
			numbers = i;
	}
	for (size_t i = numbers + 1; i < s.size();)
	{
		if (i < s.size() - 2 && isupper(s[i]) && islower(s[i + 1]) && s[i + 2] == '*')
		{
			result.push_back(s[i + 1]);
			result.push_back(s[i]);
			i += 3;
		}
		else if (s[i] == '0')
		{
			result.push_back(s[numbers--]);
			i++;
		}
		else
			result.push_back(s[i++]);
	}
	return result;
}
// https://www.hackerrank.com/challenges/sam-and-substrings/problem
// 100 %
unsigned long long substrings(string const &s)
{
	/*
	Example: "6789". Substrings: 6, 7, 8, 9, 67, 78, 89, 678, 789, 6789.
 Frequency in substrings at positions
Digit   Unit    Ten     Hundred     Thousand        Sum
6       1       1       1           1           = 6*1*1111
7       2       2       2                       = 7*2*111
8       3       3                               = 8*3*11
9       4                                       = 9*4*1

7: 7 * 100 * 2 + 7 * 10 * 2 + 7 * 2 = (7 * 2)(100 + 10 + 1) = 7 * 2 * 111
8: 8 * 10 * 3 + 8 * 3 = (8 * 3)(10 + 1) = 8 * 3 * 11

		s[i] * n * 11..1 (s.size() - n + 1 times '1').
	*/
	unsigned long long sum = 0;
	unsigned long long ones = 1;
	for (int i = s.size() - 1; i >= 0; i--)
	{
		sum += ((unsigned long long)s[i] - '0') * ones * (unsigned long long)(i + 1ull);
		ones = (ones * 10 + 1) % (unsigned long long)(1e9 + 7);
		sum %= (unsigned long long)(1e9 + 7);
	}
	return sum;
}
// https://www.hackerrank.com/challenges/absolute-permutation/problem
// 100%
vector<long> absolutePermutation(size_t n, size_t k)
{
	vector<long> sequence(n, 0);
	ranges::generate(sequence, [i = 1]() mutable
					 { return i++; });
	// |sequence[i] - i| = k
	vector<long> a;
	set<long> exists;
	for (size_t i = 1; i <= n; i++)
	{
		if (i > k && exists.find(i - k) == exists.end())
		{
			a.push_back(i - k);
			exists.insert(i - k);
		}
		else if (exists.find(i + k) == exists.end())
		{
			a.push_back(i + k);
			exists.insert(i + k);
		}
		else
			return vector<long>(1, -1);
	}
	vector<long> result(a);
	ranges::sort(a);
	return a == sequence ? result : vector<long>(1, -1);
}
// https://www.hackerrank.com/challenges/bomber-man/problem
// Times out!
vector<string> bomberMan(size_t n, vector<string> &grid)
{
	set<size_t> seconds;
	ostringstream oss;
	for (size_t second = 0; second <= n; second++)
	{
		if (!second)
		{
			// Initial state
			for (size_t i = 0; i < grid.size(); i++)
				for (size_t j = 0; j < grid[i].size(); j++)
				{
					if (grid[i][j] == 'O')
						grid[i][j] = '0'; // to detonate at third second. second % 3
				}
			seconds.insert(3);
			continue;
		}
		// After one second, Bomberman does nothing.
		if (second == 1)
			continue;
		if (seconds.find(second) != seconds.end())
		{ // Blow up!
			oss.str("");
			oss << second % 3;
			char pattern = oss.str()[0];
			for (size_t i = 0; i < grid.size(); i++)
				for (size_t j = 0; j < grid[i].size(); j++)
				{
					if (grid[i][j] == pattern)
					{
						grid[i][j] = '.';
						if (i > 0 && grid[i - 1][j] != pattern)
							grid[i - 1][j] = '.';
						if (i < grid.size() - 1 && grid[i + 1][j] != pattern)
							grid[i + 1][j] = '.';
						if (j > 0 && grid[i][j - 1] != pattern)
							grid[i][j - 1] = '.';
						if (j < grid[i].size() - 1 && grid[i][j + 1] != pattern)
							grid[i][j + 1] = '.';
					}
				}
			// cout << second << " (" << pattern << "): " << " blow up!" << endl;
			// for (size_t i = 0; i < grid.size(); i++)
			//     cout << grid[i] << endl;
		}
		else
		{ // Plant bombs
			oss.str("");
			oss << second % 3;
			char pattern = oss.str()[0];
			for (size_t i = 0; i < grid.size(); i++)
				for (size_t j = 0; j < grid[i].size(); j++)
				{
					if (grid[i][j] == '.')
						grid[i][j] = pattern; // to detonate at second + 2
				}
			seconds.insert(second + 3);
			// cout << second << " (" << pattern << "): " << " plant bombs!" << endl;
			// for (size_t i = 0; i < grid.size(); i++)
			//     cout << grid[i] << endl;
		}
	}
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] != '.')
				grid[i][j] = 'O'; // to detonate at third second. second % 3
		}
	return grid;
}
/*
 * https://leetcode.com/problems/longest-substring-without-repeating-characters
 * 100%
 * aaa -> 1
 * abcabc ->
 * dvdf -> vdf
 * abcabb
 * abcabcbb -> abc
 * pwwkew -> kew or wke
 * ohvhjdml ->
 * vqblqcb
 */
size_t LengthOfLongestUniqueSubstring(string const &s)
{
	size_t maxLength = 0;
	set<char> chars;
	string str;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (chars.find(s[i]) == chars.end())
		{
			str.append(1, s[i]);
			chars.insert(s[i]);
		}
		else
		{
			if (str.size() > maxLength)
				maxLength = str.size();
			chars.clear();
			size_t offset = str.find_first_of(s[i]) + 1;
			if (offset > str.size())
				str.clear();
			else
			{
				for (size_t j = offset; j <= str.size(); j++)
					chars.insert(str[j]);
				str = str.substr(offset);
			}
			chars.insert(s[i]);
			str.append(1, s[i]);
		}
	}
	return max(str.size(), maxLength);
}
/*
 * https://leetcode.com/problems/zigzag-conversion/
 * 100%
 */
string ZigZagConvert(string const &s, size_t numRows)
{
	bool direction = false;
	vector<string> str(numRows);
	for (long i = 0, row = 0; i < (long)s.size(); i++)
	{
		str[row].append(1, s[i]);
		if (!direction)
			row++;
		else
			row--;
		if (row == numRows)
		{
			row -= min((int)numRows, 2);
			direction = !direction;
		}
		else if (row < 0)
		{
			row += min((int)numRows, 2);
			direction = !direction;
		}
	}
	ostringstream oss;
	for (size_t i = 0; i < numRows; i++)
		oss << str[i];
	return oss.str();
}
/*
 * https://leetcode.com/problems/integer-to-roman/
 * 100%
 */
string numberToRoman(size_t num)
{
	string roman;
	size_t symbols;
	// >= 1000
	symbols = num / 1000;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'M');
	if (num >= 1000)
		num %= 1000;

	// 900 - 1000
	if (num >= 900)
	{
		roman.append("CM");
		num -= 900;
	}

	// 500 - 900
	if (num >= 500)
	{
		symbols = num / 500;
		for (size_t i = 0; i < symbols; i++)
			roman.append(1, 'D');
		num %= 500;
	}

	// 400 - 499
	if (num >= 400)
	{
		roman.append("CD");
		num -= 400;
	}

	// 100 -
	if (num >= 100)
	{
		symbols = num / 100;
		for (size_t i = 0; i < symbols; i++)
			roman.append(1, 'C');
		num %= 100;
	}

	// 90 - 99
	if (num >= 90)
	{
		roman.append("XC");
		num -= 90;
	}

	// 50 - 89
	if (num >= 50)
	{
		symbols = num / 50;
		for (size_t i = 0; i < symbols; i++)
			roman.append(1, 'L');
		num %= 50;
	}

	// 40 - 49
	if (num >= 40)
	{
		roman.append("XL");
		num -= 40;
	}
	symbols = num / 10;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'X');
	if (num >= 10)
		num %= 10;

	if (num == 9)
	{
		roman.append("IX");
		num -= 9;
	}

	if (num == 4)
	{
		roman.append("IV");
		num -= 4;
	}
	symbols = num / 5;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'V');
	if (num >= 5)
		num %= 5;

	symbols = num;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'I');
	return roman;
}
/*
* Calculate the median of 2 sorted lists of numbers in O(log (m+n))
* https://www.geeksforgeeks.org/median-two-sorted-arrays-different-sizes-ologminn-m/
Example (Even number of elements):
1 3 5 7 9
2 4 6 8 10

i: 5 / 2 = 2
j: (10 + 1) / 2 - 2 = 11 / 2 - 2 = 5 - 2 = 3
left: 5
right: 5

1 3		5 7 9
2 4 6	8 10
	 <-5 (Increase i)
	 6-> (Decrease j)
i++: 3
j: 11 / 2 - 3 = 5 - 3 = 2
1 3 5   7 9
2 4     6 8 10

median: (5+6) / 2 = 5.5
=================================
Example (Odd number of elements):
1 3 5 7 9
2 4 6 8 10 11

i: 5 / 2 = 2
j: (11 + 1) / 2 - 2 = 12 / 2 - 2 = 6 - 2 = 4
left: 6
right: 5
	left: 5
	right: 6

1 3		  5  7  9
2 4 6 8	  10 11
		<-5
		8->
i++: 3
j: 12/2 - 3 = 6 - 3 = 3
1 3 5	7 9
2 4 6	8 10 11
left: 6
right: 5

median: Max element in the LEFT (more counts compared to RIGHT): max(5,6) = 6
*/
double median(vector<long> &a, vector<long> &b)
{
	double result = 0;
	size_t minIndex = 0, maxIndex = min(a.size(), b.size());
	size_t count = a.size() + b.size();
	long i, j;
	if (a.empty() && b.empty())
		return result;
	else if (a.empty() && !b.empty())
		return b.size() % 2 ? b[b.size() / 2] : ((double)b[(b.size() / 2) - 1] + (double)b[b.size() / 2]) / (double)2;
	else if (!a.empty() && b.empty())
		return a.size() % 2 ? a[a.size() / 2] : ((double)a[(a.size() / 2) - 1] + (double)a[a.size() / 2]) / (double)2;
	for (bool found = false; minIndex <= maxIndex && !found;)
	{
		i = (minIndex + maxIndex) / 2;
		/*
		 * For add number, if no 1 is added, integer division by 2 will result in floor integer value.
		 * If 1 is added, integer division by 2 will result in ceiling integer value.
		 * For even number, adding 1 to the count does not affect integer division by 2 as floor integer value is the result.
		 * This will affect the algorithm to decide which partition to take for the odd number of elements.
		 */
		j = ((count + 1) / 2) - i;
		// If j < 0, adjust the number of elements from a included in the left partition
		if (j < 0)
		{
			maxIndex = i - 1; // Decreases i
			continue;
		}
		/* If i == a.size(), no element from a is included in the right partition
		 * If j == 0, no element from b is included in the left partition
		 */
		if (i < (long)a.size() && j > 0 && b[j - 1] > a[i])
			minIndex = i + 1; // i increases; j decreases
		/* If i == 0, no element from a is included in the left partition
		 * If j == b.size(), no element from b is included in the right partition
		 */
		else if (i > 0 && j < (long)b.size() && a[i - 1] > b[j])
			maxIndex = i - 1; // i decreases; j increases
		else
		{			// Found the desired partitions
			if (!i) // No element from a is incuded in the left partition
				result = b[j - 1];
			else if (!j)
				result = a[i - 1];
			else
				result = max(a[i - 1], b[j - 1]);
			found = true;
		}
	} // for
	if (count % 2) // Odd number of total elements in both the sorted list
		return result;
	else if (i == (long)a.size()) // No element from a is included in the right partition
		return (result + b[j]) / 2;
	else if (j == (long)b.size()) // No element from b is included in the right partition
		return (result + a[i]) / 2;
	return (result + min(a[i], b[j])) / 2;
}
/*
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/
 * 100%
 */
long ReversePolishNotation(vector<string> const &tokens)
{
	stack<long> numbers;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
		{
			long num2 = numbers.top();
			numbers.pop();
			long num1 = numbers.top();
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
			long num;
			istringstream(tokens[i]) >> num;
			numbers.push(num);
		}
	}
	return !numbers.empty() ? numbers.top() : numeric_limits<long>::max();
}
/*
3+2*2-1
sign:	+ + * -
stack:   3 2 4 -1 <= 3+4-1 = 6
3*2+2
sign:	+ * +
stack:	 3 6 2 <= 6+2 = 8
3+2-4*5
sign:	+ + -  *
stack:   3 2 -4 -20 <= 3+2-20
3*2+5/4
sign:	+ * + /
stack:   3 6 5 1 <= 6+1 = 7
*/
long BasicCalculator(string const &s)
{
	stack<long> numbers;
	char sign = '+';
	long num = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (isdigit(s[i]))
			num = num * 10 + s[i] - '0';
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || i == s.size() - 1)
		{
			switch (sign)
			{
			case '+':
				numbers.push(num);
				break;
			case '-':
				numbers.push(-num);
				break;
			case '*':
			{
				long n = numbers.top();
				numbers.pop();
				numbers.push(num * n);
				break;
			}
			case '/':
			{
				long n = numbers.top();
				numbers.pop();
				numbers.push(n / num);
				break;
			}
			default:
				throw runtime_error("Invalid arithmetic sign!");
			}
			num = 0;
			sign = s[i];
		}
	}
	if (!numbers.empty())
		for (; !numbers.empty(); num += numbers.top(), numbers.pop())
			;
	return num;
}
/* https://leetcode.com/problems/product-of-array-except-self/
 * 100%
 */
vector<long> productExceptSelf(vector<long> &nums)
{
	vector<long> result(nums.size(), 1);
	/*
		1 2 3 4
		1 1 2 6 <- Accumulate forward
	*/
	for (size_t i = 0; i < nums.size() - 1; i++)
		result[i + 1] = result[i] * nums[i];
	/*
	   1   2  3 4
	   24 24 12 4 <- Accumulate backward
	*/
	long productSum = 1;
	for (long i = nums.size() - 1; i >= 0; i--)
	{
		result[i] *= productSum;
		productSum *= nums[i];
	}
	return result;
}
/* https://leetcode.com/problems/h-index/
 * 100%
 */
size_t hIndex(vector<size_t> &citations)
{
	size_t result = 0;
	if (citations.size() == 1)
		return citations[0] > 0 ? 1 : 0;
	ranges::sort(citations);
	size_t previous = 0;
	/*
	 * [1,1] => value: 1, count: 2 => h: 1
	 * [1,2] => value: 1,2; count: 1 => h: 1
	 * [1,1,2] => value: 1, count 2 => h: 1
	 * [1,2,2] => value: 2, count: 2 => h: 2
	 * [3,2,2] => value: 2, count: 2 => h: 2
	 * [3,3,2] => value: 3, count: 2
	 */
	for (vector<size_t>::reverse_iterator it = citations.rbegin(); it != citations.rend(); it++)
	{
		if (*it != previous)
		{
			size_t value = *it;
			size_t count = ranges::count_if(citations, [&value](size_t i)
											{ return i >= value; });
			if (value < count && value > result)
				result = value;
			else if (value >= count && min(count, value) > result)
				result = min(count, value);
			previous = *it;
		}
	}
	return result;
}
/* https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * 100%
 */
void PhoneKeyLetters(string const &digits, vector<string> &result)
{
	map<char, string> letters{
		{'1', ""},
		{'2', "abc"},
		{'3', "def"},
		{'4', "ghi"},
		{'5', "jkl"},
		{'6', "mno"},
		{'7', "pqrs"},
		{'8', "tuv"},
		{'9', "wxyz"}};
	if (!digits.empty())
	{
		for (size_t i = 0; i < digits.size();)
		{
			vector<string> tmp;
			string str1 = letters[digits[i]];
			if (!i)
			{
				string str2 = i < digits.size() - 1 ? letters[digits[i + 1]] : "";
				if (str2.empty())
				{
					for (size_t j = 0; j < str1.size(); j++)
						tmp.push_back(string(1, str1[j]));
				}
				else
				{
					for (size_t j = 0; j < str1.size(); j++)
						for (size_t k = 0; k < str2.size(); k++)
						{
							ostringstream oss;
							oss << str1[j] << str2[k];
							tmp.push_back(oss.str());
						}
				}
				i += 2;
			}
			else
			{
				for (size_t j = 0; j < str1.size(); j++)
					for (vector<string>::iterator it = result.begin(); it != result.end(); it++)
					{
						ostringstream oss;
						oss << *it << str1[j];
						tmp.push_back(oss.str());
					}
				i++;
			}
			result = tmp;
		}
	}
}
/* https://leetcode.com/problems/word-break/
 * ["cats", "dog", "sand", "and", "cat"]
 * 012345678
 * catsandog
 * cats an dog
 * cat sand og
 *
 * 0123456789
 * catsanddog
 * cat sand dog
 * cats and dog
 *
 * Dynamic programming with tabulation (bottom-up) approach
 * if [0, end) is valid, all intermediate substrings which build up to [0, end) are also valid.
 * 0123456
 * catsand
 * [0,0) is valid -> [0,3) is valid -> [0,7) is valid
 * [0,0) is valid -> [0,4) is valid -> [0,7) is valid
 * 100%
 */
bool WordBreakDynamicProgramming(string const &s, set<string> const &words)
{
	vector<bool> valid(s.size() + 1, false);	 // flag to mark substring [0, end) validity
	valid[0] = true;							 // empty substring is a valid string
	for (size_t end = 1; end <= s.size(); end++) // O(N)
		for (size_t start = 0; start < end; start++)
		{ // O(N) -> Time complexity: O(N^2)
			if (valid[start] && words.find(s.substr(start, end - start)) != words.end())
			{
				valid[end] = true;
				break;
			}
		}
	return valid.back();
}
/* https://leetcode.com/problems/word-break-ii/
 * 100%
 */
void WordBreakDynamicProgramming(string const &s, set<string> const &words, vector<string> &result)
{
	map<size_t, vector<string>> strings;
	vector<bool> valid(s.size() + 1, false); // flag to mark substring [0, end) validity
	valid[0] = true;						 // empty substring is a valid string
	strings.emplace(0, vector<string>{""});
	for (size_t end = 1; end <= s.size(); end++)
		for (size_t start = 0; start < end; start++)
		{
			if (valid[start] && words.find(s.substr(start, end - start)) != words.end())
			{
				valid[end] = true;
				for (vector<string>::iterator it = strings[start].begin(); it != strings[start].end(); it++)
				{
					ostringstream oss;
					oss << *it << (it->empty() ? "" : " ") << s.substr(start, end - start);
					strings[end].push_back(oss.str());
				}
			}
		}
	if (strings.find(s.size()) != strings.end())
		result.insert(result.end(), strings[s.size()].begin(), strings[s.size()].end());
}
vector<string> WordBreakDFS(string const &s, set<string> const &words, map<string, vector<string>> &strings)
{
	vector<string> result;
	if (s.empty())
		return vector<string>{""};
	else if (strings.find(s) != strings.end())
		return strings[s];
	for (set<string>::iterator it = words.begin(); it != words.end(); it++)
	{
		size_t found = s.find(*it);
		if (found == 0)
		{
			vector<string> tmp = WordBreakDFS(s.substr(it->size()), words, strings);
			for (vector<string>::iterator it1 = tmp.begin(); it1 != tmp.end(); it1++)
			{
				ostringstream oss;
				oss << *it << (it1->empty() ? "" : " ") << *it1;
				result.push_back(oss.str());
			}
		}
	}
	if (!result.empty())
		strings.emplace(s, result);
	return result;
}
vector<string> WordBreakDFS(string const &s, set<string> const &words)
{
	map<string, vector<string>> strings;
	return WordBreakDFS(s, words, strings);
}
/* https://leetcode.com/problems/different-ways-to-add-parentheses/
 * 100%
 */
vector<long> diffWaysToCompute(string input)
{
	vector<long> result;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == '+' || input[i] == '-' || input[i] == '*')
		{
			vector<long> left = diffWaysToCompute(input.substr(0, i));
			vector<long> right = diffWaysToCompute(input.substr(i + 1));
			for (vector<long>::iterator it = left.begin(); it != left.end(); it++)
				for (vector<long>::iterator it1 = right.begin(); it1 != right.end(); it1++)
					switch (input[i])
					{
					case '+':
						result.push_back(*it + *it1);
						break;
					case '-':
						result.push_back(*it - *it1);
						break;
					case '*':
						result.push_back(*it * *it1);
						break;
					}
		}
	}
	if (result.empty())
	{
		long i;
		istringstream(input) >> i;
		result.push_back(i);
	}
	return result;
}
/* https://leetcode.com/problems/bulls-and-cows/
You are playing the Bulls and Cows game with your friend.

You write down a secret number and ask your friend to guess what the number is. When your friend makes a guess, you provide a hint with the following info:

The number of "bulls", which are digits in the guess that are in the correct position.
The number of "cows", which are digits in the guess that are in your secret number but are located in the wrong position. Specifically, the non-bull digits in the guess that could be rearranged such that they become bulls.
Given the secret number secret and your friend's guess guess, return the hint for your friend's guess.

The hint should be formatted as "xAyB", where x is the number of bulls and y is the number of cows. Note that both secret and guess may contain duplicate digits.
 * 100%
 */
string GetHint(string const &secret, string const &guess)
{
	map<char, long> counts;
	size_t bulls = 0, cows = 0;
	for (size_t i = 0; i < secret.size(); i++)
		counts[secret[i]]++;
	for (size_t i = 0; i < secret.size(); i++)
	{
		if (secret[i] == guess[i])
		{
			bulls++;
			if (--counts[secret[i]] < 0 && cows > 0)
				cows--;
		}
		else if (counts.find(guess[i]) != counts.end() && counts[guess[i]] > 0)
		{
			counts[guess[i]]--;
			cows++;
		}
	}
	ostringstream oss;
	oss << bulls << "A" << cows << "B";
	return oss.str();
}
/* https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
 * If we treat null's as leaves, then the binary tree will always be full. A full binary tree has a good property that # of leaves = # of nonleaves + 1.
 * Since we are given a pre-order serialization, we just need to find the shortest prefix of the serialization sequence satisfying the property above.
 * If such prefix does not exist, then the serialization is definitely invalid; otherwise, the serialization is valid if and only if the prefix is the entire sequence.
 * 100%
 */
bool IsValidPreOrderTreeSerialization(string const &preorder)
{
	vector<string> tokens;
	::split(preorder, ',', tokens);
	size_t leaves = 0, nonLeaves = 0, i = 0;
	for (; i < tokens.size() && leaves != nonLeaves + 1; i++)
	{
		if (tokens[i][0] == '#')
			leaves++;
		else
			nonLeaves++;
	}
	return leaves == nonLeaves + 1 && i == tokens.size();
}
/* https://leetcode.com/problems/integer-break/
 * 100%
 */
size_t LargestNumberCompositionProductWithDynamicProgramming(size_t n)
{
	vector<size_t> dp(n + 1, 0);
	dp[1] = 1;
	for (size_t i = 2; i <= n; i++)
		for (size_t j = 1; j < i; j++)
			dp[i] = max(dp[i], max(j, dp[j]) * max(i - j, dp[i - j]));
	return dp[n];
}
/* https://leetcode.com/problems/reconstruct-itinerary/
 * https://en.wikipedia.org/wiki/Eulerian_path
 * 100%
 * { {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"} }
 * (1) JFK -> ATL
 * (2) ATL -> JFK
 * (3) JFK -> SFO
 * (4) SFO -> ATL
 * (5) ATL -> SFO
 * JFK -> ATL -> JFK -> SFO -> ATL -> SFO
 */
vector<string> FindItinerary(vector<vector<string>> &tickets, string const &start)
{
	map<string, multiset<string>> vertices;
	vector<string> itinerary;
	for (vector<vector<string>>::iterator it = tickets.begin(); it != tickets.end(); it++)
		vertices[it->front()].insert(it->back());
	if (vertices.find(start) != vertices.end())
		EulerianPath(start, vertices, itinerary);
	reverse(itinerary.begin(), itinerary.end());
	return itinerary;
}
void EulerianPath(string vertex, map<string, multiset<string>> &vertices, vector<string> &path)
{
	for (; !vertices[vertex].empty();)
	{
		string next = *vertices[vertex].begin();
		vertices[vertex].erase(vertices[vertex].begin());
		EulerianPath(next, vertices, path);
	}
	path.push_back(vertex);
}
/* The minimum amount of attempts to determine the pivot floor at and above which the egg breaks when dropped.
* Base case:
* 1 egg: conservatively try every single floor from bottom to top.
* 0 floor: 0 attempt
* 1 floor: 1 attempt
*
* 2 possibilities:
* Egg broken: 1 egg less, #floors = #floors - 1
* Egg not broken: Same eggs, #floors = #floors - floors tried so far
*
*		2 Eggs, 4 floors					<= for (size_t floor = 2; floor <= floors; floor++)
*    f=1		f=2			f=3		  f=4	<= for (size_t i = 2; i <= floor; i++)
* (1,0)(2,3) (1,1)(2,2) (1,2)(2,1) (1,3)(2,0)
*
* (2,3): f=1       f=2			f=3			<= for (size_t i = 2; i <= floor; i++)
*       (1,0)(2,2) (1,1)(2,1)  (1,2)(2,0)
*
* (2,2): f=1       f=2						<= for (size_t i = 2; i <= floor; i++)
*       (1,0)(2,1) (1,1)(2,0)
*
* (1,2): f=1       f=2						<= for (size_t i = 2; i <= floor; i++)
*       (0,0)(1,1) (0,1)(1,0)
*
* (1,3): f=1       f=2			f=3			<= for (size_t i = 2; i <= floor; i++)
*       (0,0)(1,2) (0,1)(1,1)  (0,2)(1,0)
* https://medium.com/@parv51199/egg-drop-problem-using-dynamic-programming-e22f67a1a7c3
Eggs\Floors	0	1	2	3	4	5	6
		1	0	1	2	3	4	5	6
		2	0	1
		3	0	1
* https://leetcode.com/problems/super-egg-drop/
* Time limit exceeded! :-(
*/
size_t EggDrops(size_t eggs, size_t floors)
{
	vector<vector<size_t>> dp(eggs, vector<size_t>(floors + 1, numeric_limits<size_t>::max()));
	// Base case for Floor-0 and Floor-1
	for (size_t i = 0; i < eggs; i++)
	{
		dp[i][0] = 0;
		if (floors > 0)
			dp[i][1] = 1;
	}
	// Base case for 1 egg
	ranges::generate(dp[0], [n = 0]() mutable
					 { return n++; });
	// size_t attempts = eggDropsDynamicProgramming(eggs, floors, dp);
	for (size_t egg = 1; egg < eggs; egg++)
		for (size_t floor = 2; floor <= floors; floor++)
			for (size_t i = 2; i <= floor; i++)
				dp[egg][floor] = min(dp[egg][floor], 1 + max(dp[egg - 1][i - 1], dp[egg][floor - i]));
	return dp[eggs - 1][floors];
}
/*
 * https://en.wikipedia.org/wiki/Fizz_buzz
 * https://leetcode.com/problems/fizz-buzz/submissions/
 * 100%
 */
vector<string> fizzBuzz(size_t n)
{
	vector<string> result;
	for (size_t i = 1; i <= n; i++)
	{
		ostringstream oss;
		if (!(i % 3))
			oss << "Fizz";
		if (!(i % 5))
			oss << "Buzz";
		string str = oss.str();
		if (str.empty())
			str = to_string(i);
		result.push_back(str);
	}
	return result;
}
/*
 * https://www.hackerrank.com/challenges/rust-murderer/problem
 * Time out and wrong answer. WIP.
 */
vector<size_t> UnbeatenPaths(size_t n, vector<vector<size_t>> &roads, size_t source)
{
	map<size_t, set<size_t>> edges;
	for (vector<vector<size_t>>::iterator it = roads.begin(); it != roads.end(); it++)
	{
		if (edges.find((*it)[0]) == edges.end())
			edges.emplace((*it)[0], set<size_t>{(*it)[1]});
		else
			edges[(*it)[0]].insert((*it)[1]);
		if (edges.find((*it)[1]) == edges.end())
			edges.emplace((*it)[1], set<size_t>{(*it)[0]});
		else
			edges[(*it)[1]].insert((*it)[0]);
	}
	vector<size_t> data(n);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	Graph<size_t, size_t> graph(data);
	assert(graph.Count() == n);
	for (map<size_t, set<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
	{
		shared_ptr<Vertex<size_t, size_t>> v = graph.GetVertex(it->first);
		assert(v);
		for (size_t i = 1; i <= n; i++)
		{
			if (i != it->first && it->second.find(i) == it->second.end())
				graph.AddUndirectedEdge(v, graph.GetVertex(i), 1);
		}
	}
	map<shared_ptr<Vertex<size_t, size_t>>, long> costs;
	graph.Dijkstra(source, costs);
	map<size_t, size_t> sortedCosts;
	cout << "Vertex\tDistance from Source " << source << ": " << endl;
	for (map<shared_ptr<Vertex<size_t, size_t>>, long>::iterator it = costs.begin(); it != costs.end(); it++)
	{
		cout << it->first->GetItem() << "\t" << it->second << endl;
		if (it->first->GetTag() != source)
			sortedCosts.emplace(it->first->GetTag(), it->second);
	}
	vector<size_t> result;
	ranges::transform(
		sortedCosts,
		back_inserter(result),
		[](const typename map<size_t, size_t>::value_type &pair)
		{ return pair.second; });
	return result;
}
/*
 * https://www.hackerrank.com/challenges/dijkstrashortreach/problem
 * Timeout! WIP
 */
vector<long> ShortestPaths(size_t n, vector<vector<size_t>> &edges, size_t start)
{
	vector<size_t> data(n);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	vector<long> result;
	Graph<size_t, size_t> graph(data);
	assert(graph.Count() == n);
	for (vector<vector<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
		graph.AddUndirectedEdge((*it)[0], (*it)[1], (*it)[2]);
	for (size_t i = 1; i <= n; i++)
	{
		if (i != start)
			result.push_back(graph.Dijkstra(start, i));
	}
	return result;
}
/*
 * https://www.hackerrank.com/challenges/dijkstrashortreach/problem
 * Timeout! WIP
 */
vector<long> ShortestPaths1(size_t n, vector<vector<size_t>> &edges, size_t start)
{
	vector<size_t> data(n);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	vector<long> result;
	Dijkstra<size_t> dijkstra(data);
	for (vector<vector<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
		dijkstra.AddUndirectedEdge((*it)[0], (*it)[1], (*it)[2]);
	for (size_t i = 1; i <= n; i++)
	{
		if (i != start)
		{
			vector<shared_ptr<DVertex<size_t>>> path;
			result.push_back(dijkstra.ShortestPath(start, i, path));
			for (vector<shared_ptr<DVertex<size_t>>>::const_iterator it = path.begin(); it != path.end(); it++)
				cout << (*it)->Value() << " -> ";
			cout << " cost: " << result.back() << endl;
		}
	}
	return result;
}
/*
 * https://www.hackerrank.com/challenges/dijkstrashortreach/problem
 * Timeout! WIP
 */
vector<long> ShortestPaths2(size_t n, vector<vector<size_t>> &edges, size_t start)
{
	vector<size_t> data(n);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	vector<long> result;
	Dijkstra<size_t> dijkstra(data);
	for (vector<vector<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
		dijkstra.AddUndirectedEdge((*it)[0], (*it)[1], (*it)[2]);
	for (size_t i = 1; i <= n; i++)
	{
		if (i != start)
		{
			vector<shared_ptr<DVertex<size_t>>> path;
			result.push_back(dijkstra.ShortestPathStateless(start, i, path));
			for (vector<shared_ptr<DVertex<size_t>>>::const_iterator it = path.begin(); it != path.end(); it++)
				cout << (*it)->Value() << " -> ";
			cout << " cost: " << result.back() << endl;
		}
	}
	return result;
}

/*
 * https://www.hackerrank.com/challenges/johnland/problem
 * Timeout!
 */
string RoadsInHackerland(size_t n, vector<vector<size_t>> &edges)
{
	vector<size_t> data(n);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	Graph<size_t, size_t> graph(data);
	assert(graph.Count() == n);
	for (vector<vector<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
		graph.AddUndirectedEdge((*it)[0], (*it)[1], 1 << (*it)[2]);
	size_t distance = 0;
	std::mutex m;
	set<string> computed;
	parallel_for(blocked_range<size_t>(1, n, 2), [&](blocked_range<size_t> r)
				 {
		m.lock();
		cout << "parallel_for blocked range [" << r.begin() << "," << r.end() << "]" << endl;
		m.unlock();
		for (size_t i = r.begin(); i < r.end(); i++)
			for (size_t j = i + 1; j <= n; j++)
			{
				if (i != j)
				{
					ostringstream oss1, oss2;
					oss1 << i << "-" << j;
					oss2 << j << "-" << i;
					m.lock();
					if (computed.find(oss1.str()) == computed.end() && computed.find(oss2.str()) == computed.end())
					{
						computed.emplace(oss1.str());
						computed.emplace(oss2.str());
						m.unlock();
						long cost = graph.Dijkstra(i, j);
						m.lock();
						if (cost >= 0)
							distance += cost;
						m.unlock();
					}
					else
						m.unlock();
				}
			} });
	string binary = decimal_to_binary(distance ? distance : -1);
	size_t offset = binary.find_first_not_of('0');
	return binary.substr(offset != string::npos ? offset : 0);
}
string RoadsInHackerland1(size_t n, vector<vector<size_t>> &edges)
{
	vector<size_t> data(n);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	Dijkstra<size_t> dijkstra(data);
	assert(dijkstra.Count() == n);
	for (vector<vector<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
		dijkstra.AddUndirectedEdge((*it)[0], (*it)[1], 1 << (*it)[2]);
	size_t distance = 0;
	set<string> computed;
	for (size_t i = 1; i < n; i++)
		for (size_t j = i + 1; j <= n; j++)
		{
			if (i != j)
			{
				ostringstream oss1, oss2;
				oss1 << i << "-" << j;
				oss2 << j << "-" << i;
				if (computed.find(oss1.str()) == computed.end() && computed.find(oss2.str()) == computed.end())
				{
					computed.emplace(oss1.str());
					computed.emplace(oss2.str());
					vector<shared_ptr<DVertex<size_t>>> path;
					long cost = dijkstra.ShortestPath(i, j, path);
					dijkstra.InitVertices(); // This prevents the routine from being used in multi-threading mode.
					distance += cost;
				}
			}
		}
	string binary = decimal_to_binary(distance ? distance : -1);
	size_t offset = binary.find_first_not_of('0');
	return binary.substr(offset != string::npos ? offset : 0);
}
string RoadsInHackerland2(size_t n, vector<vector<size_t>> &edges)
{
	vector<size_t> data(n);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	Dijkstra<size_t> dijkstra(data);
	assert(dijkstra.Count() == n);
	for (vector<vector<size_t>>::iterator it = edges.begin(); it != edges.end(); it++)
		dijkstra.AddUndirectedEdge((*it)[0], (*it)[1], 1 << (*it)[2]);
	size_t distance = 0;
	std::mutex m;
	set<string> computed;
	parallel_for(blocked_range<size_t>(1, n, 2), [&](blocked_range<size_t> r)
				 {
		m.lock();
		cout << "parallel_for blocked range [" << r.begin() << "," << r.end() << "]" << endl;
		m.unlock();
		for (size_t i = r.begin(); i < r.end(); i++)
			for (size_t j = i + 1; j <= n; j++)
			{
				if (i != j)
				{
					ostringstream oss1, oss2;
					oss1 << i << "-" << j;
					oss2 << j << "-" << i;
					m.lock();
					if (computed.find(oss1.str()) == computed.end() && computed.find(oss2.str()) == computed.end())
					{
						computed.emplace(oss1.str());
						computed.emplace(oss2.str());
						m.unlock();
						vector<shared_ptr<DVertex<size_t>>> path;
						long cost = dijkstra.ShortestPathStateless(i, j, path);
						m.lock();
						distance += cost;
						m.unlock();
					}
					else
						m.unlock();
				}
			} });
	string binary = decimal_to_binary(distance ? distance : -1);
	size_t offset = binary.find_first_not_of('0');
	return binary.substr(offset != string::npos ? offset : 0);
}

/*
 * https://www.cppstories.com/2022/ranges-alg-part-one/
 */
void cpp20readonlyranges()
{
	// 1. all_of, any_of, none_of
	cout << "C++23 ranges all_of, any_of, none_of:" << endl;
	const vector<int> nums = {1, 2, 3, -4, 5, 6, 7, 8};
	auto is_positive = [](const auto &v)
	{ return v > 0; };
	// standard version:
	assert(!all_of(nums.begin(), nums.end(), is_positive));
	assert(any_of(nums.begin(), nums.end(), is_positive));
	// ranges version:
	assert(!ranges::all_of(nums, is_positive));
	assert(ranges::any_of(nums, is_positive));

	vector<Node<int>> nodes;
	int n = -5;
	for (size_t i = 0; i < 10; i++, n++)
		nodes.push_back(Node<int>(n));
	auto is_positive_val = [](Node<int> &n)
	{
		return n.Item() > 0;
	};
	// standard version:
	assert(!all_of(nodes.begin(), nodes.end(), is_positive_val));
	assert(any_of(nodes.begin(), nodes.end(), is_positive_val));
	// ranges version:
	assert(!ranges::all_of(nodes, is_positive, &Node<int>::Item));
	assert(ranges::any_of(nodes, is_positive, &Node<int>::Item));

	// 2. for_each
	cout << "C++23 ranges for_each:" << endl;
	auto print = [](const auto &v)
	{ cout << v << ", "; };
	// standard version:
	cout << "std::for_each:" << endl;
	for_each(nodes.begin(), nodes.end(), [](Node<int> &n)
			 { cout << n.Item() << ", "; });
	cout << endl;
	cout << "std::for_each only reversed:" << endl;
	for_each(nodes.rbegin(), nodes.rend(), [](Node<int> &n)
			 { cout << n.Item() << ", "; });
	cout << endl;
	// ranges version:
	cout << "std::ranges::for_each:" << endl;
	ranges::for_each(nodes, [](Node<int> &n)
					 { cout << n.Item() << ", "; });
	cout << endl;
	cout << "std::ranges::for_each reversed:" << endl;
	ranges::for_each(nodes | std::views::reverse,
					 print, &Node<int>::Item);
	cout << endl;

	// 3. count_if
	cout << "C++23 count_if:" << endl;
	// standard version:
	assert(5 == count_if(nodes.begin(), nodes.end(), [](Node<int> &n)
						 { return n.Item() >= 0; }));
	// ranges version:
	assert(5 == ranges::count_if(nodes, [](Node<int> &n)
								 { return n.Item() >= 0; }));
	assert(1 == ranges::count(nodes, 0, &Node<int>::Item));

	// 4. find_if
	cout << "C++23 find_if:" << endl;
	// standard version:
	vector<Node<int>>::iterator it = find_if(nodes.begin(), nodes.end(), [](Node<int> &n)
											 { return n.Item() >= 0; });
	assert(it != nodes.end());
	assert(it->Item() == 0);

	// ranges version:
	it = ranges::find_if(nodes, [](Node<int> &n)
						 { return n.Item() >= 0; });
	assert(it != nodes.end());
	assert(it->Item() == 0);

	// 5. find_first_of
	cout << "C++23 find_first_of:" << endl;
	vector<Node<int>> invalids;
	invalids.push_back(Node<int>(-3));
	invalids.push_back(Node<int>(3));
	// standard version:
	it = find_first_of(nodes.begin(), nodes.end(), invalids.begin(), invalids.end());
	assert(it != nodes.end());
	assert(distance(nodes.begin(), it) == 2);
	auto it2 = find_first_of(next(it), nodes.end(), invalids.begin(), invalids.end());
	assert(it2 != nodes.end());
	assert(distance(nodes.begin(), it2) == 8);
	// -3, -2, -1, 0, 1, 2, 3
	assert(distance(it, it2) == 6);

	// Ranges version
	// -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5
	vector<int> invalidInts = {-3, 3};
	it = ranges::find_first_of(nodes, invalidInts, ranges::equal_to{}, &Node<int>::Item);
	assert(it != nodes.end());
	auto pos = distance(nodes.begin(), it);
	assert(pos == 2);
	it2 = ranges::find_first_of(nodes | views::drop(pos + 1), invalidInts, ranges::equal_to{}, &Node<int>::Item);
	assert(it2 != nodes.end());
	assert(distance(nodes.begin(), it2) == 8);
	assert(distance(it, it2) == 6);

	// 6. mismatch
	cout << "C++23 mismatch:" << endl;
	const string firstStr = "Hello Super World";
	const string secondStr = "Hello Amazing World";
	// standard version :
	auto [first, second] = mismatch(firstStr.begin(), firstStr.end(), secondStr.begin());
	{
		assert(distance(firstStr.begin(), first) == 6);
	}
	// ranges version
	auto [i1, i2] = ranges::mismatch(firstStr, secondStr);
	assert(distance(firstStr.begin(), i1) == 6);

	// 7. search
	const string_view needle{"Super"};
	const string_view needle1{"SUPER"};
	// standard
	const auto it3 = search(firstStr.begin(), firstStr.end(), boyer_moore_searcher(needle.begin(), needle.end()));
	assert(it3 != firstStr.end());
	assert(distance(firstStr.begin(), it3) == 6);
	// ranges case-sensitive
	auto found = ranges::search(firstStr, needle);
	assert(!found.empty());
	assert(distance(firstStr.begin(), found.begin()) == 6);
	assert(distance(firstStr.begin(), found.end()) == 11);
	// ranges case-insensitive
	found = ranges::search(firstStr, needle1, ranges::equal_to{}, ::toupper, ::toupper);
	assert(!found.empty());
	assert(distance(firstStr.begin(), found.begin()) == 6);
	assert(distance(firstStr.begin(), found.end()) == 11);

	const string sequence = "CTGCCCAGGGTTT";
	const char letter = 'C';
	const size_t count = 3;
	cout << "looking for " << count << " " << letter << "'s in " << quoted(sequence) << endl;
	// standard version:
	auto it4 = search_n(sequence.begin(), sequence.end(), count, letter);
	assert(it4 != sequence.end());
	assert(distance(sequence.begin(), it4) == 3);
	// ranges case-sensitive
	found = ranges::search_n(sequence, count, letter);
	assert(!found.empty());
	assert(distance(sequence.begin(), found.begin()) == 3);
	assert(distance(sequence.begin(), found.end()) == 6);
}
ostream &operator<<(ostream &os, const Node<int> &n)
{
	os << n.Item();
	return os;
}
/*
 * https://www.cppstories.com/2022/ranges-alg-part-two/
 */
void cpp20ranges()
{
	vector<Node<int>> nodes;
	int n = -5;
	for (size_t i = 0; i < 10; i++, n++)
		nodes.push_back(Node<int>(n));
	// copy_if
	cout << "C++23 ranges copy_if:" << endl;
	// standard version:
	copy_if(nodes.begin(), nodes.end(), ostream_iterator<Node<int>>(cout, ", "), [](const Node<int> &n)
			{ return n.Item() >= 0; });
	cout << endl;
	// ranges version:
	ranges::copy_if(nodes, ostream_iterator<Node<int>>(cout, ", "), [](const Node<int> &n)
					{ return n.Item() >= 0; });
	cout << endl;

	// fill
	cout << "C++23 ranges fill:" << endl;
	nodes.clear();
	nodes.resize(5);
	// standard version
	fill(nodes.begin(), nodes.end(), -1);
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// ranges version
	nodes.clear();
	nodes.resize(5);
	ranges::fill(nodes, -2);
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// generate
	cout << "C++23 ranges generate:" << endl;
	// standard version
	generate(nodes.begin(), nodes.end(), [n = 1]() mutable
			 { return n++; });
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// ranges version
	ranges::generate(nodes, [n = 1]() mutable
					 { return n++; });
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// transform
	cout << "C++23 ranges transform:" << endl;
	// standard version
	transform(nodes.begin(), nodes.end(), nodes.begin(), [](const Node<int> &n) mutable
			  { return n.Item() * -10; });
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// ranges version
	nodes.clear();
	nodes.resize(5);
	ranges::generate(nodes, [n = 1]() mutable
					 { return n++; });
	ranges::transform(nodes, nodes.begin(), [](const Node<int> &n) mutable
					  { return n.Item() * 10; });
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	vector<Node<int>> nodes1{5, Node<int>(10)};
	vector<int> numbers = {-1, 1, 2, -2, 3};
	assert(nodes1.size() == 5);
	for (vector<Node<int>>::iterator it = nodes1.begin(); it != nodes1.end(); it++)
		assert(it->Item() == 10);
	ranges::transform(nodes1, numbers, nodes1.begin(), [](const Node<int> &n, int number)
					  { return n.Item() * number; });
	ranges::copy(nodes1, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// remove
	cout << "C++23 ranges remove:" << endl;
	nodes.clear();
	nodes.resize(10);
	ranges::generate(nodes, [n = -5]() mutable
					 { return n++; });
	// standard version
	nodes.erase(remove_if(nodes.begin(), nodes.end(), [](const Node<int> &n)
						  { return n.Item() < 0; }),
				nodes.end());
	assert(nodes.size() == 5);
	cout << "vector<Nodes<int>> after std::remove_if: ";
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// ranges version
	nodes.clear();
	nodes.resize(10);
	ranges::generate(nodes, [n = -5]() mutable
					 { return n++; });
	nodes.erase(ranges::remove_if(nodes, [](const Node<int> &n)
								  { return n.Item() < 0; })
					.begin(),
				nodes.end());
	assert(nodes.size() == 5);
	cout << "vector<Nodes<int>> after ranges::remove_if: ";
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// C++23 version:
	nodes.clear();
	nodes.resize(10);
	ranges::generate(nodes, [n = -5]() mutable
					 { return n++; });
	erase_if(nodes, [](const Node<int> &n)
			 { return n.Item() < 0; });
	assert(nodes.size() == 5);
	cout << "vector<Nodes<int>> after std::erase_if: ";
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// replace
	cout << "C++23 ranges replace:" << endl;
	// standard version
	nodes.clear();
	nodes.resize(10);
	ranges::generate(nodes, [n = -5]() mutable
					 { return n++; });
	replace(nodes.begin(), nodes.end(), Node<int>(-1), Node<int>(100));
	// ranges version
	ranges::replace(nodes, 1, Node<int>(200), &Node<int>::Item);
	ranges::replace(nodes, Node<int>(0), Node<int>(1000));
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// reverse
	cout << "C++23 ranges reverse:" << endl;
	nodes.clear();
	nodes.resize(10);
	ranges::generate(nodes, [n = -5]() mutable
					 { return n++; });
	// standard version
	reverse_copy(nodes.begin(), nodes.end(), ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// ranges version
	ranges::reverse_copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// rotate
	cout << "C++23 ranges rotate:" << endl;
	// standard version
	Node<int> firstNode(nodes[0]);
	auto newPos = rotate(nodes.begin(), next(nodes.begin(), 1), nodes.end());
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// -4, -3, -2, -1, 0, 1, 2, 3, 4, -5
	assert(9 == distance(nodes.begin(), newPos));
	cout << firstNode << " is now at position " << distance(nodes.begin(), newPos) << endl;
	// ranges version
	auto zeroPos = ranges::find(nodes, Node<int>(0));
	assert(zeroPos != nodes.end());
	Node<int> firstNode1(nodes[0]);
	assert(-4 == firstNode1.Item());
	auto newPos1 = ranges::rotate(nodes, zeroPos);
	// 0, 1, 2, 3, 4, -5, -4, -3, -2, -1
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	assert(6 == distance(nodes.begin(), newPos1.begin()));
	cout << firstNode1 << " is now at position " << distance(nodes.begin(), newPos1.begin()) << endl;

	// shuffle
	// std::random_shuffle was deprecated and removed in C++17
	cout << "C++23 ranges shuffle:" << endl;
	random_device device;
	mt19937_64 rng{device()};
	nodes.clear();
	nodes.resize(10);
	ranges::generate(nodes, [n = -5]() mutable
					 { return n++; });
	shuffle(nodes.begin(), nodes.end(), rng);
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	nodes.clear();
	nodes.resize(10);
	ranges::generate(nodes, [n = -5]() mutable
					 { return n++; });
	ranges::shuffle(nodes, rng);
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// sample
	cout << "C++23 ranges sample:" << endl;
	vector<Node<int>> firstSample, secondSample;
	sample(nodes.begin(), nodes.end(), back_inserter(firstSample), 5, rng);
	assert(!firstSample.empty());
	ranges::copy(firstSample, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	ranges::sample(firstSample, back_inserter(secondSample), 3, rng);
	assert(!secondSample.empty());
	ranges::copy(secondSample, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;

	// unique
	cout << "C++23 ranges unique:" << endl;
	nodes.clear();
	// 1, 1, 5, 5, 2, 2, 3, 3, 4, 4, 2, 2, 5, 5
	// 1, 5, 2, 3, 4, 2, 5
	nodes.push_back(Node<int>(1));
	nodes.push_back(Node<int>(1));
	nodes.push_back(Node<int>(5));
	nodes.push_back(Node<int>(5));
	nodes.push_back(Node<int>(2));
	nodes.push_back(Node<int>(2));
	nodes.push_back(Node<int>(3));
	nodes.push_back(Node<int>(3));
	nodes.push_back(Node<int>(4));
	nodes.push_back(Node<int>(4));
	nodes.push_back(Node<int>(2));
	nodes.push_back(Node<int>(2));
	nodes.push_back(Node<int>(5));
	nodes.push_back(Node<int>(5));
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// auto unique = ranges::unique(nodes, {}, &Node<int>::Item);
	auto unique = ranges::unique(nodes);
	// After the first run to unique(), the nodes vector is modified so that elements to be removed are passed to the end of the container. What’s more, they are of unspecified value.
	// The returned object contains a sub-range pointing to the first “removed” element and the end of the input range.
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	// So, use erase to remove those elements from the container
	nodes.erase(unique.begin(), unique.end());
	cout << "After removing duplicate items in the same group: ";
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	ranges::sort(nodes, {}, &Node<int>::Item);
	cout << "After sort: ";
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	unique = ranges::unique(nodes);
	nodes.erase(unique.begin(), unique.end());
	cout << "After removing duplicate items in the same group: ";
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	cout << "After sort: ";
	ranges::sort(nodes, {}, &Node<int>::Item);
	ranges::copy(nodes, ostream_iterator<Node<int>>(cout, ", "));
	cout << endl;
	vector<long> a;
	a.resize(10);
	ranges::generate(a, [n = 1]() mutable
					 { return n++; });
	ranges::transform(a, a, a.begin(), std::plus{}); // This is binary_transform using 2 vectors. In this case, it uses duplicate vector a.
	cout << "After transform with std::plus: ";
	ranges::copy(a, ostream_iterator<long>(cout, ", "));
	cout << endl;
}
/*
 * https://www.cppstories.com/2018/06/variant/
 * https://www.cppstories.com/2018/09/visit-variants/
 */
void cpp20variants()
{
	variant<long, float, string> lfs;
	static_assert(variant_size_v<decltype(lfs)> == 3);
	// default initialized to the first alternative, should be 0
	visit(VariantVisitor{}, lfs);
	// index will show the currently used 'type'
	cout << "Currently used type in variant: " << lfs.index() << endl;
	assert(0 == lfs.index());
	lfs = 123.456f;
	cout << "Currently used type in variant: " << lfs.index() << endl;
	assert(1 == lfs.index());
	lfs = "Hello World!!!";
	cout << "Currently used type in variant: " << lfs.index() << endl;
	assert(2 == lfs.index());
	// get_if<>
	if (const auto lPtr(get_if<long>(&lfs)); lPtr)
		cout << "long pointer: " << *lPtr << endl;
	else if (const auto fPtr(get_if<float>(&lfs)); fPtr)
		cout << "float pointer: " << *fPtr << endl;
	if (holds_alternative<long>(lfs))
		cout << "variant lfs holds a long value" << endl;
	else if (holds_alternative<float>(lfs))
		cout << "variant lfs holds a float value" << endl;
	else if (holds_alternative<string>(lfs))
		cout << "variant lfs holds a string value" << endl;
	try
	{
		/* std::get<Type|Index>(variant)
		 * It returns a reference to the desired type if it’s active (You can pass a Type or Index).
		 * If not then you’ll get std::bad_variant_access exception.
		 */
		auto f = get<float>(lfs);
		cout << "It's float! " << f << endl;
	}
	catch (bad_variant_access &)
	{
		cout << "Variant lfs currently does not hold a floating point value!" << endl;
	}
	// visit
	visit(VariantVisitor{}, lfs);
	lfs = 123;
	visit(VariantVisitor{}, lfs);
	lfs = 123.456f;
	visit(VariantVisitor{}, lfs);

	// Compile-time error if first alternative type does NOT have a default constructor
	// variant<Poker, long, float, string> invalid; class Poker does not have  a default constructor
	variant<monostate, Poker, long, float, string> variant1;
	cout << "Currently used type in variant1: " << variant1.index() << endl;

	// Ambiguity: double might convert to float or long.
	// variant<long, float, string> variant2 {123.456};
	// Resolve ambiguity by in_place
	variant<long, float, string> variant2{in_place_index<1>, 123.456}; // double!
	cout << "variant active type: " << variant2.index() << ", value: " << get<float>(variant2) << endl;

	variant<long, float, string> variant3{"Hello"};
	variant3 = 123;						  // long
	variant3.emplace<2>(string("Hello")); // string
	// get returns a reference.
	get<string>(variant3) += string(" World!!!");
	assert("Hello World!!!" == get<string>(variant3));
	variant3 = 123.456f;
	if (auto pFloat = get_if<float>(&variant3); pFloat)
	{
		*pFloat *= 2.0f;
		assert(123.456f * 2.0f == get<float>(variant3));
	}
	variant<long, VariantException> variant4;
	try
	{
		variant4 = VariantException(0);
	}
	catch (...)
	{
		assert(!variant4.valueless_by_exception());
		// variant state is healthy and unchanged
		cout << get<long>(variant4) << endl;
	}
	try
	{
		variant4.emplace<0>(VariantException(10)); // calls "long()" conversion operator
	}
	catch (...)
	{
		assert(!variant4.valueless_by_exception());
		cout << get<long>(variant4) << endl;
	}
	variant<long, float, string> v1{"Hello World!!!"};
	variant<long, double, string> v2{10};
	variant<long, double, string> v3{123.456};
	variant<long, float, string> v4{123.456f};
	visit(VariantVisitor{}, v1, v2, v3, v4);
}
/*
 * https://www.hackerrank.com/challenges/abbr/problem
 * 100%
 * (1) Capitalize a
 * (2) Delete remaining lowercase letters
* AbcDE
* AB DE <- Yes 'b' -> B; delete 'c'
 j: A B D E
i 1 0 0 0 0
A 0 1 0 0 0
b 0 1 1 0 0
c 0 1 1 0 0
D 0 0 0 1 0
E 0 0 0 0 1

* aaaa <- YES
* A
 j: A
i 1 0
a 1 1
a 1 1
a 1 1
a 1 1

* AbcDE
* AF DE <- NO

  j: A F D E
i 1 0 0 0  0
A 0 1 0 0  0
b 0 1 0 0  0
c 0 1 0 0  0
D 0 0 0 0  0
E 0 0 0 0  0

 * AbcDE
 * ADE	<- YES (Remove "bc")

 j: A D E
i 1 0 0 0
A 0 1 0 0
b 0 1 0 0
c 0 1 0 0
D 0 0 1 0
E 0 0 0 1

 * KXzQ
 * K 	<- NO
 j: K
i 1 0
K 0 1
X 0 0
z 0 0
Q 0 0

  j: A B A A
i 1  0 0 0 0
b 1  0 0 0 0
a 1  1 0 0 0
b 1  1 1 0 0
a 1  1 1 1 0
A 0  1 0 1 1
B 0  0 1 0 0
b 0  0 1 0 0
b 0  0 1 0 0
A 0  0 0 1 0
b 0  0 0 1 0
 */
bool Abbreviation(string const &s1, string const &s2)
{
	if (s1.empty() || (s2.empty() && count_if(s1.begin(), s1.end(), [](char c)
											  { return isupper(c); }) > 0))
		return false;
	vector<vector<bool>> table(s1.size() + 1, vector<bool>(s2.size() + 1)); // Defaults to false initial value
	// dp[i][j] = true iff s1(0..i-1) can match s2(0..j-1)
	table[0][0] = true;
	for (size_t i = 1; i <= s1.size(); i++)
		table[i][0] = table[i - 1][0] && islower(s1[i - 1]);
	for (size_t i = 1; i <= s1.size(); i++)
		for (size_t j = 1; j <= s2.size(); j++)
			table[i][j] = (table[i - 1][j - 1] && toupper(s1[i - 1]) == s2[j - 1]) || (table[i - 1][j] && islower(s1[i - 1]));
	return table[s1.size()][s2.size()];
}
/*
 * https://www.hackerrank.com/challenges/gena/problem
 * vector index # is the size of disk
 * vector element is tower #
 *
 * Use breadth-first search until the final state of 0 (0-based index) is found.
 *
 * Represent each possible arrangement as a binary number of length 2 * discCount.
 * The rightmost 2 digits represent the pole of disc 1, the next two digits represent the position of disk 2, etc.,
 * Then do a bfs of the graph starting at init_state...
 *
 * 100%
 *
 * [2, 3]
 * Towers: 1 2 3 4
 * Discs:    0 1
 *
 * [4 3 2 1]
 * Towers: 1 2 3 4
 * Discs : 4 3 2 1 (3 moves):
 *
 * [1 4 1]
 * Towers: 1      2 3 4
 * Discs : [3, 1]     2 {1: [3, 1], 4: [2]}
 */
vector<unsigned long long> BFSNextMoves(unsigned long long state, size_t towerCount, size_t discCount)
{
	// Returns a list of states that can be achieved from the given state
	vector<unsigned long long> states;
	size_t towerBitCount = (floor(log2(towerCount - 1)) + 1);
	size_t towerBitMask = ~(-(1 << towerBitCount));
	map<size_t, size_t> topDiscs;
	set<size_t> poles, skippedPoles;
	size_t pole;
	// bitset<64> bm(towerBitMask);
	// cout << "towerBitMask: " << bm << endl;
	for (size_t d = 0; d < discCount; d++)
	{
		/* {1, 4, 2, 4, 2, 2}: 01_01_11_01_11_00
		 * Pole Disc
		 * 0	0
		 * 3	[1, 3]
		 * 1	[2, 4, 5]
		 */
		pole = (state >> (d * towerBitCount)) & towerBitMask;
		cout << "Current state: Pole: " << pole << ", discs: " << d << endl;
		if (poles.find(pole) == poles.end())
		{
			topDiscs[d] = pole;
			poles.emplace(pole);
		}
	}
	cout << endl;
	for (map<size_t, size_t>::const_iterator it = topDiscs.begin(); it != topDiscs.end(); it++)
	{
		/*
		 * Next moves:
		 * Disc Poles
		 * 0	[1,2,3]
		 * 1	[1,2]
		 * 2	[2]
		 */
		skippedPoles.emplace(it->second); // (1) Skip it's own pole. (2) Skip poles with smaller discs on top.
		for (size_t p = 0; p < towerCount; p++)
			if (skippedPoles.find(p) == skippedPoles.end())
			{
				size_t offset = towerBitCount * it->first;
				unsigned long long s = state & ~(towerBitMask << offset);
				s |= (p << offset);
				bitset<64> bs(s);
				cout << "Next move: " << bs << " Pole: " << p << ", disc: " << it->first << endl;
				states.push_back(s);
			}
	}
	return states;
}
int ResetTowerOfHanoi(size_t towerCount, vector<size_t> const &poles)
{
	ostringstream oss;
	size_t towerBitCount = (floor(log2(towerCount - 1)) + 1);
	size_t towerBitMask = ~(-(1 << towerBitCount));
	size_t discCount = poles.size(), bitCount = towerBitCount * discCount;
	if (bitCount > sizeof(unsigned long long) * 8)
	{
		oss << "Too many discs/poles! " << towerCount << " towers " << discCount << " discs needs " << bitCount << " number of bits!";
		throw runtime_error(oss.str());
	}
	unsigned long long state = 0; // 64-bit
	// bitset<64> bm(towerBitMask);
	// cout << "towerBitMask: " << bm << endl;
	/* {1, 4, 2, 4, 2, 2}: 01_01_11_01_11_00
	 * Pole Disc
	 * 0	0
	 * 3	[1, 3]
	 * 1	[2, 4, 5]
	 */
	for (size_t d = 0; d < discCount; d++)
	{
		cout << "Pole " << poles[d] - 1 << " discs: " << d << endl;
		state |= (poles[d] - 1) << (d * towerBitCount);
	}
	bitset<64> s(state);
	cout << "state: " << s << endl;
	deque<towerofhanoi_state_t> queue;
	queue.push_back(towerofhanoi_state_t(state, 0));
	set<unsigned long long> visited{state};
	for (; !queue.empty();)
	{
		towerofhanoi_state_t s = queue.front();
		queue.pop_front();
		if (!s.state)
			return s.moves;
		else
		{
			vector<unsigned long long> states = BFSNextMoves(s.state, towerCount, discCount);
			for (vector<unsigned long long>::const_iterator it = states.begin(); it != states.end(); it++)
			{
				if (visited.find(*it) == visited.end())
				{
					queue.push_back(towerofhanoi_state_t(*it, s.moves + 1));
					visited.emplace(*it);
				}
			}
		}
	}
	return -1; // Impossible to reset the towers of discs
}
/*
 * https://www.hackerrank.com/challenges/summing-pieces/problem

 1 2 3 (n = 3)
[1] [2] [3]
[1 2] [3]
[1] [2 3]
[1 2 3]

p: previous value
y: starts from n-2 and decrementing by one
#: Total value contributions
1: 7 = 2^n - 1
2: 8 = p + 2^y - 2^0 = 7 + 2^(3-2) - 1 = 7 + 2 - 1
3: 7 = p + 2^y - 2^1 = 8 + 2^(3-3) - 2^1 = 8 + 1 - 2 = 7
Result: 1 * 7 + 2 * 8 + 3 * 7 = 7 + 16 + 21 = 44

 * [1 3 6 7]:
 * [(1),(3),(6),(7)]
 * [(1,3),(6),(7)]
 * [(1),(3,6),(7)]
 * [(1),(3),(6,7)]
 * [(1,3,6),(7)]
 * [(1,3),(6,7)]
 * [(1),(3,6,7)]
 * [(1,3,6,7)]
 *
 * #: Total value contributions
 * 1 - 15
 * 3 - 18
 * 6 - 18
 * 7 - 15
 *
 * ---------------------
 * | 15 | 18 | 18 | 15 |
 * ---------------------
 * ^     ^   ^     ^
 * |     |___|     |
 * |_______________|
 *
 * So, For n>1 in general, the count values are
----------------------------------------------------------------
| 2^n-1 | p+2^(y) - 2^0 | p+2^(y-1) - 2^1 | p+2^(y-2) - 2^2|...
----------------------------------------------------------------
i:0		   i:1
(2^n)-1  p+2^(n-2) - 2^0
where,
 p is previous box value
 y starts from n-2 and decremented by 1 afterwards
 *
 * WIP 15/29 test cases failed :(
 */
long double VectorSlicesSum(vector<long double> &data)
{
	long double sum = 0;
	const long double modulo = 1e9 + 7L;
	if (!data.empty())
	{
		long middle = data.size() / 2 + data.size() % 2;
		vector<long double> sums(middle);
		long double n = data.size(), y = n - 2L, z = 0L;
		sums[0] = fmodl(pow(2L, n), modulo) - 1L;
		for (long i = 1; i < middle; i++, y--, z++)
			sums[i] = fmodl(sums[i - 1] + fmodl(pow(2L, y), modulo) - fmodl(pow(2L, z), modulo), modulo);
		// Mirror the vector to second half
		for (long i = (data.size() % 2) ? middle - 2 : middle - 1; i >= 0; i--)
			sums.push_back(sums[i]);
		for (long i = 0; i < data.size(); i++)
		{
			data[i] = fmodl(data[i] * sums[i], modulo);
			sum = fmodl(sum + data[i], modulo);
		}
	}
	return sum;
}
/*
 * https://www.hackerrank.com/challenges/bear-and-steady-gene/problem
 * 100%
 * Sliding window implementation
 */
long SteadyGene(string const &gene)
{
	long count = numeric_limits<long>::max();
	if (gene.size() % 4) // gene.size() should be divisable by 4
		return count;
	size_t balancedCount = gene.size() / 4;
	map<char, size_t> genes;
	for (string::const_iterator it = gene.begin(); it != gene.end(); it++)
	{
		pair<map<char, size_t>::iterator, bool> result = genes.emplace(*it, 1);
		if (!result.second)
			result.first->second++;
	}
	/*
	 * ACGTCCGT : length = 8, N = 2
	 * 'A': 1
	 * 'G': 2
	 * 'C': 3
	 * 'T': 2
	 *
	 * i: 0, j: 0 [A]CGTCCGT
	 * 'A': 0 -> j:1
	 * 'G': 2
	 * 'C': 3
	 * 'T': 2
	 *
	 * i: 0, j: 1 [AC]GTCCGT
	 * 'A': 0
	 * 'G': 2
	 * 'C': 2 -> j:2
	 * 'T': 2
	 *
	 * i: 0, j: 2 [ACG]TCCGT
	 * 'A': 1 -> count: 2, i:1, j:2
	 * 'G': 2
	 * 'C': 2
	 * 'T': 2
	 *
	 * i: 1, j: 2 A[CG]TCCGT => AAGTCCGT
	 * 'A': 1
	 * 'G': 2
	 * 'C': 3 -> count: 1, i:2 j:2
	 * 'T': 2
	 *
	 * i: 2, j: 2 AC[G]TCCGT
	 * 'A': 1
	 * 'G': 1 -> j:3, i:2
	 * 'C': 3
	 * 'T': 2
	 *
	 * i: 2, j: 3 AC[GT]CCGT
	 * 'A': 1
	 * 'G': 1
	 * 'C': 3
	 * 'T': 1 -> j:4, i:2
	 *
	 * i: 2, j: 4 AC[GTC]CGT
	 * 'A': 1
	 * 'G': 1
	 * 'C': 2 -> j:5, i:2
	 * 'T': 1
	 *
	 * i: 2, j: 5 AC[GTCC]GT
	 * 'A': 1
	 * 'G': 2 -> count: 3, i:3 j:5
	 * 'C': 2
	 * 'T': 1
	 *
	 * i: 3, j: 5 ACG[TCC]GT
	 * 'A': 1
	 * 'G': 2
	 * 'C': 2
	 * 'T': 2 -> count: 2, i:4, j:5
	 *
	 * i: 4, j: 5 ACGT[CC]GT => ACGTACGT
	 * 'A': 1
	 * 'G': 2
	 * 'C': 3 -> count: 1, i:5, j:5
	 * 'T': 2
	 *
	 * i: 5, j: 5 ACGTC[C]GT
	 * 'A': 1
	 * 'G': 2
	 * 'C': 2 -> j:6
	 * 'T': 2
	 *
	 * i: 5, j: 6 ACGTC[CG]T => ACGTCAGT
	 * 'A': 1
	 * 'G': 2
	 * 'C': 3 -> count: 1, i:6 j:6
	 * 'T': 2
	 *
	 * i: 6, j: 6 ACGTCC[G]T
	 * 'A': 1
	 * 'G': 1 -> j:7
	 * 'C': 3
	 * 'T': 2
	 *
	 * i: 6, j: 7 ACGTCC[GT]
	 * 'A': 1
	 * 'G': 1
	 * 'C': 3
	 * 'T': 1, j:8
	 */
	for (long i = 0, j = 0; i < gene.size() && j < gene.size();)
	{
		if (genes['A'] <= balancedCount && genes['C'] <= balancedCount && genes['G'] <= balancedCount && genes['T'] <= balancedCount)
		{
			count = min(count, j - i);
			genes[gene[i++]]++;
		}
		else
			genes[gene[j++]]--;
	}
	return count;
}
/*
 * https://www.hackerrank.com/challenges/time-conversion/problem
 * 100%
 */
string TwentyFourHourTimeConversion(string const &s)
{
	int hour; // 12:00:00 AM - 11:59:59 AM => 00:00:00 - 11:59:59
	istringstream(s.substr(0, 2)) >> hour;
	if (s.find("AM") != string::npos && hour == 12)
	{
		ostringstream oss;
		oss << setfill('0') << setw(2) << hour - 12 << s.substr(2, s.size() - 4);
		return oss.str();
	}
	else if (s.find("PM") != string::npos && hour != 12)
	{ // pm
		ostringstream oss;
		oss << setfill('0') << setw(2) << hour + 12 << s.substr(2, s.size() - 4);
		return oss.str();
	}
	else
		return s.substr(0, s.size() - 2);
}
/*
 * https://en.wikipedia.org/wiki/Kaprekar_number
 * https://www.hackerrank.com/challenges/kaprekar-numbers/problem
 * 100%
 */
vector<long> KaprekarNumbers(long p, long q)
{
	string d, str, r, l;
	long j, k;
	long long square;
	vector<long> result;
	for (long i = p; i <= q; i++)
	try
	{
		d = to_string(i);
		square = (long long)i * (long long)i;
		str = to_string((long long)i * (long long)i); // Overflows for 32-bit system when i > 65535
		r = str.substr(str.size() - d.size(), d.size()); // str: 1234, d: 12 => r: 34
		l = str.substr(0, str.size() - r.size()); // l: 12
		j = 0;
		k = 0;
		istringstream(l) >> j;
		istringstream(r) >> k;
		if (j + k == i)
			result.push_back(i);
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}
	return result;
}
/*
 * ....
 * ..x.
 * ..x.
 * x...
 *
* 	0	1	2	3
0	.	.	.	.
1	.	.	x	.
2	.	.	x	.
3	x	.	.	.

	0	1	2	3
0	1   2   3   4
1	5   6   x   6
2	7   8   x   8
3	x   8   9  10

 * ..x.
 * ....
 * ....
 * x...

* 	0	1	2	3
0	.	.	x	.
1	.	.	.	.
2	.	.	.	.
3	x	.	.	.

* 	0	1	2	3
0	1   2   x   0
1	1   2   3   4
2	5   6   7   8
3	x   0   1   2

 * ....
 * ..x.
 * ....
 * x...
 *
* 	0	1	2	3
0	.	.	.	.
1	.	.	x	.
2	.	.	.	.
3	x	.	.	.

* 	0	1	2	3
0	1	2	3	4
1	5	6	x	6
2	7	8	8	9
3	x	9	9	10

*/
size_t MatrixPerimeter(vector<vector<size_t>> &area, vector<string> &grid)
{
	if (grid.empty() || area.empty() || area.size() < 2 || area[0].size() < 2)
		return 0;
	size_t r1 = area[0][0], c1 = area[0][1], r2 = area[1][0], c2 = area[1][1];
	if (r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0 || r2 < r1 || c2 < c1 || r2 >= grid.size() || c2 >= grid[0].size())
		return 0;
	size_t width = c2 - c1 + 1;
	string str1 = grid[r1].substr(c1, width);
	string str2 = grid[r2].substr(c1, width);
	if (str1.find("x") != string::npos || str2.find("x") != string::npos)
		return 0;
	size_t perimeter = 2 * width;
	size_t y = r1 + 1;
	for (; y < r2; y++)
	{
		if (grid[y][c1] == 'x')
			return 0;
	}
	if (y == r2 && (y - (r1 + 1)) > 0)
		perimeter += r2 - (r1 + 1);
	y = r1 + 1;
	for (; y < r2; y++)
	{
		if (grid[y][c2] == 'x')
			return 0;
	}
	if (y == r2 && (y - (r1 + 1)) > 0)
		perimeter += r2 - (r1 + 1);
	return perimeter;
}
/*
 * https://www.hackerrank.com/challenges/mr-k-marsh/problem
					Down					Right
 * ....			2  3  0 3				3  2  1 0
 * ..x.			1  2 -1 2				1  0 -1 0
 * ..x.			0  1 -1 1				1  0 -1 0
 * x...			-1 0  0 0				-1 2  1 0
 *
 * ....			0  1  0 3				3  2  1 0
 * x.x.			-1 0 -1 2				-1 0 -1 0
 * .x..			0 -1  1 1				0 -1  1 0
 * x...			-1 0  0 0				-1 2  1 0
 *
 * ....			2  0  1 3				3  2  1 0
 * .x..			1 -1  0 2				0 -1  1 0
 * .xx.			0 -1 -1 1				0 -1 -1 0
 * x...			-1 0  0 0				-1 2  1 0

 * .x			0 -1					0 -1
 * x.			-1 0					-1 0
 *
 * ....			0  0  0 1				3   2  1 0
 * xxx.        -1 -1 -1 0				-1 -1 -1 0
 *
 * .x			3 -1					0 -1
 * .x			2 -1					0 -1
 * .x			1 -1					0 -1
 * ..			0  0					1  0
 *
 * ..x..
 * .x.x.
 * ..x..
 *
 * ...x...
 * .x...x.
 * ...x...
 *
 * xxxx
 * x..x
 * x..x
 * xxxx
 *
 * ......
 * .xxxx.
 * .x..x.
 * .x..x.
 * .xxxx.
 * ......
 */
#if 1
/*
 * WIP - wrong answers
 */
size_t kMarsh(vector<string> &grid)
{
	vector<vector<long>> right(grid.size(), vector<long>(grid[0].size())), down(right);
	for (size_t i = 0; i < grid.size(); i++)
	{
		size_t marsh = grid[i].find('x');
		if (marsh != string::npos)
		{
			size_t j = 0;
			for (; marsh != string::npos; marsh = grid[i].find('x', marsh))
			{
				down[i][marsh] = -1;
				right[i][marsh] = -1;
				// Fix the Right matrix
				long k = marsh - j - 1;
				for (; j < marsh; j++, k--)
				{
					if (right[i][j] != -1)
						right[i][j] = k;
				}
				j = ++marsh;
			}
			// Fix Right matrix from the last marsh to the end of the row
			long k = grid[i].size() - j - 1;
			for (; j < grid[i].size(); j++, k--)
				right[i][j] = k;
		}
		else
		{
			for (long j = 0; j < grid[i].size(); j++)
				right[i][j] = grid[i].size() - j - 1;
		}
	}
	// Fix the Down matrix
	for (size_t col = 0; col < down[0].size(); col++)
	{
		long val = 0;
		size_t lastrow = 0;
		for (size_t row = 0; row < down.size(); row++)
		{
			if (down[row][col] == -1)
			{
				val = row - lastrow - 1;
				for (; lastrow < row; lastrow++)
				{
					if (down[lastrow][col] != -1)
						down[lastrow][col] = val--;
				}
				for (; lastrow < down.size() && down[lastrow][col] == -1; lastrow++)
					;
			}
		}
		if (!lastrow) // No marsh
		{
			for (size_t row = 0; row < down.size(); row++)
				down[row][col] = down.size() - row - 1;
		}
		else
		{
			// Fix Down matrix from the last marsh to the end of the col
			val = down.size() - lastrow - 1;
			for (; lastrow < down.size(); lastrow++)
			{
				if (down[lastrow][col] != -1)
					down[lastrow][col] = val--;
			}
		}
	}
	size_t perimeter = 0;
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			size_t perimeter1 = 0, perimeter2 = 0;
			// Down, Right
			if (down[i][j] > 0 && right[i + down[i][j]][j] > 0)
			{
				size_t rightSteps = right[i + down[i][j]][j] - 1;
				perimeter1 = 2 * (down[i][j] + 1) + 2 * rightSteps;
			}
			// Right, Down
			if (right[i][j] > 0 && down[i][j + right[i][j]] > 0)
			{
				size_t downSteps = down[i][j + right[i][j]] - 1;
				perimeter2 = 2 * (right[i][j] + 1) + 2 * downSteps;
			}
			if (perimeter1 && perimeter2)
				perimeter = max(perimeter, min(perimeter1, perimeter2));
		}
	return perimeter;
}
#else
/* WIP - Takes too long!*/
size_t kMarsh(vector<string> &grid)
{
	size_t perimeter = 0;
	for (size_t r1 = 0; r1 < grid.size(); r1++)
		for (size_t r2 = r1 + 1; r2 < grid.size(); r2++)
			for (size_t c1 = 0; c1 < grid[r1].size(); c1++)
				for (size_t c2 = c1 + 1; c2 < grid[r2].size(); c2++)
				{
					vector<vector<size_t>> area = vector<vector<size_t>>{{r1, c1}, {r2, c2}};
					size_t tmp = MatrixPerimeter(area, grid);
					if (tmp > perimeter)
						perimeter = tmp;
				}
	return perimeter;
}
#endif
/*
 * https://www.hackerrank.com/challenges/happy-ladybugs/problem
 * 100%
 */
bool HappyLadyBugs(string const &str)
{
	map<char, size_t> counts;
	for (size_t i = 0; i < str.size(); i++)
	{
		pair<map<char, size_t>::iterator, bool> result = counts.emplace(str[i], 1);
		if (!result.second)
			counts[str[i]]++;
	}
	if (counts.size() == 1 && counts.begin()->first == '_')
		return true;
	if (counts.find('_') == counts.end())
	{
		set<char> groups;
		char current = '\0';
		for (string::const_iterator it = str.begin(); it != str.end(); it++)
		{
			if (current == '\0' || (*it != current && groups.find(*it) == groups.end()))
			{
				current = *it;
				groups.emplace(current);
			}
			else if (*it != current)
				return false;
		}
	}
	for (map<char, size_t>::iterator it = counts.begin(); it != counts.end(); it++)
		if (it->second == 1 && it->first != '_')
			return false;
	return true;
}
/*
 * https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
 * Times out!
 */
size_t ActivityNotifications(vector<size_t> const &data, size_t d)
{
	size_t count = 0;
	bool odd = d % 2;
	size_t half = d / 2;
	// vector<long>::iterator it = data.begin();
	multiset<size_t> window(data.begin(), data.begin() + d);
	// multiset<long>::iterator it1 = window.begin();
	// advance(it1, half);
	//  for (size_t i = d, j = 0; i < data.size() && j < data.size() - d; i++, j++, it++)
	for (size_t i = d; i < data.size();)
	{
		// ranges::sort(it, it + d);
		// double median = odd ? data[j + half] : (double)(data[j + half] + data[j + half - 1]) / 2l;
		double m = odd ? *(next(window.begin(), half)) : (double)(*(next(window.begin(), half)) + *(next(window.end(), -1))) / 2l;
		if (data[i] >= 2 * m)
			count++;
		window.erase(window.find(data[i - d]));
		if (++i < data.size())
			window.insert(data[i]);
	}
	return count;
}
/*
 * https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
 * Uses CalculateMedian(vector<long> &data) defined above
 * Times out!
 */
size_t ActivityNotifications1(vector<size_t> &data, size_t d)
{
	size_t count = 0;
	for (vector<size_t>::iterator it = data.begin(), it1 = next(it, d); it1 < data.end(); it++, it1++)
	{
		const auto middleItr = next(it, d / 2);
		nth_element(it, middleItr, it1);
		double median = numeric_limits<double>::max();
		if (!(d % 2))
		{
			const auto leftMiddleItr = ranges::max_element(it, middleItr);
			median = (double)(*leftMiddleItr + *middleItr) / 2l;
		}
		else
			median = *middleItr;
		if (*it1 >= 2 * median)
			count++;
	}
	return count;
}
/*
 * [5 1 3 2 4], d: 3, middle: 2, shift: 0
 * i: 	   1 3 5    1 2 3
 * fSum:   1 2 3    1 2 3
 * median: 0 6 11   0 4
 * result:            1
 *
 * [2 3 4 2 3 6 8 4 5], d: 5, middle: 3, shift: 0
 * frequencies: {2:2, 3:2, 4:2, 5:1, 6:1, 8:1}
 * it: 	   2				3				4				2
 * it1:	   6				8				4				5
 * i: 	   [2 3 4  5 6 8]  [2 3 4  5 6 8]  [2 3 4  5 6 8]  [2 3 4  5 6 8]
 * fSum:    2 4 6  7		1 3 5			1 2 4  5		1 2 3  4
 * median:  0 6 10			0 6 10			0 0 8			0 0 8
 * result:    1				  1
 */
size_t ActivityNotifications2(vector<size_t> const &data, size_t d, size_t max)
{
	if (data.size() < d)
		return 0;
	vector<size_t> frequencies(max + 1, 0);
	for (vector<size_t>::const_iterator it = data.begin(); it < next(data.begin(), d); it++)
		frequencies[*it]++;																/* {5: 1, 1: 1, 3: 1}*/
	size_t middle = d / 2 + 1, fSum = 0, result = 0, median = 0, shift = d % 2 ? 0 : 1; /* middle: 2, shift: 0 */
	for (vector<size_t>::const_iterator it = data.begin(), it1 = next(it, d); it1 < data.end(); it++, it1++)
	{
		median = 0;
		fSum = 0;
		for (size_t i = 0; i < max; i++)
		{
			fSum += frequencies[i];
			if (!median && fSum >= middle - shift)
				median += i;
			if (fSum >= middle)
			{
				median += i;
				if (median <= *it1)
					result++;
				break;
			}
		}
		if (frequencies[*it] > 0)
			frequencies[*it]--;
		frequencies[*it1]++;
	}
	return result;
}
/*
 * https://www.hackerrank.com/challenges/the-power-sum/problem
 * sum = x^power
 * logx(sum)  = power
 * x = pow(sum, 1.0/power)
 * 100%
 */
size_t PowerSum(size_t sum, size_t power, size_t i)
{
	size_t n = pow(i, power);
	if (n > sum)
		return 0;
	else if (n == sum)
		return 1;
	return PowerSum(sum, power, i + 1) + PowerSum(sum - n, power, i + 1);
}
/*
 * https://www.hackerrank.com/challenges/morgan-and-a-string/problem
 * a: CAB, b: CAB => CABCAB
 * 100%
 */
string MorganAndString(string const &a, string const &b)
{
	string result;
	if (a.empty())
		return b;
	else if (b.empty())
		return a;
	size_t i = 0, j = 0;
	for (; i < a.size() && j < b.size();)
	{
		if (a[i] < b[j])
			result.append(1, a[i++]);
		else if (b[j] < a[i])
			result.append(1, b[j++]);
		else // a[i] == b[j]
		{
			size_t m = i + 1, n = j + 1;
			bool takeFromA = false;
			for (; m < a.size() && n < b.size(); m++, n++)
			{
				if (a[m] < b[n])
				{
					takeFromA = true;
					break;
				}
				else if (a[m] > b[n])
					break;
			}
			if (takeFromA || (m < a.size() && n == b.size()))
			{
				/*
				a: BA
				b: BC

				a: BC
				b: B
				r: BBC

				a: BA
				b: B
				r: BAB
				*/
				result.append(1, a[i++]);
				for (; i < a.size() && a[i] == a[i - 1];)
					result.append(1, a[i++]);
			}
			else
			{
				result.append(1, b[j++]);
				for (; j < b.size() && b[j] == b[j - 1];)
					result.append(1, b[j++]);
			}
		}
	}
	if (i < a.size())
		result.append(a.substr(i));
	if (j < b.size())
		result.append(b.substr(j));
	return result;
}
/*
 * https://www.hackerrank.com/challenges/journey-to-the-moon/problem
 * WIP
 * [0, 1] [2, 3] [0, 4] => [0, 1, 4] * [2, 3] = 6
 *
 * [1, 2] [2, 3] n: 4 => [1, 2, 3] * [0] = 3
 *				 n: 5 => [1, 2, 3] * [0] [4] =>

 * [0, 2], n: 4 => [0, 2] * [1] [3] =>
 * [0, 2] [1] [3] => [0, 1] [0, 3] [2, 1] [2, 3] [1, 3]
 *
 * [0, 2] [1, 8] [1, 4] [2, 8] [2, 6] [3, 5] [6, 9] => [0, 2, 8, 6, 9] [1, 8, 4] [3, 5] XXX
 * [0, 2, 6, 8, 1, 4, 9] [3, 5] [7] => 2 * 7 + 1 * 7 + 1 * 2 = 23
 */
size_t DistinctPairs(size_t n, vector<vector<size_t>> const &astronauts)
{
	set<size_t> ids;
	vector<set<size_t>> groups;
	for (size_t i = 0; i < n; i++)
		ids.emplace(i);
	for (vector<vector<size_t>>::const_iterator it = astronauts.begin(); it != astronauts.end(); it++)
	{
		ids.erase((*it)[0]);
		ids.erase((*it)[1]);
		bool found = false;
		for (vector<set<size_t>>::iterator it1 = groups.begin(); !found && it1 != groups.end(); it1++)
			if (it1->find((*it)[0]) != it1->end() || it1->find((*it)[1]) != it1->end())
			{
				it1->insert((*it)[0]);
				it1->insert((*it)[1]);
				found = true;
			}
		if (!found)
			groups.push_back(set<size_t>{(*it)[0], (*it)[1]});
	}
	for (vector<set<size_t>>::iterator it = groups.begin(); it != groups.end(); it++)
		for (vector<set<size_t>>::iterator it1 = next(it, 1); it1 != groups.end();)
		{
			set<size_t> duplicates;
			set_intersection(it->begin(), it->end(), it1->begin(), it1->end(), inserter(duplicates, duplicates.begin()));
			if (!duplicates.empty())
			{
				it->insert(it1->begin(), it1->end());
				it1 = groups.erase(it1);
			}
			else
				it1++;
		}
	size_t pairs = groups.size() > 1 ? 1 : 0, pairs1 = 0;
	for (vector<set<size_t>>::iterator it = groups.begin(); it != groups.end(); it++)
	{
		pairs *= it->size();
		pairs1 += ids.size() * it->size();
	}
	return BinomialCoefficients(ids.size(), 2) + pairs + pairs1;
}