/**
 * 1794. Count Pairs of Equal Substrings With Minimum Difference
 * 
 * You are given two strings s and t of equal length. You want to change s to t. Changing the i-th character of s to i-th character of t costs |s[i] - t[i]| that is, the absolute difference between the ASCII values of the characters.
 * 
 * You are also given an integer maxCost.
 * 
 * Return the maximum length of a substring of s that can be changed to be the same as the corresponding substring of twith a cost less than or equal to maxCost.
 * 
 * If there is no substring from s that can be changed to its corresponding substring from t, return 0.
 * 
 *  
 * 
 * Example 1:
 * 
 * Input: s = "abcd", t = "bcdf", maxCost = 3
 * Output: 3
 * Explanation: "abc" of s can change to "bcd". That costs 3, so the maximum length is 3.
 * Example 2:
 * 
 * Input: s = "abcd", t = "cdef", maxCost = 3
 * Output: 1
 * Explanation: Each character in s costs 2 to change to charactor in t, so the maximum length is 1.
 * Example 3:
 * 
 * Input: s = "abcd", t = "acde", maxCost = 0
 * Output: 1
 * Explanation: You can't make any change, so the maximum length is 1.
 *  
 * 
 * Constraints:
 * 
 * 1 <= s.length, t.length <= 10^5
 * 0 <= maxCost <= 10^6
 * s and t only contain lower case English letters.
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countQuadruples(string firstString, string secondString) {
        // 记录每个字符在 secondString 中最后一次出现的位置（1-indexed，0表示未出现）
        int lastPos[26] = {0};
        for (int i = 0; i < secondString.size(); ++i) {
            lastPos[secondString[i] - 'a'] = i + 1;  // 存储位置+1，以便区分未出现的情况
        }
        
        int minDiff = INT_MAX;  // 最小差值
        int count = 0;          // 满足最小差值的数量
        
        // 遍历 firstString
        for (int i = 0; i < firstString.size(); ++i) {
            int idx = firstString[i] - 'a';
            if (lastPos[idx] > 0) {  // 该字符在 secondString 中出现过
                int diff = i - lastPos[idx];  // i - (a+1) 相当于 i - a - 1
                if (diff < minDiff) {
                    minDiff = diff;
                    count = 1;
                } else if (diff == minDiff) {
                    count++;
                }
            }
        }
        return count;
    }
};