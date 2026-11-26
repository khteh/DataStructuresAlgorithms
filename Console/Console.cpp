// ConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
int main(int argc, char* argv[])
{
	bool flag;
	string str, str1;
	ostringstream oss;
	size_t size, size1, size2;
	long l, l1, l2;
	int32_t i, j, * iPtr;
	unsigned int ui;
	uint64_t mask = 0;
	long double ld, ld1;
	set<char> cset, cset1;
	set<size_t> uset1, uset2;
	set<string> stringset, stringset1;
	set<long> lset;
	vector<string> strings, strings1;
	vector<long> a, b, sortData;
	vector<long double> vld;
	vector<int> data, data1;
	vector<size_t> udata, udata1;
	vector<widest_unsigned_int> big_unsigned_int;
	vector<bool> bools;
	set<vector<size_t>> usetvec;
	set<set<size_t>> usetgrid;
	priority_queue<long, deque<long>> maxHeap;
	priority_queue<long, deque<long>, greater<long>> minHeap;
	PriorityQueueMedian<long> pqueue;
	vector<vector<unsigned long>> grid;
	vector<vector<long>> grid1, grid2;
	vector<vector<char>> cgrid1, cgrid2;
	vector<vector<string>> sgrid, sgrid1;
	vector<vector<size_t>> ugrid, ugrid1;
	Graph<size_t, size_t> graph;
	Arithmetic<size_t> arithmetic;
	StringArithmetic stringArithmetic;
	Arithmetic<long> larithmetic;
	DynamicProgramming<size_t> dp;
	Matrix<long> lmatrix;
	Range range;
	Palindrome palindrome;
	Permutation<long> lPermutation;
	Permutation<size_t> ulPermutation;
	Permutation<string> sPermutation;
	Tree<long> ltree;
	FenwickTree<size_t> fenwickTree;
	Search search;
	Sort<long> sortAlgorithm;
	ExceptionTest();
	TestRandom();
	KDTreeTests();
	cpp20readonlyranges();
	cpp20ranges();
	cpp20variants();
	strings = { "111", "100", "100" };
	cgrid1.resize(strings.size());
	for (size_t i = 0; i < strings.size(); i++)
		ranges::copy(strings[i], back_inserter(cgrid1[i]));
	assert(stringset.erase("Does not exist") == 0); // Erasing non-existing element does NOT throw
	str = to_string(0);
	istringstream(str) >> i;
	assert(!i);
	Singleton* singleton = Singleton::Instance();
	assert(singleton);
	singleton->Print("Hello Singleton!!!");
	unique_ptr<NameHidingExampleDerived> hide = make_unique<NameHidingExampleDerived>(0xdeadbeef);
	unique_ptr<NameHidingExample> hide1 = make_unique<NameHidingExampleDerived>(0xdeadbeef);
	hide->Print(1);
	hide1->Print(1);
	// hide->Print(1, 2);
	//((NameHidingExample*)hide)->Print(1, 2);
	cout << endl;
	unique_ptr<Radio> radio = make_unique<Radio>("Radio");
	Transmitter* tx = radio.get();
	Receiver* rx = radio.get();
	radio->Write(); // Transmitter::Write() -> Receiver::Read()
	assert(radio->Read() == "Receiver: Receiver: Radio");
	tx->Write(); // Transmitter::Write() -> Receiver::Read()
	assert(tx->Read() == "Receiver: Receiver: Receiver: Radio");
	rx->Write();
	assert(rx->Read() == "Receiver: Receiver: Receiver: Receiver: Radio");
	radio->Write("Hello World!!!");
	assert(radio->Read() == "Receiver: Hello World!!!");
	tx->Write("Transmitter");
	assert(tx->Read() == "Receiver: Transmitter");
	rx->Write("Receiver");
	assert(tx->Read() == "Receiver: Receiver");

	unique_ptr<Transmitter> tx1 = make_unique<Transmitter>();
	assert(tx1->Read().empty());
	tx1->Write();
	assert(tx1->Read().empty());
	tx1->Write("TX");
	assert(tx1->Read() == "TX");

	unique_ptr<Receiver> rx1 = make_unique<Receiver>();
	assert(rx1->Read() == "Receiver: ");
	rx1->Write();
	assert(rx1->Read() == "Receiver: ");
	rx1->Write("RX");
	assert(rx1->Read() == "Receiver: RX");

	str = "m";
	str1 = str.substr(1);
	assert(str1.empty());
	str1 = str.substr(0, 0);
	assert(str1.empty());
	char cstr[8];
	cout << "sizeof(int): " << sizeof(int) << endl;								  // Linux: 4, Windows: 4
	cout << "sizeof(size_t): " << sizeof(size_t) << endl;						  // Linux: 8, Windows: 8
	cout << "sizeof(long): " << sizeof(long) << endl;							  // Linux: 8, Widnows: 4
	cout << "sizeof(long long): " << sizeof(long long) << endl;					  // Linux: 8, Windows: 8
	cout << "sizeof(unsigned long long): " << sizeof(unsigned long long) << endl; // Linux: 8, Windows: 8
	cout << "sizeof(char[8]): " << sizeof(cstr) << endl;						  // Linux: 8, Windows: 8
	cout << "sizeof(void*): " << sizeof(void*) << endl;						  // Linux: 8, Windows: 8
	cout << "sizeof(double): " << sizeof(double) << endl;						  // LInux: 8, Windows: 8
	cout << "sizeof(long double): " << sizeof(long double) << endl;				  // Linux: 16, Windows: 8
	assert(sizeof(char) == 1);
	assert(sizeof(short) == 2);
	assert(sizeof(int) == 4);
	assert(sizeof(int32_t) == 4);
	assert(sizeof(int*) == 8);
#if defined(__GNUC__) || defined(__GNUG__)
	assert(sizeof(long) == 8);
#else
	assert(sizeof(long) == 4);
#endif
	assert(sizeof(float) == 4);
	assert(sizeof(long long) == 8);
	assert(sizeof(int64_t) == 8);
	assert(sizeof(unsigned long long) == 8);
	assert(sizeof(uint64_t) == 8);
	assert(sizeof(double) == 8);
#if defined(__GNUC__) || defined(__GNUG__)
	assert(sizeof(long double) == 16);
#else
	assert(sizeof(long double) == 8);
#endif
#if defined(__GNUC__) || defined(__GNUG__)
	assert(numeric_limits<int>::min() > numeric_limits<long>::min());
	assert(numeric_limits<int>::max() < numeric_limits<long>::max());
#else
	assert(numeric_limits<int>::min() == numeric_limits<long>::min());
	assert(numeric_limits<int>::max() == numeric_limits<long>::max());
#endif
	cout << "https://en.wikipedia.org/wiki/Machine_epsilon: Float: " << numeric_limits<float>::epsilon() << ", Double: " << numeric_limits<double>::epsilon() << ", Long Double: " << numeric_limits<long double>::epsilon() << endl;
	cout << "Machine Epsilon: Float: " << Ulp<float>((float)1) << ", Approximation: " << MachineEpsilonApproximation<float>() << endl;
	cout << "Machine Epsilon: Double: " << Ulp<double>((double)1) << ", Approximation: " << MachineEpsilonApproximation<double>() << endl;
	cout << "numeric_limits<int>::min(): " << numeric_limits<int>::min() << " (0x" << hex << numeric_limits<int>::min() << dec << "), numeric_limits<int>::max(): " << numeric_limits<int>::max() << " (0x" << hex << numeric_limits<int>::max() << ")" << endl;
	cout << "numeric_limits<unsigned int>::min(): " << numeric_limits<unsigned int>::min() << " (0x" << hex << numeric_limits<unsigned int>::min() << dec << "), numeric_limits<unsigned int>::max(): " << numeric_limits<unsigned int>::max() << " (0x" << hex << numeric_limits<unsigned int>::max() << ")" << endl;
	cout << "numeric_limits<int32_t>::min(): " << dec << numeric_limits<int32_t>::min() << " (0x" << hex << numeric_limits<int32_t>::min() << dec << "), numeric_limits<int32_t>::max(): " << numeric_limits<int32_t>::max() << " (0x" << hex << numeric_limits<int32_t>::max() << ")" << endl;
	cout << "numeric_limits<long>::min(): " << numeric_limits<long>::min() << " (0x" << hex << numeric_limits<long>::min() << dec << "), numeric_limits<long>::max(): " << numeric_limits<long>::max() << " (0x" << hex << numeric_limits<long>::max() << dec << ")" << endl;
	cout << "numeric_limits<long long>::min(): " << numeric_limits<long long>::min() << " (0x" << hex << numeric_limits<long long>::min() << dec << "), numeric_limits<long long>::max(): " << dec << fixed << numeric_limits<long long>::max() << " (0x" << hex << numeric_limits<long long>::max() << dec << ")" << endl;
#ifdef __SIZEOF_INT128__
	cout << "sizeof(int128_t): " << sizeof(int128_t) << endl; // Linux: 16, Windows: 8
	cout << "numeric_limits<int128_t>::min(): " << numeric_limits<int128_t>::min() << " (0x" << hex << numeric_limits<int128_t>::min() << dec << "), numeric_limits<int128_t>::max(): " << dec << fixed << numeric_limits<int128_t>::max() << " (0x" << hex << numeric_limits<int128_t>::max() << dec << ")" << endl;
	assert("-170141183460469231731687303715884105728" == to_string(numeric_limits<int128_t>::min()));
	assert("170141183460469231731687303715884105727" == to_string(numeric_limits<int128_t>::max()));
	cout << "numeric_limits<uint128_t>::min(): " << numeric_limits<uint128_t>::min() << " (0x" << hex << numeric_limits<uint128_t>::min() << dec << "), numeric_limits<uint128_t>::max(): " << dec << fixed << numeric_limits<uint128_t>::max() << " (0x" << hex << numeric_limits<uint128_t>::max() << dec << ")" << endl;
	assert("0" == to_string(numeric_limits<uint128_t>::min()));
	assert("340282366920938463463374607431768211455" == to_string(numeric_limits<uint128_t>::max()));
	assert(numeric_limits<int128_t>::min() * -1 == numeric_limits<int128_t>::min()); // 0x8000_0000_0000_0000 * -1 = 0x8000_0000_0000_0000
#endif
	cout << "numeric_limits<size_t>::min(): " << numeric_limits<size_t>::min() << " (0x" << hex << numeric_limits<size_t>::min() << "), numeric_limits<size_t>::max(): " << dec << fixed << numeric_limits<size_t>::max() << " (0x" << hex << numeric_limits<size_t>::max() << dec << ")" << endl;

	cout << "numeric_limits<double>::min(): " << numeric_limits<double>::min() << " (0x" << hex << numeric_limits<double>::min() << dec << "),  " << endl;
	cout << "numeric_limits<double>::max(): " << dec << fixed << numeric_limits<double>::max() << endl;
	cout << "numeric_limits<double>::max(): 0x" << hex << numeric_limits<double>::max() << dec << endl;
	cout << "numeric_limits<double>::min() * -1 = " << numeric_limits<double>::min() * -1 << endl;

	cout << "numeric_limits<long double>::min(): " << numeric_limits<long double>::min() << " (0x" << hex << numeric_limits<long double>::min() << dec << "),  " << endl;
	cout << "numeric_limits<long double>::max(): " << dec << fixed << numeric_limits<long double>::max() << endl;
	cout << "numeric_limits<long double>::max(): 0x" << hex << numeric_limits<long double>::max() << dec << endl;
	cout << "numeric_limits<long double>::min() * -1 = " << numeric_limits<long double>::min() * -1 << endl;
	// https://en.cppreference.com/w/cpp/types/numeric_limits/is_iec559
	cout << "numeric_limits<long double>::is_iec559: " << numeric_limits<long double>::is_iec559 << ", has_infinity: " << numeric_limits<long double>::has_infinity << ", has_quiet_NaN: " << numeric_limits<long double>::has_quiet_NaN << ", has_signaling_NaN: " << numeric_limits<long double>::has_signaling_NaN << endl;
	i = -123;
	j = -321;
	str = to_string(i);
	cout << "-123: 0x" << hex << i << " " << str << ", -321: 0x" << j << dec << endl;
	assert(numeric_limits<int>::min() * -1 == numeric_limits<int>::min());		   // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
	assert(numeric_limits<int32_t>::min() * -1 == numeric_limits<int32_t>::min()); // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
	assert(INT_MIN * -1 == INT_MIN);											   // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
	// assert(numeric_limits<int>::min() / -1 == numeric_limits<int>::min()); Integer overflow as 0x8000_0000 positive is > numeric_limits<int>::max()
	assert(numeric_limits<int>::max() * -1 == numeric_limits<int>::min() + 1);		   // 0x7FFFF_FFFF * -1 = -0x7FFF_FFFF = 0x8000_0001
	assert(numeric_limits<int32_t>::max() * -1 == numeric_limits<int32_t>::min() + 1); // 0x7FFFF_FFFF * -1 = -0x7FFF_FFFF = 0x8000_0001
	assert(numeric_limits<long>::min() * -1 == numeric_limits<long>::min());		   // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
	assert(numeric_limits<long long>::min() * -1 == numeric_limits<long long>::min()); // 0x8000_0000_0000_0000 * -1 = 0x8000_0000_0000_0000
	// assert(numeric_limits<long>::min() / -1 == numeric_limits<long>::min()); Integer overflow as 0x8000_0000_0000_0000 positive is > numeric_limits<long>::max()
	assert(numeric_limits<long>::max() * -1 == numeric_limits<long>::min() + 1); // 0x7FFFF_FFFF * -1 = -0x7FFF_FFFF = 0x8000_0001
	assert(1e5 == pow(10, 5));
	assert(1e5 == 10e4);
	assert(1e5 == 100'000);
	assert(pow(10, 5) == 100'000);
	assert(1e10 == 10e9);
	assert(1e10 == pow(10, 10));
	assert(1e6 == 10e5);
	assert(1e6 == pow(10, 6));
	assert(1e6 == 1'000'000);
	assert(1e9 == 1'000'000'000ull);
	assert(1e9 + 7 == 10e8 + 7);
	assert(1e9 + 7 == pow(10, 9) + 7);
	cout << "1e9: " << 1e9 << ", 10e9: " << 10e9 << endl;
	cout << "1e5: " << 1e5 << ", pow(10, 5): " << pow(10, 5) << ", " << pow(2, pow(10, 5)) << endl;
	cout << "-1e18: " << -1e18 << ", numeric_limits<long long>::min(): " << numeric_limits<long long>::min() << endl;
	/*
	 * https://stackoverflow.com/questions/42963913/what-actually-is-the-modulo-of-a-negative-number
	 * (a/b)*b + a%b == a
	 * a:3, b:4
	 * (3/4)*4 + 3%4 = 3
	 *
	 * a:7, b:5
	 * (7/5)*5 + 7%5 = 5 + 2 = 7
	 *
	 * a:-7, b:5
	 * (-7/5)*5 + -7%5 = -5 + ? = -7 => -7%5 = -2
	 *
	 * a:7, b:-5
	 * (7/-5)*-5 + 7%-5 = 5 + ? = 7 => 7%-5 = 2
	 */
	assert(-3 % 2 == -1);
	assert(3 % -2 == 1);
	assert(-3 % -2 == -1);
	l1 = 3;
	l2 = 7;
	l = 5;
	/*
	 * https://www.hackerrank.com/contests/world-codesprint-7/challenges/summing-pieces/forum/comments/188413
	 * (a - b) % m = (a % m - b % m + m) % m
	 */
	assert((l1 - l2) % l == -4);
	assert((l1 % l - l2 % l + l) % l == 1);
	/*
	a % b
	a: 3
	b: 5
	a/b = 0
	a - (a/b)b = 3 - 0 = 3

	a: 7
	b: 5
	a/b = 1
	a - (a/b)b = 7 - 5 = 2
	*/
	l1 = 3;
	l2 = 5;
	assert(l1 % l2 == l1 - (l1 / l2) * l2);
	l1 = 7;
	l2 = 5;
	assert(l1 % l2 == l1 - (l1 / l2) * l2);
	i = 3;
	assert(-i == -3);
	assert(~i == -4);
	i = 0x7FFFFFFF;
	long long ll = i;
	i++;
	ll++;
	assert(i == numeric_limits<int>::min());
	assert(i < 0);
	assert((long long)i == 0xFFFFFFFF80000000LL);
	assert(ll > 0);
	assert(ll == 0x80000000);
	cout << "(int)0x7FFFFFFF + 1: " << i << ", long long: " << (long long)(i) << endl; // sign extended to 64-bit
	cout << "(long long)0x7FFFFFFF + 1: " << ll << endl;
	ui = 0xFFFFFFFF;
	assert(ui == numeric_limits<unsigned int>::max());
	cout << "Unsigned int 0xFFFFFFFF: " << ui << endl;
	i = 0x80000000;
	ll = i;
	assert(ll < 0); // sign extended to 64-bit
	assert(ll == 0xFFFFFFFF80000000LL);
	i--;
	ll--;
	assert(i > 0); // integer overflow
	assert(i == numeric_limits<int>::max());
	assert(ll < 0); // sign extended to 64-bit
	assert(ll == 0xFFFFFFFF7FFFFFFFLL);
	cout << "(int)0x80000000 - 1: " << i << ", long long: " << (long long)(i) << endl; // integer overflow
	cout << "(long long)0x80000000 - 1: " << ll << endl;
	i = 0x80000000;
	cout << "INT_MIN: " << INT_MIN << ", 0x" << hex << INT_MIN << dec << endl;
	j = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	// assert(INT_MIN == -INT_MIN); runtime error: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself
	assert(i == j);
	assert(i < 0);
	assert(j < 0);
	cout << "(int)-0x80000000: " << i << endl;
	i = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	ll = i;
	assert(ll < 0); // sign extended to 64-bit
	assert(ll == 0xFFFFFFFF80000000LL);
	i--;
	ll--;
	assert(i > 0); // integer overflow
	assert(i == numeric_limits<int>::max());
	assert(ll < 0); // sign extended to 64-bit
	assert(ll == 0xFFFFFFFF7FFFFFFFLL);
	cout << "(int)0x80000000 - 1: " << i << ", long long: " << (long long)(i) << endl; // integer overflow
	cout << "(long long)0x80000000 - 1: " << ll << endl;
	i = 0x80000000;
	assert(i < 0);
	i /= 2;
	assert(i < 0);
	assert(i == -0x40000000);
	i = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	assert(i < 0);
	i /= 2;
	assert(i < 0);
	assert(i == -0x40000000);

	ll = 0x80000000LL;
	assert(ll > 0);
	ll--;
	assert(ll > 0);
	assert(ll == 0x7fffffffL);
	ll = -0x80000000LL;
	assert(ll == 0xFFFFFFFF80000000);
	assert(ll < 0);
	ll--;
	assert(ll < 0);
	assert(ll == 0xFFFFFFFF7FFFFFFFL);

	/* https://stackoverflow.com/questions/79450133/integer-overflow-in-expression-of-type-int-results-in-1-woverflow
	 * -Woverflow may be designed to work only with expressions containing variables
	 * -Woverflow results in Undefined behaviour.
	 */
	i = 0x80000000;
	j = 0x7FFFFFFF;
	cout << "i: " << i << ", -i: " << -i << endl;
	/*
	 * numeric_limits<int>::min(): -2147483648 (0x80000000), numeric_limits<int>::max(): 2147483647 (0x7fffffff), numeric_limits<int>::min() *-1 = 80000000
	 * numeric_limits<unsigned int>::min(): 0 (0x0), numeric_limits<unsigned int>::max(): 4294967295 (0xffffffff), numeric_limits<unsigned int>::min() *-1 = 0
	 * https://stackoverflow.com/questions/14695118/2147483648-0-returns-true-in-c/14695202
	 * -2147483648 is not a "number". C++ language does not support negative literal values.

	 * -2147483648 is actually an expression: a positive literal value 2147483648 with unary - operator in front of it. Value 2147483648 is apparently too large for the positive side of int range on your platform.
	 * If type long int had greater range on your platform, the compiler would have to automatically assume that 2147483648 has long int type.
	 * (In C++11 the compiler would also have to consider long long int type.) This would make the compiler to evaluate -2147483648 in the domain of larger type and the result would be negative, as one would expect.

	 * However, apparently in your case the range of long int is the same as range of int, and in general there's no integer type with greater range than int on your platform.
	 * This formally means that positive constant 2147483648 overflows all available signed integer types, which in turn means that the behavior of your program is undefined.
	 * (It is a bit strange that the language specification opts for undefined behavior in such cases, instead of requiring a diagnostic message, but that's the way it is.)

	 * In practice, taking into account that the behavior is undefined, 2147483648 might get interpreted as some implementation-dependent negative value which happens to turn positive after having unary - applied to it.
	 * Alternatively, some implementations might decide to attempt using unsigned types to represent the value (for example, in C89/90 compilers were required to use unsigned long int, but not in C99 or C++).
	 * Implementations are allowed to do anything, since the behavior is undefined anyway.

	 * As a side note, this is the reason why constants like INT_MIN are typically defined as

	 * #define INT_MIN (-2147483647 - 1)
	 * instead of the seemingly more straightforward

	 * #define INT_MIN -2147483648
	 * The latter would not work as intended.
	 */
#if defined(__GNUC__) || defined(__GNUG__)
	assert(0x80000000 == -0x80000000); // Windows MSVC: C4146 "unary minus operator applied to unsigned type.result still unsigned"
#endif
	assert(1 == (int)0x80000000 - (int)0x7fffffff);
	assert(1 == 0x80000000 - 0x7fffffff);
	// assert(i == -i); Why!?!
	cout << i << " - " << j << " = " << i - j << endl;
	// assert(1 == i - 0x7FFFFFFF); integer overflow in expression of type ‘int’ results in ‘1’ [-Woverflow]
	// assert(1 == (i - j)); integer overflow in expression of type ‘int’ results in ‘1’ [-Woverflow] cout << "INT_MIN: " << INT_MIN << hex << " 0x" << INT_MIN << ", -INT_MIN: " << dec << -INT_MIN << " 0x" << hex << -INT_MIN << endl;
	i = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	// assert(j == (i - 0x7FFFFFFF)); integer overflow in expression of type ‘int’ results in ‘1’ [-Woverflow]

	size_t ul = numeric_limits<size_t>::max() + 1;
	assert(!ul);
	cout << "int -" << hex << i << ": " << -i << dec << " " << -i << ", ~" << i << ": " << hex << ~i << " " << dec << ~i << endl;
	ul = 3;
	// cout << "uint -" << hex << ui << ": " << -ui << dec << " " << -ui << ", ~" << ui << ": " << hex << ~ui << " " << dec << ~ui << endl;
	assert(1 == abs(-INT_MIN - 0x7FFFFFFF));
	assert(1 == abs(0x7FFFFFFF - -INT_MIN));

	/*
	 * 0x8000_0000 + 1 = -0x7FFF_FFFF = 0x8000_0001 (two's compliment)
	 * 0x8000_0000 - 1 = -0x8000_0001 = 0x7FFF_FFFF
	 */
	i = 0x80000000;
	j = i + 1;
	cout << i << " (0x" << hex << i << ") + 1 = " << dec << j << " 0x" << hex << j << endl;
	assert(j == 0x80000001);
	j = i - 1;
	cout << dec << i << " (0x" << hex << i << ") - 1 = " << dec << j << " 0x" << hex << j << endl;
	// assert(j == 0x7FFFFFFF); Why!?!
	assert(!numeric_limits<size_t>::has_quiet_NaN);
	assert(!numeric_limits<long>::has_quiet_NaN);
	assert(!numeric_limits<size_t>::has_signaling_NaN);
	assert(!numeric_limits<long>::has_signaling_NaN);
	assert(numeric_limits<float>::has_signaling_NaN);
	assert(numeric_limits<double>::has_signaling_NaN);
	assert(numeric_limits<long double>::has_signaling_NaN);
	assert(!(-4 % 2));
	assert(!(0xFFFFFFFC % 2));
	for (size_t i = 0; i < 10; i++)
	{
		double log = log2(i);
		cout << fixed << "log2(" << i << ") = " << log << ", ceil(log2(" << i << ")) = " << ceil(log) << ", floor(log2(" << i << ")) = " << floor(log) << endl;
	}
	ul = 100;
	generate_n(inserter(uset1, uset1.end()), 10, [&ul]()
		{ return ul++; });
	set<size_t>::const_iterator it = uset1.begin();
	for (size_t i = 0; it != uset1.end(); it++, i++)
		assert(*it == 100 + i);

	time_point timestamp = system_clock::now();
	duration timespan = timestamp.time_since_epoch();
	int64_t ticks = timespan.count();
	int64_t signedTicks = timespan.count();
	assert(std::chrono::system_clock::duration::min().count() == numeric_limits<int64_t>::min());
	assert(std::chrono::system_clock::duration::max().count() == numeric_limits<int64_t>::max());
	assert(signedTicks == ticks);
	cout << "Current timestamp (ticks since Epoch): " << ticks << ", signed ticks: " << signedTicks << endl;
#ifdef __cpp_lib_hardware_interference_size
	static constexpr size_t CacheLineSize = std::hardware_destructive_interference_size;
#else
	static constexpr size_t CacheLineSize = 64; // Default standard fallback
#endif
	cout << dec << "CacheLineSize: " << CacheLineSize << endl;
	cout << "30! " << Factorial<size_t>(30) << endl;			 // The CPU signals loss of precision via a flag in the FPU control registers starting from i=26
	cout << "Fibonacci(100) " << Fibonacci<size_t>(100) << endl; // The CPU signals loss of precision via a flag in the FPU control registers starting from i=94
	str.resize(0);
	str = "Hello, ";
	assert(strlen("Hello, ") == str.size());
	str.resize(20); // resize(n) changes size: it adds n − size() '\0' characters to the string. The following += calls would then append after those nulls, leaving a block of garbage in the middle of the output.
	str += "World!!!";
	oss.str("");
	cout << "strlen: " << strlen("Hello, World!!!") << ", str.size(): " << str.size() << ", str: " << str << endl;
	assert(strlen("Hello, World!!!") != str.size());
	assert(20 + strlen("World!!!") == str.size());

	grid = { { 1, 3, 5 },{ 2, 4, 6 },{ 7, 8, 9 } };
	// grid.back() = {7,8,9}
	assert(grid.back().back() == 9);
	grid.clear();
	grid1 = { { -1, 0, -1 },{ -1, -1, -1 },{ -1, -1, -1 } };
	grid2 = { { 1, 0, 1 },{ 2, 1, 2 },{ 3, 2, 3 } };
	lmatrix.MatrixDistance(grid1, 0, 1);
	cout << "grid1 (" << grid1.size() << "): " << endl;
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
		{
			cout << grid1[i][j] << " ";
			assert(grid1[i][j] == grid2[i][j]);
		}
	cout << endl;
	str = "ab2c3";
	assert(uncompress(str) == "ababcababcababc");
	cout << "uncompress(" << quoted(str) << "): " << uncompress(str) << endl;
	str = "0010110100";
	size = FindLongestContiguousPattern(str, '1');
	assert(size == 4);
	assert(str == "0010111100");
	cout << "FindLongestContiguousPattern(\"0010110100\", \'1\'): " << str << " size: " << size << endl;
	str = "00101101100";
	size = FindLongestContiguousPattern(str, '1');
	assert(size == 5);
	assert(str == "00101111100");
	cout << "FindLongestContiguousPattern(\"00101101100\", \'1\'): " << str << " size: " << size << endl;

	// Test C++ *& "pointer reference" construct
	iPtr = (int*)malloc(10 * sizeof(int));
	cout << "Size of iPtr: " << sizeof(iPtr) << " Sizeof *iPtr: " << sizeof(*iPtr) << endl;
	memset(iPtr, 0xdeadbeef, 10 * sizeof(int));
	for (size_t i = 0; i < 10; i++)
		assert(iPtr[i] == 0xefefefef);
	cout << "iPtr @: " << iPtr << ", Size of iPtr: " << sizeof(iPtr) << ", Size of *iPtr: " << sizeof(*iPtr) << ", iPtr[0]: " << hex << iPtr[0] << dec << endl;
	testPointerReference(iPtr);
	for (size_t i = 0; i < 10; i++)
		assert(iPtr[i] == 0xabababab);
	cout << "iPtr @: " << iPtr << ", Size of iPtr: " << sizeof(iPtr) << ", Size of *iPtr: " << sizeof(*iPtr) << ", iPtr[0]: " << hex << iPtr[0] << dec << endl;
	free(iPtr);
	iPtr = nullptr;
	// End of Test C++ *& "pointer reference" construct
	assert(MinBitTrick(123, 456) == 123);
	assert(MaxBitTrick(123, 456) == 456);
	assert(gcd(48, 15) == 3);
	assert(gcd(108, 48) == 12);
	assert(gcd(1050, 507) == 3);
	assert(lcm(21, 6) == 42);
	assert(!isUniqueString("Helo World!!!"));
	str = "Hello World!!!";
	reverse(str);
	assert(str == "!!!dlroW olleH");
	str = "The house is blue";
	ReverseWords(str);
	assert(str == "blue is house The");
	str = "  The   house is    blue  ";
	ReverseWordsTrimmed(str);
	assert(str == "blue is house The");

	str = "abcdefcdbacd";
	str1 = "abcd";
	udata = FindSubString(str, str1);
	udata1 = { 0, 6, 7, 8 };
	assert(udata.size() == 4); // 0 6 7 8
	assert(udata1 == udata);

	assert(Count1Bits(10) == 2);
	assert(Count1Bits(12) == 2);
	assert(Count1Bits(7) == 3);
	a.clear();
	BitCombinations(3, a); // 000 001 010 100 011 101 110 111
	assert(a.size() == 8);
	b.clear();
	b = { 0, 1, 2, 4, 3, 5, 6, 7 };
	assert(b == a);
	cout << "BitCombinations from 0 to 3 of '1' bits: ";
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		cout << bitset<3>(*it) << " ";
	cout << endl;
	a.clear();
	BitCombinations(4, a); // 0000 0001 0010 0100 1000 0011 0101 0110 1001 1010 1100 0111 1011 1101 1110 1111
	assert(a.size() == 16);
	b.clear();
	b = { 0, 1, 2, 4, 8, 3, 5, 6, 9, 10, 12, 7, 11, 13, 14, 15 };
	assert(b == a);
	cout << "BitCombinations from 0 to 4 of '1' bits: ";
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		cout << bitset<4>(*it) << " ";
	cout << endl;
	udata.clear();
	udata = grayCode(2);
	assert(udata.size() == 4);
	udata1.clear();
	udata1 = { 0, 1, 3, 2 };
	assert(udata1 == udata);
	udata.clear();
	udata = grayCode(0);
	assert(udata.size() == 1);
	assert(udata[0] == 0);
	strings.clear();
	strings = { "a", "b", "c", "d" };
	strings1 = { "b", "c" };
	strings = findUnique(strings, strings1);
	assert(strings.size() == 2); //  a d
	assert(strings[0] == "a");
	assert(strings[1] == "d");
	str = "a";
	assert(CanShuffleWithoutRepeat(str));
	str = "aa";
	assert(!CanShuffleWithoutRepeat(str));
	str = "aab";
	assert(CanShuffleWithoutRepeat(str));
	str = "aaaabbcc";
	assert(CanShuffleWithoutRepeat(str));
	a.clear();
	a.clear();
	b.clear();
	strings.clear();
	strings = { "Angel", "legnA", "Hello World!!!", "World Hello!!!" };
	cout << "strings without sorted: " << endl;
	ranges::copy(strings, ostream_iterator<string>(cout, "\r\n"));
	ranges::sort(strings);
	assert(strings[0] == "Angel");
	assert(strings[1] == "Hello World!!!");
	assert(strings[2] == "World Hello!!!");
	assert(strings[3] == "legnA");
	cout << "strings sorted with default comparer: " << endl;
	ranges::copy(strings, ostream_iterator<string>(cout, "\r\n"));
	ranges::sort(strings, [](string a, string b) -> bool
		{
			ranges::sort(a);
			ranges::sort(b);
			return a < b; });
	assert(strings[0] == "Hello World!!!");
	assert(strings[1] == "World Hello!!!");
	assert(strings[2] == "Angel");
	assert(strings[3] == "legnA");
	cout << "strings sorted with anagrams next to each other: " << endl;
	ranges::copy(strings, ostream_iterator<string>(cout, "\r\n"));
	a.clear();
	a = { 0, 1, 2, 7, 10, 11, 12, 20, 25, 26, 27 };
	string strRange = GetRange(a);
	assert(strRange == "0 - 2, 7, 10 - 12, 20, 25 - 27");
	cout << "GetRange(\"";
	ranges::copy(a, ostream_iterator<long>(cout, ", "));
	cout << "\") : " << strRange << endl;

	// copy_on_write_string();
	float f = 0xabcd;
	cout << "float f = 0xabcd: " << fixed << f << dec << endl;
	assert(_atod("1234") == 1234);
	assert(_atod("0xabcd") == 0xabcd);
	assert(_atoull("11011110101011011011111011101111", 2) == 0xdeadbeef);
	// assert(_atof("1234.5678") == 1234.5678);
	cout << "atof(\"1234\"): " << _atod("1234") << endl;
	cout << "atoi(\"0xabcd\"): " << hex << _atod("0xabcd", 10) << dec << endl;
	cout << "atoi(\"11011110101011011011111011101111\"): " << hex << _atoull("11011110101011011011111011101111", 2) << dec << endl; // 0xDeadBeef
	cout << "atof(\"1234.5678\"): " << _atod("1234.5678") << endl;
	assert(_atoi("     -42") == -42);
	assert(_atoi("-0-") == 0);
	assert(_atoi("-+123-") == 0);
	assert(_atoi("-123 456") == -123);
	assert(_atoi("-123 Hello") == -123);
	assert(_atoi("Hello -123") == 0);
	assert(_atoi("+123 456") == 123);
	assert(_atoi("+123 Hello") == 123);
	double d;
	assert(round(1234.5678, 1) == 1234.6);
	assert(round(1234.5678, 2) == 1234.57);
	assert(round(1234.5678, 3) == 1234.568);
	assert(round(1234.5678, 4) == 1234.5678);
	d = round(1234.5678, 1);
	d = round(1234.5678, 2);
	d = round(1234.5678, 3);
	d = round(1234.5678, 4);
	assert(round(0.1234, 1) == 0.1);
	assert(round(0.1234, 2) == 0.12);
	assert(round(0.1234, 3) == 0.123);
	assert(round(0.1234, 4) == 0.1234);
	d = round(0.1234, 1);
	d = round(0.1234, 2);
	d = round(0.1234, 3);
	d = round(0.1234, 4);
	assert(SequenceSum(0) == 0);
	assert(SequenceSum(1) == 1);
	assert(SequenceSum(5) == 15);
	uint64_t factorialResult = Factorial<uint64_t>(26);
	cout << "26!: " << setiosflags(ios::fixed) << factorialResult << endl;
	assert(FactorialTrailingZeroesCount(10) == 2);
	assert(FactorialTrailingZeroesCount(25) == 6);
	assert(FactorialTrailingZeroesCount(26) == 6);
	cout << "10!: " << Factorial<uint64_t>(10) << " has " << FactorialTrailingZeroesCount(10) << " trailing zeroes." << endl;
	cout << "25!: " << Factorial<uint64_t>(25) << " has " << FactorialTrailingZeroesCount(25) << " trailing zeroes." << endl;
	cout << "26!: " << Factorial<uint64_t>(26) << " has " << FactorialTrailingZeroesCount(26) << " trailing zeroes." << endl;
	data.clear();
	str = "abc";
	a.clear();
	a.resize(25);
	ranges::generate(a.begin(), a.begin() + 10, [n = 0]() mutable
		{ return n++; });
	ranges::generate(a.begin() + 10, a.end(), [n = 5]() mutable
		{ return n++; });
	b.clear();
	FindDistinct(a, b);
	assert(b.size() == 20);

	udata.clear();
	udata1.clear();
	FindPrimes(20, udata); // Find prime numbers 0 to 20: 2,3,5,7,11,13,17,19
	assert(udata.size() == 8);
	udata.clear();
	udata1.clear();
	udata = { 15, 10, 3 };
	udata1 = { 75, 30, 5 };
	assert(CommonPrimeDivisors(udata, udata1) == 1);
	udata.clear();
	udata1.clear();
	udata = { 7, 17, 5, 3 };
	udata1 = { 7, 11, 5, 2 };
	assert(CommonPrimeDivisors(udata, udata1) == 2);

	assert(!IsPrime(1));
	assert(IsPrime(2));
	assert(IsPrime(3));
	assert(!IsPrime(4));
	assert(IsPrime(5));
	assert(!IsPrime(6));
	assert(IsPrime(7));
	assert(!IsPrime(8));
	assert(!IsPrime(9));
	assert(!IsPrime(10));
	a.clear();
	b.clear();
	big_unsigned_int.clear();
	big_unsigned_int = { 1, 2, 1, 2 };
	uint64_t findMaxResult = range.FindMax(big_unsigned_int);
	assert(findMaxResult == 9);

	big_unsigned_int.clear();
	big_unsigned_int = { 2, 3, 3, 2 };
	findMaxResult = range.FindMax(big_unsigned_int);
	assert(findMaxResult == 36);

	str = "     Hello     World!!!     ";
	assert(str.size() == 28);
	cout << str << " size: " << str.size();
	trim(str);
	// assert(str == "Hello     World!!!");
	cout << " trim(str): |" << str << "| size: " << str.size() << endl;

	a.clear();
	cout << "minDiffPairs(): " << endl;
	a = { 1, 2, 3, 4, 5, 6 };
	assert(minDiffPairs(a, 0) == 3);
	a.clear();
	a = { 1, 2, 3, 4, 5, 6 };
	assert(minDiffPairs(a, 1) == 3);
	a.clear();
	a = { 1, 2, 3, 4, 5, 6 };
	assert(minDiffPairs(a, 2) == 2);
	a.clear();
	a = { 6, 5, 4, 3, 2, 1 };
	assert(minDiffPairs(a, 3) == 3);
	cout << endl;
	a.clear();
	a = { 3, 5, 1, 6, 2, 4 };
	assert(minDiffPairs(a, 4) == 2);
	assert(minDiffPairs(a, 5) == 1);
	a.clear();
	a = { 1, 1, 1, 5, 5, 5, 5 };
	assert(minDiffPairs(a, 4) == 3);
	a.clear();
	a = { 1, 1 };
	assert(minDiffPairs(a, 1) == 0);
	// Tower of Hanoi
	cout << "Tower Of Hanoi recursive solution: " << endl;
	vector<shared_ptr<Tower<size_t>>> towers;
	for (i = 0; i < 3; i++)
		towers.push_back(make_shared<Tower<size_t>>(i));
	for (i = 2; i > 0; i--) // Smallest disk is "1"
	{
		towers[0]->Add(i);
		assert(towers[0]->TopDisc() == i);
	}
	assert(!towers[0]->isEmpty());
	assert(towers[1]->isEmpty());
	assert(towers[2]->isEmpty());
	size = towers[0]->MoveDiscs(2, towers[2], towers[1]);
	assert(size == 3); // size = #moves
	assert(towers[0]->isEmpty());
	assert(towers[1]->isEmpty());
	assert(!towers[2]->isEmpty());
	for (i = 0; i < 3; i++)
		towers[i]->Reset();
	for (i = 10; i > 0; i--) // Smallest disk is "1"
	{
		towers[0]->Add(i);
		assert(towers[0]->TopDisc() == i);
	}
	assert(!towers[0]->isEmpty());
	assert(towers[1]->isEmpty());
	assert(towers[2]->isEmpty());
	cout << "Tower 0 before move: " << endl;
	towers[0]->print();
	size = towers[0]->MoveDiscs(5, towers[2], towers[1]);
	cout << "Tower 0,1,2 after " << size << " moves: " << endl;
	towers[0]->print();
	assert(towers[0]->TopDisc() == 6);
	towers[1]->print();
	assert(towers[1]->TopDisc() == numeric_limits<size_t>::max());
	towers[2]->print();
	assert(towers[2]->TopDisc() == 1);
	towers.clear();
	// Test 2D memory buffer allocation
	cout << "Test 2D memory buffer allocation...." << endl;
	long** my2Dbuffer = my2DAlloc(10, 10);
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			my2Dbuffer[i][j] = i * 10 + j;
	// cout << "Content of 2D buffer: " << endl;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			// cout << my2Dbuffer[i][j] << " ";
			assert(my2Dbuffer[i][j] == i * 10 + j);
		}
		// cout << endl;
	}
	free(my2Dbuffer);
	// Test 3D memory buffer allocation
	cout << "Test 3D memory buffer allocation...." << endl;
	long*** my3Dbuffer = my3DAlloc(10, 10, 10);
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			for (size_t k = 0; k < 10; k++)
				my3Dbuffer[i][j][k] = i * 10 + j * 10 + k;
	// cout << "Content of 3D buffer: " << endl;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
			for (size_t k = 0; k < 10; k++)
			{
				// cout << my3Dbuffer[i][j][k] << " ";
				assert(my3Dbuffer[i][j][k] == i * 10 + j * 10 + k);
			}
		// cout << endl;
	}
	free(my3Dbuffer);

	for (i = 0; i < 64; i++)
		mask |= ((uint64_t)1 << i);
	cout << "mask: " << hex << mask << dec << endl
		<< endl;

	cout << "Test shuffle deck of cards: " << endl;
	vector<long> cards(52), result;
	ranges::iota(cards.begin(), cards.end(), 0);
	shuffleCards(cards);
	for (i = 0; i < 52; i++)
	{
		if (i && !(i % 13))
			cout << endl;
		cout << cards[i] << " ";
	}
	cout << endl
		<< endl;
	cout << "Randomly picking m integers out of an array: " << endl;
	randomSubset(cards, 13, result);
	assert(result.size() == 13);
	ranges::copy(result, ostream_iterator<long>(cout, " "));
	cout << endl;

	// Test priority queue
	for (i = -10; i < 10; i++)
	{
		maxHeap.push(i);
		minHeap.push(i);
	}
	for (long i = 9; !maxHeap.empty(); i--)
	{
		// cout << maxHeap.top() << " ";
		assert(maxHeap.top() == i);
		maxHeap.pop();
	}
	for (long i = -10; !minHeap.empty(); i++)
	{
		// cout << minHeap.top() << " ";
		assert(minHeap.top() == i);
		minHeap.pop();
	}
	a.clear();
	b.clear();
	a.push_back(123);
	long sum = parallel_reduce(
		blocked_range<size_t>(0, a.size()), 0,
		[&](tbb::blocked_range<size_t> const& r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		plus<long>());
	assert(sum == 123);

	a.clear();
	b.clear();
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	sum = parallel_reduce(
		blocked_range<size_t>(2, a.size()), 0,
		[&](tbb::blocked_range<size_t> const& r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		plus<long>());
	assert(sum == 3);

	a.clear();
	b.clear();
	a.resize(10);
	ranges::generate(a, [n = 1]() mutable
		{ return n++; });
	sum = parallel_reduce(
		blocked_range<size_t>(0, a.size()), 0,
		[&](tbb::blocked_range<size_t> const& r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		plus<long>());
	assert(sum == 55);
	a.clear();
	b.clear();
	a = { 1, 7, 15, 29, 11, 9 };
	EqualAverageDivide(a, b);
	assert(b.size() == 2);
	cout << "Left part: ";
	sum = parallel_reduce(
		blocked_range<size_t>(0, b.size()), 0,
		[&](tbb::blocked_range<size_t> const& r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += b[i];
			return running_total;
		},
		plus<long>());
	ranges::copy(b, ostream_iterator<long>(cout, " "));
	assert(sum == 24);
	cout << "sum: " << sum << endl;

	vector<char> cData1{ 1, 2, 3 }, cData2{ 4, 5, 6 };
	vector<char> sumResult = AddVectors(cData1, cData2);
	assert(sumResult.size() == 3);
	assert(sumResult[0] == 5);
	assert(sumResult[1] == 7);
	assert(sumResult[2] == 9);
	cData2.push_back(7);
	sumResult = AddVectors(cData1, cData2);
	assert(sumResult.size() == 4);
	assert(sumResult[0] == 4);
	assert(sumResult[1] == 6);
	assert(sumResult[2] == 9);
	assert(sumResult[3] == 0);

	cData1.clear();
	cData2.clear();
	cData1 = { 9, 8, 7 };
	cData2 = { 6, 5, 4 };
	sumResult = AddVectors(cData1, cData2);
	assert(sumResult.size() == 4);
	assert(sumResult[0] == 1);
	assert(sumResult[1] == 6);
	assert(sumResult[2] == 4);
	assert(sumResult[3] == 1);
	// Test JSONValidation
	assert(JSONValidation("{a:b}"));
	assert(JSONValidation("{a:b, c:d}"));
	assert(JSONValidation("{a:b,c:{e:f}}"));
	assert(JSONValidation("{a:b,c:{e:{f:g}}}"));
	assert(!JSONValidation("{a}"));
	assert(!JSONValidation("{{a}}"));
	assert(match(string("abba"), string("redbluebluered")));
	assert(match(string("aaaa"), string("asdasdasdasd")));
	assert(match(string("aabb"), string("xyzxyzabcabc")));
	assert(match(string("abab"), string("xyzabcxyzabc")));
	assert(!match(string("aabb"), string("xyzabcxyzabc")));
	assert(!match(string("abba"), string("xyzabcxyzabc")));
	assert(!match(string("aaaa"), string("xyzabcxyzabc")));

	stringset.clear();
	stringset = { "cdf", "too", "hgfdt", "paa" };
	stringset1.clear();
	FindPattern("abc", stringset, stringset1);
	assert(stringset1.size() == 1);
	assert(stringset1.count("cdf"));
	stringset1.clear();
	FindPattern("acc", stringset, stringset1);
	assert(stringset1.size() == 2);
	assert(stringset1.count("too"));
	assert(stringset1.count("paa"));
	str = "1024";
	str1 = "2048";
	istringstream iss1(str), iss2(str1);
	cout << iss2.str() << " - " << iss1.str() << " = " << subtract(iss2, iss1) << endl;

	// N-Gram test
	set<string> ngrams = intersectionNgram(string("This is a dog"), string("This is a cat"), 2);
	assert(ngrams.size() == 2);
	assert(ngrams.count("This is"));
	assert(ngrams.count("is a"));
	ngrams = intersectionNgram(string("This is a dog"), string("This is a cat"), 3);
	assert(ngrams.size() == 1);
	assert(ngrams.count("This is a"));
	ngrams = intersectionNgram(string("This is a dog"), string("This is a cat"), 4);
	assert(ngrams.empty());
	cout << endl;
	data.clear();
	data.resize(4);
	ranges::generate(data, [n = 1]() mutable
		{ return n++; });
	data1.clear();
	data1 = Increment(data);
	assert(data1[0] == 1);
	assert(data1[1] == 2);
	assert(data1[2] == 3);
	assert(data1[3] == 5);

	data.clear();
	data1.clear();
	data = { 9, 9, 9, 9 };
	data1 = Increment(data);
	assert(data1[0] == 1);
	assert(data1[1] == 0);
	assert(data1[2] == 0);
	assert(data1[3] == 0);
	assert(data1[4] == 0);

	void* addr = alignedMalloc(1000, 64);
	assert(addr);
	int alignment = (unsigned long)addr % (64 / 8);
	assert(!alignment);
	memset(addr, 'a', 1000);
	alignedFree(&addr);
	assert(!addr);

	addr = alignedMalloc(1000, 32);
	assert(addr);
	alignment = (unsigned long)addr % (32 / 8);
	assert(!alignment);
	alignedFree(&addr);
	assert(!addr);

	sortData.clear();
	sortData = { 1, 2, 3, 10, 25, 26, 30, 31, 32, 33 };
	strings = numbersegments(sortData);
	ranges::copy(strings, ostream_iterator<string>(cout, ","));
	cout << endl;
	cout << dec;
	assert(KthNumberWith357PrimeFactors(1) == 1);
	assert(KthNumberWith357PrimeFactors(2) == 3);
	assert(KthNumberWith357PrimeFactors(3) == 5);
	assert(KthNumberWith357PrimeFactors(4) == 7);
	assert(KthNumberWith357PrimeFactors(5) == 9);
	assert(KthNumberWith357PrimeFactors(6) == 15);
	assert(KthNumberWith357PrimeFactors(7) == 21);
	assert(KthNumberWith357PrimeFactors(8) == 25);
	assert(KthNumberWith357PrimeFactors(9) == 27);
	assert(KthNumberWith357PrimeFactors(10) == 35);
	a.clear();
	a = { 9, 918, 917 };
	assert(concat(a) == 9918917);
	a.clear();
	a = { 1, 112, 113 };
	assert(concat(a) == 1131121);
	a.clear();
	a = { 901, 9015 };
	// 9019015, 9015901
	assert(concat(a) == 9019015);
	strings.clear();
	strings = { "ABCW", "BAZ", "FOO", "BAR", "XTFN", "ABCDEF" };
	assert(24 == MaxLengths(strings));
	Square square1(0, 0, 10, 10), square2(5, 5, 10, 10);
	assert(square1.IsOverlappig(square2));
	assert(square2.IsOverlappig(square1));
	square2.SetCoordinates(10, 10);
	assert(square1.IsOverlappig(square2));
	assert(square2.IsOverlappig(square1));
	square2.SetCoordinates(-10, -10);
	assert(square1.IsOverlappig(square2));
	assert(square2.IsOverlappig(square1));
	square2.SetCoordinates(11, 11);
	assert(!square1.IsOverlappig(square2));
	assert(!square2.IsOverlappig(square1));
	square2.SetCoordinates(5, 5);
	square1.SetWidth(4);
	square2.SetHeight(4);
	assert(!square1.IsOverlappig(square2));
	assert(!square2.IsOverlappig(square1));
	assert(ChocolatesByNumbers(1, 2) == 1);
	assert(ChocolatesByNumbers(10, 1) == 10);
	assert(ChocolatesByNumbers(10, 2) == 5);
	assert(ChocolatesByNumbers(10, 4) == 5);
	// ChocolatesByNumbers(415633212, 234332);
	a.clear();
	a.push_back(3); // 3
	a.push_back(4); // 2
	a.push_back(5); // 1
	a.push_back(5); // 2
	a.push_back(2); // 1
	assert(CountDistinctSlices(a) == 9);
	a.clear();
	a.push_back(0);						  // 5
	a.push_back(1);						  // 4
	a.push_back(2);						  // 3
	a.push_back(3);						  // 2
	a.push_back(4);						  // 1
	assert(CountDistinctSlices(a) == 15); // 5 + 4 + 3
	a.clear();
	a.push_back(1);						 // 5
	a.push_back(1);						 // 4
	a.push_back(1);						 // 3
	a.push_back(1);						 // 2
	a.push_back(1);						 // 1
	assert(CountDistinctSlices(a) == 5); // 5 + 4 + 3
	a.clear();
	a.push_back(1);						 // 2
	a.push_back(2);						 // 1
	a.push_back(2);						 // 2
	a.push_back(3);						 // 1
	a.push_back(3);						 // 2
	a.push_back(4);						 // 1
	assert(CountDistinctSlices(a) == 9); // 5 + 4 + 3
	a.clear();
	a.push_back(1);						  // 2
	a.push_back(2);						  // 1
	a.push_back(2);						  // 3
	a.push_back(3);						  // 2
	a.push_back(4);						  // 1
	a.push_back(4);						  // 1
	assert(CountDistinctSlices(a) == 10); // 5 + 4 + 3
	a.clear();
	a.push_back(1);						  // 1
	a.push_back(1);						  // 4
	a.push_back(2);						  // 3
	a.push_back(3);						  // 2
	a.push_back(4);						  // 1
	a.push_back(4);						  // 1
	assert(CountDistinctSlices(a) == 12); // 5 + 4 + 3
	a.clear();
	a.push_back(1);						  // 2
	a.push_back(2);						  // 1
	a.push_back(1);						  // 3
	a.push_back(2);						  // 2
	a.push_back(4);						  // 1
	a.push_back(4);						  // 1
	assert(CountDistinctSlices(a) == 10); // 5 + 4 + 3
	a.clear();
	a.push_back(1);						  // 2
	a.push_back(2);						  // 1
	a.push_back(3);						  // 3
	a.push_back(4);						  // 2
	a.push_back(5);						  // 1
	a.push_back(6);						  // 1
	assert(CountDistinctSlices(a) == 21); // 5 + 4 + 3
	a.clear();
	a = { 10, 2, 5, 1, 8, 12 };
	assert(CountTriangles(a) == 4);
	assert(decimal_to_binary(0) == "0");
	assert(binary_to_decimal(string("1010")) == 10);
	cout << 0xdeadbeef << endl;
	assert(binary_to_decimal(string("1101 1110 1010 1101 1011 1110 1110 1111")) == 0xffffffffdeadbeef);
	a.clear();
	a = { 1, 5, 2, -2 };
	assert(MinAbsSum(a) == 0);
	a.clear();
	a = { 2, 2, 1 };
	assert(MinAbsSum(a) == 1);
	PlayTreasureGame();
	assert(countPaths(2, 2, 1, 1, 2) == 2);		   // 2
	assert(countPaths(2, 2, 1, 1, 3) == 0);		   // 0
	assert(countPaths(2, 2, 1, 1, 4) == 8);		   // 8
	assert(countPaths(5, 5, 4, 4, 5) == 0);		   // 0
	assert(countPaths(5, 8, 4, 6, 10) == 210);	   // 210
	assert(countPaths(5, 8, 4, 6, 16) == 2840838); // 2840838
	assert(countPaths(5, 8, 4, 6, 17) == 0);	   // 0
	// countPaths(5, 8, 4, 6, 18); too big
	// countPaths(5, 8, 4, 6, 20); too big
	// countPaths(5, 8, 4, 6, 21); too big
	/*
		/------(f)<-   /--\
		v   ---/     \ v   |
		(a) /   ----->(e)---/
		| /   /       ^
		vv    |      /
		(b)-->(c)-->(d)-->(g)->(h)
		\         ^
		-------/
	*/
	shared_ptr<Node<string>> nodeA = make_shared<Node<string>>("a");
	shared_ptr<Node<string>> nodeB = make_shared<Node<string>>("b");
	shared_ptr<Node<string>> nodeC = make_shared<Node<string>>("c");
	shared_ptr<Node<string>> nodeD = make_shared<Node<string>>("d");
	shared_ptr<Node<string>> nodeE = make_shared<Node<string>>("e");
	shared_ptr<Node<string>> nodeF = make_shared<Node<string>>("f");
	shared_ptr<Node<string>> nodeG = make_shared<Node<string>>("g");
	shared_ptr<Node<string>> nodeH = make_shared<Node<string>>("h");
	// The edges form shared_ptr cycles (A->B->C->E->F->A, E->E). They are broken with ClearLinks() after use below.
	nodeA->AddAdjacent(nodeB);
	nodeB->AddAdjacent(nodeC);
	nodeC->AddAdjacent(nodeE);
	nodeC->AddAdjacent(nodeD);
	nodeD->AddAdjacent(nodeE);
	nodeE->AddAdjacent(nodeF);
	nodeE->AddAdjacent(nodeE); // Self-referencing
	nodeF->AddAdjacent(nodeB);
	nodeF->AddAdjacent(nodeA);
	nodeD->AddAdjacent(nodeG);
	nodeD->AddAdjacent(nodeH);
	nodeG->AddAdjacent(nodeH);
	vector<shared_ptr<Node<string>>> path = shortest_cycle_path(nodeA);
	cout << "Shortest Cycle Path of node A: " << nodeA->Item() << " ";
	for (vector<shared_ptr<Node<string>>>::iterator it = path.begin(); it != path.end(); it++)
		cout << (*it)->Item() << " ";
	cout << endl;
	path = shortest_cycle_path(nodeB);
	cout << "Shortest Cycle Path of node B: " << nodeB->Item() << " ";
	for (vector<shared_ptr<Node<string>>>::iterator it = path.begin(); it != path.end(); it++)
		cout << (*it)->Item() << " ";
	cout << endl;
	path = shortest_cycle_path(nodeE);
	cout << "Shortest Cycle Path of node E: " << nodeE->Item() << " ";
	for (vector<shared_ptr<Node<string>>>::iterator it = path.begin(); it != path.end(); it++)
		cout << (*it)->Item() << " ";
	cout << endl;
	path = shortest_cycle_path(nodeG);
	cout << "Shortest Cycle Path of node G: " << nodeG->Item() << " ";
	for (vector<shared_ptr<Node<string>>>::iterator it = path.begin(); it != path.end(); it++)
		cout << (*it)->Item() << " ";
	cout << endl;
	path.clear();
	// Break the edge cycles first. reset() alone only drops these local references. Cycles must be broken with ClearLinks() before the nodes go out of scope.
	nodeA->ClearLinks();
	nodeB->ClearLinks();
	nodeC->ClearLinks();
	nodeD->ClearLinks();
	nodeE->ClearLinks();
	nodeF->ClearLinks();
	nodeG->ClearLinks();
	nodeH->ClearLinks();
	nodeA.reset();
	nodeB.reset();
	nodeC.reset();
	nodeD.reset();
	nodeE.reset();
	nodeF.reset();
	nodeG.reset();
	nodeH.reset();
	data.clear();
	data = { 1, 0, 1, 1, 0, 0, 0 };
	assert(findMinFlip(data) == 1);
	data.clear();
	data = { 0, 0, 0, 0, 1 };
	assert(findMinFlip(data) == 2);
	cgrid1.clear();
	cgrid1 = {
		{ 'R', 'G', 'R', 'B' },
		{ 'R', 'Y', 'G', 'R' },
		{ 'G', 'B', 'Y', 'Y' },
		{ 'Y', 'G', 'B', 'G' },
		{ 'B', 'R', 'Y', 'B' },
	};
	assert(IsValidMatrix(cgrid1));
	cgrid1.clear();
	cgrid1 = {
		{ 'R', 'G', 'R', 'B' },
		{ 'R', 'Y', 'G', 'R' },
		{ 'G', 'B', 'B', 'B' },
		{ 'Y', 'G', 'B', 'G' },
		{ 'B', 'R', 'Y', 'B' },
	};
	assert(!IsValidMatrix(cgrid1));
	cgrid1.clear();
	cgrid1 = {
		{ 'R', 'G', 'R', 'B' },
		{ 'R', 'Y', 'G', 'R' },
		{ 'G', 'B', 'G', 'Y' },
		{ 'Y', 'G', 'G', 'G' },
		{ 'B', 'R', 'Y', 'B' },
	};
	assert(!IsValidMatrix(cgrid1));
	a.clear();
	a = { 13, 2, 5 };
	stringset.clear();
	// assert(ZigZagEscape(a, stringset) == 7);
	assert(ZigZagEscape(a) == 7);
	a.clear();
	a = { 4, 6, 2, 1, 5 };
	stringset.clear();
	// assert(ZigZagEscape(a, stringset) == 23);
	assert(ZigZagEscape(a) == 23);
	a.clear();
	a = { 6, 3, 1, 4, 2, 5 };
	stringset.clear();
	// assert(ZigZagEscape(a, stringset) == 41);
	// assert(ZigZagEscape(a) == 41); Unfinished work!
	cpluplus17();
	FunctionObject functionObject;
	map<string, size_t> myKeyCount;
	myKeyCount["Hello World!!!"]++;
	assert(myKeyCount["Hello World!!!"] == 1);

	map<size_t, string> myStringCount;
	myStringCount[1].append("Hello ");
	myStringCount[1].append("World!!!");
	assert(myStringCount[1] == "Hello World!!!");
	map<int, char> mymap;
	mymap[123] = 'A';
	assert(mymap.size() == 1);
	assert(mymap[123] == 'A');
	map<int, char>::const_iterator mapIt;
	mymap.emplace(0, 'A');
	mymap.emplace(1, 'A');
	mymap.emplace(2, 'A');
	mymap.emplace(4, 'B');
	mymap.emplace(5, 'B');
	mapIt = mymap.upper_bound(3);
	assert(mapIt->first == 4);
	assert((--mapIt)->first == 2);
	mymap.emplace(3, 'C');
	map<size_t, vector<size_t>> mapOfVectors;
	mapOfVectors[1].push_back(2);
	assert(!mapOfVectors.empty());
	assert(1 == mapOfVectors.size());
	cout << numeric_limits<int>::lowest() << endl;
	IntervalMap<int, char> imap(0);
	imap.emplace(0, 2, 'A'); // [0,1]: 'A'
	imap.emplace(2, 4, 'A'); // [2,3]: 'B'
	imap.emplace(4, 6, 'A'); // [4,5]: 'C'
	assert(imap.size() == 5);
	assert(imap[0] == 'A');
	assert(imap[1] == 'A');
	assert(imap[2] == 'A');
	assert(imap[3] == 'A');
	assert(imap[4] == 'A');
	assert(imap[5] == 'A');
	imap.print();
	IntervalMap<int, char> imap1;
	imap1.emplace(0, 2, 'A'); // [0,1]: 'A'
	imap1.emplace(4, 6, 'A'); // [4,5]: 'A'
	imap1.emplace(2, 4, 'B'); // [2,3]: 'B'
	assert(imap1.size() == 7);
	assert(imap1[0] == 'A');
	assert(imap1[1] == 'A');
	assert(imap1[2] == 'B');
	assert(imap1[3] == 'B');
	assert(imap1[4] == 'A');
	assert(imap1[5] == 'A');
	imap1.print();
	IntervalMap<int, char> imap2;
	imap2.emplace(0, 2, 'A'); // [0,1]: 'A'
	imap2.emplace(4, 6, 'A'); // [4,5]: 'A'
	imap2.emplace(2, 4, 'B'); // [2,3]: 'B'
	assert(imap2.size() == 7);
	assert(imap2[0] == 'A');
	assert(imap2[1] == 'A');
	assert(imap2[2] == 'B');
	assert(imap2[3] == 'B');
	assert(imap2[4] == 'A');
	assert(imap2[5] == 'A');
	imap2.print();
	imap2.emplace(2, 4, 'A'); // [2,3]: 'A'
	assert(imap2.size() == 7);
	assert(imap2[2] == 'B'); // XXX
	assert(imap2[3] == 'B'); // XXX
	imap2.print();
	imap2.emplace(3, 4, 'A'); // [2,3]: 'A'
	assert(imap2.size() == 7);
	assert(imap2[2] == 'B'); // XXX
	assert(imap2[3] == 'A'); // XXX
	imap2.print();
	IntervalMap<int, char> imap3;
	imap3.emplace(0, 2, 'A'); // [0,1]: 'A'
	imap3.emplace(4, 6, 'A'); // [4,5]: 'A'
	assert(imap3.size() == 5);
	assert(imap3[4] == 'A');
	assert(imap3[5] == 'A');
	imap3.emplace(2, 6, 'B'); // [2,3,4,5]: 'B'
	assert(imap3.size() == 7);
	assert(imap3[2] == 'B');
	assert(imap3[3] == 'B');
	assert(imap3[4] == 'B');
	assert(imap3[5] == 'B');
	IntervalMap<size_t, char> imap4;
	imap4.emplace(0, 2, 'A'); // [0,1]: 'A'
	imap4.emplace(4, 6, 'A'); // [4,5]: 'A'
	imap4.emplace(2, 4, 'A'); // [2,3]: 'A'
	assert(imap4.size() == 4);
	assert(imap4[0] == 'A');
	assert(imap4[1] == 'A');
	assert(imap4[4] == 'A');
	assert(imap4[5] == 'A');
	imap4.print();
	IntervalMap<size_t, char> imap5;
	imap5.emplace(2, 0, 'A');
	imap5.emplace(4, 6, 'A'); // [4,5]: 'A'
	imap5.emplace(2, 4, 'A'); // [2,3]: 'A'
	assert(imap5.size() == 5);
	assert(imap5[2] == 'A');
	assert(imap5[3] == 'A');
	assert(imap5[4] == 'A');
	assert(imap5[5] == 'A');
	imap5.print();
	IntervalMap<size_t, char> imap6;
	imap6.emplace(2, 0, 'A');
	imap6.emplace(2, 4, 'A'); // [2,3]: 'A'
	imap6.emplace(4, 6, 'A'); // [4,5]: 'A'
	assert(imap6.size() == 3);
	assert(imap6[2] == 'A');
	assert(imap6[3] == 'A');
	assert(imap6[4] == 'A');
	assert(imap6[5] == 'A');
	imap6.print();
	IntervalMap<size_t, string> imap7;
	imap7.emplace(5, 8, "5-8"); // [5,6,7]: 'A'
	imap7.print();
	assert(imap7.size() == 4); // + numeric_limits<int>::lowest() entry
	assert(imap7[4].empty());
	assert(imap7[8] == "5-8");

	a.clear();
	a = { -3, 1, 2, -2, 5, 6 };
	assert(MaxProductOfThree(a) == 60);
	assert(binary_gap(9) == 2);
	assert(binary_gap(32) == 0);
	assert(binary_gap(529) == 4);
	data.clear();
	data.resize(5);
	ranges::generate(data, [i = 0]() mutable
		{ return i++; });
/* 0 1 2 3 4 => 2 3 4 0 1 (Rotate 3)
 */
	RotateRightArray(data, 3);
	for (size_t i = 0, j = 2; i < data.size(); i++, j = ++j % data.size())
		assert(data[i] == j);
	data.clear();
	data.resize(5);
	ranges::generate(data, [i = 0]() mutable
		{ return i++; });
/* 0 1 2 3 4 => 2 3 4 0 1 (Rotate 13)
 */
	RotateRightArray(data, 13);
	for (size_t i = 0, j = 2; i < data.size(); i++, j = ++j % data.size())
		assert(data[i] == j);
	assert(CountDiv(6, 11, 2) == 3);
	assert(CountDiv(6, 11, 6) == 1);
	// assert(CountDiv(101, 123450000, 10000) == 12345);
	assert(CountDiv(0, 2000000000, 2000000000) == 2);
	assert(CountDiv(0, numeric_limits<int>::max(), numeric_limits<int>::max()) == 2);
	a.clear();
	a = { 1, 2, 3, 4, 5, 6, 7, 8 };
	ranges::rotate(a.begin() + 2, a.begin() + 4, a.begin() + 5);
	b = { 1, 2, 5, 3, 4, 6, 7, 8 };
	assert(a == b);
	str = "if man was meant to stay on the ground god would have given us roots";
	assert(encryption(str) == "imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau");
	a.clear();
	a = { 3, 1, 5, 4, 2 };
	assert(CalculateMedian(a) == 3);
	a.clear();
	a = { 3, 1, 5, 4, 2, 6 };
	assert(CalculateMedian(a) == 3);
	assert(TimeInWords(5, 47) == "thirteen minutes to six");
	assert(TimeInWords(12, 29) == "twenty nine minutes past twelve");
	assert(TimeInWords(6, 30) == "half past six");
	assert(TimeInWords(1, 1) == "one minute past one");
	udata.clear();
	assert(substrings(string("123")) == 164);
	assert(substrings(string("1234")) == 1670);
	assert(substrings(string("972698438521")) == 445677619);
	assert(FindSubsequenceRecursive(string("1221"), string("12")) == 2);
	assert(FindSubsequenceRecursive(string("1234"), string("56")) == 0);
	assert(FindSubsequenceRecursive(string("kkkkkkz"), string("kkkk")) == 15);
	strings.clear();
	a.clear();
	a = diffWaysToCompute("2-1-1");
	assert(!a.empty());
	assert(a.size() == 2);
	a.clear();
	a = diffWaysToCompute("2*3-4*5");
	assert(!a.empty());
	assert(a.size() == 5);
	a.clear();
	a = { 1, 3, 5 };
	ListRangeSum<long> listSum(a);
	assert(listSum.Sum(0, 2) == 9);
	listSum.Update(1, 2);
	assert(listSum.Sum(0, 2) == 8);
	a.clear();
	a = { -1 };
	ListRangeSum<long> listSum1(a);
	assert(listSum1.Sum(0, 0) == -1);
	listSum1.Update(0, 1);
	assert(listSum1.Sum(0, 0) == 1);
	assert(fizzBuzz(3) == vector<string>({ "1", "2", "Fizz" }));
	assert(fizzBuzz(5) == vector<string>({ "1", "2", "Fizz", "4", "Buzz" }));
	assert(fizzBuzz(10) == vector<string>({ "1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz" }));
	assert(fizzBuzz(15) == vector<string>({ "1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz" }));
	udata.clear();
	udata1.clear();
	udata1 = { 123, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 456 };
	ranges::copy(GenerateSequence(0, 10), back_inserter(udata));
	assert(udata1 == udata);
	udata.clear();
	udata1.clear();
	udata1 = { 123, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 456 };
	ranges::copy(Generate2Sequence(0, 10, 100, 110), back_inserter(udata));
	assert(udata1 == udata);
	multimap<int, string> mmap = { { 123, "123" },{ 456, "456" },{ 123, "789" } };
	for (multimap<int, string>::iterator it = mmap.begin(); it != mmap.end(); it++)
		cout << it->first << ": " << it->second << endl;
	Dijkstra<string> dijkstra;
	strings.clear();
	strings = { "San Francisco", "Los Angeles", "Dallas", "New York", "Chicago" };
	dijkstra.AddVertices(strings);
	dijkstra.AddUndirectedEdge("San Francisco", "Los Angeles", 347);
	dijkstra.AddUndirectedEdge("San Francisco", "Dallas", 1480);
	dijkstra.AddUndirectedEdge("San Francisco", "Chicago", 1853);
	dijkstra.AddUndirectedEdge("Los Angeles", "Dallas", 1237);
	dijkstra.AddUndirectedEdge("Dallas", "Chicago", 802);
	dijkstra.AddUndirectedEdge("Dallas", "New York", 1370);
	dijkstra.AddUndirectedEdge("Chicago", "New York", 712);
	vector<shared_ptr<DVertex<string>>> dijkstraResult;
	assert(dijkstra.ShortestPath("San Francisco", "New York", dijkstraResult) == 2565);
	assert(dijkstra.ShortestPathStateless("San Francisco", "New York", dijkstraResult) == 2565);
	assert(!dijkstraResult.empty());
	for (vector<shared_ptr<DVertex<string>>>::const_iterator it = dijkstraResult.begin(); it != dijkstraResult.end(); it++)
		cout << (*it)->Value() << " -> ";
	cout << endl;
	uset1.clear();
	uset1.erase(123);
	udata.clear();
	grid1.clear();
	a.clear();
	/*
	 * modular multiplication overflows when long is 32 bits, which it is under MSVC on Windows, even in x64 builds.
	 * Why it overflows. ((x % modulo) * (y % modulo)) % modulo multiplies two values that can each be close to 1e9+7.
	 * That product needs up to about 60 bits, so in a 32-bit long it overflows before the final % modulo is applied.
	 * The true product of 3..14 is 43,589,145,600, which is already past 2^31.
	 * Why it is intermittent. Once overflow happens, the result depends on how the multiplications are grouped.
	 * fold_left always goes left to right, but parallel_reduce splits the range into chunks differently from run to run, depending on thread availability.
	 */
	const int64_t modulo = 1e9 + 7L;
	a = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	l = 1e9 + 7L;
	l1 = ranges::fold_left(a, 1l, [&modulo](int64_t x, int64_t y) -> int64_t
		{ return ((x % modulo) * (y % modulo)) % modulo; });
	l2 = parallel_reduce(
		blocked_range<int64_t>(0, a.size()), 1l /* Identity for Multiplication */,
		[&](tbb::blocked_range<int64_t> const& r, int64_t running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total = ((running_total % modulo) * (a[i] % modulo)) % modulo;
			return running_total;
		},
		[&modulo](int64_t x, int64_t y) -> int64_t
		{
			return ((x % modulo) * (y % modulo)) % modulo;
		});
	assert(l2 == l1);
	l2 = accumulate(a.begin(), a.end(), 1l, [&modulo](int64_t x, int64_t y) -> int64_t
		{ return ((x % modulo) * (y % modulo) % modulo); });
	assert(l2 == l1);
	// assert(MinimumSteps2HitTarget(1, 2, 1, 60) == 4);
	vector<size_t> cresult;
	// 11111111100, 1234567890, 9876543210
	arithmetic.NumberToVector(1234567890, udata);
	arithmetic.NumberToVector(9876543210, udata1);
	arithmetic.NumberVectorsSum(udata, udata1, cresult);
	assert(arithmetic.DigitsVectorToNumber(cresult) == 11111111100);
	// 168, 123, 45
	arithmetic.NumberToVector(123, udata);
	arithmetic.NumberToVector(45, udata1);
	arithmetic.NumberVectorsSum(udata, udata1, cresult);
	assert(arithmetic.DigitsVectorToNumber(cresult) == 168);
	// 56088, 123, 456
	str = "123";
	str1 = "456";
	assert(stringArithmetic.NumberStringMultiplication(str, str1) == "56088");
	arithmetic.NumberToVector(123, udata);
	arithmetic.NumberToVector(456, udata1);
	arithmetic.NumberVectorsMultiplication(udata, udata1, cresult);
	assert(arithmetic.DigitsVectorToNumber(cresult) == 56088);
	usetvec.clear();
	usetvec.emplace(vector<size_t>{1, 2, 3});
	assert(usetvec.size() == 1);
	usetvec.emplace(vector<size_t>{2, 1, 3});
	assert(usetvec.size() == 2);
	udata.clear();
	uset1.clear();
	uset1 = { 1, 2, 3 };
	ugrid = ulPermutation.RangePermutations(udata, uset1, 1, 1);
	for (vector<vector<size_t>>::const_iterator it = ugrid.begin(); it != ugrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	udata.clear();
	ugrid = ulPermutation.RangePermutations(udata, uset1, 2, 1);
	for (vector<vector<size_t>>::const_iterator it = ugrid.begin(); it != ugrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	udata.clear();
	ugrid = ulPermutation.RangePermutations(udata, uset1, 3, 1);
	for (vector<vector<size_t>>::const_iterator it = ugrid.begin(); it != ugrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	uset1.clear();
	uset2.clear();
	uset2 = { 1, 2, 3 };
	usetgrid = ulPermutation.RangeUniquePermutations(uset1, uset2, 1, 1);
	for (set<set<size_t>>::const_iterator it = usetgrid.begin(); it != usetgrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	uset1.clear();
	uset2.clear();
	uset2 = { 1, 2, 3 };
	usetgrid = ulPermutation.RangeUniquePermutations(uset1, uset2, 2, 1);
	for (set<set<size_t>>::const_iterator it = usetgrid.begin(); it != usetgrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	uset1.clear();
	uset2.clear();
	uset2 = { 1, 2, 3 };
	usetgrid = ulPermutation.RangeUniquePermutations(uset1, uset2, 3, 1);
	for (set<set<size_t>>::const_iterator it = usetgrid.begin(); it != usetgrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	a.clear();
	a = { 1 };
	//	assert(64 == FindConnectedComponents(a));
	a.clear();
	a = { 3 }; // 1 connected component of 2 nodes (0-1). 64 - 2 + 1 = 63
			 //	assert(63 == FindConnectedComponents(a));
	a.clear();
	a = { 3, 5 }; // [3]: 63, [5]: 63, [3,5]: 1 connected component of 3 nodes (0-1-2). 64-3+1=62. Total: 188
				//	assert(188 == FindConnectedComponents(a));
	a.clear();
	a = { 2, 5, 9 };
	// assert(504 == FindConnectedComponents(a));
	multiset<long> set{ 1, 1, 2, 2, 3, 3 }, set1{ 1, 1, 2, 3, 3 };
	set.extract(2);
	set.extract(4);
	assert(set1 == set);
	concurrent_set<size_t> cuset;
	size = 1;
	generate_n(inserter(cuset, cuset.begin()), 100, [&size]()
		{ return size++; });
	size = parallel_reduce(cuset.range(), 0 /* Identity for Addition */, [&](concurrent_set<size_t>::range_type const& r, size_t running_total)
		{
			for (auto it = r.begin(); it != r.end(); it++)
				running_total += *it;
			return running_total; }, plus<size_t>());
	assert(5050 == size);
	GCDExtendedEuclideanResult<long> gcdResult = larithmetic.gcd_extended(55, 121);
	cout << "gcd: " << gcdResult.gcd << ", x: " << gcdResult.x << ", y: " << gcdResult.y << endl;
	gcdResult = larithmetic.gcd_extended(91, 169);
	cout << "gcd: " << gcdResult.gcd << ", x: " << gcdResult.x << ", y: " << gcdResult.y << endl;
	ld = numeric_limits<long double>::max();
	assert(10771673641202074000000.0L < ld);
	cout << "10771673641202074000000.0L: " << 10771673641202074000000.0L << endl;
	// https://stackoverflow.com/questions/79602836/c-23-numeric-limitslong-doublemax-use-case
	cout << "long double radix: " << numeric_limits<long double>::radix << ", digits: " << numeric_limits<long double>::digits << ",  digits10: " << numeric_limits<long double>::digits10 << ", max_digits10: " << numeric_limits<long double>::max_digits10 << endl;
	cout << "int32_t radix: " << numeric_limits<int32_t>::radix << ", digits: " << numeric_limits<int32_t>::digits << ",  digits10: " << numeric_limits<int32_t>::digits10 << ", max_digits10: " << numeric_limits<int32_t>::max_digits10 << endl;
	feclearexcept(FE_INEXACT);
	ld = 1.0L;
	for (size_t i = 2; ld < numeric_limits<long double>::max(); i++)
	{
		ld1 = ld * i;
		if (fetestexcept(FE_INEXACT))
		{
			cout << "Inexact with i = " << i << endl;
			break;
		}
		ld = ld1;
	}
	cout << "ld: " << ld << endl;
	feclearexcept(FE_INEXACT);
	volatile long double ld2 = 1.0L, ld3 = 3.0L;
	volatile long double ld4 = ld2 / ld3;
	assert(fetestexcept(FE_INEXACT));
	// if( x > static_cast<dst_T>(limits<src_T>::max()) )
	ld = numeric_limits<long double>::max();
	ld1 = static_cast<long double>(numeric_limits<size_t>::max());
	cout << fixed << "ld: " << ld << ", ld1: " << ld1 << endl;
	/* https://stackoverflow.com/questions/79602836/c-23-numeric-limitslong-doublemax-use-case#79604603
	If you want to convert src_t x to a dst_t with a smaller range, you want to do a compare using the source type to see if the value would fit or not.
	if( x > static_cast<src_T>(limits<dst_T>::max()) ) it's out of range
	src_t = long double ld
	dst_t = size_t
	*/
	assert(ld > static_cast<long double>(numeric_limits<size_t>::max())); // No out of range
	size = numeric_limits<size_t>::max();
	size2 = static_cast<size_t>(numeric_limits<long double>::max());
	cout << fixed << "size: " << size << ", size2: " << size2 << endl;
#if defined(__GNUC__) || defined(__GNUG__)
	// For conversion, you can test which type has the larger max, and if the source type is larger then if( x > static_cast<src_T>(limits<dst_T>::max()) ) it's out of range.
	// Only works when long double has a size greater than 64 bits.
	assert(ld > static_cast<long double>(numeric_limits<size_t>::max())); // Out of range
#endif
	// The following checks and validates the next_permutation library functionality
	udata.clear();
	udata = { 1, 2, 3 };
	flag = next_permutation(udata.begin(), udata.end());
	udata1.clear();
	udata1 = { 1, 3, 2 };
	assert(flag);
	assert(udata1 == udata);

	flag = next_permutation(udata.begin(), udata.end());
	udata1.clear();
	udata1 = { 2, 1, 3 };
	assert(flag);
	assert(udata1 == udata);

	flag = next_permutation(udata.begin(), udata.end());
	udata1.clear();
	udata1 = { 2, 3, 1 };
	assert(flag);
	assert(udata1 == udata);

	flag = next_permutation(udata.begin(), udata.end());
	udata1.clear();
	udata1 = { 3, 1, 2 };
	assert(flag);
	assert(udata1 == udata);

	flag = next_permutation(udata.begin(), udata.end());
	udata1.clear();
	udata1 = { 3, 2, 1 };
	assert(flag);
	assert(udata1 == udata);

	flag = next_permutation(udata.begin(), udata.end());
	udata1.clear();
	udata1 = { 1, 2, 3 };
	assert(!flag);
	assert(udata1 == udata);

	udata.clear();
	udata = { 5, 4 };
	vector<size_t>::const_iterator it1 = lower_bound(udata.begin() + 1, udata.end(), 4);
	assert(it1 != udata.end());

	regex re("(\\d+)(\\[[a-zA-Z]+\\])");
	str = "3[a]2[bc]";
	cout << endl
		<< str << ": " << endl;
	for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), re);
		it != sregex_iterator();
		it++)
	{
		smatch const& match = *it;
		cout << "Match: " << match.str() << endl;
		for (size_t i = 0; i < match.size(); ++i)
			cout << "  Submatch " << i << ": " << match.str(i) << endl;
	}
	str = "3[a2[c]]";
	cout << endl
		<< str << ": " << endl;
	for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), re);
		it != sregex_iterator();
		it++)
	{
		smatch const& match = *it;
		cout << "Match: " << match.str() << endl;
		for (size_t i = 0; i < match.size(); ++i)
			cout << "  Submatch " << i << ": " << match.str(i) << endl;
	}
	str = "2[abc]3[cd]ef";
	cout << endl
		<< str << ": " << endl;
	for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), re);
		it != sregex_iterator();
		it++)
	{
		smatch const& match = *it;
		cout << "Match: " << match.str() << endl;
		for (size_t i = 0; i < match.size(); ++i)
			cout << "  Submatch " << i << ": " << match.str(i) << endl;
	}
	str = "2[abc]ef3[cd]";
	cout << endl
		<< str << ": " << endl;
	for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), re);
		it != sregex_iterator();
		it++)
	{
		smatch const& match = *it;
		cout << "Match: " << match.str() << endl;
		for (size_t i = 0; i < match.size(); ++i)
			cout << "  Submatch " << i << ": " << match.str(i) << endl;
	}
	str = "ef2[abc]3[cd]";
	cout << endl
		<< str << ": " << endl;
	for (sregex_iterator it = sregex_iterator(str.begin(), str.end(), re);
		it != sregex_iterator();
		it++)
	{
		smatch const& match = *it;
		cout << "Match: " << match.str() << endl;
		for (size_t i = 0; i < match.size(); ++i)
			cout << "  Submatch " << i << ": " << match.str(i) << endl;
	}
	// map<string, size_t> myKeyCount;
	myKeyCount.clear();
	myKeyCount["Hello"] = 1;
	myKeyCount["World!!!"] = 2;
	myKeyCount["There!!!"] = 2;
	multimap<size_t, string> myFlippedMap = flip_map(myKeyCount);
	multimap<size_t, string>::const_iterator myFlippedMapIt = myFlippedMap.find(1);
	assert("Hello" == myFlippedMapIt->second);
	cout << "Flipped map with key 2: ";
	for (auto [itr, rangeEnd] = myFlippedMap.equal_range(2); itr != rangeEnd; ++itr)
		cout << itr->second << ", ";
	cout << endl;
	str = stringArithmetic.Add2Binary("11", "1");
	assert("100" == stringArithmetic.Add2Binary("11", "1"));
	str = stringArithmetic.Add2Binary("1010", "1011");
	assert("10101" == stringArithmetic.Add2Binary("1010", "1011"));
	str = stringArithmetic.Add2Binary("100", "10");
	assert("110" == stringArithmetic.Add2Binary("100", "10"));
	str = stringArithmetic.Add2Binary("100", "110010");
	assert("110110" == stringArithmetic.Add2Binary("100", "110010"));
	a.clear();
	a = { 5, 4, 8, 11, numeric_limits<long>::min(), 13, 4, 7, 2, numeric_limits<long>::min(), numeric_limits<long>::min(), numeric_limits<long>::min(), numeric_limits<long>::min(), 1 };
	ltree = Tree(a, TreeType::Binary);
	ltree.PrintTree();
	// udata = []() -> generator<size_t>
	//{ co_yield ranges::elements_of(ranges::reverse_view(views::iota(0, 11))); }() | ranges::to<vector<size_t>>();
	// udata = []() -> generator<size_t>
	//{ co_yield ranges::elements_of(views::iota(0, 11)); }() | ranges::reverse_view() | ranges::to<vector<size_t>>();
	str = "acckzz";
	str1 = "ccbazz";
	/* MSVC enables a feature called Iterator Debugging(_ITERATOR_DEBUG_LEVEL = 2).
	 * Inside MSVC's implementation of std::set_intersection, it loops through your elements and explicitly checks if \(element_{n} \le element_{n+1}\).
	 * If it catches a violation, it triggers a deliberate runtime assertion (sequence not ordered) to prevent silent data corruption.
	 *
	 * GCC / g++ (Linux): By default, even when you compile with the -g flag (for debugging symbols), g++ does not add runtime data-validation checks.
	 * It assumes your data is already perfectly sorted. Instead of crashing, it invokes Undefined Behaviour (UB), meaning it silently finishes running
	 * but yields an incomplete or entirely garbage intersection output.
	 *
	 * 1. Structural RequirementsStrict Sorting: Both input ranges must already be sorted in ascending order according to the comparison criteria being used (either operator< or a custom predicate/comparator).
	 *    Passing unsorted ranges results in undefined behavior.
	 * 2. Handling Duplicates: The input ranges do not need to contain entirely unique elements. If an equivalent element appears M times in the first range and N times in the second range, the algorithm will copy exactly the first \(\min(M, N)\) elements from the first range into the destination.
	 * 3. No Memory Overlap: The output destination range cannot overlap with either of the input ranges. 
	 */
	// std::stable_sort is fully constexpr in C++26
	ranges::sort(str);
	ranges::sort(str1);
	set_intersection(str.begin(), str.end(), str1.begin(), str1.end(), inserter(cset, cset.begin()));
	ranges::copy(cset, ostream_iterator<char>(cout, ", "));
	assert(cset.size() == 3);
	cset1 = { 'a', 'c', 'z' };
	assert(cset1 == cset);
	cout << endl;
	cout << "pow(10, 10): " << pow(10, 10) << endl;
	/***** The End *****/
	cout
		<< "Press ENTER to exit";
	getline(cin, str);
	return 0;
}