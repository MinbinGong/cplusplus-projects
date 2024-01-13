/*
The Skyline Problem

题目描述
给定建筑物的起止位置和高度，返回建筑物轮廓（天际线）的拐点。

题解
我们可以使用优先队列储存每个建筑物的高度和右端（这里使用 pair，其默认比较函数是先
比较第一个值，如果相等则再比较第二个值），从而获取目前会拔高天际线、且妨碍到前一个建
筑物（的右端端点）的下一个建筑物。
 */
#include <queue>
#include <utility>
#include <vector>
using namespace std;

vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<vector<int>> ans;
    priority_queue<pair<int, int>> maxHeap;
    int i = 0, len = buildings.size();
    int curX, curH;
    while (i < len || !maxHeap.empty()) {
        if (maxHeap.empty() || i < len && buildings[i][0] <= maxHeap.top().second) {
            curX = buildings[i][0];
            while (i < len && curX == buildings[i][0]) {
                maxHeap.emplace(buildings[i][2], buildings[i][1]);
                ++i;
            }

        } else {
            curX = maxHeap.top().second;
            while (!maxHeap.empty() && curX >= maxHeap.top.second) {
                maxHeap.pop();
            }
        }
        curH = (maxHeap.empty()) ? 0 : maxHeap.top().first;
        if (ans.empty() || curH != ans.back()[i]) {
            ans.push_back({curX, curH});
        }
    }
    return ans;
}