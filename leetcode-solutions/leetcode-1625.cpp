/**
 * 1625. Lexicographically Smallest String After Applying Operations
 * 
 * You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.
 * 
 * You can apply either of the following two operations any number of times and in any order on s:
 * Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
 * Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
 * Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.
 * 
 * Example 1:
 * Input: s = "5525", a = 9, b = 2
 * Output: "2050"
 * Explanation: We can apply the following operations:
 * Start:  "5525"
 * Rotate: "2555"
 * Add:    "2454"
 * Add:    "2353"
 * Rotate: "5323"
 * Add:    "5222"
 * Add:    "5121"
 * Rotate: "2151"
 * Add:    "2050"
 * There is no way to obtain a string that is lexicographically smaller than "2050".
 * 
 * Example 2:
 * Input: s = "74", a = 5, b = 1
 * Output: "24"
 * Explanation: We can apply the following operations:
 * Start:  "74"
 * Rotate: "47"
 * Add:    "42"
 * Rotate: "24"
 * There is no way to obtain a string that is lexicographically smaller than "24".
 * 
 * Constraints:
 * 2 <= s.length <= 100
 * s.length is even.
 * s consists of digits from 0 to 9 only.
 * 1 <= a <= 9
 * 1 <= b <= s.length - 1
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        int n = s.size();
        // 状态：shift 表示向右旋转的偏移量，add 表示奇数位累加的总和（模10）
        // visited[shift][add] 表示是否访问过
        vector<vector<bool>> visited(n, vector<bool>(10, false));
        queue<pair<int, int>> q;
        q.push({0, 0});
        visited[0][0] = true;
        string ans = s; // 初始答案
        
        // 生成当前状态对应的字符串
        auto getString = [&](int shift, int add) -> string {
            string res(n, '0');
            for (int i = 0; i < n; ++i) {
                // 当前字符串的第 i 个字符对应原字符串的 (i - shift + n) % n
                int idx = (i - shift + n) % n;
                int digit = s[idx] - '0';
                if (i % 2 == 1) { // 奇数位加上 add
                    digit = (digit + add) % 10;
                }
                res[i] = digit + '0';
            }
            return res;
        };
        
        while (!q.empty()) {
            auto [shift, add] = q.front();
            q.pop();
            
            // 生成当前状态对应的字符串
            string cur = getString(shift, add);
            if (cur < ans) {
                ans = cur;
            }
            
            // 操作1：累加
            int newAdd = (add + a) % 10;
            if (!visited[shift][newAdd]) {
                visited[shift][newAdd] = true;
                q.push({shift, newAdd});
            }
            
            // 操作2：旋转
            int newShift = (shift + b) % n;
            if (!visited[newShift][add]) {
                visited[newShift][add] = true;
                q.push({newShift, add});
            }
        }
        return ans;
    }
};