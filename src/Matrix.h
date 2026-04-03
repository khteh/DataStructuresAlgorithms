#pragma once
#include "Position.h"
#include "Sort.h"
#include "LinkedList.h"
#include "GenericConstraints.h"
using namespace std;
namespace ranges = std::ranges;
typedef struct PathResult
{
	PathResult() : sum(0), path("") {}
	long sum;
	string path;
} pathResult_t;

template <typename T>
class Matrix
{
private:
	T _active, _inactive;
	vector<vector<T>> _grid;
	vector<int> _steps = {0, 1, 0, -1, 0}, _diagonals = {-1, -1, 1, 1, -1};
	size_t DisconnectCell(size_t, size_t);
	size_t DisconnectCellAllDirections(size_t, size_t, set<string> &);
	size_t DisconnectCellAllDirections_LinkedList(size_t, size_t, shared_ptr<Node<string>> &);
	size_t DisconnectCellAllDirections_DisjointSet(T, size_t, size_t, DisJointSet<T> &, map<T, size_t> &);

public:
	Matrix();
	Matrix(vector<vector<T>> &, T, T);
	Matrix(vector<vector<T>> &);
	void MatrixDistance(vector<vector<T>> &, size_t, size_t);
	void MatrixSort(vector<vector<T>> &);
	T MatrixPatternCount(vector<vector<T>> const &);
	void MatrixSortWithHeap(vector<vector<T>> &);
	T Sum(vector<vector<size_t>> &);
	T LargestSumSubmatrix(vector<vector<size_t>> &);
	bool SearchMatrix(T, vector<vector<T>> const &) const;
	bool SearchMatrix1(T, vector<vector<T>> const &) const;
	bool SearchMatrixRow(vector<vector<T>> const &, T, size_t, T, T) const;
	bool SearchMatrixCol(vector<vector<T>> const &, T, size_t, T, T) const;
	void RotateMatrix90DegressClockwise(vector<vector<T>> &);
	void RotateMatrixRTimesAntiClockwise(vector<vector<T>> &, size_t);
	vector<T> MatrixSprialOrder(vector<vector<T>> const &);
	T ChessQueensMoveCount(T, T /*[1,rows]*/, T /*[1,cols]*/, vector<vector<size_t>> const &);
	void ChessQueensPlacements(vector<string> &, size_t, vector<vector<string>> &);
	T GridlandMetro(T, T, vector<vector<T>> const &);
	T SurfaceArea3D(vector<vector<T>> const &);
	size_t TwoCrosses(vector<string> const &);
	size_t LargestPerimeter(vector<string> const &);
	vector<string> BomberMan(size_t, vector<string> const &);
	T MaxQuadrantSum(vector<vector<T>> const &);
	bool ContainersBallsSwap(vector<vector<T>> const &);
	pathResult_t FindMaxPath(vector<vector<T>> &, size_t, size_t)
		requires integral_type<T>;
	size_t PathExists(vector<vector<char>> &, size_t, size_t, size_t, size_t, stack<position_t> &, char);
	size_t FindShortestPath(vector<vector<char>> &, size_t, size_t, stack<position_t> &, char, char);
	size_t LargestGridCluster_BFS();
	size_t LargestGridCluster_DFS();
	size_t LargestGridCluster_DisjointSet_BFS();
	size_t LargestGridCluster_DisjointSet_DFS();
	size_t LargestGridCluster_LinkedList_BFS();
	size_t LargestGridCluster_LinkedList_DFS();
	size_t GridClusterCountBFS();
	size_t GridClusterCountDFS();
};