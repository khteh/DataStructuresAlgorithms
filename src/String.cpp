#include "pch.h"
#include "String.h"
void String::_Parentheses(vector<string> &result, string &str, size_t index, long left, long right)
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
void String::Parentheses(vector<string> &result, size_t count)
{
    string str;
    str.resize(count * 2);
    _Parentheses(result, str, 0, count, count);
}
/*
 * https://leetcode.com/problems/valid-parentheses/
 * 100%
 */
bool String::IsValidParentheses(string const &s)
{
    stack<char> stk;
    map<char, char> pairs = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
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
long String::LongestValidParentheses(string const &str)
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
void String::PhoneKeyLetters(string const &digits, vector<string> &result)
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
// DAMP -> LAMP -> LIMP -> LIME -> LIKE
void String::WordsLadder(string const &start, string const &stop, set<string> &dictionary, vector<string> &result)
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
        {
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
void String::Z(vector<size_t> &z, string const &str)
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
void String::RemoveDuplicateCharacters(string &str)
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
void String::RemoveDuplicateCharactersLexicographicalOrder(string &str)
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
long String::BasicCalculator(string const &s)
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
size_t String::AlternateChars(string const &s)
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
size_t String::LengthOfLongestSubstring(string const &s)
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
string String::TwentyFourHourTimeConversion(string const &s)
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
string String::NextBiggerString(string &str) // XXX: Cannot use const to the string as next_permutation needs to swap the characters in the string inline.
{
    return next_permutation(str.begin(), str.end()) ? str : "no answer";
}
/*
 * https://www.hackerrank.com/challenges/morgan-and-a-string/problem
 * a: CAB, b: CAB => CABCAB
 * 100%
 */
string String::MorganAndString(string const &a, string const &b)
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
string String::SuperReducedString(string const &s)
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
bool String::SherlockValidString(string const &s)
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
bool String::AreRotatedStrings(string const &s1, string const &s2, size_t n)
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
string String::Cipher(size_t n, size_t k, string const &s)
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
string String::DecryptPassword(string const &s)
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
string String::DecodeString(string const &str)
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
string String::ZigZagConvert(string const &s, size_t numRows)
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
vector<string> String::_WordBreakDFS(string const &s, set<string> const &words, map<string, vector<string>> &strings)
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
vector<string> String::WordBreakDFS(string const &s, set<string> const &words)
{
    map<string, vector<string>> strings;
    return _WordBreakDFS(s, words, strings);
}
/*
 * https://www.hackerrank.com/challenges/happy-ladybugs/problem
 * 100%
 */
bool String::HappyLadyBugs(string const &str)
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
string String::GetHint(string const &secret, string const &guess)
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
 * find the length of the smallest possible substring that can be replaced to make a steady gene
 * Sliding window implementation
 */
size_t String::SteadyGene(string const &gene)
{
    size_t count = numeric_limits<size_t>::max();
    if (gene.size() % 4) // gene.size() should be divisable by 4
        return count;
    size_t balancedCount = gene.size() / 4;
    map<char, size_t> genes;
    for (string::const_iterator it = gene.begin(); it != gene.end(); it++)
        genes[*it]++;
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
     * 'C': 2 -> j:6, i:5
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
size_t String::LengthOfLongestUniqueSubstring(string const &s)
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
size_t String::LongestStringWithCharacterReplacement(string const &s, size_t k)
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
string String::LongestCommonPrefix(vector<string> const &data)
{
    string result;
    if (data.size() == 1)
        return data[0];
    // Use std::max_element with a lambda function to compare strings by size
    vector<string>::const_iterator it = ranges::max_element(data, [](const string &a, const string &b)
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
string String::LongestMatchingWordWithDeletion(string const &s, set<string> const &words)
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
vector<bool> String::WeightedUniformStrings(string const &s, vector<size_t> const &queries)
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
size_t String::MaxProductOfNonOverlappingWordLengths(vector<string> const &words)
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
string String::BuildLargestNumber(vector<size_t> const &a)
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
