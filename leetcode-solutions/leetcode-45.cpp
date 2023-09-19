/*
    You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].

    Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at
    nums[i], you can jump to any nums[i + j] where:

    0 <= j <= nums[i] and
    i + j < n
    Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you can reach nums[n
   - 1].



    Example 1:

    Input: nums = [2,3,1,1,4]
    Output: 2
    Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps
   to the last index. Example 2:

    Input: nums = [2,3,0,1,4]
    Output: 2


    Constraints:

    1 <= nums.length <= 104
    0 <= nums[i] <= 1000
    It's guaranteed that you can reach nums[n - 1].
 */
#include <climits>
#include <vector>
using namespace std;

int jump1(vector<int>& nums) {
    int left = 0, right = 0, farthest = 0, jump = 0;
    while (right < nums.size() - 1) {
        for (int i = left; i <= right; i++) {
            farthest = max(farthest, i + nums[i]);
        }

        left = right + 1;
        right = farthest;
        jump++;
    }
    return jump;
}

void solve(vector<int>& nums, int& ans, int count, int index) {
    if (index >= nums.size() - 1) {
        ans = min(ans, count);
        return;
    }

    if (count > ans) {
        return;
    }

    for (int i = 1; i <= nums[index]; i++) {
        solve(nums, ans, count + 1, index + i);
    }
    return;
}

int jump2(vector<int>& nums) {
    int ans = INT_MAX, count = 0;
    solve(nums, ans, count, 0);

    return ans;
}

int solve2(vector<int>& nums, int index, vector<int>& dp) {
    if (index >= nums.size() - 1) {
        return 0;
    }

    if (dp[index] != INT_MAX - 1) {
        return dp[index];
    }

    for (int i = 1; i <= nums[index]; i++) {
        dp[index] = min(dp[index], 1 + solve2(nums, index + i, dp));
    }

    return dp[index];
}

int jump3(vector<int>& nums) {
    vector<int> dp(nums.size(), INT_MAX - 1);
    return solve2(nums, 0, dp);
}