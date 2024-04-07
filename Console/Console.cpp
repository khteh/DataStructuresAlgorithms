// ConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Console.h"
using namespace std;
namespace ranges = std::ranges;
#if defined(__GNUC__) || defined(__GNUG__)
using namespace tbb;
#endif
int main(int argc, char *argv[])
{
	string str, str1;
	size_t size;
	long l;
	random_device device;
	// Fourth run: "warm-up" sequence as as seed; different each run.
	// Advanced uses. Allows more than 32 bits of randomness.
	vector<unsigned int> seeds(mt19937_64::state_size);
	ranges::generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	int i, j, *iPtr;
	unsigned int ui;
	unsigned long long mask = 0;
	set<size_t> uset;
	vector<string> strings, strings1;
	set<string> stringset, stringset1;
	set<long> aset;
	vector<long> a, b, sortData;
	vector<long double> ld;
	vector<int> data, data1;
	vector<size_t> udata, udata1;
	vector<unsigned long long> ull;
	priority_queue<long, deque<long>> maxHeap;
	priority_queue<long, deque<long>, greater<long>> minHeap;
	PriorityQueueMedian<long> pqueue;
	vector<vector<unsigned long>> grid;
	vector<vector<long>> grid1, grid2;
	vector<vector<string>> sgrid;
	vector<vector<size_t>> ugrid, ugrid1;
	ExceptionTest();
	TestRandom();
	KDTreeTests();
	stringset.erase("Does not exist");
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
	cout << "sizeof(char[8]): " << sizeof(cstr) << endl;
	cout << "sizeof(void*): " << sizeof(void *) << endl;
	cout << "sizeof(long double): " << sizeof(long double) << endl;
	assert(sizeof(char) == 1);
	assert(sizeof(short) == 2);
	assert(sizeof(int) == 4);
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
	cout << "https://en.wikipedia.org/wiki/Machine_epsilon: Float: " << numeric_limits<float>::epsilon() << ", Double: " << numeric_limits<double>::epsilon() << endl;
	cout << "Machine Epsilon: Float: " << MachineEpsilon((float)1) << ", Approximation: " << FloatMachineEpsilonApproximation() << endl;
	cout << "Machine Epsilon: Double: " << MachineEpsilon((double)1) << ", Approximation: " << MachineEpsilonApproximation() << endl;
	cout << "numeric_limits<int>::min(): " << numeric_limits<int>::min() << " (0x" << hex << numeric_limits<int>::min() << dec << "), numeric_limits<int>::max(): " << numeric_limits<int>::max() << " (0x" << hex << numeric_limits<int>::max() << "), numeric_limits<int>::min() *-1 = " << numeric_limits<int>::min() * -1 << endl;
	cout << "numeric_limits<long>::min(): " << numeric_limits<long>::min() << " (0x" << hex << numeric_limits<long>::min() << dec << "), numeric_limits<long>::max(): " << numeric_limits<long>::max() << " (0x" << hex << numeric_limits<long>::max() << dec << "), numeric_limits<long>::min() * -1 = " << numeric_limits<long>::min() * -1 << endl;
	assert(numeric_limits<int>::min() * -1 == numeric_limits<int>::min()); // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
	// assert(numeric_limits<int>::min() / -1 == numeric_limits<int>::min()); Integer overflow as 0x8000_0000 positive is > numeric_limits<int>::max()
	assert(numeric_limits<int>::max() * -1 == numeric_limits<int>::min() + 1); // 0x7FFFF_FFFF * -1 = -0x7FFF_FFFF = 0x8000_0001
	assert(numeric_limits<long>::min() * -1 == numeric_limits<long>::min());   // 0x8000_0000 * -1 = 0xFFFF_FFFF_8000_0000
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
	/* (a/b)*b + a%b = a
	 * -3/2 = -1 => *b = -2 => -2 + a%b = -3 => a%b = -3 + 2 = -1
	 * 3/-2 = -1 => *b = 2 => 2 + a%b = 3 => a%b = 1
	 * -3/-2 = 1 => *b = -2 => -2 + a%b = -3 => a%b = -3 + 2 = -1
	 */
	assert(-3 % 2 == -1);
	assert(3 % -2 == 1);
	assert(-3 % -2 == -1);
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

	i = 0x80000000L;
	j = 1;
	assert(j == (i - 0x7FFFFFFF));
	i = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	assert(j == (i - 0x7FFFFFFF));

	size_t ul = numeric_limits<size_t>::max() + 1;
	assert(!ul);
	cout << "int -" << hex << i << ": " << -i << dec << " " << -i << ", ~" << i << ": " << hex << ~i << " " << dec << ~i << endl;
	ul = 3;
	// cout << "uint -" << hex << ui << ": " << -ui << dec << " " << -ui << ", ~" << ui << ": " << hex << ~ui << " " << dec << ~ui << endl;
	assert(1 == abs(-INT_MIN - 0x7FFFFFFF));
	assert(1 == abs(0x7FFFFFFF - -INT_MIN));

	/*
	 * 0x8000_0000 + 1 = -0x7FFF_FFFF = 0x8000_0001
	 * 0x8000_0000 - 1 = -0x8000_0001 = 0x7FFF_FFFF
	 */
	i = 0x80000000;
	j = i + 1;
	assert(j == 0x80000001);
	cout << i << " 0x" << hex << i << " + 1 = 0x" << j << dec << " " << j << endl;
	i = 0x80000000;
	j = i - 1;
	assert(j == 0x7FFFFFFF);
	cout << i << " 0x" << hex << i << " - 1 = 0x" << j << dec << " " << j << endl;
	a.resize(10);
	ranges::generate(a, [n = 1]() mutable
					 { return n++; });
	for (size_t i = 0; i < a.size(); i++)
		assert(a[i] == i + 1);
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
	vector<vector<char>> maze;
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

	str = "Hello World!!!";
	RemoveDuplicateCharacters(str);
	assert(str == "Helo Wrd!");
	str = "aaaaa";
	RemoveDuplicateCharacters(str);
	assert(str == "a");
	str = "abcd";
	RemoveDuplicateCharacters(str);
	assert(str == "abcd");
	str = "";
	RemoveDuplicateCharacters(str);
	assert(str == "");
	str = "aaaabbbbcccc";
	RemoveDuplicateCharacters(str);
	assert(str == "abc");
	str = "abababab";
	RemoveDuplicateCharacters(str);
	assert(str == "ab");
	str = "bcabc";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "abc");
	str = "abdcb";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "abdc");
	str = "abacb";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "abc");
	str = "adcba";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "adcb");
	str = "cbacdcbc";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "acdb");
	str = "cbacdbcd";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "abcd");
	str = "cbaidbcj";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "aidbcj");
	str = "cdadabcc";
	RemoveDuplicateCharactersLexicographicalOrder(str);
	assert(str == "adbc");
	assert(isAdditiveNumber(string("123")));
	assert(isAdditiveNumber(string("123581321")));
	assert(isAdditiveNumber(string("199100199")));
	assert(!isAdditiveNumber(string("1203")));
	assert(!isAdditiveNumber(string("1023")));
	assert(!isAdditiveNumber(string("0123")));
	str = "Hello World!!!";
	str1 = "llo World!!!He";
	assert(AreRotatedStrings(str, str1, 2));
	if (AreRotatedStrings(str, str1, 2))
		cout << str << " and " << str1 << " are rotated by 2 places" << endl;
	udata.clear();
	udata = {3, 1, 2};
	assert(SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = {1, 3, 4, 2};
	assert(SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = {1, 2, 3, 5, 4};
	assert(!SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = {4, 1, 3, 2};
	assert(SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = {1, 6, 5, 2, 3, 4};
	assert(!SolvabilityOfTheTilesGame(udata));
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
	assert(factorial(1) == 1);
	assert(factorial(2) == 2);
	assert(factorial(3) == 6);
	assert(factorial(4) == 24);
	assert(factorial(5) == 120);
	assert(factorial(20) == 2432902008176640000);
	assert(SequenceSum(0) == 0);
	assert(SequenceSum(1) == 1);
	assert(SequenceSum(5) == 15);
	assert(fibonacci(-1) == -1);
	assert(fibonacci(0) == 0);
	assert(fibonacci(1) == 1);
	assert(fibonacci(2) == 1);
	assert(fibonacci(3) == 2);
	assert(fibonacci(4) == 3);
	assert(fibonacci(5) == 5);
	assert(fibonacci(6) == 8);
	assert(fibonacci(7) == 13);
	assert(fibonacci(8) == 21);
	assert(fibonacci(9) == 34);
	// assert(fibonacci(90) == 2880067194370816120ULL); Times out!!!
	assert(fibonacciModified(0, 1, 4) == "5");
	assert(fibonacciModified(0, 1, 5) == "27");
	assert(fibonacciModified(0, 1, 6) == "734");
	assert(fibonacciModified(0, 1, 7) == "538783");
	assert(fibonacciModified(0, 1, 8) == "290287121823");
	assert(fibonacciModified(0, 1, 9) == "84266613096281243382112");
	assert(fibonacciModified(2, 0, 0) == "2");
	assert(fibonacciModified(2, 0, 1) == "0");
	assert(fibonacciModified(2, 0, 2) == "2");
	assert(fibonacciModified(2, 0, 3) == "4");
	assert(fibonacciModified(2, 0, 4) == "18");
	assert(fibonacciModified(2, 0, 5) == "328");
	assert(fibonacciModified(2, 0, 6) == "107602");
	assert(fibonacciModified(2, 0, 7) == "11578190732");
	assert(fibonacciModified(2, 0, 11) == "104292047421056066715537698951727494083004264929891558279344228228718658019003171882044298756195662458280101226593033166933803327203745068186400974453022429724308");

	ostringstream oss;
	unsigned long long factorialResult = factorial(26);
	cout << "26!: " << setiosflags(ios::fixed) << factorialResult << endl;
	assert(FactorialTrailingZeroesCount(10) == 2);
	assert(FactorialTrailingZeroesCount(25) == 6);
	assert(FactorialTrailingZeroesCount(26) == 6);
	cout << "10!: " << (double)factorial(10) << " has " << FactorialTrailingZeroesCount(10) << " trailing zeroes." << endl;
	cout << "25!: " << (double)factorial(25) << " has " << FactorialTrailingZeroesCount(25) << " trailing zeroes." << endl;
	cout << "26!: " << (double)factorial(26) << " has " << FactorialTrailingZeroesCount(26) << " trailing zeroes." << endl;
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
	// 0 1 2 3 4 5 6 7 8 9
	//         ^ (10 / 2 - 1)
	// (0,9), (0,8)			2
	// (1,9), (1,8), (1,7), 3
	// (2,9), (2,8), (2,7), (2,6), 4
	// (3,9), (3,8), (3,7), (3,6), (3,5) 5
	// (4,9), (4,8), (4,7), (4,6), (4,5), (4,4) 6
	// (5,9), (5,8), (5,7), (5,6), (5,5) 5
	// (6,9), (6,8), (6,7), (6,6) 4
	// (7,9), (7,8), (7,7) 3
	// (8,9), (8,8) 2
	// (9,9) 1
	// Count = 35
	a.clear();
	a.resize(10);
	iota(a.begin(), a.end(), 0);
	assert(greaterthansumpairs(a, 8) == 35);

	// 0 1 2 3 4 5 6 7 8 9 10
	//         ^ (11 / 2 - 1)
	// (0,10), (0,9), (0,8)	3
	// (1,10), (1,9), (1,8), (1,7), 4
	// (2,10), (2,9), (2,8), (2,7), (2,6), 5
	// (3,10), (3,9), (3,8), (3,7), (3,6), (3,5) 6
	// (4,10), (4,9), (4,8), (4,7), (4,6), (4,5), (4,4) 7
	// (5,10), (5,9), (5,8), (5,7), (5,6), (5,5) 6
	// (6,10), (6,9), (6,8), (6,7), (6,6) 5
	// (7,10), (7,9), (7,8), (7,7) 4
	// (8,10), (8,9), (8,8) 3
	// (9,10), (9,9) 2
	// Count = 45
	a.clear();
	a.resize(11);
	iota(a.begin(), a.end(), 0);
	assert(greaterthansumpairs(a, 8) == 45);

	// Test Recursive algorithm
	strings.clear();
	parentheses(strings, 2);
	strings1 = {"(())", "()()"};
	assert(strings.size() == 2);
	assert(strings1 == strings);

	strings.clear();
	parentheses(strings, 3);
	assert(strings.size() == 5);
	strings1.clear();
	strings1 = {"((()))", "(()())", "(())()", "()(())", "()()()"};
	assert(strings1 == strings);
	assert(LongestValidParentheses(string("(")) == 0);
	assert(LongestValidParentheses(string("((()")) == 2);
	assert(LongestValidParentheses(string("())()")) == 2);
	assert(LongestValidParentheses(string("()(()")) == 2);
	assert(LongestValidParentheses(string(")()())")) == 4);
	assert(LongestValidParentheses(string("()(()))))")) == 6);
	assert(LongestValidParentheses(string(")))(((")) == 0);
	assert(LongestValidParentheses(string(")()()(((()")) == 4);
	assert(LongestValidParentheses(string("))()(()(()")) == 2);
	assert(LongestValidParentheses(string(")())((()))")) == 6);
	assert(LongestValidParentheses(string("(()))))(()((()))")) == 8);

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
		assert(towers[0]->TopDisk() == i);
	}
	assert(!towers[0]->isEmpty());
	assert(towers[1]->isEmpty());
	assert(towers[2]->isEmpty());
	size = towers[0]->MoveDisks(2, towers[2], towers[1]);
	assert(size == 3); // size = #moves
	assert(towers[0]->isEmpty());
	assert(towers[1]->isEmpty());
	assert(!towers[2]->isEmpty());
	for (i = 0; i < 3; i++)
		towers[i]->Clear();
	for (i = 10; i > 0; i--) // Smallest disk is "1"
	{
		towers[0]->Add(i);
		assert(towers[0]->TopDisk() == i);
	}
	assert(!towers[0]->isEmpty());
	assert(towers[1]->isEmpty());
	assert(towers[2]->isEmpty());
	cout << "Tower 0 before move: " << endl;
	towers[0]->print();
	size = towers[0]->MoveDisks(5, towers[2], towers[1]);
	cout << "Tower 0,1,2 after " << size << " moves: " << endl;
	towers[0]->print();
	assert(towers[0]->TopDisk() == 6);
	towers[1]->print();
	assert(towers[1]->TopDisk() == numeric_limits<size_t>::max());
	towers[2]->print();
	assert(towers[2]->TopDisk() == 1);
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
	iota(cards.begin(), cards.end(), 0);
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
#ifdef _MSC_VER
	long sum = parallel_reduce(a.begin(), a.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	long sum = parallel_reduce(
		blocked_range<long>(0, a.size()), 0,
		[&](tbb::blocked_range<long> r, long running_total)
		{
			for (int i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		std::plus<long>());
#endif
	assert(sum == 123);

	a.clear();
	b.clear();
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
#ifdef _MSC_VER
	sum = parallel_reduce(a.begin() + 2, a.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	sum = parallel_reduce(
		blocked_range<long>(2, a.size()), 0,
		[&](tbb::blocked_range<long> r, long running_total)
		{
			for (int i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		std::plus<long>());
#endif
	assert(sum == 3);

	a.clear();
	b.clear();
	a.resize(10);
	ranges::generate(a, [n = 1]() mutable
					 { return n++; });
#ifdef _MSC_VER
	sum = parallel_reduce(a.begin(), a.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	sum = parallel_reduce(
		blocked_range<long>(0, a.size()), 0,
		[&](tbb::blocked_range<long> r, long running_total)
		{
			for (int i = r.begin(); i < r.end(); i++)
				running_total += a[i];
			return running_total;
		},
		std::plus<long>());
#endif
	assert(sum == 55);
	a.clear();
	b.clear();
	a = {1, 7, 15, 29, 11, 9};
	EqualAverageDivide(a, b);
	assert(b.size() == 2);
	cout << "Left part: ";
#ifdef _MSC_VER
	sum = parallel_reduce(b.begin(), b.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	sum = parallel_reduce(
		blocked_range<long>(0, b.size()), 0,
		[&](tbb::blocked_range<long> r, long running_total)
		{
			for (int i = r.begin(); i < r.end(); ++i)
				running_total += b[i];
			return running_total;
		},
		std::plus<long>());
#endif
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
	assert(stringset1.find("cdf") != stringset1.end());
	stringset1.clear();
	FindPattern("acc", stringset, stringset1);
	assert(stringset1.size() == 2);
	assert(stringset1.find("too") != stringset1.end());
	assert(stringset1.find("paa") != stringset1.end());
	str = "1024";
	str1 = "2048";
	istringstream iss1(str), iss2(str1);
	cout << iss2.str() << " - " << iss1.str() << " = " << subtract(iss2, iss1) << endl;

	// N-Gram test
	set<string> ngrams = intersectionNgram(string("This is a dog"), string("This is a cat"), 2);
	assert(ngrams.size() == 2);
	assert(ngrams.find("This is") != ngrams.end());
	assert(ngrams.find("is a") != ngrams.end());
	ngrams = intersectionNgram(string("This is a dog"), string("This is a cat"), 3);
	assert(ngrams.size() == 1);
	assert(ngrams.find("This is a") != ngrams.end());
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
	cout << numeric_limits<int>::lowest() << endl;
	IntervalMap<int, char> imap(0);
	imap.emplace(0, 2, 'A'); // [0,1]: 'A'
	imap.emplace(4, 6, 'A'); // [4,5]: 'A'
	imap.emplace(2, 4, 'A'); // [2,3]: 'A'
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
	assert(SherlockValidString("abcdefghhgfedecba"));
	assert(!SherlockValidString("aabbcd"));
	assert(!SherlockValidString("aaaabbcc"));
	assert(!SherlockValidString("xxxaabbccrry"));
	assert(SherlockValidString("ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd"));
	str = "if man was meant to stay on the ground god would have given us roots";
	assert(encryption(str) == "imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau");
	a.clear();
	a = {3, 1, 5, 4, 2};
	assert(calculateMedian(a) == 3);
	a.clear();
	a = {3, 1, 5, 4, 2, 6};
	assert(calculateMedian(a) == 3);
	assert(timeInWords(5, 47) == "thirteen minutes to six");
	assert(timeInWords(12, 29) == "twenty nine minutes past twelve");
	assert(timeInWords(6, 30) == "half past six");
	assert(timeInWords(1, 1) == "one minute past one");
	assert(BeautifulQuadruples(1, 1, 1, 1) == 0);
	assert(BeautifulQuadruples(1, 2, 3, 4) == 11);
	assert(BeautifulQuadruples(3, 3, 3, 3) == 9);
	vector<string> paths = findShortestPath(5, 4, 1, 0, 3);
	assert(paths.size() == 2);
	assert(paths[0] == "2");
	assert(paths[1] == "UR UR");
	paths = findShortestPath(7, 6, 6, 0, 1);
	assert(paths.size() == 2);
	assert(paths[0] == "4");
	assert(paths[1] == "UL UL UL L");
	paths = findShortestPath(6, 5, 1, 0, 5);
	assert(paths.size() == 1);
	assert(paths[0] == "Impossible");
	paths = findShortestPath(7, 0, 3, 4, 3);
	assert(paths.size() == 2);
	assert(paths[0] == "2");
	assert(paths[1] == "LR LL");
	paths = findShortestPath(150, 24, 15, 46, 102);
	assert(paths.size() == 2);
	assert(paths[0] == "49");
	assert(paths[1] == "R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R LR LR LR LR LR LR LR LR LR LR LR");
	paths = findShortestPath(70, 7, 15, 67, 3);
	assert(paths.size() == 2);
	assert(paths[0] == "30");
	assert(paths[1] == "LR LR LR LR LR LR LR LR LR LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL");
	paths = findShortestPath(100, 2, 24, 92, 45);
	assert(paths.size() == 2);
	assert(paths[0] == "45");
	assert(paths[1] == "LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LL LL LL LL LL LL LL LL LL LL LL LL");

	vector<long> from = {1, 3, 1, 4, 2};
	vector<long> to = {2, 5, 4, 5, 3};
	vector<long> weights = {60, 70, 120, 150, 80};
	assert(getLowestPathCost(5, from, to, weights) == 80);

	from.clear();
	to.clear();
	weights.clear();
	from = {1, 2, 1, 3};
	to = {2, 4, 3, 4};
	weights = {20, 30, 5, 40};
	assert(getLowestPathCost(4, from, to, weights) == 30);

	from.clear();
	to.clear();
	weights.clear();
	from = {1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 9};
	to = {2, 3, 4, 5, 6, 7, 8, 9, 10, 3, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10, 5, 6, 7, 8, 9, 10, 6, 7, 8, 9, 10, 7, 8, 9, 10, 8, 9, 10, 9, 10, 10};
	weights = {6337, 1594, 3766, 3645, 75, 5877, 8561, 242, 6386, 3331, 4194, 8069, 3934, 101, 8536, 6963, 9303, 7639, 8512, 1330, 6458, 1180, 3913, 1565, 9488, 1369, 8066, 9439, 7510, 6833, 4215, 194, 4774, 4328, 187, 1196, 200, 8743, 1433, 2933, 2069, 1974, 7349, 2351, 8423};
	assert(from.size() == 45);
	assert(to.size() == 45);
	assert(weights.size() == 45);
	assert(getLowestPathCost(10, from, to, weights) == 1196);

	assert(cipher(7, 4, string("1110101001")) == "1001011");
	assert(cipher(4, 5, string("11000110")) == "1010");
	assert(DecryptPassword(string("43Ah*ck0rr0nk")) == "hAck3rr4nk");
	assert(DecryptPassword(string("51Pa*0Lp*0e")) == "aP1pL5e");
	udata.clear();
	assert(substrings(string("123")) == 164);
	assert(substrings(string("1234")) == 1670);
	assert(substrings(string("972698438521")) == 445677619);
	strings.clear();
	strings = {"GGGGGGGGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GGGGGGGGG"};
	assert(TwoCrosses(strings) == 1);
	strings = {"GGGGGGG", "BGBBBBG", "BGBBBBG", "GGGGGGG", "GGGGGGG", "BGBBBBG"};
	assert(TwoCrosses(strings) == 5);
	strings = {"GBGBGGB", "GBGBGGB", "GBGBGGB", "GGGGGGG", "GGGGGGG", "GBGBGGB", "GBGBGGB"};
	assert(TwoCrosses(strings) == 45);
	strings = {"GGGGGGGG", "GBGBGGBG", "GBGBGGBG", "GGGGGGGG", "GBGBGGBG", "GGGGGGGG", "GBGBGGBG", "GGGGGGGG"};
	assert(TwoCrosses(strings) == 81);
	strings = {"GGGGGGGGGG", "GBBBBBBGGG", "GGGGGGGGGG", "GGGGGGGGGG", "GBBBBBBGGG", "GGGGGGGGGG", "GBBBBBBGGG", "GBBBBBBGGG", "GGGGGGGGGG"};
	assert(TwoCrosses(strings) == 45);
	strings = {"BBBBBGGBGG", "GGGGGGGGGG", "GGGGGGGGGG", "BBBBBGGBGG", "BBBBBGGBGG", "GGGGGGGGGG", "BBBBBGGBGG", "GGGGGGGGGG", "BBBBBGGBGG", "GGGGGGGGGG"};
	assert(TwoCrosses(strings) == 85);
	strings = {"GGGGGGGGGGGG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GGGGGGGGGGGG", "GBGGBBBBBBBG"};
	assert(TwoCrosses(strings) == 81);
	strings = {"GGGGGGGGGGGG", "GGGGGGGGGGGG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG"};
	assert(TwoCrosses(strings) == 189);
	strings = {"BGB", "GGG", "BGB", "BGB", "GGG", "BGB"};
	assert(TwoCrosses(strings) == 25);
	strings = {"BGBBGB", "GGGGGG", "BGBBGB"};
	assert(TwoCrosses(strings) == 25);
	a = absolutePermutation(10, 0);
	b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	assert(a == b);
	a = absolutePermutation(10, 1);
	b = {2, 1, 4, 3, 6, 5, 8, 7, 10, 9};
	assert(a == b);
	strings = {".......", "...O...", "....O..", ".......", "OO.....", "OO....."};
	strings1 = {"OOO.OOO", "OO...OO", "OOO...O", "..OO.OO", "...OOOO", "...OOOO"};
	assert(bomberMan(3, strings) == strings1);
	assert(FindSubsequenceRecursive(string("1221"), string("12")) == 2);
	assert(FindSubsequenceRecursive(string("1234"), string("56")) == 0);
	assert(FindSubsequenceRecursive(string("kkkkkkz"), string("kkkk")) == 15);
	assert(shortPalindrome(string("kkkkkkz")) == 15);
	assert(shortPalindrome(string("ghhggh")) == 4);
	assert(shortPalindrome(string("cbbdcacccdaddbaabbaacbacacaaddaaacdbccccccbbadbbcdddddddaccbdbddcbacaaadbbdcbcbcdabdddbbcdccaacdccab")) == 242745);
	strings.clear();
	vector<vector<size_t>> ladders = {{32, 62}, {42, 68}, {12, 98}};
	vector<vector<size_t>> snakes = {{95, 13}, {97, 25}, {93, 37}, {79, 27}, {75, 19}, {49, 47}, {67, 17}};
	assert(SnakesAndLaddersGame(ladders, snakes) == 3);
	assert(SnakesAndLaddersGameFast(ladders, snakes) == 3);
	vector<vector<size_t>> ladders1 = {{8, 52}, {6, 80}, {26, 42}, {2, 72}};
	vector<vector<size_t>> snakes1 = {{51, 19}, {39, 11}, {37, 29}, {81, 3}, {59, 5}, {79, 23}, {53, 7}, {43, 33}, {77, 21}};
	assert(SnakesAndLaddersGame(ladders1, snakes1) == 5);
	assert(SnakesAndLaddersGameFast(ladders1, snakes1) == 5);
	vector<vector<size_t>> ladders2 = {{3, 5}, {7, 8}, {44, 56}, {36, 54}, {88, 91}, {77, 83}, {2, 4}, {9, 99}, {45, 78}, {31, 75}};
	vector<vector<size_t>> snakes2 = {{10, 6}, {95, 90}, {96, 30}, {97, 52}, {98, 86}};
	assert(SnakesAndLaddersGame(ladders2, snakes2) == 3);
	assert(SnakesAndLaddersGameFast(ladders2, snakes2) == 3);
	vector<vector<size_t>> ladders3 = {{3, 54}, {37, 100}};
	vector<vector<size_t>> snakes3 = {{56, 33}};
	assert(SnakesAndLaddersGame(ladders3, snakes3) == 3);
	assert(SnakesAndLaddersGameFast(ladders3, snakes3) == 3);
	vector<vector<size_t>> ladders4 = {{5, 6}};
	vector<vector<size_t>> snakes4 = {{97, 95}};
	assert(SnakesAndLaddersGameFast(ladders4, snakes4) == 17);
	vector<vector<size_t>> ladders5 = {{3, 90}};
	vector<vector<size_t>> snakes5 = {{99, 10}, {97, 20}, {98, 30}, {96, 40}, {95, 50}, {94, 60}, {93, 70}};
	// assert(SnakesAndLaddersGame(ladders5, snakes5) == 0); // Impossible. Times out!
	assert(SnakesAndLaddersGameFast(ladders5, snakes5) == 0); // Impossible
	assert(LengthOfLongestUniqueSubstring(string("abcabc")) == 3);
	assert(LengthOfLongestUniqueSubstring(string("aaa")) == 1);
	assert(LengthOfLongestUniqueSubstring(string("abcdef")) == 6);
	assert(LengthOfLongestUniqueSubstring(string("dvdf")) == 3);
	assert(LengthOfLongestUniqueSubstring(string("abcabcbb")) == 3);
	assert(LengthOfLongestUniqueSubstring(string("tmmzuxt")) == 5);
	assert(LengthOfLongestUniqueSubstring(string("pwwkew")) == 3);
	assert(LengthOfLongestUniqueSubstring(string("ohvhjdml")) == 6);
	assert(LengthOfLongestUniqueSubstring(string("vqblqcb")) == 4);
	assert(zigzagconvert(string("PAYPALISHIRING"), 3) == "PAHNAPLSIIGYIR");
	assert(zigzagconvert(string("AB"), 1) == "AB");
	assert(numberToRoman(4) == "IV");
	assert(numberToRoman(9) == "IX");
	assert(numberToRoman(40) == "XL");
	assert(numberToRoman(90) == "XC");
	assert(numberToRoman(400) == "CD");
	assert(numberToRoman(900) == "CM");
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
	assert(BasicCalculator(string("3+2*2-1")) == 6);
	assert(BasicCalculator(string("3+2")) == 5);
	assert(BasicCalculator(string("3-2")) == 1);
	assert(BasicCalculator(string("3*2+2")) == 8);
	assert(BasicCalculator(string("3+2-4*5")) == -15);
	assert(BasicCalculator(string("3*2+5/4")) == 7);
	a.clear();
	a = {1, 2, 3, 4};
	a = productExceptSelf(a);
	b.clear();
	b = {24, 12, 8, 6};
	assert(!a.empty());
	assert(a.size() == 4);
	assert(b == a);
	strings = PhoneKeyLetters(string("23"));
	assert(strings.size() == 9);
	strings1 = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
	assert(strings1 == strings);
	strings = PhoneKeyLetters(string(""));
	assert(strings.empty());
	strings = PhoneKeyLetters(string("2"));
	assert(strings.size() == 3);
	strings1 = {"a", "b", "c"};
	strings = PhoneKeyLetters(string("358"));
	assert(strings.size() == 27);
	strings1 = {"djt", "dkt", "dlt", "ejt", "ekt", "elt", "fjt", "fkt", "flt", "dju", "dku", "dlu", "eju", "eku", "elu", "fju", "fku", "flu", "djv", "dkv", "dlv", "ejv", "ekv", "elv", "fjv", "fkv", "flv"};
	assert(strings1 == strings);
	strings = PhoneKeyLetters(string("5678"));
	assert(strings.size() == 108);
	stringset = {"Hello", "World"};
	strings1 = wordBreakDFS(string("HelloWorld"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 1);
	assert(strings1[0] == "Hello World");
	strings1.clear();
	stringset.clear();
	stringset = {"cats", "dog", "sand", "and", "cat"};
	strings1 = wordBreakDFS(string("catsandog"), stringset);
	assert(strings1.empty());
	strings1 = wordBreakDFS(string("catsanddog"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	strings1 = wordBreakDFS(string("catanddog"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 1);

	strings1.clear();
	stringset.clear();
	stringset = {"apple", "pen"};
	strings1 = wordBreakDFS(string("applepenapple"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 1);
	assert(strings1[0] == "apple pen apple");

	strings1.clear();
	stringset.clear();
	stringset = {"aaaa", "aaa"};
	strings1 = wordBreakDFS(string("aaaaaaa"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	a.clear();
	a.clear();
	a = diffWaysToCompute("2-1-1");
	assert(!a.empty());
	assert(a.size() == 2);
	a.clear();
	a = diffWaysToCompute("2*3-4*5");
	assert(!a.empty());
	assert(a.size() == 5);
	assert(getHint(string("6244988279"), string("3819888600")) == "2A2B");
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
	assert(eggDrops(123, 0) == 0);
	assert(eggDrops(123, 1) == 1);
	assert(eggDrops(1, 123) == 123);
	assert(eggDrops(2, 2) == 2);
	assert(eggDrops(3, 6) == 3);
	assert(fizzBuzz(3) == vector<string>({"1", "2", "Fizz"}));
	assert(fizzBuzz(5) == vector<string>({"1", "2", "Fizz", "4", "Buzz"}));
	assert(fizzBuzz(10) == vector<string>({"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz"}));
	assert(fizzBuzz(15) == vector<string>({"1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz"}));
	Graph<size_t, size_t> graph;
	vector<vector<size_t>> edges;
	edges.clear();
	edges = {{1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2}};
	assert("1000100" == RoadsInHackerland(5, edges));
	assert("1000100" == RoadsInHackerland1(5, edges));
	edges.clear();
	edges = {{1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2}};
	assert("1000100" == RoadsInHackerland2(5, edges));
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
	assert("10100011101101000001001000" == RoadsInHackerland1(18, edges));
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
	assert("10100011101101000001001000" == RoadsInHackerland2(18, edges));
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
	assert("1010100000000011001101110101111" == RoadsInHackerland1(20, edges));
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
	assert("1010100000000011001101110101111" == RoadsInHackerland2(20, edges));

	a.clear();
	a = {1};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 0);
	a.clear();
	a = {2};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 1);
	a.clear();
	a = {2, 1};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 1);
	a.clear();
	a = {2, 3};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 2);
	a.clear();
	a = {4, 3, 2, 1};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 3);
	a.clear();
	a = {1, 4, 1};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 3);
	a.clear();
	a = {4, 2, 2, 1};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 4);
	a.clear();
	a = {1, 3, 3};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 5);
	a.clear();
	a = {2, 1, 3, 2};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 7);
	a.clear();
	a = {2, 4, 4, 4};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 8);
	a.clear();
	a = {2, 4, 2, 4};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 6);
	a.clear();
	a = {3, 1, 2, 1, 4};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 10);
	a.clear();
	a = {1, 1, 3, 1, 4};
	assert(MoveDisksToTowerOfHanoi1(4, a) == 11);
	a.clear();
	a = {1, 4, 2, 4, 2, 2};
	// assert(MoveDisksToTowerOfHanoi1(4, a) == 14); WIP
	ld.clear();
	ld = {1, 2, 3};
	assert(VectorSlicesSum(ld) == 44);
	ld.clear();
	ld = {1, 3, 6};
	assert(VectorSlicesSum(ld) == 73);
	ld.clear();
	ld = {4, 2, 9, 10, 1};
	assert(VectorSlicesSum(ld) == 971);
	ld.clear();
	ld = {477, 392, 161, 421, 245, 50, 530, 889, 750, 16, 545, 303, 898, 785, 162, 279, 677, 664, 126, 149, 814, 360, 334, 681, 473, 293, 267, 120, 825, 21, 267, 301, 413, 779, 73, 657, 181, 602, 897, 930, 969, 441, 232, 218, 577, 745, 848, 253};
	assert(VectorSlicesSum(ld) == 868784194);
	ld.clear();
	ld = {695, 14, 706, 200, 379, 690, 991, 128, 60, 998, 730, 381, 301, 559, 192, 686, 608, 907, 256, 584, 177, 319, 843, 87, 446, 37, 520, 464, 483, 685, 894, 177, 50, 952, 376, 781, 641, 718, 908, 700, 715, 989, 432, 367, 547, 624, 52, 507, 530, 659, 90, 58, 978, 932, 497, 423, 321, 16, 238, 803, 52, 484, 979, 101, 435, 706, 881, 427, 423, 141, 126, 489, 129, 909, 207, 28, 884, 610, 534};
	assert(VectorSlicesSum(ld) == 818555228);
	ld.clear();
	data.clear();
	a.clear();
	assert(SteadyGene("ACGTCCGT") == 1);
	assert(SteadyGene("AAGTGCCT") == 0);
	assert(SteadyGene("ACTGAAAG") == 2);
	str = "07:05:45PM";
	assert(TwentyFourHourTimeConversion(str) == "19:05:45");
	str = "07:05:45AM";
	assert(TwentyFourHourTimeConversion(str) == "07:05:45");
	strings.clear();
	strings = {"."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"x"};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"....", "..x.", "..x.", "x..."};
	assert(kMarsh(strings) == 10);
	strings.clear();
	strings = {"....", "x.x.", ".x..", "x..."};
	assert(kMarsh(strings) == 4);
	strings.clear();
	strings = {"....", ".x..", ".xx.", "x..."};
	assert(kMarsh(strings) == 4);
	strings.clear();
	strings = {".x", "x."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"x.", "x."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"..", "xx"};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"xx", ".."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"..", ".."};
	assert(kMarsh(strings) == 4);
	strings.clear();
	strings = {"xx", "xx"};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"....", "xxx."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {".x", ".x", ".x", ".."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"x.", "x.", "x.", ".."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"..x..", ".x.x.", "..x.."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"...x...", ".x...x.", "...x..."};
	assert(kMarsh(strings) == 8);
	strings.clear();
	strings = {"...x...", ".x.x.x.", "...x..."};
	assert(kMarsh(strings) == 8);
	strings.clear();
	strings = {".....", ".x.x.", ".....", "....."};
	assert(kMarsh(strings) == 14);
	strings.clear();
	strings = {"..x...", "..x..."};
	assert(kMarsh(strings) == 6);
	strings.clear();
	strings = {"..xx...", "..xx..."};
	assert(kMarsh(strings) == 6);
	strings.clear();
	strings = {"..x.x...", "..x.x..."};
	assert(kMarsh(strings) == 6);
	strings.clear();
	strings = {"x..x", "....", "x..x"};
	assert(kMarsh(strings) == 6);
	strings.clear();
	strings = {"x...x", "..x..", "x...x"};
	assert(kMarsh(strings) == 8);
	strings.clear();
	strings = {"....", "xxxx", "...."};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"....", ".xx.", "...."};
	assert(kMarsh(strings) == 10);
	strings.clear();
	strings = {"xxxx", "x..x", "xxxx"};
	assert(kMarsh(strings) == 0);
	strings.clear();
	strings = {"....", "....", "....", "...."};
	assert(kMarsh(strings) == 12);
	strings.clear();
	strings = {"......", ".xxxx.", ".x..x.", ".x..x.", ".xxxx.", "......"};
	assert(kMarsh(strings) == 20);
	strings.clear();
	strings = {"x.x", ".x.", "x.x"};
	assert(kMarsh(strings) == 0);
	udata.clear();
	assert(NormalPlayNim(udata) == 0);
	udata.clear();
	udata = {1};
	assert(NormalPlayNim(udata) == 1);
	udata.clear();
	udata = {1, 1};
	assert(NormalPlayNim(udata) == 0);
	udata.clear();
	udata = {1, 1, 1};
	assert(NormalPlayNim(udata) == 3); // Take 1 from any of the 3 heaps
	udata.clear();
	udata = {1, 2, 1};
	assert(NormalPlayNim(udata) == 1); // Remove 2 from the heap with 2 elements
	udata.clear();
	udata = {2, 3};
	assert(NormalPlayNim(udata) == 1);
	assert(CounterGame(6));
	assert(!CounterGame(8));
	assert(!CounterGame(132));
	assert(CounterGame(1246326493));
	a.clear();
	a = {1, 1, 5};
	assert(EqualDistribution(a) == 2);
	a.clear();
	a = {2, 2, 3, 7};
	assert(EqualDistribution(a) == 2);
	a.clear();
	a = {10, 7, 12};
	assert(EqualDistribution(a) == 3);
	a.clear();
	a = {1, 2, 3, 4};
	assert(EqualDistribution(a) == 4);
	a.clear();
	a = {851, 183, 48, 473, 610, 678, 725, 87, 95, 50, 311, 258, 854};
#if 0
	assert(EqualDistribution(a) == 927);
	a.clear();
	a = {249, 666, 500, 101, 227, 85, 963, 681, 331, 119, 448, 587, 668, 398, 802};
	assert(EqualDistribution(a) == 1123);
	a.clear();
	a = {512, 125, 928, 381, 890, 90, 512, 789, 469, 473, 908, 990, 195, 763, 102, 643, 458, 366, 684, 857, 126, 534, 974, 875, 459, 892, 686, 373, 127, 297, 576, 991, 774, 856, 372, 664, 946, 237, 806, 767, 62, 714, 758, 258, 477, 860, 253, 287, 579, 289, 496};
	assert(EqualDistribution(a) == 5104);
#endif
	str = "_";
	assert(HappyLadyBugs(str));
	str = "RBRB";
	assert(!HappyLadyBugs(str));
	str = "aaaa";
	assert(HappyLadyBugs(str));
	str = "aaa";
	assert(HappyLadyBugs(str));
	str = "aa";
	assert(HappyLadyBugs(str));
	str = "a";
	assert(!HappyLadyBugs(str));
	str = "aa_";
	assert(HappyLadyBugs(str));

	ugrid.clear();
	ugrid.resize(0);
	assert(matrix.ChessQueensMoveCount(4, 4, 4, ugrid) == 9);
	ugrid.clear();
	ugrid = {{5, 5}, {4, 2}, {2, 3}};
	assert(matrix.ChessQueensMoveCount(5, 4, 3, ugrid) == 10);
	ugrid.clear();
	assert(matrix.ChessQueensMoveCount(1, 1, 1, ugrid) == 0);
	ugrid.clear();
	ugrid = {{20001, 20002}, {20001, 20004}, {20000, 20003}, {20002, 20003}, {20000, 20004}, {20000, 20002}, {20002, 20004}, {20002, 20002}, {564, 323}};
	assert(matrix.ChessQueensMoveCount(88587, 20001, 20003, ugrid) == 0);
	ugrid.clear();
	ugrid.resize(0);
	assert(matrix.ChessQueensMoveCount(100000, 4187, 5068, ugrid) == 308369);

	a.clear();
	a = {10, 20, 30, 40, 50};
	assert(ActivityNotifications(a, 3) == 1);
	a.clear();
	a = {2, 3, 4, 2, 3, 6, 8, 4, 5};
	assert(ActivityNotifications(a, 5) == 2);
	a.clear();
	a = {1, 2, 3, 4, 4};
	assert(ActivityNotifications(a, 4) == 0);
#if 0
	udata.clear();
	udata = {1, 3, 2};
	assert(PermutationGame(udata) == "Alice");

	udata.clear();
	udata = {5, 3, 2, 1, 4};
	assert(PermutationGame(udata) == "Bob");
#endif
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
	ugrid.clear();
	ugrid = {{1, 2, 10}, {1, 3, 6}, {2, 4, 8}};
	a.clear();
	a = {10l, 16l, 8l, -1l};
	assert(a == ShortestPaths(5, ugrid, 2));
	assert(a == ShortestPaths1(5, ugrid, 2));
	assert(a == ShortestPaths2(5, ugrid, 2));
	ugrid.clear();
	ugrid = {{1, 2, 24}, {1, 4, 20}, {3, 1, 3}, {4, 3, 12}};
	a.clear();
	a = {24l, 3l, 15l};
	assert(a == ShortestPaths(4, ugrid, 1));
	assert(a == ShortestPaths1(4, ugrid, 1));
	assert(a == ShortestPaths2(4, ugrid, 1));
	ugrid.clear();
	ugrid = {
		{1, 7, 45},
		{2, 14, 15},
		{3, 7, 29},
		{4, 1, 48},
		{5, 1, 66},
		{6, 7, 17},
		{7, 14, 15},
		{8, 14, 43},
		{9, 1, 27},
		{10, 1, 33},
		{11, 14, 64},
		{12, 14, 27},
		{13, 7, 66},
		{14, 7, 54},
		{15, 14, 56},
		{16, 7, 21},
		{17, 1, 20},
		{18, 1, 34},
		{19, 7, 52},
		{20, 14, 14},
		{9, 14, 9},
		{15, 1, 39},
		{12, 1, 24},
		{9, 1, 16},
		{1, 2, 33},
		{18, 1, 46},
		{9, 1, 28},
		{15, 14, 3},
		{12, 1, 27},
		{1, 2, 5},
		{15, 1, 34},
		{1, 2, 28},
		{9, 7, 16},
		{3, 7, 23},
		{9, 7, 21},
		{9, 14, 19},
		{3, 1, 20},
		{3, 1, 5},
		{12, 14, 19},
		{3, 14, 2},
		{12, 1, 46},
		{3, 14, 5},
		{9, 14, 44},
		{6, 14, 26},
		{9, 14, 16},
		{9, 14, 34},
		{6, 7, 42},
		{3, 14, 27},
		{1, 7, 9},
		{1, 7, 41},
		{15, 14, 19},
		{12, 7, 13},
		{3, 7, 10},
		{1, 7, 2}};
	a.clear();
	a = {20, 25, 25, 68, 86, 39, 22, 70, 36, 53, 91, 35, 88, 27, 30, 43, 54, 74, 41};
	assert(a == ShortestPaths(20, ugrid, 17));
	assert(a == ShortestPaths1(20, ugrid, 17));
	assert(a == ShortestPaths2(20, ugrid, 17));
	udata.clear();
	ugrid.clear();
	ugrid = {{1, 2},
			 {2, 3},
			 {1, 4}};
	udata = {3, 1, 2};
	assert(udata == UnbeatenPaths(4, ugrid, 1));
	assert(MaxSizePalindromeCount("week", 0, 3) == 2);
	assert(MaxSizePalindromeCount("week", 1, 2) == 1);
	assert(MaxSizePalindromeCount("abab", 0, 3) == 2);
	assert(MaxSizePalindromeCount("wuhmbspjnfviogqzldrcxtaeyk", 20, 20) == 1);
	assert(MaxSizePalindromeCount("wuhmbspjnfviogqzldrcxtaeyk", 3, 4) == 2);
	assert(MaxSizePalindromeCount("daadabbadcabacbcccbdcccdbcccbbaadcbabbdaaaabbbdabdbbdcadaaacaadadacddabbbbbdcccbaabbbacacddbbbcbbdbd", 13, 16) == 2);
	/***** The End *****/
	cout << "Press ENTER to exit";
	getline(cin, str);
	return 0;
}