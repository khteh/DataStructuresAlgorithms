#pragma once
#include "Node.h"
using namespace std;
/*
3 types of tree traversal:
In-Order: Left node, current node, Right node
Pre-Order: Current node, Left node, Right node
Post-Prder: Left node, right node, current node
*/
/*
Binary Tree:
			50
		-100   60
			0      100
		-50    10  75   150

Binary Search Tree:
			50
		0			100
	-50	   10	75		150
-100			60
*/
enum class TreeType
{
	Binary,
	BinarySearch
};
enum class TraversalType
{
	PreOrder,
	PostOrder
};
template <typename T>
class Tree
{
private:
	vector<size_t> _levelNodeCount;
	stack<shared_ptr<Node<T>>> _minStack, _maxStack;

protected:
	shared_ptr<Node<T>> _root;
	void _Swap(Tree &);
	void _Clear(shared_ptr<Node<T>> &);
	void _PrintColumns(const shared_ptr<Node<T>> &, long, map<long, shared_ptr<vector<T>>> &);
	void _AddToColumn(T, long, map<long, shared_ptr<vector<T>>> &);
	void _Split(string const &s, char delim, vector<string> &elems);
	void _RecoverBinarySearchTree(const shared_ptr<Node<T>> &, shared_ptr<Node<T>> &, shared_ptr<Node<T>> &, shared_ptr<Node<T>> &)
		requires arithmetic_type<T>;
	shared_ptr<Node<T>> _AddToTree(shared_ptr<Node<T>>, vector<T> &, long, long);
	shared_ptr<Node<T>> _AddToTree(vector<T> &);
	shared_ptr<Node<T>> _FindNode(const shared_ptr<Node<T>> &, T item);
	shared_ptr<Node<T>> _Copy(const shared_ptr<Node<T>> &, map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> &);
	shared_ptr<Node<T>> _LeftMostChild(shared_ptr<Node<T>> &);
	bool _IsValidBST(const shared_ptr<Node<T>> &) const;
	bool _Covers(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);
	void _FindSum(const shared_ptr<Node<T>> &, const T, long, vector<T>, vector<string> &)
		requires arithmetic_type<T>;
	vector<string> _GetRoot2LeafNumbers(const shared_ptr<Node<T>> &);
	size_t _Count(const shared_ptr<Node<T>> &) const;
	T _MinDiffInBST(shared_ptr<Node<T>>, shared_ptr<Node<T>>) const
		requires arithmetic_type<T>;
	T _Min(const shared_ptr<Node<T>> &) const;
	T _Max(const shared_ptr<Node<T>> &) const;
	T _MaxPathSum(const shared_ptr<Node<T>> &, T &)
		requires arithmetic_type<T>;
	vector<size_t> _GetLevelNodeCount(const shared_ptr<Node<T>> &, size_t);
	shared_ptr<Node<T>> _ToLinkedList(const shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> _BuildTreePreOrder(vector<T> &, vector<T> &, long, long, long);
	shared_ptr<Node<T>> _BuildTreePostOrder(vector<T> &, vector<T> &, long, long, long);
	shared_ptr<Node<T>> _CommonAncestor(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);

public:
	Tree();
	Tree(Tree<T> const &);	   // Copy constructor
	Tree(Tree<T> &&) noexcept; // Move constructor
	explicit Tree(T);
	Tree(vector<T> &, TreeType);
	Tree(TraversalType, vector<T> &preorder, vector<T> &inorder);
	Tree(shared_ptr<Node<T>> &);
	virtual ~Tree();
	void Clear();
	void InsertItem(T);
	void PrintTreeColumns();
	void LoadData(vector<T> &, TreeType);
	void Serialize(const shared_ptr<Node<T>> &, vector<T> &);
	void GetNodes(map<size_t, vector<shared_ptr<Node<T>>>> &, long level = -1 /* Get nodes of all levels by default*/) const;
	void FindSum(const shared_ptr<Node<T>> &, const T, vector<string> &)
		requires arithmetic_type<T>;
	virtual void PrintTree() const;
	virtual void InsertNode(shared_ptr<Node<T>> &, shared_ptr<Node<T>> &);

	// Tree<T> &operator=(Tree<T> const &); // Copy assignment operator
	// Tree<T> &operator=(Tree<T> &&); // Move assignment operator
	/*
	https://stackoverflow.com/questions/64378721/what-is-the-difference-between-the-copy-constructor-and-move-constructor-in-c
	The above 2 operators can be implemented as 1 operator, like below.
	This allows the caller to decide whether to construct the rhs parameter
	using its copy constructor or move constructor...
	*/
	Tree<T> &operator=(Tree<T>);
	shared_ptr<Node<T>> Root() const;
	shared_ptr<Node<T>> FindNode(T);
	shared_ptr<Node<T>> ToLinkedList();
	shared_ptr<Node<T>> InOrderSuccessor(shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> CommonAncestor(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> CommonAncestor1(shared_ptr<Node<T>> &, shared_ptr<Node<T>> &);
	bool operator==(const Tree<T> &) const;
	bool IsValidPreOrderTreeSerialization(string const &);
	bool HasNextMin() const;
	bool HasNextMax() const;
	bool IsBalancedTree() const;
	bool SubTree(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);
	bool MatchTree(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &) const;
	bool IsValidBST() const;
	bool RecoverBinarySearchTree()
		requires arithmetic_type<T>;
	size_t Count() const;
	size_t MinDepth(const shared_ptr<Node<T>> &) const;
	size_t MaxDepth(const shared_ptr<Node<T>> &) const;
	T NextMin();
	T NextMax();
	T kthSmallest(size_t);
	T kthLargest(size_t);
	T SumRoot2LeafNumbers();
	T Min() const;
	T Max() const;
	T MinSubTreesDifference() const
		requires arithmetic_type<T>;
	T MinDiffInBST() const
		requires arithmetic_type<T>;
	T TreeArithmeticTotal(shared_ptr<Node<string>>)
		requires arithmetic_type<T>;
	T MaxPathSum()
		requires arithmetic_type<T>;
	vector<size_t> GetLevelNodeCount();
};