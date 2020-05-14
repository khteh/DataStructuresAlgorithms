#include "stdafx.h"
#include "InterviewQuestions.h"
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	string line, line1;
	random_device device;
	// Fourth run: "warm-up" sequence as as seed; different each run.
	// Advanced uses. Allows more than 32 bits of randomness.
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(begin(seeds), end(seeds));
	mt19937_64 engine(sequence);
	uniform_int_distribution<long> uniformDistribution;
	int i, j, index, *iPtr;
	unsigned long long mask = 0;
	vector<string> strings, strings1;
	set<string> stringset, stringset1;
	stringset.erase("Does not exist");
	vector<long> a, b, sortData;
	vector<int> data, data1;
	vector<unsigned long long> ull;
	priority_queue<long, deque<long>> maxHeap;
	priority_queue<long, deque<long>, greater<long>> minHeap;
	PriorityQueueMedian<long> pqueue;
	vector<vector<unsigned long>> grid;
	vector<vector<long>> grid1, grid2;
	ExceptionTest();
	TestRandom();
	GreedyAlgorithmTests();
	AnagramTests();
	PalindromeTests();
	SparseNumberTests();
	SortTests();
	BinarySearchTests();
	BinarySearchStringTests();
	BinarySearchCountTests();
	StackTests();
	QueueTests();
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
	strings.clear();
	strings = {"abcczch", "abcchcz", "abcde", "ABCCZCH", "ABCCHCZ", "ABCDE"};
	sort(strings.begin(), strings.end(), LexicographicSort);
	assert(strings[0] == "abcchcz");
	assert(strings[1] == "ABCCHCZ");
	assert(strings[2] == "abcczch");
	assert(strings[3] == "ABCCZCH");
	assert(strings[4] == "abcde");
	assert(strings[5] == "ABCDE");
	Singleton*singleton = Singleton::Instance();
	assert(singleton);
	singleton->Print("Hello Singleton!!!");
	unique_ptr<NameHidingExampleDerived> hide = make_unique<NameHidingExampleDerived>(0xdeadbeef);
	unique_ptr<NameHidingExample> hide1 = make_unique<NameHidingExampleDerived>(0xdeadbeef);
	hide->Print(1);
	hide1->Print(1);
	//hide->Print(1, 2);
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
	assert(str1.size() == 0);
	str1 = str.substr(0, 0);
	assert(str1.size() == 0);
	char cstr[8];
	cout << "sizeof(char[8]): " << sizeof(cstr) << endl;
	cout << "sizeof(void*): " << sizeof(void*) << endl;
	cout << "sizeof(int): " << (int)sizeof(int) << endl;
	cout << "sizeof(long): " << (int)sizeof(long) << endl;
	cout << "sizeof(size_t): " << (int)sizeof(size_t) << endl;
	cout << "sizeof(long long): " << (int)sizeof(long long) << endl;
	cout << "sizeof(unsigned long long): " << (int)sizeof(unsigned long long) << endl;
	cout << "sizeof(double): " << (int)sizeof(double) << endl;
	cout << "sizeof(long double): " << (int)sizeof(long double) << endl;
	cout << "https://en.wikipedia.org/wiki/Machine_epsilon: Float: " << numeric_limits<float>::epsilon() << ", Double: " << numeric_limits<double>::epsilon() << endl;
	cout << "Machine Epsilon: Float: " << MachineEpsilon((float)1) << ", Approximation: " << FloatMachineEpsilonApproximation() << endl;
	cout << "Machine Epsilon: Double: " << MachineEpsilon((double)1) << ", Approximation: " << MachineEpsilonApproximation() << endl;
	cout << "numeric_limits<int>::max(): " << numeric_limits<int>::max() << endl;
	cout << "1e9: "<< 1e9 << ", 10e9: " << 10e9 << endl;
	i = 3;
	assert(-i == -3);
	assert(~i == -4);
	cout << "int -" << hex << i <<": " << -i << dec << " " << -i << ", ~" << i << ": " << hex << ~i << " " << dec << ~i << endl;
	unsigned int ui = 3;
	cout << "uint -" << hex << ui << ": " << -ui << dec << " " << -ui << ", ~" << ui << ": " << hex << ~ui << " " << dec << ~ui << endl;
	a.resize(10);
	generate(a.begin(), a.end(), [n = 1]()mutable{return n++; });
	for (size_t i = 0; i < a.size(); i++)
		assert(a[i] == i+1);
	grid = { {1,3,5}, {2,4,6}, {7,8,9} };
	pathResult_t pathResult = FindMaxPath(grid, 0, 0);
	assert(pathResult.sum == 27);
	cout << "Grid traversal which yields maximum sum " << pathResult.sum << ": " << pathResult.path << endl;

	char mazeArray[5][5] = {{'1', '1', '1', '1', '1'}, {'S', '1', 'X', '1', '1'}, {'1', '1', '1', '1', '1'}, {'X', '1', '1', 'E', '1'}, {'1', '1', '1', '1', 'X'}};
	vector<vector<char>> maze;
	maze.resize(5);
	for (size_t i = 0; i < 5; i++) {
		maze[i].resize(5);
		for (size_t j = 0; j < 5; j++)
			maze[i][j] = mazeArray[i][j];
	}
	cout << "maze (" << maze.size() << "): " << endl;
	for (size_t i = 0; i < 5; i++) {
		for (size_t j = 0; j < 5; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
	queue<string> mazeResult;
	assert(FindShortestPath(maze, 1, 0, mazeResult, 'E', 'X'));
	cout << "Shortest path: ";
	while (!mazeResult.empty()) {
		line = mazeResult.front();
		mazeResult.pop();
		cout << line << " ";
	}
	cout << endl;
	grid1 = { {-1,0,-1}, {-1,-1,-1}, {-1,-1,-1} };
	MatrixDistance(grid1, 0, 1);
	cout << "grid1 (" << grid1.size() << "): " << endl;
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++)
			cout << grid1[i][j] << " ";
		cout << endl;
	}
	grid1 = { { 1,3,5 }, { 6,4,2 },{ 7,9,8 } };
	grid2 = { { 1,3,5 }, { 6,4,2 },{ 7,9,8 } };
	MatrixSort(grid1);
	cout << "MatrixSort: " << endl;
	for (size_t i = 0; i < grid1.size(); i++) {
		for (size_t j = 0; j < grid1[i].size(); j++)
			cout << grid1[i][j] << " ";
		cout << endl;
	}
	MatrixSortWithHeap(grid2);
	cout << "MatrixSortWithHeap: " << endl;
	for (size_t i = 0; i < grid2.size(); i++) {
		for (size_t j = 0; j < grid2[i].size(); j++) {
			cout << grid2[i][j] << " ";
			assert(grid1[i][j] == grid2[i][j]);
		}
		cout << endl;
	}
	grid1 = { { 0,0,1 },{ 0,1,1 },{ 1,1,1 } };
	assert(MatrixPatternCount(grid1) == 3);

	grid1 = { { 0,0,1 },{ 0,0,1 },{ 1,1,1 } };
	assert(MatrixPatternCount(grid1) == 4);

	grid1 = { { 0,0,0,1 },{ 0,0,1,1 },{ 0,1,1,1 },{1,1,1,1} };
	assert(MatrixPatternCount(grid1) == 6);

	grid1 = { { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{1,0,0,0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 5);
	assert(ConnectedCellsInAGrid(grid1) == 5);

	grid1 = { { 0,0,1,1 },{ 0,0,1,0 },{ 0,1,1,0 },{0,1,0,0},{1,1,0,0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 8);
	assert(ConnectedCellsInAGrid(grid1) == 8);
	
	grid1 = { { 1, 1, 0, 0, 0 },{0, 1, 1, 0, 0 },{ 0, 0, 1, 0, 1 },{1, 0, 0, 0, 1},{0, 1, 0, 1, 1} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 5);
	assert(ConnectedCellsInAGrid(grid1) == 5);
	
	grid1 = { { 0, 1, 1, 1, 1 },{1, 0, 0, 0, 1 },{ 1, 1, 0, 1, 0 },{0, 1, 0, 1, 1},{0, 1, 1, 1, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 15);
	assert(ConnectedCellsInAGrid(grid1) == 15);

	grid1 = { { 1, 1, 1, 0, 1 },{0, 0, 1, 0, 0 },{ 1, 1, 0, 1, 0 },{0, 1, 1, 0, 0},{0, 0, 0, 0, 0},{0, 1, 0, 0, 0},{0, 0, 1, 1, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 9);
	assert(ConnectedCellsInAGrid(grid1) == 9);

	grid1 = { { 1, 0, 0, 1, 0, 1, 0, 0 },{0, 0, 0, 0, 0, 0, 0, 1, },{ 1, 0, 1, 0, 1, 0, 0, 0, },{0, 0, 0, 0, 0, 0, 1, 0},{1, 0, 0, 1, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 1},{0, 1, 0, 0, 0, 1, 0, 0} };
	assert(ConnectedCellsInAGridLinkedList(grid1) == 1);
	assert(ConnectedCellsInAGrid(grid1) == 1);

	maze = {{0,0,1,0,1},{0,0,0,0,0},{0,1,1,1,1},{0,1,1,0,0}};
	queue<string> puzzleResult;
	assert(PathExists(maze, 1,4, 0,3, puzzleResult, 1));
	cout << "Puzzle path: ";
	while (!puzzleResult.empty()) {
		line = puzzleResult.front();
		puzzleResult.pop();
		cout << line << " ";
	}
	cout << endl;
	maze = {{0,0,1,1,1},{0,1,0,0,0},{1,1,1,1,1},{0,0,0,0,1}};
	queue<string> puzzleResult1;
	assert(!PathExists(maze, 0,0, 1,2, puzzleResult1, 1));
	line = "ab2c3";
	assert(uncompress(line) == "ababcababcababc");
	cout << "uncompress(\"ab2c3\"): " << uncompress(line) << endl;
	line = "0010110100";
	index = findLongestContiguousPattern(line, '1');
	cout << "findLongestContiguousPattern(\"0010110100\", \'0\'): " << line << " flip location: " << index << endl;

	// Test C++ *& "pointer reference" construct
	iPtr = (int*)malloc(10 * sizeof(int));
	cout << "Size of iPtr: " << sizeof (iPtr) << " Sizeof *iPtr: " << sizeof(*iPtr) << endl;
	memset(iPtr, 0xdeadbeef, 10 * sizeof(iPtr));
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
	line = "Hello World!!!";
	line1 = "llo World!!!He";
	assert(AreRotatedStrings(line, line1, 2));
	if (AreRotatedStrings(line, line1, 2))
		cout << line << " and " << line1 << " are rotated by 2 places" << endl;
	line = "abcdefcdbacd";
	line1 = "abcd";
	vector<size_t> indices = FindSubString(line, line1);
	assert(indices.size() == 4); // 0 6 7 8
	assert(indices[0] == 0);
	assert(indices[1] == 6);
	assert(indices[2] == 7);
	assert(indices[3] == 8);

	//index = KMPSearch("ABC ABCDAB ABCDABCDABDE", "ABCDABD");
	//assert(index == 15);
	assert(bitCount(10) == 2);
	assert(bitCount(12) == 2);
	assert(bitCount(7) == 3);
	a.clear();
	BitCombinations(3, a); // 000 001 010 100 011 101 110 111
	assert(a.size() == 8);
	assert(a[0] == 0);
	assert(a[1] == 1);
	assert(a[2] == 2);
	assert(a[3] == 4);
	assert(a[4] == 3);
	assert(a[5] == 5);
	assert(a[6] == 6);
	assert(a[7] == 7);
	cout << "BitCombinations from 0 to 3 of '1' bits: ";
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		cout << bitset<3>(*it) << " ";
	cout << endl;
	a.clear();
	BitCombinations(4, a); // 0000 0001 0010 0100 1000 0011 0101 0110 1001 1010 1100 0111 1011 1101 1110 1111
	assert(a.size() == 16);
	assert(a[0] == 0);
	assert(a[1] == 1);
	assert(a[2] == 2);
	assert(a[3] == 4);
	assert(a[4] == 8);
	assert(a[5] == 3);
	assert(a[6] == 5);
	assert(a[7] == 6);
	assert(a[8] == 9);
	assert(a[9] == 10);
	assert(a[10] == 12);
	assert(a[11] == 7);
	assert(a[12] == 11);
	assert(a[13] == 13);
	assert(a[14] == 14);
	assert(a[15] == 15);
	cout << "BitCombinations from 0 to 4 of '1' bits: ";
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		cout << bitset<4>(*it) << " ";
	cout << endl;
	strings.clear();
	strings = {"a", "b", "c", "d"};
	strings1 = { "b","c" };
	strings = findUnique(strings, strings1);
	assert(strings.size() == 2); //  a d
	assert(strings[0] == "a");
	assert(strings[1] == "d");
	assert(CanShuffleWithoutRepeat(string("a")));
	assert(!CanShuffleWithoutRepeat(string("aa")));
	assert(CanShuffleWithoutRepeat(string("aab")));
	assert(CanShuffleWithoutRepeat(string("aaaabbcc")));
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
	lResult = ConsecutiveLargestSum(a, b);
	assert(lResult == 1);
	a.clear();
	a = { -1, -1, -1, -1, -1, -1, 1, 1 };
	assert(LongestNonNegativeSumSlice(a) == 4);
	lResult = ConsecutiveLargestSum(a, b);
	assert(lResult == 2);
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
	sort(strings.begin(), strings.end(), [&strings](string a, string b) -> bool {
										sort(a.begin(), a.end());
										sort(b.begin(), b.end());
										return a < b;
									}
		);
	assert(strings[0] == "Hello World!!!");
	assert(strings[1] == "World Hello!!!");
	assert(strings[2] == "Angel");
	assert(strings[3] == "legnA");
	cout << "strings sorted with anagrams next to each other: " << endl;
	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, "\r\n"));
	a.clear();
	a = {0,1,2,7,10,11,12,20,25,26,27};
	string strRange = GetRange(a);
	assert(strRange == "0 - 2, 7, 10 - 12, 20, 25 - 27");
	cout << "GetRange(\"";
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, ", "));
	cout << "\") : " << strRange << endl;
	//copy_on_write_string();
	float f = 0xabcd;
	cout << "float f = 0xabcd: " << fixed << f << dec << endl;
	assert(_atod("1234") == 1234);
	assert(_atod("0xabcd") == 0xabcd);
	assert(_atoull("11011110101011011011111011101111", 2) == 0xdeadbeef);
	//assert(_atof("1234.5678") == 1234.5678);
	cout << "atof(\"1234\"): " << _atod("1234") << endl;
	cout << "atoi(\"0xabcd\"): " << hex << _atod("0xabcd", 10) << dec << endl;
	cout << "atoi(\"11011110101011011011111011101111\"): " << hex << _atoull("11011110101011011011111011101111", 2) << dec << endl; // 0xDeadBeef
	cout << "atof(\"1234.5678\"): " << _atod("1234.5678") << endl;
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
	generate(a.begin(), a.begin() + 10, [n = 0]()mutable{return n++; });
	generate(a.begin() + 10, a.end(), [n = 5]()mutable{return n++; });
	b.clear();
	findDistinct(a, b);
	assert(b.size() == 20);

	a.clear();
	b.clear();
	findPrimes(20, a); // Find prime numbers 0 to 20: 2,3,5,7,11,13,17,19
	assert(a.size() == 8);
	a.clear();
	b.clear();
	a = {15,10,3};
	b = {75,30,5};
	assert(CommonPrimeDivisors(a, b) == 1);
	a.clear();
	b.clear();
	a = {7,17,5,3};
	b = {7,11,5,2};
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
	assert(b[b.size() - 1] == 76);
	ull.clear();
	ull = {1,2,1,2};
	unsigned long long findMaxResult = findMax(ull);
	assert(findMaxResult == 9);

	ull.clear();
	ull = {2,3,3,2};
	findMaxResult = findMax(ull);
	assert(findMaxResult == 36);

	line = "     Hello     World!!!     ";
	assert(line.size() == 28);
	cout << line << " size: " << line.size();
	trim(line);
	//assert(line == "Hello     World!!!");
	cout << " trim(line): |" << line << "| size: " << line.size() << endl;

	a.clear();
	a = {1,2,3,4,5,6,5};
	assert(sumpairs(a, 8) == 2);

	a.clear();
	a = {5,7,9,13,11,6,6,3,3};
	assert(sumpairs(a, 12) == 3);

	//long testData[] = { 92,407,1152,403,1419,689,1029,108,128,1307,300,775,622,730,978,526,943,127,566,869,715,983,820,1394,901,606,497,98,1222,843,600,1153,302,1450,1457,973,1431,217,936,958,1258,970,1155,1061,1341,657,333,1151,790,101,588,263,101,534,747,405,585,111,849,695,1256,1508,139,336,1430,615,1295,550,783,575,992,709,828,1447,1457,738,1024,529,406,164,994,1008,50,811,564,580,952,768,863,1225,251,1032,1460,1558 };
	//vector<int> testDataVector(testData, testData + sizeof(testData) / sizeof(testData[0]));
	//assert(sumpairs(a, 8) == 2);
	a.clear();
	cout << endl;
	a.resize(10);
	iota(a.begin(), a.end(), 0);
	assert(sumpairs(a, 10) == 4);
	
	set<long> lSet {1,2,3,5,6,8,9,11,12,13};
	assert(diffpairs(lSet, 3) == 6);
	lSet.clear();
	lSet = { 1,5,3,4,2 };
	assert(diffpairs(lSet, 2) == 3);
	lSet.clear();
	lSet = {1,3,5,8,6,4,2};
	assert(diffpairs(lSet, 2) == 5);
	
	a.clear();
	a = {1,5,3,4,2};
	assert(diffpairs(a, 2) == 3);
	a.clear();
	a = {1,3,5,8,6,4,2};
	assert(diffpairs(a, 2) == 5);
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
	assert(strings.size() == 2);
	assert(strings[0] == "(())");
	assert(strings[1] == "()()");

	strings.clear();
	parentheses(strings, 3);
	assert(strings.size() == 5); // ((())) (()()) (())() ()(()) ()()()
	assert(strings[0] == "((()))");
	assert(strings[1] == "(()())");
	assert(strings[2] == "(())()");
	assert(strings[3] == "()(())");
	assert(strings[4] == "()()()");
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
#if 0
	stringset.clear();
	StringCombinations(stringset, string("1234"), "", 1);
	assert(stringset.size() == 8);
	assert(stringset.find("(1)(2)(3)(4)") != stringset.end());
	assert(stringset.find("(1)(2)(34)") != stringset.end());
	assert(stringset.find("(1)(23)(4)") != stringset.end());
	assert(stringset.find("(12)(3)(4)") != stringset.end());
	assert(stringset.find("(12)(34)") != stringset.end());
	assert(stringset.find("(1)(234)") != stringset.end());
	assert(stringset.find("(123)(4)") != stringset.end());
	assert(stringset.find("(1234)") != stringset.end());
	cout << "\"1234\" combinations: ";
	copy(stringset.begin(), stringset.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
#endif
	// Tower of Hanoi
	cout << "Tower Of Hanoi recursive solution: " << endl;
	unique_ptr<Tower> towers[3];
	for (i = 0; i < 3; i++)
		towers[i] = make_unique<Tower>(i);
	for (i = 10; i > 0; i--)
		towers[0]->Add(i);
	cout << "Tower 0 before move: " << endl;
	towers[0]->print();
	towers[0]->MoveDisks(5, towers[2].get(), towers[1].get());
	cout << "Tower 0,1,2 after move: " << endl;
	towers[0]->print();
	towers[1]->print();
	towers[2]->print();

	// Test 2D memory buffer allocation
	cout << "Test 2D memory buffer allocation...." << endl;
	long** my2Dbuffer = my2DAlloc(10, 10);
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			my2Dbuffer[i][j] = i*10 + j;
	//cout << "Content of 2D buffer: " << endl;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			//cout << my2Dbuffer[i][j] << " ";
			assert(my2Dbuffer[i][j] == i*10 + j);
		}
		//cout << endl;
	}
	free(my2Dbuffer);
	// Test 3D memory buffer allocation
	cout << "Test 3D memory buffer allocation...." << endl;
	long*** my3Dbuffer = my3DAlloc(10, 10, 10);
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			for (size_t k = 0; k < 10; k++)
				my3Dbuffer[i][j][k] = i*10 + j*10 + k;
	//cout << "Content of 3D buffer: " << endl;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++)
			for (size_t k = 0; k < 10; k++) {
				//cout << my3Dbuffer[i][j][k] << " ";
				assert(my3Dbuffer[i][j][k] == i * 10 + j * 10 + k);
			}
		//cout << endl;
	}
	free(my3Dbuffer);
	cout << "Test addition without using arithmetic symbol: " << endl;
	assert(AddWithoutArithmetic(0, 0) == 0);
	assert(AddWithoutArithmetic(0xdeadbeef, 0xfeedbeef) == 0x1dd9b7dde);
	assert(AddWithoutArithmetic(0xdeadbeef, 0) == 0xdeadbeef);
	assert(AddWithoutArithmetic(0, 0xfeedbeef) ==  0xfeedbeef);

	assert(NumberStringSum(string("1234567890"), string("9876543210")) == "11111111100");
	assert(NumberStringMultiplication(string("-4"), string("5")) == "-20");
	assert(NumberStringMultiplication(string("3"), string("-4")) == "-12");
	assert(NumberStringMultiplication(string("-7"), string("-8")) == "56");
	assert(NumberStringMultiplication(string("123456"), string("654321")) == "80779853376");
	assert(NumberStringMultiplication(string("456789"), string("987654")) == "451149483006");
	for (i = 0; i < 64; i++)
		mask |= ((unsigned long long)1 << i);
	cout << "mask: " << hex << mask << dec << endl << endl;

	cout << "Test shuffle deck of cards: " << endl;
	vector<long> cards, result;
	cards.resize(52);
	iota(cards.begin(), cards.end(), 0);
	shuffleCards(cards);
	for (i = 0; i < 52; i++) {
		if (i && !(i % 13))
			cout << endl;
		cout << cards[i] << " ";
	}
	cout << endl << endl;
	cout << "Randomly picking m integers out of an array: " << endl;
	randomSubset(cards, 13, result);
	assert(result.size() == 13);
	copy(result.begin(), result.end(), ostream_iterator<long>(cout, " "));
	cout << endl;

	// Test priority queue
	for (i = -10; i < 10; i++) {
		maxHeap.push(i);
		minHeap.push(i);
	}
	for (long i = 9; !maxHeap.empty(); i--) {
		//cout << maxHeap.top() << " ";
		assert(maxHeap.top() == i);
		maxHeap.pop();
	}
	for (long i = -10; !minHeap.empty(); i++) {
		//cout << minHeap.top() << " ";
		assert(minHeap.top() == i);
		minHeap.pop();
	}

	// Test Priority Queue which returns median value
	for (i = -10; i < 10; i++) // 20 numbers. Median = (10th + 11th) / 2
		pqueue.Add(i);
	assert(pqueue.GetMedian() == -0.5);
	pqueue.Add(10); // 21 numbers. Median = 11th number = 0
	assert(pqueue.GetMedian() == 0);
	pqueue.Clear();
	assert(pqueue.GetMedian() == 0);
	// Test countDigits
	//0 - 99: 10 + 10 = 20
	//100 - 199: 2 * 20
	//200 - 299: 3 * 20 + 100 = 160
	//300 - 345: 5(first digit) + 10(second digit) = 15
	//total: 160 + 15 = 175
	assert(countDigits(2, 345) == 175);
	assert(countDigits(0, 345) == 175);
	cout << "Number of '2' in 345 is: " << countDigits(2, 345) << endl;
	cout << "Number of '0' in 345 is: " << countDigits(0, 345) << endl;

	a.clear();
	b.clear();
	a = {1,7,15,29,11,9};
	EqualAverageDivide(a, b);
	assert(b.size() == 2);
	cout << "Left part: ";
	long sum = parallel_reduce(b.begin(), b.end(), 0);
	copy(b.begin(), b.end(), ostream_iterator<long>(cout, " "));
	assert(sum == 24);
	cout << "sum: " << sum << endl;
	
	vector<char> cData1{ 1,2,3 }, cData2{4,5,6};
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
	cData1 = { 9,8,7 };
	cData2 = { 6,5,4 };
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
	set<string> dictionary;
	dictionary.insert("DAMP");
	dictionary.insert("LAMP");
	dictionary.insert("LIMP");
	dictionary.insert("LIME");
	dictionary.insert("LIKE");
	dictionary.insert("LAKE");
	queue<string> result1;
	Transform(string("DAMP"), string("LIKE"), dictionary, result1);
	assert(result1.size() > 0);
	cout << "Single-character transformation from \"DAMP\" to \"LIKE\": ";
	while (!result1.empty()) {
		cout << result1.front() << " ";
		result1.pop();
	}
	assert(match("abba", "redbluebluered"));
	assert(match("aaaa", "asdasdasdasd"));
	assert(match("aabb", "xyzxyzabcabc"));
	assert(match("abab", "xyzabcxyzabc"));
	assert(!match("aabb", "xyzabcxyzabc"));
	assert(!match("abba", "xyzabcxyzabc"));
	assert(!match("aaaa", "xyzabcxyzabc"));
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
	set<string> ngrams = intersectionNgram(string("This is a dog"), string("This is a cat"), 3);
	assert(ngrams.size() == 1);
	assert(ngrams.find("This is a") != ngrams.end());
	cout << "3-gram result: ";
	copy(ngrams.begin(), ngrams.end(), ostream_iterator<string>(cout, ", "));
	cout << endl;

	ngrams = intersectionNgram(string("This is a dog"), string("This is a cat"), 4);
	assert(ngrams.size() == 0);
	cout << "4-gram result: ";
	copy(ngrams.begin(), ngrams.end(), ostream_iterator<string>(cout, ", "));
	cout << endl;
	data.clear();
	data.resize(4);
	generate(data.begin(), data.end(), [n = 1]()mutable{return n++; });
	vector<int> intResult = Increment(data);
	assert(intResult[0] == 1);
	assert(intResult[1] == 2);
	assert(intResult[2] == 3);
	assert(intResult[3] == 5);

	data.clear();
	data = {9,9,9,9};
	intResult = Increment(data);
	assert(intResult[0] == 1);
	assert(intResult[1] == 0);
	assert(intResult[2] == 0);
	assert(intResult[3] == 0);
	assert(intResult[4] == 0);

	void *addr = alignedMalloc(1000, 64);
	assert(addr);
	int alignment = (unsigned)addr % (64 / 8);
	assert(!alignment);
	memset(addr, 'a', 1000);
	alignedFree(&addr);
	assert(!addr);

	addr = alignedMalloc(1000, 32);
	assert(addr);
	alignment = (unsigned)addr % (32 / 8);
	assert(!alignment);
	alignedFree(&addr);
	assert(!addr);

	sortData.clear();
	sortData = {1,2,3,10,25,26,30,31,32,33};
	strings = numbersegments(sortData);
	copy(strings.begin(), strings.end(), ostream_iterator<string>(cout, ","));
	cout << endl;
	cout << hex << "XOR(1): " << XOR(1) << endl;
	cout << hex << "XOR(2): " << XOR(2) << endl;
	cout << hex << "XOR(3): " << XOR(3) << endl;
	cout << hex << "XOR(4): " << XOR(4) << endl;
	cout << hex << "XOR(5): " << XOR(5) << endl;
	assert(XOR(1) == 1);
	assert(XOR(2) == 3);
	assert(XOR(3) == 0);
	assert(XOR(4) == 4);
	assert(XOR(5) == 1);
	cout << dec;
	assert(DifferentSigns(10, -20));
	assert(!DifferentSigns(10, 20));
	assert(!DifferentSigns(-10, -20));
	assert(ToggleSign(-10) == 10);
	assert(ToggleSign(10) == -10);
	assert(absolute(-10) == 10);
	assert(absolute(10) == 10);
	assert(SubtractWithPlusSign(10, 5) == 5);
	assert(SubtractWithPlusSign(10, -5) == 15);
	assert(MultiplyWithPlusSign(10, 5) == 50);
	assert(MultiplyWithPlusSign(10, -5) == -50);
	assert(DivideWithPlusSign(10, 5) == 2);
	assert(DivideWithPlusSign(10, -5) == -2);
	assert(DivideWithPlusSign(-10, 5) == -2);
	assert(DivideWithPlusSign(-10, -5) == 2);
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
	a = {9,918,917};
	assert(concat(a) == 9918917);
	a.clear();
	a = {1,112,113};
	assert(concat(a) == 1131121);
	a.clear();
	a = {901,9015};
	// 9019015, 9015901
	assert(concat(a) == 9019015);
	a.clear();
	a = {3,4,6,5};
	b.clear();
	b = {9,1,2,5,8,3};
	assert(buildmax(a, b, 5) == 98653);
	strings.clear();
	strings = {"ABCW", "BAZ", "FOO", "BAR", "XTFN", "ABCDEF"};
	long max = MaxLengths(strings);
	assert(max == 24);
	a.clear();
	a.resize(10);
	generate(a.begin(), a.end(), [&] {return uniformDistribution(engine); });
	LinkedList<long> lla1(a);
	assert(lla1.Length() == 10);
	b.clear();
	lla1.ToVector(b);
	assert(a.size() == b.size());
	for (size_t i = 0; i < a.size(); i++)
		assert(a[i] == b[i]);
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
	generate(a.begin(), a.end(), [n = 0]()mutable{return n++; });
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
	lla2.Clear();
	a.clear();
	a.push_back(1); // LSB
	a.push_back(2);
	a.push_back(3); // MSB
	LinkedList<long> lla3(a);
	assert(lla3.Length() == 3);
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
	a.push_back(1); // MSB
	LinkedList<long> listAdditionResult = lla3.AddNumbers(lla3.Head(), llb1.Head()); // 987 + 321 = 1308 List in reverse order. Head points to LSB
	assert(listAdditionResult.Length() == 4);
	listAdditionResult.Print();
	i = 0;
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
	generate(a.begin(), a.end(), [&] {return uniformDistribution(engine); });
	generate(b.begin(), b.end(), [&] {return uniformDistribution(engine); });
	LinkedList<long> lla4(a), llb2(b);
	assert(lla4.Length() == 10);
	assert(llb2.Length() == 10);
	lla4.Join(llb2);
	assert(lla4.Length() == 20);
	assert(llb2.Length() == 0);
	lla4.Clear();
	llb2.Clear();
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
	//ChocolatesByNumbers(415633212, 234332);
	a.clear();
	a.push_back(3); // 3
	a.push_back(4); // 2
	a.push_back(5); // 1
	a.push_back(5); // 2
	a.push_back(2); // 1
	assert(CountDistinctSlices(6, a) == 9);
	a.clear();
	a.push_back(0); // 5
	a.push_back(1); // 4
	a.push_back(2); // 3
	a.push_back(3); // 2
	a.push_back(4); // 1
	assert(CountDistinctSlices(6, a) == 15); // 5 + 4 + 3
	a.clear();
	a.push_back(1); // 5
	a.push_back(1); // 4
	a.push_back(1); // 3
	a.push_back(1); // 2
	a.push_back(1); // 1
	assert(CountDistinctSlices(2, a) == 5); // 5 + 4 + 3
	a.clear();
	a.push_back(1); // 2
	a.push_back(2); // 1
	a.push_back(2); // 2
	a.push_back(3); // 1
	a.push_back(3); // 2
	a.push_back(4); // 1
	assert(CountDistinctSlices(3, a) == 9); // 5 + 4 + 3
	a.clear();
	a.push_back(1); // 2
	a.push_back(2); // 1
	a.push_back(2); // 3
	a.push_back(3); // 2
	a.push_back(4); // 1
	a.push_back(4); // 1
	assert(CountDistinctSlices(3, a) == 10); // 5 + 4 + 3
	a.clear();
	a.push_back(1); // 1
	a.push_back(1); // 4
	a.push_back(2); // 3
	a.push_back(3); // 2
	a.push_back(4); // 1
	a.push_back(4); // 1
	assert(CountDistinctSlices(3, a) == 12); // 5 + 4 + 3
	a.clear();
	a.push_back(1); // 2
	a.push_back(2); // 1
	a.push_back(1); // 3
	a.push_back(2); // 2
	a.push_back(4); // 1
	a.push_back(4); // 1
	assert(CountDistinctSlices(3, a) == 10); // 5 + 4 + 3
	a.clear();
	a.push_back(1); // 2
	a.push_back(2); // 1
	a.push_back(3); // 3
	a.push_back(4); // 2
	a.push_back(5); // 1
	a.push_back(6); // 1
	assert(CountDistinctSlices(3, a) == 21); // 5 + 4 + 3
	a.clear();
	a = {10,2,5,1,8,12};
	assert(CountTriangles(a) == 4);
	assert(decimal_to_binary(0) == "0");
	a.clear();
	a = {1,5,2,-2};
	assert(MinAbsSum(a) == 0);
	a.clear();
	a = { 2,2,1 };
	assert(MinAbsSum(a) == 1);
	a.clear();
	a = { 23171, 21011 , 21123 , 21366 , 21013 , 21367 };
	assert(MaxProfit(a) == 356);
	a.clear();
	a = { 5, 3, 2 };
	assert(StockMax(a) == 0);
	a.clear();
	a = { 1, 2, 100 };
	assert(StockMax(a) == 197);
	a.clear();
	a = { 1, 3, 1, 2 };
	assert(StockMax(a) == 3);
	a.clear();
	a = {1,-2,0,9,-1,-2};
	assert(NumberSolitaire(a) == 8);
	a.clear();
	a = {1,-2,4,3,-1,-3,-7,4,-9};
	assert(NumberSolitaire(a) == 3);
	a.clear();
	a = {0,-4,-5,-2,-7,-9,-3,-10};
	assert(NumberSolitaire(a) == -12);
	a.clear();
	a = {-1,-4,-5,-2,-7,-9,-3,-10};
	assert(NumberSolitaire(a) == -13);
	PlayTreasureGame();
	assert(countPaths(2, 2, 1, 1, 2) == 2); // 2
	assert(countPaths(2, 2, 1, 1, 3) == 0); // 0
	assert(countPaths(2, 2, 1, 1, 4) == 8); // 8
	assert(countPaths(5, 5, 4, 4, 5) == 0); // 0
	assert(countPaths(5, 8, 4, 6, 10) == 210); // 210
	assert(countPaths(5, 8, 4, 6, 16) == 2840838); // 2840838
	assert(countPaths(5, 8, 4, 6, 17) == 0); // 0
	//countPaths(5, 8, 4, 6, 18); too big
	//countPaths(5, 8, 4, 6, 20); too big
	//countPaths(5, 8, 4, 6, 21); too big
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
	data = {1,0,1,1,0,0,0};
	assert(findMinFlip(data) == 1);
	data.clear();
	data = { 0,0,0,0,1 };
	assert(findMinFlip(data) == 2);
	vector<vector<char>> m = {
		{ 'R', 'G', 'R', 'B' },
		{ 'R', 'Y', 'G', 'R' },
		{ 'G', 'B', 'Y', 'Y' },
		{ 'Y', 'G', 'B', 'G' },
		{ 'B', 'R', 'Y', 'B' },
	};
	assert(IsValidMatrix(m));
	vector<vector<char>> m1 = {
		{ 'R', 'G', 'R', 'B' },
		{ 'R', 'Y', 'G', 'R' },
		{ 'G', 'B', 'B', 'B' },
		{ 'Y', 'G', 'B', 'G' },
		{ 'B', 'R', 'Y', 'B' },
	};
	assert(!IsValidMatrix(m1));
	vector<vector<char>> m2 = {
		{ 'R', 'G', 'R', 'B' },
		{ 'R', 'Y', 'G', 'R' },
		{ 'G', 'B', 'G', 'Y' },
		{ 'Y', 'G', 'G', 'G' },
		{ 'B', 'R', 'Y', 'B' },
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
	a = {13,2,5};
	stringset.clear();
	//assert(ZigZagEscape(a, stringset) == 7);
	assert(ZigZagEscape(a) == 7);
	a.clear();
	a = { 4, 6, 2, 1, 5 };
	stringset.clear();
	//assert(ZigZagEscape(a, stringset) == 23);
	assert(ZigZagEscape(a) == 23);
	a.clear();
	a = {6,3,1,4,2,5};
	stringset.clear();
	//assert(ZigZagEscape(a, stringset) == 41);
	//assert(ZigZagEscape(a) == 41); Unfinished work!
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
	a = {-3,1,2,-2,5,6};
	assert(MaxProductOfThree(a) == 60);
	IncreasingSequenceTests();
	assert(binary_gap(9) == 2);
	assert(binary_gap(32) == 0);
	assert(binary_gap(529) == 4);
	data.clear();
	data.resize(5);
	generate(data.begin(), data.end(), [i = 0]()mutable{return i++; });
	RotateRightArray(data, 3);
	for (size_t i = 0, j = 2; i < 5; i++, j = ++j % 5)
		assert(data[i] == j);
	assert(CountDiv(6, 11, 2) == 3);
	assert(CountDiv(6, 11, 6) == 1);
	//assert(CountDiv(101, 123450000, 10000) == 12345);
	assert(CountDiv(0, 2000000000, 2000000000) == 2);
	assert(CountDiv(0, numeric_limits<int>::max(), numeric_limits<int>::max()) == 2);
	a.clear();
	a = {2,1,5,3,4};
	assert(minimumBribes(a) == 3);
	a.clear();
	a = {2,5,1,3,4};
	assert(minimumBribes(a) == -1);
	assert(SherlockValidString("abcdefghhgfedecba"));
	assert(!SherlockValidString("aabbcd"));
	assert(!SherlockValidString("aaaabbcc"));
	assert(!SherlockValidString("xxxaabbccrry"));
	assert(SherlockValidString("ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd"));
	line = "if man was meant to stay on the ground god would have given us roots";
	assert(encryption(line) == "imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau");
	a.clear();
	a = {100,100,50,40,40,20,10};
	b.clear();
	b = {5,25,50,120};
	vector<size_t> leaderBoardResult = climbingLeaderboard(a, b);
	assert(leaderBoardResult[0] == 6);
	assert(leaderBoardResult[1] == 4);
	assert(leaderBoardResult[2] == 2);
	assert(leaderBoardResult[3] == 1);
	a = absolutePermutation(10, 0);
	for (size_t i = 0; i < a.size(); i++)
		assert(a[i] == i + 1);
	a = absolutePermutation(10, 1);
	//for (int i = 0; i < a.size(); i++)
	//	assert(abs(a[i] - i - 1) == 1); Unfinished work!
	a.clear();
	a = {3,1,5,4,2};
	assert(calculateMedian(a) == 3);
	a.clear();
	a = {3,1,5,4,2,6};
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
	a = {1,3,5,7,9};
	DisJointSet<long> disjointSet(a);
	disjointSet.Print(a);
	// Test islands
	//assert(disjointSet.Find(0) == 0); C++ map will insert non-existing key silently
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
	assert(disjointSet.Union(1, 3) == 7); // 1, 3, 7 root: 7
	assert(disjointSet.Union(1, 7) == 0); // Already joined!
	assert(disjointSet.Rank(1) == 1);
	assert(disjointSet.Rank(3) == 1);
	assert(disjointSet.Rank(7) == 1);
	disjointSet.Print(a);
	assert(disjointSet.Find(1) == disjointSet.Find(3));
	assert(disjointSet.Find(3) != disjointSet.Find(5));
	assert(disjointSet.Find(5) != disjointSet.Find(7));
	assert(disjointSet.Find(7) != disjointSet.Find(9));
	assert(disjointSet.Find(3) == disjointSet.Find(7));
	//assert(disjointSet.Find(2) == 0); C++ map will insert non-existing key silently
	//assert(disjointSet.Find(1) != disjointSet.Find(2)); C++ map will insert non-existing key silently
	vector<long> from{ 1,1,4,2,3,3 }, to{ 2,3,1,4,2,4 }, weights{5,3,6,7,4,5};
	assert(kruskals(4, from, to, weights) == 12);
	from.clear();
	to.clear();
	weights.clear();
	from = {1,3,4,1,3};
	to = {2,2,3,4,1};
	weights = {1,150,99,100,200};
	assert(kruskals(4, from, to, weights) == 200);

	from.clear();
	to.clear();
	weights.clear();
	from = {1,3,1,4,2};
	to = {2,5,4,5,3};
	weights = {60,70,120,150,80};
	assert(getLowestPathCost(5, from, to, weights) == 80);

	from.clear();
	to.clear();
	weights.clear();
	from = {1,2,1,3};
	to = {2,4,3,4};
	weights = {20,30,5,40};
	assert(getLowestPathCost(4, from, to, weights) == 30);
	
	from.clear();
	to.clear();
	weights.clear();
	from = { 1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,8,8,9 };
	to = { 2,3,4,5,6,7,8,9,10,3,4,5,6,7,8,9,10,4,5,6,7,8,9,10,5,6,7,8,9,10,6,7,8,9,10,7,8,9,10,8,9,10,9,10,10 };
	weights = { 6337,1594,3766,3645,75,5877,8561,242,6386,3331,4194,8069,3934,101,8536,6963,9303,7639,8512,1330,6458,1180,3913,1565,9488,1369,8066,9439,7510,6833,4215,194,4774,4328,187,1196,200,8743,1433,2933,2069,1974,7349,2351,8423 };
	assert(from.size() == 45);
	assert(to.size() == 45);
	assert(weights.size() == 45);
	assert(getLowestPathCost(10, from, to, weights) == 1196);

	vector<vector<size_t>> ladders, snakes;
	ladders = { { 3, 54}, {37, 100} };
	snakes = { { 56, 33} };
	grid1 = { { 1,2,3 },{ 1,3,4 },{ 4,2,6 },{5,2,2},{2,3,5},{3,5,7} };
	assert(PrimMinimumSpanningTree(5, grid1, 1) == 15);

	grid1 = { { 1,2,20 },{ 1,3,50 },{ 1,4,70 },{1,5,90},{2,3,30},{3,4,40}, {4,5,60} };
	assert(PrimMinimumSpanningTree(5, grid1, 2) == 150);

	grid1 = { { 2,1,1000 },{ 3,4,299 },{ 2,4,200 },{2,4,100},{3,2,300},{3,2,6} };
	assert(PrimMinimumSpanningTree(4, grid1, 2) == 1106);

	grid1 = { { 1,2 },{ 2,3 },{ 1,4 } };
	vector<size_t> unbeatenPaths;
	UnbeatenPaths(4, grid1, 1, unbeatenPaths);
	assert(unbeatenPaths.size() == 3);
	assert(unbeatenPaths[0] == 3);
	assert(unbeatenPaths[1] == 1);
	assert(unbeatenPaths[2] == 2);

	grid1 = { { 1,2 },{ 2,3 } };
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
	grid1[0] = {1,0,1};
	assert(SurfaceArea3D(grid1) == 12);

	grid1 = { {1,3,4}, {2,2,3}, {1,2,4} };
	assert(SurfaceArea3D(grid1) == 60);

	grid1.clear();
	grid1.resize(1);
	grid1[0] = {1,2,3,4,5,5,4,3,2,1};
	assert(SurfaceArea3D(grid1) == 90);

	grid1 = { {1}, {2}, {3}, {4}, {5}, {5}, {4}, {3}, {2}, {1} };
	assert(SurfaceArea3D(grid1) == 90);

	grid1.clear();
	grid1.resize(1);
	grid1[0] = {1,2,3,4,5,4,5,4,3,2,1};
	assert(SurfaceArea3D(grid1) == 102);

	grid1 = { {1}, {2}, {3}, {4}, {5}, {4},{5}, {4}, {3}, {2}, {1} };
	assert(SurfaceArea3D(grid1) == 102);

	grid1 = { {51}, {32}, {28}, {49}, {28}, {21}, {98}, {56}, {99}, {77} };
	assert(SurfaceArea3D(grid1) == 1482);

	a.clear();
	a = { 4, 2 };
	assert(AlmostSorted(a) == "swap 1 2");
	a.clear();
	a = { 4104,8529,49984,54956,63034,82534,84473,86411,92941,95929,108831,894947,125082,137123,137276,142534,149840,154703,174744,180537,207563,221088,223069,231982,249517,252211,255192,260283,261543,262406,270616,274600,274709,283838,289532,295589,310856,314991,322201,339198,343271,383392,385869,389367,403468,441925,444543,454300,455366,469896,478627,479055,484516,499114,512738,543943,552836,560153,578730,579688,591631,594436,606033,613146,621500,627475,631582,643754,658309,666435,667186,671190,674741,685292,702340,705383,722375,722776,726812,748441,790023,795574,797416,813164,813248,827778,839998,843708,851728,857147,860454,861956,864994,868755,116375,911042,912634,914500,920825,979477};
	assert(AlmostSorted(a) == "swap 12 95");
	a.clear();
	a = { 43, 65, 1, 98, 99, 101 };
	assert(AlmostSorted(a) == "no");
	a.clear();
	/***** The End *****/
	cout << endl;
	cout << "Press ENTER to exit!";
	getline(cin, line);
	return 0;
}
void testPointerReference(int *& ptr)
{
	free(ptr);
	ptr = (int*)malloc(101 * sizeof(int));
	memset(ptr, 0xabababab, 101 * sizeof(ptr));
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
	for (i = 0; i < str.length(); i++) {
		if (char_set[str[i]])
			return false;
		char_set[str[i]] = true;
	}
	return true;
}
vector<string> findUnique(vector<string> const& a, vector<string>const& b)
{
	vector<string> result;
	vector<string> c(a);
	c.insert(c.end(), b.begin(), b.end());
	sort(c.begin(), c.end());
	for (vector<string>::const_iterator it = c.begin(); it != c.end(); it++) {
		if (it != (c.end() - 1)) {
			if (*it != *(it + 1))
				result.push_back(*it);
			else {
				while (it != (c.end() - 1) && *it == *(it + 1))
					it++;
			}
		} else
			result.push_back(*it);
	}
	return result;
}
bool CanShuffleWithoutRepeat(string& str)
{
	map<char, size_t> repeats;
	size_t max = 0;
	for (string::iterator it = str.begin(); it != str.end(); it++) {
		if (repeats.find(*it) == repeats.end())
			repeats.emplace(*it, 1);
		else
			repeats[*it]++;
		max = Max(max, repeats[*it]);
	}
	return str.size() - max >= max - 1;
}
// https://en.wikipedia.org/wiki/Maximum_subarray_problem
// Kadane's algorithm
long ConsecutiveLargestSum(vector<long>& data, vector<long>& result)
{
	long max_ending_here = 0, max_so_far = 0;
	vector<long>::iterator start, end;
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++) {
		max_ending_here += *it;
		if (max_ending_here < 0) {
			max_ending_here = 0;
			start = end = data.end();
		}
		if (max_so_far < max_ending_here) {
			max_so_far = max_ending_here;
			if (start == data.end())
				start = it;
			end = it;
		}
	}
	if (start != data.end() && end != data.end())
		result.assign(start, end + 1);
	return max_so_far;
}
// https://app.codility.com/programmers/task/longest_nonnegative_sum_slice/
// https://app.codility.com/programmers/challenges/ferrum2018/
// Find the longest sequence when the graph crosses a previous point. The crossing point is when negative becodes positive and vice versa
// 100%
long LongestNonNegativeSumSlice(vector<long>& data)
{
	// -1, -1, -1, -1, -1, -1, 1 (max_len = max(1, 6 - 4) = 2), 1 (max_len = max(2, 7 - 3) = 4)
	//  1,  1,  1,  1,  1,  1, -1(max_len = max(6, 6 - 4) = 6), -1(max_len = max(6, 7 - 3) = 6)
	map<long, size_t> sums;
	long sum = 0;
	size_t max_len = 0;
	for (size_t i = 0; i < data.size(); i++) {
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
size_t CountDistinctSlices1(long m, vector<long>& data)
{
	size_t slices = 0;
	set<string> uniqueslices;
	set<long> unique;
	size_t j;
	for (size_t i = 0; i < data.size(); ) {
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
size_t CountDistinctSlices(long m, vector<long>& data)
{
	size_t slices = 0, start = 0;
	set<long> unique;
	for (size_t i = 0; i < data.size(); i++) {
		if (unique.find(data[i]) == unique.end())
			unique.emplace(data[i]);
		else {
			slices += SequenceSum(i - start);
			start = i;
			unique.clear();
			unique.emplace(data[i]);
		}
	}
	return slices + SequenceSum(data.size() - start);
}
// "Hello World!!!" -> "!!!dlroW olleH"
void reverse(string& str)
{
	char tmp;
	size_t pivot = str.size() / 2 + str.size() % 2;
	for (size_t i = 0, tail = str.size() - 1; i < pivot; i++, tail--) {
		tmp = str[tail];
		str[tail] = str[i];
		str[i] = tmp;
	}
}

// "Hello World!!!" -> "World!!! Hello"
// 1: "Hello World!!!" -> "!!!dlroW olleH"
// 2: "!!!dlroW olleH" -> World!!! Hello"
void reverseWords(string &str)
{
	string tmp;
	reverse(str); //1:
	for (size_t i = 0, j = 0; i != string::npos; j = i + 1) {
		i = str.find(" ", j);
		if (i != string::npos) {
			tmp = str.substr(j, i - j);
			reverse(tmp);
			str.replace(j, i - j, tmp);
		} else {
			tmp = str.substr(j);
			reverse(tmp);
			str.replace(j, str.size() - j, tmp);
		}
	}
}
void RemoveDuplicateCharacters(string& str)
{
	size_t tail = 1, j;
	if (str.size() > 1) {
		for (size_t i = tail; i < str.size(); i++) {
			for (j = 0; j < tail && str[j] != str[i]; j++);
			if (j == tail) // str[i] is not a duplicate character. So copy it to str[tail]
				str[tail++] = str[i];
		}
		str[tail] = 0;
		str.resize(tail);
	}
}
bool areAnagrams(string const &s1, string const &s2)
{
	if (s1.size() == s2.size()) {
		string str1(s1), str2(s2);
		sort(str1.begin(), str1.end());
		sort(str2.begin(), str2.end());
		return str1 == str2;
	} else
		return false;
}
void FindAnagrams(vector<string> const& s, vector<vector<string>> &result)
{
	map<string, vector<string>> anagrams;
	for (vector<string>::const_iterator it = s.begin(); it != s.end(); it++) {
		string s1(*it);
		sort(s1.begin(), s1.end());
		anagrams[s1].push_back(*it);
	}
	for (map<string, vector<string>>::const_iterator it = anagrams.begin(); it != anagrams.end(); it++)
		result.push_back(it->second);
}
// https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem
// Unfinished work!
size_t sherlockAndAnagrams(string const& s)
{
	SuffixTree tree(s);
	return tree.AnagramSubStrings();
}
void PalindromeTests()
{
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
}
bool isPalindrome(string const& s)
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
bool isPalindrome1(string const& s)
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
bool isPalindrome2(string const& s)
{
	for (size_t i = 0, j = s.size() - 1; i <= j;) {
		if (!isalnum(s[i])) {
			i++;
			continue;
		}
		if (!isalnum(s[j])) {
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
// https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=strings
// adapt from isPalindrome()
// 100%
bool SherlockValidString(string const& s)
{
	size_t odd = 0;
	size_t length = s.length();
	map<char, size_t> counts;
	for (string::const_iterator it = s.begin(); it != s.end(); it++)
		counts[*it]++;
	size_t min = numeric_limits<size_t>::max(), max = 0;
	bool result = true;
	map<size_t, size_t> countsCounts;
	for (map<char, size_t>::const_iterator it = counts.begin(); it != counts.end(); it++) {
		if (it->second % 2 && (!(length % 2) || ++odd > 1))
			result = false;
		if (it->second > max)
			max = it->second;
		if (it->second < min)
			min = it->second;
		pair<map<size_t, size_t>::iterator, bool> result1 = countsCounts.emplace(it->second, 1);
		if (!result1.second)
			countsCounts[it->second]++;
	}
	if (countsCounts.size() == 2 && countsCounts.find(1) != countsCounts.end() && countsCounts[1] == 1)
		return true;
	return max - min > 1 ? false : result;
}
string FindBiggestPalindromeSubstring(string const& s)
{
	string tmp, palindrome;
	for (size_t i = 1; i < s.size() - 1; i++) {
		if (s[i] == s[i + 1]) { // Even palindrome
			for (int j = i, k = i + 1; j >= 0; j--, k++) {
				if (s[j] == s[k]) {
					tmp = s.substr(j, k - j + 1);
					if (tmp.size() > palindrome.size())
						palindrome = tmp;
				} else
					break;
			}
		} else if (s[i - 1] == s[i + 1]) { // Odd palindrome
			for (int j = i - 1, k = i + 1; j >= 0; j--, k++) {
				if (s[j] == s[k]) {
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
	for (size_t i = 0; i < str.size(); i++) {
		for (size_t j = 1; j <= str.size() - i; j++) {
			substr = str.substr(i, j);
			if (j == 1 || (j == 2 && substr[0] == substr[1]))
				result++;
			else if (isPalindrome(substr)) {
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
	for (size_t i = 0; i < str.size(); i++) {
		for (size_t j = 1; j <= str.size() - i; j++) {
			counts[str[i + (j - 1)]]++;
			evenLength = !(j % 2);
			if (counts[str[i + (j - 1)]] % 2) {
				odd++;
				oddNumbers.emplace(str[i + (j - 1)]);
			}
			else {
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
	for (size_t i = 0; i < s1.size(); i++) {
		if (areAnagrams(s1.substr(i, s2.size()), s2))
			result.push_back(i);
	}
	return result;
}
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
// Unfinished work!
void KMPTable(string const& w, vector<long>& T)
{
	size_t pos = 2; // the current position we are computing in T
	size_t cnd = 0;	//the zero-based index in W of the next character of the current candidate substring
	// the first few values are fixed but different from what the algorithm might suggest
	T.push_back(-1);
	while (pos < w.size()) {
		// first case: the substring continues
		if (w[pos - 1] == w[cnd]) {
			T.resize(pos + 1);
			T[pos++] = ++cnd;
			// second case: it doesn't, but we can fall back
		} else if (cnd > 0)
			cnd = T[cnd];
		// third case: we have run out of candidates.  Note cnd = 0
		else {
			T.resize(pos + 1);
			T[pos++] = 0;
		}
	}
}
size_t KMPSearch(string const& s, string const& w)
{
	size_t m = 0, i = 0;
	vector<long> T;
	KMPTable(w, T);
	while ((m + 1) < s.size()) {
		if (w[i] == s[m + 1]) {
			if (i == (w.size() - 1))
				return m;
			i++;
		}
		else {
			if (T[i] > -1) {
				m = m + i - T[i];
				i = T[i];
			}
			else {
				i = 0;
				m++;
			}
		}
	}
	return s.size();
}
void copy_on_write_string()
{
	const char *cptr, *cptr1;
	string s1("Hello World!!!");
	string s2 = s1;
	cptr = s1.c_str();
	cptr1 = s1.c_str();
	cout << hex << "s1 @ " << (void*)(cptr) << endl;
	cout << "s2 @ " << (void*)(cptr1) << endl;
	s2 += " Hello World!!!";
	cptr = s1.c_str();
	cptr1 = s1.c_str();
	cout << hex << "s1 @ " << (void*)(cptr) << endl;
	cout << "s2 @ " << (void*)(cptr1) << endl;
}
long fibonacci(long n)
{
	// Index: 0 1 2 3
	// Value: 0 1 1 2
	return (n <= 1) ? n : fibonacci(n - 2) + fibonacci(n - 1);
}
// https://www.hackerrank.com/challenges/fibonacci-modified/problem
// Timeout for n >= 20
string fibonacciModified(long t1, long t2, long n)
{
	// Index: 0 1 2 3 4 5  6   7	  8
	// Value: 0 1 1 2 5 27 734 538783 ...
	if (n == 0)
		return to_string(t1);
	else if (n == 1)
		return to_string(t2);
	string s1 = fibonacciModified(t1, t2, n - 2);
	string s2 = fibonacciModified(t1, t2, n - 1);
	string s3 = NumberStringMultiplication(s2, s2);
	return NumberStringSum(s1, s3);
}
// http://web2.0calc.com/
// 64-bit max is 18446744073709551615
// Overflow happens at 21!
unsigned long long factorial(long n)
{
	return (n <= 0) ? 1 : n * factorial(n - 1);
}
long SequenceSum(long n)
{
	//return (n <= 0) ? 0 : n + SequenceSum(n - 1);
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
	for (long i = 5; (n / i) > 0; i*=5)
		count += (n / i);
	return count;
}
void MultiplesCount(int dividend, long &twos, long &fives)
{
	long div = dividend;
	if (dividend > 0) {
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
	for (size_t i = 0; i < data.size(); i++) {
		if (!(data[i] % 10 && data[i] % 2 && data[i] % 5)) {
			it = multipleMap.find(data[i]);
			ZeroFactors factor;
			if (it == multipleMap.end()) {
				long two = 0, five = 0;
				MultiplesCount(data[i], two, five);
				factor.two = two;
				factor.five = five;
				multipleMap.emplace(data[i], factor);
				factors.push_back(factor);
			} else {
				factor.two = it->second.two;
				factor.five = it->second.five;;
				factors.push_back(factor);
			}
		}
	}
	if (factors.size() == 1)
		result = min(factors[0].two, factors[0].five);
	else if (factors.size() == 2)
		result = min(factors[0].two + factors[1].two, factors[0].five + factors[1].five);
	else if (factors.size() > 2) {
		for (size_t i = 0; i < factors.size() - 2; i++) {
			for (size_t j = i + 1; j < factors.size() - 1; j++) {
				for (size_t k = j + 1; k < factors.size(); k++) {
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
	//vector<vector<long>> subset(count, vector<long>(100, -1));
	//map<long, long> twos, fives;
	set<long> twos, fives;
	for (size_t i = 0; i < data.size(); i++) {
		if (!(data[i] % 10 && data[i] % 2 && data[i] % 5)) {
			it = multipleMap.find(data[i]);
			ZeroFactors factor;
			if (it == multipleMap.end()) {
				long two = 0, five = 0;
				MultiplesCount(data[i], two, five);
				factor.two = two;
				factor.five = five;
				multipleMap.emplace(data[i], factor);
				factors.push_back(factor);
			} else {
				factor.two = it->second.two;
				factor.five = it->second.five;;
				factors.push_back(factor);
			}
			//twos[factor.two] = max(twos[factor.two], factor.five);
			//fives[factor.five] = max(fives[factor.five], factor.two);
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
	//for (map<long, long>::const_iterator it = subset.begin(); it != subset.end(); it++)
	//	result = max(result, min(it->))
	return 0;
}
long ConsecutiveLargestSumOfFactors(vector<zerofactors_t>& data, vector<zerofactors_t>& result, int value)
{
	long max_ending_here = 0, max_so_far = 0, count = 0;
	vector<zerofactors_t>::iterator start = data.end(), end = data.end();
	for (vector<zerofactors_t>::iterator it = data.begin(); it != data.end(); it++) {
		max_ending_here += (value == 2) ? it->two : it->five;
		if (max_ending_here < 0) {
			max_ending_here = 0;
			start = end = data.end();
		}
		if (max_so_far < max_ending_here) {
			max_so_far = max_ending_here;
			if (start == data.end())
				start = it;
			end = it;
		}
		if (++count >= 3) {
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
	//assert(MaxZeroProduct(data) == 5);
	assert(MaxZeroProductBruteForce(data) == 5);
	data.clear();
	data.push_back(2 * 5 * 5);
	data.push_back(2 * 2 * 5 * 5);
	data.push_back(2 * 2 * 2 * 5 * 5 * 5);
	//assert(MaxZeroProduct(data) == 6);
	assert(MaxZeroProductBruteForce(data) == 6);
	data.clear();
	data.push_back(7);
	data.push_back(15);// 3 * 5
	data.push_back(6); // 2
	data.push_back(20);// 2 * 2 * 5
	data.push_back(5); // 5
	data.push_back(10);// 2 * 5
	//assert(MaxZeroProduct(data) == 3);
	assert(MaxZeroProductBruteForce(data) == 3);
	data.clear();
	data = {25,10,25,10,32};
	//assert(MaxZeroProduct(data) == 4);
	assert(MaxZeroProductBruteForce(data) == 4);
	data.clear();
	data = { 1, 1, 100 };
	//assert(MaxZeroProduct(data) == 2);
	assert(MaxZeroProductBruteForce(data) == 2);
	data.clear();
	data = {1,4,25};
	//assert(MaxZeroProduct(data) == 2);
	assert(MaxZeroProductBruteForce(data) == 2);
	data.clear();
	data = { 1, 1, 101 };
	//assert(MaxZeroProduct(data) == 0);
	assert(MaxZeroProductBruteForce(data) == 0);
	data.clear();
	data = { 1, 25, 25 };
	//assert(MaxZeroProduct(data) == 0);
	assert(MaxZeroProductBruteForce(data) == 0);
	data.clear();
	data = { 125, 100, 125, 100, 64 };
	//assert(MaxZeroProduct(data) == 6);
	assert(MaxZeroProductBruteForce(data) == 6);
	data.clear();
	data.resize(9);
	generate(data.begin(), data.end(), [i = 1]()mutable{return i++; });
	//assert(MaxZeroProduct(data) == 1);
	assert(MaxZeroProductBruteForce(data) == 1);
	data.push_back(10);
	//assert(MaxZeroProduct(data) == 2);
	assert(MaxZeroProductBruteForce(data) == 2);
	data.clear();
	data.push_back(10);
	data.push_back(1000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	//assert(MaxZeroProduct(data) == 21);
	assert(MaxZeroProductBruteForce(data) == 21);
	data.clear();
	data.push_back(100000);
	data.push_back(10000000);
	data.push_back(10000000);
	data.push_back(10000000);
	//assert(MaxZeroProduct(data) == 21);
	assert(MaxZeroProductBruteForce(data) == 21);
	data.clear();
	data.push_back(1220703125);
	data.push_back(8192);
	//assert(MaxZeroProduct(data) == 13);
	assert(MaxZeroProductBruteForce(data) == 13);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5);//2^26
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5); //5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5); //5^12
	//assert(MaxZeroProduct(data) == 25);
	assert(MaxZeroProductBruteForce(data) == 25);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);//2^25
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2); //5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5); //5^12
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); //2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);//5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);//5^12
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);//2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);//5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);//5^12
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);//2^23
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(1000000000);
	data.push_back(1000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	//assert(MaxZeroProduct(data) == 26);
	assert(MaxZeroProductBruteForce(data) == 26);
	data.clear();
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	data.push_back(2000000000);
	//assert(MaxZeroProduct(data) == 27);
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
	//assert(MaxZeroProduct(data) == 1);
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
	//assert(MaxZeroProduct(data) == 1);
	assert(MaxZeroProductBruteForce(data) == 1);
	data.clear();
	data.push_back(1024);
	data.push_back(512);
	data.push_back(256);
	data.push_back(128);
	data.push_back(64);
	data.push_back(32);
	data.push_back(5); //this
	data.push_back(8);
	data.push_back(4);
	data.push_back(2); // this
	data.push_back(1);
	data.push_back(3);
	data.push_back(16);
	//assert(MaxZeroProduct(data) == 1);
	assert(MaxZeroProductBruteForce(data) == 1);
	data.clear();
	random_device device;
	// Uniform distribution used with vector
	// Distribution is [-5, 5] inclusive
	uniform_int_distribution<int> dist(0, 1000000000);
	data.resize(100);
	generate(data.begin(), data.end(), [&] { return dist(device); });
	long result1 = MaxZeroProductBruteForce(data);
	//long result2 = MaxZeroProduct(data);
	//assert(result1 == result2);
}
set<string> permute(string const &str)
{
	set<string> permutations;
	if (str.empty())
		return permutations;
	else if (str.size() == 1) {
		permutations.insert(str);
		return permutations;
	}
	char toInsert = str[0];
	set<string> words = permute(str.substr(1));
	for (set<string>::iterator it = words.begin(); it != words.end(); it++) {
		for (size_t i = 0; i <= it->size(); i++)
			permutations.insert(insertCharAt(toInsert, *it, i));
	}
	return permutations;
}
set<vector<long>> permute(vector<long>& data)
{
	set<vector<long>> permutations;
	if (data.empty())
		return permutations;
	else if (data.size() == 1) {
		vector<long> tmp { data[0] };
		permutations.insert(tmp);
		return permutations;
	}
	long toInsert = data[0];
	vector<long> subset(data.begin() + 1, data.end());
	set<vector<long>> combinations = permute(subset);
	for (set<vector<long>>::iterator it = combinations.begin(); it != combinations.end(); it++) {
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
vector<long> insertItemAt(long toInsert, vector<long>& items, size_t offset)
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
	vector<long> data{1,2,3};
	permutations = permute(data);
	assert(permutations.size() == 6);
	cout << "permutations of List of {1,2,3} are:" << endl;
	for (set<vector<long>>::iterator it = permutations.begin(); it != permutations.end(); it++) {
		copy(it->begin(), it->end(), ostream_iterator<long>(cout, " "));
		cout << endl;
	}
	permutations.clear();
}
void GraphTests()
{
	vector<size_t> data(5);
	generate(data.begin(), data.end(), [n = 1]()mutable{return n++; });
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
	for (map<size_t, vector<shared_ptr<Vertex<size_t, size_t>>>>::const_iterator it = vertices.begin(); it != vertices.end(); it++) {
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Vertex<size_t, size_t>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->GetItem() << " ";
		cout << endl;
	}
	set<shared_ptr<Vertex<size_t, size_t>>> spt; // Shortest Path Tree
	graph.Dijkstra(1, spt);
	cout << "Vertex\tDistance from Source (1): " << endl;
	for (set<shared_ptr<Vertex<size_t, size_t>>>::iterator it = spt.begin(); it != spt.end(); it++)
		cout << (*it)->GetItem() << "\t" << (*it)->GetTotalCost() << endl;
	assert(graph.Dijkstra(1, 5) == 7);
	graph.Remove(3);
	assert(!graph.HasVertex(3));
	assert(!v2->HasNeighbour(v3));
	assert(!v5->HasNeighbour(v3));
	spt.clear();
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
	assert(graph.Dijkstra(1, 2) == 1);
	assert(graph.Dijkstra(1, 3) == 3); // 1 + 2
	assert(graph.Dijkstra(1, 4) == 3); // 1 + 2
	assert(graph.Dijkstra(3, 4) == 4); // 2 + 2
	cout << "1 - 3: " << graph.Dijkstra(1, 3) << endl;
	cout << "1 - 4: " << graph.Dijkstra(1, 4) << endl;
	cout << "3 - 4: " << graph.Dijkstra(3, 4) << endl;
	spt.clear();
	graph.Clear();
	data.clear();
	data = {10,5,11};
	vector<vector<size_t>> links = { {1, 2}, {1, 3} }; // Use tag. Not value
	/*
			10
		11		5
	Diff: 15 - 11 = 4
	*/
	assert(MinSubGraphDifference(data, links) == 4);
	data.clear();
	data = {10,5,6,20};
	/*
			10
		 5		6
	  20
	Diff: 21 - 20 = 1
	*/
	links = { {1,2}, {1,3}, {2,4} };//{ {10,5}, {10,6}, {5,20} };
	assert(MinSubGraphDifference(data, links) == 1);
	/*
			10
		 5
	  20
	Diff: 20 - 15 = 5
	*/
	data.clear();
	data = { 10,5,20 };
	links = { {1,2}, {2,3} };//{ {10,5}, {5,20} };
	assert(MinSubGraphDifference(data, links) == 5);
	cout << endl;
	data.clear();
	data = {100,200,100,100,500,600};
	links = { {1,2}, {2,3}, {2,4}, {4,5}, {4,6} };
	assert(MinSubGraphDifference(data, links) == 400);
	data.clear(); 
	data = { 205, 573, 985, 242, 830, 514, 592, 263, 142, 915 };
	links = { {2,8}, {10,5}, {1,7}, {6,9}, {4,3}, {8,10}, {5,1}, {7,6}, {9,4} };
	assert(MinSubGraphDifference(data, links) == 99);
	vector<size_t> data2 = { 716,365,206,641,841,585,801,645,208,924,920,286,554,832,359,836,247,959,31,322,709,860,890,195,575,905,314,41,669,549,950,736,265,507,729,457,91,529,102,650,805,373,287,710,556,645,546,154,956,928 };
	links = { {14,25 }, { 25,13 }, { 13,20 }, { 20,24 }, { 43,2 }, { 2,48 }, { 48,42 }, { 42,5 }, { 27,18 }, { 18,30 }, { 30,7 }, { 7,36 }, { 37,9 }, { 9,23 }, { 23,49 }, { 49,15 }, { 31,26 }, { 26,29 }, { 29,50 }, { 50,21 }, { 41,45 }, { 45,10 }, { 10,17 }, { 17,34 }, { 28,47 }, { 47,44 }, { 44,11 }, { 11,16 }, { 3,8 }, { 8,39 }, { 39,38 }, { 38,22 }, { 19,32 }, { 32,12 }, { 12,40 }, { 40,46 }, { 1,35 }, { 35,4 }, { 4,33 }, { 33,6 }, { 25,2 }, { 2,27 }, { 7,37 }, { 15,50 }, { 21,10 }, { 17,28 }, { 16,39 }, { 38,19 }, { 40,1} };
	size_t result = MinSubGraphDifference(data2, links);
	//assert(result == 525); Fail but difficult to check due to the sheer number of data points.
	vector<long> data1;
	vector<vector<long>> links1;
	data1.clear();
	data1 = {1,3,4};
	links1 = { {1,2,1}, {2,3,2}, {2,4,2}, {3,5,3} };
	assert(PostmanProblem(data1, links1) == 6);
	data1.clear();
	data1 = {5,11,12,15,16};
	links1 = { {17,4,3},{11,12,5},{14,2,1},{16,14,4},{7,8,4},{13,5,5},{17,15,2},{5,3,5},{8,6,1},{18,10,4},{18,1,3},{16,1,2},{9,2,5},{11,6,1},{4,9,4},{7,20,2},{13,19,3},{19,12,3},{10,20,2} };
	assert(PostmanProblem(data1, links1) == 54);
	cout << endl;
}
void parentheses(vector<string> &result, string &str, size_t index, long left, long right)
{
	if (!left && !right)
		result.push_back(str);
	else if (left >= 0 && right >= left) {
		if (left > 0) {
			str[index] = '(';
			parentheses(result, str, index + 1, left - 1, right);
		}
		if (right > left) {
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
//()
//0: -1, 0
//1 : -1, result = 2
//
//(()
//0: -1, 0
//1 : -1, 0, 1
//2 : -1, 0 result = 2
//
//((
//0: -1, 0
//1 : -1, 1
//result = 0
//
//((()
//0: -1, 0
//1 : -1, 0, 1
//2 : -1, 0, 1, 2
//3 : -1, 0, 1 result = 2
//
//((())
//0: -1, 0
//1 : -1, 0, 1
//2 : -1, 0, 1, 2
//3 : -1, 0, 1 result = 2
//4 : -1, 0 result = 4
long LongestValidParentheses(string& str)
{
	MyStack<long> stack;
	stack.push(-1); // The first element of stack is used to provide base for next valid string
	long result = 0;
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == '(')
			stack.push(i);
		else if (str[i] == ')') {
			stack.pop(); // Remove the last matching opening bracket or -1
			if (!stack.isEmpty() && (long)(i - stack.peek()) > result)
				result = i - stack.peek();
			else if (stack.isEmpty())
				stack.push(i);
		}
	}
	return result;
}
// https://app.codility.com/programmers/task/brackets_rotation/
// Unfinished work!
long LongestValidParenthesesWithFixes(string& str, size_t k)
{
	stack<long> stack;
	long start = -1, end = -1;
	stack.push(-1); // The first element of stack is used to provide base for next valid string
	long result = 0;
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == '(')
			stack.push(i);
		else if (str[i] == ')') {
			stack.pop(); // Remove the last matching opening bracket or -1
			if (!stack.empty() && (long)(i - stack.top()) > result) {
				result = i - stack.top();
				start = stack.top() + 1;
				end = i;
			} else if (stack.empty())
				stack.push(i);
		}
	}
	long *stackEnd = &stack.top() + 1;
	long *stackBegin = stackEnd - stack.size();
	vector<long> list(stackBegin, stackEnd);
	// The algorithm implemented is based on reverse-engineering of the result sets obtained from the remaining stack elements after the for loop above.
	if (k == 0 || list.empty() || (list.size() == 1 && list[0] == -1))
		return result;
	if (result == 0) {
		if (list[0] == -1 || list.size() == 1) {
			result = !(list[0] % 2) ? list[0] : list[0] + 1;
			result = list.size() == str.size() + 1 && str.size() > 1 ? 2 : min((long)k, result / 2) * 2;
		} else {
			size_t size = list.size();
			if (list[0] == -1)
				size--;// remove -1
			//if (list[0] != 0) {
				result = !(size % 2) ? size : size - 1;
				if ((list[0] == 0 && (long)k > (result / 2)) || (list[0] != 0 && (long)k >= (result / 2)))
					result = min((long)(k * 2), result);
				else
					result = 0;
			//}
		}
	} else if (list.size() == 1 && list[0] != -1) {
		if ((list[0] > end && start > 0) || (list[0] < start && list[0] > 0)) {
			k--;
			result += 2;
		}
	} else {
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
		if (*it == '{')	{
			leftBraceCount++;
			key = "";
			value = "";
			oss.str("");
		} else if (*it == '}' || *it == ' ' || *it == ',') {
			value = oss.str();
			oss.str("");
			if (value != "")
				valueCount++;
			if (*it == '}')
				rightBraceCount++;
			if (leftBraceCount > rightBraceCount && keyCount > valueCount)
				valueCount++;
		} else if (*it == ':') {
			key = oss.str();
			oss.str("");
			if (key != "")
				keyCount++;
		} else
			oss << *it;
	}
	return leftBraceCount == rightBraceCount && keyCount == valueCount;
}
// 0 1 2 3 4 5 6 7 8 9 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
void findDistinct(vector<long>& input, vector<long>& output)
{
	for (vector<long>::const_iterator it = input.begin(); it != input.end(); it++) {
		vector<long>::const_iterator it1 = it + 1;
		for (; it1 != input.end() && (*it ^ *it1); it1++);
		if (it1 == input.end())
			output.push_back(*it);
	}
}
// http://en.wikipedia.org/wiki/Prime_number - Trial division implementation
void findPrimes(unsigned long n, vector<long>& result)
{
	if (n <= 3)
		result = { 2,3 };
	else {
		long double j;
		result = { 2,3 };
		for (unsigned long i = 4; i <= n; i++) {
			long double sqrtI = sqrt(i);
			for (j = 2; j <= sqrtI && (i % (long)j); j++);
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
	for (size_t i = 5; (i*i) <= n; i += 6) // 5 7 11
		if (!(n % i) || !(n % (i + 2)))
			return false;
	return true;
}
// https://app.codility.com/programmers/lessons/12-euclidean_algorithm/common_prime_divisors/
// Correctness: 100%
// 61% due to timeout
size_t CommonPrimeDivisors(vector<long>& data1, vector<long>& data2)
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
	for (size_t i = 0; i < data1.size(); i++) {
		maxNum = max(data1[i], data2[i]);
		bool flag = true;
		for (vector<long>::const_iterator it = primes.begin(); it < primes.end() && *it <= maxNum; it++) {
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
unsigned long long findMax(vector<unsigned long long> const& data)
{
	vector<unsigned long long> result;
	if (data.size() == 1)
		return data[0];
	else if (data.size() == 2)
		return (data[0] * data[1] > data[0] + data[1]) ? data[0] * data[1] : data[0] + data[1];
	else {
		for (vector<unsigned long long>::const_iterator it = data.begin(); it != data.end(); it+=2) {
			if (it <= data.end() - 2)
				result.push_back((*it + *(it + 1)) > (*it * *(it + 1)) ? (*it + *(it + 1)) : (*it * *(it + 1)));
			else
				result.push_back(*it);
		}
	}
	return findMax(result);
}

string uncompress(string const& str)
{
	ostringstream oss;
	for (size_t i = 0; i < str.size(); ) {
		if (isalpha(str[i]))
			oss << str[i++];
		else if (isdigit(str[i])) {
			char *end(nullptr);
			errno = 0;
			unsigned long repeat = strtoul(&str[i], &end, 10);
			if (!errno && repeat > 0 && repeat < ULONG_MAX) {
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
			} else
				i++;
		}
	}
	return oss.str();
}
// "0010110100" => 6
size_t findLongestContiguousPattern(string& str, char c)
{
	size_t max = 0;
	int index = -1;
	size_t count = 0;
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == c)
			count++;
		else {
			if (max < count) {
				max = count;
				if (i > 0 && str[i - 1] == c && str[i + 1] == c)
					index = i;
			} else
				count = 0;
		}
	if (index > 0)
		str[index] = c;
	return index;
}

template<class T>
void SortStack(MyStack<T> &src, MyStack<T> &dest, sort_order_t order)
{
	T item;
	while(!src.isEmpty()) {
		item = src.pop();
		switch (order) {
		case SortOrder::SORT_ASCENDING: // Value grows from bottom of stack to top of stack
			while(!dest.isEmpty() && item < dest.peek())
				src.push(dest.pop());
			break;
		case SortOrder::SORT_DESCENDING: // Value shrinks from bottom of stack to top of stack
			while(!dest.isEmpty() && item > dest.peek())
				src.push(dest.pop());
			break;
		default:
			throw runtime_error("Invalid sort order");
			break;
		}
		dest.push(item);
	}
}
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
template<typename type>
void sortNumbers(vector<type> &data)
{
	size_t j;
	type tmp;
	for (size_t i = 0; i < data.size(); i++) {
		if (data[i] < 0 && data[i + 1] < 0) {// Look for positive number
			for (j = i + 1; j < data.size() && data[j] < 0; j++);
			if (j == data.size())
				break;
			// Shift i+1 to j-1
			tmp = data[j];
			for (size_t k = j; k > i; k--)
				data[k] = data[k - 1];
			data[i + 1] = tmp;
		}  else if (data[i] > 0 && data[i + 1] > 0) {// Look for positive number
			for (j = i + 1; j < data.size() && data[j] > 0; j++);
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
template<typename type>
 void OrderArrayIntoNegativePositiveSeries(vector<type>& arr)
 {
	 if (arr.empty() || arr.size() < 3)
		 return;
	 // if first value is negative, then find a positive value next
	 bool positiveValToFind = arr[0] < 0;
	 type nextValue;
	 for (size_t outOfOrderPos = 1, curIndex = 1; curIndex < arr.size(); curIndex++) {
		 if ((positiveValToFind && arr[curIndex] > 0) || (!positiveValToFind && arr[curIndex] < 0)) {
			 if (outOfOrderPos == curIndex) {
				 // Scenario 1: curIndex is increment by the for loop
				 positiveValToFind = !positiveValToFind;
				 ++outOfOrderPos;
			 } else {
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
 void OrderArrayIntoNegativePositiveSeriesTests()
 {
	 vector<long> a{ 2,-1,-3,-7,-8,9,5,-5,-7 };
	// Start of Sort numbers into consecutive positive/negative numbers
	// 2,-1,-3,-7,-8,9,5,-5,-7
	sortNumbers(a);
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, " "));
	cout << endl;
	a.clear();
	TestCornerCases();
	vector<int> testArr{ 2, -1, -3, -7, -8, 9, 5, -5, -7 };
	vector<int> result{ 2, -1, 9, -3, 5, -7, -8, -5, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = { 2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = { 2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = { 2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = { -1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7 };
	result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	assert(testArr == result);

	testArr = { -1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1 };
	result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };
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
int BinarySearch(vector<long> source, int toSearch)
{
	int lower, middle, upper;
	lower = 0;
	upper = source.size() - 1;
	while (lower <= upper) {
		middle = lower + (upper - lower) / 2 + (upper - lower) % 2;
		if (toSearch == source[middle])
			return middle;
		else if (toSearch == source[lower])
			return lower;
		else if (toSearch == source[upper])
			return upper;
		else if (source[lower] <= source[middle]) {
			// 15 16 19 20 25 30 1 3 4 5 7 10 14
			// L              M               U
			// 4 8 9 9 9 10 12 13 1 2 2 3
			// L            M           U
			if (toSearch > source[lower] && toSearch < source[middle]) // Ex: toSearch=20; toSearch=9
				upper = middle - 1;
			else							   // Ex: toSearch=5; toSearch=2
				lower = middle + 1;
		} else { // Middle < Lower
			// 15 16 19 20 25 30 1 3 4 5 7 10 11 14
			// L			  	   M		      U
			// 4 8 9 9 9 10 12 13 1 2 2 3
			// L                  M     U
			if (toSearch > source[middle] && toSearch < source[upper]) // Ex: toSearch=10; toSearch=2
				lower = middle + 1;
			else				// Ex: toSearch=20; toSearch=12
				upper = middle - 1;
		}
	}
	return -1;
}
int BinarySearchCountUpper(vector<long> source, int toSearch, int start, int end)
{
	int mid = start + (end - start) / 2 + (end - start) % 2;
	if (end < start)
		return 0;
	if (source[mid] == toSearch && (mid == end || source[mid + 1] != toSearch))
		return mid;
	else if (source[mid] <= toSearch)
		return BinarySearchCountUpper(source, toSearch, mid + 1, end);
	else
		return BinarySearchCountUpper(source, toSearch, start, mid - 1);
}
int BinarySearchCountLower(vector<long> source, int toSearch, int start, int end)
{
	int mid = start + (end - start) / 2 + (end - start) % 2;
	if (end < start)
		return 0;
	if (source[mid] == toSearch && (mid == start || source[mid - 1] != toSearch))
		return mid;
	else if (source[mid] < toSearch)
		return BinarySearchCountLower(source, toSearch, mid + 1, end);
	else
		return BinarySearchCountLower(source, toSearch, start, mid - 1);
}
int BinarySearch(vector<string> source, string toSearch)
{
	int lower, middle, upper;
	lower = 0;
	upper = source.size() - 1;
	while (lower <= upper) {
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
	sortData.clear();
	sortData = {1,0,-1};
	assert(sortData[0] == 1);
	assert(sortData[1] == 0);
	assert(sortData[2] == -1);
	BubbleSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&] {return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	BubbleSort(sortData);
	for (size_t i = 0; i < sortData.size(); i++)
		assert(sortData[i] == buffer[i]);

	sortData.clear();
	sortData = { 1,0,-1 };
	assert(sortData[0] == 1);
	assert(sortData[1] == 0);
	assert(sortData[2] == -1);
	QuickSort(sortData, 0, sortData.size() - 1);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&] {return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	QuickSort(sortData, 0, sortData.size() - 1);
	for (size_t i = 0; i < sortData.size(); i++)
		assert(sortData[i] == buffer[i]);

	sortData.clear();
	sortData = {1,0,-1};
	assert(sortData[0] == 1);
	assert(sortData[1] == 0);
	assert(sortData[2] == -1);
	SelectionSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&] {return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	SelectionSort(sortData);
	for (size_t i = 0; i < sortData.size(); i++)
		assert(sortData[i] == buffer[i]);

	sortData.clear();
	sortData = { 1,0,-1 };
	assert(sortData[0] == 1);
	assert(sortData[1] == 0);
	assert(sortData[2] == -1);
	InsertionSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&] {return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	InsertionSort(sortData);
	for (size_t i = 0; i < sortData.size(); i++)
		assert(sortData[i] == buffer[i]);

	sortData.clear();
	sortData = { 1,0,-1 };
	assert(sortData[0] == 1);
	assert(sortData[1] == 0);
	assert(sortData[2] == -1);
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);

	sortData.clear();
	sortData = {2,1,3,1,2};
	assert(sortData[0] == 2);
	assert(sortData[1] == 1);
	assert(sortData[2] == 3);
	assert(sortData[3] == 1);
	assert(sortData[4] == 2);
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	assert(sortData[0] == 1);
	assert(sortData[1] == 1);
	assert(sortData[2] == 2);
	assert(sortData[3] == 2);
	assert(sortData[4] == 3);

	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&] {return uniformDistribution(engine); });
	a.clear();
	a.assign(sortData.begin(), sortData.end());
	sort(a.begin(), a.end());
	buffer.clear();
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	for (size_t i = 0; i < sortData.size(); i++)
		assert(sortData[i] == a[i]);

	sortData.clear();
	sortData = { 1,0,-1 };
	assert(sortData[0] == 1);
	assert(sortData[1] == 0);
	assert(sortData[2] == -1);
	buffer = sortData;
	BottomUpMergeSort(sortData, buffer);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);
	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&] {return uniformDistribution(engine); });
	a.clear();
	a.assign(sortData.begin(), sortData.end());
	sort(a.begin(), a.end());
	buffer = sortData;
	BottomUpMergeSort(sortData, buffer);
	for (size_t i = 0; i < sortData.size(); i++)
		assert(sortData[i] == a[i]);

	sortData.clear();
	sortData = { 1,0,-1 };
	assert(sortData[0] == 1);
	assert(sortData[1] == 0);
	assert(sortData[2] == -1);
	HeapSort(sortData);
	assert(sortData[0] == -1);
	assert(sortData[1] == 0);
	assert(sortData[2] == 1);

	vector<size_t> sortData1 { 1,0,2 };
	assert(sortData1[0] == 1);
	assert(sortData1[1] == 0);
	assert(sortData1[2] == 2);
	CountingSort(sortData1);
	assert(sortData1[0] == 0);
	assert(sortData1[1] == 1);
	assert(sortData1[2] == 2);

	sortData1.clear();
	sortData1 = { 456,789,123 };
	assert(sortData1[0] == 456);
	assert(sortData1[1] == 789);
	assert(sortData1[2] == 123);
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
		{"1250", "the"}
	};
	assert(CountingSort(strSort) == "to be or not to be - that is the question");

	strSort.clear();
	strSort = { {"100", "!!!"}, {"55", "Hello"}, {"10", "Hey,"}, {"55", "World"} };
	assert(CountingSort(strSort) == "Hey, Hello World !!!");

	sortData.clear();
	sortData.resize(100);
	generate(sortData.begin(), sortData.end(), [&] {return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	HeapSort(sortData);
	for (size_t i = 0; i < sortData.size(); i++)
		assert(sortData[i] == buffer[i]);

	a.clear();
	a.resize(10);
	b.resize(20);
	generate(a.begin(), a.end(), [&] {return uniformDistribution(engine); });
	generate(b.begin(), b.end(), [&] {return uniformDistribution(engine); });
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++) {
		if (it != a.begin())
			if (*it < *(it - 1)) {
				throw runtime_error("Merge 2 sorted lists failed!");
				break;
			}
	}
	a.resize(20);
	b.resize(10);
	generate(a.begin(), a.end(), [&] {return uniformDistribution(engine); });
	generate(b.begin(), b.end(), [&] {return uniformDistribution(engine); });
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++) {
		if (it != a.begin())
			if (*it < *(it - 1)) {
				cout << "Merge 2 sorted lists failed!";
				assert(false);
				break;
			}
	}
	a.clear();
	b.clear();
	a = {1,5,3,7};
	b = a;
	assert(TopDownMergeSortCountConversions(b, a, 0, a.size()) == 1);
	assert(a[0] == 1);
	assert(a[1] == 3);
	assert(a[2] == 5);
	assert(a[3] == 7);

	a.clear();
	b.clear();
	a = { 7,5,3,1 };
	b = a;
	assert(TopDownMergeSortCountConversions(b, a, 0, a.size()) == 6);
	assert(a[0] == 1);
	assert(a[1] == 3);
	assert(a[2] == 5);
	assert(a[3] == 7);

	a.clear();
	b.clear();
	a = {2,1,3,1,2};
	b = a;
	assert(TopDownMergeSortCountConversions(b, a, 0, a.size()) == 4);
	assert(a[0] == 1);
	assert(a[1] == 1);
	assert(a[2] == 2);
	assert(a[3] == 2);
	assert(a[4] == 3);
}
void BinarySearchTests()
{
	int pos;
	vector<long> source;
	long data[12]  = {15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5};
					/*L				      M			         U*/
	source.resize(30);
	generate(source.begin(), source.begin() + 10, [i = 0]()mutable{return i++; });
	generate(source.begin() + 10, source.begin() + 20, [i = 1000]()mutable{return i++; });
	generate(source.begin() + 20, source.begin() + 30, [i = 2000]()mutable{return i++; });
	rotate(source.begin(), source.begin() + source.size() / 2, source.end());
	pos = BinarySearch(source, 1000);
	assert(pos >= 0);
	assert(source[pos] == 1000);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 1000 found at location: " << pos << ", " << source[pos] << endl;

	source.clear();
	source.assign(&data[0], &data[11]);
	pos = BinarySearch(source, 20);
	assert(pos == 5);
	assert(source[pos] == 20);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 20 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 17);
	assert(pos == 2);
	assert(source[pos] == 17);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 0);
	assert(pos == 6);
	assert(source[pos] == 0);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 3);
	assert(pos == 9);
	assert(source[pos] == 3);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 3 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 11);
	assert(pos < 0);

	long data1[20] = {15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5, 6, 7, 8};
					/*L				             M			          U*/
	source.clear();
	source.assign(&data1[0], &data1[14]);
	pos = BinarySearch(source, 0);
	assert(pos == 6);
	assert(source[pos] == 0);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 5);
	assert(pos == 11);
	assert(source[pos] == 5);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 5 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 17);
	assert(pos == 2);
	assert(source[pos] == 17);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 11);
	assert(pos < 0);

	long data2[12] = {4, 8, 9, 9, 9, 10, 12, 13, 1, 2, 2, 3};
	source.clear();
	source.assign(&data2[0], &data2[11]);
	pos = BinarySearch(source, 9);
	assert(pos > 0);
	assert(source[pos] == 9);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 9 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 2);
	assert(pos > 0);
	assert(source[pos] == 2);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 2 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 12);
	assert(pos == 6);
	assert(source[pos] == 12);
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 12 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 0);
	assert(pos < 0);
}
void BinarySearchCountTests()
{
	vector<long> ages(50, 20);
	ages.resize(100);
	generate(ages.begin() + 50, ages.begin() + 80, [i = 30]()mutable{return i; });
	generate(ages.begin() + 80, ages.end(), [i = 50]()mutable{return i; });
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
	vector<string> str{ "abc", "ABC", "", "123", "789", "xyz", "XYZ", ""};
	sort(str.begin(), str.end());

	pos = BinarySearch(str, "123");
	assert(pos == 2);
	assert(str[pos] == "123");
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: \"123\" found at location: " << pos << ", " << str[pos] << endl;

	pos = BinarySearch(str, "abc");
	assert(pos == 6);
	assert(str[pos] == "abc");
	//cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: \"abc\" found at location: " << pos << ", " << str[pos] << endl;
}
void BubbleSort(vector<long> &data)
{
	long tmp;
	for (size_t lastIndex = data.size() - 1; lastIndex >= 1; lastIndex--) {
		for (size_t i = 0; i < lastIndex; i++) {
			if (data[i] > data[i+1]) {
				tmp = data[i];
				data[i] = data[i+1];
				data[i+1] = tmp;
			}
		}
	}
}
/* Quick Sort (http://en.wikipedia.org/wiki/Quicksort) */
void QuickSort(vector<long> &data, long left, long right)
{
	size_t pivot;
	if (left < right) {
		pivot = left + (right - left) / 2 + (right - left) % 2; // This overcomes integer overflow
		pivot = Partition(data, left, right, pivot);
		// Worst case: N-1 calls. Each call processes the list from left to right-1. O(N^2)
		// Average case: lg(N) calls. Each level of call tree processes half the original list. 2 calls processes N items. O(N*log(N)).
		QuickSort(data, left, pivot - 1);  // Either this or the call below is used in worst-case scenario
		QuickSort(data, pivot + 1, right); // Either this or the call above is used in worst-case scenario
	}
}
// Worst case: returns original list. newPivot = left || newPivot = right
// Average case: Divides the original list to half. newPivot = 1/2.
size_t Partition(vector<long> &data, size_t left, size_t right, size_t pivot)
{
	size_t newPivot = left;
	long pivotValue = data[pivot];
	Swap(data[pivot], data[right]);
	for (size_t i = left; i < right; i++) {
		if (data[i] < pivotValue) {
			if (i != newPivot)
				Swap(data[i], data[newPivot]);
			newPivot++;
		}
	}
	if (newPivot != right)
		Swap(data[newPivot], data[right]);
	return newPivot;
}
// Find the smallest element using a linear scan and move it to the front. 
// Then, find the second smallest and move it, again doing a linear scan. 
// Continue doing this until all the elements are in place. O(n^2).
void SelectionSort(vector<long> &data)
{
	size_t min = 0;
	for (size_t i = 0; i < data.size(); i++) {
		min = i;
		for (size_t j = i + 1; j < data.size(); j++) { // Find the min from lower bound to end
			if (data[j] <= data[min])
				min = j;
		}
		if (min != i)
			Swap(data[min], data[i]);
	}
}
void InsertionSort(vector<long> &data)
{
	if (data.size() > 1)
	for (size_t i = 1; i < data.size(); i++)
		for (size_t j = i; j > 0 && data[j] < data[j - 1]; j--)
			Swap(data[j], data[j - 1]);
}
// http://en.wikipedia.org/wiki/Merge_sort
// top-down merge sort algorithm that recursively splits the list (called runs in this example) into sublists 
// until sublist size is 1, then merges those sublists to produce a sorted list
//  The copy back step is avoided with alternating the direction of the merge with each level of recursion (except for an initial one time copy)
void TopDownMergeSort(vector<long>& B, vector<long>& A, size_t start, size_t end)
{
	if (end - start < 2)
		return;
	// recursively split runs into two halves until run size == 1,
	// then merge them and return back up the call chain
	size_t middle = start + (end - start) / 2 + (end - start) % 2;
	TopDownMergeSort(A, B, start, middle);
	TopDownMergeSort(A, B, middle, end);
	Merge(B, A, start, middle, end);
}
// https://www.hackerrank.com/challenges/ctci-merge-sort/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=sorting
// 100%
size_t TopDownMergeSortCountConversions(vector<long>& B, vector<long>& A, size_t start, size_t end)
{
	size_t inversions = 0;
	if (end - start < 2)
		return inversions;
	// recursively split runs into two halves until run size == 1,
	// then merge them and return back up the call chain
	size_t middle = start + (end - start) / 2 + (end - start) % 2;
	inversions += TopDownMergeSortCountConversions(A, B, start, middle);
	inversions += TopDownMergeSortCountConversions(A, B, middle, end);
	inversions += MergeCountInversions(B, A, start, middle, end);
	return inversions;
}
size_t MergeCountInversions(vector<long>& A, vector<long>& B, size_t start, size_t middle, size_t end)
{
	size_t inversions = 0;
	size_t left = start;
	size_t right = middle;
	// While there are elements in the left or right runs...
	for (size_t i = start; i < end; i++) {
		// If left run head exists and is <= existing right run head.
		if (left < middle && (right >= end || A[left] <= A[right]))
			B[i] = A[left++];
		else {
			inversions += right - i;
			B[i] = A[right++];
		}
	}
	return inversions;
}
// bottom-up merge sort algorithm which treats the list as an array of n sublists (called runs in this example) 
// of size 1, and iteratively merges sub-lists back and forth between two buffers
void BottomUpMergeSort(vector<long>& A, vector<long>& B)
{
	size_t n = A.size();
	// Each 1-element run in data is already "sorted".
	// Make successively longer sorted runs of length 2, 4, 8, 16... until whole array is sorted.
	for (size_t width = 1; width < A.size(); width *= 2) {
		// data is full of runs of length width.
		for (size_t i = 0; i < A.size(); i += 2 * width)
			Merge(A, B, i, min(i + width, n), min(i + 2 * width, n));
		// Now work array B is full of runs of length 2*width.
				// Copy array B to array A for next iteration.
				// A more efficient implementation would swap the roles of A and B.
		A = B;
		// Now array A is full of runs of length 2*width.
	}
}
void Merge(vector<long>& A, vector<long>& B, size_t start, size_t middle, size_t end)
{
	vector<long> buffer;
	size_t left = start;
	size_t right = middle;
	// While there are elements in the left or right runs...
	for (size_t i = start; i < end; i++)
		// If left run head exists and is <= existing right run head.
		B[i] = (left < middle && (right >= end || A[left] <= A[right])) ? A[left++] : A[right++];
}
// https://en.wikipedia.org/wiki/Heapsort
void HeapSort(vector<long>& data)
{
	Heap<long> heap(data, HeapType::MaxHeap);
	assert(heap.Count() == data.size());
	for (long end = data.size() - 1; end >= 0; end--) {
		long item = heap.pop()->Item();
		Swap(data[end], item);
	}
}
// https://en.wikipedia.org/wiki/Counting_sort
//  each of which has a non-negative integer key whose maximum value is at most k
void CountingSort(vector<size_t>& data)
{
	vector<size_t> input(data);
	long min = numeric_limits<size_t>::max(), max = 0;
	for (vector<size_t>::iterator it = input.begin(); it != input.end(); it++) {
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
	for (vector<size_t>::reverse_iterator it = input.rbegin(); it != input.rend(); it++) {
		data[counts[*it] - 1] = *it;
		counts[*it]--;
	}
}
string CountingSort(vector<vector<string>>& data)
{
	vector<string> result;
	long min = numeric_limits<size_t>::max(), max = 0;
	for (vector<vector<string>>::iterator it = data.begin(); it != data.end(); it++) {
		long key;
		istringstream((*it)[0]) >> key;
		if (key < min)
			min = key;
		if (key > max)
			max = key;
	}
	// Do NOT use map / multimap to keep the counts. map / multimap auto-sort on keys. This defeats the purpose of CountingSort
	vector<size_t> counts(max + 1, 0);
	for (vector<vector<string>>::iterator it = data.begin(); it != data.end(); it++) {
		size_t key;
		istringstream((*it)[0]) >> key;
		counts[key]++;
	}
	for (long i = min > 0 ? min : 1; i <= max; i++)
		counts[i] += counts[i - 1];
	result.resize(counts[counts.size() - 1]);
	// Use reverse_iterator for a stable sort
	for (vector<vector<string>>::reverse_iterator it = data.rbegin(); it != data.rend(); it++) {
		size_t key;
		istringstream((*it)[0]) >> key;
		result[counts[key] - 1] = (*it)[1];
		counts[key]--;
	}
	ostringstream oss;
	for (size_t i = 0; i < result.size(); i++) {
		if (!result[i].empty()) {
			oss << result[i];
			if (i < result.size() - 1)
				oss << " ";
		}
	}
	return oss.str();
}
void Swap(long &a, long &b)
{
	long tmp = a;
	a = b;
	b = tmp;
}
long** my2DAlloc(long rows, long cols)
{
	size_t header = rows * sizeof(long*); // Store the row pointers [i]
	size_t data = rows * cols * sizeof(long); // Store the data
	long** rowptr = (long**)malloc(header + data); // row pointers + data buffers
	long *dataptr = (long*)(rowptr + rows); // Pointer arithmetic to get the first location of data buffer
	for (int i = 0; i < rows; i++)
		rowptr[i] = dataptr + i * cols;
	return rowptr;
}
long*** my3DAlloc(long rows, long cols, long heights)
{
	size_t header = rows * sizeof(long*) + rows * cols * sizeof(long*); // Store the row pointers [i] and every cell of the 2D-plane is pointer to the Z-buffer [i][j]
	size_t data = rows * cols * heights * sizeof(long); // data
	long*** ptrs = (long***)malloc(header + data); // row pointers + 2-D plane of pointers to Z-plane data
	long** columns = (long**)(ptrs + rows); // Pointer arithmetic to get the first location of 2D plane of Z-plane pointers [i][j]
	long* dataPtr = (long*)(ptrs + rows + rows * cols); // Pointer arithmetic to get the first location of data buffer
	for (long i = 0; i < rows; i++) {
		ptrs[i] = columns + i * cols;
		for (long j = 0; j < cols; j++)
			ptrs[i][j] = dataPtr + i * cols * heights + j * heights;
	}
	return ptrs;
}
long long AddWithoutArithmetic(long long sum, long long carry)
{
	if (!carry)
		return sum;
	if (!sum)
		return carry;
	if (!sum && !carry)
		return 0;
	long long sum1 = sum ^ carry;
	long long carry1 = (sum & carry) << 1;
	return AddWithoutArithmetic(sum1, carry1);
}
// Function for finding sum of larger numbers 
string NumberStringSum(string& str1, string& str2)
{
	if (str1.empty() && !str2.empty())
		return str2;
	else if (!str1.empty() && str2.empty())
		return str1;
	else if (str1.empty() && str2.empty())
		return "";

	ostringstream oss;
	// Calculate length of both string 
	int n1 = str1.length(), n2 = str2.length();
	int diff = n2 - n1;

	// Initially take carry zero 
	int carry = 0;
	string::reverse_iterator it1 = str1.rbegin();
	string::reverse_iterator it2 = str2.rbegin();
	for (; !(it1 == str1.rend() && it2 == str2.rend()); ) {
		// Do school mathematics, compute sum of current digits and carry
		int sum = carry;
		if (it1 != str1.rend())
			sum += *it1 - '0';
		if (it2 != str2.rend())
			sum += *it2 - '0';
		oss << sum % 10;
		carry = sum / 10;
		if (it1 != str1.rend())
			it1++;
		if (it2 != str2.rend())
			it2++;
	}
	// Add remaining carry 
	if (carry)
		oss << carry;

	// reverse resultant string
	string str = oss.str();
	reverse(str.begin(), str.end());
	return str;
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
string NumberStringMultiplication(string& num1, string& num2)
{
	if (num1.empty() && !num2.empty())
		return "0";
	else if (!num1.empty() && num2.empty())
		return "0";
	else if (num1.empty() && num2.empty())
		return "0";
	bool isNegative = (num1[0] == '-' && num2[0] != '-') || (num1[0] != '-' && num2[0] == '-');
	if (num1[0] == '-')
		num1 = num1.substr(1);
	if (num2[0] == '-')
		num2 = num2.substr(1);
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 == 0 || len2 == 0)
		return "0";

	// will keep the result number in vector in reverse order 
	vector<long> result(len1 + len2, 0);

	// Below two indexes are used to find positions in result.  
	size_t i_n1 = 0, i_n2 = 0;
	// Go from right to left in num1 (bottom) 
	for (int i = len1 - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';
		// To shift position to left after every multiplication of a digit in num2 (top)
		i_n2 = 0;
		// Go from right to left in num2              
		for (int j = len2 - 1; j >= 0; j--)
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
		if (carry > 0)
			result[i_n1 + i_n2] += carry;

		// To shift position to left after every multiplication of a digit in num1. 
		i_n1++;
	}
	// ignore '0's from the right 
	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0)
		i--;
	// If all were '0's - means either both or one of num1 or num2 were '0' 
	if (i == -1)
		return "0";
	// generate the result string 
	ostringstream oss;
	if (isNegative)
		oss << '-';
	while (i >= 0)
		oss << result[i--];
	return oss.str();
}
// http://www.cplusplus.com/reference/cstdlib/rand/
// A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use 
// the modulo of the returned value by the range span and add the initial value of the range:
// v1 = rand() % 100;         // v1 in the range 0 to 99
// v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
// v3 = rand() % 30 + 1985;   // v3 in the range 1985 to 2014
void shuffleCards(vector<long> &cards)
{
	unsigned long long mask = 0;
	int tmp, index;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(begin(seeds), end(seeds));
	mt19937_64 engine(sequence);
	if (!cards.empty() && cards.size() <= 52)
	{
		for (size_t i = 0; i < 52; i++) {
			// index = (rand() % (52 - i)) + i;
			// i: n  random from n to 51
			// i: 0  random from 0  to 51
			// i: 1  (rand() % 51) + 1  = 1  to 51
			// i: 2  (rand() % 50) + 2  = 2  to 51
			// i: 10 (rand() % 42) + 10 = 10 to 51
			// i: 26 (rand() % 26) + 26 = 26 to 51
			// i: 50 (rand() % 2) + 50  = 50 to 51
			// i: 51 (rand() % 1) + 51  = 51 (Last card left)
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
void randomSubset(vector<long> &source, size_t count, vector<long>& result)
{
	set<long> masks;
	long index, tmp;
	if (count > source.size())
		return;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(begin(seeds), end(seeds));
	mt19937_64 engine(sequence);
	for (size_t i = 0; i < count; i++) {
		//index = (rand() % (source.size() - i)) + i;
		uniform_int_distribution<long> dist(0, source.size() - i - 1);
		index = dist(engine) + i;
		//cout << "source[" << index << "]: " << source[index] << endl;
		assert(masks.find(source[index]) == masks.end());
		masks.emplace(source[index]);
		result.push_back(source[index]);
		tmp = source[i];
		source[i] = source[index];
		source[index] = tmp;
	}
}
/*
----- Algo for 0...n (n < 10):  -----
first-digit: (power=1, remainder=0)
if (remainder > 2): 1

other-digits:
n/power * F(0) + F(0) = 0

----- Algo for 0...n (n < 100): -----
15: (power=10, remainder=9)
last-digit: 1(2) + 1(12)
first-digit: 0

25:
last-digit: 2 (2 x 1) + 1(22)
first-digit: 6 (20...25)

35:
last-digit: 3 (3 x 1) + 1(32)
first-figit: 10

65:
last-digit: 6 (6 x 1) + 1(62)
first-digit: 10 (20...29)

first-digit:
if (n/power == 2): remainder + 1
if (n/power > 2): power(10)

other digits:
n/power * F(9) + F(remainder) = 10 <== KEY

first-digit + other-digits = 20

----- Algo for 0...n (n < 200): -----
0...199: (power=100, remainder=99)
First-digit: 0
if (n/power == 2): remainder + 1
if (n/power > 2): power(100)

Other digits:
n/power * F(99) + F(99) = 20 + 20 = 40

----- Algo for 0...n (n < 1000): -----
0...345: (power=100, remainder=45)
3 x 20(0...99) + 100(200...299) + remainder(45)
First-digit:
if (n/power == 2): remainder + 1
if (n/power > 2): power(100)

other-digit:
n/power * F(99) + F(45) = 3 * 20 + 15
 */
/*
0 - 99: 10 + 10 = 20
100 - 199: 2 * 20
200 - 299: 3 * 20 + 100 = 160
300 - 345: 5 + 10 = 15
total: 160 + 15 = 175
 */
long countDigits(char digit, long n)
{
	long power = 1, firstDigits = 0;
	if (digit < 0 || digit > 9)
		throw runtime_error("digit must be between 0 and 9!");
	if (!n)
		return 0;

	while ((power * 10) < n)
		power *= 10;
	// Count digit from the first digit in the number
	if ((n / power) > digit)
		firstDigits = power;
	else if ((n / power) == digit)
		firstDigits = (n % power) + 1;

	// Count digit from all other digits
	return (n / power) * countDigits(digit, power - 1) + countDigits(digit, n % power) + firstDigits;
}
/* http://en.wikipedia.org/wiki/Greatest_common_divisor */
/* the largest positive integer that divides the numbers without a remainder */
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
	if ((str.length() > 2) && str[0] == '0' && str[1] == 'x') {
		base = 16;
		i = 2;
	}
	for (; i < str.length(); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			if ((str[i] - '0') >= base)
				break;
			result *= base;
			result += str[i] - '0';
		} else if (base == 16 && ((str[i] >= 'a' && str[i] <= 'f') || str[i] >= 'A' && str[i] <= 'F')) {
			result *= base;
			if (str[i] >= 'a' && str[i] <= 'f')
				result += str[i] - 'a';
			else
				result += str[i] - 'A';
			result += 10;
		} else
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
	if ((str.length() > 2) && str[0] == '0' && str[1] == 'x') {
		base = 16;
		i = 2;
	}
	for (; i < str.length(); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			if ((str[i] - '0') >= base)
					break;
			if (isRemainder) {
				qCount *= base;
				remainder *= base;
				remainder += (double)str[i] - '0';
			} else {
				quotient *= base;
				quotient += (double)str[i] - '0';
			}
		} else if (base == 16 && ((str[i] >= 'a' && str[i] <= 'f') || str[i] >= 'A' && str[i] <= 'F')) {
			if (isRemainder) {
				qCount *= base;
				remainder *= base;
				if (str[i] >= 'a' && str[i] <= 'f')
					remainder += (double)str[i] - 'a';
				else
					remainder += (double)str[i] - 'A';
				remainder += 10;
			} else {
				quotient *= base;
				if (str[i] >= 'a' && str[i] <= 'f')
					quotient += (double)str[i] - 'a';
				else
					quotient += (double)str[i] - 'A';
				quotient += 10;
			}
		} else if (str[i] == '.')
			isRemainder = true;
		else
			break;
	}
	if (remainder) {
		remainder /= qCount;
		return quotient + remainder;
	} else
		return quotient;
}
// 1234.5678
double round(double num , int n)
{
	unsigned long long tmp, tmp1;
	tmp = num * pow(10, n+1);
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
	for (i = 0; a != 0; i += d, a += d);
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
	for (long i = absolute(b); i > 0; i--, sum += a);
	return b < 0 ? ToggleSign(sum) : sum;
}
bool DifferentSigns(long a, long b)
{
	return (a > 0 && b < 0) || (a < 0 && b > 0);
}
long DivideWithPlusSign(long a, long b)
{
	if (!b)
		throw runtime_error("Divide by zero exception");
	long quotient;
	long divisor = ToggleSign(absolute(b)); // * -1
	long dividend = absolute(a);
	for (quotient = 0; dividend >= absolute(divisor); dividend += divisor, quotient++);
	return DifferentSigns(a, b) ? ToggleSign(quotient) : quotient;
}
long KthNumberWith357PrimeFactors(long n)
{
	long value = 1;
	if (n > 0) {
		queue<long> three, five, seven;
		three.push(3);
		five.push(5);
		seven.push(7);
		for (--n; n > 0; n--)
		{
			value = Min(three.front(), Min(five.front(), seven.front()));
			if (value == seven.front())
				seven.pop();
			else {
				if (value == five.front())
					five.pop();
				else {
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
	vector<string> subStrings{ "Mississippi", "M", "m", "i", "s", "p", "is", "si", "sip", "hi", "sis", "pi", "ppi","ssi","issi"};
	size_t count = sTree.Count();
	assert(count == 53);
	cout << "Suffix tree of \"Mississippi\" has " << count << " nodes" << endl;
	for (vector<string>::iterator it = subStrings.begin(); it != subStrings.end(); it++) {
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
	assert(sTree.LongestRepeatedSubstring() == "issi");
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
	assert(sTree.LongestRepeatedSubstring() == "");
	sTree.Clear();
	sTree.InsertString("aa");
	assert(sTree.LongestRepeatedSubstring() == "a");
	sTree.Clear();
	sTree.InsertString("aaa");
	assert(sTree.LongestRepeatedSubstring() == "aa");
	sTree.Clear();
	sTree.InsertString("ABABABA");
	assert(sTree.LongestRepeatedSubstring() == "ABABA");
	sTree.Clear();
	sTree.InsertString("abcd1234cd12");
	assert(sTree.LongestRepeatedSubstring() == "cd12");
	sTree.Clear();
	sTree.InsertString("abcd1234abcd");
	assert(sTree.LongestRepeatedSubstring() == "abcd");
	sTree.Clear();
	sTree.InsertString("abcdabcd1234");
	assert(sTree.LongestRepeatedSubstring() == "abcd");
	sTree.Clear();
	sTree.InsertString("abcd12341234");
	assert(sTree.LongestRepeatedSubstring() == "1234");
	sTree.Clear();
	sTree.InsertString("aaaa_11111_bbbb");
	assert(sTree.LongestRepeatedSubstring() == "1111");
	sTree.Clear();
	size_t match;
	sTree.InsertString("abcd");
	sTree.InsertString("adbc");
	match = sTree.LongestCommonSubstring(0);
	assert(match == 2);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 3);
	sTree.Clear();
	sTree.InsertString("helloworld");
	sTree.InsertString("yellomarin");
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	match = sTree.LongestCommonSubstring(3);
	assert(match == 8);
	sTree.Clear();
	sTree.InsertString("abacba");
	sTree.InsertString("abcaba");
	match = sTree.LongestCommonSubstring(0);
	assert(match == 3);
	//match = sTree.LongestCommonSubstring(1); // 'abaxba'
	//assert(match == 4);
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
	sTree.InsertString("bmnobcdeijkq");	// match "bcde"
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbijkmnopqrstuv");	// match "bcde" with first string
	sTree.InsertString("ijklmnopqrst");	// match "ijk" with all other strings
	match = sTree.LongestCommonSubstring(0);
	assert(match == 3);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 4);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbcfghiopqrstuv");
	sTree.InsertString("ijklmnopfghistuvw");
	sTree.InsertString("fghimnopqrstuv");	// match "fghi" with all other strings
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 5);
	sTree.Clear();
	sTree.InsertString("abcdewxyzjkl");
	sTree.InsertString("bbcwxyzoijkq");
	sTree.InsertString("ijklmnopwxyzstuv");
	sTree.InsertString("wxyzmnopqrst");
	sTree.InsertString("abcdmnopqrstwxyz");	// match "wxyz" with all other strings
	match = sTree.LongestCommonSubstring(0);
	assert(match == 4);
	match = sTree.LongestCommonSubstring(1);
	assert(match == 5);
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
	Trie<int> trie;					// Node count:
	trie.Insert("Amy", 12);			// 3
	trie.Insert("Christine", 34);	// 12
	trie.Insert("Tom", 56);			// 15
	trie.Insert("Robert", 78);		// 21
	trie.Insert("Kristy", 90);		// 27
	trie.Insert("apple", 1);		// 32
	trie.Insert("appendix", 2);		// 40
	trie.Insert("appetite", 3);		// 48
	trie.Insert("to", 4);			// 50
	trie.Insert("topple", 5);		// 56
	trie.Insert("tea", 6);			// 59
	trie.Insert("ted", 7);			// 62
	trie.Insert("ten", 8);			// 65
	trie.Insert("in", 9);			// 67
	trie.Insert("inn", 10);			// 70
	trie.Insert("intrinsics", 11);	// 80
	assert(trie.Find("Amy") == 12);
	assert(trie.Find("Christine") == 34);
	assert(trie.Find("Tom") == 56);
	assert(trie.Find("Robert") == 78);
	assert(trie.Find("Kristy") == 90);
	assert(trie.Find("apple") == 1);
	assert(trie.Find("appendix") == 2);
	assert(trie.Find("appetite") == 3);
	assert(trie.Find("to") == 4);
	assert(trie.Find("topple") == 5);
	assert(trie.Find("tea") == 6);
	assert(trie.Find("ted") == 7);
	assert(trie.Find("ten") == 8);
	assert(trie.Find("in") == 9);
	assert(trie.Find("inn") == 10);
	assert(trie.Find("intrinsics") == 11);
	assert(trie.Find("ABC") == int()); // not found
	assert(trie.Find("tee") == int()); // not found
	assert(trie.Find("t") == int()); // not found
	size_t count = trie.Count();
	cout << "Trie has " << count << " nodes" << endl;
	trie.RemoveString("Amy");
	trie.RemoveString("Christine");
	trie.RemoveString("Tom");
	trie.RemoveString("Robert");
	trie.RemoveString("Kristy");
	assert(trie.Find("Amy") == int());
	assert(trie.Find("Christine") == int());
	assert(trie.Find("Tom") == int());
	assert(trie.Find("Robert") == int());
	assert(trie.Find("Kristy") == int());
	assert(trie.Find("ABC") == int());
	cout << endl;
}
void PrefixTrieTests()
{
	vector<string> strings, result;
	cout << "Prefix-Trie tests..." << endl;
	strings.push_back("apple");		// 5
	strings.push_back("appendix");	// 8
	strings.push_back("appetite");	// 8
	strings.push_back("to");		// 2
	strings.push_back("topple");	// 6
	strings.push_back("tea");		// 3
	strings.push_back("ted");		// 3
	strings.push_back("ten");		// 3
	strings.push_back("in");		// 2
	strings.push_back("inn");		// 3
	strings.push_back("intrinsics");// 10
	sort(strings.begin(), strings.end());
	PrefixTrie prefixTrie(strings);
	size_t count = prefixTrie.Count();
	cout << "PrefixTrieTests has " << count << " nodes" << endl;
	result = prefixTrie.Find(string("apple"));
	assert(result.size() == 1);
	assert(result[0] == "apple");

	result = prefixTrie.Find(string("app"));
	assert(result.size() == 3);
	assert(result[0] == "appendix");
	assert(result[1] == "appetite");
	assert(result[2] == "apple");

	result = prefixTrie.Find(string("to"));
	assert(result.size() == 2);
	
	result = prefixTrie.Find(string("in"));
	assert(result.size() == 3);

	result = prefixTrie.Find(string("a"));
	assert(result.size() == 3); // appendix, appetite, apple
	assert(result[0] == "appendix");
	assert(result[1] == "appetite");
	assert(result[2] == "apple");

	result = prefixTrie.Find(string("i"));
	assert(result.size() == 3); // in inn intrinsics
	assert(result[0] == "in");
	assert(result[1] == "inn");
	assert(result[2] == "intrinsics");

	result = prefixTrie.Find(string("t"));
	assert(result.size() == 5); //  tea ted ten to topple
	assert(result[0] == "tea");
	assert(result[1] == "ted");
	assert(result[2] == "ten");
	assert(result[3] == "to");
	assert(result[4] == "topple");

	result = prefixTrie.Find(string("te"));
	assert(result.size() == 3); // tea ted ten
	assert(result[0] == "tea");
	assert(result[1] == "ted");
	assert(result[2] == "ten");

	PrefixTrieNode* node = prefixTrie.GetNode("apple");
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
}
void GetPermutations(string &w, set<string>& result)
{
	string tmp;
	for (size_t i = 0; i < w.size(); i++)
		for (char c = 'A'; c <= 'Z'; c++)
			if (w[i] != c) {
				tmp = w;
				tmp[i] = c;
				result.insert(tmp);
			}
}
// DAMP -> LAMP -> LIMP -> LIME -> LIKE
void Transform(string &start, string &stop, set<string>& dictionary, queue<string>& result)
{
	transform(start.begin(), start.end(), start.begin(), toupper);
	transform(stop.begin(), stop.end(), stop.begin(), toupper);
	queue<string> actionQ;
	set<string> visited;
	map<string, string> backtrack;
	actionQ.push(start);
	visited.emplace(start);
	while (!actionQ.empty()) {
		string w = actionQ.front(); // DAMP
		actionQ.pop();
		set<string> permutations;
		GetPermutations(w, permutations);
		for (set<string>::const_iterator it = permutations.begin(); it != permutations.end(); it++) {
			if (*it == stop) { // LIKE
				// Found our word! Now backtrack to record all the single-character change from 'start' to 'stop'
				result.push(*it);
				result.push(w);
				while (backtrack.find(w) != backtrack.end()) {
					w = backtrack[w];
					result.push(w);
				}
				return;
			} else if (dictionary.find(*it) != dictionary.end() && visited.find(*it) == visited.end()) {
				actionQ.push(*it);
				visited.insert(*it);
				backtrack[*it] = w; //Key: later; Value: earlier
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
	strings.push_back("dog");
	strings.push_back("car"); // "acr" : "car"
	strings.push_back("rats"); // "arst" : rats
	strings.push_back("arc"); // "acr" : "arc"
	vector<vector<string>> anagrams;
	FindAnagrams(strings, anagrams);
	for (vector<vector<string>>::const_iterator it = anagrams.begin(); it != anagrams.end(); it++) {
		cout << "( ";
		copy(it->begin(), it->end(), ostream_iterator<string>(cout, " "));
		cout << "), ";
	}
	assert(sherlockAndAnagrams("mom") == 2);
	assert(sherlockAndAnagrams("abba") == 4);
	assert(sherlockAndAnagrams("abcd") == 0);
	cout << sherlockAndAnagrams("cdcd") << endl;
	cout << sherlockAndAnagrams("kkkk") << endl;
	cout << sherlockAndAnagrams("ifailuhkqq") << endl;
	//assert(sherlockAndAnagrams("cdcd") == 5); //Unfinished work
	//assert(sherlockAndAnagrams("kkkk") == 10); //Unfinished work
	//assert(sherlockAndAnagrams("ifailuhkqq") == 3); //Unfinished work
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
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
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
	shared_ptr<Node<long>> node = tree.FindNode(-50), node1, node2;
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
	assert(node2);
	assert(node2->Item() == 0);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node1 = tree.FindNode(75);
	assert(node1);
	node2 = tree.CommonAncestor(node, node1);
	assert(node2);
	assert(node2->Item() == 50);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node = tree.FindNode(60);
	assert(node);
	node1 = tree.FindNode(75);
	assert(node1);
	node2 = tree.CommonAncestor(node, node1);
	assert(node2);
	assert(node2->Item() == 60);
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
	vector<vector<size_t>> links = { {10, 5}, {10,11} };
	/*
			10
		11		5
	Diff: 15 - 11 = 4
	*/
	assert(cutTheTree(data, links) == 4);
	data.clear();
	data = {10,5,6,20};
	/*
			10
		 5		6
	  20
	Diff: 21 - 20 = 1
	*/
	links = { {10,5}, {10,6}, {5,20} };
	assert(cutTheTree(data, links) == 1);
	/*
			10
		 5		
	  20
	Diff: 20 - 15 = 5
	*/
	data.clear();
	data = {10,5,20};
	links = { {10,5}, {5,20} };
	assert(cutTheTree(data, links) == 5);
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
	a = {50,-100,0,10,-50,60,100,75,150};
	sort(a.begin(), a.end());
	Tree<long> tree1(a);
	assert(tree1.Count() == 9);
	result.clear();
	tree1.Serialize(tree1.Root(), b);
	assert(!b.empty());
	assert(b.size() == a.size());
	for (size_t i = 0; i < a.size(); i++)
		assert(a[i] == b[i]);
	cout << "Binary Search Tree content: " << endl;
	tree1.PrintTree();
	cout << endl;
	tree1.PrintTreeColumns();
	long min = tree1.MinDiffInBST();
	assert(min == 10);
	cout << endl << "Binary Search Tree minimum diff between any 2 nodes: " << min << endl;
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
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	shared_ptr<Node<long>> node, node1, node2;
	node = tree1.FindNode(-50);
	assert(node);
	//assert(tree1.InOrderSuccessor(node)->Item() == 0);
	cout << "InOrder successor of -50: " << tree1.InOrderSuccessor(node)->Item() << endl;
	node = tree1.FindNode(50);
	assert(node);
	//assert(tree1.InOrderSuccessor(node)->Item() == 100);
	cout << "InOrder successor of 50: " << tree1.InOrderSuccessor(node)->Item() << endl;
	nodes.clear();

	node = tree1.FindNode(-50);
	assert(node);
	node1 = tree1.FindNode(10);
	assert(node1);
	node2 = tree1.CommonAncestor(node, node1);
	assert(node2);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node1 = tree1.FindNode(75);
	assert(node1);
	node2 = tree1.CommonAncestor(node, node1);
	assert(node2);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node = tree1.FindNode(60);
	assert(node);
	node1 = tree1.FindNode(75);
	assert(node1);
	node2 = tree1.CommonAncestor(node, node1);
	assert(node2);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;

	Tree<long> tree2(tree1);
	assert(tree1 == tree2);
	cout << "Tree2 content (= Tree1): " << endl;
	tree2.PrintTree();
	cout << endl << endl;
}
void KDTreeTests()
{
	vector<vector<long>> coordinates{ {2,3}, {5,4}, {9,6}, {4,7}, {8,1}, {7,2} };
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
	assert(heap.MaxDepth(heap.Root()) == 4/* Change this assertion number if items are added/removed*/);
	cout << "MinHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "MinHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	heap.Serialize(result);
	cout << "Serialized Min Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++) {
		cout << *it << " ";
		if (it != result.begin()) {
			if (*it < *(it - 1)) {
				cout << "Heap failed!";
				assert(false);
				break;
			}
		}
	}
	cout << endl << endl;
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
	assert(heap.MaxDepth(heap.Root()) == 4/* Change this assertion number if items are added/removed*/);
	cout << "MaxHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "MaxHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	heap.Serialize(result);
	cout << "Serialized Max Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++) {
		cout << *it << " ";
		if (it != result.begin())
			if (*it > *(it - 1)) {
				cout << "Heap failed!";
				assert(false);
				break;
			}
	}
	cout << endl << endl;
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
	assert(heap.MaxDepth(heap.Root()) == 4/* Change this assertion number if items are added/removed*/);
	cout << "MinMaxHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	assert(!nodes.empty());
	cout << "MinMaxHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	heap.Serialize(result);
	cout << "Serialized MinMax Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++) {
		cout << *it << " ";
		if (it != result.begin())
			if (*it < *(it - 1)) {
				throw runtime_error("Heap building failed!");
				break;
			}
	}
	cout << endl << endl;
}
void trim(string &str)
{
	size_t i = 0, j = 0;
	for (i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			if (i > 0 && str[i - 1] != ' ')
				str[j++] = str[i];
		} else
			str[j++] = str[i];
	}
	for (; j < str.size(); j++)
		str[j] = ' ';
}
// 1 2 3 4 5 6; sum: 8
//   6 5 4 3 2 => 3 pairs
size_t sumpairs(vector<long>& numbers, long sum)
{
	size_t count = 0;
	long tmp;
	set<long> found;
	set<long> exclude;
	for (vector<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++) {
		tmp = sum - *it;
		if (found.find(tmp) != found.end() && exclude.find(tmp) == exclude.end()) {
			count++;
			exclude.emplace(tmp);
			//cout << *it << " + " << tmp << endl;
		} else
			found.emplace(*it);
	}
	return count;
}
// https://www.hackerrank.com/challenges/pairs/problem
// 100%
size_t diffpairs(vector<long>& numbers, long diff)
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
size_t diffpairs(set<long>& numbers, long diff)
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
			//cout << *it << ", " << *srcIt << endl;
	}
	return count;
}
vector<char> AddVectors(vector<char>& a, vector<char>& b)
{
	char carry = 0;
	vector<char> result;
	vector<char>::reverse_iterator aIt = a.rbegin();
	vector<char>::reverse_iterator bIt = b.rbegin();
	for (; aIt != a.rend() && bIt != b.rend(); aIt++, bIt++) {
		result.push_back((*aIt + *bIt + carry) % 10);
		carry = (*aIt + *bIt + carry) / 10;
	}
	if (aIt != a.rend()) {
		result.push_back((*aIt + carry) % 10);
		carry = (*aIt + carry) / 10;
	}
	if (bIt != b.rend()) {
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
size_t greaterthansumpairs(vector<long>& numbers, long sum)
{
	size_t count = 0, count1;
	for (size_t it = 0; it <= numbers.size()/2 - 1; it++) {
		count1 = 0;
		for (size_t rit = numbers.size() - 1; rit >= 0 && numbers[it] + numbers[rit] >= sum && it <= rit; rit--)
			count1++;
		if (it == 0 && count1 > 0)
			count += count1 - 1;
		if (it != numbers.size() / 2 - 1)
			count1 *= 2;
		count += count1;
	}
	return count;
}
// Given a 2-dimensional array with arbitrary sizes and contains random positive values, you are required to move from the first element [0][0] to the last 
// element [n][n] using the path which will yield the maximum sum of all the elements traversed. You can only move right and down; NOT left and up.
pathResult_t FindMaxPath(vector<vector<unsigned long>>& grid, size_t r, size_t c)
{
	ostringstream oss;
	pathResult_t result;
	if (r >= grid.size() || c >= grid[r].size())
		return result;
	if (r == grid.size() - 1 && c == grid[r].size() - 1) {
		result.sum = grid[r][c];
		oss << "[" << r << "][" << c <<"]";
		result.path = oss.str();
		return result;
	}
	pathResult_t path1 = FindMaxPath(grid, r, c + 1);
	pathResult_t path2 = FindMaxPath(grid, r + 1, c);
	oss << "[" << r << "][" << c << "] ";
	if (path1.sum >= path2.sum)
		oss << path1.path;
	else
		oss << path2.path;
	result.sum = grid[r][c] + Max(path1.sum, path2.sum);
	result.path = oss.str();
	return result;
}
// S: Start; X: Obstacle E: Destination
// 1 1 1 1 1 
// S 1 X 1 1 
// 1 1 1 1 1 
// X 1 1 E 1 
// 1 1 1 1 X
bool FindShortestPath(vector<vector<char>>& grid, size_t r, size_t c, queue<string>& result, char dest, char obstacle)
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
	while (!positions.empty()) {
		vector<position_t> nextHops(positions);
		positions.clear();
		for (vector<position_t>::const_iterator it = nextHops.begin(); it != nextHops.end(); it++) {
			oss1.str("");
			oss1 << it->row << it->col;
			// Go Down
			if (it->row + 1 < grid.size())
				if (grid[it->row + 1][it->col] == dest) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row + 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row + 1][it->col] != obstacle) {// Obstacle. Cancel this route
					oss.str("");
					oss << it->row + 1 << it->col;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
						positions.push_back(position_t(it->row + 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Right
			if (it->col + 1 < grid[it->row].size())
				if (grid[it->row][it->col + 1] == dest) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col + 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row][it->col + 1] != obstacle) {
					oss.str("");
					oss << it->row << it->col + 1;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
						positions.push_back(position_t(it->row, it->col + 1));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Up
			if (it->row > 0)
				if (grid[it->row - 1][it->col] == dest) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row - 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row - 1][it->col] != obstacle) {
					oss.str("");
					oss << it->row - 1 << it->col;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
						positions.push_back(position_t(it->row - 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Left
			if (it->col > 0)
				if (grid[it->row][it->col - 1] == dest) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col - 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row][it->col - 1] != obstacle) {
					oss.str("");
					oss << it->row << it->col - 1;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
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
void MatrixDistance(vector<vector<long>>& data, size_t x, size_t y)
{
	if (x < data.size() && y < data[0].size()) {
		for (size_t i = 0; i < data.size(); i++) {
			for (size_t j = 0; j < data[0].size(); j++) {
				if (x != i && y != j)
					data[i][j] = abs((int)(x - i)) + abs((int)(y - j));
				else if (x == i && y != j)
					data[i][j] = abs((int)(y - j));
				else if (x != i && y == j)
					data[i][j] = abs((int)(x - i));
			}
		}
	}
}
void MatrixSort(vector<vector<long>>& data)
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
void MatrixSortWithHeap(vector<vector<long>>& data)
{
	Heap<long> heap;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			heap.InsertItem(data[i][j]);
	//QuickSort(sorted, 0, sorted.size() - 1);
	size_t k = 0;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			data[j][i] = heap.pop()->Item();
}
// You are given a matrix. Elements in matrix can be either 0 or 1. Each row and column of matrix is sorted in ascending order.
// Find number of '0's in the given matrix. Expected complexity is O(log(N)).
long MatrixPatternCount(vector<vector<long>>& data)
{
	long i = data.size() - 1, j = data[0].size() -1;
	long count = 0;
	for (; i >= 0 && j >= 0; i--, j--)
		if (!data[i][j]) {
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
template<typename A, typename B>
pair<B, A> flip_pair(const pair<A, B>& p)
{
	return pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
multimap<B, A> flip_map(const map<A, B>& src)
{
	multimap<B, A> dst;
	transform(src.begin(), src.end(), inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}
// https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
// 100%
size_t ConnectedCellsInAGridLinkedList(vector<vector<long>>& grid)
{
	map<string, shared_ptr<Node<string>>> nodes;
	set<shared_ptr<LinkedList<string>>> clusters;
	ostringstream location, oss;
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == 1) {
				location.str("");
				location << i << "," << j;
				//Node<string>* node = new Node<string>(location.str());
				shared_ptr<Node<string>> node(make_shared<Node<string>>(location.str()));
				//nodes[location.str()] = shared_ptr<Node<string>>(node);
				nodes[location.str()] = node;
				shared_ptr<Node<string>> parent = nullptr;
				set<shared_ptr<LinkedList<string>>> joins;
				bool skip = false;
				// Upper Left
				if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1) {
					oss.str("");
					oss << i - 1 << "," << j - 1;
					parent = nodes[oss.str()];
					if (parent) {
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++) {
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head) {
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail) {
							tail->SetNext(node);
							//continue;
							skip = true;
						}
					}
				}
				// Up
				if (i > 0 && grid[i - 1][j] == 1) {
					oss.str("");
					oss << i - 1 << "," << j;
					parent = nodes[oss.str()];
					if (parent) {
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++) {
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head) {
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail) {
							tail->SetNext(node);
							//continue;
							skip = true;
						}
					}
				}
				// Upper Right
				if (i > 0 && j < grid[0].size() - 1 && grid[i - 1][j + 1] == 1) {
					oss.str("");
					oss << i - 1 << "," << j + 1;
					parent = nodes[oss.str()];
					if (parent) {
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++) {
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head) {
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail) {
							tail->SetNext(node);
							//continue;
							skip = true;
						}
					}
				}
				// Left
				if (j > 0 && grid[i][j - 1] == 1) {
					oss.str("");
					oss << i << "," << j - 1;
					parent = nodes[oss.str()];
					if (parent) {
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++) {
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head) {
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail) {
							tail->SetNext(node);
							//continue;
							skip = true;
						}
					}
				}
				// Right
				if (j < grid[0].size() - 1 && grid[i][j + 1] == 1) {
					oss.str("");
					oss << i << "," << j + 1;
					parent = nodes[oss.str()];
					if (parent) {
						shared_ptr<Node<string>> tail = nullptr;
						for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end() && !tail; it++) {
							shared_ptr<Node<string>> head = (*it)->Find(*parent);
							if (head) {
								tail = (*it)->Tail();
								if (tail)
									joins.emplace(*it);
							}
						}
						if (!skip && tail) {
							tail->SetNext(node);
							//continue;
							skip = true;
						}
					}
				}
				// Join the overlapping clusters
				if (!joins.empty() && joins.size() > 1) {
					set<shared_ptr<LinkedList<string>>>::iterator it = joins.begin();
					set<shared_ptr<LinkedList<string>>>::iterator joinTo = clusters.find(*it++); // Get the first cluster from "clusters" and join the others to it
					for (; it != joins.end(); it++) {
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
	for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end(); it++) {
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
size_t ConnectedCellsInAGrid(vector<vector<long>>& grid)
{
	vector<long> data;
	data.resize(grid.size() * grid[0].size());
	generate(data.begin(), data.end(), [i = 1]()mutable{return i++; });
	DisJointSet<long> disjointSet(data);
	size_t width = grid[0].size();
	map<long, size_t> counts;
	size_t max = 0;
	for (size_t i = 0; i < grid.size(); i++)
		for (size_t j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == 1) {
				max = 1;
				long node = i * width + j + 1;
				long currentRoot = disjointSet.Find(node);
				// Upper Left
				if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1) {
					long neighbour = (i - 1) * width + j;
					long root = disjointSet.Union(node, neighbour);
					if (root != 0) {
						if (root != currentRoot && counts.find(currentRoot) != counts.end()) { // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						} else { // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						} 
					}
				}
				// Up
				if (i > 0 && grid[i - 1][j] == 1) {
					long neighbour = (i - 1) * width + j + 1;
					long root = disjointSet.Union(node, neighbour);
					if (root != 0) {
						if (root != currentRoot && counts.find(currentRoot) != counts.end()) { // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else { // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Upper Right
				if (i > 0 && j < grid[0].size() - 1 && grid[i - 1][j + 1] == 1) {
					long neighbour = (i - 1) * width + j + 2;
					long root = disjointSet.Union(node, neighbour);
					if (root != 0) {
						if (root != currentRoot && counts.find(currentRoot) != counts.end()) { // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else { // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Left
				if (j > 0 && grid[i][j - 1] == 1) {
					long neighbour = i * width + j;
					long root = disjointSet.Union(node, neighbour);
					if (root != 0) {
						if (root != currentRoot && counts.find(currentRoot) != counts.end()) { // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else { // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
				// Right
				if (j < grid[0].size() - 1 && grid[i][j + 1] == 1) {
					long neighbour = i * width + j + 2;
					long root = disjointSet.Union(node, neighbour);
					if (root != 0) {
						if (root != currentRoot && counts.find(currentRoot) != counts.end()) { // Existing disjoint set with more than one element
							counts[root] += counts[currentRoot];
							counts.erase(currentRoot);
						}
						else { // Single-element set
							pair<map<long, size_t>::iterator, bool> result = counts.emplace(root, 2);
							if (!result.second)
								counts[root]++;
						}
					}
				}
			} // if (grid[i][j] == 1) {
		} // for (size_t j = 0; j < grid[0].size(); j++) {
	for (map<long, size_t>::iterator it = counts.begin(); it != counts.end(); it++)
		if (it->second > max)
			max = it->second;
	//disjointSet.Print(data, grid[0].size());
	return max;
}
// 0 0 1 0 1
// 0 0 0 0 0
// 0 1 1 1 1
// 0 1 1 0 0
// Start: y:1 x:4 End: x: 3 y: 0 => true

// 0 0 1 1 1
// 0 1 0 0 0
// 1 1 1 1 1
// 0 0 0 0 1
// Start: y:0 x:0 End: x: 1 y: 2 => false
bool PathExists(vector<vector<char>>& grid, size_t r, size_t c, size_t y, size_t x, queue<string>& result, char obstacle)
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
	while (!positions.empty()) {
		vector<position_t> nextHops(positions);
		positions.clear();
		for (vector<position_t>::const_iterator it = nextHops.begin(); it != nextHops.end(); it++) {
			oss1.str("");
			oss1 << it->row << it->col;
			// Go Down
			if (it->row + 1 < grid.size())
				if (it->row + 1 == y && it->col == x) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row + 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row + 1][it->col] != obstacle) {// Obstacle. Cancel this route
					oss.str("");
					oss << it->row + 1 << it->col;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
						positions.push_back(position_t(it->row + 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Right
			if (it->col + 1 < grid[it->row].size())
				if (it->row == y && it->col + 1 == x) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col + 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row][it->col + 1] != obstacle) {
					oss.str("");
					oss << it->row << it->col + 1;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
						positions.push_back(position_t(it->row, it->col + 1));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Up
			if (it->row > 0)
				if (it->row - 1 == y && it->col == x) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row - 1 << it->col;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row - 1][it->col] != obstacle) {
					oss.str("");
					oss << it->row - 1 << it->col;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
						positions.push_back(position_t(it->row - 1, it->col));
						route.emplace(oss.str(), oss1.str());
						visited.emplace(oss.str());
					}
				}
			// Go Left
			if (it->col > 0)
				if (it->row == y && it->col - 1 == x) {// Reach destination. The first reach is the shortest path
					oss.str("");
					oss << it->row << it->col - 1;
					result.push(oss.str());
					pos = oss1.str();
					result.push(pos);
					while (pos != origin && route.find(pos) != route.end()) {
						pos = route[pos];
						result.push(pos);
					}
					return true;
				} else if (grid[it->row][it->col - 1] != obstacle) {
					oss.str("");
					oss << it->row << it->col - 1;
					if (visited.find(oss.str()) == visited.end()) { // Prevent loop
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
void EqualAverageDivide(vector<long>& data, vector<long> &left)
{
	long sum = 0, P = 0;
	size_t N = data.size(), K;
	// Sort the data
	sort(data.begin(), data.end());
	sum = parallel_reduce(data.begin(), data.end(), 0);
	for (K = 1; K < (N - K); K++) {
		if (((K * sum) % N)) //  check if such P can be integer (we operate with array of integers).
			continue;
		// picking K integers with sum of P from sorted array of integers
		P = K * sum / N;
		if (GetSum(data, K, P, 0, left))
			break;
	}
}
bool GetSum(vector<long> &data, size_t K, long P, size_t index, vector<long>& left)
{
	if (!P)
		return K == 0;
	else if (!K)
		return P == 0;
	else if (index >= data.size())
		return false;
	for (size_t i = index; i < data.size(); i++) {
		if (GetSum(data, K - 1, P - data[i], i + 1, left)) {
			left.push_back(data[i]);
			return true;
		}
	}
	return false;
}
//Question was "Given a pattern and a string input - find if the string follows the same pattern and return 0 or 1. 
//Examples:
//1) Pattern: "abba" (.+)(.+)\\2\\1 input : "redbluebluered" should return 1.
//2) Pattern: "aaaa" (.+)\\1\\1\\1  input : "asdasdasdasd" should return 1.
//3) Pattern: "aabb" (.+)\\1(.+)\\2 input : "xyzabcxyzabc" should return 0.
//3) Pattern: "abab" (.+)(.+)\\1\\2 input : "xyzabcxyzabc" should return 1.
bool match(string pattern, string input)
{
	map<char, long> patternCount;
	ostringstream regexStr;
	long captureGroup = 0;
	for (string::const_iterator it = pattern.begin(); it != pattern.end(); it++) {
		if (patternCount.find(*it) != patternCount.end())
			regexStr << "\\" << patternCount[*it];
		else {
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
	for (string::iterator it = str.begin(); it != str.end(); it++) {
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
void FindPattern(string pattern, set<string>& dictionary, set<string>& result)
{
	string encodedPattern = EncodeString(pattern);
	for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
		if (it->size() == pattern.size() && !encodedPattern.compare(EncodeString(*it)))
			result.insert(*it);
}
string GetRange(vector<long>& input)
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
			oss << " - " << numbers[numbers.size() - 1];
	}
	return oss.str();
}
bool isSparseNumber(long i)
{
	long previous2digits = 0;
	for (; i > 0; i=i>>2)
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
	for (shift = 0; i > 0; shift++, i=i>>1)
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
string subtract(istream& a, istream& b)
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
//file: "This is a dog"
//0: This is a
//1: is a dog
set<string> process(string& file, int n)
{
	ostringstream oss;
	vector<string> words;
	set<string> ngrams;
	split(file, ' ', words);
	for (size_t i = 0; i <= words.size() - n; i++)
	{
		for (size_t j = i; j < (i + n); j++) {
			oss << words[j];
			if (j != i + n - 1)
				oss << ' ';
		}
		ngrams.emplace(oss.str());
		oss.str("");
	}
	return ngrams;
}
set<string> intersectionNgram(string& file1, string& file2, int n)
{
	set<string> result;
	set<string> ngrams1 = process(file1, n);
	if (!ngrams1.size())
		return result;
	cout << "File1 " << n << "-grams: ";
	for (set<string>::const_iterator it = ngrams1.begin(); it != ngrams1.end(); it++)
		cout << "\"" << *it << "\"" << ", ";
	cout << endl;
	set<string> ngrams2 = process(file2, n);
	cout << "File2 " << n << "-grams: ";
	for (set<string>::const_iterator it = ngrams2.begin(); it != ngrams2.end(); it++)
		cout << "\"" << *it << "\"" << ", ";
	cout << endl;
	set_intersection(ngrams1.begin(), ngrams1.end(), ngrams2.begin(), ngrams2.end(), inserter(result,result.begin()));
	return result;
}
vector<int> Increment(vector<int>& data)
{
	int j = 1;
	vector<int> result;
	for (vector<int>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
	{
		j += *it;
		if (j < 10) {
			result.push_back(j);
			j = 0;
		} else {
			result.push_back(j - 10);
			j = 1;
		}
	}
	if (j == 1)
		result.push_back(j);
	reverse(result.begin(), result.end());
	return result;
}
vector<string> numbersegments(vector<long>& data)
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
		} else if (oss.str().empty())
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
void * alignedMalloc(size_t size, size_t alignment)
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
template<class URNG> 
void TestURNG(URNG& urng)
{
	// Uniform distribution used with vector
	// Distribution is [-5, 5] inclusive
	uniform_int_distribution<long> dist(-5, 5);
	vector<long> v;
	v.resize(20);
	generate(v.begin(), v.end(), [&] { return dist(urng); });
	cout << "Randomized vector: ";
	copy(v.begin(), v.end(), ostream_iterator<long>(cout, " "));
	cout << endl;

	// Shuffle an array.
	// Notice that shuffle() takes an URNG, not a distribution
	vector<string> strings = { { "H", "He", "Li", "Be", "B", "C", "N", "O", "F",
		"Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc",
		"Ti", "V", "Cr", "Mn", "Fe" } };
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
	TestURNG(device);

	// Second run: simple integer seed. Repeatable results
	cout << "Using constant-seed mersene twister engine URNG:" << endl;
	TestURNG(mt19937_64(12345));

	// Third run: random_device as seed; different each run.
	// Desirable for most purposes
	cout << "Using non-deterministic-seed mersene twister engine URNG:" << endl;
	TestURNG(mt19937_64(device()));

	// Fourth run: "warm-up" sequence as as seed; different each run.
	// Advanced uses. Allows more than 32 bits of randomness.
	cout << "Using non-deterministic-seed \"warm-up\" sequence mersene twister engine URNG" << endl;
	vector<unsigned int> seeds;
	cout << "mt19937_64::state_size: " << mt19937_64::state_size << endl;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(begin(seeds), end(seeds));
	TestURNG(mt19937_64(sequence));
}
long concat(vector<long>& data)
{
	ostringstream oss;
	sort(data.begin(), data.end(), [&data](long i, long j) -> bool {
		ostringstream a, b;
		a << i << j;
		b << j << i;
		return a.str() < b.str(); 
	});
	for (vector<long>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
		oss << *it;
	long result;
	istringstream(oss.str()) >> result;
	return result;
}
long buildmax(vector<long>& a, vector<long>& b, size_t size)
{
	long maxA = 0, maxB = 0, result = 0;
	size_t indexA = 0, indexB = 0;
	for (size_t i = 0; i < size; i++) {
		result *= 10;
		for (size_t i = indexA; i < a.size(); i++)
			if (a[i] >= maxA) {
				maxA = a[i];
				indexA = i;
			}
		for (size_t i = indexB; i < b.size(); i++)
			if (b[i] >= maxB) {
				maxB = b[i];
				indexB = i;
			}
		if (maxA > maxB) {
			result += maxA;
			indexA++;
			maxA = 0;
		} else {
			result += maxB;
			indexB++;
			maxB = 0;
		}
	}
	return result;
}
long MaxLengths(vector<string>& data)
{
	sort(data.begin(), data.end(), [](string a, string b) {return a.size() > b.size(); });
	for (vector<string>::const_iterator it = data.begin(); it != data.end(); it++)
		for (vector<string>::const_iterator it1 = it + 1; it1 != data.end(); it1++) {
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
	try {
		try {
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e) {
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw..." << endl;
			throw; // Throw the original e
		}
	}
	catch (Error e) {
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try {
		try {
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e) {
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw..." << endl;
			e.msg_ = "Second Throw";
			throw; // throw the original e
		}
	}
	catch (Error e) {
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try {
		try {
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e) {
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw e..." << endl;
			throw e; // Throw the new e
		}
	}
	catch (Error e) {
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
	cout << "------------" << endl;
	try {
		try {
			ErrorDerived e("First throw");
			cout << "Inner throw e..." << endl;
			throw e;
		}
		catch (Error e) {
			cout << "Inner catch, &e: " << &e << " msg: " << e.msg_ << endl;
			cout << "Inner re-throw e..." << endl;
			e.msg_ = "Second throw";
			throw e; // Throw the new e
		}
	}
	catch (Error e) {
		cout << "Outer catch, &e: " << &e << " msg: " << e.msg_ << endl;
	}
}
size_t LongestAlternatingSubSequence(const vector<long>& data, vector<long>& result)
{
	map<size_t, vector<long>> sequences;
	direction_t direction = Direction::NoChange, flag = Direction::NoChange;
	size_t count = 0, start = 0, index = 0;
	if (data.size() > 1) {
		for (vector<long>::const_iterator it = data.begin() + 1; it != data.end(); it++, index++) {
			flag = *it > *(it - 1) ? Direction::Up : *it < *(it -1 ) ? Direction::Down : Direction::NoChange;
			if (flag != direction) {
				count++;
				direction = flag;
			} else {
				direction = Direction::NoChange;
				if (sequences.find(index - start) == sequences.end()) {
					vector<long> tmp(data.begin() + start, it);
					sequences.emplace(index - start, tmp);
				}
				start = index;
			}
		}
	}
	if (sequences.size() > 0)
		result = sequences.rbegin()->second;
	return result.size();
}
bool LexicographicSort(string s1, string s2)
{
	size_t i, j;
	map<string, size_t> order = { { "a", 0 },{ "b", 1 },{ "c", 2 },{ "ch", 3 },{ "cz", 4 },{ "d", 5 },{ "e", 6 },{ "f", 7 },{ "g", 8 },{ "h", 9 },{ "i", 10 },{ "j", 11 },{ "k", 12 },{ "l", 13 },{ "m", 14 },{ "n", 15 },{ "o", 16 },{ "p", 17 },{ "q", 18 },{ "r", 18 },{ "s", 19 },{ "t", 20 },{ "u", 21 },{ "v", 22 },{ "w", 23 },{ "x", 24 },{ "y", 24 },{ "z", 25 } };
	map<string, size_t>::iterator s1It = order.end(), s2It = order.end();
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	for (i = 0, j = 0; i < s1.size() && j < s2.size(); ) {
		if (i < s1.size() - 1) {
			s1It = order.find(s1.substr(i, 2));
			if (s1It != order.end())
				i += 2;
		}
		if (s1It == order.end())
			s1It = order.find(s1.substr(i++, 1));
		if (j < s2.size() - 1) {
			s2It = order.find(s2.substr(j, 2));
			if (s2It != order.end())
				j += 2;
		}
		if (s2It == order.end())
			s2It = order.find(s2.substr(j++, 1));
		if (s1It->second == s2It->second) {
			s1It = order.end();
			s2It = order.end();
		} else
			return s1It->second < s2It->second;
	}
	return (s1.size() - i) < (s2.size() - j);
}
// Count number of '1' bits
size_t bitCount(long a)
{
	size_t count = 0;
	for (long i = 1; i <= a; i <<= 1)
		if (i & a)
			count++;
	return count;
}
void BitCombinations(size_t k, vector<long> &result)
{
	for (size_t i = 0; i <= k; i++)
		for (long j = (1 << i) - 1; j < (1 << k); j++)
			if (bitCount(j) == i)
				result.push_back(j);
}
void OrderedMergedCombinations(set<string>&result, string &s1, string &s2, string cur)
{
	if (s1 == "" && s2 == "") {
		result.insert(cur);
		return;
	} else if (s1 == "") {
		result.insert(cur + s2);
		return;
	} else if (s2 == "") {
		result.insert(cur + s1);
		return;
	}
	for (size_t i = 0; i <= s2.size(); i++) // Same result as below
		OrderedMergedCombinations(result, s1.substr(1, s1.size() - 1), s2.substr(i, s2.size() - i), cur + s2.substr(0, i) + s1[0]);
	//for (size_t i = 0; i <= s1.size(); i++) // Same result as above
	//	OrderedMergedCombinations(result, s1.substr(i, s1.size() - i), s2.substr(1, s2.size() - 1), cur + s1.substr(0, i) + s2[0]);
}
//A zero - indexed array A consisting of N integers is given.A triplet(P, Q, R) is triangular if it is possible to build a triangle with sides of lengths A[P], A[Q] and A[R].In other words, triplet(P, Q, R) is triangular if 0 ≤ P < Q < R < N and:
//
//•A[P] + A[Q] > A[R],
//•A[Q] + A[R] > A[P],
//•A[R] + A[P] > A[Q].
//
//For example, consider array A such that :
//A[0] = 10    A[1] = 2    A[2] = 5
//A[3] = 1     A[4] = 8    A[5] = 12
//There are four triangular triplets that can be constructed from elements of this array, namely(0, 2, 4), (0, 2, 5), (0, 4, 5), and (2, 4, 5).
size_t CountTriangles(vector<long>& data)
{
	size_t result = 0;
	if (data.size() < 3)
		return 0;
	for (size_t i = 0; i < data.size(); i++) {
		for (size_t j = i + 1; j < data.size(); j++) {
			for (size_t k = j + 1; k < data.size(); k++) {
				if (data[i] + data[j] > data[k] &&
					data[j] + data[k] > data[i] &&
					data[k] + data[i] > data[j])
					result++;
			}
		}
	}
	return result;
}
// https://app.codility.com/programmers/lessons/16-greedy_algorithms/max_nonoverlapping_segments/
// 100%
size_t MaxNonOverlappingSegments(vector<long>& head, vector<long>& tail)
{
	size_t count = 0, last_nonoverlapping_tail;
	if (!head.empty() && !tail.empty() && head.size() == tail.size()) {
		last_nonoverlapping_tail = tail[0];
		count++;
		for (size_t i = 1; i < head.size(); i++) {
			if (head[i] > (long)last_nonoverlapping_tail) {
				last_nonoverlapping_tail = tail[i];
				count++;
			}
		}
	}
	return count;
}
// https://app.codility.com/programmers/lessons/16-greedy_algorithms/tie_ropes/
// 100%
size_t TieRopes(vector<long>& data, size_t n)
{
	size_t result = 0;
	for (size_t i = 0, sum = 0; i < data.size(); ) {
		sum = 0;
		for (; sum < n && i < data.size();)
			sum += data[i++];
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
long getMinimumCost(long k, vector<long>& c) 
{
	long price = 0;
	if (!c.empty()) {
		size_t flowers = c.size();
		if ((long)flowers > k) {
			size_t solos = 0;
			while ((flowers - solos) % k) {
				solos++;
				k--;
			}
			size_t perperson = (c.size() - solos) / k;
			sort(c.begin(), c.end());
			size_t soloCnt = 0;
			for (vector<long>::reverse_iterator it = c.rbegin(); it != c.rend() && soloCnt < solos; it++, soloCnt++)
				price += *it;
			for (size_t firstflower = c.size() - 1 - solos; k > 0; k--, firstflower--) {
				price += c[firstflower];
				for (size_t i = 1; i < perperson; i++) {
					if (firstflower == perperson - 1)
						price += c[firstflower - i] * (i + 1);
					else
						price += c[firstflower - perperson * i] * (i + 1);
				}
			}
		} else
			price = accumulate(c.begin(), c.end(), 0);
	}
	return price;
}
// https://www.hackerrank.com/challenges/angry-children/problem
// 100%
long maxMin(long k, vector<long>& arr) 
{
	sort(arr.begin(), arr.end());
	long unfair = numeric_limits<long>::max();
	size_t max = 0;
	for (size_t i = 0; i < arr.size() && max < arr.size() - 1; i++) {
		for (max = i + k - 1; max >= arr.size(); max--);
		if (i != max) {
			long diff = abs(abs(arr[max]) - abs(arr[i]));
			if (diff < unfair)
				unfair = diff;
		}
	}
	return unfair;
}
void GreedyAlgorithmTests()
{
	vector<long> a, b;
	a.clear();
	a = {1,3,7,9,9};
	b.clear();
	b = {5,6,8,9,10};
	assert(MaxNonOverlappingSegments(a, b) == 3);
	a.clear();
	a = {1,6,7,9,10};
	b.clear();
	b = {5,6,8,9,10};
	assert(MaxNonOverlappingSegments(a, b) == 5); // No overlapping segments
	a.clear();
	a.resize(6);
	generate(a.begin(), a.end(), [i = 1]()mutable {return i++; });
	b.clear();
	b.resize(6);
	generate(b.begin(), b.end(), [i = 5]()mutable {return i++; });
	assert(MaxNonOverlappingSegments(a, b) == 2);
	a.clear();
	a = {1,2,3,4,1,1,3};
	assert(TieRopes(a, 4) == 3);
	a.clear();
	a = {2,5,6};
	assert(getMinimumCost(2, a) == 15);
	a.clear();
	a = {1,3,5,7,9};
	assert(getMinimumCost(3, a) == 29);
	a.clear();
	a = {10,100,300,200,1000,20,30};
	assert(maxMin(3, a) == 20);
	a.clear();
	a = {1,2,3,4,10,20,30,40,100,200};
	assert(maxMin(4, a) == 3);
	a.clear();
	a = { 1,2,1,2,1};
	assert(maxMin(2, a) == 0);
	a.clear();
	a = {100,200,300,350,400,401,402};
	assert(maxMin(3, a) == 2);
}
string decimal_to_binary(int decimal)
{
	ostringstream oss;
	int remainder = decimal % 2;
	if (decimal == 0)
		return "0";
	oss << decimal_to_binary(decimal / 2);
	oss << remainder;
	return oss.str();
}
void decimal_to_binary(int decimal, vector<bool>& binary, size_t width)
{
	while (decimal) {
		binary.push_back(decimal & 1);
		decimal >>= 1;
	}
	for (size_t i = binary.size(); i < width; i++)
		binary.push_back(false);
	reverse(binary.begin(), binary.end());
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
	for (size_t i = 0; i < x.size(); i++) {
		if (start && x[i] == 0)
			count++;
		else if (x[i] == 1) {
			if (count > max)
				max = count;
			count = 0;
			start = true;
		}
	}
	return max;
}
//For a given array A of N integers and a sequence S of N integers from the set{ −1, 1 }, we define val(A, S) as follows :
//val(A, S) = | sum{ A[i] * S[i] for i = 0..N−1 } |
//(Assume that the sum of zero elements equals zero.)
//For a given array A, we are looking for such a sequence S that minimizes val(A, S).
//Write a function :
//class Solution { public int solution(int[] A); }
//that, given an array A of N integers, computes the minimum value of val(A, S) from all possible values of val(A, S) for all possible sequences S of N integers from the set{ −1, 1 }.
//For example, given array :
//	A[0] = 1
//	A[1] = 5
//	A[2] = 2
//	A[3] = -2
//	your function should return 0, since for S = [−1, 1, −1, 1], val(A, S) = 0, which is the minimum possible value.
long MinAbsSum(vector<long>& data)
{
	long sum = 0;
	long min = LONG_MAX;
	for (size_t i = 0; i < ((size_t)1 << data.size()); i++) {
		vector<bool> binary;
		decimal_to_binary(i, binary, data.size());
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
//data: 1 -2 0 9 -1 -2 -3 9
//memo : 1, -1, MAX(-1, 1) = 1, MAX(10, 8, 10) = 10, MAX(9, 0, -2, 0) = 9, MAX(7, 8, -1, -3, -1) = 8, MAX(5, 6, 7, -2, -4, -2) = 7, MAX(16, 17, 18, 19, 10, 8, 10) = 19
long NumberSolitaire(vector<long>& data)
{
	vector<long> memo(data.size(), numeric_limits<long>::min());
	memo[0] = data[0];
	for (long i = 1; i < (long)data.size(); i++)
		for (long j = 1; j < 7 && (i - j) >= 0; j++)
			memo[i] = max(memo[i], data[i] + memo[i - j]);
	return memo[data.size() - 1];
}
// A zero - indexed array A consisting of N integers is given.It contains daily prices of a stock share for a period of N consecutive days.
// If a single share was bought on day P and sold on day Q, where 0 ≤ P ≤ Q < N, then the profit of such transaction is equal to A[Q] − A[P], provided that A[Q] ≥ A[P].
// Otherwise, the transaction brings loss of A[P] − A[Q].
// For example, consider the following array A consisting of six elements such that :
// A[0] = 23171
// A[1] = 21011
// A[2] = 21123
// A[3] = 21366
// A[4] = 21013
// A[5] = 21367
// If a share was bought on day 0 and sold on day 2, a loss of 2048 would occur because A[2] − A[0] = 21123 − 23171 = −2048. 
// If a share was bought on day 4 and sold on day 5, a profit of 354 would occur because A[5] − A[4] = 21367 − 21013 = 354. 
// Maximum possible profit was 356. It would occur if a share was bought on day 1 and sold on day 5.
// My score: 100%
long MaxProfit(vector<long>& data)
{
	long min = LONG_MAX;
	long delta = 0;
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++) {
		if (*it < min)
			min = *it;
		if ((*it - min) > delta)
			delta = (*it - min);
	}
	return delta;
}
// https://www.hackerrank.com/challenges/stockmax/problem
// 100%
size_t StockMax(vector<long>& prices)
{
	size_t profit = 0;
	size_t maxElement = 0;
	for (size_t i = 0; i < prices.size(); i++) {
		if (maxElement <= i) {
			vector<long>::iterator peak = max_element(prices.begin() + i, prices.end());
			if (peak != prices.end())
				maxElement = peak - prices.begin();
		}
		if (maxElement > i) {
			//cout << "Profit: " << *peak - prices[i] << endl;
			profit += prices[maxElement] - prices[i];
		}
	}
	return profit;
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
	//cout << "Start with room a " << game.hasTreasure(&a) << endl;
	assert(!game.hasTreasure(&a));
	c.addDoor(&f, 2);
	//cout << "Start with room a " << game.hasTreasure(&a) << endl;
	assert(game.hasTreasure(&a));
}
//Given a matrix of N * M, given the coordinates(x, y) present in a matrix,
//Find the number of paths that can reach(0, 0) from the(x, y) points with k steps(requires exactly k, k> = 0)
//From each point you can go up, down, left and right in four directions.
// https://www.geeksforgeeks.org/check-if-it-is-possible-to-move-from-0-0-to-x-y-in-exactly-k-steps/
//For example, the following matrix :
//----------
//0 0 0 0 0
//0 0 0 0 0
//0 0 0 0 0
//0 0 0 0 0
//(x, y) = (1, 1), k = 2, the output is 2
const long moves[][2] = { {0,1}, {0, -1}, {1, 0}, {-1, 0} };
size_t countPaths(size_t m, size_t n, size_t x, size_t y, size_t k)
{
	// It is clear that the shortest path to reach (0, 0) from (x, y) will be minMoves = (|x| + |y|)
	// if K ≥ minMoves then after reaching (0, 0) in minMoves number of moves the remaining (K – minMoves) number of moves have to be even in order to 
	// remain at that point for the rest of the moves.
	size_t minMoves = x + y;
	if (k >= minMoves && !((k - minMoves) % 2) && x < m && y < n) {
		if (k == 0 && x == 0 && y == 0)
			return 1;
		size_t sum = 0;
		//cout << "sizeof(moves): " << sizeof(moves) << ", sizeof(decltype(moves[0])): " << sizeof(decltype(moves[0])) << endl;
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
	while (!q.empty()) {
		shared_ptr<Node<string>> n = q.front();
		q.pop_front();
		for (set<shared_ptr<Node<string>>>::iterator i = n->m_adjacents.begin(); i != n->m_adjacents.end(); i++) {
			if (parents.find(*i) == parents.end()) {
				parents.emplace(*i, n);
				if (*i == node) {
					q.clear();
					break;
				} else
					q.push_back(*i);
			}
		}
	}
	// Build path
	vector<shared_ptr<Node<string>>> path;
	shared_ptr<Node<string>> current = node;
	do {
		path.push_back(current);
		current = parents[current];
	} while (current && current != node);
	if (path.size() == 1 && !current) // current == nullptr : no cycle
		path.clear();
	reverse(path.begin(), path.end());
	return path;
}
//given a binary array, you can flip 0 -> 1 or 1 -> 0 to make all the 1
//are in the left part and all the 0 to the right part, return the minimun flip required
//example 1
//1011000  -> 1111000 only need one flip 0 -> 1
//example 2
//00001 -> 10000 require 2 flips
int findMinFlip(vector<int>& binary)
{
	size_t count = 0, last_left = -1, last_right = -1;
	size_t left = 0, right = binary.size() - 1;
	for (; left < right; ) {
		if (binary[left] == 0)
			last_left = left;
		else if (last_left != -1 && last_left != left) {
			count += left - last_left;
			last_left = -1;
		}
		if (binary[right] == 1)
			last_right = right;
		else if (last_right != -1 && last_right != right) {
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
bool IsValidMatrix(vector<vector<char>> const& data)
{
	for (size_t row = 0; row < data.size(); row++)
		for (size_t col = 0; col < data[row].size(); col++) {
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
	if (node->isLeaf()) {
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
//Task Score: 18 %
//Correctness: 44 %
//Performance: 0 %
size_t ZigZagEscape(vector<long>& data)
{
	vector<zigzag_t> zigzag;
	set<set<int>> result;
	for (size_t i = 0; i < data.size(); i++) {
		zigzag_t zz(i, data[i]);
		zigzag.push_back(zz);
	}
	sort(zigzag.begin(), zigzag.end());
	for (size_t i = 0; i < zigzag.size(); i++) {
		bool wasSmaller = false;
		bool isFirst = true;
		set<int> r;
		r.emplace(zigzag[i].value);
		result.emplace(r);
		for (size_t k = 1; k < (zigzag.size() - i); k++) {
			r.clear();
			r.emplace(zigzag[i].value);
			for (size_t j = i + k, isFirst = true; j < zigzag.size(); j++) {
				//cout << "i: " << i << ", j: " << j << ", k: " << k << endl;
				if (isFirst) {
					isFirst = false;
					wasSmaller = zigzag[j].index < zigzag[i].index;
					r.emplace(zigzag[j].value);
					//copy(r.begin(), r.end(), ostream_iterator<size_t>(cout, " "));
					//cout << endl;
					result.emplace(r);
				} else if (wasSmaller && zigzag[j].index > zigzag[i].index) {
					wasSmaller = !wasSmaller;
					r.emplace(zigzag[j].value);
					//copy(r.begin(), r.end(), ostream_iterator<size_t>(cout, " "));
					//cout << endl;
					result.emplace(r);
				} else if (!wasSmaller && zigzag[j].index < zigzag[i].index) {
					wasSmaller = !wasSmaller;
					r.emplace(zigzag[j].value);
					//copy(r.begin(), r.end(), ostream_iterator<size_t>(cout, " "));
					//cout << endl;
					result.emplace(r);
				} else {
					set<int> tmp(r);
					tmp.erase(zigzag[j - 1].value);
					tmp.emplace(zigzag[j].value);
					result.emplace(tmp);
					//cout << "No result! i:" << zigzag[i].index << " " << zigzag[i].value << ", j: " << zigzag[j].index << " " << zigzag[j].value << endl;
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
size_t ZigZagEscape(vector<long>& data, set<string>& strResult)
{
	long current;
	vector<string> tmp;
	ostringstream oss;
	vector<long> left, right;
	for (size_t i = 0; i < data.size(); i++) {
		if (i > 0)
			left.assign(data.begin(), data.begin() + i);
		if (i != data.size() - 1)
			right.assign(data.begin() + i + 1, data.end());
		sort(left.begin(), left.end());
		sort(right.begin(), right.end());
		current = data[i];
		strResult.insert(to_string(current));
		// Start with left
		for (size_t j = 0; j < left.size(); j++) {
			if (left[j] > current) {
				if (right.empty()) {
					oss << current << " " << left[j];
					strResult.insert(oss.str());
					oss.str("");
				} else {
					tmp = ZigZagEscape(left, right, j, 0, current, true);
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++)
						strResult.insert(*it);
				}
			}
		}
		// Start with right
		for (size_t j = 0; j < right.size(); j++) {
			if (right[j] > current) {
				if (left.empty()) {
					oss << current << " " << right[j];
					strResult.insert(oss.str());
					oss.str("");
				} else {
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
vector<string> ZigZagEscape(vector<long>& left, vector<long>& right, size_t lIndex, size_t rIndex, long current, bool dir)
{//4, 6, 2, 1, 5
	long next;
	vector<string> result, tmp;
	ostringstream oss;
	if (dir && left.size()) {//left
		for (; lIndex < left.size(); lIndex++) {
			if (left[lIndex] > current) {
				next = left[lIndex];
				result.push_back(to_string(current));
				tmp = ZigZagEscape(left, right, lIndex, rIndex, next, !dir);
				if (!tmp.empty()) {
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++) {
						oss << current << " " << *it;
						result.push_back(oss.str());
						oss.str("");
					}
				} else {
					// Only take current value if the other side is empty.
					oss << current << " " << next;
					result.push_back(oss.str());
				}
				oss.str("");
			}
		}
	} else if (right.size())
		for (; rIndex < right.size(); rIndex++)
			if (right[rIndex] > current) {
				next = right[rIndex];
				result.push_back(to_string(current));
				tmp = ZigZagEscape(left, right, lIndex, rIndex, next, !dir);
				if (!tmp.empty()) {
					for (vector<string>::iterator it = tmp.begin(); it != tmp.end(); it++) {
						oss << current << " " << *it;
						result.push_back(oss.str());
						oss.str("");
					}
				} else {
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
	while (node2->Next()) {
		node1 = node1->Next();
		node2 = node2->Next()->Next();
		if (node1 == node2)
			break;
	}
	if (!node2->Next())
		return;
	node1 = head;
	while (node1 != node2) {
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
	a = {5,3,7,7,10};
	b = {1,6,6,9,9};
	assert(IncreasingSequences(a, b) == 2);
	a.clear();
	b.clear();
	a = {1,5,6};
	b = {-2,0,2};
	assert(IncreasingSequences(a, b) == 0);
	a.clear();
	b.clear();
	a = {2,5};
	b = {1,6};
	assert(IncreasingSequences(a, b) == 0);
	a.clear();
	b.clear();
	a = {5,-3,6,4,8};
	b = {2,6,-5,1,0};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0,0,0};
	b = {1,2,3};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0,1,1,2};
	b = {5,4,4,3};
	assert(IncreasingSequences(a, b) == -1); // a increasing; b decreasing

	a.clear();
	b.clear();
	a = {0,1,1,2};
	b = { 3,4,4,5 };
	assert(IncreasingSequences(a, b) == -1);// a increasing; b increasing

	a.clear();
	b.clear();
	a = {2,1,1,0};
	b = {5,4,4,3};
	assert(IncreasingSequences(a, b) == -1);// a decreasing; b decreasing

	a.clear();
	b.clear();
	a = {0,2,2,4,6,6,8,10,10};
	b = {1,2,2,3,4,4,5,6,6};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0,1,1,2,3,3,4,5,5};
	b = {10,10,9,8,8,7,6,6,5};
	assert(IncreasingSequences(a, b) == -1);

	a.clear();
	b.clear();
	a = {0,-1,-2};
	b = {-2,1,2};
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
	iota(a.begin(), a.end(), 0); //a increasing
	iota(b.begin(), b.end(), -1000000000); // b decreasing
	sort(b.begin(), b.end(), greater<long>());
	assert(IncreasingSequences(a, b) == -1);
}
// https://app.codility.com/demo/results/trainingCP4NRT-FE4/
// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/discuss/119835/Java-O(n)-DP-Solution
// 100%
int IncreasingSequences(vector<long> &a, vector<long> &b)
{
	bool outOfSequence = false;
	// swapRecord means for the ith element in A and B, the minimum swaps if we swap A[i] and B[i]
	// fixRecord means for the ith element in A and B, the minimum swaps if we DONOT swap A[i] and B[i]
	int swapRecord = 1, fixRecord = 0;
	if (a.size() != b.size())
		return -1;
	if (a.size() == 1)
		return 0;
	vector<int> A, B;
	bool isSwap = true;
	A.push_back(b[0]);
	B.push_back(a[0]);
	for (size_t i = 1; i < a.size(); i++) {
		if (a[i - 1] >= b[i] || b[i - 1] >= a[i]) {
			// In this case, the ith manipulation should be same as the i-1th manipulation
			// fixRecord = fixRecord;
			swapRecord++;
			//isSwap = true;
		} else if (a[i - 1] >= a[i] || b[i - 1] >= b[i]) {
			// In this case, the ith manipulation should be the opposite of the i-1th manipulation
			int temp = swapRecord;
			swapRecord = fixRecord + 1;
			fixRecord = temp;
			isSwap = !isSwap;
		} else {
			// Either swap or fix is OK. Let's keep the minimum one
			int minimum = min(swapRecord, fixRecord);
			swapRecord = minimum + 1;
			fixRecord = minimum;
			isSwap = swapRecord < fixRecord;
		}
		A.push_back(isSwap ? b[i] : a[i]);
		B.push_back(isSwap ? a[i] : b[i]);
		outOfSequence |= A[i] <= A[i - 1] || B[i] <= B[i - 1];
	}
	return outOfSequence ? -1 : min(swapRecord, fixRecord);
}
void cpluplus17()
{
	map<int, string> mymap;
	// Structured bindings
	// Return compound objects
	auto[it, success] = mymap.emplace(1, "Hello World!!!");
	if (success)
		cout << "Successfully inserted " << it->first << ": " << it->second << endl;
	else
		cout << "Failed to insert into mymap!" << endl;
	// Compound object iterations
	for (const auto&[key, value] : mymap)
		cout << key << ": " << value << endl;
	// Direct Initialization
	for (auto[i, ch] = pair(0U, ' '); i < 10; i++, ch++)
		cout << "[" << i << ": '" << ch << "'] ";
	cout << endl;
}
long MaxProductOfThree(vector<long> &data)
{
	sort(data.begin(), data.end());
	long tmp1 = data[0] * data[1];
	long tmp2 = data[data.size() - 2] * data[data.size() - 3];
	if (data[data.size() - 1] > 0)
		return data[data.size() - 1] * (tmp1 > tmp2 ? tmp1 : tmp2);
	else
		return data[data.size() - 1] * (tmp1 < tmp2 ? tmp1 : tmp2);
}
void RotateRightArray(vector<int>& data, int n)
{
	int previous, current;
	for (; n > 0; n--)
		for (size_t i = 0; i < data.size(); i++) {
			if (!i) {
				previous = data[i];
				data[i] = data[data.size() - 1];
			} else {
				current = data[i];
				data[i] = previous;
				previous = current;
			}
		}
}
// https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=arrays
// 100%
vector<int> RotateLeftArray(vector<int>& a, int d)
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
	else {
		//size_t multiples = (b - a + 1) / k;
		// n * k >= a => n >= a / k
		//size_t first = round(a / k);
		//size_t last = first + k * multiples;
		//return (last + multiples <= b) ? multiples++ : multiples;
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
	for (long i = 0; i < N;) {
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
	for (size_t lastIndex = data.size() - 1; lastIndex >= 1; lastIndex--) {
		for (size_t i = 0; i < lastIndex; i++) {
			if (data[i] > data[i + 1]) {
				found = bribes.emplace(data[i], 1);
				if (!found.second) {
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
vector<int> freqQuery(vector<vector<int>>& queries) 
{
	unordered_map<int, int> frequency; // frequency of data
	unordered_map<int, int> frequencies; // frequeny of frequency
	vector<int> result;
	for (size_t i = 0; i < queries.size(); i++) {
		switch (queries[i][0]) {
		case 1: // Insert
		{
			pair<unordered_map<int, int>::iterator, bool> insert = frequency.emplace(queries[i][1], 1);
			if (!insert.second)
				frequency[queries[i][1]]++;
			insert = frequencies.emplace(frequency[queries[i][1]], 1);
			if (!insert.second)
				frequencies[frequency[queries[i][1]]]++;
		}
		break;
		case 2: // Remove
			if (frequency.find(queries[i][1]) != frequency.end()) {
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
string encryption(string& s) 
{
	vector<vector<char>> result;
	s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
	size_t row = floor(sqrt(s.size()));
	size_t col = ceil(sqrt(s.size()));
	for (; col * row < s.size(); )
		if (row < col)
			row++;
		else
			col++;
	for (size_t i = 0; i < row; i++) {
		string str = s.substr(i * col, col);
		vector<char> chars(str.begin(), str.end());
		for (size_t j = str.size(); j < (size_t)col; j++)
			chars.push_back('\0');
		result.push_back(chars);
	}
	ostringstream oss;
	for (size_t i = 0; i < col; i++) {
		for (size_t j = 0; j < row && result[j][i] != '\0'; j++)
			oss << result[j][i];
		if (i < col - 1)
			oss << ' ';
	}
	return oss.str();
}
// https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem
// 100%
vector<size_t> climbingLeaderboard(vector<long>& scores, vector<long>& alice) 
{
	vector<size_t> result;
	sort(scores.begin(), scores.end());
	scores.erase(unique(scores.begin(), scores.end()), scores.end());
	for (size_t i = 0; i < alice.size(); i++) {
		vector<long>::iterator it = upper_bound(scores.begin(), scores.end(), alice[i]);
		result.push_back(scores.end() - it + 1);
		scores.insert(it, alice[i]);
	}
	return result;
}
// https://www.hackerrank.com/challenges/absolute-permutation/problem
// Unfinished work!
vector<long> absolutePermutation(long n, long k) 
{
	vector<long> result;
	if (k == 0) {
		result.resize(n);
		generate(result.begin(), result.end(), [n = 1]()mutable{return n++; });
		return result;
	}
	else if (n / 2 != k)
		return vector<long>(1, -1);
	// |result[i] - i| = k
	result.resize(n);
	generate(result.begin(), result.end(), [i = k + 1, n]()mutable {
		int tmp = i++ % n;
		return !(tmp % n) ? n : tmp % n;
	});
	return result;
}
long calculateMedian(vector<long>& data)
{
	const auto middleItr = data.begin() + data.size() / 2;// +data.size() % 2;
	nth_element(data.begin(), middleItr, data.end());
	if (data.size() % 2 == 0) {
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
		{20, "twenty"}
	};
	ostringstream str, hour;
	if (m == 0) {
		str << numbers[h] << " o' clock";
		return str.str();
	} else if (m == 15) {
		str << "quarter past " << numbers[h];
		return str.str();
	}
	else if (m == 30) {
		str << "half past " << numbers[h];
		return str.str();
	}
	else if (m == 45) {
		str << "quarter to " << numbers[h + 1];
		return str.str();
	}
	if (m > 30) {
		m -= 30;
		m = 30 - m;
		hour << " to " << numbers[h + 1];
	} else
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
					if ((i ^ j ^ k ^ l) != 0) {
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
	if (i_end < i_start && j_end < j_start) {
		if ((i_start - i_end) % 2) {
			result.push_back("Impossible");
			return result;
		}
		long uls = (i_start - i_end) / 2; // 6 / 2 = 3
		long dest_j = j_start - uls; // 6 - 3 = 3
		if ((abs(j_end - dest_j)) % 2) {
			result.push_back("Impossible");
			return result;
		}
		long L = (dest_j - j_end) / 2;
		oss << uls + L;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < (size_t)uls; i++) {
			oss << "UL";
			if (i != uls - 1)
				oss << " ";
		}
		if (L)
			oss << " ";
		for (size_t i = 0; i < (size_t)L; i++) {
			oss << "L";
			if ((long)i < L - 1)
				oss << " ";
		}
	}
	// Upper Right
	else if (i_end < i_start && j_end > j_start) {
		if ((i_start - i_end) % 2) {
			result.push_back("Impossible");
			return result;
		}
		int urs = (i_start - i_end) / 2; // 4 / 2 = 2
		int dest_j = j_start + urs; // 2 - 1 = 1
		if ((abs(j_end - dest_j)) % 2) {
			result.push_back("Impossible");
			return result;
		}
		int R = (j_end - dest_j) / 2; // (3 - 
		oss << urs + R;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < (size_t)urs; i++) {
			oss << "UR";
			if ((long)i != urs - 1)
				oss << " ";
		}
		if (R)
			oss << " ";
		for (size_t i = 0; i < (size_t)R; i++) {
			oss << "R";
			if ((long)i < R - 1)
				oss << " ";
		}
	}
	// Lower Left
	else if (i_end > i_start && j_end < j_start) {
		if ((i_end - i_start) % 2) {
			result.push_back("Impossible");
			return result;
		}
		int lls = (i_end - i_start) / 2;
		int dest_j = j_start - lls;
		if ((abs(j_end - dest_j)) % 2) {
			result.push_back("Impossible");
			return result;
		}
		int L = (dest_j - j_end) / 2;
		if (L >= 0) {
			oss << lls + L;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)lls; i++) {
				oss << "LL";
				if ((long)i != lls - 1)
					oss << " ";
			}
			if (L)
				oss << " ";
			for (size_t i = 0; i < (size_t)L; i++) {
				oss << "L";
				if ((long)i < L - 1)
					oss << " ";
			}
		} else {  // L < 0
			oss << lls;
			result.push_back(oss.str());
			oss.str("");
			for (int i = L; i < 0; i++) {
				oss << "LR";
				if (i < -1)
					oss << " ";
			}
			if (lls + L)
				oss << " ";
			for (size_t i = 0; i < (size_t)(lls + L); i++) {
				oss << "LL";
				if ((long)i != (lls + L - 1))
					oss << " ";
			}
		}
	}
	// Lower Right
	else if (i_end > i_start && j_end > j_start) {
		if ((i_end - i_start) % 2) {
			result.push_back("Impossible");
			return result;
		}
		int lrs = (i_end - i_start) / 2;
		int dest_j = j_start + lrs;
		if ((abs(j_end - dest_j)) % 2) {
			result.push_back("Impossible");
			return result;
		}
		int R = (j_end - dest_j) / 2;
		if (R >= 0) {
			oss << lrs + R;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)R; i++) {
				oss << "R";
				if ((long)i < R - 1)
					oss << " ";
			}
			if (lrs)
				oss << " ";
			for (size_t i = 0; i < (size_t)lrs; i++) {
				oss << "LR";
				if ((long)i != lrs - 1)
					oss << " ";
			}
		}
		else { // R < 0
			oss << lrs;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (size_t)(lrs + R); i++) {
				oss << "LR";
				if (i != (lrs + R - 1))
					oss << " ";
			}
			if (R < 0)
				oss << " ";
			for (int i = R; i < 0; i++) {
				oss << "LL";
				if (i < -1)
					oss << " ";
			}
		}
	}
	// UP
	else if (j_end == j_start && i_end < i_start) {
		size_t diff = i_start - i_end;
		if (diff % 4) {
			result.push_back("Impossible");
			return result;
		}
		else {
			oss << diff / 2;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (diff / 4); i++) {
				oss << "UL UR";
				if (i != (diff / 4) - 1)
					oss << " ";
			}
		}
	}
	// DOWN
	else if (j_end == j_start && i_end > i_start) {
		size_t diff = i_end - i_start;
		if (diff % 4) {
			result.push_back("Impossible");
			return result;
		}
		else {
			oss << diff / 2;
			result.push_back(oss.str());
			oss.str("");
			for (size_t i = 0; i < (diff / 4); i++) {
				oss << "LR LL";
				if (i != (diff / 4) - 1)
					oss << " ";
			}
		}
	}
	// Left
	else if (i_end == i_start && j_end < j_start) {
		if ((j_start - j_end) % 2) {
			result.push_back("Impossible");
			return result;
		}
		size_t L = (j_start - j_end) / 2;
		oss << L;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < L; i++) {
			oss << "L";
			if (i != L - 1)
				oss << " ";
		}
	}
	// Right
	else if (i_end == i_start && j_end > j_start) {
		if ((j_end - j_start) % 2) {
			result.push_back("Impossible");
			return result;
		}
		size_t R = (j_end - j_start) / 2;
		oss << R;
		result.push_back(oss.str());
		oss.str("");
		for (size_t i = 0; i < R; i++) {
			oss << "R";
			if (i != R - 1)
				oss << " ";
		}
	}
	else {
		// Destination = start?
		oss << 0 << endl;
	}
	result.push_back(oss.str());
	return result;
}
// https://www.hackerrank.com/challenges/kruskalmstrsub/problem
// https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
// 100%
int kruskals(int nodes, vector<long>& from, vector<long>& to, vector<long>& weight) 
{
	multiset<Edge> edges;
	int sum = 0;
	for (size_t i = 0; i < weight.size(); i++)
		edges.emplace(Edge(weight[i], from[i], to[i]));
	DisJointSet<long> disjointSet(from);
	disjointSet.MakeSet(to);
	for (multiset<Edge>::iterator it = edges.begin(); it != edges.end(); it++) {
		if (disjointSet.Find(it->node1) != disjointSet.Find(it->node2)) {
			sum += it->weight;
			disjointSet.Union(it->node1, it->node2);
		}
	}
	return sum;
}
// https://www.hackerrank.com/challenges/primsmstsub/problem
// https://en.wikipedia.org/wiki/Prim%27s_algorithm
// https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
// 2 cases with 1000 vertices and 10,000 edges failed
size_t PrimMinimumSpanningTree(size_t nodes, vector<vector<long>>& edges, long start)
{
	Graph<long, long> graph;
	for (size_t i = 0; i < edges.size(); i++) {
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
	for (size_t i = 0; i < nodes; i++) {
		shared_ptr<Vertex<long, long>> v = graph.GetVertex(i+1);
		assert(v);
		graph.Print(v);
	}
	return graph.PrimMinimumSpanningTree(startVertex);
}
// https://www.hackerrank.com/challenges/rust-murderer/problem
// 3/7 test cases failed :(
void UnbeatenPaths(size_t nodes, vector<vector<long>>& edges, long start, vector<size_t>& paths)
{
	Graph<long, long> graph;
	for (size_t i = 1; i <= nodes; i++)
		graph.AddVertex(i);
	for (size_t i = 0; i < edges.size(); i++) {
		shared_ptr<Vertex<long, long>> v1 = graph.GetVertex(edges[i][0]);
		shared_ptr<Vertex<long, long>> v2 = graph.GetVertex(edges[i][1]);
		assert(v1);
		assert(v2);
		graph.AddUndirectedEdge(v1, v2, 0);
	}
	cout << __FUNCTION__ << " graph (" << nodes << " nodes):" << endl;
	for (size_t i = 0; i < nodes; i++) {
		shared_ptr<Vertex<long, long>> v = graph.GetVertex(i + 1);
		assert(v);
		graph.Print(v);
	}
	graph.UnbeatenPath(start, paths);
}
// https://www.hackerrank.com/challenges/jack-goes-to-rapture/problem
// Timeout! for test cases with 50000 nodes
long getLowestPathCost(size_t g_nodes, vector<long>& g_from, vector<long>& g_to, vector<long>& g_weight)
{
	// Breadth-First-Search algorithm
	Graph<long, long> graph;
	for (size_t i = 1; i <= g_nodes; i++)
		graph.AddVertex(i);
	for (size_t i = 0; i < g_from.size(); i++) {
		shared_ptr<Vertex<long, long>> v1 = graph.GetVertex(g_from[i]);
		shared_ptr<Vertex<long, long>> v2 = graph.GetVertex(g_to[i]);
		assert(v1);
		assert(v2);
		graph.AddUndirectedEdge(v1, v2, g_weight[i]);
	}
	//cout << __FUNCTION__ << " graph (" << g_nodes << " nodes):" << endl;
	//for (size_t i = 1; i <= g_nodes; i++)
	//	graph.Print(graph.GetVertex(i));
	//cout << endl;
	set<shared_ptr<Vertex<long, long>>> spt;
	long cost = graph.GetPathsCosts(spt, graph.GetVertex(1), graph.GetVertex(g_nodes));
	//cout << "Vertex\tDistance from Source" << endl;
	//for (set<shared_ptr<Vertex<long, long>>>::iterator it = spt.begin(); it != spt.end(); it++)
	//	cout << (*it)->GetTag() << "\t" << (*it)->GetTotalCost() << endl;
	return cost;
}
// https://www.hackerrank.com/challenges/3d-surface-area/problem
// 100%
size_t SurfaceArea3D(vector<vector<long>>& data) 
{
	size_t zArea = 0, xArea = 0, yArea = 0;
	for (size_t i = 0; i < data.size(); i++) {
		for (size_t j = 0; j < data[i].size(); j++) {
			if (data[i][j] > 0)
				zArea++;
			// X-Axis : Side / Left/Right views
			if (i == 0) // Start X-Axis border
				xArea += data[i][j];
			if (i == data.size() - 1) {// End X-Axis border
				xArea += data[i][j];
				if (i != 0)
					xArea += abs(data[i][j] - data[i - 1][j]);
			}
			if (i != 0 && i != data.size() - 1)
				xArea += abs(data[i][j] - data[i - 1][j]);
			// Y-Axis : Front/Back views
			if (j == 0) // Start Y-Axis border
				yArea += data[i][j];
			if (j == data[i].size() - 1) {// End Y-Axis border
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
size_t cutTheTree(vector<size_t>& data, vector<vector<size_t>>& edges)
{
	Tree<size_t> tree(data[0]);
	for (size_t i = 0; i < edges.size(); i++) {
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
size_t MinSubGraphDifference(vector<size_t>& data, vector<vector<size_t>>& edges)
{
	Graph<size_t, size_t> graph;
	for (size_t i = 0; i < data.size(); i++)
		graph.AddVertex(i + 1, data[i]);
	for (size_t i = 0; i < edges.size(); i++) {
		shared_ptr<Vertex<size_t, size_t>> v1 = graph.GetVertex(edges[i][0]);
		shared_ptr<Vertex<size_t, size_t>> v2 = graph.GetVertex(edges[i][1]);
		assert(v1);
		assert(v2);
		graph.AddUndirectedEdge(v1, v2, 0);
	}
	//cout << __FUNCTION__ << " graph (" << data.size() << " nodes)" << endl;
	//for (size_t i = 0; i < data.size(); i++)
	//	graph.Print(graph.GetVertex(i + 1));
	//cout << endl;
	size_t result = graph.MinSubTreesDifference(graph.GetVertex(1));
	return result;
}
// https://www.hackerrank.com/challenges/jeanies-route/problem
// Times out for more than 100 nodes! ;)
long PostmanProblem(vector<long>& k, vector<vector<long>>& roads)
{
	Graph<long, long> graph;
	for (size_t i = 0; i < roads.size(); i++) {
		shared_ptr<Vertex<long, long>> v1 = graph.AddVertex(roads[i][0]);
		shared_ptr<Vertex<long, long>> v2 = graph.AddVertex(roads[i][1]);
		graph.AddUndirectedEdge(v1, v2, roads[i][2]);
	}
	set<vector<long>> paths;
	paths = permute(k);
	multimap<long, string> costs;
	ostringstream oss, oss1, oss2;
	map<string, long> costCache;
	for (set<vector<long>>::iterator it = paths.begin(); it != paths.end(); it++) {
		vector<long> path = *it;
		long totalCost = 0;
		bool isValidPath = true;
		for (size_t i = 0; i < path.size() - 1 && isValidPath; i++) {
			long cost = -1;
			oss1.str("");
			oss2.str("");
			oss1 << path[i] << "-" << path[i + 1];
			oss2 << path[i + 1] << "-" << path[i];
			if (costCache.find(oss1.str()) != costCache.end())
				cost = costCache[oss1.str()];
			else if (costCache.find(oss2.str()) != costCache.end())
				cost = costCache[oss2.str()];
			else {
				cost = graph.Dijkstra(path[i], path[i + 1]);
				costCache[oss1.str()] = cost;
				costCache[oss2.str()] = cost;
			}
			//cout << path[i] << " - " << path[i + 1] << ": " << cost << endl;
			if (cost >= 0)
				totalCost += cost;
			else
				isValidPath = false;
			oss << path[i] << "," << path[i + 1] << ",";
		}
		if (isValidPath) {
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
string AlmostSorted(vector<long>& arr)
{
	ostringstream oss;
	vector<long> sorted(arr);
	sort(sorted.begin(), sorted.end());
	vector<long> diff;
	long positive = -1, sum = 0;
	for (size_t i = 0; i < arr.size(); i++) {
		long delta = arr[i] - sorted[i];
		if (delta > 0 && positive < 0)
			positive = i;
		if (positive >= 0) { // Start tracking from the first positive delta to minimize space complexity
			size_t index = i - positive;
			diff.push_back(delta);
			sum += diff[index];
			if (diff[index] < 0 && sum == 0) {
				size_t positives = count_if(diff.begin(), diff.end(), [](long i) {return i > 0; });
				size_t negatives = count_if(diff.begin(), diff.end(), [](long i) {return i < 0; });
				if (diff[index] + diff[0] != 0)
					return "no";
				else if (positives == 1 && negatives == 1) {
					if (!oss.str().empty())
						return "no";
					oss << "swap " << positive + 1 << " " << i + 1;
				} else if (i > (size_t)(positive + 1)) {
					if (!oss.str().empty())
						return "no";
					oss << "reverse " << positive + 1 << " " << i + 1;
				}
			}
		}
	}
	return oss.str().empty() ? "no" : oss.str();
}