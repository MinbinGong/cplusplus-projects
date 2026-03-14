/*
 * 1807. Evaluate the Bracket Pairs of a String
 *
 * You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.
 * 
 * For example, in the string "(name)is(age)yearsold", there are two bracket pairs that contain the keys "name" and "age".
 * 
 * Example 1:
 * 
 * Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
 * Output: "bobistwoyearsold"
 * Explanation:
 * The key "name" maps to the value "bob", so replace "(name)" with "bob".
 * The key "age" maps to the value "two", so replace "(age)" with "two".
 * 
 * Example 2:
 * 
 * Input: s = "hi(name)", knowledge = [["a","b"]]
 * Output: "hi?"
 * Explanation: As you do not know the value of the key "name", replace "(name)" with "?".
 * 
 * Example 3:
 * 
 * Input: s = "(a)(a)(a)aaa", knowledge = [["a","yes"]]
 * Output: "yesyesyesaaa"
 * Explanation: The same key can appear multiple times.
 * The key "a" maps to the value "yes", so replace all occurrences of "(a)" with "yes".
 * Notice that the "a"s not in a bracket pair are not evaluated.
 * 
 * Constraints:
 * 
 * 1 <= s.length <= 105
 * 0 <= knowledge.length <= 105
 * knowledge[i].length == 2
 * 1 <= key.length, value.length <= 10
 * s consists of lowercase English letters and round brackets '(' and ')'.
 * Every open bracket '(' in s will have a corresponding close bracket ')'.
 * 
 */
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        // 第一步：构建哈希表，用于快速查找
        unordered_map<string, string> dict;
        for (auto& pair : knowledge) {
            dict[pair[0]] = pair[1];
        }

        string ans;
        int n = s.size();
        // 第二步：遍历字符串
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                // 找到左括号，开始提取 key
                int j = i + 1;
                while (j < n && s[j] != ')') {
                    ++j;
                }
                // 此时 s[j] == ')'，提取子串作为 key
                string key = s.substr(i + 1, j - i - 1);
                
                // 在哈希表中查找，若存在则替换为 value，否则替换为 "?"
                if (dict.count(key)) {
                    ans += dict[key];
                } else {
                    ans += "?";
                }
                
                // 将 i 移动到右括号的位置，循环结束后 i++ 会指向下一个字符
                i = j;
            } else {
                // 普通字符，直接追加
                ans += s[i];
            }
        }
        return ans;
    }
};