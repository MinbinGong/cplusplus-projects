/**
 * 978. Longest Turbulent Subarray
 *
 * A subarray A[i], A[i+1], ..., A[j] of A is said to be turbulent if and only if:
 *
 * For i <= k < j, A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
 * OR, for i <= k < j, A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.
 * That is, the subarray is turbulent if the comparison sign flips between each adjacent pair of elements in the subarray.
 *
 * Return the length of a maximum size turbulent subarray of A.
 *
 * Example 1:
 *
 * Input: [9,4,2,10,7,8,8,1,9]
 * Output: 5
 * Explanation: (A[1] > A[2] < A[3] > A[4] < A[5])
 * 
 * Example 2:
 *
 * Input: [4,8,12,16]
 * Output: 2
 * 
 * Example 3:
 *
 * Input: [100]
 * Output: 1
 * 
 * Note:
 *
 * 1 <= nums.length <= 40000
 * 0 <= nums[i] <= 109
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 1;
        
        // up: 以当前元素结尾且最后一段是上升(arr[i-1] < arr[i])的湍流子数组长度
        // down: 以当前元素结尾且最后一段是下降(arr[i-1] > arr[i])的湍流子数组长度
        int up = 1, down = 1;
        int max_len = 1;
        
        for (int i = 1; i < n; ++i) {
            if (arr[i] > arr[i-1]) {
                up = down + 1;  // 上升接在下降后面
                down = 1;       // 下降序列中断
            } else if (arr[i] < arr[i-1]) {
                down = up + 1;  // 下降接在上升后面
                up = 1;         // 上升序列中断
            } else {
                // 相等时重置
                up = down = 1;
            }
            max_len = max(max_len, max(up, down));
        }
        
        return max_len;
    }
};