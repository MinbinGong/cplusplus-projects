/**
 * 1060. Missing Element in Sorted Array
 * 
 * Given a sorted array A of unique numbers, find the K-th missing number starting from the leftmost number of the array.
 * 
 * 
 * Example 1:
 * Input: A = [4,7,9,10], K = 1
 * Output: 5
 * Explanation: 
 * The first missing number is 5.
 * 
 * Example 2:
 * Input: A = [4,7,9,10], K = 3
 * Output: 8
 * Explanation: 
 * The missing numbers are [5,6,8,...], hence the third missing number is 8.
 * 
 * Example 3:
 * Input: A = [1,2,4], K = 3
 * Output: 6
 * Explanation: 
 * The missing numbers are [3,5,6,7,...], hence the third missing number is 6.
 * 
 * Note:
 * 1 <= A.length <= 50000
 * 1 <= A[i] <= 1e7
 * 1 <= K <= 1e8
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int n = nums.size();
        // total missing numbers up to the last element
        int totalMissing = nums[n - 1] - nums[0] - (n - 1);
        
        // If k is larger than all missing numbers inside the array,
        // the answer lies beyond the last element.
        if (k > totalMissing) {
            return nums[n - 1] + (k - totalMissing);
        }
        
        // Binary search for the smallest index i such that
        // missing count up to nums[i] is at least k.
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int missing = nums[mid] - nums[0] - mid;
            if (missing < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        // Now left is the first index where missing >= k.
        // The k‑th missing number lies between nums[left-1] and nums[left].
        int prevMissing = nums[left - 1] - nums[0] - (left - 1);
        return nums[left - 1] + (k - prevMissing);
    }
};