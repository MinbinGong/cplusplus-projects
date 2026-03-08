/*
 * 1654. Minimum Jumps to Reach Home
 *
 * A certain bug's home is on the x-axis at position x. Help them get there from position 0.
 * 
 * The bug jumps according to the following rules:
 * It can jump exactly a positions forward (to the right).
 * It can jump exactly b positions backward (to the left).
 * It cannot jump backward twice in a row.
 * It cannot jump to any forbidden positions.
 * The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.
 * 
 * Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.
 * 
 * Example 1:
 * Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
 * Output: 3
 * Explanation: In 3 jumps, the bug jumps from 0 --> 3 --> 12 --> 9.
 * 
 * Example 2:
 * Input: forbidden = [8,3,16,6,12,20], a = 15, b = 13, x = 11
 * Output: -1
 * 
 * Example 3:
 * Input: forbidden = [1,6,2,14,5,17,4], a = 16, b = 9, x = 7
 * Output: 2
 * Explanation: In 2 jumps, the bug jumps from 0 --> 16 --> 7.
 * 
 * Constraints:
 * 1 <= forbidden.length <= 1000
 * 1 <= a, b, forbidden[i] <= 2000
 * 0 <= x <= 2000
 * All the elements in forbidden are distinct.
 * Position x is not forbidden.
 * 
 */
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        // 使用无序集合记录禁止位置，方便快速查找
        unordered_set<int> forbiddenSet(forbidden.begin(), forbidden.end());
        // 标记访问过的状态: 位置 * 2 + (是否可向后跳) 或直接用二维布尔数组
        // 这里使用二维布尔数组 visited[pos][canBack] 更清晰
        // 根据题目提示，x <= 2000, a,b <= 2000，上界可设为 6000 是一个安全值 [citation:4][citation:7]
        const int MAX_POS = 6000;
        vector<vector<bool>> visited(MAX_POS + 1, vector<bool>(2, false));
        
        // 队列元素: {当前位置, 当前步数, 是否允许向后跳 (1表示允许, 0表示不允许)}
        queue<tuple<int, int, int>> q;
        q.emplace(0, 0, 1); // 起点允许向后跳（但向后跳需要位置>0）
        visited[0][1] = true;

        while (!q.empty()) {
            auto [pos, steps, canBack] = q.front();
            q.pop();

            if (pos == x) {
                return steps;
            }

            // 1. 向前跳 a 步
            int nextPos = pos + a;
            if (nextPos <= MAX_POS && !forbiddenSet.count(nextPos) && !visited[nextPos][1]) {
                visited[nextPos][1] = true; // 向前跳后，允许下一次向后跳
                q.emplace(nextPos, steps + 1, 1);
            }

            // 2. 向后跳 b 步 (只有当 canBack 为 true 时才可以)
            if (canBack) {
                nextPos = pos - b;
                if (nextPos >= 0 && !forbiddenSet.count(nextPos) && !visited[nextPos][0]) {
                    visited[nextPos][0] = true; // 向后跳后，下一次不允许再向后跳
                    q.emplace(nextPos, steps + 1, 0);
                }
            }
        }

        return -1; // 无法到达
    }
};
