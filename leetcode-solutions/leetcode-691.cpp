/*
 * Sticker to Spell Word
 *
 * We are given N different types of stickers. Each sticker has a lowercase English word on it.
 *
 * You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.
 *
 * You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
 *
 * What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.
 * 
 * Example 1:
 *
 * Input:
 *
 * ["with", "example", "science"], "thehat"
 *
 * Output:
 *
 * 3
 *
 * Explanation:
 *
 * We can use 2 "with" stickers, and 1 "example" sticker.
 * After cutting and rearrange the letters of those stickers, we can form the target "thehat".
 * 
 * Example 2:
 *
 * Input:
 *
 * ["notice", "possible"], "basicbasic"
 *
 * Output:
 *
 * -1
 *
 * Explanation:
 *
 * We can't form the target "basicbasic" from cutting letters from the given stickers.
 * 
 * Note:
 * 
 * N will be in the range of [1, 50].
 * M will be in the range of [1, 15].
 * target will have length in the range of [1, 15].
 * stickers will have length in the range of [1, 100].
 * stickers[i] will have length in the range of [1, 100].
 * stickers[i][j] will be a lowercase letter.
 * target[i] will be a lowercase letter.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution1 {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = stickers.size();
        int m = target.size();
        // 统计每个贴纸中每个字母的出现次数
        vector<vector<int>> stickerCount(n, vector<int>(26, 0));
        for (int i = 0; i < n; ++i) {
            for (char c : stickers[i]) {
                stickerCount[i][c - 'a']++;
            }
        }

        // 记忆化数组，dp[mask] 表示拼成 mask 状态所需最少贴纸数，-1表示未计算
        vector<int> dp(1 << m, -1);
        dp[0] = 0;

        // 深度优先搜索（记忆化）
        function<int(int)> dfs = [&](int mask) -> int {
            if (dp[mask] != -1) return dp[mask];
            int res = INT_MAX;
            // 尝试每个贴纸
            for (int i = 0; i < n; ++i) {
                vector<int> cnt = stickerCount[i]; // 当前贴纸的可用字符
                int newMask = mask;
                // 用该贴纸尽可能覆盖未匹配的字符
                for (int j = 0; j < m; ++j) {
                    if ((newMask >> j) & 1) continue; // 已匹配
                    char c = target[j];
                    if (cnt[c - 'a'] > 0) {
                        cnt[c - 'a']--;
                        newMask |= (1 << j);
                    }
                }
                if (newMask != mask) { // 贴纸有贡献
                    int sub = dfs(newMask);
                    if (sub != -1) {
                        res = min(res, sub + 1);
                    }
                }
            }
            dp[mask] = (res == INT_MAX) ? -1 : res;
            return dp[mask];
        };

        return dfs((1 << m) - 1);
    }
};