/*
 * Valid Mountain Array
 *
 * Given an array A of integers, return true if and only if it is a valid mountain array.
 *
 * Recall that A is a mountain array if and only if:
 *
 * A.length >= 3
 * There exists some i with 0 < i < A.length - 1 such that:
 * A[0] < A[1] < ... A[i-1] < A[i]
 * A[i] > A[i+1] > ... > A[A.length - 1]
 * 
 * Example 1:
 * Input: [2,1]
 * Output: false
 * 
 * Example 2:
 * Input: [3,5,5]
 * Output: false
 * 
 * Example 3:
 * Input: [0,3,2,1]
 * Output: true
 * 
 * Note:
 * 0 <= A.length <= 10000
 * 0 <= A[i] <= 10000 
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        int n = arr.size();
        if (n < 3) return false; // 山脉数组至少需要3个元素

        int i = 0;

        // 向上爬升，直到遇到不满足严格递增的位置
        while (i + 1 < n && arr[i] < arr[i + 1]) {
            i++;
        }

        // 峰值不能是第一个或最后一个元素
        if (i == 0 || i == n - 1) return false;

        // 向下行走，直到遇到不满足严格递减的位置
        while (i + 1 < n && arr[i] > arr[i + 1]) {
            i++;
        }

        // 如果成功走到数组末尾，说明是有效的山脉数组
        return i == n - 1;
    }
};