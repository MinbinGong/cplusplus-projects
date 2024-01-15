// RemoveDuplicates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

// Remove Duplicates from Sorted Array
// Time Complexity: O(n)£¬Space Complexity: O(1)
int removeDuplicates(std::vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }

  int slow = 0;
  for (int fast = 0; fast < nums.size(); fast++) {
    if (nums[fast] != nums[slow]) {
      nums[++slow] = nums[fast];
    }
  }
  return slow + 1;
}

// Remove Duplicates from Sorted Array II
// Time complexity: O(n), Space Complexity: O(1)'
int removeDuplicates2(std::vector<int>& nums) {
  const int N = 2;
  if (nums.size() <= N) {
    return nums.size();
  }

  unsigned int slow{N};
  for (unsigned int fast = 0; fast < nums.size(); fast++) {
    if (nums[fast] != nums[slow - N]) {
      nums[slow++] = nums[fast];
    }
  }
  return slow;
}

int removeElement(std::vector<int>& nums, int target) {
  unsigned int slow = 0;
  for (unsigned fast = 0; fast < nums.size(); fast++) {
    if (nums[fast] != target) {
      nums[slow++] = nums[fast];
    }
  }
  return slow;
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
