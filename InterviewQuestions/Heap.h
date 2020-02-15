#pragma once
#include "tree.h"
enum HeapType {MinHeap, MaxHeap, MinMaxHeap};

template<class T>
class Heap : public Tree<T>
{
private:
	HeapType type_;
	Node<T>* FindEmptyLeafParent();
	Node<T>* FindLastLeaf();
	void HeapifyUp(Node<T> *, unsigned long level = 0);
	void HeapifyDown(Node<T> *);
	void swap(Node<T>*, Node<T>*);
public:
	Heap(HeapType = MinHeap);
	explicit Heap(T, HeapType type = MinHeap);
	Heap(Node<T> *, HeapType type = MinHeap);
	Heap(vector<T>&, HeapType type = MinHeap);
	virtual void InsertNode(Node<T> *, Node<T> *);
	Node<T>* pop();
	Node<T>* front();
	void Serialize(vector<T>&);
};