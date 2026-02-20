/*
 * Word Pattern II
 * 
 * Given a pattern and a string str, find if str follows the same pattern.
 * 
 * Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.
 * 
 * Example 1:
 * Input: pattern = "abab", str = "redblueredblue"
 * Output: true
 * 
 * Example 2:
 * Input: pattern = "aaaa", str = "asdasdasdasd"
 * Output: true
 * 
 * Example 3:
 * Input: pattern = "aabb", str = "xyzabcxzyabc"
 * Output: false
 * 
 */
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
private:
    // 用于存储双向映射关系的哈希表
    unordered_map<char, string> charToStr;  // 字符到子串的映射
    unordered_map<string, char> strToChar;  // 子串到字符的映射

public:
    bool wordPatternMatch(string pattern, string s) {
        // 清空映射，确保每次调用都是全新的状态
        charToStr.clear();
        strToChar.clear();
        return dfs(pattern, 0, s, 0);
    }

private:
    /**
     * 深度优先搜索函数
     * @param pattern 模式串
     * @param pIndex  当前要处理的模式字符索引
     * @param s       目标字符串
     * @param sIndex  当前要处理的字符串起始索引
     * @return        是否能匹配成功
     */
    bool dfs(const string& pattern, int pIndex, const string& s, int sIndex) {
        // 终止条件：模式和字符串都处理完毕
        if (pIndex == pattern.length() && sIndex == s.length()) {
            return true;
        }
        // 如果其中一个处理完而另一个没有，说明匹配失败
        if (pIndex == pattern.length() || sIndex == s.length()) {
            return false;
        }

        char curChar = pattern[pIndex];

        // 情况1：当前字符已经有映射
        if (charToStr.count(curChar)) {
            string mappedStr = charToStr[curChar];
            // 检查剩余字符串是否以映射的子串开头
            if (s.compare(sIndex, mappedStr.length(), mappedStr) != 0) {
                return false; // 匹配不上，直接返回 false
            }
            // 匹配成功，继续处理下一个字符
            return dfs(pattern, pIndex + 1, s, sIndex + mappedStr.length());
        }

        // 情况2：当前字符还没有映射，需要尝试所有可能长度的子串
        // 注意剪枝：剩余字符串长度必须至少等于剩余模式字符数（每个字符至少映射一个字符）
        // 同时，当前字符映射的子串长度也不能导致后面的匹配失败
        int maxPossibleLen = s.length() - sIndex - (pattern.length() - pIndex - 1);
        for (int len = 1; len <= maxPossibleLen; ++len) {
            string candidate = s.substr(sIndex, len);

            // 检查这个子串是否已经被映射给其他字符（防止双向映射冲突）
            if (strToChar.count(candidate)) {
                continue; // 如果已被映射，则跳过这个长度
            }

            // 建立新的映射关系
            charToStr[curChar] = candidate;
            strToChar[candidate] = curChar;

            // 递归进行下一层匹配
            if (dfs(pattern, pIndex + 1, s, sIndex + len)) {
                return true; // 找到可行解，直接返回
            }

            // 回溯：撤销本次尝试的映射关系
            charToStr.erase(curChar);
            strToChar.erase(candidate);
        }

        return false; // 所有尝试都失败
    }
};