/*
 * 1649. Create Sorted Array through Instructions
 *
 * Given an integer array instructions, you are asked to create a sorted array from the elements in instructions. You start with an empty container nums. For each element from left to right in instructions, insert it into nums. The cost of each insertion is the minimum of the following:
 * The number of elements currently in nums that are strictly less than instructions[i].
 * The number of elements currently in nums that are strictly greater than instructions[i].
 * For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
 * Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7.
 * 
 * Example 1:
 * Input: instructions = [1,5,6,2]
 * Output: 1
 * Explanation: Begin with nums = [].
 * Insert 1 with cost min(0, 0) = 0, now nums = [1].
 * Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
 * Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
 * Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
 * The total cost is 0 + 0 + 0 + 1 = 1.
 * 
 * Example 2:
 * Input: instructions = [1,2,3,6,5,4]
 * Output: 3
 * Explanation: Begin with nums = [].
 * Insert 1 with cost min(0, 0) = 0, now nums = [1].
 * Insert 2 with cost min(1, 0) = 0, now nums = [1,2].
 * Insert 3 with cost min(2, 0) = 0, now nums = [1,2,3].
 * Insert 6 with cost min(3, 0) = 0, now nums = [1,2,3,6].
 * Insert 5 with cost min(3, 1) = 1, now nums = [1,2,3,5,6].
 * Insert 4 with cost min(3, 2) = 2, now nums = [1,2,3,4,5,6].
 * The total cost is 0 + 0 + 0 + 0 + 1 + 2 = 3.
 * 
 * Constraints:
 * 1 <= instructions.length <= 10^5
 * 1 <= instructions[i] <= 10^5
 * 
 */
#include <vector>
using namespace std;

class Solution {
private:
    // 树状数组模板 (Fenwick Tree)
    class FenwickTree {
    private:
        vector<int> bit;
        int n;
        // lowbit 运算：获取最低位的1
        int lowbit(int x) {
            return x & -x;
        }
    public:
        FenwickTree(int size) : n(size), bit(size + 1, 0) {}

        // 单点更新：在 index 位置加上 delta
        void update(int index, int delta) {
            for (int i = index; i <= n; i += lowbit(i)) {
                bit[i] += delta;
            }
        }

        // 前缀和查询：返回 [1, index] 区间的累加和
        int query(int index) {
            int sum = 0;
            for (int i = index; i > 0; i -= lowbit(i)) {
                sum += bit[i];
            }
            return sum;
        }
    };
public:
    int createSortedArray(vector<int>& instructions) {
        const int MOD = 1e9 + 7;
        // 根据题目提示，instructions[i] 的最大值为 1e5
        int maxVal = 1e5;
        FenwickTree ft(maxVal);
        long long ans = 0;
        int n = instructions.size();

        for (int i = 0; i < n; ++i) {
            int x = instructions[i];
            // 严格小于 x 的个数
            int lessCount = ft.query(x - 1);
            // 严格大于 x 的个数 = 已插入总数 - 小于等于 x 的个数
            int greaterCount = i - ft.query(x);
            // 代价取较小值
            ans = (ans + min(lessCount, greaterCount)) % MOD;
            // 将当前数字 x 插入（更新计数）
            ft.update(x, 1);
        }
        return ans;
    }
};