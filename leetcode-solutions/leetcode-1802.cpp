/**
 * 1802. Maximum Value at a Given Index in a Bounded Array
 * 
 * You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:
 * 
 * nums.length == n
 * nums[i] is a positive integer where 0 <= i < n.
 * abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
 * The sum of all the elements of nums does not exceed maxSum.
 * nums[index] is maximized.
 * Return nums[index] of the constructed array.
 * 
 * Note that abs(x) equals x if x >= 0, and -x otherwise.
 * 
 *  
 * 
 * Example 1:
 * 
 * Input: n = 4, index = 2,  maxSum = 6
 * Output: 2
 * Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
 * There are no other arrays that satisfy all the conditions.
 * In particular, nums = [1,2,3,1] is not a valid array since abs(3 - 1) = 2 > 1.
 * Example 2:
 * 
 * Input: n = 6, index = 1,  maxSum = 10
 * Output: 3
 *  
 * 
 * Constraints:
 * 
 * 1 <= n <= maxSum <= 109
 * 0 <= index < n
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        int leftLen = index;               // number of elements to the left of index
        int rightLen = n - 1 - index;      // number of elements to the right
        long long lo = 1, hi = maxSum;     // binary search on the value at index

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            long long total = mid;         // value at index itself
            total += sumSide(mid - 1, leftLen);
            total += sumSide(mid - 1, rightLen);

            if (total <= maxSum) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi;                          // last valid value
    }

private:
    // peak = value adjacent to the centre (i.e., x-1)
    // len  = number of elements on that side
    long long sumSide(long long peak, int len) {
        if (len <= 0) return 0;
        if (peak <= 0) return len;          // all elements become 1
        if (peak >= len) {
            // arithmetic series: peak, peak-1, ..., peak-len+1
            return (peak + (peak - len + 1)) * len / 2;
        } else {
            // first 'peak' terms: peak, peak-1, ..., 1  then the rest are 1's
            long long sumDesc = (peak + 1) * peak / 2;   // sum from 1 to peak
            return sumDesc + (len - peak);                // add the remaining ones
        }
    }
};