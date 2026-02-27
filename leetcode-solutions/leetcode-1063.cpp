/**
 * 1063. Number of Valid Subarrays
 * 
 * Given an array A of integers, return the number of non-empty continuous subarrays that satisfy the following condition:
 * 
 * The leftmost element of the subarray is not larger than other elements in the subarray.
 * 
 * 
 * Example 1:
 * Input: [1,4,2,5,3]
 * Output: 11
 * Explanation: There are 11 valid subarrays: [1],[4],[2],[5],[3],[1,4],[2,5],[1,4,2],[2,5,3],[1,4,2,5],[1,4,2,5,3].
 * 
 * Example 2:
 * Input: [3,2,1]
 * Output: 3
 * Explanation: The 3 valid subarrays are: [3],[2],[1].
 * 
 * Example 3:
 * Input: [2,2,2]
 * Output: 6
 * Explanation: There are 6 valid subarrays: [2],[2],[2],[2,2],[2,2],[2,2,2].
 * 
 * Note:
 * 1 <= A.length <= 50000
 * 0 <= A[i] <= 100000
 * 
 */
#include <vector>
#include <stack>
using namespace std;

class Solution1 {
public:
    int validSubarrays(vector<int>& nums) {
        stack<int> stk;      // 单调递增栈，存放元素下标
        int res = 0;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            // 当栈顶元素对应的值大于当前元素时，说明找到了栈顶元素的“右边第一个更小值”
            while (!stk.empty() && nums[stk.top()] > nums[i]) {
                // 以 stk.top() 为起点的有效子数组，只能延伸到 i-1
                res += i - stk.top();
                stk.pop();
            }
            stk.push(i);
        }
        
        // 处理栈中剩余元素：它们右边没有更小的值，可以延伸到数组末尾
        while (!stk.empty()) {
            res += n - stk.top();
            stk.pop();
        }
        
        return res;
    }
};

class Solution2 {
public:
    int validSubarrays(vector<int>& nums) {
        // 添加一个极小值作为哨兵，确保所有元素都能在遍历过程中被处理
        nums.push_back(-1e9);  
        int res = 0;
        int n = nums.size();
        stack<int> stk;
        
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && nums[stk.top()] > nums[i]) {
                res += i - stk.top();
                stk.pop();
            }
            stk.push(i);
        }
        return res;
    }
};