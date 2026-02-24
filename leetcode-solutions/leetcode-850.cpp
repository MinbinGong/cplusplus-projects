/*
 * 850. Rectangle Area II
 * 
 * We are given a list of (axis-aligned) rectangles.  Each rectangle[i] = [x1, y1, x2, y2] , where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the ith rectangle.
 * 
 * Find the total area covered by all rectangles in the plane.  Since the answer may be too large, return it modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
 * Output: 6
 * Explanation: As illustrated in the picture.
 * 
 * Example 2:
 * Input: [[0,0,1000000000,1000000000]]
 * Output: 49
 * 
 * Note:
 * 1 <= rectangles.length <= 200
 * rectanges[i].length = 4
 * 0 <= rectangles[i][j] <= 10^9
 * The total area covered by all rectangles will never exceed 2^63 - 1 and thus will fit in a 64-bit signed integer.
 */
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solution1 {
private:
    static const int MOD = 1e9 + 7;
    
    // 计算在 [x1, x2] 区间内，所有矩形覆盖的纵坐标总长度
    long long getVerticalCover(int x1, int x2, vector<vector<int>>& rects) {
        vector<pair<int, int>> intervals; // 存储所有覆盖此x区间的矩形纵坐标范围
        
        for (auto& r : rects) {
            if (r[0] <= x1 && r[2] >= x2) { // 矩形覆盖当前x区间
                intervals.emplace_back(r[1], r[3]); // 纵坐标 [y1, y2]
            }
        }
        
        if (intervals.empty()) return 0;
        
        // 按纵坐标起点排序，进行区间合并
        sort(intervals.begin(), intervals.end());
        long long totalLen = 0;
        int curStart = intervals[0].first, curEnd = intervals[0].second;
        
        for (size_t i = 1; i < intervals.size(); ++i) {
            if (intervals[i].first <= curEnd) {
                // 区间重叠，合并
                curEnd = max(curEnd, intervals[i].second);
            } else {
                // 不重叠，累加当前区间长度
                totalLen += curEnd - curStart;
                curStart = intervals[i].first;
                curEnd = intervals[i].second;
            }
        }
        totalLen += curEnd - curStart; // 加上最后一个区间
        
        return totalLen * (x2 - x1); // 面积 = 纵覆盖长度 * 横区间宽度
    }
    
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        // 1. 收集所有横坐标并排序去重
        vector<int> xs;
        for (auto& r : rectangles) {
            xs.push_back(r[0]);
            xs.push_back(r[2]);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        
        // 2. 遍历每个相邻的横坐标区间 [xs[i], xs[i+1]]
        long long ans = 0;
        for (size_t i = 0; i < xs.size() - 1; ++i) {
            ans += getVerticalCover(xs[i], xs[i + 1], rectangles);
            ans %= MOD;
        }
        return ans;
    }
};

class Solution2 {
private:
    static const int MOD = 1e9 + 7;
    
    // 线段树节点
    struct Node {
        int l, r;           // 对应纵坐标离散化后的区间 [l, r]
        int cnt;            // 当前区间被覆盖的次数
        long long len;      // 当前区间内被覆盖的实际长度
    };
    
    vector<Node> tr;
    vector<int> ys;         // 离散化后的纵坐标
    
    void build(int u, int l, int r) {
        tr[u].l = l, tr[u].r = r;
        tr[u].cnt = tr[u].len = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }
    
    void pushUp(int u) {
        if (tr[u].cnt) {
            // 当前区间被完全覆盖，长度为实际纵坐标差
            tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];
        } else if (tr[u].l == tr[u].r) {
            tr[u].len = 0;
        } else {
            tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
        }
    }
    
    void update(int u, int l, int r, int val) {
        if (l <= tr[u].l && tr[u].r <= r) {
            tr[u].cnt += val;
            pushUp(u);
            return;
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (l <= mid) update(u << 1, l, r, val);
        if (r > mid) update(u << 1 | 1, l, r, val);
        pushUp(u);
    }
    
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        // 1. 收集所有纵坐标并离散化
        for (auto& r : rectangles) {
            ys.push_back(r[1]);
            ys.push_back(r[3]);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        // 2. 构建扫描线事件
        vector<tuple<int, int, int, int>> events; // (x, y1, y2, type)
        for (auto& r : rectangles) {
            events.emplace_back(r[0], r[1], r[3], 1);  // 左边界，进入
            events.emplace_back(r[2], r[1], r[3], -1); // 右边界，退出
        }
        sort(events.begin(), events.end()); // 按x坐标排序
        
        // 3. 建立坐标到索引的映射
        map<int, int> idx;
        for (size_t i = 0; i < ys.size(); ++i) {
            idx[ys[i]] = i;
        }
        
        // 4. 初始化线段树
        tr.resize(ys.size() * 4);
        build(1, 0, ys.size() - 2); // 区间个数 = 点个数 - 1
        
        // 5. 扫描线计算面积
        long long ans = 0;
        int lastX = get<0>(events[0]);
        
        for (size_t i = 0; i < events.size(); ++i) {
            auto [x, y1, y2, type] = events[i];
            
            // 累加从 lastX 到 x 之间的面积
            ans = (ans + tr[1].len * (x - lastX)) % MOD;
            lastX = x;
            
            // 更新线段树：纵坐标区间 [y1, y2) 的覆盖次数
            int l = idx[y1];
            int r = idx[y2] - 1; // 注意：我们维护的是区间，所以右端点要减1
            if (l <= r) {
                update(1, l, r, type);
            }
        }
        
        return ans;
    }
};