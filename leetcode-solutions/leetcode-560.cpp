/*
 * Subarray sum equals k
 *
 * Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.
 * 
 * Example:
 * Input: nums = [1,1,1], k = 2
 * Output: 2
 * 
 * Note:
 * The length of the array is in range [1, 20,000].
 * The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].
 * 
 */
#include <unordered_map>
#include <vector>
using namespace std;

int subarraySum(vector<int>& nums, int k) {
  int count = 0, psum = 0;
  unordered_map<int, int> hashmap;
  hashmap[0] = 1;
  for (int i : nums) {
    psum += i;
    count += hashmap[psum - k];
    ++hashmap[psum];
  }

  return count;
}