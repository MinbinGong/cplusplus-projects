/*
 * Three Equal Parts
 *
 * Given an array A of 0s and 1s, divide the array into 3 non-empty parts such that all of these parts represent the same binary value.
 *
 * If it is possible, return any [i, j] with i+1 < j, such that:
 *
 * A[0], A[1], ..., A[i] is the first part;
 * A[i+1], A[i+2], ..., A[j-1] is the second part, and
 * A[j], A[j+1], ..., A[A.length - 1] is the third part.
 * All three parts have equal binary value.
 * If it is not possible, return [-1, -1].
 *
 * Note that the entire part is used when considering what binary value it represents.  For example, [1,1,0] represents 6 in decimal, not 3.  Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
 *
 * Example 1:
 * Input: [1,0,1,0,1]
 * Output: [0,3]
 * Explanation: All three parts have equal binary value.
 * 
 * Example 2:
 * Input: [1,1,0,1,1]
 * Output: [-1,-1]
 * Explanation: It is not possible to split the array into 3 parts with equal binary value.
 * 
 * Example 3:
 * Input: [1,1,0,0,1]
 * Output: [0,2]
 * Explanation: All three parts have equal binary value.
 * 
 * Note:
 * 3 <= A.length <= 30000
 * A[i] == 0 or A[i] == 1
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int n = arr.size();
        int totalOnes = 0;
        
        // 统计 1 的总数
        for (int num : arr) {
            totalOnes += num;
        }
        
        // 如果 1 的个数不能被 3 整除，无法平分
        if (totalOnes % 3 != 0) {
            return {-1, -1};
        }
        
        // 全零数组的特殊情况
        if (totalOnes == 0) {
            return {0, n - 1};
        }
        
        int k = totalOnes / 3;  // 每部分应有的 1 的个数
        int start = 0, mid = 0, end = 0;
        int cnt = 0;
        
        // 定位三个部分中第一个 1 的位置
        for (int i = 0; i < n; ++i) {
            if (arr[i] == 0) continue;
            if (cnt == 0) start = i;      // 第一部分第一个 1
            ++cnt;
            if (cnt == k + 1) mid = i;    // 第二部分第一个 1
            if (cnt == 2 * k + 1) {       // 第三部分第一个 1
                end = i;
                break;
            }
        }
        
        // 比较三个部分是否相同
        while (end < n && arr[start] == arr[mid] && arr[mid] == arr[end]) {
            ++start;
            ++mid;
            ++end;
        }
        
        // 如果 end 到达数组末尾，说明三个部分完全相同
        if (end == n) {
            return {start - 1, mid};
        }
        
        return {-1, -1};
    }
};