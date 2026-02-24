/*
 * 808. Soup Servings
 * 
 * There are two types of soup: type A and type B. Initially we have N ml of each type of soup. There are four kinds of operations:
 * 
 * Serve 100 ml of soup A and 0 ml of soup B
 * Serve 75 ml of soup A and 25 ml of soup B
 * Serve 50 ml of soup A and 50 ml of soup B
 * Serve 25 ml of soup A and 75 ml of soup B
 * When we serve some soup, we give it to someone and we no longer have it.  Each turn, we will choose from the four operations with equal probability 0.25. If the remaining volume of soup is not enough to complete the operation, we will serve as much as we can.  We stop once we no longer have some quantity of both types of soup.
 * 
 * Note that we do not have the operation where all 100 ml's of soup B are used first.  
 * 
 * Example:
 * Input: N = 50
 * Output: 0.625
 * Explanation: 
 * If we choose the first two operations, A will become empty first. For the third operation, A and B will become empty at the same time. For the fourth operation, B will become empty first. So the total probability of A becoming empty first plus half the probability of A and B becoming empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
 * 
 * Note:
 * 0 <= N <= 10^9. 
 * Answers within 10^-6 of the true value will be accepted as correct.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    double soupServings(int n) {
        // 将 n 转换为以 25ml 为单位的份数，并向上取整
        // 例如 n=50 -> m=2, n=26 -> m=2
        int m = (n + 24) / 25; // 等价于 ceil(n/25.0)

        // 优化：当 n 非常大时，概率无限趋近于 1
        // 经过测试和理论推导，当 m 约大于 200 时，概率已经非常接近 1
        // 这里取一个较大值 5000/25 = 200 作为阈值，当 n >= 5000 时直接返回 1
        // 实际上 4800 或 5000 均可
        if (n >= 5000) return 1.0; 

        // 记忆化数组，memo[i][j] 表示剩余 i 份 A 和 j 份 B 时的概率
        // 由于上面已经对大 n 做了处理，这里的 m 最大约为 200，数组大小可控
        vector<vector<double>> memo(m + 1, vector<double>(m + 1, 0.0));

        // 使用 lambda 表达式定义递归函数，便于捕获 memo
        function<double(int, int)> dfs = [&](int a, int b) -> double {
            // 边界条件
            if (a <= 0 && b <= 0) return 0.5; // 同时分配完
            if (a <= 0) return 1.0;            // A 先分配完
            if (b <= 0) return 0.0;            // B 先分配完

            // 如果已经计算过，直接返回
            if (memo[a][b] > 0) return memo[a][b];

            // 四种操作，每种概率 0.25
            // 操作后的剩余量不能小于 0，用 max(0, ...) 处理
            double prob = 0.0;
            prob += dfs(max(0, a - 4), b);                // 操作1：A-4, B-0
            prob += dfs(max(0, a - 3), max(0, b - 1));    // 操作2：A-3, B-1
            prob += dfs(max(0, a - 2), max(0, b - 2));    // 操作3：A-2, B-2
            prob += dfs(max(0, a - 1), max(0, b - 3));    // 操作4：A-1, B-3

            prob *= 0.25;
            memo[a][b] = prob;
            return prob;
        };

        return dfs(m, m);
    }
};