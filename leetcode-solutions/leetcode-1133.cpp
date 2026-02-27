/**
 * 1133. Largest Unique Number
 *
 * Given an array of integers A, return the largest integer that only occurs once.
 * If no integer occurs once, return -1.
 *
 * Example 1:
 * Input: [5,7,3,9,4,9,8,3,1]
 * Output: 8
 * Explanation:
 * The maximum integer in the array is 9 but it is repeated. The number 8 occurs only once, so it's the answer.
 *
 * Example 2:
 * Input: [9,9,8,8]
 * Output: -1
 * Explanation:
 * There is no number that occurs only once.
 *
 * Note:
 *
 * 1 <= A.length <= 2000
 * 0 <= A[i] <= 1000
 *
 */
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>

class Solution1 {
public:
    int largestUniqueNumber(std::vector<int>& A) {
        // 根据题目数据范围，创建足够大的计数数组
        std::vector<int> count(1001, 0); // 索引 0-1000
        
        // 统计每个数字出现的次数
        for (int num : A) {
            count[num]++;
        }
        
        // 从大到小遍历，找到第一个出现次数为1的数字
        for (int i = 1000; i >= 0; i--) {
            if (count[i] == 1) {
                return i;
            }
        }
        
        return -1; // 没有只出现一次的数字
    }
};

class Solution2 {
public:
    int largestUniqueNumber(std::vector<int>& A) {
        std::unordered_map<int, int> freq;
        
        // 统计频率
        for (int num : A) {
            freq[num]++;
        }
        
        int ans = -1;
        // 遍历哈希表，找出频率为1的最大值
        for (const auto& pair : freq) {
            if (pair.second == 1) {
                ans = std::max(ans, pair.first);
            }
        }
        
        return ans;
    }
};