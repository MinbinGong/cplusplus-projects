/*
 * Non-decreasing Subsequences
 *
 *  Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
 *
 *  Constraints:
 *  1 <= nums.length <= 15
 *  -100 <= nums[i] <= 100
 * 
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        dfs(nums, 0, path, result);
        return result;
    }

private:
    void dfs(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& result) {
        if (path.size() > 1) {
            result.push_back(path);
        }
        unordered_set<int> used; // 记录当前层已经使用过的数字，用于去重
        for (int i = start; i < nums.size(); ++i) {
            if (!path.empty() && nums[i] < path.back()) continue; // 必须非递减
            if (used.count(nums[i])) continue; // 同一层相同数字跳过
            used.insert(nums[i]);
            path.push_back(nums[i]);
            dfs(nums, i + 1, path, result);
            path.pop_back();
        }
    }
};