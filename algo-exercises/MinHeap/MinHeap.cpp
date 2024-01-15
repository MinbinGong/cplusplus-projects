#include "MinHeap.h"

MinHeap::MinHeap(unsigned int capacity) : mHeapSize(0), mCapacity(capacity) { arr = new int[capacity]; }

MinHeap::~MinHeap() {
  if (mHeapSize == 0 && arr != nullptr) {
    delete[] arr;
  }
}

int MinHeap::top() { return 0; }

void MinHeap::popMin() {}

void MinHeap::insert(int elem) {}

void MinHeap::heapifyBottomUp() {}

void MinHeap::heapifyTopDown() {}

int MinHeap::parent(int index) { return 0; }

int MinHeap::leftChild(int index) { return 0; }

int MinHeap::rightChild(int index) { return 0; }
