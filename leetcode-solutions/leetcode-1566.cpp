/*
 * 1566. Detect Pattern of Length M Repeated K or More Times
 * 
 * Given an array of positive integers arr, find a pattern of length m that is repeated k or more times.
 * 
 * A pattern is a subarray (consecutive sub-sequence) that consists of one or more values, repeated multiple times consecutively without overlapping. A pattern is defined by its length and the number of repetitions.
 * 
 * Return true if there exists a pattern of length m that is repeated k or more times, otherwise return false.
 * 
 * Example 1:
 * Input: arr = [1,2,4,4,4,4], m = 1, k = 3
 * Output: true
 * Explanation: The pattern (4) of length 1 is repeated 4 consecutive times. Notice that pattern can be repeated k or more times but not less.
 * 
 * Example 2:
 * Input: arr = [1,2,1,2,1,1,1,3], m = 2, k = 2
 * Output: true
 * Explanation: The pattern (1,2) of length 2 is repeated 2 consecutive times. Another valid pattern (2,1) is also repeated 2 times.
 * 
 * Example 3:
 * Input: arr = [1,2,1,2,1,3], m = 2, k = 3
 * Output: false
 * Explanation: The pattern (1,2) is of length 2 but is repeated only 2 times. There is no pattern of length 2 that is repeated 3 or more times.
 * 
 * Constraints:
 * 2 <= arr.length <= 100
 * 1 <= arr[i] <= 100
 * 1 <= m <= 100
 * 2 <= k <= 100
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        int n = arr.size();
        // 枚举所有可能的起始位置，保证剩余长度足够容纳 k 个长度为 m 的模式
        for (int i = 0; i + m * k <= n; ++i) {
            bool match = true;
            // 检查后续的 k-1 个模式是否与第一个模式相等
            for (int j = 1; j < k; ++j) {
                for (int p = 0; p < m; ++p) {
                    if (arr[i + j * m + p] != arr[i + p]) {
                        match = false;
                        break;
                    }
                }
                if (!match) break;
            }
            if (match) return true;
        }
        return false;
    }
};
