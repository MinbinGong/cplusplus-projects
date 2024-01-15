#include <vector>

void siftDown(std::vector<int>& A, int end, int index) {
  if (index < 0 || index >= end) {
    return;
  }

  int child = 2 * index + 1;
  while (child < end) {
    if (child + 1 < end && A[child + 1] > A[child]) {
      ++child;
    }
    if (A[index] > A[child]) {
      break;
    }

    std::swap(A[index], A[child]);
    index = child;
    child = 2 * index + 1;
  }
}

void heapify(std::vector<int>& A) {
  for (size_t i = A.size() / 2 - 1; i >= 0; i--) {
    siftDown(A, A.size(), i);
  }
}

int findKthLargest(std::vector<int>& A, int k) {
  heapify(A);

  int size = A.size();
  for (size_t i = 1; i < k; i++) {
    std::swap(A[0], A[size - 1]);
    --size;
    siftDown(A, size, 0);
  }

  return A[0];
}