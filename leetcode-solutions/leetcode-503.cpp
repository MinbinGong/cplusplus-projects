/*
 * leetcode-503
 * Next Greater Element II
 * 
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]),
 * return the next greater number for every element in nums.
 * 
 * The next greater number of a number x is the first greater number to its traversing-order next in the array,
 * which means you could search circularly to find its next greater number.
 * If it doesn't exist, return -1 for this number.
 */
#include <stack>
#include <vector>
using namespace std;
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) {
        return {};
    }
    vector<int> ans(n);
    stack<int> indices;
    for (int i = 0; i < 2*n; ++i) {
        int num = nums[i % n];
        while (!indices.empty()) {
            int preIndex = indices.top();
            if (num <= nums[preIndex]) {
                break;
            }
            indices.pop();
            ans[preIndex] = num;
        }
        if (i < n) {
            indices.push(i);
        }
    }
    while (!indices.empty()) {
        ans[indices.top()] = -1;
        indices.pop();
    }
    return ans;
}
