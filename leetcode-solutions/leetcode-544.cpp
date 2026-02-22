/*
 * 544. Output Contest Matches
 * 
 * Given an integer n, return the nth row of the Pascal's triangle.
 * 
 * Note:
 * The row index starts from 0.
 * 
 * Example:
 * Input: 3
 * Output: [1,3,3,1]
 * 
 * Follow up:
 * Could you optimize your algorithm to use only O(k) extra space?
 * 
 * Constraints:
 * 1 <= n <= 30
 */
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

 class Solution1 {
public:
    string findContestMatch(int n) {
        // 1. 初始化：创建包含 "1" 到 "n" 的字符串向量
        vector<string> teams;
        for (int i = 1; i <= n; ++i) {
            teams.push_back(to_string(i));
        }

        // 2. 迭代配对，直到只剩一个元素
        while (teams.size() > 1) {
            vector<string> nextRound;
            int len = teams.size();
            // 将第 i 个与倒数第 i 个配对
            for (int i = 0; i < len / 2; ++i) {
                string pair = "(" + teams[i] + "," + teams[len - 1 - i] + ")";
                nextRound.push_back(pair);
            }
            // 更新为下一轮的队伍列表
            teams = nextRound;
        }

        // 3. 返回最终结果
        return teams[0];
    }
};

class Solution2 {
public:
    string findContestMatch(int n) {
        // 1. 初始化：创建包含 "1" 到 "n" 的字符串向量
        vector<string> teams(n);
        for (int i = 0; i < n; ++i) {
            teams[i] = to_string(i + 1);
        }

        // 2. 迭代配对，m 表示当前轮次的队伍数量
        for (int m = n; m > 1; m /= 2) {
            // 将第 i 个与倒数第 i 个配对，结果存回 teams[i]
            for (int i = 0; i < m / 2; ++i) {
                teams[i] = "(" + teams[i] + "," + teams[m - 1 - i] + ")";
            }
        }

        // 3. 返回最终结果
        return teams[0];
    }
};