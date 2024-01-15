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