/*
Sliding Window Maximum

题目描述
给定一个整数数组和一个滑动窗口大小，求在这个窗口的滑动过程中，每个时刻其包含的最
大值。

题解
我们可以利用双端队列进行操作：每当向右移动时，把窗口左端的值从队列左端剔除，把队
列右边小于窗口右端的值全部剔除。这样双端队列的最左端永远是当前窗口内的最大值。另外，
这道题也是单调栈的一种延申：该双端队列利用从左到右递减来维持大小关系。
 */
#include <deque>
#include <vector>
using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> ans;
    for (int i = 0; i < nums.size; ++i) {
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            ans.push_back(nums[dq.front()]);
        }
    }
    return ans;
}