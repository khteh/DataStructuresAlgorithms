#include "pch.h"
#include "StringArithmetic.h"
/*
 * 123581321
 * 1 2 3
 *   2 3 5
 *     3 5 8
 *       5 8 13
 *         8 13 21
 */
bool StringArithmetic::_CheckIfAdditiveSequence(size_t i, size_t j, string const &str)
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
char StringArithmetic::_Add2BinaryDigits(string &result, char a, char b, char carry)
{
    char sum = a + b + carry - (3 * '0');
    carry = (sum / 2) ? '1' : '0';
    result.append(1, !(sum % 2) ? '0' : '1');
    return carry;
}
/* https://leetcode.com/problems/additive-number/
 * 100%
 * i: width of the first operand
 * j: width of the second operand
 * width of sum is max(i, j). So i must be <= half the input string size
 */
bool StringArithmetic::IsAdditiveNumber(string const &str)
{
    for (size_t i = 1; i <= str.size() / 2; i++)
        for (size_t j = 1; max(i, j) <= str.size() - i - j; j++)
            if (_CheckIfAdditiveSequence(i, j, str))
                return true;
    return false;
}
/*
 * https://leetcode.com/problems/add-binary/
 * 100%
 */
string StringArithmetic::Add2Binary(string const &a, string const &b)
{
    string result;
    char carry = '0';
    for (int i = a.size() - 1, j = b.size() - 1; i >= 0 && j >= 0; i--, j--)
        carry = _Add2BinaryDigits(result, a[i], b[j], carry);
    if (a.size() > b.size())
    {
        for (int i = a.size() - b.size() - 1; i >= 0; i--)
            carry = _Add2BinaryDigits(result, a[i], '0', carry);
    }
    else if (b.size() > a.size())
    {
        for (int i = b.size() - a.size() - 1; i >= 0; i--)
            carry = _Add2BinaryDigits(result, b[i], '0', carry);
    }
    if (carry == '1')
        result.append(1, '1');
    ranges::reverse(result);
    return result;
}
// Function for finding sum of larger numbers
string StringArithmetic::NumberStringSum(const string &str1, const string &str2)
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
string StringArithmetic::NumberStringMultiplication(string &num1, string &num2)
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
