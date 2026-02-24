/*
 * 845. Longest Mountain in Array
 * 
 * You may recall that an array arr is a mountain array if and only if:
 * 
 * arr.length >= 3
 * There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
 * arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 * arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 * Given an integer array arr, return the length of the longest subarray, which is a mountain. Return 0 if there is no mountain subarray.
 * 
 * Example 1:
 * Input: arr = [2,1,4,7,3,2,5]
 * Output: 5
 * Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
 * 
 * Example 2:
 * Input: arr = [2,2,2]
 * Output: 0
 * Explanation: There is no mountain.
 * 
 * Note:
 * 1 <= arr.length <= 10^4
 * 0 <= arr[i] <= 10^4
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size();
        if (n < 3) return 0;
        
        // left[i]: 以 i 结尾的连续递增子数组的长度（不包括 i 本身）
        vector<int> left(n, 0);
        // right[i]: 以 i 开头的连续递减子数组的长度（不包括 i 本身）
        vector<int> right(n, 0);
        
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i - 1])
                left[i] = left[i - 1] + 1;
        }
        
        for (int i = n - 2; i >= 0; --i) {
            if (arr[i] > arr[i + 1])
                right[i] = right[i + 1] + 1;
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (left[i] > 0 && right[i] > 0) {
                ans = max(ans, left[i] + right[i] + 1);
            }
        }
        return ans;
    }
};