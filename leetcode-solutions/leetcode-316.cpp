/*
 * Remove Duplicate Letters
 * 
 * Given a string text, remove duplicate letters so that every letter appears once and only once.
 * You must make sure your result is the smallest in lexicographical order among all possible results.
 * 
 * Example 1:
 * Input: text = "bcabc"
 * Output: "abc"
 * 
 * Example 2:
 * Input: text = "cbacdcbc"
 * Output: "acdb"
 * 
 * Example 3:
 * Input: text = "leetcode"
 * Output: "letcod"
 * 
 */
#include <string>
#include <vector>
using namespace std;

// string removeDuplicateLetters(string text) {
//   string str;
//   vector<int> count(26);
//   vector<bool> used(26);
//   for (auto i : text) count[i - 'a']++;

//   for (auto i : text) {
//     count[i - 'a']--;
//     if (!used[i - 'a']) {
//       while (str.length() > 0 && i < str.back() && count[str.back() - 'a'] > 0) {
//         used[str.back() - 'a'] = false;
//         str.pop_back();
//       }
//       str.push_back(i);
//       used[i - 'a'] = true;
//     }
//   }
//   return str;
// }

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> lastIndex(26, 0);
        // 记录每个字符最后出现的位置
        for (int i = 0; i < s.size(); ++i) {
            lastIndex[s[i] - 'a'] = i;
        }

        vector<bool> inStack(26, false);
        string st; // 用字符串模拟栈

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            // 如果字符已经在栈中，跳过
            if (inStack[c - 'a']) continue;

            // 当栈非空、栈顶字符大于当前字符、且栈顶字符在后面还会出现时，弹出栈顶
            while (!st.empty() && st.back() > c && lastIndex[st.back() - 'a'] > i) {
                inStack[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            inStack[c - 'a'] = true;
        }

        return st;
    }
};