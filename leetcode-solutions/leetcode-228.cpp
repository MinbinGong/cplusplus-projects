/*
 * Summary Ranges
 * 
 * You are given a sorted unique integer array nums.
 * 
 * A range [a,b] is the set of all integers from a to b (inclusive).
 * 
 * Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of
 * nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not
 * in nums.
 * 
 * Each range [a,b] in the list should be output as:
 * 
 * "a->b" if a != b
 * "a" if a == b
 * 
 * Constraints:
 * 1. 0 <= nums.length <= 20
 * 2. -231 <= nums[i] <= 231 - 1
 * 3. All the values of nums are unique.
 * 4. nums is sorted in ascending order.
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        int n = nums.size();
        if (n == 0) return result;
        
        int start = nums[0]; // start of current range
        
        for (int i = 1; i < n; ++i) {
            // If not consecutive
            if (nums[i] != nums[i - 1] + 1) {
                // End the current range
                if (start == nums[i - 1]) {
                    result.push_back(to_string(start));
                } else {
                    result.push_back(to_string(start) + "->" + to_string(nums[i - 1]));
                }
                // Start a new range
                start = nums[i];
            }
        }
        
        // Add the last range
        if (start == nums[n - 1]) {
            result.push_back(to_string(start));
        } else {
            result.push_back(to_string(start) + "->" + to_string(nums[n - 1]));
        }
        
        return result;
    }
};