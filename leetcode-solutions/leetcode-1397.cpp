/**
 * 1397. Find All Good Strings
 * 
 * Given the integers n, s, and a string evil, return the number of good strings.
 * A good string has the size n, it is lexicographically greater than or equal to s, and it does not contain the string evil as a substring.
 * Since the answer can be a huge number, return this modulo 10^9 + 7.
 * 
 * Example 1:
 * Input: n = 2, s = "aa", evil = "b"
 * Output: 81
 * Explanation: There are 81 strings greater than or equal to "aa" that do not contain the string "b" as a substring.
 * 
 * Example 2:
 * Input: n = 8, s = "leetcode", evil = "leet"
 * Output: 0
 * Explanation: All strings greater than or equal to "leetcode" contain the string "leet" as a substring.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        this->s1 = s1;
        this->s2 = s2;
        this->evil = evil;
        this->n = n;
        this->m = evil.size();
        mod = 1e9 + 7;
        
        // 构建 KMP 的 next 数组（失配函数）
        getNext(evil);
        
        // 初始化记忆化数组为 -1
        memset(dp, -1, sizeof dp);
        
        // 从第 0 位开始，evil 匹配长度为 0，上下界均受到限制
        return dfs(0, 0, true, true);
    }

private:
    string s1, s2, evil;
    int n, m;
    long long mod;
    int ne[60];                     // KMP 的 next 数组
    long long dp[550][55][2][2];    // 记忆化：位置，evil匹配长度，是否受上界限制，是否受下界限制
    
    // 构建 next 数组
    void getNext(const string& evil) {
        int i = 0, k = -1;
        ne[0] = -1;
        while (i < m) {
            if (k == -1 || evil[i] == evil[k]) {
                ++i, ++k;
                ne[i] = k;
            } else {
                k = ne[k];
            }
        }
    }
    
    // DFS + 记忆化
    // now: 当前要填第几位 (0-indexed)
    // enow: 当前已匹配 evil 的长度
    // ulimit: 当前位是否受到 s2 的上界限制（true 表示前几位与 s2 完全相等）
    // dlimit: 当前位是否受到 s1 的下界限制（true 表示前几位与 s1 完全相等）
    long long dfs(int now, int enow, bool ulimit, bool dlimit) {
        // 剪枝：已经匹配到完整的 evil，不合法
        if (enow == m) return 0;
        // 递归边界：已经填完所有位，找到一个合法字符串
        if (now == n) return 1;
        
        // 记忆化
        if (dp[now][enow][ulimit][dlimit] != -1) 
            return dp[now][enow][ulimit][dlimit];
        
        long long res = 0;
        // 当前位可以填的字符范围
        char up = ulimit ? s2[now] : 'z';
        char down = dlimit ? s1[now] : 'a';
        
        // 遍历所有可能的字符
        for (char c = down; c <= up; ++c) {
            // 使用 KMP 计算填入字符 c 后，新的匹配长度
            int loc = enow;
            while (loc != -1 && c != evil[loc]) 
                loc = ne[loc];
            int new_enow = loc + 1;   // 匹配成功则长度+1，否则可能回到0
            
            // 递归下一层
            // ulimit 更新：只有当前受上界限制且当前字符恰好等于上界字符时，下一层仍受限制
            // dlimit 更新：只有当前受下界限制且当前字符恰好等于下界字符时，下一层仍受限制
            res = (res + dfs(now + 1, new_enow, 
                            ulimit && (c == up), 
                            dlimit && (c == down))) % mod;
        }
        
        return dp[now][enow][ulimit][dlimit] = res;
    }
};