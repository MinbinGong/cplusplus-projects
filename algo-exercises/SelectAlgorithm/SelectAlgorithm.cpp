// SelectAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

void swapElement(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int a[], int low, int high) {
  int pivot = a[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (a[j] < pivot) {
      i++;
      swapElement(&a[i], &a[j]);
    }
  }
  swapElement(&a[i + 1], &a[high]);
  return i + 1;
}

int partition2(int a[], int left, int right) {
  int pivot{a[right]};
  int i{left};

  for (size_t j = left; j < right; j++) {
    if (a[j] < pivot) {
      swapElement(&a[i], &a[j]);
      i++;
    }
  }
  swapElement(&a[i], &a[right]);
  return i;
}

int main() {
  int a[10] = {4, 3, 6, 11, 26, 23, 32, 1, 9, 5};

  std::cout << partition2(a, 0, 9) << std::endl;

  for (const auto i : a) std::cout << i << ' ';
  std::cout << std::endl;

  return 0;
}