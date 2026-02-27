/**
 * 1064. Fixed Point
 * 
 * Given an array A of distinct integers sorted in ascending order, return the smallest index i that satisfies A[i] == i.
 * Return -1 if no such i exists.
 * 
 * 
 * Example 1:
 * Input: [-10,-5,0,3,7]
 * Output: 3
 * Explanation: 
 * For the given array, A[0] = -10, A[1] = -5, A[2] = 0, A[3] = 3, thus the output is 3.
 * 
 * Example 2:
 * Input: [0,2,5,8,17]
 * Output: 0
 * Explanation: 
 * A[0] = 0, thus the output is 0.
 * 
 * Example 3:
 * Input: [-10,-5,3,4,7,9]
 * Output: -1
 * Explanation: 
 * There is no such i that A[i] = i, thus the output is -1.
 * 
 * Note:
 * 1 <= A.length <= 10000
 * -10^9 <= A[i] <= 10^9
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    int fixedPoint(vector<int>& A) {
        int left = 0, right = A.size() - 1;
        int ans = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (A[mid] < mid) {
                left = mid + 1;          // 固定点只可能在右侧
            } else if (A[mid] > mid) {
                right = mid - 1;          // 固定点只可能在左侧
            } else { // A[mid] == mid
                ans = mid;                // 记录当前固定点
                right = mid - 1;           // 继续向左寻找更小的索引
            }
        }
        return ans;
    }
};