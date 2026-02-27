/*
 * 1087. Brace Expansion
 *
 * A string S represents a list of words.
 * Each letter in the word has 1 or more options.  If there is one option, the letter is represented as is.  If there is more than one option, then curly braces delimit the options.  For example, "{a,b,c}" represents options ["a", "b", "c"].
 * For example, "{a,b,c}d{e,f}" represents the list ["ade", "adf", "bde", "bdf", "cde", "cdf"].
 * Return all words that can be formed in this manner, in lexicographical order.
 * 
 * Example 1:
 * Input: "{a,b}c{d,e}f"
 * Output: ["acdf","acef","bcdf","bcef"]
 * 
 * Example 2:
 * Input: "abcd"
 * Output: ["abcd"]
 * 
 * Note:
 * 1 <= S.length <= 50
 * There are no nested curly brackets.
 * All characters inside a pair of consecutive opening and ending curly brackets are different.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> expand(string s) {
        vector<string> result;
        string current;
        dfs(s, 0, current, result);
        
        // 按字典序排序
        sort(result.begin(), result.end());
        return result;
    }
    
private:
    void dfs(const string& s, int index, string& current, vector<string>& result) {
        // 递归终止条件：到达字符串末尾
        if (index >= s.length()) {
            result.push_back(current);
            return;
        }
        
        // 保存当前路径长度，用于回溯
        int originalLength = current.length();
        
        if (s[index] == '{') {
            // 找到对应的 '}'
            int end = index + 1;
            while (end < s.length() && s[end] != '}') {
                end++;
            }
            
            // 提取括号内的字符选项
            vector<char> options;
            for (int i = index + 1; i < end; i++) {
                if (isalpha(s[i])) {  // 只处理字母字符
                    options.push_back(s[i]);
                }
            }
            
            // 对选项按字典序排序（题目要求最终结果有序）
            sort(options.begin(), options.end());
            
            // 对每个选项进行递归
            for (char c : options) {
                current.push_back(c);
                dfs(s, end + 1, current, result);
                current.pop_back();  // 回溯
            }
        } 
        else if (isalpha(s[index])) {
            // 普通字符，直接添加
            current.push_back(s[index]);
            dfs(s, index + 1, current, result);
            current.pop_back();  // 回溯
        }
        else {
            // 跳过逗号等其他字符
            dfs(s, index + 1, current, result);
        }
    }
};