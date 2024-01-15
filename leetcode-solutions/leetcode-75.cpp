// leetcode 75. Sort Colors
// Given an array nums with n objects colored red, white, or blue, sort them in-place
// so that objects of the same color are adjacent, with the colors in the order red, white,
// and blue. We will use the integers 0, 1, and 2 to represent the color red, white, and blue,
// respectively.
// You must solve this problem without using the library's sort function.

#include <algorithm>
#include <vector>
using namespace std;

void sort_colors(vector<int> &nums) {
  unsigned int low{0}, mid{0}, high{nums.size() - 1};

  int blue = 0, white = 1, red = 2;
  while (mid <= high) {
    if (nums[mid] == blue) {
      swap(nums[mid], nums[low]);
      low++;
      mid++;
    } else if (nums[mid] == red) {
      swap(nums[mid], nums[high]);
      high--;
    } else {
      mid++;
    }
  }
}