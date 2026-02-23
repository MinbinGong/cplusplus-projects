/*
 * Falling Squares
 * 
 * On an infinite number line (x-axis), we drop given squares in the order they are given.
 * 
 * The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point being positions[i][0] and sidelength positions[i][1].
 * 
 * The square is dropped with the bottom edge parallel to the number line, and from a higher height than all currently landed squares. We wait for each square to stick before dropping the next.
 * 
 * The squares are infinitely sticky on their bottom edge, and will remain fixed to any positive length surface they touch (either the number line or another square). Squares dropped adjacent to each other will not stick together prematurely.
 * 
 * Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped, after dropping squares represented by positions[0], positions[1], ..., positions[i].
 * 
 * Example 1:
 * 
 * Input: [[1, 2], [2, 3], [6, 1]]
 * Output: [2, 5, 5]
 * Explanation:
 * 
 * After the first drop of positions[0] = [1, 2]:
 * _aa
 * _aa
 * -------
 * The maximum height of any square is 2.
 * 
 * After the second drop of positions[1] = [2, 3]:
 * __aaa
 * __aaa
 * __aaa
 * _aa__
 * _aa__
 * --------------
 * The maximum height of any square is 5.  
 * The larger square stays on top of the smaller square despite where its center
 * of gravity is, because squares are infinitely sticky on their bottom edge.
 * 
 * After the third drop of positions[1] = [6, 1]:
 * __aaa
 * __aaa
 * __aaa
 * _aa
 * _aa___a
 * --------------
 * The maximum height of any square is 5.
 * 
 * Note:
 * 1. 1 <= positions.length <= 1000.
 * 2. 1 <= positions[i][0] <= 10^8.
 * 3. 1 <= positions[i][1] <= 10^6.
 * 4. positions[i][0] < positions[i][0] + positions[i][1].
 * 5. positions[i][0] < positions[i+1][0].
 * 6. positions[i][1] <= positions[i+1][1].
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // 离散化所有左右端点
        vector<int> xs;
        for (auto& p : positions) {
            xs.push_back(p[0]);
            xs.push_back(p[0] + p[1]);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int m = xs.size();
        int n = m - 1; // 区间个数：xs[0]~xs[1], xs[1]~xs[2], ...

        // 线段树：维护区间最大值，支持区间赋值
        vector<int> seg(4 * n, 0);
        vector<int> lazy(4 * n, -1); // -1 表示无懒标记

        function<void(int,int,int,int,int,int)> update =
            [&](int L, int R, int val, int node, int l, int r) {
                if (L <= l && r <= R) {
                    seg[node] = val;
                    lazy[node] = val;
                    return;
                }
                if (lazy[node] != -1) {
                    seg[node * 2] = lazy[node];
                    seg[node * 2 + 1] = lazy[node];
                    lazy[node * 2] = lazy[node];
                    lazy[node * 2 + 1] = lazy[node];
                    lazy[node] = -1;
                }
                int mid = (l + r) / 2;
                if (L <= mid) update(L, R, val, node * 2, l, mid);
                if (R > mid)  update(L, R, val, node * 2 + 1, mid + 1, r);
                seg[node] = max(seg[node * 2], seg[node * 2 + 1]);
            };

        function<int(int,int,int,int,int)> query =
            [&](int L, int R, int node, int l, int r) {
                if (L <= l && r <= R) return seg[node];
                if (lazy[node] != -1) {
                    seg[node * 2] = lazy[node];
                    seg[node * 2 + 1] = lazy[node];
                    lazy[node * 2] = lazy[node];
                    lazy[node * 2 + 1] = lazy[node];
                    lazy[node] = -1;
                }
                int mid = (l + r) / 2;
                int res = 0;
                if (L <= mid) res = max(res, query(L, R, node * 2, l, mid));
                if (R > mid)  res = max(res, query(L, R, node * 2 + 1, mid + 1, r));
                return res;
            };

        vector<int> ans;
        int curMax = 0;
        for (auto& p : positions) {
            int left = p[0], side = p[1], right = left + side;
            int L = lower_bound(xs.begin(), xs.end(), left) - xs.begin();
            int R = lower_bound(xs.begin(), xs.end(), right) - xs.begin();
            // 查询区间 [L, R-1] 的最大高度
            int h = query(L, R - 1, 1, 0, n - 1);
            int newH = h + side;
            curMax = max(curMax, newH);
            ans.push_back(curMax);
            // 将区间 [L, R-1] 更新为 newH
            update(L, R - 1, newH, 1, 0, n - 1);
        }
        return ans;
    }
};