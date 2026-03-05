/*
 * 1588. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
 * 
 * Given an array of integers arr and two integers k and threshold, return the number of sub-arrays of size k and average greater than or equal to threshold.   
 * 
 * Example 1:
 * Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
 * Output: 3
 * Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively. All other sub-arrays of size 3 have averages less than 4 (the threshold).
 * 
 * Example 2:
 * Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
 * Output: 6
 * Explanation: The first 6 sub-arrays of size 3 have averages greater than 5. Note that averages are not integers.
 * 
 * Constraints:
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 10^4
 * 1 <= k <= arr.length
 * 0 <= threshold <= 10^4
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int total = 0;
        for (int i = 0; i < n; ++i) {
            int left = i;                 // 左边可选元素个数
            int right = n - i - 1;         // 右边可选元素个数
            // 左边选偶数个的方案数：0,2,4,... 共 left/2 + 1
            int left_even = left / 2 + 1;
            // 左边选奇数个的方案数：1,3,5,... 共 (left+1)/2
            int left_odd = (left + 1) / 2;
            // 右边同理
            int right_even = right / 2 + 1;
            int right_odd = (right + 1) / 2;
            // 总方案数 = (左偶*右偶) + (左奇*右奇)
            int count = left_even * right_even + left_odd * right_odd;
            total += arr[i] * count;
        }
        return total;
    }
};