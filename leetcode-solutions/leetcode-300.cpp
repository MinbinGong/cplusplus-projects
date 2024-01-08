/*
	Longest Increasing Subsequent

	题目描述
		给定一个未排序的整数数组，求最长的递增子序列。

	题解
		对于子序列问题，第一种动态规划方法是，定义一个 dp 数组，其中 dp[i] 表示以 i 结尾的子序列的性质。
	在处理好每个位置后，统计一遍各个位置的结果即可得到题目要求的结果.
		在本题中，dp[i] 可以表示以 i 结尾的、最长子序列长度。对于每一个位置 i，如果其之前的某
	个位置 j 所对应的数字小于位置 i 所对应的数字，则我们可以获得一个以 i 结尾的、长度为 dp[j]
	+ 1 的子序列。为了遍历所有情况，我们需要 i 和 j 进行两层循环，其时间复杂度为 O(n2 )。
 */

#include <vector>
#include <iterator>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
	vector<int> dp;
	for (const auto& num : nums) {
		auto up = lower_bound(nums.begin(), nums.end(), num);
		if (up != dp.end()) {
			*up = num;
		}
		else {
			dp.emplace_back(num);
		}
	}
	return dp.size();
}