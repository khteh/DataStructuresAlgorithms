#pragma once
using namespace std;
template <typename T>
class GCDExtendedEuclideanResult
{
public:
	GCDExtendedEuclideanResult()
		requires arithmetic_type<T>;
	GCDExtendedEuclideanResult(T, T, T)
		requires arithmetic_type<T>;
	T gcd, x, y;
	bool operator==(GCDExtendedEuclideanResult<T> const &) const
		requires arithmetic_type<T>;
};
template <typename T>
class Arithmetic
{
private:
	bool CheckIfAdditiveSequence(size_t, size_t, string const &);

public:
	T gcd(T, T)
		requires arithmetic_type<T>;
	GCDExtendedEuclideanResult<T> gcd_extended(T, T)
		requires arithmetic_type<T>;
	T gcd_euclidean(T, T)
		requires arithmetic_type<T>;
	GCDExtendedEuclideanResult<T> gcd_euclidean_extended(T, T)
		requires arithmetic_type<T>;
	T lcm(T, T)
		requires arithmetic_type<T>;
	T ModInverse(T, T)
		requires arithmetic_type<T>;
	T XOR(T)
		requires arithmetic_type<T>;
	T XorSequence(T, T)
		requires arithmetic_type<T>;
	T SansaXor(vector<T> const &)
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
	T Divide(T, T)
		requires arithmetic_type<T>;
	T Divide(T, T, T)
		requires arithmetic_type<T>;
	T AddWithoutArithmetic(T, T)
		requires arithmetic_type<T>;
	bool IsAdditiveNumber(string const &);
	void NumberToVector(T, vector<T> &)
		requires arithmetic_type<T>;
	T DigitsVectorToNumber(vector<T> const &)
		requires arithmetic_type<T>;
	string DigitsVectorToNumberString(vector<T> const &)
		requires arithmetic_type<T>;
	string NumberStringSum(const string &, const string &);
	string NumberStringMultiplication(string &, string &);
	void NumberVectorsSum(vector<T> const &, vector<T> const &, vector<T> &)
		requires arithmetic_type<T>;
	void NumberVectorsMultiplication(vector<T> const &, vector<T> const &, vector<T> &)
		requires arithmetic_type<T>;
	// void NumberVectorsSquare(vector<T> const &, vector<T> &)
	//	requires arithmetic_type<T>;
	T ReversePolishNotation(vector<string> const &)
		requires arithmetic_type<T>;
};