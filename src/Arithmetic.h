#pragma once
#include <limits>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std;
class Arithmetic
{
private:
	bool CheckIfAdditiveSequence(size_t, size_t, string const &);

public:
	unsigned long long XOR(unsigned long long);
	long ToggleSign(long);
	long absolute(long);
	long SubtractWithPlusSign(long, long);
	long MultiplyWithPlusSign(long, long);
	long DivideWithPlusSign(long, long);
	long divide(long, long);
	long long AddWithoutArithmetic(long long, long long);
	string NumberStringSum(const string &, const string &);
	string NumberStringMultiplication(string &, string &);
	size_t XorSequence(size_t, size_t);
	bool IsAdditiveNumber(string const &);
};