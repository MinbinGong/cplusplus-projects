/*
 * 1707. Maximum XOR With an Element From Array
 * 
 * You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].
 * The answer to the ith query is the maximum XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.
 * 
 * Example 1:
 * Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
 * Output: [3,3,7]
 * Explanation:
 * 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
 * 2) 1 XOR 2 = 3.
 * 3) 5 XOR 2 = 7.
 * 
 * Example 2:
 * Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
 * Output: [15,-1,5]
 * 1) 12 XOR 5 = 15.
 * 2) There is no integer in nums that is not greater than 1.
 * 3) 6 XOR 4 = 5.
 * 
 * Constraints:
 * 1 <= nums.length, queries.length <= 10^5
 * queries[i].length == 2
 * 0 <= nums[j], xi, mi <= 10^9
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Trie {
private:
    // 字典树节点，每个节点有两个子节点：0 和 1
    Trie* next[2] = {nullptr};
public:
    Trie() {}

    // 将数字 x 插入字典树
    void insert(int x) {
        Trie* node = this;
        // 从高位到低位处理（因为数字最大 10^9，所以考虑 30 位即可）
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1; // 取出当前位
            if (node->next[bit] == nullptr) {
                node->next[bit] = new Trie();
            }
            node = node->next[bit];
        }
    }

    // 在字典树中查找与 x 异或的最大值
    int search(int x) {
        Trie* node = this;
        int res = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            // 贪心：尽量走与当前位相反的路径，这样异或结果当前位为 1
            if (node->next[!bit] != nullptr) {
                res |= (1 << i); // 将结果的第 i 位置为 1
                node = node->next[!bit];
            } else {
                node = node->next[bit];
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        // 1. 对 nums 排序，便于后续按条件插入
        sort(nums.begin(), nums.end());

        int n = queries.size();
        // 2. 给 queries 加上原始索引，排序后仍能恢复顺序
        vector<vector<int>> newQueries;
        for (int i = 0; i < n; i++) {
            newQueries.push_back({queries[i][0], queries[i][1], i});
        }

        // 3. 按 mi (阈值) 升序排序
        sort(newQueries.begin(), newQueries.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        Trie* root = new Trie();
        vector<int> ans(n);
        int idx = 0; // 指向 nums 的指针

        // 4. 处理每个查询
        for (auto& q : newQueries) {
            int x = q[0], m = q[1], originalIdx = q[2];

            // 将所有 <= m 的 nums 插入字典树
            while (idx < nums.size() && nums[idx] <= m) {
                root->insert(nums[idx]);
                idx++;
            }

            // 如果没有元素可插入，说明没有满足条件的数，答案为 -1
            if (idx == 0) {
                ans[originalIdx] = -1;
            } else {
                ans[originalIdx] = root->search(x);
            }
        }

        return ans;
    }
};