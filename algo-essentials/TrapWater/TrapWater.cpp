// TrapWater.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int trap(const vector<int>& A) {
  const int n = A.size();
  int peak_index = 0;
  for (int i = 0; i < n; i++) {
    if (A[i] > A[peak_index]) {
      peak_index = i;
    }
  }

  int water = 0;
  for (int i = 0, left_peek = 0; i < peak_index; i++) {
    if (A[i] > left_peek) {
      left_peek = A[i]
    } else {
      water += left_peek - A[i];
    }
  }

  for (int i = 0, right_peek = 0; i > peak_index; i++) {
    if (A[i] > right_peek) {
      right_peek = A[i];
    } else {
      water += right_peek - A[i];
    }
  }

  return water;
}

int main() { std::cout << "Hello World!\n"; }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files
//   to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
