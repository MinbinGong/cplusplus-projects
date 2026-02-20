/*
 * Palindrome Permutation II
 * 
 * Given a string s, return all the palindromic permutations (without duplicates) of it.
 * You may return the answer in any order. If s has no palindromic permutation, return an empty list.
 * 
 * Example 1:
 * Input: s = "aabb"
 * Output: ["abba", "baab"]
 * 
 * Example 2:
 * Input: s = "abc"
 * Output: []
 * 
 * Constraints:
 * 1. 1 <= s.length <= 16
 * 2. s consists of only lowercase English letters.
 * 3. The length of the string will be in the range of [1, 1000].
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// 时间复杂度：O(n * n!)
// 空间复杂度：O(n)
// 回溯算法
class Solution1 {
private:
    vector<string> result;
    int n;
    
    void backtrack(vector<int>& count, string current) {
        // 如果当前字符串长度达到原长度，说明找到了一个有效回文
        if (current.length() == n) {
            result.push_back(current);
            return;
        }
        
        // 尝试在两侧添加一对相同字符
        for (int i = 0; i < 26; ++i) {
            if (count[i] >= 2) {
                // 选择该字符
                count[i] -= 2;
                char c = 'a' + i;
                // 递归：在当前字符串两侧加上该字符
                backtrack(count, c + current + c);
                // 回溯：恢复状态
                count[i] += 2;
            }
        }
    }
    
public:
    vector<string> generatePalindromes(string s) {
        n = s.length();
        vector<int> count(26, 0);
        
        // 统计每个字符出现次数
        for (char c : s) {
            count[c - 'a']++;
        }
        
        // 检查能否构成回文
        int oddCount = 0;
        char oddChar = 0;
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 == 1) {
                oddCount++;
                oddChar = 'a' + i;
            }
        }
        
        // 如果不能构成回文，返回空列表
        if (oddCount > 1) {
            return {};
        }
        
        // 如果有奇数个字符，先把它作为中间字符
        string start = "";
        if (oddCount == 1) {
            start = string(1, oddChar);
            count[oddChar - 'a']--; // 中间字符用掉一个
        }
        
        result.clear();
        backtrack(count, start);
        return result;
    }
};

// 时间复杂度：O(n * n!)
// 空间复杂度：O(n)
// 排序 + 下一个排列
class Solution2 {
public:
    vector<string> generatePalindromes(string s) {
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;
        
        string mid, half;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                if (mid.empty()) mid = string(1, 'a' + i);
                else return {}; // 多于一个奇数，不可能构成回文
            }
            half += string(cnt[i] / 2, 'a' + i);
        }
        
        vector<string> result;
        do {
            string revHalf = half;
            reverse(revHalf.begin(), revHalf.end());
            result.push_back(half + mid + revHalf);
        } while (next_permutation(half.begin(), half.end()));
        
        return result;
    }
};