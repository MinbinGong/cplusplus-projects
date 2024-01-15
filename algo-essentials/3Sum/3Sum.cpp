// 3Sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> threeSumClosest(vector<int>& nums, int target) {
  sort(nums.begin(), nums.end());

  int diff = INT_MAX;
  for (int i = 0; i < nums.size(); i++) {
    int low = i + 1, high = nums.size() - 1;
    while (low < high) {
      int sum = nums[i] + nums[low] + nums[high];
      if (abs(sum - target) < abs(diff)) {
        diff = target - sum;
      }

      if (sum < target) {
        ++low;
      } else {
        --high;
      }
    }
  }

  return target - diff;
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
