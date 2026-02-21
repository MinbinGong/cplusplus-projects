/*
 * Freedom Trail
 *
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
 *
 * Given a string ring that represents the code engraved on the outer ring and another string key that represents the keyword that needs to be spelled, return the minimum number of steps to spell all the characters in the keyword.
 *
 * Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating ring clockwise or anticlockwise to make each character of the string key aligned at the "12:00" direction and then by pressing the center button.
 *
 * At the stage of rotating the ring to spell the key character key[i]:
 * You can rotate the ring clockwise or anticlockwise by one place, which counts as one step. The final purpose of the rotation is to align one of ring's characters at the "12:00" direction, where this character must equal key[i].
 * 
 * Constraints:
 * 1 <= ring.length, key.length <= 100
 * ring and key consist of only lower case English letters.
 * It is guaranteed that key could always be spelled by rotating ring.
 * 
 */
#include <vector>
#include <string>
#include <functional>
#include <climits>

using namespace std;

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size();
        int m = key.size();

        // 记录每个字符在圆环上的所有位置
        vector<int> positions[26];
        for (int i = 0; i < n; ++i) {
            positions[ring[i] - 'a'].push_back(i);
        }

        // 记忆化搜索 dp[i][j] 表示当前圆环指针在位置 i，要拼写 key[j..] 所需的最少步数
        vector<vector<int>> dp(n, vector<int>(m, -1));

        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (j == m) return 0;               // 已经拼完所有字符
            if (dp[i][j] != -1) return dp[i][j];

            int c = key[j] - 'a';
            int best = INT_MAX;

            // 尝试所有可能的目标位置 t（即 key[j] 在圆环上的位置）
            for (int t : positions[c]) {
                int dist = min(abs(t - i), n - abs(t - i));   // 顺时针或逆时针旋转的最小步数
                best = min(best, dist + 1 + dfs(t, j + 1));   // 旋转 + 按按钮 + 后续拼写
            }

            dp[i][j] = best;
            return best;
        };

        // 初始指针在位置 0
        return dfs(0, 0);
    }
};