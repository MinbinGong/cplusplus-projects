/*
 * Add Bold Tag in String
 * 
 * Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in dict.
 * If two such substrings overlap, you need to wrap them together by only one pair of closed bold tag.
 * Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
 * 
 * Example 1:
 * Input: 
 * s = "abcxyz123"
 * dict = ["abc","123"]
 * Output:
 * "<b>abc</b>xyz<b>123</b>"
 * 
 * Example 2:
 * Input: 
 * s = "aaabbcc"
 * dict = ["aaa","aab","bc"]
 * Output:
 * "<b>aaabbc</b>c"
 * 
 * Note:
 * 1. The given dict won't contain duplicates, and its length won't exceed 100.
 * 2. All the strings in input have length in range [1, 1000].
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    string addBoldTag(string s, vector<string>& dict) {
        int n = s.size();
        // 标记每个字符是否需要加粗
        vector<bool> bold(n, false);
        
        // 收集所有字典单词的长度，用于优化检查
        unordered_set<string> wordSet(dict.begin(), dict.end());
        unordered_set<int> lens;
        int maxLen = 0;
        for (const string& w : dict) {
            lens.insert(w.size());
            maxLen = max(maxLen, (int)w.size());
        }
        
        // 遍历字符串，标记需要加粗的位置
        for (int i = 0; i < n; ++i) {
            // 从当前位置开始，检查所有可能的长度
            for (int len : lens) {
                if (i + len > n) continue;  // 超出范围
                string sub = s.substr(i, len);
                if (wordSet.count(sub)) {
                    // 标记从 i 到 i+len-1 的所有位置为加粗
                    for (int j = i; j < i + len; ++j) {
                        bold[j] = true;
                    }
                }
            }
        }
        
        // 构建结果字符串
        string result;
        for (int i = 0; i < n; ++i) {
            // 当前位置需要加粗且前一个位置不需要加粗（或这是第一个字符），添加开标签
            if (bold[i] && (i == 0 || !bold[i-1])) {
                result += "<b>";
            }
            result += s[i];
            // 当前位置需要加粗且后一个位置不需要加粗（或这是最后一个字符），添加闭标签
            if (bold[i] && (i == n-1 || !bold[i+1])) {
                result += "</b>";
            }
        }
        
        return result;
    }
};