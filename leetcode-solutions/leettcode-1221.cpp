/**
 * 1221. Split a String in Balanced Strings
 *
 * Balanced strings are those that have an equal quantity of 'L' and 'R' characters.
 *
 * Given a balanced string s, split it in the maximum amount of balanced strings.
 *
 * Return the maximum amount of split balanced strings.
 *
 *
 *
 * Example 1:
 *
 * Input: s = "RLRRLLRLRL"
 * Output: 4
 * Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.
 *
 * Example 2:
 *
 * Input: s = "RLLLLRRRLR"
 * Output: 3
 * Explanation: s can be split into "RL", "LLLRRR", "LR", each substring contains same number of 'L' and 'R'.
 *
 * Example 3:
 *
 * Input: s = "LLLLRRRR"
 * Output: 1
 * Explanation: s can be split into "LLLLRRRR".
 *
 * Example 4:
 *
 * Input: s = "RLRRRLLRLL"
 * Output: 2
 * Explanation: s can be split into "RL", "RRRLLRLL", since each substring contains an equal number of 'L' and 'R'
 *
 *
 * Constraints:
 *
 * 1 <= s.length <= 1000
 * s[i] is either 'L' or 'R'.
 * s is a balanced string.
 *
 */
#include <string>

class Solution1 {
public:
    int balancedStringSplit(std::string s) {
        int balance = 0;  // 平衡计数器
        int count = 0;    // 平衡子串数量
        
        for (char c : s) {
            if (c == 'L') {
                balance++;
            } else {  // c == 'R'
                balance--;
            }
            
            // 当平衡计数器为0时，表示找到一个平衡子串
            if (balance == 0) {
                count++;
            }
        }
        
        return count;
    }
};

// 另一种写法：使用更直观的变量名
class Solution2 {
public:
    int balancedStringSplit(std::string s) {
        int lCount = 0, rCount = 0;
        int result = 0;
        
        for (char c : s) {
            if (c == 'L') lCount++;
            else rCount++;
            
            if (lCount == rCount) {
                result++;
                lCount = rCount = 0;  // 重置计数器（可选，因为相等时自然重置）
            }
        }
        
        return result;
    }
};
