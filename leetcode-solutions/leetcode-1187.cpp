/*
 * 1187. Make Array Strictly Increasing
 * 
 * Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
 * 
 * In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
 * 
 * If there is no way to make arr1 strictly increasing, return -1.
 * 
 * Example 1:
 * 
 * Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
 * Output: 1
 * Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
 * 
 * Example 2:
 * Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
 * Output: 2
 * Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].
 * 
 * Example 3:
 * Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
 * Output: -1
 * Explanation: You can't make arr1 strictly increasing.
 * 
 * 
 * Constraints:
 * 1 <= arr1.length, arr2.length <= 2000
 * 0 <= arr1[i], arr2[i] <= 10^9
 * 
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        // 1. 对 arr2 排序去重
        sort(arr2.begin(), arr2.end());
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());

        // 2. 收集所有可能的值（arr1、arr2 和一个虚拟最小值）
        vector<int> vals = arr1;
        vals.insert(vals.end(), arr2.begin(), arr2.end());
        const int NEG_INF = -1e9 - 1;   // 虚拟最小值，必须小于所有实际值
        vals.push_back(NEG_INF);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int n = vals.size();
        unordered_map<int, int> idx;
        for (int i = 0; i < n; ++i) idx[vals[i]] = i;

        // 3. 线段树（维护区间最小值）
        vector<int> seg(4 * n, 1e9);
        function<void(int, int, int, int, int)> update = [&](int node, int l, int r, int pos, int val) {
            if (l == r) {
                seg[node] = min(seg[node], val);
                return;
            }
            int mid = (l + r) / 2;
            if (pos <= mid) update(node * 2, l, mid, pos, val);
            else update(node * 2 + 1, mid + 1, r, pos, val);
            seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
        };
        function<int(int, int, int, int, int)> query = [&](int node, int l, int r, int ql, int qr) {
            if (ql > r || qr < l) return 1e9;
            if (ql <= l && r <= qr) return seg[node];
            int mid = (l + r) / 2;
            return min(query(node * 2, l, mid, ql, qr),
                       query(node * 2 + 1, mid + 1, r, ql, qr));
        };

        // 虚拟值位置的操作数为 0
        update(1, 0, n - 1, idx[NEG_INF], 0);

        // 4. 遍历 arr1 的每个元素
        for (int x : arr1) {
            unordered_map<int, int> newStates;   // 暂存本轮新状态

            // 保留 x
            int px = idx[x];
            int best = query(1, 0, n - 1, 0, px - 1);   // 所有小于 x 的值的最小操作数
            if (best < 1e9) {
                newStates[x] = best;                     // 保留，操作数不变
            }

            // 替换为 arr2 中的每个值
            for (int y : arr2) {
                int py = idx[y];
                best = query(1, 0, n - 1, 0, py - 1);   // 所有小于 y 的值的最小操作数
                if (best < 1e9) {
                    int cand = best + 1;                  // 替换一次
                    if (newStates.find(y) == newStates.end() || cand < newStates[y]) {
                        newStates[y] = cand;
                    }
                }
            }

            // 将本轮新状态合并到线段树中
            for (auto& [val, cnt] : newStates) {
                update(1, 0, n - 1, idx[val], cnt);
            }
        }

        // 5. 答案取所有实际值（不含虚拟值）的最小操作数
        int ans = 1e9;
        for (int i = 1; i < n; ++i) {   // 跳过虚拟值
            ans = min(ans, query(1, 0, n - 1, i, i));
        }
        return ans >= 1e9 ? -1 : ans;
    }
};