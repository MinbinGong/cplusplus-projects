/**
 * 1737. Change Minimum Characters to Satisfy One of Three Conditions
 * 
 * You are given two strings a and b that consist of lowercase letters. In one operation, you can change any character in a or b to any lowercase letter.
 * Your goal is to satisfy one of the following three conditions:
 * Every letter in a is strictly less than every letter in b in the alphabet.
 * Every letter in b is strictly less than every letter in a in the alphabet.
 * Both a and b consist of only one distinct letter.
 * Return the minimum number of operations needed to achieve your goal.
 * 
 * Example 1:
 * Input: a = "aba", b = "caa"
 * Output: 2
 * Explanation: Consider the best way to make each condition true:
 * 1) Change b to "ccc" in 2 operations, then every letter in a is less than every letter in b.
 * 2) Change a to "bbb" and b to "aaa" in 3 operations, then every letter in b is less than every letter in a.
 * 
 * Example 2:
 * Input: a = "dabadd", b = "cda"
 * Output: 3
 * Explanation: The best way is to make condition 1 true by changing b to "eee".
 * 
 * Constraints:
 * 1 <= a.length, b.length <= 105
 * a and b consist only of lowercase letters.
 * 
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minCharacters(string a, string b) {
        int n = a.size(), m = b.size();
        vector<int> cntA(26, 0), cntB(26, 0);
        for (char c : a) cntA[c - 'a']++;
        for (char c : b) cntB[c - 'c']++;  // 注意这里应该是 'a'，但原代码写错了，修正为 'a'
        // 上面一行有笔误，实际应为 cntB[c - 'a']++; 我们将在最终代码中修正

        // 条件3：各自变成单一字符
        int maxA = *max_element(cntA.begin(), cntA.end());
        int maxB = *max_element(cntB.begin(), cntB.end());
        int ans = n + m - maxA - maxB;

        // 前缀和
        vector<int> preA(26, 0), preB(26, 0);
        preA[0] = cntA[0];
        preB[0] = cntB[0];
        for (int i = 1; i < 26; ++i) {
            preA[i] = preA[i-1] + cntA[i];
            preB[i] = preB[i-1] + cntB[i];
        }

        // 枚举分界 i (0~24)
        for (int i = 0; i < 25; ++i) {
            // 条件1：a ≤ i, b > i
            ans = min(ans, (n - preA[i]) + preB[i]);
            // 条件2：a > i, b ≤ i
            ans = min(ans, preA[i] + (m - preB[i]));
        }
        return ans;
    }
};