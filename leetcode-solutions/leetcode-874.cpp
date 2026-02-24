/**
 * 874. Walking Robot Simulation
 * 
 * Example 1:
 * Input: commands = [4,-1,3], obstacles = []
 * Output: 25
 * Explanation: robot will go to (3, 4)
 * 
 * Example 2:
 * Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
 * Output: 65
 * Explanation: robot will be stuck at (1, 4) before turning left and going to (1, 8)
 * 
 * Note:
 * 0 <= commands.length <= 10000
 * 0 <= obstacles.length <= 10000
 * -30000 <= obstacle[i][0] <= 30000
 * -30000 <= obstacle[i][1] <= 30000
 * The answer is guaranteed to be less than 2 ^ 31.
 * 
 */
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // 方向数组：北、东、南、西
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int dir = 0; // 初始朝北
        int x = 0, y = 0;
        int ans = 0;

        // 用集合存储障碍物坐标以便快速判断
        set<pair<int, int>> obstacleSet;
        for (auto& ob : obstacles) {
            obstacleSet.insert({ob[0], ob[1]});
        }

        for (int cmd : commands) {
            if (cmd == -2) { // 左转
                dir = (dir + 3) % 4;
            } else if (cmd == -1) { // 右转
                dir = (dir + 1) % 4;
            } else {
                for (int i = 0; i < cmd; ++i) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    // 遇到障碍物则停止移动
                    if (obstacleSet.count({nx, ny})) {
                        break;
                    }
                    x = nx;
                    y = ny;
                    ans = max(ans, x * x + y * y);
                }
            }
        }
        return ans;
    }
};