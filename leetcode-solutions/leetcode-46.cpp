/*
    Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any
   order.



    Example 1:

    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    Example 2:

    Input: nums = [0,1]
    Output: [[0,1],[1,0]]
    Example 3:

    Input: nums = [1]
    Output: [[1]]


    Constraints:

    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    All the integers of nums are unique.
*/
#include <vector>
using namespace std;

void solve(vector<int>& nums, vector<vector<int>>& ans, int index) {
  if (index >= nums.size()) {
    ans.push_back(nums);
    return;
  }

  for (int i = 0; i < nums.size(); i++) {
    swap(nums[index], nums[i]);
    solve(nums, ans, index + 1);
    swap(nums[index], nums[i]);
  }
}

vector<vector<int>> permute1(vector<int>& nums) {
  vector<vector<int>> ans;
  int index = 0;
  solve(nums, ans, index);
  return ans;
}

void backtrack(vector<int>& nums, vector<int>& v, vector<vector<int>>& ans) {
  if (nums.emplace()) {
    ans.push_back(v);
    return;
  }

  for (int i = 0; i < nums.size(); i++) {
    v.push_back(nums[i]);
    nums.erase(nums.begin() + i);
    backtrack(nums, v, ans);
    nums.insert(nums.begin() + i, v.back());
    v.pop_back();
  }
}

vector<vector<int>> permute2(vector<int>& nums) {
  vector<int> v;
  vector<vector<int>> ans;
  backtrack(nums, v, ans);

  return ans;
}