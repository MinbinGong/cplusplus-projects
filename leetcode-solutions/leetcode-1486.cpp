/**
 * 1486. XOR Operation in an Array
 * 
 * You are given an integer n and an integer start.
 * 
 * Define an array nums where nums[i] = start + 2 * i (0-indexed) and n == nums.length.
 * 
 * Return the bitwise XOR of all elements of nums.
 * 
 * Example 1:
 * Input: n = 5, start = 0
 * Output: 8
 * Explanation: Array nums is equal to [0, 2, 4, 6, 8] where (0 ^ 2 ^ 4 ^ 6 ^ 8) = 8.
 * Where "^" corresponds to bitwise XOR operator.
 * 
 * Example 2:
 * Input: n = 4, start = 3
 * Output: 8
 * Explanation: Array nums is equal to [3, 5, 7, 9] where (3 ^ 5 ^ 7 ^ 9) = 8.
 * 
 * Constraints:
 * 1 <= n <= 10^4
 * 0 <= start <= 10^4
 * n == nums.length
 */
class Solution1 {
public:
    int xorOperation(int n, int start) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans ^= (start + 2 * i);
        }
        return ans;
    }
};

class Solution2 {
public:
    int xorOperation(int n, int start) {
        // 函数计算 0 到 n 的异或
        auto xorN = [](int n) -> int {
            int mod = n % 4;
            if (mod == 0) return n;
            if (mod == 1) return 1;
            if (mod == 2) return n + 1;
            return 0;
        };

        int s = start >> 1;        // 去掉最低位
        int prefix = xorN(s + n - 1) ^ xorN(s - 1);
        int last = (n & start & 1); // 如果 n 和 start 都是奇数，则最低位为 1
        return (prefix << 1) | last;
    }
};