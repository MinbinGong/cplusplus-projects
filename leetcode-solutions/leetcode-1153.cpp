/**
 * 1153. String Transforms Into Another String
 * Hard
 * 
 * (This problem is an interactive problem.)
 * 
 * Given two strings str1 and str2 of the same length, determine whether you can transform str1 into str2 by doing zero or more conversions.
 * 
 * In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.
 * 
 * Return true if and only if you can transform str1 into str2.
 * 
 * Example 1:
 * Input: str1 = "aabcc", str2 = "ccdee"
 * Output: true
 * Explanation: 
 * Convert 'c' to 'e' then 'b' to 'd' then 'a' to 'c'. Note that the order of conversions matter.
 * 
 * Example 2:
 * Input: str1 = "leetcode", str2 = "codeleet"
 * Output: false
 * Explanation: 
 * There is no way to transform str1 to str2.
 * 
 * Note:
 * 1 <= str1.length == str2.length <= 10^4
 * 0 <= str1[i], str2[i] <= 10^9
 * 
 */
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    bool canConvert(string str1, string str2) {
        // 如果两个字符串相等，不需要任何转换
        if (str1 == str2) return true;

        // 统计str2中不同字符的数量
        int cnt[26] = {0};
        int uniqueCharInStr2 = 0;
        for (char c : str2) {
            if (++cnt[c - 'a'] == 1) {
                ++uniqueCharInStr2;
            }
        }

        // 关键条件：如果str2包含了所有26个小写字母，
        // 则无法转换（除非str1和str2已经相等，但前面已判断）
        // 因为转换需要一个临时字符作为桥梁，但所有字符都被占用了
        if (uniqueCharInStr2 == 26) return false;

        // 建立映射关系：str1中的字符 -> str2中对应的字符
        // 使用数组模拟哈希表，0表示未映射，1~26表示映射到的字符
        int mapping[26] = {0};
        for (int i = 0; i < str1.size(); ++i) {
            int a = str1[i] - 'a';
            int b = str2[i] - 'a';
            
            if (mapping[a] == 0) {
                mapping[a] = b + 1;  // +1是为了区分0（未映射）和映射到'a'（值为0）的情况
            } else if (mapping[a] != b + 1) {
                return false;  // 同一个字符映射到了不同的目标字符（一对多）
            }
        }

        return true;
    }
};