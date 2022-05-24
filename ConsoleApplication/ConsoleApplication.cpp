﻿// ConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "ConsoleApplication.h"
using namespace std;
namespace ranges = std::ranges;
#if defined(__GNUC__) || defined(__GNUG__)
using namespace tbb;
#endif
int main(int argc, char* argv[])
{
	string line, line1;
	size_t size;
	random_device device;
	// Fourth run: "warm-up" sequence as as seed; different each run.
	// Advanced uses. Allows more than 32 bits of randomness.
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	ranges::generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	int i, j, index, * iPtr;
	unsigned long long mask = 0;
	vector<string> strings, strings1;
	set<string> stringset, stringset1;
	vector<long> a, b, sortData;
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
	line = to_string(0);
	istringstream(line) >> i;
	assert(i == 0);
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

	string str = "m";
	string str1 = str.substr(1);
	assert(str1.empty());
	str1 = str.substr(0, 0);
	assert(str1.empty());
	char cstr[8];
	cout << "sizeof(char[8]): " << sizeof(cstr) << endl;
	cout << "sizeof(void*): " << sizeof(void*) << endl;
	cout << "sizeof(long double): " << sizeof(long double) << endl;
	assert(sizeof(char) == 1);
	assert(sizeof(short) == 2);
	assert(sizeof(int) == 4);
	assert(sizeof(int*) == 8);
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
	cout << "numeric_limits<int>::min(): " << numeric_limits<int>::min() << ", numeric_limits<int>::max(): " << numeric_limits<int>::max() << ", numeric_limits<int>::min() * -1 = " << numeric_limits<int>::min() * -1 << endl;
	cout << "numeric_limits<long>::min(): " << numeric_limits<long>::min() << ", numeric_limits<long>::max(): " << numeric_limits<long>::max() << ", numeric_limits<long>::min() * -1 = " << numeric_limits<long>::min() * -1 << endl;
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
	long long l = i;
	i++;
	l++;
	assert(i == numeric_limits<int>::min());
	assert(i < 0);
	assert((long long)i == 0xFFFFFFFF80000000LL);
	assert(l > 0);
	assert(l == 0x80000000);
	cout << "(int)0x7FFFFFFF + 1: " << i << ", long long: " << (long long)(i) << endl; // sign extended to 64-bit
	cout << "(long long)0x7FFFFFFF + 1: " << l << endl;

	i = 0x80000000;
	l = i;
	assert(l < 0); // sign extended to 64-bit
	assert(l == 0xFFFFFFFF80000000LL);
	i--;
	l--;
	assert(i > 0); // integer overflow
	assert(i == numeric_limits<int>::max());
	assert(l < 0); // sign extended to 64-bit
	assert(l == 0xFFFFFFFF7FFFFFFFLL);
	cout << "(int)0x80000000 - 1: " << i << ", long long: " << (long long)(i) << endl; // integer overflow
	cout << "(long long)0x80000000 - 1: " << l << endl;
	i = 0x80000000;
	j = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	assert(i == j);
	assert(i < 0);
	assert(j < 0);
	cout << "(int)-0x80000000: " << i << endl;
	i = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	l = i;
	assert(l < 0); // sign extended to 64-bit
	assert(l == 0xFFFFFFFF80000000LL);
	i--;
	l--;
	assert(i > 0); // integer overflow
	assert(i == numeric_limits<int>::max());
	assert(l < 0); // sign extended to 64-bit
	assert(l == 0xFFFFFFFF7FFFFFFFLL);
	cout << "(int)0x80000000 - 1: " << i << ", long long: " << (long long)(i) << endl; // integer overflow
	cout << "(long long)0x80000000 - 1: " << l << endl;
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

	l = 0x80000000LL;
	assert(l > 0);
	l--;
	assert(l > 0);
	assert(l == 0x7fffffffL);
	l = -0x80000000LL;
	assert(l == 0xFFFFFFFF80000000);
	assert(l < 0);
	l--;
	assert(l < 0);
	assert(l == 0xFFFFFFFF7FFFFFFFL);

	i = 0x80000000L;
	j = 1;
	assert(j == (i - 0x7FFFFFFF));
	i = -INT_MIN; // https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4146?view=msvc-160
	assert(j == (i - 0x7FFFFFFF));

	size_t ui = numeric_limits<size_t>::max() + 1;
	assert(!ui);
	cout << "int -" << hex << i << ": " << -i << dec << " " << -i << ", ~" << i << ": " << hex << ~i << " " << dec << ~i << endl;
	ui = 3;
	// cout << "uint -" << hex << ui << ": " << -ui << dec << " " << -ui << ", ~" << ui << ": " << hex << ~ui << " " << dec << ~ui << endl;

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
	ranges::generate(a, [n = 1]() mutable { return n++; });
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
	grid = { {1, 3, 5}, {2, 4, 6}, {7, 8, 9} };
	// grid.back() = {7,8,9}
	assert(grid.back().back() == 9);
	grid.clear();
	grid = { {1, 3, 5}, {2, 4, 6}, {7, 8, 9} };
	pathResult_t pathResult = FindMaxPath(grid, 0, 0);
	assert(pathResult.sum == 27);
	cout << "Grid traversal which yields maximum sum " << pathResult.sum << ": " << pathResult.path << endl;

	vector<vector<char>> maze = { {'1', '1', '1', '1', '1'}, {'S', '1', 'X', '1', '1'}, {'1', '1', '1', '1', '1'}, {'X', '1', '1', 'E', '1'}, {'1', '1', '1', '1', 'X'} };
	cout << "maze (" << maze.size() << "): " << endl;
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
	queue<string> mazeResult;
	assert(FindShortestPath(maze, 1, 0, mazeResult, 'E', 'X'));
	cout << "Shortest path: ";
	while (!mazeResult.empty())
	{
		line = mazeResult.front();
		mazeResult.pop();
		cout << line << " ";
	}
	cout << endl;
	grid1 = { {-1, 0, -1}, {-1, -1, -1}, {-1, -1, -1} };
	grid2 = { {1, 0, 1}, {2, 1, 2}, {3, 2, 3} };
	MatrixDistance(grid1, 0, 1);
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
	grid1 = { {1, 3, 5}, {6, 4, 2}, {7, 9, 8} };
	grid2 = { {1, 3, 5}, {6, 4, 2}, {7, 9, 8} };
	MatrixSort(grid1);
	cout << "MatrixSort: " << endl;
	for (size_t i = 0; i < grid1.size(); i++)
	{
		for (size_t j = 0; j < grid1[i].size(); j++)
			cout << grid1[i][j] << " ";
		cout << endl;
	}
	MatrixSortWithHeap(grid2);
	cout << "MatrixSortWithHeap: " << endl;
	for (size_t i = 0; i < grid2.size(); i++)
	{
		for (size_t j = 0; j < grid2[i].size(); j++)
		{
			cout << grid2[i][j] << " ";
			assert(grid1[i][j] == grid2[i][j]);
		}
		cout << endl;
	}
	grid1 = { {0, 0, 1}, {0, 1, 1}, {1, 1, 1} };
	assert(MatrixPatternCount(grid1) == 3);

	grid1 = { {0, 0, 1}, {0, 0, 1}, {1, 1, 1} };
	assert(MatrixPatternCount(grid1) == 4);

	grid1 = { {0, 0, 0, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}, {1, 1, 1, 1} };
	assert(MatrixPatternCount(grid1) == 6);

	grid1 = { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 5);
	assert(ConnectedCellsInAGrid(grid1) == 5);

	grid1 = { {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 8);
	assert(ConnectedCellsInAGrid(grid1) == 8);

	grid1 = { {1, 1, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 1} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 5);
	assert(ConnectedCellsInAGrid(grid1) == 5);

	grid1 = { {0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 0, 1, 1}, {0, 1, 1, 1, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 15);
	assert(ConnectedCellsInAGrid(grid1) == 15);

	grid1 = { {1, 1, 1, 0, 1}, {0, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 1, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 9);
	assert(ConnectedCellsInAGrid(grid1) == 9);

	grid1 = { {1, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 1);
	assert(ConnectedCellsInAGrid(grid1) == 1);

	maze = { {0, 0, 1, 0, 1}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 1}, {0, 1, 1, 0, 0} };
	queue<string> puzzleResult;
	assert(PathExists(maze, 1, 4, 0, 3, puzzleResult, 1));
	cout << "Puzzle path: ";
	while (!puzzleResult.empty())
	{
		line = puzzleResult.front();
		puzzleResult.pop();
		cout << line << " ";
	}
	cout << endl;
	maze = { {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1} };
	queue<string> puzzleResult1;
	assert(!PathExists(maze, 0, 0, 1, 2, puzzleResult1, 1));
	maze.clear();
	maze = { {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'} };
	assert(WordExistsInGrid(maze, string("ABCCED")));
	assert(!WordExistsInGrid(maze, string("ABCB")));
	line = "ab2c3";
	assert(uncompress(line) == "ababcababcababc");
	cout << "uncompress(" << quoted(line) << "): " << uncompress(line) << endl;
	line = "0010110100";
	size = findLongestContiguousPattern(line, '1');
	assert(size == 4);
	assert(line == "0010111100");
	cout << "findLongestContiguousPattern(\"0010110100\", \'1\'): " << line << " size: " << size << endl;
	line = "00101101100";
	size = findLongestContiguousPattern(line, '1');
	assert(size == 5);
	assert(line == "00101111100");
	cout << "findLongestContiguousPattern(\"00101101100\", \'1\'): " << line << " size: " << size << endl;

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
	assert(Min(123, 456) == 123);
	assert(Max(123, 456) == 456);
	assert(gcd(48, 15) == 3);
	assert(gcd(108, 48) == 12);
	assert(gcd(1050, 507) == 3);
	assert(lcm(21, 6) == 42);
	assert(!isUniqueString("Helo World!!!"));
	line = "Hello World!!!";
	reverse(line);
	assert(line == "!!!dlroW olleH");
	line = "The house is blue";
	reverseWords(line);
	assert(line == "blue is house The");
	line = "  The   house is    blue  ";
	reverseWordsTrimmed(line);
	assert(line == "blue is house The");

	line = "Hello World!!!";
	RemoveDuplicateCharacters(line);
	assert(line == "Helo Wrd!");
	line = "aaaaa";
	RemoveDuplicateCharacters(line);
	assert(line == "a");
	line = "abcd";
	RemoveDuplicateCharacters(line);
	assert(line == "abcd");
	line = "";
	RemoveDuplicateCharacters(line);
	assert(line == "");
	line = "aaaabbbbcccc";
	RemoveDuplicateCharacters(line);
	assert(line == "abc");
	line = "abababab";
	RemoveDuplicateCharacters(line);
	assert(line == "ab");
	line = "bcabc";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "abc");
	line = "abdcb";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "abdc");
	line = "abacb";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "abc");
	line = "adcba";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "adcb");
	line = "cbacdcbc";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "acdb");
	line = "cbacdbcd";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "abcd");
	line = "cbaidbcj";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "aidbcj");
	line = "cdadabcc";
	RemoveDuplicateCharactersLexicographicalOrder(line);
	assert(line == "adbc");
	assert(isAdditiveNumber(string("123")));
	assert(isAdditiveNumber(string("123581321")));
	assert(isAdditiveNumber(string("199100199")));
	assert(!isAdditiveNumber(string("1203")));
	assert(!isAdditiveNumber(string("1023")));
	assert(!isAdditiveNumber(string("0123")));
	line = "Hello World!!!";
	line1 = "llo World!!!He";
	assert(AreRotatedStrings(line, line1, 2));
	if (AreRotatedStrings(line, line1, 2))
		cout << line << " and " << line1 << " are rotated by 2 places" << endl;
	udata.clear();
	udata = { 3, 1, 2 };
	assert(SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = { 1, 3, 4, 2 };
	assert(SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = { 1, 2, 3, 5, 4 };
	assert(!SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = { 4, 1, 3, 2 };
	assert(SolvabilityOfTheTilesGame(udata));
	udata.clear();
	udata = { 1, 6, 5, 2, 3, 4 };
	assert(!SolvabilityOfTheTilesGame(udata));
	line = "abcdefcdbacd";
	line1 = "abcd";
	udata = FindSubString(line, line1);
	udata1 = { 0, 6, 7, 8 };
	assert(udata.size() == 4); // 0 6 7 8
	assert(udata1 == udata);

	udata.clear();
	KMPSearch("ABC ABCDAB ABCDABCDABDE", "ABCDABD", udata);
	assert(!udata.empty());
	assert(udata.size() == 1);
	assert(udata[0] == 15);
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
	line = "a";
	assert(CanShuffleWithoutRepeat(line));
	line = "aa";
	assert(!CanShuffleWithoutRepeat(line));
	line = "aab";
	assert(CanShuffleWithoutRepeat(line));
	line = "aaaabbcc";
	assert(CanShuffleWithoutRepeat(line));
	a.clear();
	a = { -2, -3, 4, -1, -2, 1, 5, -3 };
	b.clear();
	long lResult = ConsecutiveLargestSum(a, b);
	assert(lResult == 7);
	cout << "ConsecutiveLargestSum of ";
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, " "));
	cout << ": " << lResult << " (";
	copy(b.begin(), b.end(), ostream_iterator<long>(cout, " "));
	cout << ")" << endl;
	assert(b.size() == 5);
	assert(b[0] == 4);
	assert(b[1] == -1);
	assert(b[2] == -2);
	assert(b[3] == 1);
	assert(b[4] == 5);
	a.clear();
	b.clear();
	a = { 2, 3, -6 };
	lResult = ConsecutiveLargestSum(a, b);
	assert(lResult == 5);
	cout << "ConsecutiveLargestSum of ";
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, " "));
	cout << ": " << lResult << " (";
	copy(b.begin(), b.end(), ostream_iterator<long>(cout, " "));
	cout << ")" << endl;
	assert(b.size() == 2);
	assert(b[0] == 2);
	assert(b[1] == 3);
	a.clear();
	b.clear();
	a = { 2, 3, -6, 4, 5, 6, -20 };
	lResult = ConsecutiveLargestSum(a, b);
	assert(lResult == 15);
	cout << "ConsecutiveLargestSum of ";
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, " "));
	cout << ": " << lResult << " (";
	copy(b.begin(), b.end(), ostream_iterator<long>(cout, " "));
	cout << ")" << endl;
	assert(b.size() == 3);
	assert(b[0] == 4);
	assert(b[1] == 5);
	assert(b[2] == 6);
	a.clear();
	b.clear();
	a = { 2, 3, -2, 4 };
	assert(6 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { -2, 0, -1 };
	assert(0 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { -2, -1, 0 };
	assert(2 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { -3, -1, -1 };
	assert(3 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { 0, 2 };
	assert(2 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { 3, -1, 4 };
	assert(4 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { -1, -1 };
	assert(1 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { 0, -2, -3 };
	assert(6 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { 2, -5, -2, -4, 3 };
	assert(24 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = { 2, 0, -3, 2, 1, 0, 1, -2 };
	assert(2 == ConsecutiveLargestProduct(a));
	a.clear();
	a = { 2, 3, 1, 2, 4, 3 };
	assert(ConsecutiveSumMinCount(7, a) == 2);
	a.clear();
	assert(ConsecutiveSumMinCount(1, a) == -1);
	a.clear();
	a = { 1, 4, 4 };
	assert(ConsecutiveSumMinCount(5, a) == 2);
	assert(ConsecutiveSumMinCount(4, a) == 1);
	//  [−1, −1, 1, −1, 1, 0, 1, −1, −1]: 2 to 8 = 7
	a = { -1, -1, 1, -1, 1, 0, 1, -1, -1 };
	assert(LongestNonNegativeSumSlice(a) == 7);
	a.clear();
	//  [1, 1, −1, −1, −1, −1, −1, 1, 1]: first or last 4
	a = { 1, 1, -1, -1, -1, -1, -1, 1, 1 };
	assert(LongestNonNegativeSumSlice(a) == 4);
	a.clear();
	a = { 0, -1, 0, 0, 1, 0, -1, -1 };
	assert(LongestNonNegativeSumSlice(a) == 6);
	assert(1 == ConsecutiveLargestSum(a, b));
	a.clear();
	a = { -1, -1, -1, -1, -1, -1, 1, 1 };
	assert(LongestNonNegativeSumSlice(a) == 4);
	assert(2 == ConsecutiveLargestSum(a, b));
	a.clear();
	b.clear();
	strings.clear();
	strings = { "Angel", "legnA", "Hello World!!!", "World Hello!!!" };
	cout << "strings without sorted: " << endl;
	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, "\r\n"));
	sort(strings.begin(), strings.end());
	assert(strings[0] == "Angel");
	assert(strings[1] == "Hello World!!!");
	assert(strings[2] == "World Hello!!!");
	assert(strings[3] == "legnA");
	cout << "strings sorted with default comparer: " << endl;
	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, "\r\n"));
	sort(strings.begin(), strings.end(), [](string a, string b) -> bool
		{
			sort(a.begin(), a.end());
			sort(b.begin(), b.end());
			return a < b; });
	assert(strings[0] == "Hello World!!!");
	assert(strings[1] == "World Hello!!!");
	assert(strings[2] == "Angel");
	assert(strings[3] == "legnA");
	cout << "strings sorted with anagrams next to each other: " << endl;
	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, "\r\n"));
	a.clear();
	a = { 0, 1, 2, 7, 10, 11, 12, 20, 25, 26, 27 };
	string strRange = GetRange(a);
	grid1.clear();
	grid1 = { {1, 3}, {2, 6}, {8, 10}, {15, 18} };
	grid2 = MergeIntervals(grid1);
	assert(grid2.size() == 3);
	assert(grid2[0][0] == 1);
	assert(grid2[0][1] == 6);
	assert(grid2[1][0] == 8);
	assert(grid2[1][1] == 10);
	assert(grid2[2][0] == 15);
	assert(grid2[2][1] == 18);
	grid1.clear();
	grid1 = { {1, 4}, {4, 5} };
	grid2 = MergeIntervals(grid1);
	assert(grid2.size() == 1);
	assert(grid2[0][0] == 1);
	assert(grid2[0][1] == 5);
	grid1.clear();
	grid1 = { {2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10} };
	grid2 = MergeIntervals(grid1);
	assert(grid2.size() == 1);
	assert(grid2[0][0] == 1);
	assert(grid2[0][1] == 10);
	assert(strRange == "0 - 2, 7, 10 - 12, 20, 25 - 27");
	cout << "GetRange(\"";
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, ", "));
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
	assert(NumberStringSum(string("1234567890"), string("9876543210")) == "11111111100");
	assert(NumberStringSum(string("123"), string("45")) == "168");
	line = "-4";
	line1 = "5";
	assert(NumberStringMultiplication(line, line1) == "-20");
	line = "3";
	line1 = "-4";
	assert(NumberStringMultiplication(line, line1) == "-12");
	line = "-7";
	line1 = "-8";
	assert(NumberStringMultiplication(line, line1) == "56");
	line = "123456";
	line1 = "654321";
	assert(NumberStringMultiplication(line, line1) == "80779853376");
	line = "456789";
	line1 = "987654";
	assert(NumberStringMultiplication(line, line1) == "451149483006");

	assert(factorial(1) == 1);
	assert(factorial(2) == 2);
	assert(factorial(3) == 6);
	assert(factorial(4) == 24);
	assert(factorial(5) == 120);
	assert(factorial(20) == 2432902008176640000);
	assert(factorialDynamicProgramming(1) == 1);
	assert(factorialDynamicProgramming(2) == 2);
	assert(factorialDynamicProgramming(3) == 6);
	assert(factorialDynamicProgramming(4) == 24);
	assert(factorialDynamicProgramming(5) == 120);
	assert(factorialDynamicProgramming(20) == 2432902008176640000);
#if defined(__GNUC__) || defined(__GNUG__)
	assert(factorialDynamicProgramming(25) == 15511210043330985984000000); // Only 64-bit on GNU C++. "constant too big" compilation error on MSVC
#endif
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
	assert(fibonacciDynamicProgramming(-1) == -1);
	assert(fibonacciDynamicProgramming(0) == 0);
	assert(fibonacciDynamicProgramming(1) == 1);
	assert(fibonacciDynamicProgramming(2) == 1);
	assert(fibonacciDynamicProgramming(3) == 2);
	assert(fibonacciDynamicProgramming(4) == 3);
	assert(fibonacciDynamicProgramming(5) == 5);
	assert(fibonacciDynamicProgramming(6) == 8);
	assert(fibonacciDynamicProgramming(7) == 13);
	assert(fibonacciDynamicProgramming(8) == 21);
	assert(fibonacciDynamicProgramming(9) == 34);
	assert(fibonacciDynamicProgramming(90) == 2880067194370816120ULL);
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

	assert(fibonacciModifiedDynamicProgramming(0, 1, 4) == "5");
	assert(fibonacciModifiedDynamicProgramming(0, 1, 5) == "27");
	assert(fibonacciModifiedDynamicProgramming(0, 1, 6) == "734");
	assert(fibonacciModifiedDynamicProgramming(0, 1, 7) == "538783");
	assert(fibonacciModifiedDynamicProgramming(0, 1, 8) == "290287121823");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 0) == "2");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 1) == "0");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 2) == "2");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 3) == "4");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 4) == "18");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 5) == "328");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 6) == "107602");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 7) == "11578190732");
	assert(fibonacciModifiedDynamicProgramming(2, 0, 11) == "104292047421056066715537698951727494083004264929891558279344228228718658019003171882044298756195662458280101226593033166933803327203745068186400974453022429724308");

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
	ranges::generate(a.begin(), a.begin() + 10, [n = 0]() mutable { return n++; });
	ranges::generate(a.begin() + 10, a.end(), [n = 5]() mutable	{ return n++; });
	b.clear();
	findDistinct(a, b);
	assert(b.size() == 20);

	a.clear();
	b.clear();
	findPrimes(20, a); // Find prime numbers 0 to 20: 2,3,5,7,11,13,17,19
	assert(a.size() == 8);
	a.clear();
	b.clear();
	a = { 15, 10, 3 };
	b = { 75, 30, 5 };
	assert(CommonPrimeDivisors(a, b) == 1);
	a.clear();
	b.clear();
	a = { 7, 17, 5, 3 };
	b = { 7, 11, 5, 2 };
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
	a = { 1, 2, 51, 50, 60, 55, 70, 68, 80, 76, 75, 12, 45 };
	size_t count = LongestAlternatingSubSequence(a, b);
	assert(count == 9);
	assert(b.size() == 9);
	assert(b[0] == 2);
	assert(b.back() == 76);
	cout << "Longest alternating subsequence of ";
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, " "));
	cout << ": ";
	copy(b.begin(), b.end(), ostream_iterator<long>(cout, " "));
	cout << endl;
	ull.clear();
	ull = { 1, 2, 1, 2 };
	unsigned long long findMaxResult = findMax(ull);
	assert(findMaxResult == 9);

	ull.clear();
	ull = { 2, 3, 3, 2 };
	findMaxResult = findMax(ull);
	assert(findMaxResult == 36);

	line = "     Hello     World!!!     ";
	assert(line.size() == 28);
	cout << line << " size: " << line.size();
	trim(line);
	// assert(line == "Hello     World!!!");
	cout << " trim(line): |" << line << "| size: " << line.size() << endl;

	a.clear();
	a = { 1, 2, 3, 4, 5, 6, 5 };
	// 1, 2, 3, 4, 5, 6, 5
	//    6  5  4
	assert(sumpairs(a, 8) == 2);

	a.clear();
	a = { 5, 7, 9, 13, 11, 6, 6, 3, 3 };
	assert(sumpairs(a, 12) == 3);

	// long testData[] = { 92,407,1152,403,1419,689,1029,108,128,1307,300,775,622,730,978,526,943,127,566,869,715,983,820,1394,901,606,497,98,1222,843,600,1153,302,1450,1457,973,1431,217,936,958,1258,970,1155,1061,1341,657,333,1151,790,101,588,263,101,534,747,405,585,111,849,695,1256,1508,139,336,1430,615,1295,550,783,575,992,709,828,1447,1457,738,1024,529,406,164,994,1008,50,811,564,580,952,768,863,1225,251,1032,1460,1558 };
	// vector<int> testDataVector(testData, testData + sizeof(testData) / sizeof(testData[0]));
	// assert(sumpairs(a, 8) == 2);
	a.clear();
	cout << endl;
	a.resize(10);
	iota(a.begin(), a.end(), 0);
	assert(sumpairs(a, 10) == 4);
	a.clear();
	a = { -1, 0, 1, 2, -1, -4 };
	grid1 = { {-1, -1, 2}, {-1, 0, 1} };
	grid2 = threeSum(a);
	assert(grid1 == grid2);
	a.clear();
	a = { 0, 0, 0 };
	grid1 = { {0, 0, 0} };
	grid2 = threeSum(a);
	assert(grid1 == grid2);
	a.clear();
	a = { 1, 0, -1, 0, -2, 2 };
	grid1 = { {-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1} };
	grid2 = fourSum(a, 0);
	assert(grid1 == grid2);
	a.clear();
	a = { -3, -1, 0, 2, 4, 5 };
	grid1 = { {-3, -1, 2, 4} };
	grid2 = fourSum(a, 2);
	assert(grid1 == grid2);
	set<long> lSet{ 1, 2, 3, 5, 6, 8, 9, 11, 12, 13 };
	assert(diffpairs(lSet, 3) == 6);
	lSet.clear();
	lSet = { 1, 5, 3, 4, 2 };
	assert(diffpairs(lSet, 2) == 3);
	lSet.clear();
	lSet = { 1, 3, 5, 8, 6, 4, 2 };
	assert(diffpairs(lSet, 2) == 5);

	a.clear();
	a = { 1, 5, 3, 4, 2 };
	assert(diffpairs(a, 2) == 3);
	a.clear();
	a = { 1, 3, 5, 8, 6, 4, 2 };
	assert(diffpairs(a, 2) == 5);
	a.clear();
	a = { 1, 2, 3, 4, 5, 6 };
	assert(minDiffPairs(a, 0) == 3);
	a.clear();
	a = { 1, 2, 3, 4, 5, 6 };
	assert(minDiffPairs(a, 1) == 3);
	a.clear();
	a = { 1, 2, 3, 4, 5, 6 };
	assert(minDiffPairs(a, 4) == 2);
	a.clear();
	a = { 6, 5, 4, 3, 2, 1 };
	assert(minDiffPairs(a, 4) == 2);
	a.clear();
	a = { 3, 5, 1, 6, 2, 4 };
	assert(minDiffPairs(a, 4) == 2);
	a.clear();
	a = { 1, 1, 1, 5, 5, 5, 5 };
	assert(minDiffPairs(a, 4) == 3);
	a.clear();
	a = { 1, 1 };
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
	strings1 = { "(())", "()()" };
	assert(strings.size() == 2);
	assert(strings1 == strings);

	strings.clear();
	parentheses(strings, 3);
	assert(strings.size() == 5);
	strings1.clear();
	strings1 = { "((()))", "(()())", "(())()", "()(())", "()()()" };
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
	unique_ptr<Tower<size_t>> towers[3];
	for (i = 0; i < 3; i++)
		towers[i] = make_unique<Tower<size_t>>(i);
	for (i = 2; i > 0; i--) // Smallest disk is "1"
	{
		towers[0]->Add(i);
		assert(towers[0]->TopDisk() == i);
	}
	size = towers[0]->MoveDisks(2, towers[2].get(), towers[1].get());
	assert(size == 3); // size = #moves
	for (i = 0; i < 3; i++)
		towers[i]->Clear();
	for (i = 10; i > 0; i--) // Smallest disk is "1"
	{
		towers[0]->Add(i);
		assert(towers[0]->TopDisk() == i);
	}
	cout << "Tower 0 before move: " << endl;
	towers[0]->print();
	size = towers[0]->MoveDisks(5, towers[2].get(), towers[1].get());
	cout << "Tower 0,1,2 after " << size << " moves: " << endl;
	towers[0]->print();
	assert(towers[0]->TopDisk() == 6);
	towers[1]->print();
	assert(towers[1]->TopDisk() == numeric_limits<size_t>::max());
	towers[2]->print();
	assert(towers[2]->TopDisk() == 1);

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
	cout << "Test addition without using arithmetic symbol: " << endl;
	assert(AddWithoutArithmetic(0, 0) == 0);
	assert(AddWithoutArithmetic(-1, 1) == 0);
	assert(AddWithoutArithmetic(0xdeadbeef, 0xfeedbeef) == 0x1dd9b7dde);
	assert(AddWithoutArithmetic(0xdeadbeef, 0) == 0xdeadbeef);
	assert(AddWithoutArithmetic(0, 0xfeedbeef) == 0xfeedbeef);

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
	copy(result.begin(), result.end(), ostream_iterator<long>(cout, " "));
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
	// Test countDigits
	// 0 - 99: 10 + 10 = 20
	// 100 - 199: 2 * 20
	// 200 - 299: 3 * 20 + 100 = 160
	// 300 - 345: 5(first digit) + 10(second digit) = 15
	// total: 160 + 15 = 175
	assert(countDigits(2, 345) == 175);
	assert(countDigits(0, 345) == 175);
	assert(countDigits(3, 35) == 10); // {3,13,23},30,31,32,{3}3,34,35
	assert(countNumbersWithUniqueDigits(0) == 1);
	assert(countNumbersWithUniqueDigits(1) == 10);
	assert(countNumbersWithUniqueDigits(2) == 91);	// [0,100)
	assert(countNumbersWithUniqueDigits(3) == 739); // [0,1000)
	assert(countNumbersWithUniqueDigits(11) == 0);
	a.clear();
	b.clear();
	a.resize(10);
	ranges::generate(a, [n = 1]() mutable { return n++; });
#ifdef _MSC_VER
	long sum = parallel_reduce(a.begin(), a.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	long sum = parallel_reduce(
		blocked_range<long>(0, a.size()), 0,
		[&](tbb::blocked_range<long> r, long running_total)
		{
			for (int i = r.begin(); i < r.end(); ++i)
				running_total += a[i];
			return running_total;
		},
		std::plus<long>());
#endif
	assert(sum == 55);
	a.clear();
	b.clear();
	a = { 1, 7, 15, 29, 11, 9 };
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
	copy(b.begin(), b.end(), ostream_iterator<long>(cout, " "));
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
	// Test single-character string permutations
	set<string> dictionary = { "DAMP", "LAMP", "LIMP", "LIME", "LIKE", "LAKE" };
	strings.clear();
	WordLadder(string("DAMP"), string("LIKE"), dictionary, strings);
	assert(!strings.empty());
	cout << "Single-character transformation from \"DAMP\" to \"LIKE\": ";
	// DAMP LAMP LIMP LIME LIKE
	assert(strings.size() == 5);
	assert(strings[0] == "LIKE");
	assert(strings[1] == "LIME");
	assert(strings[2] == "LIMP");
	assert(strings[3] == "LAMP");
	assert(strings[4] == "DAMP");
	copy(strings.rbegin(), strings.rend(), ostream_iterator<string>(cout, " "));
	cout << endl;
	strings.clear();
	WordLadder(string("DAMP"), string("Like"), dictionary, strings);
	assert(strings.empty()); // "LICK" is not in the dictionary
	dictionary.clear();
	strings.clear();
	dictionary = { "Hot", "Dot", "Dog", "Lot", "Log", "Cog" };
	WordLadder(string("Hit"), string("Cog"), dictionary, strings);
	assert(!strings.empty());
	assert(strings.size() == 5);
	assert(strings[0] == "Cog");
	assert(strings[1] == "Dog");
	assert(strings[2] == "Dot");
	assert(strings[3] == "Hot");
	assert(strings[4] == "Hit");
	cout << "Single-character transformation from \"Hit\" to \"Cog\": ";
	copy(strings.rbegin(), strings.rend(), ostream_iterator<string>(cout, " "));
	cout << endl;
	strings.clear();
	WordLadder(string("Hit"), string("Hat"), dictionary, strings);
	assert(strings.empty()); // "HAT" is not in the dictionary
	assert(match(string("abba"), string("redbluebluered")));
	assert(match(string("aaaa"), string("asdasdasdasd")));
	assert(match(string("aabb"), string("xyzxyzabcabc")));
	assert(match(string("abab"), string("xyzabcxyzabc")));
	assert(!match(string("aabb"), string("xyzabcxyzabc")));
	assert(!match(string("abba"), string("xyzabcxyzabc")));
	assert(!match(string("aaaa"), string("xyzabcxyzabc")));
	cout << endl;
	stringset.clear();
	stringset.insert("cdf");
	stringset.insert("too");
	stringset.insert("hgfdt");
	stringset.insert("paa");
	stringset1.clear();
	FindPattern("abc", stringset, stringset1);
	assert(stringset1.size() == 1);
	assert(stringset1.find("cdf") != stringset1.end());
	stringset1.clear();
	FindPattern("acc", stringset, stringset1);
	assert(stringset1.size() == 2);
	assert(stringset1.find("too") != stringset1.end());
	assert(stringset1.find("paa") != stringset1.end());
	line = "1024";
	line1 = "2048";
	istringstream iss1(line), iss2(line1);
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
	ranges::generate(data, [n = 1]() mutable { return n++; });
	vector<int> intResult = Increment(data);
	assert(intResult[0] == 1);
	assert(intResult[1] == 2);
	assert(intResult[2] == 3);
	assert(intResult[3] == 5);

	data.clear();
	data = { 9, 9, 9, 9 };
	intResult = Increment(data);
	assert(intResult[0] == 1);
	assert(intResult[1] == 0);
	assert(intResult[2] == 0);
	assert(intResult[3] == 0);
	assert(intResult[4] == 0);

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
	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, ","));
	cout << endl;
	assert(XOR(1) == 1);
	assert(XOR(2) == 3);
	assert(XOR(3) == 0);
	assert(XOR(4) == 4);
	assert(XOR(5) == 1);
	cout << dec;
	assert(ToggleSign(-10) == 10);
	assert(ToggleSign(10) == -10);
	assert(absolute(-10) == 10);
	assert(absolute(10) == 10);
	assert(SubtractWithPlusSign(10, 5) == 5);
	assert(SubtractWithPlusSign(10, -5) == 15);
	assert(MultiplyWithPlusSign(10, 5) == 50);
	assert(MultiplyWithPlusSign(10, -5) == -50);
	assert(DivideWithPlusSign(10, 3) == 3);
	assert(DivideWithPlusSign(10, -3) == -3);
	assert(DivideWithPlusSign(-10, 3) == -3);
	assert(DivideWithPlusSign(-10, -3) == 3);
	assert(DivideWithPlusSign(-10, -1) == 10);
	assert(DivideWithPlusSign(-1, 1) == -1);
	assert(DivideWithPlusSign(1, -1) == -1);
	assert(DivideWithPlusSign(-1, -1) == 1);
	assert(DivideWithPlusSign(-2147483648, -1) == (long)2147483648);
	assert(DivideWithPlusSign(-2147483648, 1) == -2147483648);
	assert(DivideWithPlusSign(2147483648, -1) == -2147483648); // Takes very long time to ToggleSign of 64-bit value
	assert(divide(10, 3) == 3);
	assert(divide(10, -3) == -3);
	assert(divide(-10, 3) == -3);
	assert(divide(-10, -3) == 3);
	assert(divide(-1, 1) == -1);
	assert(divide(1, -1) == -1);
	assert(divide(-1, -1) == 1);
	assert(divide(-2147483648, -1) == (long)2147483648);
	assert(divide(-2147483648, 1) == -2147483648);
	assert(divide(2147483648, -1) == -2147483648); // Takes very long time to ToggleSign of 64-bit value
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
	udata.clear();
	udata = { 10, 2 };
	assert(buildmax(udata) == "210");
	udata.clear();
	udata = { 3, 30, 34, 5, 9 };
	assert(buildmax(udata) == "9534330");
	udata.clear();
	udata = { 128, 12, 320, 32 };
	assert(buildmax(udata) == "3232012812");
	udata.clear();
	udata = { 0, 0 };
	assert(buildmax(udata) == "0");
	udata.clear();
	assert(buildmax(udata) == "0");
	strings.clear();
	strings = { "ABCW", "BAZ", "FOO", "BAR", "XTFN", "ABCDEF" };
	long max = MaxLengths(strings);
	assert(max == 24);
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
	assert(CountDistinctSlices(6, a) == 9);
	a.clear();
	a.push_back(0);							 // 5
	a.push_back(1);							 // 4
	a.push_back(2);							 // 3
	a.push_back(3);							 // 2
	a.push_back(4);							 // 1
	assert(CountDistinctSlices(6, a) == 15); // 5 + 4 + 3
	a.clear();
	a.push_back(1);							// 5
	a.push_back(1);							// 4
	a.push_back(1);							// 3
	a.push_back(1);							// 2
	a.push_back(1);							// 1
	assert(CountDistinctSlices(2, a) == 5); // 5 + 4 + 3
	a.clear();
	a.push_back(1);							// 2
	a.push_back(2);							// 1
	a.push_back(2);							// 2
	a.push_back(3);							// 1
	a.push_back(3);							// 2
	a.push_back(4);							// 1
	assert(CountDistinctSlices(3, a) == 9); // 5 + 4 + 3
	a.clear();
	a.push_back(1);							 // 2
	a.push_back(2);							 // 1
	a.push_back(2);							 // 3
	a.push_back(3);							 // 2
	a.push_back(4);							 // 1
	a.push_back(4);							 // 1
	assert(CountDistinctSlices(3, a) == 10); // 5 + 4 + 3
	a.clear();
	a.push_back(1);							 // 1
	a.push_back(1);							 // 4
	a.push_back(2);							 // 3
	a.push_back(3);							 // 2
	a.push_back(4);							 // 1
	a.push_back(4);							 // 1
	assert(CountDistinctSlices(3, a) == 12); // 5 + 4 + 3
	a.clear();
	a.push_back(1);							 // 2
	a.push_back(2);							 // 1
	a.push_back(1);							 // 3
	a.push_back(2);							 // 2
	a.push_back(4);							 // 1
	a.push_back(4);							 // 1
	assert(CountDistinctSlices(3, a) == 10); // 5 + 4 + 3
	a.clear();
	a.push_back(1);							 // 2
	a.push_back(2);							 // 1
	a.push_back(3);							 // 3
	a.push_back(4);							 // 2
	a.push_back(5);							 // 1
	a.push_back(6);							 // 1
	assert(CountDistinctSlices(3, a) == 21); // 5 + 4 + 3
	a.clear();
	a = { 10, 2, 5, 1, 8, 12 };
	assert(CountTriangles(a) == 4);
	assert(decimal_to_binary(0) == "0");
	a.clear();
	a = { 1, 5, 2, -2 };
	assert(MinAbsSum(a) == 0);
	a.clear();
	a = { 2, 2, 1 };
	assert(MinAbsSum(a) == 1);
	a.clear();
	a = { 23171, 21011, 21123, 21366, 21013, 21367 };
	assert(MaxProfit(a) == 356);
	a.clear();
	a = { 5, 3, 2 };
	assert(StockMax(a) == 0);
	a.clear();
	a = { 1, 2, 100 };
	assert(StockMax(a) == 197); // (100 - 1 = 99) + (100 - 2 = 98) = 197
	a.clear();
	a = { 1, 3, 1, 2 };
	assert(StockMax(a) == 3);
	a.clear();
	a = { 1, 2, 3, 0, 2, 5 };
	assert(StockMaxProfit(a) == 6);
	a.clear();
	a = { 1, 2, 3, 0, 1, 5 };
	assert(StockMaxProfit(a) == 6);
	a.clear();
	a = { 1, 2, 6, 0, 1, 5 };
	assert(StockMaxProfit(a) == 9);
	a.clear();
	a = { 1, -2, 0, 9, -1, -2 };
	assert(NumberSolitaire(a) == 8);
	a.clear();
	a = { 1, -2, 4, 3, -1, -3, -7, 4, -9 };
	assert(NumberSolitaire(a) == 3);
	a.clear();
	a = { 0, -4, -5, -2, -7, -9, -3, -10 };
	assert(NumberSolitaire(a) == -12);
	a.clear();
	a = { -1, -4, -5, -2, -7, -9, -3, -10 };
	assert(NumberSolitaire(a) == -13);
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
	data = { 1, 0, 1, 1, 0, 0, 0 };
	assert(findMinFlip(data) == 1);
	data.clear();
	data = { 0, 0, 0, 0, 1 };
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
	CircularLinkedListLoopStart();
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
	interval_map<int, char> imap(0);
	imap.assign(0, 2, 'A');
	imap.assign(4, 6, 'A');
	imap.assign(2, 4, 'A');
	assert(imap.size() == 5);
	assert(imap[0] == 'A');
	assert(imap[1] == 'A');
	assert(imap[4] == 'A');
	assert(imap[5] == 'A');
	interval_map<int, char> imap1(0);
	imap1.assign(0, 2, 'A');
	imap1.assign(4, 6, 'A');
	imap1.assign(2, 4, 'B');
	assert(imap1.size() == 7);
	assert(imap1[0] == 'A');
	assert(imap1[1] == 'A');
	assert(imap1[2] == 'B');
	assert(imap1[3] == 'B');
	assert(imap1[4] == 'A');
	assert(imap1[5] == 'A');
	interval_map<int, char> imap2(0);
	imap2.assign(0, 2, 'A');
	imap2.assign(4, 6, 'A');
	imap2.assign(2, 4, 'B');
	assert(imap2.size() == 7);
	assert(imap2[0] == 'A');
	assert(imap2[1] == 'A');
	assert(imap2[2] == 'B');
	assert(imap2[3] == 'B');
	assert(imap2[4] == 'A');
	assert(imap2[5] == 'A');
	imap2.assign(2, 4, 'A');
	assert(imap2.size() == 7);
	assert(imap2[2] == 'B');
	assert(imap2[3] == 'B');
	interval_map<int, char> imap3(0);
	imap3.assign(0, 2, 'A');
	imap3.assign(4, 6, 'A');
	assert(imap3.size() == 5);
	assert(imap3[4] == 'A');
	assert(imap3[5] == 'A');
	imap3.assign(2, 6, 'B');
	assert(imap3.size() == 7);
	assert(imap3[2] == 'B');
	assert(imap3[3] == 'B');
	assert(imap3[4] == 'B');
	assert(imap3[5] == 'B');
	interval_map<unsigned int, char> imap4(0);
	imap4.assign(0, 2, 'A');
	imap4.assign(4, 6, 'A');
	imap4.assign(2, 4, 'A');
	assert(imap4.size() == 4);
	assert(imap4[0] == 'A');
	assert(imap4[1] == 'A');
	assert(imap4[4] == 'A');
	assert(imap4[5] == 'A');
	interval_map<unsigned int, char> imap5(0);
	imap5.assign(2, 0, 'A');
	imap5.assign(4, 6, 'A');
	imap5.assign(2, 4, 'A');
	assert(imap5.size() == 5);
	assert(imap5[2] == 'A');
	assert(imap5[3] == 'A');
	assert(imap5[4] == 'A');
	assert(imap5[5] == 'A');
	interval_map<unsigned int, char> imap6(0);
	imap6.assign(2, 0, 'A');
	imap6.assign(2, 4, 'A');
	imap6.assign(4, 6, 'A');
	assert(imap6.size() == 3);
	assert(imap6[2] == 'A');
	assert(imap6[3] == 'A');
	a.clear();
	a = { -3, 1, 2, -2, 5, 6 };
	assert(MaxProductOfThree(a) == 60);
	assert(binary_gap(9) == 2);
	assert(binary_gap(32) == 0);
	assert(binary_gap(529) == 4);
	data.clear();
	data.resize(5);
	ranges::generate(data, [i = 0]() mutable { return i++; });
	/* 0 1 2 3 4 => 2 3 4 0 1 (Rotate 3)
	 */
	RotateRightArray(data, 3);
	for (size_t i = 0, j = 2; i < data.size(); i++, j = ++j % data.size())
		assert(data[i] == j);
	data.clear();
	data.resize(5);
	ranges::generate(data, [i = 0]() mutable { return i++; });
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
	a = { 2, 1, 5, 3, 4 };
	assert(minimumBribes(a) == 3);
	a.clear();
	a = { 2, 5, 1, 3, 4 };
	assert(minimumBribes(a) == -1);
	assert(SherlockValidString("abcdefghhgfedecba"));
	assert(!SherlockValidString("aabbcd"));
	assert(!SherlockValidString("aaaabbcc"));
	assert(!SherlockValidString("xxxaabbccrry"));
	assert(SherlockValidString("ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd"));
	line = "if man was meant to stay on the ground god would have given us roots";
	assert(encryption(line) == "imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau");
	a.clear();
	a = { 100, 100, 50, 40, 40, 20, 10 };
	b.clear();
	b = { 5, 25, 50, 120 };
	vector<size_t> leaderBoardResult = climbingLeaderboard(a, b);
	assert(leaderBoardResult[0] == 6);
	assert(leaderBoardResult[1] == 4);
	assert(leaderBoardResult[2] == 2);
	assert(leaderBoardResult[3] == 1);
	a.clear();
	a = { 3, 1, 5, 4, 2 };
	assert(calculateMedian(a) == 3);
	a.clear();
	a = { 3, 1, 5, 4, 2, 6 };
	assert(calculateMedian(a) == 3);
	assert(timeInWords(5, 47) == "thirteen minutes to six");
	assert(timeInWords(12, 29) == "twenty nine minutes past twelve");
	assert(timeInWords(6, 30) == "half past six");
	assert(timeInWords(1, 1) == "one minute past one");
	assert(beautifulQuadruples(1, 1, 1, 1) == 0);
	assert(beautifulQuadruples(3, 3, 3, 3) == 9);
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
	a.clear();
	a = { 1, 3, 5, 7, 9 };
	DisJointSet<long> disjointSet(a);
	disjointSet.Print(a);
	// Test islands
	// assert(disjointSet.Find(0) == 0); C++ map will insert non-existing key silently
	assert(disjointSet.Find(1) == 1);
	assert(disjointSet.Find(3) == 3);
	assert(disjointSet.Find(5) == 5);
	assert(disjointSet.Find(7) == 7);
	assert(disjointSet.Find(9) == 9);
	// Test all islands of Rank 0
	assert(disjointSet.Rank(1) == 0);
	assert(disjointSet.Rank(3) == 0);
	assert(disjointSet.Rank(5) == 0);
	assert(disjointSet.Rank(7) == 0);
	assert(disjointSet.Rank(9) == 0);
	assert(disjointSet.Find(1) != disjointSet.Find(3));
	assert(disjointSet.Find(3) != disjointSet.Find(5));
	assert(disjointSet.Find(5) != disjointSet.Find(7));
	assert(disjointSet.Find(7) != disjointSet.Find(9));
	assert(disjointSet.Union(3, 7) == 7); // 3,7 root: 7
	assert(disjointSet.Find(1) != disjointSet.Find(3));
	assert(disjointSet.Find(3) != disjointSet.Find(5));
	assert(disjointSet.Find(5) != disjointSet.Find(7));
	assert(disjointSet.Find(7) != disjointSet.Find(9));
	assert(disjointSet.Find(3) == disjointSet.Find(7));
	assert(disjointSet.Rank(3) == 1);
	assert(disjointSet.Rank(7) == 1);
	disjointSet.Print(a);
	// Put smaller ranked item under bigger ranked item if ranks are different
	assert(disjointSet.Union(1, 3) == 7);							// 1, 3, 7 root: 7
	assert(disjointSet.Union(1, 7) == numeric_limits<long>::min()); // Already joined!
	assert(disjointSet.Rank(1) == 1);
	assert(disjointSet.Rank(3) == 1);
	assert(disjointSet.Rank(7) == 1);
	disjointSet.Print(a);
	assert(disjointSet.Find(1) == disjointSet.Find(3));
	assert(disjointSet.Find(3) != disjointSet.Find(5));
	assert(disjointSet.Find(5) != disjointSet.Find(7));
	assert(disjointSet.Find(7) != disjointSet.Find(9));
	assert(disjointSet.Find(3) == disjointSet.Find(7));
	// assert(disjointSet.Find(2) == 0); C++ map will insert non-existing key silently
	// assert(disjointSet.Find(1) != disjointSet.Find(2)); C++ map will insert non-existing key silently
	vector<long> from{ 1, 1, 4, 2, 3, 3 }, to{ 2, 3, 1, 4, 2, 4 }, weights{ 5, 3, 6, 7, 4, 5 };
	assert(kruskals(4, from, to, weights) == 12);
	from.clear();
	to.clear();
	weights.clear();
	from = { 1, 3, 4, 1, 3 };
	to = { 2, 2, 3, 4, 1 };
	weights = { 1, 150, 99, 100, 200 };
	assert(kruskals(4, from, to, weights) == 200);

	from.clear();
	to.clear();
	weights.clear();
	from = { 1, 3, 1, 4, 2 };
	to = { 2, 5, 4, 5, 3 };
	weights = { 60, 70, 120, 150, 80 };
	assert(getLowestPathCost(5, from, to, weights) == 80);

	from.clear();
	to.clear();
	weights.clear();
	from = { 1, 2, 1, 3 };
	to = { 2, 4, 3, 4 };
	weights = { 20, 30, 5, 40 };
	assert(getLowestPathCost(4, from, to, weights) == 30);

	from.clear();
	to.clear();
	weights.clear();
	from = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 9 };
	to = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 3, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10, 5, 6, 7, 8, 9, 10, 6, 7, 8, 9, 10, 7, 8, 9, 10, 8, 9, 10, 9, 10, 10 };
	weights = { 6337, 1594, 3766, 3645, 75, 5877, 8561, 242, 6386, 3331, 4194, 8069, 3934, 101, 8536, 6963, 9303, 7639, 8512, 1330, 6458, 1180, 3913, 1565, 9488, 1369, 8066, 9439, 7510, 6833, 4215, 194, 4774, 4328, 187, 1196, 200, 8743, 1433, 2933, 2069, 1974, 7349, 2351, 8423 };
	assert(from.size() == 45);
	assert(to.size() == 45);
	assert(weights.size() == 45);
	assert(getLowestPathCost(10, from, to, weights) == 1196);

	grid1.clear();
	grid1.resize(1);
	grid1[0].push_back(1);
	assert(SurfaceArea3D(grid1) == 6);
	grid1.clear();
	grid1.resize(1);
	grid1[0] = { 1, 0, 1 };
	assert(SurfaceArea3D(grid1) == 12);

	grid1 = { {1, 3, 4}, {2, 2, 3}, {1, 2, 4} };
	assert(SurfaceArea3D(grid1) == 60);

	grid1.clear();
	grid1.resize(1);
	grid1[0] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	assert(SurfaceArea3D(grid1) == 90);

	grid1 = { {1}, {2}, {3}, {4}, {5}, {5}, {4}, {3}, {2}, {1} };
	assert(SurfaceArea3D(grid1) == 90);

	grid1.clear();
	grid1.resize(1);
	grid1[0] = { 1, 2, 3, 4, 5, 4, 5, 4, 3, 2, 1 };
	assert(SurfaceArea3D(grid1) == 102);

	grid1 = { {1}, {2}, {3}, {4}, {5}, {4}, {5}, {4}, {3}, {2}, {1} };
	assert(SurfaceArea3D(grid1) == 102);

	grid1 = { {51}, {32}, {28}, {49}, {28}, {21}, {98}, {56}, {99}, {77} };
	assert(SurfaceArea3D(grid1) == 1482);

	a.clear();
	a = { 4, 2 };
	assert(AlmostSorted(a) == "swap 1 2");
	a.clear();
	a = { 4104, 8529, 49984, 54956, 63034, 82534, 84473, 86411, 92941, 95929, 108831, 894947, 125082, 137123, 137276, 142534, 149840, 154703, 174744, 180537, 207563, 221088, 223069, 231982, 249517, 252211, 255192, 260283, 261543, 262406, 270616, 274600, 274709, 283838, 289532, 295589, 310856, 314991, 322201, 339198, 343271, 383392, 385869, 389367, 403468, 441925, 444543, 454300, 455366, 469896, 478627, 479055, 484516, 499114, 512738, 543943, 552836, 560153, 578730, 579688, 591631, 594436, 606033, 613146, 621500, 627475, 631582, 643754, 658309, 666435, 667186, 671190, 674741, 685292, 702340, 705383, 722375, 722776, 726812, 748441, 790023, 795574, 797416, 813164, 813248, 827778, 839998, 843708, 851728, 857147, 860454, 861956, 864994, 868755, 116375, 911042, 912634, 914500, 920825, 979477 };
	assert(AlmostSorted(a) == "swap 12 95");
	a.clear();
	a = { 43, 65, 1, 98, 99, 101 };
	assert(AlmostSorted(a) == "no");
	assert(cipher(7, 4, string("1110101001")) == "1001011");
	assert(cipher(4, 5, string("11000110")) == "1010");
	assert(DecryptPassword(string("43Ah*ck0rr0nk")) == "hAck3rr4nk");
	assert(DecryptPassword(string("51Pa*0Lp*0e")) == "aP1pL5e");
	udata.clear();
	udata = { 1, 2, 3 };
	assert(sherlockAndCost(udata) == 2);
	udata.clear();
	udata = { 4, 7, 9 };
	assert(sherlockAndCost(udata) == 12);
	udata.clear();
	udata = { 10, 1, 10, 1, 10 };
	assert(sherlockAndCost(udata) == 36);
	assert(substrings(string("123")) == 164);
	assert(substrings(string("1234")) == 1670);
	assert(substrings(string("972698438521")) == 445677619);
#if 0
	assert(steadyGene(string("ACGT")) == 0);
	assert(steadyGene(string("AAAA")) == 3);
	assert(steadyGene(string("ACAA")) == 2);
	assert(steadyGene(string("ACTGAAAG")) == 2);
	assert(steadyGene(string("GAAATAAA")) == 5);
	assert(steadyGene(string("TGATGCCGTCCCCTCAACTTGAGTGCTCCTAATGCGTTGC")) == 5);
	//assert(steadyGene(string("ACAAAAATAAACAAAAACAAAAAAAAAATAAATACAATAAAAAAAAAAAATGAAATACAACAACAAATAAAATAAAAACGACTAAAAAATAAAAAAAAAAAAAAAAAGAGTACTAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAACACAATCAAAATAAACAAAAAAAAAAAAACCAAAATAATCAACAAAAAAAAAAAAAACAAAAACAACAACAAACAAAAAAAAACACAAACAAAAAAAAAAAAAAAACAAAACAAACAAAAAAAAAAAAACAAAAAAACAAAAAAAAAAAAAAAAACAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAACAAACAAAAAAAAAAAATACAAAAAGCTATAAAAAAAAAAAAATTAAAAAACAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAGAAAAACAAAAAAAAAAAAAAAAACAACCAAAAAACAAAAAAAAACTAAAAAAAAAAAAAAAAAAAAAAAAAAATAACAAAAAACACAAAAAAAAAAAAGAAAGAAAAAAAACACAAAAAAAAACAAACAAAAAAAAAAAAAAAAAAAGAAAACAAAAAAACAAAAAAAACAAAAAAAAAACAAAAATTGGACAAAAAAAAACAAAAAAAAAAAACAAAAAAAGTAAAACAAATAAAAAAACAAAAAAAACAAAAAAAAAAAAAAAAAACAAAAAAGAAACAAAAAACAAAAAAAAATAACAAAACCAAAAAACAAATAAAAAACAAAAAAAATAACACAAAAAAAAAAAGAAACAAAAAAAAAAAAAAAAAAAAAAATTATAAAAAAAAAAAAAAAACAAAAAAAAAAAAAACAAAAAAAAAAGGAAAAAAAAAAAAAAAAAAAAAAAAAAATAACTAAACAAAAAAAAACAAACAAAAAATCAAAAAAAAAAAAGAAAAAAGAATAAGCAACAAAAACACAAAAAAAAAAAAAAAAAAAAAAAACATAAACAATAATAAAAAAAAAACAAAAAAAACAAAAGAACAACAAAAAACAAAACTAAACAAATAAAAAAAAAAAAACAAAAACTACAAAAAAAAAAAGAAAAAAAAAGAAAAAAAAACAAATAAAAGAAAAAAAAAAAAAAAAAAAACACAAAAAAAAAAATAAAAAAAAAAAAAAAAACAAAATAAACAAAAACAAAGAAAAAAACAAACAAAAAAAAAAAACAAAAAACTAAAAACAAAAAAAAAACAAAACACAAAAAAAAAAAAAAATAAAAAAAAAACAAAAAAACAAAAAGGAAAAAAAAAAAAGAACAAAAAAAAAAACAACAGAAAAAAGAAAAGAAAAAAAAAAAAAGACCACAAAATAAAAAAAAACAACAAACAAAAAAAAACAAAACAAAAAAACGAACAAAAAAAACAAAAACAAAAAAAAAAAAAAAAAAAAAAAGGCAAAAACAAAAAAAACAAAACAAAACAAAAAAACAAAAAAAAATTAAGATAAAGAACAAAAAAAGAAGAGAAAAAATTAACAAAAAAAAAAAAATAAAAAATACAAAAAGAAATAAAAAATACAACACACAACAAAAACGAAAAAAAAAAAAAAAACACAAAATAGAAAAAAAAAAAAAACAAAAAAAAAAAAAAGAAAAAAACAAAAAAAAAAAAATAAAAAAAAACGACACAGAAACAAAAAATAACAAAAAAAAAAAAAATAAAAAAAAAACAAAAAAAAAACAAAAAATAAAAAAAAAAACAAACAAAAAAAAAAAAAAAATAAAAAAAAAAAAAGCAAAACATAAACAAGAAAAAAAAAAAAAGTACAAATAACAAAACAAAAAAGACACTAAAAAAAAAAAAAAAAAACAAAAAAAAAAAAAAAAAAAAAAAAAGAAAAAAAACCACAAAACAAAAAAATAAAGCAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAATGAAAAAAAAAAGAAAACCAAAAAAATAAAAGA")) == 1393); stack overflow!
#endif
	strings.clear();
	strings = { "GGGGGGGGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GGGGGGGGG" };
	assert(TwoCrosses(strings) == 1);
	strings = { "GGGGGGG", "BGBBBBG", "BGBBBBG", "GGGGGGG", "GGGGGGG", "BGBBBBG" };
	assert(TwoCrosses(strings) == 5);
	strings = { "GBGBGGB", "GBGBGGB", "GBGBGGB", "GGGGGGG", "GGGGGGG", "GBGBGGB", "GBGBGGB" };
	assert(TwoCrosses(strings) == 45);
	strings = { "GGGGGGGG", "GBGBGGBG", "GBGBGGBG", "GGGGGGGG", "GBGBGGBG", "GGGGGGGG", "GBGBGGBG", "GGGGGGGG" };
	assert(TwoCrosses(strings) == 81);
	strings = { "GGGGGGGGGG", "GBBBBBBGGG", "GGGGGGGGGG", "GGGGGGGGGG", "GBBBBBBGGG", "GGGGGGGGGG", "GBBBBBBGGG", "GBBBBBBGGG", "GGGGGGGGGG" };
	assert(TwoCrosses(strings) == 45);
	strings = { "BBBBBGGBGG", "GGGGGGGGGG", "GGGGGGGGGG", "BBBBBGGBGG", "BBBBBGGBGG", "GGGGGGGGGG", "BBBBBGGBGG", "GGGGGGGGGG", "BBBBBGGBGG", "GGGGGGGGGG" };
	assert(TwoCrosses(strings) == 85);
	strings = { "GGGGGGGGGGGG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GGGGGGGGGGGG", "GBGGBBBBBBBG" };
	assert(TwoCrosses(strings) == 81);
	strings = { "GGGGGGGGGGGG", "GGGGGGGGGGGG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG" };
	assert(TwoCrosses(strings) == 189);
	strings = { "BGB", "GGG", "BGB", "BGB", "GGG", "BGB" };
	assert(TwoCrosses(strings) == 25);
	strings = { "BGBBGB", "GGGGGG", "BGBBGB" };
	assert(TwoCrosses(strings) == 25);
	a = absolutePermutation(10, 0);
	b = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	assert(a == b);
	a = absolutePermutation(10, 1);
	b = { 2, 1, 4, 3, 6, 5, 8, 7, 10, 9 };
	assert(a == b);
	strings = { ".......", "...O...", "....O..", ".......", "OO.....", "OO....." };
	strings1 = { "OOO.OOO", "OO...OO", "OOO...O", "..OO.OO", "...OOOO", "...OOOO" };
	assert(bomberMan(3, strings) == strings1);
	assert(FindSubsequenceRecursive(string("1221"), string("12")) == 2);
	assert(FindSubsequenceRecursive(string("1234"), string("56")) == 0);
	assert(FindSubsequenceRecursive(string("kkkkkkz"), string("kkkk")) == 15);
	assert(FindSubsequenceDynamicProgramming(string("1221"), string("12")) == 2);
	assert(FindSubsequenceDynamicProgramming(string("1234"), string("56")) == 0);
	assert(FindSubsequenceDynamicProgramming(string("kkkkkkz"), string("kkkk")) == 15);
	assert(shortPalindrome(string("kkkkkkz")) == 15);
	assert(shortPalindrome(string("ghhggh")) == 4);
	assert(shortPalindrome(string("cbbdcacccdaddbaabbaacbacacaaddaaacdbccccccbbadbbcdddddddaccbdbddcbacaaadbbdcbcbcdabdddbbcdccaacdccab")) == 242745);
	strings = { "123412", "561212", "123634", "781288" };
	strings1 = { "12", "34" };
	assert(gridSearch(strings, strings1));
	strings.clear();
	vector<vector<size_t>> ladders = { {32, 62}, {42, 68}, {12, 98} };
	vector<vector<size_t>> snakes = { {95, 13}, {97, 25}, {93, 37}, {79, 27}, {75, 19}, {49, 47}, {67, 17} };
	assert(SnakesAndLaddersGame(ladders, snakes) == 3);
	assert(SnakesAndLaddersGameFast(ladders, snakes) == 3);
	vector<vector<size_t>> ladders1 = { {8, 52}, {6, 80}, {26, 42}, {2, 72} };
	vector<vector<size_t>> snakes1 = { {51, 19}, {39, 11}, {37, 29}, {81, 3}, {59, 5}, {79, 23}, {53, 7}, {43, 33}, {77, 21} };
	assert(SnakesAndLaddersGame(ladders1, snakes1) == 5);
	assert(SnakesAndLaddersGameFast(ladders1, snakes1) == 5);
	vector<vector<size_t>> ladders2 = { {3, 5}, {7, 8}, {44, 56}, {36, 54}, {88, 91}, {77, 83}, {2, 4}, {9, 99}, {45, 78}, {31, 75} };
	vector<vector<size_t>> snakes2 = { {10, 6}, {95, 90}, {96, 30}, {97, 52}, {98, 86} };
	assert(SnakesAndLaddersGame(ladders2, snakes2) == 3);
	assert(SnakesAndLaddersGameFast(ladders2, snakes2) == 3);
	vector<vector<size_t>> ladders3 = { {3, 54}, {37, 100} };
	vector<vector<size_t>> snakes3 = { {56, 33} };
	assert(SnakesAndLaddersGame(ladders3, snakes3) == 3);
	assert(SnakesAndLaddersGameFast(ladders3, snakes3) == 3);
	vector<vector<size_t>> ladders4 = { {5, 6} };
	vector<vector<size_t>> snakes4 = { {97, 95} };
	assert(SnakesAndLaddersGameFast(ladders4, snakes4) == 17);
	vector<vector<size_t>> ladders5 = { {3, 90} };
	vector<vector<size_t>> snakes5 = { {99, 10}, {97, 20}, {98, 30}, {96, 40}, {95, 50}, {94, 60}, {93, 70} };
	// assert(SnakesAndLaddersGame(ladders5, snakes5) == 0); // Impossible. Times out!
	assert(SnakesAndLaddersGameFast(ladders5, snakes5) == 0); // Impossible
	assert(lengthOfLongestSubstring(string("abcabc")) == 3);
	assert(lengthOfLongestSubstring(string("aaa")) == 1);
	assert(lengthOfLongestSubstring(string("abcdef")) == 6);
	assert(lengthOfLongestSubstring(string("dvdf")) == 3);
	assert(lengthOfLongestSubstring(string("abcabcbb")) == 3);
	assert(lengthOfLongestSubstring(string("tmmzuxt")) == 5);
	assert(lengthOfLongestSubstring(string("pwwkew")) == 3);
	assert(lengthOfLongestSubstring(string("ohvhjdml")) == 6);
	assert(lengthOfLongestSubstring(string("vqblqcb")) == 4);
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
	a = { 1, 3, 5, 7, 9 };
	b = { 2, 4, 6, 8, 10 };
	assert(median(a, b) == 11 / (double)2);
	a.clear();
	b.clear();
	a = { 1, 3, 5, 7, 9 };
	b = { 2, 4, 6, 8, 10, 11 };
	assert(median(a, b) == 6);
	a.clear();
	b.clear();
	a = { 1, 3, 5 };
	b = { 2, 4, 6, 8, 10, 11 };
	assert(median(a, b) == 5);
	a.clear();
	b.clear();
	a = { 1, 3, 5 };
	b = { 2, 4, 6, 8, 10, 11, 13 };
	assert(median(a, b) == 11 / (double)2);
	a.clear();
	b.clear();
	a = { 1, 3, 5, 7, 9, 11, 13 };
	b = { 2, 4, 6, 8 };
	assert(median(a, b) == 6);
	a.clear();
	b.clear();
	a = { 1, 3, 5, 7, 9, 11, 13, 15 };
	b = { 2, 4, 6, 8 };
	assert(median(a, b) == (6 + 7) / (double)2);
	a.clear();
	b.clear();
	b = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	assert(median(a, b) == 5);
	b.clear();
	b = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	assert(median(a, b) == (5 + 6) / (double)2);
	a.clear();
	b.clear();
	a = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	assert(median(a, b) == 5);
	a.clear();
	a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	assert(median(a, b) == (5 + 6) / (double)2);
	a.clear();
	b.clear();
	assert(median(a, b) == 0);
	LRUCache<long, long> lruCache(2);
	lruCache.Put(1, 1);
	lruCache.Put(2, 2);
	assert(lruCache.Get(1) == 1);
	lruCache.Put(3, 3);
	assert(lruCache.Get(2) == -1);
	lruCache.Put(4, 4);
	assert(lruCache.Get(1) == -1);
	assert(lruCache.Get(3) == 3);
	assert(lruCache.Get(4) == 4);

	LRUCache<long, long> lruCache1(3);
	lruCache1.Put(1, 1);
	lruCache1.Put(2, 2);
	lruCache1.Put(3, 3);		   // 1,2,3
	lruCache1.Put(4, 4);		   // 2,3,4
	assert(lruCache1.Get(4) == 4); // 2,3,4
	assert(lruCache1.Get(3) == 3); // 2,4,3
	assert(lruCache1.Get(2) == 2); // 4,3,2
	assert(lruCache1.Get(1) == -1);
	lruCache1.Put(5, 5);
	assert(lruCache1.Get(1) == -1);
	assert(lruCache1.Get(2) == 2);
	assert(lruCache1.Get(3) == 3);
	assert(lruCache1.Get(4) == -1);
	assert(lruCache1.Get(5) == 5);

	LRUCache<long, long> lruCache2(1);
	lruCache2.Put(2, 1);
	assert(lruCache2.Get(2) == 1);
	lruCache2.Put(3, 2);
	assert(lruCache2.Get(2) == -1);
	assert(lruCache2.Get(3) == 2);
	strings.clear();
	strings = { "2", "1", "+", "3", "*" };
	assert(ReversePolishNotation(strings) == 9);
	strings.clear();
	strings = { "4", "13", "5", "/", "+" };
	assert(ReversePolishNotation(strings) == 6);
	strings.clear();
	strings = { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
	assert(ReversePolishNotation(strings) == 22);
	assert(basicCalculator(string("3+2*2-1")) == 6);
	assert(basicCalculator(string("3+2")) == 5);
	assert(basicCalculator(string("3-2")) == 1);
	assert(basicCalculator(string("3*2+2")) == 8);
	assert(basicCalculator(string("3+2-4*5")) == -15);
	assert(basicCalculator(string("3*2+5/4")) == 7);
	a.clear();
	a = { 1, 2, 3, 4 };
	a = productExceptSelf(a);
	b.clear();
	b = { 24, 12, 8, 6 };
	assert(!a.empty());
	assert(a.size() == 4);
	assert(b == a);
	udata.clear();
	udata = { 3, 0, 6, 1, 5 };
	assert(hIndex(udata) == 3);
	udata.clear();
	udata = { 0, 1 };
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = { 1, 1 };
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = { 123 };
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = { 1, 1, 2 };
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = { 1, 2, 2 };
	assert(hIndex(udata) == 2);
	udata.clear();
	udata = { 3, 2, 2 };
	assert(hIndex(udata) == 2);
	udata.clear();
	udata = { 3, 3, 2 };
	assert(hIndex(udata) == 2);
	strings = PhoneKeyLetters(string("23"));
	assert(strings.size() == 9);
	strings1 = { "ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf" };
	assert(strings1 == strings);
	strings = PhoneKeyLetters(string(""));
	assert(strings.empty());
	strings = PhoneKeyLetters(string("2"));
	assert(strings.size() == 3);
	strings1 = { "a", "b", "c" };
	strings = PhoneKeyLetters(string("358"));
	assert(strings.size() == 27);
	strings1 = { "djt", "dkt", "dlt", "ejt", "ekt", "elt", "fjt", "fkt", "flt", "dju", "dku", "dlu", "eju", "eku", "elu", "fju", "fku", "flu", "djv", "dkv", "dlv", "ejv", "ekv", "elv", "fjv", "fkv", "flv" };
	assert(strings1 == strings);
	strings = PhoneKeyLetters(string("5678"));
	assert(strings.size() == 108);
	stringset.clear();
	stringset = { "Hello", "World" };
	assert(wordBreakDynamicProgramming(string("HelloWorld"), stringset));
	strings1.clear();
	wordBreakDynamicProgramming(string("HelloWorld"), stringset, strings1);
	assert(!strings1.empty());
	assert(strings1.size() == 1);
	assert(strings1[0] == "Hello World");
	strings1 = wordBreakDFS(string("HelloWorld"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 1);
	assert(strings1[0] == "Hello World");
	stringset.clear();
	stringset = { "cats", "dog", "sand", "and", "cat" };
	assert(!wordBreakDynamicProgramming(string("catsandog"), stringset));
	assert(wordBreakDynamicProgramming(string("catsanddog"), stringset));
	assert(wordBreakDynamicProgramming(string("catanddog"), stringset));
	strings1.clear();
	wordBreakDynamicProgramming(string("catsandog"), stringset, strings1);
	assert(strings1.empty());
	strings1.clear();
	wordBreakDynamicProgramming(string("catsanddog"), stringset, strings1);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	strings1.clear();
	wordBreakDynamicProgramming(string("catanddog"), stringset, strings1);
	assert(strings1.size() == 1);
	assert(strings1[0] == "cat and dog");
	strings1.clear();
	strings1 = wordBreakDFS(string("catsandog"), stringset);
	assert(strings1.empty());
	strings1 = wordBreakDFS(string("catsanddog"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	strings1 = wordBreakDFS(string("catanddog"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 1);

	stringset.clear();
	stringset = { "apple", "pen" };
	assert(wordBreakDynamicProgramming(string("applepenapple"), stringset));
	strings1.clear();
	wordBreakDynamicProgramming(string("applepenapple"), stringset, strings1);
	assert(!strings1.empty());
	assert(strings1.size() == 1);
	assert(strings1[0] == "apple pen apple");
	strings1.clear();
	strings1 = wordBreakDFS(string("applepenapple"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 1);
	assert(strings1[0] == "apple pen apple");

	stringset.clear();
	stringset = { "aaaa", "aaa" };
	assert(wordBreakDynamicProgramming(string("aaaaaaa"), stringset));
	strings1.clear();
	wordBreakDynamicProgramming(string("aaaaaaa"), stringset, strings1);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	strings1.clear();
	strings1 = wordBreakDFS(string("aaaaaaa"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	ugrid = { {1, 0} };
	udata.clear();
	assert(canFinishCourseTopologicalSort(2, ugrid, udata));
	assert(!udata.empty());
	assert(udata.size() == 2);
	assert(udata[0] == 0);
	assert(udata[1] == 1);
	ugrid.clear();
	ugrid = { {1, 0}, {0, 1} };
	udata.clear();
	assert(!canFinishCourseTopologicalSort(2, ugrid, udata));
	assert(udata.empty());
	ugrid.clear();
	ugrid = { {1, 0}, {2, 0} };
	udata.clear();
	assert(canFinishCourseTopologicalSort(3, ugrid, udata));
	assert(!udata.empty());
	assert(udata.size() == 3);
	assert(udata[0] == 0);
	ugrid.push_back(vector<size_t>{0, 2});
	udata.clear();
	assert(!canFinishCourseTopologicalSort(3, ugrid, udata));
	assert(udata.empty());
	ugrid.clear();
	ugrid = { {1, 0}, {0, 2}, {2, 1} };
	udata.clear();
	assert(!canFinishCourseTopologicalSort(3, ugrid, udata));
	assert(udata.empty());
	a.clear();
	a = { 1, 2, 3, 1 };
	assert(containsNearbyAlmostDuplicate(a, 3, 0));
	a.clear();
	a = { 1, 0, 1, 1 };
	assert(containsNearbyAlmostDuplicate(a, 1, 2));
	a.clear();
	a = { 1, 5, 9, 1, 5, 9 };
	assert(!containsNearbyAlmostDuplicate(a, 2, 3));
	assert(!containsNearbyAlmostDuplicate(a, 0, 0)); // indices must be distinct
	assert(!containsNearbyAlmostDuplicate(a, 0, 1));
	assert(containsNearbyAlmostDuplicate(a, 3, 0));
	assert(!containsNearbyAlmostDuplicate(a, 2, 0));
	assert(!containsNearbyAlmostDuplicate(a, -1, -1));
	a.clear();
	assert(abs(2147483647L - -1) == (long)2147483648);
	assert(abs(-1 - 2147483647L) == (long)2147483648);
	a = { 2147483647, -1, 2147483647 }; // 0x7FFFF_FFFF, 0xFFFF_FFFF
	assert(!containsNearbyAlmostDuplicate(a, 1, 2147483647));
	assert(!containsNearbyAlmostDuplicate(a, 1, -2147483648L)); // 2147483648 is 0x8000_0000 = 0xFFFF_FFFF_8000_0000 < 0
	a.clear();
	assert(abs(-INT_MIN - 0x7FFFFFFF) == 1);
	assert(abs(0x7FFFFFFF - -INT_MIN) == 1);
	a = { (long)-2147483648, 2147483647 };			 // 0xFFFF_FFFF_8000_0000, 0x7FFF_FFFF
	assert(!containsNearbyAlmostDuplicate(a, 1, 1)); // -2147483648 = 0xFFFF_FFFF_8000_0000; 2147483647 = 0x7FFF_FFFF. One in negative bucket, another in positive bucket. Different from abs((long)2147483648 - (long)2147483647)
	a.clear();
	a = { 4, 1, -1, 6, 5 };
	assert(containsNearbyAlmostDuplicate(a, 3, 1));
	a.clear();
	a = diffWaysToCompute("2-1-1");
	assert(!a.empty());
	assert(a.size() == 2);
	a.clear();
	a = diffWaysToCompute("2*3-4*5");
	assert(!a.empty());
	assert(a.size() == 5);
	assert(getHint(string("6244988279"), string("3819888600")) == "2A2B");
	grid1.clear();
	grid1 = { {2, 0, -3, 4}, {6, 3, 2, -1}, {5, 4, 7, 3}, {2, -6, 8, 1} };
	CMatrix<long> matrix(grid1);
	ugrid.clear();
	ugrid = { {1, 1}, {3, 2} };
	assert(matrix.Sum(ugrid) == 18);
	ugrid.clear();
	ugrid = { {0, 2}, {3, 3} };
	assert(matrix.Sum(ugrid) == 21);
	ugrid.clear();
	sum = matrix.LargestSumSubmatrix(ugrid);
	assert(!ugrid.empty());
	grid1.clear();
	grid1 = { {-4, -5} };
	CMatrix<long> matrix1(grid1);
	ugrid.clear();
	ugrid = { {0, 0}, {0, 0} };
	assert(matrix1.Sum(ugrid) == -4);
	ugrid.clear();
	ugrid = { {0, 0}, {0, 1} };
	assert(matrix1.Sum(ugrid) == -9);
	ugrid.clear();
	assert(matrix1.LargestSumSubmatrix(ugrid) == -4);
	assert(!ugrid.empty());
	ugrid1.clear();
	ugrid1 = { {0, 0}, {0, 0} };
	assert(ugrid1 == ugrid);
	grid1.clear();
	grid1 = { {-1, -2, -3, -4}, {-2, 3, 2, -3}, {-3, 4, 7, -2}, {-4, -3, -2, -1} };
	CMatrix<long> matrix2(grid1);
	ugrid.clear();
	ugrid1.clear();
	assert(matrix2.LargestSumSubmatrix(ugrid) == 16);
	assert(!ugrid.empty());
	ugrid1 = { {1, 1}, {2, 2} };
	assert(ugrid1 == ugrid);
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
	a.clear();
	a = { 1, 7, 4, 9, 2, 5 };
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 6);
	assert(a == b);
	a.clear();
	a = { 0 };
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 1);
	assert(b.back() == 0);
	a.clear();
	a = { 0, 0 };
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 1);
	assert(b.back() == 0);
	a.clear();
	b.clear();
	a = { 3, 3, 3, 2, 5 };
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 3);
	a.clear();
	a = { 3, 2, 5 };
	assert(b == a);
	a.clear();
	a = { 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 };
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 7);
	a.clear();
	a = { 1, 17, 5, 15, 5, 16, 8 };
	assert(a == b);
	a.clear();
	a = { 1, 17, 5, 10, 13, 15, 12, 5, 16, 8 };
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 7);
	a.clear();
	a = { 1, 17, 5, 15, 5, 16, 8 };
	assert(a == b);
	a.clear();
	b.clear();
	a = { 1, 17, 5, 10, 13, 11, 12, 5, 16, 8 };
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 9);
	a.clear();
	a = { 1, 17, 5, 13, 11, 12, 5, 16, 8 };
	assert(a == b);
	assert(!isValidPreOrderTreeSerialization(string("1")));
	assert(isValidPreOrderTreeSerialization(string("#")));
	assert(isValidPreOrderTreeSerialization(string("1,#,#")));
	assert(isValidPreOrderTreeSerialization(string("9,3,4,#,#,1,#,#,2,#,6,#,#")));
	assert(isValidPreOrderTreeSerialization(string("9,#,93,#,9,9,#,#,#")));
	assert(isValidPreOrderTreeSerialization(string("9,9,9,19,#,9,#,#,#,9,#,69,#,#,#")));
	assert(LargestNumberCompositionProductWithDynamicProgramming(2) == 1);
	assert(LargestNumberCompositionProductWithDynamicProgramming(10) == 36);
	strings.clear();
	strings = { "abcw", "baz", "foo", "bar", "xtfn", "abcdef" };
	assert(maxProductOfNonOverlappingWordLengths(strings) == 16); // "abcw", "xtfn"
	strings.clear();
	strings = { "a", "ab", "abc", "d", "cd", "bcd", "abcd" };
	assert(maxProductOfNonOverlappingWordLengths(strings) == 4); // "ab", "cd"
	strings.clear();
	strings = { "a", "aa", "aaa", "aaaa" };
	assert(maxProductOfNonOverlappingWordLengths(strings) == 0);
	sgrid.clear();
	sgrid = { {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"} };
	strings = findItinerary(sgrid, string("JFK"));
	assert(!strings.empty());
	assert(strings.size() == 5);
	strings1.clear();
	strings1 = { "JFK", "MUC", "LHR", "SFO", "SJC" };
	assert(strings1 == strings);
	sgrid.clear();
	sgrid = { {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"} };
	strings = findItinerary(sgrid, string("JFK"));
	assert(!strings.empty());
	assert(strings.size() == 6);
	strings1.clear();
	strings1 = { "JFK", "ATL", "JFK", "SFO", "ATL", "SFO" };
	assert(strings1 == strings);
	sgrid.clear();
	sgrid = { {"EZE", "AXA"}, {"TIA", "ANU"}, {"ANU", "JFK"}, {"JFK", "ANU"}, {"ANU", "EZE"}, {"TIA", "ANU"}, {"AXA", "TIA"}, {"TIA", "JFK"}, {"ANU", "TIA"}, {"JFK", "TIA"} };
	strings = findItinerary(sgrid, string("JFK"));
	assert(!strings.empty());
	assert(strings.size() == 11);
	strings1.clear();
	strings1 = { "JFK", "ANU", "EZE", "AXA", "TIA", "ANU", "JFK", "TIA", "ANU", "TIA", "JFK" };
	assert(strings1 == strings);
	ugrid.clear();
	numberCombinations(4, 2, ugrid);
	assert(!ugrid.empty());
	assert(ugrid.size() == 6);
	for (vector<vector<size_t>>::iterator it = ugrid.begin(); it != ugrid.end(); it++)
		assert(it->size() == 2);
	ugrid1.clear();
	ugrid1 = { {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4} };
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
	assert(fizzBuzz(3) == vector<string>({ "1", "2", "Fizz" }));
	assert(fizzBuzz(5) == vector<string>({ "1", "2", "Fizz", "4", "Buzz" }));
	assert(fizzBuzz(10) == vector<string>({ "1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz" }));
	assert(fizzBuzz(15) == vector<string>({ "1", "2", "Fizz", "4", "Buzz", "Fizz", "7", "8", "Fizz", "Buzz", "11", "Fizz", "13", "14", "FizzBuzz" }));
	cpp20readonlyranges();
	cpp20ranges();
	/***** The End *****/
	// cout << endl << "Press ENTER to exit!";
	// getline(cin, line);
	return 0;
}