/*
 * 1121. Divide Array Into Increasing Sequences
 * 
 * Given a non-decreasing array of positive integers nums and an integer K, find out if this array can be divided into one or more disjoint increasing subsequences of length at least K.
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= K <= nums.length
 * 1 <= nums[i] <= 10^5
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution1 {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int K) {
        int n = nums.size();
        int maxCount = 1;  // 记录某个数字的最大出现次数
        int curCount = 1;  // 记录当前数字的出现次数

        // 遍历数组，统计最大频次
        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1]) {
                // 如果和上一个数字相同，当前计数+1
                curCount++;
                maxCount = max(maxCount, curCount);
            } else {
                // 遇到新数字，重置当前计数
                curCount = 1;
            }
        }

        // 核心判断：maxCount * K <= n ?
        // 为了防止整数溢出，可以写成除法形式
        return maxCount <= n / K;
    }
};

class Solution2 {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int K) {
        int n = nums.size();
        int curCount = 1;  // 当前数字出现的次数

        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1]) {
                curCount++;
                // 实时检查：如果当前数字的出现次数 * K 已经大于数组长度，则不可能成功
                // 这里直接写乘法 curCount * K > n 可能会有整数溢出风险（虽然此题数据范围较小）
                // 转换为除法比较更安全
                if (curCount > n / K) {
                    return false;
                }
            } else {
                curCount = 1; // 遇到新数字，重置计数
            }
        }

        // 还有一种情况：如果整个数组遍历完都没有触发 false，且最大值也满足条件，则返回 true
        // 注意：上面的循环已经实时检查了所有可能成为最大值的 curCount
        // 但为了保险，可以再加一次判断（其实上面的检查已经覆盖了所有情况，因为每次 curCount 更新后都检查了）
        // 我们可以直接返回 true，或者再加一个最终的 maxCount 判断
        // 为了清晰，这里使用方法一的最终判断作为保底
        // 实际上，由于我们在循环中已经实时检查了每个 curCount，可以简化为：
        return true;

        // 如果选择更严谨的写法，可以像方法一那样最后再检查一次：
        // int maxCount = 1;
        // int curCount = 1;
        // for (int i = 1; i < n; ++i) {
        //     if (nums[i] == nums[i-1]) {
        //         curCount++;
        //         maxCount = max(maxCount, curCount);
        //     } else {
        //         curCount = 1;
        //     }
        // }
        // return maxCount <= n / K;
    }
};