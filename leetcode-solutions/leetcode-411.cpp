/*
 * Minimum Unique Word Abbreviation
 *
 * A string such as "word" contains the following abbreviations:
 * ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
 * 
 * Given a target string and a set of strings in a dictionary, find an abbreviation of this target string with the smallest possible length such that it does not conflict with abbreviations of the strings in the dictionary.
 * 
 * Example 1:
 * Input: target = "apple", dictionary = ["blade"]
 * Output: "a4"
 * Explanation: The best abbreviation for "apple" is "a4" because it only has 1 character, which is the same as the character "a" in "blade".
 * 
 * Example 2:
 * Input: target = "apple", dictionary = ["blade","plain","amber"]
 * Output: "1p3"
 * Explanation: The best abbreviation for "apple" is "1p3" because it only has 3 characters, which is the same as the characters "p" and "e" in "plain" and "amber".
 * 
 * Constraints:
 * 1 <= target.length <= 20
 * 1 <= dictionary.length <= 1000
 * 1 <= dictionary[i].length <= 20
 * target and dictionary[i] consist of lowercase English letters only.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        int m = target.size();
        // 1. 过滤掉长度不一致的单词，并计算每个单词的差异掩码
        vector<int> masks;
        for (const string& word : dictionary) {
            if (word.size() != m) continue;
            int mask = 0;
            for (int i = 0; i < m; ++i) {
                if (word[i] != target[i]) {
                    mask |= (1 << (m - 1 - i)); // 注意位序：高位对应左边字符
                }
            }
            masks.push_back(mask);
        }
        // 如果没有等长单词，直接返回数字缩写（如 "4"）
        if (masks.empty()) return to_string(m);

        // 2. 枚举所有可能的缩写掩码 (0 到 2^m - 1)
        //    1 表示保留原字符，0 表示被数字替换
        int bestLen = m + 1;
        string bestAbbr;
        for (int cand = 0; cand < (1 << m); ++cand) {
            // 检查该缩写是否与所有字典单词冲突
            bool ok = true;
            for (int mask : masks) {
                if ((cand & mask) == 0) { // 没有位差异，冲突
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            // 将掩码转换为缩写字符串
            string abbr = maskToAbbr(target, cand);
            int len = abbrLength(abbr);
            if (len < bestLen) {
                bestLen = len;
                bestAbbr = abbr;
            }
        }
        return bestAbbr;
    }

private:
    // 将掩码转换为缩写形式：1保留原字符，0替换为数字
    string maskToAbbr(const string& target, int mask) {
        int n = target.size();
        string res;
        int cnt = 0; // 连续0的个数
        for (int i = 0; i < n; ++i) {
            int bitPos = n - 1 - i; // 当前字符对应掩码的位（左边是高位）
            if (mask & (1 << bitPos)) { // 保留字符
                if (cnt > 0) {
                    res += to_string(cnt);
                    cnt = 0;
                }
                res += target[i];
            } else {
                cnt++;
            }
        }
        if (cnt > 0) res += to_string(cnt);
        return res;
    }

    // 计算缩写字符串的长度（每个字母或数字块计为1）
    int abbrLength(const string& abbr) {
        int len = 0;
        for (int i = 0; i < abbr.size(); ) {
            if (isdigit(abbr[i])) {
                while (i < abbr.size() && isdigit(abbr[i])) i++;
            } else {
                i++;
            }
            len++;
        }
        return len;
    }
};