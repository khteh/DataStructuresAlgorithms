#pragma once
using namespace std;
class StringArithmetic
{
private:
    bool _CheckIfAdditiveSequence(size_t, size_t, string const &);
    char _Add2BinaryDigits(string &, char, char, char);

public:
    string Add2Binary(string const &, string const &);
    bool IsAdditiveNumber(string const &);
    string NumberStringSum(const string &, const string &);
    string NumberStringMultiplication(string &, string &);
};