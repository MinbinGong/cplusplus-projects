/**
 * 1630. Arithmetic Subarrays
 * 
 * A sequence of numbers is called arithmetic if it consists of at least two elements, and the difference between every two consecutive elements is the same. More formally, a sequence s is arithmetic if and only if s[i+1] - s[i] == s[1] - s[0] for all valid i.
 * 
 * For example, these are arithmetic sequences:
 * 1, 3, 5, 7, 9
 * 7, 7, 7, 7
 * 3, -1, -5, -9
 * The following sequence is not arithmetic:
 * 1, 1, 2, 5, 7
 * You are given an array of n integers, nums, and two arrays of m integers each, l and r, representing the m range queries, where the ith query is the range [l[i], r[i]]. All the arrays are 0-indexed.
 * 
 * Example 1:
 * Input: nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
 * Output: [true,false,true]
 * Explanation:
 * In the 0th query, the subarray is [4,6,5]. This can be rearranged as [6,5,4], which is an arithmetic sequence with a difference of 1.
 * In the 1st query, the subarray is [4,6,5,9]. This cannot be rearranged as an arithmetic sequence.
 * In the 2nd query, the subarray is [5,9,3,7]. This can be rearranged as [3,5,7,9], which is an arithmetic sequence with a difference of 2.
 * 
 * Example 2:
 * Input: nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r = [4,4,9,7,9,10]
 * Output: [false,true,false,false,true,true]
 * 
 * Constraints:
 * n == nums.length
 * m == l.length
 * m == r.length
 * 2 <= n <= 500
 * 1 <= m <= 500
 * 0 <= l[i] < r[i] < n
 * -105 <= nums[i] <= 105
 * 
 */
#include <vector>
#include <unordered_map>
#include <functional>
#include <cstdint>

using namespace std;

class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int n = nums.size();
        // 预处理对数表
        vector<int> log2(n + 1, 0);
        for (int i = 2; i <= n; ++i) log2[i] = log2[i / 2] + 1;
        
        // 构建 prev 数组，记录每个元素上一次出现的 1‑based 位置
        vector<int> prev(n, 0);
        unordered_map<int, int> lastPos;
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            if (lastPos.count(num)) {
                prev[i] = lastPos[num];
            } else {
                prev[i] = 0;
            }
            lastPos[num] = i + 1; // 1‑based
        }
        
        // 比较函数对象
        auto cmp_min = [](int a, int b) { return a < b; };
        auto cmp_max = [](int a, int b) { return a > b; };
        
        // 构建稀疏表
        auto buildSparseTable = [&](vector<int>& arr, function<bool(int, int)> cmp) {
            int m = arr.size();
            int k = log2[m] + 1;
            vector<vector<int>> st(k, vector<int>(m));
            for (int i = 0; i < m; ++i) st[0][i] = arr[i];
            for (int j = 1; j < k; ++j) {
                for (int i = 0; i + (1 << j) <= m; ++i) {
                    st[j][i] = cmp(st[j-1][i], st[j-1][i + (1 << (j-1))])
                                   ? st[j-1][i]
                                   : st[j-1][i + (1 << (j-1))];
                }
            }
            return st;
        };
        // 查询稀疏表
        auto querySparseTable = [&](vector<vector<int>>& st, int l, int r,
                                     function<bool(int, int)> cmp) {
            int j = log2[r - l + 1];
            int left = st[j][l];
            int right = st[j][r - (1 << j) + 1];
            return cmp(left, right) ? left : right;
        };
        
        vector<vector<int>> minST = buildSparseTable(nums, cmp_min);
        vector<vector<int>> maxST = buildSparseTable(nums, cmp_max);
        vector<vector<int>> prevMaxST = buildSparseTable(prev, cmp_max);
        
        // 前缀和、前缀平方和
        vector<long long> prefSum(n + 1, 0), prefSqSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            long long x = nums[i];
            prefSum[i + 1] = prefSum[i] + x;
            prefSqSum[i + 1] = prefSqSum[i] + x * x;
        }
        
        vector<bool> ans;
        int q = l.size();
        for (int i = 0; i < q; ++i) {
            int L = l[i], R = r[i];
            // 检查重复元素
            int maxPrev = querySparseTable(prevMaxST, L, R, cmp_max);
            if (maxPrev >= L + 1) { // 存在重复
                ans.push_back(false);
                continue;
            }
            int mn = querySparseTable(minST, L, R, cmp_min);
            int mx = querySparseTable(maxST, L, R, cmp_max);
            int k = R - L + 1;
            if (k == 1) {
                ans.push_back(true);
                continue;
            }
            long long diff = (long long)mx - mn;
            if (diff % (k - 1) != 0) {
                ans.push_back(false);
                continue;
            }
            long long d = diff / (k - 1);
            // 等差数列和
            long long sum = (long long)k * (mn + mx);
            if (sum % 2 != 0) {
                ans.push_back(false);
                continue;
            }
            long long S = sum / 2;
            // 等差数列平方和
            __int128 term1 = (__int128)k * mn * mn;
            __int128 term2 = (__int128)k * (k - 1) * d * mn;
            __int128 term3_num = (__int128)d * d * (k - 1) * k * (2 * k - 1);
            if (term3_num % 6 != 0) {
                ans.push_back(false);
                continue;
            }
            __int128 term3 = term3_num / 6;
            __int128 S2_128 = term1 + term2 + term3;
            long long S2 = (long long)S2_128;
            // 实际和与平方和
            long long actSum = prefSum[R + 1] - prefSum[L];
            long long actSqSum = prefSqSum[R + 1] - prefSqSum[L];
            ans.push_back(S == actSum && S2 == actSqSum);
        }
        return ans;
    }
};