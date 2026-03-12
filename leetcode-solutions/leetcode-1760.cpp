/**
 * 1760. Minimum Limit of Balls in a Bag
 * 
 * You are given an integer array nums where the ith bag contains nums[i] balls.
 * You are also given an integer maxOperations.
 * 
 * You can perform the following operation at most maxOperations times:
 * 
 * Take any bag of balls and divide it into two new bags with a positive number of balls.
 * For example, a bag of 5 balls can become two new bags of 1 and 4 balls, or two new bags of 2 and 3 balls.
 * 
 * Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the operations.
 * 
 * Return the minimum possible penalty after performing the operations.
 * 
 * Example 1:
 * 
 * Input: nums = [9], maxOperations = 2
 * Output: 3
 * Explanation: 
 * - Divide the bag with 9 balls into two bags of sizes 6 and 3. [9] -> [6,3].
 * 
 * Example 2:
 * 
 * Input: nums = [2,4,8,2], maxOperations = 4
 * Output: 2
 * Explanation:
 * - Divide the bag with 8 balls into two bags of sizes 4 and 4. [2,4,8,2] -> [2,4,4,4,2].
 * - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,4,4,4,2] -> [2,2,2,4,4,2].
 * - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,4,4,2] -> [2,2,2,2,2,4,2].
 * - Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,2,2,4,2] -> [2,2,2,2,2,2,2,2].
 * 
 * Example 3:
 * 
 * Input: nums = [7,17], maxOperations = 2
 * Output: 7
 * 
 * Constraints:
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= maxOperations, nums[i] <= 10^9
 * 
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int left = 1;
        int right = *max_element(nums.begin(), nums.end());
        int ans = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long ops = 0;
            
            for (int a : nums) {
                ops += (a - 1) / mid;   // minimum operations needed for this bag
                if (ops > maxOperations) break;  // early termination
            }
            
            if (ops <= maxOperations) {
                ans = mid;          // feasible, try smaller limit
                right = mid - 1;
            } else {
                left = mid + 1;     // infeasible, need larger limit
            }
        }
        
        return ans;
    }
};