/*
Subsets

Given an integer array nums of unique elements, return all possible
subsets
 (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.



Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
Example 2:

Input: nums = [0]
Output: [[],[0]]
 */
#include <cmath>
#include <vector>
using namespace std;

vector<vector<int>> subsets(vector<int>& v) {
  int n = v.size();
  int size = pow(2, n);
  vector<vector<int>> res;
  for (int i = 0; i < size; ++i) {
    vector<int> temp;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        temp.push_back(v[j]);
      }
    }
    res.push_back(temp);
  }
  return res;
}