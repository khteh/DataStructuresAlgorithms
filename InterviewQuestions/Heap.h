#pragma once
#include "tree.h"
enum HeapType {MinHeap, MaxHeap, MinMaxHeap};

template<class T>
class Heap : public Tree<T>
{
private:
	HeapType type_;
	shared_ptr<Node<T>> FindEmptyLeafParent();
	shared_ptr<Node<T>> FindLastLeaf();
	void HeapifyUp(shared_ptr<Node<T>>, unsigned long level = 0);
	void HeapifyDown(shared_ptr<Node<T>>);
	void swap(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
public:
	Heap(HeapType = MinHeap);
	explicit Heap(T, HeapType type = MinHeap);
	Heap(shared_ptr<Node<T>>, HeapType type = MinHeap);
	Heap(vector<T>&, HeapType type = MinHeap);
	virtual void InsertNode(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
	shared_ptr<Node<T>> pop();
	shared_ptr<Node<T>> front();
	void Serialize(vector<T>&);
};