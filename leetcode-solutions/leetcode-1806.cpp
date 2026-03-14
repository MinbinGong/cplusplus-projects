/*
 * 1806. Minimum Number of Operations to Reinitialize a Permutation
 *
 * You are given an even integer n​​​​​​. You initially have a permutation perm of size n​​ where perm[i] == i​ (0-indexed).
 * 
 * In one operation, you will create a new array arr, and for each i:
 * 
 * If i % 2 == 0, then arr[i] = perm[i / 2].
 * If i % 2 == 1, then arr[i] = perm[n / 2 + (i - 1) / 2].
 * You will then assign arr​​​​ to perm.
 * 
 * Return the minimum non-zero number of operations you need to perform on perm to return the permutation to its initial value.
 * 
 * Example 1:
 * 
 * Input: n = 2
 * Output: 1
 * Explanation: perm = [0,1] initially.
 * After the 1st operation, perm = [0,1]
 * So it takes only 1 operation.
 * 
 * Example 2:
 * 
 * Input: n = 4
 * Output: 2
 * Explanation: perm = [0,1,2,3] initially.
 * After the 1st operation, perm = [0,2,1,3]
 * After the 2nd operation, perm = [0,1,2,3]
 * So it takes only 2 operations.
 * 
 * Example 3:
 * 
 * Input: n = 6
 * Output: 4
 * 
 * Constraints:
 * 
 * 2 <= n <= 1000
 * n​​​​​​ is even.
 * 
 */
#include <vector>
#include <numeric> // for iota
#include <unordered_map>

class Solution1 {
public:
    int reinitializePermutation(int n) {
        // 初始化 perm 和 target 数组为 [0, 1, 2, ..., n-1]
        std::vector<int> perm(n);
        std::vector<int> target(n);
        std::iota(perm.begin(), perm.end(), 0);
        std::iota(target.begin(), target.end(), 0);

        int steps = 0;
        while (true) {
            // 执行一次操作，结果存到 arr
            std::vector<int> arr(n);
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) {
                    arr[i] = perm[i / 2];
                } else {
                    arr[i] = perm[n / 2 + (i - 1) / 2];
                }
            }
            // 将 arr 赋值给 perm，步数加一
            perm = std::move(arr);
            ++steps;

            // 检查是否回到初始状态
            if (perm == target) {
                break;
            }
        }
        return steps;
    }
};

class Solution2 {
public:
    int reinitializePermutation(int n) {
        int steps = 0;
        // 我们从数字 '1' 开始追踪它的下标
        // 初始时，数字 1 在下标 1 的位置
        int idx = 1; 

        while (true) {
            // 根据规则，计算当前下标 idx 在下一步操作后的新位置
            if (idx < n / 2) {
                // 规则前半部分对应的是原下标在左半区的情况
                idx = idx * 2;
            } else {
                // 规则后半部分对应原下标在右半区的情况
                idx = (idx - n / 2) * 2 + 1;
            }
            ++steps;

            // 如果数字 '1' 回到了下标 1，则说明排列复原
            if (idx == 1) {
                break;
            }
        }
        return steps;
    }
};

class Solution3 {
public:
    int reinitializePermutation(int n) {
        std::unordered_map<int, int> nextPos;
        // 构建映射：当前下标 i 上的数，下一步会移动到哪个下标
        // 更直接地，我们找到数字 1 的轨迹
        // 但为了和思路对应，这里构建下标的映射关系
        for (int i = 1; i < n - 1; ++i) { // 0 和 n-1 不需要考虑
            if (i % 2 == 0) {
                nextPos[i] = i / 2;
            } else {
                nextPos[i] = n / 2 + (i - 1) / 2;
            }
        }

        int steps = 0;
        int current = 1; // 从数字 1 所在的下标开始
        do {
            current = nextPos[current];
            ++steps;
        } while (current != 1); // 直到回到下标 1

        return steps;
    }
};