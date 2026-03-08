/**
 * 1659. Maximize Grid Happiness
 * 
 * You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.
 * 
 * You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.
 * 
 * The happiness of each person is calculated as follows:
 * Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
 * Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
 * Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.
 * 
 * The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.
 * 
 * Example 1:
 * Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
 * Output: 240
 * Explanation: Assume the grid is 1-indexed with coordinates (row, column).
 * We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
 * - Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
 * - Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
 * - Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
 * The grid happiness is 120 + 60 + 60 = 240.
 * 
 * Example 2:
 * Input: m = 3, n = 1, introvertsCount = 2, extrovertsCount = 1
 * Output: 260
 * Explanation: Place the two introverts in (1,1) and (3,1) and the extrovert at (2,1).
 * - Introvert at (1,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 * - Introvert at (3,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 * - Extrovert at (2,1) happiness: 40 (starting happiness) + (2 * 20) (2 neighbors) = 80
 * The grid happiness is 90 + 90 + 80 = 260.
 * 
 * Example 3:
 * Input: m = 2, n = 2, introvertsCount = 4, extrovertsCount = 0
 * Output: 240
 * Explanation: Place the four introverts in (1,1), (1,2), (2,1), and (2,2).
 * - Introvert at (1,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 * - Introvert at (1,2) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 * - Introvert at (2,1) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 * - Introvert at (2,2) happiness: 120 (starting happiness) - (1 * 30) (1 neighbor) = 90
 * The grid happiness is 90 + 90 + 90 + 90 = 360.
 * 
 * Constraints:
 * 1 <= m, n <= 5
 * 0 <= introvertsCount, extrovertsCount <= min(m * n, 6)   
 * 
 */
#include <vector>
#include <cmath>
using namespace std;

class Solution {
private:
    int m, n;
    int n3;                          // 3^n，一行所有可能的状态数
    vector<vector<int>> bits;         // bits[mask][col] 表示状态mask在第col列的值 (0/1/2)
    vector<int> in, ex;               // in[mask], ex[mask] 表示状态mask中内向和外向的人数
    vector<int> score;                // score[mask] 行内分数（包含基本分 + 左右邻居影响）
    vector<vector<int>> trans;        // trans[mask1][mask2] 两行相邻时的行间分数
    vector<vector<vector<vector<int>>>> memo; // 记忆化数组

    // 邻居影响矩阵，h[a][b] 表示类型a与类型b相邻时的分数变化
    // 0:空，1:内向，2:外向
    const int h[3][3] = {{0, 0, 0}, {0, -60, -10}, {0, -10, 40}};

public:
    int getMaxGridHappiness(int m_, int n_, int introvertsCount, int extrovertsCount) {
        m = m_; n = n_;
        n3 = pow(3, n);
        
        // 1. 预处理所有状态
        bits.resize(n3, vector<int>(n));
        in.resize(n3, 0);
        ex.resize(n3, 0);
        score.resize(n3, 0);
        
        for (int mask = 0; mask < n3; ++mask) {
            int tmp = mask;
            // 解析三进制的每一位
            for (int j = 0; j < n; ++j) {
                bits[mask][j] = tmp % 3;
                tmp /= 3;
                if (bits[mask][j] == 1) {
                    in[mask]++;
                    score[mask] += 120;           // 内向基础分
                } else if (bits[mask][j] == 2) {
                    ex[mask]++;
                    score[mask] += 40;             // 外向基础分
                }
            }
            // 计算左右相邻影响（同一行内）
            for (int j = 1; j < n; ++j) {
                int left = bits[mask][j-1];
                int right = bits[mask][j];
                score[mask] += h[left][right];
            }
        }
        
        // 2. 预处理两行之间的影响
        trans.resize(n3, vector<int>(n3, 0));
        for (int up = 0; up < n3; ++up) {
            for (int down = 0; down < n3; ++down) {
                for (int j = 0; j < n; ++j) {
                    trans[up][down] += h[bits[up][j]][bits[down][j]];
                }
            }
        }
        
        // 3. 记忆化搜索（dp[row][preMask][ic][ec]）
        // 注意：preMask 为上一行的状态，对于第一行，preMask=0（虚拟的空行）
        memo.resize(m, vector<vector<vector<int>>>(
            n3, vector<vector<int>>(
                introvertsCount + 1, vector<int>(extrovertsCount + 1, -1))));
        
        return dfs(0, 0, introvertsCount, extrovertsCount);
    }
    
    int dfs(int row, int preMask, int ic, int ec) {
        if (row == m || (ic == 0 && ec == 0)) return 0;
        if (memo[row][preMask][ic][ec] != -1) return memo[row][preMask][ic][ec];
        
        int res = 0;
        // 枚举当前行的所有可能状态
        for (int curMask = 0; curMask < n3; ++curMask) {
            if (in[curMask] > ic || ex[curMask] > ec) continue; // 人数不够
            int curScore = score[curMask] + trans[preMask][curMask];
            curScore += dfs(row + 1, curMask, ic - in[curMask], ec - ex[curMask]);
            res = max(res, curScore);
        }
        return memo[row][preMask][ic][ec] = res;
    }
};