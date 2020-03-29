#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <queue>
#include <set>
#include <bitset>
#include <iomanip>
#include <regex>
#include <exception>
#include <ppl.h>
#include <limits.h>
#include <cmath>
#include "Tower.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "Tree.h"
#include "KDTree.h"
#include "Heap.h"
#include "Node.h"
#include "Trie.h"
#include "SuffixTree.h"
#include "PrefixTrie.h"
#include "PriorityQueueMedian.h"
#include "DiamondProblem.h"
#include "Error.h"
#include "LinkedList.h"
#include "Square.h"
#include "TreasureGame.h"
#include "FunctionObject.h"
#include "interval_map.h"
using namespace std;
using namespace concurrency;
typedef enum { SORT_ASCENDING, SORT_DESCENDING } sort_order_t;
typedef union {
	long l;
	float f;
} thirty_two_bit;
typedef union {
	long long ll;
	double d;
} sixty_four_bit;
typedef struct ZeroFactors {
	long two, five, value, minValue;
	bool operator > (const ZeroFactors& other) const {
		return max(two, five) == max(other.two, other.five) ? value > other.value : max(two, five) > max(other.two, other.five);
		//return minValue == other.minValue ? value > other.value : minValue > other.minValue;
	}
	bool operator < (const ZeroFactors& other) const {
		return min(two, five) == min(other.two, other.five) ? value < other.value : min(two, five) < min(other.two, other.five);
	}
} zerofactors_t;
typedef struct ZeroFactorsTwoCount {
	long count, fives, value, index;
	bool operator > (const ZeroFactorsTwoCount& other) const {
		if (count == other.count)
			return (fives == other.fives) ? value > other.value : fives > other.fives;
		else
			return count > other.count;
	}
} zerofactorstwocount_t;
typedef struct ZeroFactorsFiveCount {
	long count, twos, value, index;
	bool operator > (const ZeroFactorsFiveCount& other) const {
		if (count == other.count)
			return (twos == other.twos) ? value > other.value : twos > other.twos;
		else
			return count > other.count;
	}
} zerofactorsfivecount_t;
float MachineEpsilon(float value);
float FloatMachineEpsilonApproximation();
double MachineEpsilon(double value);
double MachineEpsilonApproximation();
bool LexicographicSort(string i, string j);
void testPointerReference(int*&);
long Min(long, long);
long Max(long, long);
long gcd(long a, long b);
long gcd_euclidean(long a, long b);
long lcm(long a, long b);
unsigned long long _atoull(string, char base = 10);
double _atod(string str, char base = 10);
double round(double num , int n);
bool isUniqueString(string const&);
vector<string> findUnique(vector<string> const&, vector<string>const&);
bool CanShuffleWithoutRepeat(string&);
long ConsecutiveLargestSum(vector<long>&, vector<long>&);
long ConsecutiveLargestSumOfFactors(vector<zerofactors_t>& data, vector<zerofactors_t>& result, int value);
long LongestNonNegativeSumSlice(vector<long>&);
size_t CountDistinctSlices(long m, vector<long>&);
size_t CountTriangles(vector<long>&);
// Greedy Algorithms
size_t MaxNonOverlappingSegments(vector<long>&, vector<long>&);
size_t TieRopes(vector<long>&, long);
long MinAbsSum(vector<long>&);
long NumberSolitaire(vector<long>&);
long MaxProfit(vector<long>&);
string decimal_to_binary(int);
void decimal_to_binary(int decimal, vector<bool>&, size_t width);
size_t binary_gap(long);
void reverse(string&);
void reverseWords(string&);
void RemoveDuplicateCharacters(string&);
bool areAnagrams(string const&, string const &);
void FindAnagrams(vector<string> const&, vector<vector<string>> &);
size_t sherlockAndAnagrams(string const&);
void PalindromeTests();
bool isPalindrome(string const&);
bool isPalindrome1(string const&);
bool isPalindrome2(string const&);
bool SherlockValidString(string const&);
string FindBiggestPalindromeSubstring(string const&);
size_t PalindromeAnagramCount(string const&);
size_t PalindromeAnagramCount1(string const &);
bool AreRotatedStrings(string const &, string const &, size_t);
void RotateRightArray(vector<int>&, int);
vector<int> RotateLeftArray(vector<int>&, int);
vector<size_t> FindSubString(string const &, string const s2);
size_t KMPSearch(string const&, string const&);
void KMPTable(string const&, vector<long>&);
void copy_on_write_string();
long fibonacci(long);
unsigned long long factorial(long);
long SequenceSum(long n);
void MultiplesCount(int, long &, long &);
long FactorialTrailingZeroesCount(long);
long MaxZeroProductBruteForce(vector<int> const&);
long MaxZeroProduct(vector<int> const&, size_t);
void MaxZeroProductTests();
set<string> permute(string const&);
void BitCombinations(size_t, vector<long> &);
void OrderedMergedCombinations(set<string>&, string&, string&, string);
string insertCharAt(char, string, size_t);
void findDistinct(vector<long>&, vector<long>&);
void findPrimes(unsigned long, vector<long>&);
size_t CommonPrimeDivisors(vector<long>&, vector<long>&);
unsigned long long findMax(vector<unsigned long long> const&);
void Merge(vector<long> &, vector<long> &);
int BinarySearch(vector<long> source, int toSearch);
int BinarySearchCountUpper(vector<long> source, int toSearch, int start, int end);
int BinarySearchCountLower(vector<long> source, int toSearch, int start, int end);
int BinarySearch(vector<string> source, string toSearch);
void parentheses(vector<string> &, size_t);
void parentheses(vector<string> &, string &, size_t, long, long);
long LongestValidParentheses(string&);
long LongestValidParenthesesWithFixes(string&, size_t k);
template<class T>
void SortStack(MyStack<T> &, MyStack<T> &, sort_order_t order);
bool DifferentSigns(long a, long b);
long ToggleSign(long);
long absolute(long a);
long SubtractWithPlusSign(long a, long b);
long MultiplyWithPlusSign(long a, long b);
long DivideWithPlusSign(long a, long b);
void StackTests();
void QueueTests();
void TestBinarySearch();
void TestBinarySearchString();
void TestBinarySearchCount();
void SuffixTreeTests();
void PrefixTrieTests();
void TrieTests();
void TestStringPermutations();
void BubbleSort(vector<long>&);
size_t minimumBribes(vector<long>&);
size_t Partition(vector<long> &, size_t left, size_t right, size_t pivot);
void QuickSort(vector<long> &, long left, long right);
void SelectionSort(vector<long> &);
void InsertionSort(vector<long> &);
void HeapSort(vector<long> &);
void CountingSort(vector<size_t> &);
string CountingSort(vector<vector<string>>&);
void TopDownMergeSort(vector<long>&, vector<long>&, size_t, size_t);
void BottomUpMergeSort(vector<long>&, vector<long>&);
long countInversions(vector<long>&);
size_t TopDownMergeSortCountConversions(vector<long>&, vector<long>&, size_t, size_t);
size_t MergeCountInversions(vector<long>&, vector<long>&, size_t, size_t, size_t);
void Merge(vector<long>&, vector<long>&, size_t start, size_t middle, size_t end);
void Swap(long &, long &);
long** my2DAlloc(long rows, long cols);
long AddWithoutArithmetic(long a, long b);
void shuffleCards(vector<long> &);
void randomSubset(vector<long> &, size_t count, vector<long> &);
long countDigits(char digit, long n);
void sortingTests();
void BinaryTreeTests();
void KDTreeTests();
void BinarySearchTreeTests();
void MinHeapTests();
void MaxHeapTests();
void MinMaxHeapTests();
void Transform(string &, string&, set<string>&, queue<string>&);
void GetPermutations(string &);
void trim(string &);
size_t sumpairs(vector<long>&, long);
size_t diffpairs(vector<long>&, long);
size_t diffpairs(set<long>&, long);
size_t greaterthansumpairs(vector<long>&, long sum);
string uncompress(string const&);
size_t findLongestContiguousPattern(string&, char c);
string GetRange(vector<long>&);
bool isSparseNumber(long i);
long NextSparseNumber(long number);
void SparseNumberTests();
long KthNumberWith357PrimeFactors(long);
typedef struct PathResult {
	PathResult() : sum(0), path("") {}
	unsigned long sum;
	string path;
} pathResult_t;
pathResult_t FindMaxPath(vector<vector<unsigned long>>&, size_t, size_t);
bool PathExists(vector<vector<char>>&, size_t, size_t, size_t, size_t, queue<string>&, char obstacle);
typedef struct Position {
	Position() : row(-1), col(-1) {}
	Position(size_t r, size_t c) : row(r), col(c) {}
	size_t row;
	size_t col;
} position_t;
typedef struct ZigZagEscape {
	size_t index;
	int value;
	ZigZagEscape(size_t i, int v) : index(i), value(v) {}
	bool operator < (const ZigZagEscape& other) const {
		return value < other.value;
	}
	bool operator > (const ZigZagEscape& other) const {
		return value < other.value;
	}
} zigzag_t;
bool FindShortestPath(vector<vector<char>>&, size_t r, size_t c, queue<string>&, char dest, char obstacle);
void MatrixDistance(vector<vector<long>>&, size_t, size_t);
void MatrixSort(vector<vector<long>>&);
long MatrixPatternCount(vector<vector<long>>&);
void MatrixSortWithHeap(vector<vector<long>>&);
size_t ConnectedCellsInAGrid(vector<vector<long>>&);
// Start of Sort numbers into consecutive positive/negative numbers
template<typename type>
void sortNumbers(vector<long> &);
template<typename type>
void OrderArrayIntoNegativePositiveSeries(vector<long> &);
void OrderArrayIntoNegativePositiveSeriesTests();
void TestCornerCases();
void TestCase1();
void TestCase2();
void TestCase3();
void TestCase4();
void TestCase5();
void TestCase6();
// End of Sort numbers into consecutive positive/negative numbers
void EqualAverageDivide(vector<long>&, vector<long>&);
bool GetSum(vector<long> &, size_t K, long sum, size_t index, vector<long>&);
bool match(string pattern, string input);
string EncodeString(string);
void FindPattern(string, set<string>&, set<string>&);
string subtract(istream&, istream &);
set<string> intersectionNgram(string&, string&, int n);
vector<int> Increment(vector<int>&);
void *alignedMalloc(size_t bytes, size_t alignment);
void alignedFree(void **p);
vector<string> numbersegments(vector<long>&);
unsigned long long XOR(unsigned long long);
template<class URNG> 
void TestURNG(URNG&);
void TestRandom();
void TestGreedyAlgorithms();
long concat(vector<long>&);
long buildmax(vector<long>&, vector<long>&, size_t);
bool JSONValidation(string);
vector<char> AddVectors(vector<char>&, vector<char>&);
long MaxLengths(vector<string>&);
void ExceptionTest();
size_t LongestAlternatingSubSequence(const vector<long>&, vector<long>&);
size_t bitCount(long);
void PlayTreasureGame();
const size_t moves[][2] = { {0,1}, {0, -1}, {1, 0}, {-1, 0} };
size_t countPaths(size_t, size_t, size_t, size_t, size_t);
void testPathCount(size_t, size_t, size_t, size_t, size_t);
vector<shared_ptr<Node<string>>> shortest_cycle_path(shared_ptr<Node<string>>);
int findMinFlip(vector<int>&);
bool IsValidMatrix(vector<vector<char>> const&);
template <class T>
T TreeArithmeticTotal(shared_ptr<Node<string>>);
size_t ZigZagEscape(vector<long>&);
size_t ZigZagEscape(vector<long>&, set<string>&);
vector<string> ZigZagEscape(vector<long>&, vector<long>&, size_t lIndex, size_t rIndex, long current, bool dir);
void CircularLinkedListLoopStart();
int IncreasingSequences(vector<long>&, vector<long>&);
void IncreasingSequenceTests();
void cpluplus17();
long MaxProductOfThree(vector<long>&);
size_t CountDiv(size_t, size_t, size_t);
long ChocolatesByNumbers(long, long);
long getMinimumCost(long, vector<long>&);
long maxMin(long, vector<long>&);
vector<int> freqQuery(vector<vector<int>>&);
string encryption(string&);
vector<size_t> climbingLeaderboard(vector<long>&, vector<long>&);
vector<long> absolutePermutation(long, long);
long calculateMedian(vector<long>&);
string timeInWords(int, int);
size_t beautifulQuadruples(int, int, int, int);