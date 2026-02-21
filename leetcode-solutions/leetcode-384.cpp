/*
 * Shuffle an Array
 *
 * Given an integer array nums, design an algorithm to randomly shuffle the array. All permutations of the array should be equally likely as a result of the shuffling.
 * 
 * Implement the Solution class:
 * 
 * Solution(int[] nums) Initializes the object with the integer array nums.
 * int[] reset() Resets the array to its original configuration and returns it.
 * int[] shuffle() Returns a random shuffling of the array.
 * 
 */
#include <random>
#include <vector>
using namespace std;

vector<int> shuffle(vector<int>& origin) {
  if (origin.empty()) {
    return {};
  }

  vector<int> shuffled(origin);
  int n = shuffled.size();
  // for (int i = n - 1; i >= 0; --i) {
  //   swap(shuffled[i], shuffled[rand() % (i + 1)]);
  // }
  for (int i = 0; i < n; ++i) {
    swap(shuffled[i], shuffled[rand() % (n - i) + i]);
  }
  return shuffled;
}