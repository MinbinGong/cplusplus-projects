/*
 * 952. Largest Component Size by Common Factor
 *
 * You are given an integer array of unique positive integers nums. Consider the following graph:
 *
 * There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
 *
 * There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
 *
 * Return the size of the largest connected component in the graph.
 *
 * Example 1:
 *
 * Input: nums = [4,6,15,35]
 * Output: 4
 *
 * Example 2:
 *
 * Input: nums = [20,50,9,63]
 * Output: 2
 *
 * Example 3:
 *
 * Input: nums = [2,3,6,7,4,12,21,39]
 * Output: 8
 *
 * Note:
 *
 * 1 <= nums.length <= 2 * 104
 * 1 <= nums[i] <= 105
 * All the values of nums are unique.
 */
#include <vector>
using namespace std;

class Solution {
private:
    // 并查集类
    vector<int> parent;

    // 查找根节点（带路径压缩）
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并两个集合
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

public:
    int largestComponentSize(vector<int>& nums) {
        // 1. 找到数组中的最大值，以此确定并查集的大小
        int maxVal = 0;
        for (int num : nums) {
            maxVal = max(maxVal, num);
        }

        // 2. 初始化并查集，大小为 maxVal + 1，因为数字本身可以作为节点
        parent.resize(maxVal + 1);
        for (int i = 0; i <= maxVal; ++i) {
            parent[i] = i;
        }

        // 3. 遍历数组中的每个数字，将其与它的所有因子合并
        for (int num : nums) {
            // 找出 num 的所有因子（从 2 到 sqrt(num)）
            for (int i = 2; i * i <= num; ++i) {
                if (num % i == 0) {
                    // i 是 num 的因子，将 num 与 i 合并
                    unite(num, i);
                    // num / i 也是 num 的因子，将 num 与 num / i 合并
                    unite(num, num / i);
                }
            }
        }

        // 4. 统计每个根节点（代表一个连通组件）包含的原数组元素个数
        vector<int> count(maxVal + 1, 0);
        int ans = 0;
        for (int num : nums) {
            int root = find(num);
            count[root]++;
            ans = max(ans, count[root]);
        }

        return ans;
    }
};