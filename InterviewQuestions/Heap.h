#pragma once
#include "tree.h"
enum class HeapType {MinHeap, MaxHeap, MinMaxHeap};

template<class T>
class Heap : public Tree<T>
{
private:
	using Tree<T>::m_root;
	HeapType type_;
	shared_ptr<Node<T>> FindEmptyLeafParent();
	shared_ptr<Node<T>> FindLastLeaf();
	void HeapifyUp(shared_ptr<Node<T>>&, unsigned long level = 0);
	void HeapifyDown(shared_ptr<Node<T>>&);
	void swap(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
public:
	using Tree<T>::GetNodes;
	using Tree<T>::InsertItem;
	using Tree<T>::MaxDepth;
	using Tree<T>::Tree;
	Heap(HeapType = HeapType::MinHeap);
	explicit Heap(T, HeapType type = HeapType::MinHeap);
	Heap(shared_ptr<Node<T>>&, HeapType type = HeapType::MinHeap);
	Heap(vector<T>&, HeapType type = HeapType::MinHeap);
	virtual void InsertNode(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	shared_ptr<Node<T>> pop();
	shared_ptr<Node<T>> front();
	void Serialize(vector<T>&);
};