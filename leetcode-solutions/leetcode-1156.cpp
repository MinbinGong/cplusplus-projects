/**
 * 1156. Swap For Longest Repeated Character Substring
 * Medium
 * 
 * (This problem is an interactive problem.)
 * 
 * Given a string text, we are allowed to swap two of the characters in the string. Find the length of the longest substring with repeated characters.
 * 
 * Example 1:
 * Input: text = "ababa"
 * Output: 3
 * Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa", which its length is 3.
 * 
 * Example 2:
 * Input: text = "aaabaaa"
 * Output: 6
 * Explanation: Swap 'b' with the last 'a' (or the first 'a'), and we get longest repeated character substring "aaaaaa", which its length is 6.
 * 
 * Example 3:
 * Input: text = "aaabbaaa"
 * Output: 4
 * 
 * Example 4:
 * Input: text = "aaaaa"
 * Output: 5
 * 
 * Example 5:
 * Input: text = "abcdef"
 * Output: 1
 * 
 * Note:
 * 1 <= text.length <= 20000
 * text consist of lowercase English characters only.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int maxRepOpt1(string text) {
        int n = text.size();
        vector<int> total(26, 0);
        for (char c : text) total[c - 'a']++;

        // 记录每个字符的连续段，存储 (起始索引, 结束索引)
        vector<vector<pair<int, int>>> segs(26);
        int i = 0;
        while (i < n) {
            int j = i;
            while (j + 1 < n && text[j + 1] == text[i]) j++;
            int c = text[i] - 'a';
            segs[c].push_back({i, j});
            i = j + 1;
        }

        int ans = 0;
        for (int c = 0; c < 26; ++c) {
            int tot = total[c];
            auto &vec = segs[c];
            if (vec.empty()) continue;

            // 单个段的情况
            for (auto &p : vec) {
                int len = p.second - p.first + 1;
                ans = max(ans, len);
                if (tot > len) ans = max(ans, len + 1);
            }

            // 相邻段的情况（中间只隔一个字符）
            for (int k = 0; k + 1 < vec.size(); ++k) {
                int end1 = vec[k].second;
                int start2 = vec[k + 1].first;
                if (end1 + 2 == start2) { // 中间恰好一个字符
                    int len1 = vec[k].second - vec[k].first + 1;
                    int len2 = vec[k + 1].second - vec[k + 1].first + 1;
                    int sum = len1 + len2;
                    if (tot > sum) {
                        ans = max(ans, sum + 1);
                    } else {
                        ans = max(ans, sum); // tot == sum
                    }
                }
            }
        }
        return ans;
    }
};