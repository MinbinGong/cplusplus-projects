/**
 * 1227. Airplane Seat Assignment Probability
 *
 * n passengers board an airplane with exactly n seats. The first passenger has lost the ticket and picks a seat randomly. But after that, the rest of the passengers will:
 *
 * Take their own seat if it is still available, and
 * Pick other seats randomly when they find their seat occupied
 *
 * Return the probability that the nth person gets his own seat.
 *
 *
 *
 * Example 1:
 *
 * Input: n = 1
 * Output: 1.00000
 * Explanation: The first person can only get the first seat.
 *
 * Example 2:
 *
 * Input: n = 2
 * Output: 0.50000
 * Explanation: The second person has a probability of 0.5 to get the second seat (when first person gets the first seat).
 *
 *
 * Constraints:
 *
 * 1 <= n <= 10^5
 *
 */
#include <vector>

using namespace std;

class Solution1 {
public:
    // 方法1: 数学解法 - 直接返回概率
    double nthPersonGetsNthSeat(int n) {
        // 当只有1个乘客时，概率为1
        // 当n>1时，概率总是1/2
        return n == 1 ? 1.0 : 0.5;
    }
};

// 方法2: 动态规划解法 - 展示推导过程
class Solution2 {
public:
    double nthPersonGetsNthSeat(int n) {
        if (n == 1) return 1.0;
        
        // dp[i] 表示有i个乘客时，第i个乘客坐到第i个座位的概率
        vector<double> dp(n + 1, 0.0);
        dp[1] = 1.0;
        
        for (int i = 2; i <= n; ++i) {
            // 状态转移方程: dp[i] = 1/i + (i-2)/i * dp[i-1]
            dp[i] = 1.0 / i + (i - 2.0) / i * dp[i - 1];
        }
        
        return dp[n];
    }
};

// 方法3: 递归解法（不推荐，可能栈溢出）
class Solution3 {
public:
    double nthPersonGetsNthSeat(int n) {
        if (n == 1) return 1.0;
        return 0.5;
    }
};

// 数学推导解释：
// 1. 当n=1时，只有一个乘客和一个座位，概率为1
// 2. 当n>1时：
//    - 第一个乘客有1/n的概率选到自己的座位，此时最后一个乘客一定能坐到自己的座位
//    - 第一个乘客有1/n的概率选到最后一个乘客的座位，此时最后一个乘客一定坐不到自己的座位
//    - 第一个乘客有(n-2)/n的概率选到其他乘客的座位，问题转化为规模为n-1的相同问题
//    - 通过数学归纳法可以证明，对于所有n>1，概率都是1/2