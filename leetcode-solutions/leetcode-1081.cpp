/*
 * 1081. Smallest Subsequence of Distinct Characters
 *
 * Return the lexicographically smallest subsequence of text that contains all the distinct characters of text exactly once.
 * 
 * Example 1:
 * Input: "cdadabcc"
 * Output: "adbc"
 * 
 * Example 2:
 * Input: "abcd"
 * Output: "abcd"
 * 
 * Example 3:
 * Input: "ecbacba"
 * Output: "eacb"
 * 
 * Example 4:
 * Input: "leetcode"
 * Output: "letcod"
 * 
 * Note:
 * 1 <= text.length <= 1000
 * text consists of lowercase English letters.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {
        // 统计每个字符出现的次数
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        // 记录字符是否已在栈中
        vector<bool> inStack(26, false);
        string stack; // 用字符串模拟栈
        
        for (char c : s) {
            // 每遍历一个字符，剩余次数减1
            count[c - 'a']--;
            
            // 如果字符已在栈中，跳过
            if (inStack[c - 'a']) {
                continue;
            }
            
            // 维护单调栈：当栈顶字符大于当前字符且后面还会出现时，弹出栈顶
            while (!stack.empty() && c < stack.back() && count[stack.back() - 'a'] > 0) {
                inStack[stack.back() - 'a'] = false;
                stack.pop_back();
            }
            
            // 将当前字符入栈
            stack.push_back(c);
            inStack[c - 'a'] = true;
        }
        
        return stack;
    }
};