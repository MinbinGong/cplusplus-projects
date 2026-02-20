/*
 * Flip Game II
 * 
 * You are playing the following Flip Game with your friend:
 * 
 * Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--".
 * The game ends when a person can no longer make a move and therefore the other person will be the winner.
 * 
 * Write a function to determine if the starting player can guarantee a win.
 * 
 * Example:
 * Input: s = "++++"
 * Output: true 
 * Explanation: The starting player can guarantee a win by flipping the middle "++" to become "+--+".
 * 
 * Note:
 * 1 <= s.length <= 60
 * s[i] is either a '+' or a '-'.
 * 
 */
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;

// Solution1: 深度优先搜索 + 记忆化
class Solution1 {
public:
    bool canWin(string s) {
        // 使用哈希表记录已经判断过的字符串是否能赢
        unordered_map<string, bool> memo;
        return dfs(s, memo);
    }

private:
    bool dfs(string& s, unordered_map<string, bool>& memo) {
        // 如果当前局面已经计算过，直接返回结果
        if (memo.count(s)) return memo[s];

        // 遍历字符串，寻找可翻转的 "++"
        for (int i = 0; i < (int)s.size() - 1; ++i) {
            if (s[i] == '+' && s[i + 1] == '+') {
                // 进行翻转操作
                s[i] = s[i + 1] = '-';

                // 递归判断对手是否必败
                bool opponentWin = dfs(s, memo);

                // 回溯，恢复原状
                s[i] = s[i + 1] = '+';

                // 如果对手必败，则当前玩家必胜
                if (!opponentWin) {
                    memo[s] = true;
                    return true;
                }
            }
        }

        // 遍历完所有可能，都没有找到必胜策略，则当前玩家必败
        memo[s] = false;
        return false;
    }
};

// Solution2: 动态规划 +  Grundy 数
class Solution2 {
public:
    bool canWin(string s) {
        vector<int> segments;
        s.push_back('-'); // 哨兵，方便处理最后一段
        int cnt = 0, maxLen = 0;

        // 将连续 '+' 的长度提取出来
        for (char c : s) {
            if (c == '+') {
                ++cnt;
            } else {
                if (cnt > 0) {
                    segments.push_back(cnt);
                    maxLen = max(maxLen, cnt);
                    cnt = 0;
                }
            }
        }

        // 如果没有连续 '+' 或最大长度小于2，无法进行任何操作，先手必败
        if (maxLen <= 1) return false;

        // 计算每个长度的 Grundy 数 (SG值)
        vector<int> sg(maxLen + 1, 0);
        for (int i = 2; i <= maxLen; ++i) {
            unordered_set<int> mexSet;
            // 对于长度为 i 的段，尝试在每一个位置翻转 "++"
            for (int j = 0; j < i / 2; ++j) {
                // 翻转后，原段被拆分为两个长度分别为 j 和 i-j-2 的子段
                mexSet.insert(sg[j] ^ sg[i - j - 2]);
            }
            // 计算 mex (最小的非负整数，不在集合中)
            int g = 0;
            while (mexSet.count(g)) ++g;
            sg[i] = g;
        }

        // 计算所有子段 SG 值的异或和
        int xorSum = 0;
        for (int len : segments) {
            xorSum ^= sg[len];
        }

        return xorSum != 0;
    }
};