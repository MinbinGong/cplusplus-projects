/*
 * Find the Shortest Superstring
 *
 * Given an array A of strings, find any smallest string that contains each string in A as a substring.
 *
 * We may assume that no string in A is substring of another string in A.
 * 
 * Example 1:
 * Input: ["alex","loves","leetcode"]
 * Output: "alexlovesleetcode"
 * Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
 * 
 * Example 2:
 * Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
 * Output: "gctaagttcatgcatc"
 * 
 * Note:
 * 1 <= A.length <= 12
 * 1 <= A[i].length <= 20
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> overlap(n, vector<int>(n, 0));

        // 计算两个单词的最大重叠长度
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                int len1 = words[i].size(), len2 = words[j].size();
                int maxOverlap = min(len1, len2);
                for (int k = maxOverlap; k >= 0; --k) {
                    if (words[i].substr(len1 - k) == words[j].substr(0, k)) {
                        overlap[i][j] = k;
                        break;
                    }
                }
            }
        }

        vector<vector<string>> dp(1 << n, vector<string>(n));
        vector<vector<int>> len(1 << n, vector<int>(n, INT_MAX / 2));

        // 初始化
        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = words[i];
            len[1 << i][i] = words[i].size();
        }

        // DP转移
        for (int mask = 1; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) continue;
                for (int j = 0; j < n; ++j) {
                    if (mask & (1 << j)) continue;
                    int newMask = mask | (1 << j);
                    int newLen = len[mask][i] + words[j].size() - overlap[i][j];
                    if (newLen < len[newMask][j]) {
                        len[newMask][j] = newLen;
                        dp[newMask][j] = dp[mask][i] + words[j].substr(overlap[i][j]);
                    }
                }
            }
        }

        // 找出最优解
        int finalMask = (1 << n) - 1;
        string result;
        int minLen = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (len[finalMask][i] < minLen) {
                minLen = len[finalMask][i];
                result = dp[finalMask][i];
            }
        }
        return result;
    }
};