/*
 * Largest Number
 *
 * Given a list of non-negative integers nums, arrange them such that they form
 * the largest number and return it.
 *
 * Since the result may be very large, so you need to return a string instead
 * of an integer.
 *
 *  
 *
 * Example 1:
 *
 * Input: nums = [10,2]
 * Output: "210"
 * Example 2:
 *
 * Input: nums = [3,30,34,5,9]
 * Output: "9534330"
 *  
 *
 * Constraints:
 *
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 109
 */
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string largestNumber(vector<int> &nums) {
  sort(nums.begin(), nums.end(), [](int a, int b) {
      return to_string(a) + to_string(b) > to_string(b) + to_string(a);
      });

  string ans{""};
  for (int i = 0; i < nums.size(); i++) {
    ans += to_string(nums[i]);
  }

  if (ans[0] == '0') {
    return "0";
  }

  return ans;
}

