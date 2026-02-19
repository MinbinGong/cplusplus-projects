/*
 * Contains Duplicate II
 * 
 * Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array
 * such that nums[i] == nums[j] and abs(i - j) <= k.
 * 
 * Constraints:
 * 1. 1 <= nums.length <= 105
 * 2. -109 <= nums[i] <= 109
 * 3. 0 <= k <= 105
 */
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> lastSeen; // value -> last index
        
        for (int i = 0; i < nums.size(); ++i) {
            if (lastSeen.count(nums[i]) && i - lastSeen[nums[i]] <= k) {
                return true;
            }
            // Update the last seen index (always store the most recent)
            lastSeen[nums[i]] = i;
        }
        return false;
    }
};