/*
Daily Temperatures

题目描述
给定每天的温度，求对于每一天需要等几天才可以等到更暖和的一天。如果该天之后不存在
更暖和的天气，则记为 0。

题解
我们可以维持一个单调递减的栈，表示每天的温度；为了方便计算天数差，我们这里存放位
置（即日期）而非温度本身。我们从左向右遍历温度数组，对于每个日期 p，如果 p 的温度比栈
顶存储位置 q 的温度高，则我们取出 q，并记录 q 需要等待的天数为 p − q；我们重复这一过程，
直到 p 的温度小于等于栈顶存储位置的温度（或空栈）时，我们将 p 插入栈顶，然后考虑下一天。
在这个过程中，栈内数组永远保持单调递减，避免了使用排序进行比较。最后若栈内剩余一些日
期，则说明它们之后都没有出现更暖和的日期。
 */
#include <stack>
#include <vector>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    if (n == 0) {
        return {};
    }

    vector<int> ans(n);
    stack<int> indices;
    for (int i = 0; i < n; ++i) {
        while (!indices.empty()) {
            int preIndex = indices.top();
            if (temperatures[i] <= temperatures[preIndex]) {
                break;
            }
            indices.pop();
            ans[preIndex] = i - preIndex;
        }
        indices.push(i);
    }
    return ans;
}