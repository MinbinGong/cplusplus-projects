/**
 * 1593. Split a String Into the Max Number of Unique Substrings
 * 
 * Given a string s, return the maximum number of unique substrings that the given string can be split into.
 * 
 * You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string. However, you must split the substrings such that all of them are unique.
 * 
 * A substring is a contiguous sequence of characters within a string.
 * 
 * Example 1:
 * Input: s = "ababccc"
 * Output: 5
 * Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.
 * 
 * Example 2:
 * Input: s = "aba"
 * Output: 2
 * Explanation: One way to split maximally is ['a', 'ba'].
 * 
 * Example 3:
 * Input: s = "aa"
 * Output: 1
 * Explanation: It is impossible to split the string any further.
 * 
 * Constraints:
 * 1 <= s.length <= 16
 * s contains only lower case English letters.
 * 
 */
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxUniqueSplit(string s) {
        unordered_set<string> seen;
        int maxCount = 0;
        backtrack(s, 0, seen, 0, maxCount);
        return maxCount;
    }

private:
    void backtrack(const string& s, int start, unordered_set<string>& seen, 
                   int count, int& maxCount) {
        int n = s.size();
        // 如果已经到达字符串末尾，更新最大分割数
        if (start == n) {
            maxCount = max(maxCount, count);
            return;
        }
        
        // 剪枝：即使剩下的每个字符单独成串，也无法超过当前最优解
        if (count + (n - start) <= maxCount) return;

        // 尝试所有可能的子串，从 start 开始
        for (int end = start + 1; end <= n; ++end) {
            string sub = s.substr(start, end - start);
            // 如果子串未出现过，则加入集合并递归
            if (seen.find(sub) == seen.end()) {
                seen.insert(sub);
                backtrack(s, end, seen, count + 1, maxCount);
                seen.erase(sub); // 回溯
            }
        }
    }
};