// 4Sum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

vector<vector<int>> twoSumII(vector<int>& nums, int start, int target) {
  vector<vector<int>> result{};
  unordered_set<int> s;
  for (auto i = start; i < nums.size(); i++) {
    if (result.empty() || result.back()[1] != nums[i]) {
      int complement = target - nums[i];
      if (s.count(complement)) {
        result.push_back({complement, nums[i]});
      }
    }
    s.insert(nums[i]);
  }
}

vector<vector<int>> kSum(vector<int>& nums, int start, int target, int k) {
  if (2 == k) {
    return twoSumII(nums, start, target);
  }

  vector<vector<int>> result{};
  if (start + k > nums.size() || nums[start] * k > target || target > nums.back() * k) {
    return result;
  }

  for (int i = start; i < nums.size(); i++) {
    if (i == start || nums[i - 1] != nums[i]) {
      for (auto& list : kSum(nums, i + 1, target - nums[i], k - 1)) {
        list.push_back(nums[i]);
        result.push_back(list);
      }
    }
  }
  return result;
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {
  sort(nums.begin(), nums.end());
  return kSum(nums, 0, target, 4);
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
