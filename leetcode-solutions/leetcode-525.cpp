/*
 * Contiguous Array
 *
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
 * 
 * Constraints:
 * 1 <= nums.length <= 10^5
 * nums[i] is either 0 or 1.
 * 
 */
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> firstOcc;
        firstOcc[0] = -1;  // prefix sum 0 at index -1
        int count = 0, maxLen = 0;
        
        for (int i = 0; i < nums.size(); ++i) {
            count += (nums[i] == 1) ? 1 : -1;  // treat 0 as -1
            if (firstOcc.find(count) != firstOcc.end()) {
                maxLen = max(maxLen, i - firstOcc[count]);
            } else {
                firstOcc[count] = i;
            }
        }
        return maxLen;
    }
};