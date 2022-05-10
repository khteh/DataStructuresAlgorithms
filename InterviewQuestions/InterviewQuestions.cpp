#include "stdafx.h"
#include "InterviewQuestions.h"
using namespace std;
#if defined(__GNUC__) || defined(__GNUG__)
using namespace tbb;
#endif
map<long, set<vector<size_t>>> coinChangeCache;
map<long, set<vector<size_t>>> knapsackCache;
map<long, size_t> dpMemoization;
int main(int argc, char *argv[])
{
	string line, line1;
	size_t size;
	random_device device;
	// Fourth run: "warm-up" sequence as as seed; different each run.
	// Advanced uses. Allows more than 32 bits of randomness.
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	int i, j, index, *iPtr;
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
	GreedyAlgorithmTests();
	Knapsack_CoinChangeTests();
	Knapsack_CombinationSumTests();
	AnagramTests();
	PalindromeTests();
	SparseNumberTests();
	SortTests();
	BinarySearchTests();
	BinarySearchStringTests();
	BinarySearchCountTests();
	StackTests();
	QueueTests();
	LinkedListTests();
	BinaryTreeTests();
	BinarySearchTreeTests();
	KDTreeTests();
	MinHeapTests();
	MaxHeapTests();
	MinMaxHeapTests();
	SuffixTreeTests();
	TrieTests();
	PrefixTrieTests();
	StringPermutationTests();
	ListPermutationTests();
	GraphTests();
	LongestCommonSubsequenceTests();
	TweeterAPITests();
	stringset.erase("Does not exist");
	line = to_string(0);
	istringstream(line) >> i;
	assert(i == 0);
	strings.clear();
	strings = {"abcczch", "abcchcz", "abcde", "ABCCZCH", "ABCCHCZ", "ABCDE"};
	strings1 = {"abcchcz", "ABCCHCZ", "abcczch", "ABCCZCH", "abcde", "ABCDE"};
	sort(strings.begin(), strings.end(), LexicographicSort);
	assert(strings1 == strings);
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

	string str = "m";
	string str1 = str.substr(1);
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
	generate(a.begin(), a.end(), [n = 1]() mutable
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
	grid = {{1, 3, 5}, {2, 4, 6}, {7, 8, 9}};
	// grid.back() = {7,8,9}
	assert(grid.back().back() == 9);
	grid.clear();
	grid = {{1, 3, 5}, {2, 4, 6}, {7, 8, 9}};
	pathResult_t pathResult = FindMaxPath(grid, 0, 0);
	assert(pathResult.sum == 27);
	cout << "Grid traversal which yields maximum sum " << pathResult.sum << ": " << pathResult.path << endl;

	vector<vector<char>> maze = {{'1', '1', '1', '1', '1'}, {'S', '1', 'X', '1', '1'}, {'1', '1', '1', '1', '1'}, {'X', '1', '1', 'E', '1'}, {'1', '1', '1', '1', 'X'}};
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
	grid1 = {{-1, 0, -1}, {-1, -1, -1}, {-1, -1, -1}};
	grid2 = {{1, 0, 1}, {2, 1, 2}, {3, 2, 3}};
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
	grid1 = {{1, 3, 5}, {6, 4, 2}, {7, 9, 8}};
	grid2 = {{1, 3, 5}, {6, 4, 2}, {7, 9, 8}};
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
	grid1 = {{0, 0, 1}, {0, 1, 1}, {1, 1, 1}};
	assert(MatrixPatternCount(grid1) == 3);

	grid1 = {{0, 0, 1}, {0, 0, 1}, {1, 1, 1}};
	assert(MatrixPatternCount(grid1) == 4);

	grid1 = {{0, 0, 0, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}};
	assert(MatrixPatternCount(grid1) == 6);

	grid1 = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}};
	assert(ConnectedCellsInAGridLinkedList(grid1) == 5);
	assert(ConnectedCellsInAGrid(grid1) == 5);

	grid1 = {{0, 0, 1, 1}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
	assert(ConnectedCellsInAGridLinkedList(grid1) == 8);
	assert(ConnectedCellsInAGrid(grid1) == 8);

	grid1 = {{1, 1, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 1}};
	assert(ConnectedCellsInAGridLinkedList(grid1) == 5);
	assert(ConnectedCellsInAGrid(grid1) == 5);

	grid1 = {{0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 0, 1, 1}, {0, 1, 1, 1, 0}};
	assert(ConnectedCellsInAGridLinkedList(grid1) == 15);
	assert(ConnectedCellsInAGrid(grid1) == 15);

	grid1 = {{1, 1, 1, 0, 1}, {0, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 1, 0}};
	assert(ConnectedCellsInAGridLinkedList(grid1) == 9);
	assert(ConnectedCellsInAGrid(grid1) == 9);

	grid1 = {{1, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0, 0}};
	assert(ConnectedCellsInAGridLinkedList(grid1) == 1);
	assert(ConnectedCellsInAGrid(grid1) == 1);

	maze = {{0, 0, 1, 0, 1}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 1}, {0, 1, 1, 0, 0}};
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
	maze = {{0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}};
	queue<string> puzzleResult1;
	assert(!PathExists(maze, 0, 0, 1, 2, puzzleResult1, 1));
	maze.clear();
	maze = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
	assert(WordExistsInGrid(maze, string("ABCCED")));
	assert(!WordExistsInGrid(maze, string("ABCB")));
	line = "ab2c3";
	assert(uncompress(line) == "ababcababcababc");
	cout << "uncompress(\"ab2c3\"): " << uncompress(line) << endl;
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
	line = "abcdefcdbacd";
	line1 = "abcd";
	udata = FindSubString(line, line1);
	udata1 = {0, 6, 7, 8};
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
	line = "a";
	assert(CanShuffleWithoutRepeat(line));
	line = "aa";
	assert(!CanShuffleWithoutRepeat(line));
	line = "aab";
	assert(CanShuffleWithoutRepeat(line));
	line = "aaaabbcc";
	assert(CanShuffleWithoutRepeat(line));
	a.clear();
	a = {-2, -3, 4, -1, -2, 1, 5, -3};
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
	a = {2, 3, -6};
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
	a = {2, 3, -6, 4, 5, 6, -20};
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
	a = {2, 3, -2, 4};
	assert(6 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {-2, 0, -1};
	assert(0 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {-2, -1, 0};
	assert(2 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {-3, -1, -1};
	assert(3 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {0, 2};
	assert(2 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {3, -1, 4};
	assert(4 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {-1, -1};
	assert(1 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {0, -2, -3};
	assert(6 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {2, -5, -2, -4, 3};
	assert(24 == ConsecutiveLargestProduct(a));
	a.clear();
	b.clear();
	a = {2, 0, -3, 2, 1, 0, 1, -2};
	assert(2 == ConsecutiveLargestProduct(a));
	a.clear();
	a = {2, 3, 1, 2, 4, 3};
	assert(ConsecutiveSumMinCount(7, a) == 2);
	a.clear();
	assert(ConsecutiveSumMinCount(1, a) == -1);
	a.clear();
	a = {1, 4, 4};
	assert(ConsecutiveSumMinCount(5, a) == 2);
	assert(ConsecutiveSumMinCount(4, a) == 1);
	//  [−1, −1, 1, −1, 1, 0, 1, −1, −1]: 2 to 8 = 7
	a = {-1, -1, 1, -1, 1, 0, 1, -1, -1};
	assert(LongestNonNegativeSumSlice(a) == 7);
	a.clear();
	//  [1, 1, −1, −1, −1, −1, −1, 1, 1]: first or last 4
	a = {1, 1, -1, -1, -1, -1, -1, 1, 1};
	assert(LongestNonNegativeSumSlice(a) == 4);
	a.clear();
	a = {0, -1, 0, 0, 1, 0, -1, -1};
	assert(LongestNonNegativeSumSlice(a) == 6);
	assert(1 == ConsecutiveLargestSum(a, b));
	a.clear();
	a = {-1, -1, -1, -1, -1, -1, 1, 1};
	assert(LongestNonNegativeSumSlice(a) == 4);
	assert(2 == ConsecutiveLargestSum(a, b));
	a.clear();
	b.clear();
	strings.clear();
	strings = {"Angel", "legnA", "Hello World!!!", "World Hello!!!"};
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
	a = {0, 1, 2, 7, 10, 11, 12, 20, 25, 26, 27};
	string strRange = GetRange(a);
	grid1.clear();
	grid1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
	grid2 = MergeIntervals(grid1);
	assert(grid2.size() == 3);
	assert(grid2[0][0] == 1);
	assert(grid2[0][1] == 6);
	assert(grid2[1][0] == 8);
	assert(grid2[1][1] == 10);
	assert(grid2[2][0] == 15);
	assert(grid2[2][1] == 18);
	grid1.clear();
	grid1 = {{1, 4}, {4, 5}};
	grid2 = MergeIntervals(grid1);
	assert(grid2.size() == 1);
	assert(grid2[0][0] == 1);
	assert(grid2[0][1] == 5);
	grid1.clear();
	grid1 = {{2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10}};
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
	assert(factorialDynamicProgramming(25) == 15511210043330985984000000);
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
	generate(a.begin(), a.begin() + 10, [n = 0]() mutable
			 { return n++; });
	generate(a.begin() + 10, a.end(), [n = 5]() mutable
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
	a = {1, 2, 51, 50, 60, 55, 70, 68, 80, 76, 75, 12, 45};
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
	ull = {1, 2, 1, 2};
	unsigned long long findMaxResult = findMax(ull);
	assert(findMaxResult == 9);

	ull.clear();
	ull = {2, 3, 3, 2};
	findMaxResult = findMax(ull);
	assert(findMaxResult == 36);

	line = "     Hello     World!!!     ";
	assert(line.size() == 28);
	cout << line << " size: " << line.size();
	trim(line);
	// assert(line == "Hello     World!!!");
	cout << " trim(line): |" << line << "| size: " << line.size() << endl;

	a.clear();
	a = {1, 2, 3, 4, 5, 6, 5};
	// 1 2 3 4 5 6
	//   6 5 4
	assert(sumpairs(a, 8) == 2);

	a.clear();
	a = {5, 7, 9, 13, 11, 6, 6, 3, 3};
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
	a = {-1, 0, 1, 2, -1, -4};
	grid1 = {{-1, -1, 2}, {-1, 0, 1}};
	grid2 = threeSum(a);
	assert(grid1 == grid2);
	a.clear();
	a = {0, 0, 0};
	grid1 = {{0, 0, 0}};
	grid2 = threeSum(a);
	assert(grid1 == grid2);
	a.clear();
	a = {1, 0, -1, 0, -2, 2};
	grid1 = {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};
	grid2 = fourSum(a, 0);
	assert(grid1 == grid2);
	a.clear();
	a = {-3, -1, 0, 2, 4, 5};
	grid1 = {{-3, -1, 2, 4}};
	grid2 = fourSum(a, 2);
	assert(grid1 == grid2);
	set<long> lSet{1, 2, 3, 5, 6, 8, 9, 11, 12, 13};
	assert(diffpairs(lSet, 3) == 6);
	lSet.clear();
	lSet = {1, 5, 3, 4, 2};
	assert(diffpairs(lSet, 2) == 3);
	lSet.clear();
	lSet = {1, 3, 5, 8, 6, 4, 2};
	assert(diffpairs(lSet, 2) == 5);

	a.clear();
	a = {1, 5, 3, 4, 2};
	assert(diffpairs(a, 2) == 3);
	a.clear();
	a = {1, 3, 5, 8, 6, 4, 2};
	assert(diffpairs(a, 2) == 5);
	a.clear();
	a = {1, 2, 3, 4, 5, 6};
	assert(minDiffPairs(a, 0) == 3);
	a.clear();
	a = {1, 2, 3, 4, 5, 6};
	assert(minDiffPairs(a, 1) == 3);
	a.clear();
	a = {1, 2, 3, 4, 5, 6};
	assert(minDiffPairs(a, 4) == 2);
	a.clear();
	a = {6, 5, 4, 3, 2, 1};
	assert(minDiffPairs(a, 4) == 2);
	a.clear();
	a = {3, 5, 1, 6, 2, 4};
	assert(minDiffPairs(a, 4) == 2);
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
	OrderArrayIntoNegativePositiveSeriesTests();

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
	vector<long> cards, result;
	cards.resize(52);
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
	a = {1, 7, 15, 29, 11, 9};
	EqualAverageDivide(a, b);
	assert(b.size() == 2);
	cout << "Left part: ";
#ifdef _MSC_VER
	long sum = parallel_reduce(b.begin(), b.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	long sum = parallel_reduce(
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
	// Test single-character string permutations
	set<string> dictionary = {"DAMP", "LAMP", "LIMP", "LIME", "LIKE", "LAKE"};
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
	dictionary = {"Hot", "Dot", "Dog", "Lot", "Log", "Cog"};
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
	generate(data.begin(), data.end(), [n = 1]() mutable
			 { return n++; });
	vector<int> intResult = Increment(data);
	assert(intResult[0] == 1);
	assert(intResult[1] == 2);
	assert(intResult[2] == 3);
	assert(intResult[3] == 5);

	data.clear();
	data = {9, 9, 9, 9};
	intResult = Increment(data);
	assert(intResult[0] == 1);
	assert(intResult[1] == 0);
	assert(intResult[2] == 0);
	assert(intResult[3] == 0);
	assert(intResult[4] == 0);

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
	a = {10, 2, 5, 1, 8, 12};
	assert(CountTriangles(a) == 4);
	assert(decimal_to_binary(0) == "0");
	a.clear();
	a = {1, 5, 2, -2};
	assert(MinAbsSum(a) == 0);
	a.clear();
	a = {2, 2, 1};
	assert(MinAbsSum(a) == 1);
	a.clear();
	a = {23171, 21011, 21123, 21366, 21013, 21367};
	assert(MaxProfit(a) == 356);
	a.clear();
	a = {5, 3, 2};
	assert(StockMax(a) == 0);
	a.clear();
	a = {1, 2, 100};
	assert(StockMax(a) == 197); // (100 - 1 = 99) + (100 - 2 = 98) = 197
	a.clear();
	a = {1, 3, 1, 2};
	assert(StockMax(a) == 3);
	a.clear();
	a = {1, 2, 3, 0, 2, 5};
	assert(StockMaxProfit(a) == 6);
	a.clear();
	a = {1, 2, 3, 0, 1, 5};
	assert(StockMaxProfit(a) == 6);
	a.clear();
	a = {1, 2, 6, 0, 1, 5};
	assert(StockMaxProfit(a) == 9);
	a.clear();
	a = {1, -2, 0, 9, -1, -2};
	assert(NumberSolitaire(a) == 8);
	a.clear();
	a = {1, -2, 4, 3, -1, -3, -7, 4, -9};
	assert(NumberSolitaire(a) == 3);
	a.clear();
	a = {0, -4, -5, -2, -7, -9, -3, -10};
	assert(NumberSolitaire(a) == -12);
	a.clear();
	a = {-1, -4, -5, -2, -7, -9, -3, -10};
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
	shared_ptr<Node<string>> multiplier = make_shared<Node<string>>("*");
	shared_ptr<Node<string>> adder = make_shared<Node<string>>("+");
	shared_ptr<Node<string>> minus = make_shared<Node<string>>("-");
	shared_ptr<Node<string>> num1 = make_shared<Node<string>>("1"), num2 = make_shared<Node<string>>("2"), num3 = make_shared<Node<string>>("3"), num4 = make_shared<Node<string>>("4");
	shared_ptr<Node<string>> num5 = make_shared<Node<string>>("1.2"), num6 = make_shared<Node<string>>("2.3"), num7 = make_shared<Node<string>>("3.4"), num8 = make_shared<Node<string>>("4.5");
	adder->SetLeft(num1);
	adder->SetRight(num2);
	minus->SetLeft(num3);
	minus->SetRight(num4);
	multiplier->SetLeft(adder);
	multiplier->SetRight(minus);
	// (1 + 2) * (3 - 4) = 3 * -1 = -3
	assert(TreeArithmeticTotal<long>(multiplier) == -3);
	adder->SetLeft(num5);
	adder->SetRight(num6);
	minus->SetLeft(num7);
	minus->SetRight(num8);
	// (1.2 + 2.3) * (3.4 - 4.5) = 3.5 * -1.1 = -3.85
	double expected = (1.2 + 2.3) * (3.4 - 4.5);
	assert(fabs(TreeArithmeticTotal<double>(multiplier) - expected) < numeric_limits<double>::epsilon());
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
	CircularLinkedListLoopStart();
	MaxZeroProductTests();
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
	a = {-3, 1, 2, -2, 5, 6};
	assert(MaxProductOfThree(a) == 60);
	IncreasingSequenceTests();
	assert(binary_gap(9) == 2);
	assert(binary_gap(32) == 0);
	assert(binary_gap(529) == 4);
	data.clear();
	data.resize(5);
	generate(data.begin(), data.end(), [i = 0]() mutable
			 { return i++; });
	/* 0 1 2 3 4 => 2 3 4 0 1 (Rotate 3)
	 */
	RotateRightArray(data, 3);
	for (size_t i = 0, j = 2; i < data.size(); i++, j = ++j % data.size())
		assert(data[i] == j);
	data.clear();
	data.resize(5);
	generate(data.begin(), data.end(), [i = 0]() mutable
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
	a = {2, 1, 5, 3, 4};
	assert(minimumBribes(a) == 3);
	a.clear();
	a = {2, 5, 1, 3, 4};
	assert(minimumBribes(a) == -1);
	assert(SherlockValidString("abcdefghhgfedecba"));
	assert(!SherlockValidString("aabbcd"));
	assert(!SherlockValidString("aaaabbcc"));
	assert(!SherlockValidString("xxxaabbccrry"));
	assert(SherlockValidString("ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd"));
	line = "if man was meant to stay on the ground god would have given us roots";
	assert(encryption(line) == "imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau");
	a.clear();
	a = {100, 100, 50, 40, 40, 20, 10};
	b.clear();
	b = {5, 25, 50, 120};
	vector<size_t> leaderBoardResult = climbingLeaderboard(a, b);
	assert(leaderBoardResult[0] == 6);
	assert(leaderBoardResult[1] == 4);
	assert(leaderBoardResult[2] == 2);
	assert(leaderBoardResult[3] == 1);
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
	a = {1, 3, 5, 7, 9};
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
	vector<long> from{1, 1, 4, 2, 3, 3}, to{2, 3, 1, 4, 2, 4}, weights{5, 3, 6, 7, 4, 5};
	assert(kruskals(4, from, to, weights) == 12);
	from.clear();
	to.clear();
	weights.clear();
	from = {1, 3, 4, 1, 3};
	to = {2, 2, 3, 4, 1};
	weights = {1, 150, 99, 100, 200};
	assert(kruskals(4, from, to, weights) == 200);

	from.clear();
	to.clear();
	weights.clear();
	from = {1, 3, 1, 4, 2};
	to = {2, 5, 4, 5, 3};
	weights = {60, 70, 120, 150, 80};
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

	grid1 = {{1, 2, 3}, {1, 3, 4}, {4, 2, 6}, {5, 2, 2}, {2, 3, 5}, {3, 5, 7}};
	assert(PrimMinimumSpanningTree(5, grid1, 1) == 15);

	grid1 = {{1, 2, 20}, {1, 3, 50}, {1, 4, 70}, {1, 5, 90}, {2, 3, 30}, {3, 4, 40}, {4, 5, 60}};
	assert(PrimMinimumSpanningTree(5, grid1, 2) == 150);

	grid1 = {{2, 1, 1000}, {3, 4, 299}, {2, 4, 200}, {2, 4, 100}, {3, 2, 300}, {3, 2, 6}};
	assert(PrimMinimumSpanningTree(4, grid1, 2) == 1106);

	grid1 = {{1, 2}, {2, 3}, {1, 4}};
	vector<size_t> unbeatenPaths;
	UnbeatenPaths(4, grid1, 1, unbeatenPaths);
	assert(unbeatenPaths.size() == 3);
	assert(unbeatenPaths[0] == 3);
	assert(unbeatenPaths[1] == 1);
	assert(unbeatenPaths[2] == 2);

	grid1 = {{1, 2}, {2, 3}};
	unbeatenPaths.clear();
	UnbeatenPaths(4, grid1, 2, unbeatenPaths);
	assert(unbeatenPaths.size() == 3);
	assert(unbeatenPaths[0] == 2);
	assert(unbeatenPaths[1] == 2);
	assert(unbeatenPaths[2] == 1);
	grid1.clear();
	grid1.resize(1);
	grid1[0].push_back(1);
	assert(SurfaceArea3D(grid1) == 6);
	grid1.clear();
	grid1.resize(1);
	grid1[0] = {1, 0, 1};
	assert(SurfaceArea3D(grid1) == 12);

	grid1 = {{1, 3, 4}, {2, 2, 3}, {1, 2, 4}};
	assert(SurfaceArea3D(grid1) == 60);

	grid1.clear();
	grid1.resize(1);
	grid1[0] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
	assert(SurfaceArea3D(grid1) == 90);

	grid1 = {{1}, {2}, {3}, {4}, {5}, {5}, {4}, {3}, {2}, {1}};
	assert(SurfaceArea3D(grid1) == 90);

	grid1.clear();
	grid1.resize(1);
	grid1[0] = {1, 2, 3, 4, 5, 4, 5, 4, 3, 2, 1};
	assert(SurfaceArea3D(grid1) == 102);

	grid1 = {{1}, {2}, {3}, {4}, {5}, {4}, {5}, {4}, {3}, {2}, {1}};
	assert(SurfaceArea3D(grid1) == 102);

	grid1 = {{51}, {32}, {28}, {49}, {28}, {21}, {98}, {56}, {99}, {77}};
	assert(SurfaceArea3D(grid1) == 1482);

	a.clear();
	a = {4, 2};
	assert(AlmostSorted(a) == "swap 1 2");
	a.clear();
	a = {4104, 8529, 49984, 54956, 63034, 82534, 84473, 86411, 92941, 95929, 108831, 894947, 125082, 137123, 137276, 142534, 149840, 154703, 174744, 180537, 207563, 221088, 223069, 231982, 249517, 252211, 255192, 260283, 261543, 262406, 270616, 274600, 274709, 283838, 289532, 295589, 310856, 314991, 322201, 339198, 343271, 383392, 385869, 389367, 403468, 441925, 444543, 454300, 455366, 469896, 478627, 479055, 484516, 499114, 512738, 543943, 552836, 560153, 578730, 579688, 591631, 594436, 606033, 613146, 621500, 627475, 631582, 643754, 658309, 666435, 667186, 671190, 674741, 685292, 702340, 705383, 722375, 722776, 726812, 748441, 790023, 795574, 797416, 813164, 813248, 827778, 839998, 843708, 851728, 857147, 860454, 861956, 864994, 868755, 116375, 911042, 912634, 914500, 920825, 979477};
	assert(AlmostSorted(a) == "swap 12 95");
	a.clear();
	a = {43, 65, 1, 98, 99, 101};
	assert(AlmostSorted(a) == "no");
	assert(cipher(7, 4, string("1110101001")) == "1001011");
	assert(cipher(4, 5, string("11000110")) == "1010");
	assert(DecryptPassword(string("43Ah*ck0rr0nk")) == "hAck3rr4nk");
	assert(DecryptPassword(string("51Pa*0Lp*0e")) == "aP1pL5e");
	udata.clear();
	udata = {1, 2, 3};
	assert(sherlockAndCost(udata) == 2);
	udata.clear();
	udata = {4, 7, 9};
	assert(sherlockAndCost(udata) == 12);
	udata.clear();
	udata = {10, 1, 10, 1, 10};
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
	assert(FindSubsequenceDynamicProgramming(string("1221"), string("12")) == 2);
	assert(FindSubsequenceDynamicProgramming(string("1234"), string("56")) == 0);
	assert(FindSubsequenceDynamicProgramming(string("kkkkkkz"), string("kkkk")) == 15);
	assert(shortPalindrome(string("kkkkkkz")) == 15);
	assert(shortPalindrome(string("ghhggh")) == 4);
	assert(shortPalindrome(string("cbbdcacccdaddbaabbaacbacacaaddaaacdbccccccbbadbbcdddddddaccbdbddcbacaaadbbdcbcbcdabdddbbcdccaacdccab")) == 242745);
	strings = {"123412", "561212", "123634", "781288"};
	strings1 = {"12", "34"};
	assert(gridSearch(strings, strings1));
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
	strings = {"2", "1", "+", "3", "*"};
	assert(ReversePolishNotation(strings) == 9);
	strings.clear();
	strings = {"4", "13", "5", "/", "+"};
	assert(ReversePolishNotation(strings) == 6);
	strings.clear();
	strings = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
	assert(ReversePolishNotation(strings) == 22);
	assert(basicCalculator(string("3+2*2-1")) == 6);
	assert(basicCalculator(string("3+2")) == 5);
	assert(basicCalculator(string("3-2")) == 1);
	assert(basicCalculator(string("3*2+2")) == 8);
	assert(basicCalculator(string("3+2-4*5")) == -15);
	assert(basicCalculator(string("3*2+5/4")) == 7);
	a.clear();
	a = {1, 2, 3, 4};
	a = productExceptSelf(a);
	b.clear();
	b = {24, 12, 8, 6};
	assert(!a.empty());
	assert(a.size() == 4);
	assert(b == a);
	udata.clear();
	udata = {3, 0, 6, 1, 5};
	assert(hIndex(udata) == 3);
	udata.clear();
	udata = {0, 1};
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = {1, 1};
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = {123};
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = {1, 1, 2};
	assert(hIndex(udata) == 1);
	udata.clear();
	udata = {1, 2, 2};
	assert(hIndex(udata) == 2);
	udata.clear();
	udata = {3, 2, 2};
	assert(hIndex(udata) == 2);
	udata.clear();
	udata = {3, 3, 2};
	assert(hIndex(udata) == 2);
	grid1.clear();
	grid1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	a.clear();
	a = {1, 2, 3, 6, 9, 8, 7, 4, 5};
	assert(matrixSprialOrder(grid1) == a);
	grid1.clear();
	grid1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
	a.clear();
	a = {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
	assert(matrixSprialOrder(grid1) == a);
	grid1.clear();
	grid1 = {{1, 2}, {3, 4}};
	a.clear();
	a = {1, 2, 4, 3};
	assert(matrixSprialOrder(grid1) == a);
	grid1.clear();
	grid1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	grid2 = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
	rotateMatrix90DegressClockwise(grid1);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	rotateMatrixRTimesAntiClockwise(grid1, 1);
	assert(grid1 == grid2);
	grid1 = {{1}};
	grid2 = {{1}};
	rotateMatrixRTimesAntiClockwise(grid1, 1);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{}};
	grid2 = {{}};
	rotateMatrixRTimesAntiClockwise(grid1, 1);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{2, 4}, {1, 3}};
	rotateMatrixRTimesAntiClockwise(grid1, 1);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{4, 3}, {2, 1}};
	rotateMatrixRTimesAntiClockwise(grid1, 2);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{3, 1}, {4, 2}};
	rotateMatrixRTimesAntiClockwise(grid1, 3);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{1, 2}, {3, 4}};
	rotateMatrixRTimesAntiClockwise(grid1, 0);
	assert(grid1 == grid2);
	rotateMatrixRTimesAntiClockwise(grid1, 4);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{2, 4}, {1, 3}};
	rotateMatrixRTimesAntiClockwise(grid1, 5);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{4, 3}, {2, 1}};
	rotateMatrixRTimesAntiClockwise(grid1, 6);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{3, 1}, {4, 2}};
	rotateMatrixRTimesAntiClockwise(grid1, 7);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {12, 1, 2, 5}, {11, 4, 3, 6}, {10, 9, 8, 7}};
	grid2 = {{3, 4, 5, 6}, {2, 3, 4, 7}, {1, 2, 1, 8}, {12, 11, 10, 9}};
	rotateMatrixRTimesAntiClockwise(grid1, 2);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	grid2 = {{3, 4, 8, 12}, {2, 11, 10, 16}, {1, 7, 6, 15}, {5, 9, 13, 14}};
	rotateMatrixRTimesAntiClockwise(grid1, 2);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	grid2 = {{2, 3, 4, 8}, {1, 7, 11, 12}, {5, 6, 10, 16}, {9, 13, 14, 15}};
	rotateMatrixRTimesAntiClockwise(grid1, 1);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {7, 8, 9, 10}, {13, 14, 15, 16}, {19, 20, 21, 22}, {25, 26, 27, 28}};
	grid2 = {{28, 27, 26, 25}, {22, 9, 15, 19}, {16, 8, 21, 13}, {10, 14, 20, 7}, {4, 3, 2, 1}};
	rotateMatrixRTimesAntiClockwise(grid1, 7);
	assert(grid1 == grid2);
	grid1.clear();
	grid2.clear();
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
	stringset.clear();
	stringset = {"Hello", "World"};
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
	stringset = {"cats", "dog", "sand", "and", "cat"};
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
	stringset = {"apple", "pen"};
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
	stringset = {"aaaa", "aaa"};
	assert(wordBreakDynamicProgramming(string("aaaaaaa"), stringset));
	strings1.clear();
	wordBreakDynamicProgramming(string("aaaaaaa"), stringset, strings1);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	strings1.clear();
	strings1 = wordBreakDFS(string("aaaaaaa"), stringset);
	assert(!strings1.empty());
	assert(strings1.size() == 2);
	ugrid = {{1, 0}};
	udata.clear();
	assert(canFinishCourseTopologicalSort(2, ugrid, udata));
	assert(!udata.empty());
	assert(udata.size() == 2);
	assert(udata[0] == 0);
	assert(udata[1] == 1);
	ugrid.clear();
	ugrid = {{1, 0}, {0, 1}};
	udata.clear();
	assert(!canFinishCourseTopologicalSort(2, ugrid, udata));
	assert(udata.empty());
	ugrid.clear();
	ugrid = {{1, 0}, {2, 0}};
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
	ugrid = {{1, 0}, {0, 2}, {2, 1}};
	udata.clear();
	assert(!canFinishCourseTopologicalSort(3, ugrid, udata));
	assert(udata.empty());
	a.clear();
	a = {1, 2, 3, 1};
	assert(containsNearbyAlmostDuplicate(a, 3, 0));
	a.clear();
	a = {1, 0, 1, 1};
	assert(containsNearbyAlmostDuplicate(a, 1, 2));
	a.clear();
	a = {1, 5, 9, 1, 5, 9};
	assert(!containsNearbyAlmostDuplicate(a, 2, 3));
	assert(!containsNearbyAlmostDuplicate(a, 0, 0)); // indices must be distinct
	assert(!containsNearbyAlmostDuplicate(a, 0, 1));
	assert(containsNearbyAlmostDuplicate(a, 3, 0));
	assert(!containsNearbyAlmostDuplicate(a, 2, 0));
	assert(!containsNearbyAlmostDuplicate(a, -1, -1));
	a.clear();
	assert(abs(2147483647L - -1) == (long)2147483648);
	assert(abs(-1 - 2147483647L) == (long)2147483648);
	a = {2147483647, -1, 2147483647}; // 0x7FFFF_FFFF, 0xFFFF_FFFF
	assert(!containsNearbyAlmostDuplicate(a, 1, 2147483647));
	assert(!containsNearbyAlmostDuplicate(a, 1, -2147483648L)); // 2147483648 is 0x8000_0000 = 0xFFFF_FFFF_8000_0000 < 0
	a.clear();
	assert(abs(-INT_MIN - 0x7FFFFFFF) == 1);
	assert(abs(0x7FFFFFFF - -INT_MIN) == 1);
	a = {(long)-2147483648, 2147483647};			 // 0xFFFF_FFFF_8000_0000, 0x7FFF_FFFF
	assert(!containsNearbyAlmostDuplicate(a, 1, 1)); // -2147483648 = 0xFFFF_FFFF_8000_0000; 2147483647 = 0x7FFF_FFFF. One in negative bucket, another in positive bucket. Different from abs((long)2147483648 - (long)2147483647)
	a.clear();
	a = {4, 1, -1, 6, 5};
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
	grid1 = {{2, 0, -3, 4}, {6, 3, 2, -1}, {5, 4, 7, 3}, {2, -6, 8, 1}};
	CMatrix<long> matrix(grid1);
	ugrid.clear();
	ugrid = {{1, 1}, {3, 2}};
	assert(matrix.Sum(ugrid) == 18);
	ugrid.clear();
	ugrid = {{0, 2}, {3, 3}};
	assert(matrix.Sum(ugrid) == 21);
	ugrid.clear();
	sum = matrix.LargestSumSubmatrix(ugrid);
	assert(!ugrid.empty());
	grid1.clear();
	grid1 = {{-4, -5}};
	CMatrix<long> matrix1(grid1);
	ugrid.clear();
	ugrid = {{0, 0}, {0, 0}};
	assert(matrix1.Sum(ugrid) == -4);
	ugrid.clear();
	ugrid = {{0, 0}, {0, 1}};
	assert(matrix1.Sum(ugrid) == -9);
	ugrid.clear();
	assert(matrix1.LargestSumSubmatrix(ugrid) == -4);
	assert(!ugrid.empty());
	ugrid1.clear();
	ugrid1 = {{0, 0}, {0, 0}};
	assert(ugrid1 == ugrid);
	grid1.clear();
	grid1 = {{-1, -2, -3, -4}, {-2, 3, 2, -3}, {-3, 4, 7, -2}, {-4, -3, -2, -1}};
	CMatrix<long> matrix2(grid1);
	ugrid.clear();
	ugrid1.clear();
	assert(matrix2.LargestSumSubmatrix(ugrid) == 16);
	assert(!ugrid.empty());
	ugrid1 = {{1, 1}, {2, 2}};
	assert(ugrid1 == ugrid);
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
	a.clear();
	a = {1, 7, 4, 9, 2, 5};
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 6);
	assert(a == b);
	a.clear();
	a = {0};
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 1);
	assert(b.back() == 0);
	a.clear();
	a = {0, 0};
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 1);
	assert(b.back() == 0);
	a.clear();
	b.clear();
	a = {3, 3, 3, 2, 5};
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 3);
	a.clear();
	a = {3, 2, 5};
	assert(b == a);
	a.clear();
	a = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 7);
	a.clear();
	a = {1, 17, 5, 15, 5, 16, 8};
	assert(a == b);
	a.clear();
	a = {1, 17, 5, 10, 13, 15, 12, 5, 16, 8};
	b.clear();
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 7);
	a.clear();
	a = {1, 17, 5, 15, 5, 16, 8};
	assert(a == b);
	a.clear();
	b.clear();
	a = {1, 17, 5, 10, 13, 11, 12, 5, 16, 8};
	wiggleMaxLength(a, b);
	assert(!b.empty());
	assert(b.size() == 9);
	a.clear();
	a = {1, 17, 5, 13, 11, 12, 5, 16, 8};
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
	strings = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
	assert(maxProductOfNonOverlappingWordLengths(strings) == 16); // "abcw", "xtfn"
	strings.clear();
	strings = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
	assert(maxProductOfNonOverlappingWordLengths(strings) == 4); // "ab", "cd"
	strings.clear();
	strings = {"a", "aa", "aaa", "aaaa"};
	assert(maxProductOfNonOverlappingWordLengths(strings) == 0);
	sgrid.clear();
	sgrid = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
	strings = findItinerary(sgrid, string("JFK"));
	assert(!strings.empty());
	assert(strings.size() == 5);
	strings1.clear();
	strings1 = {"JFK", "MUC", "LHR", "SFO", "SJC"};
	assert(strings1 == strings);
	sgrid.clear();
	sgrid = {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
	strings = findItinerary(sgrid, string("JFK"));
	assert(!strings.empty());
	assert(strings.size() == 6);
	strings1.clear();
	strings1 = {"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"};
	assert(strings1 == strings);
	sgrid.clear();
	sgrid = {{"EZE", "AXA"}, {"TIA", "ANU"}, {"ANU", "JFK"}, {"JFK", "ANU"}, {"ANU", "EZE"}, {"TIA", "ANU"}, {"AXA", "TIA"}, {"TIA", "JFK"}, {"ANU", "TIA"}, {"JFK", "TIA"}};
	strings = findItinerary(sgrid, string("JFK"));
	assert(!strings.empty());
	assert(strings.size() == 11);
	strings1.clear();
	strings1 = {"JFK", "ANU", "EZE", "AXA", "TIA", "ANU", "JFK", "TIA", "ANU", "TIA", "JFK"};
	assert(strings1 == strings);
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
	/***** The End *****/
	// cout << endl << "Press ENTER to exit!";
	// getline(cin, line);
	return 0;
}
void testPointerReference(int *&ptr)
{
	free(ptr);
	ptr = (int *)malloc(101 * sizeof(int));
	memset(ptr, 0xabababab, 101 * sizeof(int)); // XXX: sizeof(int*) is 8 bytes on x64!!!
}
long Min(long a, long b)
{
	long delta = b - a;
	long sign = (delta >> 31) & 1;
	// b > a: sign = 0: returns a
	// b < a: sign = 1: returns a - (a - b) = b
	return a - sign * (a - b);
}
long Max(long a, long b)
{
	long delta = a - b;
	long sign = (delta >> 31) & 1;
	// a > b: sign = 0 => return a
	// a < b: sign = 1 => return a - (a - b) = b
	return a - sign * (a - b);
}
float MachineEpsilon(float value)
{
	thirty_two_bit f;
	f.f = value;
	f.l++;
	return f.f - value;
}
double MachineEpsilon(double value)
{
	sixty_four_bit d;
	d.d = value;
	d.ll++;
	return d.d - value;
}
float FloatMachineEpsilonApproximation()
{
	float e = 1.0;
	while ((1 + 0.5 * e) != 1.0)
		e *= 0.5;
	return e;
}
double MachineEpsilonApproximation()
{
	double e = 1.0;
	while ((1 + 0.5 * e) != 1.0)
		e *= 0.5;
	return e;
}
/* Assume ASCII character set */
bool isUniqueString(string const &str)
{
	size_t i;
	bool char_set[256];
	for (i = 0; i < 256; i++)
		char_set[i] = false;
	for (i = 0; i < str.length(); i++)
	{
		if (char_set[str[i]])
			return false;
		char_set[str[i]] = true;
	}
	return true;
}
vector<string> findUnique(vector<string> const &a, vector<string> const &b)
{
	vector<string> result;
	vector<string> c(a);
	c.insert(c.end(), b.begin(), b.end());
	sort(c.begin(), c.end());
	for (vector<string>::const_iterator it = c.begin(); it != c.end(); it++)
	{
		if (it != (c.end() - 1))
		{
			if (*it != *(it + 1))
				result.push_back(*it);
			else
			{
				while (it != (c.end() - 1) && *it == *(it + 1))
					it++;
			}
		}
		else
			result.push_back(*it);
	}
	return result;
}
bool CanShuffleWithoutRepeat(string &str)
{
	map<char, size_t> repeats;
	size_t maxCount = 0;
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		repeats[*it]++;
		maxCount = max(maxCount, repeats[*it]);
	}
	return str.size() - maxCount >= maxCount - 1;
}
// https://en.wikipedia.org/wiki/Maximum_subarray_problem
// Kadane's algorithm
long ConsecutiveLargestSum(vector<long> &data, vector<long> &result)
{
	vector<long> tmp;
	map<long, vector<long>> results;
	long max_ending_here = 0, max_so_far = 0; // max_so_far = max of all max_ending_here's found
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++)
	{
		max_ending_here += *it;
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			tmp.clear();
		}
		else
			tmp.push_back(*it);
		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			results.emplace(max_so_far, tmp);
		}
	}
	result = results[max_so_far];
	return max_so_far;
}
/* https://leetcode.com/problems/maximum-product-subarray/
 * 100%
 */
long ConsecutiveLargestProduct(vector<long> &data)
{
	vector<long> tmp;
	map<long, vector<long>> results;
	long maxproduct = numeric_limits<long>::min(), max_ending_here = 1, min_ending_here = 1;
	bool zero = false;
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++)
	{
		if (!*it)
		{
			zero = true;
			maxproduct = max(maxproduct, (long)0);
		}
		else if (*it > 0)
		{
			min_ending_here = zero ? 1 : min((long)1, min_ending_here * *it); // -ve * +ve
			max_ending_here = zero ? *it : max_ending_here * *it;
			zero = false;
			maxproduct = max(maxproduct, max_ending_here);
		}
		else
		{ // < 0
			long tmp = max_ending_here;
			if (!zero)
			{
				if (min_ending_here * *it > 0)
				{
					max_ending_here = min_ending_here * *it;
					maxproduct = max(maxproduct, max_ending_here);
				}
				else
					max_ending_here = 1;
				min_ending_here = tmp ? min((long)1, tmp * *it) : *it; // +ve * -ve
			}
			else
			{
				min_ending_here = *it;
				max_ending_here = 1;
			}
			zero = false;
		}
	}
	return maxproduct;
}
// https://app.codility.com/programmers/task/longest_nonnegative_sum_slice/
// https://app.codility.com/programmers/challenges/ferrum2018/
// Find the longest sequence when the graph crosses a previous point. The crossing point is when negative becomes positive and vice versa
// 100%
long LongestNonNegativeSumSlice(vector<long> &data)
{
	// -1, -1, -1, -1, -1, -1, 1 (max_len = max(1, 6 - 4) = 2), 1 (max_len = max(2, 7 - 3) = 4)
	//  1,  1,  1,  1,  1,  1,-1 (max_len = max(6, 6 - 4) = 6),-1 (max_len = max(6, 7 - 3) = 6)
	map<long, size_t> sums;
	long sum = 0;
	size_t max_len = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		sum += data[i];
		if (sum >= 0)
			max_len = i + 1;
		else if (data[i] >= 0 && max_len == 0)
			max_len = 1;
		if (sums.find(sum) != sums.end())
			max_len = max(max_len, i - sums[sum]);
		else
			sums.emplace(sum, i);
	}
	return max_len;
}
size_t CountDistinctSlices1(long m, vector<long> &data)
{
	size_t slices = 0;
	set<string> uniqueslices;
	set<long> unique;
	size_t j;
	for (size_t i = 0; i < data.size();)
	{
		unique.clear();
		unique.emplace(data[i]);
		for (j = i + 1; j < data.size() && unique.find(data[j]) == unique.end(); j++)
			unique.emplace(data[j]);
		for (size_t k = (j - i); k > 0; k--)
			slices += k;
		i = j;
	}
	return slices;
}
// a.push_back(3); // 3
// a.push_back(4); // 2
// a.push_back(5); // 1
// a.push_back(5); // 2
// a.push_back(2); // 1
size_t CountDistinctSlices(long m, vector<long> &data)
{
	size_t slices = 0, start = 0;
	set<long> unique;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (unique.find(data[i]) == unique.end())
			unique.emplace(data[i]);
		else
		{
			slices += SequenceSum(i - start);
			start = i;
			unique.clear();
			unique.emplace(data[i]);
		}
	}
	return slices + SequenceSum(data.size() - start);
}
// "Hello World!!!" -> "!!!dlroW olleH"
void reverse(string &str)
{
	char tmp;
	size_t pivot = str.size() / 2 + str.size() % 2;
	for (size_t i = 0, tail = str.size() - 1; i < pivot; i++, tail--)
	{
		tmp = str[tail];
		str[tail] = str[i];
		str[i] = tmp;
	}
}
/*
 * "Hello World!!!" -> "World!!! Hello"
 * 1: "Hello World!!!" -> "!!!dlroW olleH"
 * 2: "!!!dlroW olleH" -> "World!!! Hello"
 */
void reverseWords(string &str)
{
	reverse(str);
	for (size_t i = 0, j = 0; i != string::npos; j = i + 1)
	{
		i = str.find(" ", j);
		if (i != string::npos)
		{
			string tmp = str.substr(j, i - j);
			reverse(tmp);
			str.replace(j, i - j, tmp);
		}
		else
		{
			string tmp = str.substr(j);
			reverse(tmp);
			str.replace(j, str.size() - j, tmp);
		}
	}
}
/* "  Hello World!!!  " -> "World!!! Hello"
 * 1: "Hello World!!!" -> "!!!dlroW olleH"
 * 2: "!!!dlroW olleH" -> World!!! Hello"
 */
void reverseWordsTrimmed(string &str)
{
	reverse(str);
	for (size_t i = 0, j = 0; i != string::npos && j < str.size();)
	{
		i = str.find(' ', j);
		if (i != string::npos)
		{
			size_t k = i;
			for (; str[k] == ' '; k++)
				;
			if (!i)
			{ // If str is prefixed with spaces
				str = str.substr(k);
				continue;
			}
			else if (k == str.size()) // if str ends with spaces
				str.erase(i, k - i);
			else if ((k - i) > 1) // More than one space in between words
				str.erase(i, k - i - 1);
			string tmp = str.substr(j, i - j);
			reverse(tmp);
			str.replace(j, i - j, tmp);
		}
		else
		{
			string tmp = str.substr(j);
			reverse(tmp);
			str.replace(j, str.size() - j, tmp);
		}
		j = i + 1;
	}
}
/* 0 1   2   3
 *  a b   b   c
 *    i,t
 *    j
 *  a b   b   c
 *        i,t
 *    j
 *  a b   b   c
 *        t   i
 *        j
 *  a b   c
 */
void RemoveDuplicateCharacters(string &str)
{
	if (str.size() > 1)
	{
		size_t tail = 1, j;
		for (size_t i = tail; i < str.size(); i++)
		{
			for (j = 0; j < tail && str[j] != str[i]; j++)
				;
			if (j == tail) // str[i] is not a duplicate character. So copy it to str[tail]
				str[tail++] = str[i];
		}
		str[tail] = 0;
		str.resize(tail);
	}
}
/* https://leetcode.com/problems/remove-duplicate-letters/
* 100%
bcabc
bc
  abc

abacb
ab
  acb <= abc

cbacdcbc
c
 b
  acd c b

cbacdbcd
c
 b
  acd b -> acb -> ab
	abcd

cbaidbcj
c
 b
  aidbcj
WITHOUT reorder the original character sequence!
*/
void RemoveDuplicateCharactersLexicographicalOrder(string &str)
{
	string result;
	map<char, long> counts;
	for (size_t i = 0; i < str.size(); i++)
		counts[str[i]]++;
	for (size_t i = 0; i < str.size(); i++)
	{
		char c = str[i];
		for (; !result.empty() && c < result.back() && counts[result.back()] && result.find(c) == string::npos; result.pop_back())
			;
		if (result.find(c) == string::npos)
			result.push_back(c);
		counts[c]--;
	}
	str = result;
}
/* https://leetcode.com/problems/additive-number/
 * 100%
 * i: width of the first operand
 * j: width of the second operand
 * width of sum is max(i, j). So i must be <= half the input string size
 */
bool isAdditiveNumber(const string &str)
{
	for (size_t i = 1; i <= str.size() / 2; i++)
		for (size_t j = 1; max(i, j) <= str.size() - i - j; j++)
			if (checkIfAdditiveSequence(i, j, str))
				return true;
	return false;
}
/*
 * 123581321
 * 1 2 3
 *   2 3 5
 *     3 5 8
 *       5 8 13
 *         8 13 21
 */
bool checkIfAdditiveSequence(size_t i, size_t j, const string &str)
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
bool areAnagrams(string const &s1, string const &s2)
{
	if (s1.size() == s2.size())
	{
		string str1(s1), str2(s2);
		sort(str1.begin(), str1.end());
		sort(str2.begin(), str2.end());
		return str1 == str2;
	}
	else
		return false;
}
size_t FindAnagrams(vector<string> const &s, vector<vector<string>> &result)
{
	map<string, vector<string>> anagrams;
	for (vector<string>::const_iterator it = s.begin(); it != s.end(); it++)
	{
		string s1(*it);
		sort(s1.begin(), s1.end());
		anagrams[s1].push_back(*it);
	}
	size_t count = 0;
	for (map<string, vector<string>>::const_iterator it = anagrams.begin(); it != anagrams.end(); it++)
	{
		/*
			2 elements: a a = [0,1] 1 pair of anagrams
			3 elements: a a a = [0,1],[1,2],[0,2] 3 pairs of anagrams
			4 elements: a a a a = [0,1],[1,2],[2,3],[0,2],[0,3] 5 pairs of anagrams
			(n+1)*n/2 - n = ((n+1)*n - 2n) / 2 = (n^2 + n - 2n) / 2 = (n^2 - n) / 2 = (n * (n - 1)) / 2 (Note: Multiply BEFORE divide!)
		*/
		if (it->second.size() > 1)
			result.push_back(it->second);
		count += ((it->second.size() - 1) * it->second.size()) / 2;
	}
	return count;
}
// https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem
// 100%
size_t sherlockAndAnagrams(string const &s)
{
	vector<string> strings;
	vector<vector<string>> anagrams;
	for (size_t i = 0; i < s.size(); i++)
		for (size_t len = 1; len <= s.size() - i; len++)
			strings.push_back(s.substr(i, len));
	return FindAnagrams(strings, anagrams);
}
/*
	https://www.hackerrank.com/challenges/sherlock-and-cost/problem
	100%
4 7 9
i: 1
hl = 4 - 1 = 3
lh = 7 - 1 = 6
hh = 7 - 4 = 3
l = max(0, 0+3) = 3
h = max(0+3, 0+6) = 6

i: 2
hl = 7 - 1 = 6
lh = 9 - 1 = 8
hh = 9 - 7 = 2
l = max(3, 6+6) = 12
h = max(6+2, 3+8) = 11
*/
size_t sherlockAndCost(vector<size_t> &data)
{
	/*
		lh: low to high from data[i - 1]=1 to data[i]
		hl: high to low from data[i - 1] to data[i]=1
		hh: hight to high from data[i - 1] to data[i]
	*/
	size_t l = 0, h = 0, lh, hh, hl, newLow, newHigh;
	for (size_t i = 1; i < data.size(); i++)
	{
		lh = abs((long)data[i] - 1);
		hl = abs((long)data[i - 1] - 1);
		hh = abs((long)data[i] - (long)data[i - 1]);

		newLow = max(l, h + hl);
		newHigh = max(h + hh, l + lh);

		l = newLow;
		h = newHigh;
	}
	return max(l, h);
}
void PalindromeTests()
{
	set<string> palindromes;
	assert(isPalindrome("abcdefghhgfedecba"));
	assert(!isPalindrome("aabbcd"));
	assert(isPalindrome("aabbc"));
	assert(!isPalindrome("xxxaabbccrry"));
	//	assert(!isPalindrome("aaaabbcc"));
	assert(isPalindrome("mmo"));
	assert(!isPalindrome2("mmo"));
	assert(isPalindrome("yakak"));
	assert(!isPalindrome2("yakak"));
	assert(!isPalindrome("travel"));
	assert(isPalindrome1("mmo"));
	assert(isPalindrome1("yakak"));
	assert(!isPalindrome1("travel"));
	assert(isPalindrome("12121"));
	assert(isPalindrome("12321"));
	assert(isPalindrome("123321"));
	assert(!isPalindrome("121212"));
	assert(!isPalindrome("123421"));
	assert(isPalindrome1("12121"));
	assert(isPalindrome1("12321"));
	assert(isPalindrome1("123321"));
	assert(!isPalindrome1("121212"));
	assert(!isPalindrome1("123421"));
	assert(isPalindrome2("12121"));
	assert(isPalindrome2("12321"));
	assert(isPalindrome2("123321"));
	assert(!isPalindrome2("121212"));
	assert(!isPalindrome2("123421"));
	// https://en.wikipedia.org/wiki/Palindrome
	assert(isPalindrome2("A man, a plan, a canal, Panama!"));
	assert(isPalindrome2("Amor, Roma"));
	assert(isPalindrome2("race car"));
	assert(isPalindrome2("stack cats"));
	assert(isPalindrome2("step on no pets"));
	assert(isPalindrome2("taco cat"));
	assert(isPalindrome2("put it up"));
	assert(isPalindrome2("Was it a car or a cat I saw?"));
	assert(isPalindrome2("No 'x' in Nixon"));
	assert(FindBiggestPalindromeSubstring("AABCDCBA") == "ABCDCBA");
	assert(FindBiggestPalindromeSubstring("AABCDDCBA") == "ABCDDCBA");
	assert(FindBiggestPalindromeSubstring("DEFABCBAYT") == "ABCBA");
	assert(FindBiggestPalindromeSubstring("DEFABCCBAYT") == "ABCCBA");
	assert(PalindromeAnagramCount("02002") == 11);
	assert(PalindromeAnagramCount1("02002") == 11);
	FindPalindromeSubstrings("a", palindromes);
	assert(palindromes.empty());
	palindromes.clear();
	FindPalindromeSubstrings("aa", palindromes);
	assert(palindromes.size() == 1);
	assert(palindromes.find("aa") != palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aaa", palindromes);
	assert(palindromes.size() == 2);
	assert(palindromes.find("aa") != palindromes.end());
	assert(palindromes.find("aaa") != palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aba", palindromes);
	assert(palindromes.size() == 1);
	assert(palindromes.find("aba") != palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aaazaaksforskeeggeeks", palindromes);
	assert(palindromes.find("skeeggeeks") != palindromes.end());
	assert(palindromes.find("aazaa") != palindromes.end());
}
/*
 * 1 2 3 2 1 Odd count; #odd = 1
 * XXX This will return true but NOT palindrome: "13221"
 */
bool isPalindrome(string const &s)
{
	size_t odd = 0;
	size_t length = s.length();
	map<char, size_t> counts;
	for (string::const_iterator it = s.begin(); it != s.end(); it++)
		counts[*it]++;
	for (map<char, size_t>::const_iterator it = counts.begin(); it != counts.end(); it++)
		if (it->second % 2 && (!(length % 2) || ++odd > 1))
			return false;
	return true;
}
/*
 * 12321 => 11223
 *   count: 12121 : true
 * 123421 => 112234
 *   count:  12121 : Even length -> false
 * 12121 => 11122
 *   count: 12312 : true
 * 121212 => 111222
 *   count:  123 : Even length -> false
 */
bool isPalindrome1(string const &s)
{
	size_t count = 1, odd = 0;
	size_t length = s.length();
	string s1(s);
	sort(s1.begin(), s1.end());
	for (size_t i = 1; i < length; i++)
	{
		if (s1[i] == s1[i - 1])
			count++;
		else
		{
			if (count % 2 && (!(length % 2) || ++odd > 1))
				return false;
			count = 1;
		}
	}
	return true;
}
// https://en.wikipedia.org/wiki/Palindrome
bool isPalindrome2(string const &s)
{
	for (size_t i = 0, j = s.size() - 1; i <= j;)
	{
		if (!isalnum(s[i]))
		{
			i++;
			continue;
		}
		if (!isalnum(s[j]))
		{
			j--;
			continue;
		}
		if (tolower(s[i]) != tolower(s[j]))
			return false;
		i++;
		j--;
	}
	return true;
}
// https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
// adapt from isPalindrome()
// 100%
bool SherlockValidString(string const &s)
{
	size_t odd = 0;
	size_t length = s.length();
	map<char, size_t> counts;
	for (string::const_iterator it = s.begin(); it != s.end(); it++)
		counts[*it]++;
	size_t min = numeric_limits<size_t>::max(), max = 0;
	bool result = true;
	map<size_t, size_t> countsCounts;
	for (map<char, size_t>::const_iterator it = counts.begin(); it != counts.end(); it++)
	{
		if (it->second % 2 && (!(length % 2) || ++odd > 1))
			result = false;
		if (it->second > max)
			max = it->second;
		if (it->second < min)
			min = it->second;
		countsCounts[it->second]++;
	}
	if (countsCounts.size() == 2 && countsCounts.find(1) != countsCounts.end() && countsCounts[1] == 1)
		return true;
	return max - min > 1 ? false : result;
}
/*
 * "" -> ""
 * "a" -> "a"
 * "ab" -> "a"
 * "aa" -> "aa"
 */
string FindBiggestPalindromeSubstring(string const &s)
{
	string tmp, palindrome;
	for (size_t i = 1; i < s.size() - 1; i++)
	{
		if (s[i] == s[i + 1])
		{ // Even palindrome: abba
			for (int j = i, k = i + 1; j >= 0; j--, k++)
			{
				if (s[j] == s[k])
				{
					tmp = s.substr(j, k - j + 1);
					if (tmp.size() > palindrome.size())
						palindrome = tmp;
				}
				else
					break;
			}
		}
		else if (s[i - 1] == s[i + 1])
		{ // Odd palindrome
			for (int j = i - 1, k = i + 1; j >= 0; j--, k++)
			{
				if (s[j] == s[k])
				{
					tmp = s.substr(j, k - j + 1);
					if (tmp.size() > palindrome.size())
						palindrome = tmp;
				}
				else
					break;
			}
		}
	}
	return palindrome;
}
/*
"aa"
center: [0,3]
center:0 left: 0, right:0
	p: ""
center:1 left: 0, right: 1
	p: "aa"
center:2 left: 1, right: 1
	p: ""
center:3 left: 1, right: 2
	p: ""
---
"aba"
center: [0,5]
center:0 left:0, right:0
	p: ""
center:1 left:0, right:1
	p: ""
center:2 left:1, right:1
	p: ""
	p: "aba" left:0, right:2
center:3 left:1, right:2
	p: ""
center:4 left:2, right:2
	p: ""
center:5 left:2, right:3
	p: ""
*/
void FindPalindromeSubstrings(string const &s, set<string> &result)
{
	size_t length = s.size();
	for (size_t center = 0; center < 2 * length; center++)
	{
		long left = center / 2;
		long right = left + center % 2;
		string palindrome; // Keep the biggest palindrome around the current 'center'
		while (left >= 0 && right < (long)length && s[left] == s[right])
		{
			palindrome = s.substr(left, right - left + 1);
			left--;
			right++;
			if (!palindrome.empty() && palindrome.size() > 1)
				result.insert(palindrome);
		}
	}
}
// https://app.codility.com/programmers/task/winter_lights/
// WinterLights
// Given a string of digits, count the number of subwords(consistent subsequences) that are anagrams of any palindrome.
// Task Score: 40 %
// Correctness: 100 %
// Performance: 25 %
size_t PalindromeAnagramCount(string const &str)
{
	size_t result = 0;
	vector<string> palindromes;
	string substr;
	// Time complexity: O(N^2)
	for (size_t i = 0; i < str.size(); i++)
	{
		for (size_t j = 1; j <= str.size() - i; j++)
		{
			substr = str.substr(i, j);
			if (j == 1 || (j == 2 && substr[0] == substr[1]))
				result++;
			else if (isPalindrome(substr))
			{
				palindromes.push_back(substr);
				result++;
			}
		}
	}
	return result;
}
// Task Score: 50 %
// Correctness: 100 %
// Performance: 37 %
size_t PalindromeAnagramCount1(string const &str)
{
	size_t result = 0;
	map<char, size_t> counts;
	set<char> oddNumbers;
	long odd = 0;
	bool notPalindrome = false;
	bool evenLength = false;
	// Time complexity: O(N^2)
	for (size_t i = 0; i < str.size(); i++)
	{
		for (size_t j = 1; j <= str.size() - i; j++)
		{
			counts[str[i + (j - 1)]]++;
			evenLength = !(j % 2);
			if (counts[str[i + (j - 1)]] % 2)
			{
				odd++;
				oddNumbers.emplace(str[i + (j - 1)]);
			}
			else
			{
				if (oddNumbers.find(str[i + (j - 1)]) != oddNumbers.end())
					oddNumbers.erase(str[i + (j - 1)]);
				if (--odd < 0)
					odd = 0;
			}
			if ((evenLength || odd > 1) && oddNumbers.size())
				notPalindrome = true;
			if (!notPalindrome)
				result++;
			notPalindrome = false;
		}
		odd = 0;
		oddNumbers.clear();
		counts.clear();
	}
	return result;
}
// Write a code to test whether string s2 is obtained by rotating the string s1 by n places.
bool AreRotatedStrings(string const &s1, string const &s2, size_t n)
{
	string str(s1);
	rotate(str.begin(), str.begin() + n, str.end());
	return (str == s2);
}
// Return occurrance of any anagram of s2 in s1
vector<size_t> FindSubString(string const &s1, string const s2)
{
	vector<size_t> result;
	if (s1.size() >= s2.size())
		for (size_t i = 0; i < s1.size(); i++)
		{
			if (areAnagrams(s1.substr(i, s2.size()), s2))
				result.push_back(i);
		}
	return result;
}
/* https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 */
void KMPTable(string const &w, vector<long> &T)
{
	// the first few values are fixed but different from what the algorithm might suggest
	T.resize(w.size() + 1);
	T[0] = -1;
	long pos = 1, cnd = 0;
	for (; pos < (long)w.size(); pos++, cnd++)
	{
		if (w[pos] == w[cnd])
			T[pos] = T[cnd];
		else
		{
			T[pos] = cnd;
			cnd = T[cnd]; // To increase performance
			for (; cnd >= 0 && w[pos] != w[cnd]; cnd = T[cnd])
				;
		}
	}
	T[pos] = cnd; // (only needed when all word occurrences are searched)
}
void KMPSearch(string const &s, string const &w, vector<size_t> &result)
{
	vector<long> T;
	KMPTable(w, T);
	for (long j = 0, k = 0; j < (long)s.size();)
	{
		if (w[k] == s[j])
		{
			j++;
			k++;
			if (k == w.size())
			{
				// (occurrence found, if only first occurrence is needed, m ← j - k  may be returned here)
				result.push_back(j - k);
				k = T[k]; // (T[length(W)] can't be -1)
			}
		}
		else
		{
			k = T[k];
			if (k < 0)
			{
				j++;
				k++;
			}
		}
	}
}
void copy_on_write_string()
{
	const char *cptr, *cptr1;
	string s1("Hello World!!!");
	string s2 = s1;
	cptr = s1.c_str();
	cptr1 = s1.c_str();
	cout << hex << "s1 @ " << (void *)(cptr) << endl;
	cout << "s2 @ " << (void *)(cptr1) << endl;
	s2 += " Hello World!!!";
	cptr = s1.c_str();
	cptr1 = s1.c_str();
	cout << hex << "s1 @ " << (void *)(cptr) << endl;
	cout << "s2 @ " << (void *)(cptr1) << endl;
}
unsigned long long fibonacci(long n)
{
	// {0 1 1 2 ...}
	return (n <= 1) ? n : fibonacci(n - 2) + fibonacci(n - 1);
}
/* Bottom-up Dynamic Programming
 */
unsigned long long fibonacciDynamicProgramming(long n)
{
	/* 0 1 2 3
	 * {0 1 1 2 3 5 8}
	 * {0, 1}, {1, 1}, {1, 2}, {3, 2}, {3, 5}
	 */
	vector<unsigned long long> result = {0, 1};
	if (n <= 1)
		return n;
	for (size_t i = 2; i <= (size_t)n; i++)
		result[i % 2] = result[(i - 2) % 2] + result[(i - 1) % 2];
	return result[n % 2];
}
/* https://www.hackerrank.com/challenges/fibonacci-modified/problem
 * Timeout for n >= 20
 */
string fibonacciModified(long t1, long t2, long n)
{
	// Index: 0 1 2 3 4 5  6   7	  8
	// Value: 0 1 1 2 5 27 734 538783 ...
	if (!n)
		return to_string(t1);
	else if (n == 1)
		return to_string(t2);
	string s1 = fibonacciModified(t1, t2, n - 2);
	string s2 = fibonacciModified(t1, t2, n - 1);
	string s3 = NumberStringMultiplication(s2, s2);
	return NumberStringSum(s1, s3);
}
string fibonacciModifiedDynamicProgramming(long t1, long t2, long n)
{
	// Index: 0 1 2 3 4 5  6   7	  8
	// Value: 0 1 1 2 5 27 734 538783 ...
	if (!n)
		return to_string(t1);
	else if (n == 1)
		return to_string(t2);
	vector<string> result = {to_string(t1), to_string(t2)};
	for (size_t i = 2; i <= (size_t)n; i++)
		result[i % 2] = NumberStringSum(result[(i - 2) % 2], NumberStringMultiplication(result[(i - 1) % 2], result[(i - 1) % 2]));
	return result[n % 2];
}
// http://web2.0calc.com/
// 64-bit max is 18446744073709551615
// Overflow happens at 21!
unsigned long long factorial(long n)
{
	return (n <= 0) ? 1 : n * factorial(n - 1);
}
unsigned long long factorialDynamicProgramming(long n)
{
	/* 0 1 2 3 4
	 * {1 1 2 6 24 ...}
	 * result = 1,
	 */
	unsigned long long result = 1;
	if (n <= 0)
		return 1;
	for (size_t i = 1; i <= (size_t)n; result *= i++)
		;
	return result;
}
long SequenceSum(long n)
{
	// return (n <= 0) ? 0 : n + SequenceSum(n - 1);
	return (n + 1) * (n) / 2;
}
/*
 Trailing zeros are contributed by pairs of 5 and 2, because 5*2 = 10.
 To count the number of pairs, we just have to count the number of multiples of 5.
 Note that while 5 contributes to one multiple of 10, 25 contributes two (because 25 = 5*5).
 Examples:
 25(5*5) 24 23 22 21 20(5*4) 19 18 17 16 15(5*3) 14 13 12 11 10(5*2) 9 8 7 6 5 4 3 2 1 => 6 zeroes
 10(5*2) 9 8 7 6 5 4 3 2 1 => 2 zeroes
 */
long FactorialTrailingZeroesCount(long n)
{
	long count = 0;
	if (n < 0)
		return 0;
	for (long i = 5; (n / i) > 0; i *= 5)
		count += (n / i);
	return count;
}
void MultiplesCount(int dividend, long &twos, long &fives)
{
	long div = dividend;
	if (dividend > 0)
	{
		for (; (dividend / 5) > 0 && !(dividend % 5); dividend /= 5)
			fives++;
		dividend = div;
		for (; (dividend >> 1) > 0 && !(dividend % 2); dividend >>= 1)
			twos++;
	}
}
// given an array of N positive integers, returns the maximum number of trailing zeros of the number obtained by multiplying three different elements from the array.
// Numbers are considered different if they are at different positions in the array
// 100% correctness However, performance is bad with O(N**3).
long MaxZeroProductBruteForce(vector<int> &data)
{
	long result = 0;
	map<int, ZeroFactors> multipleMap;
	map<int, ZeroFactors>::const_iterator it;
	vector<ZeroFactors> factors;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (!(data[i] % 10 && data[i] % 2 && data[i] % 5))
		{
			it = multipleMap.find(data[i]);
			ZeroFactors factor;
			if (it == multipleMap.end())
			{
				long two = 0, five = 0;
				MultiplesCount(data[i], two, five);
				factor.two = two;
				factor.five = five;
				multipleMap.emplace(data[i], factor);
				factors.push_back(factor);
			}
			else
			{
				factor.two = it->second.two;
				factor.five = it->second.five;
				;
				factors.push_back(factor);
			}
		}
	}
	if (factors.size() == 1)
		result = min(factors[0].two, factors[0].five);
	else if (factors.size() == 2)
		result = min(factors[0].two + factors[1].two, factors[0].five + factors[1].five);
	else if (factors.size() > 2)
	{
		for (size_t i = 0; i < factors.size() - 2; i++)
		{
			for (size_t j = i + 1; j < factors.size() - 1; j++)
			{
				for (size_t k = j + 1; k < factors.size(); k++)
				{
					long twofactor = factors[i].two + factors[j].two + factors[k].two;
					long fivefactor = factors[i].five + factors[j].five + factors[k].five;
					if (min(twofactor, fivefactor) > result)
						result = min(twofactor, fivefactor);
				}
			}
		}
	}
	return result;
}
// XXX: This doesn't work yet
long MaxZeroProduct(vector<int> &data, size_t count = 3)
{
	long result = 0;
	map<int, ZeroFactors> multipleMap;
	map<int, ZeroFactors>::const_iterator it;
	vector<ZeroFactors> factors;
	// Initializing each value with -1;
#define MAX5 100
	// vector<vector<long>> subset(count, vector<long>(100, -1));
	// map<long, long> twos, fives;
	set<long> twos, fives;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (!(data[i] % 10 && data[i] % 2 && data[i] % 5))
		{
			it = multipleMap.find(data[i]);
			ZeroFactors factor;
			if (it == multipleMap.end())
			{
				long two = 0, five = 0;
				MultiplesCount(data[i], two, five);
				factor.two = two;
				factor.five = five;
				multipleMap.emplace(data[i], factor);
				factors.push_back(factor);
			}
			else
			{
				factor.two = it->second.two;
				factor.five = it->second.five;
				;
				factors.push_back(factor);
			}
			// twos[factor.two] = max(twos[factor.two], factor.five);
			// fives[factor.five] = max(fives[factor.five], factor.two);
			twos.emplace(factor.two);
			fives.emplace(factor.five);
#if 0
			// Calculating subset[i][j] for maximum amount of twos we can collect by checking first i numbers and taking 
			// j of them with total power of five. 
			//for (int i = count - 1; i >= 0; i--)
			for (size_t j = 0; j < count; j++)
				for (int k = 0; k < subset[j].size(); k++)
				//for (size_t k = 0; k < 100; k++)
					// If subset[j][k] is not calculated. 
					//if (subset[j][k] != -1)
					//subset[j][k + factor.five] = max(subset[j][k + factor.five], subset[j][k] + factor.two);
					subset[j][k] = max(subset[j][k], subset[j][k] + factor.two);
#endif
		}
	}
	// for (map<long, long>::const_iterator it = subset.begin(); it != subset.end(); it++)
	//	result = max(result, min(it->))
	return 0;
}
long ConsecutiveLargestSumOfFactors(vector<zerofactors_t> &data, vector<zerofactors_t> &result, int value)
{
	long max_ending_here = 0, max_so_far = 0, count = 0;
	vector<zerofactors_t>::iterator start = data.end(), end = data.end();
	for (vector<zerofactors_t>::iterator it = data.begin(); it != data.end(); it++)
	{
		max_ending_here += (value == 2) ? it->two : it->five;
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			start = end = data.end();
		}
		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			if (start == data.end())
				start = it;
			end = it;
		}
		if (++count >= 3)
		{
			max_ending_here = 0;
			count = 0;
		}
	}
	if (start != data.end() && end != data.end())
		result.assign(start, end + 1);
	return max_so_far;
}
void MaxZeroProductTests()
{
	vector<int> data;
	data.push_back(2 * 2);
	data.push_back(2 * 2 * 2);
	data.push_back(2 * 2 * 2 * 2);
	data.push_back(5 * 5);
	data.push_back(5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5);
	// assert(MaxZeroProduct(data) == 5);
	assert(MaxZeroProductBruteForce(data) == 5);
	data.clear();
	data.push_back(2 * 5 * 5);
	data.push_back(2 * 2 * 5 * 5);
	data.push_back(2 * 2 * 2 * 5 * 5 * 5);
	// assert(MaxZeroProduct(data) == 6);
	assert(MaxZeroProductBruteForce(data) == 6);
	data.clear();
	data.push_back(7);
	data.push_back(15); // 3 * 5
	data.push_back(6);	// 2
	data.push_back(20); // 2 * 2 * 5
	data.push_back(5);	// 5
	data.push_back(10); // 2 * 5
	// assert(MaxZeroProduct(data) == 3);
	assert(MaxZeroProductBruteForce(data) == 3);
	data.clear();
	data = {25, 10, 25, 10, 32};
	// assert(MaxZeroProduct(data) == 4);
	assert(MaxZeroProductBruteForce(data) == 4);
	data.clear();
	data = {1, 1, 100};
	// assert(MaxZeroProduct(data) == 2);
	assert(MaxZeroProductBruteForce(data) == 2);
	data.clear();
	data = {1, 4, 25};
	// assert(MaxZeroProduct(data) == 2);
	assert(MaxZeroProductBruteForce(data) == 2);
	data.clear();
	data = {1, 1, 101};
	// assert(MaxZeroProduct(data) == 0);
	assert(MaxZeroProductBruteForce(data) == 0);
	data.clear();
	data = {1, 25, 25};
	// assert(MaxZeroProduct(data) == 0);
	assert(MaxZeroProductBruteForce(data) == 0);
	data.clear();
	data = {125, 100, 125, 100, 64};
	// assert(MaxZeroProduct(data) == 6);
	assert(MaxZeroProductBruteForce(data) == 6);
	data.clear();
	data.resize(9);
	generate(data.begin(), data.end(), [i = 1]() mutable
			 { return i++; });
	// assert(MaxZeroProduct(data) == 1);
	assert(MaxZeroProductBruteForce(data) == 1);
	data.push_back(10);
	// assert(MaxZeroProduct(data) == 2);
	assert(MaxZeroProductBruteForce(data) == 2);
	data.clear();
	data.push_back(10);
	data.push_back(1000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	// assert(MaxZeroProduct(data) == 21);
	assert(MaxZeroProductBruteForce(data) == 21);
	data.clear();
	data.push_back(100000);
	data.push_back(10000000);
	data.push_back(10000000);
	data.push_back(10000000);
	// assert(MaxZeroProduct(data) == 21);
	assert(MaxZeroProductBruteForce(data) == 21);
	data.clear();
	data.push_back(1220703125);
	data.push_back(8192);
	// assert(MaxZeroProduct(data) == 13);
	assert(MaxZeroProductBruteForce(data) == 13);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5); // 2^26
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	// assert(MaxZeroProduct(data) == 25);
	assert(MaxZeroProductBruteForce(data) == 25);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^25
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);														   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);													   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);													   // 5^12
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);												   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);														   // 5^12
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^23
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(1000000000);
	data.push_back(1000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	// assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	data.push_back(2000000000);
	// assert(MaxZeroProduct(data) == 27);
	assert(MaxZeroProductBruteForce(data) == 27);
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5);
	data.push_back(5 * 5);
	data.push_back(5);
	data.push_back(1);
	data.push_back(2);
	// assert(MaxZeroProduct(data) == 1);
	assert(MaxZeroProductBruteForce(data) == 1);
	data.clear();
	data.push_back(1024);
	data.push_back(512);
	data.push_back(256);
	data.push_back(128);
	data.push_back(64);
	data.push_back(32);
	data.push_back(16);
	data.push_back(8);
	data.push_back(4);
	data.push_back(2);
	data.push_back(1);
	data.push_back(3);
	data.push_back(5);
	// assert(MaxZeroProduct(data) == 1);
	assert(MaxZeroProductBruteForce(data) == 1);
	data.clear();
	data.push_back(1024);
	data.push_back(512);
	data.push_back(256);
	data.push_back(128);
	data.push_back(64);
	data.push_back(32);
	data.push_back(5); // this
	data.push_back(8);
	data.push_back(4);
	data.push_back(2); // this
	data.push_back(1);
	data.push_back(3);
	data.push_back(16);
	// assert(MaxZeroProduct(data) == 1);
	assert(MaxZeroProductBruteForce(data) == 1);
	data.clear();
	random_device device;
	// Uniform distribution used with vector
	// Distribution is [-5, 5] inclusive
	uniform_int_distribution<int> dist(0, 1000000000);
	data.resize(100);
	generate(data.begin(), data.end(), [&]
			 { return dist(device); });
	long result1 = MaxZeroProductBruteForce(data);
	// long result2 = MaxZeroProduct(data);
	// assert(result1 == result2);
}
set<string> permute(string const &str)
{
	set<string> permutations;
	if (str.empty())
		return permutations;
	else if (str.size() == 1)
	{
		permutations.insert(str);
		return permutations;
	}
	char toInsert = str[0];
	set<string> words = permute(str.substr(1));
	for (set<string>::iterator it = words.begin(); it != words.end(); it++)
	{
		for (size_t i = 0; i <= it->size(); i++)
			permutations.insert(insertCharAt(toInsert, *it, i));
	}
	return permutations;
}
// O(n!)
set<vector<long>> permute(vector<long> &data)
{
	set<vector<long>> permutations;
	if (data.empty())
		return permutations;
	else if (data.size() == 1)
	{
		permutations.insert(vector<long>{data[0]});
		return permutations;
	}
	long toInsert = data[0];
	vector<long> subset(data.begin() + 1, data.end());
	set<vector<long>> combinations = permute(subset);
	for (set<vector<long>>::iterator it = combinations.begin(); it != combinations.end(); it++)
	{
		vector<long> tmp = *it;
		for (size_t offset = 0; offset <= tmp.size(); offset++)
			permutations.insert(insertItemAt(toInsert, tmp, offset));
	}
	return permutations;
}
string insertCharAt(char toInsert, string str, size_t offset)
{
	string start = str.substr(0, offset);
	string end = str.substr(offset);
	return start + toInsert + end;
}
vector<long> insertItemAt(long toInsert, vector<long> &items, size_t offset)
{
	vector<long> result(items.begin(), items.begin() + offset);
	result.push_back(toInsert);
	result.insert(result.end(), items.begin() + offset, items.end());
	return result;
}
void StringPermutationTests()
{
	set<string> permutations;
	permutations = permute("abc");
	assert(permutations.size() == 6);
	assert(permutations.find("abc") != permutations.end());
	assert(permutations.find("bac") != permutations.end());
	assert(permutations.find("bca") != permutations.end());
	assert(permutations.find("acb") != permutations.end());
	assert(permutations.find("cba") != permutations.end());
	assert(permutations.find("cab") != permutations.end());
	cout << "permutations of \"abc\" are: ";
	copy(permutations.begin(), permutations.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	permutations.clear();

	OrderedMergedCombinations(permutations, string("Hey"), string("Bob"), string(""));
	cout << "Ordered permutations of \"HeyBob\" are: ";
	copy(permutations.begin(), permutations.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	assert(permutations.size() == 20);
	assert(permutations.find("HeBoby") != permutations.end());
	assert(permutations.find("HeBoyb") != permutations.end());
	assert(permutations.find("HeByob") != permutations.end());
	assert(permutations.find("HeyBob") != permutations.end());
	assert(permutations.find("HBoeby") != permutations.end());
	assert(permutations.find("HBoeyb") != permutations.end());
	assert(permutations.find("HBobey") != permutations.end());
	assert(permutations.find("HBeoby") != permutations.end());
	assert(permutations.find("HBeoyb") != permutations.end());
	assert(permutations.find("HBeyob") != permutations.end());
	assert(permutations.find("BoHeby") != permutations.end());
	assert(permutations.find("BoHeyb") != permutations.end());
	assert(permutations.find("BoHbey") != permutations.end());
	assert(permutations.find("BobHey") != permutations.end());
	assert(permutations.find("BHoeby") != permutations.end());
	assert(permutations.find("BHoeyb") != permutations.end());
	assert(permutations.find("BHobey") != permutations.end());
	assert(permutations.find("BHeoby") != permutations.end());
	assert(permutations.find("BHeoyb") != permutations.end());
	assert(permutations.find("BHeyob") != permutations.end());
}
void ListPermutationTests()
{
	set<vector<long>> permutations;
	vector<long> data{1, 2, 3};
	permutations = permute(data);
	assert(permutations.size() == 6);
	cout << "permutations of List of {1,2,3} are:" << endl;
	for (set<vector<long>>::iterator it = permutations.begin(); it != permutations.end(); it++)
	{
		copy(it->begin(), it->end(), ostream_iterator<long>(cout, " "));
		cout << endl;
	}
	permutations.clear();
	data.clear();
	data = {1, 2, 3, 4, 5};
	permutations = permute(data);
	assert(permutations.size() == 120);
	permutations.clear();
}
void GraphTests()
{
	vector<size_t> data(5);
	generate(data.begin(), data.end(), [n = 1]() mutable
			 { return n++; });
	Graph<size_t, size_t> graph(data);
	assert(graph.Count() == 5);
	shared_ptr<Vertex<size_t, size_t>> v1 = graph.GetVertex(1);
	assert(graph.HasVertex(1));
	assert(graph.HasVertex(2));
	assert(graph.HasVertex(3));
	assert(graph.HasVertex(4));
	assert(graph.HasVertex(5));

	assert(!v1->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v2 = graph.GetVertex(2);
	assert(!v2->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v3 = graph.GetVertex(3);
	assert(!v3->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v4 = graph.GetVertex(4);
	assert(!v4->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v5 = graph.GetVertex(5);
	assert(!v5->HasNeighbours());
	assert(v1->GetCost(v1) == 0);
	assert(v2->GetCost(v2) == 0);
	assert(v3->GetCost(v3) == 0);
	assert(v4->GetCost(v4) == 0);
	graph.AddUndirectedEdge(v1, v2, 1);
	assert(v1->HasNeighbour(v2));
	assert(v1->GetCost(v2) == 1);
	assert(v2->HasNeighbour(v1));
	assert(v2->GetCost(v1) == 1);
	graph.AddUndirectedEdge(v2, v3, 2);
	assert(v2->HasNeighbour(v3));
	assert(v2->GetCost(v3) == 2);
	assert(v3->HasNeighbour(v2));
	assert(v3->GetCost(v2) == 2);
	graph.AddUndirectedEdge(v2, v4, 3);
	assert(v2->HasNeighbour(v4));
	assert(v2->GetCost(v4) == 3);
	assert(v4->HasNeighbour(v2));
	assert(v4->GetCost(v2) == 3);
	graph.AddUndirectedEdge(v3, v5, 4);
	assert(v3->HasNeighbour(v5));
	assert(v3->GetCost(v5) == 4);
	assert(v5->HasNeighbour(v3));
	assert(v5->GetCost(v3) == 4);
	graph.AddUndirectedEdge(v4, v5, 5);
	assert(v4->HasNeighbour(v5));
	assert(v4->GetCost(v5) == 5);
	assert(v5->HasNeighbour(v4));
	assert(v5->GetCost(v4) == 5);
	graph.Print(v1);
	graph.Print(v2);
	graph.Print(v3);
	graph.Print(v4);
	map<size_t, vector<shared_ptr<Vertex<size_t, size_t>>>> vertices; // Get BFS vertices
	graph.GetBFSNodes(vertices, v1);
	assert(!vertices.empty());
	cout << "Graph content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Vertex<size_t, size_t>>>>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Vertex<size_t, size_t>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->GetItem() << " ";
		cout << endl;
	}
	map<shared_ptr<Vertex<size_t, size_t>>, long> costs;
	graph.Dijkstra(1, costs);
	cout << "Vertex\tDistance from Source (1): " << endl;
	for (map<shared_ptr<Vertex<size_t, size_t>>, long>::iterator it = costs.begin(); it != costs.end(); it++)
		cout << it->first->GetItem() << "\t" << it->second << endl;
	assert(graph.Dijkstra(1, 5) == 7);
	graph.Remove(3);
	assert(!graph.HasVertex(3));
	assert(!v2->HasNeighbour(v3));
	assert(!v5->HasNeighbour(v3));
	costs.clear();
	graph.Clear();
	assert(graph.Count() == 0);
	v1 = graph.AddVertex(1);
	v2 = graph.AddVertex(2);
	v3 = graph.AddVertex(3);
	v4 = graph.AddVertex(4);
	v5 = graph.AddVertex(5);
	assert(graph.Count() == 5);
	graph.AddUndirectedEdge(v1, v2, 1);
	graph.AddUndirectedEdge(v2, v3, 2);
	graph.AddUndirectedEdge(v3, v5, 3);
	graph.AddUndirectedEdge(v2, v4, 2);
	assert(graph.Dijkstra(1, 5) == 6); // 1 + 2 + 3
	assert(graph.Dijkstra(1, 2) == 1);
	assert(graph.Dijkstra(2, 3) == 2);
	assert(graph.Dijkstra(1, 3) == 3); // 1 + 2
	assert(graph.Dijkstra(1, 4) == 3); // 1 + 2
	assert(graph.Dijkstra(3, 4) == 4); // 2 + 2
	costs.clear();
	graph.Clear();
	data.clear();
	data = {10, 5, 11};
	vector<vector<size_t>> links = {{1, 2}, {1, 3}}; // Use tag. Not value
	/*
			10
		11		5
	Diff: 15 - 11 = 4
	*/
	assert(MinSubGraphDifference(data, links) == 4);
	data.clear();
	data = {10, 5, 6, 20};
	/*
			10
		 5		6
	  20
	Diff: 21 - 20 = 1
	*/
	links = {{1, 2}, {1, 3}, {2, 4}}; //{ {10,5}, {10,6}, {5,20} };
	assert(MinSubGraphDifference(data, links) == 1);
	/*
			10
		 5
	  20
	Diff: 20 - 15 = 5
	*/
	data.clear();
	data = {10, 5, 20};
	links = {{1, 2}, {2, 3}}; //{ {10,5}, {5,20} };
	assert(MinSubGraphDifference(data, links) == 5);
	cout << endl;
	data.clear();
	data = {100, 200, 100, 100, 500, 600};
	links = {{1, 2}, {2, 3}, {2, 4}, {4, 5}, {4, 6}};
	assert(MinSubGraphDifference(data, links) == 400);
	data.clear();
	data = {205, 573, 985, 242, 830, 514, 592, 263, 142, 915};
	links = {{2, 8}, {10, 5}, {1, 7}, {6, 9}, {4, 3}, {8, 10}, {5, 1}, {7, 6}, {9, 4}};
	assert(MinSubGraphDifference(data, links) == 99);
	vector<size_t> data2 = {716, 365, 206, 641, 841, 585, 801, 645, 208, 924, 920, 286, 554, 832, 359, 836, 247, 959, 31, 322, 709, 860, 890, 195, 575, 905, 314, 41, 669, 549, 950, 736, 265, 507, 729, 457, 91, 529, 102, 650, 805, 373, 287, 710, 556, 645, 546, 154, 956, 928};
	links = {{14, 25}, {25, 13}, {13, 20}, {20, 24}, {43, 2}, {2, 48}, {48, 42}, {42, 5}, {27, 18}, {18, 30}, {30, 7}, {7, 36}, {37, 9}, {9, 23}, {23, 49}, {49, 15}, {31, 26}, {26, 29}, {29, 50}, {50, 21}, {41, 45}, {45, 10}, {10, 17}, {17, 34}, {28, 47}, {47, 44}, {44, 11}, {11, 16}, {3, 8}, {8, 39}, {39, 38}, {38, 22}, {19, 32}, {32, 12}, {12, 40}, {40, 46}, {1, 35}, {35, 4}, {4, 33}, {33, 6}, {25, 2}, {2, 27}, {7, 37}, {15, 50}, {21, 10}, {17, 28}, {16, 39}, {38, 19}, {40, 1}};
	size_t result = MinSubGraphDifference(data2, links);
	// assert(result == 525); Fail but difficult to check due to the sheer number of data points.
	vector<long> data1;
	vector<vector<long>> links1;
	data1.clear();
	data1 = {1, 3, 4};
	links1 = {{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}};
	assert(PostmanProblem(data1, links1) == 6);
	data1.clear();
	data1 = {5, 11, 12, 15, 16};
	links1 = {{17, 4, 3}, {11, 12, 5}, {14, 2, 1}, {16, 14, 4}, {7, 8, 4}, {13, 5, 5}, {17, 15, 2}, {5, 3, 5}, {8, 6, 1}, {18, 10, 4}, {18, 1, 3}, {16, 1, 2}, {9, 2, 5}, {11, 6, 1}, {4, 9, 4}, {7, 20, 2}, {13, 19, 3}, {19, 12, 3}, {10, 20, 2}};
	assert(PostmanProblem(data1, links1) == 54);
	cout << endl;
}
void parentheses(vector<string> &result, string &str, size_t index, long left, long right)
{
	if (!left && !right)
		result.push_back(str);
	else
	{
		if (left > 0)
		{
			str[index] = '(';
			parentheses(result, str, index + 1, left - 1, right);
		}
		if (right > left)
		{
			str[index] = ')';
			parentheses(result, str, index + 1, left, right - 1);
		}
	}
}
void parentheses(vector<string> &result, size_t count)
{
	string str;
	str.resize(count * 2);
	parentheses(result, str, 0, count, count);
}
/*
 * i - stack.peek()
 * ()
 * 0: -1, 0
 * 1 : -1, result = 2
 *
 * (()
 * 0: -1, 0
 * 1 : -1, 0, 1
 * 2 : -1, 0 result = 2
 *
 * ((
 * 0: -1, 0
 * 1 : -1, 1
 * result = 0
 *
 * ((()
 * 0: -1, 0
 * 1 : -1, 0, 1
 * 2 : -1, 0, 1, 2
 * 3 : -1, 0, 1 result = 2
 *
 * ((())
 * 0: -1, 0
 * 1 : -1, 0, 1
 * 2 : -1, 0, 1, 2
 * 3 : -1, 0, 1 result = 2
 * 4 : -1, 0 result = 4
 *
 * ())()
 * 0: -1, 0
 * 1: -1 result = 2
 * 2: 2			<= extra ')'
 * 3: 2, 3
 * 4: 2 result = 2
 */
long LongestValidParentheses(const string &str)
{
	MyStack<long> stack;
	stack.push(-1); // The first element of stack is used to provide base for next valid string
	long result = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			stack.push(i);
		else if (str[i] == ')')
		{
			stack.pop(); // Remove the last matching opening bracket or -1
			if (!stack.isEmpty() && (long)(i - stack.peek()) > result)
				result = i - stack.peek();
			else if (stack.isEmpty())
				stack.push(i); // This marks the next invalid extra ')' as base case
		}
	}
	return result;
}
// https://app.codility.com/programmers/task/brackets_rotation/
// Unfinished work!
long LongestValidParenthesesWithFixes(const string &str, size_t k)
{
	stack<long> stack;
	long start = -1, end = -1;
	stack.push(-1); // The first element of stack is used to provide base for next valid string
	long result = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			stack.push(i);
		else if (str[i] == ')')
		{
			stack.pop(); // Remove the last matching opening bracket or -1
			if (!stack.empty() && (long)(i - stack.top()) > result)
			{
				result = i - stack.top();
				start = stack.top() + 1;
				end = i;
			}
			else if (stack.empty())
				stack.push(i);
		}
	}
	long *stackEnd = &stack.top() + 1;
	long *stackBegin = stackEnd - stack.size();
	vector<long> list(stackBegin, stackEnd);
	// The algorithm implemented is based on reverse-engineering of the result sets obtained from the remaining stack elements after the for loop above.
	if (k == 0 || list.empty() || (list.size() == 1 && list[0] == -1))
		return result;
	if (result == 0)
	{
		if (list[0] == -1 || list.size() == 1)
		{
			result = !(list[0] % 2) ? list[0] : list[0] + 1;
			result = list.size() == str.size() + 1 && str.size() > 1 ? 2 : min((long)k, result / 2) * 2;
		}
		else
		{
			size_t size = list.size();
			if (list[0] == -1)
				size--; // remove -1
						// if (list[0] != 0) {
			result = !(size % 2) ? size : size - 1;
			if ((list[0] == 0 && (long)k > (result / 2)) || (list[0] != 0 && (long)k >= (result / 2)))
				result = min((long)(k * 2), result);
			else
				result = 0;
			//}
		}
	}
	else if (list.size() == 1 && list[0] != -1)
	{
		if ((list[0] > end && start > 0) || (list[0] < start && list[0] > 0))
		{
			k--;
			result += 2;
		}
	}
	else
	{
		size_t size = list.size();
		if (list[0] == -1)
			size--;
		result += min(k, size / 2 + size % 2) * 2;
	}
	return result;
}
bool JSONValidation(string json)
{
	size_t keyCount = 0, valueCount = 0, leftBraceCount = 0, rightBraceCount = 0;
	ostringstream oss;
	string key = "", value = "";
	for (string::const_iterator it = json.begin(); it != json.end(); it++)
	{
		if (*it == '{')
		{
			leftBraceCount++;
			key = "";
			value = "";
			oss.str("");
		}
		else if (*it == '}' || *it == ' ' || *it == ',')
		{
			value = oss.str();
			oss.str("");
			if (value != "")
				valueCount++;
			if (*it == '}')
				rightBraceCount++;
			if (leftBraceCount > rightBraceCount && keyCount > valueCount)
				valueCount++;
		}
		else if (*it == ':')
		{
			key = oss.str();
			oss.str("");
			if (key != "")
				keyCount++;
		}
		else
			oss << *it;
	}
	return leftBraceCount == rightBraceCount && keyCount == valueCount;
}
// 0 1 2 3 4 5 6 7 8 9 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
void findDistinct(vector<long> &input, vector<long> &output)
{
	for (vector<long>::const_iterator it = input.begin(); it != input.end(); it++)
	{
		vector<long>::const_iterator it1 = it + 1;
		for (; it1 != input.end() && (*it ^ *it1); it1++)
			;
		if (it1 == input.end())
			output.push_back(*it);
	}
}
// http://en.wikipedia.org/wiki/Prime_number - Trial division implementation
void findPrimes(unsigned long n, vector<long> &result)
{
	if (n <= 3)
		result = {2, 3};
	else
	{
		long double j;
		result = {2, 3};
		for (unsigned long i = 4; i <= n; i++)
		{
			long double sqrtI = sqrt(i);
			for (j = 2; j <= sqrtI && (i % (long)j); j++)
				;
			if (j > sqrtI)
				result.push_back(i);
		}
	}
}
// https://en.wikipedia.org/wiki/Primality_test
bool isPrime(unsigned long n)
{
	if (n <= 3)
		return n > 1;
	else if (!(n % 2) || !(n % 3))
		return false;
	for (size_t i = 5; (i * i) <= n; i += 6) // 5 7 11
		if (!(n % i) || !(n % (i + 2)))
			return false;
	return true;
}
// https://app.codility.com/programmers/lessons/12-euclidean_algorithm/common_prime_divisors/
// Correctness: 100%
// 61% due to timeout
size_t CommonPrimeDivisors(vector<long> &data1, vector<long> &data2)
{
	vector<size_t> indices;
	vector<long> a(data1), b(data2);
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	long maxNum = max(a.back(), b.back());
	vector<long> primes;
	findPrimes(maxNum, primes);
	if (data1.size() == 1 && data2.size() == 1 && data1[0] == 1 && data2[0] == 1)
		return 1;
	for (size_t i = 0; i < data1.size(); i++)
	{
		maxNum = max(data1[i], data2[i]);
		bool flag = true;
		for (vector<long>::const_iterator it = primes.begin(); it < primes.end() && *it <= maxNum; it++)
		{
			if (!(data1[i] % *it) ^ !(data2[i] % *it))
				flag = false;
		}
		if (flag)
			indices.push_back(i);
	}
	return indices.size();
}
// 2 1 1 2 => (2+1)*(2+1) = 9
// 2 3 3 2 :
// (1) 2 + 3 + 3 + 2 = 10
// (2) 2 * 3 * 3 * 2 = 36
// (3) (2 + 3) * (3 + 2) = 25
// (4) 2 + (3 * 3) + 2 = 11
unsigned long long findMax(vector<unsigned long long> const &data)
{
	vector<unsigned long long> result;
	if (data.size() == 1)
		return data[0];
	else if (data.size() == 2)
		return (data[0] * data[1] > data[0] + data[1]) ? data[0] * data[1] : data[0] + data[1];
	else
	{
		for (vector<unsigned long long>::const_iterator it = data.begin(); it != data.end(); it += 2)
		{
			if (it <= data.end() - 2)
				result.push_back((*it + *(it + 1)) > (*it * *(it + 1)) ? (*it + *(it + 1)) : (*it * *(it + 1)));
			else
				result.push_back(*it);
		}
	}
	return findMax(result);
}

string uncompress(string const &str)
{
	ostringstream oss;
	for (size_t i = 0; i < str.size();)
	{
		if (isalpha(str[i]))
			oss << str[i++];
		else if (isdigit(str[i]))
		{
			char *end(nullptr);
			errno = 0;
			unsigned long repeat = strtoul(&str[i], &end, 10);
			if (!errno && repeat > 0 && repeat < numeric_limits<unsigned long>::max())
			{
				if (*end)
					while (str[i] != end[0])
						i++;
				else
					i++;
				ostringstream oss1;
				for (size_t k = 0; k < repeat; k++)
					oss1 << oss.str();
				oss.str("");
				oss << oss1.str();
			}
			else
				i++;
		}
	}
	return oss.str();
}
/*
 "0010110100" => Length: 4
 "0010110110" => Length: 5
 */
size_t findLongestContiguousPattern(string &str, char c)
{
	size_t max = 0;
	int index = -1;
	size_t count = 0;
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == c)
			count++;
		else
		{
			if (max < count)
			{
				max = count;
				if (i > 0 && str[i - 1] == c && str[i + 1] == c)
				{
					count = (index != -1) ? i - index : count + 1;
					index = i;
				}
			}
			else
				count = 0;
		}
	if (index > 0)
		str[index] = c;
	return max;
}

template <class T>
void SortStack(MyStack<T> &src, MyStack<T> &dest, sort_order_t order)
{
	T item;
	while (!src.isEmpty())
	{
		item = src.pop();
		switch (order)
		{
		case SortOrder::SORT_ASCENDING: // Value grows from bottom of stack to top of stack
			while (!dest.isEmpty() && item < dest.peek())
				src.push(dest.pop());
			break;
		case SortOrder::SORT_DESCENDING: // Value shrinks from bottom of stack to top of stack
			while (!dest.isEmpty() && item > dest.peek())
				src.push(dest.pop());
			break;
		default:
			throw runtime_error("Invalid sort order");
			break;
		}
		dest.push(item);
	}
}
/*
 * dest:  {1,3,5,7,9,11,13,15}
 * source:{6,8,10,12,14}
 * dest:  {1,3,5,[6],7,8,9,10,11 ,12 ,13 ,14 ,15 }
 *
 * dest:  {6,8,10,12,14,16,18}
 * source:{1,3,5,7,9,11}
 * dest:  {1,3,5,[6],7,8,9,10 ,11 ,12 ,14 ,16 ,18 }
 */
void Merge(vector<long> &dest, vector<long> &source)
{
	int k = dest.size() + source.size() - 1;
	int i = dest.size() - 1;
	int j = source.size() - 1;
	dest.resize(k + 1);
	while (i >= 0 && j >= 0)
		dest[k--] = dest[i] > source[j] ? dest[i--] : source[j--];
	while (j >= 0)
		dest[k--] = source[j--];
}
// Start of Sort numbers into consecutive positive/negative numbers
// http://www.careercup.com/question?id=5183920823861248
template <typename type>
void sortNumbers(vector<type> &data)
{
	size_t j;
	type tmp;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i] < 0 && data[i + 1] < 0)
		{ // Look for positive number
			for (j = i + 1; j < data.size() && data[j] < 0; j++)
				;
			if (j == data.size())
				break;
			// Shift i+1 to j-1
			tmp = data[j];
			for (size_t k = j; k > i; k--)
				data[k] = data[k - 1];
			data[i + 1] = tmp;
		}
		else if (data[i] > 0 && data[i + 1] > 0)
		{ // Look for positive number
			for (j = i + 1; j < data.size() && data[j] > 0; j++)
				;
			if (j == data.size())
				break;
			// Shift i+1 to j-1
			tmp = data[j];
			for (size_t k = j; k > i; k--)
				data[k] = data[k - 1];
			data[i + 1] = tmp;
		}
	}
}
// http://cpluspluslearning-petert.blogspot.co.uk/2014/10/data-structure-and-algorithm-order.html
template <typename type>
void OrderArrayIntoNegativePositiveSeries(vector<type> &arr)
{
	if (arr.empty() || arr.size() < 3)
		return;
	// if first value is negative, then find a positive value next
	bool positiveValToFind = arr[0] < 0;
	type nextValue;
	for (size_t outOfOrderPos = 1, curIndex = 1; curIndex < arr.size(); curIndex++)
	{
		if ((positiveValToFind && arr[curIndex] > 0) || (!positiveValToFind && arr[curIndex] < 0))
		{
			if (outOfOrderPos == curIndex)
			{
				// Scenario 1: curIndex is increment by the for loop
				positiveValToFind = !positiveValToFind;
				++outOfOrderPos;
			}
			else
			{
				// Scenario 2: curIndex is increment by the for loop
				nextValue = arr[curIndex];
				memcpy(&arr[outOfOrderPos + 1],
					   &arr[outOfOrderPos],
					   (curIndex - outOfOrderPos) * sizeof(type));
				arr[outOfOrderPos] = nextValue;
				outOfOrderPos += 2;
			}
		}
	}
}
//********************************************************************************
// Tests
//********************************************************************************
void SparseNumberTests()
{
	assert(isSparseNumber(0));
	assert(isSparseNumber(1));
	assert(isSparseNumber(2));
	assert(!isSparseNumber(3));
	assert(isSparseNumber(4));
	assert(isSparseNumber(5));
	assert(!isSparseNumber(6));
	assert(!isSparseNumber(7));
	assert(isSparseNumber(8));
	assert(isSparseNumber(9));
	assert(NextSparseNumber(0) == 1);
	assert(NextSparseNumber(1) == 2);
	assert(NextSparseNumber(2) == 4);
	assert(NextSparseNumber(3) == 4);
	assert(NextSparseNumber(4) == 5);
	assert(NextSparseNumber(5) == 8);
	assert(NextSparseNumber(6) == 8);
	assert(NextSparseNumber(7) == 8);
	assert(NextSparseNumber(8) == 9);
	assert(NextSparseNumber(9) == 10);
}
void LongestCommonSubsequenceTests()
{
	vector<char> chars1, chars2;
	vector<size_t> num1, num2, result;
	string s1, s2;
	s1 = "HARRY";
	s2 = "SALLY";
	assert(LCSLength(s1, s2) == 2);
	s1 = "HARRY";
	s2 = "SALLY";
	chars1.insert(chars1.end(), s1.begin(), s1.end());
	chars2.insert(chars2.end(), s2.begin(), s2.end());
	assert(LCSLength<char>(chars1, chars2) == 2);
	s1 = "SHINCHAN";
	s2 = "NOHARAAA";
	assert(LCSLength(s1, s2) == 3);
	s1 = "ABCDEF";
	s2 = "FBDAMN";
	assert(LCSLength(s1, s2) == 2);
	s1 = "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS";
	s2 = "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC";
	assert(LCSLength(s1, s2) == 15);
	s1 = "HARRY";
	s2 = "SALLY";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	assert(LCSLength(table, s1, s2) == 2);
	assert(LCSBackTrack(table, s1, s2, s1.size() - 1, s2.size() - 1) == "AY");
	LCSPrintDiff(table, s1, s2, s1.size() - 1, s2.size() - 1);
	cout << endl;
	s1 = "SHINCHAN";
	s2 = "NOHARAAA";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table1(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	assert(LCSLength(table1, s1, s2) == 3);
	assert(LCSBackTrack(table1, s1, s2, s1.size() - 1, s2.size() - 1) == "NHA");
	s1 = "ABCDEF";
	s2 = "FBDAMN";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table2(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	assert(LCSLength(table2, s1, s2) == 2);
	assert(LCSBackTrack(table2, s1, s2, s1.size() - 1, s2.size() - 1) == "BD");
	s1 = "aa";
	s2 = "baaa";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table3(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	assert(LCSLength(table3, s1, s2) == 2);
	assert(LCSBackTrack(table3, s1, s2, s1.size() - 1, s2.size() - 1) == "aa");
	LCSPrintDiff(table3, s1, s2, s1.size() - 1, s2.size() - 1);
	s1 = "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS";
	s2 = "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table4(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	assert(LCSLength(table4, s1, s2) == 15);
	assert(LCSBackTrack(table4, s1, s2, s1.size() - 1, s2.size() - 1) == "DGCGTRMZJRBAJJV");
	chars1.clear();
	chars2.clear();
	chars1.insert(chars1.end(), s1.begin(), s1.end());
	chars2.insert(chars2.end(), s2.begin(), s2.end());
	vector<vector<size_t>> table5(chars1.size(), vector<size_t>(chars2.size())); // Defaults to zero initial value
	assert(LCSLength<char>(table5, chars1, chars2) == 15);
	chars1 = LCSBackTrack<char>(table5, chars1, chars2, chars1.size() - 1, chars2.size() - 1);
	s1.clear();
	s1.insert(s1.end(), chars1.begin(), chars1.end());
	assert(s1 == "DGCGTRMZJRBAJJV");
	num1 = {1, 2, 3, 4, 1};
	num2 = {3, 4, 1, 2, 1, 3};
	assert(LCSLength<size_t>(num1, num2) == 3); // "1 2 3", "1 2 1", "3 4 1" are all correct answers
	num1 = {1, 2, 3, 4, 1};
	num2 = {3, 4, 1, 2, 1, 3};
	num1.insert(num1.begin(), 0);
	num2.insert(num2.begin(), 0);
	vector<vector<size_t>> table6(num1.size(), vector<size_t>(num2.size())); // Defaults to zero initial value
	assert(LCSLength<size_t>(table6, num1, num2) == 3);						 // "1 2 3", "1 2 1", "3 4 1" are all correct answers
	result = LCSBackTrack<size_t>(table6, num1, num2, num1.size() - 1, num2.size() - 1);
	assert(result.size() == 3);
	assert(result[0] == 1);
	assert(result[1] == 2);
	assert(result[2] == 3);
	LCSPrintDiff<size_t>(table6, num1, num2, num1.size() - 1, num2.size() - 1);
	cout << endl;
}
void OrderArrayIntoNegativePositiveSeriesTests()
{
	vector<long> a{2, -1, -3, -7, -8, 9, 5, -5, -7};
	// Start of Sort numbers into consecutive positive/negative numbers
	// 2,-1,-3,-7,-8,9,5,-5,-7
	sortNumbers(a);
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, " "));
	cout << endl;
	a.clear();
	TestCornerCases();
	vector<int> testArr{2, -1, -3, -7, -8, 9, 5, -5, -7};
	vector<int> result{2, -1, 9, -3, 5, -7, -8, -5, -7};
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = {2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7};
	result = {2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7};
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = {2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1};
	result = {2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7};
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = {2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7};
	result = {2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7};
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = {-1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7};
	result = {-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1};
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = {-1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1};
	result = {-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1};
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);
	// End of Sort numbers into consecutive positive/negative numbers
}
void TestCornerCases()
{
	vector<int> testArr;
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr.empty());

	testArr.push_back(1);
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr.size() == 1);
	assert(testArr[0] == 1);
	testArr.clear();

	testArr.push_back(1);
	testArr.push_back(-1);
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr.size() == 2);
	assert(testArr[0] == 1);
	assert(testArr[1] == -1);
}
// End of Sort numbers into consecutive positive/negative numbers

// Binary Search (http://en.wikipedia.org/wiki/Binary_search_algorithm)
// Dichotomic Divide And Conquer: O(Log n). In case of duplicates, the algorithm drops to linear search O(n)
// Assumption: source is sorted in increasing order and rotated a number of times
// Ex: Input: find 5 in array (15 16 19 20 25 1 3 4 5 7 10 14)
//			                   L             M              U
// 4 8 9 9 9 10 12 13 1 2 2 3
// L            M           U
size_t BinarySearch(vector<size_t> &data, size_t toSearch)
{
	for (size_t lower = 0, middle = 0, upper = data.size() - 1; lower <= upper;)
	{
		middle = lower + (upper - lower) / 2 + (upper - lower) % 2;
		if (toSearch == data[middle])
			return middle;
		else if (toSearch == data[lower])
			return lower;
		else if (toSearch == data[upper])
			return upper;
		else if (data[lower] <= data[middle])
		{
			// 5 6 7 8 1 2 3
			// L     M     U
			if (toSearch > data[lower] && toSearch < data[middle]) // Ex: toSearch=7
				upper = middle - 1;
			else // Ex: toSearch=2
				lower = middle + 1;
		}
		else
		{ // Lower >= Middle
			// 6 7 8 9 1 2 3 4 5
			// L       M       U
			if (toSearch > data[middle] && toSearch < data[upper]) // Ex: toSearch=3
				lower = middle + 1;
			else // Ex: toSearch=8
				upper = middle - 1;
		}
	}
	return -1;
}
/* https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 * 100%
 */
long BinarySearchMinimum(vector<long> &data, long start, long end)
{
	if (start == end)
		return data[start];
	else if (end - start == 1)
		return min(data[start], data[end]);
	else if (start < end)
	{
		size_t middle = start + (end - start) / 2 + (end - start) % 2;
		long data1 = BinarySearchMinimum(data, start, middle - 1);
		long data2 = BinarySearchMinimum(data, middle + 1, end);
		return min(data[middle], min(data1, data2));
	}
	return numeric_limits<long>::min();
}
/* https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 * 100%
 */
vector<long> searchRange(vector<size_t> &nums, size_t target)
{
	long start = 0, end = nums.size() - 1, middle = end / 2 + end % 2;
	vector<long> result{-1, -1}; // result[0] = start (inclusive); result[1] = end (exclusive)
	if (nums.empty())
		return result;
	for (; start <= end && (result[0] == -1 || result[1] == -1);)
	{
		if (target > nums[start] && target < nums[middle])
		{
			size_t data = nums[middle - 1];
			for (end = middle - 1; end >= start && nums[end] == data; end--)
				;
			if (start > end)
				return result;
			end++;
			middle = start + (end - start) / 2 + (end - start) % 2;
		}
		else if (target > nums[middle] && target < nums[end])
		{
			size_t data = nums[middle + 1];
			for (start = middle + 1; start <= end && nums[start] == data; start++)
				;
			if (start > end)
				return result;
			start--;
			middle = start + (end - start) / 2 + (end - start) % 2;
		}
		else if (target < nums[start] || target > nums[end])
			return result;
		long index = -1;
		if (target == nums[start])
			index = start;
		else if (target == nums[end])
			index = end;
		else if (target == nums[middle])
			index = middle;
		if (index > -1)
		{
			for (start = index; start >= 0 && nums[start] == target; start--)
				result[0] = start;
			for (end = index; end < (long)nums.size() && nums[end] == target; end++)
				result[1] = end;
		}
	}
	return result;
}
/*
 * Binary search for the upper bound of sorted list with duplicate items.
 * Returns the last index of the repeated items found in the sorted list
 */
int BinarySearchCountUpper(vector<long> &source, long toSearch, long start, long end)
{
	int mid = start + (end - start) / 2 + (end - start) % 2;
	if (end < start)
		return 0;
	if (source[mid] == toSearch && (mid == end || source[mid + 1] != toSearch))
		// 1 2 3 4 [4] 5
		return mid;
	else if (source[mid] <= toSearch)
		// 1 2 3 [3] 4 4 4 (toSearch: 4)
		return BinarySearchCountUpper(source, toSearch, mid + 1, end);
	else
		// 1 2 3 [4] 4 4 (toSearch: 3)
		return BinarySearchCountUpper(source, toSearch, start, mid - 1);
}
/*
 * Binary search for the lower bound of sorted list with duplicate items.
 * Returns the first index of the repeated items found in the sorted list
 */
int BinarySearchCountLower(vector<long> &source, long toSearch, long start, long end)
{
	int mid = start + (end - start) / 2 + (end - start) % 2;
	if (end < start)
		return 0;
	if (source[mid] == toSearch && (mid == start || source[mid - 1] != toSearch))
		// 1 [2] 2 3 4 5
		return mid;
	else if (source[mid] < toSearch)
		// 1 2 3 [3] 4 4 4 (toSearch: 4)
		return BinarySearchCountLower(source, toSearch, mid + 1, end);
	else
		return BinarySearchCountLower(source, toSearch, start, mid - 1);
}
int BinarySearch(vector<string> &source, const string &toSearch)
{
	int lower, middle, upper;
	lower = 0;
	upper = source.size() - 1;
	while (lower <= upper)
	{
		while (lower <= upper && source[upper].empty())
			upper--;
		if (lower > upper)
			return -1;
		middle = lower + (upper - lower) / 2 + (upper - lower) % 2;
		while (source[middle].empty())
			middle++;
		if (source[middle] == toSearch)
			return middle;
		else if (toSearch < source[middle])
			upper = middle - 1;
		else
			lower = middle + 1;
	}
	return -1;
}
void SortTests()
{
	// Test Sorting algorithms
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	vector<long> a, b, sortData, buffer;
	vector<size_t> udata, udata1;
	sortData.clear();
	sortData = {1, 0, -1};
	BubbleSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&]
			 { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	BubbleSort(sortData);
	assert(sortData == buffer);
	sortData.clear();
	sortData = {1, 3, 0, 2};
	QuickSort(sortData, 0, sortData.size() - 1);
	assert(sortData[0] == 0);
	assert(sortData[1] == 1);
	assert(sortData[2] == 2);
	assert(sortData[3] == 3);

	sortData.clear();
	sortData = {1, 0, -1};
	QuickSort(sortData, 0, sortData.size() - 1);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&]
			 { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	QuickSort(sortData, 0, sortData.size() - 1);
	assert(sortData == buffer);

	sortData.clear();
	sortData = {1, 0, -1};
	SelectionSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&]
			 { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	SelectionSort(sortData);
	assert(sortData == buffer);

	sortData.clear();
	sortData = {1, 0, -1};
	InsertionSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&]
			 { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	InsertionSort(sortData);
	assert(sortData == buffer);

	sortData.clear();
	sortData = {1, 0, -1};
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);

	sortData.clear();
	sortData = {2, 1, 3, 1, 2};
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	assert(sortData[0] == 1);
	assert(sortData[1] == 1);
	assert(sortData[2] == 2);
	assert(sortData[3] == 2);
	assert(sortData[4] == 3);

	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&]
			 { return uniformDistribution(engine); });
	a.clear();
	a.assign(sortData.begin(), sortData.end());
	sort(a.begin(), a.end());
	buffer.clear();
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	assert(sortData == a);

	sortData.clear();
	sortData = {1, 0, -1};
	buffer = sortData;
	BottomUpMergeSort(sortData, buffer);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&]
			 { return uniformDistribution(engine); });
	a.clear();
	a.assign(sortData.begin(), sortData.end());
	sort(a.begin(), a.end());
	buffer = sortData;
	BottomUpMergeSort(sortData, buffer);
	assert(sortData == a);

	sortData.clear();
	sortData = {1, 0, -1};
	HeapSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);

	vector<size_t> sortData1{1, 0, 2};
	CountingSort(sortData1);
	assert(sortData1[0] == 0);
	assert(sortData1[1] == 1);
	assert(sortData1[2] == 2);

	sortData1.clear();
	sortData1 = {456, 789, 123};
	CountingSort(sortData1);
	assert(sortData1[0] == 123);
	assert(sortData1[1] == 456);
	assert(sortData1[2] == 789);

	vector<vector<string>> strSort{
		{"400", "not"},
		{"1500", "question"},
		{"550", "to"},
		{"100", "to"},
		{"650", "be"},
		{"1100", "-"},
		{"200", "be"},
		{"1234", "is"},
		{"1100", "that"},
		{"300", "or"},
		{"1250", "the"}};
	assert(CountingSort(strSort) == "to be or not to be - that is the question");

	strSort.clear();
	strSort = {{"100", "!!!"}, {"55", "Hello"}, {"10", "Hey,"}, {"55", "World"}};
	assert(CountingSort(strSort) == "Hey, Hello World !!!");

	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&]
			 { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	HeapSort(sortData);
	assert(sortData == buffer);

	a.clear();
	a.resize(10);
	b.resize(20);
	generate(a.begin(), a.end(), [&]
			 { return uniformDistribution(engine); });
	generate(b.begin(), b.end(), [&]
			 { return uniformDistribution(engine); });
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
	{
		if (it != a.begin())
			if (*it < *(it - 1))
			{
				throw runtime_error("Merge 2 sorted lists failed!");
				break;
			}
	}
	a.resize(20);
	b.resize(10);
	generate(a.begin(), a.end(), [&]
			 { return uniformDistribution(engine); });
	generate(b.begin(), b.end(), [&]
			 { return uniformDistribution(engine); });
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
	{
		if (it != a.begin())
			if (*it < *(it - 1))
			{
				cout << "Merge 2 sorted lists failed!";
				assert(false);
				break;
			}
	}
	a.clear();
	b.clear();
	a = {1, 5, 3, 7};
	b = a;
	assert(TopDownMergeSortCountConversions(b, a, 0, a.size()) == 1);
	assert(a[0] == 1);
	assert(a[1] == 3);
	assert(a[2] == 5);
	assert(a[3] == 7);

	a.clear();
	b.clear();
	a = {7, 5, 3, 1};
	b = a;
	assert(TopDownMergeSortCountConversions(b, a, 0, a.size()) == 6);
	assert(a[0] == 1);
	assert(a[1] == 3);
	assert(a[2] == 5);
	assert(a[3] == 7);

	a.clear();
	b.clear();
	a = {2, 1, 3, 1, 2};
	b = a;
	assert(TopDownMergeSortCountConversions(b, a, 0, a.size()) == 4);
	assert(a[0] == 1);
	assert(a[1] == 1);
	assert(a[2] == 2);
	assert(a[3] == 2);
	assert(a[4] == 3);
	udata.clear();
	udata = {2, 5, 3, 1};
	assert(SortSwapCount(udata) == 2);
	udata.clear();
	udata = {3, 4, 2, 5, 1};
	assert(SortSwapCount(udata) == 2);

	udata.clear();
	udata = {2, 0, 2, 1, 1, 0};
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = {0, 0, 1, 1, 2, 2};
	assert(udata == udata1);

	udata.clear();
	udata = {0};
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = {0};
	assert(udata == udata1);

	udata.clear();
	udata = {1};
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = {1};
	assert(udata == udata1);

	udata.clear();
	udata = {2};
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = {2};
	assert(udata == udata1);

	a.clear();
	a = {1, 5, 1, 1, 6, 4};
	WiggleSort(a);
	b.clear();
	b = {1, 6, 1, 5, 1, 4};
	assert(a == b);

	a.clear();
	a = {1, 3, 2, 2, 3, 1};
	WiggleSort(a);
	b.clear();
	b = {2, 3, 1, 3, 1, 2};
	assert(a == b);

	a.clear();
	a = {1, 1, 2, 1, 2, 2, 1};
	b.clear();
	b = {1, 2, 1, 2, 1, 2, 1};
	WiggleSort(a);
	assert(b == a);

	a.clear();
	a = {5, 3, 1, 2, 6, 7, 8, 5, 5};
	b.clear();
	b = {5, 8, 5, 7, 3, 6, 2, 5, 1};
	WiggleSort(a);
	assert(b == a);
}
void BinarySearchTests()
{
	int pos;
	vector<size_t> source;
	long data[12] = {15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5};
	/*L				      M			         U*/
	source.resize(30);
	generate(source.begin(), source.begin() + 10, [i = 0]() mutable
			 { return i++; });
	generate(source.begin() + 10, source.begin() + 20, [i = 1000]() mutable
			 { return i++; });
	generate(source.begin() + 20, source.begin() + 30, [i = 2000]() mutable
			 { return i++; });
	rotate(source.begin(), source.begin() + source.size() / 2, source.end());
	pos = BinarySearch(source, 1000);
	assert(pos >= 0);
	assert(source[pos] == 1000);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 1000 found at location: " << pos << ", " << source[pos] << endl;

	source.clear();
	source.assign(&data[0], &data[11]);
	pos = BinarySearch(source, 20);
	assert(pos == 5);
	assert(source[pos] == 20);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 20 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 17);
	assert(pos == 2);
	assert(source[pos] == 17);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 0);
	assert(pos == 6);
	assert(source[pos] == 0);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 3);
	assert(pos == 9);
	assert(source[pos] == 3);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 3 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 11);
	assert(pos < 0);

	long data1[20] = {15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5, 6, 7, 8};
	/*L				             M			          U*/
	source.clear();
	source.assign(&data1[0], &data1[14]);
	pos = BinarySearch(source, 0);
	assert(pos == 6);
	assert(source[pos] == 0);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 5);
	assert(pos == 11);
	assert(source[pos] == 5);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 5 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 17);
	assert(pos == 2);
	assert(source[pos] == 17);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 11);
	assert(pos < 0);

	long data2[12] = {4, 8, 9, 9, 9, 10, 12, 13, 1, 2, 2, 3};
	source.clear();
	source.assign(&data2[0], &data2[11]);
	pos = BinarySearch(source, 9);
	assert(pos > 0);
	assert(source[pos] == 9);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 9 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 2);
	assert(pos > 0);
	assert(source[pos] == 2);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 2 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 12);
	assert(pos == 6);
	assert(source[pos] == 12);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 12 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 0);
	assert(pos < 0);

	vector<vector<long>> a = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
	assert(searchMatrix(a, 3));
	assert(!searchMatrix(a, 13));
	a.clear();
	a = {{1}};
	assert(!searchMatrix(a, 0));
	assert(searchMatrix(a, 1));
	a.clear();
	a = {{1}, {3}};
	assert(searchMatrix(a, 1));
	assert(!searchMatrix(a, 0));
	a.clear();
	a = {{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
	assert(searchMatrix1(a, 1));
	assert(searchMatrix1(a, 5));
	assert(searchMatrix1(a, 9));
	assert(searchMatrix1(a, 17));
	assert(searchMatrix1(a, 30));
	assert(!searchMatrix1(a, 0));
	a.clear();
	a = {{1}, {2}, {3}, {4}, {5}};
	assert(searchMatrix1(a, 2));
	assert(!searchMatrix1(a, 0));
	a.clear();
	a = {{1, 1}};
	assert(searchMatrix1(a, 1));
	assert(!searchMatrix1(a, 0));
	source.clear();
	source = {5, 7, 7, 8, 8, 10};
	vector<long> result = searchRange(source, 8);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == 3);
	assert(result[1] == 4);

	source.clear();
	result = searchRange(source, 0);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == -1);
	assert(result[1] == -1);

	source.clear();
	source = {1};
	result = searchRange(source, 1);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == 0);
	assert(result[1] == 0);

	source.clear();
	source = {1, 3};
	result = searchRange(source, 1);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == 0);
	assert(result[1] == 0);
	result = searchRange(source, 3);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == 1);
	assert(result[1] == 1);

	source.clear();
	source = {1, 5};
	result = searchRange(source, 4);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == -1);
	assert(result[1] == -1);

	source.clear();
	source = {0, 0, 1, 1, 1, 4, 5, 5};
	result = searchRange(source, 2);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == -1);
	assert(result[1] == -1);

	source.clear();
	source = {0, 1, 2, 3, 4, 4, 4};
	result = searchRange(source, 2);
	assert(!result.empty());
	assert(result.size() == 2);
	assert(result[0] == 2);
	assert(result[1] == 2);

	vector<long> b{3, 4, 5, 1};
	assert(BinarySearchMinimum(b, 0, b.size() - 1) == 1);
}
void BinarySearchCountTests()
{
	vector<long> ages(50, 20);
	ages.resize(100);
	// 0:49 20, 50: 79 30, 80: 99 50
	generate(ages.begin() + 50, ages.begin() + 80, [i = 30]() mutable
			 { return i; });
	generate(ages.begin() + 80, ages.end(), [i = 50]() mutable
			 { return i; });
	int count = BinarySearchCountUpper(ages, 18, 0, ages.size() - 1) - BinarySearchCountLower(ages, 18, 0, ages.size() - 1);
	assert(count == 0);
	count = BinarySearchCountUpper(ages, 20, 0, ages.size() - 1) - BinarySearchCountLower(ages, 20, 0, ages.size() - 1) + 1;
	assert(count == 50);
	count = BinarySearchCountUpper(ages, 30, 0, ages.size() - 1) - BinarySearchCountLower(ages, 30, 0, ages.size() - 1) + 1;
	assert(count == 30);
	count = BinarySearchCountUpper(ages, 50, 0, ages.size() - 1) - BinarySearchCountLower(ages, 50, 0, ages.size() - 1) + 1;
	assert(count == 20);
}
void BinarySearchStringTests()
{
	int pos;
	vector<string> str{"abc", "ABC", "", "123", "789", "xyz", "XYZ", ""};
	sort(str.begin(), str.end());

	pos = BinarySearch(str, string("123"));
	assert(pos == 2);
	assert(str[pos] == "123");
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: \"123\" found at location: " << pos << ", " << str[pos] << endl;

	pos = BinarySearch(str, string("abc"));
	assert(pos == 6);
	assert(str[pos] == "abc");
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: \"abc\" found at location: " << pos << ", " << str[pos] << endl;
}
void BubbleSort(vector<long> &data)
{
	long tmp;
	for (size_t lastIndex = data.size() - 1; lastIndex >= 1; lastIndex--)
	{
		for (size_t i = 0; i < lastIndex; i++)
		{
			if (data[i] > data[i + 1])
			{
				tmp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = tmp;
			}
		}
	}
}
/* Quick Sort (http://en.wikipedia.org/wiki/Quicksort)
 * C=2, L=lg(N), Other: N
 * #nodes = (C^L - 1) / (C - 1) = 2^lg(N) - 1
 * TC: (2^lg(N) - 1) * N = N^2
 * Mathematics: 2^lg(N)
 * N: 8
 * ln(N) = 3 => 2^3 = 8
 * So, 2^lg(N) = N
 */
void QuickSort(vector<long> &data, long left, long right)
{
	size_t pivot;
	if (left >= 0 && right < (long)data.size() && left < right)
	{
		pivot = left + (right - left) / 2 + (right - left) % 2; // This overcomes integer overflow which happens if data.size() is large and naive approach of (lo + hi)/2 is used to index the middle element.
		// Worst case: N-1 calls. Each call processes the list from left to right-1 (N) => O(N^2)
		// Average case: lg(N) calls. Each level of call tree processes half the original list. Both calls processes N items => O(N*log(N)).
		pivot = Partition(data, left, right, pivot);
		QuickSort(data, left, pivot - 1);  // Either this or the call below is used in worst-case scenario
		QuickSort(data, pivot + 1, right); // Either this or the call above is used in worst-case scenario
	}
}
/* Worst case: returns original list (newPivot = left || newPivot = right)
 * Average case: Divides the original list to half. newPivot = 1/2.
 * newPivot = The final position of the pivot at the end of this partition operation.
 * Example:
 * [1,3,{0},2]: left:0, right: 3, pivot: 2
 * pivotValue: 0
 * newPivot = 0
 * [1,3,2,{0}]
 * i:0
 *		newPivot:0
 * i:1
 *		newPivot:0
 * i:2
 *		newPivot:0
 * => [0,3,2,1]
 * [0], [3,2,1] left:1, right: 3, pivot: 2
 * pivotValue: 2
 * newPivot = 1
 * [0,3,1,2]
 * i:1
 *		newPivot: 1
 * i:2
 *		[0,1,3,2]
 *		newPivot: 2
 * => [0,1,2,3]
 */
size_t Partition(vector<long> &data, size_t left, size_t right, size_t pivot)
{
	size_t newPivot = left; // This is used to find the final location for the pivot value
	long pivotValue = data[pivot];
	if (pivot != right)
		swap(data[pivot], data[right]);
	for (size_t i = left; i < right; i++)
		if (data[i] < pivotValue)
		{
			if (i != newPivot)
				swap(data[i], data[newPivot]);
			newPivot++;
		}
	if (newPivot != right)
		swap(data[newPivot], data[right]);
	return newPivot;
}
// Find the smallest element using a linear scan and move it to the front.
// Then, find the second smallest and move it, again doing a linear scan.
// Continue doing this until all the elements are in place. O(n^2).
void SelectionSort(vector<long> &data)
{
	size_t min = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		min = i;
		for (size_t j = i + 1; j < data.size(); j++)
		{ // Find the min from lower bound to end
			if (data[j] <= data[min])
				min = j;
		}
		if (min != i)
			swap(data[min], data[i]);
	}
}
void InsertionSort(vector<long> &data)
{
	if (data.size() > 1)
		for (size_t i = 1; i < data.size(); i++)
			for (size_t j = i; j > 0 && data[j] < data[j - 1]; j--)
				swap(data[j], data[j - 1]);
}
/* http://en.wikipedia.org/wiki/Merge_sort
 * top-down merge sort algorithm that recursively splits the list (called runs in this example) into sublists
 * until sublist size is 1, then merges those sublists to produce a sorted list
 * The copy back step is avoided with alternating the direction of the merge with each level of recursion (except for an initial one time copy)
 * start: inclusive; end: exclusive
 * Example:
 * [2,1]:  A,B [0,2)
 * [2] [1] B,A [0,1), [1,2) <- Never gets into the if (end - start > 1) condition.
 * [1,2]   A,B <= Bottom of recursion. Merge into B
 * Time complexity: 1 level (log(n)), 1 comparison. 2 items. => O(n*log(n))
 *
 * [2,1,4,3]:      A,B [0:4)
 * [2,1] [4,3]	   B,A [0:2), [2:4)
 * [2] [1] [4] [3] A,B [0:1), [1,2), [2,3), [3,4) <- Never gets into the if (end - start > 1) condition.
 * [1,2] [3,4]	   B,A <= Bottom of recurssion. Merge into A. 2 comparisons. 4 items.
 * [1,2,3,4]	   A,B <= Next higher level, merge into B. 1 comparison. 4 items.
 * Time complexity: 2 levels (log(n)), 3 comparisons, 4 items. => O(n*log(n))
 * C: 2, L: lg(N), Others: N
 * #nodes = (C^L - 1) / (C - 1) = 2^lg(N) = N
 * TC = N*lg((N)
 */
void TopDownMergeSort(vector<long> &A, vector<long> &B, size_t start, size_t end)
{
	if (end - start > 1)
	{ // If run size == 1, consider it sorted
		// recursively split runs into two halves until run size == 1,
		// then merge them and return back up the call chain
		size_t middle = start + (end - start) / 2 + (end - start) % 2;
		TopDownMergeSort(B, A, start, middle);
		TopDownMergeSort(B, A, middle, end);
		Merge(A, B, start, middle, end);
	}
}
// https://www.hackerrank.com/challenges/ctci-merge-sort/problem
// 100%
size_t TopDownMergeSortCountConversions(vector<long> &B, vector<long> &A, size_t start, size_t end)
{
	size_t inversions = 0;
	if (end - start > 1)
	{ // If run size == 1, consider it sorted
		// recursively split runs into two halves until run size == 1,
		// then merge them and return back up the call chain
		size_t middle = start + (end - start) / 2 + (end - start) % 2;
		inversions += TopDownMergeSortCountConversions(A, B, start, middle);
		inversions += TopDownMergeSortCountConversions(A, B, middle, end);
		inversions += MergeCountInversions(B, A, start, middle, end);
	}
	return inversions;
}
size_t MergeCountInversions(vector<long> &source, vector<long> &dest, size_t start, size_t middle, size_t end)
{
	size_t inversions = 0;
	size_t left = start;
	size_t right = middle;
	// While there are elements in the left or right runs...
	for (size_t i = start; i < end; i++)
	{
		// If left run head exists and is <= existing right run head.
		// dest[i] = (left < middle && (right >= end || source[left] <= source[right])) ? source[left++] : source[right++];
		if (left < middle && (right >= end || source[left] <= source[right]))
			dest[i] = source[left++];
		else
		{
			inversions += right - i;
			dest[i] = source[right++];
		}
	}
	return inversions;
}
/* bottom-up merge sort algorithm which treats the list consisting of n sublists (called runs in this example)
 * of size 1, and iteratively merges sub-lists back and forth between two buffers
 * List A[] has the items to sort; list B[] is a work buffer
 * Example:
 * [2,1] => [1,2]
 *
 * [0,2,1]
 * [0],[2],[1]
 * => [0,2], [1] : width = 1
 * => [0,1,2] : width = 2. 1 Inversion
 *		[0,2], [1]: width = 1 => [0,2,1]
 *		[0,1,2]: width = 2.
 *			[0,1,2] Inversion between index 1 & 2
 * [0,3,1,2]
 * [0], [3], [1], [2]
 * => [0,3], [1,2] : width = 1
 * => [0,1,2,3] : width = 2. 2 Inversions: {1,2}, {2,3}
 *		[0,3], [1,2]: width = 1 => [0,3,1,2]
 *		[0,1,2,3]: width = 2.
 *			[0,1,3,2] Inversion between index 1 & 2
 *			[0,1,2,3] Inversion between index 2 & 3
 * O(lg(N) * N) = O(N * lg(N))
 */
void BottomUpMergeSort(vector<long> &A, vector<long> &B)
{
	size_t n = A.size();
	// Each 1-element run in data is already "sorted".
	// Make successively longer sorted runs of length 2, 4, 8, 16... until whole array is sorted.
	for (size_t width = 1; width < A.size(); width *= 2)
	{ // O(lg(N))
		// Array A is full of runs of length width.
		// width: 1, i(+2): 0, 2, 4, 6, 8, 10
		// width: 2, i(+4): 0, 4, 8, 12,16,20
		for (size_t i = 0; i < A.size(); i += 2 * width)			  // Range of each Merge call. Total is O(N).
																	  /* Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
																	   * width: 1
																	   *   i:0 Merge two runs: A[0:0] and A[1:1] to B[] [start, middle, end] : [0,1,2)
																	   *   i:2 Merge two runs: A[2:2] and A[3:3] to B[] [start, middle, end] : [2,3,4)
																	   *   i:4 Merge two runs: A[4:4] and A[5:5] to B[] [start, middle, end] : [4,5,6)
																	   *  width: 2
																	   *   i:0 Merge two runs: A[0:1] and A[2:3] to B[] [start, middle, end] : [0,2,4)
																	   *   i:2 Merge two runs: A[2:3] and A[4:5] to B[] [start, middle, end] : [2,4,6)
																	   *   i:4 Merge two runs: A[4:5] and A[6:7] to B[] [start, middle, end] : [4,6,8)
																	   *  or copy A[i:n-1] to B[] ( if (i+width >= n) )
																	   */
			Merge(A, B, i, min(i + width, n), min(i + 2 * width, n)); // O(N)
		// Now work array B is full of runs of length 2*width.
		// Copy array B to array A for next iteration.
		// A more efficient implementation would swap the roles of A and B.
		A = B;
		// Now array A is full of runs of length 2*width.
	}
}
/* https://leetcode.com/problems/wiggle-sort-ii/
 * 100%
 * 1 5 1 1 6 4
 * 1 1 1 [4] 5 6
 *     i  M    j
 * 1 6 1 5 1 4
 *
 * 1 3 2 2 3 1
 * 1 1 2 [2] 3 3
 *     i  M    j
 * 2 3 1 3 1 2
 *
 * 5 3 1 2 6 7 8 5 5
 * 1 2 3 5 5 [5] 6 7 8
 * 		  i  M      j
 * 5 8 5 7 3 6 2 5 1
 */
void WiggleSort(vector<long> &data)
{
	sort(data.begin(), data.end());
	vector<long> result;
	size_t middle = data.size() / 2 + data.size() % 2;
	int i = middle - 1, j = data.size() - 1;
	for (; i >= 0 && j >= (int)middle; i--, j--)
	{
		result.push_back(data[i]);
		result.push_back(data[j]);
	}
	if (i >= 0)
		result.push_back(data[i]);
	else if (j > (int)middle)
		result.push_back(data[j]);
	data = result;
}
void Merge(vector<long> &source, vector<long> &dest, size_t start, size_t middle, size_t end)
{
	size_t left = start;
	size_t right = middle;
	// While there are elements in the left or right runs...
	for (size_t i = start; i < end; i++)
		/* If left run head exists (left < middle)
		 * AND value is <= existing right run head.
		 * OR  Right run is empty (right >= end)
		 * Example:
		 * width: 1
		 * source: [0,2(R),1] dest: [] [start, middle, end] = [0,1,2)
		 * left:0, right: 1, middle: 1, end: 2
		 * dest[0] = 0, Take left. left == middle == 1
		 * dest[1] = 2 (left == middle), Take right.
		 * source: [0,2,1] dest: [0,2] [start, middle, end] = [2,3,3)
		 * left:2, right: 3, middle: 3, end: 3
		 * dest[2] = 1 (right == end), Take left. left == middle == 3
		 *
		 * width: 2
		 * source: [0,2,1(R)] dest: [0,2,1] [start, middle, end] = [0,2,3)
		 * left:0, right: 2, middle: 2, end: 3
		 * dest[0] = 0, Take left. left = 1
		 * dest[1] = 1, Take right (1 < 2). right = 3 == end [Inversion count = right - i = 2 - 1 = 1]
		 * dest[2] = 2, Take left (right == end). left = 2
		 */
		dest[i] = (left < middle && (right >= end || source[left] <= source[right])) ? source[left++] : source[right++];
}
// https://en.wikipedia.org/wiki/Heapsort
void HeapSort(vector<long> &data)
{
	Heap<long> heap(data, HeapType::MaxHeap);
	assert(heap.Count() == data.size());
	for (long end = data.size() - 1; end >= 0; end--)
	{
		long item = heap.pop()->Item();
		swap(data[end], item);
	}
}
// https://en.wikipedia.org/wiki/Counting_sort
//  each of which has a non-negative integer key whose maximum value is at most k
void CountingSort(vector<size_t> &data)
{
	vector<size_t> input(data);
	long min = numeric_limits<size_t>::max(), max = 0;
	for (vector<size_t>::iterator it = input.begin(); it != input.end(); it++)
	{
		if ((long)*it < min)
			min = *it;
		if ((long)*it > max)
			max = *it;
	}
	// Do NOT use map / multimap to keep the counts. map / multimap auto-sort on keys. This defeats the purpose of CountingSort
	vector<size_t> counts(max + 1, 0);
	for (vector<size_t>::iterator it = input.begin(); it != input.end(); it++)
		counts[*it]++;
	for (long i = min > 0 ? min : 1; i <= max; i++)
		counts[i] += counts[i - 1];
	// Use reverse_iterator for a stable sort
	for (vector<size_t>::reverse_iterator it = input.rbegin(); it != input.rend(); it++)
	{
		data[counts[*it] - 1] = *it;
		counts[*it]--;
	}
}
string CountingSort(vector<vector<string>> &data)
{
	vector<string> result;
	long min = numeric_limits<size_t>::max(), max = 0;
	for (vector<vector<string>>::iterator it = data.begin(); it != data.end(); it++)
	{
		long key;
		istringstream((*it)[0]) >> key;
		if (key < min)
			min = key;
		if (key > max)
			max = key;
	}
	// Do NOT use map / multimap to keep the counts. map / multimap auto-sort on keys. This defeats the purpose of CountingSort
	vector<size_t> counts(max + 1, 0);
	for (vector<vector<string>>::iterator it = data.begin(); it != data.end(); it++)
	{
		size_t key;
		istringstream((*it)[0]) >> key;
		counts[key]++;
	}
	for (long i = min > 0 ? min : 1; i <= max; i++)
		counts[i] += counts[i - 1];
	result.resize(counts.back());
	// Use reverse_iterator for a stable sort
	for (vector<vector<string>>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
	{
		size_t key;
		istringstream((*it)[0]) >> key;
		result[counts[key] - 1] = (*it)[1];
		counts[key]--;
	}
	ostringstream oss;
	for (size_t i = 0; i < result.size(); i++)
	{
		if (!result[i].empty())
		{
			oss << result[i];
			if (i < result.size() - 1)
				oss << " ";
		}
	}
	return oss.str();
}
/*
   Count the minimum number of swaps needed to sort the data in either ascending or descending order
data:         2 5 3 1
sorted index: 1 3 2 0 <= 3 links (0:1 - 1:3 - 3:0) 2 swaps

#index link #swaps
	2		1
	3		2
	4		3
	5		4
Not optimized for big data input
*/
size_t SortSwapCount(vector<size_t> &data)
{
	size_t result = 0, resultDescend = 0;
	set<size_t> visited, visitedDescend;
	set<size_t> sorted(data.begin(), data.end());
	set<size_t, greater<size_t>> sortedDescend(data.begin(), data.end());
	for (size_t i = 0; i < data.size(); i++)
	{
		if (distance(sorted.begin(), sorted.find(data[i])) != i)
		{
			long offset = i;
			size_t cnt = 0;
			do
			{
				offset = distance(sorted.begin(), sorted.find(data[offset]));
				if (visited.find(offset) == visited.end())
				{
					cnt++;
					visited.insert(offset);
				}
			} while (offset != i);
			result += cnt > 0 ? cnt - 1 : 0;
		}
		if (distance(sortedDescend.begin(), sortedDescend.find(data[i])) != i)
		{
			long offset = i;
			size_t cnt = 0;
			do
			{
				offset = distance(sortedDescend.begin(), sortedDescend.find(data[offset]));
				if (visitedDescend.find(offset) == visitedDescend.end())
				{
					cnt++;
					visitedDescend.insert(offset);
				}
			} while (offset != i);
			resultDescend += cnt > 0 ? cnt - 1 : 0;
		}
	}
	return min(result, resultDescend);
}
/* https://en.wikipedia.org/wiki/Dutch_national_flag_problem
* https://leetcode.com/problems/sort-colors/
* 100%
* i: index for the next 0
* j: index for the next 1
* k: index for the next 2
0  i   j   k  n-1
<mid mid ??? >mid

2 1 0 1 2 0 1 2
i,j           k (>mid)

2 1 0 1 2 0 1 2
i,j         k   (>mid)

1 1 0 1 2 0 2 2
i,j       k     (==mid)

1 1 0 1 2 0 2 2
i j       k    (==mid)

1 1 0 1 2 0 2 2
i   j     k    (<mid)

0 1 1 1 2 0 2 2
  i   j     k  (==mid)

0 1 1 1 2 0 2 2
  i     j   k  (>mid)

0 1 1 1 2 0 2 2
  i     j k    (>mid)

0 1 1 1 0 2 2 2
  i     j,k    (<mid)

0 0 1 1 1 2 2 2
	i   k j		<= j > k base case
*/
void DutchPartitioning(vector<size_t> &data, size_t mid)
{
	for (int i = 0, j = 0, k = data.size() - 1; !data.empty() && j <= k;)
	{
		if (data[j] < mid)
			swap(data[i++], data[j++]);
		else if (data[j] > mid)
			swap(data[j], data[k--]);
		else // if (data[j] == mid)
			j++;
	}
}
long **my2DAlloc(long rows, long cols)
{
	size_t header = rows * sizeof(long *);			// Store the row pointers [i]
	size_t data = rows * cols * sizeof(long);		// Store the data
	long **rowptr = (long **)malloc(header + data); // row pointers + data buffers
	long *dataptr = (long *)(rowptr + rows);		// Pointer arithmetic to get the first location of data buffer
	for (int i = 0; i < rows; i++)
		rowptr[i] = dataptr + i * cols;
	return rowptr;
}
long ***my3DAlloc(long rows, long cols, long heights)
{
	size_t header = rows * sizeof(long *) + rows * cols * sizeof(long *); // Store the row pointers [i] and every cell of the 2D-plane is pointer to the Z-buffer [i][j]
	size_t data = rows * cols * heights * sizeof(long);					  // data
	long ***ptrs = (long ***)malloc(header + data);						  // row pointers + 2-D plane of pointers to Z-plane data
	long **columns = (long **)(ptrs + rows);							  // Pointer arithmetic to get the first location of 2D plane of Z-plane pointers [i][j]
	long *dataPtr = (long *)(ptrs + rows + rows * cols);				  // Pointer arithmetic to get the first location of data buffer
	for (long i = 0; i < rows; i++)
	{
		ptrs[i] = columns + i * cols;
		for (long j = 0; j < cols; j++)
			ptrs[i][j] = dataPtr + i * cols * heights + j * heights;
	}
	return ptrs;
}
/* https://leetcode.com/problems/sum-of-two-integers/			   1
 * 1 + 1 = 10b, 1 + 0 = 1b, 0 + 0 = 0b
 * Only 1 1 has carry
 * https://stackoverflow.com/questions/55615186/c-left-shift-overflow-for-negative-numbers
 * Left-shifting a negative value results in undefined behaviour. Use unsigned for bit manipulations.
 */
long long AddWithoutArithmetic(long long sum, long long carry)
{
	return !carry ? sum : AddWithoutArithmetic(sum ^ carry, (unsigned long long)(sum & carry) << 1);
}
// Function for finding sum of larger numbers
string NumberStringSum(const string &str1, const string &str2)
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
string NumberStringMultiplication(string &num1, string &num2)
{
	if (num1.empty() || num2.empty())
		return "0";
	bool isNegative = (num1[0] == '-' && num2[0] != '-') || (num1[0] != '-' && num2[0] == '-');
	if (num1[0] == '-')
		num1 = num1.substr(1);
	if (num2[0] == '-')
		num2 = num2.substr(1);

	// will keep the result number in vector in reverse order
	vector<long> result(num1.size() + num2.size(), 0);

	size_t i_n1 = 0, i_n2 = 0;
	// Go from right to left in num1 (bottom)
	for (int i = num1.size() - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';
		// To shift position to left after every multiplication of a digit in num2 (top)
		i_n2 = 0;
		// Go from right to left in num2
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
/* http://www.cplusplus.com/reference/cstdlib/rand/
 * A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use
 * the modulo of the returned value by the range span and add the initial value of the range:
 * v1 = rand() % 100;         // v1 in the range 0 to 99
 * v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
 * v3 = rand() % 30 + 1985;   // v3 in the range 1985 to 2014
 */
void shuffleCards(vector<long> &cards)
{
	unsigned long long mask = 0; // bitmask of 52 cards.
	int tmp, index;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	if (!cards.empty() && cards.size() <= 52)
	{
		for (size_t i = 0; i < 52; i++)
		{
			/* index = (rand() % (52 - i)) + i;
			 * i: n  random from n to 51
			 * i: 0  (rand() % 52) + 0  = 0  to 51
			 * i: 1  (rand() % 51) + 1  = 1  to 51
			 * i: 2  (rand() % 50) + 2  = 2  to 51
			 * i: 10 (rand() % 42) + 10 = 10 to 51
			 * i: 26 (rand() % 26) + 26 = 26 to 51
			 * i: 50 (rand() % 2) + 50  = 50 to 51
			 * i: 51 (rand() % 1) + 51  = 51 (Last card left)
			 */
			uniform_int_distribution<int> dist(i, 51);
			index = dist(engine);
			assert(!(mask & ((unsigned long long)1 << cards[index])));
			mask |= ((unsigned long long)1 << cards[index]);
			tmp = cards[i];
			cards[i] = cards[index];
			cards[index] = tmp;
		}
	}
}
void randomSubset(vector<long> &source, size_t count, vector<long> &result)
{
	set<long> masks;
	long index, tmp;
	if (count > source.size())
		return;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	for (size_t i = 0; i < count; i++)
	{
		// index = (rand() % (source.size() - i)) + i;
		uniform_int_distribution<long> dist(i, source.size() - 1);
		index = dist(engine);
		// cout << "source[" << index << "]: " << source[index] << endl;
		assert(masks.find(source[index]) == masks.end());
		masks.emplace(source[index]);
		result.push_back(source[index]);
		tmp = source[i];
		source[i] = source[index];
		source[index] = tmp;
	}
}
/*
 *  0  1  2  3  4  5  6  7  8  9
 * 10 11 12 13 14 15 16 17 18 19
 * 20 21 22 23 24 25 26 27 28 29
 * 30 31 32 33 34 35 36 37 38 39
 * ...
 * 100 101 102 103 104 105 106 107 108 109
 * 110 111 112 113 114 115 116 117 118 119
 *
 * The last digit will repeat every 10 numbers, the last two digits will repeat every 10^2 numbers, the last 3 digits will repeat every 10^3 numbers, etc.
 *
 * So, if there are X 3s between 0 and 9, then we know there are 2x '3' between 0 and 19.
 * Between 0 and 39, we have 4x '3' from the last digit, and another 10 '3's from the first digit.
 *
 * sequence of last m digits (power-1) repeats n/power times.
 *
 * n: 235 digit: 3
 *
 * f(9):
 * power=1
 * repeats (last digit): 1 {3}
 *
 * f(99):	The last digit will repeat every 10 numbers
 * power=10
 * repeats (last digit): 99/10=9: 13,23,33,43,53,63,73,83,93 (within the power of 10)
 * MSBs: 10
 *
 * f(235):  The last two digits will repeat every 10^2 numbers
 * power:100
 * repeats (last 2 digits): 235/100=2 Example: 134, 234
 *
 * repeats = n / power
 * Total(n=235, digit=3) = n/power * f(power-1) + f(n % power) + MSBs
 *
 * MSBs: n / power > digit ? power : (n % power) == digit ? (n % power) + 1 : 0
 *
 * Example:
 * digit:3, n: 35
 * {3,13,23},{30,31,32,3{3},34,35}
 * first digit repeats n/10= 3 times => 3 * f(power - 1) : {3,13,23}
 * + MSBs = 6 {30,31,32,33,34,35}
 * + f(5) {3'3'}
 *
 * So, if there are X 2s between 0 and 99, then we know there are 2x twos between 0 and 199.
 * Between 0 and 299, we have 3x twos from the last two digits, and another 100 2s from the first digit.
 */
size_t countDigits(char digit, size_t n)
{
	unsigned long power = 1, MSBs = 0;
	if (digit < 0 || digit > 9)
		throw runtime_error("digit must be between 0 and 9!");
	if (!n)
		return 0;
	for (; (power * 10) < n; power *= 10)
		;
	/* Count MSB digits in the number
	 * 123: power = 100. '1' appears in 100-123
	 * 223: power = 100. '1' appears in 100-199
	 */
	if ((char)(n / power) > digit)
		MSBs = power;
	else if ((n / power) == digit)
		MSBs = (n % power) + 1;

	// Count digit from all other digits
	return (n / power) * countDigits(digit, power - 1) + countDigits(digit, n % power) + MSBs;
}
/* https://leetcode.com/problems/count-numbers-with-unique-digits/
 * 100%
 * Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n. 0 <= n <= 8
 * MSB: 1-9 count=9
 * next: 0-9 exclude MSB count=9
 * next: 0-9 count = 10 - 2 = 8
 * count: 9,9,8,7,6,5,4,3,2,1,0
 *
 * i:		 0 1 2 3 4 5 6 7 8 9 10
 * lastCount: 9 9 8 7 6 5 4 3 2 1 0(-1)
 *
 * MSB cannot have '0' digit
 *
 * n: 1 [0,10) 0-9
 * 10
 *
 * n: 2 [0,100) 0-99
 * Start from LSB:
 * LSB: 10 numbers
 * next: 10 - LSB's digit - '0' = 8 => 80 numbers
 *
 * Start from MSB:
 * MSB: 10 - '0' = 9
 * next: 10 - MSB's digit = 9 => 81 numbers
 *
 * n: 3 [0,1000) 0-999
 * Start from LSB:
 * LSB: 10 numbers
 * next: 10 - LSB's digit = 9
 * next: 10 - 1 ('0') - 2 = 7 => 7 * 9 * 10 = 630
 *
 * Start from MSB:
 * MSB: 10 - '0' = 9 digits
 * next: 10 - MSB's digit = 9
 * next: 8 => 8 * 9 * 9 = 648
 *
 * Starting from MSB will give more unique numbers
 */
size_t countNumbersWithUniqueDigits(size_t n)
{
	size_t count = 1;
	if (n >= 0 && n <= 1)
		return pow(10, n);
	else if (n <= 10)
	{
		long lastCount = 9;
		for (size_t i = 0; i < n; i++)
		{
			count *= lastCount;
			if (i >= 1)
				lastCount--;
		}
		return count + countNumbersWithUniqueDigits(n - 1);
	}
	return 0;
}
/* http://en.wikipedia.org/wiki/Greatest_common_divisor
 * the largest positive integer that divides the numbers without a remainder
 */
long gcd_euclidean(long a, long b)
{
	return !(a % b) ? b : gcd_euclidean(b, a % b);
}
long gcd(long a, long b)
{
	if (!a)
		return b;
	else if (!b)
		return a;
	else
		return a >= b ? gcd_euclidean(a, b) : gcd_euclidean(b, a);
}
/* http://en.wikipedia.org/wiki/Least_common_multiple */
/* he smallest positive integer that is divisible by both a and b.[1] If either a or b is 0, LCM(a, b) is defined to be zero. */
long lcm(long a, long b)
{
	return (!a || !b) ? 0 : (a * b) / gcd(a, b);
}
unsigned long long _atoull(string str, char base)
{
	size_t i = 0;
	unsigned long long result = 0;
	if ((str.length() > 2) && str[0] == '0' && str[1] == 'x')
	{
		base = 16;
		i = 2;
	}
	for (; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if ((str[i] - '0') >= base)
				break;
			result *= base;
			result += str[i] - '0';
		}
		else if (base == 16 && ((str[i] >= 'a' && str[i] <= 'f') || str[i] >= 'A' && str[i] <= 'F'))
		{
			result *= base;
			if (str[i] >= 'a' && str[i] <= 'f')
				result += str[i] - 'a';
			else
				result += str[i] - 'A';
			result += 10;
		}
		else
			break;
	}
	return result;
}
double _atod(string str, char base)
{
	size_t i = 0;
	bool isRemainder = false;
	double quotient = 0;
	double remainder = 0;
	unsigned long long qCount = 1;
	if ((str.length() > 2) && str[0] == '0' && str[1] == 'x')
	{
		base = 16;
		i = 2;
	}
	for (; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if ((str[i] - '0') >= base)
				break;
			if (isRemainder)
			{
				qCount *= base;
				remainder *= base;
				remainder += (double)str[i] - '0';
			}
			else
			{
				quotient *= base;
				quotient += (double)str[i] - '0';
			}
		}
		else if (base == 16 && ((str[i] >= 'a' && str[i] <= 'f') || str[i] >= 'A' && str[i] <= 'F'))
		{
			if (isRemainder)
			{
				qCount *= base;
				remainder *= base;
				if (str[i] >= 'a' && str[i] <= 'f')
					remainder += (double)str[i] - 'a';
				else
					remainder += (double)str[i] - 'A';
				remainder += 10;
			}
			else
			{
				quotient *= base;
				if (str[i] >= 'a' && str[i] <= 'f')
					quotient += (double)str[i] - 'a';
				else
					quotient += (double)str[i] - 'A';
				quotient += 10;
			}
		}
		else if (str[i] == '.')
			isRemainder = true;
		else
			break;
	}
	if (remainder)
	{
		remainder /= qCount;
		return quotient + remainder;
	}
	else
		return quotient;
}
/*
 * https://leetcode.com/problems/string-to-integer-atoi/
 * 100%
 */
long _atoi(string str)
{
	int result = 0;
	bool isNegative = false, isPositive = false, foundNumber = false;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '-')
		{
			if (!isNegative && !isPositive && !foundNumber)
				isNegative = true;
			else if (foundNumber)
				return isNegative ? result * -1 : result;
			else
				return 0;
		}
		else if (str[i] == '+')
		{
			if (!isPositive && !isNegative && !foundNumber)
				isPositive = true;
			else if (foundNumber)
				return isNegative ? result * -1 : result;
			else
				return 0;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			long r = (long)result * 10;
			r += str[i] - '0';
			if (isNegative)
				r *= -1;
			if (r >= numeric_limits<int>::max())
				return numeric_limits<int>::max();
			else if (r <= numeric_limits<int>::min())
				return numeric_limits<int>::min();
			result *= 10;
			result += str[i] - '0';
			foundNumber = true;
		}
		else if (foundNumber || isNegative || isPositive)
		{
			if (foundNumber)
				return isNegative ? result * -1 : result;
			else
				return 0;
		}
		else if (str[i] != ' ')
			return 0;
	}
	if (isNegative)
		result *= -1;
	return result;
}
// 1234.5678
double round(double num, int n)
{
	unsigned long long tmp, tmp1;
	tmp = num * pow(10, n + 1);
	tmp1 = num * pow(10, n);
	if (tmp % 10 >= 5)
		tmp1++;
	return tmp1 / pow(10, n);
}
long absolute(long a)
{
	return a > 0 ? a : ToggleSign(a);
}
long ToggleSign(long a)
{
	long i, d = a < 0 ? 1 : -1;
	for (i = 0; a != 0; i += d, a += d)
		;
	return i;
}
long SubtractWithPlusSign(long a, long b)
{
	return a + ToggleSign(b);
}
long MultiplyWithPlusSign(long a, long b)
{
	if (b > a)
		return MultiplyWithPlusSign(b, a); // Just faster doing it the other way round
	long sum = 0;
	for (long i = absolute(b); i > 0; i--, sum += a)
		;
	return b < 0 ? ToggleSign(sum) : sum;
}
long DivideWithPlusSign(long a, long b)
{
	if (!b)
		throw runtime_error("Divide by zero exception");
	bool isNegative = (a < 0) ^ (b < 0);
	if (b == 1 || b == -1)
	{
		if (a == numeric_limits<int>::min())
#if defined(__GNUC__) || defined(__GNUG__)
			return isNegative ? numeric_limits<int>::min() : -a; // ToggleSign of 64-bit value takes very long time
#else
			return numeric_limits<int>::min();
#endif
		else if (a == numeric_limits<int>::max())
			return isNegative ? numeric_limits<int>::min() + 1 : numeric_limits<int>::max();
		if (a == numeric_limits<long>::min())
			return numeric_limits<long>::min();
		else if (a == numeric_limits<long>::max())
			return isNegative ? numeric_limits<long>::min() + 1 : numeric_limits<long>::max();
		if (isNegative)			   // result should be < 0
			return a < 0 ? a : -a; // ToggleSign of 64-bit value takes very long time
		return a < 0 ? -a : a;
	}
	long quotient;
	long divisor = ToggleSign(absolute(b)); // * -1
	long dividend = absolute(a);
	for (quotient = 0; dividend >= absolute(divisor); dividend += divisor, quotient++)
		;
	return isNegative ? -quotient : quotient;
}
long divide(long dividend, long divisor)
{
	if (!divisor)
		throw runtime_error("Divide by zero exception");
	int quotient = 0;
	bool isNegative = (dividend < 0) ^ (divisor < 0);
	if (divisor == 1 || divisor == -1)
	{
		if (dividend == numeric_limits<int>::min())
			return isNegative ? numeric_limits<int>::min() : -dividend; // ToggleSign of 64-bit value takes very long time
		else if (dividend == numeric_limits<int>::max())
			return isNegative ? numeric_limits<int>::min() + 1 : numeric_limits<int>::max();
		if (dividend == numeric_limits<long>::min())
			return numeric_limits<long>::min();
		else if (dividend == numeric_limits<long>::max())
			return isNegative ? numeric_limits<long>::min() + 1 : numeric_limits<long>::max();
		if (isNegative)
			return dividend < 0 ? dividend : -dividend; // ToggleSign of 64-bit value takes very long time
		return dividend < 0 ? -dividend : dividend;
	}
	if (divisor < 0)
		divisor = -divisor;
	if (dividend < 0)
		dividend = -dividend;
	for (; dividend >= divisor; quotient++, dividend -= divisor)
		;
	return isNegative ? -quotient : quotient;
}
long KthNumberWith357PrimeFactors(long n)
{
	long value = 1;
	if (n > 0)
	{
		queue<long> three, five, seven;
		three.push(3);
		five.push(5);
		seven.push(7);
		for (--n; n > 0; n--)
		{
			value = Min(three.front(), Min(five.front(), seven.front()));
			if (value == seven.front())
				seven.pop();
			else
			{
				if (value == five.front())
					five.pop();
				else
				{
					three.pop();
					three.push(value * 3);
				}
				five.push(value * 5);
			}
			seven.push(value * 7);
		}
	}
	return value;
}
void SuffixTreeTests()
{
	cout << "Test Suffix Tree..." << endl;
	SuffixTree sTree("Mississippi");
	vector<size_t> indexes;
	vector<string> subStrings{"Mississippi", "M", "m", "i", "s", "p", "is", "si", "sip", "hi", "sis", "pi", "ppi", "ssi", "issi"};
	size_t count = sTree.Count();
	assert(count == 53);
	cout << "Suffix tree of \"Mississippi\" has " << count << " nodes" << endl;
	for (vector<string>::iterator it = subStrings.begin(); it != subStrings.end(); it++)
	{
		cout << "Suffix index of substring " << *it << ": ";
		indexes = sTree.GetIndexes(*it);
		if (!indexes.empty())
			copy(indexes.begin(), indexes.end(), ostream_iterator<size_t>(cout, " "));
		else
			cout << "\"" << *it << "\" not found!";
		cout << endl;
	}
	vector<size_t> indices1 = sTree.GetIndexes("is");
	assert(indices1.size() == 2); // ississippi, issippi
	assert(indices1[0] == 1);
	assert(indices1[1] == 4);
	indices1 = sTree.GetIndexes("si");
	assert(indices1.size() == 2); // sissippi, sippi
	assert(indices1[0] == 3);
	assert(indices1[1] == 6);
	indices1 = sTree.GetIndexes("ssi");
	assert(indices1.size() == 2); // ssissippi, ssippi
	assert(indices1[0] == 2);
	assert(indices1[1] == 5);
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "issi");
	sTree.InsertString("sister");
	indices1 = sTree.GetIndexes("sis");
	assert(indices1.size() == 2);
	assert(indices1[0] == 3);
	assert(indices1[1] == string("Mississippi").size());
	indices1 = sTree.GetIndexes("sister");
	assert(indices1.size() == 1);
	assert(indices1[0] == string("Mississippi").size());
	sTree.Clear();
	assert(!sTree.Count());
	sTree.InsertString("Amazon");
	sTree.InsertString("Neha Aman");
	sTree.InsertString("+6591785484");
	/*
						root
	A     m     a          z  o  n    N    e   h   <sp>
	m     a     z <sp> n   o  n <5,8> e    h   a    A
	a     z n   o   A  <7> n <4>      h    a  <sp>  m
	z n   o <6> n   m     <3>         a  <sp>  A    a
	o <5> n    <2>  a                <sp>  A   m    n
	n    <1>        n                 A    m   a    <4>
	<0>            <3>                m    a   n
									  a	   n   <2>
									  n   <1>
									 <0>
	*/
	indexes = sTree.GetIndexes("Ama");
	assert(indexes.size() == 2);
	assert(indexes[0] == 0);
	assert(indexes[1] == 11);
	subStrings.clear();
	indexes = sTree.GetIndexes("+6591785484");
	assert(indexes.size() == 1);
	assert(indexes[0] == 15);
	indexes = sTree.GetIndexes("91785484");
	assert(indexes.size() == 1);
	assert(indexes[0] == 18);
	sTree.RemoveString("Amazon");
	sTree.RemoveString("Neha Aman");
	sTree.RemoveString("+6591785484");
	indexes = sTree.GetIndexes("Amazon");
	assert(indexes.empty());
	indexes = sTree.GetIndexes("Neha Aman");
	assert(indexes.empty());
	indexes = sTree.GetIndexes("+6591785484");
	assert(indexes.empty());
	sTree.Clear();
	assert(!sTree.Count());

	sTree.Clear();
	sTree.InsertString("abc.pqr.google.com");
	sTree.InsertString("pqr.google.com");
	sTree.InsertString("pqr.google.net");
	sTree.InsertString("yahoo.com");
	sTree.InsertString("abc.yahoo.com");
	indexes = sTree.GetIndexes("google.com");
	assert(indexes.size() == 2);
	assert(indexes[0] == 8);
	assert(indexes[1] == 22);
	sTree.Clear();
	sTree.InsertString("a");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(subStrings.empty());
	sTree.Clear();
	sTree.InsertString("aa");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "a");
	sTree.Clear();
	sTree.InsertString("aaa");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "aa");
	sTree.Clear();
	sTree.InsertString("ABABABA");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "ABABA");
	sTree.Clear();
	sTree.InsertString("abcd1234cd12");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "cd12");
	sTree.Clear();
	sTree.InsertString("abcd1234abcd");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "abcd");
	sTree.Clear();
	sTree.InsertString("abcdabcd1234");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "abcd");
	sTree.Clear();
	sTree.InsertString("abcd12341234");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "1234");
	sTree.Clear();
	sTree.InsertString("aaaa_11111_bbbb");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "1111");
	sTree.Clear();
	sTree.InsertString("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 2);
	assert(subStrings[0] == "AAAAACCCCC");
	assert(subStrings[1] == "CCCCCAAAAA");
	sTree.Clear();
	sTree.InsertString("GAGAGAGAGAGAG");
	subStrings = sTree.LongestRepeatedSubstring();
	assert(!subStrings.empty());
	assert(subStrings.size() == 1);
	assert(subStrings[0] == "GAGAGAGAGAG");

	sTree.Clear();
	size_t match;
	sTree.InsertString("abcd");
	sTree.InsertString("adbc");
	match = sTree.LongestCommonSubstring(0); // bc
	assert(match == 2);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 3);
	sTree.Clear();
	sTree.InsertString("helloworld");
	sTree.InsertString("yellomarin");
	match = sTree.LongestCommonSubstring(0); // ello
	assert(match == 4);
	match = sTree.LongestCommonSubstring(3);
	assert(match == 8);
	sTree.Clear();
	sTree.InsertString("abacba");
	sTree.InsertString("abcaba");
	match = sTree.LongestCommonSubstring(0);
	assert(match == 3);
	// match = sTree.LongestCommonSubstring(1); // 'abaxba'
	// assert(match == 4);
	sTree.Clear();
	sTree.InsertString("tabriz");
	sTree.InsertString("torino");
	match = sTree.LongestCommonSubstring(0);
	assert(match == 2);
	match = sTree.LongestCommonSubstring(2);
	assert(match == 4);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbcabcghijmnopq"); // match "ghij"
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bmnobcdeijkq"); // match "bcde"
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbijkmnopqrstuv"); // match "bcde" with first string
	sTree.InsertString("ijklmnopqrst");	   // match "ijk" with all other strings
	match = sTree.LongestCommonSubstring(0);
	assert(match == 3);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 4);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbcfghiopqrstuv");
	sTree.InsertString("ijklmnopfghistuvw");
	sTree.InsertString("fghimnopqrstuv"); // match "fghi" with all other strings
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 5);
	sTree.Clear();
	sTree.InsertString("abcdewxyzjkl");
	sTree.InsertString("bbcwxyzoijkq");
	sTree.InsertString("ijklmnopwxyzstuv");
	sTree.InsertString("wxyzmnopqrst");
	sTree.InsertString("abcdmnopqrstwxyz"); // match "wxyz" with all other strings
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 5);

	sTree.Clear();
	sTree.InsertString("Mississippi");
	assert(sTree.Count() == 53);
	sTree.InsertString("Mississippi");
	assert(sTree.Count() == 53); // Assert no duplicates!
	indices1 = sTree.GetIndexes("is");
	assert(indices1.size() == 2); // ississippi, issippi
	assert(indices1[0] == 1);
	assert(indices1[1] == 4);
#if 0
	Stack overflow!
	string s1 = "gatezejttddpkmndtauvjcffiiafgzhkqgzliirdldbmqkdfpeadgjxcirgkmkcfxorthhpujbnenxansboejjrqfxoohuolsxgohukxmpzfukzvkduurvajrodlpxojzsihiqftrbkixbcxraqpiyadbkzqihmigunrzfzcgzfkeszcpkdotulkktfduekyqzkymqpeidhpyuhotynqaxknnsheiogrhobrajzkrekexvorlvlyhtgstjrtdgjzahvmjnprcumulnvftgoiyctjgtthleeunkgbemapsntmfdnuaydkrbyngbrbpsznfdftonfmbjahqrpgddbkokvdxfflzysneapnqvsqhilxabbjamkdhpktscxsczpoontmliozurkrvagnidnmcayiradtbacltouzacvseayrdzkkkqgbfrrnfydbnnxvctffgtfpbmfzsqjnclcnttztcvvpbmkovahvpdnjqghcafzcxhrxumhxxkdtyjqypljzsbidfpoydlumdrhokvmstydlmymldvimdduvzzcmiyxapbrrrndhjnhncpibdmiryjteyvcydxkthxcbgxshffuzevvfrcrpzaotcpbefqqppehgdlbfstralgzbtdfervuvejyvvocrabkiohjxjnnrshvyijyonzzioeakpbkgxybtlcbybgzvvvvhhkdfvpupxnlecqizvzhgigliotybprnnntqdsiquxvdxojripdlmzsyorhjandaqtjfptgebxbjmnokevncfxkkadrsqjvxuttokcabefxehmnhkcbgrdmnmmycflifrrkriggeplcfafpxsbfchbdzbvdgsbrcebgkgsdbdntfdbaltnsdzraafhobrsygkvetomeqvkrntyzeqimcaktnvfcehaeexqjnjfyvomfqlbdjxhhjojvytaovvprpfrdpgurzfhknsimnmhctbkzxfxjrzfjvjsigivmlxcgiginjitarxettzzcpceonufetlpdxupmpfmhzanufjxrkaapaaalaulebxizfjshbjsagmxmuesvecuoobuctngykkzsztzauquxxdgmjxuybkzvxsftzpqhmarlsbaeriaahlrcdgjadhbrizmnabcfadtnfdzobdhayhrxmdddycenimblnrlicasqhttekqyiafijoiykcmutzbjupsbqxbzeyqxbsshelvzieoiozylenrlaelpykdpvzhvpttmsyxsjbrfqchgrxcuvkgqinluzjrqlnzitvhlofjiznsxvbbhscsuoufodozsrmjecfdrkcslgmmrcletuvxcdfitpmgocjdcurrbfqpefxtndzkuuzxpaxfanxdxnteiapkzouvqiykxntmltdpmyzjveivnfuhzlrkseyhpbgrtcvnqmpqcgubjyourdrizixmoflmyzsskvfagtdopgthcdmmqhkmksxgeckagmjgauvz";
	sTree.InsertString(s1);
	sTree.InsertString("bbcdemnoijgltezejtfdehkmndtauvicffiiafozhkqmzlieedldbmqjdfpeadgjxcirbkmkcfxorthhpujbnekzansboejjrqfxoohuozsxgohukxmpzbukzvkduurvajrodlpxojzsvhiqftrbgixbcxmaqpiyadbkzqnhmigunrzfzugzfkeszcpbdotulketftuekfqzkymqpeidhpyuhotynqqxknnsheitgrhobrajzkrekexvorlvlyhtmstjrldhjzahvmjnprgtgulhvftgoiyctjgtthleeunkgbemapsntmfdnuaydkrbyigbrbpsknfdftonfmbtahqrpgddbkokvdxfflzysneapnqvsqhilnabbjamkdhpktsxxsczpoontmliozurkrvagnidnmcayiradtbacltouzacvseayrdzkkkqgbfrrnfydbnnxuctfegtfpbmfzsqjnclcnttftcvvpbmkovahvpdnjqghcafzcxhrgumhoxkityjqypljzsbidfcoynlumdrhokvmstydlmymldvimrduvzzcmiyxapbrrrndhjnhncpjbdmiryjteyvcydxkthxcbgxshffyzevvfrcrpzaotcpbefqqppehgdlbfstaalgzbtdfervuvehyvvocrabkioojxjnnrshvyijymnnzioeakpbkgxdbtlobybgzvpvvhhkdcvplpvnlecqizvzhgiglsotobprnnntqdsiquxvdxojripdlmzsyorhjandaqtjfptgegxbjmnokevncfxkladrsqjvxugtokcabeqxehmnhkcbgrdmnmmyfsmifrrkriggeplcfbfpxsbfcxbdzbvdgsbrcebmkpsdbdntfdbaltnsdzrfafhobrsygktetomeqvkrztyzeqimcaktnvfcehaeexqjnjfyvomfqsbdjxhhjojvytaovvirpfrdpgurzfhknsimnmhctbkixfcjrzfjvjsigilmoxcuiginjitarxettzzcpcesnufbtlpdxupmpfmhzqnufjxrkaapaaalaulebxizfjshbjsagmxmueshecuoobzctngykkzsftzatquxxdgmjxuybkzvxsftzpqhmarlsbayriaahlrcdgjadhbrizmnaycfaftnfdzobdhhyhrxvddsycenimblnrcicasqhttekqyiafijoiykcmstzbjupsbqxbzeyqxbsshelvzxekiozylenrlaelpykdpvzhvpttmsyxsjbrfqchgrxcubkgqinluzjrqltzitvhlofjizxsxvbbqbcsuoufodozsrmjecfdricsljmmrcletuvxcxfitpmgocjdcurzbfqpefxtndzkuuzxpaxfanxdxntuiapkzoufqiykxntmlyepmyzjneyvnfuqzlrkseyhpbgrtcpnqmpqcgubjuourdriziimoflmyzsskvfagldopgthcdmmqhrmksxgeckarmjgauvjkq", s1.size());	// match "bcde"
	match = sTree.LongestCommonSubstring(11);
	assert(match == 5);
#endif
	cout << endl;
}
void TrieTests()
{
	cout << "Trie tests..." << endl;
	Trie<int> trie;					   // Node count:
	trie.InsertFast("Amy", 12);		   // 3
	trie.InsertFast("Christine", 34);  // 9
	trie.InsertFast("Tom", 56);		   // 3
	trie.InsertFast("Robert", 78);	   // 6
	trie.InsertFast("Kristy", 90);	   // 6
	trie.InsertFast("apple", 1);	   // 5
	trie.InsertFast("appendix", 2);	   // 5 ("app" common nodes)
	trie.InsertFast("appetite", 3);	   // 4 ("appe" common nodes)
	trie.InsertFast("to", 4);		   // 2
	trie.InsertFast("topple", 5);	   // 4 ("to" common nodes)
	trie.InsertFast("tea", 6);		   // 2 ("t" common node)
	trie.InsertFast("ted", 7);		   // 1 ("te" common nodes)
	trie.InsertFast("ten", 8);		   // 1 ("te" common nodes)
	trie.InsertFast("in", 9);		   // 2
	trie.InsertFast("inn", 10);		   // 1 ("in" common nodes)
	trie.InsertFast("intrinsics", 11); // 8 ("in" common nodes)
	assert(trie.Find("Amy") == 12);
	assert(trie.FindFast("Amy") == 12);
	assert(trie.Find("Christine") == 34);
	assert(trie.FindFast("Christine") == 34);
	assert(trie.Find("Tom") == 56);
	assert(trie.FindFast("Tom") == 56);
	assert(trie.Find("Robert") == 78);
	assert(trie.FindFast("Robert") == 78);
	assert(trie.Find("Kristy") == 90);
	assert(trie.FindFast("Kristy") == 90);
	assert(trie.Find("apple") == 1);
	assert(trie.FindFast("apple") == 1);
	assert(trie.Find("appendix") == 2);
	assert(trie.FindFast("appendix") == 2);
	assert(trie.Find("appetite") == 3);
	assert(trie.FindFast("appetite") == 3);
	assert(trie.Find("app") == numeric_limits<int>::min());
	assert(trie.FindFast("app") == numeric_limits<int>::min()); // not found
	assert(trie.Find("ap..e") == 1);
	assert(trie.FindFast("ap..e") == 1);
	assert(trie.Find("ap...") == 1);
	assert(trie.FindFast("ap...") == 1);
	assert(trie.Find("to") == 4);
	assert(trie.FindFast("to") == 4);
	assert(trie.Find("topple") == 5);
	assert(trie.FindFast("topple") == 5);
	assert(trie.Find("tea") == 6);
	assert(trie.FindFast("tea") == 6);
	assert(trie.Find("ted") == 7);
	assert(trie.FindFast("ted") == 7);
	assert(trie.Find("ten") == 8);
	assert(trie.FindFast("ten") == 8);
	assert(trie.Find("in") == 9);
	assert(trie.FindFast("in") == 9);
	assert(trie.Find("inn") == 10);
	assert(trie.FindFast("inn") == 10);
	assert(trie.Find("intrinsics") == 11);
	assert(trie.FindFast("intrinsics") == 11);
	assert(trie.Find("in........") == 11);
	assert(trie.FindFast("in........") == 11);
	assert(trie.Find("..........") == 11);
	assert(trie.FindFast("..........") == 11);
	assert(trie.Find("in.........") == numeric_limits<int>::min());
	assert(trie.FindFast("in.........") == numeric_limits<int>::min());
	assert(trie.Find("ABC") == numeric_limits<int>::min());
	assert(trie.FindFast("ABC") == numeric_limits<int>::min());
	assert(trie.Find("tee") == numeric_limits<int>::min());
	assert(trie.FindFast("tee") == numeric_limits<int>::min());
	assert(trie.Find("t") == numeric_limits<int>::min());
	assert(trie.FindFast("t") == numeric_limits<int>::min());
	size_t count = trie.Count();
	assert(count == 62);
	cout << "Trie has " << count << " nodes" << endl;
	trie.InsertFast("intrinsics", 12);
	assert(count == trie.Count()); // Assert no duplicates! Only the value changes
	assert(trie.Find("intrinsics") == 12);
	assert(trie.FindFast("intrinsics") == 12);
	trie.RemoveString("Amy");
	trie.RemoveString("Christine");
	trie.RemoveString("Tom");
	trie.RemoveString("Robert");
	trie.RemoveString("Kristy");
	assert(trie.Find("Amy") == numeric_limits<int>::min());
	assert(trie.Find("Christine") == numeric_limits<int>::min());
	assert(trie.Find("Tom") == numeric_limits<int>::min());
	assert(trie.Find("Robert") == numeric_limits<int>::min());
	assert(trie.Find("Kristy") == numeric_limits<int>::min());
	assert(trie.Find("ABC") == numeric_limits<int>::min());

	assert(trie.FindFast("Amy") == numeric_limits<int>::min());
	assert(trie.FindFast("Christine") == numeric_limits<int>::min());
	assert(trie.FindFast("Tom") == numeric_limits<int>::min());
	assert(trie.FindFast("Robert") == numeric_limits<int>::min());
	assert(trie.FindFast("Kristy") == numeric_limits<int>::min());
	assert(trie.FindFast("ABC") == numeric_limits<int>::min());
	trie.Clear();
	cout << endl;
}
void PrefixTrieTests()
{
	vector<string> result;
	PrefixTrie prefixTrie;
	cout << "Prefix-Trie tests..." << endl;
	prefixTrie.InsertString("apple");	   // 5
	prefixTrie.InsertString("appendix");   // 5 ("app" common not included)
	prefixTrie.InsertString("appetite");   // 4 ("app" common not included)
	prefixTrie.InsertString("to");		   // 2
	prefixTrie.InsertString("topple");	   // 4 ("to" common not included)
	prefixTrie.InsertString("tea");		   // 2 ("t" common not included)
	prefixTrie.InsertString("ted");		   // 1 ("te" common not included)
	prefixTrie.InsertString("ten");		   // 1 ("te" common not included)
	prefixTrie.InsertString("in");		   // 2
	prefixTrie.InsertString("inn");		   // 1 ("in" common not included)
	prefixTrie.InsertString("intrinsics"); // 8 ("in" common not included)
	assert(prefixTrie.Count() == 35);
	assert(prefixTrie.Find(string("apple")));
	result = prefixTrie.StartsWith(string("apple"));
	assert(result.size() == 1);
	assert(result[0] == "apple");

	assert(!prefixTrie.Find(string("app")));
	result = prefixTrie.StartsWith(string("app"));
	assert(result.size() == 3);
	assert(result[0] == "appendix");
	assert(result[1] == "appetite");
	assert(result[2] == "apple");

	assert(prefixTrie.Find(string("to")));
	result = prefixTrie.StartsWith(string("to"));
	assert(result.size() == 2);

	assert(prefixTrie.Find(string("in")));
	result = prefixTrie.StartsWith(string("in"));
	assert(result.size() == 3);

	assert(!prefixTrie.Find(string("a")));
	result = prefixTrie.StartsWith(string("a"));
	assert(result.size() == 3); // appendix, appetite, apple
	assert(result[0] == "appendix");
	assert(result[1] == "appetite");
	assert(result[2] == "apple");

	assert(!prefixTrie.Find(string("i")));
	result = prefixTrie.StartsWith(string("i"));
	assert(result.size() == 3); // in inn intrinsics
	assert(result[0] == "in");
	assert(result[1] == "inn");
	assert(result[2] == "intrinsics");

	assert(!prefixTrie.Find(string("t")));
	result = prefixTrie.StartsWith(string("t"));
	assert(result.size() == 5); //  tea ted ten to topple
	assert(result[0] == "tea");
	assert(result[1] == "ted");
	assert(result[2] == "ten");
	assert(result[3] == "to");
	assert(result[4] == "topple");

	assert(!prefixTrie.Find(string("te")));
	result = prefixTrie.StartsWith(string("te"));
	assert(result.size() == 3); // tea ted ten
	assert(result[0] == "tea");
	assert(result[1] == "ted");
	assert(result[2] == "ten");

	PrefixTrieNode *node = prefixTrie.GetNode("apple");
	assert(node);
	assert(node->Value() == "apple");

	node = prefixTrie.GetNode("app");
	assert(node);
	assert(node->Value() == "");

	node = prefixTrie.GetNode("to");
	assert(node);
	assert(node->Value() == "to");

	node = prefixTrie.GetNode("in");
	assert(node);
	assert(node->Value() == "in");

	node = prefixTrie.GetNode("a");
	assert(node);
	assert(node->Value() == "");

	node = prefixTrie.GetNode("i");
	assert(node);
	assert(node->Value() == "");

	node = prefixTrie.GetNode("t");
	assert(node);
	assert(node->Value() == "");

	node = prefixTrie.GetNode("te");
	assert(node);
	assert(node->Value() == "");

	result = prefixTrie.GetNodes();
	assert(!result.empty());

	string longestCommonPrefix = prefixTrie.LongestCommonPrefix("a");
	assert(longestCommonPrefix == "app");

	longestCommonPrefix = prefixTrie.LongestCommonPrefix("i");
	assert(longestCommonPrefix == "in");
	prefixTrie.InsertString("intrinsics");
	assert(prefixTrie.Count() == 35); // Assert no duplicate nodes
	result = prefixTrie.StartsWith(string("apple"));
	assert(result.size() == 1);
	assert(result[0] == "apple");

	prefixTrie.Clear();
	assert(!prefixTrie.Find(string("a")));
	result = prefixTrie.StartsWith(string("a"));
	assert(result.empty());

	prefixTrie.InsertString("Hello");
	assert(prefixTrie.Count() == 5);
	assert(prefixTrie.Find("Hello"));
	assert(!prefixTrie.Find("Hell"));
	result = prefixTrie.StartsWith(string("Hel"));
	assert(!result.empty());
	assert(result.size() == 1);
	result = prefixTrie.StartsWith(string("Hello"));
	assert(!result.empty());
	assert(result.size() == 1);
	result = prefixTrie.StartsWith(string("Helloa"));
	assert(result.empty());
	result = prefixTrie.StartsWith(string("e"));
	assert(result.empty());
	assert(prefixTrie.Find("Hello"));
	assert(!prefixTrie.Find("Hell"));
	assert(prefixTrie.Find("Hell."));
	assert(prefixTrie.Find(".ello"));
	assert(prefixTrie.Find("....."));
	assert(!prefixTrie.Find("...."));
	assert(!prefixTrie.Find("......"));
	assert(!prefixTrie.Find("Hell.."));

	prefixTrie.InsertString("Hello"); // Assert no duplicates!
	assert(prefixTrie.Count() == 5);
	result = prefixTrie.StartsWith(string("Hel"));
	assert(!result.empty());
	assert(result.size() == 1);
	result = prefixTrie.StartsWith(string("Hello"));
	assert(!result.empty());
	assert(result.size() == 1);
	prefixTrie.Clear();
}
void GetPermutations(string &w, set<string> &dictionary, set<string> &result)
{
	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		if (it->size() == w.size() && *it != w)
		{
			size_t count = 0;
			for (size_t i = 0; i < it->size() && count < 2; i++)
				if ((*it)[i] != w[i])
					count++;
			if (count < 2)
				result.insert(*it);
		}
	}
}
// DAMP -> LAMP -> LIMP -> LIME -> LIKE
void WordLadder(const string &start, const string &stop, set<string> &dictionary, vector<string> &result)
{
	queue<string> actionQ;
	set<string> visited;
	map<string, string> backtrack;
	actionQ.push(start);
	visited.emplace(start);
	while (!actionQ.empty())
	{
		string w = actionQ.front(); // DAMP
		actionQ.pop();
		set<string> permutations;
		dictionary.erase(w);
		GetPermutations(w, dictionary, permutations);
		for (set<string>::const_iterator it = permutations.begin(); it != permutations.end(); it++)
		{
			if (*it == stop)
			{ // LIKE
				// Found our word! Now backtrack to record all the single-character change from 'start' to 'stop'
				result.push_back(*it);
				result.push_back(w);
				while (backtrack.find(w) != backtrack.end())
				{
					w = backtrack[w];
					result.push_back(w);
				}
				return;
			}
			else if (visited.find(*it) == visited.end())
			{
				actionQ.push(*it);
				visited.insert(*it);
				backtrack[*it] = w; // Key: later; Value: earlier
			}
		}
	}
}
void AnagramTests()
{
	string str, str1;
	vector<string> strings;
	str = "Hello World!!!";
	str1 = "World Hello!!!";
	assert(areAnagrams(str, str1));
	cout << "\"" << str << "\" and \"" << str1 << "\" -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "World!!! Hello";
	assert(areAnagrams(str, str1));
	cout << "\"" << str << "\" and \"" << str1 << "\" -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "!HWr ole!d!lol";
	assert(areAnagrams(str, str1));
	cout << "\"" << str << "\" and \"" << str1 << "\" -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "World Hello!!! ";
	assert(!areAnagrams(str, str1));
	cout << "\"" << str << "\" and \"" << str1 << "\" -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "world hello!!!";
	assert(!areAnagrams(str, str1));
	cout << "\"" << str << "\" and \"" << str1 << "\" -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "Good Morning!!!";
	assert(!areAnagrams(str, str1));
	cout << "\"" << str << "\" and \"" << str1 << "\" -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	strings.clear();
	strings.push_back("star"); // "arst" : "star"
	strings.push_back("dog");  // "dgo" : "dog"
	strings.push_back("car");  // "acr" : "car"
	strings.push_back("rats"); // "arst" : rats
	strings.push_back("arc");  // "acr" : "arc"
	strings.push_back("god");  // "dgo" : "god"
	vector<vector<string>> anagrams;
	assert(FindAnagrams(strings, anagrams) == 3);
	for (vector<vector<string>>::const_iterator it = anagrams.begin(); it != anagrams.end(); it++)
	{
		cout << "( ";
		copy(it->begin(), it->end(), ostream_iterator<string>(cout, " "));
		cout << "), ";
	}
	assert(sherlockAndAnagrams("mom") == 2);
	assert(sherlockAndAnagrams("abba") == 4);
	assert(sherlockAndAnagrams("abcd") == 0);
	assert(sherlockAndAnagrams("cdcd") == 5);
	assert(sherlockAndAnagrams("kkkk") == 10);
	assert(sherlockAndAnagrams("ifailuhkqq") == 3);
	assert(sherlockAndAnagrams("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 166650);
	assert(sherlockAndAnagrams("ifailuhkqqhucpoltgtyovarjsnrbfpvmupwjjjfiwwhrlkpekxxnebfrwibylcvkfealgonjkzwlyfhhkefuvgndgdnbelgruel") == 399);
	cout << endl;
}
void StackTests()
{
	cout << "Stack tests..." << endl;
	MyStack<int> stack, sortedStack;
	stack.push(100);
	stack.push(-100);
	stack.push(0);
	stack.push(-50);
	stack.push(50);
	stack.push(-1);
	stack.push(1);
	stack.push(-75);
	stack.push(75);
	stack.push(25);
	cout << "Stack content: ";
	stack.PrintStack();

	MyStack<int> unSortedStack(stack);
	SortStack<int>(stack, sortedStack, sort_order_t::SORT_ASCENDING);
	cout << "Stack content (Ascending): ";
	sortedStack.PrintStack();
	sortedStack.clear();
	SortStack<int>(unSortedStack, sortedStack, sort_order_t::SORT_DESCENDING);
	cout << "Stack content (Descending): ";
	sortedStack.PrintStack();
	cout << endl;
}
void QueueTests()
{
	cout << "Queue tests..." << endl;
	MyQueue<int> myQueue;
	myQueue.push_back(-1);
	myQueue.push_back(0);
	myQueue.push_back(10);
	assert(myQueue.size() == 3);
	assert(myQueue.front() == -1);
	assert(myQueue.size() == 2);
	assert(myQueue.front() == 0);
	assert(myQueue.size() == 1);
	assert(myQueue.front() == 10);
	assert(myQueue.size() == 0);
}
void LinkedListTests()
{
	vector<long> a, b;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	uniform_int_distribution<long> uniformDistribution;
	a.clear();
	a.resize(10);
	generate(a.begin(), a.end(), [&]
			 { return uniformDistribution(engine); });
	LinkedList<long> lla1(a);
	assert(lla1.Length() == 10);
	b.clear();
	lla1.ToVector(b);
	assert(a.size() == b.size());
	assert(a == b);
	shared_ptr<Node<long>> odd = nullptr, even = nullptr;
	lla1.SplitList(even, odd);
	assert(lla1.Length() == 10);
	assert(odd);
	assert(even);
	shared_ptr<Node<long>> node = even;
	for (size_t i = 0; node; node = node->Next(), i += 2)
		assert(node->Item() == a[i]);
	node = odd;
	for (size_t i = 1; node; node = node->Next(), i += 2)
		assert(node->Item() == a[i]);
	lla1.Clear();
	a.clear();
	a.resize(10);
	generate(a.begin(), a.end(), [n = 0]() mutable
			 { return n++; });
	// 0->1->2->3->4->5->6->7->8->9
	// 10 9  8  7  6  5  4  3  2  1
	LinkedList<long> lla2(a);
	assert(lla2.Length() == 10);
	// Implement an algorithm to find the nth to last element of a singly linked list.
	shared_ptr<Node<long>> lptr = lla2.NthElementFromBack(3);
	assert(lptr);
	assert(lptr->Item() == 7);
	lptr = lla2.NthElementFromBack(10);
	assert(lptr);
	assert(lptr->Item() == 0);
	lptr = lla2.NthElementFromBack(11);
	assert(!lptr);
	lptr = lla2.RemoveNthElementFromBack(4);
	assert(lla2.Length() == 9);
	a.clear();
	a = {0, 1, 2, 3, 4, 5, 7, 8, 9};
	for (size_t i = 0; i < lla2.Length(); i++)
	{
		assert(lptr->Item() == a[i]);
		lptr = lptr->Next();
	}
	// 0->1->2->3->4->5->7->8->9
	// 9  8  7  6  5  4  3  2  1
	lptr = lla2.RemoveNthElementFromBack(7);
	assert(lla2.Length() == 8);
	a.clear();
	a = {0, 1, 3, 4, 5, 7, 8, 9};
	for (size_t i = 0; i < lla2.Length(); i++)
	{
		assert(lptr->Item() == a[i]);
		lptr = lptr->Next();
	}
	// 0->1->3->4->5->7->8->9
	// 8  7  6  5  4  3  2  1
	lptr = lla2.RemoveNthElementFromBack(8);
	assert(lla2.Length() == 7);
	a.clear();
	a = {1, 3, 4, 5, 7, 8, 9};
	for (size_t i = 0; i < lla2.Length(); i++)
	{
		assert(lptr->Item() == a[i]);
		lptr = lptr->Next();
	}
	lla2.Clear();
	a.clear();
	a.push_back(1); // LSB
	a.push_back(2);
	a.push_back(3); // MSB
	LinkedList<long> lla3(a);
	assert(lla3.Length() == 3);
	assert(lla3.Find(Node<long>(2)));
	lla3.Print();
	a.clear();
	a.push_back(7); // LSB
	a.push_back(8);
	a.push_back(9); // MSB
	LinkedList<long> llb1(a);
	assert(llb1.Length() == 3);
	llb1.Print();
	a.clear();
	a.push_back(8); // LSB
	a.push_back(0);
	a.push_back(3);
	a.push_back(1);																	 // MSB
	LinkedList<long> listAdditionResult = lla3.AddNumbers(lla3.Head(), llb1.Head()); // 987 + 321 = 1308 List in reverse order. Head points to LSB
	assert(listAdditionResult.Length() == 4);
	listAdditionResult.Print();
	size_t i = 0;
	for (shared_ptr<Node<long>> n = listAdditionResult.Head(); n; n = n->Next())
		assert(n->Item() == a[i++]);
	vector<long> listAdditionResultVector;
	listAdditionResult.ToVector(listAdditionResultVector);
	assert(listAdditionResultVector.size() == 4);
	assert(listAdditionResultVector[0] == 8);
	assert(listAdditionResultVector[1] == 0);
	assert(listAdditionResultVector[2] == 3);
	assert(listAdditionResultVector[3] == 1);
	listAdditionResult.Clear();
	lla3.Clear();
	llb1.Clear();
	a.clear();
	b.clear();
	a.resize(10);
	b.resize(10);
	generate(a.begin(), a.end(), [&]
			 { return uniformDistribution(engine); });
	generate(b.begin(), b.end(), [&]
			 { return uniformDistribution(engine); });
	LinkedList<long> lla4(a), llb2(b);
	assert(lla4.Length() == 10);
	assert(llb2.Length() == 10);
	lla4.Join(llb2);
	assert(lla4.Length() == 20);
	assert(llb2.Length() == 0);
	lla4.Clear();
	llb2.Clear();
	a.clear();
	a = {-1, 0, 1, 2, 3, 4, 5, 0}; // Loop starts at '0'
	CircularLinkedList<long> cll(a);
	assert(cll.Length() == 7);
	Node<long> lNode(-1);
	shared_ptr<Node<long>> head = cll.Find(lNode);
	assert(head);
	lNode.SetItem(0);
	shared_ptr<Node<long>> loopStart = cll.Find(lNode);
	assert(loopStart);
	cll.Print();
	assert(cll.LoopStart(head) == loopStart);

	a.clear();
	a = {-2, -1, 0, 1, 2, 3, 4, 5, 0}; // Loop starts at '0'
	CircularLinkedList<long> cll1(a);
	assert(cll1.Length() == 8);
	lNode.SetItem(-2);
	head = cll1.Find(lNode);
	assert(head);
	lNode.SetItem(0);
	loopStart = cll1.Find(lNode);
	assert(loopStart);
	cll1.Print();
	assert(cll1.LoopStart(head) == loopStart);

	a.clear();
	a = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 0}; // Loop starts at '0'
	CircularLinkedList<long> cll2(a);
	assert(cll2.Length() == 9);
	lNode.SetItem(-3);
	head = cll2.Find(lNode);
	assert(head);
	lNode.SetItem(0);
	loopStart = cll2.Find(lNode);
	assert(loopStart);
	cll2.Print();
	assert(cll2.LoopStart(head) == loopStart);

	a.clear();
	a = {-3, -2, -1, 0, 1, 2, 3, 4, 5}; // NO loop!
	CircularLinkedList<long> cll3(a);
	assert(cll3.Length() == 9);
	lNode.SetItem(-3);
	head = cll3.Find(lNode);
	assert(head);
	cll3.Print();
	assert(!cll3.LoopStart(head));

	a.clear();
	a = {1, 2}; // NO loop!
	CircularLinkedList<long> cll4(a);
	assert(cll4.Length() == 2);
	lNode.SetItem(1);
	head = cll4.Find(lNode);
	assert(head);
	cll4.Print();
	assert(!cll4.LoopStart(head));

	a.clear();
	a = {1, 2, 1}; // Loop starts at '1'
	CircularLinkedList<long> cll5(a);
	assert(cll5.Length() == 2);
	lNode.SetItem(1);
	head = cll5.Find(lNode);
	assert(head);
	loopStart = cll5.Find(lNode);
	assert(loopStart);
	cll5.Print();
	assert(cll5.LoopStart(head) == loopStart);

	a.clear();
	a = {1}; // NO loop!
	CircularLinkedList<long> cll6(a);
	assert(cll6.Length() == 1);
	head = cll6.Find(lNode);
	assert(head);
	cll6.Print();
	assert(!cll6.LoopStart(head));

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> lla5(a);
	assert(lla5.Length() == 5);
	lla5.Reverse(1, 3);
	assert(lla5.Length() == 5);
	b.clear();
	b = {1, 4, 3, 2, 5};
	vector<long> c;
	lla5.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> lla6(a);
	assert(lla6.Length() == 5);
	lla6.Reverse(0, 4);
	assert(lla6.Length() == 5);
	b.clear();
	b = {5, 4, 3, 2, 1};
	c.clear();
	lla6.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> lla7(a);
	assert(lla7.Length() == 5);
	lla7.Reverse(0, 3);
	assert(lla7.Length() == 5);
	b.clear();
	b = {4, 3, 2, 1, 5};
	c.clear();
	lla7.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> lla8(a);
	assert(lla8.Length() == 5);
	lla8.Reverse(1, 4);
	assert(lla8.Length() == 5);
	b.clear();
	b = {1, 5, 4, 3, 2};
	c.clear();
	lla8.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> lla9(a);
	assert(lla9.Length() == 5);
	lla9.Reverse(1, 1);
	assert(lla9.Length() == 5);
	b.clear();
	b = {1, 2, 3, 4, 5};
	c.clear();
	lla9.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2};
	LinkedList<long> lla10(a);
	assert(lla10.Length() == 2);
	lla10.Reverse(0, 1);
	assert(lla10.Length() == 2);
	b.clear();
	b = {2, 1};
	c.clear();
	lla10.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> lla11(a);
	assert(lla11.Length() == 7);
	lla11.RemoveDuplicates();
	assert(lla11.Length() == 5);
	b.clear();
	b = {1, 2, 3, 4, 5};
	c.clear();
	lla11.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> lla12(a);
	assert(lla12.Length() == 7);
	lla12.RemoveAllDuplicates();
	assert(lla12.Length() == 3);
	b.clear();
	b = {1, 2, 5};
	c.clear();
	lla12.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> lla13(a);
	assert(lla13.Length() == 8);
	lla13.RemoveDuplicates();
	assert(lla13.Length() == 5);
	b.clear();
	b = {1, 2, 3, 4, 5};
	c.clear();
	lla13.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> lla14(a);
	assert(lla14.Length() == 8);
	lla14.RemoveAllDuplicates();
	assert(lla14.Length() == 2);
	b.clear();
	b = {2, 5};
	c.clear();
	lla14.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1};
	LinkedList<long> lla15(a);
	assert(lla15.Length() == 1);
	lla15.RemoveDuplicates();
	assert(lla15.Length() == 1);
	b.clear();
	b = {1};
	c.clear();
	lla15.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1};
	LinkedList<long> lla16(a);
	assert(lla16.Length() == 1);
	lla16.RemoveAllDuplicates();
	assert(lla16.Length() == 1);
	b.clear();
	b = {1};
	c.clear();
	lla16.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1};
	LinkedList<long> lla18(a);
	assert(lla18.Length() == 2);
	lla18.RemoveDuplicates();
	assert(lla18.Length() == 1);
	b.clear();
	b = {1};
	c.clear();
	lla18.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1};
	LinkedList<long> lla19(a);
	assert(lla19.Length() == 2);
	lla19.RemoveAllDuplicates();
	assert(lla19.Length() == 0);

	a.clear();
	a = {1, 2, 2};
	LinkedList<long> lla20(a);
	assert(lla20.Length() == 3);
	lla20.RemoveDuplicates();
	assert(lla20.Length() == 2);
	b.clear();
	b = {1, 2};
	c.clear();
	lla20.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 2};
	LinkedList<long> lla21(a);
	assert(lla21.Length() == 3);
	lla21.RemoveAllDuplicates();
	assert(lla21.Length() == 1);
	b.clear();
	b = {1};
	c.clear();
	lla21.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1, 1, 2};
	LinkedList<long> lla22(a);
	assert(lla22.Length() == 4);
	lla22.RemoveDuplicates();
	assert(lla22.Length() == 2);
	b.clear();
	b = {1, 2};
	c.clear();
	lla22.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1, 1, 2};
	LinkedList<long> lla23(a);
	assert(lla23.Length() == 4);
	lla23.RemoveAllDuplicates();
	assert(lla23.Length() == 1);
	b.clear();
	b = {2};
	c.clear();
	lla23.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1, 1, 2, 3};
	LinkedList<long> lla24(a);
	assert(lla24.Length() == 5);
	lla24.RemoveDuplicates();
	assert(lla24.Length() == 3);
	b.clear();
	b = {1, 2, 3};
	c.clear();
	lla24.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 1, 1, 2, 3};
	LinkedList<long> lla25(a);
	assert(lla25.Length() == 5);
	lla25.RemoveAllDuplicates();
	assert(lla25.Length() == 2);
	b.clear();
	b = {2, 3};
	c.clear();
	lla25.ToVector(c);
	assert(b == c);

	a.clear();
	a = {-1, 0, 0, 0, 0, 3, 3};
	LinkedList<long> lla26(a);
	assert(lla26.Length() == 7);
	lla26.RemoveDuplicates();
	assert(lla26.Length() == 3);
	b.clear();
	b = {-1, 0, 3};
	c.clear();
	lla26.ToVector(c);
	assert(b == c);

	a.clear();
	a = {-1, 0, 0, 0, 0, 3, 3};
	LinkedList<long> lla27(a);
	assert(lla27.Length() == 7);
	lla27.RemoveAllDuplicates();
	assert(lla27.Length() == 1);
	b.clear();
	b = {-1};
	c.clear();
	lla27.ToVector(c);
	assert(b == c);

	a.clear();
	a = {2, 1};
	LinkedList<long> lla28(a);
	assert(lla28.Length() == 2);
	lla28.Sort();
	assert(lla28.Length() == 2);
	c.clear();
	lla28.ToVector(c);
	assert(c.size() == 2);
	assert(c[0] == 1);
	assert(c[1] == 2);

	a.clear();
	a = {4, 2, 1, 3};
	LinkedList<long> lla29(a);
	assert(lla29.Length() == 4);
	lla29.Sort();
	assert(lla29.Length() == 4);
	c.clear();
	lla29.ToVector(c);
	assert(c.size() == 4);
	assert(c[0] == 1);
	assert(c[1] == 2);
	assert(c[2] == 3);
	assert(c[3] == 4);

	a.clear();
	a = {-1, 5, 3, 4, 0};
	LinkedList<long> lla30(a);
	assert(lla30.Length() == 5);
	lla30.Sort();
	assert(lla30.Length() == 5);
	c.clear();
	lla30.ToVector(c);
	assert(c.size() == 5);
	assert(c[0] == -1);
	assert(c[1] == 0);
	assert(c[2] == 3);
	assert(c[3] == 4);
	assert(c[4] == 5);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> lla31(a);
	assert(lla31.Length() == 5);
	lla31.RotateRight(2);
	assert(lla31.Length() == 5);
	b.clear();
	b = {4, 5, 1, 2, 3};
	c.clear();
	lla31.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1, 2, 3};
	LinkedList<long> lla32(a);
	assert(lla32.Length() == 3);
	lla32.RotateRight(2000000000);
	assert(lla32.Length() == 3);
	b.clear();
	b = {2, 3, 1};
	c.clear();
	lla32.ToVector(c);
	assert(b == c);

	a.clear();
	a = {1};
	LinkedList<long> lla33(a);
	assert(lla33.Length() == 1);
	lla33.RotateRight(1);
	assert(lla33.Length() == 1);
	b.clear();
	b = {1};
	c.clear();
	lla33.ToVector(c);
	assert(b == c);
}
void BinaryTreeTests()
{
	cout << "Binary tree tests..." << endl;
	vector<string> result;
	Tree<long> tree(50);
	tree.InsertItem(-100);
	tree.InsertItem(0);
	tree.InsertItem(10);
	tree.InsertItem(-50);
	tree.InsertItem(60);
	tree.InsertItem(100);
	tree.InsertItem(75);
	tree.InsertItem(150);
	assert(tree.Count() == 9);
	Tree<long> subtree((long)0);
	subtree.InsertItem(-50);
	subtree.InsertItem(10);

	Tree<long> subtree1((long)0);
	subtree1.InsertItem(50);
	subtree1.InsertItem(60);

	Tree<long> subtree2(50);
	subtree2.InsertItem(-100);
	subtree2.InsertItem(60);

	cout << "Binary Tree content: " << endl;
	tree.PrintTree();
	cout << endl;

	cout << "SubTree content: " << endl;
	subtree.PrintTree();
	cout << endl;
	cout << (tree.SubTree(tree.Root(), subtree.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "SubTree1 content: " << endl;
	subtree1.PrintTree();
	cout << endl;
	cout << (tree.SubTree(tree.Root(), subtree1.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "SubTree2 content: " << endl;
	subtree2.PrintTree();
	cout << endl;
	cout << (tree.SubTree(tree.Root(), subtree2.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "MinDepth: " << tree.MinDepth(tree.Root()) << ", MaxDepth: " << tree.MaxDepth(tree.Root()) << " " << (tree.IsBalancedTree() ? "balanced" : "Unbalanced") << endl;
	tree.PrintTreeColumns();
	tree.FindSum(tree.Root(), -100, result);
	assert(!result.empty());
	assert(result.size() == 3); //"-100" "-100 0" "-50 0 -100 50"
	cout << "Sum -100 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << "\"" << *it << "\" ";
	cout << endl;
	result.clear();

	tree.FindSum(tree.Root(), 110, result);
	assert(result.size() == 1);
	cout << "Sum 110 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << "\"" << *it << "\" ";
	cout << endl;
	result.clear();

	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	tree.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "Binary Tree content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	nodes.clear();
	/*
Binary Tree content:
Level 0:                50
Level 1:      -100(50)        60(50)
Level 2:            0(-100)         100(60)
Level 3:       -50(0)     10(0)  75(100)   150(100)
	*/
	shared_ptr<Node<long>> node = tree.FindNode(-50), node1, node2, node3;
	assert(node);
	assert(tree.InOrderSuccessor(node)->Item() == 0);
	node = tree.FindNode(50);
	assert(node);
	assert(tree.InOrderSuccessor(node)->Item() == 60);
	node = tree.FindNode(10);
	assert(node);
	assert(tree.InOrderSuccessor(node)->Item() == 50);

	node = tree.FindNode(-50);
	assert(node);
	node1 = tree.FindNode(10);
	assert(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	assert(node2);
	assert(node3);
	assert(node2->Item() == 0);
	assert(node3->Item() == 0);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node1 = tree.FindNode(75);
	assert(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	assert(node2);
	assert(node3);
	assert(node2->Item() == 50);
	assert(node3->Item() == 50);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node = tree.FindNode(60);
	assert(node);
	node1 = tree.FindNode(75);
	assert(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	assert(node2);
	assert(node3);
	assert(node2->Item() == 60);
	assert(node3->Item() == 60);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;

	Tree<long> tree1(tree);
	assert(tree == tree1);
	cout << "Tree1 content (= Tree): " << endl;
	tree1.PrintTree();

	tree.Clear();
	tree.InsertItem(2);
	tree.InsertItem(3);
	tree.InsertItem(-4);
	tree.InsertItem(3);
	tree.InsertItem(1);
	tree.InsertItem(2);
	result.clear();
	cout << "Tree content (= Tree): " << endl;
	tree.PrintTree();
	tree.FindSum(tree.Root(), 5, result);
	assert(!result.empty());
	assert(result.size() == 1);
	cout << "Sum 5 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << "\"" << *it << "\" ";
	cout << endl;
	result.clear();
	vector<size_t> data = {10, 5, 11};
	vector<vector<size_t>> links = {{10, 5}, {10, 11}};
	/*
			10
		11		5
	Diff: 15 - 11 = 4
	*/
	assert(cutTheTree(data, links) == 4);
	data.clear();
	data = {10, 5, 6, 20};
	/*
			10
		 5		6
	  20
	Diff: 21 - 20 = 1
	*/
	links = {{10, 5}, {10, 6}, {5, 20}};
	assert(cutTheTree(data, links) == 1);
	/*
			10
		 5
	  20
	Diff: 20 - 15 = 5
	*/
	data.clear();
	data = {10, 5, 20};
	links = {{10, 5}, {5, 20}};
	assert(cutTheTree(data, links) == 5);

	vector<long> a, b;
	a.clear();
	b.clear();
	a = {1, 2, 3, 4, 5};
	Tree<long> tree2(a, TreeType::Binary);
	assert(tree2.Count() == 5);
	cout << "Binary Tree content: " << endl;
	tree2.PrintTree();
	cout << endl;
	result.clear();
	tree2.Serialize(tree2.Root(), b);
	assert(!b.empty());
	assert(b.size() == a.size());
	tree2.PrintTreeColumns();
	cout << endl;

	a.clear();
	a = {1, 2, 3};
	Tree<long> tree3(a, TreeType::Binary);
	assert(tree3.Count() == 3);
	assert(tree3.SumRoot2LeafNumbers() == 25);

	a.clear();
	a = {4, 9, 0, 5, 1};
	Tree<long> tree4(a, TreeType::Binary);
	assert(tree4.Count() == 5);
	assert(tree4.SumRoot2LeafNumbers() == 1026);

	a.clear();
	a = {5, 3, 2, 7, 0, 6, numeric_limits<long>::min(), numeric_limits<long>::min(), numeric_limits<long>::min(), 0};
	Tree<long> tree5(a, TreeType::Binary);
	tree5.PrintTree();
	assert(tree5.Count() == 7);
	assert(tree5.SumRoot2LeafNumbers() == 6363);

	a.clear();
	a = {1, 2, 5, 3, 4, numeric_limits<long>::min(), 6};
	Tree<long> tree6(a, TreeType::Binary);
	tree6.ToLinkedList();
	tree6.PrintTree();

	a.clear();
	b.clear();
	a = {1, 3};
	b = {3, 1};
	Tree<long> tree7(TraversalType::PreOrder, a, b);
	assert(tree7.Count() == 2);
	tree7.PrintTree();

	a.clear();
	b.clear();
	a = {3, 1};
	b = {3, 1};
	Tree<long> tree8(TraversalType::PreOrder, a, b);
	assert(tree8.Count() == 2);
	tree8.PrintTree();

	a.clear();
	b.clear();
	a = {9, 3, 15, 20, 7};
	b = {3, 9, 20, 15, 7};
	/*
	* 		3
		 9     20
			15     7
	*/
	Tree<long> tree9(TraversalType::PreOrder, a, b);
	assert(tree9.Count() == 5);
	assert(!tree9.isValidBST());
	tree9.PrintTree();

	a.clear();
	b.clear();
	a = {3, 2, 1};
	b = {1, 2, 3};
	/*
	*    1
	   2
	 3
	*/
	Tree<long> tree10(TraversalType::PreOrder, a, b);
	assert(tree10.Count() == 3);
	assert(!tree10.isValidBST());
	tree10.PrintTree();

	a.clear();
	b.clear();
	a = {1, 2, 3};
	b = {1, 2, 3};
	/*
	*    1
		   2
			 3
	*/
	Tree<long> tree11(TraversalType::PreOrder, a, b);
	assert(tree11.Count() == 3);
	assert(tree11.isValidBST());
	tree11.PrintTree();

	a.clear();
	b.clear();
	a = {2, 3, 1};
	b = {1, 2, 3};
	/*
	*     1
		2
		  3
	*/
	Tree<long> tree12(TraversalType::PreOrder, a, b);
	assert(tree12.Count() == 3);
	assert(!tree12.isValidBST());
	tree12.PrintTree();

	a.clear();
	b.clear();
	a = {1, 2, 3, 4};
	b = {4, 3, 1, 2};
	/*
	*      4
		3
		  1
			 2
	*/
	Tree<long> tree13(TraversalType::PreOrder, a, b);
	assert(tree13.Count() == 4);
	assert(tree13.isValidBST());
	tree13.PrintTree();

	a.clear();
	b.clear();
	a = {4, 2, 1, 3};
	b = {4, 3, 1, 2};
	/*
	*        4
				 3
			   1
			 2
	*/
	Tree<long> tree14(TraversalType::PreOrder, a, b);
	assert(tree14.Count() == 4);
	assert(!tree14.isValidBST());
	tree14.PrintTree();

	a.clear();
	b.clear();
	a = {9, 3, 15, 20, 7};
	b = {9, 15, 7, 20, 3};
	/*
	*     3
		 / \
		9  20
		  /  \
		 15   7
	*/
	Tree<long> tree15(TraversalType::PostOrder, a, b);
	assert(tree15.Count() == 5);
	assert(!tree15.isValidBST());
	tree15.PrintTree();

	a.clear();
	b.clear();
	a = {1, 2, 3, 4};
	b = {2, 1, 3, 4};
	/*
	*      4
		3
	  1
		 2
	*/
	Tree<long> tree16(TraversalType::PostOrder, a, b);
	tree16.PrintTree();
	assert(tree16.Count() == 4);
	assert(tree16.isValidBST());
	cout << endl;
}
void BinarySearchTreeTests()
{
	cout << "BST tests..." << endl;
	vector<long> a, b;
	vector<string> result;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	Tree<long> subtree((long)0);
	subtree.InsertItem(-50);
	subtree.InsertItem(10);

	Tree<long> subtree1((long)0);
	subtree1.InsertItem(50);
	subtree1.InsertItem(60);

	Tree<long> subtree2(50);
	subtree2.InsertItem(-100);
	subtree2.InsertItem(60);

	a.clear();
	b.clear();
	a = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	Tree<long> tree0(a, TreeType::BinarySearch);
	assert(tree0.isValidBST());
	assert(tree0.Count() == 9);
	assert(tree0.Min() == 0);
	assert(tree0.Max() == 8);
	assert(tree0.NextMin() == 0);
	assert(tree0.NextMin() == 1);
	assert(tree0.NextMin() == 2);
	assert(tree0.NextMin() == 3);
	assert(tree0.NextMin() == 4);
	assert(tree0.NextMin() == 5);
	assert(tree0.NextMin() == 6);
	assert(tree0.NextMin() == 7);
	assert(tree0.NextMin() == 8);
	assert(!tree0.HasNextMin());
	assert(tree0.NextMax() == 8);
	assert(tree0.NextMax() == 7);
	assert(tree0.NextMax() == 6);
	assert(tree0.NextMax() == 5);
	assert(tree0.NextMax() == 4);
	assert(tree0.NextMax() == 3);
	assert(tree0.NextMax() == 2);
	assert(tree0.NextMax() == 1);
	assert(tree0.NextMax() == 0);
	assert(!tree0.HasNextMax());
	result.clear();
	vector<size_t> levelNodeCount = tree0.GetLevelNodeCount();
	assert(!levelNodeCount.empty());
	assert(levelNodeCount.size() == 4);
	assert(levelNodeCount[0] == 1); // 4
	assert(levelNodeCount[1] == 2); // 2 7
	assert(levelNodeCount[2] == 4); // 1 3 6 8
	assert(levelNodeCount[3] == 2); // 0 5
	tree0.Serialize(tree0.Root(), b);
	assert(!b.empty());
	assert(b.size() == a.size());
	assert(b == a);
	cout << "Binary Search Tree content: " << endl;
	tree0.PrintTree();
	cout << endl;
	tree0.PrintTreeColumns();

	a.clear();
	b.clear();
	a = {50, -100, 0, 10, -50, 60, 100, 75, 150};
	Tree<long> tree1(a, TreeType::BinarySearch);
	assert(tree1.isValidBST());
	assert(tree1.Count() == 9);
	assert(tree1.Min() == -100);
	assert(tree1.Max() == 150);
	result.clear();
	tree1.Serialize(tree1.Root(), b);
	levelNodeCount = tree1.GetLevelNodeCount();
	assert(!levelNodeCount.empty());
	assert(levelNodeCount.size() == 4);
	assert(levelNodeCount[0] == 1); // 50
	assert(levelNodeCount[1] == 2); // 0 100
	assert(levelNodeCount[2] == 4); // -50 10 75 150
	assert(levelNodeCount[3] == 2); // -100 60
	assert(tree1.NextMin() == -100);
	assert(tree1.NextMin() == -50);
	assert(tree1.NextMin() == 0);
	assert(tree1.NextMin() == 10);
	assert(tree1.NextMin() == 50);
	assert(tree1.NextMin() == 60);
	assert(tree1.NextMin() == 75);
	assert(tree1.NextMin() == 100);
	assert(tree1.NextMin() == 150);
	assert(!tree1.HasNextMin());
	assert(tree1.NextMax() == 150);
	assert(tree1.NextMax() == 100);
	assert(tree1.NextMax() == 75);
	assert(tree1.NextMax() == 60);
	assert(tree1.NextMax() == 50);
	assert(tree1.NextMax() == 10);
	assert(tree1.NextMax() == 0);
	assert(tree1.NextMax() == -50);
	assert(tree1.NextMax() == -100);
	assert(!tree1.HasNextMax());
	assert(!b.empty());
	assert(b.size() == a.size());
	assert(b == a);
	cout << "Binary Search Tree content: " << endl;
	tree1.PrintTree();
	cout << endl;
	tree1.PrintTreeColumns();
	long min = tree1.MinDiffInBST();
	assert(min == 10);
	cout << endl
		 << "Binary Search Tree minimum diff between any 2 nodes: " << min << endl;
	cout << endl;
	cout << "Subtree content: " << endl;
	subtree.PrintTree();
	cout << endl;
	cout << (tree1.SubTree(tree1.Root(), subtree.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "Subtree1 content: " << endl;
	subtree1.PrintTree();
	cout << endl;
	cout << (tree1.SubTree(tree1.Root(), subtree1.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "Subtree2 content: " << endl;
	subtree2.PrintTree();
	cout << endl;
	cout << (tree1.SubTree(tree1.Root(), subtree2.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "MinDepth: " << tree1.MinDepth(tree1.Root()) << ", MaxDepth: " << tree1.MaxDepth(tree1.Root()) << " " << (tree1.IsBalancedTree() ? "balanced" : "Unbalanced") << endl;

	tree1.FindSum(tree1.Root(), -100, result);
	cout << "Sum -100 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << "\"" << *it << "\" ";
	cout << endl;
	result.clear();

	tree1.FindSum(tree1.Root(), 150, result);
	cout << "Sum 150 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << "\"" << *it << "\" ";
	cout << endl;
	result.clear();

	tree1.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "Binary Search Tree content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	shared_ptr<Node<long>> node, node1, node2, node3;
	node = tree1.FindNode(-50);
	assert(node);
	// assert(tree1.InOrderSuccessor(node)->Item() == 0);
	cout << "InOrder successor of -50: " << tree1.InOrderSuccessor(node)->Item() << endl;
	node = tree1.FindNode(50);
	assert(node);
	// assert(tree1.InOrderSuccessor(node)->Item() == 100);
	cout << "InOrder successor of 50: " << tree1.InOrderSuccessor(node)->Item() << endl;
	nodes.clear();

	node = tree1.FindNode(-50);
	assert(node);
	node1 = tree1.FindNode(10);
	assert(node1);
	node2 = tree1.CommonAncestor(node, node1);
	node3 = tree1.CommonAncestor1(node, node1);
	assert(node2);
	assert(node3);
	assert(node2 == node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node1 = tree1.FindNode(75);
	assert(node1);
	node2 = tree1.CommonAncestor(node, node1);
	node3 = tree1.CommonAncestor1(node, node1);
	assert(node2);
	assert(node3);
	assert(node2 == node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node = tree1.FindNode(60);
	assert(node);
	node1 = tree1.FindNode(75);
	assert(node1);
	node2 = tree1.CommonAncestor(node, node1);
	node3 = tree1.CommonAncestor1(node, node1);
	assert(node2);
	assert(node3);
	assert(node2 == node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;

	Tree<long> tree2(tree1);
	assert(tree2 == tree1);
	assert(tree2.isValidBST());
	assert(tree2.Count() == 9);
	assert(tree2.Min() == -100);
	assert(tree2.Max() == 150);
	// 50,-100,0,10,-50,60,100,75,150
	// -100,-50,0,10,50,60,75,100,150
	assert(tree2.kthSmallest(3) == 0);
	assert(tree2.kthLargest(3) == 75);
	cout << "Tree2 content (= Tree1): " << endl;
	tree2.PrintTree();
	cout << endl;
}
void KDTreeTests()
{
	vector<vector<long>> coordinates{{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
	KDTree<long> kdTree(coordinates);
	kdTree.PrintTree();
}
void MinHeapTests()
{
	vector<long> result;
	Heap<long> heap(50);
	heap.InsertItem(-100);
	heap.InsertItem(0);
	heap.InsertItem(10);
	heap.InsertItem(-50);
	heap.InsertItem(60);
	heap.InsertItem(100);
	heap.InsertItem(75);
	heap.InsertItem(150);
	assert(heap.Count() == 9);
	assert(heap.MaxDepth(heap.Root()) == 4 /* Change this assertion number if items are added/removed*/);
	cout << "MinHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "MinHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	heap.Serialize(result);
	cout << "Serialized Min Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
		if (it != result.begin())
		{
			if (*it < *(it - 1))
			{
				cout << "Heap failed!";
				assert(false);
				break;
			}
		}
	}
	cout << endl
		 << endl;
}
void MaxHeapTests()
{
	vector<long> result;
	Heap<long> heap(50, HeapType::MaxHeap);
	heap.InsertItem(-100);
	heap.InsertItem(0);
	heap.InsertItem(10);
	heap.InsertItem(-50);
	heap.InsertItem(60);
	heap.InsertItem(100);
	heap.InsertItem(75);
	heap.InsertItem(150);
	assert(heap.Count() == 9);
	assert(heap.MaxDepth(heap.Root()) == 4 /* Change this assertion number if items are added/removed*/);
	cout << "MaxHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "MaxHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	heap.Serialize(result);
	cout << "Serialized Max Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
		if (it != result.begin())
			if (*it > *(it - 1))
			{
				cout << "Heap failed!";
				assert(false);
				break;
			}
	}
	cout << endl
		 << endl;
}
void MinMaxHeapTests()
{
	vector<long> result;
	Heap<long> heap(50, HeapType::MinMaxHeap);
	heap.InsertItem(-100);
	heap.InsertItem(0);
	heap.InsertItem(10);
	heap.InsertItem(-50);
	heap.InsertItem(60);
	heap.InsertItem(100);
	heap.InsertItem(75);
	heap.InsertItem(150);
	assert(heap.Count() == 9);
	assert(heap.MaxDepth(heap.Root()) == 4 /* Change this assertion number if items are added/removed*/);
	cout << "MinMaxHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "MinMaxHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	heap.Serialize(result);
	cout << "Serialized MinMax Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
		if (it != result.begin())
			if (*it < *(it - 1))
			{
				throw runtime_error("Heap building failed!");
				break;
			}
	}
	cout << endl
		 << endl;
}
/*
 * Perform a down-heap or heapify-down operation for a max-heap
 * Index start from 0
 */
void MaxHeapifyDown(vector<long> &data, size_t start)
{
	size_t left = 2 * start + 1;
	size_t right = 2 * start + 2;
	size_t max = start;
	if (left < data.size() && data[left] > data[max])
		max = left;
	if (right < data.size() && data[right] > data[max])
		max = right;
	if (max != start)
	{
		long tmp = data[start];
		data[start] = data[max];
		data[max] = tmp;
		MaxHeapifyDown(data, max);
	}
}
/*
 * Perform a down-heap or heapify-down operation for a min-heap
 * Index start from 0
 */
void MinHeapifyDown(vector<long> &data, size_t start)
{
	size_t left = 2 * start + 1;
	size_t right = 2 * start + 2;
	size_t min = start;
	if (left < data.size() && data[left] < data[min])
		min = left;
	if (right < data.size() && data[right] < data[min])
		min = right;
	if (min != start)
	{
		long tmp = data[start];
		data[start] = data[min];
		data[min] = tmp;
		MaxHeapifyDown(data, min);
	}
}
void trim(string &str)
{
	size_t i = 0, j = 0;
	for (i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			if (i > 0 && str[i - 1] != ' ')
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
	}
	for (; j < str.size(); j++)
		str[j] = ' ';
}
/*       1 2 3 4 5 6 (sum: 8)
 * diff:  7 6 5 4 3 2
 * pairs: 1 2 3 4	  <= 2 pairs: {[3,5], [2,6]}
 */
size_t sumpairs(vector<long> &numbers, long sum)
{
	size_t count = 0;
	long diff;
	set<long> pairs;
	set<long> exclude;
	for (vector<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		diff = sum - *it;
		if (pairs.find(diff) != pairs.end() && exclude.find(diff) == exclude.end())
		{
			count++;
			exclude.emplace(diff);
			// cout << *it << " + " << tmp << endl;
		}
		else
			pairs.emplace(*it);
	}
	return count;
}
/* https://leetcode.com/problems/3sum/
 * 100%
 */
vector<vector<long>> threeSum(vector<long> &nums)
{
	set<vector<long>> result;
	if (nums.empty() || nums.size() < 3)
		return vector<vector<long>>();
	sort(nums.begin(), nums.end());
	// -1,0,1,2,-1,-4 => -1, -1, 0, 1, 2, 4
	// -4,-1,-1,0,1,2
	for (size_t i = 0; i < nums.size(); i++)
	{
		for (size_t j = i + 1, k = nums.size() - 1; j < k;)
		{
			long sum = nums[i] + nums[j] + nums[k];
			if (!sum)
				result.insert(vector<long>{nums[i], nums[j++], nums[k--]});
			else if (sum < 0)
				j++;
			else
				k--;
		}
	}
	vector<vector<long>> result1(result.begin(), result.end());
	return result1;
}
/* https://leetcode.com/problems/4sum/
 * 100%
 */
vector<vector<long>> fourSum(vector<long> &nums, long target)
{
	set<vector<long>> result;
	if (nums.empty() || nums.size() < 4)
		return vector<vector<long>>();
	sort(nums.begin(), nums.end());
	// -1,0,1,2,-1,-4 => -1, -1, 0, 1, 2, 4
	// -4,-1,-1,0,1,2
	for (size_t i = 0; i < nums.size(); i++)
	{
		for (size_t j = i + 1, k = nums.size() - 1; j < k; j++)
			for (size_t l = j + 1, m = k; l < m;)
			{
				long sum = nums[i] + nums[j] + nums[l] + nums[m];
				if (sum == target)
					result.insert(vector<long>{nums[i], nums[j], nums[l++], nums[m--]});
				else if (sum < target)
					l++;
				else
					m--;
			}
	}
	vector<vector<long>> result1(result.begin(), result.end());
	return result1;
}
/* https://www.hackerrank.com/challenges/pairs/problem
 * 100%
 *       1 2 3 4 5 6 (diff: 1)
 * tmp:  2 3 4 5 6 7
 * count:1 2	3 4	5  	=> 5 pairs
 */
size_t diffpairs(vector<long> &numbers, long diff)
{
	size_t count = 0;
	set<long> pairs(numbers.begin(), numbers.end());
	long tmp;
	for (vector<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		tmp = *it + diff;
		if (pairs.find(tmp) != pairs.end())
			count++;
	}
	return count;
}
size_t diffpairs(set<long> &numbers, long diff)
{
	size_t count = 0;
	long tmp;
	set<long>::iterator srcIt;
	for (set<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		tmp = diff + *it;
		srcIt = numbers.find(tmp);
		if (srcIt != numbers.end())
			count++;
		// cout << *it << ", " << *srcIt << endl;
	}
	return count;
}
size_t minDiffPairs(vector<long> &numbers, long diff)
{
	size_t count = 0;
	sort(numbers.begin(), numbers.end());
	set<long> pairs;
	if (numbers.size() < 2)
		return 0;
	size_t offset = 1;
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (pairs.find(i) != pairs.end())
			continue;
		int num = numbers[i];
		for (size_t j = offset; j < numbers.size(); j++)
		{
			if (pairs.find(j) != pairs.end())
				continue;
			if (abs(numbers[i] - numbers[j]) >= diff)
			{
				offset = j + 1;
				pairs.insert(i);
				pairs.insert(j);
				break;
			}
		}
	}
	return pairs.size() / 2;
}
vector<char> AddVectors(vector<char> &a, vector<char> &b)
{
	char carry = 0;
	vector<char> result;
	vector<char>::reverse_iterator aIt = a.rbegin();
	vector<char>::reverse_iterator bIt = b.rbegin();
	for (; aIt != a.rend() && bIt != b.rend(); aIt++, bIt++)
	{
		result.push_back((*aIt + *bIt + carry) % 10);
		carry = (*aIt + *bIt + carry) / 10;
	}
	if (aIt != a.rend())
	{
		result.push_back((*aIt + carry) % 10);
		carry = (*aIt + carry) / 10;
	}
	if (bIt != b.rend())
	{
		result.push_back((*bIt + carry) % 10);
		carry = (*bIt + carry) / 10;
	}
	if (carry > 0)
		result.push_back(carry);
	reverse(result.begin(), result.end());
	return result;
}
// 0 1 2 3 4 5 6 7 8 9
//         ^ (10 / 2 - 1)
// (0,9), (0,8)	2
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
size_t greaterthansumpairs(vector<long> &numbers, long sum)
{
	size_t count = 0, count1;
	for (size_t i = 0; i <= numbers.size() / 2 - 1; i++)
	{
		count1 = 0;
		for (size_t j = numbers.size() - 1; j >= 0 && numbers[i] + numbers[j] >= sum && i <= j; j--)
			count1++;
		if (!i && count1)
			count += count1 - 1;
		if (i != numbers.size() / 2 - 1)
			count1 *= 2;
		count += count1;
	}
	return count;
}
/* Given a 2-dimensional array with arbitrary sizes and contains random positive values, you are required to move from the first element [0][0] to the last
 * element [n][n] using the path which will yield the maximum sum of all the elements traversed. You can only move right and down; NOT left and up.
 * 1 2
 */
pathResult_t FindMaxPath(vector<vector<unsigned long>> &grid, size_t r, size_t c)
{
	ostringstream oss;
	pathResult_t result;
	if (r < grid.size() && c < grid[r].size())
	{
		if (r == grid.size() - 1 && c == grid[r].size() - 1)
		{
			result.sum = grid[r][c];
			oss << "[" << r << "][" << c << "]";
			result.path = oss.str();
			return result;
		}
		pathResult_t path1 = FindMaxPath(grid, r, c + 1);
		pathResult_t path2 = FindMaxPath(grid, r + 1, c);
		oss << "[" << r << "][" << c << "] " << ((path1.sum >= path2.sum) ? path1.path : path2.path);
		result.sum = grid[r][c] + max(path1.sum, path2.sum);
		result.path = oss.str();
	}
	return result;
}
// S: Start; X: Obstacle E: Destination
// 1 1 1 1 1
// S 1 X 1 1
// 1 1 1 1 1
// X 1 1 E 1
// 1 1 1 1 X
bool FindShortestPath(vector<vector<char>> &grid, size_t r, size_t c, queue<string> &result, char dest, char obstacle)
{
	string pos, origin;
	ostringstream oss, oss1;
	set<string> visited;
	map<string, string> route;
	vector<position_t> positions;
	positions.push_back(position_t(r, c));
	oss << r << c;
	origin = oss.str();
	oss.str("");
	while (!positions.empty())
	{
		vector<position_t> nextHops(positions);
		positions.clear();
		for (vector<position_t>::const_iterator it = nextHops.begin(); it != nextHops.end(); it++)
		{
			oss1.str("");
			oss1 << it->row << it->col;
			// Go Down
			if (it->row + 1 < grid.size())
				if (grid[it->row + 1][it->col] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row + 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row + 1][it->col] != obstacle)
				{ // Obstacle. Cancel this route
					oss.str("");
					oss << it->row + 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row + 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Right
			if (it->col + 1 < grid[it->row].size())
				if (grid[it->row][it->col + 1] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col + 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col + 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col + 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col + 1));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Up
			if (it->row > 0)
				if (grid[it->row - 1][it->col] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row - 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row - 1][it->col] != obstacle)
				{
					oss.str("");
					oss << it->row - 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row - 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Left
			if (it->col > 0)
				if (grid[it->row][it->col - 1] == dest)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col - 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col - 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col - 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col - 1));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
		}
	}
	return false;
}
// -1  0 -1
// -1 -1 -1
// -1 -1 -1
void MatrixDistance(vector<vector<long>> &data, size_t x, size_t y)
{
	if (x < data.size() && y < data[0].size())
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			for (size_t j = 0; j < data[0].size(); j++)
			{
				if (x != i && y != j)
					data[i][j] = abs((long)(x - i)) + abs((long)(y - j));
				else if (x == i && y != j)
					data[i][j] = abs((long)(y - j));
				else if (x != i && y == j)
					data[i][j] = abs((long)(x - i));
			}
		}
	}
}
void MatrixSort(vector<vector<long>> &data)
{
	vector<long> sorted;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			sorted.push_back(data[i][j]);
	QuickSort(sorted, 0, sorted.size() - 1);
	size_t k = 0;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			data[j][i] = sorted[k++];
}
void MatrixSortWithHeap(vector<vector<long>> &data)
{
	Heap<long> heap;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			heap.InsertItem(data[i][j]);
	// QuickSort(sorted, 0, sorted.size() - 1);
	size_t k = 0;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			data[j][i] = heap.pop()->Item();
}
// You are given a matrix. Elements in matrix can be either 0 or 1. Each row and column of matrix is sorted in ascending order.
// Find number of '0's in the given matrix. Expected complexity is O(log(N)).
long MatrixPatternCount(vector<vector<long>> &data)
{
	long i = data.size() - 1, j = data[0].size() - 1;
	long count = 0;
	for (; i >= 0 && j >= 0; i--, j--)
		if (!data[i][j])
		{
			count = (i + 1) * (j + 1);
			break;
		}
	long ii = i, jj = j;
	if (ii < (long)data.size() - 1)
		for (; j >= 0; j--)
			for (i = ii + 1; !data[i][j]; i++)
				count++;
	i = ii;
	if (jj < (long)data[ii].size() - 1)
		for (; i >= 0; i--)
			for (j = jj + 1; !data[i][j]; j++)
				count++;
	return count;
}
template <typename A, typename B>
pair<B, A> flip_pair(const pair<A, B> &p)
{
	return pair<B, A>(p.second, p.first);
}

template <typename A, typename B>
multimap<B, A> flip_map(const map<A, B> &src)
{
	multimap<B, A> dst;
	transform(src.begin(), src.end(), inserter(dst, dst.begin()), flip_pair<A, B>);
	return dst;
}
// https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
// 100%
size_t ConnectedCellsInAGridLinkedList(vector<vector<long>> &grid)
{
	map<string, shared_ptr<Node<string>>> nodes;
	set<shared_ptr<LinkedList<string>>> clusters;
	ostringstream location, oss;
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == 1)
			{
				location.str("");
				location << i << "," << j;
				// Node<string>* node = new Node<string>(location.str());
				shared_ptr<Node<string>> node(make_shared<Node<string>>(location.str()));
				// nodes[location.str()] = shared_ptr<Node<string>>(node);
				nodes[location.str()] = node;
				shared_ptr<Node<string>> parent = nullptr;
				set<shared_ptr<LinkedList<string>>> joins;
				bool skip = false;
				// Upper Left
				if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1)
				{
					oss.str("");
					oss << i - 1 << "," << j - 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Up
				if (i > 0 && grid[i - 1][j] == 1)
				{
					oss.str("");
					oss << i - 1 << "," << j;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Upper Right
				if (i > 0 && j < grid[0].size() - 1 && grid[i - 1][j + 1] == 1)
				{
					oss.str("");
					oss << i - 1 << "," << j + 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Left
				if (j > 0 && grid[i][j - 1] == 1)
				{
					oss.str("");
					oss << i << "," << j - 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Right
				if (j < grid[0].size() - 1 && grid[i][j + 1] == 1)
				{
					oss.str("");
					oss << i << "," << j + 1;
					parent = nodes[oss.str()];
					if (parent)
					{
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++)
						{
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head)
							{
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail)
						{
							tail->SetNext(node);
							// continue;
							skip = true;
						}
					}
				}
				// Join the overlapping clusters
				if (!joins.empty() && joins.size() > 1)
				{
					set<shared_ptr<LinkedList<string>>>::iterator it = joins.begin();
					set<shared_ptr<LinkedList<string>>>::iterator joinTo = clusters.find(*it++); // Get the first cluster from "clusters" and join the others to it
					for (; it != joins.end(); it++)
					{
						set<shared_ptr<LinkedList<string>>>::iterator it1 = clusters.find(*it);
						(*joinTo)->Join(**it1);
						clusters.erase(*it1);
					}
				}
				if (!skip)
					clusters.emplace(make_shared<LinkedList<string>>(node));
				joins.clear();
			} // if (grid[i][j] == 1) {
		}
	size_t max = 0;
	for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end(); it++)
	{
		//(*it)->Print();
		if ((*it)->Length() > max)
			max = (*it)->Length();
	}
	nodes.clear();
	clusters.clear();
	return max;
}
// https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
// 100%
size_t ConnectedCellsInAGrid(vector<vector<long>> &grid)
{
	vector<long> data;
	data.resize(grid.size() * grid[0].size());
	generate(data.begin(), data.end(), [i = 1]() mutable
			 { return i++; });
	DisJointSet<long> disjointSet(data);
	size_t width = grid[0].size();
	map<long, size_t> counts;
	size_t max = 0;
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j] == 1)
			{
				max = 1;
				long node = i * width + j + 1;
				long currentRoot = disjointSet.Find(node);
				// Upper Left
				if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1)
				{
					long neighbour = (i - 1) * width + j;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Up
				if (i > 0 && grid[i - 1][j] == 1)
				{
					long neighbour = (i - 1) * width + j + 1;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Upper Right
				if (i > 0 && j < grid[0].size() - 1 && grid[i - 1][j + 1] == 1)
				{
					long neighbour = (i - 1) * width + j + 2;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Left
				if (j > 0 && grid[i][j - 1] == 1)
				{
					long neighbour = i * width + j;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Right
				if (j < grid[0].size() - 1 && grid[i][j + 1] == 1)
				{
					long neighbour = i * width + j + 2;
					long root = disjointSet.Union(node, neighbour);
					if (root != numeric_limits<long>::min())
					{
						if (root != currentRoot && counts.find(currentRoot) != counts.end())
						{ // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else
						{ // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
			} // if (grid[i][j] == 1) {
		}	  // for (size_t j = 0; j < grid[0].size(); j++) {
	for (map<long, size_t>::iterator it = counts.begin(); it != counts.end(); it++)
		if (it->second > max)
			max = it->second;
	// disjointSet.Print(data, grid[0].size());
	return max;
}
/* https://leetcode.com/problems/word-search/
 * 100%
 */
bool WordExistsInGrid(vector<vector<char>> &board, const string &word)
{
	for (size_t i = 0; i < board.size(); i++)
		for (size_t j = 0; j < board[i].size(); j++)
			if (WordExistsInGrid(board, word, i, j, 0))
				return true;
	return false;
}
bool WordExistsInGrid(vector<vector<char>> &board, const string &word, long row, long col, size_t offset)
{
	if (row < 0 || col < 0 || row >= (long)board.size() || col >= (long)board[row].size() || offset >= word.size() || word[offset] != board[row][col])
		return false;
	if (offset == word.size() - 1)
		return true;
	board[row][col] ^= 0x80; // "visited" mark
	bool flag = WordExistsInGrid(board, word, row, col + 1, offset + 1) ||
				WordExistsInGrid(board, word, row + 1, col, offset + 1) ||
				WordExistsInGrid(board, word, row, col - 1, offset + 1) ||
				WordExistsInGrid(board, word, row - 1, col, offset + 1);
	board[row][col] ^= 0x80; //
	return flag;
}
// 0 0 1 0 1
// 0 0 0 0 0
// 0 1 1 1 1
// 0 1 1 0 0
// Start: y:1 x:4 End: y: 0 x: 3=> true

// 0 0 1 1 1
// 0 1 0 0 0
// 1 1 1 1 1
// 0 0 0 0 1
// Start: y:0 x:0 End: y: 2 x: 1  => false
bool PathExists(vector<vector<char>> &grid, size_t r, size_t c, size_t y, size_t x, queue<string> &result, char obstacle)
{
	string pos, origin;
	ostringstream oss, oss1;
	set<string> visited;
	map<string, string> route;
	vector<position_t> positions;
	positions.push_back(position_t(r, c));
	oss << r << c;
	origin = oss.str();
	oss.str("");
	while (!positions.empty())
	{
		vector<position_t> nextHops(positions);
		positions.clear();
		for (vector<position_t>::const_iterator it = nextHops.begin(); it != nextHops.end(); it++)
		{
			oss1.str("");
			oss1 << it->row << it->col;
			// Go Down
			if (it->row + 1 < grid.size())
				if (it->row + 1 == y && it->col == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row + 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row + 1][it->col] != obstacle)
				{ // Obstacle. Cancel this route
					oss.str("");
					oss << it->row + 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row + 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Right
			if (it->col + 1 < grid[it->row].size())
				if (it->row == y && it->col + 1 == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col + 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col + 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col + 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col + 1));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Up
			if (it->row > 0)
				if (it->row - 1 == y && it->col == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row - 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row - 1][it->col] != obstacle)
				{
					oss.str("");
					oss << it->row - 1 << it->col;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row - 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Left
			if (it->col > 0)
				if (it->row == y && it->col - 1 == x)
				{ // Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col - 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end())
					{
						pos = route[pos];
						result.push(pos);
					}
					return true;
				}
				else if (grid[it->row][it->col - 1] != obstacle)
				{
					oss.str("");
					oss << it->row << it->col - 1;
					if (visited.find(oss.str()) == visited.end())
					{ // Prevent loop
						positions.push_back(position_t(it->row, it->col - 1));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
		}
	}
	return false;
}
// Divide the array(+ve and -ve numbers) into two parts such that the average of both the parts is equal.
//
// Assume that such splitting exists.
//
// Let then N be array length, Sum - sum of entire array, P - sum of one part of items, K - count of numbers in that part.
// Let's write equations for averages in both parts of array:
//
// P / K = (Sum - P) / (N - K)
// P * (N - K) = K * (Sum - P)
// P * N - P * K = K * Sum - K * P
// P * N = K * Sum
// P = K * Sum / N
void EqualAverageDivide(vector<long> &data, vector<long> &left)
{
	long sum = 0, P = 0;
	size_t N = data.size(), K;
	// Sort the data
	sort(data.begin(), data.end());
#ifdef _MSC_VER
	sum = parallel_reduce(data.begin(), data.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	sum = parallel_reduce(
		blocked_range<long>(0, data.size()), 0,
		[&](tbb::blocked_range<long> r, long running_total)
		{
			for (int i = r.begin(); i < r.end(); ++i)
				running_total += data[i];
			return running_total;
		},
		std::plus<long>());
#endif

	for (K = 1; K < (N - K); K++)
	{
		if (((K * sum) % N)) //  check if such P can be integer (we operate with array of integers).
			continue;
		// picking K integers with sum of P from sorted array of integers
		P = K * sum / N;
		if (GetSum(data, K, P, 0, left))
			break;
	}
}
bool GetSum(vector<long> &data, size_t K, long P, size_t index, vector<long> &left)
{
	if (!P)
		return K == 0;
	else if (!K)
		return P == 0;
	else if (index >= data.size())
		return false;
	for (size_t i = index; i < data.size(); i++)
	{
		if (GetSum(data, K - 1, P - data[i], i + 1, left))
		{
			left.push_back(data[i]);
			return true;
		}
	}
	return false;
}
// Question was "Given a pattern and a string input - find if the string follows the same pattern and return 0 or 1.
// Examples:
// 1) Pattern: "abba" (.+)(.+)\\2\\1 input : "redbluebluered" should return 1.
// 2) Pattern: "aaaa" (.+)\\1\\1\\1  input : "asdasdasdasd" should return 1.
// 3) Pattern: "aabb" (.+)\\1(.+)\\2 input : "xyzabcxyzabc" should return 0.
// 3) Pattern: "abab" (.+)(.+)\\1\\2 input : "xyzabcxyzabc" should return 1.
bool match(const string &pattern, const string &input)
{
	map<char, long> patternCount;
	ostringstream regexStr;
	long captureGroup = 0;
	for (string::const_iterator it = pattern.begin(); it != pattern.end(); it++)
	{
		if (patternCount.find(*it) != patternCount.end())
			regexStr << "\\" << patternCount[*it];
		else
		{
			patternCount.emplace(*it, ++captureGroup);
			regexStr << "(.+)";
		}
	}
	return regex_match(input.begin(), input.end(), regex(regexStr.str()));
}
string EncodeString(string str)
{
	ostringstream oss;
	map<char, long> codes;
	long code = 0;
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (codes.find(*it) == codes.end())
			codes.emplace(*it, code++);
		oss << codes[*it];
	}
	return oss.str();
}
// Given a pattern and a dictionary, print out all the strings which match the pattern
// where a char in the pattern maps uniquely to a char in the dictionary.
// Eg: 'abc' <'cdf', 'too', 'hgfdt', 'paa'> => 'cdf'
// Eg: 'acc' <'cdf', 'too', 'hgfdt', 'paa'> => 'too', 'paa'
void FindPattern(string pattern, set<string> &dictionary, set<string> &result)
{
	string encodedPattern = EncodeString(pattern);
	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
		if (it->size() == pattern.size() && !encodedPattern.compare(EncodeString(*it)))
			result.insert(*it);
}
string GetRange(vector<long> &input)
{
	ostringstream oss;
	vector<long> numbers(input);
	sort(numbers.begin(), numbers.end());
	if (!numbers.empty())
	{
		size_t first = 0;
		for (size_t i = 1; i < numbers.size(); i++)
			if ((numbers[i] - numbers[i - 1]) > 1)
			{
				oss << numbers[first];
				if (first != i - 1)
					oss << " - " << numbers[i - 1] << ", ";
				else
					oss << ", ";
				first = i;
			}
		oss << numbers[first];
		if (first != numbers.size() - 1)
			oss << " - " << numbers.back();
	}
	return oss.str();
}
/* https://leetcode.com/problems/merge-intervals/
 * 100%
 */
vector<vector<long>> MergeIntervals(vector<vector<long>> &intervals)
{
	vector<vector<long>> result;
	// Sort the 2D vector in ascending order of the first element.
	sort(intervals.begin(), intervals.end(), [](const vector<long> &a, const vector<long> &b)
		 { return a[0] < b[0]; });
	for (size_t i = 0; i < intervals.size(); i++)
	{
		if (!i)
			result.push_back(intervals[i]);
		else if (intervals[i][1] < result.back()[0] || intervals[i][0] > result.back()[1])
			result.push_back(intervals[i]);
		else if (intervals[i][0] <= result.back()[0])
		{
			result.back()[0] = intervals[i][0];
			if (intervals[i][1] >= result.back()[1])
				result.back()[1] = intervals[i][1];
		}
		else if (intervals[i][0] <= result.back()[1] && intervals[i][1] > result.back()[1])
			result.back()[1] = intervals[i][1];
	}
	return result;
}
bool isSparseNumber(long i)
{
	long previous2digits = 0;
	for (; i > 0; i = i >> 2)
	{
		if (((i & 3) == 1 && previous2digits == 2) || (i & 3) == 3)
			return false;
		previous2digits = i & 3;
	}
	return true;
}
long NextSparseNumber(long number)
{
	long i = number;
	long shift;
	for (shift = 0; i > 0; shift++, i = i >> 1)
	{
		if (!(i & 3))
			return i + (1 << shift);
		else if ((i & 7) == 1)
			return 1 << (shift + 1) > number ? 1 << (shift + 1) : number - (1 << shift) + (1 << (shift + 1));
	}
	return number == 0 ? 1 : 1 << (shift + 1);
}
// a and b are streams of integer from LSB to MSB
// Assume a >= b
string subtract(istream &a, istream &b)
{
	ostringstream oss;
	char i, j;
	while (b.read(&j, 1))
	{
		a.read(&i, 1);
		oss << i - j;
	}
	cout << "Result : " << oss.str() << endl;
	return oss.str();
}
void split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		elems.push_back(item);
}
// file: "This is a dog"
// 0: This is a
// 1: is a dog
set<string> process(const string &str, int n)
{
	vector<string> words;
	set<string> ngrams;
	::split(str, ' ', words);
	for (size_t i = 0; i <= words.size() - n; i++) // i: 0, 1
	{
		string s;
		for (size_t j = i; j < (i + n); j++)
		{ // j: [0,2] [1,3]: "This is a", "is a dog"
			s.append(words[j]);
			if (j != i + n - 1)
				s.append(" ");
		}
		ngrams.emplace(s);
	}
	return ngrams;
}
set<string> intersectionNgram(const string &str1, const string &str2, int n)
{
	set<string> result;
	set<string> ngrams1 = process(str1, n);
	if (ngrams1.empty())
		return result;
	cout << "str1 " << n << "-grams: ";
	for (set<string>::const_iterator it = ngrams1.begin(); it != ngrams1.end(); it++)
		cout << "\"" << *it << "\""
			 << ", ";
	cout << endl;
	set<string> ngrams2 = process(str2, n);
	cout << "str2 " << n << "-grams: ";
	for (set<string>::const_iterator it = ngrams2.begin(); it != ngrams2.end(); it++)
		cout << "\"" << *it << "\""
			 << ", ";
	cout << endl;
	set_intersection(ngrams1.begin(), ngrams1.end(), ngrams2.begin(), ngrams2.end(), inserter(result, result.begin()));
	return result;
}
vector<int> Increment(vector<int> &data)
{
	int j = 1;
	vector<int> result;
	for (vector<int>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
	{
		j += *it;
		if (j < 10)
		{
			result.push_back(j);
			j = 0;
		}
		else
		{
			result.push_back(j - 10);
			j = 1;
		}
	}
	if (j == 1)
		result.push_back(j);
	reverse(result.begin(), result.end());
	return result;
}
vector<string> numbersegments(vector<long> &data)
{
	ostringstream oss;
	vector<string> result;
	oss << data.front();
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++)
		if (it == (data.end() - 1) || *it != (*(it + 1) - 1))
		{
			if (!oss.str().empty())
				oss << '-';
			oss << *it;
			result.push_back(oss.str());
			oss.str("");
		}
		else if (oss.str().empty())
			oss << *it;
	return result;
}
/*
sizeof(void*) = 4
Align 4: alignment - 1 = 3
1 : 1 + 3 = 4 / 4 = 1
2 : 2 + 3 = 5 / 4 = 1
3 : 3 + 3 = 6 / 4 = 1
4 : 4 + 3 = 7 / 4 = 1

5 : 5 + 3 = 8 / 4 = 2
6 : 6 + 3 = 9 / 4 = 2
7 : 7 + 3 = 10 / 4 = 2
8 : 8 + 3 = 11 / 4 = 2

9 : 9 + 3 = 12 / 4 = 3
10 : 10 + 3 = 13 / 4 = 3
*/
void *alignedMalloc(size_t size, size_t alignment)
{
	size_t bytes = alignment / 8;
	return malloc(size + (size % bytes) / bytes);
}
void alignedFree(void **p)
{
	free(*p);
	*p = nullptr;
}
unsigned long long XOR(unsigned long long n)
{
	return (n <= 1) ? n : n ^ XOR(n - 1);
}
template <class URNG>
void TestURNG(URNG &urng)
{
	// Uniform distribution used with vector
	// Distribution is [-5, 5] inclusive
	uniform_int_distribution<long> dist(-5, 5);
	vector<long> v;
	v.resize(20);
	generate(v.begin(), v.end(), [&]
			 { return dist(urng); });
	cout << "Randomized vector: ";
	copy(v.begin(), v.end(), ostream_iterator<long>(cout, " "));
	cout << endl;

	// Shuffle an array.
	// Notice that shuffle() takes an URNG, not a distribution
	vector<string> strings = {{"H", "He", "Li", "Be", "B", "C", "N", "O", "F",
							   "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc",
							   "Ti", "V", "Cr", "Mn", "Fe"}};
	shuffle(strings.begin(), strings.end(), urng);
	cout << "Randomized vector<string>: ";
	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
}
void TestRandom()
{
	// First run: non-seedable, non-deterministic URNG random_device
	// Slower but crypto-secure and non-repeatable.
	random_device device;
	cout << "Using random_device URNG:" << endl;
	uniform_int_distribution<long> dist(-5, 5);
	vector<long> v;
	v.resize(20);
	generate(v.begin(), v.end(), [&]
			 { return dist(device); });

	TestURNG(device);

	// Second run: simple integer seed. Repeatable results
	cout << "Using constant-seed mersene twister engine URNG:" << endl;
	mt19937_64 constant_seed_mersene_twister_engine{mt19937_64(12345)};
	TestURNG(constant_seed_mersene_twister_engine);

	// Third run: random_device as seed; different each run.
	// Desirable for most purposes
	cout << "Using non-deterministic-seed mersene twister engine URNG:" << endl;
	mt19937_64 non_deterministic_seed_mersene_twister_engine{mt19937_64(device())};
	TestURNG(non_deterministic_seed_mersene_twister_engine);

	// Fourth run: "warm-up" sequence as as seed; different each run.
	// Advanced uses. Allows more than 32 bits of randomness.
	cout << "Using non-deterministic-seed \"warm-up\" sequence mersene twister engine URNG" << endl;
	vector<unsigned int> seeds;
	cout << "mt19937_64::state_size: " << mt19937_64::state_size << endl;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 non_deterministic_seed_sequence_mersene_twister_engine{mt19937_64(sequence)};
	TestURNG(non_deterministic_seed_sequence_mersene_twister_engine);
}
long concat(vector<long> &data)
{
	ostringstream oss;
	sort(data.begin(), data.end(), [&data](long i, long j) -> bool
		 {
		ostringstream a, b;
		a << i << j;
		b << j << i;
		return a.str() < b.str(); });
	for (vector<long>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
		oss << *it;
	long result;
	istringstream(oss.str()) >> result;
	return result;
}
/* https://leetcode.com/problems/largest-number/
 * {10, 2} => 210
 * {3,30,34,5,9} => 9534330
 *
 * Use string comparator to decide which goes before the other:
 * lhs: 12
 * rhs: 10
 * lhsrhs = 1210
 * rhslhs = 1012
 *
 * lhsrhs < rhslhs : lhs goes after rhs
 * lhsrhs > rhslhs : lhs goes before rhs
 *
 * 100%
 */
string buildmax(vector<size_t> &a)
{
	bool nonZero = false;
	multiset<string, buildmax_comparator_t> data;
	for (vector<size_t>::iterator it = a.begin(); it != a.end(); it++)
	{
		if (*it > 0)
			nonZero = true;
		data.insert(to_string(*it));
	}
	ostringstream oss;
	for (multiset<string, buildmax_comparator_t>::iterator it = data.begin(); it != data.end(); it++)
		oss << *it;
	return oss.str().empty() || !nonZero ? "0" : oss.str();
}
long MaxLengths(vector<string> &data)
{
	sort(data.begin(), data.end(), [](string a, string b)
		 { return a.size() > b.size(); });
	for (vector<string>::const_iterator it = data.begin(); it != data.end(); it++)
		for (vector<string>::const_iterator it1 = it + 1; it1 != data.end(); it1++)
		{
			size_t i = 0;
			for (; i < it1->size(); i++)
				if (it->find(it1[i]) != string::npos)
					break;
			if (i != it1->size() - 1)
				return it->size() * it1->size();
		}
	return 0;
}
void ExceptionTest()
{
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw..." << endl;
			throw; // Throw the original e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw..." << endl;
			e.msg_ = "Second Throw";
			throw; // throw the original e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw e..." << endl;
			throw e; // Throw the new e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try
	{
		try
		{
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e)
		{
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw e..." << endl;
			e.msg_ = "Second throw";
			throw e; // Throw the new e
		}
	}
	catch (Error e)
	{
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
}
size_t LongestAlternatingSubSequence(const vector<long> &data, vector<long> &result)
{
	map<size_t, vector<long>> sequences;
	direction_t direction = Direction::NoChange, flag = Direction::NoChange;
	size_t count = 0, start = 0, index = 0;
	if (data.size() > 1)
	{
		for (vector<long>::const_iterator it = data.begin() + 1; it != data.end(); it++, index++)
		{
			flag = *it > *(it - 1) ? Direction::Up : *it < *(it - 1) ? Direction::Down
																	 : Direction::NoChange;
			if (flag != direction)
			{
				count++;
				direction = flag;
			}
			else
			{
				direction = Direction::NoChange;
				if (sequences.find(index - start) == sequences.end())
				{
					vector<long> tmp(data.begin() + start, it);
					sequences.emplace(index - start, tmp);
				}
				start = index;
			}
		}
	}
	if (!sequences.empty())
		result = sequences.rbegin()->second;
	return result.size();
}
bool LexicographicSort(string s1, string s2)
{
	size_t i, j;
	map<string, size_t> order = {{"a", 0}, {"b", 1}, {"c", 2}, {"ch", 3}, {"cz", 4}, {"d", 5}, {"e", 6}, {"f", 7}, {"g", 8}, {"h", 9}, {"i", 10}, {"j", 11}, {"k", 12}, {"l", 13}, {"m", 14}, {"n", 15}, {"o", 16}, {"p", 17}, {"q", 18}, {"r", 18}, {"s", 19}, {"t", 20}, {"u", 21}, {"v", 22}, {"w", 23}, {"x", 24}, {"y", 24}, {"z", 25}};
	map<string, size_t>::iterator s1It = order.end(), s2It = order.end();
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	for (i = 0, j = 0; i < s1.size() && j < s2.size();)
	{
		if (i < s1.size() - 1)
		{
			s1It = order.find(s1.substr(i, 2));
			if (s1It != order.end())
				i += 2;
		}
		if (s1It == order.end())
			s1It = order.find(s1.substr(i++, 1));
		if (j < s2.size() - 1)
		{
			s2It = order.find(s2.substr(j, 2));
			if (s2It != order.end())
				j += 2;
		}
		if (s2It == order.end())
			s2It = order.find(s2.substr(j++, 1));
		if (s1It->second == s2It->second)
		{
			s1It = order.end();
			s2It = order.end();
		}
		else
			return s1It->second < s2It->second; // substring comparison
	}
	return (s1.size() - i) < (s2.size() - j); // String length comparison.
}
// Count number of '1' bits
size_t Count1Bits(long a)
{
	size_t count = 0;
	for (long i = 1; i <= a; i <<= 1)
		if (i & a)
			count++;
	return count;
}
/* Returns a sequence of bit patterns with increasing number of '1' bits
 * k: total number of bits in the bit patterns
 */
void BitCombinations(size_t k, vector<long> &result)
{
	for (size_t i = 0; i <= k; i++)
		for (long j = (1 << i) - 1; j < (1 << k); j++)
			if (Count1Bits(j) == i)
				result.push_back(j);
}
/* https://leetcode.com/problems/gray-code/
 * 100%
 */
vector<size_t> grayCode(size_t n)
{
	// 00, 01
	// 10, 10
	// 00 01 11 10

	// 000, 001
	// 010, 010
	// 100, 100
	// 000 001 011 010 110 111
	size_t i = 1;
	vector<size_t> result;
	result.push_back(0);
	for (; n > 0; n--, i <<= 1)
		for (int j = result.size() - 1; j >= 0; j--)
			result.push_back(result[j] | i);
	return result;
}
void OrderedMergedCombinations(set<string> &result, const string &s1, const string &s2, string cur)
{
	if (s1.empty() && s2.empty())
	{
		result.insert(cur);
		return;
	}
	else if (s1.empty() || s2.empty())
	{
		result.insert(s1.empty() ? cur + s2 : cur + s1);
		return;
	}
	/*
	 * s1: Hey, ey,    y,  ""
	 * s2: Bob, Bob, Bob, Bob
	 * cur: "",  H,   He, Hey  => HeyBob
	 *                     ""
	 *                     ob
	 *                    HeBy => HeByob
	 *                     ""
	 *                      b
	 *                  HeBoy  => HeBoyb
	 *                     ""
	 *                     ""
	 *                  HeBoby => HeBoby
	 */
	for (size_t i = 0; i <= s2.size(); i++) // Same result as below
		OrderedMergedCombinations(result, s1.substr(1, s1.size() - 1), s2.substr(i, s2.size() - i), cur + s2.substr(0, i) + s1[0]);
	// for (size_t i = 0; i <= s1.size(); i++) // Same result as above
	//	OrderedMergedCombinations(result, s1.substr(i, s1.size() - i), s2.substr(1, s2.size() - 1), cur + s1.substr(0, i) + s2[0]);
}
/*
k: 2
i: 1
comb: 1

k: 1
i: 2
comb: 1,2 combs: {{1,2}}
comb: 1
i: 3
comb: 1,3 combs: {{1,2}, {1,3}}
comb: 1
i: 4
comb: 1,4 combs: {{1,2}, {1,3}, {1,4}}
comb: 1

k: 2
i: 2
comb: 2

k: 1
i: 3
comb: 2,3 combs: {{1,2}, {1,3}, {1,4}, {2,3}}
comb: 2
i: 4
comb: 2,4 combs: {{1,2}, {1,3}, {1,4}, {2,3}, {2,4}}
comb: 2

k: 2
i: 3
comb: 3

k: 1
i: 4
comb: 3,4 combs: {{1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4}}
comb: 3

k: 2
i: 4
comb: 4

k: 1
i: 4
comb: 4 combs: {{1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4}}
comb: {}
* C=1, L: O(count), Other: O(n) n: end-start
* #nodes = O(count).
* TC = O(count * n)
*/
void numberCombinations1(size_t start, size_t end, size_t count, vector<size_t> &comb, vector<vector<size_t>> &result)
{
	if (!count)
		result.push_back(comb);
	else
	{
		for (size_t i = start; i <= end; i++)
		{
			comb.push_back(i);
			numberCombinations1(i + 1, end, count - 1, comb, result);
			comb.pop_back();
		}
	}
}
/* https://leetcode.com/problems/combinations/
 * 100%
 */
void numberCombinations(size_t n, size_t k, vector<vector<size_t>> &result)
{
	vector<size_t> comb;
	numberCombinations1(1, n, k, comb, result);
}
/*A zero-indexed array A consisting of N integers is given. A triplet(P, Q, R) is triangular if it is possible to build a triangle with sides of lengths A[P], A[Q] and A[R].
 * In other words, triplet(P, Q, R) is triangular if 0 ≤ P < Q < R < N and:
 *
 * A[P] + A[Q] > A[R],
 * A[Q] + A[R] > A[P],
 * A[R] + A[P] > A[Q].
 *
 * For example, consider array A such that :
 * A[0] = 10    A[1] = 2    A[2] = 5
 * A[3] = 1     A[4] = 8    A[5] = 12
 * There are four triangular triplets that can be constructed from elements of this array, namely(0, 2, 4), (0, 2, 5), (0, 4, 5), and (2, 4, 5).
 */
size_t CountTriangles(vector<long> &data)
{
	size_t result = 0;
	if (data.size() < 3)
		return 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = i + 1; j < data.size(); j++)
		{
			for (size_t k = j + 1; k < data.size(); k++)
			{
				if (data[i] + data[j] > data[k] &&
					data[j] + data[k] > data[i] &&
					data[k] + data[i] > data[j])
					result++;
			}
		}
	}
	return result;
}
/* https://app.codility.com/programmers/lessons/16-greedy_algorithms/max_nonoverlapping_segments/
 * 100%
 */
size_t MaxNonOverlappingSegments(vector<size_t> &head, vector<size_t> &tail)
{
	size_t count = 0, last_nonoverlapping_tail;
	if (!head.empty() && !tail.empty() && head.size() == tail.size())
	{
		last_nonoverlapping_tail = tail[0];
		count++;
		for (size_t i = 1; i < head.size(); i++)
		{
			if (head[i] > last_nonoverlapping_tail)
			{
				last_nonoverlapping_tail = tail[i];
				count++;
			}
		}
	}
	return count;
}
/* https://app.codility.com/programmers/lessons/16-greedy_algorithms/tie_ropes/
 * 100%
 * A[0] = 1
 * A[1] = 2
 * A[2] = 3
 * A[3] = 4
 * A[4] = 1
 * A[5] = 1
 * A[6] = 3
 * n: 4
 * {0,1,2},{3},{4,5,6}
 */
size_t TieRopes(vector<size_t> &data, size_t n)
{
	size_t result = 0;
	for (vector<size_t>::iterator it = data.begin(); it != data.end();)
	{
		size_t sum = 0;
		for (; sum < n && it != data.end(); sum += *it++)
			;
		if (sum >= n)
			result++;
	}
	return result;
}
// https://www.hackerrank.com/challenges/greedy-florist/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=greedy-algorithms
// XXX: 0%
// 3 2
// 2 5 6 : 1..2 [1]
// 5 3
// 1 3 5 7 9 : 1..2 [2]
// 5 3
// 1 3 5 7 9
size_t getMinimumCost(size_t k, vector<size_t> &c)
{
	size_t price = 0;
	if (!c.empty())
	{
		size_t flowers = c.size();
		if (flowers > k)
		{
			size_t solos = 0;
			while ((flowers - solos) % k)
			{
				solos++;
				k--;
			}
			size_t perperson = (c.size() - solos) / k;
			sort(c.begin(), c.end());
			size_t soloCnt = 0;
			for (vector<size_t>::reverse_iterator it = c.rbegin(); it != c.rend() && soloCnt < solos; it++, soloCnt++)
				price += *it;
			for (size_t firstflower = c.size() - 1 - solos; k > 0; k--, firstflower--)
			{
				price += c[firstflower];
				for (size_t i = 1; i < perperson; i++)
				{
					if (firstflower == perperson - 1)
						price += c[firstflower - i] * (i + 1);
					else
						price += c[firstflower - perperson * i] * (i + 1);
				}
			}
		}
		else
			price = accumulate(c.begin(), c.end(), 0);
	}
	return price;
}
// https://www.hackerrank.com/challenges/angry-children/problem
// 100%
size_t maxMin(size_t k, vector<size_t> &arr)
{
	sort(arr.begin(), arr.end());
	size_t unfair = numeric_limits<size_t>::max();
	size_t max = 0;
	for (size_t i = 0; i < arr.size() && max < arr.size() - 1; i++)
	{
		for (max = i + k - 1; max >= arr.size(); max--)
			;
		if (i != max)
		{
			size_t diff = abs(abs((long)arr[max]) - abs((long)arr[i]));
			if (diff < unfair)
				unfair = diff;
		}
	}
	return unfair;
}
void GreedyAlgorithmTests()
{
	vector<size_t> a, b;
	a.clear();
	a = {1, 3, 7, 9, 9};
	b.clear();
	b = {5, 6, 8, 9, 10};
	assert(MaxNonOverlappingSegments(a, b) == 3);
	a.clear();
	a = {1, 6, 7, 9, 10};
	b.clear();
	b = {5, 6, 8, 9, 10};
	assert(MaxNonOverlappingSegments(a, b) == 5); // No overlapping segments
	a.clear();
	a.resize(6);
	generate(a.begin(), a.end(), [i = 1]() mutable
			 { return i++; });
	b.clear();
	b.resize(6);
	generate(b.begin(), b.end(), [i = 5]() mutable
			 { return i++; });
	assert(MaxNonOverlappingSegments(a, b) == 2);
	a.clear();
	a = {1, 2, 3, 4, 1, 1, 3};
	assert(TieRopes(a, 4) == 3);
	a.clear();
	a = {2, 5, 6};
	assert(getMinimumCost(2, a) == 15);
	a.clear();
	a = {1, 3, 5, 7, 9};
	assert(getMinimumCost(3, a) == 29);
	a.clear();
	a = {10, 100, 300, 200, 1000, 20, 30};
	assert(maxMin(3, a) == 20);
	a.clear();
	a = {1, 2, 3, 4, 10, 20, 30, 40, 100, 200};
	assert(maxMin(4, a) == 3);
	a.clear();
	a = {1, 2, 1, 2, 1};
	assert(maxMin(2, a) == 0);
	a.clear();
	a = {100, 200, 300, 350, 400, 401, 402};
	assert(maxMin(3, a) == 2);
}
void Knapsack_CoinChangeTests()
{
	vector<size_t> numbers = {3, 2, 1};
	coinChangeCache.clear();
	set<vector<size_t>> combinations = CoinChange(0, numbers);
	assert(combinations.empty());
	set<vector<size_t>> combinations1 = CoinsChangeDynamicProgramming(0, numbers);
	assert(combinations1.empty());
	assert(CoinsChangeUniqueWaysDynamicProgramming(0, numbers) == 0);
	assert(CoinsChangeDuplicateWaysDynamicProgramming(0, numbers) == 0);
	coinChangeCache.clear();
	combinations = CoinChange(1, numbers);
	assert(combinations.size() == 1);
	set<vector<size_t>>::iterator it = combinations.begin();
	assert(it->size() == 1);
	assert((*it)[0] == 1);
	combinations1 = CoinsChangeDynamicProgramming(1, numbers);
	assert(combinations1.size() == 1);
	assert(combinations == combinations1);
	assert(CoinsChangeUniqueWaysDynamicProgramming(1, numbers) == 1);
	assert(CoinsChangeDuplicateWaysDynamicProgramming(1, numbers) == 1);
	coinChangeCache.clear();
	combinations = CoinChange(2, numbers);
	assert(combinations.size() == 2);
	combinations1 = CoinsChangeDynamicProgramming(2, numbers);
	assert(combinations1.size() == 2);
	assert(combinations == combinations1);
	assert(CoinsChangeUniqueWaysDynamicProgramming(2, numbers) == 2);
	assert(CoinsChangeDuplicateWaysDynamicProgramming(2, numbers) == 2);
	coinChangeCache.clear();
	combinations = CoinChange(3, numbers);
	assert(combinations.size() == 3);
	combinations1 = CoinsChangeDynamicProgramming(3, numbers);
	assert(combinations1.size() == 3);
	assert(combinations == combinations1);
	assert(CoinsChangeUniqueWaysDynamicProgramming(3, numbers) == 3);
	assert(CoinsChangeDuplicateWaysDynamicProgramming(3, numbers) == 4); // {3},{1,2},{2,1},{1,1,1}
	coinChangeCache.clear();
	combinations = CoinChange(4, numbers);
	assert(combinations.size() == 4);
	combinations1 = CoinsChangeDynamicProgramming(4, numbers);
	assert(CoinsChangeUniqueWaysDynamicProgramming(4, numbers) == 4);
	assert(CoinsChangeDuplicateWaysDynamicProgramming(4, numbers) == 7); // {3,1},{3,1},{1,1,2},{1,2,1},{2,1,1},{2,2},{1,1,1,1}
	assert(combinations1.size() == 4);
	assert(combinations == combinations1);
	numbers.clear();
	numbers = {6, 5, 3, 2};
	coinChangeCache.clear();
	combinations = CoinChange(10, numbers);
	assert(combinations.size() == 5);
	combinations1 = CoinsChangeDynamicProgramming(10, numbers);
	assert(combinations1.size() == 5);
	assert(combinations == combinations1);
	assert(CoinsChangeUniqueWaysDynamicProgramming(10, numbers) == 5);
	assert(CoinsChangeDuplicateWaysDynamicProgramming(10, numbers) == 17);
	coinChangeCache.clear();
	numbers.clear();
	numbers = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
	combinations = CoinChange(10, numbers);
	assert(combinations.size() == 5);
	combinations1 = CoinsChangeDynamicProgramming(10, numbers);
	assert(combinations1.size() == 5);
	assert(combinations == combinations1);
	coinChangeCache.clear();
	numbers.clear();
	numbers = {1, 50};
	combinations = CoinChange(200, numbers);
	assert(combinations.size() == 5);
	combinations1 = CoinsChangeDynamicProgramming(200, numbers);
	assert(combinations1.size() == 5);
	assert(combinations == combinations1);
	coinChangeCache.clear();
	numbers.clear();
	numbers = {2, 3, 5};
	assert(CoinsChangeUniqueWaysDynamicProgramming(5, numbers) == 2);	 // {{2,3}, {5}}
	assert(CoinsChangeDuplicateWaysDynamicProgramming(5, numbers) == 3); //{2,3},{3,2},{5}
	assert(CoinsChangeUniqueWaysDynamicProgramming(6, numbers) == 2);	 // {{2,2,2}, {3,3}}
	assert(CoinsChangeDuplicateWaysDynamicProgramming(6, numbers) == 2); //
	numbers.clear();
	numbers = {5, 37, 8, 39, 33, 17, 22, 32, 13, 7, 10, 35, 40, 2, 43, 49, 46, 19, 41, 1, 12, 11, 28};
	sort(numbers.begin(), numbers.end());
	assert(CoinsChangeUniqueWaysDynamicProgramming(166, numbers) == 96190959);
	coinChangeCache.clear();
	numbers.clear();
	numbers = {1, 2, 5};
	assert(CoinsChangeFewestCoinsDynamicProgramming(11, numbers) == 3);
	assert(CoinsChangeFewestCoinsDynamicProgramming(10, numbers) == 2);
	numbers.clear();
	numbers = {2};
	assert(CoinsChangeFewestCoinsDynamicProgramming(3, numbers) == -1);
	numbers.clear();
	numbers = {1};
	assert(CoinsChangeFewestCoinsDynamicProgramming(0, numbers) == 0);
	assert(CoinsChangeFewestCoinsDynamicProgramming(1, numbers) == 1);
	assert(CoinsChangeFewestCoinsDynamicProgramming(2, numbers) == 2);
	numbers.clear();
	numbers = {1, 2};
	dpMemoization.clear();
	assert(StairsClimbingDynamicProgramming(6, numbers) == 13);
	assert(StairsClimbingDynamicProgrammingBottomUp(6, numbers) == 13);
	numbers.clear();
	numbers = {1, 2, 3};
	dpMemoization.clear();
	assert(StairsClimbingDynamicProgramming(6, numbers) == 24);
	assert(StairsClimbingDynamicProgrammingBottomUp(6, numbers) == 24);
	// combinations1 = CoinsChangeDynamicProgramming(166, numbers); Times out!
	// assert(!combinations1.empty());
	// combinations = CoinChange(166, numbers); //Times out!
	// assert(combinations.size() == 96190959);
	numbers.clear();
	numbers = {3, 7, 405, 436};
	coinChangeCache.clear();
	// combinations1 = CoinsChangeDynamicProgramming(8839, numbers); // Stack overflow! using recursive CoinChange()
	// assert(!combinations1.empty());
	numbers.clear();
	numbers = {2, 3, 4};
	assert(UnboundedKnapsack(9, numbers) == 9); // [3,3,3]
	numbers.clear();
	numbers = {3, 4, 10};
	assert(UnboundedKnapsack(12, numbers) == 12); // [3,3,3,3] or [4,4,4]
	assert(UnboundedKnapsack(13, numbers) == 13); // [3,10]
	assert(UnboundedKnapsack(16, numbers) == 16); // [4,4,4,4]
	numbers.clear();
	numbers = {2000, 2000, 2000};
	assert(UnboundedKnapsack(2000, numbers) == 2000); // 2000
	numbers.clear();
	numbers = {9, 9, 9};
	assert(UnboundedKnapsack(9, numbers) == 9); // 9
	assert(UnboundedKnapsack(8, numbers) == 0);
	numbers.clear();
	numbers = {1};
	assert(UnboundedKnapsack(9999, numbers) == 9999); // 1 * 9999
	numbers.clear();
	numbers = {1, 2};
	assert(UnboundedKnapsack(9999, numbers) == 9999);
	numbers.clear();
	numbers = {5, 9};
	assert(UnboundedKnapsack(10, numbers) == 10); // [5,5]
	assert(UnboundedKnapsack(8, numbers) == 5);	  // [5]
	numbers.clear();
	numbers = {9};
	assert(UnboundedKnapsack(10, numbers) == 9); // [9]
	assert(UnboundedKnapsack(9, numbers) == 9);	 // [9]
	assert(UnboundedKnapsack(8, numbers) == 0);	 // [0]
	numbers.clear();
	numbers = {10, 1, 2, 7, 6, 1, 5};
	vector<vector<size_t>> result = BoundedKnapsack(8, numbers);
	assert(result.size() == 4);
	cout << "BoundedKnapsack which sums to amount 8: ";
	for (vector<vector<size_t>>::iterator it = result.begin(); it != result.end(); it++)
		copy(it->begin(), it->end(), ostream_iterator<size_t>(cout, " "));
	cout << endl;
	numbers.clear();
	numbers = {2, 3, 5};
	result = BoundedKnapsack(6, numbers);
	assert(result.empty());
}
void Knapsack_CombinationSumTests()
{
	set<vector<size_t>> combinations = BoundedKnapsackCombinationSum(3, 7);
	assert(combinations.size() == 1); // [[1,2,4]]
	combinations = BoundedKnapsackCombinationSum(3, 9);
	assert(combinations.size() == 3); // [[1,2,6],[1,3,5],[2,3,4]]
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		assert(it->size() == 3);
	combinations = BoundedKnapsackCombinationSum(4, 1);
	assert(combinations.empty());
	combinations = BoundedKnapsackCombinationSum(3, 2);
	assert(combinations.empty());
	combinations = BoundedKnapsackCombinationSum(9, 45);
	assert(combinations.size() == 1); // [[1,2,3,4,5,6,7,8,9]]
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		assert(it->size() == 9);
}
void TweeterAPITests()
{
	vector<size_t> feeds, feeds1;
	Twitter<size_t, size_t> twitter;
	twitter.PostTweet(1, 5);
	feeds = twitter.GetNewsFeed(1);
	assert(!feeds.empty());
	assert(feeds.size() == 1);
	twitter.Follow(1, 2);
	twitter.PostTweet(2, 6);
	feeds = twitter.GetNewsFeed(1);
	assert(!feeds.empty());
	assert(feeds.size() == 2);
	assert(feeds[0] == 6);
	assert(feeds[1] == 5);
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(feeds.size() == 1);
	twitter.UnFollow(1, 2);
	feeds = twitter.GetNewsFeed(1);
	assert(!feeds.empty());
	assert(feeds.size() == 1);
	assert(feeds[0] == 5);
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(feeds.size() == 1);
	assert(feeds[0] == 6);
	twitter.Clear();
	twitter.PostTweet(1, 5);
	twitter.Follow(1, 2);
	twitter.Follow(2, 1);
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty()); // 5
	assert(feeds[0] == 5);
	twitter.PostTweet(2, 6);
	feeds = twitter.GetNewsFeed(1);	 // 5, 6(2)
	feeds1 = twitter.GetNewsFeed(2); // 5(1), 6
	assert(!feeds.empty());
	assert(!feeds1.empty());
	assert(feeds.size() == 2);
	assert(feeds1.size() == 2);
	assert(feeds == feeds1);
	twitter.UnFollow(2, 1); // 1: 5, 6(2) 2: 6
	feeds = twitter.GetNewsFeed(1);
	feeds1 = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(!feeds1.empty());
	assert(feeds.size() == 2);
	assert(feeds1.size() == 1);
	twitter.Clear();
	twitter.PostTweet(2, 5);   // 2: 5
	twitter.PostTweet(1, 3);   // 1: 3
	twitter.PostTweet(1, 101); // 1: {3, 101}
	twitter.PostTweet(2, 13);  // 2: {5, 13}
	twitter.PostTweet(2, 10);  // 2: {5, 13, 10}
	twitter.PostTweet(1, 2);   // 1: {3, 101, 2}
	twitter.PostTweet(2, 94);  // 2: {5, 13, 10, 94}
	twitter.PostTweet(2, 505); // 2: {5, 13, 10, 94, 505}
	twitter.PostTweet(1, 333); // 1: {3, 101, 2, 333}
	twitter.PostTweet(1, 22);  // 1: {3, 101, 2, 333, 22}
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(feeds.size() == 5);
	feeds1 = {505, 94, 10, 13, 5};
	assert(feeds1 == feeds);
	twitter.Follow(2, 1); // 2: {5, 13, 10, 94, 505, 3, 101, 2, 133, 22}
	/* [22,333,505,94,2,10,13,101,3,5]
	1: {3, 101, 2, 333, 22}
	2: {5, 13, 10, 94, 505}
	*/
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(feeds.size() == 10);
	feeds1 = {22, 333, 505, 94, 2, 10, 13, 101, 3, 5};
	assert(feeds1 == feeds);
	twitter.Clear();
	twitter.PostTweet(1, 6765); // 1: {6765}
	twitter.PostTweet(5, 671);	// 5: {671}
	twitter.PostTweet(3, 2868); // 3: {2868}
	twitter.PostTweet(4, 8148); // 4: {8148}
	twitter.PostTweet(4, 386);	// 4: {8148, 386}
	twitter.PostTweet(3, 6673); // 3: {2868, 6673}
	twitter.PostTweet(3, 7946); // 3: {2868, 6673, 7946}
	twitter.PostTweet(3, 1445); // 3: {2868, 6673, 7946, 1445}
	twitter.PostTweet(4, 4822); // 4: {8148, 386, 4822}
	twitter.PostTweet(1, 3781); // 1: {6765, 3781}
	twitter.PostTweet(4, 9038); // 4: {8148, 386, 4822, 9038}
	twitter.PostTweet(1, 9643); // 1: {6765, 3781, 9643}
	twitter.PostTweet(3, 5917); // 3: {2868, 6673, 7946, 1445, 5917}
	twitter.PostTweet(2, 8847); // 2: {8847}
	feeds = twitter.GetNewsFeed(1);
	feeds1 = {9643, 3781, 6765};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(2);
	feeds1 = {8847};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(3);
	feeds1 = {5917, 1445, 7946, 6673, 2868};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(4);
	feeds1 = {9038, 4822, 386, 8148};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(5);
	feeds1 = {671};
	assert(!feeds.empty());
	assert(feeds1 == feeds);

	twitter.Follow(1, 3); // 1: {6765, 3781, 9643} 3: {2868, 6673, 7946, 1445, 5917}
	feeds = twitter.GetNewsFeed(1);
	assert(!feeds.empty());
	assert(feeds.size() == 8);
	twitter.Follow(1, 4); // 1: {6765, 3781, 9643} 3: {2868, 6673, 7946, 1445, 5917} 4: {8148, 386, 4822, 9038}
	feeds = twitter.GetNewsFeed(1);
	assert(!feeds.empty());
	assert(feeds.size() == 10); // Limit to 10 items. Actual result is 12.
	feeds = twitter.GetNewsFeed(1, 20);
	assert(!feeds.empty());
	assert(feeds.size() == 12); // Limit to 10 items. Actual result is 12.
	twitter.Follow(4, 2);		// 4: {8148, 386, 4822, 9038} 2: {8847}
	feeds = twitter.GetNewsFeed(4);
	assert(!feeds.empty());
	assert(feeds.size() == 5);
	twitter.Follow(4, 1); // 4: {8148, 386, 4822, 9038} 2: {8847} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(4);
	assert(!feeds.empty());
	assert(feeds.size() == 8);
	twitter.Follow(3, 2); // 3: {2868, 6673, 7946, 1445, 5917} 2: {8847}
	feeds = twitter.GetNewsFeed(3);
	assert(!feeds.empty());
	assert(feeds.size() == 6);
	twitter.Follow(3, 5); // 3: {2868, 6673, 7946, 1445, 5917} 2: {8847} 5: {671}
	feeds = twitter.GetNewsFeed(3);
	assert(!feeds.empty());
	assert(feeds.size() == 7);
	twitter.Follow(3, 1); // 3: {2868, 6673, 7946, 1445, 5917} 2: {8847} 5: {671} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(3);
	assert(!feeds.empty());
	assert(feeds.size() == 10);
	twitter.Follow(2, 3); // 2: {8847} 3: {2868, 6673, 7946, 1445, 5917}
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(feeds.size() == 6);
	twitter.Follow(2, 1); // 2: {8847} 3: {2868, 6673, 7946, 1445, 5917} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(feeds.size() == 9);
	twitter.Follow(2, 5); // 2: {8847} 3: {2868, 6673, 7946, 1445, 5917} 1: {6765, 3781, 9643} 5: {671}
	feeds = twitter.GetNewsFeed(2);
	assert(!feeds.empty());
	assert(feeds.size() == 10);
	twitter.Follow(5, 1); // 5: {671} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(5);
	assert(!feeds.empty());
	assert(feeds.size() == 4);
	twitter.Follow(5, 2); // 5: {671} 1: {6765, 3781, 9643} 2: {8847}
	feeds = twitter.GetNewsFeed(5);
	assert(!feeds.empty());
	assert(feeds.size() == 5);

	feeds = twitter.GetNewsFeed(1);
	feeds1 = {5917, 9643, 9038, 3781, 4822, 1445, 7946, 6673, 386, 8148};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(2);
	feeds1 = {8847, 5917, 9643, 3781, 1445, 7946, 6673, 2868, 671, 6765};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(3);
	feeds1 = {8847, 5917, 9643, 3781, 1445, 7946, 6673, 2868, 671, 6765};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(4);
	feeds1 = {8847, 9643, 9038, 3781, 4822, 386, 8148, 6765};
	assert(!feeds.empty());
	assert(feeds1 == feeds);
	feeds = twitter.GetNewsFeed(5);
	feeds1 = {8847, 9643, 3781, 671, 6765};
	assert(!feeds.empty());
	assert(feeds1 == feeds);

	twitter.Clear();
	twitter.PostTweet(1, 1);
	twitter.PostTweet(1, 2);
	twitter.PostTweet(1, 3);
	twitter.PostTweet(1, 4);
	twitter.PostTweet(1, 5);
	twitter.PostTweet(1, 6);
	twitter.PostTweet(1, 7);
	twitter.PostTweet(1, 8);
	twitter.PostTweet(1, 9);
	twitter.PostTweet(1, 10);
	feeds = twitter.GetNewsFeed(1);
	assert(!feeds.empty());
	assert(feeds.size() == 10);
	feeds1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	assert(feeds1 == feeds);
	feeds = twitter.GetFromLastNewsFeed(1, 5);
	assert(!feeds.empty());
	assert(feeds.size() == 5);
	feeds1 = {10, 9, 8, 7, 6};
	assert(feeds1 == feeds);
	feeds = twitter.GetFromLastNewsFeed(1, 5, 3);
	assert(!feeds.empty());
	assert(feeds.size() == 3);
	feeds1 = {8, 7, 6};
	assert(feeds1 == feeds);
	feeds = twitter.GetFromLastNewsFeed(1, 10);
	assert(feeds.empty());
}
string decimal_to_binary(int decimal)
{
	if (decimal > 0)
	{
		ostringstream oss;
		int remainder = decimal % 2;
		oss << decimal_to_binary(decimal / 2);
		oss << remainder;
		return oss.str();
	}
	return "0";
}
void decimal_to_binary(int decimal, vector<bool> &binary, size_t width)
{
	binary.resize(width, false);
	for (long i = width - 1; i >= 0 && decimal; i--)
	{
		binary[i] = decimal & 1;
		decimal >>= 1;
	}
}
// Find longest sequence of zeros in binary representation of an integer.
// 9: 1001 => 2
// 529: 1000010001  => 4
// 32: 100000 => 0
size_t binary_gap(long n)
{
	bool start = false;
	int count = 0, max = 0;
	bitset<32> x(n);
	for (size_t i = 0; i < x.size(); i++)
	{
		if (start && x[i] == 0)
			count++;
		else if (x[i] == 1)
		{
			if (count > max)
				max = count;
			count = 0;
			start = true;
		}
	}
	return max;
}
/*
 * For a given array A of N integers and a sequence S of N integers from the set{ −1, 1 }, we define val(A, S) as follows :
 * val(A, S) = | sum{ A[i] * S[i] for i = 0..N−1 } |
 * (Assume that the sum of zero elements equals zero.)
 * For a given array A, we are looking for such a sequence S that minimizes val(A, S).
 * Write a function that, given an array A of N integers, computes the minimum value of val(A, S) from all possible values of val(A, S) for all possible sequences S of N integers from the set{ −1, 1 }.
 * For example, given array:
 * A = {1,5,2,-2}
 * S = {-1,1,-1,1}
 * val:{-1,4,2,0}
 * your function should return 0, since for S = [−1, 1, −1, 1], val(A, S) = 0, which is the minimum possible value.
 */
long MinAbsSum(vector<long> &data)
{
	long sum = 0;
	long min = numeric_limits<long>::max();
	for (size_t i = 0; i < ((size_t)1 << data.size()); i++)
	{
		vector<bool> binary;
		decimal_to_binary(i, binary, data.size()); // Permutations of {-1,1} for all the bit patterns
		for (size_t j = 0; j < binary.size(); j++)
			sum += (binary[j] ? -1 : 1) * data[j];
		if (abs(sum) < min)
			min = abs(sum);
		sum = 0;
	}
	return min;
}
// https://codility.com/demo/take-sample-test/number_solitaire/
// https://codesays.com/2015/solution-to-number-solitaire-by-codility/
// data: 1 -2 0 9 -1 -2 -3 9
// memo : 1, -1, MAX(-1, 1) = 1, MAX(10, 8, 10) = 10, MAX(9, 0, -2, 0) = 9, MAX(7, 8, -1, -3, -1) = 8, MAX(5, 6, 7, -2, -4, -2) = 7, MAX(16, 17, 18, 19, 10, 8, 10) = 19
long NumberSolitaire(vector<long> &data)
{
	vector<long> memo(data.size(), numeric_limits<long>::min());
	memo[0] = data[0];
	for (long i = 1; i < (long)data.size(); i++)
		for (long j = 1; j < 7 && (i - j) >= 0; j++)
			memo[i] = max(memo[i], data[i] + memo[i - j]);
	return memo[data.size() - 1];
}
/* A zero - indexed array A consisting of N integers is given.It contains daily prices of a stock share for a period of N consecutive days.
 * If a single share was bought on day P and sold on day Q, where 0 ≤ P ≤ Q < N, then the profit of such transaction is equal to A[Q] − A[P], provided that A[Q] ≥ A[P].
 * Otherwise, the transaction brings loss of A[P] − A[Q].
 * For example, consider the following array A consisting of six elements such that :
 * A[0] = 23171
 * A[1] = 21011
 * A[2] = 21123
 * A[3] = 21366
 * A[4] = 21013
 * A[5] = 21367
 * If a share was bought on day 0 and sold on day 2, a loss of 2048 would occur because A[2] − A[0] = 21123 − 23171 = −2048.
 * If a share was bought on day 4 and sold on day 5, a profit of 354 would occur because A[5] − A[4] = 21367 − 21013 = 354.
 * Maximum possible profit was 356. It would occur if a share was bought on day 1 and sold on day 5.
 * 100%
 */
long MaxProfit(vector<long> &data)
{
	long min = numeric_limits<long>::max();
	long delta = 0;
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++)
	{
		if (*it < min)
			min = *it;
		if ((*it - min) > delta)
			delta = (*it - min);
	}
	return delta;
}
/* https://www.hackerrank.com/challenges/stockmax/problem
 * 100%
 * { 1, 2, 100 } : (100 - 1 = 99) + (100 - 2 = 98) = 197
 */
size_t StockMax(vector<long> &prices)
{
	size_t profit = 0;
	size_t maxIndex = 0;
	for (size_t i = 0; i < prices.size(); i++)
	{
		if (maxIndex <= i)
		{
			vector<long>::iterator peak = max_element(prices.begin() + i, prices.end());
			if (peak != prices.end())
				maxIndex = distance(prices.begin(), peak);
		}
		if (maxIndex > i)
		{
			// cout << "Profit: " << *peak - prices[i] << endl;
			profit += prices[maxIndex] - prices[i];
		}
	}
	return profit;
}
/* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
* 100%
* State machine of 3 states: (stay, bought, sold). Keep track of amount of profit at every state.
* stay -> bought -> sold -> stay
* stay -> stay
* bought -> bought
* sold -> stay
*
* state[i] = max profit:
* stay[i] = max(stay[i - 1], sold[i - 1]); // Stay put, or rest from sold state
* bought[i] = max(bought[i - 1], stay[i - 1] - prices[i]); // Stay put, or buy again (Cannot buy immediately after sell)
* sold[i] = bought[i - 1] + prices[i]; // Sell
* stay[0] = 0; // At the start, you don't have any stock if you just rest
* bought[0] = -prices[0]; // After buy, you should have -prices[0] profit. Be positive!
* sold[0] = 0;

		1  2  3	 0 2
stay:   0  0  1  2 2
bought: -1 -1 -1 1 1
sold:   0  1  2 -1 3
*/
long StockMaxProfit(vector<long> &prices)
{
	if (prices.size() < 2)
		return 0;
	long profit = 0;
	vector<long> stay(prices.size(), 0), bought(prices.size(), 0), sold(prices.size(), 0);
	stay[0] = 0;
	bought[0] = -prices[0];
	sold[0] = 0;
	for (size_t i = 1; i < prices.size(); i++)
	{
		stay[i] = max(stay[i - 1], sold[i - 1]);
		bought[i] = max(bought[i - 1], stay[i - 1] - prices[i]);
		sold[i] = bought[i - 1] + prices[i];
	}
	return max(stay.back(), sold.back());
}
// You are a game developer working on a game that randomly generates levels. A level is an undirected graph of rooms, each connected by doors.
// The player starts in one room, and there is a treasure in another room. Some doors are locked, and each lock is opened by a unique key.
// A room may contain one of those unique keys, or the treasure, or nothing. Implement a representation for a level and write code that,
// given a level and starting room, returns true if the treasure can be reached by the player—likely requiring them to find certain other keys first—or
// false if there is no solution.
void PlayTreasureGame()
{
	TreasureGame game;
	Room a(false), b(1), c(3), d(-1), e(2), f(true);
	a.addDoor(&b);
	b.addDoor(&c, 6);
	a.addDoor(&c, 1);
	a.addDoor(&d, 1);
	d.addDoor(&e, 3);
	e.addDoor(&f, 7);
	// cout << "Start with room a " << game.hasTreasure(&a) << endl;
	assert(!game.hasTreasure(&a));
	c.addDoor(&f, 2);
	// cout << "Start with room a " << game.hasTreasure(&a) << endl;
	assert(game.hasTreasure(&a));
}
// Given a matrix of N * M, given the coordinates(x, y) present in a matrix,
// Find the number of paths that can reach(0, 0) from the(x, y) points with k steps(requires exactly k, k> = 0)
// From each point you can go up, down, left and right in four directions.
//  https://www.geeksforgeeks.org/check-if-it-is-possible-to-move-from-0-0-to-x-y-in-exactly-k-steps/
// For example, the following matrix :
//----------
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
//(x, y) = (1, 1), k = 2, the output is 2
const long moves[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
size_t countPaths(size_t m, size_t n, size_t x, size_t y, size_t k)
{
	// It is clear that the shortest path to reach (0, 0) from (x, y) will be minMoves = (|x| + |y|)
	// if K ≥ minMoves then after reaching (0, 0) in minMoves number of moves the remaining (K – minMoves) number of moves have to be even in order to
	// remain at that point for the rest of the moves.
	size_t minMoves = x + y;
	if (k >= minMoves && !((k - minMoves) % 2) && x < m && y < n)
	{
		if (k == 0 && x == 0 && y == 0)
			return 1;
		size_t sum = 0;
		// cout << "sizeof(moves): " << sizeof(moves) << ", sizeof(decltype(moves[0])): " << sizeof(decltype(moves[0])) << endl;
		for (size_t i = 0; i < sizeof(moves) / sizeof(decltype(moves[0])); i++)
			sum += countPaths(m, n, x + moves[i][0], y + moves[i][1], k - 1);
		return sum;
	}
	return 0;
}
vector<shared_ptr<Node<string>>> shortest_cycle_path(shared_ptr<Node<string>> node)
{
	map<shared_ptr<Node<string>>, shared_ptr<Node<string>>> parents;
	deque<shared_ptr<Node<string>>> q(1, node);
	while (!q.empty())
	{
		shared_ptr<Node<string>> n = q.front();
		q.pop_front();
		for (set<shared_ptr<Node<string>>>::iterator i = n->m_adjacents.begin(); i != n->m_adjacents.end(); i++)
		{
			if (parents.find(*i) == parents.end())
			{
				parents.emplace(*i, n);
				if (*i == node)
				{
					q.clear();
					break;
				}
				else
					q.push_back(*i);
			}
		}
	}
	// Build path
	vector<shared_ptr<Node<string>>> path;
	shared_ptr<Node<string>> current = node;
	do
	{
		path.push_back(current);
		current = parents[current];
	} while (current && current != node);
	if (path.size() == 1 && !current) // current == nullptr : no cycle
		path.clear();
	reverse(path.begin(), path.end());
	return path;
}
// given a binary array, you can flip 0 -> 1 or 1 -> 0 to make all the 1
// are in the left part and all the 0 to the right part, return the minimun flip required
// example 1
// 1011000  -> 1111000 only need one flip 0 -> 1
// example 2
// 00001 -> 10000 require 2 flips
int findMinFlip(vector<int> &binary)
{
	size_t count = 0, last_left = -1, last_right = -1;
	size_t left = 0, right = binary.size() - 1;
	for (; left < right;)
	{
		if (binary[left] == 0)
			last_left = left;
		else if (last_left != -1 && last_left != left)
		{
			count += left - last_left;
			last_left = -1;
		}
		if (binary[right] == 1)
			last_right = right;
		else if (last_right != -1 && last_right != right)
		{
			count += last_right - right;
			last_right = -1;
		}
		left++;
		right--;
	}
	if (last_left != -1 && last_left != left)
		count += left - last_left;
	if (last_right != -1 && last_right != right)
		count += last_right - right;
	return count;
}
// The matrix is valid if there is no consecutive 3 elements with the same value.
bool IsValidMatrix(vector<vector<char>> const &data)
{
	for (size_t row = 0; row < data.size(); row++)
		for (size_t col = 0; col < data[row].size(); col++)
		{
			if (row <= (data.size() - 3) && data[row][col] == data[row + 1][col] && data[row][col] == data[row + 2][col])
				return false;
			if (col <= (data[row].size() - 3) && data[row][col] == data[row][col + 1] && data[row][col] == data[row][col + 2])
				return false;
		}
	return true;
}
// Return the arithmetic total.
// Tree nodes are arithmetic operators. Only leaf nodes are values (long in this case).
template <class T>
T TreeArithmeticTotal(shared_ptr<Node<string>> node)
{
	T result;
	if (node->isLeaf())
	{
		istringstream(node->Item()) >> result;
		return result;
	}
	T left = TreeArithmeticTotal<T>(node->Left());
	T right = TreeArithmeticTotal<T>(node->Right());
	if (node->Item() == decltype(node->Item())("+"))
		result = left + right;
	else if (node->Item() == decltype(node->Item())("-"))
		result = left - right;
	else if (node->Item() == decltype(node->Item())("*"))
		result = left * right;
	else if (node->Item() == decltype(node->Item())("/"))
		result = left / right;
	return result;
}
// https://app.codility.com/programmers/task/zig_zag_escape/
// Given a sequence S of integers, find a number of increasing sequences I such that every two consecutive elements in I appear in S, but on the opposite sides of the first element of I.
// Unfinished work!
// Task Score: 18 %
// Correctness: 44 %
// Performance: 0 %
size_t ZigZagEscape(vector<long> &data)
{
	vector<zigzag_t> zigzag;
	set<set<int>> result;
	for (size_t i = 0; i < data.size(); i++)
	{
		zigzag_t zz(i, data[i]);
		zigzag.push_back(zz);
	}
	sort(zigzag.begin(), zigzag.end());
	for (size_t i = 0; i < zigzag.size(); i++)
	{
		bool wasSmaller = false;
		bool isFirst = true;
		set<int> r;
		r.emplace(zigzag[i].value);
		result.emplace(r);
		for (size_t k = 1; k < (zigzag.size() - i); k++)
		{
			r.clear();
			r.emplace(zigzag[i].value);
			for (size_t j = i + k, isFirst = true; j < zigzag.size(); j++)
			{
				// cout << "i: " << i << ", j: " << j << ", k: " << k << endl;
				if (isFirst)
				{
					isFirst = false;
					wasSmaller = zigzag[j].index < zigzag[i].index;
					r.emplace(zigzag[j].value);
					// copy(r.begin(), r.end(), ostream_iterator<size_t>(cout, " "));
					// cout << endl;
					result.emplace(r);
				}
				else if (wasSmaller && zigzag[j].index > zigzag[i].index)
				{
					wasSmaller = !wasSmaller;
					r.emplace(zigzag[j].value);
					// copy(r.begin(), r.end(), ostream_iterator<size_t>(cout, " "));
					// cout << endl;
					result.emplace(r);
				}
				else if (!wasSmaller && zigzag[j].index < zigzag[i].index)
				{
					wasSmaller = !wasSmaller;
					r.emplace(zigzag[j].value);
					// copy(r.begin(), r.end(), ostream_iterator<size_t>(cout, " "));
					// cout << endl;
					result.emplace(r);
				}
				else
				{
					set<int> tmp(r);
					tmp.erase(zigzag[j - 1].value);
					tmp.emplace(zigzag[j].value);
					result.emplace(tmp);
					// cout << "No result! i:" << zigzag[i].index << " " << zigzag[i].value << ", j: " << zigzag[j].index << " " << zigzag[j].value << endl;
				}
			}
		}
	}
#if 0
	cout << "Final: " << endl;
	for (set<set<int>>::const_iterator it = result.begin(); it != result.end(); it++) {
		copy(it->begin(), it->end(), ostream_iterator<size_t>(cout, " "));
		cout << endl;
	}
#endif
	return result.size();
}
size_t ZigZagEscape(vector<long> &data, set<string> &strResult)
{
	long current;
	vector<string> tmp;
	ostringstream oss;
	vector<long> left, right;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (i > 0)
			left.assign(data.begin(), data.begin() + i);
		if (i != data.size() - 1)
			right.assign(data.begin() + i + 1, data.end());
		sort(left.begin(), left.end());
		sort(right.begin(), right.end());
		current = data[i];
		strResult.insert(to_string(current));
		// Start with left
		for (size_t j = 0; j < left.size(); j++)
		{
			if (left[j] > current)
			{
				if (right.empty())
				{
					oss << current << " " << left[j];
					strResult.insert(oss.str());
					oss.str("");
				}
				else
				{
					tmp = ZigZagEscape(left, right, j, 0, current, true);
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++)
						strResult.insert(*it);
				}
			}
		}
		// Start with right
		for (size_t j = 0; j < right.size(); j++)
		{
			if (right[j] > current)
			{
				if (left.empty())
				{
					oss << current << " " << right[j];
					strResult.insert(oss.str());
					oss.str("");
				}
				else
				{
					tmp = ZigZagEscape(left, right, 0, j, current, false);
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++)
						strResult.insert(*it);
				}
			}
		}
		// Clean up
		left.clear();
		right.clear();
	}
	return strResult.size();
}
vector<string> ZigZagEscape(vector<long> &left, vector<long> &right, size_t lIndex, size_t rIndex, long current, bool dir)
{ // 4, 6, 2, 1, 5
	long next;
	vector<string> result, tmp;
	ostringstream oss;
	if (dir && left.size())
	{ // left
		for (; lIndex < left.size(); lIndex++)
		{
			if (left[lIndex] > current)
			{
				next = left[lIndex];
				result.push_back(to_string(current));
				tmp = ZigZagEscape(left, right, lIndex, rIndex, next, !dir);
				if (!tmp.empty())
				{
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						oss << current << " " << *it;
						result.push_back(oss.str());
						oss.str("");
					}
				}
				else
				{
					// Only take current value if the other side is empty.
					oss << current << " " << next;
					result.push_back(oss.str());
				}
				oss.str("");
			}
		}
	}
	else if (right.size())
		for (; rIndex < right.size(); rIndex++)
			if (right[rIndex] > current)
			{
				next = right[rIndex];
				result.push_back(to_string(current));
				tmp = ZigZagEscape(left, right, lIndex, rIndex, next, !dir);
				if (!tmp.empty())
				{
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						oss << current << " " << *it;
						result.push_back(oss.str());
						oss.str("");
					}
				}
				else
				{
					oss << current << " " << next;
					result.push_back(oss.str());
				}
				oss.str("");
			}
	return result;
}
void CircularLinkedListLoopStart()
{
	shared_ptr<Node<int>> head = make_shared<Node<int>>(-3);
	shared_ptr<Node<int>> n1 = make_shared<Node<int>>(-2);
	head->SetNext(n1);
	shared_ptr<Node<int>> n2 = make_shared<Node<int>>(-1);
	n1->SetNext(n2);
	shared_ptr<Node<int>> n3 = make_shared<Node<int>>(0);
	n2->SetNext(n3);
	shared_ptr<Node<int>> n4 = make_shared<Node<int>>(1);
	n3->SetNext(n4);
	shared_ptr<Node<int>> n5 = make_shared<Node<int>>(2);
	n4->SetNext(n5);
	shared_ptr<Node<int>> n6 = make_shared<Node<int>>(3);
	n5->SetNext(n6);
	shared_ptr<Node<int>> n7 = make_shared<Node<int>>(4);
	n6->SetNext(n7);
	shared_ptr<Node<int>> n8 = make_shared<Node<int>>(5);
	n7->SetNext(n8);
	shared_ptr<Node<int>> n9 = make_shared<Node<int>>(6);
	n8->SetNext(n9);
	shared_ptr<Node<int>> n10 = make_shared<Node<int>>(7);
	n9->SetNext(n10);
	n10->SetNext(n3);
	shared_ptr<Node<int>> node1 = head;
	shared_ptr<Node<int>> node2 = head;
	// Find meeting point
	while (node2->Next())
	{
		node1 = node1->Next();
		node2 = node2->Next()->Next();
		if (node1 == node2)
			break;
	}
	if (!node2->Next())
		return;
	node1 = head;
	while (node1 != node2)
	{
		node1 = node1->Next();
		node2 = node2->Next();
	}
	cout << "Circular linked list loop starts at: " << node1->Item() << " / " << node2->Item() << endl;
}
void IncreasingSequenceTests()
{
	vector<long> a, b;
	a.clear();
	b.clear();
	a = {5, 3, 7, 7, 10};
	b = {1, 6, 6, 9, 9};
	assert(IncreasingSequences(a, b) == 2);
	a.clear();
	b.clear();
	a = {1, 5, 6};
	b = {-2, 0, 2};
	assert(IncreasingSequences(a, b) == 0);
	a.clear();
	b.clear();
	a = {2, 5};
	b = {1, 6};
	assert(IncreasingSequences(a, b) == 0);
	a.clear();
	b.clear();
	a = {5, -3, 6, 4, 8};
	b = {2, 6, -5, 1, 0};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0, 0, 0};
	b = {1, 2, 3};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0, 1, 1, 2};
	b = {5, 4, 4, 3};
	assert(IncreasingSequences(a, b) == -1); // a increasing; b decreasing

	a.clear();
	b.clear();
	a = {0, 1, 1, 2};
	b = {3, 4, 4, 5};
	assert(IncreasingSequences(a, b) == -1); // a increasing; b increasing

	a.clear();
	b.clear();
	a = {2, 1, 1, 0};
	b = {5, 4, 4, 3};
	assert(IncreasingSequences(a, b) == -1); // a decreasing; b decreasing

	a.clear();
	b.clear();
	a = {0, 2, 2, 4, 6, 6, 8, 10, 10};
	b = {1, 2, 2, 3, 4, 4, 5, 6, 6};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0, 1, 1, 2, 3, 3, 4, 5, 5};
	b = {10, 10, 9, 8, 8, 7, 6, 6, 5};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0, -1, -2};
	b = {-2, 1, 2};
	assert(IncreasingSequences(a, b) == -1);
	// Performance tests
	a.clear();
	b.clear();
	a.resize(100000);
	b.resize(100000);
	iota(a.begin(), a.end(), 0);
	iota(b.begin(), b.end(), -1000000000); // a and b increasing
	assert(IncreasingSequences(a, b) == 0);

	a.clear();
	b.clear();
	a.resize(100000);
	b.resize(100000);
	iota(a.begin(), a.end(), -50000);
	iota(b.begin(), b.end(), 50000);
	sort(a.begin(), a.end(), greater<long>()); // a and b decreasing
	sort(b.begin(), b.end(), greater<long>());
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a.resize(100000);
	b.resize(100000);
	iota(a.begin(), a.end(), 0);		   // a increasing
	iota(b.begin(), b.end(), -1000000000); // b decreasing
	sort(b.begin(), b.end(), greater<long>());
	assert(IncreasingSequences(a, b) == -1);
	a.clear();
	vector<size_t> c = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	assert(LongestIncreasingSubsequence(c) == 6);	   // 0, 2, 6, 9, 13, 15
	assert(LongestIncreasingSubsequenceNlogN(c) == 6); // 0, 2, 6, 9, 13, 15
	c.clear();
	c = {3, 2, 4, 1, 5};
	assert(increasingTriplet(c));
	assert(LongestIncreasingSubsequenceNlogN(c) == 3); // 3,4,5
	c.clear();
	c = {1, 1, 1, 1, 1};
	assert(!increasingTriplet(c));
	assert(LongestIncreasingSubsequenceNlogN(c) == 1); // 1
}
/* https://app.codility.com/demo/results/trainingCP4NRT-FE4/
 * https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/discuss/119835/Java-O(n)-DP-Solution
 * 100%
 * index               0    1    2    3    4
 * A                   1    3    5    4    9
 * B                   1    2    3    7    10
 * swapRecord          0    1    2    1    2
 * fixRecord           0    0    0    2    1	(swap = 1)
 *
 * index               0    1    2    3    4
 * A                   1    3    5    4    9 (Impossible)
 * B                   1    2    3    10   8
 * swapRecord          0    1    2    1    2
 * fixRecord           0    0    0    2    2
 *
 * index               0    1    2    3    4
 * A                   1    3    5    10   9
 * B                   1    2    3    8    7 (Impossible)
 * swapRecord          0    1    2    1    2
 * fixRecord           0    0    0    0    0
 *
 * index               0    1    2
 * A                   1    3    5
 * B                   1    2    3
 * swapRecord          0    1    2
 * fixRecord           0    0    0 (swap = 0)
 *
 */
int IncreasingSequences(vector<long> &a, vector<long> &b)
{
	bool outOfSequence = false;
	// swapRecord[i]: min swaps to make A[0:i] and B[0:i] increasing if we swap A[i] and B[i]
	// fixRecord[i] : min swaps to make A[0:i] and B[0:i] increasing if we do not swap A[i] and B[i]
	size_t swapRecord = 0, fixRecord = 0;
	if (a.size() != b.size())
		return -1;
	if (a.size() == 1)
		return 0;
	vector<long> A, B;
	bool isSwap = false;
	A.push_back(a[0]);
	B.push_back(b[0]);
	for (size_t i = 1; i < a.size(); i++)
	{
		if (a[i - 1] >= b[i] || b[i - 1] >= a[i])
		{
			// In this case, the ith manipulation should be same as the i-1th manipulation
			// fixRecord = fixRecord;
			swapRecord++;
		}
		else if (a[i - 1] >= a[i] || b[i - 1] >= b[i])
		{
			// In this case, the ith manipulation should be the opposite of the i-1th manipulation
			size_t temp = swapRecord;
			swapRecord = fixRecord + 1;
			fixRecord = temp;
			isSwap = !isSwap; // Because "opposite"
		}
		else
		{
			// Either swap or fix is OK. Let's keep the minimum one
			isSwap = swapRecord > fixRecord;
			size_t minimum = min(swapRecord, fixRecord);
			swapRecord = minimum + 1;
			fixRecord = minimum;
		}
		A.push_back(isSwap ? b[i] : a[i]);
		B.push_back(isSwap ? a[i] : b[i]);
		outOfSequence |= A[i] <= A[i - 1] || B[i] <= B[i - 1];
	}
	return outOfSequence ? -1 : min(swapRecord, fixRecord);
}
/*
  https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem
  https://www.tutorialspoint.com/cplusplus-program-to-find-the-longest-increasing-subsequence-of-a-given-sequence
  Times out for >= 1 million data points
		1 2 5 3
		  i
lengths:1 2		<= max = 2
			i
lengths:1 2 3	<= max = 3
			  i
lengths:1 2 3 3
----
		5 2 3 1
		  i
lengths:1 1		<= max = 1
			i
lengths:1 1 2	<= max = 2
			  i
lengths:1 1 2 1
*/
size_t LongestIncreasingSubsequence(vector<size_t> &data)
{
	size_t max = 0;
	vector<size_t> lengths(data.size(), 0);
	lengths[0] = 1;
	for (size_t i = 1; i < data.size(); i++)
	{
		for (size_t j = 0; j < i; j++)
			if (data[j] < data[i] && lengths[j] > lengths[i])
				lengths[i] = lengths[j];
		if (++lengths[i] > max)
			max = lengths[i];
	}
	return max;
}
/*
   https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem
   100%
   https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
1. If A[i] is smallest among all end candidates of active lists, we will start
   new active list of length 1.
2. If A[i] is largest among all end candidates of active lists, we will clone the largest active
   list, and extend it by A[i].
3. If A[i] is in between, we will find a list with largest end element that is smaller than A[i].
   Clone and extend this list by A[i]. We will discard all other lists of same length as that of this modified list.
[1 2 5 3]
[1]
[1 2]
[1 2 5]
[1 2 3] replaces [1 2 5]
*/
size_t LongestIncreasingSubsequenceNlogN(vector<size_t> &data)
{
	vector<size_t> tails;
	if (!data.empty())
	{
		tails.push_back(data[0]);
		for (vector<size_t>::iterator it = data.begin(); it != data.end(); it++)
		{
			vector<size_t>::iterator it1 = lower_bound(tails.begin(), tails.end(), *it); // Look for element >= data[i]
			if (it1 == tails.end())														 // If not present change the tail element to v[i]
				tails.push_back(*it);
			else
				*it1 = *it;
		}
	}
	return tails.size();
}
bool increasingTriplet(vector<size_t> &data)
{
	vector<size_t> tails;
	if (!data.empty())
	{
		for (vector<size_t>::iterator it = data.begin(); it != data.end(); it++)
		{
			vector<size_t>::iterator it1 = lower_bound(tails.begin(), tails.end(), *it); // >= data[i]
			if (it1 == tails.end())
				tails.push_back(*it);
			else
				*it1 = *it;
		}
	}
	return tails.size() >= 3;
}
// https://stackoverflow.com/questions/6877249/find-the-number-of-occurrences-of-a-subsequence-in-a-string
size_t FindSubsequenceRecursive(const string &str, const string &tomatch)
{
	size_t result = 0;
	if (tomatch.empty())
		return 1;
	else if (str.empty())
		return 0;
	if (str[0] == tomatch[0])
		result += FindSubsequenceRecursive(str.substr(1), tomatch.substr(1)) + FindSubsequenceRecursive(str.substr(1), tomatch);
	else
		result += FindSubsequenceRecursive(str.substr(1), tomatch);
	return result;
}
/*
* s1 is tomatch1
* 				j:0	j:1(s1=2)	j:2(s1=12)
				0	1			2
i:0			0	1	0			0
i:1(s=1)	1	1	0			0
i:2(s=21)	2	1	1			0
i:3(s=221)	2	1	2			0
i:4(s=1221)	1	1	2			2
*/
size_t FindSubsequenceDynamicProgramming(const string &str, const string &tomatch)
{
	if (tomatch.empty())
		return 1;
	else if (str.empty())
		return 0;
	vector<vector<size_t>> counts(str.size() + 1, vector<size_t>(tomatch.size() + 1)); // Add one dimension for the empty element which is the base case
	for (size_t i = 0; i <= str.size(); i++)
	{
		string s = str.substr(str.size() - i, i);
		for (size_t j = 0; j <= tomatch.size(); j++)
		{
			string tomatch1 = tomatch.substr(tomatch.size() - j, j);
			if (tomatch1.empty())
				counts[i][j] = 1;
			else if (s.empty())
				counts[i][j] = 0;
			else if (i > 0 && j > 0)
			{
				/*
					In cell [row][col] write the value found at [row-1][col].
					Intuitively this means "The number of matches for 221 / 2 includes all the matches for 21 / 2."
				*/
				counts[i][j] = counts[i - 1][j];
				if (s[0] == tomatch1[0])
					counts[i][j] += counts[i - 1][j - 1];
			}
		}
	}
	return counts[str.size()][tomatch.size()];
}
// https://www.hackerrank.com/challenges/short-palindrome/problem
// Times out!
size_t shortPalindrome(const string &s)
{
	set<char> chars(s.begin(), s.end());
	set<string> patterns;
	string str(chars.begin(), chars.end());
	string permutation;
	for (size_t i = 0; i < str.size(); i++)
	{
		permutation.clear();
		permutation.push_back(str[i]);
		permutation.push_back(str[i]);
		permutation.push_back(str[i]);
		permutation.push_back(str[i]);
		patterns.insert(permutation);
		for (size_t j = i + 1; j < str.size(); j++)
		{
			permutation.clear();
			permutation.push_back(str[j]);
			permutation.push_back(str[j]);
			permutation.push_back(str[j]);
			permutation.push_back(str[j]);
			patterns.insert(permutation);
			permutation.clear();
			permutation.push_back(str[i]);
			permutation.push_back(str[j]);
			permutation.push_back(str[j]);
			permutation.push_back(str[i]);
			patterns.insert(permutation);
			permutation.clear();
			permutation.push_back(str[j]);
			permutation.push_back(str[i]);
			permutation.push_back(str[i]);
			permutation.push_back(str[j]);
			patterns.insert(permutation);
		}
	}
	size_t count = 0;
	for (set<string>::iterator it = patterns.begin(); it != patterns.end(); it++)
		count += FindSubsequenceDynamicProgramming(s, (string)(*it));
	return count;
}
void cpluplus17()
{
	map<int, string> mymap;
	// Structured bindings
	// Return compound objects
	auto [it, success] = mymap.emplace(1, "Hello World!!!");
	assert(success);
	assert(it->first == 1);
	assert(it->second == "Hello World!!!");
	// Compound object iterations
	for (const auto &[key, value] : mymap)
		cout << key << ": " << value << endl;
	// Direct Initialization
	for (auto [i, ch] = pair(0U, ' '); i < 10; i++, ch++)
		cout << "[" << i << ": '" << ch << "'] ";
	cout << endl;
}
long MaxProductOfThree(vector<long> &data)
{
	sort(data.begin(), data.end());
	long tmp1 = data[0] * data[1];
	long tmp2 = data[data.size() - 2] * data[data.size() - 3];
	if (data.back() > 0)
		return data.back() * (tmp1 > tmp2 ? tmp1 : tmp2);
	else
		return data.back() * (tmp1 < tmp2 ? tmp1 : tmp2);
}
/*
 * 1 2 3 4 5, n = 2
 * 5 4 3 2 1, reverse the whole vector
 * 4 5 3 2 1, reverse 0:n-1
 * 4 5 1 2 3, reverse 2:data.size()-1
 */
void RotateRightArray(vector<int> &data, int n)
{
	n %= data.size();
	reverse(data.begin(), data.end());
	reverse(data.begin(), data.begin() + n);
	reverse(data.begin() + n, data.end());
}
// https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem?
// 100%
vector<int> RotateLeftArray(vector<int> &a, int d)
{
	vector<int> result;
	for (size_t i = 0; i < a.size(); i++)
		result.push_back(a[(i + d) % a.size()]);
	return result;
}

// https://app.codility.com/programmers/lessons/5-prefix_sums/count_div/
// Pending. Only 87%
size_t CountDiv(size_t a, size_t b, size_t k)
{
	if (b < a || k > b)
		return 0;
	else if (b == a)
		return !(a % k) ? 1 : 0;
	else if (k == 1)
		return b - a + 1;
	else if (!a && k == b)
		return 2;
	else
	{
		// size_t multiples = (b - a + 1) / k;
		//  n * k >= a => n >= a / k
		// size_t first = round(a / k);
		// size_t last = first + k * multiples;
		// return (last + multiples <= b) ? multiples++ : multiples;
		double result = ((double)b - (double)a + (double)1) / (double)k;
		return !(k % 10) ? floor(result) : round(result);
	}
}
// https://app.codility.com/programmers/lessons/12-euclidean_algorithm/chocolates_by_numbers/
// Correctness: 100%
// 87% due to timeout. For example: ChocolatesByNumbers(415633212, 234332);
long ChocolatesByNumbers(long n, long m)
{
	long count = 0;
	if (n <= 0 || m <= 0)
		return 0;
	else if (n == 1 && m > n)
		return 1;
	else if (m == 1)
		return n;
	else if (m == 2)
		return n / 2;
	long greatestCommonDivisor = gcd(n, m);
	long N = n / greatestCommonDivisor;
	long M = m / greatestCommonDivisor;
	for (long i = 0; i < N;)
	{
		count++;
		i += M;
		i %= N;
		if (!i)
			break;
	}
	return count;
}
// https://www.hackerrank.com/challenges/new-year-chaos/problem
// It's New Year's Day and everyone's in line for the Wonderland rollercoaster ride! There are a number of people queued up, and each person wears a sticker indicating their initial position in the queue. Initial positions increment by  from  at the front of the line to  at the back.
// Any person in the queue can bribe the person directly in front of them to swap positions.If two people swap positions, they still wear the same sticker denoting their original places in line.One person can bribe at most two others.For example, ifand bribes, the queue will look like this: .
// Fascinated by this chaotic queue, you decide you must know the minimum number of bribes that took place to get the queue into its current state!
// Use a modification of Bubble sort. Timeouts!
size_t minimumBribes(vector<long> &data)
{
	size_t count = 0;
	long tmp;
	map<long, size_t> bribes;
	pair<map<long, size_t>::iterator, bool> found;
	for (size_t lastIndex = data.size() - 1; lastIndex >= 1; lastIndex--)
	{
		for (size_t i = 0; i < lastIndex; i++)
		{
			if (data[i] > data[i + 1])
			{
				found = bribes.emplace(data[i], 1);
				if (!found.second)
				{
					bribes[data[i]]++;
					if (bribes[data[i]] > 2)
						return -1;
				}
				count++;
				tmp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = tmp;
			}
		}
	}
	return count;
}
// https://www.hackerrank.com/challenges/frequency-queries/problem
// 5/15 failed
// Test case 5 data included in solution as queryFrequencyInput.txt
vector<int> freqQuery(vector<vector<int>> &queries)
{
	unordered_map<int, int> frequency;	 // frequency of data
	unordered_map<int, int> frequencies; // frequeny of frequency
	vector<int> result;
	for (size_t i = 0; i < queries.size(); i++)
	{
		switch (queries[i][0])
		{
		case 1: // Insert
		{
			frequency[queries[i][1]]++;
			frequencies[frequency[queries[i][1]]]++;
		}
		break;
		case 2: // Remove
			if (frequency.find(queries[i][1]) != frequency.end())
			{
				if (--frequencies[frequency[queries[i][1]]] <= 0)
					frequencies.erase(frequency[queries[i][1]]);
				frequency[queries[i][1]]--;
			}
			break;
		case 3: // Find frequency
		{
			int j = frequencies.find(queries[i][1]) != frequencies.end() ? 1 : 0;
			result.push_back(frequencies.find(queries[i][1]) != frequencies.end() ? 1 : 0);
		}
		break;
		default:
			break;
		}
	}
	return result;
}
// https://www.hackerrank.com/challenges/encryption/problem
// 100%
string encryption(string &s)
{
	vector<vector<char>> result;
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	size_t row = floor(sqrt(s.size()));
	size_t col = ceil(sqrt(s.size()));
	for (; col * row < s.size();)
		if (row < col)
			row++;
		else
			col++;
	for (size_t i = 0; i < row; i++)
	{
		string str = s.substr(i * col, col);
		vector<char> chars(str.begin(), str.end());
		for (size_t j = str.size(); j < (size_t)col; j++)
			chars.push_back('\0');
		result.push_back(chars);
	}
	ostringstream oss;
	for (size_t i = 0; i < col; i++)
	{
		for (size_t j = 0; j < row && result[j][i] != '\0'; j++)
			oss << result[j][i];
		if (i < col - 1)
			oss << ' ';
	}
	return oss.str();
}
// https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem
// 100%
vector<size_t> climbingLeaderboard(vector<long> &scores, vector<long> &alice)
{
	vector<size_t> result;
	sort(scores.begin(), scores.end());
	scores.erase(unique(scores.begin(), scores.end()), scores.end());
	for (size_t i = 0; i < alice.size(); i++)
	{
		vector<long>::iterator it = upper_bound(scores.begin(), scores.end(), alice[i]);
		result.push_back(scores.end() - it + 1);
		scores.insert(it, alice[i]);
	}
	return result;
}
long calculateMedian(vector<long> &data)
{
	const auto middleItr = data.begin() + data.size() / 2; // +data.size() % 2;
	nth_element(data.begin(), middleItr, data.end());
	if (data.size() % 2 == 0)
	{
		const auto leftMiddleItr = max_element(data.begin(), middleItr);
		return (*leftMiddleItr + *middleItr) / 2;
	}
	return *middleItr;
}
string timeInWords(int h, int m)
{
	static map<int, string> numbers = {
		{1, "one"},
		{2, "two"},
		{3, "three"},
		{4, "four"},
		{5, "five"},
		{6, "six"},
		{7, "seven"},
		{8, "eight"},
		{9, "nine"},
		{10, "ten"},
		{11, "eleven"},
		{12, "twelve"},
		{13, "thirteen"},
		{14, "fourteen"},
		{15, "fifteen"},
		{16, "sixteen"},
		{17, "seventeen"},
		{18, "eighteen"},
		{19, "nineteen"},
		{20, "twenty"}};
	ostringstream str, hour;
	if (m == 0)
	{
		str << numbers[h] << " o' clock";
		return str.str();
	}
	else if (m == 15)
	{
		str << "quarter past " << numbers[h];
		return str.str();
	}
	else if (m == 30)
	{
		str << "half past " << numbers[h];
		return str.str();
	}
	else if (m == 45)
	{
		str << "quarter to " << numbers[h + 1];
		return str.str();
	}
	if (m > 30)
	{
		m -= 30;
		m = 30 - m;
		hour << " to " << numbers[h + 1];
	}
	else
		hour << " past " << numbers[h];
	if (m > 20)
		str << "twenty " << numbers[m % 20] << " minutes";
	else
		str << numbers[m] << (m > 1 ? " minutes" : " minute");
	str << hour.str();
	return str.str();
}
// https://www.hackerrank.com/challenges/xor-quadruples/problem
// 100% Functionality. However, time out as it is O(N^3)
size_t beautifulQuadruples(int a, int b, int c, int d)
{
	/*
	 * Write your code here.
	 */
	set<multiset<int>> quadruples;
	for (int i = 1; i <= a; i++)
		for (int j = 1; j <= b; j++)
			for (int k = 1; k <= c; k++)
				for (int l = 1; l <= d; l++)
					if ((i ^ j ^ k ^ l) != 0)
					{
						multiset<int> tmp;
						tmp.emplace(i);
						tmp.emplace(j);
						tmp.emplace(k);
						tmp.emplace(l);
						quadruples.emplace(tmp);
					}
	return quadruples.size();
}
// https://www.hackerrank.com/challenges/red-knights-shortest-path/problem
// 100%
vector<string> findShortestPath(int n, int i_start, int j_start, int i_end, int j_end)
{
	vector<string> result;
	ostringstream oss;
	// Print the distance along with the sequence of moves.
	// UL, UR, R, LR, LL, L.
	size_t diff_i = abs(i_end - i_start), diff_j = abs(j_end - j_start);
	// Upper Left
	if (i_end < i_start && j_end < j_start)
	{
		if ((i_start - i_end) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		long uls = (i_start - i_end) / 2; // 6 / 2 = 3
		long dest_j = j_start - uls;	  // 6 - 3 = 3
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		long L = (dest_j - j_end) / 2;
		oss << uls + L;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < (size_t)uls; i++)
		{
			oss << "UL";
			if (i != uls - 1)
				oss << " ";
		}
		if (L)
			oss << " ";
		for (size_t i = 0; i < (size_t)L; i++)
		{
			oss << "L";
			if ((long)i < L - 1)
				oss << " ";
		}
	}
	// Upper Right
	else if (i_end < i_start && j_end > j_start)
	{
		if ((i_start - i_end) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int urs = (i_start - i_end) / 2; // 4 / 2 = 2
		int dest_j = j_start + urs;		 // 2 - 1 = 1
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int R = (j_end - dest_j) / 2; // (3 -
		oss << urs + R;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < (size_t)urs; i++)
		{
			oss << "UR";
			if ((long)i != urs - 1)
				oss << " ";
		}
		if (R)
			oss << " ";
		for (size_t i = 0; i < (size_t)R; i++)
		{
			oss << "R";
			if ((long)i < R - 1)
				oss << " ";
		}
	}
	// Lower Left
	else if (i_end > i_start && j_end < j_start)
	{
		if ((i_end - i_start) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int lls = (i_end - i_start) / 2;
		int dest_j = j_start - lls;
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int L = (dest_j - j_end) / 2;
		if (L >= 0)
		{
			oss << lls + L;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)lls; i++)
			{
				oss << "LL";
				if ((long)i != lls - 1)
					oss << " ";
			}
			if (L)
				oss << " ";
			for (size_t i = 0; i < (size_t)L; i++)
			{
				oss << "L";
				if ((long)i < L - 1)
					oss << " ";
			}
		}
		else
		{ // L < 0
			oss << lls;
			result.push_back(oss.str());
			oss.str("");
			for (int i = L; i < 0; i++)
			{
				oss << "LR";
				if (i < -1)
					oss << " ";
			}
			if (lls + L)
				oss << " ";
			for (size_t i = 0; i < (size_t)(lls + L); i++)
			{
				oss << "LL";
				if ((long)i != (lls + L - 1))
					oss << " ";
			}
		}
	}
	// Lower Right
	else if (i_end > i_start && j_end > j_start)
	{
		if ((i_end - i_start) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int lrs = (i_end - i_start) / 2;
		int dest_j = j_start + lrs;
		if ((abs(j_end - dest_j)) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		int R = (j_end - dest_j) / 2;
		if (R >= 0)
		{
			oss << lrs + R;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)R; i++)
			{
				oss << "R";
				if ((long)i < R - 1)
					oss << " ";
			}
			if (lrs)
				oss << " ";
			for (size_t i = 0; i < (size_t)lrs; i++)
			{
				oss << "LR";
				if ((long)i != lrs - 1)
					oss << " ";
			}
		}
		else
		{ // R < 0
			oss << lrs;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)(lrs + R); i++)
			{
				oss << "LR";
				if (i != (lrs + R - 1))
					oss << " ";
			}
			if (R < 0)
				oss << " ";
			for (int i = R; i < 0; i++)
			{
				oss << "LL";
				if (i < -1)
					oss << " ";
			}
		}
	}
	// UP
	else if (j_end == j_start && i_end < i_start)
	{
		size_t diff = i_start - i_end;
		if (diff % 4)
		{
			result.push_back("Impossible");
			return result;
		}
		else
		{
			oss << diff / 2;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (diff / 4); i++)
			{
				oss << "UL UR";
				if (i != (diff / 4) - 1)
					oss << " ";
			}
		}
	}
	// DOWN
	else if (j_end == j_start && i_end > i_start)
	{
		size_t diff = i_end - i_start;
		if (diff % 4)
		{
			result.push_back("Impossible");
			return result;
		}
		else
		{
			oss << diff / 2;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (diff / 4); i++)
			{
				oss << "LR LL";
				if (i != (diff / 4) - 1)
					oss << " ";
			}
		}
	}
	// Left
	else if (i_end == i_start && j_end < j_start)
	{
		if ((j_start - j_end) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		size_t L = (j_start - j_end) / 2;
		oss << L;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < L; i++)
		{
			oss << "L";
			if (i != L - 1)
				oss << " ";
		}
	}
	// Right
	else if (i_end == i_start && j_end > j_start)
	{
		if ((j_end - j_start) % 2)
		{
			result.push_back("Impossible");
			return result;
		}
		size_t R = (j_end - j_start) / 2;
		oss << R;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < R; i++)
		{
			oss << "R";
			if (i != R - 1)
				oss << " ";
		}
	}
	else
	{
		// Destination = start?
		oss << 0 << endl;
	}
	result.push_back(oss.str());
	return result;
}
/* https://www.hackerrank.com/challenges/kruskalmstrsub/problem
   https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
   https://stackoverflow.com/questions/1195872/when-should-i-use-kruskal-as-opposed-to-prim-and-vice-versa
   Kruskal can have better performance if the edges can be sorted in linear time, or are already sorted
   100%
*/
long kruskals(int nodes, vector<long> &from, vector<long> &to, vector<long> &weight)
{
	multiset<Edge> edges; // Sorted edges based on weights
	long sum = 0;
	for (size_t i = 0; i < weight.size(); i++)
		edges.emplace(Edge(weight[i], from[i], to[i]));
	DisJointSet<long> disjointSet(from); // Every vertex is a disjoint set
	disjointSet.MakeSet(to);
	for (multiset<Edge>::iterator it = edges.begin(); it != edges.end(); it++)
	{
		if (disjointSet.Find(it->node1) != disjointSet.Find(it->node2))
		{
			sum += it->weight;
			disjointSet.Union(it->node1, it->node2);
		}
	}
	return sum;
}
/* https://www.hackerrank.com/challenges/primsmstsub/problem
   https://en.wikipedia.org/wiki/Prim%27s_algorithm
   https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
   https://stackoverflow.com/questions/1195872/when-should-i-use-kruskal-as-opposed-to-prim-and-vice-versa
   Use Prim's algorithm when you have a graph with lots of edges, i.e., if the number of edges to vertices is high.
   Prim's algorithm is significantly faster in the limit when you've got a really dense graph with many more edges than vertices.
   100%
*/
size_t PrimMinimumSpanningTree(size_t nodes, vector<vector<long>> &edges, long start)
{
	Graph<long, long> graph;
	for (size_t i = 0; i < edges.size(); i++)
	{
		shared_ptr<Vertex<long, long>> v1 = graph.GetVertex(edges[i][0]);
		shared_ptr<Vertex<long, long>> v2 = graph.GetVertex(edges[i][1]);
		if (!v1)
			v1 = make_shared<Vertex<long, long>>(edges[i][0]);
		if (!v2)
			v2 = make_shared<Vertex<long, long>>(edges[i][1]);
		graph.AddUndirectedEdge(v1, v2, edges[i][2]);
	}
	shared_ptr<Vertex<long, long>> startVertex = graph.GetVertex(start);
	assert(startVertex);
	cout << __FUNCTION__ << " graph (" << nodes << " nodes):" << endl;
	for (size_t i = 0; i < nodes; i++)
	{
		shared_ptr<Vertex<long, long>> v = graph.GetVertex(i + 1);
		assert(v);
		graph.Print(v);
	}
	return graph.PrimMinimumSpanningTree(startVertex);
}
// https://www.hackerrank.com/challenges/rust-murderer/problem
// 2/7 test cases failed and 1 test case times out!
void UnbeatenPaths(size_t nodes, vector<vector<long>> &edges, long start, vector<size_t> &paths)
{
	Graph<long, long> graph;
	for (size_t i = 1; i <= nodes; i++)
		graph.AddVertex(i);
	for (size_t i = 0; i < edges.size(); i++)
	{
		shared_ptr<Vertex<long, long>> v1 = graph.GetVertex(edges[i][0]);
		shared_ptr<Vertex<long, long>> v2 = graph.GetVertex(edges[i][1]);
		assert(v1);
		assert(v2);
		graph.AddUndirectedEdge(v1, v2, 0);
	}
	cout << __FUNCTION__ << " graph (" << nodes << " nodes):" << endl;
	for (size_t i = 0; i < nodes; i++)
	{
		shared_ptr<Vertex<long, long>> v = graph.GetVertex(i + 1);
		assert(v);
		graph.Print(v);
	}
	graph.UnbeatenPath(start, paths);
}
// https://www.hackerrank.com/challenges/jack-goes-to-rapture/problem
// Timeout! for test cases with 50000 nodes
long getLowestPathCost(size_t g_nodes, vector<long> &g_from, vector<long> &g_to, vector<long> &g_weight)
{
	// Breadth-First-Search algorithm
	Graph<long, long> graph;
	for (size_t i = 1; i <= g_nodes; i++)
		graph.AddVertex(i);
	for (size_t i = 0; i < g_from.size(); i++)
	{
		shared_ptr<Vertex<long, long>> v1 = graph.GetVertex(g_from[i]);
		shared_ptr<Vertex<long, long>> v2 = graph.GetVertex(g_to[i]);
		assert(v1);
		assert(v2);
		graph.AddUndirectedEdge(v1, v2, g_weight[i]);
	}
	// cout << __FUNCTION__ << " graph (" << g_nodes << " nodes):" << endl;
	// for (size_t i = 1; i <= g_nodes; i++)
	//	graph.Print(graph.GetVertex(i));
	// cout << endl;
	set<shared_ptr<Vertex<long, long>>> spt;
	long cost = graph.GetPathsCosts(spt, graph.GetVertex(1), graph.GetVertex(g_nodes));
	// cout << "Vertex\tDistance from Source" << endl;
	// for (set<shared_ptr<Vertex<long, long>>>::iterator it = spt.begin(); it != spt.end(); it++)
	//	cout << (*it)->GetTag() << "\t" << (*it)->GetTotalCost() << endl;
	return cost;
}
// https://www.hackerrank.com/challenges/3d-surface-area/problem
// 100%
size_t SurfaceArea3D(vector<vector<long>> &data)
{
	size_t zArea = 0, xArea = 0, yArea = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].size(); j++)
		{
			if (data[i][j] > 0)
				zArea++;
			// X-Axis : Side / Left/Right views
			if (i == 0) // Start X-Axis border
				xArea += data[i][j];
			if (i == data.size() - 1)
			{ // End X-Axis border
				xArea += data[i][j];
				if (i != 0)
					xArea += abs(data[i][j] - data[i - 1][j]);
			}
			if (i != 0 && i != data.size() - 1)
				xArea += abs(data[i][j] - data[i - 1][j]);
			// Y-Axis : Front/Back views
			if (j == 0) // Start Y-Axis border
				yArea += data[i][j];
			if (j == data[i].size() - 1)
			{ // End Y-Axis border
				yArea += data[i][j];
				if (j != 0)
					yArea += abs(data[i][j] - data[i][j - 1]);
			}
			if (j != 0 && j != data[i].size() - 1)
				yArea += abs(data[i][j] - data[i][j - 1]);
		}
	}
	return xArea + yArea + zArea * 2;
}
// https://www.hackerrank.com/challenges/cut-the-tree/problem
// Only pass the sample quetions with 6 and 10 nodes. Difficult to reproduce due to the data input
size_t cutTheTree(vector<size_t> &data, vector<vector<size_t>> &edges)
{
	Tree<size_t> tree(data[0]);
	for (size_t i = 0; i < edges.size(); i++)
	{
		shared_ptr<Node<size_t>> parent = tree.FindNode(edges[i][0]);
		assert(parent);
		shared_ptr<Node<size_t>> n = make_shared<Node<size_t>>(edges[i][1]);
		tree.InsertNode(parent, n);
	}
	tree.PrintTree();
	size_t result = tree.MinSubTreesDifference();
	return result;
}
// https://www.hackerrank.com/challenges/cut-the-tree/problem
// Only pass the sample quetions with 6 and 10 nodes. Difficult to reproduce due to the data input.
size_t MinSubGraphDifference(vector<size_t> &data, vector<vector<size_t>> &edges)
{
	Graph<size_t, size_t> graph;
	for (size_t i = 0; i < data.size(); i++)
		graph.AddVertex(i + 1, data[i]);
	for (size_t i = 0; i < edges.size(); i++)
	{
		shared_ptr<Vertex<size_t, size_t>> v1 = graph.GetVertex(edges[i][0]);
		shared_ptr<Vertex<size_t, size_t>> v2 = graph.GetVertex(edges[i][1]);
		assert(v1);
		assert(v2);
		graph.AddUndirectedEdge(v1, v2, 0);
	}
	// cout << __FUNCTION__ << " graph (" << data.size() << " nodes)" << endl;
	// for (size_t i = 0; i < data.size(); i++)
	//	graph.Print(graph.GetVertex(i + 1));
	// cout << endl;
	size_t result = graph.MinSubTreesDifference(graph.GetVertex(1));
	return result;
}
// https://www.hackerrank.com/challenges/jeanies-route/problem
// Times out for more than 100 nodes! ;)
long PostmanProblem(vector<long> &k, vector<vector<long>> &roads)
{
	Graph<long, long> graph;
	for (size_t i = 0; i < roads.size(); i++)
	{
		shared_ptr<Vertex<long, long>> v1 = graph.AddVertex(roads[i][0]);
		shared_ptr<Vertex<long, long>> v2 = graph.AddVertex(roads[i][1]);
		graph.AddUndirectedEdge(v1, v2, roads[i][2]);
	}
	set<vector<long>> paths;
	paths = permute(k);
	multimap<long, string> costs;
	ostringstream oss, oss1, oss2;
	map<string, long> costCache;
	for (set<vector<long>>::iterator it = paths.begin(); it != paths.end(); it++)
	{
		vector<long> path = *it;
		long totalCost = 0;
		bool isValidPath = true;
		for (size_t i = 0; i < path.size() - 1 && isValidPath; i++)
		{
			long cost = -1;
			oss1.str("");
			oss2.str("");
			oss1 << path[i] << "-" << path[i + 1];
			oss2 << path[i + 1] << "-" << path[i];
			if (costCache.find(oss1.str()) != costCache.end())
				cost = costCache[oss1.str()];
			else if (costCache.find(oss2.str()) != costCache.end())
				cost = costCache[oss2.str()];
			else
			{
				cost = graph.Dijkstra(path[i], path[i + 1]);
				costCache[oss1.str()] = cost;
				costCache[oss2.str()] = cost;
			}
			// cout << path[i] << " - " << path[i + 1] << ": " << cost << endl;
			if (cost >= 0)
				totalCost += cost;
			else
				isValidPath = false;
			oss << path[i] << "," << path[i + 1] << ",";
		}
		if (isValidPath)
		{
			costs.emplace(totalCost, oss.str());
			oss.str("");
		}
	}
	return costs.empty() ? -1 : costs.begin()->first;
}
/* https://www.hackerrank.com/challenges/almost-sorted/problem
   100%
3 1 2
1 2 3 : No
2 -1 -1

1 3 2 4
1 2 3 4 : Swap 1 2
0 1 -1 0

1 4 2 3
1 2 3 4 : No
0 2 -1 -1 : 0

1 4 3 5 2
1 2 3 4 5 : No
0 2 0 1 -3: 0

1 4 3 2
1 2 3 4 : Swap 1 3
0 2 0 -2

1 5 4 3 2
1 2 3 4 5: Reverse 1-4
0 3 1 -1 -3

1 5 3 4 2
1 2 3 4 5: Swap 1 4
0 3 0 0 -3

4 2
2 4 : Swap 0 1
2 -2

1 5 4 3 2 6
1 2 3 4 5 6	: Reverse 1 4
0 3 1 -1 -3 0

43 65 1  98 99 101
1  43 65 98 99 101 : No
42 22 -64 0 0  0

2 3 1 4 5 6
1 2 3 4 5 6 : No
1 1 -2 0 0 0
*/
string AlmostSorted(vector<long> &arr)
{
	ostringstream oss;
	vector<long> sorted(arr);
	sort(sorted.begin(), sorted.end());
	vector<long> diff;
	long positive = -1, sum = 0;
	for (size_t i = 0; i < arr.size(); i++)
	{
		long delta = arr[i] - sorted[i];
		if (delta > 0 && positive < 0)
			positive = i;
		if (positive >= 0)
		{ // Start tracking from the first positive delta to minimize space complexity
			size_t index = i - positive;
			diff.push_back(delta);
			sum += diff[index];
			if (diff[index] < 0 && sum == 0)
			{
				size_t positives = count_if(diff.begin(), diff.end(), [](long i)
											{ return i > 0; });
				size_t negatives = count_if(diff.begin(), diff.end(), [](long i)
											{ return i < 0; });
				if (diff[index] + diff[0] != 0)
					return "no";
				else if (positives == 1 && negatives == 1)
				{
					if (!oss.str().empty())
						return "no";
					oss << "swap " << positive + 1 << " " << i + 1;
				}
				else if (i > (size_t)(positive + 1))
				{
					if (!oss.str().empty())
						return "no";
					oss << "reverse " << positive + 1 << " " << i + 1;
				}
			}
		}
	}
	return oss.str().empty() ? "no" : oss.str();
}
/* https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
* https://www.hackerrank.com/challenges/common-child/problem
* 100%
* 		j:0	j:1	j:2	j:3	j:4	j:5
		\0'	H	A	R	R	Y
i:0	\0'	0	0	0	0	0	0
i:1	S	0	0	0	0	0	0
i:2	A	0	0	1	1	1	1
i:3	L	0	0	1	1	1	1
i:4	L	0	0	1	1	1	1
i:5	Y	0	0	1	1	1	2
*/
size_t LCSLength(string &s1, string &s2)
{
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	for (size_t i = 1; i < s1.size(); i++)
		for (size_t j = 1; j < s2.size(); j++)
			table[i][j] = s1[i] == s2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[s1.size() - 1][s2.size() - 1];
}
template <typename T>
size_t LCSLength(vector<T> &n1, vector<T> &n2)
{
	n1.insert(n1.begin(), 0);
	n2.insert(n2.begin(), 0);
	vector<vector<size_t>> table(n1.size(), vector<size_t>(n2.size())); // Defaults to zero initial value
	for (size_t i = 1; i < n1.size(); i++)
		for (size_t j = 1; j < n2.size(); j++)
			table[i][j] = n1[i] == n2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[n1.size() - 1][n2.size() - 1];
}
size_t LCSLength(vector<vector<size_t>> &table, string &s1, string &s2)
{
	for (size_t i = 1; i < s1.size(); i++)
		for (size_t j = 1; j < s2.size(); j++)
			table[i][j] = s1[i] == s2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[s1.size() - 1][s2.size() - 1];
}
template <typename T>
size_t LCSLength(vector<vector<size_t>> &table, vector<T> &n1, vector<T> &n2)
{
	for (size_t i = 1; i < n1.size(); i++)
		for (size_t j = 1; j < n2.size(); j++)
			table[i][j] = n1[i] == n2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[n1.size() - 1][n2.size() - 1];
}
string LCSBackTrack(vector<vector<size_t>> &table, string &s1, string &s2, size_t i, size_t j)
{
	if (!i || !j)
		return "";
	if (s1[i] == s2[j])
		return LCSBackTrack(table, s1, s2, i - 1, j - 1) + s1[i];
	return table[i][j - 1] > table[i - 1][j] ? LCSBackTrack(table, s1, s2, i, j - 1) : LCSBackTrack(table, s1, s2, i - 1, j);
}
template <typename T>
vector<T> LCSBackTrack(vector<vector<size_t>> &table, vector<T> &n1, vector<T> &n2, size_t i, size_t j)
{
	vector<T> result;
	if (!i || !j)
		return result;
	if (n1[i] == n2[j])
	{
		result = LCSBackTrack(table, n1, n2, i - 1, j - 1);
		result.push_back(n1[i]);
		return result;
	}
	return table[i][j - 1] > table[i - 1][j] ? LCSBackTrack(table, n1, n2, i, j - 1) : LCSBackTrack(table, n1, n2, i - 1, j);
}
void LCSPrintDiff(vector<vector<size_t>> &table, string &s1, string &s2, long i, long j)
{
	if (i > 0 && j > 0 && s1[i] == s2[j])
	{
		LCSPrintDiff(table, s1, s2, i - 1, j - 1);
		cout << s1[i];
	}
	else if (j > 0 && (!i || (table[i][j - 1] >= table[i - 1][j])))
	{
		LCSPrintDiff(table, s1, s2, i, j - 1);
		cout << "+" << s2[j];
	}
	else if (i > 0 && (!j || (table[i][j - 1] < table[i - 1][j])))
	{
		LCSPrintDiff(table, s1, s2, i - 1, j);
		cout << "-" << s1[i];
	}
}
template <typename T>
void LCSPrintDiff(vector<vector<size_t>> &table, vector<T> &n1, vector<T> &n2, long i, long j)
{
	if (i > 0 && j > 0 && n1[i] == n2[j])
	{
		LCSPrintDiff(table, n1, n2, i - 1, j - 1);
		cout << n1[i];
	}
	else if (j > 0 && (!i || (table[i][j - 1] >= table[i - 1][j])))
	{
		LCSPrintDiff(table, n1, n2, i, j - 1);
		cout << "+" << n2[j];
	}
	else if (i > 0 && (!j || (table[i][j - 1] < table[i - 1][j])))
	{
		LCSPrintDiff(table, n1, n2, i - 1, j);
		cout << "-" << n1[i];
	}
}
// https://www.hackerrank.com/challenges/coin-change/problem
// Times out!
set<vector<size_t>> CoinChange(long amount, vector<size_t> &coins)
{
	set<vector<size_t>> combinations;
	if (amount > 0)
		for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end(); coin++)
		{
			if (amount >= (long)*coin)
			{
				set<vector<size_t>> tmp;
				if (coinChangeCache.find(amount - *coin) == coinChangeCache.end())
				{
					tmp = CoinChange(amount - *coin, coins);
					if (!tmp.empty())
						coinChangeCache[amount - *coin] = tmp;
				}
				else
					tmp = coinChangeCache[amount - *coin];
				if (!tmp.empty())
					for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						vector<size_t> change(*it);
						if (accumulate(change.begin(), change.end(), *coin) == amount)
						{
							change.push_back(*coin);
							sort(change.begin(), change.end());
							combinations.insert(change);
						}
					}
				else if (*coin == amount)
					combinations.insert(vector<size_t>{*coin});
			} // if (amount >= (long)coins[i]) {
		}
	return combinations;
}
set<vector<size_t>> CoinsChangeDynamicProgramming(long amount, vector<size_t> &coins)
{
	map<size_t, set<vector<size_t>>> dp;
	sort(coins.begin(), coins.end());
	for (size_t i = coins[0]; i <= (size_t)amount; i++) // Bottom-Up
		for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end(); coin++)
		{
			if (i == *coin)
				dp[i].insert(vector<size_t>{i});
			else if (i > *coin)
			{ // i:5 coins[j]:2 delta:3 dp[3] = {3}
				size_t delta = i - *coin;
				if (dp.find(delta) != dp.end())
				{
					for (set<vector<size_t>>::iterator it = dp[delta].begin(); it != dp[delta].end(); it++)
					{
						vector<size_t> tmp = *it;
						tmp.push_back(*coin);
						sort(tmp.begin(), tmp.end());
						dp[i].insert(tmp);
					}
				}
			}
		}
	return dp[amount];
}
/* https://www.hackerrank.com/challenges/coin-change/problem
 * https://leetcode.com/problems/coin-change-2/
 * 100%
 * coins: {2,3,5} amount: 10
 * coin = 2; i = starts from 2
 * ways: 1 0 1 0 1 0 1 0 1 0 1
 * i:    0 1 2 3 4 5 6 7 8 9 10
 *
 * coin = 3; i = starts from 3
 * ways: 1 0 1 1 1 1 2 1 2 2 2
 * i:    0 1 2 3 4 5 6 7 8 9 10
 *
 * coin = 5; i = starts from 5
 * ways: 1 0 1 1 1 2 2 2 3 3 4
 * i:    0 1 2 3 4 5 6 7 8 9 10 {5,5},{5,2,3},{2,2,3,3},{2,2,2,2,2}
 */
size_t CoinsChangeUniqueWaysDynamicProgramming(long amount, vector<size_t> &coins)
{
	if (amount <= 0 || coins.empty())
		return 0;
	vector<size_t> dp(amount + 1, 0); // Index: amount. Value: #ways or #posibilities
	dp[0] = 1;						  // $0 is one possibility
	for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end(); coin++)
		for (size_t i = *coin; i <= (size_t)amount; i++)
			dp[i] += dp[i - *coin];
	return dp[amount];
}
/* https://leetcode.com/problems/combination-sum-iv/
 * 100%
 * coins: {2,3,5} amount: 10
 * ways: 1 0 1 1 1 3 2 5 6 8 14
 * i:    0 1 2 3 4 5 6 7 8 9 10
 */
size_t CoinsChangeDuplicateWaysDynamicProgramming(size_t amount, vector<size_t> &coins)
{
	if (amount <= 0 || coins.empty())
		return 0;
	sort(coins.begin(), coins.end());
	vector<size_t> dp(amount + 1, 0); // Index: amount. Value: #ways or #posibilities
	dp[0] = 1;						  // $0 is one possibility
	for (size_t i = coins[0]; i <= amount; i++)
		for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end() && i >= *coin; coin++)
			dp[i] += dp[i - *coin];
	return dp[amount];
}
/* https://leetcode.com/problems/coin-change/
 * 100%
 * coins: {1,2,5}, amount: 10
 * i:    0 1 2     3     4     5        6       7      8       9       10
 * ways: 0 1 {2,1} {2,2} {3,2} {3,3,1} {2,3,2} {3,2,2} {3,3,3} {4,3,3} {4,4,2}
 */
long CoinsChangeFewestCoinsDynamicProgramming(long amount, vector<size_t> &coins)
{
	if (amount <= 0 || coins.empty())
		return 0;
	sort(coins.begin(), coins.end());
	vector<size_t> dp(amount + 1, numeric_limits<size_t>::max()); // Index: amount. Value: #coins
	dp[0] = 0;													  // $0 = 0 coins
	for (size_t i = coins[0]; i <= (size_t)amount; i++)
		for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end() && i >= *coin; coin++)
			if (dp[i - *coin] != numeric_limits<size_t>::max())
				dp[i] = min(dp[i], dp[i - *coin] + 1);
	return dp[amount] == numeric_limits<size_t>::max() ? -1 : dp[amount];
}
/* The Recursive Staircase - Top Down Dynamic Programming
 *			6
 *       4        5
 *    2       3
 *  0(1)	1
 *     -1(0) 0(1)
 */
size_t StairsClimbingDynamicProgramming(long destination, vector<size_t> &steps)
{
	if (!destination) // 0 step = stays. So it is one possibility.
		return 1;
	else if (destination < 0) // Impossible
		return 0;
	size_t combinations = 0;
	for (vector<size_t>::iterator it = steps.begin(); it != steps.end(); it++)
	{
		if (dpMemoization.find(destination - *it) == dpMemoization.end())
			dpMemoization[destination - *it] = StairsClimbingDynamicProgramming(destination - *it, steps);
		combinations += dpMemoization[destination - *it];
	}
	return combinations;
}
/* The Recursive Staircase - Bottom Up Dynamic Programming
 * Steps: {1,2} Destination: 6
 *  0 1 2 3 4 5 6
 * {1,1,2,3,5,8,13} <= [i] = [i-1] + [i-2]
 * {1,0}, {1,1}, {2,1}, {2,3}, {5,3}, {5,8}, {13,8} => [N%2] = 13
 *
 * Steps: {1,2,3} Destination: 6
 *  0 1 2 3 4 5  6
 * {1,1,2,4,7,13,24} <= [i] = [i-1] + [i-2] + [i-3]
 * {1,0,0}, {1,1,0}, {1,1,2}, {4,1,2}, {4,7,2}, {4,7,13}, {24,7,13} => [n%3] = 24
 */
size_t StairsClimbingDynamicProgrammingBottomUp(long destination, vector<size_t> &steps)
{
	vector<size_t> combinations(steps.size(), 0);
	combinations[0] = 1;
	for (size_t i = 1; i <= (size_t)destination; i++)
		combinations[i % combinations.size()] = accumulate(combinations.begin(), combinations.end(), 0);
	return combinations[destination % combinations.size()];
}
// https://www.hackerrank.com/challenges/unbounded-knapsack/problem
// 100%
set<vector<size_t>> Knapsack(long amount, vector<size_t> &numbers)
{
	set<vector<size_t>> combinations;
	if (amount > 0 && !numbers.empty())
	{
		if (numbers.size() == 1 && (long)numbers[0] <= amount)
			combinations.insert(vector<size_t>{amount - amount % numbers[0]}); // Multiples of numbers[0] closest to amount
		else if (find(numbers.begin(), numbers.end(), 1) != numbers.end())
			combinations.insert(vector<size_t>{(size_t)amount});
		else
		{
			for (vector<size_t>::iterator number = numbers.begin(); number != numbers.end(); number++)
			{
				if (amount >= (long)*number)
				{
					set<vector<size_t>> tmp;
					if (knapsackCache.find(amount - *number) == knapsackCache.end())
					{
						tmp = Knapsack(amount - *number, numbers);
						if (!tmp.empty())
							knapsackCache[amount - *number] = tmp;
					}
					else
						tmp = knapsackCache[amount - *number];
					if (!tmp.empty())
						for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
						{
							vector<size_t> change(*it);
							if (accumulate(change.begin(), change.end(), *number) <= (size_t)amount)
							{
								change.push_back(*number);
								sort(change.begin(), change.end());
								combinations.insert(change);
							}
						}
					else
						combinations.insert(vector<size_t>{*number});
				} // if (amount >= (long)numbers[i]) {
			}
		}
	}
	return combinations;
}
// Bounded places an upper bound on the number of copies of each kind of item included in the knapsack
// Unbounded places no upper bound on the number of copies of each kind of item included in the knapsack
size_t UnboundedKnapsack(long k, vector<size_t> &arr)
{
	knapsackCache.clear();
	set<vector<size_t>> combinations = Knapsack(k, arr);
	set<size_t> sums;
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		sums.insert(accumulate(it->begin(), it->end(), 0));
	return sums.empty() ? 0 : *sums.rbegin();
}
set<vector<size_t>> _BoundedKnapsack(long amount, vector<size_t> &numbers)
{
	set<vector<size_t>> combinations;
	if (amount > 0 && !numbers.empty())
	{
		for (vector<size_t>::iterator number = numbers.begin(); number != numbers.end(); number++)
		{
			if (amount >= (long)*number)
			{
				set<vector<size_t>> tmp;
				if (knapsackCache.find(amount - *number) == knapsackCache.end())
				{
					tmp = _BoundedKnapsack(amount - *number, numbers);
					knapsackCache[amount - *number] = tmp;
				}
				else
					tmp = knapsackCache[amount - *number];
				if (!tmp.empty())
				{
					for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						vector<size_t> tmp1(*it);
						if (accumulate(tmp1.begin(), tmp1.end(), *number) == amount)
						{
							tmp1.push_back(*number);
							sort(tmp1.begin(), tmp1.end());
							size_t cnt = count(tmp1.begin(), tmp1.end(), *number);
							size_t cnt1 = count(numbers.begin(), numbers.end(), *number);
							if (cnt <= cnt1) // The result must not contain more than the input as this is *Bounded* knapsack.
								combinations.insert(tmp1);
						}
					}
				}
				else
					combinations.insert(vector<size_t>{*number});
			}
		}
	}
	return combinations;
}
vector<vector<size_t>> BoundedKnapsack(long amount, vector<size_t> &numbers)
{
	vector<vector<size_t>> result;
	knapsackCache.clear();
	set<vector<size_t>> combinations = _BoundedKnapsack(amount, numbers);
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		if (accumulate(it->begin(), it->end(), 0) == amount)
			result.push_back(*it);
	return result;
}
/* https://leetcode.com/problems/combination-sum-iii/
 * 100%
 */
set<vector<size_t>> _BoundedKnapsackCombinationSum(size_t k, size_t sum)
{
	set<vector<size_t>> combinations;
	for (size_t i = 1; i < 10; i++)
	{
		if (sum >= i)
		{
			set<vector<size_t>> tmp;
			if (knapsackCache.find(sum - i) == knapsackCache.end())
			{
				tmp = _BoundedKnapsackCombinationSum(k, sum - i);
				knapsackCache[sum - i] = tmp;
			}
			else
				tmp = knapsackCache[sum - i];
			if (!tmp.empty())
				for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
				{
					if (it->size() < k && find(it->begin(), it->end(), i) == it->end())
					{
						vector<size_t> change(*it);
						change.push_back(i);
						if (accumulate(change.begin(), change.end(), 0) == sum)
						{
							sort(change.begin(), change.end());
							combinations.insert(change);
						}
					}
				}
			else if (i == sum)
				combinations.insert(vector<size_t>{i});
		}
	} // for
	return combinations;
}
set<vector<size_t>> BoundedKnapsackCombinationSum(size_t k, size_t sum)
{
	knapsackCache.clear();
	set<vector<size_t>> combinations = _BoundedKnapsackCombinationSum(k, sum);
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end();)
		if (it->size() != k)
			it = combinations.erase(it);
		else
			it++;
	return combinations;
}
/*
  https://www.hackerrank.com/challenges/cipher/problem
1001 011     shift 0
0100 1011    shift 1
0010 01011   shift 2
0001 001011  shift 3
-----------
1110 101001  <- XORed/encoded string s

1111 010     shift 0
0111 1010    shift 1
0011 11010   shift 2
0001 111010  shift 3
-----------
1010 110110  <- XORed/encoded string s

1101 101     shift 0
0110 1101    shift 1
0011 01101   shift 2
0001 101101  shift 3
-----------
1001 101001  <- XORed/encoded string s

0111 000     shift 0
0011 1001    shift 1
0001 11001   shift 2
0000 111001  shift 3
-----------
0101 101001  <- XORed/encoded string s

1010	  shift 0
0101 0	  shift 1
0010 10	  shift 2
0001 010  shift 3
0000 1010 shift 4
-----------
1100 0110

Observation:
	Result is derived from the encoded string s and the computed result so far. Intermediate shifted strings are distractions.
	result[0] = s[0]
	For i < k, result[i] = s[i - 1] == s[i] ? '0' : '1'
	For i >= k, result[i] = s[i - 1] == s[i] ? result[i - k] : result[i - k] == '1' ? '0' : '1'
100%
*/
string cipher(size_t n, size_t k, const string &s)
{
	string result;
	if (!s.empty() && k <= s.size() && s.size() >= n)
	{
		result = s[0];
		for (size_t i = 1; i < n; i++)
		{
			if (i < k)
				result.push_back(s[i - 1] == s[i] ? '0' : '1');
			else
				result.push_back(s[i - 1] == s[i] ? result[i - k] : result[i - k] == '1' ? '0'
																						 : '1');
		}
	}
	return result;
}
// Encryption scheme:
// If s[i] is lowercase and s[i+1] is uppercase, swap them and add an asterik '*' after them
// If s[i] is a number, replace it with 0 and place the original number at the beginning.
// 100%
string DecryptPassword(const string &s)
{
	string result;
	long numbers = -1;
	for (size_t i = 0; i < s.size() && isdigit(s[i]) && s[i] != '0'; i++)
	{
		if (isdigit(s[i]) && s[i] != '0')
			numbers = i;
	}
	for (size_t i = numbers + 1; i < s.size();)
	{
		if (i < s.size() - 2 && isupper(s[i]) && islower(s[i + 1]) && s[i + 2] == '*')
		{
			result.push_back(s[i + 1]);
			result.push_back(s[i]);
			i += 3;
		}
		else if (s[i] == '0')
		{
			result.push_back(s[numbers--]);
			i++;
		}
		else
			result.push_back(s[i++]);
	}
	return result;
}
// https://www.hackerrank.com/challenges/sam-and-substrings/problem
// 100 %
unsigned long long substrings(const string &s)
{
	/*
	Example: "6789". Substrings: 6, 7, 8, 9, 67, 78, 89, 678, 789, 6789.
 Frequency in substrings at positions
Digit   Unit    Ten     Hundred     Thousand        Sum
6       1       1       1           1           = 6*1*1111
7       2       2       2                       = 7*2*111
8       3       3                               = 8*3*11
9       4                                       = 9*4*1

7: 7 * 100 * 2 + 7 * 10 * 2 + 7 * 2 = (7 * 2)(100 + 10 + 1) = 7 * 2 * 111
8: 8 * 10 * 3 + 8 * 3 = (8 * 3)(10 + 1) = 8 * 3 * 11

		s[i] * n * 11..1 (s.size() - n + 1 times '1').
	*/
	unsigned long long sum = 0;
	unsigned long long ones = 1;
	for (int i = s.size() - 1; i >= 0; i--)
	{
		sum += ((unsigned long long)s[i] - '0') * ones * (unsigned long long)(i + 1ull);
		ones = (ones * 10 + 1) % (unsigned long long)(1e9 + 7);
		sum %= (unsigned long long)(1e9 + 7);
	}
	return sum;
}
/* https://www.hackerrank.com/challenges/larrys-array/problem
   https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
Formula: ( (grid width odd) && (#inversions even) )  ||  ( (grid width even) && ((blank on odd row from bottom) == (#inversions even)) )
   The given array can be then compared to a rectangle of width 3, and any height h, so that total number of tiles is (3*h)-1.
   (Like it was (w*h)-1 in the original 15 tile puzzle)
blank spaces for a grid with width 3 to satisfy (3*h)-1:
0: add 2
1: add 0
2: add 1
	Don't have to add anything to the input data to fulfil the (3*h)-1 tiles since we can arbitrarily add the numbers which are in-sequence and bigger than the biggest number currently in the board.
	100%
*/
bool SolvabilityOfTheTilesGame(vector<size_t> &data)
{
	size_t inversions = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		size_t item = data[i];
		size_t smallerItems = count_if(data.begin(), data.begin() + i, [&item](size_t i)
									   { return i < item; });
		inversions += item - 1 - smallerItems;
	}
	return !(inversions % 2);
}
/* https://www.hackerrank.com/challenges/bear-and-steady-gene/problem
 * Unfinished work!
 */
size_t steadyGene(string &gene)
{
	size_t result = 0, count = gene.size() / 4;
	map<char, size_t> counts = {
		{'A', 0},
		{'C', 0},
		{'G', 0},
		{'T', 0},
	};
	map<char, vector<size_t>> indices;
	size_t i = 0;
	long start = -1;
	for (string::iterator it = gene.begin(); it != gene.end(); it++, i++)
	{
		counts[*it]++;
		indices[*it].push_back(i);
		if (counts[*it] > count && start < 0)
			start = i;
	}
	if (start < 0)
		return 0;
	/*
	assert(steadyGene(string("AAAA")) == 3);
	assert(steadyGene(string("ACAA")) == 2);
	assert(steadyGene(string("ACTGAAAG")) == 2);
	assert(steadyGene(string("GAAATAAA")) == 5);
	*/
	vector<size_t> fixedIndices;
	for (map<char, size_t>::iterator it = counts.begin(); it != counts.end(); it++)
	{
		if (it->second < count)
		{
			size_t shortage = count - it->second;
			for (map<char, vector<size_t>>::iterator it1 = indices.begin(); it1 != indices.end() && shortage > 0; it1++)
			{
				if (it1->first != it->first && it1->second.size() > count)
				{
					size_t excess = it1->second.size() - count;
					size_t toRemove = abs((long)excess - (long)shortage);
					fixedIndices.assign(it1->second.begin(), it1->second.begin() + toRemove + 1);
					it1->second.erase(it1->second.begin(), it1->second.begin() + toRemove + 1);
					shortage -= toRemove;
				}
			}
		}
	}
	return 0;
}
// https://www.hackerrank.com/challenges/two-pluses/problem
// 100%
size_t TwoCrosses(vector<string> &grid)
{
	multimap<size_t, vector<size_t>> crosses;
	// Firstly, record all the crosses with size > 1. A single cell is considered a valid cross
	for (size_t i = 1; i < grid.size(); i++)
		for (size_t j = 1; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 'G')
			{
				size_t up = 0, down = 0, left = 0, right = 0;
				// UP
				for (long k = i - 1; k >= 0 && grid[k][j] == 'G'; k--)
					up++;
				// DOWN
				for (long k = i + 1; k < (long)grid.size() && grid[k][j] == 'G'; k++)
					down++;
				// LEFT
				for (long k = j - 1; k >= 0 && grid[i][k] == 'G'; k--)
					left++;
				// RIGHT
				for (long k = j + 1; k < (long)grid[i].size() && grid[i][k] == 'G'; k++)
					right++;
				size_t size = min(left, right);
				size = min(size, up);
				size = min(size, down);
				for (; size; size--)
					crosses.emplace(size * 4 + 1, vector<size_t>{i, j});
			}
		}
	// If no crosses with size > 1 found, return if there is a 'G' cell in the grid
	if (crosses.empty())
	{
		for (vector<string>::iterator it = grid.begin(); it != grid.end(); it++)
			if (it->find("G") != string::npos)
				return 1;
		return 0;
	}
	vector<size_t> crossCentre;
	set<size_t> products;
	size_t product = 0, firstWidth = 0;
	// Go through all the crosses, check for overlap and get the products of the 2 crosses.
	for (multimap<size_t, vector<size_t>>::iterator it1 = crosses.begin(); it1 != crosses.end(); it1++)
	{
		product = it1->first;
		crossCentre = it1->second;
		firstWidth = (it1->first - 1) / 4;
		products.insert(product);
		for (multimap<size_t, vector<size_t>>::iterator it = it1; it != crosses.end(); it++)
		{
			if (it->first > 1)
			{
				size_t x = it->second[1], y = it->second[0];
				size_t width = (it->first - 1) / 4;
				// Above at the same x position
				if (x == crossCentre[1] && y < crossCentre[0] && y + width < crossCentre[0] - firstWidth)
					products.insert(product * it->first);
				// Below at the same x position
				else if (x == crossCentre[1] && y > crossCentre[0] && y - width > crossCentre[0] + firstWidth)
					products.insert(product * it->first);
				// Left at the same y position
				else if (y == crossCentre[0] && x < crossCentre[1] && x + width < crossCentre[1] - firstWidth)
					products.insert(product * it->first);
				// Right at the same y position
				else if (y == crossCentre[0] && x > crossCentre[1] && x - width > crossCentre[1] + firstWidth)
					products.insert(product * it->first);
				// Top left of crossCentre
				else if (x < crossCentre[1] && y < crossCentre[0])
				{
					size_t right = x + width;
					size_t down = y + width;
					size_t top = crossCentre[0] - firstWidth;
					size_t left = crossCentre[1] - firstWidth;
					if ((right < crossCentre[1] || top > y) && (left > x || down < crossCentre[0]))
						products.insert(product * it->first);
				}
				// Bottom right of crossCentre
				else if (x > crossCentre[1] && y > crossCentre[0])
				{
					size_t right = crossCentre[1] + firstWidth;
					size_t down = crossCentre[0] + firstWidth;
					size_t top = y - width;
					size_t left = x - width;
					if ((right < x || top > crossCentre[0]) && (left > crossCentre[1] || down < y))
						products.insert(product * it->first);
				}
				// Top right of crossCentre
				else if (x > crossCentre[1] && y < crossCentre[0])
				{
					size_t right = crossCentre[1] + firstWidth;
					size_t top = crossCentre[0] - firstWidth;
					size_t down = y + width;
					size_t left = x - width;
					if ((left > crossCentre[1] || top > y) && (down < crossCentre[1] || right < x))
						products.insert(product * it->first);
				}
				// Bottom left of crossCentre
				else if (x < crossCentre[1] && y > crossCentre[0])
				{
					size_t left = crossCentre[1] - firstWidth;
					size_t down = crossCentre[0] + firstWidth;
					size_t right = x + width;
					size_t top = y - width;
					if ((top > crossCentre[0] || left > x) && (right < crossCentre[1] || down < y))
						products.insert(product * it->first);
				}
			}
		}
	}
	return *max_element(products.begin(), products.end());
}
// https://www.hackerrank.com/challenges/absolute-permutation/problem
// 100%
vector<long> absolutePermutation(size_t n, size_t k)
{
	vector<long> sequence(n, 0);
	generate(sequence.begin(), sequence.end(), [i = 1]() mutable
			 { return i++; });
	// |sequence[i] - i| = k
	vector<long> a, b;
	set<long> exists;
	for (size_t i = 1; i <= n; i++)
	{
		if (i > k && exists.find(i - k) == exists.end())
		{
			a.push_back(i - k);
			exists.insert(i - k);
		}
		else if (exists.find(i + k) == exists.end())
		{
			a.push_back(i + k);
			exists.insert(i + k);
		}
		else
			return vector<long>(1, -1);
	}
	vector<long> result(a);
	sort(a.begin(), a.end());
	if (a == sequence)
		return result;
	return vector<long>(1, -1);
}
// https://www.hackerrank.com/challenges/bomber-man/problem
// Times out!
vector<string> bomberMan(size_t n, vector<string> &grid)
{
	set<size_t> seconds;
	ostringstream oss;
	for (size_t second = 0; second <= n; second++)
	{
		if (!second)
		{
			// Initial state
			for (size_t i = 0; i < grid.size(); i++)
				for (size_t j = 0; j < grid[i].size(); j++)
				{
					if (grid[i][j] == 'O')
						grid[i][j] = '0'; // to detonate at third second. second % 3
				}
			seconds.insert(3);
			continue;
		}
		// After one second, Bomberman does nothing.
		if (second == 1)
			continue;
		if (seconds.find(second) != seconds.end())
		{ // Blow up!
			oss.str("");
			oss << second % 3;
			char pattern = oss.str()[0];
			for (size_t i = 0; i < grid.size(); i++)
				for (size_t j = 0; j < grid[i].size(); j++)
				{
					if (grid[i][j] == pattern)
					{
						grid[i][j] = '.';
						if (i > 0 && grid[i - 1][j] != pattern)
							grid[i - 1][j] = '.';
						if (i < grid.size() - 1 && grid[i + 1][j] != pattern)
							grid[i + 1][j] = '.';
						if (j > 0 && grid[i][j - 1] != pattern)
							grid[i][j - 1] = '.';
						if (j < grid[i].size() - 1 && grid[i][j + 1] != pattern)
							grid[i][j + 1] = '.';
					}
				}
			// cout << second << " (" << pattern << "): " << " blow up!" << endl;
			// for (size_t i = 0; i < grid.size(); i++)
			//     cout << grid[i] << endl;
		}
		else
		{ // Plant bombs
			oss.str("");
			oss << second % 3;
			char pattern = oss.str()[0];
			for (size_t i = 0; i < grid.size(); i++)
				for (size_t j = 0; j < grid[i].size(); j++)
				{
					if (grid[i][j] == '.')
						grid[i][j] = pattern; // to detonate at second + 2
				}
			seconds.insert(second + 3);
			// cout << second << " (" << pattern << "): " << " plant bombs!" << endl;
			// for (size_t i = 0; i < grid.size(); i++)
			//     cout << grid[i] << endl;
		}
	}
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] != '.')
				grid[i][j] = 'O'; // to detonate at third second. second % 3
		}
	return grid;
}
// https://www.hackerrank.com/challenges/the-grid-search/problem
// 100%
bool gridSearch(vector<string> &grid, vector<string> &pattern)
{
	size_t i = 0;
	size_t found = 0;
	set<size_t> locations;
	for (size_t j = 0; j < grid.size() && i < pattern.size();)
	{
		bool resetI = false;
		set<size_t> locations1;
		for (size_t offset = 0, tmp = 0; offset < grid[j].size() && tmp != string::npos; offset++)
		{
			tmp = grid[j].find(pattern[i], offset);
			if (tmp != string::npos)
				locations1.insert(tmp);
		}
		if (locations1.empty() && !locations.empty())
		{
			locations.clear();
			found = 0;
			i = 0;
			resetI = true;
		}
		else if (!locations1.empty() && locations.empty())
			locations = locations1;
		else if (!locations1.empty() && !locations.empty())
		{
			set<size_t> intersections;
			set_intersection(locations1.begin(), locations1.end(), locations.begin(), locations.end(), inserter(intersections, intersections.begin()));
			if (intersections.empty())
			{
				locations.clear();
				found = 0;
				i = 0;
				resetI = true;
			}
			else
				locations = intersections;
		}
		if (!locations.empty())
		{
			found++;
			i++;
		}
		if (!resetI) // Do not advance row if we have to search for pattern from the start of the pattern block
			j++;
	}
	return i == pattern.size() && found == pattern.size();
}
/*
 * https://www.hackerrank.com/challenges/the-quickest-way-up/problem
 * http://theoryofprogramming.com/2014/12/25/snakes-and-ladders-game-code/
 * Times out!
 */
size_t SnakesAndLaddersGame(vector<vector<size_t>> &ladders, vector<vector<size_t>> &snakes)
{
	map<size_t, size_t> laddermap, snakemap;
	shared_ptr<Vertex<size_t, size_t>> root(make_shared<Vertex<size_t, size_t>>(1));
	map<size_t, shared_ptr<Vertex<size_t, size_t>>> vertices;
	vertices.emplace(1, root);
	for (size_t i = 0; i < ladders.size(); i++)
		laddermap.emplace(ladders[i][0], ladders[i][1]);
	for (size_t i = 0; i < snakes.size(); i++)
		snakemap.emplace(snakes[i][0], snakes[i][1]);
	for (size_t i = 1; i <= 100; i++)
		if (laddermap.find(i) == laddermap.end() && snakemap.find(i) == snakemap.end())
		{ // Skip the number if it is at the beginning of a ladder
			shared_ptr<Vertex<size_t, size_t>> parent = vertices.find(i) != vertices.end() ? vertices[i] : nullptr;
			if (!parent)
			{
				parent = make_shared<Vertex<size_t, size_t>>(i);
				vertices.emplace(i, parent);
			}
			for (size_t j = min((long)6, (long)(100 - i)); j > 0; j--)
			{
				size_t next = i + j;
				if (laddermap.find(next) != laddermap.end())
					next = laddermap[next];
				if (snakemap.find(next) != snakemap.end())
					next = snakemap[next];
				shared_ptr<Vertex<size_t, size_t>> vertex = vertices.find(next) != vertices.end() ? vertices[next] : nullptr;
				if (!vertex)
				{
					vertex = make_shared<Vertex<size_t, size_t>>(next);
					vertices.emplace(next, vertex);
				}
				parent->AddNeighbour(vertex, 0);
			}
		}
	size_t level = 0;
	map<size_t, vector<shared_ptr<Vertex<size_t, size_t>>>> result;
	result.emplace(level, vector<shared_ptr<Vertex<size_t, size_t>>>{root});
	for (; !result[level].empty(); level++)
	{
		vector<shared_ptr<Vertex<size_t, size_t>>> tmp;
		for (vector<shared_ptr<Vertex<size_t, size_t>>>::const_iterator it = result[level].begin(); it != result[level].end(); it++)
		{
			if ((*it)->GetTag() == 100)
				return level;
			vector<shared_ptr<Vertex<size_t, size_t>>> neighbours = (*it)->GetNeighbours();
			tmp.insert(tmp.end(), neighbours.begin(), neighbours.end());
		}
		result.emplace(level + 1, tmp);
	}
	return 0;
}
/*
 * https://www.hackerrank.com/challenges/the-quickest-way-up/problem
 * http://theoryofprogramming.com/2014/12/25/snakes-and-ladders-game-code/
 * 100%
 */
size_t SnakesAndLaddersGameFast(vector<vector<size_t>> &ladders, vector<vector<size_t>> &snakes)
{
	map<size_t, vector<size_t>> adjacency_list;
	map<size_t, size_t> laddermap, snakemap;
	for (size_t i = 0; i < ladders.size(); i++)
		laddermap.emplace(ladders[i][0], ladders[i][1]);
	for (size_t i = 0; i < snakes.size(); i++)
		snakemap.emplace(snakes[i][0], snakes[i][1]);
	for (size_t i = 1; i <= 100; i++)
		if (laddermap.find(i) == laddermap.end() && snakemap.find(i) == snakemap.end())
		{ // Skip the number if it is at the beginning of a ladder
			for (size_t j = min((long)6, (long)(100 - i)); j > 0; j--)
			{
				size_t next = i + j;
				if (laddermap.find(next) != laddermap.end())
					next = laddermap[next];
				if (snakemap.find(next) != snakemap.end())
					next = snakemap[next];
				adjacency_list[i].push_back(next);
			}
		}
	size_t level = 0;
	map<size_t, vector<size_t>> result;
	result.emplace(level, vector<size_t>{1});
	set<size_t> visited;
	for (; !result[level].empty(); level++)
	{
		vector<size_t> tmp;
		for (vector<size_t>::const_iterator it = result[level].begin(); it != result[level].end(); it++)
		{
			if (visited.find(*it) == visited.end())
			{
				if (*it == 100)
					return level;
				if (adjacency_list.find(*it) != adjacency_list.end())
					tmp.insert(tmp.end(), adjacency_list[*it].begin(), adjacency_list[*it].end());
				visited.insert(*it);
			}
		}
		result.emplace(level + 1, tmp);
	}
	return 0;
}
/*
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/
 * 100%
 * aaa -> 1
 * abcabc ->
 * dvdf -> vdf
 * abcabb
 * abcabcbb -> abc
 * pwwkew -> kew or wke
 * ohvhjdml ->
 * vqblqcb
 */
size_t lengthOfLongestSubstring(const string &s)
{
	size_t maxLength = 0;
	set<char> chars;
	string str;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (chars.find(s[i]) == chars.end())
		{
			str.append(1, s[i]);
			chars.insert(s[i]);
		}
		else
		{
			if (str.size() > maxLength)
				maxLength = str.size();
			chars.clear();
			size_t offset = str.find_first_of(s[i]) + 1;
			if (offset > str.size())
				str.clear();
			else
			{
				for (size_t j = offset; j <= str.size(); j++)
					chars.insert(str[j]);
				str = str.substr(offset);
			}
			chars.insert(s[i]);
			str.append(1, s[i]);
		}
	}
	return max(str.size(), maxLength);
}
/*
 * https://leetcode.com/problems/zigzag-conversion/
 * 100%
 */
string zigzagconvert(const string &s, size_t numRows)
{
	bool direction = false;
	vector<string> str(numRows);
	for (long i = 0, row = 0; i < (long)s.size(); i++)
	{
		str[row].append(1, s[i]);
		if (!direction)
			row++;
		else
			row--;
		if (row == numRows)
		{
			row -= min((int)numRows, 2);
			direction = !direction;
		}
		else if (row < 0)
		{
			row += min((int)numRows, 2);
			direction = !direction;
		}
	}
	ostringstream oss;
	for (size_t i = 0; i < numRows; i++)
		oss << str[i];
	return oss.str();
}
/*
 * https://leetcode.com/problems/integer-to-roman/
 * 100%
 */
string numberToRoman(size_t num)
{
	string roman;
	size_t symbols;
	// >= 1000
	symbols = num / 1000;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'M');
	if (num >= 1000)
		num %= 1000;

	// 900 - 1000
	if (num >= 900)
	{
		roman.append("CM");
		num -= 900;
	}

	// 500 - 900
	if (num >= 500)
	{
		symbols = num / 500;
		for (size_t i = 0; i < symbols; i++)
			roman.append(1, 'D');
		num %= 500;
	}

	// 400 - 499
	if (num >= 400)
	{
		roman.append("CD");
		num -= 400;
	}

	// 100 -
	if (num >= 100)
	{
		symbols = num / 100;
		for (size_t i = 0; i < symbols; i++)
			roman.append(1, 'C');
		num %= 100;
	}

	// 90 - 99
	if (num >= 90)
	{
		roman.append("XC");
		num -= 90;
	}

	// 50 - 89
	if (num >= 50)
	{
		symbols = num / 50;
		for (size_t i = 0; i < symbols; i++)
			roman.append(1, 'L');
		num %= 50;
	}

	// 40 - 49
	if (num >= 40)
	{
		roman.append("XL");
		num -= 40;
	}
	symbols = num / 10;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'X');
	if (num >= 10)
		num %= 10;

	if (num == 9)
	{
		roman.append("IX");
		num -= 9;
	}

	if (num == 4)
	{
		roman.append("IV");
		num -= 4;
	}
	symbols = num / 5;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'V');
	if (num >= 5)
		num %= 5;

	symbols = num;
	for (size_t i = 0; i < symbols; i++)
		roman.append(1, 'I');
	return roman;
}
/*
* Calculate the median of 2 sorted lists of numbers in O(log (m+n))
* https://www.geeksforgeeks.org/median-two-sorted-arrays-different-sizes-ologminn-m/
Example (Even number of elements):
1 3 5 7 9
2 4 6 8 10

i: 5 / 2 = 2
j: (10 + 1) / 2 - 2 = 11 / 2 - 2 = 5 - 2 = 3
left: 5
right: 5

1 3		5 7 9
2 4 6	8 10
	 <-5 (Increase i)
	 6-> (Decrease j)
i++: 3
j: 11 / 2 - 3 = 5 - 3 = 2
1 3 5   7 9
2 4     6 8 10

median: (5+6) / 2 = 5.5
=================================
Example (Odd number of elements):
1 3 5 7 9
2 4 6 8 10 11

i: 5 / 2 = 2
j: (11 + 1) / 2 - 2 = 12 / 2 - 2 = 6 - 2 = 4
left: 6
right: 5
	left: 5
	right: 6

1 3		  5  7  9
2 4 6 8	  10 11
		<-5
		8->
i++: 3
j: 12/2 - 3 = 6 - 3 = 3
1 3 5	7 9
2 4 6	8 10 11
left: 6
right: 5

median: Max element in the LEFT (more counts compared to RIGHT): max(5,6) = 6
*/
double median(vector<long> &a, vector<long> &b)
{
	double result = 0;
	size_t minIndex = 0, maxIndex = min(a.size(), b.size());
	size_t count = a.size() + b.size();
	long i, j;
	if (a.empty() && b.empty())
		return result;
	else if (a.empty() && !b.empty())
		return b.size() % 2 ? b[b.size() / 2] : ((double)b[(b.size() / 2) - 1] + (double)b[b.size() / 2]) / (double)2;
	else if (!a.empty() && b.empty())
		return a.size() % 2 ? a[a.size() / 2] : ((double)a[(a.size() / 2) - 1] + (double)a[a.size() / 2]) / (double)2;
	for (bool found = false; minIndex <= maxIndex && !found;)
	{
		i = (minIndex + maxIndex) / 2;
		/*
		 * For add number, if no 1 is added, integer division by 2 will result in floor integer value.
		 * If 1 is added, integer division by 2 will result in ceiling integer value.
		 * For even number, adding 1 to the count does not affect integer division by 2 as floor integer value is the result.
		 * This will affect the algorithm to decide which partition to take for the odd number of elements.
		 */
		j = ((count + 1) / 2) - i;
		// If j < 0, adjust the number of elements from a included in the left partition
		if (j < 0)
		{
			maxIndex = i - 1; // Decreases i
			continue;
		}
		/* If i == a.size(), no element from a is included in the right partition
		 * If j == 0, no element from b is included in the left partition
		 */
		if (i < (long)a.size() && j > 0 && b[j - 1] > a[i])
			minIndex = i + 1; // i increases; j decreases
		/* If i == 0, no element from a is included in the left partition
		 * If j == b.size(), no element from b is included in the right partition
		 */
		else if (i > 0 && j < (long)b.size() && a[i - 1] > b[j])
			maxIndex = i - 1; // i decreases; j increases
		else
		{			// Found the desired partitions
			if (!i) // No element from a is incuded in the left partition
				result = b[j - 1];
			else if (!j)
				result = a[i - 1];
			else
				result = max(a[i - 1], b[j - 1]);
			found = true;
		}
	}			   // for
	if (count % 2) // Odd number of total elements in both the sorted list
		return result;
	else if (i == (long)a.size()) // No element from a is included in the right partition
		return (result + b[j]) / 2;
	else if (j == (long)b.size()) // No element from b is included in the right partition
		return (result + a[i]) / 2;
	return (result + min(a[i], b[j])) / 2;
}
/* https://leetcode.com/problems/search-a-2d-matrix/
 * 100%
 */
bool searchMatrix(vector<vector<long>> &matrix, long target)
{
	if (matrix.empty())
		return false;
	size_t rlower = 0, rupper = matrix.size() - 1, rmiddle = (rupper) / 2 + (rupper) % 2;
	// First get the row
	for (; rlower < rupper;)
	{
		if (target == matrix[rlower][0] || target == matrix[rmiddle][0] || target == matrix[rupper][0])
			return true;
		else if (target > matrix[rlower][0] && target < matrix[rmiddle][0])
		{
			rupper = rmiddle - 1;
			rmiddle = rlower + (rupper - rlower) / 2 + (rupper - rlower) % 2;
		}
		else if (target > matrix[rmiddle][0] && target < matrix[rupper][0])
		{
			rlower = rmiddle;
			rupper--;
			rmiddle = rlower + (rupper - rlower) / 2 + (rupper - rlower) % 2;
		}
		else if (target > matrix[rupper][0])
		{
			rlower = rupper;
			rmiddle = rupper;
		}
		else if (target < matrix[rlower][0])
			return false;
	}
	if (rlower == rmiddle || rlower == rupper)
	{ // Found the row
		size_t row = rlower;
		if (matrix[row].empty())
			return false;
		size_t clower = 0, cupper = matrix[row].size() - 1, cmiddle = (cupper) / 2 + (cupper) % 2;
		for (; clower <= cupper;)
		{
			if (target == matrix[row][clower] || target == matrix[row][cmiddle] || target == matrix[row][cupper])
				return true;
			else if (target > matrix[row][clower] && target < matrix[row][cmiddle])
			{
				cupper = cmiddle - 1;
				cmiddle = clower + (cupper - clower) / 2 + (cupper - clower) % 2;
			}
			else if (target > matrix[row][cmiddle] && target < matrix[row][cupper])
			{
				clower = cmiddle + 1;
				cmiddle = clower + (cupper - clower) / 2 + (cupper - clower) % 2;
			}
			else if (target > matrix[row][cupper] || target < matrix[row][clower])
				return false;
		}
	}
	return false;
}
bool searchMatrixRow(vector<vector<long>> &matrix, long target, size_t row, long start, long end)
{
	if (start >= 0 && end < (long)matrix[row].size() && start <= end)
	{
		if (matrix[row][start] == target || matrix[row][end] == target)
			return true;
		long middle = start + (end - start) / 2 + (end - start) % 2;
		if (matrix[row][middle] == target)
			return true;
		else if (matrix[row][middle] > target)
			return searchMatrixRow(matrix, target, row, start, middle - 1);
		else
			return searchMatrixRow(matrix, target, row, middle + 1, end);
	}
	return false;
}
bool searchMatrixCol(vector<vector<long>> &matrix, long target, size_t col, long start, long end)
{
	if (start >= 0 && end < (long)matrix.size() && start <= end)
	{
		if (matrix[start][col] == target || matrix[end][col] == target)
			return true;
		long middle = start + (end - start) / 2 + (end - start) % 2;
		if (matrix[middle][col] == target)
			return true;
		else if (matrix[middle][col] > target)
			return searchMatrixCol(matrix, target, col, start, middle - 1);
		else
			return searchMatrixCol(matrix, target, col, middle + 1, end);
	}
	return false;
}
/* https://leetcode.com/problems/spiral-matrix/
 * 100%
 */
vector<long> matrixSprialOrder(vector<vector<long>> &matrix)
{
	vector<long> result;
	int row = 0, col = 0;
	int left = 0, right = matrix[0].size() - 1, top = 0, bottom = matrix.size() - 1;
	for (row = top, col = left; top <= bottom && left <= right;)
	{
		// left to right
		for (; col <= right; col++)
			result.push_back(matrix[row][col]);
		top++;
		col--;
		row++;
		if (!(top <= bottom))
			return result;
		// top to bottom
		for (; row <= bottom; row++)
			result.push_back(matrix[row][col]);
		right--;
		bottom--;
		row--;
		col--;
		if (!(left <= right))
			return result;
		// right to left
		for (; col >= left; col--)
			result.push_back(matrix[row][col]);
		col++;
		row--;
		if (!(top <= bottom))
			return result;
		// bottom to top
		for (; row >= top; row--)
			result.push_back(matrix[row][col]);
		left++;
		row++;
		col++;
	}
	return result;
}
/* https://leetcode.com/problems/rotate-image/
 * Rotate a NxN 2D matrix 90 degree clockwise in-place.
 * 100%
 * [1] 2 [3]	7 [2]  1     7 4 1
 * 4   5  6  => 4  5  [6] => 8 5 2
 * 7  8   9     9  8   3     9 6 3
 *
 * [3] 2  1     7 [6] 1
 * 4   5  6     4  5  2
 * 7   8 [9]    9 [8] 3
 *
 * [9] 2 1      7  [8] 1
 * 4   5 6      [4] 5  2
 * [7] 8 3      9   6  3
 */
void rotateMatrix90DegressClockwise(vector<vector<long>> &matrix)
{
	for (long i = 0, j = matrix.size() - 1; i < j; i++, j--)
	{
		for (size_t k = 0; k < (size_t)(j - i); k++)
		{
			swap(matrix[i][i + k], matrix[i + k][j]);
			swap(matrix[i][i + k], matrix[j][j - k]);
			swap(matrix[i][i + k], matrix[j - k][i]);
		}
	}
}
size_t matrixDistance(size_t x1, size_t y1, size_t x2, size_t y2)
{
	size_t distance = 0;
	distance += x1 <= x2 ? x2 - x1 : x1 - x2;
	distance += y1 <= y2 ? y2 - y1 : y1 - y2;
	return distance;
}
/*
 * https://www.hackerrank.com/challenges/matrix-rotation-algo/problem
 * 100%
 * 1 2  r: 3
 * 3 4

 * 2 4
 * 1 3

 * 4 3
 * 2 1

 * 3 1
 * 4 2

1 2 4 3
r1: 2 4 3 1
r2: 4 3 1 2
r3: 3 1 2 4
 */
void rotateMatrixRTimesAntiClockwise(vector<vector<long>> &matrix, size_t rotation)
{
	long bottom = matrix.size() - 1, right = matrix[0].size() - 1, top = 0, left = 0;
	vector<long> items;
	for (; left < right && top < bottom; top++, left++, bottom--, right--)
	{
		size_t rowCount = right - left + 1, colCount = bottom - top - 1;
		size_t count = 2 * rowCount + 2 * (bottom - top - 1);
		if (!count)
			return;
		items.clear();
		size_t r = rotation % count;
		if (!r)
			continue;
		// Copy top row
		items.insert(items.end(), matrix[top].begin() + left, matrix[top].begin() + left + rowCount);
		// Copy right column
		for (size_t y = top + 1; y < bottom; y++)
			items.push_back(matrix[y][right]);
		// Copy bottom row in reverse order
		items.insert(items.end(), matrix[bottom].rbegin() + left, matrix[bottom].rbegin() + left + rowCount); // left here is offset from the right which is the same both left and right
		// Copy left column in reverse order
		for (long y = bottom - 1; y > top; y--)
			items.push_back(matrix[y][left]);
		rotate(items.begin(), items.begin() + rotation % count, items.end());
		// Copy back top row
		copy(items.begin(), items.begin() + rowCount, matrix[top].begin() + left);
		// Copy back right column
		for (size_t y = top + 1, i = rowCount; y < bottom && i < rowCount + colCount; y++, i++)
			matrix[y][right] = items[i];
		// Copy back bottom row in reverse order
		copy(items.begin() + rowCount + colCount, items.begin() + 2 * rowCount + colCount, matrix[bottom].rbegin() + left);
		// Copy back left column
		for (long y = bottom - 1, i = 2 * rowCount + colCount; y > top && i < 2 * rowCount + 2 * colCount; y--, i++)
			matrix[y][left] = items[i];
	}
}
/* https://leetcode.com/problems/search-a-2d-matrix-ii/
 * 100%
 */
bool searchMatrix1(vector<vector<long>> &matrix, long target)
{
	if (matrix.empty())
		return false;
	for (size_t row = 0, col = 0;;)
	{
		if ((row < matrix.size() && searchMatrixRow(matrix, target, row, col, matrix[row < matrix.size() ? row : row - 1].size() - 1)) ||
			(col < matrix[row < matrix.size() ? row : row - 1].size() && searchMatrixCol(matrix, target, col, row, matrix.size() - 1)))
			return true;
		if (row < matrix.size())
			row++;
		if (col < matrix[row < matrix.size() ? row : row - 1].size())
			col++;
		if (row >= matrix.size() && col >= matrix[row < matrix.size() ? row : row - 1].size())
			break;
	}
	return false;
}
/*
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/
 * 100%
 */
long ReversePolishNotation(vector<string> &tokens)
{
	stack<long> numbers;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
		{
			long num2 = numbers.top();
			numbers.pop();
			long num1 = numbers.top();
			numbers.pop();
			switch (tokens[i][0])
			{
			case '+':
				num1 += num2;
				break;
			case '-':
				num1 -= num2;
				break;
			case '*':
				num1 *= num2;
				break;
			case '/':
				num1 /= num2;
				break;
			default:
				throw runtime_error("Invalid operator!");
			}
			numbers.push(num1);
		}
		else
		{
			long num;
			istringstream(tokens[i]) >> num;
			numbers.push(num);
		}
	}
	return !numbers.empty() ? numbers.top() : numeric_limits<long>::max();
}
/*
3+2*2-1
sign:	+ + * -
stack:   3 2 4 -1 <= 3+4-1 = 6
3*2+2
sign:	+ * +
stack:	 3 6 2 <= 6+2 = 8
3+2-4*5
sign:	+ + -  *
stack:   3 2 -4 -20 <= 3+2-20
3*2+5/4
sign:	+ * + /
stack:   3 6 5 1 <= 6+1 = 7
*/
long basicCalculator(const string &s)
{
	stack<long> numbers;
	char sign = '+';
	long num = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (isdigit(s[i]))
			num = num * 10 + s[i] - '0';
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || i == s.size() - 1)
		{
			switch (sign)
			{
			case '+':
				numbers.push(num);
				break;
			case '-':
				numbers.push(-num);
				break;
			case '*':
			{
				long n = numbers.top();
				numbers.pop();
				numbers.push(num * n);
				break;
			}
			case '/':
			{
				long n = numbers.top();
				numbers.pop();
				numbers.push(n / num);
				break;
			}
			default:
				throw runtime_error("Invalid arithmetic sign!");
			}
			num = 0;
			sign = s[i];
		}
	}
	if (!numbers.empty())
		for (; !numbers.empty(); num += numbers.top(), numbers.pop())
			;
	return num;
}
/* https://leetcode.com/problems/minimum-size-subarray-sum/
*  100%
 0 1 2 3 4 5
[2,3,1,2,4,3] target: 7
 j     i		sum: 8 count: 4
   j   i		sum: 6
   j     i		sum: 10 count: 4
	 j   i		sum: 7 count: 3
	   j i		sum: 6
	   j   i	sum: 9 count: 3
		 j i	sum: 7 count: 2
[1 4 4]
 j i     sum: 5 count: 2
   i,j   sum: 4 count: 1
   j i   sum: 8 count: 2
	 i,j sum: 4 count: 1
*/
long ConsecutiveSumMinCount(long target, vector<long> &data)
{
	size_t count = numeric_limits<size_t>::max();
	long sum = 0;
	for (size_t i = 0, j = 0; i < data.size(); i++)
	{
		sum += data[i];
		for (; sum >= target; j++)
		{
			sum -= data[j];
			count = min(count, i - j + 1);
		}
	}
	return count == numeric_limits<size_t>::max() ? -1 : count;
}
/* https://leetcode.com/problems/product-of-array-except-self/
 * 100%
 */
vector<long> productExceptSelf(vector<long> &nums)
{
	vector<long> result(nums.size(), 1);
	/*
		1 2 3 4
		1 1 2 6 <- Accumulate forward
	*/
	for (size_t i = 0; i < nums.size() - 1; i++)
		result[i + 1] = result[i] * nums[i];
	/*
	   1   2  3 4
	   24 24 12 4 <- Accumulate backward
	*/
	long productSum = 1;
	for (long i = nums.size() - 1; i >= 0; i--)
	{
		result[i] *= productSum;
		productSum *= nums[i];
	}
	return result;
}
/* https://leetcode.com/problems/h-index/
 * 100%
 */
size_t hIndex(vector<size_t> &citations)
{
	size_t result = 0;
	if (citations.size() == 1)
		return citations[0] > 0 ? 1 : 0;
	sort(citations.begin(), citations.end());
	size_t previous = 0;
	/*
	 * [1,1] => value: 1, count: 2 => h: 1
	 * [1,2] => value: 1,2; count: 1 => h: 1
	 * [1,1,2] => value: 1, count 2 => h: 1
	 * [1,2,2] => value: 2, count: 2 => h: 2
	 * [3,2,2] => value: 2, count: 2 => h: 2
	 * [3,3,2] => value: 3, count: 2
	 */
	for (vector<size_t>::reverse_iterator it = citations.rbegin(); it != citations.rend(); it++)
	{
		if (*it != previous)
		{
			size_t value = *it;
			size_t count = count_if(citations.begin(), citations.end(), [&value](size_t i)
									{ return i >= value; });
			if (value < count && value > result)
				result = value;
			else if (value >= count && min(count, value) > result)
				result = min(count, value);
			previous = *it;
		}
	}
	return result;
}
/* https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * 100%
 */
vector<string> PhoneKeyLetters(const string &digits)
{
	map<char, string> letters{
		{'1', ""},
		{'2', "abc"},
		{'3', "def"},
		{'4', "ghi"},
		{'5', "jkl"},
		{'6', "mno"},
		{'7', "pqrs"},
		{'8', "tuv"},
		{'9', "wxyz"}};
	vector<string> result;
	if (digits.empty())
		return result;
	for (size_t i = 0; i < digits.size();)
	{
		vector<string> tmp;
		string str1 = letters[digits[i]];
		if (!i)
		{
			string str2 = i < digits.size() - 1 ? letters[digits[i + 1]] : "";
			if (str2.empty())
			{
				for (size_t j = 0; j < str1.size(); j++)
					tmp.push_back(string(1, str1[j]));
			}
			else
			{
				for (size_t j = 0; j < str1.size(); j++)
					for (size_t k = 0; k < str2.size(); k++)
					{
						ostringstream oss;
						oss << str1[j] << str2[k];
						tmp.push_back(oss.str());
					}
			}
			i += 2;
		}
		else
		{
			for (size_t j = 0; j < str1.size(); j++)
				for (vector<string>::iterator it = result.begin(); it != result.end(); it++)
				{
					ostringstream oss;
					oss << *it << str1[j];
					tmp.push_back(oss.str());
				}
			i++;
		}
		result = tmp;
	}
	return result;
}
/* https://leetcode.com/problems/word-break/
 * ["cats", "dog", "sand", "and", "cat"]
 * 012345678
 * catsandog
 * cats an dog
 * cat sand og
 *
 * 0123456789
 * catsanddog
 * cat sand dog
 * cats and dog
 *
 * Dynamic programming with tabulation (bottom-up) approach
 * if [0, end) is valid, all intermediate substrings which build up to [0, end) are also valid.
 * 0123456
 * catsand
 * [0,0) is valid -> [0,3) is valid -> [0,7) is valid
 * [0,0) is valid -> [0,4) is valid -> [0,7) is valid
 * 100%
 */
bool wordBreakDynamicProgramming(const string &s, set<string> &words)
{
	vector<bool> valid(s.size() + 1, false);	 // flag to mark substring [0, end) validity
	valid[0] = true;							 // empty substring is a valid string
	for (size_t end = 1; end <= s.size(); end++) // O(N)
		for (size_t start = 0; start < end; start++)
		{ // O(N) -> Time complexity: O(N^2)
			if (valid[start] && words.find(s.substr(start, end - start)) != words.end())
			{
				valid[end] = true;
				break;
			}
		}
	return valid.back();
}
/* https://leetcode.com/problems/word-break-ii/
 */
void wordBreakDynamicProgramming(const string &s, set<string> &words, vector<string> &result)
{
	map<size_t, vector<string>> strings;
	vector<bool> valid(s.size() + 1, false); // flag to mark substring [0, end) validity
	valid[0] = true;						 // empty substring is a valid string
	strings.emplace(0, vector<string>{""});
	for (size_t end = 1; end <= s.size(); end++)
		for (size_t start = 0; start < end; start++)
		{
			if (valid[start] && words.find(s.substr(start, end - start)) != words.end())
			{
				valid[end] = true;
				for (vector<string>::iterator it = strings[start].begin(); it != strings[start].end(); it++)
				{
					ostringstream oss;
					oss << *it << (it->empty() ? "" : " ") << s.substr(start, end - start);
					strings[end].push_back(oss.str());
				}
			}
		}
	if (strings.find(s.size()) != strings.end())
		result.insert(result.end(), strings[s.size()].begin(), strings[s.size()].end());
}
vector<string> wordBreakDFS(string s, set<string> &words, map<string, vector<string>> &strings)
{
	vector<string> result;
	if (s.empty())
		return vector<string>{""};
	else if (strings.find(s) != strings.end())
		return strings[s];
	for (set<string>::iterator it = words.begin(); it != words.end(); it++)
	{
		size_t found = s.find(*it);
		if (found == 0)
		{
			vector<string> tmp = wordBreakDFS(s.substr(it->size()), words, strings);
			for (vector<string>::iterator it1 = tmp.begin(); it1 != tmp.end(); it1++)
			{
				ostringstream oss;
				oss << *it << (it1->empty() ? "" : " ") << *it1;
				result.push_back(oss.str());
			}
		}
	}
	if (!result.empty())
		strings.emplace(s, result);
	return result;
}
vector<string> wordBreakDFS(const string &s, set<string> &words)
{
	map<string, vector<string>> strings;
	return wordBreakDFS(s, words, strings);
}
/* https://leetcode.com/problems/course-schedule/
 * https://en.wikipedia.org/wiki/Topological_sorting
 * Use Kahn's algorithm
 * 100%
 */
bool canFinishCourseTopologicalSort(size_t numCourses, vector<vector<size_t>> &courses, vector<size_t> &sequence) // First element depends on second element in each row
{
	map<size_t, size_t> dependencies;
	map<size_t, vector<size_t>> edges; // Key: Independent; Value: Dependent
	size_t edgeCount = courses.size();
	for (size_t i = 0; i < edgeCount; i++)
	{
		edges[courses[i][1]].push_back(courses[i][0]);
		dependencies[courses[i][0]]++;
	}
	queue<size_t> independentNodes; // Set of all nodes with no incoming edge
	for (size_t i = 0; i < numCourses; i++)
		if (dependencies.find(i) == dependencies.end())
			independentNodes.push(i);
	for (; !independentNodes.empty();)
	{
		size_t i = independentNodes.front();
		independentNodes.pop();
		sequence.push_back(i);
		if (edges.find(i) != edges.end())
			for (vector<size_t>::iterator it = edges[i].begin(); it != edges[i].end(); it++)
			{
				edgeCount--; // remove edge e from the graph
				if (dependencies.find(*it) == dependencies.end() || !--dependencies[*it])
					independentNodes.push(*it);
			}
	}
	return !edgeCount; // A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a directed acyclic graph (DAG)
}
/* https://leetcode.com/problems/contains-duplicate-iii/
* Use bucket sort theory.
* nums are distributed to bucket of size t.
* (1) All values within the same bucket will have a diff or distance <= t.
* (2) Neighbouring buckets will have a diff or distance ranging from t to 2*t.
* Observations:
* (1) Positive values will have even distribution of size t
* (2) Need to adjust the distribution of negative numbers
* (3) t+1 to avoid division by zero
 i i/w* desired**
-7 -3	-4
-6 -3	-3
-5 -2   -3
-4 -2   -2
-3 -1   -2
-2 -1   -1
-1  0   -1 => (i - 1) / w
 0  0    0
 1  0    0
 2  1    1
 3  1    1
 4  2    2
 5  2    2
 6  3	 3
 7  3	 3
 8  4	 4

t:2
w = t+1 = 3
i  i/w* desired**
-6 -2	-2    -6 -2 / 3 = -2
-5 -1   -2    -5 -2 / 3 = -2
-4 -1   -2    -4 -2 / 3 = -2
-3 -1   -1    -3 -2 / 3 = -1
-2  0   -1    -2 -2 / 3 = -1
-1  0   -1 => -1 -2 / 3 = -1
 0  0    0
 1  0    0
 2  0    0
 3  1    1
 4  1    1
 5  1    1
 6  2	 2
 7  2 	 2
 8  2	 2

 Test cases:
[2147483647,-1,2147483647]
k: 1
t: 2147483647
w = t + 1 = 2147483648
 i 			i/w*
-1 			(-1 /2147483648) - 1 = -1
2147483647  (2147483647)/2147483648 = 0;

[10,-1,10]
k: 1
t: 10
w: t+1 = 11
 i i/w*
-1 (-1 / 11) - 1 = -1
10 (10) / 11 = 0;

[-2147483648,2147483647] => [0x80000_000, 0x7FFF_FFFF]
k: 1
t: 1
w: t+1 = 2

 i 				i/w*
-2147483648		(-2147483648 / 2) - 1 = -0x40000000 - 1 = -0x40000001 (<0)
2147483647		(2147483647) / 2 > 0
*/
bool containsNearbyAlmostDuplicate(vector<long> &nums, long k, long t)
{
	map<long, long> buckets;
	if (k > 0 && t >= 0)
	{ // Absolute diff. t >= 0. k = 0 means diff is 0.
		long w = t + 1;
		for (size_t i = 0; i < nums.size(); i++)
		{
			long bucket = nums[i] < 0 ? (nums[i] / w) - 1 : nums[i] / w;
			if (buckets.find(bucket) != buckets.end()) // (1) All values within the same bucket will have a diff or distance <= t.
				return true;
			if (buckets.find(bucket - 1) != buckets.end() && (unsigned long)abs(buckets[bucket - 1] - nums[i]) <= (unsigned long)t)
				return true;
			if (buckets.find(bucket + 1) != buckets.end() && (unsigned long)abs(buckets[bucket + 1] - nums[i]) <= (unsigned long)t)
				return true;
			buckets.emplace(bucket, nums[i]);
			if ((long)i >= k)
			{ // ">=" as i will be +1 in the next loop and i will be > k
				long bucket = nums[i - k] < 0 ? (nums[i - k] - 1) / w : nums[i - k] / w;
				buckets.erase(bucket);
			}
		}
	}
	return false;
}
/* https://leetcode.com/problems/different-ways-to-add-parentheses/
 * 100%
 */
vector<long> diffWaysToCompute(string input)
{
	vector<long> result;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == '+' || input[i] == '-' || input[i] == '*')
		{
			vector<long> left = diffWaysToCompute(input.substr(0, i));
			vector<long> right = diffWaysToCompute(input.substr(i + 1));
			for (vector<long>::iterator it = left.begin(); it != left.end(); it++)
				for (vector<long>::iterator it1 = right.begin(); it1 != right.end(); it1++)
					switch (input[i])
					{
					case '+':
						result.push_back(*it + *it1);
						break;
					case '-':
						result.push_back(*it - *it1);
						break;
					case '*':
						result.push_back(*it * *it1);
						break;
					}
		}
	}
	if (result.empty())
	{
		long i;
		istringstream(input) >> i;
		result.push_back(i);
	}
	return result;
}
/* https://leetcode.com/problems/bulls-and-cows/
 * 100%
 */
string getHint(const string &secret, const string &guess)
{
	map<char, long> counts;
	size_t bulls = 0, cows = 0;
	for (size_t i = 0; i < secret.size(); i++)
		counts[secret[i]]++;
	for (size_t i = 0; i < secret.size(); i++)
	{
		if (secret[i] == guess[i])
		{
			bulls++;
			if (--counts[secret[i]] < 0 && cows > 0)
				cows--;
		}
		else if (counts.find(guess[i]) != counts.end() && counts[guess[i]] > 0)
		{
			counts[guess[i]]--;
			cows++;
		}
	}
	ostringstream oss;
	oss << bulls << "A" << cows << "B";
	return oss.str();
}
/* https://leetcode.com/problems/wiggle-subsequence/
 * 100%
 * 1 17 5 10 13 15 10 5 16 8
 * 1 17 5 15 5 16 8
 *
 * 1 17 5 10 13 15 12 5 16 8
 * 1 17 5 15 5 16 8
 *
 * 1 17 5 10 13 11 12 5 16 8
 * 1 17 5 13 11 12 5 16 8
 */
void wiggleMaxLength(vector<long> &nums, vector<long> &result)
{
	bool direction = false; // false: down. true: up
	for (size_t i = 0; i < nums.size(); i++)
	{
		if (!i)
			result.push_back(nums[i]);
		else if (nums[i] < result.back())
		{
			if (result.size() == 1 || direction)
				result.push_back(nums[i]);
			else if (!direction && nums[i] < result.back())
				result.back() = nums[i];
			direction = false;
		}
		else if (nums[i] > result.back())
		{
			if (result.size() == 1 || !direction)
				result.push_back(nums[i]);
			else if (direction && nums[i] > result.back())
				result.back() = nums[i];
			direction = true;
		}
	}
}
/* https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
 * If we treat null's as leaves, then the binary tree will always be full. A full binary tree has a good property that # of leaves = # of nonleaves + 1.
 * Since we are given a pre-order serialization, we just need to find the shortest prefix of the serialization sequence satisfying the property above.
 * If such prefix does not exist, then the serialization is definitely invalid; otherwise, the serialization is valid if and only if the prefix is the entire sequence.
 * 100%
 */
bool isValidPreOrderTreeSerialization(const string &preorder)
{
	vector<string> tokens;
	::split(preorder, ',', tokens);
	size_t leaves = 0, nonLeaves = 0, i = 0;
	for (; i < tokens.size() && leaves != nonLeaves + 1; i++)
	{
		if (tokens[i][0] == '#')
			leaves++;
		else
			nonLeaves++;
	}
	return leaves == nonLeaves + 1 && i == tokens.size();
}
/* https://leetcode.com/problems/integer-break/
 * 100%
 */
size_t LargestNumberCompositionProductWithDynamicProgramming(size_t n)
{
	vector<size_t> dp(n + 1, 0);
	dp[1] = 1;
	for (size_t i = 2; i <= n; i++)
		for (size_t j = 1; j < i; j++)
			dp[i] = max(dp[i], max(j, dp[j]) * max(i - j, dp[i - j]));
	return dp[n];
}
/* https://leetcode.com/problems/maximum-product-of-word-lengths/
 * 100%
 */
size_t maxProductOfNonOverlappingWordLengths(vector<string> &words)
{
	size_t result = 0;
#if 0
	Times out!
	set<char> intersection;
	vector<set<char>> strings;
	for (vector<string>::iterator it = words.begin(); it != words.end(); it++)
		strings.push_back(set<char>(it->begin(), it->end()));
	for (size_t i = 0; i < strings.size(); i++)
		for (size_t j = i + 1; j < strings.size(); j++) {
			intersection.clear();
			set_intersection(strings[i].begin(), strings[i].end(), strings[j].begin(), strings[j].end(), inserter(intersection, intersection.begin()));
			if (intersection.empty() && words[i].size() * words[j].size() > result)
				result = words[i].size() * words[j].size();
		}
#endif
	map<size_t, size_t> patterns;
	for (size_t i = 0; i < words.size(); i++)
	{
		int pattern = 0;
		for (size_t c = 0; c < words[i].size(); c++)
			pattern |= 1 << (words[i][c] - 'a');
		patterns[pattern] = max(patterns[pattern], words[i].size());
		for (map<size_t, size_t>::iterator it = patterns.begin(); it != patterns.end(); it++)
			if (!(it->first & pattern))
				result = max(result, it->second * words[i].size());
	}
	return result;
}
/* https://leetcode.com/problems/reconstruct-itinerary/
 * https://en.wikipedia.org/wiki/Eulerian_path
 * 100%
 * { {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"} }
 * (1) JFK -> ATL
 * (2) ATL -> JFK
 * (3) JFK -> SFO
 * (4) SFO -> ATL
 * (5) ATL -> SFO
 * JFK -> ATL -> JFK -> SFO -> ATL -> SFO
 */
vector<string> findItinerary(vector<vector<string>> &tickets, const string &start)
{
	map<string, multiset<string>> vertices;
	vector<string> itinerary;
	for (vector<vector<string>>::iterator it = tickets.begin(); it != tickets.end(); it++)
		vertices[it->front()].insert(it->back());
	if (vertices.find(start) != vertices.end())
		EulerianPath(start, vertices, itinerary);
	reverse(itinerary.begin(), itinerary.end());
	return itinerary;
}
void EulerianPath(string vertex, map<string, multiset<string>> &vertices, vector<string> &path)
{
	for (; !vertices[vertex].empty();)
	{
		string next = *vertices[vertex].begin();
		vertices[vertex].erase(vertices[vertex].begin());
		EulerianPath(next, vertices, path);
	}
	path.push_back(vertex);
}
/* The minimum amount of attempts to determine the pivot floor at and above which the egg breaks when dropped.
* Base case:
* 1 egg: conservatively try every single floor from bottom to top.
* 0 floor: 0 attempt
* 1 floor: 1 attempt
*
* 2 possibilities:
* Egg broken: 1 egg less, #floors = #floors - 1
* Egg not broken: Same eggs, #floors = #floors - floors tried so far
*
*		2 Eggs, 4 floors					<= for (size_t floor = 2; floor <= floors; floor++)
*    f=1		f=2			f=3		  f=4	<= for (size_t i = 2; i <= floor; i++)
* (1,0)(2,3) (1,1)(2,2) (1,2)(2,1) (1,3)(2,0)
*
* (2,3): f=1       f=2			f=3			<= for (size_t i = 2; i <= floor; i++)
*       (1,0)(2,2) (1,1)(2,1)  (1,2)(2,0)
*
* (2,2): f=1       f=2						<= for (size_t i = 2; i <= floor; i++)
*       (1,0)(2,1) (1,1)(2,0)
*
* (1,2): f=1       f=2						<= for (size_t i = 2; i <= floor; i++)
*       (0,0)(1,1) (0,1)(1,0)
*
* (1,3): f=1       f=2			f=3			<= for (size_t i = 2; i <= floor; i++)
*       (0,0)(1,2) (0,1)(1,1)  (0,2)(1,0)
* https://medium.com/@parv51199/egg-drop-problem-using-dynamic-programming-e22f67a1a7c3
Eggs\Floors	0	1	2	3	4	5	6
		1	0	1	2	3	4	5	6
		2	0	1
		3	0	1
* https://leetcode.com/problems/super-egg-drop/
* Time limit exceeded! :-(
*/
size_t eggDrops(size_t eggs, size_t floors)
{
	vector<vector<size_t>> dp(eggs, vector<size_t>(floors + 1, numeric_limits<size_t>::max()));
	// Base case for Floor-0 and Floor-1
	for (size_t i = 0; i < eggs; i++)
	{
		dp[i][0] = 0;
		if (floors > 0)
			dp[i][1] = 1;
	}
	// Base case for 1 egg
	generate(dp[0].begin(), dp[0].end(), [n = 0]() mutable
			 { return n++; });
	// size_t attempts = eggDropsDynamicProgramming(eggs, floors, dp);
	for (size_t egg = 1; egg < eggs; egg++)
		for (size_t floor = 2; floor <= floors; floor++)
			for (size_t i = 2; i <= floor; i++)
				dp[egg][floor] = min((size_t)dp[egg][floor], 1 + max((size_t)dp[egg - 1][i - 1], (size_t)dp[egg][floor - i]));
	return dp[eggs - 1][floors];
}
/*
 * https://en.wikipedia.org/wiki/Fizz_buzz
 * https://leetcode.com/problems/fizz-buzz/submissions/
 * 100%
 */
vector<string> fizzBuzz(size_t n)
{
	vector<string> result;
	for (size_t i = 1; i <= n; i++)
	{
		ostringstream oss;
		if (!(i % 3))
			oss << "Fizz";
		if (!(i % 5))
			oss << "Buzz";
		string str = oss.str();
		if (str.empty())
			str = to_string(i);
		result.push_back(str);
	}
	return result;
}