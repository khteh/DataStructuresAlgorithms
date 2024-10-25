#pragma once
#include <limits>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stack>
#include "GenericConstraints.h"
using namespace std;
template <typename T>
class Arithmetic
{
private:
	bool CheckIfAdditiveSequence(size_t, size_t, string const &);

public:
	T XOR(T)
		requires arithmetic_type<T>;
	T XorSequence(T, T)
		requires arithmetic_type<T>;
	T ToggleSign(T)
		requires arithmetic_type<T>;
	T absolute(T)
		requires arithmetic_type<T>;
	T SubtractWithPlusSign(T, T)
		requires arithmetic_type<T>;
	T MultiplyWithPlusSign(T, T)
		requires arithmetic_type<T>;
	T DivideWithPlusSign(T, T)
		requires arithmetic_type<T>;
	T divide(T, T)
		requires arithmetic_type<T>;
	T AddWithoutArithmetic(T, T)
		requires arithmetic_type<T>;
	bool IsAdditiveNumber(string const &);
	void NumberToVector(T, vector<char> &)
		requires arithmetic_type<T>;
	T DigitsVectorToNumber(vector<char> const &)
		requires arithmetic_type<T>;
	string DigitsVectorToNumberString(vector<char> const &);
	string NumberStringSum(const string &, const string &);
	string NumberStringMultiplication(string &, string &);
	void NumberVectorsSum(vector<char> const &, vector<char> const &, vector<char> &);
	void NumberVectorsMultiplication(vector<char> const &, vector<char> const &, vector<char> &);
	T ReversePolishNotation(vector<string> const &)
		requires arithmetic_type<T>;
};