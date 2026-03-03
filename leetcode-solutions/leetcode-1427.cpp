/**
 * 1427. Perform String Shifts
 * 
 * You are given a string s containing lowercase English letters, and a matrix shift, where shift[i] = [direction, amount]:
 * 
 * direction can be 0 (for left shift) or 1 (for right shift). 
 * amount is the amount by which string s is to be shifted.
 * A left shift by 1 means remove the first character of s and append it to the end.
 * Similarly, a right shift by 1 means remove the last character of s and add it to the beginning.
 * Return the final string after all operations.
 * 
 * Example 1:
 * 
 * Input: s = "abc", shift = [[0,1],[1,2]]
 * Output: "cab"
 * Explanation: 
 * [0,1] means shift to left by 1. "abc" -> "bca"
 * [1,2] means shift to right by 2. "bca" -> "cab"
 * 
 * Example 2:
 * 
 * Input: s = "abcdefg", shift = [[1,1],[1,1],[0,2],[1,3]]
 * Output: "efgabcd"
 * Explanation:  
 * [1,1] means shift to right by 1. "abcdefg" -> "gabcdef"
 * [1,1] means shift to right by 1. "gabcdef" -> "fgabcde"
 * [0,2] means shift to left by 2. "fgabcde" -> "abcdefg"
 * [1,3] means shift to right by 3. "abcdefg" -> "efgabcd"
 * 
 * Note:
 * 1 <= s.length <= 100
 * s only contains lower case English letters.
 * 1 <= shift.length <= 100
 * shift[i].length == 2
 * 0 <= shift[i][0] <= 1
 * 0 <= shift[i][1] <= 100
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string stringShift(string s, vector<vector<int>>& shift) {
        int totalShift = 0;
        // 第一步：计算净移位量（右移为正，左移为负）
        for (const auto& op : shift) {
            int direction = op[0];
            int amount = op[1];
            if (direction == 1) { // 右移
                totalShift += amount;
            } else { // 左移
                totalShift -= amount;
            }
        }

        int n = s.length();
        // 第二步：将净移位量规范化到 [0, n-1] 范围内
        // 注意：C++中取模可能为负，因此采用 (totalShift % n + n) % n 处理
        totalShift = ((totalShift % n) + n) % n; // 现在 totalShift 表示等效右移位数

        // 第三步：执行最终的一次性移位
        // 如果 totalShift == 0，直接返回原字符串
        if (totalShift == 0) return s;
        // 右移 totalShift 位等价于：最后 totalShift 个字符移到前面
        return s.substr(n - totalShift) + s.substr(0, n - totalShift);
    }
};