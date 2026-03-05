/*
 * 1585. Check if String Is Transformable With Substring Sort Operations
 *
 * Given two strings s and t, you want to transform string s into string t using the following operation any number of times:
 * Choose a non-empty substring in s and sort it in-place so the characters are in ascending order.
 * For example, applying the operation on the underlined substring in "14234" results in "12344".
 * 
 * Return true if it is possible to transform string s into string t. Otherwise, return false.
 * 
 * A substring is a contiguous sequence of characters within a string.
 * 
 * Example 1:
 * Input: s = "84532", t = "34852"
 * Output: true
 * Explanation: You can transform s into t using the following sort operations:
 * "84532" (from index 2 to 3) -> "84352"
 * "84352" (from index 0 to 2) -> "34852"
 * 
 * Example 2:
 * Input: s = "34521", t = "23415"
 * Output: true
 * Explanation: You can transform s into t using the following sort operations:
 * "34521" (from index 0 to 4) -> "23451"
 * "23451" (from index 3 to 4) -> "23415"
 * 
 * Example 3:
 * Input: s = "12345", t = "12435"
 * Output: false
 * Explanation: It is impossible to transform s into t.
 * 
 * Constraints:
 * 1 <= s.length <= 10^5
 * s.length == t.length
 * s and t consist of only digits.
 * 
 */
#include <string>
#include <queue>
using namespace std;

class Solution {
public:
    bool isTransformable(string s, string t) {
        // 使用队列数组存储每个数字 0-9 在 s 中出现的所有下标
        queue<int> pos[10];
        int n = s.size();
        
        // 遍历 s，记录每个数字出现的下标位置
        for (int i = 0; i < n; ++i) {
            pos[s[i] - '0'].push(i);
        }
        
        // 遍历目标字符串 t
        for (char& c : t) {
            int x = c - '0';  // 当前需要匹配的数字
            
            // 如果 s 中已经没有这个数字了，无法完成转换
            if (pos[x].empty()) {
                return false;
            }
            
            // 关键检查：对于所有比 x 小的数字 j
            // 如果 j 在 s 中的最靠前位置比 x 的最靠前位置还要靠前
            // 那么 x 无法被移动到当前位置，因为排序时小数字会挡住它
            for (int j = 0; j < x; ++j) {
                if (!pos[j].empty() && pos[j].front() < pos[x].front()) {
                    return false;
                }
            }
            
            // 当前数字 x 可以被匹配，将其从队列中移除（表示已使用）
            pos[x].pop();
        }
        
        return true;
    }
};