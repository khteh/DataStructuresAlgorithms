#include "pch.h"
#include "String.h"
void String::_Parentheses(vector<string>& result, string& str, size_t index, long left, long right)
{
    if (!left && !right)
        result.push_back(str);
    else
    {
        if (left > 0)
        {
            str[index] = '(';
            _Parentheses(result, str, index + 1, left - 1, right);
        }
        if (right > left)
        {
            str[index] = ')';
            _Parentheses(result, str, index + 1, left, right - 1);
        }
    }
}
/*
 * https://leetcode.com/problems/generate-parentheses/
 * 100%
 */
void String::Parentheses(vector<string>& result, size_t count)
{
    string str;
    str.resize(count * 2);
    _Parentheses(result, str, 0, count, count);
}
/*
 * https://leetcode.com/problems/valid-parentheses/
 * 100%
 */
bool String::IsValidParentheses(string const& s)
{
    stack<char> stk;
    map<char, char> pairs = { { '(', ')' },{ '[', ']' },{ '{', '}' } };
    for (string::const_iterator it = s.begin(); it != s.end(); it++)
    {
        if (pairs.count(*it))
            stk.push(*it);
        else if (stk.empty() || *it != pairs[stk.top()])
            return false;
        else
            stk.pop();
    }
    return stk.empty();
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
long String::LongestValidParentheses(string const& str)
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
/* https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * 100%
 */
void String::PhoneKeyLetters(string const& digits, vector<string>& result)
{
    map<char, string> letters{
        { '1', "" },
        { '2', "abc" },
        { '3', "def" },
        { '4', "ghi" },
        { '5', "jkl" },
        { '6', "mno" },
        { '7', "pqrs" },
        { '8', "tuv" },
        { '9', "wxyz" } };
    if (!digits.empty())
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
            result = move(tmp);
        }
}
// DAMP -> LAMP -> LIMP -> LIME -> LIKE
void String::WordsLadder(string const& start, string const& stop, set<string>& dictionary, vector<string>& result)
{
    queue<string> actionQ;
    set<string> visited;
    map<string, string> backtrack;
    actionQ.push(start);
    visited.emplace(start);
    Permutation<string> permutation;
    while (!actionQ.empty())
    {
        string w = actionQ.front(); // DAMP
        actionQ.pop();
        set<string> permutations;
        dictionary.erase(w);
        permutation.GetPermutations(w, dictionary, permutations);
        for (set<string>::const_iterator it = permutations.begin(); it != permutations.end(); it++)
            if (*it == stop)
            { // LIKE
                // Found our word! Now backtrack to record all the single-character change from 'start' to 'stop'
                result.push_back(*it);
                result.push_back(w);
                while (backtrack.count(w))
                {
                    w = backtrack[w];
                    result.push_back(w);
                }
                return;
            }
            else if (!visited.count(*it))
            {
                actionQ.push(*it);
                visited.insert(*it);
                backtrack[*it] = w; // Key: later; Value: earlier
            }
    }
}
/*
https://www.hackerrank.com/challenges/string-similarity/problem
100%
https://cp-algorithms.com/string/z-function.html

ababaa
babaa 0
abaa  3
baa   0
aa    1
a     1
*/
void String::Z(vector<size_t>& z, string const& str)
{
    z.resize(str.size());
    for (size_t l = 0, r = 0, i = 1; i < str.size(); i++)
    {
        if (i < r) // The current position is inside the current segment match [l, r)
            z[i] = min(r - i, z[i - l]);
        // trivial
        for (; i + z[i] < str.size() && str[z[i]] == str[i + z[i]]; z[i]++)
            ;
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
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
void String::RemoveDuplicateCharacters(string& str)
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
void String::RemoveDuplicateCharactersLexicographicalOrder(string& str)
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
    str = move(result);
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
long String::BasicCalculator(string const& s)
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
                throw invalid_argument("Invalid arithmetic sign!");
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
/* https://www.hackerrank.com/challenges/two-characters/problem
 * Return longest string with only 2 alternating characters
 * 100%
 */
size_t String::AlternateChars(string const& s)
{
    set<char> unique(s.begin(), s.end());
    if (unique.size() <= 1)
        return 0;
    else if (unique.size() == 2)
        return s.size() == 2 ? 2 : 0;
    size_t result = 0;
    ostringstream oss;
    for (char i = 'a'; i < 'z'; i++)
        for (char j = 'b'; j <= 'z'; j++)
        {
            oss.str("");
            for (size_t k = 0; k < s.size(); k++)
            {
                string str = oss.str();
                if (s[k] == i || s[k] == j)
                {
                    if (!str.empty() && str.back() == s[k])
                    {
                        oss.str("");
                        break;
                    }
                    else
                        oss << s[k];
                }
            }
            result = max(result, oss.str().size());
        }
    return result;
}
/* https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * 100%
 * "aabaab!bb"
 * *it  str  result
 * a -> a
 * a -> a    a
 * b -> ab	 a
 * a -> ba   ab
 * a -> a    ab
 * b -> ab   ab
 * ! -> ab!  ab
 * b -> !b   ab!
 * b -> b	 ab!
 */
size_t String::LengthOfLongestSubstring(string const& s)
{
    size_t result = 0;
    string str;
    for (string::const_iterator it = s.cbegin(); it != s.cend(); it++)
    {
        size_t offset = str.find(*it);
        if (offset == string::npos)
        {
            str.append(1, *it);
            if (next(it) == s.end() && str.size() > result)
                result = str.size();
        }
        else
        {
            if (str.size() > result)
                result = str.size();
            str = str.substr(offset + 1);
            str.append(1, *it);
        }
    }
    return result;
}
/*
 * https://www.hackerrank.com/challenges/time-conversion/problem
 * 100%
 */
string String::TwentyFourHourTimeConversion(string const& s)
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
https://www.hackerrank.com/challenges/bigger-is-greater/problem
100%
aPb => bPa
bPa => Pba => Pab
abP => aPb
Pab => Pba

dkhc => (swap) hkdc => (sort) hcdk

aPa => Paa
baPac => (swap) caPab => (sort) caabP

bPa => (swap) Pba => (sort) Pab
abPac => (swap) acPab => (sort) acabP
*/
string String::NextBiggerString(string& str) // XXX: Cannot use const to the string as next_permutation needs to swap the characters in the string inline.
{
    return next_permutation(str.begin(), str.end()) ? str : "no answer";
}
/*
 * https://www.hackerrank.com/challenges/morgan-and-a-string/problem
 * a: CAB, b: CAB => CABCAB
 * 100%
 */
string String::MorganAndString(string const& a, string const& b)
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
/* https://www.hackerrank.com/challenges/reduced-string/problem
 * 100%
 */
string String::SuperReducedString(string const& s)
{
    string result;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (result.empty() || s[i] != result.back())
            result.append(1, s[i]);
        else if (!result.empty())
            result.pop_back();
    }
    return result;
}
/*
 * https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
 * adapt from IsPalindrome()
 * 100%
 */
bool String::SherlockValidString(string const& s)
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
    if (countsCounts.size() == 2 && countsCounts.count(1) && countsCounts[1] == 1)
        return true;
    return max - min > 1 ? false : result;
}
// Write a code to test whether string s2 is obtained by rotating the string s1 by n places.
bool String::AreRotatedStrings(string const& s1, string const& s2, size_t n)
{
    string str(s1);
    ranges::rotate(str, str.begin() + n);
    return (str == s2);
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
string String::Cipher(size_t n, size_t k, string const& s)
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
/* Encryption scheme:
 * If s[i] is lowercase and s[i+1] is uppercase, swap them and add an asterik '*' after them
 * If s[i] is a number, replace it with 0 and place the original number at the beginning.
 * 100%
 */
string String::DecryptPassword(string const& s)
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
/*
 * https://leetcode.com/problems/decode-string/
 * All the integers in s are in the range [1, 300].
 * To prevent N^2 behaviour, never build intermediate strings. Write into a single buffer, remember where each [ started, and on ] append that segment k − 1 more times:
 *
 * 3[a]2[bc]
result: ""
stack: [(0, 3)]
result: "a" -> "aaa"

result: "aaa"
stack: [(3, 2)]
result: "aaabc" -> "aaabcbc"

3[a2[c]]
result: ""
stack: [(0, 3)]

result: "a"
stack: [(0, 3), (1, 2)]
result: "ac" -> "acc"
stack: [(0, 3)]
result: "acc" -> "accaccacc"

 * 100%
 */
string String::DecodeString(string const& str)
{
    string result;                      // Single output buffer
    vector<pair<size_t, size_t>> stack; // (start index in result, k)
    size_t k = 0;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            k = k * 10 + (c - '0'); // Build the multiplier k
        else if (c == '[')
        {
            stack.emplace_back(result.size(), k); // Remember where this segment starts and its multiplier
            k = 0;                                // Reset k for the next number
        }
        else if (c == ']')
        {
            auto [start, repeat] = stack.back();
            stack.pop_back();
            if (repeat > 1)
            {                                          // k == 1: nothing to do, no copy
                string segment = result.substr(start); // Get the segment to repeat. costs |seg| <= what we append next
                if (!segment.empty())
                {
                    result.reserve(result.size() + segment.size() * (repeat - 1)); // Reserve enough space to avoid multiple reallocations
                    for (size_t i = 1; i < repeat; i++)
                        result += segment; // Append the segment k-1 more times
                }
            }
        }
        else
            result += c; // Regular character, just append to result
    }
    return result;
}
/*
 * https://leetcode.com/problems/zigzag-conversion/
 * 100%
rows: 2, incr: 2, 2
P Y A I H R N
A P L S I I G

rows: 3, incr: 4, 2, 4, 2, 4
P   A   H   N
A P L S I I G
Y   I   R

rows: 4, incr: 6, 4, 2, 6, 4, 2, 6
P     I    N
A   L S  I G
Y A   H R
P     I

rows: 5, incr: 8, 6, 4, 2, 8, 6, 4, 2
P       H
A     S   I
Y   I       R
P L            I     G
A                 N
 */
string String::ZigZagConvert(string const& s, size_t numRows)
{
    bool direction = false;
    vector<string> str(numRows);
    long row = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        str[row].append(1, s[i]);
        if (!direction)
            row++;
        else
            row--;
        if (row == numRows)
        {
            row -= min<size_t>(numRows, 2);
            direction = !direction;
        }
        else if (row < 0)
        {
            row += min<size_t>(numRows, 2);
            direction = !direction;
        }
    }
    ostringstream oss;
    for (size_t i = 0; i < numRows; i++)
        oss << str[i];
    return oss.str();
}
vector<string> String::_WordBreakDFS(string const& s, set<string> const& words, map<string, vector<string>>& strings)
{
    vector<string> result;
    if (s.empty())
        return vector<string>{""};
    else if (strings.find(s) != strings.end())
        return strings[s];
    for (set<string>::iterator it = words.begin(); it != words.end(); it++)
    {
        size_t found = s.find(*it);
        if (!found)
        {
            vector<string> tmp = _WordBreakDFS(s.substr(it->size()), words, strings);
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
vector<string> String::WordBreakDFS(string const& s, set<string> const& words)
{
    map<string, vector<string>> strings;
    return _WordBreakDFS(s, words, strings);
}
/*
 * https://www.hackerrank.com/challenges/happy-ladybugs/problem
 * 100%
 */
bool String::HappyLadyBugs(string const& str)
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
    if (!counts.count('_'))
    {
        set<char> groups;
        char current = '\0';
        for (string::const_iterator it = str.begin(); it != str.end(); it++)
        {
            if (current == '\0' || (*it != current && !groups.count(*it)))
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
/* https://leetcode.com/problems/bulls-and-cows/
You are playing the Bulls and Cows game with your friend.

You write down a secret number and ask your friend to guess what the number is. When your friend makes a guess, you provide a hint with the following info:

The number of "bulls", which are digits in the guess that are in the correct position.
The number of "cows", which are digits in the guess that are in your secret number but are located in the wrong position. Specifically, the non-bull digits in the guess that could be rearranged such that they become bulls.
Given the secret number secret and your friend's guess guess, return the hint for your friend's guess.

The hint should be formatted as "xAyB", where x is the number of bulls and y is the number of cows. Note that both secret and guess may contain duplicate digits.
 * 100%
 */
string String::GetHint(string const& secret, string const& guess)
{
    map<char, long> counts;
    size_t bulls = 0, cows = 0;
    for (size_t i = 0; i < secret.size(); i++)
        counts[secret[i]]++;
    for (size_t i = 0; i < secret.size(); i++)
        if (secret[i] == guess[i])
        {
            bulls++;
            if (--counts[secret[i]] < 0 && cows > 0)
                cows--;
        }
        else if (counts.count(guess[i]) && counts[guess[i]] > 0)
        {
            counts[guess[i]]--;
            cows++;
        }
    ostringstream oss;
    oss << bulls << "A" << cows << "B";
    return oss.str();
}
/*
 * https://www.hackerrank.com/challenges/bear-and-steady-gene/problem
 * 100%
 * Find the length of the smallest possible substring that can be replaced to make a steady gene
 * A sliding window needs monotonicity: if a window is fixable, so is a smaller one inside it.
 * Sliding window implementation
 */
size_t String::SteadyGene(string const& gene)
{
    size_t count = numeric_limits<size_t>::max();
    if (gene.size() % 4) // gene.size() should be divisable by 4
        return count;
    size_t balancedCount = gene.size() / 4;
    map<char, size_t> genes;
    for (string::const_iterator it = gene.begin(); it != gene.end(); it++)
        genes[*it]++;
    /*
     * ACGTCCGT : length = 8, N = 2, balancedCount = 2
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
     * i: 0, j: 2 [ACG]TCCGT => A[AG]TCCGT
     * 'A': 1 -> count: 2 ("CG"), i:1, j:2
     * 'G': 2
     * 'C': 2
     * 'T': 2
     *
     * i: 1, j: 2 A[CG]TCCGT => AC[G]TCCGT
     * 'A': 1
     * 'G': 2
     * 'C': 3 -> count: 1 ("G"), i:2 j:2
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
     * 'G': 2 -> count: 3 ("TCC"), i:3 j:5
     * 'C': 2
     * 'T': 1
     *
     * i: 3, j: 5 ACG[TCC]GT
     * 'A': 1
     * 'G': 2
     * 'C': 2
     * 'T': 2 -> count: 2 ("CC"), i:4, j:5
     *
     * i: 4, j: 5 ACGT[CC]GT
     * 'A': 1
     * 'G': 2
     * 'C': 3 -> count: 1 ("C"), i:5, j:5
     * 'T': 2
     *
     * i: 5, j: 5 ACGTC[C]GT
     * 'A': 1
     * 'G': 2
     * 'C': 2 -> j:6, i:5
     * 'T': 2
     *
     * i: 5, j: 6 ACGTC[CG]T => ACGTCAGT
     * 'A': 1
     * 'G': 2
     * 'C': 3 -> count: 1 ("C"), i:6 j:6
     * 'T': 2
     *
     * i: 6, j: 6 ACGTCC[G]T
     * 'A': 1
     * 'G': 1 -> j:7, i:6
     * 'C': 3
     * 'T': 2
     *
     * i: 6, j: 7 ACGTCC[GT]
     * 'A': 1
     * 'G': 1
     * 'C': 3
     * 'T': 1, j:8, i:6
     */
    for (size_t i = 0, j = 0; i < gene.size() && j < gene.size();)
        if (genes['A'] <= balancedCount && genes['C'] <= balancedCount && genes['G'] <= balancedCount && genes['T'] <= balancedCount)
        {
            count = min(count, j - i);
            genes[gene[i++]]++;
        }
        else
            genes[gene[j++]]--;
    return count;
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
size_t String::LengthOfLongestUniqueSubstring(string const& s)
{
    size_t maxLength = 0;
    set<char> chars;
    string str;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (!chars.count(s[i]))
        {
            str.append(1, s[i]);
            chars.emplace(s[i]);
        }
        else
        {
            if (str.size() > maxLength)
                maxLength = str.size();
            chars.clear();
            size_t offset = str.find_first_of(s[i]) + 1;
            if (offset > str.size()) // s[i] is the last character in str
                str.clear();
            else
            { // s[i] in the middle of str
                chars.insert(str.begin() + offset, str.end());
                str = str.substr(offset);
            }
            chars.insert(s[i]);
            str.append(1, s[i]);
        }
    }
    return max(str.size(), maxLength);
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
size_t String::LongestStringWithCharacterReplacement(string const& s, size_t k)
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
 * https://leetcode.com/problems/longest-common-prefix/
 * 100%
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 *
 * "flower","flow","flight" -> "fl"
 * "dog","racecar","car" -> ""
 */
string String::LongestCommonPrefix(vector<string> const& data)
{
    string result;
    if (data.size() == 1)
        return data[0];
    // Use std::max_element with a lambda function to compare strings by size
    vector<string>::const_iterator it = ranges::max_element(data, [](const string& a, const string& b)
        { return a.size() < b.size(); });
    size_t length = it != data.end() ? it->size() : 0;
    bool match = true;
    for (size_t i = 0; i < length && match; i++)
    {
        for (size_t j = 1; j < data.size() && match; j++)
            match = data[j][i] == data[0][i];
        if (match)
            result.append(1, data[0][i]);
    }
    return result;
}
/*
Given a string S and a set of words D, find the longest word in D that is a subsequence of S.

Word W is a subsequence of S if some number of characters, possibly zero, can be deleted from S to form W, without reordering the remaining characters.

Note: D can appear in any format (list, hash table, prefix tree, etc.

For example, given the input of S = "abppplee" and D = {"able", "ale", "apple", "bale", "kangaroo"} the correct output would be "apple"

The words "able" and "ale" are both subsequences of S, but they are shorter than "apple".
The word "bale" is not a subsequence of S because even though S has all the right letters, they are not in the right order.
The word "kangaroo" is the longest word in D, but it isn't a subsequence of S.

'a':
a -> [("able", 1), ("ale", 1), ("apple", 1)]; transfer ("able", 1) to map['b'], ("ale", 1) to map['l'], ("apple", 1) to map['p']
b -> [("bale", 0)]
k -> [("kangaroo", 0)]

b -> [("bale", 0), ("able", 1)]
k -> [("kangaroo", 0)]
l -> [("ale", 1)]
p -> [("apple", 1)]

'b':
b -> [("bale", 1), ("able", 2)]; transfer ("bale", 1) to map['a'], ("able", 2) to map['l']
k -> [("kangaroo", 0)]
l -> [("ale", 1)]
p -> [("apple", 1)]

a -> [("bale", 1)]
k -> [("kangaroo", 0)]
l -> [("ale", 1), ("able", 2)]
p -> [("apple", 1)]

'p':
a -> [("bale", 1)]
k -> [("kangaroo", 0)]
l -> [("ale", 1), ("able", 2)]
p -> [("apple", 2)]: transfer ("apple", 2) to map['p']

'p':
a -> [("bale", 1)]
k -> [("kangaroo", 0)]
l -> [("ale", 1), ("able", 2)]
p -> [("apple", 3)]: transfer ("apple", 3) to map['l']

a -> [("bale", 1)]
k -> [("kangaroo", 0)]
l -> [("ale", 1), ("able", 2), ("apple", 3)]

'p':
a -> [("bale", 1)]
k -> [("kangaroo", 0)]
l -> [("ale", 1), ("able", 2), ("apple", 3)]

'l':
a -> [("bale", 1)]
k -> [("kangaroo", 0)]
l -> [("ale", 2), ("able", 3), ("apple", 4)]: transfer ("ale", 2) to map['e'], ("able", 3) to map['e'], ("apple", 4) to map['e']

a -> [("bale", 1)]
k -> [("kangaroo", 0)]
e -> [("ale", 2), ("able", 3), ("apple", 4)]: transfer ("ale", 2) to map['e'], ("able", 3) to map['e'], ("apple", 4) to map['e']

'e':
a -> [("bale", 1)]
k -> [("kangaroo", 0)]
e -> [("ale", 3), ("able", 4), ("apple", 5)]
result: ["apple", "able", "ale"]

'e':
a -> [("bale", 1)]
k -> [("kangaroo", 0)]
result: ["apple", "able", "ale"]
*/
string String::LongestMatchingWordWithDeletion(string const& s, set<string> const& words)
{
    vector<longestmatchingwordwithdeletion_state_t> tuples; // index: The number refers to the number of characters in w that have already been found in S.
    map<char, vector<longestmatchingwordwithdeletion_state_t>> groups;
    set<string, greater<string>> result;
    for (set<string>::const_iterator it = words.begin(); it != words.end(); it++)
        tuples.push_back(longestmatchingwordwithdeletion_state_t(0, *it));
    for (vector<longestmatchingwordwithdeletion_state_t>::iterator it = tuples.begin(); it != tuples.end(); it++)
    {
        /* group words by their first character
            a -> [("able", 0), ("ale", 0), ("apple", 0)]
            b -> [("bale", 0)]
            k -> [("kangaroo", 0)]
        */
        groups[it->word[0]].push_back(*it);
    }
    for (char c : s)
    {
        /*
        Scan S one character (c) at a time. For each tuple t in map[c], increment t.i by 1 and transfer t to map[t.w[t.i]].
        */
        if (groups.count(c))
        {
            vector<longestmatchingwordwithdeletion_state_t> group = groups[c];
            groups.erase(c);
            for (vector<longestmatchingwordwithdeletion_state_t>::iterator it = group.begin(); it != group.end(); it++)
            {
                it->index++;
                if (it->index < it->word.size())
                    groups[it->word[it->index]].push_back(*it);
                else
                    result.insert(it->word);
            }
        }
    }
    return *result.begin();
}
/* https://www.hackerrank.com/challenges/weighted-uniform-string/problem
 * 100%
 */
vector<bool> String::WeightedUniformStrings(string const& s, vector<size_t> const& queries)
{
    set<size_t> weights;
    vector<bool> result;
    char c = ' ';
    for (size_t i = 0, weight = 0, count = 0; i < s.size(); i++)
    {
        if (c != s[i])
        {
            weight = s[i] - 'a' + 1;
            count = 1;
            weights.emplace(weight);
            c = s[i];
        }
        else if (s[i] == c)
            weights.emplace(weight * ++count);
    }
    for (vector<size_t>::const_iterator it = queries.begin(); it != queries.end(); it++)
        result.push_back(weights.count(*it));
    return result;
}
/* https://leetcode.com/problems/maximum-product-of-word-lengths/
 * 100%
 * Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters.
 * If no such two words exist, return 0.
Example 1:
Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".

Example 2:
Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4
Explanation: The two words can be "ab", "cd".

Example 3:
Input: words = ["a","aa","aaa","aaaa"]
Output: 0
Explanation: No such pair of words.
 */
size_t String::MaxProductOfNonOverlappingWordLengths(vector<string> const& words)
{
    size_t result = 0;
    map<size_t, size_t> patterns;
    for (vector<string>::const_iterator it = words.begin(); it != words.end(); it++)
    {
        int pattern = 0;
        for (size_t c = 0; c < it->size(); c++)
            pattern |= 1 << ((*it)[c] - 'a');
        patterns[pattern] = max(patterns[pattern], it->size());
        for (map<size_t, size_t>::iterator it1 = patterns.begin(); it1 != patterns.end(); it1++)
            if (!(it1->first & pattern))
                result = max(result, it1->second * it->size());
    }
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
string String::BuildLargestNumber(vector<size_t> const& a)
{
    bool nonZero = false;
    multiset<string, BuildLargestNumber_comparator_t> data;
    for (vector<size_t>::const_iterator it = a.begin(); it != a.end(); it++)
    {
        if (*it > 0)
            nonZero = true;
        data.insert(to_string(*it));
    }
    ostringstream oss;
    for (multiset<string, BuildLargestNumber_comparator_t>::iterator it = data.begin(); it != data.end(); it++)
        oss << *it;
    return oss.str().empty() || !nonZero ? "0" : oss.str();
}
/* https://app.codility.com/programmers/task/brackets_rotation/
 * Divide and conquer on the minimum prefix balance.
The key fact: the cost of one substring
Match brackets greedily from left to right, as in the usual stack check. Whatever stays unmatched always looks like )))…(((: a unmatched ) followed by b unmatched (. The fewest flips that make the substring valid is then:
⌈a/2⌉ + ⌈b/2⌉ (and the length must be even)
You flip half of the )s to ( and half of the (s to ). For example, "))))" needs 2 flips, giving "()()".
If a is odd, b is odd too, because the length is even, and the middle ")(" costs 2.
So the task becomes: find the longest even-length substring with ⌈a/2⌉ + ⌈b/2⌉ ≤ K.

The divide and conquer works on prefix balances, P[x] = (number of () − (number of )) in the first x brackets.
For a substring from i to j, with m the minimum of P between them, a = P[i] − m and b = P[j] − m.

1. Take t, the position of the minimum P in the current range. Every substring passing through t has m = P[t].
2. For each index on the smaller side of t, the formula gives the largest P allowed at the other end. A sparse table then finds the farthest index on the other side, of the same parity, with P that small. Each lookup is a binary search, O(log N).
3. Recurse on the two sides.

Iterating the smaller side keeps the total to O(N log N) lookups, the same reasoning as “small-to-large” merging. That’s where O(N log² N) comes from.

Think of P as a path going up and down. For the substring s[i..j), look at the part of the path from position i to position j:

m is the lowest point on that part of the path (between i and j).
a = P[i] − m is how far the path drops below where it started. Each drop below the starting level is a ) with no ( before it to match: an unmatched ).
b = P[j] − m is how far the path ends above its lowest point. Each step up after the lowest point that never comes back down is a ( with no ) after it: an unmatched (.

Example: s[0..6) = )(())(. The path is P[0..6] = 0, −1, 0, 1, 0, −1, 0.

It starts at 0, the lowest point is m = −1, and it ends at 0.
a = 0 − (−1) = 1: the first ) has nothing to match.
b = 0 − (−1) = 1: the last ( has nothing to match.
Cost = ⌈1/2⌉ + ⌈1/2⌉ = 2 flips, giving ((())). With K = 1, that’s too many.

A second example: s[1..5) = (()). The path is −1, 0, 1, 0, −1, so m = −1, and a = 0, b = 0. It’s already valid and costs 0.

The divide and conquer keeps asking two questions about the prefix balances P, and the sparse table answers both quickly:

1. Where is the lowest point between l and r? This picks the split point t for each range. The table answers it in O(1).
2. What’s the farthest position on one side, of a given parity, with P ≤ some bound? This finds the end of the longest affordable substring.
   The sparse table answers it in O(log N), by binary searching with question 1.

The divide and conquer, step by step:

Point 1: split at the lowest point of the whole range. Over all positions 0 … 7, the lowest P is −1. It first occurs at t = 1. Every substring s[i..j) that contains position t (i ≤ 1 ≤ j) passes through that lowest point, so its m is −1.
That means its m is known without any searching. Substrings that don’t contain t lie entirely to the left of t or entirely to the right, and point 3 deals with those.

Point 2: for each start, find the farthest end that’s affordable. Take i = 1 (on the left of t, or at t itself):

a = P[1] − m = −1 − (−1) = 0, so the start costs ⌈0/2⌉ = 0 flips.
That leaves K − 0 = 1 flip for the b side, so b ≤ 2, since ⌈2/2⌉ = 1.
b = P[j] − m, so P[j] ≤ m + 2 = 1. That’s the “allowed P at the other end”.
The length j − i must be even. So j must have the same parity as i: both odd here.
On the right of t, the farthest odd position with P ≤ 1 is j = 7 (P[7] = 1). So s[1..7) = (())((, length 6. Its b is 2, costing 1 flip ✓.
Now take i = 0: a = 0 − (−1) = 1, which costs ⌈1/2⌉ = 1 flip. That uses the whole budget, leaving 0 flips for the b side. Since a is odd, b is also odd (the length is even), so b ≥ 1 and costs at least 1 more flip. That’s impossible, so no j works for i = 0.
You always want the farthest valid end, because we’re looking for the longest substring. Finding it is where the sparse table comes in. It’s a lookup structure that answers “what’s the last position in this range with this parity and P ≤ some value?” with a binary search, instead of scanning every position.
Which side to loop over. Here the left side of t has 2 positions (0, 1) and the right side has 7 (1 … 7). Looping over the smaller side and doing a lookup on the bigger side keeps the total work down. That choice is what makes it O(N log² N) instead of O(N²). The result is the same whichever side you loop over.

Point 3: repeat on each side. Substrings that don’t contain t = 1 lie entirely within positions 0 … 0, which is too short, or entirely within positions 2 … 7. So the same steps run on 2 … 7: its lowest point is t = 5 (P = −1), and the search finds )) and (( (length 2 each). It then splits again, into 2 … 4 and 6 … 7, and so on, until the ranges are too short to hold a substring.

The full trace finds 6 as the longest, which matches the brute force:

Range of positions	Lowest point t	Best substring found through t
0 … 7	            1 (P = −1)	    s[1..7) = (())((, length 6
2 … 7	            5 (P = −1)	    )) or ((, length 2
2 … 4	            2 (P = 0)	    (), length 2
6 … 7, 3 … 4	    6, 4	        nothing longer

Every substring is checked exactly once: in the first range that contains it whose split point t falls inside it. At that point t is its lowest point, so its m is P[t].

=== "((()", k=0 ===
Here is the trace for s = ((() with K = 0. The expected answer is 2, from the () at the end.

Step 0: the prefix balances P

Count +1 for ( and −1 for ), with positions between the brackets:

position x:   0    1    2    3    4
bracket:        (    (    (    )
P[x]:         0    1    2    3    2
The rules each step applies

For a start i on the left of the lowest point t and an end j on the right:

Unmatched at the start, a = P[i] − m. It costs ⌈a/2⌉ flips.
Flips left for the other end: K − ⌈a/2⌉. If that’s negative, skip this start.
Allowed P at the other end: P[j] ≤ m + 2 × (flips left) − (1 if a is odd). With K = 0 and a = 0, that’s simply P[j] ≤ m: the other end can’t have any unmatched (.
Same parity: j − i must be even, so i and j must both be even or both be odd.
Farthest end: of the positions that qualify, take the farthest one, since we want the longest substring.
The trace

Range 0 … 4. P = 0, 1, 2, 3, 2. The lowest point is t = 0 (P = 0), so m = 0.

The left side of t is empty (t is at the left edge), and the right side has 4 positions. So we loop over the left side, which is just i = 0.
i = 0: a = P[0] − 0 = 0, costing 0 flips. 0 flips are left, so the allowed P at the end is ≤ 0. On the right of t, the even positions are 0, 2 and 4, with P = 0, 2, 2. Only position 0 has P ≤ 0, so j = 0: the empty substring, length 0.
This is why the whole string can’t count. Any substring starting at 0 ends at P = 2 or more, which means at least 2 unmatched (, and that costs at least 1 flip.
Split into ranges 0 … −1 (empty) and 1 … 4.

Range 1 … 4. P = 1, 2, 3, 2. Lowest point t = 1 (P = 1), m = 1. The left side is empty again.

i = 1: a = 0, allowed P ≤ 1. The odd positions on the right are 1 and 3, with P = 1 and 3. Only position 1 qualifies, so the substring is empty again, length 0.
Split into 1 … 0 (empty) and 2 … 4.

Range 2 … 4. P = 2, 3, 2. Lowest point t = 2 (P = 2), m = 2. The first minimum is used, so t is 2, not 4.

i = 2: a = 0, allowed P ≤ 2. The even positions on the right are 2 and 4, with P = 2 and 2. Both qualify, and the farthest is j = 4. So s[2..4) = (), length 2, costing 0 flips ✓.
Split into 2 … 1 (empty) and 3 … 4.

Range 3 … 4. P = 3, 2. Lowest point t = 4 (P = 2), m = 2. Now the left side has 1 position and the right side none, so we loop over the right side, which is j = 4.

j = 4: b = P[4] − 2 = 0, allowed P at the start ≤ 2. On the left of t, the even positions are just 4 (position 3 is odd), with P = 2. So i = 4: the empty substring, length 0.
Split into 3 … 3 and 5 … 4, both too short.

Every range left is too short, so the answer is 2 ✓

What the trace shows
Each range finds the longest substring through its lowest point. The () was only found once the ranges reached 2 … 4. Before that, every substring started at the range’s lowest point and ended higher up, which K = 0 can’t afford.
On an input like this, the lowest point keeps landing at the left edge, so each range is only one position shorter than the one before.
That’s the shape that made your recursive version go N levels deep. The fixed version keeps its ranges in a vector instead, and finds each t in O(1) instead of scanning the range.

The end side’s unmatched brackets are always (. The start side’s are always ).
Why each side has its own kind of bracket. After greedy matching, whatever is left over always looks like )))(((. The leftover ) come first and the leftover ( come last:

A ')' can only be left unmatched if no '(' before it is free. So unmatched ) sit towards the start of the substring. There are a = P[i] − m of them: the path drops a steps below its starting level.
A '(' can only be left unmatched if no' ') after it closes it. So unmatched ( sit towards the end of the substring. There are b = P[j] − m of them: the path finishes b steps above its lowest point.
So the start determines 'a', the number of unmatched ')', and the end determines 'b', the number of unmatched '('.
From the trace, with i = 0 (m = 0) in ((():

End j	Substring s[0..j)	P[j]	b = P[j] − m	Unmatched	Flips
2	((	2	2	((	1 (→ ())
4	((()	2	2	the first two (	1 (→ ()())
0	(empty)	0	0	none	0

Only the empty substring has P[j] ≤ 0, so no non-empty substring starting at 0 is affordable with K = 0. When the loop runs over the end side instead, as in range 3 … 4 of the trace, the roles swap.
The fixed end’s P[j] − m is the b, and the condition P[i] ≤ … limits a, the start’s unmatched ).
=== "((()", k=0 ===

Within one range of the divide and conquer, the lowest point m = P[t] is already known. So:

a = P[i] − m depends only on the start i. Pick a start, and a is settled, whichever end you pair it with.
b = P[j] − m depends only on the end j. Pick an end, and b is settled, whichever start you pair it with.

That separation is what makes the search work:

Pick a start i. Its a, and so its cost ⌈a/2⌉, is known straight away.
The flips left over decide how large b can be, which is the “allowed P at the other end”.
Search the other side for the farthest end whose b is within that limit.

There is one subtlety. In general, m depends on both ends, because it’s the lowest point between them. a depends only on i because each range only considers substrings that pass through t.
That’s why the trace splits at the lowest point: it turns m into a known constant.

SparseTable<T>, a sparse table, finds 't' in O(1). There are log₂ N rows of N entries, so building the table takes O(N log N) time and memory, once.
rightmost / leftmost binary-search a per-parity sparse table for the farthest end, in O(log N).
A ranges stack replaces the recursion.

Why this gives O(N log² N)

The divide and conquer does O(N log N) “farthest end” lookups in total, and each one is a binary search of O(log N) steps, each costing O(1).
Finding each range’s lowest point adds only O(1) per range, so the total is O(N log² N). In the generalised SparseTable<T, Compare>, all of this is unchanged.
“Lowest” just becomes “best according to Compare”, so a greater<T> table does the same with maximums.

The factor N is the number of positions. The previous step bounded how many times one position is looped over, about log₂ N. To get the total, you add that up over all the positions:

total lookups = (number of positions) × (most times each one is looped over) ≤ (N + 1) × log₂(N + 1)
 */
size_t String::LongestValidParenthesesWithFixes(string const& str, size_t k)
{
    if (str.size() < 2)
        return 0;
    if (k >= str.size() - str.size() % 2)
        return str.size() - str.size() % 2;
    vector<long> P;
    P.push_back(0);
    for (char c : str)
        P.push_back(c == ')' ? P.back() - 1 : P.back() + 1);
    // The substring s[i..j) has length j - i, so i and j must have the same parity. P only at even / odd positions, LONG_MAX elsewhere:
    vector<long> evenP(P.size(), numeric_limits<long>::max()), oddP(P.size(), numeric_limits<long>::max());
    for (size_t x = 0; x < P.size(); x++)
        (x % 2 ? oddP : evenP)[x] = P[x];
    /*
    Same parity: the evenP / oddP tables

    A substring s[i..j) needs j − i even, so i and j need the same parity. The code builds a second and third table over copies of P with the positions of the other parity set to ∞ (LONG_MAX):

    oddP:                inf   -1  inf    1  inf   -1  inf    1

    A position holding ∞ is never the minimum and never ≤ any bound. So every lookup in oddP effectively only sees the odd positions.
    */
    SparseTable<long> lowest(P), sameParity[2] = { SparseTable(evenP), SparseTable(oddP) };
    /*
    * The “allowed P at the other end”, or LONG_MIN if this end alone costs more than k flips.
    * This end has `unmatched` brackets, costing ⌈unmatched / 2⌉. The other end has the remaining flips: at most 2 * remainingFlips unmatched,
    * and if `unmatched` is odd, the other end's is odd too, because the length is even: at most 2 * remainingFlips - 1.
    * The other end's unmatched count is P - m, so P <= m + 2 * remainingFlips - (unmatched odd).
    */
    auto allowed = [k](long m, long unmatched) {
        long remainingFlips = (long)k - (unmatched / 2 + unmatched % 2);
        return remainingFlips < 0 ? numeric_limits<long>::min() : m + 2 * remainingFlips - unmatched % 2;
        };
    size_t result = 0;
    vector<pair<long, long>> ranges{ { 0, (long)P.size() - 1 } }; // A stack of ranges instead of recursion, which overflowed the stack on long inputs
    while (!ranges.empty()) {
        auto [start, end] = ranges.back();
        ranges.pop_back();
        if (start >= end)
            continue;
        long t = lowest.Index(start, end), m = P[t]; // Every substring s[i..j) with i <= t <= j has its lowest point at t
        // Loop over the smaller side
        if (t - start <= end - t)
            for (long i = start; i <= t; i++) {
                long allowedP = allowed(m, P[i] - m); // a = P[i] - m
                if (allowedP == numeric_limits<long>::min())
                    continue;
                long j = sameParity[i % 2].RightMost(t, end, allowedP); // The farthest j on the right of t
                if (j >= 0)
                    result = max<size_t>(result, j - i);
            }
        else
            for (long j = t; j <= end; j++) {
                long allowedP = allowed(m, P[j] - m); // b = P[j] - m
                if (allowedP == numeric_limits<long>::min())
                    continue;
                long i = sameParity[j % 2].LeftMost(start, t, allowedP); // The farthest i on the left of t
                if (i >= 0)
                    result = max<size_t>(result, j - i);
            }
        // Substrings that don't contain t lie entirely on one side of it
        ranges.emplace_back(start, t - 1);
        ranges.emplace_back(t + 1, end);
    }
    return result;
}