/*
 * 1652. Defuse the Bomb
 *
 * You have a bomb to defuse, and your time is running out! Your informer will provide you with a circular array code of length of n and a key k.
 * 
 * To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.
 * 
 * If k > 0, replace the ith number with the sum of the next k numbers.
 * If k < 0, replace the ith number with the sum of the previous k numbers.
 * If k == 0, replace the ith number with 0.
 * As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].
 * 
 * Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!
 * 
 * Example 1:
 * Input: code = [5,7,1,4], k = 3
 * Output: [12,10,16,13]
 * Explanation: Each number is replaced by the sum of the next 3 numbers. The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.
 * 
 * Example 2:
 * Input: code = [1,2,3,4], k = 0
 * Output: [0,0,0,0]
 * Explanation: When k is zero, the numbers are replaced by 0. 
 * 
 * Constraints:
 * n == code.length
 * 1 <= n <= 100
 * 1 <= code[i] <= 100
 * -(n - 1) <= k <= n - 1
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        vector<int> res(n, 0);
        if (k == 0) return res;          // k == 0 直接全零

        int sum = 0;
        if (k > 0) {
            // 计算第一个窗口：下标 1 到 k 的和（循环）
            for (int i = 1; i <= k; ++i) sum += code[i % n];
            res[0] = sum;
            // 滑动窗口，每次移除 code[i]，加入 code[(i + k) % n]
            for (int i = 1; i < n; ++i) {
                sum -= code[i];                  // 移出窗口左侧
                sum += code[(i + k) % n];         // 加入窗口右侧
                res[i] = sum;
            }
        } else { // k < 0
            int m = -k;                           // 取绝对值
            // 计算第一个窗口：前 m 个元素（下标 -1, -2, ..., -m）
            for (int i = 1; i <= m; ++i) sum += code[(0 - i + n) % n];
            res[0] = sum;
            // 滑动窗口，每次移除 code[(i-1 - m) % n]，加入 code[i-1]
            for (int i = 1; i < n; ++i) {
                sum -= code[(i - 1 - m + n) % n]; // 移出窗口最老的元素
                sum += code[i - 1];                // 加入新的前一个元素
                res[i] = sum;
            }
        }
        return res;
    }
};