/*
 * Maximum Product Subarray
 * Given an integer array nums, find a 
 * subarray
 *  that has the largest product, and return the product.
 *
 *  The test cases are generated so that the answer will fit in a 32-bit
 *  integer.
 */
#include <vector>
#include <algorithm>
using namespace std;

int maxProduct(vector<int>& nums) {
  if (nums.size() == 0) {
    return 0;
  }

  if (nums.size() == 1) {
    return nums[0];
  }

  int temp1 = 0, temp2 = 0, ans = 0;
  for (int i = 0; i < nums.size(); i++) {
    int temp = max(max(temp1 * nums[i], temp2 * nums[i]), nums[i]);
    temp2 = min(min(temp1 * nums[i], temp2 * nums[i]), nums[i]);
    temp1 = temp;
    ans = max(ans, temp1);
  }

  return ans;
}
