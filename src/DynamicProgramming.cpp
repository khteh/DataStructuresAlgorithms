#include "pch.h"
#include "DynamicProgramming.h"
template class DynamicProgramming<int>;
template class DynamicProgramming<long long>;
template class DynamicProgramming<unsigned long long>;
template class DynamicProgramming<string>;
#if defined(__GNUC__) || defined(__GNUG__)
template class DynamicProgramming<__int128>;
template class DynamicProgramming<unsigned __int128>;
#endif
template class DynamicProgramming<int64_t>;
template class DynamicProgramming<uint64_t>;
template <typename T>
T DynamicProgramming<T>::Factorial(size_t n, T modulo)
    requires arithmetic_type<T>
{
    /* 0 1 2 3 4
     * {1 1 2 6 24 ...}
     * result = 1,
     */
    T result = 1;
    if (n <= 0)
        return 1;
    for (size_t i = 2; i <= (size_t)n; i++)
    {
        T tmp = result * i;
        if ((result > 0 && tmp < 0) || (result < 0 && tmp > 0))
            throw range_error("overflow!");
        result = tmp;
        if (modulo)
            result %= modulo;
    }
    return result;
}
/* Bottom-up Dynamic Programming
 */
template <typename T>
T DynamicProgramming<T>::Fibonacci(long n)
    requires arithmetic_type<T>
{
    /* 0 1 2 3
     * {0 1 1 2 3 5 8}
     * {0, 1}, {1, 1}, {1, 2}, {3, 2}, {3, 5}
     * [a,b] = [0,1] => a=0, b=1
     * [a,b] = [1,1] => a=b=1, b=a+b=0+1=1
     * [a,b] = [1,2] => a=b=1, b=a+b=1+1=2
     */
    // https://stackoverflow.com/questions/79421066/c-long-double-128-bit-precision
    vector<T> result = {0, 1};
    if (n <= 1)
        return n;
    /*
for (size_t i = 2; i <= (size_t)n; i++)
    result[i % 2] = result[(i - 2) % 2] + result[(i - 1) % 2];
return result[n % 2];
    */
    T a = 0, b = 1;
    for (size_t i = 2; i <= (size_t)n; i++)
    {
        T temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
/*
 * This is slightly better. It fails 2 tests due to timeout!
 */
template <typename T>
string DynamicProgramming<T>::FibonacciModified(T t1, T t2, size_t n)
    requires arithmetic_type<T>
{
    // Index: 0 1 2 3 4 5  6   7	  8
    // Value: 0 1 1 2 5 27 734 538783 ...
    if (!n)
        return to_string(t1);
    else if (n == 1)
        return to_string(t2);
    Arithmetic<string> arithmetic;
    vector<string> result = {to_string(t1), to_string(t2)};
    for (size_t i = 2; i <= (size_t)n; i++)
        result[i % 2] = arithmetic.NumberStringSum(result[(i - 2) % 2], arithmetic.NumberStringMultiplication(result[(i - 1) % 2], result[(i - 1) % 2]));
    return result[n % 2];
}

/* https://leetcode.com/problems/integer-break/
 * 100%
 * Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.
 * Return the maximum product you can get.
 *
 * Sum of k positive integers = n.
 * Refer to the LargestNumberCompositionProduct() in DataStructuresAlgorithms.cpp for mathematical implementation and better understanding.

 * n:10
 * 0 1 2 3 4 5 6 7 8 9 10
 * [0 1]
 * i:2 j:1 dp[2]=0 dp[j]=1
 *         i-j=1 dp[i-j]=1 => dp[2]=1
 * dp: [0, 1, 1] -> n:2 result:1 <- 1 + 1 = 2; 1 * 1 = 1
 *
 * [0 1 1]
 * i:3 j:1 dp[3]=0 dp[j]=1
 *         i-j=2 dp[i-j]=1 => dp[3]=2
 *
 *     j:2 dp[3]=2 dp[j]=1
 *         i-j=1 dp[i-j]=1 => dp[3]=2
 * dp: [0, 1, 1, 2] -> n:3 result:2 <- 2 + 1 = 3; 2 * 1 = 2
 *
 * [0 1 1 2]
 * i:4 j:1 dp[4]=0 dp[j]=1
 *         i-j=3 dp[i-j]=2 => dp[4]=3
 *
 *     j:2 dp[4]=3 dp[j]=1
 *         i-j=2 dp[i-j]=1 => dp[4]=4
 *
 *     j:3 dp[4]=4 dp[j]=2
 *         i-j=1 dp[i-j]=1 => dp[4]=4
 * dp: [0, 1, 1, 2, 4] -> n:4 result:4 -> n:4 result: 4 <- 4 + 1 = 5; 4 * 1 = 4
 *                                                      <- 2 + 2 = 4; 2 * 2 = 4
 *
 * [0 1 1 2 3]
 * i:5 j:1 dp[5]=0 dp[j]=1
 *         i-j=4 dp[i-j]=4 => dp[5]=4
 *
 *     j:2 dp[5]=4 dp[j]=1
 *         i-j=3 dp[i-j]=2 => dp[5]=6
 *
 *     j:3 dp[5]=6 dp[j]=2
 *         i-j=2 dp[i-j]=1 => dp[5]=6
 *
 *     j:4 dp[5]=6 dp[j]=4
 *         i-j=1 dp[i-j]=1 => dp[5]=6
 *
 * dp: [0 1 1 2 4 6] -> n:5 result:6 <- 3 + 2 = 5; 3 * 2 = 6
 *                               <- 2 + 2 + 1 = 5; 2 * 2 * 1 = 4
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
* Egg broken: 1 egg less, #floors = #floors - 1 (1 floor below is the potential pivot floor)
* Egg not broken: Same #eggs, #floors = #floors - floors tried so far
*
* Each pair is a sub-problem written as (eggs, floors): how many eggs you have left and how many floors you still need to check.
*
  dp[egg][floor] = min<T>(dp[egg][floor], 1 + max<T>(dp[egg - 1][i - 1], dp[egg][floor - i]));
                                                  // └─ (eggs−1, f−1) ─┘ └─ (eggs, floors−f) ┘

*		2 Eggs, 4 floors					<= for (size_t floor = 2; floor <= floors; floor++)
*    f=1		f=2			f=3		  f=4	<= for (size_t i = 2; i <= floor; i++)
* (1,0)(2,3) (1,1)(2,2) (1,2)(2,1) (1,3)(2,0)
*  ↑    ↑
* broke  didn't break
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
        0	0	1	2	3	4	5	6
        1	0	1
        2	0	1
* https://leetcode.com/problems/super-egg-drop/
* Time limit exceeded! (eggs:6, floors: 10000)
* TC: O(eggs × floors²)
* SC: O(eggs × floors)
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
                /*
                    max is used because you don’t know which outcome will happen, so you plan for the worse one.
                    + 1 counts this drop.
                    min over all f picks the floor whose worst case is the best.
                */
                dp[egg][floor] = min<T>(dp[egg][floor], 1 /* Current floor */ + max<T>(dp[egg - 1][i - 1], dp[egg][floor - i]));
    return dp[eggs - 1][floors];
}
/*
 * https://leetcode.com/problems/super-egg-drop/
 * 100%
Flip the question

Instead of asking “what’s the fewest drops for k eggs and n floors?”, ask:

With m drops and k eggs, how many floors can I fully check?

Call that dp[m][k]. Drop the first egg from some floor:

It breaks. You have m − 1 drops and k − 1 eggs left, which can check dp[m−1][k−1] floors below.
It survives. You have m − 1 drops and k eggs left, which can check dp[m−1][k] floors above.
Plus 1 for the floor you dropped from.

dp[m][k] = dp[m−1][k−1] + dp[m−1][k] + 1

Increase m until dp[m][eggs] ≥ floors. That m is the answer. There’s no inner loop over drop floors, because the recurrence already places the drop at the best floor.

The answer m is small. It’s at most floors, and for many eggs about log₂(floors). So this runs in O(eggs × answer).

 * dp[k]: max #floors that can be fully checked with the current #moves and k eggs.
 * Each move: drop from the floor that splits the building into
 *   below: dp[k-1] floors (egg broke: 1 egg less, 1 move less)
 *   above: dp[k]   floors (egg survived: same eggs, 1 move less)
 *   +1 for the floor dropped from
 * => dp[m][k] = dp[m-1][k-1] + dp[m-1][k] + 1
 * Iterate k downwards so dp[k-1] still holds the previous move's value.
 * Time: O(eggs * moves), Space: O(eggs)
 *
 * k counts down for the same reason as in the 0/1 knapsack 1-D trick: dp[k] is updated in place, and dp[k − 1] must still hold the previous move’s value when you read it.
 *
 * The 1-D version is the 2-D table with only one row kept in memory. Here it is step by step with a small example: 2 eggs, 10 floors.

The 2-D table

dp[m][k] is the most floors you can fully check with m drops and k eggs, using:

dp[m][k] = dp[m−1][k−1] + dp[m−1][k] + 1

Fill it row by row:

         k=0  k=1  k=2
m=0       0    0    0     ← no drops: check 0 floors
m=1       0    1    1
m=2       0    2    3
m=3       0    3    6
m=4       0    4   10     ← dp[4][2] = 10 ≥ 10 floors → answer: 4 drops

Why one row is enough

Each row only reads from the row directly above it. Once row 3 is done, rows 0, 1 and 2 are never needed again. So you keep one row, dp[k], and overwrite it in place to turn row m−1 into row m:

dp[k] += dp[k - 1] + 1;
// dp[k] (new)  =  dp[k] (old, = dp[m−1][k])  +  dp[k−1] (must still be old, = dp[m−1][k−1])  +  1

Rows are m, the number of drops.
Columns are k, the number of eggs.

The 1-D array dp holds one row of the table, and its index k picks the column within that row:

         k=0  k=1  k=2       ← columns = array index k
m=2       0    2    3        ← the 1-D array dp holds this row: dp = [0, 2, 3]
m=3       0    3    6        ← after one pass of the k-loop, dp holds this row: dp = [0, 3, 6]

So one pass of for (k = eggs; k > 0; k--) turns the array from row m−1 into row m, one slot at a time.
During that pass, the array is a mix of two rows. The slots you’ve already updated hold the new row; the ones you haven’t reached still hold the old row.

k:2 dp[2] = dp[2] + dp[1] + 1 <- read dp[1] first. Both dp[2] and dp[1] are old values used to calculate new value of dp[2]
    dp[1] = dp[1] + dp[0] + 1 <- update dp[1]. It doesn't use the updated/new dp[2] value

    dp[1] = dp[1] + dp[0] + 1 <- read dp[0]
    dp[2] = dp[2] + dp[1] + 1 <- dp[1] used in the calculation is not the *old* value but the new/updated value, which is WRONG.

    So, we need to iterate k downwards so dp[k-1] still holds the previous move's value.

TC: O(eggs * moves), Space: O(eggs)
 */
template <typename T>
T DynamicProgramming<T>::EggDropsImproved(T eggs, T floors)
    requires arithmetic_type<T>
{
    vector<T> dp(eggs + 1, 0);
    T moves = 0;
    for (; dp[eggs] < floors; moves++)
        for (T k = eggs; k > 0; k--)
            dp[k] += dp[k - 1] + 1;
    return moves;
}
/* https://leetcode.com/problems/word-break/
 * 100%
 * Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 *
 * Dynamic programming with tabulation (bottom-up) approach
 *
 * valid[end]: whether prefix [0, end) can be segmented into dictionary words.
 * [0, end) is valid iff there is a split point start < end where
 *   [0, start) is valid (already computed) AND s[start, end) is a dictionary word.
 * Not every prefix of a valid string is valid ("catsand" is valid, "catsa" is not);
 * only the prefixes ending at word boundaries are.
 *
 * 0123456
 * catsand
 * [0,0) valid + "cat"  [0,3) -> [0,3) valid; [0,3) valid + "sand" [3,7) -> [0,7) valid
 * [0,0) valid + "cats" [0,4) -> [0,4) valid; [0,4) valid + "and"  [4,7) -> [0,7) valid
 *
 * 012345678
 * catsandog
 * [0,0) valid + "cat"  [0,3) -> [0,3) valid; [0,3) valid + "sand" [3,7) -> [0,7) valid -> [0,7) valid + "og" [7,9) -> [0,9) invalid
 * [0,0) valid + "cats" [0,4) -> [0,4) valid; [0,4) valid + "and"  [4,7) -> [0,7) valid -> [0,7) valid + "og" [7,9) -> [0,9) invalid

 * 0123456789
 * catsanddog
 * [0,0) valid + "cat"  [0,3) -> [0,3) valid; [0,3) valid + "sand" [3,7) -> [0,7) valid -> [0,7) valid + "dog" [7,10) -> [0,10) valid
 * [0,0) valid + "cats" [0,4) -> [0,4) valid; [0,4) valid + "and"  [4,7) -> [0,7) valid -> [0,7) valid + "dog" [7,10) -> [0,10) valid
 *
 */
template <typename T>
bool DynamicProgramming<T>::WordBreak(string const &s, set<string> const &words)
{
    vector<bool> valid(s.size() + 1, false);     // flag to mark substring [0, end) validity
    valid[0] = true;                             // empty substring is a valid string
    for (size_t end = 1; end <= s.size(); end++) // O(N)
        for (size_t start = 0; start < end; start++)
            // O(N) -> Time complexity: O(N^2)
            if (valid[start] && words.count(s.substr(start, end - start)))
            {
                valid[end] = true;
                break;
            }
    return valid.back();
}
/* https://leetcode.com/problems/word-break-ii/
 * 100%
 * Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 *
 * 0123456
 * catsand
 * [0,0) valid + "cat"  [0,3) {3: ["cat"]} -> [0,3) valid; [0,3) valid + "sand" [3,7) {3: ["cat"], 7: ["cat sand"]} -> [0,7) valid
 * [0,0) valid + "cats" [0,4) {3: ["cat"], 4: ["cats"]} -> [0,4) valid; [0,4) valid + "and" [4,7) {3: ["cat"] 4: ["cats"], 7: ["cats and", "cats and"]} -> [0,7) valid
 */
template <typename T>
vector<string> DynamicProgramming<T>::WordBreak2(string const &s, set<string> const &words)
{
    map<size_t, vector<string>> strings;
    vector<bool> valid(s.size() + 1, false); // flag to mark substring [0, end) validity
    valid[0] = true;                         // empty substring is a valid string
    strings.emplace(0, vector<string>{""});
    for (size_t end = 1; end <= s.size(); end++)
        for (size_t start = 0; start < end; start++)
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
    return strings[s.size()];
}
/*
 * https://www.hackerrank.com/challenges/abbr/problem
 * 100%
 * Can s1 be turned into s2 by:
 *   (1) capitalising zero or more of its lowercase letters, and
 *   (2) deleting all the remaining lowercase letters?
 * Uppercase letters in s1 can never be deleted or changed: each one must match s2.
 *
 * State:
 *   table[i][j] = true iff the first i chars of s1, s1[0, i), can become the first j chars of s2, s2[0, j)
 *
 * Base cases:
 *   table[0][0] = true                               <- empty s1 becomes empty s2
 *   table[i][0] = table[i-1][0] && islower(s1[i-1])  <- s1[0, i) becomes "" only if every char is lowercase (all deleted)
 *   table[0][j] = false for j > 0                    <- empty s1 can't produce any letters
 *
 * Transition: look at the last char of s1[0, i), c = s1[i-1]. Two choices:
 *   (a) Keep c as s2's j-th char: c, capitalised if lowercase, must equal s2[j-1],
 *       and the rest, s1[0, i-1), must become s2[0, j-1)          -> table[i-1][j-1]  (diagonal ↘)
 *   (b) Delete c: only allowed if c is lowercase,
 *       and s1[0, i-1) must already become all of s2[0, j)       -> table[i-1][j]    (straight down ↓)
 *   table[i][j] = (table[i-1][j-1] && toupper(c) == s2[j-1]) || (table[i-1][j] && islower(c))
 *
 * Example: s1 = "daBcd", s2 = "ABC" -> YES ("dAbcd" -> capitalise a, c; delete d, d)
 *
 *          j:0  A  B  C
 *   i:0     1   0  0  0
 *   d       1   0  0  0    <- [1][0]: delete d, "" -> "" ([0][0]). [1][1]: D != A, and "" can't become "A" ([0][1] = 0)
 *   a       1   1  0  0    <- [2][0]: delete a, "" -> "" ([1][0]). [2][1]: capitalise a -> A, "d" -> "" ([1][0])
 *   B       0   0  1  0    <- B can't be deleted: [3][0], [3][1] = 0. [3][2]: B == B, "da" -> "A" ([2][1])
 *   c       0   0  1  1    <- [4][2]: delete c ([3][2]). [4][3]: capitalise c -> C, "daB" -> "AB" ([3][2])
 *   d       0   0  1  1    <- [5][2]: delete d ([4][2]). [5][3]: delete d, "daBc" -> "ABC" ([4][3])
 *                     ↑ table[5][3] = 1 -> YES *
 *
 * TC: O(|s1| * |s2|), Space: O(|s1| * |s2|)
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
i:0(s="")		1	0			0			0			0			 0				0				0				0
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
            string s1 = tomatch.substr(tomatch.size() - j, j);
            if (s1.empty())
                counts[i][j] = 1;
            else if (s.empty())
                counts[i][j] = 0;
            else if (i > 0 && j > 0)
            {
                // s[0, i-1) must already become all of s1[0, j)       -> table[i-1][j]    (straight down ↓)
                counts[i][j] = counts[i - 1][j]; // Preserve previously matched character
                if (s[0] == s1[0])
                    // the rest, s1[0, i-1), must become s1[0, j-1)          -> table[i-1][j-1]  (diagonal ↘)
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
 *
 * i:1, j:[1] -> dp[1] = max(dp[1], data[1] + dp[0]) = max(-inf, 1 - 2)  = -1
 * i:2, j:[1, 2] -> dp[2] = max(dp[2], data[2] + dp[1]) = max(-inf, -1)  = -1
 *                  dp[2] = max(dp[2], data[2] + dp[0]) = max(-1, 1)  = 1
 * i:3, j:[1, 3] -> dp[3] = max(dp[3], data[3] + dp[2]) = max(-inf, 10)  = 10
 *                  dp[3] = max(dp[3], data[3] + dp[1]) = max(10, 8)  = 10
 *                  dp[3] = max(dp[3], data[3] + dp[0]) = max(10, 10)  = 10
 * dp[n] = max(dp[n], max(max(data[n] + dp[n-1], data[n] + dp[n - 2]), data[n] + dp[n - 3])...)
 */
template <typename T>
T DynamicProgramming<T>::NumberSolitaire(vector<T> const &data)
    requires arithmetic_type<T>
{
    vector<T> dp(data.size(), numeric_limits<T>::min());
    dp[0] = data[0];
    for (long i = 1; i < (long)data.size(); i++)
        for (long j = 1; j < 7 && (i - j) >= 0; j++) // To achieve the position i, we can only come from the positions i-6, i-5, i-4, i-3, i-2, and i-1. Dice has 6 faces, so we can only jump from the last 6 positions.
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
result: dp[(n-2)%2] * (k - 1) = dp[0] * 2 = 2. Actual dp: [0,1,1,3,2]

n:5, k:3, x:1
1 [2,3] [1,2,3] [2,3] 1
1 [2] [1] [2] 1
1 [2] [1] [3] 1
1 [2] [3] [2] 1
1 [3] [1] [2] 1
1 [3] [1] [3] 1
1 [3] [2] [3] 1
i:2 [1,1] Actual dp: [0,1,1]
i:3 [1,2+1] = [1,3] Actual dp: [0,1,1,3]
i:4 [2+3,3] = [5,3] Actual dp: [0,1,1,3,5]
result: dp[(n-2)%2] * (k - 1) = dp[1] * 2 = 3*2 = 6. Actual dp: [0,1,1,3,5,6]

n:4, k:3, x:2
1 [2,3] [1,3] 2
1 [2] [1] 2
1 [2] [3] 2
1 [3] [1] 2 => 3
1 [k-1] [k-1] 2
i:2 [1,1] Actual dp: [0,1,1]
i:3 [1,2+1] = [1,3] Actual dp: [0,1,1,3]
result: dp[(n-1)%2] = 3. Actual dp: [0,1,1,3,3]

n:5, k:3, x:2
1 [2,3] [1,2,3] [1,3] 2
1 [2] [1] [3] 2
1 [2] [3] [1] 2
1 [3] [1] [3] 2
1 [3] [2] [1] 2
1 [3] [1] [3] 2 => 5
i:2 [1,1] Actual dp: [0,1,1]
i:3 [1,2+1] = [1,3] Actual dp: [0,1,1,3]
i:4 [2+3,3] = [5,3] Actual dp: [0,1,1,3,5]
result: dp[(n-1)%2] = 5. Actual dp: [0,1,1,3,5,5]

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
T DynamicProgramming<T>::WaysToFillRange(size_t n, size_t k, size_t x)
    requires arithmetic_type<T>
{
    const T modulo = 1e9 + 7L;
    vector<T> dp = {0, 1};
    for (T i = 2; i < n; i++)
        dp[i % 2] = ((dp[(i - 2) % 2] * (k - 1)) % modulo + (dp[(i - 1) % 2] * (k - 2)) % modulo) % modulo;
    return x == 1 ? (dp[(n - 2) % 2] * (k - 1)) % modulo : dp[(n - 1) % 2]; // XXX: Don't understand this!
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
"contributions" = # times the number contribute to the sum of the slice / piece. Example: (1,3) => (1 + 3) * 2 = 1 * 2 + 3 * 2 => 1's contributions = 2, 3's contributions = 2.
                = Length of the slice / piece.
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
 * 100%
 */
template <typename T>
T DynamicProgramming<T>::VectorSlicesSum(vector<T> const &data)
    requires arithmetic_type<T>
{
    T result = 0;
    const long modulo = 1e9 + 7L;
    if (!data.empty())
    {
        vector<T> twoPower = {1};
        for (size_t i = 0; i < data.size(); i++)
        {
            T tmp = twoPower.back() * 2;
            if ((twoPower.back() > 0 && tmp < 0) || (twoPower.back() < 0 && tmp > 0))
                throw range_error("overflow!");
            twoPower.push_back(tmp % modulo);
        }
        T sum = twoPower.back() - 1, tmp = data[0] * sum;
        if (((sum > 0 && data[0] > 0) || (sum < 0 && data[0] < 0)) && tmp < 0)
            throw range_error("overflow!");
        result = tmp % modulo;
        T prevResult = result;
        for (size_t i = 1, y = data.size() - 2L; i < data.size(); i++, y--)
        {
            /*
             * https://www.hackerrank.com/contests/world-codesprint-7/challenges/summing-pieces/forum/comments/188413
             * (a - b) % m = (a % m - b % m + m) % m
             */
            T tmp = (twoPower[y] % modulo - twoPower[i - 1] % modulo + modulo) % modulo;
            if (sum > 0 && tmp > numeric_limits<T>::max() - sum)
                throw range_error("overflow!");
            if (sum < 0 && tmp < numeric_limits<T>::min() - sum)
                throw range_error("overflow!");
            sum = (sum + tmp) % modulo;
            tmp = data[i] * sum;
            if (((data[i] > 0 && sum > 0) || (data[i] < 0 && sum < 0)) && tmp < 0)
                throw range_error("overflow!");
            if (result > 0 && (tmp % modulo) > numeric_limits<T>::max() - result)
                throw range_error("overflow!");
            if (result < 0 && (tmp % modulo) < numeric_limits<T>::min() - result)
                throw range_error("overflow!");
            prevResult = result;
            result = (result + tmp % modulo) % modulo;
        }
    }
    return result;
}
/*
 * https://leetcode.com/problems/unique-paths/description/
 * 100%
 */
template <typename T>
size_t DynamicProgramming<T>::UniquePaths(size_t rows, size_t cols)
{
    vector<vector<size_t>> dp(rows, vector<size_t>(cols, 0));
    ranges::fill(dp[0], 1);
    for (size_t i = 0; i < rows; i++)
        dp[i][0] = 1;
    for (size_t i = 1; i < rows; i++)
        for (size_t j = 1; j < cols; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    return dp[rows - 1][cols - 1];
}
/*
 * https://leetcode.com/problems/edit-distance/
 * 100%
    rep_cost:1

      0 r  o s
    0 0 1  2 3
    h 1 1  2 3
    o 2 2 [1] 2 ho-> ro : h->r 1 edits
    r 3[2] 2 2
    s 4 3  3 [2] hors -> ros : Remove h 1 del,
    e 5 4 [4] 3 horse -> ro: Remove "ho": + Remove 'e': 3 dels, s->o 1 edits | horse -> ros: Remove "ho" 2 dels, "se"->"os" 2 edits

    rep_cost:2
    j  0 1  2 3
  i      r  o s
  0    0 1  2 3
  1  h 1 2  3 4
  2  o 2 3 [2] 3 ho-> ro : h->r 2 edits
  3  r 3 [2] 3 4 hor -> r : Remove "ho" 2 dels
  4  s 4 3  4 [3]  hors -> ros : Remove h: 1 del, "or" -> "ro"
  5  e 5 4  5 4 horse -> ros: Remove "ho": + Remove 'e': 3 dels, s->o 2 edits
*/
template <typename T>
size_t DynamicProgramming<T>::MinimumEditDistance(string const &word1, string const &word2, size_t ins_cost, size_t del_cost, size_t rep_cost)
{
    vector<vector<size_t>> distances(word1.size() + 1, vector<size_t>(word2.size() + 1, 0)); // word index is 1-based
    for (size_t i = 1; i <= word1.size(); i++)
        distances[i][0] = distances[i - 1][0] + del_cost;
    for (size_t i = 1; i <= word2.size(); i++)
        distances[0][i] = distances[0][i - 1] + ins_cost;
    for (size_t i = 1; i <= word1.size(); i++)
        for (size_t j = 1; j <= word2.size(); j++)
        {
            size_t replace_cost = word1[i - 1] == word2[j - 1] ? 0 : rep_cost; // Comparing the current chracter since it is 1-based
            distances[i][j] = min(distances[i - 1][j] + del_cost, min(distances[i][j - 1] + ins_cost, distances[i - 1][j - 1] + replace_cost));
        }
    return distances[word1.size()][word2.size()];
}
/*
 * https://leetcode.com/problems/house-robber
 * 100%
 * (1) Rob current house(i) + previous 2 proceed(i-2)
 * (2) Skip current house, take proceed from previous house(i-1)
 * [1 2 3 1]: 4
 * [0 1 2 3 1]
 * [0 1]
 * i:2 max(2, 1)=2 [0 1 2]     | [2 1]
 * i:3 max(4, 2)=4 [0 1 2 4]   | [2 4]
 * i:4 max(3, 4)=4 [0 1 2 4 4] | [4 4]
 *
 * [2,7,9,3,1]: 12
 * [0 2 7 9 3 1]
 * [0 2]
 * i:2 max(7, 2)=7 [0 2 7]             | [7 2]
 * i:3 max(11, 7)=11 [0 2 7 11]        | [7 11]
 * i:4 max(10, 11)=11 [0 2 7 11 11]    | [11 11]
 * i:5 max(12, 11)=12 [0 2 7 11 11 12] | [11 12]
 *
 * [5 1 3 2 4]: 12
 * [0 5 1 3 2 4]
 * [0 5]
 * i:2 max(5, 1)=5 [0 5 5]      | [5 5]
 * i:3 max(8, 5)=8 [0 5 5 8]    | [5 8]
 * i:4 max(7, 8)=8 [0 5 5 8 8]  | [8 8]
 * i:5 max(12,8)=12 [0 5 5 8 8 12] | [8 12]
 */
template <typename T>
T DynamicProgramming<T>::NonAdjacentMaxSum(vector<T> &data)
    requires arithmetic_type<T>
{
    vector<T> result(2, 0);
    if (data.empty())
        return 0;
    result[1] = data[0];
    data.insert(data.begin(), 0);
    for (size_t i = 2; i < data.size(); i++)
        result[i % 2] = max<T>(result[(i - 2) % 2] + data[i], result[(i - 1) % 2]);
    return result[(data.size() - 1) % 2];
}
