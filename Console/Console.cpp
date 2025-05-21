// ConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Console.h"
using namespace std;
namespace ranges = std::ranges;
using namespace oneapi::tbb;
int main(int argc, char *argv[])
{
	string str, str1;
	ostringstream oss;
	size_t size, size1;
	long l, l1, l2;
	int32_t i, j, *iPtr;
	unsigned int ui;
	unsigned long long mask = 0;
	long double ld, ld1;
	set<size_t> uset1, uset2;
	set<string> stringset, stringset1;
	set<long> lset;
	vector<string> strings, strings1;
	vector<long> a, b, sortData;
	vector<long double> vld;
	vector<int> data, data1;
	vector<size_t> udata, udata1;
	vector<unsigned long long> ull;
	vector<bool> bools;
	set<vector<size_t>> usetvec;
	set<set<size_t>> usetgrid;
	priority_queue<long, deque<long>> maxHeap;
	priority_queue<long, deque<long>, greater<long>> minHeap;
	PriorityQueueMedian<long> pqueue;
	vector<vector<unsigned long>> grid;
	vector<vector<long>> grid1, grid2;
	vector<vector<char>> cgrid1, cgrid2;
	vector<vector<string>> sgrid;
	vector<vector<size_t>> ugrid, ugrid1;
	Graph<size_t, size_t> graph;
	Arithmetic<size_t> arithmetic;
	Arithmetic<long> larithmetic;
	DynamicProgramming<size_t> dp;
	Range range;
	Palindrome palindrome;
	Permutation<long> lPermutation;
	Permutation<size_t> ulPermutation;
	Permutation<string> sPermutation;
	FenwickTree<size_t> fenwickTree;
	Sort<long> sortAlgorithm;
	ExceptionTest();
	TestRandom();
	KDTreeTests();
	strings = {"111", "100", "100"};
	cgrid1.resize(strings.size());
	for (size_t i = 0; i < strings.size(); i++)
		ranges::copy(strings[i], back_inserter(cgrid1[i]));
	assert(stringset.erase("Does not exist") == 0); // Erasing non-existing element does NOT throw
	str = to_string(0);
	istringstream(str) >> i;
	assert(i == 0);
	Singleton *singleton = Singleton::Instance();
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
	Transmitter *tx = radio.get();
	Receiver *rx = radio.get();
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
	cout << "sizeof(void*): " << sizeof(void *) << endl;						  // Linux: 8, Windows: 8
	cout << "sizeof(double): " << sizeof(double) << endl;						  // LInux: 8, Windows: 8
	cout << "sizeof(long double): " << sizeof(long double) << endl;				  // Linux: 16, Windows: 8
#if defined(__GNUC__) || defined(__GNUG__)
	cout << "sizeof(__int128): " << sizeof(__int128) << endl; // Linux: 16, Windows: 8
#endif
	assert(sizeof(char) == 1);
	assert(sizeof(short) == 2);
	assert(sizeof(int) == 4);
	assert(sizeof(int32_t) == 4);
	assert(sizeof(int *) == 8);
#if defined(__GNUC__) || defined(__GNUG__)
	assert(sizeof(long) == 8);
#else
	assert(sizeof(long) == 4);
#endif
	assert(sizeof(float) == 4);
	assert(sizeof(long long) == 8);
	assert(sizeof(unsigned long long) == 8);
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
	cout << "Machine Epsilon: Float: " << MachineEpsilon((float)1) << ", Approximation: " << FloatMachineEpsilonApproximation() << endl;
	cout << "Machine Epsilon: Double: " << MachineEpsilon((double)1) << ", Approximation: " << MachineEpsilonApproximation() << endl;
	cout << "numeric_limits<int>::min(): " << numeric_limits<int>::min() << " (0x" << hex << numeric_limits<int>::min() << dec << "), numeric_limits<int>::max(): " << numeric_limits<int>::max() << " (0x" << hex << numeric_limits<int>::max() << "), numeric_limits<int>::min() *-1 = " << numeric_limits<int>::min() * -1 << endl;
	cout << "numeric_limits<unsigned int>::min(): " << numeric_limits<unsigned int>::min() << " (0x" << hex << numeric_limits<unsigned int>::min() << dec << "), numeric_limits<unsigned int>::max(): " << numeric_limits<unsigned int>::max() << " (0x" << hex << numeric_limits<unsigned int>::max() << "), numeric_limits<unsigned int>::min() *-1 = " << numeric_limits<unsigned int>::min() * -1 << endl;
	cout << "numeric_limits<int32_t>::min(): " << dec << numeric_limits<int32_t>::min() << " (0x" << hex << numeric_limits<int32_t>::min() << dec << "), numeric_limits<int32_t>::max(): " << numeric_limits<int32_t>::max() << " (0x" << hex << numeric_limits<int32_t>::max() << "), numeric_limits<int32_t>::min() *-1 = " << numeric_limits<int32_t>::min() * -1 << endl;
	cout << "numeric_limits<long>::min(): " << numeric_limits<long>::min() << " (0x" << hex << numeric_limits<long>::min() << dec << "), numeric_limits<long>::max(): " << numeric_limits<long>::max() << " (0x" << hex << numeric_limits<long>::max() << dec << "), numeric_limits<long>::min() * -1 = " << numeric_limits<long>::min() * -1 << endl;
	cout << "numeric_limits<long long>::min(): " << numeric_limits<long long>::min() << " (0x" << hex << numeric_limits<long long>::min() << dec << "), numeric_limits<long long>::max(): " << dec << fixed << numeric_limits<long long>::max() << " (0x" << hex << numeric_limits<long long>::max() << dec << "), numeric_limits<long long>::min() * -1 = " << numeric_limits<long long>::min() * -1 << endl;
#if defined(__GNUC__) || defined(__GNUG__)
	cout << "numeric_limits<__int128>::min(): " << numeric_limits<__int128>::min() << " (0x" << hex << numeric_limits<__int128>::min() << dec << "), numeric_limits<__int128>::max(): " << dec << fixed << numeric_limits<__int128>::max() << " (0x" << hex << numeric_limits<__int128>::max() << dec << "), numeric_limits<__int128>::min() * -1 = " << numeric_limits<__int128>::min() * -1 << endl;
#endif
	cout << "numeric_limits<size_t>::min(): " << numeric_limits<size_t>::min() << " (0x" << hex << numeric_limits<size_t>::min() << "), numeric_limits<size_t>::max(): " << dec << fixed << numeric_limits<size_t>::max() << " (0x" << hex << numeric_limits<size_t>::max() << dec << "), numeric_limits<size_t>::min() * -1 = " << numeric_limits<size_t>::min() * -1 << endl;

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
	assert(numeric_limits<int>::min() * -1 == numeric_limits<int>::min());		   // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
	assert(numeric_limits<int32_t>::min() * -1 == numeric_limits<int32_t>::min()); // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
	// assert(numeric_limits<int>::min() / -1 == numeric_limits<int>::min()); Integer overflow as 0x8000_0000 positive is > numeric_limits<int>::max()
	assert(numeric_limits<int>::max() * -1 == numeric_limits<int>::min() + 1);		   // 0x7FFFF_FFFF * -1 = -0x7FFF_FFFF = 0x8000_0001
	assert(numeric_limits<int32_t>::max() * -1 == numeric_limits<int32_t>::min() + 1); // 0x7FFFF_FFFF * -1 = -0x7FFF_FFFF = 0x8000_0001
	assert(numeric_limits<long>::min() * -1 == numeric_limits<long>::min());		   // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
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
	j = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
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
	unsigned long long ticks = timespan.count();
	long long signedTicks = timespan.count();
	assert(std::chrono::system_clock::duration::min().count() == numeric_limits<long long>::min());
	assert(std::chrono::system_clock::duration::max().count() == numeric_limits<long long>::max());
	assert(signedTicks == ticks);
	cout << "Current timestamp (ticks since Epoch): " << ticks << ", signed ticks: " << signedTicks << endl;
	cpp20readonlyranges();
	cpp20ranges();
	cpp20variants();
	cout << "30! " << dp.Factorial(30) << endl;				// The CPU signals loss of precision via a flag in the FPU control registers starting from i=26
	cout << "Fibonacci(100) " << dp.Fibonacci(100) << endl; // The CPU signals loss of precision via a flag in the FPU control registers starting from i=94
	grid = {{1, 3, 5}, {2, 4, 6}, {7, 8, 9}};
	// grid.back() = {7,8,9}
	assert(grid.back().back() == 9);
	grid.clear();
	grid1 = {{-1, 0, -1}, {-1, -1, -1}, {-1, -1, -1}};
	grid2 = {{1, 0, 1}, {2, 1, 2}, {3, 2, 3}};
	Matrix<long> matrix;
	matrix.MatrixDistance(grid1, 0, 1);
	cout << "grid1 (" << grid1.size() << "): " << endl;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			cout << grid1[i][j] << " ";
			assert(grid1[i][j] == grid2[i][j]);
		}
		cout << endl;
	}
	str = "ab2c3";
	assert(uncompress(str) == "ababcababcababc");
	cout << "uncompress(" << quoted(str) << "): " << uncompress(str) << endl;
	str = "0010110100";
	size = findLongestContiguousPattern(str, '1');
	assert(size == 4);
	assert(str == "0010111100");
	cout << "findLongestContiguousPattern(\"0010110100\", \'1\'): " << str << " size: " << size << endl;
	str = "00101101100";
	size = findLongestContiguousPattern(str, '1');
	assert(size == 5);
	assert(str == "00101111100");
	cout << "findLongestContiguousPattern(\"00101101100\", \'1\'): " << str << " size: " << size << endl;

	// Test C++ *& "pointer reference" construct
	iPtr = (int *)malloc(10 * sizeof(int));
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
	assert(Min(123, 456) == 123);
	assert(Max(123, 456) == 456);
	assert(gcd(48, 15) == 3);
	assert(gcd(108, 48) == 12);
	assert(gcd(1050, 507) == 3);
	assert(lcm(21, 6) == 42);
	assert(!isUniqueString("Helo World!!!"));
	str = "Hello World!!!";
	reverse(str);
	assert(str == "!!!dlroW olleH");
	str = "The house is blue";
	reverseWords(str);
	assert(str == "blue is house The");
	str = "  The   house is    blue  ";
	reverseWordsTrimmed(str);
	assert(str == "blue is house The");

	str = "abcdefcdbacd";
	str1 = "abcd";
	udata = FindSubString(str, str1);
	udata1 = {0, 6, 7, 8};
	assert(udata.size() == 4); // 0 6 7 8
	assert(udata1 == udata);

	assert(Count1Bits(10) == 2);
	assert(Count1Bits(12) == 2);
	assert(Count1Bits(7) == 3);
	a.clear();
	BitCombinations(3, a); // 000 001 010 100 011 101 110 111
	assert(a.size() == 8);
	b.clear();
	b = {0, 1, 2, 4, 3, 5, 6, 7};
	assert(b == a);
	cout << "BitCombinations from 0 to 3 of '1' bits: ";
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		cout << bitset<3>(*it) << " ";
	cout << endl;
	a.clear();
	BitCombinations(4, a); // 0000 0001 0010 0100 1000 0011 0101 0110 1001 1010 1100 0111 1011 1101 1110 1111
	assert(a.size() == 16);
	b.clear();
	b = {0, 1, 2, 4, 8, 3, 5, 6, 9, 10, 12, 7, 11, 13, 14, 15};
	assert(b == a);
	cout << "BitCombinations from 0 to 4 of '1' bits: ";
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		cout << bitset<4>(*it) << " ";
	cout << endl;
	udata.clear();
	udata = grayCode(2);
	assert(udata.size() == 4);
	udata1.clear();
	udata1 = {0, 1, 3, 2};
	assert(udata1 == udata);
	udata.clear();
	udata = grayCode(0);
	assert(udata.size() == 1);
	assert(udata[0] == 0);
	strings.clear();
	strings = {"a", "b", "c", "d"};
	strings1 = {"b", "c"};
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
	strings = {"Angel", "legnA", "Hello World!!!", "World Hello!!!"};
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
	a = {0, 1, 2, 7, 10, 11, 12, 20, 25, 26, 27};
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
	assert(Factorial(1) == 1);
	assert(Factorial(2) == 2);
	assert(Factorial(3) == 6);
	assert(Factorial(4) == 24);
	assert(Factorial(5) == 120);
	assert(Factorial(20) == 2432902008176640000);
	assert(SequenceSum(0) == 0);
	assert(SequenceSum(1) == 1);
	assert(SequenceSum(5) == 15);
	assert(Fibonacci(-1) == -1);
	assert(Fibonacci(0) == 0);
	assert(Fibonacci(1) == 1);
	assert(Fibonacci(2) == 1);
	assert(Fibonacci(3) == 2);
	assert(Fibonacci(4) == 3);
	assert(Fibonacci(5) == 5);
	assert(Fibonacci(6) == 8);
	assert(Fibonacci(7) == 13);
	assert(Fibonacci(8) == 21);
	assert(Fibonacci(9) == 34);
// assert(Fibonacci(90) == 2880067194370816120ULL); Times out!!!
#if 0
	assert(FibonacciModified(0, 1, 4) == "5");
	assert(FibonacciModified(0, 1, 5) == "27");
	assert(FibonacciModified(0, 1, 6) == "734");
	assert(FibonacciModified(0, 1, 7) == "538783");
	assert(FibonacciModified(0, 1, 8) == "290287121823");
	assert(FibonacciModified(0, 1, 9) == "84266613096281243382112");
	assert(FibonacciModified(2, 0, 0) == "2");
	assert(FibonacciModified(2, 0, 1) == "0");
	assert(FibonacciModified(2, 0, 2) == "2");
	assert(FibonacciModified(2, 0, 3) == "4");
	assert(FibonacciModified(2, 0, 4) == "18");
	assert(FibonacciModified(2, 0, 5) == "328");
	assert(FibonacciModified(2, 0, 6) == "107602");
	assert(FibonacciModified(2, 0, 7) == "11578190732");
	assert(FibonacciModified(2, 0, 11) == "104292047421056066715537698951727494083004264929891558279344228228718658019003171882044298756195662458280101226593033166933803327203745068186400974453022429724308");
#endif
	unsigned long long factorialResult = Factorial(26);
	cout << "26!: " << setiosflags(ios::fixed) << factorialResult << endl;
	assert(FactorialTrailingZeroesCount(10) == 2);
	assert(FactorialTrailingZeroesCount(25) == 6);
	assert(FactorialTrailingZeroesCount(26) == 6);
	cout << "10!: " << (double)Factorial(10) << " has " << FactorialTrailingZeroesCount(10) << " trailing zeroes." << endl;
	cout << "25!: " << (double)Factorial(25) << " has " << FactorialTrailingZeroesCount(25) << " trailing zeroes." << endl;
	cout << "26!: " << (double)Factorial(26) << " has " << FactorialTrailingZeroesCount(26) << " trailing zeroes." << endl;
	data.clear();
	str = "abc";
	a.clear();
	a.resize(25);
	ranges::generate(a.begin(), a.begin() + 10, [n = 0]() mutable
					 { return n++; });
	ranges::generate(a.begin() + 10, a.end(), [n = 5]() mutable
					 { return n++; });
	b.clear();
	findDistinct(a, b);
	assert(b.size() == 20);

	a.clear();
	b.clear();
	findPrimes(20, a); // Find prime numbers 0 to 20: 2,3,5,7,11,13,17,19
	assert(a.size() == 8);
	a.clear();
	b.clear();
	a = {15, 10, 3};
	b = {75, 30, 5};
	assert(CommonPrimeDivisors(a, b) == 1);
	a.clear();
	b.clear();
	a = {7, 17, 5, 3};
	b = {7, 11, 5, 2};
	assert(CommonPrimeDivisors(a, b) == 2);

	assert(!isPrime(1));
	assert(isPrime(2));
	assert(isPrime(3));
	assert(!isPrime(4));
	assert(isPrime(5));
	assert(!isPrime(6));
	assert(isPrime(7));
	assert(!isPrime(8));
	assert(!isPrime(9));
	assert(!isPrime(10));
	a.clear();
	b.clear();
	ull.clear();
	ull = {1, 2, 1, 2};
	unsigned long long findMaxResult = findMax(ull);
	assert(findMaxResult == 9);

	ull.clear();
	ull = {2, 3, 3, 2};
	findMaxResult = findMax(ull);
	assert(findMaxResult == 36);

	str = "     Hello     World!!!     ";
	assert(str.size() == 28);
	cout << str << " size: " << str.size();
	trim(str);
	// assert(str == "Hello     World!!!");
	cout << " trim(str): |" << str << "| size: " << str.size() << endl;

	a.clear();
	cout << "minDiffPairs(): " << endl;
	a = {1, 2, 3, 4, 5, 6};
	assert(minDiffPairs(a, 0) == 3);
	a.clear();
	a = {1, 2, 3, 4, 5, 6};
	assert(minDiffPairs(a, 1) == 3);
	a.clear();
	a = {1, 2, 3, 4, 5, 6};
	assert(minDiffPairs(a, 2) == 2);
	a.clear();
	a = {6, 5, 4, 3, 2, 1};
	assert(minDiffPairs(a, 3) == 3);
	cout << endl;
	a.clear();
	a = {3, 5, 1, 6, 2, 4};
	assert(minDiffPairs(a, 4) == 2);
	assert(minDiffPairs(a, 5) == 1);
	a.clear();
	a = {1, 1, 1, 5, 5, 5, 5};
	assert(minDiffPairs(a, 4) == 3);
	a.clear();
	a = {1, 1};
	assert(minDiffPairs(a, 1) == 0);

	// Test Recursive algorithm
	assert(LongestValidParenthesesWithFixes(string("("), 0) == 0);
	assert(LongestValidParenthesesWithFixes(string("((()"), 0) == 2);
	assert(LongestValidParenthesesWithFixes(string("())()"), 0) == 2);
	assert(LongestValidParenthesesWithFixes(string("()(()"), 0) == 2);
	assert(LongestValidParenthesesWithFixes(string(")()())"), 0) == 4);
	assert(LongestValidParenthesesWithFixes(string("()(()))))"), 0) == 6);
	assert(LongestValidParenthesesWithFixes(string(")))((("), 0) == 0);
	assert(LongestValidParenthesesWithFixes(string(")()()(((()"), 0) == 4);
	assert(LongestValidParenthesesWithFixes(string("))()(()(()"), 0) == 2);
	assert(LongestValidParenthesesWithFixes(string(")())((()))"), 0) == 6);
	assert(LongestValidParenthesesWithFixes(string("(()))))(()((()))"), 0) == 8);
	assert(LongestValidParenthesesWithFixes(string(")()()("), 3) == 6);
	assert(LongestValidParenthesesWithFixes(string(")))((("), 2) == 4);
	assert(LongestValidParenthesesWithFixes(string(")))(("), 0) == 0);
	assert(LongestValidParenthesesWithFixes(string(")("), 1) == 0);
	assert(LongestValidParenthesesWithFixes(string(")("), 2) == 2);
	assert(LongestValidParenthesesWithFixes(string("((("), 0) == 0);
	assert(LongestValidParenthesesWithFixes(string("((("), 1) == 2);
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
		towers[i]->Clear();
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
	long **my2Dbuffer = my2DAlloc(10, 10);
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
	long ***my3Dbuffer = my3DAlloc(10, 10, 10);
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
		mask |= ((unsigned long long)1 << i);
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
	pqueue.Clear();
	pqueue.Add(6);
	pqueue.Add(5);
	pqueue.Add(1);
	pqueue.Add(3);
	pqueue.Add(2);
	pqueue.Add(7);
	assert(pqueue.GetMedian() == 4);
	pqueue.Add(8);
	assert(pqueue.GetMedian() == 5);
	pqueue.Clear();
	// Test Priority Queue which returns median value
	// -10 -9 -8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8 9
	for (i = -10; i < 10; i++) // 20 numbers. Median = (10th + 11th) / 2
		pqueue.Add(i);
	assert(pqueue.GetMedian() == -0.5);
	pqueue.Add(10); // 21 numbers. Median = 11th number = 0
	assert(pqueue.GetMedian() == 0);
	pqueue.Clear();
	assert(pqueue.GetMedian() == 0);
	a.clear();
	b.clear();
	a.push_back(123);
	long sum = parallel_reduce(
		blocked_range<size_t>(0, a.size()), 0,
		[&](tbb::blocked_range<size_t> const &r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		std::plus<long>());
	assert(sum == 123);

	a.clear();
	b.clear();
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	sum = parallel_reduce(
		blocked_range<size_t>(2, a.size()), 0,
		[&](tbb::blocked_range<size_t> const &r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		std::plus<long>());
	assert(sum == 3);

	a.clear();
	b.clear();
	a.resize(10);
	ranges::generate(a, [n = 1]() mutable
					 { return n++; });
	sum = parallel_reduce(
		blocked_range<size_t>(0, a.size()), 0,
		[&](tbb::blocked_range<size_t> const &r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		std::plus<long>());
	assert(sum == 55);
	a.clear();
	b.clear();
	a = {1, 7, 15, 29, 11, 9};
	EqualAverageDivide(a, b);
	assert(b.size() == 2);
	cout << "Left part: ";
	sum = parallel_reduce(
		blocked_range<size_t>(0, b.size()), 0,
		[&](tbb::blocked_range<size_t> const &r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += b[i];
			return running_total;
		},
		std::plus<long>());
	ranges::copy(b, ostream_iterator<long>(cout, " "));
	assert(sum == 24);
	cout << "sum: " << sum << endl;

	vector<char> cData1{1, 2, 3}, cData2{4, 5, 6};
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
	cData1 = {9, 8, 7};
	cData2 = {6, 5, 4};
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
	stringset = {"cdf", "too", "hgfdt", "paa"};
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
	data = {9, 9, 9, 9};
	data1 = Increment(data);
	assert(data1[0] == 1);
	assert(data1[1] == 0);
	assert(data1[2] == 0);
	assert(data1[3] == 0);
	assert(data1[4] == 0);

	void *addr = alignedMalloc(1000, 64);
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
	sortData = {1, 2, 3, 10, 25, 26, 30, 31, 32, 33};
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
	a = {9, 918, 917};
	assert(concat(a) == 9918917);
	a.clear();
	a = {1, 112, 113};
	assert(concat(a) == 1131121);
	a.clear();
	a = {901, 9015};
	// 9019015, 9015901
	assert(concat(a) == 9019015);
	udata.clear();
	udata = {10, 2};
	assert(buildmax(udata) == "210");
	udata.clear();
	udata = {3, 30, 34, 5, 9};
	assert(buildmax(udata) == "9534330");
	udata.clear();
	udata = {128, 12, 320, 32};
	assert(buildmax(udata) == "3232012812");
	udata.clear();
	udata = {0, 0};
	assert(buildmax(udata) == "0");
	udata.clear();
	assert(buildmax(udata) == "0");
	strings.clear();
	strings = {"ABCW", "BAZ", "FOO", "BAR", "XTFN", "ABCDEF"};
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
	a = {10, 2, 5, 1, 8, 12};
	assert(CountTriangles(a) == 4);
	assert(decimal_to_binary(0) == "0");
	assert(binary_to_decimal(string("1010")) == 10);
	cout << 0xdeadbeef << endl;
#if defined(__GNUC__) || defined(__GNUG__)
	assert(binary_to_decimal(string("1101 1110 1010 1101 1011 1110 1110 1111")) == 0xffffffffdeadbeef);
#else
	assert(binary_to_decimal(string("1101 1110 1010 1101 1011 1110 1110 1111")) == 0xdeadbeef);
#endif
	a.clear();
	a = {1, 5, 2, -2};
	assert(MinAbsSum(a) == 0);
	a.clear();
	a = {2, 2, 1};
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
	nodeA->SetNext(nodeB);
	nodeB->SetNext(nodeC);
	nodeC->SetNext(nodeE);
	nodeC->SetNext(nodeD);
	nodeD->SetNext(nodeE);
	nodeE->SetNext(nodeF);
	nodeE->SetNext(nodeE);
	nodeF->SetNext(nodeB);
	nodeF->SetNext(nodeA);
	nodeD->SetNext(nodeG);
	nodeD->SetNext(nodeH);
	nodeG->SetNext(nodeH);
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
	data.clear();
	data = {1, 0, 1, 1, 0, 0, 0};
	assert(findMinFlip(data) == 1);
	data.clear();
	data = {0, 0, 0, 0, 1};
	assert(findMinFlip(data) == 2);
	vector<vector<char>> m = {
		{'R', 'G', 'R', 'B'},
		{'R', 'Y', 'G', 'R'},
		{'G', 'B', 'Y', 'Y'},
		{'Y', 'G', 'B', 'G'},
		{'B', 'R', 'Y', 'B'},
	};
	assert(IsValidMatrix(m));
	vector<vector<char>> m1 = {
		{'R', 'G', 'R', 'B'},
		{'R', 'Y', 'G', 'R'},
		{'G', 'B', 'B', 'B'},
		{'Y', 'G', 'B', 'G'},
		{'B', 'R', 'Y', 'B'},
	};
	assert(!IsValidMatrix(m1));
	vector<vector<char>> m2 = {
		{'R', 'G', 'R', 'B'},
		{'R', 'Y', 'G', 'R'},
		{'G', 'B', 'G', 'Y'},
		{'Y', 'G', 'G', 'G'},
		{'B', 'R', 'Y', 'B'},
	};
	assert(!IsValidMatrix(m2));
	a.clear();
	a = {13, 2, 5};
	stringset.clear();
	// assert(ZigZagEscape(a, stringset) == 7);
	assert(ZigZagEscape(a) == 7);
	a.clear();
	a = {4, 6, 2, 1, 5};
	stringset.clear();
	// assert(ZigZagEscape(a, stringset) == 23);
	assert(ZigZagEscape(a) == 23);
	a.clear();
	a = {6, 3, 1, 4, 2, 5};
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
	a = {-3, 1, 2, -2, 5, 6};
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
	a = {1, 2, 3, 4, 5, 6, 7, 8};
	ranges::rotate(a.begin() + 2, a.begin() + 4, a.begin() + 5);
	b = {1, 2, 5, 3, 4, 6, 7, 8};
	assert(a == b);
	str = "if man was meant to stay on the ground god would have given us roots";
	assert(encryption(str) == "imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau");
	a.clear();
	a = {3, 1, 5, 4, 2};
	assert(CalculateMedian(a) == 3);
	a.clear();
	a = {3, 1, 5, 4, 2, 6};
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
	b.clear();
	a = {1, 3, 5, 7, 9};
	b = {2, 4, 6, 8, 10};
	assert(median(a, b) == 11 / (double)2);
	a.clear();
	b.clear();
	a = {1, 3, 5, 7, 9};
	b = {2, 4, 6, 8, 10, 11};
	assert(median(a, b) == 6);
	a.clear();
	b.clear();
	a = {1, 3, 5};
	b = {2, 4, 6, 8, 10, 11};
	assert(median(a, b) == 5);
	a.clear();
	b.clear();
	a = {1, 3, 5};
	b = {2, 4, 6, 8, 10, 11, 13};
	assert(median(a, b) == 11 / (double)2);
	a.clear();
	b.clear();
	a = {1, 3, 5, 7, 9, 11, 13};
	b = {2, 4, 6, 8};
	assert(median(a, b) == 6);
	a.clear();
	b.clear();
	a = {1, 3, 5, 7, 9, 11, 13, 15};
	b = {2, 4, 6, 8};
	assert(median(a, b) == (6 + 7) / (double)2);
	a.clear();
	b.clear();
	b = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	assert(median(a, b) == 5);
	b.clear();
	b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	assert(median(a, b) == (5 + 6) / (double)2);
	a.clear();
	b.clear();
	a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	assert(median(a, b) == 5);
	a.clear();
	a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	assert(median(a, b) == (5 + 6) / (double)2);
	a.clear();
	b.clear();
	assert(median(a, b) == 0);
	a.clear();
	a = {1, 2, 3, 4};
	a = productExceptSelf(a);
	b.clear();
	b = {24, 12, 8, 6};
	assert(!a.empty());
	assert(a.size() == 4);
	assert(b == a);
	a.clear();
	a = diffWaysToCompute("2-1-1");
	assert(!a.empty());
	assert(a.size() == 2);
	a.clear();
	a = diffWaysToCompute("2*3-4*5");
	assert(!a.empty());
	assert(a.size() == 5);
	a.clear();
	a = {1, 3, 5};
	ListRangeSum<long> listSum(a);
	assert(listSum.Sum(0, 2) == 9);
	listSum.Update(1, 2);
	assert(listSum.Sum(0, 2) == 8);
	a.clear();
	a = {-1};
	ListRangeSum<long> listSum1(a);
	assert(listSum1.Sum(0, 0) == -1);
	listSum1.Update(0, 1);
	assert(listSum1.Sum(0, 0) == 1);
	ugrid.clear();
	numberCombinations(4, 2, ugrid);
	assert(!ugrid.empty());
	assert(ugrid.size() == 6);
	for (vector<vector<size_t>>::iterator it = ugrid.begin(); it != ugrid.end(); it++)
		assert(it->size() == 2);
	ugrid1.clear();
	ugrid1 = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};
	assert(ugrid1 == ugrid);
	ugrid.clear();
	numberCombinations(20, 16, ugrid);
	assert(!ugrid.empty());
	assert(ugrid.size() == 4845);
	assert(fizzBuzz(3) == vector<string>({"1", "2", "Fizz"}));
	assert(fizzBuzz(5) == vector<string>({"1", "2", "Fizz", "4", "Buzz"}));
	assert(fizzBuzz(10) == vector<string>({"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz"}));
	assert(fizzBuzz(15) == vector<string>({"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz"}));
	udata.clear();
	udata1.clear();
	udata1 = {123, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 456};
	ranges::copy(GenerateSequence(0, 10), back_inserter(udata));
	assert(udata1 == udata);
	udata.clear();
	udata1.clear();
	udata1 = {123, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 456};
	ranges::copy(Generate2Sequence(0, 10, 100, 110), back_inserter(udata));
	assert(udata1 == udata);
	vector<vector<size_t>> edges;
	edges.clear();
	edges = {{1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2}};
	assert("1000100" == RoadsInHackerland(5, edges));
	// assert("1000100" == RoadsInHackerland1(5, edges));
	edges.clear();
	edges = {{1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2}};
	// assert("1000100" == RoadsInHackerland2(5, edges));
	edges.clear();
	edges = {
		{5, 12, 18},
		{17, 2, 5},
		{7, 18, 3},
		{17, 6, 0},
		{15, 12, 16},
		{2, 3, 8},
		{14, 9, 20},
		{4, 9, 11},
		{13, 1, 21},
		{13, 12, 15},
		{15, 12, 10},
		{6, 16, 9},
		{11, 18, 2},
		{9, 16, 17},
		{12, 4, 4},
		{7, 4, 19},
		{17, 1, 12},
		{10, 14, 7},
		{8, 5, 13},
		{18, 3, 14},
		{4, 11, 6},
		{15, 3, 1},
		{12, 5, 22},
	};
	assert("10100011101101000001001000" == RoadsInHackerland(18, edges));
	// assert("10100011101101000001001000" == RoadsInHackerland1(18, edges));
	edges.clear();
	edges = {
		{5, 12, 18},
		{17, 2, 5},
		{7, 18, 3},
		{17, 6, 0},
		{15, 12, 16},
		{2, 3, 8},
		{14, 9, 20},
		{4, 9, 11},
		{13, 1, 21},
		{13, 12, 15},
		{15, 12, 10},
		{6, 16, 9},
		{11, 18, 2},
		{9, 16, 17},
		{12, 4, 4},
		{7, 4, 19},
		{17, 1, 12},
		{10, 14, 7},
		{8, 5, 13},
		{18, 3, 14},
		{4, 11, 6},
		{15, 3, 1},
		{12, 5, 22},
	};
	// assert("10100011101101000001001000" == RoadsInHackerland2(18, edges));
	edges.clear();
	edges = {
		{4, 11, 27},
		{7, 9, 14},
		{13, 6, 23},
		{18, 10, 3},
		{19, 4, 19},
		{2, 7, 6},
		{11, 13, 20},
		{6, 15, 0},
		{14, 18, 2},
		{16, 5, 26},
		{2, 20, 10},
		{16, 17, 21},
		{6, 2, 9},
		{11, 5, 25},
		{20, 19, 28},
		{14, 4, 29},
		{10, 4, 24},
		{9, 7, 8},
		{7, 1, 15},
		{12, 13, 7},
		{8, 3, 22},
		{8, 13, 4},
		{17, 14, 1},
		{8, 15, 11},
		{1, 10, 5},
		{18, 15, 18},
		{7, 13, 17},
		{12, 9, 16},
		{14, 6, 12},
		{9, 2, 13},
	};
	assert("1010100000000011001101110101111" == RoadsInHackerland(20, edges));
	edges.clear();
	edges = {{67, 12, 346},
			 {299, 226, 42},
			 {226, 285, 206},
			 {218, 253, 167},
			 {125, 96, 177},
			 {123, 5, 156},
			 {167, 179, 19},
			 {280, 3, 300},
			 {265, 44, 242},
			 {116, 277, 153},
			 {235, 289, 6},
			 {202, 242, 56},
			 {244, 239, 78},
			 {123, 109, 141},
			 {71, 20, 349},
			 {212, 221, 134},
			 {6, 229, 23},
			 {211, 207, 202},
			 {32, 38, 284},
			 {203, 41, 245},
			 {229, 169, 157},
			 {115, 209, 337},
			 {32, 180, 345},
			 {260, 232, 244},
			 {150, 114, 147},
			 {206, 80, 331},
			 {201, 198, 143},
			 {107, 167, 305},
			 {132, 228, 225},
			 {90, 216, 233},
			 {62, 11, 85},
			 {99, 270, 79},
			 {154, 298, 280},
			 {256, 276, 28},
			 {153, 236, 93},
			 {69, 297, 330},
			 {222, 262, 322},
			 {19, 64, 166},
			 {26, 27, 53},
			 {162, 107, 256},
			 {183, 231, 125},
			 {180, 213, 145},
			 {152, 234, 312},
			 {103, 127, 291},
			 {97, 294, 13},
			 {111, 9, 169},
			 {24, 198, 111},
			 {179, 273, 162},
			 {270, 92, 207},
			 {231, 279, 71},
			 {248, 273, 246},
			 {267, 38, 64},
			 {73, 179, 105},
			 {73, 126, 237},
			 {87, 217, 289},
			 {186, 76, 316},
			 {223, 266, 94},
			 {48, 140, 180},
			 {74, 107, 252},
			 {282, 237, 279},
			 {148, 56, 128},
			 {33, 204, 129},
			 {16, 151, 17},
			 {15, 295, 114},
			 {178, 148, 329},
			 {288, 41, 182},
			 {85, 276, 194},
			 {250, 168, 265},
			 {237, 45, 121},
			 {213, 196, 296},
			 {81, 158, 84},
			 {210, 97, 268},
			 {185, 82, 136},
			 {4, 92, 127},
			 {194, 284, 336},
			 {143, 17, 55},
			 {15, 17, 223},
			 {188, 176, 285},
			 {264, 132, 82},
			 {69, 84, 24},
			 {230, 220, 226},
			 {128, 299, 323},
			 {277, 29, 229},
			 {27, 261, 317},
			 {71, 297, 159},
			 {55, 298, 306},
			 {100, 195, 320},
			 {64, 199, 288},
			 {243, 39, 253},
			 {173, 204, 258},
			 {105, 120, 290},
			 {49, 251, 189},
			 {286, 2, 65},
			 {150, 61, 130},
			 {108, 176, 86},
			 {87, 233, 133},
			 {222, 7, 250},
			 {228, 129, 10},
			 {196, 34, 171},
			 {141, 35, 131},
			 {30, 285, 109},
			 {170, 86, 43},
			 {93, 101, 148},
			 {171, 263, 154},
			 {159, 95, 73},
			 {66, 121, 39},
			 {25, 145, 15},
			 {91, 235, 319},
			 {68, 297, 81},
			 {199, 13, 8},
			 {89, 268, 45},
			 {293, 154, 321},
			 {82, 115, 274},
			 {27, 101, 228},
			 {299, 8, 307},
			 {53, 291, 309},
			 {29, 218, 117},
			 {239, 75, 293},
			 {152, 74, 198},
			 {2, 121, 222},
			 {178, 237, 213},
			 {177, 285, 184},
			 {82, 15, 88},
			 {151, 161, 347},
			 {1, 227, 238},
			 {175, 215, 311},
			 {65, 93, 123},
			 {252, 288, 41},
			 {58, 102, 144},
			 {295, 189, 90},
			 {197, 202, 87},
			 {20, 28, 239},
			 {83, 73, 132},
			 {171, 267, 35},
			 {295, 290, 100},
			 {150, 226, 124},
			 {194, 253, 151},
			 {10, 292, 257},
			 {124, 52, 235},
			 {214, 120, 211},
			 {205, 175, 314},
			 {221, 108, 38},
			 {101, 209, 77},
			 {254, 53, 161},
			 {149, 298, 29},
			 {298, 229, 297},
			 {34, 236, 119},
			 {232, 86, 110},
			 {61, 13, 261},
			 {163, 157, 232},
			 {208, 271, 266},
			 {170, 230, 287},
			 {37, 102, 333},
			 {40, 37, 103},
			 {104, 45, 218},
			 {14, 245, 341},
			 {1, 118, 20},
			 {129, 217, 57},
			 {31, 200, 32},
			 {56, 210, 62},
			 {287, 136, 96},
			 {240, 114, 210},
			 {208, 88, 273},
			 {116, 161, 49},
			 {178, 183, 243},
			 {269, 84, 106},
			 {96, 274, 69},
			 {29, 281, 263},
			 {220, 259, 264},
			 {227, 5, 191},
			 {233, 290, 107},
			 {277, 189, 51},
			 {144, 298, 7},
			 {148, 214, 97},
			 {187, 281, 4},
			 {299, 76, 342},
			 {166, 216, 46},
			 {191, 137, 155},
			 {8, 172, 89},
			 {39, 146, 301},
			 {80, 235, 240},
			 {67, 143, 241},
			 {83, 81, 251},
			 {219, 53, 190},
			 {251, 112, 176},
			 {279, 78, 102},
			 {50, 51, 95},
			 {163, 287, 58},
			 {135, 113, 269},
			 {190, 66, 178},
			 {80, 78, 332},
			 {109, 161, 0},
			 {114, 7, 108},
			 {185, 135, 224},
			 {154, 134, 299},
			 {273, 182, 174},
			 {198, 300, 22},
			 {258, 271, 47},
			 {223, 88, 276},
			 {186, 298, 146},
			 {193, 138, 262},
			 {149, 146, 267},
			 {194, 287, 315},
			 {141, 242, 340},
			 {278, 255, 338},
			 {125, 157, 135},
			 {186, 131, 172},
			 {153, 112, 91},
			 {23, 184, 326},
			 {199, 17, 270},
			 {260, 36, 168},
			 {43, 96, 116},
			 {145, 89, 61},
			 {254, 67, 193},
			 {226, 280, 74},
			 {30, 3, 40},
			 {110, 238, 50},
			 {147, 124, 150},
			 {64, 130, 31},
			 {18, 168, 120},
			 {137, 279, 34},
			 {294, 261, 247},
			 {158, 172, 188},
			 {139, 71, 152},
			 {111, 70, 12},
			 {112, 62, 76},
			 {143, 48, 59},
			 {147, 243, 181},
			 {291, 23, 36},
			 {275, 195, 3},
			 {201, 122, 271},
			 {93, 115, 254},
			 {42, 127, 278},
			 {207, 170, 9},
			 {95, 219, 208},
			 {163, 262, 310},
			 {43, 259, 328},
			 {63, 68, 325},
			 {122, 241, 80},
			 {278, 156, 126},
			 {166, 145, 339},
			 {72, 57, 200},
			 {101, 98, 308},
			 {190, 181, 101},
			 {59, 11, 140},
			 {91, 296, 344},
			 {177, 266, 21},
			 {255, 248, 199},
			 {113, 169, 185},
			 {119, 26, 215},
			 {35, 98, 249},
			 {94, 286, 231},
			 {49, 203, 26},
			 {186, 79, 137},
			 {155, 130, 60},
			 {252, 236, 14},
			 {173, 126, 54},
			 {193, 142, 92},
			 {272, 181, 227},
			 {110, 155, 104},
			 {72, 133, 170},
			 {165, 220, 318},
			 {76, 194, 302},
			 {167, 116, 1},
			 {193, 217, 236},
			 {239, 206, 160},
			 {165, 160, 115},
			 {231, 227, 70},
			 {187, 299, 139},
			 {78, 201, 98},
			 {87, 66, 72},
			 {197, 253, 27},
			 {28, 284, 343},
			 {256, 156, 281},
			 {245, 246, 37},
			 {219, 265, 334},
			 {152, 257, 5},
			 {272, 164, 216},
			 {238, 268, 48},
			 {46, 55, 175},
			 {106, 244, 219},
			 {9, 116, 18},
			 {10, 283, 304},
			 {99, 28, 187},
			 {75, 205, 99},
			 {224, 69, 158},
			 {282, 144, 2},
			 {150, 155, 149},
			 {4, 235, 295},
			 {47, 70, 196},
			 {36, 217, 192},
			 {8, 130, 52},
			 {87, 224, 327},
			 {248, 187, 209},
			 {249, 99, 221},
			 {292, 19, 197},
			 {300, 60, 163},
			 {140, 42, 186},
			 {164, 234, 298},
			 {79, 212, 248},
			 {22, 103, 44},
			 {249, 225, 63},
			 {250, 33, 11},
			 {12, 192, 83},
			 {160, 65, 259},
			 {57, 24, 25},
			 {138, 58, 260},
			 {21, 84, 142},
			 {254, 206, 164},
			 {47, 59, 113},
			 {174, 190, 75},
			 {210, 253, 138},
			 {118, 33, 283},
			 {85, 64, 173},
			 {68, 51, 201},
			 {100, 234, 294},
			 {32, 133, 112},
			 {131, 296, 165},
			 {196, 105, 205},
			 {204, 214, 230},
			 {40, 88, 214},
			 {221, 81, 33},
			 {34, 77, 286},
			 {247, 215, 30},
			 {162, 252, 212},
			 {188, 200, 335},
			 {119, 289, 275},
			 {275, 67, 118},
			 {201, 77, 303},
			 {184, 246, 277},
			 {128, 94, 183},
			 {16, 292, 292},
			 {264, 60, 16},
			 {111, 96, 122},
			 {44, 191, 67},
			 {104, 40, 195},
			 {52, 211, 324},
			 {13, 160, 282},
			 {164, 258, 203},
			 {293, 142, 234},
			 {30, 209, 255},
			 {162, 247, 66},
			 {21, 117, 68},
			 {185, 244, 204},
			 {25, 136, 313},
			 {80, 213, 220},
			 {106, 121, 179},
			 {54, 274, 217},
			 {192, 174, 272},
			 {153, 50, 348}};
	// assert("100001110110101101000110111011110000000000001100010011111101010011010111100110011001001000101100001000110111110011111010001111101000101011100001110110101001011011111111011110101000100100011010000001110110001000110000100010011001101001100011101100100101001101111000001110000000100111000010001111110111100010111010011111111011111101111111110011111101111" == RoadsInHackerland(300, edges));
	udata.clear();
	udata = {1, 3, 2};
	cout << "{1, 3, 2}: " << LongestIncreasingSubsequenceNlogN(udata) << ", " << LongestDecreasingSubsequenceNlogN(udata) << endl;
	udata.clear();
	udata = {5, 3, 2, 1, 4};
	cout << "{5, 3, 2, 1, 4}: " << LongestIncreasingSubsequenceNlogN(udata) << ", " << LongestDecreasingSubsequenceNlogN(udata) << endl;
	udata.clear();
	udata = {4, 2, 5, 6};
	cout << "{4, 2, 5, 6}: " << LongestIncreasingSubsequenceNlogN(udata) << ", " << LongestDecreasingSubsequenceNlogN(udata) << endl;
	udata.clear();
	udata = {9, 7, 5, 6};
	cout << "{9, 7, 5, 6}: " << LongestIncreasingSubsequenceNlogN(udata) << ", " << LongestDecreasingSubsequenceNlogN(udata) << endl;
	udata.clear();
	udata = {6, 4, 2, 1, 3, 5, 7};
	cout << "{6, 4, 2, 1, 3, 5, 7}: " << LongestIncreasingSubsequenceNlogN(udata) << ", " << LongestDecreasingSubsequenceNlogN(udata) << endl;
	udata.clear();
	udata = {6, 4, 2, 3, 5, 7, 9};
	cout << "{6, 4, 2, 3, 5, 7, 9}: " << LongestIncreasingSubsequenceNlogN(udata) << ", " << LongestDecreasingSubsequenceNlogN(udata) << endl;
	multimap<int, string> mmap = {{123, "123"}, {456, "456"}, {123, "789"}};
	for (multimap<int, string>::iterator it = mmap.begin(); it != mmap.end(); it++)
		cout << it->first << ": " << it->second << endl;
	Dijkstra<string> dijkstra;
	strings.clear();
	strings = {"San Francisco", "Los Angeles", "Dallas", "New York", "Chicago"};
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
	ugrid.clear();
	ugrid = {{1, 2},
			 {2, 3},
			 {1, 4}};
	a = {3, 1, 2};
	assert(a == UnbeatenPaths(4, ugrid, 1));
	ugrid.clear();
	ugrid = {{12397, 52974}, {107864, 38870}};
	// a = UnbeatenPaths(110857, ugrid, 47678);
	grid1.clear();
	a.clear();
	const long modulo = 1e9 + 7L;
	a = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	l = 1e9 + 7L;
	l1 = ranges::fold_left(a, 1, [&modulo](long x, long y) -> long
						   { return ((x % modulo) * (y % modulo) % modulo); });
	l2 = parallel_reduce(
		blocked_range<long>(0, a.size()), 1l /* Identity for Multiplication */,
		[&](tbb::blocked_range<long> const &r, long running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total = ((running_total % modulo) * (a[i] % modulo)) % modulo;
			return running_total;
		},
		[&modulo](long x, long y) -> long
		{
			return ((x % modulo) * (y % modulo) % modulo);
		});
	assert(l2 == l1);
	l2 = accumulate(a.begin(), a.end(), 1l, [&modulo](long x, long y) -> long
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
	assert(arithmetic.NumberStringMultiplication(str, str1) == "56088");
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
	uset1 = {1, 2, 3};
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
	uset2 = {1, 2, 3};
	usetgrid = ulPermutation.RangeUniquePermutations(uset1, uset2, 1, 1);
	for (set<set<size_t>>::const_iterator it = usetgrid.begin(); it != usetgrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	uset1.clear();
	uset2.clear();
	uset2 = {1, 2, 3};
	usetgrid = ulPermutation.RangeUniquePermutations(uset1, uset2, 2, 1);
	for (set<set<size_t>>::const_iterator it = usetgrid.begin(); it != usetgrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	uset1.clear();
	uset2.clear();
	uset2 = {1, 2, 3};
	usetgrid = ulPermutation.RangeUniquePermutations(uset1, uset2, 3, 1);
	for (set<set<size_t>>::const_iterator it = usetgrid.begin(); it != usetgrid.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<size_t>(cout, ", "));
		cout << endl;
	}
	a.clear();
	a = {1};
	//	assert(64 == FindConnectedComponents(a));
	a.clear();
	a = {3}; // 1 connected component of 2 nodes (0-1). 64 - 2 + 1 = 63
			 //	assert(63 == FindConnectedComponents(a));
	a.clear();
	a = {3, 5}; // [3]: 63, [5]: 63, [3,5]: 1 connected component of 3 nodes (0-1-2). 64-3+1=62. Total: 188
				//	assert(188 == FindConnectedComponents(a));
	a.clear();
	a = {2, 5, 9};
	// assert(504 == FindConnectedComponents(a));
	multiset<long> set{1, 1, 2, 2, 3, 3}, set1{1, 1, 2, 3, 3};
	set.extract(2);
	set.extract(4);
	assert(set1 == set);
	concurrent_set<size_t> cuset;
	size = 1;
	generate_n(inserter(cuset, cuset.begin()), 100, [&size]()
			   { return size++; });
	size = parallel_reduce(cuset.range(), 0 /* Identity for Addition */, [&](concurrent_set<size_t>::range_type const &r, size_t running_total)
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
	// if( x > static_cast<src_T>(limits<dst_T>::max()) )
	ld = numeric_limits<long double>::max();
	ld1 = static_cast<long double>(numeric_limits<size_t>::max());
	cout << fixed << "ld: " << ld << ", ld1: " << ld1 << endl;
	/* https://stackoverflow.com/questions/79602836/c-23-numeric-limitslong-doublemax-use-case#79604603
	if( x > static_cast<src_T>(limits<dst_T>::max()) ) it's out of range
	*/
	assert(ld > static_cast<long double>(numeric_limits<size_t>::max())); // overflow!
	size = numeric_limits<size_t>::max();
	size1 = static_cast<size_t>(numeric_limits<long double>::max());
	cout << fixed << "size: " << size << ", size1: " << size1 << endl;
#if defined(__GNUC__) || defined(__GNUG__)
	// Only works when long double has a size greater than 64 bits.
	assert(!(size > static_cast<size_t>(numeric_limits<long double>::max()))); // No overflow!
#endif
	/***** The End *****/
	cout << "Press ENTER to exit";
	getline(cin, str);
	return 0;
}