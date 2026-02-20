/*
 * Single Number III
 * Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice.
 * Find the two elements that appear only once. You can return the answer in any order.
 * 
 * You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
      int xor_all = 0;
      for (int num : nums) {
        xor_all ^= num;
      }

      int set_bit = xor_all & (-xor_all);
      int x = 0, y = 0;
      for (int num : nums) {
        if (num & set_bit) {
          x ^= num;
        } else {
          y ^= num;
        }
      }
      return {x, y};
    }
};