#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
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
#include <unordered_set>
#include <bitset>
#include <iomanip>
#include <regex>
#include <exception>
#include <ppl.h>
#include <limits.h>
#include <cmath>
#include "NameHidingExample.h"
#include "Singleton.h"
#include "Graph.h"
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
#include "CircularLinkedList.h"
#include "Square.h"
#include "TreasureGame.h"
#include "FunctionObject.h"
#include "interval_map.h"
#include "DisJointSet.h"
#include "Edge.h"
using namespace std;
using namespace concurrency;
typedef enum class SortOrder { SORT_ASCENDING, SORT_DESCENDING } sort_order_t;
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
typedef enum class Direction {
	Up, Down, NoChange
} direction_t;
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
double _atod(string, char base = 10);
long _atoi(string);
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
size_t TieRopes(vector<long>&, size_t);
long MinAbsSum(vector<long>&);
long NumberSolitaire(vector<long>&);
long MaxProfit(vector<long>&);
size_t StockMax(vector<long>&);
string decimal_to_binary(int);
void decimal_to_binary(int decimal, vector<bool>&, size_t width);
size_t binary_gap(long);
void reverse(string&);
void reverseWords(string&);
void RemoveDuplicateCharacters(string&);
bool areAnagrams(string const&, string const &);
size_t FindAnagrams(vector<string> const&, vector<vector<string>>&);
bool SherlockValidString(string const&);
size_t sherlockAndAnagrams(string const&);
size_t sherlockAndCost(vector<size_t>&);
bool isPalindrome(string const&);
bool isPalindrome1(string const&);
bool isPalindrome2(string const&);
string FindBiggestPalindromeSubstring(string const&);
void FindPalindromeSubstrings(string const&, set<string>&);
size_t PalindromeAnagramCount(string const&);
size_t PalindromeAnagramCount1(string const &);
bool AreRotatedStrings(string const &, string const &, size_t);
bool SolvabilityOfTheTilesGame(vector<size_t>&);
void RotateRightArray(vector<int>&, int);
vector<int> RotateLeftArray(vector<int>&, int);
vector<size_t> FindSubString(string const&, string const);
size_t KMPSearch(string const&, string const&);
void KMPTable(string const&, vector<long>&);
void copy_on_write_string();
long fibonacci(long);
string fibonacciModified(long, long, long);
unsigned long long factorial(long);
long SequenceSum(long n);
void MultiplesCount(int, long &, long &);
long FactorialTrailingZeroesCount(long);
long MaxZeroProductBruteForce(vector<int> const&);
long MaxZeroProduct(vector<int> const&, size_t);
void MaxZeroProductTests();
set<string> permute(string const&);
set<vector<long>> permute(vector<long>&);
void BitCombinations(size_t, vector<long> &);
void OrderedMergedCombinations(set<string>&, string&, string&, string);
string insertCharAt(char, string, size_t);
vector<long> insertItemAt(long, vector<long>&, size_t);
void findDistinct(vector<long>&, vector<long>&);
void findPrimes(unsigned long, vector<long>&);
bool isPrime(unsigned long);
size_t CommonPrimeDivisors(vector<long>&, vector<long>&);
unsigned long long findMax(vector<unsigned long long> const&);
void Merge(vector<long> &, vector<long> &);
int BinarySearch(vector<size_t>&, size_t);
int BinarySearchCountUpper(vector<long>&, long, long, long);
int BinarySearchCountLower(vector<long>&, long, long, long);
int BinarySearch(vector<string>&, string&);
void parentheses(vector<string>&, size_t);
void parentheses(vector<string>&, string&, size_t, long, long);
long LongestValidParentheses(string&);
long LongestValidParenthesesWithFixes(string&, size_t k);
template<class T>
void SortStack(MyStack<T> &, MyStack<T> &, sort_order_t order);
long ToggleSign(long);
long absolute(long a);
long SubtractWithPlusSign(long a, long b);
long MultiplyWithPlusSign(long a, long b);
long DivideWithPlusSign(long a, long b);
long divide(long, long);
void AnagramTests();
void PalindromeTests();
void StackTests();
void QueueTests();
void LinkedListTests();
void BinarySearchTests();
void BinarySearchStringTests();
void BinarySearchCountTests();
void SuffixTreeTests();
void PrefixTrieTests();
void TrieTests();
void StringPermutationTests();
void ListPermutationTests();
void GraphTests();
void SortTests();
void KDTreeTests();
void BinaryTreeTests();
void BinarySearchTreeTests();
void MinHeapTests();
void MaxHeapTests();
void MinMaxHeapTests();
void MinHeapifyDown(vector<long>&, size_t);
void MaxHeapifyDown(vector<long>&, size_t);
void SparseNumberTests();
void LongestCommonSubsequenceTests();
template<class URNG>
void TestURNG(URNG&);
void TestRandom();
void GreedyAlgorithmTests();
void Knapsack_CoinChangeTests();
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
size_t SortSwapCount(vector<size_t>&);
void Swap(long &, long &);
long** my2DAlloc(long, long);
long*** my3DAlloc(long, long, long);
long long AddWithoutArithmetic(long long, long long);
string NumberStringSum(string&, string&);
string NumberStringMultiplication(string& num1, string& num2);
void shuffleCards(vector<long> &);
void randomSubset(vector<long> &, size_t count, vector<long> &);
long countDigits(char digit, long n);
void Transform(string &, string&, set<string>&, queue<string>&);
void GetPermutations(string &);
void trim(string &);
size_t sumpairs(vector<long>&, long);
size_t diffpairs(vector<long>&, long);
size_t diffpairs(set<long>&, long);
size_t minDiffPairs(vector<long>&, long);
size_t greaterthansumpairs(vector<long>&, long sum);
string uncompress(string const&);
size_t findLongestContiguousPattern(string&, char c);
string GetRange(vector<long>&);
bool isSparseNumber(long i);
long NextSparseNumber(long number);
long KthNumberWith357PrimeFactors(long);
typedef struct PathResult {
	PathResult() : sum(0), path("") {}
	unsigned long sum;
	string path;
} pathResult_t;
pathResult_t FindMaxPath(vector<vector<unsigned long>>&, size_t, size_t);
bool PathExists(vector<vector<char>>&, size_t, size_t, size_t, size_t, queue<string>&, char obstacle);
vector<string> findShortestPath(int n, int i_start, int j_start, int i_end, int j_end);
bool FindShortestPath(vector<vector<char>>&, size_t r, size_t c, queue<string>&, char dest, char obstacle);
void MatrixDistance(vector<vector<long>>&, size_t, size_t);
void MatrixSort(vector<vector<long>>&);
long MatrixPatternCount(vector<vector<long>>&);
void MatrixSortWithHeap(vector<vector<long>>&);
size_t ConnectedCellsInAGridLinkedList(vector<vector<long>>&);
size_t ConnectedCellsInAGrid(vector<vector<long>>&);
// Start of Sort numbers into consecutive positive/negative numbers
template<typename type>
void sortNumbers(vector<long> &);
template<typename type>
void OrderArrayIntoNegativePositiveSeries(vector<long> &);
void OrderArrayIntoNegativePositiveSeriesTests();
void TestCornerCases();
// End of Sort numbers into consecutive positive/negative numbers
void EqualAverageDivide(vector<long>&, vector<long>&);
bool GetSum(vector<long> &, size_t K, long sum, size_t index, vector<long>&);
bool match(string&, string&);
string EncodeString(string);
string cipher(size_t, size_t, string&);
void FindPattern(string, set<string>&, set<string>&);
string subtract(istream&, istream &);
set<string> intersectionNgram(string&, string&, int n);
vector<int> Increment(vector<int>&);
void *alignedMalloc(size_t bytes, size_t alignment);
void alignedFree(void **p);
vector<string> numbersegments(vector<long>&);
unsigned long long XOR(unsigned long long);
long concat(vector<long>&);
long buildmax(vector<long>&, vector<long>&, size_t);
bool JSONValidation(string);
vector<char> AddVectors(vector<char>&, vector<char>&);
long MaxLengths(vector<string>&);
void ExceptionTest();
size_t LongestAlternatingSubSequence(const vector<long>&, vector<long>&);
size_t bitCount(long);
void PlayTreasureGame();
size_t countPaths(size_t, size_t, size_t, size_t, size_t);
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
size_t LongestIncreasingSubsequence(vector<size_t>&);
size_t LongestIncreasingSubsequenceNlogN(vector<size_t>&);
void IncreasingSequenceTests();
size_t FindSubsequenceRecursive(string&, string&);
size_t FindSubsequenceDynamicProgramming(string&, string&);
size_t shortPalindrome(string&);
void cpluplus17();
long MaxProductOfThree(vector<long>&);
size_t CountDiv(size_t, size_t, size_t);
long ChocolatesByNumbers(long, long);
long getMinimumCost(long, vector<long>&);
long maxMin(long, vector<long>&);
vector<int> freqQuery(vector<vector<int>>&);
string encryption(string&);
vector<size_t> climbingLeaderboard(vector<long>&, vector<long>&);
long calculateMedian(vector<long>&);
string timeInWords(int, int);
size_t beautifulQuadruples(int, int, int, int);
long kruskals(int, vector<long>&, vector<long>&, vector<long>&);
size_t PrimMinimumSpanningTree(size_t, vector<vector<long>>&, long);
void UnbeatenPaths(size_t, vector<vector<long>>&, long, vector<size_t>&);
long getLowestPathCost(size_t g_nodes, vector<long>&, vector<long>&, vector<long>&);
size_t SurfaceArea3D(vector<vector<long>>&);
size_t cutTheTree(vector<size_t>&, vector<vector<size_t>>&);
size_t MinSubGraphDifference(vector<size_t>&, vector<vector<size_t>>&);
long PostmanProblem(vector<long>&, vector<vector<long>>&);
string AlmostSorted(vector<long>&);
size_t LCSLength(string&, string&);
template<typename T>
size_t LCSLength(vector<T>&, vector<T>&);
size_t LCSLength(vector<vector<size_t>>&, string&, string&);
template<typename T>
size_t LCSLength(vector<vector<size_t>>&, vector<T>&, vector<T>&);
string LCSBackTrack(vector<vector<size_t>>&, string&, string&, size_t, size_t);
template<typename T>
vector<T> LCSBackTrack(vector<vector<size_t>>&, vector<T>&, vector<T>&, size_t, size_t);
void LCSPrintDiff(vector<vector<size_t>>&, string&, string&, long, long);
template<typename T>
void LCSPrintDiff(vector<vector<size_t>>&, vector<T>&, vector<T>&, long, long);
set<vector<size_t>> CoinChange(long, vector<size_t>&);
set<vector<size_t>> Knapsack(long, vector<size_t>&);
size_t UnboundedKnapsack(long, vector<size_t>&);
string DecryptPassword(string&);
unsigned long long substrings(string&);
size_t steadyGene(string&);
size_t TwoCrosses(vector<string>&);
vector<long> absolutePermutation(size_t, size_t);
vector<string> bomberMan(size_t, vector<string>&);
bool gridSearch(vector<string>&, vector<string>&);
size_t SnakesAndLaddersGame(vector<vector<size_t>>&, vector<vector<size_t>>&);
size_t lengthOfLongestSubstring(string&);
string zigzagconvert(string&, size_t);
string numberToRoman(size_t);
double median(vector<long>&, vector<long>&);