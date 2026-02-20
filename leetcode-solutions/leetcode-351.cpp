/*
 * Android Unlock Patterns
 * 
 * Given an Android 3x3 key lock screen and two integers m and n, where 1 ≤ m ≤ n ≤ 9, count the total number of unlock patterns of the Android lock screen, which consist of minimum of m keys and maximum n keys.
 * 
 * Rules for a valid pattern:
 * Each pattern must connect at least m keys and at most n keys.
 * All the keys must be distinct.
 * If the line connecting two consecutive keys in the pattern passes through any other keys, the other keys must have previously selected in the pattern. No jumps through non selected key is allowed.
 * The order of keys used matters.
 * 
 * Explanation:
 * | 1 | 2 | 3 |
 * | 4 | 5 | 6 |
 * | 7 | 8 | 9 |
 * Invalid move: 4 - 1 - 3 - 6
 * Line 1 - 3 passes through key 2 which had not been selected in the pattern.
 * 
 * Invalid move: 4 - 1 - 9 - 2
 * Line 1 - 9 passes through key 5 which had not been selected in the pattern.
 * 
 * Valid move: 2 - 4 - 1 - 3 - 6
 * Line 1 - 3 is valid because it passes through key 2, which had been selected in the pattern
 * 
 * Valid move: 6 - 5 - 4 - 1 - 9 - 2
 * Line 1 - 9 is valid because it passes through key 5, which had been selected in the pattern.
 * 
 */
#include <vector>
#include <cstring>
using namespace std;

class Solution {
public:
    int numberOfPatterns(int m, int n) {
        // 记录两个数字之间的障碍数字（如果存在）
        int skip[10][10];
        memset(skip, 0, sizeof(skip));
        skip[1][3] = skip[3][1] = 2;
        skip[1][7] = skip[7][1] = 4;
        skip[3][9] = skip[9][3] = 6;
        skip[7][9] = skip[9][7] = 8;
        skip[2][8] = skip[8][2] = 5;
        skip[4][6] = skip[6][4] = 5;
        skip[1][9] = skip[9][1] = 5;
        skip[3][7] = skip[7][3] = 5;

        vector<bool> visited(10, false);
        int total = 0;

        // 利用对称性：1,3,7,9 对称；2,4,6,8 对称；5 单独
        // 从 1 开始，乘以 4
        total += 4 * dfs(1, 1, m, n, visited, skip);
        // 从 2 开始，乘以 4
        total += 4 * dfs(2, 1, m, n, visited, skip);
        // 从 5 开始
        total += dfs(5, 1, m, n, visited, skip);

        return total;
    }

private:
    int dfs(int cur, int len, int m, int n, vector<bool>& visited, int skip[10][10]) {
        if (len > n) return 0;
        int count = 0;
        if (len >= m) count = 1; // 当前长度符合要求，计数当前路径

        visited[cur] = true;
        for (int nxt = 1; nxt <= 9; ++nxt) {
            if (!visited[nxt]) {
                int mid = skip[cur][nxt];
                // 如果中间有障碍且未访问，则不能直接跳
                if (mid == 0 || visited[mid]) {
                    count += dfs(nxt, len + 1, m, n, visited, skip);
                }
            }
        }
        visited[cur] = false;
        return count;
    }
};