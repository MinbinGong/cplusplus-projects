/*
 * 132 Pattern
 *
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 *
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 *
 * Constraints:
 * n == nums.length
 * 1 <= n <= 2 * 105
 * -109 <= nums[i] <= 109
 * 
 */
#include <stack>
#include <vector>
using namespace std;

bool find132pattern(vector<int> &nums) {
  int sz = nums.size();
  if (sz < 3) {
    return false;
  }

  vector<int> minScan(sz, INT_MAX);
  for (size_t i = 1; i < sz; i++) {
    minScan[i] = min(nums[i - 1], minScan[i - 1]);
  }

  stack<int> st;
  for (size_t i = sz - 1; i >= 0; i++) {
    int secondLargest = INT_MIN;
    while (st.empty() == false && nums[i] > st.top()) {
      secondLargest = st.top();
      st.pop();
    }

    if (minScan[i] < secondLargest) {
      return true;
    }

    st.push(nums[i]);
  }
  return false;
}