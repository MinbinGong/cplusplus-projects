/*
 * 967. Numbers With Same Consecutive Differences
 *
 * Return all non-negative integers of length n such that the absolute difference between every two consecutive digits is k.
 *
 * Note that every number in the answer must not have leading zeros. For example, 01 has one leading zero and is invalid.
 *
 * You may return the answer in any order.
 *
 * Example 1:
 *
 * Input: n = 3, k = 7
 * Output: [181,292,707,818,929]
 * Explanation: Note that 070 is not a valid number, because it has leading zeroes.
 * 
 * Example 2:
 *
 * Input: n = 2, k = 1
 * Output: [10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]
 * 
 * Note:
 *
 * 2 <= n <= 9
 * 0 <= k <= 9
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        vector<int> res;
        if (n == 1) {
            for (int i = 0; i <= 9; ++i) res.push_back(i);
            return res;
        }
        for (int i = 1; i <= 9; ++i) {
            dfs(n - 1, k, i, res);
        }
        return res;
    }

private:
    void dfs(int remaining, int k, int cur, vector<int>& res) {
        if (remaining == 0) {
            res.push_back(cur);
            return;
        }
        int last = cur % 10;
        int next1 = last + k;
        if (next1 <= 9) {
            dfs(remaining - 1, k, cur * 10 + next1, res);
        }
        int next2 = last - k;
        if (k != 0 && next2 >= 0) {
            dfs(remaining - 1, k, cur * 10 + next2, res);
        }
    }
};