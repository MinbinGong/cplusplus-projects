/*
 * Missing Ranges 
 * 
 * You are given an inclusive range [lower, upper] and a sorted unique integer array nums, where all elements are in the inclusive range.
 * 
 * A number x is considered missing if x is in the range [lower, upper] and x is not in nums.
 * 
 * Return the smallest sorted list of ranges that cover every missing number exactly. That is, no element of nums is in any of the ranges, and each missing number is in one of the ranges.
 * 
 * Each range [a,b] in the list should be output as:
 * 1. "a->b" if a != b
 * 2. "a" if a == b
 * 
 * Constraints:
 * 1. -109 <= lower <= upper <= 109
 * 2. 0 <= nums.length <= 100
 * 3. lower <= nums[i] <= upper
 * 4. All the values of nums are unique.
 * 5. nums is sorted in ascending order.
 * 6. nums[i] != nums[i + 1] for all 0 <= i < nums.length - 1
 * 7. lower <= nums[0] <= upper
 * 8. nums[nums.length - 1] <= upper
 * 9. nums[0] <= lower <= upper <= nums[nums.length - 1]
 * 
 */
#include <string>
#include <vector>
using namespace std;

vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
    vector<string> result;
    long long prev = (long long)lower - 1;  // use long long to safely handle lower = INT_MIN
    
    for (int i = 0; i <= nums.size(); ++i) {
        long long curr = (i < nums.size()) ? (long long)nums[i] : (long long)upper + 1;
        
        // If there is a gap between prev+1 and curr-1, it's a missing range
        if (prev + 1 <= curr - 1) {
            if (prev + 1 == curr - 1) {
                // Single number
                result.push_back(to_string(prev + 1));
            } else {
                // Range
                result.push_back(to_string(prev + 1) + "->" + to_string(curr - 1));
            }
        }
        prev = curr;
    }
    
    return result;
}
