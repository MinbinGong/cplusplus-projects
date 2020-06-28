#pragma once

class MinHeap
{
public:
	explicit MinHeap(unsigned int capacity);
	~MinHeap();

public:
	int top();
	void popMin();
	void insert(int elem);

private:
	void heapifyBottomUp();
	void heapifyTopDown();
	int parent(int index);
	int leftChild(int index);
	int rightChild(int index);

private:
	unsigned int mCapacity;
	unsigned int mHeapSize;
	int *arr;
};

