#pragma once
using namespace std;
template <arithmetic_type T>
class GCDExtendedEuclideanResult
{
public:
	GCDExtendedEuclideanResult();
	explicit GCDExtendedEuclideanResult(T, T, T);
	T gcd, x, y;
	bool operator==(GCDExtendedEuclideanResult<T> const &) const;
};
template <arithmetic_type T>
class Arithmetic
{
public:
	T gcd(T, T);
	GCDExtendedEuclideanResult<T> gcd_extended(T, T);
	T gcd_euclidean(T, T);
	GCDExtendedEuclideanResult<T> gcd_euclidean_extended(T, T);
	T lcm(T, T);
	T ModInverse(T, T);
	T XOR(T);
	T XorSequence(T, T);
	T SansaXor(vector<T> const &);
	T ToggleSign(T);
	T absolute(T);
	T SubtractWithPlusSign(T, T);
	T MultiplyWithPlusSign(T, T);
	T DivideWithPlusSign(T, T);
	T Divide(T, T);
	T Divide(T, T, T);
	T AddWithoutArithmetic(T, T);
	T Sqrt(T)
		requires unsigned_integral<T>;
	void NumberToVector(T, vector<T> &);
	T DigitsVectorToNumber(vector<T> const &);
	string DigitsVectorToNumberString(vector<T> const &);
	void NumberVectorsSum(vector<T> const &, vector<T> const &, vector<T> &);
	void NumberVectorsMultiplication(vector<T> const &, vector<T> const &, vector<T> &);
	// void NumberVectorsSquare(vector<T> const &, vector<T> &)
	//	;
	T ReversePolishNotation(vector<string> const &);
};