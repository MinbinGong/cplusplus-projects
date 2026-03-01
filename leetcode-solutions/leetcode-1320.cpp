/**
 * 1320. Minimum Distance to Type a Word Using Two Fingers
 * 
 * You have a keyboard layout as shown above in the XY plane, where each English uppercase letter is located at some coordinate, for example, the letter A is located at coordinate (0,0), the letter B is located at coordinate (0,1), the letter P is located at coordinate (2,3) and the letter Z is located at coordinate (4,1).
 * 
 * Given the string word, return the minimum total distance to type such string using only two fingers. The distance between coordinates (x1,y1) and (x2,y2) is |x1 - x2| + |y1 - y2|. 
 * 
 * Note that the initial positions of your two fingers are considered free so don't count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.
 * 
 * Example 1:
 * Input: word = "CAKE"
 * Output: 3
 * Explanation: 
 * Using two fingers, one optimal way to type "CAKE" is: 
 * 1. Move your finger from coordinate (0,0) to coordinate (0,1) to type 'C'.
 * 2. Move your finger from coordinate (0,1) to coordinate (2,3) to type 'A'.
 * 3. Move your finger from coordinate (2,3) to coordinate (3,1) to type 'K'.
 * 4. Move your finger from coordinate (3,1) to coordinate (4,1) to type 'E'.
 * 
 * Total distance = 1 + 1 + 2 + 1 = 4.
 * 
 * Example 2:
 * Input: word = "HAPPY"
 * Output: 6
 * Explanation: 
 * One optimal way to type "HAPPY" is:
 * 1. Move your finger from coordinate (0,0) to coordinate (1,1) to type 'H'.
 * 2. Move your finger from coordinate (1,1) to coordinate (2,3) to type 'A'.
 * 3. Move your finger from coordinate (2,3) to coordinate (3,1) to type 'P'.
 * 4. Move your finger from coordinate (3,1) to coordinate (3,2) to type 'P'.
 * 5. Move your finger from coordinate (3,2) to coordinate (4,1) to type 'Y'.
 * 
 * Total distance = 1 + 2 + 2 + 1 + 1 = 7.
 * 
 * Example 3:
 * Input: word = "NEW"
 * Output: 3
 * 
 * Example 4:
 * Input: word = "YEAR"
 * Output: 7
 * 
 * Note:
 * 2 <= word.length <= 300
 * Each word[i] is an English uppercase letter.
 * 
 */
#include <vector>
#include <string>
#include <numeric>
using namespace std;

class Solution {
public:
    int minimumDistance(string word) {
        int n = word.size();
        const int INF = 1e9;
        // 距离函数
        auto dist = [](int a, int b) {
            return abs(a / 6 - b / 6) + abs(a % 6 - b % 6);
        };

        // dp[j][k] 表示当前两根手指分别在 j 和 k 的最小代价
        vector<vector<int>> dp(26, vector<int>(26, INF));
        // 初始状态：未按任何字符，任意位置代价为0
        for (int i = 0; i < 26; ++i)
            for (int j = 0; j < 26; ++j)
                dp[i][j] = 0;

        for (char c : word) {
            int next = c - 'A';
            vector<vector<int>> new_dp(26, vector<int>(26, INF));
            for (int j = 0; j < 26; ++j) {
                for (int k = 0; k < 26; ++k) {
                    if (dp[j][k] == INF) continue;
                    // 用 j 手指按 next
                    new_dp[next][k] = min(new_dp[next][k], dp[j][k] + dist(j, next));
                    // 用 k 手指按 next
                    new_dp[j][next] = min(new_dp[j][next], dp[j][k] + dist(k, next));
                }
            }
            dp = move(new_dp);
        }

        int ans = INF;
        for (int j = 0; j < 26; ++j)
            for (int k = 0; k < 26; ++k)
                ans = min(ans, dp[j][k]);
        return ans;
    }
};