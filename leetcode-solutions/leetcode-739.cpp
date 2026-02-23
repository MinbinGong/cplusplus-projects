/*
 * Daily Temperatures
 *
 * Given a list of daily temperatures T, return a list such that, for each day in the input,
 * tells you how many days you would have to wait until a warmer temperature. If there is no
 * warmer temperature, put 0 instead.
 * 
 * Note:
 * 1. The length of temperatures will be in the range [1, 30000].
 * 2. Each temperature will be an integer in the range [30, 100].
 * 3. The temperature of each day is guaranteed to be in the range [30, 100].
 * 4. The temperature of each day is guaranteed to be in the range [30, 100].
 * 
 */
#include <stack>
#include <vector>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
  int n = temperatures.size();
  if (n == 0) {
    return {};
  }

  vector<int> ans(n);
  stack<int> indices;
  for (int i = 0; i < n; ++i) {
    while (!indices.empty()) {
      int preIndex = indices.top();
      if (temperatures[i] <= temperatures[preIndex]) {
        break;
      }
      indices.pop();
      ans[preIndex] = i - preIndex;
    }
    indices.push(i);
  }
  return ans;
}