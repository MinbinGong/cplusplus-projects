/*
 * 1675. Minimize Deviation in Array
 * 
 * You are given an array nums of n positive integers.
 * 
 * You can perform two types of operations on any element of the array any number of times:
 * 
 * If the element is even, divide it by 2.
 * For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
 * If the element is odd, multiply it by 2.
 * For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
 * The deviation of the array is the maximum difference between any two elements in the array.
 * 
 * Return the minimum deviation the array can have after performing some number of operations.
 * 
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: 1
 * Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
 * 
 * Example 2:
 * Input: nums = [4,1,5,20,3]
 * Output: 3
 * Explanation: You can transform the array after two operations to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.
 * 
 * Example 3:
 * Input: nums = [2,10,8]
 * Output: 3
 * Explanation: You can transform the array after one operation to [2,5,8], then the deviation will be 8 - 2 = 6.
 * 
 * Constraints:
 * n == nums.length
 * 2 <= n <= 105
 * 1 <= nums[i] <= limit <= 105
 * n is even.
 * 
 */
#include <vector>
#include <queue>
using namespace std;

class Solution1 {
public:
    int minimumDeviation(vector<int>& nums) {
        priority_queue<int> pq; // 最大堆
        int minVal = INT_MAX;

        // 第一步：将所有奇数翻倍，并记录最小值
        for (int num : nums) {
            if (num % 2 == 1) {
                num *= 2; // 奇数只能变大，翻倍后可以后续缩小
            }
            pq.push(num);
            minVal = min(minVal, num);
        }

        int ans = INT_MAX;
        // 第二步：不断尝试缩小最大值
        while (true) {
            int maxVal = pq.top();
            pq.pop();
            ans = min(ans, maxVal - minVal); // 更新最小偏移量

            // 如果最大值是奇数，则无法再缩小（因为题目操作只允许缩小偶数）
            if (maxVal % 2 == 1) {
                break;
            }

            // 将最大值减半，并重新入堆
            int newVal = maxVal / 2;
            pq.push(newVal);
            minVal = min(minVal, newVal); // 更新全局最小值
        }
        return ans;
    }
};

class Solution2 {
public:
    int minimumDeviation(vector<int>& nums) {
        priority_queue<int> pq;
        int minVal = INT_MAX;

        for (int num : nums) {
            if (num % 2 == 1) num *= 2;
            pq.push(num);
            minVal = min(minVal, num);
        }

        int ans = INT_MAX;
        while (true) {
            int maxVal = pq.top();
            pq.pop();
            ans = min(ans, maxVal - minVal);

            // 内部循环：在满足条件时连续缩小同一个数
            while (maxVal % 2 == 0 && maxVal >= pq.top()) {
                maxVal /= 2;
                minVal = min(minVal, maxVal);
                ans = min(ans, max(maxVal, pq.top()) - minVal);
            }
            // 如果无法再缩小或最大值已为奇数，将当前值推回堆中
            pq.push(maxVal);
            if (pq.top() % 2 == 1) break; // 堆顶为奇数时结束
        }
        return ans;
    }
};