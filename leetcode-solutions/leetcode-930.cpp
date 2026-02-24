/*
 * Binary Subarrays With Sum
 *
 * In an array A of 0s and 1s, how many non-empty subarrays have sum S?
 *
 * Example 1:
 * Input: A = [1,0,1,0,1], S = 2
 * Output: 4
 * Explanation: The 4 subarrays are bolded below:
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 * [1,0,1,0,1]
 *
 * Note:
 * A.length <= 30000
 * 0 <= S <= A.length
 * A[i] is either 0 or 1.
 *
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> prefixCount; // maps prefix sum -> frequency
        prefixCount[0] = 1;                  // sum 0 before any element
        int currentSum = 0;
        int result = 0;

        for (int num : nums) {
            currentSum += num;
            // We need previous sum = currentSum - goal
            int target = currentSum - goal;
            if (prefixCount.count(target)) {
                result += prefixCount[target];
            }
            prefixCount[currentSum]++;
        }

        return result;
    }
};