/*
 * 816. Ambiguous Coordinates
 * 
 * We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)".  Then, we removed all commas, decimal points, and spaces, and ended up with the string S.  Return a list of strings representing all possibilities for what our original coordinates could have been.
 * 
 * Our original representation never had extraneous zeroes, so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other number that can be represented with less digits.  Also, a decimal point within a number never occurs without at least one digit occuring before it, so we never started with numbers like ".1".
 * 
 * The final answer list can be returned in any order.  Also note that all coordinates in the final answer have exactly one space between them (occurring after the comma.)
 * 
 * Example:
 * Input: "(123)"
 * Output: ["(1, 23)", "(12, 3)", "(1.2, 3)", "(1, 2.3)"]
 * 
 * Note:
 * 4 <= S.length <= 12.
 * S[0] = "(", S[S.length - 1] = ")", and the other elements in S are digits.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        // 去掉括号
        string digits = s.substr(1, s.size() - 2);
        int n = digits.size();
        vector<string> res;

        // 枚举分割点，左边部分长度 i，右边部分长度 n-i
        for (int i = 1; i < n; ++i) {
            string leftStr = digits.substr(0, i);
            string rightStr = digits.substr(i);

            vector<string> leftOpts = generate(leftStr);
            vector<string> rightOpts = generate(rightStr);

            for (const string& l : leftOpts) {
                for (const string& r : rightOpts) {
                    res.push_back("(" + l + ", " + r + ")");
                }
            }
        }

        sort(res.begin(), res.end());
        return res;
    }

private:
    vector<string> generate(string str) {
        vector<string> opts;
        int n = str.size();

        // 整个作为整数（无小数点）
        if (n == 1 || str[0] != '0') {
            opts.push_back(str);
        }

        // 枚举小数点位置：放在第 i 个字符之后（i 从 1 到 n-1）
        for (int i = 1; i < n; ++i) {
            string intPart = str.substr(0, i);
            string fracPart = str.substr(i);

            // 整数部分不能有前导零（除非是单个0）
            if (intPart.size() > 1 && intPart[0] == '0') continue;
            // 小数部分不能以零结尾
            if (fracPart.back() == '0') continue;

            opts.push_back(intPart + "." + fracPart);
        }

        return opts;
    }
};