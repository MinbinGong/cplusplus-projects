/**
 * 1681. Minimum Incompatibility
 * 
 * You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size such that there are no two equal elements in the same subset.
 * 
 * A subset's incompatibility is the difference between the maximum and minimum elements in the subset.
 * 
 * Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.
 * 
 * A subset is a group integers that appear in the array with no particular order.
 * 
 * Example 1:
 * Input: nums = [1,2,1,4], k = 2
 * Output: 4
 * Explanation: The optimal distribution of subsets is [1,2] and [1,4].
 * The incompatibility is (2-1) + (4-1) = 4.
 * Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
 * 
 * Example 2:
 * Input: nums = [6,3,8,1,3,1,2,2], k = 4
 * Output: 6
 * Explanation: The optimal distribution of subsets is [1,2], [2,3], [6,8], and [1,3].
 * The incompatibility is (2-1) + (3-2) + (8-6) + (3-1) = 6.
 * 
 * Example 3:
 * Input: nums = [5,3,3,6,3,3], k = 3
 * Output: -1
 * Explanation: It is impossible to distribute nums into 3 subsets where no two elements are equal in the same subset.
 * 
 * Constraints:
 * 1 <= k <= nums.length <= 16
 * nums.length is divisible by k
 * 1 <= nums[i] <= nums.length
 * 
 */
#include <vector>
#include <climits>
#include <cstring> // for memset if needed, but not required

using namespace std;

class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n = nums.size();
        if (n % k != 0) return -1;
        int m = n / k;                     // size of each subset
        
        // ---------- precompute all valid groups ----------
        vector<int> groupMasks;             // bitmask of the group
        vector<int> groupCost;               // incompatibility of the group
        vector<vector<int>> groupsByBit(n); // groups that contain a given index
        
        for (int mask = 1; mask < (1 << n); ++mask) {
            if (__builtin_popcount(mask) != m) continue;
            
            bool seen[17] = {false};        // values are between 1 and 16
            int minVal = 17, maxVal = 0;
            bool valid = true;
            
            for (int i = 0; i < n; ++i) {
                if (mask >> i & 1) {
                    int val = nums[i];
                    if (seen[val]) {
                        valid = false;
                        break;
                    }
                    seen[val] = true;
                    if (val < minVal) minVal = val;
                    if (val > maxVal) maxVal = val;
                }
            }
            
            if (!valid) continue;
            
            int cost = maxVal - minVal;
            int idx = groupMasks.size();
            groupMasks.push_back(mask);
            groupCost.push_back(cost);
            
            for (int i = 0; i < n; ++i) {
                if (mask >> i & 1) {
                    groupsByBit[i].push_back(idx);
                }
            }
        }
        
        // ---------- DP over subsets ----------
        int full = (1 << n) - 1;
        const int INF = 1e9;
        vector<int> dp(1 << n, INF);
        dp[0] = 0;
        
        for (int mask = 0; mask <= full; ++mask) {
            if (dp[mask] == INF) continue;
            int pc = __builtin_popcount(mask);
            // only states that consist of complete groups are relevant
            if (pc % m != 0) continue;
            
            int remaining = full ^ mask;
            if (remaining == 0) continue;   // all elements already used
            
            // take the smallest unused index – this guarantees we consider each partition once
            int first = __builtin_ctz(remaining);
            
            for (int gIdx : groupsByBit[first]) {
                int G = groupMasks[gIdx];
                // check if the whole group lies in the remaining set
                if ((G & remaining) == G) {
                    int newMask = mask | G;
                    int newCost = dp[mask] + groupCost[gIdx];
                    if (newCost < dp[newMask]) {
                        dp[newMask] = newCost;
                    }
                }
            }
        }
        
        return dp[full] == INF ? -1 : dp[full];
    }
};