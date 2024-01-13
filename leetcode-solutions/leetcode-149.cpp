/*
Max Points on a Line

题目描述
给定一些二维坐标中的点，求同一条线上最多由多少点。

题解
对于每个点，我们对其它点建立哈希表，统计同一斜率的点一共有多少个。这里利用的原理
是，一条线可以由一个点和斜率而唯一确定。另外也要考虑斜率不存在和重复坐标的情况。
本题也利用了一个小技巧：在遍历每个点时，对于数组中位置 i 的点，我们只需要考虑 i 之
后的点即可，因为 i 之前的点已经考虑过 i 了。
 */
#include <unordered_map>
#include <vector>
using namespace std;

int maxPoints(vector<vector<int>>& points) {
    unordered_map<double, int> hash;
    int maxCount = 0, same = 1, sameY = 1;
    for (int i = 0; i < points.size(); ++i) {
        same = 1, sameY = 1;
        for (int j = i + 1; j < points.size(); ++j) {
            if (points[i][1] == points[j][1]) {
                ++sameY;
                if (points[i][0] == points[j][0]) {
                    ++same;
                }
            } else {
                double dx = points[i][0] - points[j][0], dy = points[i][1] - points[j][1];
                ++hash[dx / dy];
            }
        }

        maxCount = max(maxCount, sameY);
        for (auto item : hash) {
            maxCount = max(maxCount, same + item.second);
        }
        hash.clear();
    }
    return maxCount;
}