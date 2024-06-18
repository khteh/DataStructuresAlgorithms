#include "Palindrome.h"
/*
 * This is loose palindrome detection. Returns true for any string which can be a palindrome by rearranging the characters.
 * 1 2 3 2 1 Odd count; #odd = 1
 * XXX This will return true but NOT palindrome: "13221"
 */
bool Palindrome::IsPalindrome(string const &s)
{
    size_t odd = 0;
    size_t length = s.length();
    map<char, size_t> counts;
    for (string::const_iterator it = s.begin(); it != s.end(); it++)
        counts[*it]++;
    for (map<char, size_t>::const_iterator it = counts.begin(); it != counts.end(); it++)
        if (it->second % 2 && (!(length % 2) || ++odd > 1))
            return false;
    return true;
}
/*
 * This is loose palindrome detection. Returns true for any string which can be a palindrome by rearranging the characters.
 * 12321 => 11223
 *   count: 12121 : true
 * 123421 => 112234
 *   count:  12121 : Even length -> false
 * 12121 => 11122
 *   count: 12312 : true
 * 121212 => 111222
 *   count:  123 : Even length -> false
 */
bool Palindrome::IsPalindrome1(string const &s)
{
    size_t count = 1, odd = 0;
    size_t length = s.length();
    string s1(s);
    ranges::sort(s1);
    for (size_t i = 1; i < length; i++)
    {
        if (s1[i] == s1[i - 1])
            count++;
        else
        {
            if (count % 2 && (!(length % 2) || ++odd > 1))
                return false;
            count = 1;
        }
    }
    return true;
}
// https://en.wikipedia.org/wiki/Palindrome
bool Palindrome::IsPalindrome2(string const &s)
{
    for (size_t i = 0, j = s.size() - 1; i <= j;)
    {
        if (!isalnum(s[i]))
        {
            i++;
            continue;
        }
        if (!isalnum(s[j]))
        {
            j--;
            continue;
        }
        if (tolower(s[i]) != tolower(s[j]))
            return false;
        i++;
        j--;
    }
    return true;
}
/*
 * "" -> ""
 * "a" -> ""
 * "ab" -> "a"
 * "aa" -> "aa"
 */
string Palindrome::FindBiggestPalindromeSubstring(string const &s)
{
    string tmp, palindrome;
    for (int i = 1; i < s.size() - 1; i++)
    {
        if (s[i] == s[i + 1])
        { // Even palindrome: abba
            for (int j = i, k = i + 1; j >= 0 && k < s.size(); j--, k++)
            {
                if (s[j] == s[k])
                {
                    tmp = s.substr(j, k - j + 1);
                    if (tmp.size() > palindrome.size())
                        palindrome = tmp;
                }
                else
                    break;
            }
        }
        else if (s[i - 1] == s[i + 1])
        { // Odd palindrome: aba
            for (int j = i - 1, k = i + 1; j >= 0 && k < s.size(); j--, k++)
            {
                if (s[j] == s[k])
                {
                    tmp = s.substr(j, k - j + 1);
                    if (tmp.size() > palindrome.size())
                        palindrome = tmp;
                }
                else
                    break;
            }
        }
    }
    return palindrome;
}
/*
"aa"
center: [0,3]
center:0 left: 0, right:0
    p: ""
center:1 left: 0, right: 1
    p: "aa"
center:2 left: 1, right: 1
    p: ""
center:3 left: 1, right: 2
    p: ""
---
"aba"
center: [0,5]
center:0 left:0, right:0
    p: ""
center:1 left:0, right:1
    p: ""
center:2 left:1, right:1
    p: ""
    p: "aba" left:0, right:2
center:3 left:1, right:2
    p: ""
center:4 left:2, right:2
    p: ""
center:5 left:2, right:3
    p: ""
*/
void Palindrome::FindPalindromeSubstrings(string const &s, set<string> &result)
{
    size_t length = s.size();
    for (size_t center = 0; center < 2 * length; center++)
    {
        long left = center / 2;
        long right = left + center % 2;
        string palindrome; // Keep the biggest palindrome around the current 'center'
        while (left >= 0 && right < (long)length && s[left] == s[right])
        {
            palindrome = s.substr(left, right - left + 1);
            left--;
            right++;
            if (!palindrome.empty() && palindrome.size() > 1)
                result.insert(palindrome);
        }
    }
}
/* https://app.codility.com/programmers/task/winter_lights/
 * WinterLights
 * Given a string of digits, count the number of subwords(consistent subsequences) that are anagrams of any palindrome.
 * Task Score: 40 %
 * Correctness: 100 %
 * Performance: 25 %
 */
size_t Palindrome::PalindromeAnagramCount(string const &str)
{
    size_t result = 0;
    vector<string> palindromes;
    string substr;
    // Time complexity: O(N^2)
    for (size_t i = 0; i < str.size(); i++)
    {
        for (size_t j = 1; j <= str.size() - i; j++)
        {
            substr = str.substr(i, j);
            if (j == 1 || (j == 2 && substr[0] == substr[1]))
                result++;
            else if (IsPalindrome(substr))
            {
                palindromes.push_back(substr);
                result++;
            }
        }
    }
    return result;
}
/*
 * Task Score: 50 %
 * Correctness: 100 %
 * Performance: 37 %
 */
size_t Palindrome::PalindromeAnagramCount1(string const &str)
{
    size_t result = 0;
    map<char, size_t> counts;
    set<char> oddNumbers;
    long odd = 0;
    bool notPalindrome = false;
    bool evenLength = false;
    // Time complexity: O(N^2)
    for (size_t i = 0; i < str.size(); i++)
    {
        for (size_t j = 1; j <= str.size() - i; j++)
        {
            counts[str[i + (j - 1)]]++;
            evenLength = !(j % 2);
            if (counts[str[i + (j - 1)]] % 2)
            {
                odd++;
                oddNumbers.emplace(str[i + (j - 1)]);
            }
            else
            {
                if (oddNumbers.find(str[i + (j - 1)]) != oddNumbers.end())
                    oddNumbers.erase(str[i + (j - 1)]);
                if (--odd < 0)
                    odd = 0;
            }
            if ((evenLength || odd > 1) && oddNumbers.size())
                notPalindrome = true;
            if (!notPalindrome)
                result++;
            notPalindrome = false;
        }
        odd = 0;
        oddNumbers.clear();
        counts.clear();
    }
    return result;
}
/*
 * https://www.hackerrank.com/challenges/richie-rich/problem
 * 100%
 */
void Palindrome::HighestValuePalindrome(string &s, size_t k)
{
    bool IsPalindrome = true;
    set<size_t> tofix; // Record # characters and positions to fix
    for (long i = 0, j = s.size() - 1; i <= j; i++, j--)
    {
        if (i != j && s[i] != s[j])
            tofix.emplace(i);
    }
    if (tofix.size() > k)
    {
        s = "-1";
        return;
    }
    size_t spare = k - tofix.size(); // Check if we have spare
    /*
     * (k:3 spare: 2) 1 2 3 1 => 1 3 3 1 => 9 3 3 9
     * (k:1 spare: 0) 3 9 4 3 => 3 9 9 3
     * (k:3 spare: 1) 0 9 2 2 8 2 => 2 9 2 2 9 2 => 9 9 2 2 9 9
     */
    // Firstly, fix the string to be a valid palindrome
    for (set<size_t>::iterator it = tofix.begin(); it != tofix.end(); it++)
    {
        if (s[*it] > s[s.size() - *it - 1])
            s[s.size() - *it - 1] = s[*it];
        else if (s[*it] < s[s.size() - *it - 1])
            s[*it] = s[s.size() - *it - 1];
    }
    // Change the string value if we have any spare
    for (long i = 0, j = s.size() - 1; i <= j && spare > 0; i++, j--)
    {
        if (tofix.find(i) == tofix.end())
        {
            if (i == j && spare >= 1 && s[i] != '9')
            {
                s[i] = '9';
                spare -= 1;
            }
            else if (i != j && spare >= 2 && s[i] != '9' && s[j] != '9')
            {
                s[i] = '9';
                s[j] = '9';
                spare -= 2;
            }
        }
        else if (tofix.find(i) != tofix.end() && spare > 0 && s[i] != '9' && s[j] != '9')
        {
            s[i] = '9';
            s[j] = '9';
            spare--;
        }
    }
}
/*
 * https://www.hackerrank.com/challenges/short-palindrome/problem
 * abba
 * i    c   count   j       str123      str12       str1
 * 0    a   0       -       0           0           ['a'] = 1
 * 1    b   0       0['a']  0           [a][b]=1
 *                  1['b']  0           [b][b]=0    ['b'] = 1
 * 2    b   0       0['a']  ['a']=1     [a][b]=2
 *                  1['b']  ['b']=0     [b][b]=1    ['b'] = 2
 * 3    a   1       0['a']  ['a']=1     [a][a]=1
 *                  1['b']  ['b']=0     [b][a]=2    ['a'] = 2
 *
 * abxa
 * i    c   count   j       str123      str12       str1
 * 0    a   0       -       0           0           ['a'] = 1
 * 1    b   0       0['a']  0           [a][b]=1
 *                  1['b']  0           [b][b]=0
 *                  23['x'] 0           [x][b]=0    ['b'] = 1
 * 2    x   0       0['a']  ['a']=0     [a][x]=0
 *                  1['b']  ['b']=0     [b][x]=0
 *                  23['x'] ['x']=0     [x][x]=0    ['x'] = 1
 * 3    a   0       0['a']  ['a']=0     [a][a]=1
 *                  1['b']  ['b']=0     [b][a]=1
 *                  23['x'] ['x']=0     [x][a]=1    ['a'] = 2
 *
 * abbx
 * i    c   count   j       str123      str12       str1
 * 0    a   0       -       0           0           ['a'] = 1
 * 1    b   0       0['a']  0           [a][b]=1
 *                  1['b']  0           [b][b]=0
 *                  23['x'] 0           [x][b]=0    ['b'] = 1
 * 2    b   0       0['a']  ['a']=1     [a][b]=2
 *                  1['b']  ['b']=0     [b][x]=0
 *                  23['x'] ['x']=0     [x][x]=0    ['b'] = 2
 * 3    x   0       0['a']  ['a']=1     [a][x]=1
 *                  1['b']  ['b']=0     [b][x]=2
 *                  23['x'] ['x']=0     [x][x]=0    ['x'] = 1
 *
 * ghhggh
 * i    c   count   j       str123      str12       str1
 * 0    'g' 0       -       0           0           ['g'] = 1
 * 1    'h' 0       6('g')  0           [g][h]=1
 *                  7['h']  0           [h][h]=0    ['h'] = 1
 * 2    'h' 0       6['g']  ['g']=1     [g][h]=2
 *                  7['h']  0           [h][h]=1    ['h'] = 2
 * 3    'g' 1       6['g']  0           [g][g]=1
 *                  7['h']  0           [h][g]=2    ['g'] = 2
 * 4    'g' 2       6['g']  ['g']=2     [g][g]=3
 *                  7['h']  ['h']=2     [h][g]=2    ['g'] = 3
 * 5    'h' 4       6['g']  ['g']=4     [g][h]=4
 *                  7['h']  ['h']=4     [h][h]=4    ['h'] = 3
 *
 * abbaab
 * i    c   count   j       str123      str12       str1
 * 0    'a' 0       -       0           0           ['a'] = 1
 * 1    'b' 0       0['a']  0           [a][b]=1
 *                  1['b']  0           [b][b]=0    ['b'] = 1
 * 2    'b' 0       0]'a']  ['a']=1     [a][b]=2
 *                  1['b']  ['b']=0     [b][b]=1    ['b'] = 2
 * 3    'a' 1       0['a']  ['a']=1     [a][a]=1
 *                  1['b']  ['b']=0     [b][a]=2    ['a'] = 2
 * 4    'a' 2       0['a']  ['a']=2     [a][a]=3
 *                  1['b']  ['b']=2     [b][a]=4    ['a'] = 3
 * 5    'b' 4       0['a']  ['a']=4     [a][b]=5
 *                  1['b']  ['b']=3     [b][b]=4    ['b'] = 3
 *
 * akakak
 * i    c   count   j       str123      str12       str1
 * 0    'a' 0       -       0           0           ['a'] = 1
 * 1    'k' 0       0['a']  0           [a][k]=1
 *                  ['k']   0           [k][k]=0    ['k'] = 1
 * 2    'a' 0       0['a']  0           [a][a]=1
 *                  ['k']   0           [k][a]=1    ['a'] = 2
 * 3    'k' 0       0['a']  ['a']=1     [a][k]=3
 *                  ['k']   ['k']=0     [k][k]=1    ['k'] = 2
 * 4    'a' 1       0['a']  ['a']=2     [a][a]=3
 *                  ['k']   ['k']=1     [k][a]=3    ['a'] = 3
 * 5    'k' 2       0['a']  ['a']=5     [a][k]=6
 *                  ['k']   ['k']=2     [k][k]=3    ['k'] = 3
 *
 * 100%
 */
size_t Palindrome::ShortPalindrome(const string &s)
{
    size_t count = 0;
    vector<size_t> str1(26, 0), str123(26, 0);
    vector<vector<size_t>> str12(26, vector<size_t>(26, 0));
    for (size_t i = 0; i < s.size(); i++)
    {
        size_t c = s[i] - 'a';
        count += str123[c];
        for (size_t j = 0; j < 26; j++) // j will provide the "previous" character
        {
            str123[j] += str12[j][c]; // "xb" += "bx" str123 tracks complete quad of a palindrome
            str12[j][c] += str1[j];   // str12 tracks the first half the quad string of a palindrome
        }
        str1[c]++;
    }
    return count;
}
/*
 * https://www.hackerrank.com/challenges/maximum-palindromes/problem
 * https://stackoverflow.com/questions/66807141/count-palindromic-permutations-mirrors-of-an-array
 * https://www.youtube.com/watch?v=juGgfHsO-xM
 * https://www.tutorialspoint.com/number-of-palindromic-permutations#:~:text=We%20can%20find%20palindromic%20permutations,string%20%E2%80%9Cxxyyyxxzzy%E2%80%9D%20is%205.
 * https://chalkdustmagazine.com/features/counting-palindromes/
 * WIP: 11/32 test cases failed and timeout for some! :(
 */
long double Palindrome::MaxSizePalindromeCount(string const &s, size_t l, size_t r)
{
    const long double modulo = 1e9 + 7L;
    string str = s.substr(l, r - l + 1);
    map<char, size_t> chars;
    if (str.empty())
        return 0;
    else if (l == r && l >= 0 && l < s.size())
        return 1;
    for (string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        pair<map<char, size_t>::iterator, bool> result = chars.emplace(*it, 1);
        if (!result.second)
            chars[*it]++;
    }
    long double singulars = 0, sum = 0, divisor = 1;
    vector<vector<long double>> divisors;
    for (typename map<char, size_t>::const_iterator it = chars.begin(); it != chars.end(); it++)
        if (it->second == 1)
            singulars++;
        else
        {
            // once you have settled the left half of a palindrome (finding all unique permutations of the numbers that end up in that left half) , the right half is fully determined
            size_t sumHalved = (it->second - it->second % 2) / 2;
            sum += sumHalved;
            // divisor *= Factorial(sumHalved);
            vector<long double> d(sumHalved);
            ranges::generate(d, [n = 1]() mutable
                             { return n++; });
            divisors.push_back(d);
            singulars += it->second % 2;
        }
    // sum = Factorial(sum);
    // long double count = sum / divisor;
    vector<long double> sum1(sum);
    ranges::generate(sum1, [n = 1]() mutable
                     { return n++; });
    for (vector<long double>::iterator it = sum1.begin(); it != sum1.end();)
    {
        bool removed = false;
        for (vector<vector<long double>>::iterator it1 = divisors.begin(); it1 != divisors.end() && !removed; it1++)
        {
            vector<long double>::iterator it2 = ranges::find_if(*it1, [it](const auto &value)
                                                                { return value == *it; }); // Look for element <= data[i]
            if (it2 != it1->end())
            {
                removed = true;
                it1->erase(it2);
                it = sum1.erase(it);
            }
        }
        if (!removed)
            it++;
    }
#ifdef _MSC_VER
    // https://docs.microsoft.com/en-us/cpp/parallel/concrt/how-to-perform-map-and-reduce-operations-in-parallel?view=msvc-170
    // https://en.wikipedia.org/wiki/Identity_element
    sum = parallel_reduce(sum1.begin(), sum1.end(), 1.0L /* Identity for Multiplication */, [](long double a, long double b)
                          { return a * b; });
#elif defined(__GNUC__) || defined(__GNUG__)
    sum = parallel_reduce(
        blocked_range<size_t>(0, sum1.size()), 1.0L /* Identity for Multiplication */,
        [&](tbb::blocked_range<size_t> const &r, long double running_total)
        {
            for (size_t i = r.begin(); i < r.end(); i++)
                running_total *= sum1[i];
            return running_total;
        },
        std::multiplies<long double>());
#endif
    for (vector<vector<long double>>::iterator it = divisors.begin(); it != divisors.end(); it++)
    {
#ifdef _MSC_VER
        // https://docs.microsoft.com/en-us/cpp/parallel/concrt/how-to-perform-map-and-reduce-operations-in-parallel?view=msvc-170
        // https://en.wikipedia.org/wiki/Identity_element
        divisor1 *= parallel_reduce(it1->begin(), it1->end(), 1.0L /* Identity for Multiplication */, [](long double a, long double b)
                                    { return a * b; });
#elif defined(__GNUC__) || defined(__GNUG__)
        divisor *= parallel_reduce(
            blocked_range<size_t>(0, it->size()), 1.0L /* Identity for Multiplication */,
            [&](tbb::blocked_range<size_t> const &r, long double running_total)
            {
                for (size_t i = r.begin(); i < r.end(); i++)
                    running_total *= (*it)[i];
                return running_total;
            },
            std::multiplies<long double>());
#endif
    }
    long double count = sum / divisor;
    long double result = fmodl(count * (singulars > 0 ? singulars : 1), modulo);
    cout << fixed << setprecision(0) << result << endl;
    return result;
}
