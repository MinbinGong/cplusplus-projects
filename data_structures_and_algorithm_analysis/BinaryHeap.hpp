#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include <vector>
using namespace std;

template <typename Comparable> class BinaryHeap {
private:
  int currentSize;
  vector<Comparable> array;

private:
  void buildHeap();
  void percolateDown(int hole) {
    int child;
    Comparable tmp = std::move(array[hole]);

    for (; hole * 2 <= currentSize; hole = child) {
      child = hole * 2;
      if (child != currentSize && array[child + 1] < array[child]) {
        ++child;
      }

      if (array[child] < tmp) {
        array[hole] = std::move(array[child]);
      } else {

        break;
      }
    }
    array[hole] = std::move(tmp);
  }

public:
  explicit BinaryHeap(int capacity = 100) {}
  explicit BinaryHeap(const vector<Comparable> &items)
      : array(items.size() + 10), currentSize{items.size()} {
    for (size_t i = 0; i < items.size(); i++) {
      array[i + 1] = items[i];
    }
    buildHeap();
  }

  bool isEmpty() const;
  const Comparable &findMin() const;

  void insert(const Comparable &x) {
    if (currentSize == array.size() - 1) {
      array.resize(array.size() * 2);
    }

    int hole = ++currentSize;
    Comparable copy = x;

    array[0] = std::move(copy);
    for (; x < array[hole / 2]; hole /= 2) {
      array[hole] = std::move(array[hole / 2]);
    }

    array[hole] = std::move(array[0]);
  }

  //   void insert(Comparable &&x);
  void deleteMin() {
    if (isEmpty()) {
      throw UnderflowException{};
    }

    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
  }

  void deleteMin(Comparable &minItem) {
    if (isEmpty()) {
      throw UnderflowException{};
    }

    minItem = std::move(array[1]);
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
  }

  void makeEmpty();
};
#endif