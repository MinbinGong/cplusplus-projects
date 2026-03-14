/**
 * 1788. Maximize the Beauty of the Garden
 * 
 * There is a garden of n flowers, and each flower has an integer beauty value. The flowers are arranged in a line. You are given an integer array flowers of size n and each flowers[i] represents the beauty of the ith flower.
 * 
 * A garden is valid if it meets these conditions:
 * 
 * The garden has at least two flowers.
 * The first and the last flower of the garden have the same beauty value.
 * As the appointed gardener, you have the ability to remove any (possibly none) flowers from the garden. You want to remove flowers in a way that makes the remaining garden valid. The beauty of the garden is the sum of the beauty of all the remaining flowers.
 * 
 * Given the integer array flowers, return the maximum possible beauty of some valid garden after you have removed any (possibly none) flowers.
 * 
 *  
 * 
 * Example 1:
 * 
 * Input: flowers = [1,2,3,1,2]
 * Output: 8
 * Explanation: Remove the third and the fourth flowers. The garden becomes valid. The remaining flowers have beauty values of [1,2,1,2]. The sum of the beauty values is 8.
 * Example 2:
 * 
 * Input: flowers = [1,2,4,1,2,5,1,2,6]
 * Output: 12
 * Explanation: Remove the first, the third, and the fifth flowers. The garden becomes valid. The remaining flowers have beauty values of [2,4,2,6]. The sum of the beauty values is 12.
 *  
 * 
 * Constraints:
 * 
 * 2 <= flowers.length <= 105
 * 1 <= flowers[i] <= 105
 * 
 */
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximumBeauty(vector<int>& flowers) {
        int n = flowers.size();
        vector<int> prefixSum(n + 1, 0);  // 前缀和，只累加正数
        
        // 计算前缀和（只累加正数）
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + max(0, flowers[i]);
        }
        
        unordered_map<int, int> firstIndex;  // 记录每种美观度第一次出现的位置
        int ans = INT_MIN;
        
        for (int i = 0; i < n; ++i) {
            // 如果当前美观度之前出现过，可以形成一个有效花园
            if (firstIndex.count(flowers[i])) {
                int start = firstIndex[flowers[i]];
                // 计算从 start 到 i 的区间和（只包含正数）
                int sum = prefixSum[i + 1] - prefixSum[start];
                
                // 如果当前美观度是负数，需要加上两倍（因为区间和没包括两端）
                if (flowers[i] < 0) {
                    sum += 2 * flowers[i];
                }
                ans = max(ans, sum);
            } else {
                // 第一次出现，记录位置
                firstIndex[flowers[i]] = i;
            }
        }
        
        return ans;
    }
};