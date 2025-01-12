#include "DynamicProgramming.h"
template class DynamicProgramming<char>;
template class DynamicProgramming<int>;
template class DynamicProgramming<size_t>;
template class DynamicProgramming<long>;
template class DynamicProgramming<long long>;
template class DynamicProgramming<unsigned long long>;
template class DynamicProgramming<string>;
template <typename T>
long double DynamicProgramming<T>::Factorial(T n)
    requires arithmetic_type<T>
{
    /* 0 1 2 3 4
     * {1 1 2 6 24 ...}
     * result = 1,
     */
    long double result = 1;
    if (n <= 0)
        return 1;
    for (size_t i = 2; i <= (size_t)n; result *= i++)
        ;
    return result;
}

/* Bottom-up Dynamic Programming
 */
template <typename T>
long double DynamicProgramming<T>::Fibonacci(T n)
    requires arithmetic_type<T>
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
/*
 * This is slightly better. It fails 2 tests due to timeout!
 */
template <typename T>
string DynamicProgramming<T>::FibonacciModified(T t1, T t2, T n)
    requires arithmetic_type<T>
{
    // Index: 0 1 2 3 4 5  6   7	  8
    // Value: 0 1 1 2 5 27 734 538783 ...
    if (!n)
        return to_string(t1);
    else if (n == 1)
        return to_string(t2);
    Arithmetic<T> arithmetic;
    vector<string> result = {to_string(t1), to_string(t2)};
    for (size_t i = 2; i <= (size_t)n; i++)
        result[i % 2] = arithmetic.NumberStringSum(result[(i - 2) % 2], arithmetic.NumberStringMultiplication(result[(i - 1) % 2], result[(i - 1) % 2]));
    return result[n % 2];
}

/* https://leetcode.com/problems/integer-break/
 * 100%
 */
template <typename T>
T DynamicProgramming<T>::LargestNumberCompositionProduct(T n)
    requires arithmetic_type<T>
{
    vector<T> dp(n + 1, 0);
    dp[1] = 1;
    for (T i = 2; i <= n; i++)
        for (T j = 1; j < i; j++)
            dp[i] = max<T>(dp[i], max<T>(j, dp[j]) * max<T>(i - j, dp[i - j]));
    return dp[n];
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
template <typename T>
T DynamicProgramming<T>::EggDrops(T eggs, T floors)
    requires arithmetic_type<T>
{
    vector<vector<T>> dp(eggs, vector<T>(floors + 1, numeric_limits<T>::max()));
    // Base case for Floor-0 and Floor-1
    for (T i = 0; i < eggs; i++)
    {
        dp[i][0] = 0;
        if (floors > 0)
            dp[i][1] = 1;
    }
    // Base case for 1 egg
    ranges::generate(dp[0], [n = 0]() mutable
                     { return n++; });
    // size_t attempts = eggDropsDynamicProgramming(eggs, floors, dp);
    for (T egg = 1; egg < eggs; egg++)
        for (T floor = 2; floor <= floors; floor++)
            for (T i = 2; i <= floor; i++)
                dp[egg][floor] = min<T>(dp[egg][floor], 1 + max<T>(dp[egg - 1][i - 1], dp[egg][floor - i]));
    return dp[eggs - 1][floors];
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
template <typename T>
bool DynamicProgramming<T>::WordBreak(string const &s, set<string> const &words)
{
    vector<bool> valid(s.size() + 1, false);     // flag to mark substring [0, end) validity
    valid[0] = true;                             // empty substring is a valid string
    for (size_t end = 1; end <= s.size(); end++) // O(N)
        for (size_t start = 0; start < end; start++)
        { // O(N) -> Time complexity: O(N^2)
            if (valid[start] && words.count(s.substr(start, end - start)))
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
template <typename T>
void DynamicProgramming<T>::WordBreak2(string const &s, set<string> const &words, vector<string> &result)
{
    map<size_t, vector<string>> strings;
    vector<bool> valid(s.size() + 1, false); // flag to mark substring [0, end) validity
    valid[0] = true;                         // empty substring is a valid string
    strings.emplace(0, vector<string>{""});
    for (size_t end = 1; end <= s.size(); end++)
        for (size_t start = 0; start < end; start++)
        {
            if (valid[start] && words.count(s.substr(start, end - start)))
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
template <typename T>
bool DynamicProgramming<T>::Abbreviation(string const &s1, string const &s2)
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
template <typename T>
size_t DynamicProgramming<T>::FindSubsequence(string const &str, string const &tomatch)
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
/* https://codility.com/demo/take-sample-test/number_solitaire/
 * https://codesays.com/2015/solution-to-number-solitaire-by-codility/
 * Return the maximal result that can be achieved on the board represented by data
 *       0  1 2 3  4  5  6 7
 * data: 1 -2 0 9 -1 -2 -3 9
 * dp  : 1,-1, MAX(-1, 1) = 1, MAX(10, 8, 10) = 10, MAX(0, -2, 0, 9) = 9, MAX(-1, -3, -1, 8, 7) = 8, MAX(-2, -4, -2, 7, 6, 5) = 7, MAX(10, 8, 10, 19, 18, 17, 16) = 19
 */
template <typename T>
T DynamicProgramming<T>::NumberSolitaire(vector<T> const &data)
    requires arithmetic_type<T>
{
    vector<T> dp(data.size(), numeric_limits<T>::min());
    dp[0] = data[0];
    for (long i = 1; i < (long)data.size(); i++)
        for (long j = 1; j < 7 && (i - j) >= 0; j++)
            dp[i] = max<T>(dp[i], data[i] + dp[i - j]);
    return dp[data.size() - 1];
}
/*
 * https://www.hackerrank.com/challenges/construct-the-array/problem
 * Constraint Satisfaction problem
 * 100% editorial solution but I don't fully understand how it works, especially the line:
 * cout << (x == 1 ? 1LL * (k - 1) * d[n - 2] % mod : d[n - 1]) << endl;
 * f(n) = (k-1)f(n-2) + (k-2)f(n-1)
 * f(0) = 0
 * f(1) = 1
n:3, k:3, x:1
1 [2,3] 1
1 [k-1] 1 => 2
i:2 [1,1] Actual dp: [0,1,1]
result: dp[(n-2)%2] * (k-1) = dp[1]*2 = 2

n:3, k:3, x:2
1 [3] 2
1 [k-2] 2 => 1
i:2 [1,1] Actual dp: [0,1,1]
result: dp[(n-1)%2] = 1

n:3, k:3, x:3
1 [2] 3
1 [k-2] 3 => 1
i:2 [1,1] Actual dp: [0,1,1]
result: dp[(n-1)%2] = 1

n:4, k:3, x:1
1 [2,3] [2,3] 1
1 [2] [3] 1
1 [3] [2] 1 => 2
1 [k-1] [k-1] 1
i:2 [1,1] Actual dp: [0,1,1]
i:3 [1,2+1] = [1,3] Actual dp: [0,1,1,3]
result: dp[(n-2)%2] * (k - 1) = dp[0] * 2 = 2

n:4, k:3, x:2
1 [2,3] [1,3] 2
1 [2] [1] 2
1 [2] [3] 2
1 [3] [1] 2 => 3
1 [k-1] [k-1] 2
i:2 [1,1] Actual dp: [0,1,1]
i:3 [1,2+1] = [1,3] Actual dp: [0,1,1,3]
result: dp[(n-1)%2] = 3

n:4, k:3, x:3
1 [2,3] [1,2] 3
1 [2] [1] 3
1 [3] [2] 3
1 [3] [1] 3 => 3
i:2 [1,1] Actual dp: [0,1,1]
i:3 [1,2+1] = [1,3] Actual dp: [0,1,1,3]
result: dp[(n-1)%2] = 3
 */
template <typename T>
unsigned long long DynamicProgramming<T>::WaysToFillRange(T n, T k, T x)
    requires arithmetic_type<T>
{
    const long double modulo = 1e9 + 7L;
    vector<unsigned long long> dp = {0, 1};
    for (T i = 2; i < n; i++)
        dp[i % 2] = fmodl(fmodl(dp[(i - 2) % 2] * (k - 1), modulo) + fmodl(dp[(i - 1) % 2] * (k - 2), modulo), modulo);
    return x == 1 ? fmodl(dp[(n - 2) % 2] * (k - 1), modulo) : dp[(n - 1) % 2]; // XXX: Don't understand this!
}
/*
 * https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
 * https://www.hackerrank.com/challenges/floyd-city-of-blinding-lights/problem
 * 100%
 */
template <typename T>
void DynamicProgramming<T>::FloydWarshall(size_t n, vector<vector<T>> const &edges, vector<vector<T>> &distances)
    requires signed_integral_type<T>
{
    distances.resize(n + 1);
    for (size_t i = 0; i <= n; i++)
    {
        distances[i] = vector<T>(n + 1, numeric_limits<T>::max());
        distances[i][i] = 0;
    }
    for (typename vector<vector<T>>::const_iterator it = edges.begin(); it != edges.end(); it++)
        distances[(*it)[0]][(*it)[1]] = (*it)[2];
    for (size_t k = 1; k <= n; k++) // Assuming 1-based index for vertex
        for (size_t i = 1; i <= n; i++)
            for (size_t j = 1; j <= n; j++)
                if (distances[i][k] != numeric_limits<T>::max() && distances[k][j] != numeric_limits<T>::max())
                    distances[i][j] = min<T>(distances[i][j], distances[i][k] + distances[k][j]);
}