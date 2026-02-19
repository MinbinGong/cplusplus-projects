/*
 * Subsets
 *
 * Given an integer array nums that may contain duplicates, return all possible subsets
 * (the power set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 */
#include <vector>
#include <algorithm>
using namespace std;

void subset(int idx, vector<int>& ds, vector<int>& nums, vector<vector<int>>& ans, int n) {
    ans.push_back(ds);

    for (int i = idx; i < n; ++i) {
        if (i > idx && nums[i] == nums[i - 1]) {
            continue;
        }
        ds.push_back(nums[i]);
        subset(i + 1, ds, nums, ans, n);
        ds.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    int n = nums.size();
    vector<int> ds;
    vector<vector<int>> ans;

    sort(nums.begin(), nums.end());
    subset(0, ds, nums, ans, n);
    return ans;
}
