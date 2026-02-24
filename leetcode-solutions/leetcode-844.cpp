/*
 * 844. Backspace String Compare
 * 
 * Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.
 * 
 * Note that after backspacing an empty text, the text will continue empty.
 * 
 * Example 1:
 * Input: S = "ab#c", T = "ad#c"
 * Output: true
 * Explanation: Both S and T become "ac".
 * 
 * Example 2:
 * Input: S = "ab##", T = "c#d#"
 * Output: true
 * Explanation: Both S and T become "".
 * 
 * Example 3:
 * Input: S = "a##c", T = "#a#c"
 * Output: true
 * Explanation: Both S and T become "c".
 * 
 * Example 4:
 * Input: S = "a#c", T = "b"
 * Output: false
 * Explanation: S becomes "c" while T becomes "b".
 * 
 * Note:
 * 1 <= S.length <= 200
 * 1 <= T.length <= 200
 * S and T only contain lowercase letters and '#' characters.
 * 
 */
#include <string>
#include <vector>
using namespace std;

class Solution1 {
public:
    bool backspaceCompare(string s, string t) {
        return build(s) == build(t);
    }

    string build(string str) {
        string ret;
        for (char c : str) {
            if (c != '#') {
                ret.push_back(c);
            } else if (!ret.empty()) {
                ret.pop_back();
            }
        }
        return ret;
    }
};

class Solution2 {
public:
    bool backspaceCompare(string s, string t) {
        int i = s.length() - 1, j = t.length() - 1;
        int skipS = 0, skipT = 0;

        while (i >= 0 || j >= 0) {
            // 处理 s 的退格
            while (i >= 0) {
                if (s[i] == '#') {
                    skipS++;
                    i--;
                } else if (skipS > 0) {
                    skipS--;
                    i--;
                } else {
                    break;
                }
            }
            // 处理 t 的退格
            while (j >= 0) {
                if (t[j] == '#') {
                    skipT++;
                    j--;
                } else if (skipT > 0) {
                    skipT--;
                    j--;
                } else {
                    break;
                }
            }
            // 比较当前有效字符
            if (i >= 0 && j >= 0) {
                if (s[i] != t[j]) return false;
            } else if (i >= 0 || j >= 0) {
                // 一个已结束，另一个还有有效字符
                return false;
            }
            i--;
            j--;
        }
        return true;
    }
};