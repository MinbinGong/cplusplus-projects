/*
 * 1820. Maximum Number of Accepted Invitations
 * 
 * There are m boys and n girls in a class attending an upcoming party.
 * 
 * You are given an m x n integer matrix grid, where grid[i][j] equals 0 or 1.
 * If grid[i][j] == 1, then that means the ith boy can invite the jth girl to the party.
 * A boy can invite at most one girl, and a girl can accept at most one invitation from a boy.
 * 
 * Return the maximum possible number of accepted invitations.
 * 
 * Example 1:
 * Input: grid = [[1,1,1],
 *                [1,0,1],
 *                [0,0,1]]
 * Output: 3
 * Explanation: The invitations are sent as follows:
 * - The 1st boy invites the 2nd girl.
 * - The 2nd boy invites the 1st girl.
 * - The 3rd boy invites the 3rd girl.
 * 
 * Example 2:
 * Input: grid = [[1,0,1,0],
 *                [1,0,0,0],
 *                [0,0,1,0],
 *                [1,1,1,0]]
 * Output: 3
 * Explanation: The invitations are sent as follows:
 * - The 1st boy invites the 3rd girl.
 * - The 2nd boy invites the 1st girl.
 * - The 3rd boy invites no one.
 * - The 4th boy invites the 2nd girl.
 * 
 * Constraints:
 * 
 * grid.length == m
 * grid[i].length == n
 * 1 <= m, n <= 200
 * grid[i][j] is either 0 or 1.
 * 
 */
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int maximumInvitations(vector<vector<int>>& grid) {
        int m = grid.size();    // 男孩数量
        int n = grid[0].size(); // 女孩数量
        vector<int> match(n, -1); // match[j] 表示当前匹配给女孩 j 的男孩索引，-1 表示未匹配
        int ans = 0;
        
        // 辅助函数：尝试为男孩 i 寻找匹配
        function<bool(int, vector<bool>&)> find = [&](int i, vector<bool>& vis) -> bool {
            for (int j = 0; j < n; ++j) {
                // 如果男孩 i 可以邀请女孩 j，且女孩 j 在本轮未被尝试过
                if (grid[i][j] && !vis[j]) {
                    vis[j] = true;
                    // 如果女孩 j 没有匹配，或者可以为她当前的匹配男孩找到新的匹配
                    if (match[j] == -1 || find(match[j], vis)) {
                        match[j] = i;
                        return true;
                    }
                }
            }
            return false;
        };
        
        // 对每个男孩尝试匹配
        for (int i = 0; i < m; ++i) {
            vector<bool> vis(n, false); // 记录在当前男孩的尝试中，哪些女孩已被访问
            if (find(i, vis)) {
                ++ans;
            }
        }
        
        return ans;
    }
};
