/*
 * 806. Number of Lines To Write String
 * 
 * We are to write the letters of a given string S, from left to right into lines. Each line has maximum width 100 units, and if writing a letter would cause the width of the line to exceed 100 units, it is written on the next line. We are given an array widths, an array where widths[0] is the width of 'a', widths[1] is the width of 'b', ..., and widths[25] is the width of 'z'.
 * 
 * Now answer two questions: how many lines have at least one character from S, and what is the width used by the last such line? Return your answer as an integer list of length 2.
 * 
 * Example :
 * Input: 
 * widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
 * S = "abcdefghijklmnopqrstuvwxyz"
 * Output: [3, 60]
 * Explanation: 
 * All letters have the same length of 10. To write all 26 letters,
 * we need two full lines and one line with 60 units.
 * 
 * Note:
 * The length of S will be in the range [1, 1000].
 * S will only contain lowercase letters.
 * widths is an array of length 26.
 * widths[i] will be in the range of [2, 10].
 * 
 */
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        int lines = 1;          // 至少一行
        int currentWidth = 0;   // 当前行已用宽度

        for (char c : s) {
            int w = widths[c - 'a'];  // 当前字符需要的宽度
            if (currentWidth + w > 100) {
                // 如果加上当前字符会超过 100，则换行
                lines++;
                currentWidth = w;      // 新行以当前字符宽度开始
            } else {
                currentWidth += w;     // 否则继续累加
            }
        }

        return {lines, currentWidth};
    }
};