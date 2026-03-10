/**
 * 1735. Count Ways to Make Array With Product
 * 
 * You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find the number of different ways you can place positive integers into an array of size ni such that the product of the integers is ki. As the number of ways may be too large, the answer to the ith query is the number of ways modulo 109 + 7.
 * Return an integer array answer where answer.length == queries.length, and answer[i] is the answer to the ith query.
 * 
 * Example 1:
 * Input: queries = [[2,6],[5,1],[73,660]]
 * Output: [4,1,50734910]
 * Explanation: Each query is independent.
 * [2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
 * [5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
 * [73,660]: There are 1050 ways to fill an array of size 73 that multiply to 660. 1050 % (109 + 7) = 50734910.
 * 
 * Example 2:
 * Input: queries = [[1,1],[2,2],[3,3],[4,4],[5,5]]
 * Output: [1,2,3,10,5]
 * Explanation: Each query is independent.
 * [1,1]: There is 1 way to fill an array of size 1 that multiply to 1: [1].
 * [2,2]: There are 2 ways to fill an array of size 2 that multiply to 2: [1,2], [2,1].
 * [3,3]: There are 3 ways to fill an array of size 3 that multiply to 3: [1,1,3], [1,3,1], [3,1,1].
 * [4,4]: There are 10 ways to fill an array of size 4 that multiply to 4: [1,1,1,4], [1,1,4,1], [1,4,1,1], [4,1,1,1], [1,2,2,2], [2,1,2,2], [2,2,1,2], [2,2,2,1], [3,1,1,2], [3,1,2,1].
 * 
 * Constraints:
 * 1 <= queries.length <= 104
 * 1 <= ni, ki <= 104
 * 
 */
#include <vector>
using namespace std;

class Solution {
private:
    static const int MOD = 1e9 + 7;
    static const int MAXK = 10000;  // ki 的最大值
    static const int MAXN = 10000;  // ni 的最大值
    static const int MAXP = 15;     // 质因子个数上限（2^15 > 10000）
    int C[MAXN + MAXP + 5][MAXP + 5];  // 组合数表

public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        // 预处理组合数 C[i][j] = C(i, j) % MOD
        C[0][0] = 1;
        for (int i = 1; i <= MAXN + MAXP; ++i) {
            C[i][0] = 1;
            for (int j = 1; j <= MAXP; ++j) {
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
            }
        }

        vector<int> ans;
        for (auto& q : queries) {
            int n = q[0], k = q[1];
            long long res = 1;

            // 质因数分解 k
            int temp = k;
            for (int i = 2; i * i <= temp; ++i) {
                if (temp % i == 0) {
                    int cnt = 0;
                    while (temp % i == 0) {
                        temp /= i;
                        ++cnt;
                    }
                    // 将 cnt 个相同小球放入 n 个盒子（允许空盒）
                    // 方案数为 C(cnt + n - 1, cnt)
                    res = res * C[cnt + n - 1][cnt] % MOD;
                }
            }
            // 处理剩余的大质因子（如果有）
            if (temp > 1) {
                // 此时 cnt = 1，方案数为 C(1 + n - 1, 1) = C(n, 1) = n
                res = res * n % MOD;
            }

            ans.push_back(res);
        }
        return ans;
    }
};