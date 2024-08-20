#pragma once
#include <limits>
#include <memory>
#include <utility>
#include <thread>
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
#include <cstring>
#include <ranges>
#include <variant>
#include <typeinfo>
#include <limits.h>
#include <cmath>
#include <chrono>
#include <concepts>
#include "oneapi/tbb.h"
#include "Arithmetic.h"
#include "Dijkstra.h"
#include "NameHidingExample.h"
#include "Singleton.h"
#include "Graph.h"
#include "Greedy.h"
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
#include "FenwickTree.h"
#include "LinkedList.h"
#include "CircularLinkedList.h"
#include "Square.h"
#include "TreasureGame.h"
#include "FunctionObject.h"
#include "IntervalMap.h"
#include "DisJointSet.h"
#include "Edge.h"
#include "LRUCache.h"
#include "Search.h"
#include "Twitter.h"
#include "Matrix.h"
#include "ListRangeSum.h"
#include "LongestCommonSubsequence.h"
#include "Knapsack.h"
#include "Palindrome.h"
#include "Range.h"
#include "Sort.h"
#include "Poker.h"
#include "VariantVisitor.h"
#include "GameTheory.h"
#include "Permutation.h"
using namespace std;
using namespace chrono;
using namespace oneapi::tbb;
typedef union
{
	long l;
	float f;
} thirty_two_bit;
typedef union
{
	long long ll;
	double d;
} sixty_four_bit;
typedef union
{
	long double ll;
	double d;
} one_two_eight_bit;
typedef struct ZeroFactors
{
	long two, five, value, minValue;
	bool operator>(const ZeroFactors &other) const
	{
		return max(two, five) == max(other.two, other.five) ? value > other.value : max(two, five) > max(other.two, other.five);
	}
	bool operator<(const ZeroFactors &other) const
	{
		return min(two, five) == min(other.two, other.five) ? value < other.value : min(two, five) < min(other.two, other.five);
	}
} zerofactors_t;
typedef struct ZeroFactorsTwoCount
{
	long count, fives, value, index;
	bool operator>(const ZeroFactorsTwoCount &other) const
	{
		if (count == other.count)
			return (fives == other.fives) ? value > other.value : fives > other.fives;
		else
			return count > other.count;
	}
} zerofactorstwocount_t;
typedef struct ZeroFactorsFiveCount
{
	long count, twos, value, index;
	bool operator>(const ZeroFactorsFiveCount &other) const
	{
		if (count == other.count)
			return (twos == other.twos) ? value > other.value : twos > other.twos;
		else
			return count > other.count;
	}
} zerofactorsfivecount_t;
typedef struct Position
{
	Position() : row(-1), col(-1) {}
	Position(size_t r, size_t c) : row(r), col(c) {}
	size_t row;
	size_t col;
} position_t;
typedef struct ZigZagEscape
{
	size_t index;
	int value;
	ZigZagEscape(size_t i, int v) : index(i), value(v) {}
	bool operator<(const ZigZagEscape &other) const
	{
		return value < other.value;
	}
	bool operator>(const ZigZagEscape &other) const
	{
		return value < other.value;
	}
} zigzag_t;
typedef struct buildmax_comparator
{
	bool operator()(string lhs, string rhs) const
	{
		ostringstream oss1, oss2;
		oss1 << lhs << rhs;
		oss2 << rhs << lhs;
		// True: lhs goes before rhs; False: lhs goes after rhs
		// lhsrhs < rhslhs : lhs goes after rhs
		// lhsrhs > rhslhs : lhs goes before rhs
		return oss1.str() > oss2.str();
	}
} buildmax_comparator_t;
class VariantException
{
public:
	explicit VariantException(long i)
	{
		throw long(i);
	}
	operator long() { throw long(123); }
};
void cpp20readonlyranges();
void cpp20ranges();
void cpp20variants();
float MachineEpsilon(float value);
float FloatMachineEpsilonApproximation();
double MachineEpsilon(double value);
double MachineEpsilonApproximation();
void testPointerReference(int *&);
long Min(long, long);
long Max(long, long);
long gcd(long a, long b);
long gcd_euclidean(long a, long b);
long lcm(long a, long b);
unsigned long long _atoull(string, char base = 10);
double _atod(string, char base = 10);
long _atoi(string);
double round(double num, int n);
long double Factorial(long);
long double FactorialDynamicProgramming(long);
long FactorialTrailingZeroesCount(long);
long SequenceSum(long);
long double BinomialCoefficients(size_t, size_t);
long double MultinomialCoefficients(size_t, vector<size_t> const &);
void MultiplesCount(int, long &, long &);
long MaxZeroProductBruteForce(vector<int> const &);
long MaxZeroProduct(vector<int> const &, size_t count = 3);
bool isUniqueString(string const &);
vector<string> findUnique(vector<string> const &, vector<string> const &);
bool CanShuffleWithoutRepeat(string &);
long ConsecutiveMaximumSumOfFactors(vector<zerofactors_t> &, vector<zerofactors_t> &, int);
size_t CountDistinctSlices(vector<long> &);
size_t CountTriangles(vector<long> &);
long MinAbsSum(vector<long> &);
string decimal_to_binary(long);
long binary_to_decimal(string const &);
void decimal_to_binary(long, vector<bool> &, size_t);
size_t binary_gap(long);
void reverse(string &);
void reverseWords(string &);
void reverseWordsTrimmed(string &);
void RemoveDuplicateCharacters(string &);
void RemoveDuplicateCharactersLexicographicalOrder(string &);
bool AreAnagrams(string const &, string const &);
size_t FindAnagrams(vector<string> const &, vector<vector<string>> &);
bool SherlockValidString(string const &);
size_t SherlockAndAnagrams(string const &);
bool AreRotatedStrings(string const &, string const &, size_t);
bool SolvabilityOfTheTilesGame(vector<size_t> &);
void RotateRightArray(vector<int> &, int);
vector<int> RotateLeftArray(vector<int> &, int);
vector<size_t> FindSubString(string const &, string const);
void copy_on_write_string();
long double Fibonacci(long);
long double FibonacciDynamicProgramming(long);
string FibonacciModified(long, long, long);
string FibonacciModifiedDynamicProgramming(long, long, long);
void BitCombinations(size_t, vector<long> &);
vector<size_t> grayCode(size_t);
void OrderedMergedCombinations(set<string> &, string const &, string const &, string);
void numberCombinations1(size_t, size_t, size_t, vector<size_t> &, vector<vector<size_t>> &);
void numberCombinations(size_t, size_t, vector<vector<size_t>> &);
string insertCharAt(char, string, size_t);
void findDistinct(vector<long> &, vector<long> &);
void findPrimes(unsigned long, vector<long> &);
bool isPrime(unsigned long);
size_t CommonPrimeDivisors(vector<long> &, vector<long> &);
unsigned long long findMax(vector<unsigned long long> const &);
void Merge(vector<long> &, vector<long> &);
void Parentheses(vector<string> &, size_t);
void Parentheses(vector<string> &, string &, size_t, long, long);
long LongestValidParentheses(string const &);
long LongestValidParenthesesWithFixes(string const &, size_t k);
vector<long> diffWaysToCompute(string);
void KDTreeTests();
template <typename URNG>
void TestURNG(URNG &);
void TestRandom();
void MinHeapifyDown(vector<long> &, size_t);
void MaxHeapifyDown(vector<long> &, size_t);
long countInversions(vector<long> &);
size_t MergeCountInversions(vector<long> &, vector<long> &, size_t, size_t, size_t);
void DutchPartitioning(vector<long> &, long);
long **my2DAlloc(long, long);
long ***my3DAlloc(long, long, long);
void shuffleCards(vector<long> &);
void randomSubset(vector<long> &, size_t, vector<long> &);
size_t CountDigits(char, size_t);
size_t CountNumbersWithUniqueDigits(size_t);
size_t Count1Bits(long);
void WordsLadder(string const &, string const &, set<string> &, vector<string> &);
void trim(string &);
size_t minDiffPairs(vector<long> &, long);
string uncompress(string const &);
size_t findLongestContiguousPattern(string &, char);
string GetRange(vector<long> &);
vector<vector<long>> MergeIntervals(vector<vector<long>> &);
bool IsSparseNumber(long);
long NextSparseNumber(long);
long KthNumberWith357PrimeFactors(long);
typedef struct PathResult
{
	PathResult() : sum(0), path("") {}
	unsigned long sum;
	string path;
} pathResult_t;
pathResult_t FindMaxPath(vector<vector<size_t>> &, size_t, size_t);
bool PathExists(vector<vector<char>> &, size_t, size_t, size_t, size_t, queue<string> &, char);
vector<string> findShortestPath(int, int, int, int, int);
bool FindShortestPath(vector<vector<char>> &, size_t, size_t, queue<string> &, char, char);
size_t ConnectedCellsInAGridLinkedList(vector<vector<long>> &);
size_t ConnectedCellsInAGrid(vector<vector<long>> &);
bool WordExistsInGrid(vector<vector<char>> &, string const &);
bool WordExistsInGrid(vector<vector<char>> &, string const &, long, long, size_t);
void EqualAverageDivide(vector<long> &, vector<long> &);
bool GetSum(vector<long> &, size_t K, long sum, size_t index, vector<long> &);
bool match(string const &, string const &);
string EncodeString(string);
string Cipher(size_t, size_t, string const &);
void FindPattern(string, set<string> &, set<string> &);
string subtract(istream &, istream &);
set<string> intersectionNgram(string const &, string const &, int n);
vector<int> Increment(vector<int> &);
void *alignedMalloc(size_t bytes, size_t alignment);
void alignedFree(void **p);
vector<string> numbersegments(vector<long> &);
long concat(vector<long> &);
string buildmax(vector<size_t> &);
bool JSONValidation(string);
vector<char> AddVectors(vector<char> &, vector<char> &);
long MaxLengths(vector<string> &);
void ExceptionTest();
void PlayTreasureGame();
size_t countPaths(size_t, size_t, size_t, size_t, size_t);
vector<shared_ptr<Node<string>>> shortest_cycle_path(shared_ptr<Node<string>>);
int findMinFlip(vector<int> &);
bool IsValidMatrix(vector<vector<char>> const &);
size_t ZigZagEscape(vector<long> &);
size_t ZigZagEscape(vector<long> &, set<string> &);
vector<string> ZigZagEscape(vector<long> &, vector<long> &, size_t lIndex, size_t rIndex, long current, bool dir);
size_t IncreasingSequences(vector<long> &, vector<long> &);
size_t LongestIncreasingSubsequenceNlogN(vector<size_t> &);
size_t LongestDecreasingSubsequenceNlogN(vector<size_t> &);
bool IncreasingTriplet(vector<size_t> &);
size_t FindSubsequenceRecursive(string const &, string const &);
size_t FindSubsequenceDynamicProgramming(string const &, string const &);
void cpluplus17();
long MaxProductOfThree(vector<long> &);
size_t CountDiv(size_t, size_t, size_t);
long ChocolatesByNumbers(long, long);
vector<int> freqQuery(vector<vector<int>> &);
string encryption(string &);
vector<size_t> ClimbLeaderBoard(vector<long> &, vector<long> &);
long CalculateMedian(vector<long> &);
string TimeInWords(size_t, size_t);
size_t BeautifulQuadruples(long, long, long, long);
long kruskals(int, vector<long> &, vector<long> &, vector<long> &);
long getLowestPathCost(size_t g_nodes, vector<long> &, vector<long> &, vector<long> &);
size_t PostmanProblem(vector<size_t> &, vector<vector<size_t>> &);
string DecryptPassword(string const &);
unsigned long long substrings(string const &);
vector<string> bomberMan(size_t, vector<string> &);
size_t LengthOfLongestUniqueSubstring(string const &);
string ZigZagConvert(string const &, size_t);
string numberToRoman(size_t);
double median(vector<long> &, vector<long> &);
long BasicCalculator(string const &);
vector<long> productExceptSelf(vector<long> &);
size_t hIndex(vector<size_t> &);
void PhoneKeyLetters(string const &, vector<string> &);
bool WordBreakDynamicProgramming(string const &, set<string> const &);
void WordBreakDynamicProgramming(string const &, set<string> const &, vector<string> &);
vector<string> WordBreakDFS(string const &, set<string> const &);
vector<string> WordBreakDFS(string const &, set<string> const &, map<string, vector<string>> &);
string GetHint(string const &, string const &);
size_t LargestNumberCompositionProductWithDynamicProgramming(size_t);
vector<string> FindItinerary(vector<vector<string>> &, string const &);
void EulerianPath(string, map<string, multiset<string>> &, vector<string> &);
size_t EggDrops(size_t, size_t);
vector<string> fizzBuzz(size_t);
vector<long> UnbeatenPaths(size_t, vector<vector<size_t>> &, size_t);
string RoadsInHackerland(size_t, vector<vector<size_t>> &);
string RoadsInHackerland1(size_t, vector<vector<size_t>> &);
string RoadsInHackerland2(size_t, vector<vector<size_t>> &);
bool Abbreviation(string const &, string const &);
typedef struct TowerOfHanoiState
{
	TowerOfHanoiState() : state(0), moves(0) {}
	TowerOfHanoiState(unsigned long long s, size_t m) : state(s), moves(m) {}
	unsigned long long state;
	size_t moves;
} towerofhanoi_state_t;
int ResetTowerOfHanoi(size_t, vector<size_t> const &);
long double VectorSlicesSum(vector<long double> &);
long SteadyGene(string const &);
size_t IntervalSelection(vector<vector<size_t>> &);
string TwentyFourHourTimeConversion(string const &);
vector<long> KaprekarNumbers(long, long);
size_t kMarsh(vector<string> &);
size_t MatrixPerimeter(vector<vector<size_t>> &, vector<string> &);
bool HappyLadyBugs(string const &);
size_t PowerSum(size_t, size_t, size_t i = 1);
string MorganAndString(string const &, string const &);
unsigned long long DistinctPairs(size_t, vector<vector<long>> const &);
size_t CountArray(size_t, size_t, size_t);
void Z(vector<size_t> &, string const &);
size_t ActivityNotifications(vector<size_t> const &, size_t);
size_t ActivityNotifications1(vector<size_t> &, size_t);
size_t ActivityNotifications2(vector<size_t> const &, size_t);
string NextBiggerString(string &);