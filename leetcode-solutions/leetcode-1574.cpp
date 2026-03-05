/*
 * 1574. Shortest Sub-array to be Removed to Make Array Sorted
 *
 * Given an integer array arr, remove a sub-array (can be empty) from arr such that the remaining elements in arr are non-decreasing.
 * Return the length of the shortest sub-array to remove.
 * 
 * Example 1:
 * Input: arr = [1,2,3,10,4,2,3,5]
 * Output: 3
 * Explanation: The shortest sub-array we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.   
 * 
 * Example 2:
 * Input: arr = [5,4,3,2,1]
 * Output: 4
 * Explanation: Since the array is strictly decreasing, we can only keep a single element. Therefore we need to remove a sub-array of length 4, either [5,4,3,2] or [4,3,2,1].
 *
 * Constraints:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^4
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        
        // 1. find longest non‑decreasing prefix
        int left = 0;
        while (left + 1 < n && arr[left] <= arr[left + 1]) {
            ++left;
        }
        // already sorted?
        if (left == n - 1) return 0;
        
        // 2. find longest non‑decreasing suffix
        int right = n - 1;
        while (right > 0 && arr[right - 1] <= arr[right]) {
            --right;
        }
        
        // 3. initial answer: keep only the prefix or only the suffix
        int minRemove = min(n - left - 1, right);   // (n - (left+1)) and right
        
        // 4. two‑pointer scan: try to merge a prefix [0..i] with a suffix [j..n-1]
        int j = right;
        for (int i = 0; i <= left; ++i) {
            // advance j to the first element not smaller than arr[i]
            while (j < n && arr[j] < arr[i]) {
                ++j;
            }
            if (j == n) break;   // no valid suffix for larger i
            int remaining = (i + 1) + (n - j);
            minRemove = min(minRemove, n - remaining);
        }
        
        return minRemove;
    }
};