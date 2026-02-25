/*
 * 964. Least Operators to Express Number
 *
 * Given a single positive integer x, we will write an expression of the form x (op1) x (op2) x (op3) x ... where each operator op1, op2, etc. is either addition, subtraction, multiplication, or division (+, -, *, or /). For example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of 3.
 *
 * When writing such an expression, we adhere to the following conventions:
 *
 * The division operator (/) returns rational numbers.
 * There are no parentheses placed anywhere.
 * We use the usual order of operations: multiplication and division happens before addition and subtraction.
 * It is not allowed to use the unary negation operator (-). For example, "x - x" is a valid expression as it only uses subtraction, but "-x + x" is not because it uses negation.
 * We would like to write an expression with the least number of operators such that the expression equals the given target. Return the least number of operators used.
 *
 * Example 1:
 *
 * Input: x = 3, target = 19
 * Output: 5
 * Explanation: 3 * 3 + 3 * 3 + 3 / 3.
 * The expression contains 5 operations.
 * 
 * Example 2:
 *
 * Input: x = 5, target = 501
 * Output: 8
 * Explanation: 5 * 5 * 5 * 5 - 5 * 5 * 5 + 5 / 5.
 * The expression contains 8 operations.
 * 
 * Example 3:
 *
 * Input: x = 100, target = 100000000
 * Output: 3
 * Explanation: 100 * 100 * 100 * 100.
 * The expression contains 3 operations.
 * 
 * Note:
 *
 * 2 <= x <= 100
 * 1 <= target <= 2 * 10^8
 * 
 */
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        // 记忆化哈希表，记录已经计算过的中间结果
        unordered_map<int, int> memo;
        
        // 递归函数：返回用 x 构造出数值 v 所需的最少运算符数
        function<int(int)> dfs = [&](int v) -> int {
            // 如果已经计算过，直接返回
            if (memo.count(v)) return memo[v];
            
            int res;
            // 基本情况：v < x
            if (v < x) {
                // 两种情况取最小：
                // 1. 用 v 个 x/x 相加：需要 v-1 个加号 + v 个除号 = 2*v - 1
                // 2. 用 x 减去 (x-v) 个 x/x：需要 1 个减号 + (x-v) 个除号 + (x-v-1) 个加号？仔细算：
                //    表达式为 x - x/x - x/x - ... (x-v 个 x/x)
                //    需要 (x-v) 个除号，以及 (x-v) 个减号（第一个减号连接 x 和第一个 x/x，后续每个 x/x 前有一个减号）
                //    总数为 2*(x-v)
                res = min(2 * v - 1, 2 * (x - v));
            } 
            // 递归情况：v >= x
            else {
                int k = 2;
                long long pow_xk = (long long)x * x; // x^2
                // 找到最小的 k 使得 x^k >= v
                while (pow_xk < v) {
                    pow_xk *= x;
                    k++;
                }
                
                // 计算 x^(k-1)
                long long pow_xk_1 = pow_xk / x;
                
                // 策略二：从 x^(k-1) 开始加
                // 构造 x^(k-1) 需要 (k-2) 个乘号（第一个 x 不算运算符）
                // 再加上递归结果 dfs(v - pow_xk_1)
                res = (k - 1) + dfs(v - pow_xk_1);
                
                // 策略一：从 x^k 开始减
                // 只有当差值小于 v 时才有考虑价值
                if (pow_xk - v < v) {
                    // 构造 x^k 需要 (k-1) 个乘号，再减去差值
                    res = min(res, k + dfs(pow_xk - v));
                }
            }
            
            // 记忆化存储
            memo[v] = res;
            return res;
        };
        
        return dfs(target);
    }
};