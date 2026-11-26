#include "pch.h"
#include "SlidingWindow.h"
template class SlidingWindow<int64_t>;
template class SlidingWindow<uint64_t>;
template class SlidingWindow<double>;
#ifdef __SIZEOF_INT128__
template class SlidingWindow<int128_t>;
template class SlidingWindow<uint128_t>;
#endif
#ifdef _MSC_VER
template class SlidingWindow<size_t>;
template class SlidingWindow<long>;
#endif
/*
 * https://leetcode.com/problems/sliding-window-maximum/
 * 100%
 * A sliding window needs monotonicity: if a window is fixable, so is a smaller one inside it.
 * Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

 * [1,3,-1,-3,5,3,6,7], k:3
 * i:0 [1] window: [0]
 * i:1 [3] window: [1]
 * i:2 [3 -1] window: [1 2], result: [3]
 * i:3 [3 -1 -3] window: [1 2 3], result: [3 3]
 * i:4 [-1 -3] window: [2 3] => window: [2] => [5] window: [4] result: [3 3 5]
 * i:5 [5 3] => window: [4 5], result: [3 3 5 5]
 * i:6 [6] => window: [6], result: [3 3 5 5 6]
 * i:7 [7] => window: [7], result: [3 3 5 5 6 7]
 *
 * [7,2,4], k:2
 * i:0 [7]
 * i:1 [7 2] => result: [7]
 * i:2 [4] => result: [7 4]
 *
 * [1 -1], k:1
 * i:0 [1] => result: [1]
 * i:1 [-1] => reulst: [1 -1]
 */
template<typename T>
void SlidingWindow<T>::MaxSlidingWindow(vector<T> const& data, size_t k, vector<T>& result)
{
    deque<long> window;
    for (long i = 0; i < data.size(); i++)
    {
        if (!window.empty() && window.front() == (i - k))
            window.pop_front();
        for (; !window.empty() && data[window.back()] < data[i]; window.pop_back())
            ;
        window.push_back(i);
        if (i >= (k - 1) && !window.empty())
            result.push_back(data[window.front()]);
    }
}
/*
 * https://leetcode.com/problems/fruit-into-baskets/description/
 * 100%
 * A sliding window needs monotonicity: if a window is fixable, so is a smaller one inside it.
 * Sliding Window approach.
 *
 * [1] 2 1
 * basket[1]: 1
 *
 * 1 [2] 1
 * basket[1]: 1
 * basket[2]: 1
 *
 * 1 2 [1]
 * basket[1]: 2
 * basket[2]: 1
 *
 * ================================
 * [0] 1 2 2
 * basket[0]: 1
 *
 * 0 [1] 2 2
 * basket[0]: 1
 * basket[1]: 1
 *
 * 0 1 [2] 2
 * basket[0]: 0 i:1
 * basket[1]: 1
 * basket[2]: 1
 *
 * 0 1 2 [2]
 * basket[0]: 0 i:1
 * basket[1]: 1
 * basket[2]: 2 j:3 result: j - i + 1 = 3
 *
 * =====================================
 * [1] 2 3 2 2
 * basket[1]: 1
 *
 * 1 [2] 3 2 2
 * basket[1]: 1
 * basket[2]: 1
 *
 * 1 2 [3] 2 2
 * basket[1]: 0 i:1
 * basket[2]: 1
 * basket[3]: 1
 *
 * 1 2 3 [2] 2
 * basket[1]: 0 i:1
 * basket[2]: 2 j:3
 * basket[3]: 1
 *
 * 1 2 3 2 [2]
 * basket[1]: 0 i:1
 * basket[2]: 3 j:4 result: j - i + 1 = 4
 * basket[3]: 1
 *
 * ====================================
 * 1 1 0 2 2 2
 * basket[1]: 0 i:2
 * basket[0]: 1
 * basket[2]: 3 j:5 result: j - i + 1 = 4
 */
template<typename T>
size_t SlidingWindow<T>::MaxHarvest(vector<T> const& fruits, size_t n)
{
    map<size_t, size_t> count;
    size_t result = 0;
    for (size_t i = 0, j = 0; i < fruits.size() && j < fruits.size(); j++)
    {
        count[fruits[j]]++;
        for (; count.size() > n && i < j; i++)
            if (!--count[fruits[i]])
                count.erase(fruits[i]);
        result = max(result, j - i + 1);
    }
    return result;
}
/*
 * https://www.hackerrank.com/challenges/bear-and-steady-gene/problem
 * 100%
 * Find the length of the smallest possible substring that can be replaced to make a steady gene
 * A sliding window needs monotonicity: if a window is fixable, so is a smaller one inside it.
 * Sliding window implementation.
 * The key fact: only the letters outside the window matter
Call the substring you replace the window. Whatever is inside it can become anything, and the letters outside stay as they are. So:
A window works if and only if every letter appears at most n/4 times outside it.

1. If a letter appears more than n/4 times outside, no replacement can remove the extra copies, so the gene can’t become steady.
2. If every letter is at most n/4 outside, the window has exactly enough room to make up the shortfalls. Its length is n minus the letters outside, which is exactly Σ (n/4 − outside count). So you fill it with the missing letters.

In the code, genes holds the counts outside the window, not the counts of the whole gene. It starts as the counts of the whole gene because the window starts empty. genes[gene[j++]]-- moves a letter into the window, and genes[gene[i++]]++ puts one back outside.

Why a sliding window works here:

Making a window bigger only moves more letters inside, so the outside counts can only go down. A window that works keeps working when it grows. That’s the property that makes the method correct.
When the window works and the loop moves i forward, j stays where it is. It never has to move back.
Moving i forward takes one letter out of the window and puts it back outside. A smaller window can only be the same or worse. So no end before the current j can suddenly work.
Those ends had already failed with the bigger window, and with one fewer letter they still fail. So the loop just carries on from the current j:

1. The window works: record j − i, then i++. Try dropping the leftmost letter, to see if a shorter window still works.
2. The window doesn’t work: j++. Add the next letter on the right.

Each pointer only moves forward, at most n times each, so the function is O(n).

(For ACGTCCGT: n/4 = 2, and only C is over, at 3. So a window holding one C works, and the answer is 1.)

Σ (n/4 − outside count) means work out n/4 − (that letter’s count outside the window) for each of the four letters, then add the four results.

Each term (n/4 − outside count) is a letter’s shortfall: how many more copies of it the gene needs to reach n/4. Written out:

Σ (n/4 − outside count) = (n/4 − outside A) + (n/4 − outside C) + (n/4 − outside G) + (n/4 − outside T)

Why it equals the window’s length. Every letter is either inside the window or outside it, so:

window length = n − (outside A + outside C + outside G + outside T)

n is 4 × n/4, which is n/4 once for each letter. So the right-hand side can be regrouped as one shortfall per letter:

n − (outside A + … + outside T) = (n/4 − outside A) + (n/4 − outside C) + (n/4 − outside G) + (n/4 − outside T)

So the total of the shortfalls is exactly the room you have in the window. Filling the window with each letter’s missing copies uses up every position, with none left over.

Example: ATAA, replacing the final AA (n = 4, so n/4 = 1):

Letter	Outside AT[AA]	Shortfall = 1 − outside
A	    1	            0
T	    1	            0
C	    0	            1
G	    0	            1
Total		            2 = the window’s length

So the window becomes CG, giving ATCG, with one of each ✓.

Why every letter must be at most n/4 outside. If a letter is over n/4 outside the window, its shortfall is negative.
That’s an extra copy you have no way to remove, so no filling of the window can fix the gene. When every shortfall is 0 or more, the window can always be filled exactly.

i	j	Window	Outside A, T	Works?
0	0	[]ATAA	3, 1	        no → grow
0	1	[A]TAA	2, 1	        no → grow
0	2	[AT]AA	2, 0	        no → grow
0	3	[ATA]A	1, 0	        yes: length 3, shrink
1	3	A[TA]A	2, 0	        no → grow, so j = 4 and the loop exits
1	4	A[TAA]	1, 0	        yes: length 3, shrink
2   4   AT[AA]  1, 1            yes: length 2, shrink
3   4   ATA[A]  2, 1            no → break
 */
template<typename T>
size_t SlidingWindow<T>::SteadyGene(string const& gene)
{
    size_t count = numeric_limits<size_t>::max();
    if (gene.size() % 4) // gene.size() should be divisable by 4
        return count;
    size_t balancedCount = gene.size() / 4;
    map<char, size_t> genes; // the counts outside the window
    for (string::const_iterator it = gene.begin(); it != gene.end(); it++)
        genes[*it]++;
    for (size_t i = 0, j = 0; i < gene.size();)
        if (genes['A'] <= balancedCount && genes['C'] <= balancedCount && genes['G'] <= balancedCount && genes['T'] <= balancedCount)
        {
            count = min(count, j - i);
            genes[gene[i++]]++;   // Works: record it, then try a shorter window by shrinking from the left
        }
        else if (j < gene.size())
            genes[gene[j++]]--;   // Doesn't work: grow it on the right
        else
            break;                // Doesn't work and can't grow: no window starting at i or later works
    return count;
}
/*
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 * 100%
 * You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character.
 * You can perform this operation at most k times. Return the length of the longest substring containing the same letter you can get after performing the above operations.
 *
 * A sliding window needs monotonicity: if a window is fixable, so is a smaller one inside it.
 * Sliding window implementation
 * [A]BAB k=1: maxFreq:1, maxLength:1
 * [AB]AB : maxFreq:1, maxLength:2
 * [ABA]B : maxFreq:2, maxLength:3
 * [ABAB] : maxFreq:2, diff:2, maxLength:3
 * A[BAB] : maxFreq:2, diff:1, maxLength:3
 *
 * [A]CBA k=1, maxFreq:1, maxLength:1
 * [AC]BA : maxFreq:1, maxLength:2
 * [ACB]A : maxFreq:1, diff:2, maxLength:3
 * A[CB]A : maxFreq:1, diff:1, maxLength:2
 * A[CBA] : maxFreq:1, diff:2, maxLength:2
 * AC[BA] : maxFreq:1, diff:1, maxLength:2
 */
template<typename T>
size_t SlidingWindow<T>::LongestStringWithCharacterReplacement(string const& s, size_t k)
{
    map<char, size_t> freqs;
    size_t maxLength = 0, maxFreq = 0;
    for (size_t i = 0, j = 0; i < s.size() && j < s.size(); j++)
    {
        maxFreq = max(maxFreq, ++freqs[s[j]]);
        for (; (j - i + 1 - maxFreq) > k && i < s.size(); freqs[s[i++]]--)
            ;
        maxLength = max(maxLength, j - i + 1);
    }
    return maxLength;
}
/*
https://www.hackerrank.com/challenges/substring-diff/problem
WIP - 2 test cases failed
In this problem, we'll use the term "longest common substring" loosely. It refers to substrings differing at some number or fewer characters when compared *index by index*.
For example, 'abc' and 'adc' differ in one position, 'aab' and 'aba' differ in two.
Given two strings and an integer , determine the length of the longest common substrings of the two strings that differ in no more than  positions.
For example, . Strings  and . Check to see if the whole string (the longest substrings) matches. Given that neither the first nor last characters match and , we need to try shorter substrings.
The next longest substrings are  and . Two pairs of these substrings only differ in  position:  and . They are of length .

Shift d	−5	−4	−3	−2	−1	0	1	2	3	4	5
Length	1	2	3	4	5	6	5	4	3	2	1
All the lengths add up to 6 × 6 = 36: every cell of the comparison table is on exactly one diagonal:
1 2 3 4	5 6 5 4 3 2 1 -> 5*6 + 6 = 36
1 2 3 4	5 6
5 4 3 2 1

With s1 of length n and s2 of length m, the diagonal with shift d, comparing s1[i] with s2[i + d], has length:

min(n, m, n + d, m − d)

Each of the four limits is something that runs out first:

n: it can't pair up more characters than s1 has.
m: nor more than s2 has.
n + d: for a negative d, the first |d| characters of s1 have nothing to pair with.
m − d: for a positive d, the first d characters of s2 have nothing to pair with.

The shifts run from d = −(m − 1) to n − 1, so there are n + m − 1 diagonals.

When the strings have different lengths, n and m with n ≤ m, the longest diagonals have length n, the full shorter string.
There are m − n + 1 of them, one for each place the shorter string fits inside the longer one.
With equal lengths, n = m, the formula becomes min(n + d, n − d) = n − |d|.
Without the gap between n and m there's no plateau, just the peak at d = 0, i.e., the length of the diagonal peaks at d:0.

s1: tabriz
s2: torino

d:-1 s1[i] - s2[i - 1]
tabriz
 torino
Position	1	2	3	4	5
s1		    a	b	r	i	z
s2		    t	o	r	i	n
Match?		✗	✗	✓	✓	✗

The window is a stretch of these positions, from a left end to a right end:
dlength = min(n, m, n + d, m - d)
n == m: dlength = n - |d| = 6 - 1 = 5

Step	What happens	            Window	Mismatches	Length
1	    right end takes in 1 (a/t)	1 … 1	1	        1
2	    right end takes in 2 (b/o)	1 … 2	2	        2
3	    right end takes in 3 (r/r)	1 … 3	2	        3
4	    right end takes in 4 (i/i)	1 … 4	2	        4
5	    right end takes in 5 (z/n)	1 … 5	3: too many
6	    left end drops 1 (a/t)	    2 … 5	2	        4 (briz / orin)

Shift d	Pairs compared	        Match?	Best window (at most 2 mismatches)	Length
−5	    z/t	                    ✗	    z / t	                            1
−4	    i/t z/o	                ✗✗	    iz / to	                            2
−3	    r/t i/o z/r	            ✗✗✗	    ri / to	                            2
−2	    b/t r/o i/r z/i	        ✗✗✗✗	br / to	                            2
−1	    a/t b/o r/r i/i z/n	    ✗✗✓✓✗	abri / tori	                        4
0	    t/t a/o b/r r/i i/n z/o ✓✗✗✗✗✗	tab / tor	                        3
1	    t/o a/r b/i r/n i/o	    ✗✗✗✗✗	ta / or	                            2
2	    t/r a/i b/n r/o	        ✗✗✗✗	ta / ri	                            2
3	    t/i a/n b/o	            ✗✗✗	    ta / in	                            2
4	    t/n a/o	                ✗✗	    ta / no	                            2
5	    t/o	                    ✗	    t / o	                            1

Making the window bigger can only add mismatches. Taking in more positions keeps the count the same, if they match, or increases it, if they don't. It never goes down.

s1[i] - s2[i + d]
-5:
tabriz
     torino
-4:
tabriz
    torino
0:
tabriz
torino
1:
 tabriz
torino
5:
     tabriz
torino
---
s1: uvwxyz
s2: abcd
m:6, n:4
d: [-5, 3]
s1[i] s2[i+d]:
d=-5:
 uvwxyz
      abcd
d=-4:
 uvwxyz
      abcd

d=0:
 uvwxyz
 abcd

d=3:
   uvwxyz
      abcd

s1: abcd
s2: uvwxyz
m:4, n:6
d: [-3, 5]:
s1[i] s2[i+1]:
d=-3:
 abcd
    uvwxyz

d=0:
 abcd
 uvwxyz

d=5:
      abcd
 uvwxyz
*/
template<typename T>
size_t SlidingWindow<T>::LongestCommonSubstringWithFixes(string const& str1, string const& str2, size_t k)
{
    size_t m = str1.size(), n = str2.size(), result = 0;
    for (long d = 1 - m; d < (long)n; d++) {
        size_t dlength = min<size_t>(n, min(m, min<size_t>(n + d, m - d)));
        for (size_t i = d >= 0 ? 0 : abs(d), j = i, mismatches = 0, count = 0; count < dlength&& i <= j; count++, j++) {
            if (str1[j] == str2[j + d])
                result = max(result, j - i + 1);
            else if (++mismatches > k) {
                for (;mismatches > k; i++) { // Doesn't work. Shrink from the front.
                    if (str1[i] != str2[i + d])
                        mismatches--;
                }
            }
        }
    }
    return result;
}