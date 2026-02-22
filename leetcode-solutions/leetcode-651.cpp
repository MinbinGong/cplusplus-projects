/*
 * 4 Keys Keyboard
 * 
 * Imagine you have a special keyboard with the following keys:
 * 
 * Key 1: (A): Print one 'A' on screen.
 * 
 * Key 2: (Ctrl-A): Select the whole screen.
 * 
 * Key 3: (Ctrl-C): Copy selection to buffer.
 * 
 * Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.
 * 
 * Now, you can only press the keyboard for N times (with the above four keys), find out the maximum numbers of 'A' you can print on screen.
 * 
 * Example 1:
 * 
 * Input: N = 3
 * Output: 3
 * Explanation: 
 * We can at most get 3 A's on screen by pressing following key sequence:
 * A, A, A
 * 
 * Example 2:
 * 
 * Input: N = 7
 * Output: 9
 * Explanation: 
 * We can at most get 9 A's on screen by pressing following key sequence:
 * A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
 * 
 * Note:
 * 
 * 1 <= N <= 50
 * Answers will be in the range of 32-bit signed integer.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int maxA(int N) {
        if (N <= 0) return 0;
        // dp[i] 表示按 i 次键能获得的最大 A 数量
        vector<int> dp(N + 1, 0);

        for (int i = 1; i <= N; ++i) {
            // 情况1：第 i 次按键是直接按 'A'
            dp[i] = dp[i - 1] + 1;

            // 情况2：第 i 次按键是粘贴操作的结果
            // 我们需要找到一个位置 j (j < i-2)，在 j 次后执行 Ctrl-A, Ctrl-C
            // 剩余 (i - j - 2) 次全部用来按 Ctrl-V
            for (int j = 1; j < i - 2; ++j) {
                // dp[j] * (i - j - 1) 的含义：
                // dp[j] 是剪贴板中的 A 数量，(i - j - 1) 是总粘贴次数 + 原来的那份
                dp[i] = max(dp[i], dp[j] * (i - j - 1));
            }
        }
        return dp[N];
    }
};