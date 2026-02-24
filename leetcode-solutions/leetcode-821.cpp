/**
 * 821. Shortest Distance to a Character
 *
 * Given a string s and a character c that occurs in s, return an array of integers answer where answer.length == s.length
 * and answer[i] is the distance from index i to the closest occurrence of character c in s.
 *
 * The distance between two indices i and j is abs(i - j), where abs is the absolute value function.
 *
 * Example:
 * Input: s = "loveleetcode", c = "e"
 * Output: [3,2,1,0,1,0,0,1,2,2,1,0]
 * Explanation: The character 'e' appears at indices 3, 5, 6, and 11 (0-indexed).
 * The closest occurrence of 'e' for index 0 is at index 3, so the distance is abs(0 - 3) = 3.
 * The closest occurrence of 'e' for index 1 is at index 3, so the distance is abs(1 - 3) = 2.
 * For index 4, there is a tie between the 'e' at index 3 and the 'e' at index 5, but the distance is still the same: abs(4 - 3) == abs(4 - 5) = 1.
 * The closest occurrence of 'e' for index 8 is at index 6, so the distance is abs(8 - 6) = 2.
 *
 * Note:
 * 1 <= s.length <= 104
 * s[i] and c are lowercase English letters.
 * It is guaranteed that c occurs at least once in s.
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        int n = s.size();
        vector<int> ans(n, n);  // 初始化为一个较大的数
        int prev = -n;           // 记录上一个 c 出现的位置（负值保证初始距离较大）

        // 从左到右扫描，计算每个位置到左边最近 c 的距离
        for (int i = 0; i < n; ++i) {
            if (s[i] == c) prev = i;
            ans[i] = i - prev;
        }

        prev = 2 * n;            // 从右向左扫描，记录右边最近 c 的位置
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == c) prev = i;
            ans[i] = min(ans[i], prev - i);
        }

        return ans;
    }
};